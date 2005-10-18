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
#include "argparse.h"

#include "release.h"
#include "arg-data.h"
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
} ModeT;

/*--------------------------------------------------------------------------*/

static BoolT    main_used_one_off = FALSE;
static BoolT    main_used_other   = FALSE;
static ArgDataT main_arg_data;
static ModeT	mode = MODE_LINKER;

/*--------------------------------------------------------------------------*/

static void
main_handle_all(char *option, void *gclosure, BoolT enable)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_set_extract_all (&main_arg_data, enable);
}

static void
main_handle_all_hide_defd(char *option, void *gclosure, BoolT enable)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_set_all_hide_defd (&main_arg_data, enable);
}

static void
main_handle_basename(char *option, void *gclosure, BoolT enable)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_set_extract_basename (&main_arg_data, enable);
}

static void
main_handle_debug_file(char *option, void *gclosure, char *debug_file)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_set_debug_file (&main_arg_data, debug_file);
}

static void
main_handle_hide(char *option, void *gclosure, char *shape, char *name)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_add_hide (&main_arg_data, shape, name);
}

static void
main_handle_hide_defined(char *option, void *gclosure, char *shape)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_add_hide_defined (&main_arg_data, shape);
}

static void
main_handle_index(char *option, void *gclosure, BoolT enable)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_set_content_index (&main_arg_data, enable);
}

static void
main_handle_info(char *option, void *gclosure, BoolT enable)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	msg_sev_set(MSG_SEV_INFO, enable);
}

static void
main_handle_keep(char *option, void *gclosure, char *shape, char *name)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_add_keep (&main_arg_data, shape, name);
}

static void
main_handle_keep_all(char *option, void *gclosure, char *shape)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_add_keep_all (&main_arg_data, shape);
}

static void
main_handle_library_file(char *option, void *gclosure, char *library_file)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_add_library_file (&main_arg_data, library_file);
}

static void
main_handle_match_base(char *option, void *gclosure, BoolT enable)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_set_extract_match_base (&main_arg_data, enable);
}

static void
main_handle_output_file(char *option, void *gclosure, char *output_file)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_set_output_file (&main_arg_data, output_file);
}

static void
main_handle_library_path(char *option, void *gclosure, char *directory)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_add_library_path (&main_arg_data, directory);
}

static void
main_handle_rename(char *option, void *gclosure, char *shape, char *from,
	char *to)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_parse_rename (&main_arg_data, shape, from, to);
}

static void
main_handle_rename_file(char *option, void *gclosure, char *name)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	rename_file_parse (name, &main_arg_data);
}

static void
main_handle_size(char *option, void *gclosure, BoolT enable)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_set_content_size (&main_arg_data, enable);
}

static void
main_handle_suppress(char *option, void *gclosure, char *shape, char *name)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_add_suppress (&main_arg_data, shape, name);
}

static void
main_handle_suppress_all(char *option, void *gclosure, char *shape)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_add_suppress_all (&main_arg_data, shape);
}

static void
main_handle_suppress_mult(char *option, void *gclosure, BoolT enable)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_set_suppress_mult (&main_arg_data, enable);
}

static void
main_handle_tdf_version(char *option, void *gclosure, BoolT enable)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_set_content_version (&main_arg_data, enable);
}

static void
main_handle_unit_file(char *option, void *gclosure, char *unit_file)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	arg_data_set_unit_file (&main_arg_data, unit_file);
}

static void
main_handle_version(char *option, void *gclosure)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_one_off = TRUE;
	tenapp_report_version();
}

static void
main_handle_warning(char *option, void *gclosure, BoolT enable)
{
	UNUSED (option);
	UNUSED (gclosure);
	main_used_other = TRUE;
	msg_sev_set(MSG_SEV_WARNING, enable);
}

static void
main_handle_mode(char *option, void *closure, char *arg)
{
	UNUSED(closure);

	if (arg[1])
		MSG_bad_mode (option);
	switch (arg[0]) {
	case 'c': mode = MODE_BUILDER; break;
	case 't': mode = MODE_CONTENTS;	break;
	case 'x': mode = MODE_EXTRACT; break;
	case 'l': break;
	default:
		MSG_bad_mode (option);
		UNREACHED;
	}
}

static void main_handle_root_help (char *, void *);
static void main_handle_builder_help (char *, void *);
static void main_handle_contents_help (char *, void *);
static void main_handle_extract_help (char *, void *);
static void main_handle_linker_help (char *, void *);

/*--------------------------------------------------------------------------*/

/*
 * Top level options
 */
static ArgListT main_opts[] = {
	AP_OPT_EMPTY	(help,		'h', NULL, main_handle_root_help),
	AP_OPT_IMMEDIATE(mode,		'm', NULL, main_handle_mode),
	AP_OPT_EMPTY	(version,	'V', NULL, main_handle_version),
	AP_OPT_EOL
};

static ArgListT main_builder_arg_list[] = {
	AP_OPT_FOLLOWING(debug_file,	'd', "debug-file", main_handle_debug_file),
	AP_OPT_EMPTY	(help,			'h', "help", main_handle_builder_help),
	AP_OPT_FOLLOWING(include_library,'i',"include-library", main_handle_library_file),
	AP_OPT_FOLLOWING(output_file,	'o', "output-file",main_handle_output_file),
	AP_OPT_FOLLOWING2(suppress,		's', "suppress", main_handle_suppress),
	AP_OPT_FOLLOWING(suppress_all,	'S', "suppress-all", main_handle_suppress_all),
	AP_OPT_PROC_SW	(suppress_mult,	'M', "suppress-mult", main_handle_suppress_mult),
	AP_OPT_FOLLOWING(unit_file,		'u', "unit-file", main_handle_unit_file),
	AP_OPT_EMPTY	(version,		'V', NULL, main_handle_version),
	AP_OPT_EOL
};

static ArgListT main_contents_arg_list[] = {
	AP_OPT_FOLLOWING(debug_file,	'd', "debug-file", main_handle_debug_file),
	AP_OPT_EMPTY	(help,			'h', "help", main_handle_contents_help),
	AP_OPT_PROC_SW	(index,			'i', "index", main_handle_index),
	AP_OPT_PROC_SW	(size,			's', "size", main_handle_size),
	AP_OPT_PROC_SW	(tdf_version,	't', "tdf-version", main_handle_tdf_version),
	AP_OPT_EMPTY	(version,		'V', NULL, main_handle_version),
	AP_OPT_EOL
};

static ArgListT main_extract_arg_list[] = {
	AP_OPT_PROC_SW	(all,			'a', "all", main_handle_all),
	AP_OPT_PROC_SW	(basename,		'b', "basename", main_handle_basename),
	AP_OPT_FOLLOWING(debug_file,	'd', "debug-file", main_handle_debug_file),
	AP_OPT_EMPTY	(help,			'h', "help", main_handle_extract_help),
	AP_OPT_PROC_SW	(info,			'i', "info", main_handle_info),
	AP_OPT_PROC_SW	(match_basename,'m', "match-basename", main_handle_match_base),
	AP_OPT_EMPTY	(version,	'V', NULL, main_handle_version),
	AP_OPT_EOL
};

static ArgListT main_linker_arg_list[] = {
	AP_OPT_PROC_SW	(all_hide_defined,'a', "all-hide-defined",
		main_handle_all_hide_defd),
	AP_OPT_FOLLOWING(debug_file,	'd', "debug-file", main_handle_debug_file),
	AP_OPT_EMPTY	(help,			'\0', "help", main_handle_linker_help),
	AP_OPT_FOLLOWING2(hide,			'h', "hide", main_handle_hide),
	AP_OPT_FOLLOWING(hide_defined,	'H', "hide-defined", main_handle_hide_defined),
	AP_OPT_FOLLOWING2(keep,			'k', "keep", main_handle_keep),
	AP_OPT_FOLLOWING(keep_all,		'K', "keep-all", main_handle_keep_all),
	AP_OPT_EITHER	(library_file,	'l', "library", main_handle_library_file),
	AP_OPT_FOLLOWING(output_file,	'o', "output-file", main_handle_output_file),
   	AP_OPT_EITHER	(path,			'L', "path", main_handle_library_path),
	AP_OPT_FOLLOWING3(rename,		'r', "rename", main_handle_rename),
	AP_OPT_FOLLOWING(rename_file,	'R', "rename-file", main_handle_rename_file),
	AP_OPT_FOLLOWING2(suppress,		's', "suppress", main_handle_suppress),
	AP_OPT_FOLLOWING(suppress_all,	'S', "suppress-all", main_handle_suppress_all),
	AP_OPT_PROC_SW	(suppress_mult,	'M', "suppress-mult", main_handle_suppress_mult),
	AP_OPT_FOLLOWING(unit_file,		'u', "unit-file", main_handle_unit_file),
	AP_OPT_EMPTY	(version,		'V', NULL, main_handle_version),
	AP_OPT_PROC_SW	(warning,		'w', "warnings", main_handle_warning),
	AP_OPT_EOL
};

static void
main_handle_root_help(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	MSG_root_usage ();
	arg_print_usage (main_opts);
	msg_append_newline ();
}

static void
main_handle_builder_help(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	MSG_builder_usage ();
	arg_print_usage (main_builder_arg_list);
	msg_append_newline ();
}

static void
main_handle_contents_help(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	MSG_contents_usage ();
	arg_print_usage (main_contents_arg_list);
	msg_append_newline ();
}

static void
main_handle_extract_help(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	MSG_extract_usage ();
	arg_print_usage (main_extract_arg_list);
	msg_append_newline ();
}

static void
main_handle_linker_help(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	MSG_linker_usage ();
	arg_print_usage (main_linker_arg_list);
	msg_append_newline ();
}

/*--------------------------------------------------------------------------*/

/*
 * Handlers for tld specific message objects
 */
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
	ArgListT *arg_list;
	int       skip;

	msg_uh_add(MSG_KEY_NStringP, msg_uh_NStringP);
	msg_uh_add(MSG_KEY_NameKeyP, msg_uh_NameKeyP);
	msg_uh_add(MSG_KEY_capsule_offset, msg_uh_capsule_offset);
	msg_uh_add(MSG_KEY_library_offset, msg_uh_library_offset);
	msg_uh_add(MSG_KEY_istream_line, msg_uh_istream_line);
	msg_uh_add(MSG_KEY_tdfr_offset, msg_uh_tdfr_offset);
	msg_uh_add(MSG_KEY_ExceptionName, msg_uh_ExceptionName);
	msg_uh_add(MSG_KEY_libcapfullname, msg_uh_libcapfullname);
	argc--;
	argv++;
	if (argc <= 0) {
		main_handle_root_help (NULL, NULL);
		return (EXIT_FAILURE);
	}
	if (argv[0][0] == '-') {
		switch (argv[0][1]) {
		case 'h':
		case 'm':
		case 'V':
			skip = arg_parse_arguments (main_opts, 1, argv);
			argc -= skip;
			argv += skip;
			break;
		}
	}
	switch (mode) {
	case MODE_BUILDER:
		arg_list = main_builder_arg_list;
		arg_data_init (&main_arg_data, "library.tl");
		break;
	case MODE_CONTENTS:
		arg_list = main_contents_arg_list;
		arg_data_init (&main_arg_data, NULL);
		break;
	case MODE_EXTRACT:
		arg_list = main_extract_arg_list;
		arg_data_init (&main_arg_data, NULL);
		break;
	case MODE_LINKER:
		arg_list = main_linker_arg_list;
		arg_data_init (&main_arg_data, "capsule.j");
	}
	skip = arg_parse_arguments (arg_list, argc, argv);
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
			char *file = (char *) EXCEPTION_VALUE ();

			MSG_file_read_error (file);
			UNREACHED;
		} else if (exception == XX_bostream_write_error) {
			char *file = (char *) EXCEPTION_VALUE ();

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
