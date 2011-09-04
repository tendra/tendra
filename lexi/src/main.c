/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <shared/error.h>

#include "adt/tree.h"

#include "lexer.h"
#include "lctlexer.h"
#include "syntax.h"
#include "lctsyntax.h"
#include "output-c/c-output.h"
#include "output-dot/dot-output.h"
#include "options.h"

/*
 * XXX This is made global specifically for <make-copyright> in syntax.act.
 * It shouldn't be global.
 */
cmd_line_options options;



/*
    PROCESS FILE

    This routine processes the lxi input file.
*/

static void
process_lxi_file(char *nm,lexer_parse_tree* top_level)
{
	FILE* input;
	crt_line_no = 1;
	if (nm == NULL || !strcmp(nm, "-")) {
		crt_file_name = "<stdin>";
		input = stdin;
		nm = NULL;
	} else {
		crt_file_name = nm;
		input = fopen(nm, "r");
		if (input == NULL) {
			error(ERROR_SERIOUS, "Can't open input file, '%s'", nm);
			return;
		}
	}
	lexi_init(&lexer_state, input);
	ADVANCE_LXI_LEXER;
	read_lex(tree_get_globalzone(top_level));
	if (nm)fclose(input);
	return;
}

/*
    PROCESS FILE

    This routine processes the lct input file.
*/
static void 
process_lct_file (lexer_parse_tree* parse_tree, char* fn) 
{

	crt_line_no = 1 ;
	FILE* lct_file;
	if (!(lct_file=fopen(fn,"r"))) {
		error(ERROR_SERIOUS, "Can't open input file, '%s'", fn);
		return; /*error message*/
	}
	crt_file_name = fn;
	init_lct_parse_tree(&global_lct_parse_tree) ;
	lexi_lct_init(&lct_lexer_state, lct_file) ;
	ADVANCE_LCT_LEXER ;

	lxi_top_level=parse_tree;
	read_lct_unit();
	fclose(lct_file);
}

/*
 * Usage
 */
static void
report_usage(void) {
	fputs("usage: lexi [-vh] [-a] [-t token-prefix] [-p lexi-prefix] "
		"[-i interface-prefix] [-l output-language]  "
		"input-file [lct-input-file] [output-file ...]\n", stdout);
}

/*
 * Open a file for writing, defaulting to stdout if the name given is "-".
 */
static FILE *
open_filestream(const char *name) {
	return !strcmp(name, "-") ? stdout : fopen(name, "w");
}

/*
 * Main routine
 *
 * This is the main routine.  It processes the command-line options,
 * reads the input file, and writes the output files.
 */
int
main(int argc, char **argv)
{
	int optc;
	lexer_parse_tree *top_level;
 	cmd_line_options_init(&options);
	int i;

#define COMMON_OPTIONS "C:t:l:p:i:vh"
	struct outputs {
		const char *language;
		const signed int inputfiles;
		const signed int outputfiles;
		void (*output_all)(cmd_line_options *, lexer_parse_tree *);
		const char *options;
	} outputs[] = {
		{ "C90", 2, 2, c_output_all, COMMON_OPTIONS "a" },
		{ "C99", 2, 2, c_output_all, COMMON_OPTIONS "a"	},
		{ "Dot", 1, 1, dot_output_all, COMMON_OPTIONS	},
		{ "test", 1, 0, NULL, COMMON_OPTIONS	},
	};

	/* Default to C90 output */
	struct outputs *output = &outputs[0];

	/* Process arguments */
	set_progname(argv [0], "2.0");
	while ((optc = getopt(argc, argv, output->options)) != -1) {
		switch(optc) {
		case 'a':
			options.generate_asserts = true;
			break;

		case 't':
			token_prefix = optarg;
			break;

		case 'l': {
			int i;

			for(i = sizeof outputs / sizeof *outputs - 1; i >= 0; i--) {

				if(!strcasecmp(optarg, outputs[i].language)) {
					output = &outputs[i];
					break;
				}
			}

			if(i < 0) {
				/* TODO I suppose we could automate writing this list of languages, too */
				error(ERROR_FATAL, "Unrecognised language '%s'. The supported languages are: C90 (default), C99 and Dot",
					optarg);
			}

			break;
		}

		case 'v':
			report_version();
			return EXIT_SUCCESS;

		case 'p':
			options.lexi_prefix=optarg;
			break;

		case 'i':
			options.interface_prefix = optarg;
			break;

		default:
			/* getopt will report error */

		case 'h':
			report_usage();
			return EXIT_FAILURE;
		}
	}
	argc -= optind;
	argv += optind;

	/*
	 * Default to the lexi_prefix if no interface prefix is given. This maintains
	 * compatibility should -p be given and -i not be specified.
	 */
	if (options.interface_prefix == NULL) {
		options.interface_prefix = options.lexi_prefix;
	}

	/*
	 * This is carried through for output routines shared between multiple
	 * languages to inspect, should they need to.
	 */
	options.language = output->language;

	/* Check arguments (+1 for input file) */
	if (argc < output->outputfiles + output->inputfiles) {
		report_usage();
		error(ERROR_FATAL, "Not enough arguments");
		/* TODO resolve - here, and pass FILE * to process_lxi_file();
		 * we can permit argc < 1 for stdin */
	}

	if (argc > output->outputfiles + output->inputfiles) {
		report_usage();
		error(ERROR_FATAL, "Too many arguments");
	}

	/*
	 * Open each relevant file for output. Note that argv[0]
	 * contains the input file.
	 */
	for(i = 0; i < output->outputfiles; i++) {
		options.outputfile[i].name = argv[i + output->inputfiles];
		options.outputfile[i].file = open_filestream(argv[i + output->inputfiles]);

		if(!options.outputfile[i].file) {
			error(ERROR_FATAL, "Can't open output file, %s", argv[i + 1]);
			/* TODO perror for cases like this */
			return EXIT_FAILURE;
		}
	}

	/* Process input file */
	top_level = init_lexer_parse_tree();

	set_predefined_char_lexi_type(top_level, "CHARACTER", "char");
	set_predefined_string_lexi_type(top_level, "STRING", "char*");
	set_predefined_int_lexi_type(top_level, "INTEGER", "int");
	set_predefined_terminal_lexi_type(top_level, "TERMINAL");


	process_lxi_file(argv[0], top_level);

	if (exit_status != EXIT_SUCCESS) {
		error(ERROR_FATAL, "Terminating due to previous errors");
		return exit_status;
	}

	if(output->inputfiles>1) {
		process_lct_file(top_level, argv[1]);
	}

	if (exit_status != EXIT_SUCCESS) {
		error(ERROR_FATAL, "Terminating due to previous errors in lct file");
		return exit_status;
	}

	/* Generate output */
 	if (tree_get_globalzone(top_level)->white_space == NULL)
		tree_get_globalzone(top_level)->white_space = make_group(tree_get_globalzone(top_level), "white", " \t\n");

	if(output->output_all!=NULL)
		output->output_all(&options, top_level);

	for(i = 0; i < output->outputfiles; i++) {
		if(options.outputfile[i].file) {
			fclose(options.outputfile[i].file);
		}
	}

	
	tree_close_copyright_files(top_level);

	return exit_status;
}

