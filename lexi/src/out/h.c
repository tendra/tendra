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
#include <out/common.h>

#include "ast.h"
#include "lexer.h"
#include "lctsyntax.h"
#include "options.h"

/*
 * OUTPUT OPTIONS
 *
 * read_name gives the name of the character reading
 * function used in the output routines.
 */
static const char *read_token_name;
static const char *lexi_prefix;

/*
 * OUTPUT FILE
 *
 * These variables gives the output files. out is used within this file
 * as a shorthand for lex_out_h.
 */
FILE *lex_out_h;


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
out_groupname(FILE *f, struct group_name *gn)
{
	const char *prefix;

	assert(f != NULL);
	assert(gn != NULL);

	prefix = zone_isglobal(gn->z) ? "group" : gn->z->name;

	fprintf(f, "%s%s_%s", lexi_prefix, prefix, gn->name);
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
out_keywords(struct ast *ast, FILE *out_h)
{
	assert(ast != NULL);
	assert(out_h != NULL);

	if (ast->global->keywords == NULL) {
		return;
	}

	fputs("\n/* Identify a keyword */\n", out_h);
	fprintf(out_h, "int %skeyword(const char *identifier, int notfound);\n",
		lexi_prefix);
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
out_macros(struct options *opt, struct ast *ast)
{
	if (all_groups_empty(ast)) {
		return;
	}

	fprintf(lex_out_h, "enum %sgroups {\n", opt->lexi_prefix);
	out_macros_zone(opt, ast->global);
	fputs("};\n", lex_out_h);

	fputs("\n/* true if the given character is present in the given group */\n",
		lex_out_h);
	fputs("#if defined(__STDC_VERSION__) && (__STDC_VERSION__ - 0L) >= 199901L\n",
		lex_out_h);
	fprintf(lex_out_h, "%s %sgroup(enum %sgroups group, int c);\n",
		"bool", opt->lexi_prefix, opt->lexi_prefix);
	fputs("#else\n", lex_out_h);
	fprintf(lex_out_h, "%s %sgroup(enum %sgroups group, int c);\n",
		"int", opt->lexi_prefix, opt->lexi_prefix);
	fputs("#endif\n", lex_out_h);
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

	if (buffer_length(ast) == 0) {
		return;
	}

	/* Other buffer operations */
	fputs("/* Push a character to lexi's buffer */\n", lex_out_h);
	fprintf(lex_out_h, "void %spush(struct %sstate *state, const int c);\n\n",
		lexi_prefix, lexi_prefix);

	fputs("/* Pop a character from lexi's buffer */\n", lex_out_h);
	fprintf(lex_out_h, "int %spop(struct %sstate *state);\n\n",
		lexi_prefix, lexi_prefix);

	fputs("/* Flush lexi's buffer */\n", lex_out_h);
	fprintf(lex_out_h, "void %sflush(struct %sstate *state);\n\n",
		lexi_prefix, lexi_prefix);
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
h_out_all(struct options *opt, struct ast *ast)
{
	struct lxi_additional_argument* add_arg;

	lex_out_h = opt->out[1].file;

	read_token_name = xstrcat(opt->lexi_prefix, "read_token");
	lexi_prefix = opt->lexi_prefix;

	out_generated_by_lexi(lex_out_h);

	fprintf(lex_out_h, "#ifndef LEXI_GENERATED_HEADER_%s_INCLUDED\n", lexi_prefix);
	fprintf(lex_out_h, "#define LEXI_GENERATED_HEADER_%s_INCLUDED\n", lexi_prefix);
	fputs("\n", lex_out_h);

	code_out(lex_out_h, lct_ast.hfileheader, NULL, NULL, NULL, NULL, 0);

	fputs("#if defined(__STDC_VERSION__) && (__STDC_VERSION__ - 0L) >= 199901L\n",
		lex_out_h);
	fputs("#include <stdbool.h>\n", lex_out_h);
	fputs("#endif\n\n", lex_out_h);

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

	fputs("#ifndef LEXI_EOF\n", lex_out_h);
	fprintf(lex_out_h, "#define LEXI_EOF %d\n", EOF); /* TODO: remove LEXI_EOF */
	fputs("#endif\n\n", lex_out_h);

	out_macros(opt, ast);

	/* Keywords */
	out_keywords(ast, lex_out_h);

	/* Main pass */
	fputs("\n/* Identify a token */\n", lex_out_h);
	fprintf(lex_out_h, "int %s(struct %sstate *state);\n\n",
		read_token_name, lexi_prefix);

	/* lexi_init() */
	/* TODO: assert() state */
	fprintf(lex_out_h, "/* Initialise a %sstate structure */\n",
		opt->lexi_prefix);
	fprintf(lex_out_h, "void %sinit(struct %sstate *state",
		opt->lexi_prefix, opt->lexi_prefix);

	for (add_arg = lct_ast.arg_head; add_arg != NULL; add_arg = add_arg->next) {
		fprintf(lex_out_h, ", %s %s", add_arg->ctype, add_arg->name);
	}
	fputs(");\n\n", lex_out_h);

	code_out(lex_out_h, lct_ast.hfiletrailer, NULL, NULL, NULL, NULL, 0);

	fputs("#endif\n", lex_out_h);

	fputs("\n", lex_out_h);
}

