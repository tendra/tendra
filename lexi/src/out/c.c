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
#include <adt/arg.h>
#include <adt/cmd.h>
#include <adt/keyword.h>
#include <adt/trie.h>
#include <adt/zone.h>
#include <adt/group.h>
#include <adt/localnames.h>

#include <out/c.h>

#include "ast.h"
#include "lexer.h"
#include "lctsyntax.h"
#include "options.h"

static int out_cmds(struct zone *parent, struct cmd_list *ret, unsigned int n, unsigned int d);
static void out_pass(struct zone* z, struct trie *p, int in_pre_pass, unsigned int n, unsigned int d);

/*
 * OUTPUT OPTIONS
 *
 * read_name gives the name of the character reading
 * function used in the output routines.
 */
static const char *read_token_name;
static const char *lexi_prefix;

static void
indent(unsigned int depth)
{
	while (depth-- > 0) {
		fputc('\t', stdout);
	}
}

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

	/* XXX: account for is_beginendmarker_in_zone */
	assert(ast->global != NULL);

	i = zone_maxlength(ast->global, 0);
	if (ast->global->pre) {
		i += zone_maxlength(ast->global, 1);
	}

	return i;
}

static void
out_groupname(struct group_name *gn)
{
	const char *prefix;

	assert(gn != NULL);

	prefix = zone_isglobal(gn->z) ? "group" : gn->z->name;

	printf("%s%s_%s", lexi_prefix, prefix, gn->name);
}

static void
out_keyword(struct keyword *kw, void *opaque)
{
	(void) opaque;

	printf("\tif (0 == strcmp(identifier, \"%s\")) return ", kw->name);

	switch (kw->cmd->kind) {
	case CMD_RETURN:
		printf("%s", kw->cmd->u.name);
		break;

	default:
		assert(!"unrecognised command type for keyword");
	}

	printf(";\n");
}

/*
 * KEYWORDS GENERATION
 *
 * This routine outputs a keyword interface.
 *
 * TODO: at some point (where the code is clearer), this can
 * be rewritten to generate and output a trie in its own right.
 * For the moment, we just need the interface in place to set
 * the generated API.
 */
static void
out_keywords(struct ast *ast)
{
	assert(ast != NULL);

	if (ast->global->keywords == NULL) {
		return;
	}

	printf("int %skeyword(const char *identifier, int notfound) {\n",
		lexi_prefix);

	keywords_iterate(ast->global->keywords, out_keyword, NULL);

	printf("\treturn notfound;\n}\n");
}

static void
out_locals(struct LocalNamesT *locals, unsigned int d)
{
	struct LocalNamesIteratorT it;
	const char *prefixvar  = "ZV";
	const char *prefixtype = "ZT";
	char *st;
	char *s;

	assert(locals != NULL);

	s = xmalloc_nof(char, locals->max_depth + 1);

	for (localnames_begin(&it, locals); it.p; localnamesiterator_next(&it)) {
		struct LocalNamesEntryT *p = it.p;
		int i;

		s[it.depth] = 0;

		for (i = it.depth - 1; i >= 0; i--) {
			/* TODO: assert(p) */
			s[i] = p->c;
			p = p->up;
		}

		/* TODO: assert(p->et->kind == ENTRY_TYPE); */

		st = nstring_to_cstring(&p->et->key);

		indent(d);
		printf("%s%s %s%s;\n", prefixtype, st, prefixvar, s);

		xfree(st);
	}

	xfree(s);
}

static void
out_action(struct ast *ast,
	struct entry *ea, struct args_list *lhs, struct args_list *rhs, unsigned int d)
{
	assert(ast != NULL);
	assert(ea != NULL);
	assert(lhs != NULL);
	assert(rhs != NULL);

	/* TODO: assert(ea->kind == ENTRY_ACTION) */

	/* TODO: output #line delimiters instead of comments */
	indent(d);
	printf("/* ACTION <%s> */\n", nstring_to_cstring(&ea->key));

	indent(d);
	printf("{\n");

	d++;

	if (lhs->return_count) {
		char *prefixtype = "ZT";
		struct entry *et;
		char *st;

		et = ast->lexi_terminal_type;
		/* TODO: assert(et->kind == ENTRY_TYPE); */
		st = nstring_to_cstring(&et->key);

		indent(d);
		printf("%s%s ZT1;\n", prefixtype, st);

		/* TODO: free st? */
	}

	if (ea->u.act->defined) {
		code_out(stdout, ea->u.act->code, rhs, ea->u.act->in, lhs, ea->u.act->out, d);
		if (lhs->return_count) {
			/* TODO: assert(lhs->return_count == 1) */
			indent(d);
			printf("return ZT1;\n");
		}
	} else {
		/* TODO: We should catch this error before beginning output */
		char *pe;

		pe = nstring_to_cstring(&ea->key);
		error(ERROR_SERIOUS, "Action %s is used but undefined", pe);
		xfree(pe);
	}

	d--;

	indent(d);
	printf("}\n");

	indent(d);
	printf("/* END ACTION <%s> */\n", nstring_to_cstring(&ea->key));
}

static void
out_push_zone(struct zone *parent, struct cmd *cmd, unsigned int n, unsigned int d)
{
	assert(parent != NULL);
	assert(cmd != NULL);
	assert(cmd->kind == CMD_PUSH_ZONE);

	if (cmd->u.s.z->kind == ZONE_GENERAL) {
		indent(d);
		printf("state->zone = %s_%s;\n",
			read_token_name, cmd->u.s.z->name);
	}

	if (cmd->u.s.z->enter->head != NULL) {
		out_cmds(parent, cmd->u.s.z->enter, n, d);
	}

	if (cmd->u.s.z->enter->return_count != 0) {
		return;
	}

	indent(d);
	switch (cmd->u.s.z->kind) {
	case ZONE_GENERAL:
		printf("return %s(state);\n", read_token_name);
		break;

	case ZONE_PSEUDO:
		printf("return %s_%s(state);\n", read_token_name, cmd->u.s.z->name);
		break;

	case ZONE_PURE:
		printf("%s_%s(state);\n", read_token_name, cmd->u.s.z->name);
		indent(d);
		printf("goto start;	/* pure function */\n");
		break;
	}
}

static void
out_pop_zone(struct zone *parent, struct cmd *cmd, unsigned int n, unsigned int d)
{
	assert(parent != NULL);
	assert(cmd != NULL);
	assert(cmd->kind == CMD_POP_ZONE);

	if (parent->kind == ZONE_GENERAL) {
		indent(d);
		if (zone_isglobal(cmd->u.s.z)) {
			printf("state->zone = %s;\n", read_token_name);
		} else {
			printf("state->zone = %s_%s;\n", read_token_name,
				cmd->u.s.z->name);
		}
	}

	if (!cmd->u.s.is_beginendmarker_in_zone) {
		unsigned int i;

		for (i = n + 1; i > 0; i--) {
			indent(d);
			printf("%spush(state, c%u);\n", lexi_prefix, i - 1);
		}
	}

	if (parent->exit->head) {
		out_cmds(parent, parent->exit, n, d);
	}

	if (parent->exit->return_count != 0) {
		return;
	}

	indent(d);
	switch (parent->kind) {
	case ZONE_GENERAL:
		printf("return %s(state);\n", read_token_name);
		break;

	case ZONE_PURE:
		printf("return;\n");
		break;

	case ZONE_PSEUDO:
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
	int r;

	assert(parent != NULL);
	assert(ret != NULL);

	if (ret->local_names.top) {
		indent(d);
		printf("{\n");
		++d;
		out_locals(&ret->local_names, d);
	}

	r = 0;
	for (cmd = ret->head; cmd != NULL; cmd = cmd->next) {
		/* TODO: can simplify the calls to out_push_zone() et al by passing only what we need, not the entire cmd */
		switch (cmd->kind) {
		case CMD_RETURN:
			r = 1;
			assert(cmd->next == NULL);
			indent(d);
			printf("return %s;\n", cmd->u.name);
			break;

		case CMD_ACTION:
			out_action(parent->ast, cmd->u.act.ea, cmd->u.act.lhs, cmd->u.act.rhs, d);
			break;

		case CMD_PUSH_ZONE:
			r = 1;
			out_push_zone(parent, cmd, n, d);
			break;

		case CMD_POP_ZONE:
			r = 1;
			out_pop_zone(parent, cmd, n, d);
			break;

		case CMD_NOOP:
			assert(cmd->next == NULL); /* caught during parsing */
			break;
		}
	}

	if (ret->local_names.top) {
		d--;
		indent(d);
		printf("}\n");
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
		indent(d);
		printf("goto start;\n");
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

	indent(d);
	printf("c0 = %s;\n", str);

	indent(d);
	printf("goto restart;\n");
}

/*
 * Returns true if a return was made; false indicates that control is still
 * present in the containing block.
 */
static int
out_leaf(struct zone *parent, struct trie *p, int in_pre_pass, unsigned int n, unsigned int d)
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
			indent(d);
			printf("goto start; /* leaf */\n");
		}

		return 1;
	}

	return 0;
}

static void
out_char_letters(struct zone *z, struct trie *p, int in_pre_pass, unsigned int n, unsigned int d)
{
	struct trie *q;
	int letters;

	assert(z != NULL);
	assert(p != NULL);

	/* count letters */
	letters = 0;
	for (q = p; q != NULL; q = q->opt) {
		letters += q->kind == TRIE_CHAR;
	}

	/* output letters as appropiate for the given count */
	switch (letters) {
	case 0:
		return;

	case 1:
		/* find the single TRIE_CHAR */
		for (q = p; q->kind != TRIE_CHAR; q = q->opt) {
			assert(q->opt != NULL);
		}

		assert(q != NULL);

		indent(d);
		printf("if (c%u == %s) {\n", n, char_lit(q->v.c));

		if (q->next != NULL) {
			out_pass(z, q->next, in_pre_pass, n + 1, d + 1);
		}
		out_leaf(z, q, in_pre_pass, n, d + 1);

		indent(d);
		printf("}\n");

		return;

	default:
		indent(d);
		printf("switch (c%u) {\n", n);
		for (q = p; q != NULL; q = q->opt) {
			int r;

			if (q->kind != TRIE_CHAR) {
				continue;
			}

			indent(d);
			printf("case %s: {\n", char_lit(q->v.c));
			d++;

			if (q->next != NULL) {
				out_pass(z, q->next, in_pre_pass, n + 1, d + 1);
			}
			r = out_leaf(z, q, in_pre_pass, n, d + 1);

			indent(d);
			printf("}\n");

			if (!r) {
				indent(d);
				printf("break;\n");
			}

			printf("\n");

			d--;
		}
		indent(d);
		printf("}\n");

		return;
	}
}

static void
out_char_groups(struct zone *z, struct trie *p, int in_pre_pass, unsigned int n, unsigned int d)
{
	struct trie *q;
	int started;
	int groups;

	assert(z != NULL);
	assert(p != NULL);

	/* count groups */
	groups = 0;
	for (q = p; q != NULL; q = q->opt) {
		groups += q->kind == TRIE_GROUP;
	}

	if (groups == 0) {
		return;
	}

	/* output groups */
	started = 0;
	for (q = p; q != NULL; q = q->opt) {
		struct group_name *gn;

		if (q->kind != TRIE_GROUP) {
			continue;
		}

		gn = q->v.g.gn;
		indent(d);

		if (started) {
			printf("} else ");
		}

		printf("if (%s%sgroup(", q->v.g.not ? "!" : "", lexi_prefix);
		out_groupname(gn);
		printf(", c%u)) {\n", n);

		if (q->next != NULL) {
			out_pass(z, q->next, in_pre_pass, n + 1, d + 1);
		}

		out_leaf(z, q, in_pre_pass, n, d + 1);

		started = 1;
	}

	indent(d);
	printf("}\n");
}

/*
 * OUTPUT PASS INFORMATION
 *
 * This routine outputs code for the lexical pass indicated by p.
 * n gives the depth of recursion and d gives the indentation.
*/
static void
out_pass(struct zone *z, struct trie *p, int in_pre_pass, unsigned int n, unsigned int d)
{
	int w1 = n == 0 && !in_pre_pass;
	int w2 = n == 0 && in_pre_pass;

	assert(z != NULL);
	assert(p != NULL);

	indent(d);
	if (!in_pre_pass && z->pre) {
		if (zone_isglobal(z)) {
			printf("int c%u = %s_aux(state)",
				n, read_token_name);
		} else {
			printf("int c%u = %s_%s_aux(state)",
				n, read_token_name, z->name);
		}
	} else {
		printf("int c%u = %sreadchar(state)", n, lexi_prefix);
	}
	printf(";\n");

	/* TODO: can we move out w1 and w2 into out_zone_*pass(), and keep the recursion simple? */
	if (w1) {
		struct group_name *white;

		white = find_group(z, "white");
		if (white != NULL && !is_group_empty(white->g)) {
			indent(d);
			printf("if (%sgroup(", lexi_prefix);
			out_groupname(white);
			printf(", c0)) goto start;\n");
		}
	}
	if (w2) {
		indent(d);
		printf("restart: {\n");
		d++;
	}

	/* We match letters before groups; letters have priority (TODO: do we need to?) */
	out_char_letters(z, p, in_pre_pass, n, d);
	out_char_groups (z, p, in_pre_pass, n, d);

	if (w2) {
		d--;
		indent(d);
		printf("}\n");
	}

	if (n) {
		indent(d);
		printf("%spush(state, c%u);\n", lexi_prefix,n);
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

	s = p->kind == ZONE_PURE ? "void" : "int";

	if (p == p->ast->global) {
		return;
	}

	printf("static %s %s_%s(struct %sstate *state);\n", s,
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

	printf("/* PRE PASS ANALYSER for %s*/\n\n", zone_name(z));
	if (zone_isglobal(z)) {
		printf("static int %s_aux(struct %sstate *state)\n",
			read_token_name, lexi_prefix);
	} else {
		printf("static int %s_%s_aux(struct %sstate *state)\n",
			read_token_name, z->name, lexi_prefix);
	}
	printf("{\n");
	printf("\tstart: {\n");

	out_pass(z, z->pre, 1, 0, 2);
	out_leaf(z, z->pre, 1, 0, 2);

	printf("\treturn c0;\n");
	printf("\t}\n");
	printf("}\n\n\n");

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

	printf("\n/* MAIN PASS ANALYSER for %s */\n", zone_name(p));
	if (zone_isglobal(p)) {
		printf("int\n%s(struct %sstate *state)\n", read_token_name, lexi_prefix);
		printf("{\n");
		if (p->ast->global->next != NULL) {
			printf("\tif (state->zone != %s)\n", read_token_name);
			printf("\t\treturn state->zone(state);\n");
		}
	} else {
		const char *s;

		s = p->kind == ZONE_PURE ? "void" : "int";

		printf("static %s\n%s_%s(struct %sstate *state)\n", s,
			read_token_name, p->name, lexi_prefix);
		printf("{\n");
	}

	printf("\tstart: {\n");

	/* main pass */
	if (p->main != NULL) {
		out_pass(p, p->main, 0, 0, 2);
	}

	/* TOKEN DEFAULT -> ...; */
	printf("\n\t\t/* DEFAULT */\n");
	if (p->local != NULL) {
		if (!out_cmds(p, p->local, 1, 2)) {
			indent(2);
			printf("goto start; /* DEFAULT */\n");
		}
	} else {
		printf("\t\treturn %sunknown_token;\n",
			opt->interface_prefix);
	}

	printf("\t}\n");
	printf("}\n");
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
	for (p = ast->groups; p != NULL; p = p->next) {
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
	for (p = ast->groups; p != NULL; p = p->next) {
		if (!is_group_empty(p)) {
			i++;
		}
	}

	return i;
}

static void
out_macros(struct options* opt, struct ast *ast)
{

	if (all_groups_empty(ast)) {
		return;
	}

	/*
	 * I'm presenting an int here for multibyte character literals, although
	 * the lookup-table behind them is not that wide. Furthermore, it helps set
	 * my mind at ease for lexers generated on machines with different signedness
	 * for char than the machine upon which the generated lexer is compiled.
	 */
	printf("#if defined(__STDC_VERSION__) && (__STDC_VERSION__ - 0L) >= 199901L\n");
	printf("%s %sgroup(enum %sgroups group, int c) {\n",
		"bool", opt->lexi_prefix, opt->lexi_prefix);
	printf("#else\n");
	printf("%s %sgroup(enum %sgroups group, int c) {\n",
		"int", opt->lexi_prefix, opt->lexi_prefix);
	printf("#endif\n");
	printf("\tif (c == LEXI_EOF) {\n");
	printf("\t\treturn 0;\n");
	printf("\t}\n");
	printf("\treturn lookup_tab[c] & group;\n");
	printf("}\n");
}

/*
 * OUTPUT THE LOOKUP TABLE
 */
static void
out_lookup_table(struct ast *ast,
	const char *groupc90type, const char *groupc99type,
	const char *grouphex, size_t groupwidth)
{
	struct group *g;
	int c;

	if (all_groups_empty(ast)) {
		return;
	}

	/* Character look-up table */
	printf("/* LOOKUP TABLE */\n\n");
	printf("#if defined(__STDC_VERSION__) && (__STDC_VERSION__ - 0L) >= 199901L\n");
	printf("typedef %s lookup_type;\n", groupc99type);
	printf("#else\n");
	printf("typedef %s lookup_type;\n", groupc90type);
	printf("#endif\n");
	printf("static lookup_type lookup_tab[] = {\n");

	for (c = 0; c <= 255; c++) {
		unsigned long m;

		m = 0;
		for (g = ast->groups; g != NULL; g = g->next) {
			if (in_group(g, c)) {
				m |= group_number(ast, g);
			}
		}

		if (c % groupwidth == 0) {
			putc('\t', stdout);
		}

		printf(grouphex, m);

		if (c < 255) {
			printf(", ");
		}
		if ((c % groupwidth) == groupwidth - 1) {
			putc('\n', stdout);
		}
	}

	printf("\n};");
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
	printf("int %sreadchar(struct %sstate *state) {\n",
		lexi_prefix, lexi_prefix);

	if (buffer_length(ast) > 0) {
		printf("\tif (state->buffer_index) {\n");
		printf("\t\treturn %spop(state);\n", lexi_prefix);
		printf("\t}\n\n");
	}

	/* TODO: pass opaque here */
	printf("\treturn %sgetchar(state);\n", opt->interface_prefix);
	printf("}\n");

	if (buffer_length(ast) == 0) {
		return;
	}

	/* Other buffer operations */
	printf("void %spush(struct %sstate *state, const int c) {\n",
		lexi_prefix, lexi_prefix);
	printf("\tassert(state);\n");
	printf("\tassert((size_t) state->buffer_index < sizeof state->buffer / sizeof *state->buffer);\n");
	printf("\tstate->buffer[state->buffer_index++] = c;\n");
	printf("}\n\n");

	printf("int %spop(struct %sstate *state) {\n",
		lexi_prefix, lexi_prefix);
	printf("\tassert(state);\n");
	printf("\tassert(state->buffer_index > 0);\n");
	printf("\treturn state->buffer[--state->buffer_index];\n");
	printf("}\n\n");

	printf("void %sflush(struct %sstate *state) {\n", lexi_prefix, lexi_prefix);
	printf("\tstate->buffer_index = 0;\n");
	printf("}\n\n");
}

static void
out_buffer_storage(struct ast *ast)
{
	if (buffer_length(ast) == 0) {
		return;
	}
}

void
c_out_all(struct options *opt, struct ast *ast)
{
	size_t groupwidth;
	const char *groupc90type, *groupc99type;
	const char *grouphex;
	struct lxi_additional_argument *add_arg;

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
			groupc90type = "unsigned long";
			groupc99type = "uint32_t";
			grouphex = "%# 8lxUL";
			groupwidth = 6;
		} else if (t > 8) {
			groupc90type = "unsigned short";
			groupc99type = "uint16_t";
			grouphex = "%# 4lx";
			groupwidth = 12;
		} else {
			groupc90type = "unsigned char";
			groupc99type = "uint8_t";
			grouphex = "%# 4lx";
			groupwidth = 12;
		}
	}

	printf("#include <assert.h>\n");
	printf("#include <string.h>\n\n");

	printf("#if defined(__STDC_VERSION__) && (__STDC_VERSION__ - 0L) >= 199901L\n");
	printf("#include <stdbool.h>\n");
	printf("#include <stdint.h>\n");
	printf("#endif\n\n");

	code_out(stdout, lct_ast.cfileheader, NULL, NULL, NULL, NULL, 0);

	out_buffer_storage(ast);

	out_buffer(opt, ast);
	printf("\n");

	out_lookup_table(ast, groupc90type, groupc99type, grouphex, groupwidth);
	printf("\n\n");

	out_macros(opt, ast);
	printf("\n\n");

	/* Keywords */
	out_keywords(ast);

	/* Lexical pre-pass */
	printf("/* PRE-PASS ANALYSERS */\n\n");
	out_zone_prepass(ast->global);

	/* lexi_init() */
	/* TODO: assert() state */
	printf("void %sinit(struct %sstate *state",
		opt->lexi_prefix, opt->lexi_prefix);

	for (add_arg = lct_ast.arg_head; add_arg != NULL; add_arg = add_arg->next) {
		printf(", %s %s", add_arg->ctype, add_arg->name);
	}
	printf(") {\n\tstate->zone = %s;\n", read_token_name);

	if (buffer_length(ast) > 0) {
		printf("\tstate->buffer_index = 0;\n");
	}
	for (add_arg = lct_ast.arg_head; add_arg != NULL; add_arg = add_arg->next) {
		printf("\tstate->%s = %s;\n", add_arg->name, add_arg->name);
	}
	printf("}\n");

	printf("/* ZONES PASS ANALYSER PROTOTYPES */\n\n");
	out_zone_pass_prototypes(ast->global);

	printf("/* MAIN PASS ANALYSERS */\n\n");
  	out_zone_pass(opt, ast->global);

	code_out(stdout, lct_ast.cfiletrailer, NULL, NULL, NULL, NULL, 0);

	printf("\n");
}

