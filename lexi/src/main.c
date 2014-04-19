/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <shared/error.h>
#include <shared/getopt.h>

#include <adt/tree.h>

#include <out/c.h>
#include <out/dot.h>

#include "lexer.h"
#include "lctlexer.h"
#include "syntax.h"
#include "lctsyntax.h"
#include "options.h"

static struct options opt;

static void
process_lxi_file(char *nm, struct lexer_parse_tree *top_level)
{
	FILE *input;

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

	if (nm != NULL) {
		fclose(input);
	}

	return;
}

static void
process_lct_file(struct lexer_parse_tree* parse_tree, char* fn)
{
	FILE *lct_file;

	crt_line_no = 1;

	lct_file = fopen(fn, "r");
	if (lct_file == NULL) {
		error(ERROR_SERIOUS, "Can't open input file, '%s'", fn);
		return;
	}

	crt_file_name = fn;
	init_lct_parse_tree(&global_lct_parse_tree);
	lexi_lct_init(&lct_lexer_state, lct_file);

	ADVANCE_LCT_LEXER;

	lxi_top_level = parse_tree;
	read_lct_unit();

	fclose(lct_file);
}

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
open_filestream(const char *name)
{
	return 0 == strcmp(name, "-") ? stdout : fopen(name, "w");
}

int
main(int argc, char **argv)
{
	struct lexer_parse_tree *top_level;
	struct outputs *output;
	int i;

	struct outputs {
		const char *language;
		const signed int inputfiles;
		const signed int outputfiles;
		void (*output_all)(struct options *, struct lexer_parse_tree *);
		const char *options;
	} outputs[] = {
#define COMMON "C:t:l:p:i:vh"
		{ "C90",  2, 2, c_output_all,   COMMON "a" },
		{ "C99",  2, 2, c_output_all,   COMMON "a" },
		{ "Dot",  1, 1, dot_output_all, COMMON     },
		{ "test", 1, 0, NULL,           COMMON     },
#undef COMMON
	};

 	options_init(&opt);

	/* default to C90 output */
	output = &outputs[0];

	set_progname(argv [0], "2.0");

	{
		int c;

		while (c = getopt(argc, argv, output->options), c != -1) {
			switch(c) {
			case 'l': {
				int i;

				for (i = sizeof outputs / sizeof *outputs - 1; i >= 0; i--) {
					if (0 == strcasecmp(optarg, outputs[i].language)) {
						output = &outputs[i];
						break;
					}
				}

				if (i < 0) {
					/* TODO I suppose we could automate writing this list of languages, too */
					error(ERROR_FATAL, "Unrecognised language '%s'. The supported languages are: C90 (default), C99 and Dot",
						optarg);
				}

				break;
			}

			case 'a': opt.generate_asserts = true;   break;
			case 't': token_prefix         = optarg; break;
			case 'p': opt.lexi_prefix      = optarg; break;
			case 'i': opt.interface_prefix = optarg; break;

			default:
				/* getopt will report error */
			case 'h': report_usage();   return EXIT_FAILURE;
			case 'v': report_version(); return EXIT_SUCCESS;
			}
		}

		argc -= optind;
		argv += optind;
	}

	/*
	 * Default to the lexi_prefix if no interface prefix is given. This maintains
	 * compatibility should -p be given and -i not be specified.
	 */
	if (opt.interface_prefix == NULL) {
		opt.interface_prefix = opt.lexi_prefix;
	}

	/*
	 * This is carried through for output routines shared between multiple
	 * languages to inspect, should they need to.
	 */
	opt.language = output->language;

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
	for (i = 0; i < output->outputfiles; i++) {
		opt.output[i].name = argv[i + output->inputfiles];
		opt.output[i].file = open_filestream(argv[i + output->inputfiles]);

		if (!opt.output[i].file) {
			error(ERROR_FATAL, "Can't open output file, %s", argv[i + 1]);
			/* TODO perror for cases like this */
			return EXIT_FAILURE;
		}
	}

	/* Process input file */
	top_level = init_lexer_parse_tree();

	set_predefined_char_lexi_type    (top_level, "CHARACTER", "char");
	set_predefined_string_lexi_type  (top_level, "STRING",    "char *");
	set_predefined_int_lexi_type     (top_level, "INTEGER",   "int");
	set_predefined_terminal_lexi_type(top_level, "TERMINAL");

	process_lxi_file(argv[0], top_level);

	if (exit_status != EXIT_SUCCESS) {
		error(ERROR_FATAL, "Terminating due to previous errors");
		return exit_status;
	}

	if (output->inputfiles > 1) {
		process_lct_file(top_level, argv[1]);
	}

	if (exit_status != EXIT_SUCCESS) {
		error(ERROR_FATAL, "Terminating due to previous errors in lct file");
		return exit_status;
	}

	/* Generate output */
 	if (tree_get_globalzone(top_level)->white_space == NULL) {
		tree_get_globalzone(top_level)->white_space = make_group(tree_get_globalzone(top_level), "white", " \t\n");
	}

	if (output->output_all!=NULL) {
		output->output_all(&opt, top_level);
	}

	for (i = 0; i < output->outputfiles; i++) {
		if (opt.output[i].file == NULL) {
			continue;
		}

		fclose(opt.output[i].file);
	}

	return exit_status;
}

