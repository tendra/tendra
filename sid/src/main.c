/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
#include <errno.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/cstring.h>
#include <exds/dstring.h>
#include <exds/error.h>
#include <exds/istream.h>
#include <exds/ostream.h>
#include <exds/cstring-list.h>

#include <shared/check.h>
#include <shared/error.h>

#include "adt/rule.h"

#include "arg-parse.h"
#include "grammar.h"
#include "lexer.h"
#include "output.h"
#include "parser.h"
#include "lang.h"
#include "fmt.h"

#include "lang-c/c-main.h"
#include "lang-test/test-main.h"
#include "lang-bnf/bnf-main.h"

#define USAGE "\
usage:[option ...] in-file ... out-file ...\n\
where option is one of:\n"
#define PROGNAME  "sid"
#define LANGUAGES "ansi-c, pre-ansi-c, test, bnf"
#define VERSION   "version 1.11 (" LANGUAGES ")"
#define RELEASE   "tendra.org"

typedef struct PhaseListT {
	char *phase;
	void (*proc)(BoolT);
} PhaseListT;

static void
main_handle_phase_all(BoolT enable)
{
	rule_set_inline_singles(enable);
	rule_set_inline_tail_calls(enable);
	rule_set_inline_all_basics(enable);
	rule_set_inline_non_tail_calls(enable);
	rule_set_multiple_inlining(enable);
}

static BoolT main_did_one_off = FALSE;
static BoolT main_did_other   = FALSE;

static OutputInfoT *main_info_closure;

static CStringListT main_language_options;

static OStreamT dump_stream;

static PhaseListT  main_phase_list[] = {
	{ "singles", rule_set_inline_singles },
	{ "tail", rule_set_inline_tail_calls },
	{ "basics", rule_set_inline_all_basics },
	{ "other", rule_set_inline_non_tail_calls },
	{ "multi", rule_set_multiple_inlining },
	{ "all", main_handle_phase_all },
	{ NULL, NULL }
};

/*
 * Note that the size of this array needs to be kept in sync with the list of
 * languages initialised in main().
 *
 * TODO: permit unused functions (e.g. main_input_test) to be NULL
 */
static LangListT *main_language_list[6];

static LangListT *main_language;

static void
main_handle_dump_file(char *option, ArgUsageT *usage, void *gclosure,
	char *dump_file)
{
	UNUSED(option);
	UNUSED(usage);
	UNUSED(gclosure);

	main_did_other = TRUE;
	if (ostream_is_open(&dump_stream)) {
		error(ERR_FATAL, "more than one dump file specified");
		UNREACHED;
	} else if (!ostream_open(&dump_stream, dump_file)) {
		error(ERR_FATAL, "cannot open dump file '%s': %s", dump_file, strerror(errno));
		UNREACHED;
	}
}

static void
main_handle_help(char *option, ArgUsageT *usage, void *gclosure)
{
	UNUSED(option);
	UNUSED(gclosure);

	main_did_one_off = TRUE;
	write_arg_usage(ostream_error, usage);
	write_newline(ostream_error);
	ostream_flush(ostream_error);
}

static void
main_handle_factor_limit(char *option, ArgUsageT *usage, void *gclosure,
	char *limit_str)
{
	unsigned limit;

	UNUSED(option);
	UNUSED(usage);
	UNUSED(gclosure);
	main_did_other = TRUE;
	if (!cstring_to_unsigned(limit_str, &limit) || limit == 0) {
		error(ERR_FATAL, "bad factor limit '%s'", limit_str);
		UNREACHED;
	}
	rule_set_factor_limit(limit);
}

static void
main_handle_inlining(char *option, ArgUsageT *usage, void *gclosure,
	char *inline_str)
{
	UNUSED(option);
	UNUSED(usage);
	UNUSED(gclosure);
	main_did_other = TRUE;
	while (*inline_str) {
		BoolT       enable = TRUE;
		DStringT    dstring;
		char       *phase;
		PhaseListT *entry;

		if (tolower((unsigned char)inline_str[0]) == 'n' &&
			(tolower((unsigned char)inline_str[1]) == 'o')) {
			inline_str += 2;
			enable = FALSE;
		}
		dstring_init(&dstring);
		while (*inline_str && *inline_str != ',') {
			dstring_append_char(&dstring, tolower((unsigned char) *inline_str++));
		}

		if (*inline_str == ',') {
			inline_str++;
		}

		phase = dstring_destroy_to_cstring(&dstring);
		for (entry = main_phase_list; entry->phase; entry++) {
			if (!strcmp(phase, entry->phase)) {
				if (entry->proc) {
					entry->proc(enable);
				}
				goto next;
			}
		}

		error(ERR_FATAL, "bad inlining phase '%s'", phase);
		UNREACHED;
next:
		;
	}
}

static void
main_handle_language(char *option, ArgUsageT *usage, void *gclosure,
	char *language_str)
{
	size_t i;

	UNUSED(option);
	UNUSED(usage);
	UNUSED(gclosure);
	main_did_other = TRUE;

	for (i = 0; i < sizeof main_language_list / sizeof *main_language_list; i++) {
		if (!strcmp(language_str, main_language_list[i]->language)) {
			main_language = main_language_list[i];
			return;
		}
	}

	error(ERR_FATAL, "unknown language '%s' (should be one of %s)", language_str, LANGUAGES);
	UNREACHED;
}

static void
main_handle_switch(char *option, ArgUsageT *usage, void *gclosure,
	char *opt)
{
	UNUSED(option);
	UNUSED(usage);
	UNUSED(gclosure);

	main_did_other = TRUE;
	cstring_list_append(&main_language_options, opt);
}

static void
main_handle_version(char *option, ArgUsageT *usage, void *gclosure)
{
	UNUSED(option);
	UNUSED(usage);
	UNUSED(gclosure);

	main_did_one_off = TRUE;
	write_cstring(ostream_error, PROGNAME);
	write_cstring(ostream_error, ": ");
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
		" INLINES\n\tSet which classes of rule are inlined.\n"
			"\tShould be any of 'SINGLES', 'BASICS', 'TAIL', 'OTHER', 'MULTI', or 'ALL'."
	} }, { {
		"description of language",
		" LANGUAGE\n\tSet the language for the output parser."
	} }, { {
		"description of switch",
		" OPTION\n\tPass OPTION to language specific option parser."
	} }, { {
		"description of version",
		"\n\tDisplay the version number on the standard error."
	} }, ERROR_END_STRING_LIST
};

#ifdef __TenDRA__
/* XXX Some conversions to ArgProcP are slightly suspect */
#pragma TenDRA begin
#pragma TenDRA conversion analysis (pointer-pointer) off
#endif

static ArgListT main_arglist[] = {
	{
		"dump-file", 'd', AT_FOLLOWING,
		(ArgProcP) main_handle_dump_file, NULL,
		{ "description of dump-file" }
	}, {
		"factor-limit", 'f', AT_FOLLOWING,
		(ArgProcP) main_handle_factor_limit, NULL,
		{ "description of factor-limit" }
	}, {
		"help", 'h', AT_EMPTY,
		(ArgProcP)main_handle_help, NULL,
		{ "description of help" }
	}, {
		"inline", 'i', AT_FOLLOWING,
		(ArgProcP) main_handle_inlining, NULL,
		{ "description of inlining" }
	}, {
		"language", 'l', AT_FOLLOWING,
		(ArgProcP) main_handle_language, NULL,
		{ "description of language" }
	}, {
		"switch", 's', AT_FOLLOWING,
		(ArgProcP) main_handle_switch, NULL,
		{ "description of switch" }
	}, {
		"version", 'v',	AT_EMPTY,
		(ArgProcP) main_handle_version,	 NULL,
		{ "description of version" }
	}, ARG_PARSE_END_LIST
};

#ifdef __TenDRA__
#pragma TenDRA end
#endif

static void
main_init(int argc, char **argv, OutputInfoT *out_info)
{
	EStringT  *usage_estring = error_define_string("sid usage message", USAGE);
	int        skip;
	unsigned   i;
	unsigned   num_infiles;
	unsigned   num_outfiles;

	error_intern_strings(main_description_strings);
	main_info_closure = out_info;
	arg_parse_intern_descriptions(main_arglist);
	skip = arg_parse_arguments(main_arglist, usage_estring, --argc, ++argv);
	argc -= skip;
	argv += skip;
	if (main_did_one_off && !main_did_other && argc == 0) {
		exit(EXIT_SUCCESS);
		UNREACHED;
	}

	num_infiles  = main_language->num_input_files;
	num_outfiles = main_language->num_output_files;
	if ((unsigned) argc != (num_infiles + num_outfiles)) {
		error(ERR_FATAL, "language '%s' requires %u input files and %u output files",
			main_language->language, num_infiles, num_outfiles);
		UNREACHED;
	}

	out_info_set_num_input_files(out_info, num_infiles);
	out_info_set_num_output_files(out_info, num_outfiles);
	for (i = 0; i < num_infiles; i++) {
		char *name = argv[i];

		if (!istream_open(out_info_get_istream(out_info, i), name)) {
			error(ERR_FATAL, "cannot open input file '%s': %s", name, strerror(errno));
			UNREACHED;
		}
		out_info_set_infile_name(out_info, i, name);
	}

	for (i = 0; i < num_outfiles; i++) {
		char *name = argv[num_infiles + i];

		if (!ostream_open(out_info_get_ostream(out_info, i), name)) {
			error(ERR_FATAL, "cannot open output file '%s': %s", name, strerror(errno));
			UNREACHED;
		}
		out_info_set_outfile_name(out_info, i, name);
	}
}

static void
main_dump_grammar(OStreamT *dstream, GrammarT *grammar, char *mesg)
{
	if (dstream == NULL) {
		return;
	}

	write_cstring(dstream, mesg);
	write_newline(dstream);
	write_newline(dstream);
	write_grammar(dstream, grammar);
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
main_1(OutputInfoT *out_info, OStreamT *dstream)
{
	LexerStreamT  lstream;
	GrammarT      grammar;
	void         *output_closure;

	if (main_language->init_proc != NULL) {
		output_closure = main_language->init_proc(out_info,
			&main_language_options);
	} else {
		output_closure = NULL;
	}

	grammar_init(&grammar);
	lexer_init(&lstream, out_info_get_istream(out_info, 0));
	sid_current_stream  = &lstream;
	sid_parse_grammar(&grammar);
	lexer_close(&lstream);
	main_abort_if_errored();
	grammar_check_complete(&grammar);
	main_abort_if_errored();

	if (main_language->input_proc != NULL) {
		main_language->input_proc(output_closure, &grammar);
		main_abort_if_errored();
	}

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

	if (main_language->output_proc != NULL) {
		main_language->output_proc(output_closure, &grammar);
	}
}


/*
 * Externally visible functions
 */

int
main(int argc, char **argv)
{
	main_language_list[0] = &c_language_list_ansi;
	main_language_list[1] = &c_language_list_pre_ansi;
	main_language_list[2] = &c_language_list_iso;
	main_language_list[3] = &c_language_list_pre_iso;
	main_language_list[4] = &test_language_list;
	main_language_list[5] = &bnf_language_list;

	/* Default to ANSI C */
	main_language = main_language_list[0];

	set_progname(PROGNAME, VERSION);
	fmt_init();

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
		ExceptionT *exception = EXCEPTION_EXCEPTION();

		if (exception == XX_dalloc_no_memory) {
			error(ERR_FATAL, "cannot allocate memory");
			UNREACHED;
		} else if (exception == XX_istream_read_error) {
			char *file = (char *) EXCEPTION_VALUE();	/* XXX cast */

			error(ERR_FATAL, "error reading from file '%s': %s", file, strerror(errno));
			UNREACHED;
		} else if (exception == XX_ostream_write_error) {
			char *file = (char *) EXCEPTION_VALUE();

			error(ERR_FATAL, "error writing to file '%s': %s", file, strerror(errno));
			UNREACHED;
		} else {
			RETHROW();
			UNREACHED;
		}
	} END_HANDLE

	exit(EXIT_SUCCESS);
	UNREACHED;
}
