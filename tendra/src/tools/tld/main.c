/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


/*** main.c --- tld program main routine.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file contains the main routine for the TDF linker.  It performs
 * argument parsing, and then calls one of "builder_main", "contents_main",
 * "extract_main" or "linker_main" to do the actual work.  See the files in
 * the "frontends" directory for more details.
 *
 *** Change Log:*/

/****************************************************************************/

#include "config.h"
#include "release.h"
#include "arg-data.h"
#include "arg-parse.h"
#include "builder.h"
#include "contents.h"
#include "debug.h"
#include "exception.h"
#include "extract.h"
#include "istream.h"
#include "msgcat.h"
#include "catstdn.h"
#include "linker.h"
#include "rename-file.h"
#include "tenapp.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

typedef enum {
    MODE_BUILDER,
    MODE_CONTENTS,
    MODE_EXTRACT,
    MODE_LINKER
} ModeT, *ModeP;

/*--------------------------------------------------------------------------*/

static BoolT    main_used_one_off = FALSE;
static BoolT    main_used_other   = FALSE;
static ArgDataT main_arg_data;

/*--------------------------------------------------------------------------*/

static void
main_handle_all(CStringP option, ArgUsageP usage,
				GenericP gclosure, BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_extract_all (&main_arg_data, enable);
}

static void
main_handle_all_hide_defd(CStringP option,
						  ArgUsageP usage,
						  GenericP gclosure,
						  BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_all_hide_defd (&main_arg_data, enable);
}

static void
main_handle_basename(CStringP option, ArgUsageP usage,
					 GenericP gclosure, BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_extract_basename (&main_arg_data, enable);
}

static void
main_handle_debug_file(CStringP option, ArgUsageP usage,
					   GenericP gclosure,
					   CStringP debug_file)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_debug_file (&main_arg_data, debug_file);
}

static void
main_handle_help(CStringP option, ArgUsageP usage,
				 GenericP gclosure)
{
    UNUSED (option);
    UNUSED (gclosure);
    main_used_one_off = TRUE;
    MSG_arg_usage(usage);
}

static void
main_handle_hide(CStringP option, ArgUsageP usage,
				 GenericP gclosure, CStringP shape,
				 CStringP name)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_hide (&main_arg_data, shape, name);
}

static void
main_handle_hide_defined(CStringP option,
						 ArgUsageP usage,
						 GenericP gclosure,
						 CStringP shape)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_hide_defined (&main_arg_data, shape);
}

static void
main_handle_index(CStringP option, ArgUsageP usage,
				  GenericP gclosure, BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_content_index (&main_arg_data, enable);
}

static void
main_handle_info(CStringP option, ArgUsageP usage,
				 GenericP gclosure, BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    msg_sev_set(MSG_SEV_INFO, enable);
}

static void
main_handle_keep(CStringP option, ArgUsageP usage,
				 GenericP gclosure, CStringP shape,
				 CStringP name)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_keep (&main_arg_data, shape, name);
}

static void
main_handle_keep_all(CStringP option, ArgUsageP usage,
					 GenericP gclosure, CStringP shape)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_keep_all (&main_arg_data, shape);
}

static void
main_handle_library_file(CStringP option,
						 ArgUsageP usage,
						 GenericP gclosure,
						 CStringP library_file)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_library_file (&main_arg_data, library_file);
}

static void
main_handle_match_base(CStringP option, ArgUsageP usage,
					   GenericP gclosure,
					   BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_extract_match_base (&main_arg_data, enable);
}

static void
main_handle_output_file(CStringP option, ArgUsageP usage,
						GenericP gclosure,
						CStringP output_file)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_output_file (&main_arg_data, output_file);
}

static void
main_handle_library_path(CStringP option,
						 ArgUsageP usage,
						 GenericP gclosure,
						 CStringP directory)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_library_path (&main_arg_data, directory);
}

static void
main_handle_rename(CStringP option, ArgUsageP usage,
				   GenericP gclosure, CStringP shape,
				   CStringP from, CStringP to)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_parse_rename (&main_arg_data, shape, from, to);
}

static void
main_handle_rename_file(CStringP option, ArgUsageP usage,
						GenericP gclosure,
						CStringP name)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    rename_file_parse (name, &main_arg_data);
}

static void
main_handle_show_errors(CStringP option, ArgUsageP usage,
						GenericP gclosure)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_one_off = TRUE;
/*    write_error_file (ostream_output); */ /* delete this fn */
    ostream_flush (ostream_output);
}

static void
main_handle_size(CStringP option, ArgUsageP usage,
				 GenericP gclosure, BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_content_size (&main_arg_data, enable);
}

static void
main_handle_suppress(CStringP option, ArgUsageP usage,
					 GenericP gclosure, CStringP shape,
					 CStringP name)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_suppress (&main_arg_data, shape, name);
}

static void
main_handle_suppress_all(CStringP option,
						 ArgUsageP usage,
						 GenericP gclosure,
						 CStringP shape)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_add_suppress_all (&main_arg_data, shape);
}

static void
main_handle_suppress_mult(CStringP option,
						  ArgUsageP usage,
						  GenericP gclosure,
						  BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_suppress_mult (&main_arg_data, enable);
}

static void
main_handle_tdf_version(CStringP option, ArgUsageP usage,
						GenericP gclosure,
						BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_content_version (&main_arg_data, enable);
}

static void
main_handle_unit_file(CStringP option, ArgUsageP usage,
					  GenericP gclosure,
					  CStringP unit_file)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    arg_data_set_unit_file (&main_arg_data, unit_file);
}

static void
main_handle_version(CStringP option, ArgUsageP usage,
					GenericP gclosure)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_one_off = TRUE;
	tenapp_report_version();
}

static void
main_handle_warning(CStringP option, ArgUsageP usage,
					GenericP gclosure, BoolT enable)
{
    UNUSED (option);
    UNUSED (usage);
    UNUSED (gclosure);
    main_used_other = TRUE;
    msg_sev_set(MSG_SEV_WARNING, enable);
}

/*--------------------------------------------------------------------------*/

#ifdef __TenDRA__
/* Some conversions to ArgProcP are slightly suspect */
#pragma TenDRA begin
#pragma TenDRA conversion analysis (pointer-pointer) off
#endif

static ArgListT main_builder_arg_list [] = {
    {
		"debug-file", 'd',			AT_FOLLOWING,
		(ArgProcP) main_handle_debug_file,	NIL (GenericP),
		MID_description_of_debug_file
    }, {
		"help", '?',				AT_EMPTY,
		(ArgProcP) main_handle_help,		NIL (GenericP),
		MID_description_of_help
    }, {
		"include-library", 'i',			AT_FOLLOWING,
		(ArgProcP) main_handle_library_file,	NIL (GenericP),
		MID_description_of_include_library
    }, {
		"output-file", 'o',			AT_FOLLOWING,
		(ArgProcP) main_handle_output_file,	NIL (GenericP),
		MID_description_of_output_file
    }, {
		"show-errors", 'e',			AT_EMPTY,
		(ArgProcP) main_handle_show_errors,	NIL (GenericP),
		MID_description_of_show_errors
    }, {
		"suppress", 's',			AT_FOLLOWING2,
		(ArgProcP) main_handle_suppress,	NIL (GenericP),
		MID_description_of_suppress
    }, {
		"suppress-all", 'S',			AT_FOLLOWING,
		(ArgProcP) main_handle_suppress_all,	NIL (GenericP),
		MID_description_of_suppress_all
    }, {
		"suppress-mult", 'M',			AT_PROC_SWITCH,
		(ArgProcP) main_handle_suppress_mult,	NIL (GenericP),
		MID_description_of_suppress_mult
    }, {
		"unit-file", 'u',			AT_FOLLOWING,
		(ArgProcP) main_handle_unit_file,	NIL (GenericP),
		MID_description_of_unit_file
    }, {
		"version", 'v',				AT_EMPTY,
		(ArgProcP) main_handle_version,		NIL (GenericP),
		MID_description_of_version
    }, ARG_PARSE_END_LIST
};

static ArgListT main_contents_arg_list [] = {
    {
		"debug-file", 'd',			AT_FOLLOWING,
		(ArgProcP) main_handle_debug_file,	NIL (GenericP),
		MID_description_of_debug_file
    }, {
		"help", '?',				AT_EMPTY,
		(ArgProcP) main_handle_help,		NIL (GenericP),
		MID_description_of_help
    }, {
		"index", 'i',				AT_PROC_SWITCH,
		(ArgProcP) main_handle_index,		NIL (GenericP),
		MID_description_of_index
    }, {
		"show-errors", 'e',			AT_EMPTY,
		(ArgProcP) main_handle_show_errors,	NIL (GenericP),
		MID_description_of_show_errors
    }, {
		"size", 's',				AT_PROC_SWITCH,
		(ArgProcP) main_handle_size,		NIL (GenericP),
		MID_description_of_size
    }, {
		"tdf-version", 't',			AT_PROC_SWITCH,
		(ArgProcP) main_handle_tdf_version,	NIL (GenericP),
		MID_description_of_tdf_version
    }, {
		"version", 'v',				AT_EMPTY,
		(ArgProcP) main_handle_version,		NIL (GenericP),
		MID_description_of_version
    }, ARG_PARSE_END_LIST
};

static ArgListT main_extract_arg_list [] = {
    {
		"all", 'a',				AT_PROC_SWITCH,
		(ArgProcP) main_handle_all,		NIL (GenericP),
		MID_description_of_all
    }, {
		"basename", 'b',			AT_PROC_SWITCH,
		(ArgProcP) main_handle_basename,	NIL (GenericP),
		MID_description_of_basename
    }, {
		"debug-file", 'd',			AT_FOLLOWING,
		(ArgProcP) main_handle_debug_file,	NIL (GenericP),
		MID_description_of_debug_file
    }, {
		"show-errors", 'e',			AT_EMPTY,
		(ArgProcP) main_handle_show_errors,	NIL (GenericP),
		MID_description_of_show_errors
    }, {
		"help", '?',				AT_EMPTY,
		(ArgProcP) main_handle_help,		NIL (GenericP),
		MID_description_of_help
    }, {
		"info", 'i',				AT_PROC_SWITCH,
		(ArgProcP) main_handle_info,		NIL (GenericP),
		MID_description_of_info
    }, {
		"match-basename", 'm',			AT_PROC_SWITCH,
		(ArgProcP) main_handle_match_base,	NIL (GenericP),
		MID_description_of_match_basename
    }, {
		"version", 'v',				AT_EMPTY,
		(ArgProcP) main_handle_version,		NIL (GenericP),
		MID_description_of_version
    }, ARG_PARSE_END_LIST
};

static ArgListT main_linker_arg_list [] = {
    {
		"all-hide-defined", 'a',		AT_PROC_SWITCH,
		(ArgProcP) main_handle_all_hide_defd,	NIL (GenericP),
		MID_description_of_all_hide_defined
    }, {
		"debug-file", 'd',			AT_FOLLOWING,
		(ArgProcP) main_handle_debug_file,	NIL (GenericP),
		MID_description_of_debug_file
    }, {
		"help", '?',				AT_EMPTY,
		(ArgProcP) main_handle_help,		NIL (GenericP),
		MID_description_of_help
    }, {
		"hide", 'h',				AT_FOLLOWING2,
		(ArgProcP) main_handle_hide,		NIL (GenericP),
		MID_description_of_hide
    }, {
		"hide-defined", 'H',			AT_FOLLOWING,
		(ArgProcP) main_handle_hide_defined,	NIL (GenericP),
		MID_description_of_hide_defined
    }, {
		"keep", 'k',				AT_FOLLOWING2,
		(ArgProcP) main_handle_keep,		NIL (GenericP),
		MID_description_of_keep
    }, {
		"keep-all", 'K',			AT_FOLLOWING,
		(ArgProcP) main_handle_keep_all,	NIL (GenericP),
		MID_description_of_keep_all
    }, {
		"library", '\0',			AT_FOLLOWING,
		(ArgProcP) main_handle_library_file,	NIL (GenericP),
		MID_description_of_library_file
    }, {
		NIL (CStringP), 'l',			AT_EITHER,
		(ArgProcP) main_handle_library_file,	NIL (GenericP),
		MID_description_of_l
    }, {
		"output-file", 'o',			AT_FOLLOWING,
		(ArgProcP) main_handle_output_file,	NIL (GenericP),
		MID_description_of_output_file
    }, {
		"path", '\0',				AT_FOLLOWING,
		(ArgProcP) main_handle_library_path,	NIL (GenericP),
		MID_description_of_path
    }, {
		NIL (CStringP), 'L',			AT_EITHER,
		(ArgProcP) main_handle_library_path,	NIL (GenericP),
		MID_description_of_L
    }, {
		"rename", 'r',				AT_FOLLOWING3,
		(ArgProcP) main_handle_rename,		NIL (GenericP),
		MID_description_of_rename
    }, {
		"rename-file", 'R',			AT_FOLLOWING,
		(ArgProcP) main_handle_rename_file,	NIL (GenericP),
		MID_description_of_rename_file
    }, {
		"show-errors", 'e',			AT_EMPTY,
		(ArgProcP) main_handle_show_errors,	NIL (GenericP),
		MID_description_of_show_errors
    }, {
		"suppress", 's',			AT_FOLLOWING2,
		(ArgProcP) main_handle_suppress,	NIL (GenericP),
		MID_description_of_suppress
    }, {
		"suppress-all", 'S',			AT_FOLLOWING,
		(ArgProcP) main_handle_suppress_all,	NIL (GenericP),
		MID_description_of_suppress_all
    }, {
		"suppress-mult", 'M',			AT_PROC_SWITCH,
		(ArgProcP) main_handle_suppress_mult,	NIL (GenericP),
		MID_description_of_suppress_mult
    }, {
		"unit-file", 'u',			AT_FOLLOWING,
		(ArgProcP) main_handle_unit_file,	NIL (GenericP),
		MID_description_of_unit_file
    }, {
		"version", 'v',				AT_EMPTY,
		(ArgProcP) main_handle_version,		NIL (GenericP),
		MID_description_of_version
    }, {
		"warnings", 'w',			AT_PROC_SWITCH,
		(ArgProcP) main_handle_warning,		NIL (GenericP),
		MID_description_of_warning
    }, ARG_PARSE_END_LIST
};

#ifdef __TenDRA__
#pragma TenDRA end
#endif

/*--------------------------------------------------------------------------*/

/*
 * Handlers for tld specific message objects
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
msg_uh_NameKeyP(char ch, void *pp)
{
	UNUSED(ch);
	write_name_key(msg_stream, (NameKeyP)pp);
}

static void
msg_uh_capsule_offset(char ch, void *pp)
{
	CapsuleP capsule = pp;

	UNUSED(ch);
	write_fmt(msg_stream, "%s: %lu: ", capsule_name(capsule),
		(unsigned long)capsule_byte(capsule));
}

static void
msg_uh_library_offset(char ch, void *pp)
{
	LibraryP lib = pp;

	UNUSED(ch);
	write_fmt(msg_stream, "%s: %lu: ", library_name(lib),
		(unsigned long)library_byte(lib));
}

static void
msg_uh_istream_line(char ch, void *pp)
{
	IStreamP is = pp;

	UNUSED(ch);
	write_fmt(msg_stream, "%s: %lu: ", istream_name(is),
		(unsigned long)istream_line(is));
}

static void
msg_uh_tdfr_offset(char ch, void *pp)
{
	TDFReaderP tdfr = pp;

	UNUSED(ch);
	write_fmt(msg_stream, "%s: %lu: ", tdf_reader_name(tdfr),
		(unsigned long)tdf_reader_byte(tdfr));
}

static void
msg_uh_ExceptionName(char ch, void *pp)
{
	UNUSED(ch);
	msg_append_string(exception_name((ExceptionP)pp));
}

static void
msg_uh_libcapfullname(char ch, void *pp)
{
	UNUSED(ch);
	write_lib_capsule_full_name(msg_stream, (LibCapsuleP)pp);
}

static ModeT
main_init(int argc, char **argv)
{
    ModeT     mode          = MODE_LINKER;
    ArgListP  arg_list      = main_linker_arg_list;
    int       skip;

	msg_uh_add(MSG_KEY_ArgUsageP, msg_uh_ArgUsageP);
	msg_uh_add(MSG_KEY_NStringP, msg_uh_NStringP);
	msg_uh_add(MSG_KEY_NameKeyP, msg_uh_NameKeyP);
	msg_uh_add(MSG_KEY_capsule_offset, msg_uh_capsule_offset);
	msg_uh_add(MSG_KEY_library_offset, msg_uh_library_offset);
	msg_uh_add(MSG_KEY_istream_line, msg_uh_istream_line);
	msg_uh_add(MSG_KEY_tdfr_offset, msg_uh_tdfr_offset);
	msg_uh_add(MSG_KEY_ExceptionName, msg_uh_ExceptionName);
	msg_uh_add(MSG_KEY_libcapfullname, msg_uh_libcapfullname);
    argc --;
    argv ++;
  retry:
    if ((argc > 0) && (argv [0][0] == '-') && (argv [0][1] == 'm')) {
		char c = argv [0][2];

		argc --;
		argv ++;
		switch (c) {
		case 'c':
			mode     = MODE_BUILDER;
			arg_list = main_builder_arg_list;
			arg_data_init (&main_arg_data, "library.tl");
			break;
		case 't':
			mode     = MODE_CONTENTS;
			arg_list = main_contents_arg_list;
			arg_data_init (&main_arg_data, NIL (CStringP));
			break;
		case 'x':
			mode     = MODE_EXTRACT;
			arg_list = main_extract_arg_list;
			arg_data_init (&main_arg_data, NIL (CStringP));
			break;
		case 'l':
			goto linker_case;
		case 'v':
			main_used_one_off = TRUE;
			main_used_other   = FALSE;
			tenapp_report_version();
			goto retry;
		default:
			MSG_bad_mode (argv [0][2]);
			UNREACHED;
		}
    } else {
      linker_case:
		arg_data_init (&main_arg_data, "capsule.j");
    }
    skip = arg_parse_arguments (arg_list, MID_tld_usage_message, argc, argv);
    argc -= skip;
    argv += skip;
    if (main_used_one_off && (!main_used_other) && (argc == 0)) {
		exit (EXIT_SUCCESS);
		UNREACHED;
    } else if (argc == 0) {
		MSG_missing_files ();
		UNREACHED;
    }
    arg_data_set_files (&main_arg_data, argc, argv);
    arg_data_vector_libraries (&main_arg_data);
    debug_set_file (arg_data_get_debug_file (&main_arg_data));
    return (mode);
}

/*--------------------------------------------------------------------------*/

int
main(int argc, char **argv)
{
    HANDLE {
		istream_setup ();
		tenapp_init(argc, argv, "TDF linker", "4.0#8");
		msg_sev_set(MSG_SEV_WARNING, 0);

		switch (main_init (argc, argv)) EXHAUSTIVE {
		case MODE_BUILDER:
			builder_main (&main_arg_data);
			break;
		case MODE_CONTENTS:
			contents_main (&main_arg_data);
			break;
		case MODE_EXTRACT:
			extract_main (&main_arg_data);
			break;
		case MODE_LINKER:
			linker_main (&main_arg_data);
			break;
		}
    } WITH {
		ExceptionP exception = EXCEPTION_EXCEPTION ();

		if (exception == XX_dalloc_no_memory) {
			MSG_no_memory ();
			UNREACHED;
		} else if ((exception == XX_istream_read_error) ||
				   (exception == XX_bistream_read_error)) {
			CStringP file = (CStringP) EXCEPTION_VALUE ();

			MSG_file_read_error (file);
			UNREACHED;
		} else if (exception == XX_bostream_write_error) {
			CStringP file = (CStringP) EXCEPTION_VALUE ();

			MSG_file_write_error (file);
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
 * compile-command: "build_tld next-cc"
 * eval: (include::add-path-entry "os-interface" "library" "tdf")
 * eval: (include::add-path-entry "frontends" "generated")
 * End:
 **/
