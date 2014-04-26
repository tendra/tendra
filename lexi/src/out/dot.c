/* $Id$ */

/*
 * Copyright 2008-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <shared/error.h>

#include <adt/cmd.h>
#include <adt/trie.h>
#include <adt/zone.h>
#include <adt/frame.h>

#include <out/dot.h>
#include <out/common.h>

#include "ast.h"
#include "options.h"

/*
 * Yield a string representing a quoted character. Characters are quoted
 * according to Dot's requirements for strings.
 *
 * A static buffer is used; the pointer returned should not be freed.
 * This is not thread-safe.
 *
 * XXX centralise this?
 */
static char *
quote_char(int c)
{
	static char buf[5];

	if (c > 127) {
		return "?";
	}

	switch (c) {
	case EOF:  return "\\\\e";
	case '\n': return "\\n";
	case '\r': return "\\r";
	case '\t': return "\\t";
	case '\v': return "\\v";
	case '\f': return "\\f";
	case '\\': return "\\\"";
	case '\'': return "\\'";
	case '\"': return "\\\"";
	}

	sprintf(buf, "%c", c);
	return buf;
}

/*
 * Render out a single node. The shape and label of the node is determined by
 * its type according to tree_get_translation().
 */
static void
out_node(struct ast *ast, struct trie *p, struct options *opt) {
	/* node value */
	{
		printf("\t\tc%p [ ", (void *) p);

		switch (p->kind) {
		case TRIE_CHAR:
			printf("label=\"%s\"", quote_char(p->v.c));
			break;

		case TRIE_GROUP:
			printf("shape=box, label=\"[%s%s]\"", p->v.g.not ? "^" : "",
				p->v.g.gn->name);
			break;
		}

		printf(" ];\n");
	}

	/* actions */
	if (p->u.frame != NULL) {
		struct cmd *cmd;

		printf("\t\tc%p -> i%p;\n", (void *) p, (void *) p);
		printf("\t\ti%p [ ", (void *) p);
		printf("shape=plaintext, label=\"");

		for (cmd = p->u.frame->cmds; cmd != NULL; cmd = cmd->next) {
			switch (cmd->kind) {
			case CMD_RETURN:
				/* TODO: rename to just prefix */
				/* TODO: map back _H */
				printf("$%s", cmd->u.name + strlen(opt->lexi_prefix) - 1);
				break;

			case CMD_PUSH_ZONE:
				printf("<push> %s", cmd->u.s.z->name);
				break;

			case CMD_POP_ZONE:
				printf("<pop> %s", cmd->u.s.z->name);
				break;

			case CMD_DISCARD:
				printf("$$");
				break;

			default:
				printf("TODO");	/* TODO: unimplemented */
				break;
			}
		}

		printf("\" ];\n");
	}
}

/*
 * Perform a pass over an entire trie, outputting nodes and their links to
 * adjacent nodes.
 */
static void
pass(void *prev, struct trie *p, struct ast *ast, struct options *opt) {
	struct trie *q;

	for (q = p; q != NULL; q = q->opt) {
		out_node(ast, q, opt);

		printf("\t\tc%p -> c%p [ dir=none ];\n", prev, (void *) q);

		if (q->next == NULL) {
			continue;
		}

		pass(q, q->next, ast, opt);
	}

}

static void
out_zone(struct options *opt, struct ast *ast, struct zone *z)
{
	struct zone *p;

	assert(opt != NULL);
	assert(ast != NULL);
	assert(z != NULL);

	printf("\t{\n");

	for (p = z; p != NULL; p = p->opt) {
		/* TODO output pre-pass mappings (render as -> "xyz") */
		/* TODO keywords, pending #250 */
		/* TODO DEFAULT */
		/* TODO enter/leaving commands */

		printf("\t\tc%p [ shape=plaintext, label=\"%s\" ];\n",
			(void *) p, p->name == NULL ? "(global)" : p->name);

		pass(p, p->main, ast, opt);

		if (p->next != NULL) {
			out_zone(opt, ast, p->next);
		}
	}

	printf("\t}\n");
}

void
dot_out_all(struct options *opt, struct ast *ast)
{
	assert(opt != NULL);
	assert(ast != NULL);

	printf("digraph G {\n");
	printf("\tnode [ shape=circle, fontname=verdana ];\n");
	printf("\trankdir = LR;\n");

	/* TODO output each child zone, not just siblings (nest as subgraphs) */
	out_zone(opt, ast, ast->global);

	printf("};\n");
}

