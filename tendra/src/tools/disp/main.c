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
#include "types.h"
#include "ascii.h"
#include "basic.h"
#include "file.h"
#include "capsule.h"
#include "pretty.h"
#include "sort.h"
#include "tdf.h"
#include "tree.h"
#include "unit.h"

static void
opt_decode_all(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	diagnostics = TRUE;
	show_usage = TRUE;
	versions = 1;
}

static void
opt_version(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	tenapp_report_version ();
	MSG_TDF_version(version_major, version_minor);
}

static void
opt_pagewidth(char *option, void *closure, char *value)
{
	UNUSED(option);
	UNUSED(closure);

	maxcol = atoi (value);
}

static void
opt_null(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);
}

static void opt_help(char *option, void *closure);

static ArgListT cmdl_opts[] = {
	AP_OPT_EMPTY	(decode_all,	'A', NULL, opt_decode_all),
	AP_OPT_SET		(bin_dump,		'D', NULL, &dump),
	AP_OPT_SET		(num_ext_toks,	'E', NULL, &show_stuff),
	AP_OPT_SET		(show_skip,		'T', NULL, &show_skip),
	AP_OPT_EMPTY	(version,		'V', NULL, opt_version),
	AP_OPT_SET		(warn_undecl,	'W', NULL, &warn_undeclared),
	AP_OPT_RESET	(no_dots,		'a', NULL, &helpflag),
	AP_OPT_SET		(diagunits,		'g', NULL, &diagnostics),
	AP_OPT_EMPTY	(help,			'h', "help", opt_help),
	AP_OPT_EMPTY	(compat,		'i', NULL, opt_null),
	AP_OPT_SET		(show_usage,	'l', NULL, &show_usage),
	AP_OPT_EITHER	(pagewidth,		'n', NULL, opt_pagewidth),
	AP_OPT_SET		(quick,			'q', NULL, &quickflag),
	AP_OPT_SET		(dumb_mode,		'r', NULL, &dumb_mode),
	AP_OPT_SET		(progress,		'v', NULL, &progress),
	AP_OPT_RESET	(noversions,	'x', NULL, &versions),
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
msg_uh_tdfoff(char ch, void *pp)
{
	UNUSED(ch);
	UNUSED(pp);
	write_fmt(msg_stream, "byte %lu, bit %d: ",
		(unsigned long)here.byte, here.bit);
}


/*
 *    MAIN ROUTINE
 */

int
main(int argc, char **argv)
{
	char *input, *output;
	int optcnt;

    tenapp_init(argc, argv, "TDF pretty printer", "1.5");
    msg_uh_add(MSG_GLOB_tdfoff, msg_uh_tdfoff);

	output = NULL;
	argc--;
	argv++;
	optcnt = arg_parse_arguments (cmdl_opts, argc, argv);
	argc -= optcnt;
	argv += optcnt;

	if (argc < 1)
		MSG_getopt_not_enough_arguments ();
	input = *argv++;
	if (argc > 2)
		MSG_getopt_too_many_arguments ();
	if (argc == 2)
		output = *argv;

    /* Open the files */
	open_files (input, output);

    /* Perform binary dump if required */
    if (dump) {
		long f;
		int bits = 0, n = 1;
		while (f = fetch (1), !read_error) {
			if (n == 1) IGNORE fprintf (pp_file, "%d :\t", bits / 8);
			IGNORE fputc ((f ? '1' : '0'), pp_file);
			if (n == 64) {
				IGNORE fputc ('\n', pp_file);
				n = 1;
			} else {
				if (n % 8 == 0) IGNORE fputc (' ', pp_file);
				n++;
			}
			bits++;
		}
		if (n != 1) IGNORE fputc ('\n', pp_file);
		exit (0);
    }

    /* Call the main routines */
    if (diagnostics || show_usage) do_foreign_sorts = 1;
    init_foreign_sorts ();
    initialize_tree ();
    de_capsule ();
    pretty_tree ();
    return (exit_status);
}
