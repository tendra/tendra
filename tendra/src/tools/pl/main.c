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
#include "tenapp.h"

#include "release.h"
#include "namedecs.h"
#include "lex.h"
#include "includes.h"
#include "syntax.h"
#include "units.h"

static BoolT diag = FALSE;

static void
opt_include(char *option, void *closure, char *value)
{
	UNUSED(option);
	UNUSED(closure);

	add_include (value);
}


static void opt_help(char *option, void *closure);

static ArgListT cmdl_opts[] = {
	AP_OPT_EITHER	(include,		'I', NULL, opt_include),
	AP_OPT_EMPTY	(version,		'V', NULL, arg_std_version),
	AP_OPT_SET		(diag,			'g', NULL, &diag),
	AP_OPT_EMPTY	(help,			'h', "help", opt_help),
	AP_OPT_SET		(diag,			'p', NULL, &do_pp),
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

int
main(int argc, char **argv)
{
    char *in, *out;
	int optcnt;

    tenapp_init(argc, argv, "PL-TDF compiler", "5.0");
    init_includes ();
	argc--;
	argv++;
	optcnt = arg_parse_arguments (cmdl_opts, argc, argv);
	argc -= optcnt;
	argv += optcnt;

	if (argc < 2)
		MSG_getopt_not_enough_arguments ();
	in = *argv++;
	if (argc > 2)
		MSG_getopt_too_many_arguments ();
	if (argc == 2)
		out = *argv;

    in_file = fopen (in, "r");
    file_name = in;
    if (in_file == NULL) {
		MSG_cant_open_input_file(in);
    }
    out_file = fopen (out, "wb");
    if (out_file == NULL) {
		MSG_cant_open_output_file(out);
    }
    lex_v = reader ();
    init_units ();
    if (diag) line_no_tok = next_capsule_name (tok_ent);
    read_program ();
    IGNORE fclose (in_file);
    IGNORE fclose (out_file);
    return (0);
}
