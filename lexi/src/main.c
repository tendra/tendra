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
#include "output.h"
#include "syntax.h"
#include "options.h"

/*
 * Usage
 */
static void
report_usage(void) {
	fputs("usage: lexi [-vha] [-t token-prefix] [-p lexi-prefix] [-l output-language] [-C copyright-notice-file] input-file output-file header-output-file\n", stdout);
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
	cmd_line_options options;
 	cmd_line_options_init(&options);

	/* Process arguments */
	set_progname(argv [0], "2.0");
	while ((optc = getopt(argc, argv, "C:t:l:p:vha")) != -1) {
		switch(optc) {
		/* TODO document flag to disable including <assert.h> for C89-only systems */
		case 'a':
			options.generate_asserts = false;
			break;

		case 't':
			token_prefix = optarg;
			break;

		case 'l':
			if(strcasecmp(optarg, "C90")) {
				error(ERROR_FATAL, "Unrecognised language '%s'. The supported language is: C90 (default)",
					optarg);
			}
			break;

		case 'C':
			options.copyright_filename_cmd_line = optarg;
			options.copyright_file_cmd_line=fopen(options.copyright_filename_cmd_line,"r");
			if ( options.copyright_file_cmd_line == NULL) 
				error(ERROR_FATAL, "Can't open copyright file, %s", options.copyright_filename_cmd_line);
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

	/* Check arguments */
	if (argc < 3) {
		report_usage();
		error(ERROR_FATAL, "Not enough arguments");
		/* TODO resolve - here, and pass FILE * to process_file();
		 * we can permit argc < 1 for stdin */
	}

	if (argc > 3) {
		report_usage();
		error(ERROR_FATAL, "Too many arguments");
	}

	/* Open output file */
	options.lex_output = !strcmp(argv[1], "-") ? stdout : fopen(argv[1], "w");
	options.lex_output_filename = !strcmp(argv[1], "-") ? "" : argv[1];
	if (options.lex_output == NULL) {
		error(ERROR_FATAL, "Can't open output file, %s", argv[1]);
		/* TODO perror for cases like this */
		return EXIT_FAILURE;
	}

	/* Open output header */
	options.lex_output_h = !strcmp(argv[2], "-") ? stdout : fopen(argv[2], "w");
	options.lex_output_h_filename = !strcmp(argv[2], "-") ? "" : argv[2];
	if (options.lex_output_h == NULL) {
		error(ERROR_FATAL, "Can't open output file, %s", argv[2]);
		/* TODO perror for cases like this */
		return EXIT_FAILURE;
	}

	/* Process input file */
	init_lexer_parse_tree(&top_level);
	process_file(argv[0],&top_level);

	if (exit_status != EXIT_SUCCESS) {
		error(ERROR_FATAL, "Terminating due to previous errors");
		return exit_status;
	}

	/* Generate output */
 	if (top_level.global_zone->white_space == NULL)
		top_level.global_zone->white_space = make_group(top_level.global_zone,"white",
							  make_string(" \t\n",top_level.global_zone));

	/* TODO pass output fd here; remove globals */
	output_all(&options, &top_level);

	fclose(options.lex_output);
	fclose(options.lex_output_h);

	return exit_status;
}

