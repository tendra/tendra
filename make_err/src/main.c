/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/error.h>
#include <shared/getopt.h>

#include "obj_c/errors.h"
#include "lex.h"
#include "process.h"
#include "syntax.h"


int
main(int argc, char **argv)
{
	char *input;
	char *output;
	int act;

	input  = NULL;
	output = NULL;
	act = 0;

	set_progname(argv[0], "1.1");

	{
		int c;

		while (c = getopt(argc, argv, "dnuv"), c != -1) {
			switch (c) {
			case 'd': act = 1; break;
			case 'n': act = 2; break;
			case 'u': act = 3; break;

			case 'v':
				report_version();
				break;

			default:
				return 1;
			}
		}

		argc -= optind;
		argv += optind;
	}

	/* Check arguments */
	if (argc >= 1) {
		input = argv[0];
	}

	if (argc == 2) {
		output = argv[1];
	}

	if (argc > 2) {
		error(ERROR_FATAL, "Too many arguments");
	}

	/* Process the input */
	process_file(input);
	output_all(output, act);

	return exit_status;
}

