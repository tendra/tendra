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

#include <out/c.h>
#include <out/dot.h>

#include "ast.h"
#include "lexer.h"
#include "lctlexer.h"
#include "syntax.h"
#include "lctsyntax.h"
#include "options.h"

static struct options opt;

static void
process_lxi_file(char *path, struct ast *ast)
{
	FILE *input;

	crt_line_no = 1;

	if (path == NULL || !strcmp(path, "-")) {
		crt_file_name = "<stdin>";
		input = stdin;
		path = NULL;
	} else {
		crt_file_name = path;
		input = fopen(path, "r");
		if (input == NULL) {
			error(ERROR_SERIOUS, "Can't open input file, '%s'", path);
			return;
		}
	}

	lexi_init(&lexer_state, input);

	ADVANCE_LXI_LEXER;
	read_lex(tree_get_globalzone(ast));

	if (path != NULL) {
		fclose(input);
	}

	return;
}

static void
process_lct_file(struct ast *ast, char *path)
{
	FILE *lct_file;

	crt_line_no = 1;

	lct_file = fopen(path, "r");
	if (lct_file == NULL) {
		error(ERROR_SERIOUS, "Can't open input file, '%s'", path);
		return;
	}

	crt_file_name = path;
	init_lct_ast(&lct_ast);
	lexi_lct_init(&lct_lexer_state, lct_file);

	ADVANCE_LCT_LEXER;

	lxi_ast = ast;
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
	struct ast *ast;
	struct out *out;
	int i;

	struct out {
		const char *lang;
		const signed int infiles;
		const signed int outfiles;
		void (*out_all)(struct options *, struct ast *);
		const char *options;
	} outs[] = {
#define COMMON "C:t:l:p:i:vh"
		{ "C90",  2, 2, c_out_all,   COMMON "a" },
		{ "C99",  2, 2, c_out_all,   COMMON "a" },
		{ "Dot",  1, 1, dot_out_all, COMMON     },
		{ "test", 1, 0, NULL,        COMMON     },
#undef COMMON
	};

 	options_init(&opt);

	/* default to C90 output */
	out = &outs[0];

	set_progname(argv [0], "2.0");

	{
		int c;

		while (c = getopt(argc, argv, out->options), c != -1) {
			switch(c) {
			case 'l': {
				int i;

				for (i = sizeof outs / sizeof *outs - 1; i >= 0; i--) {
					if (0 == strcasecmp(optarg, outs[i].lang)) {
						out = &outs[i];
						break;
					}
				}

				if (i < 0) {
					/* TODO: I suppose we could automate writing this list of languages, too */
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
	opt.lang = out->lang;

	/* Check arguments (+1 for input file) */
	if (argc < out->outfiles + out->infiles) {
		report_usage();
		error(ERROR_FATAL, "Not enough arguments");
		/* TODO: resolve - here, and pass FILE * to process_lxi_file();
		 * we can permit argc < 1 for stdin */
	}

	if (argc > out->outfiles + out->infiles) {
		report_usage();
		error(ERROR_FATAL, "Too many arguments");
	}

	/*
	 * Open each relevant file for output. Note that argv[0]
	 * contains the input file.
	 */
	for (i = 0; i < out->outfiles; i++) {
		opt.out[i].name = argv[i + out->infiles];
		opt.out[i].file = open_filestream(argv[i + out->infiles]);

		if (!opt.out[i].file) {
			error(ERROR_FATAL, "Can't open output file, %s", argv[i + 1]);
			/* TODO: perror for cases like this */
			return EXIT_FAILURE;
		}
	}

	/* Process input file */
	ast = init_ast();

	set_builtin_char_lexi_type    (ast, "CHARACTER");
	set_builtin_string_lexi_type  (ast, "STRING");
	set_builtin_int_lexi_type     (ast, "INTEGER");
	set_builtin_terminal_lexi_type(ast, "TERMINAL");

	process_lxi_file(argv[0], ast);

	if (exit_status != EXIT_SUCCESS) {
		error(ERROR_FATAL, "Terminating due to previous errors");
		return exit_status;
	}

	if (out->infiles > 1) {
		process_lct_file(ast, argv[1]);
	}

	if (exit_status != EXIT_SUCCESS) {
		error(ERROR_FATAL, "Terminating due to previous errors in lct file");
		return exit_status;
	}

	/* Generate output */
 	if (tree_get_globalzone(ast)->white_space == NULL) {
		tree_get_globalzone(ast)->white_space = make_group(tree_get_globalzone(ast), "white", " \t\n");
	}

	if (out->out_all != NULL) {
		out->out_all(&opt, ast);
	}

	for (i = 0; i < out->outfiles; i++) {
		if (opt.out[i].file == NULL) {
			continue;
		}

		fclose(opt.out[i].file);
	}

	return exit_status;
}

