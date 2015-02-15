/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#include <shared/error.h>

#include "obj_c/tdf.h"
#include "obj_c/cmd_ops.h"
#include "obj_c/spec_ops.h"
#include "input.h"
#include "lex.h"
#include "output.h"
#include "syntax.h"


int
main(int argc, char **argv)
{
    int a;
    int too_many = 0;
    char *input = NULL;
    char *templ = NULL;
    char *output = NULL;

    /* Process arguments */
    set_progname(argv[0], "2.0");
    for (a = 1; a < argc; a++) {
	char *arg = argv[a];
	if (arg[0] == '-' && arg[1]) {
	    int known = 0;
	    switch (arg[1]) {
		case 'v': {
		    if (arg[2]) break;
		    report_version(stdout);
		    known = 1;
		    break;
		}
	    }
	    if (!known) {
		error(ERR_WARN, "Unknown option, '%s'", arg);
	    }
	} else {
	    if (input == NULL) {
		input = arg;
	    } else if (templ == NULL) {
		templ = arg;
	    } else if (output == NULL) {
		output = arg;
	    } else {
		too_many = 1;
	    }
	}
    }

    /* Check arguments */
    if (too_many) error(ERR_WARN, "Too many arguments");

    /* Process the input */
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
