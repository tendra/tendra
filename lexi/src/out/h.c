/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

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

#include <out/c.h>

#include "ast.h"
#include "lexer.h"
#include "lctsyntax.h"
#include "options.h"

/*
 * OUTPUT OPTIONS
 *
 * next_name gives the name of the character reading
 * function used in the output routines.
 */
static const char *next_name;
static const char *lexi_prefix;

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

	printf("\n/* Identify a keyword */\n");
	printf("int %skeyword(const char *identifier, int notfound);\n",
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

static int
more_groups(struct zone *z)
{
	struct zone *p;

	/* Group interface */
	for (p = z; p != NULL; p = p->opt) {
		if (p->groups != NULL) {
			return 1;
		}

		if (more_groups(z->next)) {
			return 1;
		}
	}

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

			printf("\t");
			out_groupname(gn);
			printf(" = %#lx", m);

			if (gn->next || more_groups(p->opt) || more_groups(p->next)) {
				printf(",");
			}

			printf("\n");
		}

		if (z->next) {
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

	printf("enum %sgroups {\n", opt->lexi_prefix);
	out_macros_zone(opt, ast->global);
	printf("};\n");

	printf("\n/* true if the given character is present in the given group */\n");
	printf("#if defined(__STDC_VERSION__) && (__STDC_VERSION__ - 0L) >= 199901L\n");
	printf("%s %sgroup(enum %sgroups group, int c);\n",
		"bool", opt->lexi_prefix, opt->lexi_prefix);
	printf("#else\n");
	printf("%s %sgroup(enum %sgroups group, int c);\n",
		"int", opt->lexi_prefix, opt->lexi_prefix);
	printf("#endif\n");
}

/*
 * OUTPUT LEXI AUTOMATED DEFINED OPERATIONS
 */
static void
out_buffer(struct options *opt, struct ast *ast)
{
	UNUSED(opt);

	/*
	 * Strictly the state argument is not required in the case of a
	 * lookahead of one character, since the token buffer does not exist.
	 * However, we pass it regardless, for simplicity.
	 */
	printf("/* Read a character */\n");
	printf("int %sreadchar(struct %sstate *state);\n\n",
		lexi_prefix, lexi_prefix);

	if (buffer_length(ast) == 0) {
		return;
	}

	/* Other buffer operations */
	printf("/* Push a character to lexi's buffer */\n");
	printf("void %spush(struct %sstate *state, const int c);\n\n",
		lexi_prefix, lexi_prefix);

	printf("/* Pop a character from lexi's buffer */\n");
	printf("int %spop(struct %sstate *state);\n\n",
		lexi_prefix, lexi_prefix);

	printf("/* Flush lexi's buffer */\n");
	printf("void %sflush(struct %sstate *state);\n\n",
		lexi_prefix, lexi_prefix);
}

static void
out_buffer_storage(struct ast *ast)
{
	if (buffer_length(ast) == 0) {
		return;
	}

	/* Buffer storage */
	printf("\n");
	printf("\t/*\n");
	printf("\t * Lexi's buffer is a simple stack.\n");
	printf("\t */\n");
	printf("\tint buffer[%u];\n", buffer_length(ast));
	printf("\tint buffer_index;\n");
}

void
h_out_all(struct options *opt, struct ast *ast)
{
	struct lxi_additional_argument *add_arg;

	next_name = xstrcat(opt->lexi_prefix, "next");
	lexi_prefix = opt->lexi_prefix;

	printf("#ifndef LEXI_GENERATED_HEADER_%s_INCLUDED\n", lexi_prefix);
	printf("#define LEXI_GENERATED_HEADER_%s_INCLUDED\n", lexi_prefix);
	printf("\n");

	printf("#if defined(__STDC_VERSION__) && (__STDC_VERSION__ - 0L) >= 199901L\n");
	printf("#include <stdbool.h>\n");
	printf("#endif\n\n");

	code_out(stdout, lct_ast.hfileheader, NULL, NULL, NULL, NULL, 0);

	printf(
		"/*\n"
		" * This struct holds state for the lexer; its representation is\n"
		" * private, but present here for ease of allocation.\n"
		" */\n");
	printf("struct %sstate {\n"
	      "\tint (*zone)(struct %sstate *);\n",
		opt->lexi_prefix, opt->lexi_prefix);
	out_buffer_storage(ast);

	for (add_arg = lct_ast.arg_head; add_arg != NULL; add_arg = add_arg->next) {
		printf("\t%s %s;\n", add_arg->ctype, add_arg->name);
	}
	printf("};\n\n");

	out_buffer(opt, ast);

	printf("#ifndef LEXI_EOF\n");
	printf("#define LEXI_EOF %d\n", EOF); /* TODO: remove LEXI_EOF */
	printf("#endif\n\n");

	out_macros(opt, ast);

	/* Keywords */
	out_keywords(ast);

	/* Main pass */
	printf("\n/* Identify a token */\n");
	printf("int %s(struct %sstate *state);\n\n",
		next_name, lexi_prefix);

	/* lexi_init() */
	/* TODO: assert() state */
	printf("/* Initialise a %sstate structure */\n", opt->lexi_prefix);
	printf("void %sinit(struct %sstate *state", opt->lexi_prefix, opt->lexi_prefix);

	for (add_arg = lct_ast.arg_head; add_arg != NULL; add_arg = add_arg->next) {
		printf(", %s %s", add_arg->ctype, add_arg->name);
	}
	printf(");\n\n");

	code_out(stdout, lct_ast.hfiletrailer, NULL, NULL, NULL, NULL, 0);

	printf("#endif\n");

	printf("\n");
}

