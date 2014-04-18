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

#include "adt/char.h"
#include "adt/instruction.h"
#include "adt/tree.h"
#include "adt/zone.h"	/* XXX */

#include "options.h"
#include "dot-output.h"
#include "output.h"

/* This is a convenience for brevity */
#define dotout opt->outputfile[0].file

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
output_node(lexer_parse_tree *top_level, character *p, cmd_line_options *opt) {
	/* node value */
	{
		fprintf(dotout, "\t\tc%p [ ", (void *) p);

		switch (p->type) {
		case char_letter:
			fprintf(dotout, "label=\"%s\"", quote_char(p->v.c));
			break;

		case group_letter:
			fprintf(dotout, "shape=box, label=\"[%s%s]\"", p->v.g.not ? "^" : "",
				p->v.g.grp->name);
			break;
		}

		fprintf(dotout, " ];\n");
	}

	/* actions */
	if (p->u.definition != NULL) {
		instruction* instr;

		fprintf(dotout, "\t\tc%p -> i%p;\n", (void *) p, (void *) p);
		fprintf(dotout, "\t\ti%p [ ", (void *) p);
		fprintf(dotout, "shape=plaintext, label=\"");

		for (instr = p->u.definition->head; instr != NULL; instr = instr->next) {
			switch (instr->type) {
			case return_terminal:
				/* TODO rename to just prefix */
				/* TODO map back _H */
				fprintf(dotout, "$%s",
					instr->u.name + strlen(opt->lexi_prefix) - 1);
				break;

			case pop_zone:
				fprintf(dotout, "<pop> %s",
					instr->u.s.z->zone_name);
				break;

			case push_zone:
				fprintf(dotout, "<push> %s",
					instr->u.s.z->zone_name);
				break;

			case do_nothing:
				fprintf(dotout, "$$");
				break;

			default:
				fprintf(dotout, "TODO");	/* TODO unimplemented */
				break;
			}
		}

		fprintf(dotout, "\" ];\n");
	}
}

/*
 * Perform a pass over an entire trie, outputting nodes and their links to
 * adjacent nodes.
 */
static void
pass(void *prev, character *p, lexer_parse_tree *top_level, cmd_line_options *opt) {
	character *q;

	for (q = p; q != NULL; q = q->opt) {
		output_node(top_level, q, opt);

		fprintf(dotout, "\t\tc%p -> c%p [ dir=none ];\n", prev, (void *) q);

		if (q->next == NULL) {
			continue;
		}

		pass(q, q->next, top_level, opt);
	}

}

static void
output_zone(cmd_line_options *opt, lexer_parse_tree *top_level,  zone *z)
{
	zone *p;

	assert(opt != NULL);
	assert(top_level != NULL);
	assert(z != NULL);

	fprintf(dotout, "\t{\n");

	for (p = z; p != NULL; p = p->opt) {
		/* TODO output pre-pass mappings (render as -> "xyz") */
		/* TODO keywords, pending #250 */
		/* TODO DEFAULT */
		/* TODO enter/leaving instructions */

		fprintf(dotout, "\t\tc%p [ shape=plaintext, label=\"%s\" ];\n",
			(void *) p, p->zone_name == NULL ? "(global)" : p->zone_name);

		pass(p, p->zone_main_pass, top_level, opt);

		if (p->next != NULL) {
			output_zone(opt, top_level, p->next);
		}
	}

	fprintf(dotout, "\t}\n");
}

void dot_output_all(cmd_line_options *opt, lexer_parse_tree *top_level) {
	FILE_list_entry *file_list;

	assert(opt != NULL);
	assert(top_level != NULL);

	for (file_list = tree_get_copyright_list(top_level);
            file_list != NULL;
            file_list = file_list_next(file_list)) {
		if (!output_comment_file(OUTPUT_COMMENT_C90, dotout, file_list_crt_file(file_list))) {
			error(ERROR_SERIOUS,"Copyright file %s contains comment characters",
			      file_list_crt_filename(file_list));
		}
	}

	output_generated_by_lexi(OUTPUT_COMMENT_C90, dotout);

	fprintf(dotout, "digraph G {\n");
	fprintf(dotout, "\tnode [ shape=circle, fontname=verdana ];\n");
	fprintf(dotout, "\trankdir = LR;\n");

	/* TODO output each child zone, not just siblings (nest as subgraphs) */
	output_zone(opt, top_level, tree_get_globalzone(top_level));

	fprintf(dotout, "};\n");

  	return;
}

