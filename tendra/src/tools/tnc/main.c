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


#include "config.h"
#include "argparse.h"
#include "catstdn.h"
#include "msgcat.h"
#include "ostream.h"
#include "tenapp.h"

#include "release.h"
#include "fetch.h"
#include "types.h"
#include "read_types.h"
#include "analyser.h"
#include "check.h"
#include "de_types.h"
#include "de_capsule.h"
#include "enc_cap.h"
#include "eval.h"
#include "file.h"
#include "help.h"
#include "node.h"
#include "read_cap.h"
#include "shape.h"
#include "tdf.h"
#include "table.h"
#include "utility.h"
#include "write.h"


static BoolT do_not_process = 0;
static BoolT expand = 0;
static BoolT evaluate = 0;
static BoolT lib_input = 0;

static char *out_file = NULL;

static void (*input_fn)(void);
static void (*output_fn)(void);

/*
 *    PROCESS AN OUTPUT OPTION
 *
 *    The show option corresponding to arg is set to t.
 */

static boolean
output_option(char *arg, boolean t)
{
    boolean *p = null;
    if (streq (arg, "tokdecs")) {
		p = &show_tokdecs;
    } else if (streq (arg, "tokdefs")) {
		p = &show_tokdefs;
    } else if (streq (arg, "aldecs")) {
		p = &show_aldecs;
    } else if (streq (arg, "aldefs")) {
		p = &show_aldefs;
    } else if (streq (arg, "tagdecs")) {
		p = &show_tagdecs;
    } else if (streq (arg, "tagdefs")) {
		p = &show_tagdefs;
    }
    if (p == null) return (0);
    if (t) {
		show_tokdecs = 0;
		show_tokdefs = 0;
		show_aldefs = 0;
		show_tagdecs = 0;
		show_tagdefs = 0;
    }
    *p = t;
    return (1);
}

static void
opt_check(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	/* Switch on shape checking */
	init_shapes ();
	do_check = 1;
}

static void
opt_cv(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	init_shapes ();
	do_check = 1;
	print_shapes = 1;
}

static void
opt_decode(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	input_fn = de_capsule;
	text_input = 0;
}

static void
opt_encode(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	output_fn = enc_capsule;
	text_output = 0;
}

static void
opt_func(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	func_input = 1;
	func_output = 1;
}

static void
opt_print(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	/* Pretty printer mode */
	input_fn = de_capsule;
	output_fn = print_capsule;
	text_input = 0;
	text_output = 1;
}

static void
opt_read(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	input_fn = read_capsule;
	text_input = 1;
}

static void
opt_write(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	output_fn = print_capsule;
	text_output = 1;
}

static void
opt_tsimp(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	evaluate = 1;
	expand = 1;
}

static void
opt_subject(char *option, void *closure, char *value)
{
	UNUSED(option);
	UNUSED(closure);

	help (value);
	do_not_process = TRUE;
}

static void
opt_include(char *option, void *closure, char *value)
{
	UNUSED(option);
	UNUSED(closure);

	add_directory (value);
}

static void
opt_lprefix(char *option, void *closure, char *value)
{
	UNUSED(option);
	UNUSED(closure);

	local_prefix = value;
}

static void
opt_outfile(char *option, void *closure, char *value)
{
	UNUSED(option);
	UNUSED(closure);

	out_file = value;
}

static void
opt_version(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	tenapp_report_version ();
	MSG_TDF_version(VERSION_major, VERSION_minor);
}

static void
opt_no(char *option, void *closure, char *value)
{
	UNUSED(option);
	UNUSED(closure);

	if (!output_option (value, 0))
		MSG_getopt_unknown_option (value);
}

static void
opt_only(char *option, void *closure, char *value)
{
	UNUSED(option);
	UNUSED(closure);

	if (!output_option (value, 1))
		MSG_getopt_unknown_option (value);
}

static void opt_help(char *option, void *closure);

static ArgListT cmdl_opts[] = {
	AP_OPT_EITHER	(include,		'I', NULL, opt_include),
	AP_OPT_EITHER	(lprefix,		'L', NULL, opt_lprefix),
	AP_OPT_EITHER	(subject,		'S', NULL, opt_subject),
	AP_OPT_EMPTY	(version,		'V', NULL, opt_version),
	AP_OPT_EMPTY	(check,			'c', "check", opt_check),
	AP_OPT_EMPTY	(cv,			'\0', "cv", opt_cv),
	AP_OPT_EMPTY	(decode,		'd', "decode", opt_decode),
	AP_OPT_EMPTY	(encode,		'e', "encode", opt_encode),
	AP_OPT_SET		(eval,			'\0', "eval", &evaluate),
	AP_OPT_SET		(expand,		'\0', "expand", &expand),
	AP_OPT_SET		(funcin,		'\0', "funcin", &func_input),
	AP_OPT_SET		(funcout,		'\0', "funcout", &func_output),
	AP_OPT_EMPTY	(func,			'f', "func", opt_func),
	AP_OPT_EMPTY	(help,			'h', "help", opt_help),
	AP_OPT_SET		(lib,			'l', "lib", &lib_input),
	AP_OPT_FOLLOWING(no,			'\0', "no", opt_no),
	AP_OPT_FOLLOWING(only,			'\0', "only", opt_only),
	AP_OPT_EITHER	(outfile,		'o', NULL, opt_outfile),
	AP_OPT_EMPTY	(print,			'p', "print", opt_print),
	AP_OPT_SET		(dont_check,	'q', NULL, &dont_check),
	AP_OPT_EMPTY	(read,			'r', "read", opt_read),
	AP_OPT_EMPTY	(tsimp,			't', "tsimp", opt_tsimp),
	AP_OPT_RESET	(unsorted,		'u', "unsorted", &order_names),
	AP_OPT_SET		(verbose,		'v', NULL, &verbose),
	AP_OPT_EMPTY	(write,			'w', "write", opt_write),
	AP_OPT_EOL
};

static void
opt_help(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	MSG_usage ();
	arg_print_usage (cmdl_opts);
	msg_append_newline ();
}

static void
msg_uh_where(char ch, void *pp)
{
	UNUSED(ch);
	UNUSED(pp);
    if (input_file) {
		write_fmt (msg_stream, ", %s", input_file);
		if (text_input) {
			write_fmt (msg_stream, ", line %ld", line_no);
		} else {
			long b = input_posn ();
			if (capname)
				write_fmt(msg_stream, ", capsule %s", capname);
			switch (decode_status) {
			case 0:
				write_fmt (msg_stream, " (at outermost level)");
				break;
			case 1:
				write_fmt (msg_stream, " (in linking information)");
				break;
			case 2 :
				write_fmt (msg_stream, " (in unit body)");
				break;
			}
			write_fmt (msg_stream, ", byte %ld, bit %ld", b / 8, b % 8);
			if (decode_status == 0)
				write_fmt (msg_stream, " (Illegal TDF capsule?)");
			if (decode_status >= 1 && !have_version)
				write_fmt (msg_stream, " (TDF version error?)");
		}
    }
}


/*
 *    MAIN ROUTINE
 *
 *    This is the main routine.  It processes the command line arguments
 *    and calls the appropriate input and output routines.
 */

int
main(int argc, char **argv)
{
    int optcnt;

	tenapp_init(argc, argv, "TDF notation compiler", "1.9");
	msg_uh_add(MSG_GLOB_where, msg_uh_where);

    /* Default action : read text, encode TDF capsule */
    input_fn = read_capsule;
    output_fn = enc_capsule;
    text_input = 1;
    text_output = 0;

    /* Initialize internal tables */
    init_tables ();
    init_constructs ();

	optcnt = arg_parse_arguments (cmdl_opts, --argc, ++argv);
	if (do_not_process)
		return (exit_status);
	argc -= optcnt;
	argv += optcnt;
	if (argc < 1)
		MSG_getopt_not_enough_arguments ();
	open_input (*argv++, 0);
	if (argc == 2) {
		if (out_file)
			MSG_getopt_too_many_arguments ();
		else
			open_output (*argv);
	} else
		output = stdout;

    /* Check on library input */
    if (lib_input && input_fn == de_capsule) input_fn = de_library;

    /* Perform the appropriate actions */
    (*input_fn) ();
    if (exit_status == EXIT_SUCCESS || text_output) {
		if (expand) expand_all ();
		if (evaluate) eval_all ();
		sort_all ();
		(*output_fn) ();
    }
    return (exit_status);
}
