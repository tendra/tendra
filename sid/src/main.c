/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
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
 * main.c - SID program main routine.
 *
 * This file implements the main function for SID.  The main function just
 * deals with exception handling.  It calls the ``main_init'' function to
 * initialise the error reporting routines and parse the command line
 * arguments, and the ``main_1'' function to parse the grammar.
 *
 * The initialisation stuff should be trivial.  The ``main_1'' function first
 * parses the grammar and any language specific input files.  The grammar
 * parser is defined in the file "parser/parser.sid".  The language specific
 * file parsers are defined in the files "LANGUAGE-input/LANGUAGE-parser.sid".
 *
 * After reading in the grammar, and language specific information, it then
 * calls various functions to manipulate the grammar.  These functions are
 * described in "transforms/grammar.[ch]".
 *
 * Finally, it calls an output function to output a program to recognise the
 * grammar.  The output functions are described in the
 * "LANGUAGE-output/LANGUAGE-output.[ch]" files.
 */

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <exds/common.h>
#include <exds/exception.h>
#include "shared/check/check.h"
#include "arg-parse.h"
#include "lang-c/c-check.h"
#include "lang-c/c-lexer.h"
#include "lang-c/c-output.h"
#include "lang-c/c-parser.h"
#include <exds/cstring.h>
#include "adt/cstring-list.h"
#include <exds/dstring.h>
#include <exds/error.h>
#include <exds/error-file.h>
#include "gen-errors.h"
#include "grammar.h"
#include <exds/istream.h>
#include "lexer.h"
#include <exds/ostream.h>
#include "output.h"
#include "parser.h"
#include "adt/rule.h"

#define USAGE "\
usage:[option ...] in-file ... out-file ...\n\
where option is one of:\n"
#define VERSION "sid: version 1.11 (ansi-c, pre-ansi-c, test)"
#define RELEASE "tendra.org"

typedef struct PhaseListT {
    char *			phase;
    void		     (*proc)(BoolT);
} PhaseListT;

typedef struct LangListT {
    char *			language;
    void *		     (*init_proc)(OutputInfoT *, CStringListT *);
    void		     (*input_proc)(void *, GrammarT *);
    unsigned			num_input_files;
    void		     (*output_proc)(void *, GrammarT *);
    unsigned			num_output_files;
} LangListT;

static void
main_handle_phase_all(BoolT enable)
{
    rule_set_inline_singles(enable);
    rule_set_inline_tail_calls(enable);
    rule_set_inline_all_basics(enable);
    rule_set_inline_non_tail_calls(enable);
    rule_set_multiple_inlining(enable);
}

static void *
main_init_c(OutputInfoT * out_info, CStringListT * options, BoolT ansi)
{
    COutputInfoT *      c_out_info = ALLOCATE(COutputInfoT);
    CStringListEntryT * entry;

    c_out_info_init(c_out_info, out_info);
    if (ansi) {
	c_out_info_set_prototypes(c_out_info, TRUE);
    }
    for (entry = cstring_list_head(options); entry;
	 entry = cstring_list_entry_deallocate(entry)) {
	char * option = cstring_list_entry_string(entry);

	if (!strcmp(option, "prototypes") ||
	    !strcmp(option, "proto")) {
	    c_out_info_set_prototypes(c_out_info, TRUE);
	} else if (!strcmp(option, "no-prototypes") ||
		   !strcmp(option, "no-proto")) {
	    c_out_info_set_prototypes(c_out_info, FALSE);
	} else if (!strcmp(option, "split")) {
	    c_out_info_set_split(c_out_info, (unsigned)5000);
	} else if (cstring_starts(option, "split=")) {
	    unsigned limit;
	    if (!cstring_to_unsigned(option + 6, &limit)) {
		E_bad_split_size(option + 6);
		UNREACHED;
	    }
	    c_out_info_set_split(c_out_info, limit);
	} else if (!strcmp(option, "no-split")) {
	    c_out_info_set_split(c_out_info, (unsigned)0);
	} else if (!strcmp(option, "numeric-ids") ||
		   !strcmp(option, "numeric")) {
	    c_out_info_set_numeric_ids(c_out_info, TRUE);
	} else if (!strcmp(option, "no-numeric-ids") ||
		   !strcmp(option, "no-numeric")) {
	    c_out_info_set_numeric_ids(c_out_info, FALSE);
	} else if (!strcmp(option, "casts") ||
		   !strcmp(option, "cast")) {
	    c_out_info_set_casts(c_out_info, TRUE);
	} else if (!strcmp(option, "no-casts") ||
		   !strcmp(option, "no-cast")) {
	    c_out_info_set_casts(c_out_info, FALSE);
	} else if (!strcmp(option, "unreachable-macros") ||
		   !strcmp(option, "unreachable-macro")) {
	    c_out_info_set_unreachable(c_out_info, TRUE);
	} else if (!strcmp(option, "unreachable-comments") ||
		   !strcmp(option, "unreachable-comment")) {
	    c_out_info_set_unreachable(c_out_info, FALSE);
	} else if (!strcmp(option, "lines") ||
		   !strcmp(option, "line")) {
	    c_out_info_set_lines(c_out_info, TRUE);
	} else if (!strcmp(option, "no-lines") ||
		   !strcmp(option, "no-line")) {
	    c_out_info_set_lines(c_out_info, FALSE);
	} else {
	    char * lang;
	    lang = (ansi ? "ansi-c" : "pre-ansi-c");
	    E_bad_language_option(lang, option);
	}
    }
    return(c_out_info);
}

static void *
main_init_ansi_c(OutputInfoT * out_info, CStringListT * options)
{
    return(main_init_c(out_info, options, TRUE));
}

static void *
main_init_pre_ansi_c(OutputInfoT * out_info, CStringListT * options)
{
    return(main_init_c(out_info, options, FALSE));
}

static void
main_input_c(void * gclosure, GrammarT * grammar)
{
    COutputInfoT *  c_out_info = (COutputInfoT *)gclosure;
    OutputInfoT *   out_info   = c_out_info_info(c_out_info);
    CLexerStreamT clstream;

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
main_output_c(void * gclosure, GrammarT * grammar)
{
    COutputInfoT * c_out_info = (COutputInfoT *)gclosure;

    grammar_compute_mutations(grammar);
    out_info_set_current_ostream(c_out_info_info(c_out_info), (unsigned)0);
    c_output_parser(c_out_info, grammar);
    out_info_set_current_ostream(c_out_info_info(c_out_info), (unsigned)1);
    c_output_header(c_out_info, grammar);
}

static void *
main_init_test(OutputInfoT * info, CStringListT * options)
{
    CStringListEntryT * entry;

    UNUSED(info);
    for (entry = cstring_list_head(options); entry;
	 entry = cstring_list_entry_deallocate(entry)) {
	char * option = cstring_list_entry_string(entry);

	E_bad_language_option("test", option);
    }
    return(NULL);
}

static void
main_input_test(void * gclosure, GrammarT * grammar)
{
    UNUSED(gclosure);
    UNUSED(grammar);
}

static void
main_output_test(void * gclosure, GrammarT * grammar)
{
    UNUSED(gclosure);
    UNUSED(grammar);
}

static BoolT main_did_one_off = FALSE;
static BoolT main_did_other   = FALSE;

static OutputInfoT * main_info_closure;

static CStringListT main_language_options;

static OStreamT dump_stream;

static PhaseListT  main_phase_list[] = {
    {"singles", rule_set_inline_singles},
    {"tail", rule_set_inline_tail_calls},
    {"basics", rule_set_inline_all_basics},
    {"other", rule_set_inline_non_tail_calls},
    {"multi", rule_set_multiple_inlining},
    {"all", main_handle_phase_all},
    {NULL, NULL}
};

static LangListT main_language_list[] = {
    {"ansi-c", main_init_ansi_c, main_input_c, 2, main_output_c, 2},
    {"pre-ansi-c", main_init_pre_ansi_c, main_input_c, 2, main_output_c, 2},
    {"iso-c", main_init_ansi_c, main_input_c, 2, main_output_c, 2},
    {"pre-iso-c", main_init_pre_ansi_c, main_input_c, 2, main_output_c, 2},
    {"test", main_init_test, main_input_test, 1, main_output_test, 0},
    {NULL, NULL, NULL, 0, NULL, 0}
};

static LangListT * main_language = &(main_language_list[0]);

static void
main_handle_dump_file(char * option, ArgUsageT * usage, void * gclosure,
		      char * dump_file)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_did_other = TRUE;
    if (ostream_is_open(&dump_stream)) {
	E_multiple_dump_files();
	UNREACHED;
    } else if (!ostream_open(&dump_stream, dump_file)) {
	E_cannot_open_dump_file(dump_file);
	UNREACHED;
    }
}

static void
main_handle_help(char * option, ArgUsageT * usage, void * gclosure)
{
    UNUSED(option);
    UNUSED(gclosure);
    main_did_one_off = TRUE;
    write_arg_usage(ostream_error, usage);
    write_newline(ostream_error);
    ostream_flush(ostream_error);
}

static void
main_handle_factor_limit(char * option, ArgUsageT * usage, void * gclosure,
			 char * limit_str)
{
    unsigned limit;

    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_did_other = TRUE;
    if ((!cstring_to_unsigned(limit_str, &limit)) || (limit == 0)) {
	E_bad_factor_limit(limit_str);
	UNREACHED;
    }
    rule_set_factor_limit(limit);
}

static void
main_handle_inlining(char * option, ArgUsageT * usage, void * gclosure,
		     char * inline_str)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_did_other = TRUE;
    while (*inline_str) {
	BoolT      enable = TRUE;
	DStringT   dstring;
	char *   phase;
	PhaseListT * entry;

	if ((tolower((unsigned char)inline_str[0]) == 'n') &&
	   (tolower((unsigned char)inline_str[1]) == 'o')) {
	    inline_str += 2;
	    enable = FALSE;
	}
	dstring_init(&dstring);
	while ((*inline_str) && (*inline_str != ',')) {
	    dstring_append_char(&dstring, tolower((unsigned char)*inline_str++));
	}
	if (*inline_str == ',') {
	    inline_str++;
	}
	phase = dstring_destroy_to_cstring(&dstring);
	for (entry = main_phase_list; entry->phase; entry++) {
	    if (!strcmp(phase, entry->phase)) {
		if (entry->proc) {
		   (*(entry->proc))(enable);
		}
		goto next;
	    }
	}
	E_bad_inlining_phase(phase);
	UNREACHED;
      next:;
    }
}

static void
main_handle_language(char * option, ArgUsageT * usage, void * gclosure,
		     char * language_str)
{
    LangListT * entry;

    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_did_other = TRUE;
    for (entry = main_language_list; entry->language; entry++) {
	if (!strcmp(language_str, entry->language)) {
	    main_language = entry;
	    return;
	}
    }
    E_bad_language(language_str);
    UNREACHED;
}

static void
main_handle_switch(char * option, ArgUsageT * usage, void * gclosure,
		   char * opt)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_did_other = TRUE;
    cstring_list_append(&main_language_options, opt);
}

static void
main_handle_tab_width(char * option, ArgUsageT * usage, void * gclosure,
		      char * width_str)
{
    unsigned width;

    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_did_other = TRUE;
    if ((!cstring_to_unsigned(width_str, &width)) || (width == 0)) {
	E_bad_tab_width(width_str);
	UNREACHED;
    }
    out_info_set_tab_width(main_info_closure, width);
}

static void
main_handle_version(char * option, ArgUsageT * usage, void * gclosure)
{
    UNUSED(option);
    UNUSED(usage);
    UNUSED(gclosure);
    main_did_one_off = TRUE;
    write_cstring(ostream_error, VERSION);
    write_cstring(ostream_error, " (");
    write_cstring(ostream_error, RELEASE);
    write_cstring(ostream_error, ")");
    write_newline(ostream_error);
    ostream_flush(ostream_error);
}

static EStringDataT main_description_strings[] = {
    { {
	"description of dump-file",
	" FILE\n\tCause intermediate grammars to be written to FILE."
    } }, { {
	"description of help",
	"\n\tDisplay an option summary for the current mode."
    } }, { {
	"description of factor-limit",
	" NUMBER\n\tSet the maximum number of rules to be generated during factorisation."
    } }, { {
	"description of inlining",
	" INLINES\n\tSet which classes of rule are inlined.\n\tShould be any of 'SINGLES', 'BASICS', 'TAIL', 'OTHER', 'MULTI', or 'ALL'."
    } }, { {
	"description of language",
	" LANGUAGE\n\tSet the language for the output parser."
    } }, { {
	"description of switch",
	" OPTION\n\tPass OPTION to language specific option parser."
    } }, { {
	"description of tab-width",
	" NUMBER\n\tSet the number of spaces in a tab character."
    } }, { {
	"description of version",
	"\n\tDisplay the version number on the standard error."
    } }, ERROR_END_STRING_LIST
};

#ifdef __TenDRA__
/* Some conversions to ArgProcP are slightly suspect */
#pragma TenDRA begin
#pragma TenDRA conversion analysis (pointer-pointer) off
#endif

static ArgListT main_arglist[] = {
    {
	"dump-file", 'd',			AT_FOLLOWING,
	(ArgProcP)main_handle_dump_file,	NULL,
	{ "description of dump-file" }
    }, {
        "factor-limit", 'f',			AT_FOLLOWING,
	(ArgProcP)main_handle_factor_limit,	NULL,
	{ "description of factor-limit" }
    }, {
	"help", 'h',				AT_EMPTY,
	(ArgProcP)main_handle_help,		NULL,
	{ "description of help" }
    }, {
	"inline", 'i',				AT_FOLLOWING,
	(ArgProcP)main_handle_inlining,	NULL,
	{ "description of inlining" }
    }, {
	"language", 'l',			AT_FOLLOWING,
	(ArgProcP)main_handle_language,	NULL,
	{ "description of language" }
    }, {
	"switch", 's',				AT_FOLLOWING,
	(ArgProcP)main_handle_switch,		NULL,
	{ "description of switch" }
    }, {
	"tab-width", 't',			AT_FOLLOWING,
	(ArgProcP)main_handle_tab_width,	NULL,
	{ "description of tab-width" }
    }, {
	"version", 'v',				AT_EMPTY,
	(ArgProcP)main_handle_version,		NULL,
	{ "description of version" }
    }, ARG_PARSE_END_LIST
};

#ifdef __TenDRA__
#pragma TenDRA end
#endif

static void
main_init(int argc, char **argv, OutputInfoT * out_info)
{
    EStringT *  usage_estring = error_define_string("sid usage message", USAGE);
    ArgUsageT closure;
    int       skip;
    unsigned  i;
    unsigned  num_infiles;
    unsigned  num_outfiles;

    error_init(argv[0], gen_errors_init_errors);
    error_intern_strings(main_description_strings);
    closure.usage     = error_string_contents(usage_estring);
    closure.arg_list  = main_arglist;
    main_info_closure = out_info;
    arg_parse_intern_descriptions(main_arglist);
    skip = arg_parse_arguments(main_arglist, usage_estring, --argc, ++argv);
    argc -= skip;
    argv += skip;
    if (main_did_one_off && (!main_did_other) && (argc == 0)) {
	exit(EXIT_SUCCESS);
	UNREACHED;
    }
    num_infiles  = main_language->num_input_files;
    num_outfiles = main_language->num_output_files;
    if ((unsigned)argc != (num_infiles + num_outfiles)) {
	E_usage(main_language->language, num_infiles, num_outfiles, &closure);
	UNREACHED;
    }
    out_info_set_num_input_files(out_info, num_infiles);
    out_info_set_num_output_files(out_info, num_outfiles);
    for (i = 0; i < num_infiles; i++) {
	char *  name = argv[i];
	if (!istream_open(out_info_get_istream(out_info, i), name)) {
	    E_cannot_open_input_file(name);
	    UNREACHED;
	}
	out_info_set_infile_name(out_info, i, name);
    }
    for (i = 0; i < num_outfiles; i++) {
	char *  name = argv[num_infiles + i];
	if (!ostream_open(out_info_get_ostream(out_info, i), name)) {
	    E_cannot_open_output_file(name);
	    UNREACHED;
	}
	out_info_set_outfile_name(out_info, i, name);
    }
}

static void
main_dump_grammar(OStreamT * dstream, GrammarT * grammar, char * mesg)
{
    if (dstream) {
	write_cstring(dstream, mesg);
	write_newline(dstream);
	write_newline(dstream);
	write_grammar(dstream, grammar);
    }
}

static void
main_abort_if_errored(void)
{
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}

static void
main_1(OutputInfoT * out_info, OStreamT * dstream)
{
    LexerStreamT lstream;
    GrammarT     grammar;
    void *     output_closure;

    output_closure = (*(main_language->init_proc))(out_info,
						   &main_language_options);
    grammar_init(&grammar);
    lexer_init(&lstream, out_info_get_istream(out_info, (unsigned)0));
    sid_current_stream  = &lstream;
    sid_parse_grammar(&grammar);
    lexer_close(&lstream);
    main_abort_if_errored();
    grammar_check_complete(&grammar);
    main_abort_if_errored();
   (*(main_language->input_proc))(output_closure, &grammar);
    main_abort_if_errored();
    main_dump_grammar(dstream, &grammar, "Original grammar:");
    grammar_remove_left_recursion(&grammar);
    main_dump_grammar(dstream, &grammar, "After left recursion elimination:");
    main_abort_if_errored();
    grammar_compute_first_sets(&grammar);
    main_abort_if_errored();
    grammar_factor(&grammar);
    main_dump_grammar(dstream, &grammar, "After factorisation:");
    main_abort_if_errored();
    grammar_simplify(&grammar);
    main_dump_grammar(dstream, &grammar, "After simplification:");
    grammar_compute_inlining(&grammar);
    grammar_check_collisions(&grammar);
    main_dump_grammar(dstream, &grammar, "After everything:");
    main_abort_if_errored();
    grammar_recompute_alt_names(&grammar);
    if (dstream) {
	ostream_close(dstream);
    }
   (*(main_language->output_proc))(output_closure, &grammar);
}

/*
 * Externally visible functions
 */

int
main(int argc, char **argv)
{
    HANDLE {
	OutputInfoT out_info;

	istream_setup();
	ostream_setup();
	out_info_init(&out_info, argv[0]);
	ostream_init(&dump_stream);
	cstring_list_init(&main_language_options);
	main_init(argc, argv, &out_info);
	if (ostream_is_open(&dump_stream)) {
	    main_1(&out_info, &dump_stream);
	} else {
	    main_1(&out_info, NULL);
	}
    } WITH {
	ExceptionT * exception = EXCEPTION_EXCEPTION();

	if (exception == XX_dalloc_no_memory) {
	    E_no_memory();
	    UNREACHED;
	} else if (exception == XX_istream_read_error) {
	    char * file = (char *)EXCEPTION_VALUE();

	    E_read_error(file);
	    UNREACHED;
	} else if (exception == XX_ostream_write_error) {
	    char * file = (char *)EXCEPTION_VALUE();

	    E_write_error(file);
	    UNREACHED;
	} else {
	    RETHROW();
	    UNREACHED;
	}
    } END_HANDLE
    exit(EXIT_SUCCESS);
    UNREACHED;
}
