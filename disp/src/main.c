/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/check.h>
#include <shared/error.h>

#include <tdf/magic.h>

#include "config.h"

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
#include "utility.h"


#define version_string		"Version: 1.5"


int
main(int argc, char **argv)
{
    char c;
    int input, output;
    int a, b, stage = 1;

    /* Read the arguments */
    for (a = 1; a < argc; a++) {
	if (argv[a][0] == '-') {
	    b = 1;
	    if (argv[a][1] == 'n') {
		maxcol = 0;
		while (c = argv[a][++b], is_digit(c)) {
		    maxcol = 10 * maxcol + digit(c);
		}
	    } else {
		while (c = argv[a][b++], c != 0) {
		    switch (c) {
			case 'd': dflag = 0; break;
			case 'g': diagnostics = 1; break;
			case 'h': helpflag = 0; break;
			case 'i' : /* Compatibility */ break ;
			case 'p': progress = 1; break;
			case 'q': quickflag = 1; break;
			case 'r': recover = 1; break;
			case 'x': versions = 0; break;
			case 'A': {
			    diagnostics = 1;
			    show_usage = 1;
			    versions = 1;
			    break;
			}
			case 'D': dump = 1; break;
			case 'E': show_stuff = 1; break;
			case 'S': skip_pass = 0; break;
			case 'T': show_skip = 1; break;
			case 'U': show_usage = 1; break;
			case 'V': dumb_mode = 1; break;
			case 'W': warn_undeclared = 1; break;

			case 'v': {
			    /* Version number */
			    IGNORE fprintf(stderr, "%s: %s",
					     progname, version_string);
			    IGNORE fprintf(stderr, ", TDF %d.%d",
					     version_major, version_minor);
			    IGNORE fprintf(stderr, " (tendra.org)\n");
			    return 0;
			}
		    }
		}
	    }
	} else {
	    /* Handle files */
	    switch (stage) {
		case 1 : input = a; stage = 2; break;
		case 2 : output = a; stage = 3; break;
		default : stage = 4; break;
	    }
	}
    }

    /* Open the files */
    switch (stage) {
	case 1: {
	    fatal_error("Not enough arguments");
	    break;
	}
	case 2: {
	    SET(input);
	    open_files(argv[input], NULL);
	    break;
	}
	case 3: {
	    SET(input);
	    SET(output);
	    open_files(argv[input], argv[output]);
	    break;
	}
	default : {
	    fatal_error("Too many arguments");
	    break;
	}
    }

    /* Perform binary dump if required */
    if (dump) {
	long f;
	int bits = 0, n = 1;
	while (f = fetch(1), !read_error) {
	    if (n == 1)IGNORE fprintf(pp_file, "%d :\t", bits / 8);
	    IGNORE fputc((f ? '1' : '0'), pp_file);
	    if (n == 64) {
		IGNORE fputc('\n', pp_file);
		n = 1;
	    } else {
		if (n % 8 == 0)IGNORE fputc(' ', pp_file);
		n++;
	    }
	    bits++;
	}
	if (n != 1)IGNORE fputc('\n', pp_file);
	exit(0);
    }

    /* Call the main routines */
    if (diagnostics || show_usage) do_foreign_sorts = 1;
    init_foreign_sorts();
    initialize_tree();
    de_capsule();
    pretty_tree();
    return exit_status;
}
