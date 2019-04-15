/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#include <shared/error.h>
#include <shared/getopt.h>

#include "obj_c/tdf.h"
#include "obj_c/cmd_ops.h"
#include "obj_c/spec_ops.h"

#include "input.h"
#include "lex.h"
#include "output.h"
#include "syntax.h"

static void
report_usage(FILE *f) {
	fputs("Usage: make_tdf [-vh] [spec-file] [template-file] [output-file]\n"
		  "\n"
		  "Missing file arguments or '-' will be interpreted as stdin/stdout\n", f);
}


int
main(int argc, char **argv)
{
	int a;

	char *input  = NULL;
	char *templ  = NULL;
	char *output = NULL;

	set_progname(argv[0], "2.0");

	{
		int c;

		while (c = getopt(argc, argv, "vh"), c != -1) {
			switch (c) {
			case 'v':
				report_version(stdout);
				return 0;
			case 'h':
				report_usage(stdout);
				return 0;
			default:
				fprintf(stderr, "Try '%s -h' for more information.\n", argv[0]);
				return 1;
			}

			argc -= optind;
			argv += optind;
		}
	}

	for (a = 1; a < argc; a++) {
		char *arg;

		arg = argv[a];

		if (input == NULL) {
			input = arg;
		} else if (templ == NULL) {
			templ = arg;
		} else if (output == NULL) {
			output = arg;
		} else {
			error(ERR_WARN, "Too many arguments");
		}
	}

	builtin_sorts();

	if (open_file(input)) {
		SPECIFICATION spec = NULL_spec;
		ADVANCE_LEXER;
		read_spec(&spec);
		close_file();

		if (!IS_NULL_spec(spec)) {
			COMMAND cmd = NULL_cmd;

			if (open_file(templ)) {
				MAKE_cmd_simple(1, "<dummy>", cmd);
				cmd = read_template(cmd);
				close_file();
			}

			if (!IS_NULL_cmd(cmd)) {
				output_spec(output, spec, cmd);
			}
		}
	}

	return exit_status;
}

