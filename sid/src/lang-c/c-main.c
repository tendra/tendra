/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * c-main.c - C language entry points.
 */

#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>

#include <exds/dalloc.h>
#include <exds/error.h>
#include <exds/cstring-list.h>

#include "c-main.h"
#include "c-out-info.h"
#include "c-output.h"
#include "c-check.h"
#include "c-lexer.h"
#include "c-parser.h"

#include "../lang.h"
#include "../output.h"

static void *
main_init_c(OutputInfoT *out_info, CStringListT *options, bool ansi)
{
	COutputInfoT      *c_out_info = ALLOCATE(COutputInfoT);
	CStringListEntryT *entry;

	c_out_info_init(c_out_info, out_info);
	if (ansi) {
		c_out_info_set_prototypes(c_out_info, true);
	}

	for (entry = cstring_list_head(options); entry;
		entry = cstring_list_entry_deallocate(entry)) {
		const char *option;

		option = cstring_list_entry_string(entry);
		if (streq(option, "prototypes") || streq(option, "proto")) {
			c_out_info_set_prototypes(c_out_info, true);
		} else if (streq(option, "no-prototypes")
			|| streq(option, "no-proto")) {
			c_out_info_set_prototypes(c_out_info, false);
		} else if (streq(option, "split")) {
			c_out_info_set_split(c_out_info, 5000);
		} else if (cstring_starts(option, "split=")) {
			unsigned limit;
			if (!cstring_to_unsigned(option + 6, &limit)) {
				error(ERR_FATAL, "bad split size '%s'", option + 6);
				UNREACHED;
			}
			c_out_info_set_split(c_out_info, limit);
		} else if (streq(option, "no-split")) {
			c_out_info_set_split(c_out_info, 0);
		} else if (streq(option, "numeric-ids")
			|| streq(option, "numeric")) {
			c_out_info_set_numeric_ids(c_out_info, true);
		} else if (streq(option, "no-numeric-ids")
			|| streq(option, "no-numeric")) {
			c_out_info_set_numeric_ids(c_out_info, false);
		} else if (streq(option, "numeric-terminals")
			|| streq(option, "numeric-terminals")) {
			c_out_info_set_numeric_terminals(c_out_info, true);
		} else if (streq(option, "no-numeric-terminals")
			|| streq(option, "no-numeric-terminals")) {
			c_out_info_set_numeric_terminals(c_out_info, false);
		} else if (streq(option, "casts")
			|| streq(option, "cast")) {
			c_out_info_set_casts(c_out_info, true);
		} else if (streq(option, "no-casts")
			|| streq(option, "no-cast")) {
			c_out_info_set_casts(c_out_info, false);
		} else if (streq(option, "unreachable-macros")
			|| streq(option, "unreachable-macro")) {
			c_out_info_set_unreachable(c_out_info, true);
		} else if (streq(option, "unreachable-comments")
			|| streq(option, "unreachable-comment")) {
			c_out_info_set_unreachable(c_out_info, false);
		} else if (streq(option, "lines")
			|| streq(option, "line")) {
			c_out_info_set_lines(c_out_info, true);
		} else if (streq(option, "no-lines")
			|| streq(option, "no-line")) {
			c_out_info_set_lines(c_out_info, false);
		} else if (streq(option, "terminals")
			|| streq(option, "terminal")) {
			c_out_info_set_terminals(c_out_info, true);
		} else if (streq(option, "no-terminals")
			|| streq(option, "no-terminal")) {
			c_out_info_set_terminals(c_out_info, false);
		} else {
			error(ERR_FATAL, "language '%s' doesn't understand option '%s'",
				ansi ? "ansi-c" : "pre-ansi-c", option);
		}
	}

	return c_out_info;
}

static void *
main_init_ansi_c(OutputInfoT *out_info, CStringListT *options)
{
	return main_init_c(out_info, options, true);
}

static void *
main_init_pre_ansi_c(OutputInfoT *out_info, CStringListT *options)
{
	return main_init_c(out_info, options, false);
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
