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

#include "error.h"

#include "char.h"
#include "lex.h"
#include "lctlex.h"
#include "syntax.h"
#include "output-c/c-output.h"
#include "output-dot/dot-output.h"
#include "options.h"

/*
 * XXX This is made global specifically for <make-copyright> in syntax.act.
 * It shouldn't be global.
 */
cmd_line_options options;

/*
 * Usage
 */
static void
report_usage(void) {
	fputs("usage: lexi [-vh] [-a] [-t token-prefix] [-p lexi-prefix] "
		"[-l output-language] [-C copyright-notice-file] "
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
	lexer_parse_tree top_level;
 	cmd_line_options_init(&options);
	int i;

#define COMMON_OPTIONS "C:t:l:p:vh"
	struct outputs {
		const char *language;
		const signed int inputfiles;
		const signed int outputfiles;
		void (*output_all)(cmd_line_options *, lexer_parse_tree *);
		const char *options;
	} outputs[] = {
		{ "C90", 2, 2, c_output_all, COMMON_OPTIONS	},
		{ "C99", 2, 2, c_output_all, COMMON_OPTIONS "a"	},
		{ "Dot", 1, 1, dot_output_all, COMMON_OPTIONS	},
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

		case 'C':
			options.copyright_file=fopen(optarg, "r");
			if ( options.copyright_file == NULL) 
				error(ERROR_FATAL, "Can't open copyright file, %s", optarg);
			break;

		case 'v':
			report_version();
			return EXIT_SUCCESS;

		case 'p':
			options.lexi_prefix=optarg;
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
	 * This is carried through for output routines shared between multiple
	 * languages to inspect, should they need to.
	 */
	options.language = output->language;

	/* Check arguments (+1 for input file) */
	if (argc < output->outputfiles + output->inputfiles) {
		report_usage();
		error(ERROR_FATAL, "Not enough arguments");
		/* TODO resolve - here, and pass FILE * to process_file();
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
	init_lexer_parse_tree(&top_level);
	process_file(argv[0],&top_level);

	if (exit_status != EXIT_SUCCESS) {
		error(ERROR_FATAL, "Terminating due to previous errors");
		return exit_status;
	}

	if(output->inputfiles>1) {
		process_lctfile(argv[1]);
	}

	if (exit_status != EXIT_SUCCESS) {
		error(ERROR_FATAL, "Terminating due to previous errors in lct file");
		return exit_status;
	}

	/* Generate output */
 	if (top_level.global_zone->white_space == NULL)
		top_level.global_zone->white_space = make_group(top_level.global_zone,"white",
							  make_string(" \t\n",top_level.global_zone));

	output->output_all(&options, &top_level);

	for(i = 0; i < output->outputfiles; i++) {
		if(options.outputfile[i].file) {
			fclose(options.outputfile[i].file);
		}
	}
	if(options.copyright_file) {
		fclose(options.copyright_file);
	}

	return exit_status;
}

