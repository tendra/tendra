/*
 * Copyright (c) 2002-2008 The TenDRA Project <http://www.tendra.org/>.
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
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

/*
 * c-main.c - C language entry points.
 */

#include <string.h>

#include <exds/dalloc.h>
#include <exds/error.h>
#include <exds/cstring-list.h>

#include <shared/check.h>
#include <shared/error.h>

#include "c-main.h"
#include "c-out-info.h"
#include "c-output.h"
#include "c-check.h"
#include "c-lexer.h"
#include "c-parser.h"

#include "../lang.h"
#include "../output.h"

static void *
main_init_c(OutputInfoT *out_info, CStringListT *options, BoolT ansi)
{
	COutputInfoT      *c_out_info = ALLOCATE(COutputInfoT);
	CStringListEntryT *entry;

	c_out_info_init(c_out_info, out_info);
	if (ansi) {
		c_out_info_set_prototypes(c_out_info, TRUE);
	}

	for (entry = cstring_list_head(options); entry;
		entry = cstring_list_entry_deallocate(entry)) {
		char *option;

		option = cstring_list_entry_string(entry);
		if (!strcmp(option, "prototypes") || !strcmp(option, "proto")) {
			c_out_info_set_prototypes(c_out_info, TRUE);
		} else if (!strcmp(option, "no-prototypes")
			|| !strcmp(option, "no-proto")) {
			c_out_info_set_prototypes(c_out_info, FALSE);
		} else if (!strcmp(option, "split")) {
			c_out_info_set_split(c_out_info, 5000);
		} else if (cstring_starts(option, "split=")) {
			unsigned limit;
			if (!cstring_to_unsigned(option + 6, &limit)) {
				error(ERROR_FATAL, "bad split size '%s'", option + 6);
				UNREACHED;
			}
			c_out_info_set_split(c_out_info, limit);
		} else if (!strcmp(option, "no-split")) {
			c_out_info_set_split(c_out_info, 0);
		} else if (!strcmp(option, "numeric-ids")
			|| !strcmp(option, "numeric")) {
			c_out_info_set_numeric_ids(c_out_info, TRUE);
		} else if (!strcmp(option, "no-numeric-ids")
			|| !strcmp(option, "no-numeric")) {
			c_out_info_set_numeric_ids(c_out_info, FALSE);
		} else if (!strcmp(option, "numeric-terminals")
			|| !strcmp(option, "numeric-terminals")) {
			c_out_info_set_numeric_terminals(c_out_info, TRUE);
		} else if (!strcmp(option, "no-numeric-terminals")
			|| !strcmp(option, "no-numeric-terminals")) {
			c_out_info_set_numeric_terminals(c_out_info, FALSE);
		} else if (!strcmp(option, "casts")
			|| !strcmp(option, "cast")) {
			c_out_info_set_casts(c_out_info, TRUE);
		} else if (!strcmp(option, "no-casts")
			|| !strcmp(option, "no-cast")) {
			c_out_info_set_casts(c_out_info, FALSE);
		} else if (!strcmp(option, "unreachable-macros")
			|| !strcmp(option, "unreachable-macro")) {
			c_out_info_set_unreachable(c_out_info, TRUE);
		} else if (!strcmp(option, "unreachable-comments")
			|| !strcmp(option, "unreachable-comment")) {
			c_out_info_set_unreachable(c_out_info, FALSE);
		} else if (!strcmp(option, "lines")
			|| !strcmp(option, "line")) {
			c_out_info_set_lines(c_out_info, TRUE);
		} else if (!strcmp(option, "no-lines")
			|| !strcmp(option, "no-line")) {
			c_out_info_set_lines(c_out_info, FALSE);
		} else if (!strcmp(option, "terminals")
			|| !strcmp(option, "terminal")) {
			c_out_info_set_terminals(c_out_info, TRUE);
		} else if (!strcmp(option, "no-terminals")
			|| !strcmp(option, "no-terminal")) {
			c_out_info_set_terminals(c_out_info, FALSE);
		} else {
			error(ERROR_FATAL, "language '%s' doesn't understand option '%s'",
				ansi ? "ansi-c" : "pre-ansi-c", option);
		}
	}

	return c_out_info;
}

static void *
main_init_ansi_c(OutputInfoT *out_info, CStringListT *options)
{
	return main_init_c(out_info, options, TRUE);
}

static void *
main_init_pre_ansi_c(OutputInfoT *out_info, CStringListT *options)
{
	return main_init_c(out_info, options, FALSE);
}

static void
main_input_c(void *gclosure, GrammarT *grammar)
{
	COutputInfoT  *c_out_info = gclosure;
	OutputInfoT   *out_info   = c_out_info_info(c_out_info);
	CLexerStreamT  clstream;

	c_lexer_init(&clstream, out_info_get_istream(out_info, (unsigned)1));
	c_current_stream   = &clstream;
	c_current_out_info = c_out_info;
	c_current_table    = grammar_table(grammar);
	c_parse_grammar();
	c_lexer_close(&clstream);
	if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
		exit(EXIT_FAILURE);
		UNREACHED;
	}
	c_check_grammar(grammar);
}

static void
main_output_c(void *gclosure, GrammarT *grammar)
{
	COutputInfoT *c_out_info = gclosure;

	grammar_compute_mutations(grammar);
	out_info_set_current_ostream(c_out_info_info(c_out_info), 0);
	c_output_parser(c_out_info, grammar);
	out_info_set_current_ostream(c_out_info_info(c_out_info), 1);
	c_output_header(c_out_info, grammar);
}

struct LangListT c_language_list_ansi = {
	"ansi-c", 2, 2, main_init_ansi_c, main_input_c, main_output_c
};

struct LangListT c_language_list_pre_ansi = {
	"pre-ansi-c", 2, 2, main_init_pre_ansi_c, main_input_c, main_output_c
};

struct LangListT c_language_list_iso = {
	"iso-c", 2, 2, main_init_ansi_c, main_input_c, main_output_c
};

struct LangListT c_language_list_pre_iso = {
	"pre-iso-c", 2, 2, main_init_pre_ansi_c, main_input_c, main_output_c
};

