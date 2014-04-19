/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <libgen.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>

#include <shared/error.h>
#include <shared/xalloc.h>
#include <shared/check.h>
#include <shared/string.h>

#include <adt/action.h>
#include <adt/entry.h>
#include <adt/char.h>
#include <adt/cmd.h>
#include <adt/keyword.h>
#include <adt/tree.h>
#include <adt/type.h>
#include <adt/zone.h>
#include <adt/group.h>
#include <adt/localnames.h>
#include <adt/nametrans.h>

#include <out/c.h>
#include <out/common.h>

#include "lexer.h"
#include "lctsyntax.h"
#include "options.h"

static int output_cmds(struct zone *parent, struct cmd_list *ret, unsigned int n, unsigned int d);
static void output_pass(struct zone* z, struct character *p, int in_pre_pass, unsigned int n, unsigned int d);

/*
 * This is populated by the selected output language, set from opt->language.
 * It may be inspected for language-specific regions of the generated code.
 */
enum {
	C90,
	C99
} language;


/*
 * OUTPUT OPTIONS
 *
 * The flag in_pre_pass is used to indicate the preliminary pass to
 * output_pass.  read_name gives the name of the character reading
 * function used in the output routines.
 */
static const char *read_token_name;
static const char *lexi_prefix;


/*
 * OUTPUT FILE
 *
 * These variables gives the output files. out is used within this file
 * as a shorthand for lex_output. Likewise lex_output_h is a convenience
 * for the output header.
 *
 * These correspond to options.output[0].file and [1] respectively.
 */
FILE *lex_output;
FILE *lex_output_h;


/*
 * FIND A CHARACTER LITERAL
 *
 * This routine finds the character literal corresponding to c.
 */
static const char *
char_lit(int c)
{
	static char buf[10];

	switch (c) {
	case EOF:  return "LEXI_EOF";	/* XXX: convert to EOF instead */
	case '\n': return "'\\n'";
	case '\r': return "'\\r'";
	case '\t': return "'\\t'";
	case '\v': return "'\\v'";
	case '\f': return "'\\f'";
	case '\\': return "'\\\\'";
	case '\'': return "'\\''";
	}

	if (c > 127 || c <= 0) {
		return "'?'";
	}

	sprintf(buf, "'%c'", c);

	return buf;
}


/*
 * FIND THE LENGTH REQUIRED FOR THE TOKEN BUFFER
 *
 * A token buffer is only required if prepass mappings and the tokens proper
 * constitute more than one character in total. For just one character
 * lookahead, lexi_push() would never be called, and so the buffer is
 * unneccessary, and its length will be zero.
 */
static unsigned int
buffer_length(struct lexer_parse_tree *top_level)
{
	unsigned int i;
	struct zone *global;

	/* XXX: account for is_beginendmarker_in_zone */
	global = tree_get_globalzone(top_level);
	assert(global != NULL);

	i = zone_maxlength(global, 0);
	if (global->pre) {
		i += zone_maxlength(global, 1);
	}

	return i;
}

static void
output_groupname(FILE *f, struct group_name *gn)
{
	const char *prefix;

	assert(f != NULL);
	assert(gn != NULL);

	prefix = zone_isglobal(gn->z) ? "group" : gn->z->name;

	fprintf(f, "%s%s_%s", lexi_prefix, prefix, gn->name);
}

static void
output_keyword(struct keyword *keyword, void *opaque)
{
	FILE *output = opaque;

	fprintf(output, "\tif (");

	fprintf(output, "0 == strcmp(identifier, \"%s\")) return ", keyword_name(keyword));

	switch (keyword_cmd(keyword)->type) {
	case return_terminal:
		fprintf(output, "%s", keyword_cmd(keyword)->u.name);
		break;

	default:
		assert(!"unrecognised command type for keyword");
	}

	fprintf(output, ";\n");
}

/*
 * KEYWORDS GENERATION
 *
 * This routine outputs a keyword interface.
 *
 * TODO at some point (where the code is clearer), this can
 * be rewritten to generate and output a trie in its own right.
 * For the moment, we just need the interface in place to set
 * the generated API.
 */
static void
output_keywords(struct lexer_parse_tree *top_level, FILE *output, FILE *output_h)
{
	assert(top_level != NULL);
	assert(output != NULL);
	assert(output_h != NULL);

	if (tree_get_globalzone(top_level)->keywords == NULL) {
		return;
	}

	fputs("\n/* Identify a keyword */\n", output_h);
	fprintf(output_h, "int %skeyword(const char *identifier, int notfound);\n",
		lexi_prefix);

	fprintf(output, "#include <string.h>\n");
	fprintf(output, "int %skeyword(const char *identifier, int notfound) {\n",
		lexi_prefix);

	keywords_iterate(tree_get_globalzone(top_level)->keywords, output_keyword, output);

	fprintf(output, "\treturn notfound;\n}\n");
}

static void
output_locals(struct LocalNamesT *locals, unsigned int d, FILE *lex_output)
{
	struct LocalNamesIteratorT it;
	const char *prefixvar = "ZV";
	const char *prefixtype = "ZT";
	char *st;
	char *s;

	assert(locals != NULL);
	assert(lex_output != NULL);

	s = xmalloc_nof(char, locals->max_depth + 1);

	for (localnames_begin(&it, locals);
	    it.p;
	    localnamesiterator_next(&it))
	{
		struct LocalNamesEntryT *p = it.p;
		struct entry *et = p->et;
		int i;

		s[it.depth] = 0;

		for (i = it.depth - 1; i >= 0; i--) {
			/* TODO: assert(p) */
			s[i] = p->c;
			p = p->up;
		}

		/* TODO: assert(entry_is_type(t)); */

		if (et->u.type->mapped) {
			prefixtype = "";
			st = nstring_to_cstring(&et->u.type->mapping);
		} else {
			st = nstring_to_cstring(entry_key(et));
		}

		output_indent(lex_output, d);
		fprintf(lex_output,"%s%s %s%s;\n", prefixtype, st, prefixvar, s);

		DEALLOCATE(st);
	}

	xfree(s);
}

static void
output_action(FILE *lex_output, struct lexer_parse_tree *top_level,
	struct entry *ea, struct args_list *lhs, struct args_list *rhs, unsigned int d)
{
	struct NameTransT trans;

	assert(lex_output != NULL);
	assert(top_level != NULL);
	assert(ea != NULL);
	assert(lhs != NULL);
	assert(rhs != NULL);

	/* TODO: assert(entry_is_action(action)) */
	/*
	 * Semi Inefficient: we will recreate the translator stack each time
	 * we output the same action; this will never be the same translator stack,
	 * however the sort will always give the same permutation: an optimization
	 * should be possible here. I don't see it as necessary for the moment.
	 */
	nametrans_init(&trans, typetuple_length(&ea->u.act->in) + typetuple_length(&ea->u.act->out));
	nametrans_append_tuple(&trans, &ea->u.act->in,  rhs);
	nametrans_append_tuple(&trans, &ea->u.act->out, lhs);
	nametrans_sort(&trans);

	/* TODO: output #line delimiters instead of comments */
	output_indent(lex_output, d);
	fprintf(lex_output, "/* ACTION <%s> */\n", nstring_to_cstring(entry_key(ea)));

	output_indent(lex_output, d);
	fprintf(lex_output, "{\n");

	d++;

	if (lhs->nb_return_terminal) {
		char *prefixtype = "ZT";
		struct entry *et;
		char *st;

		et = lexer_terminal_type(top_level);
		/* TODO assert(entry_is_type(t)); */

		if (et->u.type->mapped) {
			prefixtype="";
			st = nstring_to_cstring(&et->u.type->mapping);
		} else {
			st = nstring_to_cstring(entry_key(et));
		}

		output_indent(lex_output, d);
		fprintf(lex_output,"%s%s ZT1;\n", prefixtype, st);
	}

	/* End Semi Inefficient */

	if (action_is_defined(ea->u.act)) {
		ccode_output(lex_output, &ea->u.act->code, &trans, d );
		if (lhs->nb_return_terminal) {
			/*TODO assert(lhs->nb_return_terminal==1)*/
			output_indent(lex_output, d);
			fputs("return ZT1;\n",lex_output);
		}
	} else {
		/*TODO We should catch this error before beginning output */
		char* pe=nstring_to_cstring(entry_key(ea));
		error(ERROR_SERIOUS, "Action %s is used but undefined", pe);
		DEALLOCATE(pe);
	}

	d--;

	output_indent(lex_output, d);
	fprintf(lex_output, "}\n");

	output_indent(lex_output, d);
	fprintf(lex_output, "/* END ACTION <%s> */\n", nstring_to_cstring(entry_key(ea)));
}


static void
output_pushzone(struct zone *parent, struct cmd *cmd, unsigned int n, unsigned int d)
{
	assert(parent != NULL);
	assert(cmd != NULL);
	assert(cmd->type == push_zone);

	if (cmd->u.s.z->type == typezone_general_zone) {
		output_indent(lex_output, d);
		fprintf(lex_output, "state->zone = %s_%s;\n",
			read_token_name, cmd->u.s.z->name);
	}

	if (cmd->u.s.z->enter->head != NULL) {
		output_cmds(parent, cmd->u.s.z->enter, n, d);
	}

	if (cmd->u.s.z->enter->nb_return_terminal != 0) {
		return;
	}

	output_indent(lex_output, d);
	switch (cmd->u.s.z->type) {
	case typezone_general_zone:
		fprintf(lex_output, "return %s(state);\n", read_token_name);
		break;

	case typezone_pseudo_token:
		fprintf(lex_output, "return %s_%s(state);\n", read_token_name, cmd->u.s.z->name);
		break;

	case typezone_pure_function:
		fprintf(lex_output, "%s_%s(state);\n", read_token_name, cmd->u.s.z->name);
		output_indent(lex_output, d);
		fputs("goto start;	/* pure function */\n", lex_output);
		break;
	}
}

static void
output_popzone(struct zone *parent, struct cmd *cmd, unsigned int n, unsigned int d)
{
	assert(parent != NULL);
	assert(cmd != NULL);
	assert(cmd ->type == pop_zone);

	if (parent->type == typezone_general_zone) {
		output_indent(lex_output, d);
		if (zone_isglobal(cmd->u.s.z)) {
			fprintf(lex_output, "state->zone = %s;\n", read_token_name);
		} else {
			fprintf(lex_output, "state->zone = %s_%s;\n", read_token_name,
				cmd->u.s.z->name);
		}
	}

	if (!cmd->u.s.is_beginendmarker_in_zone) {
		unsigned int i;

		for (i = n + 1; i > 0; i--) {
			output_indent(lex_output, d);
			fprintf(lex_output, "%spush(state, c%u);\n", lexi_prefix, i - 1);
		}
	}

	if (parent->exit->head) {
		output_cmds(parent, parent->exit, n, d);
	}

	if (parent->exit->nb_return_terminal != 0) {
		return;
	}

	output_indent(lex_output, d);
	switch (parent->type) {
	case typezone_general_zone:
		fprintf(lex_output, "return %s(state);\n", read_token_name);
		break;

	case typezone_pure_function:
		fputs("return;\n", lex_output);
		break;

	case typezone_pseudo_token:
		UNREACHED;
	}
}

/*
 * Returns true if a return was made; false indicates that control is still
 * present in the containing block.
 */
static int
output_cmds(struct zone *parent, struct cmd_list *ret, unsigned int n, unsigned int d)
{
	struct cmd *cmd;
	struct LocalNamesT *locals;
	int r;

	assert(parent != NULL);
	assert(ret != NULL);

	locals = cmdlist_localnames(ret);
	if (locals->top) {
		output_indent(lex_output, d);
		fputs("{\n", lex_output);
		++d;
		output_locals(locals, d, lex_output);
	}

	r = 0;
	for (cmd = ret->head; cmd != NULL; cmd = cmd->next) {
		/* TODO: can simplify the calls to output_pushzone() et al by passing only what we need, not the entire cmd */
		switch (cmd->type) {
		case return_terminal:
			r = 1;
			assert(cmd->next == NULL);
			output_indent(lex_output, d);
			fprintf(lex_output, "return %s;\n", cmd->u.name);
			break;

		case action_call:
			output_action(lex_output, parent->top_level, cmd->u.act.called_act, cmd->u.act.lhs, cmd->u.act.rhs, d);
			break;

		case push_zone:
			r = 1;
			output_pushzone(parent, cmd, n, d);
			break;

		case pop_zone:
			r = 1;
			output_popzone(parent, cmd, n, d);
			break;

		case do_nothing:
			assert(cmd->next == NULL); /* caught during parsing */
			break;
		}
	}

	if (locals->top) {
		d--;
		output_indent(lex_output, d);
		fputs("}\n", lex_output);
	}

	return r;
}

static void
output_mapping(const char *map, unsigned int d)
{
	const char *str;
	char m;

	assert(map != NULL);

	if (strlen(map) == 0) {
		output_indent(lex_output, d);
		fputs("goto start;\n", lex_output);
		return;
	}

	/* TODO: this could probably be simplified if we store the mapping un-escaped */
	if (map[0] == '\\') {
		str = char_lit(find_escape(map[1]));
		m = map[2];
	} else {
		str = char_lit(map[0]);
		m = map[1];
	}

	if (m != '\0') {
		error(ERROR_SERIOUS, "Bad mapping string, '%s'", map);
	}

	output_indent(lex_output, d);
	fprintf(lex_output, "c0 = %s;\n", str);

	output_indent(lex_output, d);
	fputs("goto restart;\n", lex_output);
}

/*
 * Returns true if a return was made; false indicates that control is still
 * present in the containing block.
 */
static int
output_leaf(struct zone *parent, struct character *p, int in_pre_pass, unsigned int n, unsigned int d)
{
	assert(parent != NULL);
	assert(p != NULL);

	/* TODO: could avoid passing in_pre_pass around by finding it on the fly */
	/* TODO: this can be reworked. also see u.map simplification for adt/char.h */
	if (in_pre_pass) {
		if (p->u.map != NULL) {
			output_mapping(p->u.map, d);
		}

		return 1;
	}

	if (p->u.cmds != NULL) {
		if (!output_cmds(parent, p->u.cmds, n, d)) {
			output_indent(lex_output, d);
			fprintf(lex_output, "goto start; /* leaf */\n");
		}

		return 1;
	}

	return 0;
}

static void
output_char_letters(struct zone *z, struct character *p, int in_pre_pass, unsigned int n, unsigned int d)
{
	struct character *q;
	int letters;

	assert(z != NULL);
	assert(p != NULL);

	/* count letters */
	letters = 0;
	for (q = p; q != NULL; q = q->opt) {
		letters += q->type == char_letter;
	}

	/* output letters as appropiate for the given count */
	switch (letters) {
	case 0:
		return;

	case 1:
		/* find the single char_letter */
		for (q = p; q->type != char_letter; q = q->opt) {
			assert(q->opt != NULL);
		}

		assert(q != NULL);

		output_indent(lex_output, d);
		fprintf(lex_output, "if (c%u == %s) {\n", n, char_lit(q->v.c));

		if (q->next != NULL) {
			output_pass(z, q->next, in_pre_pass, n + 1, d + 1);
		}
		output_leaf(z, q, in_pre_pass, n, d + 1);

		output_indent(lex_output, d);
		fputs("}\n", lex_output);

		return;

	default:
		output_indent(lex_output, d);
		fprintf(lex_output, "switch (c%u) {\n", n);
		for (q = p; q != NULL; q = q->opt) {
			int r;

			if (q->type != char_letter) {
				continue;
			}

			output_indent(lex_output, d);
			fprintf(lex_output, "case %s: {\n", char_lit(q->v.c));
			d++;

			if (q->next != NULL) {
				output_pass(z, q->next, in_pre_pass, n + 1, d + 1);
			}
			r = output_leaf(z, q, in_pre_pass, n, d + 1);

			output_indent(lex_output, d);
			fputs("}\n", lex_output);

			if (!r) {
				output_indent(lex_output, d);
				fputs("break;\n", lex_output);
			}

			fputs("\n", lex_output);

			d--;
		}
		output_indent(lex_output, d);
		fputs("}\n", lex_output);

		return;
	}
}

static void
output_char_groups(struct zone *z, struct character *p, int in_pre_pass, unsigned int n, unsigned int d)
{
	struct character *q;
	int started;
	int groups;

	assert(z != NULL);
	assert(p != NULL);

	/* count groups */
	groups = 0;
	for (q = p; q != NULL; q = q->opt) {
		groups += q->type == group_letter;
	}

	if (groups == 0) {
		return;
	}

	/* output groups */
	started = 0;
	for (q = p; q != NULL; q = q->opt) {
		struct group_name *gn;

		if (q->type != group_letter) {
			continue;
		}

		gn = q->v.g.gn;
		output_indent(lex_output, d);

		if (started) {
			fputs("} else ", lex_output);
		}

		fprintf(lex_output, "if (%s%sgroup(", q->v.g.not ? "!" : "", lexi_prefix);
		output_groupname(lex_output, gn);
		fprintf(lex_output, ", c%u)) {\n", n);

		if (q->next != NULL) {
			output_pass(z, q->next, in_pre_pass, n + 1, d + 1);
		}

		output_leaf(z, q, in_pre_pass, n, d + 1);

		started = 1;
	}

	output_indent(lex_output, d);
	fputs("}\n", lex_output);
}

/*
 * OUTPUT PASS INFORMATION
 *
 * This routine outputs code for the lexical pass indicated by p.
 * n gives the depth of recursion and d gives the indentation.
*/
static void
output_pass(struct zone *z, struct character *p, int in_pre_pass, unsigned int n, unsigned int d)
{
	int w1 = n == 0 && !in_pre_pass;
	int w2 = n == 0 && in_pre_pass;

	assert(z != NULL);
	assert(p != NULL);

	output_indent(lex_output, d);
	if (!in_pre_pass && z->pre) {
		if (zone_isglobal(z)) {
			fprintf(lex_output, "int c%u = %s_aux(state)",
				n, read_token_name);
		} else {
			fprintf(lex_output, "int c%u = %s_%s_aux(state)",
				n, read_token_name, z->name);
		}
	} else {
		fprintf(lex_output, "int c%u = %sreadchar(state)", n, lexi_prefix);
	}
	fputs(";\n", lex_output);

	/* TODO: can we move out w1 and w2 into output_zone_*pass(), and keep the recursion simple? */
	if (w1) {
		struct group_name *white;

		white = find_group(z, "white");
		if (white != NULL && !is_group_empty(white->g)) {
			output_indent(lex_output, d);
			fprintf(lex_output, "if (%sgroup(", lexi_prefix);
			output_groupname(lex_output, white);
			fprintf(lex_output, ", c0)) goto start;\n");
		}
	}
	if (w2) {
		output_indent(lex_output, d);
		fputs("restart: {\n", lex_output);
		d++;
	}

	/* We match letters before groups; letters have priority (TODO do we need to?) */
	output_char_letters(z, p, in_pre_pass, n, d);
	output_char_groups (z, p, in_pre_pass, n, d);

	if (w2) {
		d--;
		output_indent(lex_output, d);
		fputs("}\n", lex_output);
	}

	if (n) {
		output_indent(lex_output, d);
		fprintf(lex_output, "%spush(state, c%u);\n", lexi_prefix,n);
	}
}

static void
output_zone_pass_prototypes(struct zone *p)
{
	struct zone *z;
	const char *s;

	assert(p != NULL);

	for (z = p->next; z != NULL; z = z->opt) {
		output_zone_pass_prototypes(z);
	}

	s = p->type == typezone_pure_function ? "void" : "int";

	if (p == tree_get_globalzone(p->top_level)) {
		return;
	}

	fprintf(lex_output,"static %s %s_%s(struct %sstate *state);\n", s,
		read_token_name, p->name, lexi_prefix);
}

static void
output_zone_prepass(struct zone *z)
{
	assert(z != NULL);

	/* recurr through all zones */
	{
		struct zone *p;

		for (p = z->next; p != NULL; p = p->opt) {
			output_zone_prepass(p);
		}
	}

	if (z->pre == NULL) {
		return;
	}

	fprintf(lex_output, "/* PRE PASS ANALYSER for %s*/\n\n", zone_name(z));
	if (zone_isglobal(z)) {
		fprintf(lex_output, "static int %s_aux(struct %sstate *state)\n",
			read_token_name, lexi_prefix);
	} else {
		fprintf(lex_output, "static int %s_%s_aux(struct %sstate *state)\n",
			read_token_name, z->name, lexi_prefix);
	}
	fputs("{\n", lex_output);
	fputs("\tstart: {\n", lex_output);

	output_pass(z, z->pre, 1, 0, 2);
	output_leaf(z, z->pre, 1, 0, 2);

	fputs("\treturn c0;\n", lex_output);
	fputs("\t}\n", lex_output);
	fputs("}\n\n\n", lex_output);

	return;
}

static void
output_zone_pass(struct options *opt, struct zone *p)
{
	/* recurr through all zones */
	{
		struct zone *z;

		for (z = p->next; z != NULL; z = z->opt) {
			output_zone_pass(opt, z);
		}
	}

	fprintf(lex_output, "\n/* MAIN PASS ANALYSER for %s */\n", zone_name(p));
	if (zone_isglobal(p)) {
		fprintf(lex_output,"int\n%s(struct %sstate *state)\n",
			read_token_name, lexi_prefix);
		fputs("{\n", lex_output);
		if (tree_get_globalzone(p->top_level)->next != NULL) {
			fprintf(lex_output, "\tif (state->zone != %s)\n", read_token_name);
			fprintf(lex_output, "\t\treturn state->zone(state);\n");
		}
	} else {
		const char *s;

		s = p->type == typezone_pure_function ? "void" : "int";

		fprintf(lex_output, "static %s\n%s_%s(struct %sstate *state)\n", s,
		read_token_name, p->name, lexi_prefix);
		fputs("{\n", lex_output);
	}

	fputs("\tstart: {\n", lex_output);

	/* main pass */
	if (p->main != NULL) {
		output_pass(p, p->main, 0, 0, 2);
	}

	/* TOKEN DEFAULT -> ...; */
	fprintf(lex_output, "\n\t\t/* DEFAULT */\n");
	if (p->local != NULL) {
		if (!output_cmds(p, p->local, 1, 2)) {
			output_indent(lex_output, 2);
			fprintf(lex_output, "goto start; /* DEFAULT */\n");
		}
	} else {
		fprintf(lex_output, "\t\treturn %sunknown_token;\n",
			opt->interface_prefix);
	}

	fputs("\t}\n", lex_output);
	fputs("}\n", lex_output);

	return;
}

/*
 * Groups are numbered as powers of two, so that they may be masked together
 * to form a bitmap. This bitmap is used as a look-up table to easily identify
 * if a character belongs to a group or not.
 */
static unsigned long
group_number(struct lexer_parse_tree *top_level, struct group *g)
{
	struct group *p;
	unsigned int i;

	assert(g != NULL);

	i = 0;
	for (p = tree_get_grouplist(top_level); p != NULL; p = p->next) {
		if (g == p) {
			return 1 << i;
		}

		if (!is_group_empty(p)) {
			i++;
		}
	}

	assert(!"Unrecognised group");
	return 0;
}

static unsigned int
count_nonempty_groups(struct lexer_parse_tree *top_level)
{
	struct group *p;
	unsigned int i;

	assert(top_level != NULL);

	i = 0;
	for (p = tree_get_grouplist(top_level); p != NULL; p = p->next) {
		if (!is_group_empty(p)) {
			i++;
		}
	}

	return i;
}

/*
 * OUTPUT THE MACROS NEEDED TO ACCESS THE LOOKUP TABLE
 */
static void
output_macros_zone(struct options *opt, struct zone *z)
{
	struct group_name *gn;
	struct zone *p;

	/* Group interface */
	for (p = z; p != NULL; p = p->opt) {
		for (gn = p->groups; gn != NULL; gn = gn->next) {
			unsigned long m;

			if (is_group_empty(gn->g)) {
				m = 0;
			} else {
				m = group_number(z->top_level, gn->g);
			}

			fputc('\t', lex_output_h);
			output_groupname(lex_output_h, gn);
			fprintf(lex_output_h, " = %#lx", m);

			if (gn->next || z->next || z->opt) {
				fputs(",", lex_output_h);
			}

			fputs("\n", lex_output_h);
		}

		if(z->next) {
			output_macros_zone(opt, z->next);
		}
	}

}

static void
output_macros(struct options* opt, struct lexer_parse_tree *top_level)
{

	if (all_groups_empty(top_level)) {
		return;
	}

	fprintf(lex_output_h, "enum %sgroups {\n", opt->lexi_prefix);
	output_macros_zone(opt, tree_get_globalzone(top_level));

	fputs("};\n", lex_output_h);

	fputs("\n/* true if the given character is present in the given group */\n",
		lex_output_h);
	fprintf(lex_output_h, "%s %sgroup(enum %sgroups group, int c);\n",
		language == C90 ? "int" : "bool", opt->lexi_prefix, opt->lexi_prefix);

	/*
	 * I'm presenting an int here for multibyte character literals, although
	 * the lookup-table behind them is not that wide. Furthermore, it helps set
	 * my mind at ease for lexers generated on machines with different signedness
	 * for char than the machine upon which the generated lexer is compiled.
	 */
	fprintf(lex_output, "%s %sgroup(enum %sgroups group, int c) {\n",
		language == C90 ? "int" : "bool", opt->lexi_prefix, opt->lexi_prefix);
	fputs("\tif (c == LEXI_EOF) {\n", lex_output);
	fputs("\t\treturn 0;\n", lex_output);
	fputs("\t}\n", lex_output);
	fputs("\treturn lookup_tab[c] & group;\n", lex_output);
	fputs("}\n", lex_output);
}

/*
 * OUTPUT THE LOOKUP TABLE
 */
static void
output_lookup_table(struct lexer_parse_tree *top_level, const char *grouptype,
	const char *grouphex, size_t groupwidth)
{
	struct group *g;
	int c;

	if (all_groups_empty(top_level)) {
		return;
	}

	/* Character look-up table */
	fputs("/* LOOKUP TABLE */\n\n", lex_output);
	fprintf(lex_output, "typedef %s lookup_type;\n", grouptype);
	fputs("static lookup_type lookup_tab[] = {\n", lex_output);

	for (c = 0; c <= 255; c++) {
		unsigned long m;

		m = 0;
		for (g = tree_get_grouplist(top_level); g != NULL; g = g->next) {
			if (in_group(g, c)) {
				m |= group_number(top_level, g);
			}
		}

		if (c % groupwidth == 0) {
			fputc('\t', lex_output);
		}

		fprintf(lex_output, grouphex, m);

		if (c < 255) {
			fputs(", ", lex_output);
		}
		if ((c % groupwidth) == groupwidth - 1) {
			fputc('\n', lex_output);
		}
	}

	fputs("\n};",lex_output);
}

/*
 * OUTPUT LEXI AUTOMATED DEFINED OPERATIONS 
 */
static void
output_buffer(struct options *opt, struct lexer_parse_tree *top_level)
{
	/*
	 * Strictly the state argument is not required in the case of a
	 * lookahead of one character, since the token buffer does not exist.
	 * However, we pass it regardless, for simplicity.
	 */
	fputs("/* Read a character */\n", lex_output_h);
	fprintf(lex_output_h, "int %sreadchar(struct %sstate *state);\n\n",
		lexi_prefix, lexi_prefix);
	fprintf(lex_output,"int %sreadchar(struct %sstate *state) {\n",
		lexi_prefix, lexi_prefix);

	if (buffer_length(top_level) > 0) {
		fputs("\tif (state->buffer_index) {\n", lex_output);
		fprintf(lex_output,"\t\treturn %spop(state);\n", lexi_prefix);
		fputs("\t}\n\n", lex_output);
	}

	/* TODO pass opaque here */
	fprintf(lex_output, "\treturn %sgetchar(state);\n", opt->interface_prefix);
	fputs("}\n", lex_output);

	if (buffer_length(top_level) == 0) {
		return;
	}

	/* Other buffer operations */
	fputs("/* Push a character to lexi's buffer */\n", lex_output_h);
	fprintf(lex_output_h, "void %spush(struct %sstate *state, const int c);\n\n",
		lexi_prefix, lexi_prefix);
	fprintf(lex_output, "void %spush(struct %sstate *state, const int c) {\n",
		lexi_prefix, lexi_prefix);
	if (opt->generate_asserts) {
		fputs("\tassert(state);\n", lex_output);
		fputs("\tassert((size_t) state->buffer_index < sizeof state->buffer / sizeof *state->buffer);\n", lex_output);
	}
	fputs("\tstate->buffer[state->buffer_index++] = c;\n", lex_output);
	fputs("}\n\n", lex_output);

	fputs("/* Pop a character from lexi's buffer */\n", lex_output_h);
	fprintf(lex_output_h, "int %spop(struct %sstate *state);\n\n",
		lexi_prefix, lexi_prefix);
	fprintf(lex_output, "int %spop(struct %sstate *state) {\n",
		lexi_prefix, lexi_prefix);
	if (opt->generate_asserts) {
		fputs("\tassert(state);\n", lex_output);
		fputs("\tassert(state->buffer_index > 0);\n", lex_output);
	}
	fputs("\treturn state->buffer[--state->buffer_index];\n", lex_output);
	fputs("}\n\n", lex_output);

	fputs("/* Flush lexi's buffer */\n", lex_output_h);
	fprintf(lex_output_h, "void %sflush(struct %sstate *state);\n\n",
		lexi_prefix, lexi_prefix);
	fprintf(lex_output, "void %sflush(struct %sstate *state) {\n",
		lexi_prefix, lexi_prefix);
	fputs("\tstate->buffer_index = 0;\n", lex_output);
	fputs("}\n\n", lex_output);
}

static void
output_buffer_storage(struct lexer_parse_tree *top_level)
{
	if (buffer_length(top_level) == 0) {
		return;
	}

	/* Buffer storage */
	fputs("\n", lex_output_h);
	fputs("\t/*\n", lex_output_h);
	fputs("\t * Lexi's buffer is a simple stack.\n", lex_output_h);
	fputs("\t */\n", lex_output_h);
	fprintf(lex_output_h, "\tint buffer[%u];\n", buffer_length(top_level));
	fputs("\tint buffer_index;\n", lex_output_h);
}

void
output_headers(void)
{
	ccode_output(lex_output_h, &global_lct_parse_tree.hfileheader, NULL, 0);
	ccode_output(lex_output,   &global_lct_parse_tree.cfileheader, NULL, 0);
}

void
output_trailers(void)
{
	ccode_output(lex_output_h, &global_lct_parse_tree.hfiletrailer, NULL, 0);
	ccode_output(lex_output,   &global_lct_parse_tree.cfiletrailer, NULL, 0);
}

void
c_output_all(struct options *opt, struct lexer_parse_tree *top_level)
{
	size_t groupwidth;
	const char *grouptype;
	const char *grouphex;
	struct lxi_additional_argument* add_arg;

	assert(!strcmp(opt->language, "C90") || !strcmp(opt->language, "C99"));
	language = !strcmp(opt->language, "C90") ? C90 : C99;

	lex_output = opt->output[0].file;
	lex_output_h = opt->output[1].file;

	read_token_name = xstrcat(opt->lexi_prefix, "read_token");
	lexi_prefix = opt->lexi_prefix;

	/*
	 * Here we ouput exact-width types from stdint.h for C99, and appropiate
	 * types based on their respective minimum maxiums otherwise. These types
	 * may be larger than required on some systems, but that's ok.
	 */
	/* TODO: we can tidy up widths a little for narrow hex widths */
	{
		unsigned int t;

		t = count_nonempty_groups(top_level);

		if (t >= 32) {
			error(ERROR_FATAL, "Too many non-empty groups defined (%u)", t);
		} else if (t > 16) {
			grouptype = language == C99 ? "uint32_t" : "unsigned long";
			grouphex = "%# 8lxUL";
			groupwidth = 6;
		} else if (t > 8) {
			grouptype = language == C99 ? "uint16_t" : "unsigned short";
			grouphex = "%# 4lx";
			groupwidth = 12;
		} else {
			grouptype = language == C99 ? "uint8_t" : "unsigned char";
			grouphex = "%# 4lx";
			groupwidth = 12;
		}
	}

	output_generated_by_lexi(OUTPUT_COMMENT_C90, lex_output);

	output_generated_by_lexi(OUTPUT_COMMENT_C90, lex_output_h);
	fprintf(lex_output_h, "#ifndef LEXI_GENERATED_HEADER_%s_INCLUDED\n", lexi_prefix);
	fprintf(lex_output_h, "#define LEXI_GENERATED_HEADER_%s_INCLUDED\n", lexi_prefix);
	fputs("\n", lex_output_h);

	if (opt->output[1].name && (opt->output[1].file!=stdout)) {
		char *s;

		/* XXX: This assumes both files are in the same directory */
		s = xstrdup(opt->output[1].name);
		fprintf(lex_output, "#include \"%s\"\n\n", basename(s));
		free(s);
	}

	output_headers();

	if (opt->generate_asserts) {
		fputs("#include <assert.h>\n", lex_output);
	}
	if (language == C99) {
		fputs("#include <stdbool.h>\n", lex_output);
		fputs("#include <stdint.h>\n\n", lex_output);

		fputs("#include <stdbool.h>\n\n", lex_output_h);
	}

	fputs(
		"/*\n"
		" * This struct holds state for the lexer; its representation is\n"
		" * private, but present here for ease of allocation.\n"
		" */\n", lex_output_h);
	fprintf(lex_output_h, "struct %sstate {\n"
	      "\tint (*zone)(struct %sstate *);\n",
		opt->lexi_prefix, opt->lexi_prefix);
	output_buffer_storage(top_level);

	for(add_arg = global_lct_parse_tree.arg_head; add_arg != NULL; add_arg = add_arg->next) {
		fprintf(lex_output_h, "\t%s %s;\n", add_arg->ctype, add_arg->name);
	}
	fputs("};\n\n", lex_output_h);

	output_buffer(opt, top_level);
	fputs("\n", lex_output);

	output_lookup_table(top_level,grouptype,grouphex,groupwidth);
	fputs("\n\n", lex_output);

	fputs("#ifndef LEXI_EOF\n", lex_output_h);
	fprintf(lex_output_h, "#define LEXI_EOF %d\n", EOF); /* TODO: remove LEXI_EOF */
	fputs("#endif\n\n", lex_output_h);

	output_macros(opt,top_level);
	fputs("\n\n", lex_output);

	/* Keywords */
	output_keywords(top_level, lex_output, lex_output_h);

	/* Lexical pre-pass */
	fputs("/* PRE-PASS ANALYSERS */\n\n", lex_output);
	output_zone_prepass(tree_get_globalzone(top_level));

	/* Main pass */
	fputs("\n/* Identify a token */\n", lex_output_h);
	fprintf(lex_output_h, "int %s(struct %sstate *state);\n\n",
		read_token_name, lexi_prefix);

	/* lexi_init() */
	/* TODO assert() state */
	fprintf(lex_output_h, "/* Initialise a %sstate structure */\n",
		opt->lexi_prefix);
	fprintf(lex_output_h, "void %sinit(struct %sstate *state",
		opt->lexi_prefix, opt->lexi_prefix);
	fprintf(lex_output,"void %sinit(struct %sstate *state",
		opt->lexi_prefix, opt->lexi_prefix);

	for(add_arg = global_lct_parse_tree.arg_head; add_arg != NULL; add_arg = add_arg->next) {
		fprintf(lex_output_h, ", %s %s", add_arg->ctype, add_arg->name);
		fprintf(lex_output, ", %s %s", add_arg->ctype, add_arg->name);
	}
	fputs(");\n\n",lex_output_h);
	fprintf(lex_output, ") {\n\tstate->zone = %s;\n", read_token_name);

	if (buffer_length(top_level) > 0) {
		fprintf(lex_output, "\tstate->buffer_index = 0;\n");
	}
	for(add_arg = global_lct_parse_tree.arg_head; add_arg != NULL; add_arg = add_arg->next) {
		fprintf(lex_output, "\tstate->%s = %s;\n", add_arg->name, add_arg->name);
	}
	fprintf(lex_output, "}\n");

	fputs("/* ZONES PASS ANALYSER PROTOTYPES*/\n\n", lex_output);
	output_zone_pass_prototypes(tree_get_globalzone(top_level));

	fputs("/* MAIN PASS ANALYSERS */\n\n", lex_output);
  	output_zone_pass(opt, tree_get_globalzone(top_level));

	output_trailers();

	fputs("#endif\n", lex_output_h);

	fputs("\n", lex_output);
	fputs("\n", lex_output_h);
}

