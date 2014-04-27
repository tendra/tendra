/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <shared/error.h>
#include <shared/getopt.h>

#include <out/c.h>
#include <out/h.h>
#include <out/dot.h>
#include <out/common.h>

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
	read_lex(ast->global);

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

int
main(int argc, char **argv)
{
	struct ast *ast;
	struct out *out;

	struct out {
		const char *lang;
		const signed int infiles;
		const signed int outfiles;
		void (*out_all)(struct options *, struct ast *);
		const char *options;
	} outs[] = {
#define COMMON "C:t:l:p:i:vh"
		{ "c",    2, 1, c_out_all,   COMMON },
		{ "h",    2, 1, h_out_all,   COMMON },
		{ "dot",  1, 1, dot_out_all, COMMON },
		{ "test", 1, 0, NULL,        COMMON },
#undef COMMON
	};

	/* TODO: These are language-specific; see options.h */
	opt.lexi_prefix      = "lexi_";
	opt.interface_prefix = NULL;

	/* default to C output */
	out = &outs[0];

	set_progname(argv[0], "2.0");

	{
		int c;

		while (c = getopt(argc, argv, out->options), c != -1) {
			switch(c) {
			case 'l': {
				int i;

				for (i = sizeof outs / sizeof *outs - 1; i >= 0; i--) {
					if (0 == strcmp(optarg, outs[i].lang)) {
						out = &outs[i];
						break;
					}
				}

				if (i < 0) {
					/* TODO: I suppose we could automate writing this list of languages, too */
					error(ERROR_FATAL, "Unrecognised language '%s'. The supported languages are: C (default), Dot and test",
						optarg);
				}

				break;
			}

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

	/* Process input file */
	ast = init_ast();

	set_builtin_type(ast, &ast->lexi_char_type,     "CHARACTER");
	set_builtin_type(ast, &ast->lexi_string_type,   "STRING");
	set_builtin_type(ast, &ast->lexi_int_type,      "INTEGER");
	set_builtin_type(ast, &ast->lexi_terminal_type, "TERMINAL");

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

	argv += out->infiles;

	/* Generate output */
 	if (ast->global->white == NULL) {
		ast->global->white = make_group(ast->global, "white", " \t\n");
	}

	if (out->out_all != NULL) {
		assert(out->outfiles == 1);

		if (0 != strcmp(argv[0], "-")) {
			stdout = freopen(argv[0], "w", stdout);
			if (stdout == NULL) {
				perror(argv[0]);
				exit(1);
			}
		}

		out_generated_by_lexi(stdout);

		out->out_all(&opt, ast);

		fclose(stdout);
	}

	return exit_status;
}

