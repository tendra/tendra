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
#include <adt/type.h>
#include <adt/zone.h>
#include <adt/group.h>
#include <adt/localnames.h>
#include <adt/nametrans.h>

#include <out/c.h>
#include <out/common.h>

#include "ast.h"
#include "lexer.h"
#include "lctsyntax.h"
#include "options.h"

static int out_cmds(struct zone *parent, struct cmd_list *ret, unsigned int n, unsigned int d);
static void out_pass(struct zone* z, struct character *p, int in_pre_pass, unsigned int n, unsigned int d);

/*
 * This is populated by the selected output language, set from opt->lang.
 * It may be inspected for language-specific regions of the generated code.
 */
enum {
	C90,
	C99
} lang;

/*
 * OUTPUT OPTIONS
 *
 * The flag in_pre_pass is used to indicate the preliminary pass to
 * out_pass.  read_name gives the name of the character reading
 * function used in the output routines.
 */
static const char *read_token_name;
static const char *lexi_prefix;

/*
 * OUTPUT FILE
 *
 * These variables gives the output files. out is used within this file
 * as a shorthand for lex_out. Likewise lex_out_h is a convenience
 * for the output header.
 *
 * These correspond to options.out[0].file and [1] respectively.
 */
FILE *lex_out;
FILE *lex_out_h;


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
buffer_length(struct ast *ast)
{
	unsigned int i;
	struct zone *global;

	/* XXX: account for is_beginendmarker_in_zone */
	global = tree_get_globalzone(ast);
	assert(global != NULL);

	i = zone_maxlength(global, 0);
	if (global->pre) {
		i += zone_maxlength(global, 1);
	}

	return i;
}

static void
out_groupname(FILE *f, struct group_name *gn)
{
	const char *prefix;

	assert(f != NULL);
	assert(gn != NULL);

	prefix = zone_isglobal(gn->z) ? "group" : gn->z->name;

	fprintf(f, "%s%s_%s", lexi_prefix, prefix, gn->name);
}

static void
out_keyword(struct keyword *keyword, void *opaque)
{
	FILE *out = opaque;

	fprintf(out, "\tif (");

	fprintf(out, "0 == strcmp(identifier, \"%s\")) return ", keyword_name(keyword));

	switch (keyword_cmd(keyword)->type) {
	case return_terminal:
		fprintf(out, "%s", keyword_cmd(keyword)->u.name);
		break;

	default:
		assert(!"unrecognised command type for keyword");
	}

	fprintf(out, ";\n");
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
out_keywords(struct ast *ast, FILE *out, FILE *out_h)
{
	assert(ast != NULL);
	assert(out != NULL);
	assert(out_h != NULL);

	if (tree_get_globalzone(ast)->keywords == NULL) {
		return;
	}

	fputs("\n/* Identify a keyword */\n", out_h);
	fprintf(out_h, "int %skeyword(const char *identifier, int notfound);\n",
		lexi_prefix);

	fprintf(out, "#include <string.h>\n");
	fprintf(out, "int %skeyword(const char *identifier, int notfound) {\n",
		lexi_prefix);

	keywords_iterate(tree_get_globalzone(ast)->keywords, out_keyword, out);

	fprintf(out, "\treturn notfound;\n}\n");
}

static void
out_locals(struct LocalNamesT *locals, unsigned int d, FILE *lex_out)
{
	struct LocalNamesIteratorT it;
	const char *prefixvar = "ZV";
	const char *prefixtype = "ZT";
	char *st;
	char *s;

	assert(locals != NULL);
	assert(lex_out != NULL);

	s = xmalloc_nof(char, locals->max_depth + 1);

	for (localnames_begin(&it, locals); it.p; localnamesiterator_next(&it)) {
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

		out_indent(lex_out, d);
		fprintf(lex_out,"%s%s %s%s;\n", prefixtype, st, prefixvar, s);

		xfree(st);
	}

	xfree(s);
}

static void
out_action(FILE *lex_out, struct ast *ast,
	struct entry *ea, struct args_list *lhs, struct args_list *rhs, unsigned int d)
{
	struct NameTransT trans;

	assert(lex_out != NULL);
	assert(ast != NULL);
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
	out_indent(lex_out, d);
	fprintf(lex_out, "/* ACTION <%s> */\n", nstring_to_cstring(entry_key(ea)));

	out_indent(lex_out, d);
	fprintf(lex_out, "{\n");

	d++;

	if (lhs->nb_return) {
		char *prefixtype = "ZT";
		struct entry *et;
		char *st;

		et = lexer_terminal_type(ast);
		/* TODO assert(entry_is_type(t)); */

		if (et->u.type->mapped) {
			prefixtype="";
			st = nstring_to_cstring(&et->u.type->mapping);
		} else {
			st = nstring_to_cstring(entry_key(et));
		}

		out_indent(lex_out, d);
		fprintf(lex_out,"%s%s ZT1;\n", prefixtype, st);
	}

	/* End Semi Inefficient */

	if (action_is_defined(ea->u.act)) {
		ccode_out(lex_out, &ea->u.act->code, &trans, d );
		if (lhs->nb_return) {
			/*TODO assert(lhs->nb_return==1)*/
			out_indent(lex_out, d);
			fputs("return ZT1;\n",lex_out);
		}
	} else {
		/*TODO We should catch this error before beginning output */
		char* pe=nstring_to_cstring(entry_key(ea));
		error(ERROR_SERIOUS, "Action %s is used but undefined", pe);
		xfree(pe);
	}

	d--;

	out_indent(lex_out, d);
	fprintf(lex_out, "}\n");

	out_indent(lex_out, d);
	fprintf(lex_out, "/* END ACTION <%s> */\n", nstring_to_cstring(entry_key(ea)));
}


static void
out_pushzone(struct zone *parent, struct cmd *cmd, unsigned int n, unsigned int d)
{
	assert(parent != NULL);
	assert(cmd != NULL);
	assert(cmd->type == push_zone);

	if (cmd->u.s.z->type == typezone_general_zone) {
		out_indent(lex_out, d);
		fprintf(lex_out, "state->zone = %s_%s;\n",
			read_token_name, cmd->u.s.z->name);
	}

	if (cmd->u.s.z->enter->head != NULL) {
		out_cmds(parent, cmd->u.s.z->enter, n, d);
	}

	if (cmd->u.s.z->enter->nb_return != 0) {
		return;
	}

	out_indent(lex_out, d);
	switch (cmd->u.s.z->type) {
	case typezone_general_zone:
		fprintf(lex_out, "return %s(state);\n", read_token_name);
		break;

	case typezone_pseudo_token:
		fprintf(lex_out, "return %s_%s(state);\n", read_token_name, cmd->u.s.z->name);
		break;

	case typezone_pure_function:
		fprintf(lex_out, "%s_%s(state);\n", read_token_name, cmd->u.s.z->name);
		out_indent(lex_out, d);
		fputs("goto start;	/* pure function */\n", lex_out);
		break;
	}
}

static void
out_popzone(struct zone *parent, struct cmd *cmd, unsigned int n, unsigned int d)
{
	assert(parent != NULL);
	assert(cmd != NULL);
	assert(cmd ->type == pop_zone);

	if (parent->type == typezone_general_zone) {
		out_indent(lex_out, d);
		if (zone_isglobal(cmd->u.s.z)) {
			fprintf(lex_out, "state->zone = %s;\n", read_token_name);
		} else {
			fprintf(lex_out, "state->zone = %s_%s;\n", read_token_name,
				cmd->u.s.z->name);
		}
	}

	if (!cmd->u.s.is_beginendmarker_in_zone) {
		unsigned int i;

		for (i = n + 1; i > 0; i--) {
			out_indent(lex_out, d);
			fprintf(lex_out, "%spush(state, c%u);\n", lexi_prefix, i - 1);
		}
	}

	if (parent->exit->head) {
		out_cmds(parent, parent->exit, n, d);
	}

	if (parent->exit->nb_return != 0) {
		return;
	}

	out_indent(lex_out, d);
	switch (parent->type) {
	case typezone_general_zone:
		fprintf(lex_out, "return %s(state);\n", read_token_name);
		break;

	case typezone_pure_function:
		fputs("return;\n", lex_out);
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
out_cmds(struct zone *parent, struct cmd_list *ret, unsigned int n, unsigned int d)
{
	struct cmd *cmd;
	struct LocalNamesT *locals;
	int r;

	assert(parent != NULL);
	assert(ret != NULL);

	locals = cmdlist_localnames(ret);
	if (locals->top) {
		out_indent(lex_out, d);
		fputs("{\n", lex_out);
		++d;
		out_locals(locals, d, lex_out);
	}

	r = 0;
	for (cmd = ret->head; cmd != NULL; cmd = cmd->next) {
		/* TODO: can simplify the calls to out_pushzone() et al by passing only what we need, not the entire cmd */
		switch (cmd->type) {
		case return_terminal:
			r = 1;
			assert(cmd->next == NULL);
			out_indent(lex_out, d);
			fprintf(lex_out, "return %s;\n", cmd->u.name);
			break;

		case action_call:
			out_action(lex_out, parent->ast, cmd->u.act.called_act, cmd->u.act.lhs, cmd->u.act.rhs, d);
			break;

		case push_zone:
			r = 1;
			out_pushzone(parent, cmd, n, d);
			break;

		case pop_zone:
			r = 1;
			out_popzone(parent, cmd, n, d);
			break;

		case do_nothing:
			assert(cmd->next == NULL); /* caught during parsing */
			break;
		}
	}

	if (locals->top) {
		d--;
		out_indent(lex_out, d);
		fputs("}\n", lex_out);
	}

	return r;
}

static void
out_mapping(const char *map, unsigned int d)
{
	const char *str;
	char m;

	assert(map != NULL);

	if (strlen(map) == 0) {
		out_indent(lex_out, d);
		fputs("goto start;\n", lex_out);
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

	out_indent(lex_out, d);
	fprintf(lex_out, "c0 = %s;\n", str);

	out_indent(lex_out, d);
	fputs("goto restart;\n", lex_out);
}

/*
 * Returns true if a return was made; false indicates that control is still
 * present in the containing block.
 */
static int
out_leaf(struct zone *parent, struct character *p, int in_pre_pass, unsigned int n, unsigned int d)
{
	assert(parent != NULL);
	assert(p != NULL);

	/* TODO: could avoid passing in_pre_pass around by finding it on the fly */
	/* TODO: this can be reworked. also see u.map simplification for adt/char.h */
	if (in_pre_pass) {
		if (p->u.map != NULL) {
			out_mapping(p->u.map, d);
		}

		return 1;
	}

	if (p->u.cmds != NULL) {
		if (!out_cmds(parent, p->u.cmds, n, d)) {
			out_indent(lex_out, d);
			fprintf(lex_out, "goto start; /* leaf */\n");
		}

		return 1;
	}

	return 0;
}

static void
out_char_letters(struct zone *z, struct character *p, int in_pre_pass, unsigned int n, unsigned int d)
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

		out_indent(lex_out, d);
		fprintf(lex_out, "if (c%u == %s) {\n", n, char_lit(q->v.c));

		if (q->next != NULL) {
			out_pass(z, q->next, in_pre_pass, n + 1, d + 1);
		}
		out_leaf(z, q, in_pre_pass, n, d + 1);

		out_indent(lex_out, d);
		fputs("}\n", lex_out);

		return;

	default:
		out_indent(lex_out, d);
		fprintf(lex_out, "switch (c%u) {\n", n);
		for (q = p; q != NULL; q = q->opt) {
			int r;

			if (q->type != char_letter) {
				continue;
			}

			out_indent(lex_out, d);
			fprintf(lex_out, "case %s: {\n", char_lit(q->v.c));
			d++;

			if (q->next != NULL) {
				out_pass(z, q->next, in_pre_pass, n + 1, d + 1);
			}
			r = out_leaf(z, q, in_pre_pass, n, d + 1);

			out_indent(lex_out, d);
			fputs("}\n", lex_out);

			if (!r) {
				out_indent(lex_out, d);
				fputs("break;\n", lex_out);
			}

			fputs("\n", lex_out);

			d--;
		}
		out_indent(lex_out, d);
		fputs("}\n", lex_out);

		return;
	}
}

static void
out_char_groups(struct zone *z, struct character *p, int in_pre_pass, unsigned int n, unsigned int d)
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
		out_indent(lex_out, d);

		if (started) {
			fputs("} else ", lex_out);
		}

		fprintf(lex_out, "if (%s%sgroup(", q->v.g.not ? "!" : "", lexi_prefix);
		out_groupname(lex_out, gn);
		fprintf(lex_out, ", c%u)) {\n", n);

		if (q->next != NULL) {
			out_pass(z, q->next, in_pre_pass, n + 1, d + 1);
		}

		out_leaf(z, q, in_pre_pass, n, d + 1);

		started = 1;
	}

	out_indent(lex_out, d);
	fputs("}\n", lex_out);
}

/*
 * OUTPUT PASS INFORMATION
 *
 * This routine outputs code for the lexical pass indicated by p.
 * n gives the depth of recursion and d gives the indentation.
*/
static void
out_pass(struct zone *z, struct character *p, int in_pre_pass, unsigned int n, unsigned int d)
{
	int w1 = n == 0 && !in_pre_pass;
	int w2 = n == 0 && in_pre_pass;

	assert(z != NULL);
	assert(p != NULL);

	out_indent(lex_out, d);
	if (!in_pre_pass && z->pre) {
		if (zone_isglobal(z)) {
			fprintf(lex_out, "int c%u = %s_aux(state)",
				n, read_token_name);
		} else {
			fprintf(lex_out, "int c%u = %s_%s_aux(state)",
				n, read_token_name, z->name);
		}
	} else {
		fprintf(lex_out, "int c%u = %sreadchar(state)", n, lexi_prefix);
	}
	fputs(";\n", lex_out);

	/* TODO: can we move out w1 and w2 into out_zone_*pass(), and keep the recursion simple? */
	if (w1) {
		struct group_name *white;

		white = find_group(z, "white");
		if (white != NULL && !is_group_empty(white->g)) {
			out_indent(lex_out, d);
			fprintf(lex_out, "if (%sgroup(", lexi_prefix);
			out_groupname(lex_out, white);
			fprintf(lex_out, ", c0)) goto start;\n");
		}
	}
	if (w2) {
		out_indent(lex_out, d);
		fputs("restart: {\n", lex_out);
		d++;
	}

	/* We match letters before groups; letters have priority (TODO do we need to?) */
	out_char_letters(z, p, in_pre_pass, n, d);
	out_char_groups (z, p, in_pre_pass, n, d);

	if (w2) {
		d--;
		out_indent(lex_out, d);
		fputs("}\n", lex_out);
	}

	if (n) {
		out_indent(lex_out, d);
		fprintf(lex_out, "%spush(state, c%u);\n", lexi_prefix,n);
	}
}

static void
out_zone_pass_prototypes(struct zone *p)
{
	struct zone *z;
	const char *s;

	assert(p != NULL);

	for (z = p->next; z != NULL; z = z->opt) {
		out_zone_pass_prototypes(z);
	}

	s = p->type == typezone_pure_function ? "void" : "int";

	if (p == tree_get_globalzone(p->ast)) {
		return;
	}

	fprintf(lex_out,"static %s %s_%s(struct %sstate *state);\n", s,
		read_token_name, p->name, lexi_prefix);
}

static void
out_zone_prepass(struct zone *z)
{
	assert(z != NULL);

	/* recurr through all zones */
	{
		struct zone *p;

		for (p = z->next; p != NULL; p = p->opt) {
			out_zone_prepass(p);
		}
	}

	if (z->pre == NULL) {
		return;
	}

	fprintf(lex_out, "/* PRE PASS ANALYSER for %s*/\n\n", zone_name(z));
	if (zone_isglobal(z)) {
		fprintf(lex_out, "static int %s_aux(struct %sstate *state)\n",
			read_token_name, lexi_prefix);
	} else {
		fprintf(lex_out, "static int %s_%s_aux(struct %sstate *state)\n",
			read_token_name, z->name, lexi_prefix);
	}
	fputs("{\n", lex_out);
	fputs("\tstart: {\n", lex_out);

	out_pass(z, z->pre, 1, 0, 2);
	out_leaf(z, z->pre, 1, 0, 2);

	fputs("\treturn c0;\n", lex_out);
	fputs("\t}\n", lex_out);
	fputs("}\n\n\n", lex_out);

	return;
}

static void
out_zone_pass(struct options *opt, struct zone *p)
{
	/* recurr through all zones */
	{
		struct zone *z;

		for (z = p->next; z != NULL; z = z->opt) {
			out_zone_pass(opt, z);
		}
	}

	fprintf(lex_out, "\n/* MAIN PASS ANALYSER for %s */\n", zone_name(p));
	if (zone_isglobal(p)) {
		fprintf(lex_out,"int\n%s(struct %sstate *state)\n",
			read_token_name, lexi_prefix);
		fputs("{\n", lex_out);
		if (tree_get_globalzone(p->ast)->next != NULL) {
			fprintf(lex_out, "\tif (state->zone != %s)\n", read_token_name);
			fprintf(lex_out, "\t\treturn state->zone(state);\n");
		}
	} else {
		const char *s;

		s = p->type == typezone_pure_function ? "void" : "int";

		fprintf(lex_out, "static %s\n%s_%s(struct %sstate *state)\n", s,
		read_token_name, p->name, lexi_prefix);
		fputs("{\n", lex_out);
	}

	fputs("\tstart: {\n", lex_out);

	/* main pass */
	if (p->main != NULL) {
		out_pass(p, p->main, 0, 0, 2);
	}

	/* TOKEN DEFAULT -> ...; */
	fprintf(lex_out, "\n\t\t/* DEFAULT */\n");
	if (p->local != NULL) {
		if (!out_cmds(p, p->local, 1, 2)) {
			out_indent(lex_out, 2);
			fprintf(lex_out, "goto start; /* DEFAULT */\n");
		}
	} else {
		fprintf(lex_out, "\t\treturn %sunknown_token;\n",
			opt->interface_prefix);
	}

	fputs("\t}\n", lex_out);
	fputs("}\n", lex_out);

	return;
}

/*
 * Groups are numbered as powers of two, so that they may be masked together
 * to form a bitmap. This bitmap is used as a look-up table to easily identify
 * if a character belongs to a group or not.
 */
static unsigned long
group_number(struct ast *ast, struct group *g)
{
	struct group *p;
	unsigned int i;

	assert(g != NULL);

	i = 0;
	for (p = tree_get_grouplist(ast); p != NULL; p = p->next) {
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
count_nonempty_groups(struct ast *ast)
{
	struct group *p;
	unsigned int i;

	assert(ast != NULL);

	i = 0;
	for (p = tree_get_grouplist(ast); p != NULL; p = p->next) {
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
out_macros_zone(struct options *opt, struct zone *z)
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
				m = group_number(z->ast, gn->g);
			}

			fputc('\t', lex_out_h);
			out_groupname(lex_out_h, gn);
			fprintf(lex_out_h, " = %#lx", m);

			if (gn->next || z->next || z->opt) {
				fputs(",", lex_out_h);
			}

			fputs("\n", lex_out_h);
		}

		if(z->next) {
			out_macros_zone(opt, z->next);
		}
	}

}

static void
out_macros(struct options* opt, struct ast *ast)
{

	if (all_groups_empty(ast)) {
		return;
	}

	fprintf(lex_out_h, "enum %sgroups {\n", opt->lexi_prefix);
	out_macros_zone(opt, tree_get_globalzone(ast));

	fputs("};\n", lex_out_h);

	fputs("\n/* true if the given character is present in the given group */\n",
		lex_out_h);
	fprintf(lex_out_h, "%s %sgroup(enum %sgroups group, int c);\n",
		lang == C90 ? "int" : "bool", opt->lexi_prefix, opt->lexi_prefix);

	/*
	 * I'm presenting an int here for multibyte character literals, although
	 * the lookup-table behind them is not that wide. Furthermore, it helps set
	 * my mind at ease for lexers generated on machines with different signedness
	 * for char than the machine upon which the generated lexer is compiled.
	 */
	fprintf(lex_out, "%s %sgroup(enum %sgroups group, int c) {\n",
		lang == C90 ? "int" : "bool", opt->lexi_prefix, opt->lexi_prefix);
	fputs("\tif (c == LEXI_EOF) {\n", lex_out);
	fputs("\t\treturn 0;\n", lex_out);
	fputs("\t}\n", lex_out);
	fputs("\treturn lookup_tab[c] & group;\n", lex_out);
	fputs("}\n", lex_out);
}

/*
 * OUTPUT THE LOOKUP TABLE
 */
static void
out_lookup_table(struct ast *ast, const char *grouptype,
	const char *grouphex, size_t groupwidth)
{
	struct group *g;
	int c;

	if (all_groups_empty(ast)) {
		return;
	}

	/* Character look-up table */
	fputs("/* LOOKUP TABLE */\n\n", lex_out);
	fprintf(lex_out, "typedef %s lookup_type;\n", grouptype);
	fputs("static lookup_type lookup_tab[] = {\n", lex_out);

	for (c = 0; c <= 255; c++) {
		unsigned long m;

		m = 0;
		for (g = tree_get_grouplist(ast); g != NULL; g = g->next) {
			if (in_group(g, c)) {
				m |= group_number(ast, g);
			}
		}

		if (c % groupwidth == 0) {
			fputc('\t', lex_out);
		}

		fprintf(lex_out, grouphex, m);

		if (c < 255) {
			fputs(", ", lex_out);
		}
		if ((c % groupwidth) == groupwidth - 1) {
			fputc('\n', lex_out);
		}
	}

	fputs("\n};",lex_out);
}

/*
 * OUTPUT LEXI AUTOMATED DEFINED OPERATIONS 
 */
static void
out_buffer(struct options *opt, struct ast *ast)
{
	/*
	 * Strictly the state argument is not required in the case of a
	 * lookahead of one character, since the token buffer does not exist.
	 * However, we pass it regardless, for simplicity.
	 */
	fputs("/* Read a character */\n", lex_out_h);
	fprintf(lex_out_h, "int %sreadchar(struct %sstate *state);\n\n",
		lexi_prefix, lexi_prefix);
	fprintf(lex_out,"int %sreadchar(struct %sstate *state) {\n",
		lexi_prefix, lexi_prefix);

	if (buffer_length(ast) > 0) {
		fputs("\tif (state->buffer_index) {\n", lex_out);
		fprintf(lex_out,"\t\treturn %spop(state);\n", lexi_prefix);
		fputs("\t}\n\n", lex_out);
	}

	/* TODO pass opaque here */
	fprintf(lex_out, "\treturn %sgetchar(state);\n", opt->interface_prefix);
	fputs("}\n", lex_out);

	if (buffer_length(ast) == 0) {
		return;
	}

	/* Other buffer operations */
	fputs("/* Push a character to lexi's buffer */\n", lex_out_h);
	fprintf(lex_out_h, "void %spush(struct %sstate *state, const int c);\n\n",
		lexi_prefix, lexi_prefix);
	fprintf(lex_out, "void %spush(struct %sstate *state, const int c) {\n",
		lexi_prefix, lexi_prefix);
	if (opt->generate_asserts) {
		fputs("\tassert(state);\n", lex_out);
		fputs("\tassert((size_t) state->buffer_index < sizeof state->buffer / sizeof *state->buffer);\n", lex_out);
	}
	fputs("\tstate->buffer[state->buffer_index++] = c;\n", lex_out);
	fputs("}\n\n", lex_out);

	fputs("/* Pop a character from lexi's buffer */\n", lex_out_h);
	fprintf(lex_out_h, "int %spop(struct %sstate *state);\n\n",
		lexi_prefix, lexi_prefix);
	fprintf(lex_out, "int %spop(struct %sstate *state) {\n",
		lexi_prefix, lexi_prefix);
	if (opt->generate_asserts) {
		fputs("\tassert(state);\n", lex_out);
		fputs("\tassert(state->buffer_index > 0);\n", lex_out);
	}
	fputs("\treturn state->buffer[--state->buffer_index];\n", lex_out);
	fputs("}\n\n", lex_out);

	fputs("/* Flush lexi's buffer */\n", lex_out_h);
	fprintf(lex_out_h, "void %sflush(struct %sstate *state);\n\n",
		lexi_prefix, lexi_prefix);
	fprintf(lex_out, "void %sflush(struct %sstate *state) {\n",
		lexi_prefix, lexi_prefix);
	fputs("\tstate->buffer_index = 0;\n", lex_out);
	fputs("}\n\n", lex_out);
}

static void
out_buffer_storage(struct ast *ast)
{
	if (buffer_length(ast) == 0) {
		return;
	}

	/* Buffer storage */
	fputs("\n", lex_out_h);
	fputs("\t/*\n", lex_out_h);
	fputs("\t * Lexi's buffer is a simple stack.\n", lex_out_h);
	fputs("\t */\n", lex_out_h);
	fprintf(lex_out_h, "\tint buffer[%u];\n", buffer_length(ast));
	fputs("\tint buffer_index;\n", lex_out_h);
}

void
out_headers(void)
{
	ccode_out(lex_out_h, &lct_ast.hfileheader, NULL, 0);
	ccode_out(lex_out,   &lct_ast.cfileheader, NULL, 0);
}

void
out_trailers(void)
{
	ccode_out(lex_out_h, &lct_ast.hfiletrailer, NULL, 0);
	ccode_out(lex_out,   &lct_ast.cfiletrailer, NULL, 0);
}

void
c_out_all(struct options *opt, struct ast *ast)
{
	size_t groupwidth;
	const char *grouptype;
	const char *grouphex;
	struct lxi_additional_argument* add_arg;

	assert(!strcmp(opt->lang, "C90") || !strcmp(opt->lang, "C99"));
	lang = !strcmp(opt->lang, "C90") ? C90 : C99;

	lex_out   = opt->out[0].file;
	lex_out_h = opt->out[1].file;

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

		t = count_nonempty_groups(ast);

		if (t >= 32) {
			error(ERROR_FATAL, "Too many non-empty groups defined (%u)", t);
		} else if (t > 16) {
			grouptype = lang == C99 ? "uint32_t" : "unsigned long";
			grouphex = "%# 8lxUL";
			groupwidth = 6;
		} else if (t > 8) {
			grouptype = lang == C99 ? "uint16_t" : "unsigned short";
			grouphex = "%# 4lx";
			groupwidth = 12;
		} else {
			grouptype = lang == C99 ? "uint8_t" : "unsigned char";
			grouphex = "%# 4lx";
			groupwidth = 12;
		}
	}

	out_generated_by_lexi(OUT_COMMENT_C90, lex_out);
	out_generated_by_lexi(OUT_COMMENT_C90, lex_out_h);

	fprintf(lex_out_h, "#ifndef LEXI_GENERATED_HEADER_%s_INCLUDED\n", lexi_prefix);
	fprintf(lex_out_h, "#define LEXI_GENERATED_HEADER_%s_INCLUDED\n", lexi_prefix);
	fputs("\n", lex_out_h);

	if (opt->out[1].name && opt->out[1].file != stdout) {
		char *s;

		/* XXX: This assumes both files are in the same directory */
		s = xstrdup(opt->out[1].name);
		fprintf(lex_out, "#include \"%s\"\n\n", basename(s));
		free(s);
	}

	out_headers();

	if (opt->generate_asserts) {
		fputs("#include <assert.h>\n", lex_out);
	}
	if (lang == C99) {
		fputs("#include <stdbool.h>\n", lex_out);
		fputs("#include <stdint.h>\n\n", lex_out);

		fputs("#include <stdbool.h>\n\n", lex_out_h);
	}

	fputs(
		"/*\n"
		" * This struct holds state for the lexer; its representation is\n"
		" * private, but present here for ease of allocation.\n"
		" */\n", lex_out_h);
	fprintf(lex_out_h, "struct %sstate {\n"
	      "\tint (*zone)(struct %sstate *);\n",
		opt->lexi_prefix, opt->lexi_prefix);
	out_buffer_storage(ast);

	for(add_arg = lct_ast.arg_head; add_arg != NULL; add_arg = add_arg->next) {
		fprintf(lex_out_h, "\t%s %s;\n", add_arg->ctype, add_arg->name);
	}
	fputs("};\n\n", lex_out_h);

	out_buffer(opt, ast);
	fputs("\n", lex_out);

	out_lookup_table(ast,grouptype,grouphex,groupwidth);
	fputs("\n\n", lex_out);

	fputs("#ifndef LEXI_EOF\n", lex_out_h);
	fprintf(lex_out_h, "#define LEXI_EOF %d\n", EOF); /* TODO: remove LEXI_EOF */
	fputs("#endif\n\n", lex_out_h);

	out_macros(opt,ast);
	fputs("\n\n", lex_out);

	/* Keywords */
	out_keywords(ast, lex_out, lex_out_h);

	/* Lexical pre-pass */
	fputs("/* PRE-PASS ANALYSERS */\n\n", lex_out);
	out_zone_prepass(tree_get_globalzone(ast));

	/* Main pass */
	fputs("\n/* Identify a token */\n", lex_out_h);
	fprintf(lex_out_h, "int %s(struct %sstate *state);\n\n",
		read_token_name, lexi_prefix);

	/* lexi_init() */
	/* TODO assert() state */
	fprintf(lex_out_h, "/* Initialise a %sstate structure */\n",
		opt->lexi_prefix);
	fprintf(lex_out_h, "void %sinit(struct %sstate *state",
		opt->lexi_prefix, opt->lexi_prefix);
	fprintf(lex_out,"void %sinit(struct %sstate *state",
		opt->lexi_prefix, opt->lexi_prefix);

	for (add_arg = lct_ast.arg_head; add_arg != NULL; add_arg = add_arg->next) {
		fprintf(lex_out_h, ", %s %s", add_arg->ctype, add_arg->name);
		fprintf(lex_out, ", %s %s", add_arg->ctype, add_arg->name);
	}
	fputs(");\n\n",lex_out_h);
	fprintf(lex_out, ") {\n\tstate->zone = %s;\n", read_token_name);

	if (buffer_length(ast) > 0) {
		fprintf(lex_out, "\tstate->buffer_index = 0;\n");
	}
	for (add_arg = lct_ast.arg_head; add_arg != NULL; add_arg = add_arg->next) {
		fprintf(lex_out, "\tstate->%s = %s;\n", add_arg->name, add_arg->name);
	}
	fprintf(lex_out, "}\n");

	fputs("/* ZONES PASS ANALYSER PROTOTYPES*/\n\n", lex_out);
	out_zone_pass_prototypes(tree_get_globalzone(ast));

	fputs("/* MAIN PASS ANALYSERS */\n\n", lex_out);
  	out_zone_pass(opt, tree_get_globalzone(ast));

	out_trailers();

	fputs("#endif\n", lex_out_h);

	fputs("\n", lex_out);
	fputs("\n", lex_out_h);
}

