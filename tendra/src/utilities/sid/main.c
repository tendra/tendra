/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
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
 */

/****************************************************************************/

#include "config.h"
#include "release.h"
#include "arg-parse.h"
#include "basic.h"
#include "c-check.h"
#include "c-lexer.h"
#include "c-output.h"
#include "c-parser.h"
#include "catstdn.h"
#include "cstring.h"
#include "cstring-list.h"
#include "dstring.h"
#include "msgcat.h"
#include "grammar.h"
#include "istream.h"
#include "lexer.h"
#include "ostream.h"
#include "output.h"
#include "parser.h"
#include "rule.h"
#include "syntax.h"
#include "tenapp.h"

/*--------------------------------------------------------------------------*/

typedef struct PhaseListT {
	CStringP	phase;
	void		(*proc)(BoolT);
} PhaseListT, *PhaseListP;

typedef struct LangListT {
	CStringP	language;
	GenericP	(*init_proc)(OutputInfoP,  CStringListP);
	void		(*input_proc)(GenericP, GrammarP);
	unsigned	num_input_files;
	void		(*output_proc)(GenericP, GrammarP);
	unsigned	num_output_files;
} LangListT, *LangListP;

/*--------------------------------------------------------------------------*/

static void
main_handle_phase_all(BoolT enable)
{
	rule_set_inline_singles (enable);
	rule_set_inline_tail_calls (enable);
	rule_set_inline_all_basics (enable);
	rule_set_inline_non_tail_calls (enable);
	rule_set_multiple_inlining (enable);
}

/*--------------------------------------------------------------------------*/

static GenericP
main_init_c(OutputInfoP out_info, CStringListP options,
			BoolT ansi, BoolT ossg)
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
		} else if (strncmp (option, "split=", 6) == 0) {
			unsigned limit;
			if (!string_to_unsigned (option + 6, &limit)) {
				MSG_bad_split_size (option + 6);
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
			CStringP lang;
			lang = (ossg ? "ossg-c" : (ansi ? "ansi-c" : "pre-ansi-c"));
			MSG_bad_language_option (lang, option);
		}
	}
	return ((GenericP) c_out_info);
}

static GenericP
main_init_ansi_c(OutputInfoP out_info, CStringListP options)
{
	return (main_init_c (out_info, options, TRUE, FALSE));
}

static GenericP
main_init_pre_ansi_c(OutputInfoP out_info,
					 CStringListP options)
{
	return (main_init_c (out_info, options, FALSE, FALSE));
}

static GenericP
main_init_ossg_c(OutputInfoP out_info, CStringListP options)
{
	return (main_init_c (out_info, options, TRUE, TRUE));
}

static void
main_input_c(GenericP gclosure, GrammarP grammar)
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
	tenapp_checkerrors(MSG_SEV_ERROR);
	c_check_grammar (grammar);
}

static void
main_output_c(GenericP gclosure, GrammarP grammar)
{
	COutputInfoP c_out_info = (COutputInfoP) gclosure;
	
	grammar_compute_mutations (grammar);
	out_info_set_current_ostream (c_out_info_info (c_out_info), (unsigned) 0);
	c_output_parser (c_out_info, grammar);
	out_info_set_current_ostream (c_out_info_info (c_out_info), (unsigned) 1);
	c_output_header (c_out_info, grammar);
}

static GenericP
main_init_test(OutputInfoP info, CStringListP options)
{
	CStringListEntryP entry;
	
	UNUSED (info);
	for (entry = cstring_list_head (options); entry;
		 entry = cstring_list_entry_deallocate (entry)) {
		CStringP option = cstring_list_entry_string (entry);
		
		MSG_bad_language_option ("test", option);
	}
	return (NIL (GenericP));
}

static void
main_input_test(GenericP gclosure, GrammarP grammar)
{
	UNUSED (gclosure);
	UNUSED (grammar);
}

static void
main_output_test(GenericP gclosure, GrammarP grammar)
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
	{NIL (CStringP), NIL (void (*)(BoolT))}
};

static LangListT main_language_list [] = {
	{"ansi-c", main_init_ansi_c, main_input_c, 2, main_output_c, 2},
	{"pre-ansi-c", main_init_pre_ansi_c, main_input_c, 2, main_output_c, 2},
	{"iso-c", main_init_ansi_c, main_input_c, 2, main_output_c, 2},
	{"pre-iso-c", main_init_pre_ansi_c, main_input_c, 2, main_output_c, 2},
	{"ossg-c", main_init_ossg_c, main_input_c, 2, main_output_c, 2},
	{"test", main_init_test, main_input_test, 1, main_output_test, 0},
	{NIL (CStringP), NIL (GenericP (*)(OutputInfoP, CStringListP)),
	 NIL (void (*)(GenericP, GrammarP)), 0,
	 NIL (void (*)(GenericP, GrammarP)), 0}
};

static LangListP main_language = &(main_language_list [0]);

/*--------------------------------------------------------------------------*/

static void
main_handle_dump_file(CStringP option, ArgUsageP usage,
					  GenericP gclosure,
					  CStringP dump_file)
{
	UNUSED (option);
	UNUSED (usage);
	UNUSED (gclosure);
	main_did_other = TRUE;
	if (ostream_is_open (&dump_stream)) {
		MSG_multiple_dump_files ();
		UNREACHED;
	} else if (!ostream_open (&dump_stream, dump_file)) {
		MSG_cannot_open_dump_file (dump_file);
		UNREACHED;
	}
}

static void
main_handle_help(CStringP option, ArgUsageP usage,
				 GenericP gclosure)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_did_one_off = TRUE;
	write_arg_usage (usage);
	write_newline (ostream_error);
	ostream_flush (ostream_error);
}

static void
main_handle_factor_limit(CStringP option,
						 ArgUsageP usage,
						 GenericP gclosure,
						 CStringP limit_str)
{
	unsigned limit;
	
	UNUSED (option);
	UNUSED (usage);
	UNUSED (gclosure);
	main_did_other = TRUE;
	if ((!string_to_unsigned (limit_str, &limit)) || (limit == 0)) {
		MSG_bad_factor_limit (limit_str);
		UNREACHED;
	}
	rule_set_factor_limit (limit);
}

static void
main_handle_inlining(CStringP option, ArgUsageP usage,
					 GenericP gclosure, CStringP inline_str)
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
		MSG_bad_inlining_phase (phase);
		UNREACHED;
	  next:;
	}
}

static void
main_handle_language(CStringP option, ArgUsageP usage,
					 GenericP gclosure, CStringP language_str)
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
	MSG_bad_language (language_str);
	UNREACHED;
}

static void
main_handle_switch (CStringP option, ArgUsageP usage,
				    GenericP gclosure, CStringP opt)
{
	UNUSED (option);
	UNUSED (usage);
	UNUSED (gclosure);
	main_did_other = TRUE;
	cstring_list_append (&main_language_options, opt);
}

static void
main_handle_tab_width(CStringP option, ArgUsageP usage,
					  GenericP gclosure,
					  CStringP width_str)
{
	unsigned width;
	
	UNUSED (option);
	UNUSED (usage);
	UNUSED (gclosure);
	main_did_other = TRUE;
	if ((!string_to_unsigned (width_str, &width)) || (width == 0)) {
		MSG_bad_tab_width (width_str);
		UNREACHED;
	}
	out_info_set_tab_width (main_info_closure, width);
}

static void
main_handle_version(CStringP option, ArgUsageP usage,
					GenericP gclosure)
{
	UNUSED (option);
	UNUSED (usage);
	UNUSED (gclosure);
	main_did_one_off = TRUE;
	tenapp_report_version ();
}

/*--------------------------------------------------------------------------*/


#ifdef __TenDRA__
/* Some conversions to ArgProcP are slightly suspect */
#pragma TenDRA begin
#pragma TenDRA conversion analysis (pointer-pointer) off
#endif

static ArgListT main_arglist [] = {
	{
		"dump-file", 'd',			AT_FOLLOWING,
		(ArgProcP) main_handle_dump_file,	NIL (GenericP),
		MID_description_of_dump_file
	}, {
		"factor-limit", 'f',			AT_FOLLOWING,
		(ArgProcP) main_handle_factor_limit,	NIL (GenericP),
		MID_description_of_factor_limit
	}, {
		"help", '?',				AT_EMPTY,
		(ArgProcP) main_handle_help,		NIL (GenericP),
		MID_description_of_help
	}, {
		"inline", 'i',				AT_FOLLOWING,
		(ArgProcP) main_handle_inlining,	NIL (GenericP),
		MID_description_of_inlining
	}, {
		"language", 'l',			AT_FOLLOWING,
		(ArgProcP) main_handle_language,	NIL (GenericP),
		MID_description_of_language
	}, {
		"switch", 's',				AT_FOLLOWING,
		(ArgProcP) main_handle_switch,		NIL (GenericP),
		MID_description_of_switch
	}, {
		"tab-width", 't',			AT_FOLLOWING,
		(ArgProcP) main_handle_tab_width,	NIL (GenericP),
		MID_description_of_tab_width
	}, {
		"version", 'v',				AT_EMPTY,
		(ArgProcP) main_handle_version,		NIL (GenericP),
		MID_description_of_version
	}, ARG_PARSE_END_LIST
};

#ifdef __TenDRA__
#pragma TenDRA end
#endif

/*--------------------------------------------------------------------------*/

/*
 * Handlers for sid specific message objects
 */
static void
msg_uh_ArgUsageP(char ch, void *pp)
{
	UNUSED(ch);
	write_arg_usage((ArgUsageP)pp);
}

static void
msg_uh_NStringP(char ch, void *pp)
{
	NStringP nstring = (NStringP)pp;

	UNUSED(ch);
	msg_append_nstring(nstring->ns_contents, nstring_length(nstring));
}

static void
msg_uh_KeyP(char ch, void *pp)
{
	UNUSED(ch);
	write_key (msg_stream, (KeyP)pp);
}

static void
msg_uh_BasicClosureP(char ch, void *pp)
{
	UNUSED(ch);
	write_basics (msg_stream, (BasicClosureP)pp);
}

static void
msg_uh_ClashListP(char ch, void *pp)
{
	UNUSED(ch);
	write_clashes (msg_stream, (ClashListP)pp);
}

static void
msg_uh_EntryP(char ch, void *pp)
{
	UNUSED(ch);
	write_key (msg_stream, entry_key ((EntryP)pp));
}

static void
msg_uh_EntryListP(char ch, void *pp)
{
	UNUSED(ch);
	write_entry_list (msg_stream, (EntryListP)pp);
}

static void
msg_uh_RuleP(char ch, void *pp)
{
	UNUSED(ch);
	write_key (msg_stream, entry_key (rule_entry ((RuleP)pp)));
}

static void
msg_uh_RuleProdsP(char ch, void *pp)
{
	RuleP rule = pp;

	UNUSED(ch);

	for (; rule; rule = rule_get_next_in_reverse_dfs (rule)) {
		write_newline (msg_stream);
		write_rule (msg_stream, rule);
	}
}

static void
msg_uh_TypeTupleP(char ch, void *pp)
{
	UNUSED(ch);
	write_type_types (msg_stream, (TypeTupleP)pp);
}

static void
msg_uh_istream_line(char ch, void *pp)
{
	UNUSED(ch);
	UNUSED(pp);
	write_fmt(msg_stream, "%s: %lu: ",
		lexer_stream_name (sid_current_stream),
		(unsigned long) lexer_stream_line(sid_current_stream));
}

static void
msg_uh_c_stream_line(char ch, void *pp)
{
	UNUSED(ch);
	UNUSED(pp);
	write_fmt(msg_stream, "%s: %lu: ",
		c_lexer_stream_name (c_current_stream),
		(unsigned long) c_lexer_stream_line(c_current_stream));
}

static void
main_init(int argc, char **argv, OutputInfoP out_info)
{
	ArgUsageT closure;
	int       skip;
	unsigned  i;
	unsigned  num_infiles;
	unsigned  num_outfiles;
	
	msg_uh_add(MSG_KEY_ArgUsageP, msg_uh_ArgUsageP);
	msg_uh_add(MSG_KEY_NStringP, msg_uh_NStringP);
	msg_uh_add(MSG_KEY_KeyP, msg_uh_KeyP);
	msg_uh_add(MSG_KEY_BasicClosureP, msg_uh_BasicClosureP);
	msg_uh_add(MSG_KEY_ClashListP, msg_uh_ClashListP);
	msg_uh_add(MSG_KEY_EntryP, msg_uh_EntryP);
	msg_uh_add(MSG_KEY_EntryListP, msg_uh_EntryListP);
	msg_uh_add(MSG_KEY_RuleP, msg_uh_RuleP);
	msg_uh_add(MSG_KEY_RuleProdsP, msg_uh_RuleProdsP);
	msg_uh_add(MSG_KEY_TypeTupleP, msg_uh_TypeTupleP);
	msg_uh_add(MSG_KEY_c_stream_line, msg_uh_c_stream_line);
	msg_uh_add(MSG_KEY_istream_line, msg_uh_istream_line);

	closure.usage     = NULL;
	closure.arg_list  = main_arglist;
	main_info_closure = out_info;
	skip = arg_parse_arguments (main_arglist, MID_sid_usage_message,
		 --argc, ++argv);
	argc -= skip;
	argv += skip;
	if (main_did_one_off && (!main_did_other) && (argc == 0)) {
		exit (EXIT_SUCCESS);
		UNREACHED;
	}
	num_infiles  = main_language->num_input_files;
	num_outfiles = main_language->num_output_files;
	if ((unsigned) argc != (num_infiles + num_outfiles)) {
		MSG_usage (main_language->language, num_infiles, num_outfiles, &closure);
		UNREACHED;
	}
	out_info_set_num_input_files (out_info, num_infiles);
	out_info_set_num_output_files (out_info, num_outfiles);
	for (i = 0; i < num_infiles; i ++) {
		CStringP  name = argv [i];
		if (!istream_open (out_info_get_istream (out_info, i), name)) {
			MSG_cant_open_input_file (name);
			UNREACHED;
		}
		out_info_set_infile_name (out_info, i, name);
	}
	for (i = 0; i < num_outfiles; i ++) {
		CStringP  name = argv [num_infiles + i];
		if (!ostream_open (out_info_get_ostream (out_info, i), name)) {
			MSG_cant_open_output_file (name);
			UNREACHED;
		}
		out_info_set_outfile_name (out_info, i, name);
	}
}

static void
main_dump_grammar(OStreamP dstream, GrammarP grammar,
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
main_abort_if_errored(void)
{
	tenapp_checkerrors(MSG_SEV_ERROR);
}

static void
main_1(OutputInfoP out_info, OStreamP dstream)
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
main(int argc, char **argv)
{
	OutputInfoT out_info;

	tenapp_init(argc, argv, "Parser generator", "1.10 (ansi-c, pre-ansi-c, ossg-c, test)");
	istream_setup ();
	out_info_init (&out_info, argv [0]);
	ostream_init (&dump_stream);
	cstring_list_init (&main_language_options);
	main_init (argc, argv, &out_info);
	if (ostream_is_open (&dump_stream)) {
		main_1 (&out_info, &dump_stream);
	} else {
		main_1 (&out_info, NIL (OStreamP));
	}
	tenapp_exit2 (EXIT_SUCCESS);
	UNREACHED;
}
