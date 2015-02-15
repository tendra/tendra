/* $Id$ */

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

#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include "config.h"
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


/*
 * MAIN INITIALISATION ROUTINE
 *
 * This is the initialisation routine called at the very start of the program.
 */

static void
main_start(char *prog)
{
	size_t i;

	struct {
		const char *name;
		const char *value;
	} a[] = {
		{ "PREFIX",         PREFIX         },
		{ "PREFIX_BIN",     PREFIX_BIN     },
		{ "PREFIX_LIB",     PREFIX_LIB     },
		{ "PREFIX_LIBEXEC", PREFIX_LIBEXEC },
		{ "PREFIX_SHARE",   PREFIX_SHARE   },
		{ "PREFIX_INCLUDE", PREFIX_INCLUDE },
		{ "PREFIX_MAN",     PREFIX_MAN     },
		{ "PREFIX_TSPEC",   PREFIX_TSPEC   },
		{ "PREFIX_STARTUP", PREFIX_STARTUP },
		{ "PREFIX_ENV",     PREFIX_ENV     },
		{ "PREFIX_API",     PREFIX_API     },
		{ "PREFIX_LPI",     PREFIX_LPI     },
		{ "PREFIX_SYS",     PREFIX_SYS     },
		{ "PREFIX_TMP",     PREFIX_TMP     },
		{ "PREFIX_MAP",     PREFIX_MAP     },

		/* Platform-specific things */
		{ "MD_EXECFORMAT",  EXECFORMAT     },
		{ "MD_BLDARCH",     BLDARCH        },
		{ "MD_TRANSARCH",   TRANSARCH      },
		{ "MD_OSFAM",       OSFAM          },
		{ "MD_OSVER",       OSVER          }
	};

	atexit(main_end);

	buffer = xmalloc_nof(char, buffer_size);
	set_progname(find_basename(prog), VERSION);

	srand(time(NULL));

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

	/* Initialisation */
	main_start(PROGNAME_TCC);

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
