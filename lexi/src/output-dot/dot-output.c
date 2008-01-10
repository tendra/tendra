/*
 * Copyright (c) 2008 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "char.h"
#include "error.h"
#include "options.h"
#include "dot-output.h"

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
quote_char(letter_translation* ctrans)
{
	static char buff[5];

	assert(ctrans->type != last_letter);

	if(ctrans->type == eof_letter) {
		return "\\\\e";
	}

	assert(ctrans->type == char_letter);

	if(ctrans->u.ch > 127) {
		return "?";
	}

	switch (ctrans->u.ch) {
		case '\n': return "\\n";
		case '\r': return "\\r";
		case '\t': return "\\t";
		case '\v': return "\\v";
		case '\f': return "\\f";
		case '\\': return "\\\"";
		case '\'': return "\\'";
		case '\"': return "\\\"";
	}

	sprintf(buff, "%c", (char)ctrans->u.ch);
	return buff;
}

/*
 * Render out a single node. The shape and label of the node is determined by
 * its type according to letters_table_get_translation().
 */
static void
output_node(lexer_parse_tree *top_level, character *p, cmd_line_options *opt) {
	letter_translation *ctrans;

	ctrans = letters_table_get_translation(p->ch, top_level->letters_table);
	fprintf(dotout, "\tc%p [ ", p);

	switch(ctrans->type) {
	case last_letter: {
		instruction* instr;

		fprintf(dotout, "shape=plaintext, label=\"");

		if(p->u.definition) {
			for(instr = p->u.definition->head; instr; instr = instr->next) {
				switch(instr->type) {
				case return_token:
					/* TODO rename to just prefix */
					/* TODO map back _H */
					fprintf(dotout, "$%s",
						instr->u.name + strlen(opt->lexi_prefix) - 1);
					break;

				case apply_function:
					fprintf(dotout, "%s()",
						instr->u.fun->name);
					break;

				case pop_zone:
					fprintf(dotout, "<pop> %s",
						instr->u.z->zone_name);
					break;

				case push_zone:
					fprintf(dotout, "<push> %s",
						instr->u.z->zone_name);
					break;

				case do_nothing:
					fprintf(dotout, "$$");
					break;

				default:
					fprintf(dotout, "TODO");	/* TODO unimplemented */
					break;
				}
			}
		} else {
			/* Must be the root node, which, confusingly, is of type last_letter */
			fprintf(dotout, "/");
		}

		fprintf(dotout, "\"");
		break;
	}

	case eof_letter:
	case char_letter:
		fprintf(dotout, "label=\"%s\"",
			quote_char(ctrans));
		break;

	case group_letter:
	case notin_group_letter:
		/* TODO handle inverted groups */
		fprintf(dotout, "shape=box, label=\"[%s]\"",
			ctrans->u.grp->name);
		break;

	default:
		fprintf(dotout, "shape=plaintext, label=\"TODO\"");
		break;
	}

	fprintf(dotout, " ];\n");
}

/*
 * Perform a pass over an entire trie, outputting nodes and their links to
 * adjacent nodes.
 */
static void
pass(character *p, lexer_parse_tree *top_level, cmd_line_options *opt) {
	character *q;

	if(!p) {
		return;
	}

	output_node(top_level, p, opt);

	for(q = p->next; q; q = q->opt) {
		letter_translation* ctrans;

		ctrans = letters_table_get_translation(q->ch, top_level->letters_table);

		fprintf(dotout, "\tc%p -> c%p [ dir=%s ];\n",
			p, q, ctrans->type == last_letter ? "forward" : "none");

		pass(q, top_level, opt);
	}

}

void dot_output_all(cmd_line_options *opt, lexer_parse_tree *top_level) {
	fprintf(dotout, "digraph G {\n");
	fprintf(dotout, "\tnode [ shape=circle, fontname=verdana ];\n");
	fprintf(dotout, "\trankdir = LR;\n");

	/* TODO output each zone */
	/* TODO output pre-pass mappings (render as -> "xyz") */
	/* TODO keywords, pending #250 */

	pass(top_level->global_zone->zone_main_pass, top_level, opt);

	fprintf(dotout, "};\n");

  	return;
}

