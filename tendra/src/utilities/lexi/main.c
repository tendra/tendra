/*
 * Copyright (c) 2002, 2003, The Tendra Project <http://www.ten15.org/>
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
 *  		 Crown Copyright (c) 1997
 *
 *  This TenDRA(r) Computer Program is subject to Copyright
 *  owned by the United Kingdom Secretary of State for Defence
 *  acting through the Defence Evaluation and Research Agency
 *  (DERA).  It is made available to Recipients with a
 *  royalty-free licence for its use, reproduction, transfer
 *  to other parties and amendment for any purpose not excluding
 *  product development provided that any such use et cetera
 *  shall be deemed to be acceptance of the following conditions:-
 *
 *      (1) Its Recipients shall ensure that this Notice is
 *      reproduced upon any copies or amended versions of it;
 *
 *      (2) Any amended version of it shall be clearly marked to
 *      show both the nature of and the organisation responsible
 *      for the relevant amendment or amendments;
 *
 *      (3) Its onward transfer from a recipient to another
 *      party shall be deemed to be that party's acceptance of
 *      these conditions;
 *
 *      (4) DERA gives no warranty or assurance as to its
 *      quality or suitability for any purpose and DERA accepts
 *      no liability whatsoever in relation to any use to which
 *      it may be put.
 *
 * $TenDRA$
 */


#include "config.h"
#include "argparse.h"
#include "msgcat.h"
#include "tenapp.h"

#include "catstdn.h"
#include "char.h"
#include "lex.h"
#include "output.h"
#include "syntax.h"


static unsigned output_opts = OUTPUT_MAIN;

static void
opt_output(char *option, void *closure)
{
	UNUSED (closure);

	switch (option[0]) {
	case 'f':
		output_opts |= OUTPUT_FUNCTIONS;
		break;
	case 'k':
		output_opts |= OUTPUT_KEYWORDS;
		break;
	case 'm':
		output_opts |= OUTPUT_MACROS;
		break;
	case 't':
		output_opts |= OUTPUT_TABLE;
		break;
	}
}

static void
opt_prefix(char *option, void *closure, char *value)
{
	UNUSED(option);
	UNUSED(closure);

	sid_prefix = value;
}

static void opt_help(char *option, void *closure);

static ArgListT cmdl_opts[] = {
	AP_OPT_EMPTY	(version, 	'V', NULL, arg_std_version),
	AP_OPT_EMPTY	(functions,	'f', NULL, opt_output),
	AP_OPT_EMPTY	(help,		'h', "help", opt_help),
	AP_OPT_EMPTY	(keywords,	'k', NULL, opt_output),
	AP_OPT_EITHER	(prefix,	'l', NULL, opt_prefix),
	AP_OPT_EMPTY	(macros,	'm', NULL, opt_output),
	AP_OPT_EMPTY	(table,		't', NULL, opt_output),
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


/*
 *    MAIN ROUTINE
 *
 *    This is the main routine.  It processes the command-line options,
 *    reads the input file, and writes the output files.
 */

int
main(int argc, char **argv)
{
    OStreamT lex_ostream;
    int optcnt;
    char *input = NULL;
    char *output = NULL;

    /* Process arguments */
    tenapp_init(argc, argv, "Lexical analyser", "1.3");
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

    /* Process input file */
    process_file (input);

    /* Generate output */
    if (exit_status == EXIT_SUCCESS) {
		if (white_space == NULL) white_space = make_string (" \t\n");
		if (output == NULL || streq (output, "-")) {
			lex_output = ostream_output;
			output = NULL;
		} else {
			lex_output = &lex_ostream;
			if (!ostream_open(lex_output, output)) {
				MSG_cant_open_input_file(output);
			}
		}
		output_all (output_opts);
		if (output) ostream_close(lex_output);
    } else {
		MSG_had_errors();
    }
    tenapp_exit();
    return (0);
}
