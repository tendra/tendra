/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.tendra.org/>
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

#include "tdf.h"
#include "cmd_ops.h"
#include "spec_ops.h"
#include "input.h"
#include "lex.h"
#include "output.h"
#include "syntax.h"

static void opt_help(char *option, void *closure);

static ArgListT cmdl_opts[] = {
	AP_OPT_EMPTY	(version, 	'V', NULL, arg_std_version),
	AP_OPT_EMPTY	(help,		'h', "help", opt_help),
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
	tenapp_exit();
}


/*
 *    MAIN ROUTINE
 *
 *    This is the main routine.  It processes the command-line options,
 *    reads the input file, and writes the output files.
 */

int
main(int argc, char **argv)
{
	int optcnt;
	char *input = NULL;
	char *templ = NULL;
	char *output = NULL;
	
	/* Process arguments */
	tenapp_init(argc, argv, "TDF encoder/decoder generator", "2.0");
	argc--;
	argv++;
	optcnt = arg_parse_arguments (cmdl_opts, argc, argv);
	argc -= optcnt;
	argv += optcnt;
	if (argc > 3)
		MSG_too_many_arguments ();

	for (; argc > 0; argc--, argv++) {
		if (input == NULL) {
			input = *argv;
		} else if (templ == NULL) {
			templ = *argv;
		} else if (output == NULL) {
			output = *argv;
		}
	}
	
	/* Process the input */
	builtin_sorts ();
	if (open_file (input)) {
		SPECIFICATION spec = NULL_spec;
		ADVANCE_LEXER;
		read_spec (&spec);
		close_file ();
		if (!IS_NULL_spec (spec)) {
			COMMAND cmd = NULL_cmd;
			if (open_file (templ)) {
				MAKE_cmd_simple (1, "<dummy>", cmd);
				cmd = read_template (cmd);
				close_file ();
			}
			if (!IS_NULL_cmd (cmd)) {
				output_spec (output, spec, cmd);
			}
		}
	}
	tenapp_exit();
	return (0);
}
