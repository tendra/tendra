/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stdlib.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/getopt.h>
#include <shared/string.h>

#include <tdf/magic.h>

#include "types.h"
#include "read_types.h"
#include "analyser.h"
#include "check.h"
#include "de_types.h"
#include "de_capsule.h"
#include "dot.h"
#include "enc_cap.h"
#include "eval.h"
#include "file.h"
#include "help.h"
#include "node.h"
#include "read_cap.h"
#include "shape.h"
#include "tdf.h"
#include "table.h"
#include "utility.h"
#include "write.h"



static void
output_option(char *arg, bool t)
{
	bool *p = NULL;

	if (streq(arg, "tokdecs"))
		p = &show_tokdecs;
	else if (streq(arg, "tokdefs"))
		p = &show_tokdefs;
	else if (streq(arg, "aldecs"))
		p = &show_aldecs;
	else if (streq(arg, "aldefs"))
		p = &show_aldefs;
	else if (streq(arg, "tagdecs"))
		p = &show_tagdecs;
	else if (streq(arg, "tagdefs"))
		p = &show_tagdefs;

	if (p == NULL)
		fatal_error("Unrecognised output option: %s", arg);

	if (t) {
		show_tokdecs = 0;
		show_tokdefs = 0;
		show_aldefs  = 0;
		show_tagdecs = 0;
		show_tagdefs = 0;
	}

	*p = t;
}


int
main(int argc, char **argv)
{
	int status = 0;
	bool expand = 0;
	bool evaluate = 0;
	bool lib_input = 0;
	bool output_next = 0;
	bool help_output;

	void(*input_fn)(void);
	void(*output_fn)(void);

	set_progname("tnc", "1.9");

	/* Default action : read text, encode TDF capsule */
	input_fn    = read_capsule;
	output_fn   = enc_capsule;
	text_input  = 1;
	text_output = 0;
	help_output = 0;

	/* Initialize internal tables */
	input  = stdin;
	output = stdout;
	init_tables();
	init_constructs();

	{
		int c;

		while (c = getopt(argc, argv, "acdefgln:opqrtuvwx" "HI:L:V"), c != -1) {
			switch (c) {
			case 'a':
				/* Expand token definitions */
				expand = 1;
				break;

			case 'c':
				/* Switch on shape checking */
				init_shapes();
				do_check = 1;
				break;

			case 'd':
				/* Decode mode */
				input_fn   = de_capsule;
				text_input = 0;
				break;

			case 'e':
				/* Encode mode */
				output_fn = enc_capsule;
				text_output = 0;
				break;

			case 'f':
				/* Check on form of input and output */
				func_input  = 1;
				func_output = 1;
				break;

			case 'g':
				/* Graphviz mode */
				output_fn   = dot_capsule;
				text_output = 1;
				break;

			case 'l':
				lib_input = 1;
				break;

			case 'n':
				/* "no" / "only" */
				output_option(optarg + (*optarg == '-'), *optarg != '-');
				break;

			case 'o':
				/* Output file */
				open_output(optarg);
				break;

			case 'p':
				/* Pretty printer mode */
				input_fn    = de_capsule;
				output_fn   = print_capsule;
				text_input  = 0;
				text_output = 1;
				break;

			case 'q':
				dont_check = 1;
				break;

			case 'r':
				/* Read mode */
				input_fn   = read_capsule;
				text_input = 1;
				break;

			case 't':
				/* Expand token definitions and evaulate expressions */
				evaluate = 1;
				expand   = 1;
				break;

			case 'u':
				/* Unsorted */
				order_names = 0;
				break;

			case 'v':
				/* Version */
				report_version(stderr);
				IGNORE fprintf(stderr, " (TDF %d.%d)\n",
					VERSION_major, VERSION_minor);
				break;

			case 'w':
				/* Write mode */
				output_fn = print_capsule;
				text_output = 1;
				break;

			case 'x':
				/* Evaluate expressions */
				evaluate = 1;
				break;

			case 'H':
				/* Help option */
				help_output = 1;
				break;

			case 'I':
				add_directory(optarg);
				break;

			case 'L':
				local_prefix = optarg;
				break;

			case 'V':
				/* Verbose */
				print_shapes = 1;
				verbose = 1;
				break;

			default:
				return 1;
			}
		}

		argc -= optind;
		argv += optind;
	}

	/* Help */
	if (help_output) {
		if (argc == 0) {
			help("all");
		} else {
			while (argc--) {
				help(*argv++);
			}
		}

		exit(exit_status);
	}

	switch (argc) {
	case 0:
		break;

	case 1:
		open_input(argv[0], 0);
		break;

	case 2:
		open_input(argv[0], 0);
		open_output(argv[1]);
		break;

	default:
		warning("Too many arguments");
		return 1;
	}

	/* Check on library input */
	if (lib_input && input_fn == de_capsule) {
		input_fn = de_library;
	}

	(*input_fn)();

	if (exit_status == EXIT_SUCCESS || text_output) {
		if (expand)
			expand_all();

		if (evaluate)
			eval_all();

		sort_all();

		(*output_fn)();
	}

	return exit_status;
}

