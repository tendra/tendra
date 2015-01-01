/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <time.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>

#include <out/index.h>
#include <out/print.h>
#include <out/env.h>

#include "object.h"
#include "hash.h"
#include "lex.h"
#include "name.h"
#include "syntax.h"
#include "type.h"
#include "utility.h"

/*
 * The default search path for when $INPUT_ENV is not
 * defined. This is also prefixed to user-supplied paths.
 */
#define INPUT_DEFAULT "."


/*
 * INPUT AND OUTPUT DIRECTORIES
 *
 * The variable input_dir consists of a colon-separated list of directories
 * to be searched for input files.  output_incl_dir and output_src_dir
 * give respectively the output include and output source directories,
 * and output_env_dir gives the directory for generating tcc environments.
 */

char *input_dir;
char *output_incl_dir;
char *output_src_dir;
char *output_env_dir;


/*
 * SIGNAL HANDLER
 *
 * This routine handles caught signals.
 */
static void
handler(int sig)
{
    char *s;
    hash_elem *e;

    IGNORE signal(SIGINT, SIG_IGN);
    switch (sig) {
	case SIGINT:  s = "interrupt";              break;
	case SIGSEGV: s = "segmentation violation"; break;
	case SIGTERM: s = "termination signal";     break;
	default :     s = "unknown signal";         break;
    }

    error(ERROR_SERIOUS, "Caught %s", s);
    for (e = sort_hash(files); e != NULL; e = e->next) {
		object *p = e->obj;
		FILE *f = p->u.u_file;
		if (f != NULL) {
			char *nm = p->name;
			if (verbose) {
				IGNORE printf("Removing %s ...\n", nm);
			}
			IGNORE fclose(f);
			IGNORE remove(nm);
		}
    }

    exit(exit_status);
}

/*
 * SEPARATE COMPILATION ROUTINE
 *
 * This routine performs the separate compilation of the set object p.
 */
static void
separate(object *p)
{
	info *i = p->u.u_info;
	static char *exec = NULL;

	if (i->subset || i->file == NULL) {
		return;
	}

	if (exec == NULL) {
		exec = buffer + strlen(buffer);
	}

	IGNORE sprintf(exec, "%s %s", i->api, i->file);
	if (verbose > 1) {
		IGNORE printf("Executing '%s' ...\n", buffer);
	}

	if (system(buffer)) {
		error(ERROR_SERIOUS, "Separate compilation of %s failed", p->name);
	}
}

/*
 * MARK A SET AS IMPLEMENTED
 *
 * This routine recursively marks all implemented subsets of p.
 */
static void
implement(object *p, int depth)
{
    object *q;
    info *i = p->u.u_info;

    if (i == NULL || i->implemented >= depth) {
		return;
	}

    i->implemented = depth;
    for (q = i->elements; q != NULL; q = q->next) {
		if (q->objtype == OBJ_IMPLEMENT) {
			implement(q->u.u_obj, depth + 1);
		}
    }
}

int
main(int argc, char **argv)
{
	int a;
	char *env;
	char *dir = INPUT_DEFAULT;

	char *api    = NULL;
	char *file   = NULL;
	char *subset = NULL;

	object *commands = NULL;
	FILE *preproc_file = NULL;

	int show_index      = 0;
	bool check_only     = 0;
	bool output_env     = 0;
	bool preproc_input  = 0;
	bool separate_files = 0;

	set_progname("tspec", "2.8");
	crt_line_no = 1;
	set_filename("built-in definitions");
	init_hash();
	init_keywords();
	init_types();
	set_filename("command line");
	IGNORE signal(SIGINT, handler);
	IGNORE signal(SIGSEGV, handler);
	IGNORE signal(SIGTERM, handler);

	env = getenv(INPUT_ENV);
	if (env != NULL) {
		input_dir = xstrdup(env);
	} else {
		input_dir = xstrdup(INPUT_DEFAULT);
	}

	env = getenv(OUTPUT_ENV);
	if (env != NULL) {
		output_incl_dir = string_printf("%s/include", env);
		output_src_dir  = string_printf("%s/src", env);
		output_env_dir  = string_printf("%s/env", env);
	}

	env = getenv(INCLUDE_ENV);
	if (env != NULL) {
		output_incl_dir = xstrdup(env);
	}

	env = getenv(SRC_ENV);
	if (env != NULL) {
		output_src_dir = xstrdup(env);
	}

	env = getenv(TCC_ENV);
	if (env != NULL) {
		output_env_dir = xstrdup(env);
	}

	for (a = 1; a < argc; a++) {
		char *arg = argv[a];
		crt_line_no = a;
		if (arg [0] == '-') {
			if (arg [1] == 'I') {
				dir = string_printf("%s:%s", dir, arg + 2);
			} else if (arg [1] == 'O') {
				output_incl_dir = arg + 2;
			} else if (arg [1] == 'S') {
				output_src_dir = arg + 2;
			} else if (arg [1] == 'E') {
				output_env_dir = arg + 2;
			} else {
				char *s;

				for (s = arg + 1; *s != '\0'; s++) {
					switch (*s) {
					case 'a': separate_files  = 0; break;
					case 'b': basename_apis   = 1; break;
					case 'c': check_only      = 1; break;
					case 'd': restrict_depth  = 0; break;
					case 'f': force_output    = 1; break;
					case 'i': show_index      = 1; break;
					case 'l': local_input     = 1; break;
					case 'm': show_index      = 2; break;
					case 'p': preproc_input   = 1; break;
					case 'r': restrict_use    = 1; break;
					case 's': separate_files  = 1; break;
					case 't': allow_long_long = 1; break;
					case 'u': unique_names    = 1; break;
					case 'w': warnings        = 0; break;
					case 'y': output_env      = 1; break;

					case 'e': preproc_file = stdout;           break;
					case 'n': progdate = date_stamp(argv [0]); break;

					case 'v':
						verbose++;
						break;

					case 'V':
						report_version();
						break;

					default:
						error(ERROR_WARNING, "Unknown option, -%c", *s);
						break;
					}
				}
			}
		} else {
			if (api == NULL) {
			api = arg;
			} else if (file == NULL) {
			file = arg;
			} else if (subset == NULL) {
			subset = arg;
			} else {
			error(ERROR_WARNING, "Too many arguments");
			}
		}
	}

	if (show_index && output_env) {
		error(ERROR_FATAL, "Can't output both an index and an environment");
	}

	if (local_input) {
		if (subset)error(ERROR_WARNING, "Too many arguments");
		subset = file;
		file = api;
		api = LOCAL_API;
	}

	if (api == NULL) {
		error(ERROR_FATAL, "Not enough arguments");
	}
	input_dir = string_printf("%s:%s", dir, input_dir);

	if (preproc_input) {
		/* Open preprocessed input */
		if (file != NULL) {
			error(ERROR_WARNING, "Too many arguments");
		}

		preproc_file = fopen(api, "r");
		set_filename(api);
		crt_line_no = 1;
		if (preproc_file == NULL) {
			error(ERROR_FATAL, "Can't open input file");
		}
	} else {
		int n;

		/* Find the temporary file */
		if (preproc_file == NULL) {
			preproc_file = tmpfile();
			if (preproc_file == NULL) {
				error(ERROR_FATAL, "Can't open temporary file");
			}
		}

		/* Do the preprocessing */
		preproc(preproc_file, api, file, subset);
		n = number_errors;
		if (n) {
			set_filename(NULL);
			error(ERROR_FATAL, "%d error(s) in preprocessor phase", n);
		}

		if (preproc_file == stdout) {
			exit(exit_status);
		}

		set_filename("temporary file");
		crt_line_no = 1;
	}

	/* Deal with separate compilation */
	if (separate_files) {
		int n;
		hash_elem *e;
		char *s = buffer;

		IGNORE sprintf(s, "%s ", argv [0]);
		for (a = 1; a < argc; a++) {
			char *arg = argv [a];
			if (arg [0] == '-') {
			s = s + strlen(s);
			IGNORE sprintf(s, "%s ", arg);
			}
		}

		s = s + strlen(s);
		IGNORE strcpy(s, "-ac ");
		set_filename(NULL);

		for (e = sort_hash(subsets); e != NULL; e = e->next) {
			separate(e->obj);
		}

		n = number_errors;
		if (n) {
			error(ERROR_FATAL, "%d error(s) in separate compilation", n);
		}

		exit(exit_status);
	}

	/* Process the input */
	input_file = preproc_file;
	input_pending = LEX_EOF;
	rewind(input_file);
	ADVANCE_LEXER;
	read_spec(&commands);
	if (number_errors) {
		set_filename(NULL);
		error(ERROR_FATAL, "%d error(s) in analyser phase", number_errors);
	}

	if (check_only) {
		return exit_status;
	}

	if (output_env) {
		print_env(commands);
		return exit_status;
	}

	/* Perform the output */
	set_filename(NULL);
	if (commands && commands->objtype == OBJ_SET) {
		implement(commands->u.u_obj, 1);
		if (show_index == 0) {
			print_set(commands, 0);
			print_set(commands, 1);
		} else {
			if (show_index == 1) {
				print_index(commands);
			} else {
				print_machine_index(commands);
			}
		}
	}

	return exit_status;
}

