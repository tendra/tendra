/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include "external.h"
#include "filename.h"
#include "archive.h"
#include "list.h"
#include "environ.h"
#include "execute.h"
#include "flags.h"
#include "compile.h"
#include "main.h"
#include "options.h"
#include "startup.h"
#include "suffix.h"
#include "utility.h"
#include "temp.h"


#define VERSION "5.0" "/" BLDARCH


void
print_version(void)
{
	report_version(stdout);
	flag_no_files = 1;
}


/*
 * MAIN CLEAN UP ROUTINE
 *
 * This routine always used to exit the program, except when an exec fails in
 * the child process. It cleans up the temporary directory etc. and returns
 * exit_status to the calling process.
 */

static void
main_end(void)
{
	remove_junk();
	remove_startup();
	if (tempdir != NULL &&
	    !(exit_status != EXIT_SUCCESS && flag_keep_err)) {
		cmd_string(NULL);
		cmd_env("RMDIR");
		cmd_string(tempdir);
		IGNORE execute(no_filename, no_filename);
	}
	kill_stray();
}

typedef struct _t_env_pair {
	const char *name;
	const char *value;
} t_env_pair;

/*
 * MAIN INITIALISATION ROUTINE
 *
 * This is the initialisation routine called at the very start of the program.
 */

static void
main_start(char *prog, char *executable_path)
{
	size_t i;

	atexit(main_end);

	buffer = xmalloc(buffer_size);
	const char *prog_name = find_basename(prog);
	set_progname(prog_name, VERSION);

	srand(time(NULL));

	const char *root_path = find_compiler_root(executable_path, prog_name);
	const t_env_pair a[] = {
		{ "PREFIX",         root_path      							},
		{ "PREFIX_BIN",     path_join(root_path, "bin") 			},
		{ "PREFIX_LIB",     path_join(root_path, "lib")     		},
		{ "PREFIX_LIBEXEC", path_join(root_path, "libexec") 		},
		{ "PREFIX_SHARE",   path_join(root_path, "share")   		},
		{ "PREFIX_INCLUDE", path_join(root_path, "include") 		},
		{ "PREFIX_MAN",     path_join(root_path, "man")     		},
		{ "PREFIX_TSPEC",   path_join(root_path, "share/tspec")   	},
		{ "PREFIX_STARTUP", path_join(root_path, "lib/tcc/startup") },
		{ "PREFIX_ENV",     path_join(root_path, "lib/tcc/env")     },
		{ "PREFIX_API",     path_join(root_path, "lib/tcc/api")     },
		{ "PREFIX_LPI",     path_join(root_path, "lib/tcc/lpi")     },
		{ "PREFIX_SYS",     path_join(root_path, "lib/tcc/sys")     },
		{ "PREFIX_TMP",     path_join(root_path, "tmp")     		},
		{ "PREFIX_MAP",     path_join(root_path, "lib/tcc/map")     },

		/* Platform-specific things */
		{ "MD_EXECFORMAT",  EXECFORMAT     },
		{ "MD_BLDARCH",     BLDARCH        },
		{ "MD_TRANSARCH",   TRANSARCH      },
		{ "MD_OSFAM",       OSFAM          },
		{ "MD_OSVER",       OSVER          }
	};


	for (i = 0; i < sizeof a / sizeof *a; i++) {
		envvar_set(&envvars, a[i].name, a[i].value,
			HASH_ASSIGN, HASH_DEFAULT);
	}

	{
		const char *tcc_env;

		envvar_set(&envvars, "ENVPATH", PREFIX_ENV,
			HASH_ASSIGN, HASH_DEFAULT);

		tcc_env = getenv(TCCENV_VAR);
		if (tcc_env != NULL) {
			envvar_set(&envvars, "ENVPATH", tcc_env,
				HASH_ASSIGN, HASH_TCCENV);
		}

		envvar_set(&envvars, "ENVPATH", PREFIX_TSPEC "/TenDRA/env",
			HASH_APPEND, HASH_SYSENV);
	}

	read_env("base");

	initialise_options();
}


int
main(int argc, char **argv)
{
	int a;
	char *s;
	filename *output;
	list *opts = NULL;

	char *executable_path = argv[0];

	/* Initialisation */
	main_start(PROGNAME_TCC, executable_path);

	/* Check TCCOPTS options */
	s = getenv(TCCOPT_VAR);
	if (s != NULL) {
		opts = make_list(s);
		process_options(opts, main_optmap, HASH_SYSENV);
		free_list(opts);
		opts = NULL;
	}

	/* Process command line options */
	for (a = argc - 1; a >= 1; a--) {
		opts = insert_item(argv[a], opts);
	}
	process_options(opts, main_optmap, HASH_CLI);
	update_options();
	reconcile_envopts(envvars);
	free_list(opts);

	/* Dump env information ? XXX: Where should this really be? */
	if (env_dump) {
		dump_env(envvars);
		/* main_end(); XXX */
		return 0;
	}

	/* Check for input files */
	if (input_files == NULL) {
		if (flag_no_files) {
			main_end();
			return exit_status;
		} else {
			error(ERR_FATAL, "No input files specified");
		}
	}

	if (tempdir == NULL) {
		tempdir = temp_mkdir(envvar_get(envvars, "PREFIX_TMP"), progname);
	}

	/* Apply compilation */
	output = apply_all(input_files);

	/* Check for unprocessed files */
	while (output != NULL) {
		if (output->storage == INPUT_FILE) {
			error(ERR_WARN, "Input file '%s' not processed", output->name);
		}
		output = output->next;
	}

	return exit_status;
}
