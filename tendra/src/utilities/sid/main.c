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


/*** main.c --- SID program main routine.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
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
 *
 *** Change Log:
 * $Log: main.c,v $
 * Revision 1.2  1998/02/06  17:05:44  release
 * Last minute pre-release polishing.
 *
 * Revision 1.1.1.1  1998/01/17  15:57:41  release
 * First version to be checked into rolling release.
 *
 * Revision 1.13  1996/07/01  13:29:41  smf
 * main.c:
 * 	- updated version number.
 *
 * Revision 1.12  1996/07/01  09:36:04  smf
 * main.c:
 * 	- updated version numer.
 *
 * Revision 1.11  1996/06/28  15:12:34  smf
 * main.c:
 * 	- added extra information to version string;
 * 	- added "build" mechanism for release system.
 *
 * Revision 1.10  1996/03/01  09:51:56  smf
 * main.c:
 * 	- updated version number.
 *
 * Revision 1.9  1996/02/29  09:53:26  smf
 * main.c:
 * 	- updated version number.
 *
 * Revision 1.8  1996/02/28  15:43:56  smf
 * Updated version number in main.c.
 * Modified build_sid to use new platform designation.
 *
 * Revision 1.7  1995/02/10  16:28:56  smf
 * Fixed bugs "CR95_111.sid-inline-no-var-check" and "CR95_112.sid-lre-var-call".
 * Updated version number.
 *
 * Revision 1.6  1994/12/23  09:44:18  smf
 * Fixing "CR94_227.sid-exception-optimisation-bug" - updated version number.
 *
 * Revision 1.5  1994/12/15  09:55:01  smf
 * Updated version to "1.9#4".
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.4  1994/11/11  11:35:40  smf
 * Updated version number for bug fix CR94_127.sid-tail-rec.
 *
 * Revision 1.3  1994/08/22  09:34:15  smf
 * Fixed bug DR114:ids-too-long.
 *
 * Revision 1.2  1994/08/18  13:42:35  smf
 * Fixed bug "DR115:SID-shadow-error".  Also modified "build_sid" to make
 * parallel bug fixing simpler.
 *
 * Revision 1.1.1.1  1994/07/25  16:04:11  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "os-interface.h"
#include "release.h"
#include "arg-parse.h"
#include "c-check.h"
#include "c-lexer.h"
#include "c-output.h"
#include "c-parser.h"
#include "cstring.h"
#include "cstring-list.h"
#include "dstring.h"
#include "error.h"
#include "error-file.h"
#include "exception.h"
#include "gen-errors.h"
#include "grammar.h"
#include "istream.h"
#include "lexer.h"
#include "ostream.h"
#include "output.h"
#include "parser.h"
#include "rule.h"
#include "syntax.h"

/*--------------------------------------------------------------------------*/

#define USAGE "\
\tusage: [option ...] in-file ... out-file ...\n\
\twhere option is one of:"
#ifndef VERSION
#define VERSION "sid: version 1.9#13 (ansi-c, pre-ansi-c, ossg-c, test)"
#endif /* !defined (VERSION) */
#ifndef RELEASE
#define RELEASE "unknown"
#endif /* !defined (RELEASE) */
#ifndef BANNER
#define BANNER ""
#endif /* !defined (BANNER) */

/*--------------------------------------------------------------------------*/

typedef struct PhaseListT {
    CStringP			phase;
    void		      (*proc) PROTO_S ((BoolT));
} PhaseListT, *PhaseListP;

typedef struct LangListT {
    CStringP			language;
    GenericP		      (*init_proc) PROTO_S ((OutputInfoP,
						     CStringListP));
    void		      (*input_proc) PROTO_S ((GenericP, GrammarP));
    unsigned			num_input_files;
    void		      (*output_proc) PROTO_S ((GenericP, GrammarP));
    unsigned			num_output_files;
} LangListT, *LangListP;

/*--------------------------------------------------------------------------*/

static void
main_handle_phase_all PROTO_N ((enable))
		      PROTO_T (BoolT enable)
{
    rule_set_inline_singles (enable);
    rule_set_inline_tail_calls (enable);
    rule_set_inline_all_basics (enable);
    rule_set_inline_non_tail_calls (enable);
    rule_set_multiple_inlining (enable);
}

/*--------------------------------------------------------------------------*/

static GenericP
main_init_c PROTO_N ((out_info, options, ansi, ossg))
	    PROTO_T (OutputInfoP  out_info X
		     CStringListP options X
		     BoolT        ansi X
		     BoolT        ossg )
{
    COutputInfoP      c_out_info = ALLOCATE (COutputInfoT);
    CStringListEntryP entry;

    c_out_info_init (c_out_info, out_info);
    if (ansi) {
	c_out_info_set_prototypes (c_out_info, TRUE);
    }
    if (ossg) {
	c_out_info_set_ossg (c_out_info, TRUE);
    }
    for (entry = cstring_list_head (options); entry;
	 entry = cstring_list_entry_deallocate (entry)) {
	CStringP option = cstring_list_entry_string (entry);

	if (cstring_equal (option, "prototypes") ||
	    cstring_equal (option, "proto")) {
	    c_out_info_set_prototypes (c_out_info, TRUE);
	    c_out_info_set_ossg (c_out_info, FALSE);
	} else if (cstring_equal (option, "no-prototypes") ||
		   cstring_equal (option, "no-proto")) {
	    c_out_info_set_prototypes (c_out_info, FALSE);
	    c_out_info_set_ossg (c_out_info, FALSE);
	} else if (cstring_equal (option, "ossg-prototypes") ||
		   cstring_equal (option, "ossg-proto")) {
	    c_out_info_set_prototypes (c_out_info, TRUE);
	    c_out_info_set_ossg (c_out_info, TRUE);
	} else if (cstring_equal (option, "split")) {
	    c_out_info_set_split (c_out_info, (unsigned) 5000);
	} else if (cstring_starts (option, "split=")) {
	    unsigned limit;
	    if (!cstring_to_unsigned (option + 6, &limit)) {
		E_bad_split_size (option + 6);
		UNREACHED;
	    }
	    c_out_info_set_split (c_out_info, limit);
	} else if (cstring_equal (option, "no-split")) {
	    c_out_info_set_split (c_out_info, (unsigned) 0);
	} else if (cstring_equal (option, "numeric-ids") ||
		   cstring_equal (option, "numeric")) {
	    c_out_info_set_numeric_ids (c_out_info, TRUE);
	} else if (cstring_equal (option, "no-numeric-ids") ||
		   cstring_equal (option, "no-numeric")) {
	    c_out_info_set_numeric_ids (c_out_info, FALSE);
	} else if (cstring_equal (option, "casts") ||
		   cstring_equal (option, "cast")) {
	    c_out_info_set_casts (c_out_info, TRUE);
	} else if (cstring_equal (option, "no-casts") ||
		   cstring_equal (option, "no-cast")) {
	    c_out_info_set_casts (c_out_info, FALSE);
	} else if (cstring_equal (option, "unreachable-macros") ||
		   cstring_equal (option, "unreachable-macro")) {
	    c_out_info_set_unreachable (c_out_info, TRUE);
	} else if (cstring_equal (option, "unreachable-comments") ||
		   cstring_equal (option, "unreachable-comment")) {
	    c_out_info_set_unreachable (c_out_info, FALSE);
	} else if (cstring_equal (option, "lines") ||
		   cstring_equal (option, "line")) {
	    c_out_info_set_lines (c_out_info, TRUE);
	} else if (cstring_equal (option, "no-lines") ||
		   cstring_equal (option, "no-line")) {
	    c_out_info_set_lines (c_out_info, FALSE);
	} else {
	    CStringP lang ;
	    lang = (ossg ? "ossg-c" : (ansi ? "ansi-c" : "pre-ansi-c"));
	    E_bad_language_option (lang, option);
	}
    }
    return ((GenericP) c_out_info);
}

static GenericP
main_init_ansi_c PROTO_N ((out_info, options))
		 PROTO_T (OutputInfoP  out_info X
			  CStringListP options)
{
    return (main_init_c (out_info, options, TRUE, FALSE));
}

static GenericP
main_init_pre_ansi_c PROTO_N ((out_info, options))
		     PROTO_T (OutputInfoP  out_info X
			      CStringListP options)
{
    return (main_init_c (out_info, options, FALSE, FALSE));
}

static GenericP
main_init_ossg_c PROTO_N ((out_info, options))
		 PROTO_T (OutputInfoP  out_info X
			  CStringListP options)
{
    return (main_init_c (out_info, options, TRUE, TRUE));
}

static void
main_input_c PROTO_N ((gclosure, grammar))
	     PROTO_T (GenericP gclosure X
		      GrammarP grammar)
{
    COutputInfoP  c_out_info = (COutputInfoP) gclosure;
    OutputInfoP   out_info   = c_out_info_info (c_out_info);
    CLexerStreamT clstream;

    c_lexer_init (&clstream, out_info_get_istream (out_info, (unsigned) 1));
    c_current_stream   = &clstream;
    c_current_out_info = c_out_info;
    c_current_table    = grammar_table (grammar);
    c_parse_grammar ();
    c_lexer_close (&clstream);
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
	exit (EXIT_FAILURE);
	UNREACHED;
    }
    c_check_grammar (grammar);
}

static void
main_output_c PROTO_N ((gclosure, grammar))
	      PROTO_T (GenericP gclosure X
		       GrammarP grammar)
{
    COutputInfoP c_out_info = (COutputInfoP) gclosure;

    grammar_compute_mutations (grammar);
    out_info_set_current_ostream (c_out_info_info (c_out_info), (unsigned) 0);
    c_output_parser (c_out_info, grammar);
    out_info_set_current_ostream (c_out_info_info (c_out_info), (unsigned) 1);
    c_output_header (c_out_info, grammar);
}

static GenericP
main_init_test PROTO_N ((info, options))
	       PROTO_T (OutputInfoP  info X
			CStringListP options)
{
    CStringListEntryP entry;

    UNUSED (info);
    for (entry = cstring_list_head (options); entry;
	 entry = cstring_list_entry_deallocate (entry)) {
	CStringP option = cstring_list_entry_string (entry);

	E_bad_language_option ("test", option);
    }
    return (NIL (GenericP));
}

static void
main_input_test PROTO_N ((gclosure, grammar))
		PROTO_T (GenericP gclosure X
			 GrammarP grammar)
{
    UNUSED (gclosure);
    UNUSED (grammar);
}

static void
main_output_test PROTO_N ((gclosure, grammar))
		 PROTO_T (GenericP gclosure X
			  GrammarP grammar)
{
    UNUSED (gclosure);
    UNUSED (grammar);
}

/*--------------------------------------------------------------------------*/

static BoolT main_did_one_off = FALSE;
static BoolT main_did_other   = FALSE;

static OutputInfoP main_info_closure;

static CStringListT main_language_options;

static OStreamT dump_stream;

static PhaseListT  main_phase_list [] = {
    {"singles", rule_set_inline_singles},
    {"tail", rule_set_inline_tail_calls},
    {"basics", rule_set_inline_all_basics},
    {"other", rule_set_inline_non_tail_calls},
    {"multi", rule_set_multiple_inlining},
    {"all", main_handle_phase_all},
    {NIL (CStringP), NIL (void (*) PROTO_S ((BoolT)))}
};

static LangListT main_language_list [] = {
    {"ansi-c", main_init_ansi_c, main_input_c, 2, main_output_c, 2},
    {"pre-ansi-c", main_init_pre_ansi_c, main_input_c, 2, main_output_c, 2},
    {"iso-c", main_init_ansi_c, main_input_c, 2, main_output_c, 2},
    {"pre-iso-c", main_init_pre_ansi_c, main_input_c, 2, main_output_c, 2},
    {"ossg-c", main_init_ossg_c, main_input_c, 2, main_output_c, 2},
    {"test", main_init_test, main_input_test, 1, main_output_test, 0},
    {NIL (CStringP), NIL (GenericP (*) PROTO_S ((OutputInfoP, CStringListP))),
     NIL (void (*) PROTO_S ((GenericP, GrammarP))), 0,
     NIL (void (*) PROTO_S ((GenericP, GrammarP))), 0}
};

static LangListP main_language = &(main_language_list [0]);

/*--------------------------------------------------------------------------*/

static void
main_handle_dump_file PROTO_N ((option, usage, gclosure, dump_file))
		      PROTO_T (CStringP  option X
			       ArgUsageP usage X
			       GenericP  gclosure X
			       CStringP  dump_file)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_did_other = TRUE;
    if (ostream_is_open (&dump_stream)) {
	E_multiple_dump_files ();
	UNREACHED;
    } else if (!ostream_open (&dump_stream, dump_file)) {
	E_cannot_open_dump_file (dump_file);
	UNREACHED;
    }
}

static void
main_handle_help PROTO_N ((option, usage, gclosure))
		 PROTO_T (CStringP  option X
			  ArgUsageP usage X
			  GenericP  gclosure)
{
    UNUSED (option);
    UNUSED (gclosure);
    main_did_one_off = TRUE;
    write_arg_usage (ostream_error, usage);
    write_newline (ostream_error);
    ostream_flush (ostream_error);
}

static void
main_handle_factor_limit PROTO_N ((option, usage, gclosure, limit_str))
			 PROTO_T (CStringP  option X
				  ArgUsageP usage X
				  GenericP  gclosure X
				  CStringP  limit_str)
{
    unsigned limit;

    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_did_other = TRUE;
    if ((!cstring_to_unsigned (limit_str, &limit)) || (limit == 0)) {
	E_bad_factor_limit (limit_str);
	UNREACHED;
    }
    rule_set_factor_limit (limit);
}

static void
main_handle_inlining PROTO_N ((option, usage, gclosure, inline_str))
		     PROTO_T (CStringP  option X
			      ArgUsageP usage X
			      GenericP  gclosure X
			      CStringP  inline_str)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_did_other = TRUE;
    while (*inline_str) {
	BoolT      enable = TRUE;
	DStringT   dstring;
	CStringP   phase;
	PhaseListP entry;

	if ((syntax_downcase (inline_str [0]) == 'n') &&
	    (syntax_downcase (inline_str [1]) == 'o')) {
	    inline_str += 2;
	    enable = FALSE;
	}
	dstring_init (&dstring);
	while ((*inline_str) && (*inline_str != ',')) {
	    dstring_append_char (&dstring, syntax_downcase (*inline_str ++));
	}
	if (*inline_str == ',') {
	    inline_str ++;
	}
	phase = dstring_destroy_to_cstring (&dstring);
	for (entry = main_phase_list; entry->phase; entry ++) {
	    if (cstring_equal (phase, entry->phase)) {
		if (entry->proc) {
		    (*(entry->proc)) (enable);
		}
		goto next;
	    }
	}
	E_bad_inlining_phase (phase);
	UNREACHED;
      next:;
    }
}

static void
main_handle_language PROTO_N ((option, usage, gclosure, language_str))
		     PROTO_T (CStringP  option X
			      ArgUsageP usage X
			      GenericP  gclosure X
			      CStringP  language_str)
{
    LangListP entry;

    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_did_other = TRUE;
    for (entry = main_language_list; entry->language; entry ++) {
	if (cstring_equal (language_str, entry->language)) {
	    main_language = entry;
	    return;
	}
    }
    E_bad_language (language_str);
    UNREACHED;
}

static void
main_handle_show_errors PROTO_N ((option, usage, gclosure))
			PROTO_T (CStringP  option X
				 ArgUsageP usage X
				 GenericP  gclosure)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_did_one_off = TRUE;
    write_error_file (ostream_output);
    ostream_flush (ostream_output);
}

static void
main_handle_switch PROTO_N ((option, usage, gclosure, opt))
		   PROTO_T (CStringP  option X
			    ArgUsageP usage X
			    GenericP  gclosure X
			    CStringP  opt)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_did_other = TRUE;
    cstring_list_append (&main_language_options, opt);
}

static void
main_handle_tab_width PROTO_N ((option, usage, gclosure, width_str))
		      PROTO_T (CStringP  option X
			       ArgUsageP usage X
			       GenericP  gclosure X
			       CStringP  width_str)
{
    unsigned width;

    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_did_other = TRUE;
    if ((!cstring_to_unsigned (width_str, &width)) || (width == 0)) {
	E_bad_tab_width (width_str);
	UNREACHED;
    }
    out_info_set_tab_width (main_info_closure, width);
}

static void
main_handle_version PROTO_N ((option, usage, gclosure))
		    PROTO_T (CStringP  option X
			     ArgUsageP usage X
			     GenericP  gclosure)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_did_one_off = TRUE;
    write_cstring (ostream_error, VERSION);
    write_cstring (ostream_error, " (Release ");
    write_cstring (ostream_error, RELEASE);
    write_cstring (ostream_error, ")");
    write_cstring (ostream_error, BANNER);
    write_newline (ostream_error);
    ostream_flush (ostream_error);
}

/*--------------------------------------------------------------------------*/

static EStringDataT main_description_strings [] = {
    UB {
	"description of dump-file",
	" FILE\n\tCause intermediate grammars to be written to FILE."
    } UE, UB {
	"description of help",
	"\n\tDisplay an option summary for the current mode."
    } UE, UB {
	"description of factor-limit",
	" NUMBER\n\tSet the maximum number of rules to be generated during factorisation."
    } UE, UB {
	"description of inlining",
	" INLINES\n\tSet which classes of rule are inlined.\n\tShould be any of 'SINGLES', 'BASICS', 'TAIL', 'OTHER', 'MULTI', or 'ALL'."
    } UE, UB {
	"description of language",
	" LANGUAGE\n\tSet the language for the output parser."
    } UE, UB {
	"description of show-errors",
	"\n\tDisplay the current error table on the standard output."
    } UE, UB {
	"description of switch",
	" OPTION\n\tPass OPTION to language specific option parser."
    } UE, UB {
	"description of tab-width",
	" NUMBER\n\tSet the number of spaces in a tab character."
    } UE, UB {
	"description of version",
	"\n\tDisplay the version number on the standard error."
    } UE, ERROR_END_STRING_LIST
};

#ifdef __TenDRA__
/* Some conversions to ArgProcP are slightly suspect */
#pragma TenDRA begin
#pragma TenDRA conversion analysis (pointer-pointer) off
#endif

static ArgListT main_arglist [] = {
    {
	"dump-file", 'd',			AT_FOLLOWING,
	(ArgProcP) main_handle_dump_file,	NIL (GenericP),
	UB "description of dump-file" UE
    }, {
        "factor-limit", 'f',			AT_FOLLOWING,
	(ArgProcP) main_handle_factor_limit,	NIL (GenericP),
	UB "description of factor-limit" UE
    }, {
	"help", '?',				AT_EMPTY,
	(ArgProcP) main_handle_help,		NIL (GenericP),
	UB "description of help" UE
    }, {
	"inline", 'i',				AT_FOLLOWING,
	(ArgProcP) main_handle_inlining,	NIL (GenericP),
	UB "description of inlining" UE
    }, {
	"language", 'l',			AT_FOLLOWING,
	(ArgProcP) main_handle_language,	NIL (GenericP),
	UB "description of language" UE
    }, {
	"show-errors", 'e',			AT_EMPTY,
	(ArgProcP) main_handle_show_errors,	NIL (GenericP),
	UB "description of show-errors" UE
    }, {
	"switch", 's',				AT_FOLLOWING,
	(ArgProcP) main_handle_switch,		NIL (GenericP),
	UB "description of switch" UE
    }, {
	"tab-width", 't',			AT_FOLLOWING,
	(ArgProcP) main_handle_tab_width,	NIL (GenericP),
	UB "description of tab-width" UE
    }, {
	"version", 'v',				AT_EMPTY,
	(ArgProcP) main_handle_version,		NIL (GenericP),
	UB "description of version" UE
    }, ARG_PARSE_END_LIST
};

#ifdef __TenDRA__
#pragma TenDRA end
#endif

/*--------------------------------------------------------------------------*/

static void
main_init PROTO_N ((argc, argv, out_info))
	  PROTO_T (int         argc X
		   char      **argv X
		   OutputInfoP out_info)
{
    EStringP  usage_estring = error_define_string ("sid usage message", USAGE);
    ArgUsageT closure;
    CStringP  error_file;
    int       skip;
    unsigned  i;
    unsigned  num_infiles;
    unsigned  num_outfiles;

    error_init (argv [0], gen_errors_init_errors);
    error_intern_strings (main_description_strings);
    if ((error_file = getenv ("SID_ERROR_FILE")) != NIL (CStringP)) {
	error_file_parse (error_file, FALSE);
    }
    closure.usage     = error_string_contents (usage_estring);
    closure.arg_list  = main_arglist;
    main_info_closure = out_info;
    arg_parse_intern_descriptions (main_arglist);
    skip = arg_parse_arguments (main_arglist, usage_estring, -- argc, ++ argv);
    argc -= skip;
    argv += skip;
    if (main_did_one_off && (!main_did_other) && (argc == 0)) {
	exit (EXIT_SUCCESS);
	UNREACHED;
    }
    num_infiles  = main_language->num_input_files;
    num_outfiles = main_language->num_output_files;
    if ((unsigned) argc != (num_infiles + num_outfiles)) {
	E_usage (main_language->language, num_infiles, num_outfiles, &closure);
	UNREACHED;
    }
    out_info_set_num_input_files (out_info, num_infiles);
    out_info_set_num_output_files (out_info, num_outfiles);
    for (i = 0; i < num_infiles; i ++) {
	CStringP  name = argv [i];
	if (!istream_open (out_info_get_istream (out_info, i), name)) {
	    E_cannot_open_input_file (name);
	    UNREACHED;
	}
	out_info_set_infile_name (out_info, i, name);
    }
    for (i = 0; i < num_outfiles; i ++) {
	CStringP  name = argv [num_infiles + i];
	if (!ostream_open (out_info_get_ostream (out_info, i), name)) {
	    E_cannot_open_output_file (name);
	    UNREACHED;
	}
	out_info_set_outfile_name (out_info, i, name);
    }
}

static void
main_dump_grammar PROTO_N ((dstream, grammar, mesg))
		  PROTO_T (OStreamP dstream X
			   GrammarP grammar X
			   CStringP mesg)
{
    if (dstream) {
	write_cstring (dstream, mesg);
	write_newline (dstream);
	write_newline (dstream);
	write_grammar (dstream, grammar);
    }
}

static void
main_abort_if_errored PROTO_Z ()
{
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
	exit (EXIT_FAILURE);
	UNREACHED;
    }
}

static void
main_1 PROTO_N ((out_info, dstream))
       PROTO_T (OutputInfoP out_info X
		OStreamP    dstream)
{
    LexerStreamT lstream;
    GrammarT     grammar;
    GenericP     output_closure;

    output_closure = (*(main_language->init_proc)) (out_info,
						    &main_language_options);
    grammar_init (&grammar);
    lexer_init (&lstream, out_info_get_istream (out_info, (unsigned) 0));
    sid_current_stream  = &lstream;
    sid_current_grammar = &grammar;
    sid_parse_grammar ();
    lexer_close (&lstream);
    main_abort_if_errored ();
    grammar_check_complete (&grammar);
    main_abort_if_errored ();
    (*(main_language->input_proc)) (output_closure, &grammar);
    main_abort_if_errored ();
    main_dump_grammar (dstream, &grammar, "Original grammar:");
    grammar_remove_left_recursion (&grammar);
    main_dump_grammar (dstream, &grammar, "After left recursion elimination:");
    main_abort_if_errored ();
    grammar_compute_first_sets (&grammar);
    main_abort_if_errored ();
    grammar_factor (&grammar);
    main_dump_grammar (dstream, &grammar, "After factorisation:");
    main_abort_if_errored ();
    grammar_simplify (&grammar);
    main_dump_grammar (dstream, &grammar, "After simplification:");
    grammar_compute_inlining (&grammar);
    grammar_check_collisions (&grammar);
    main_dump_grammar (dstream, &grammar, "After everything:");
    main_abort_if_errored ();
    grammar_recompute_alt_names (&grammar);
    if (dstream) {
	ostream_close (dstream);
    }
    (*(main_language->output_proc)) (output_closure, &grammar);
}

/*--------------------------------------------------------------------------*/

int
main PROTO_N ((argc, argv))
     PROTO_T (int    argc X
	      char **argv)
{
    HANDLE {
	OutputInfoT out_info;

	istream_setup ();
	ostream_setup ();
	out_info_init (&out_info, argv [0]);
	ostream_init (&dump_stream);
	cstring_list_init (&main_language_options);
	main_init (argc, argv, &out_info);
	if (ostream_is_open (&dump_stream)) {
	    main_1 (&out_info, &dump_stream);
	} else {
	    main_1 (&out_info, NIL (OStreamP));
	}
    } WITH {
	ExceptionP exception = EXCEPTION_EXCEPTION ();

	if (exception == XX_dalloc_no_memory) {
	    E_no_memory ();
	    UNREACHED;
	} else if (exception == XX_istream_read_error) {
	    CStringP file = (CStringP) EXCEPTION_VALUE ();

	    E_read_error (file);
	    UNREACHED;
	} else if (exception == XX_ostream_write_error) {
	    CStringP file = (CStringP) EXCEPTION_VALUE ();

	    E_write_error (file);
	    UNREACHED;
	} else {
	    RETHROW ();
	    UNREACHED;
	}
    } END_HANDLE
    exit (EXIT_SUCCESS);
    UNREACHED;
}

/*
 * Local variables(smf):
 * compile-command: "build_sid"
 * eval: (include::add-path-entry "os-interface" "library" "transforms")
 * eval: (include::add-path-entry "parser" "output" "c-output" "c-input")
 * eval: (include::add-path-entry "generated")
 * End:
**/
