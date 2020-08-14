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

typedef struct {
	const char *name;
	const char *value;
} t_env_pair_const;

typedef struct {
	const char *name;
	char *value;
} t_env_pair_ptr;


void init_prefix_envvars(char *root_path)
{
	const t_env_pair_ptr a[] = {
		{ "PREFIX_BIN",     path_join(root_path, "bin")            },
		{ "PREFIX_LIB",     path_join(root_path, "lib")            },
		{ "PREFIX_LIBEXEC", path_join(root_path, "libexec")        },
		{ "PREFIX_SHARE",   path_join(root_path, "share")          },
		{ "PREFIX_INCLUDE", path_join(root_path, "include")        },
		{ "PREFIX_MAN",     path_join(root_path, "man")            },
		{ "PREFIX_TSPEC",   path_join(root_path, "share/tspec")    },
		{ "PREFIX_STARTUP", path_join(root_path, "lib/tcc/startup")},
		{ "PREFIX_ENV",     path_join(root_path, "lib/tcc/env")    },
		{ "PREFIX_API",     path_join(root_path, "lib/tcc/api")    },
		{ "PREFIX_LPI",     path_join(root_path, "lib/tcc/lpi")    },
		{ "PREFIX_SYS",     path_join(root_path, "lib/tcc/sys")    },
		{ "PREFIX_MAP",     path_join(root_path, "lib/tcc/map")    },
	};

	envvar_set(&envvars, "PREFIX", root_path,
		HASH_ASSIGN, HASH_DEFAULT);

	size_t i;
	for (i = 0; i < sizeof a / sizeof *a; i++) {
		envvar_set(&envvars, a[i].name, a[i].value,
			HASH_ASSIGN, HASH_DEFAULT);

		free(a[i].value);
	}
}

void init_platform_envvars()
{
	const t_env_pair_const b[] = {
		/* Platform-specific things */
		{ "MD_EXECFORMAT",  EXECFORMAT     },
		{ "MD_BLDARCH",     BLDARCH        },
		{ "MD_TRANSARCH",   TRANSARCH      },
		{ "MD_OSFAM",       OSFAM          },
		{ "MD_OSVER",       OSVER          }
	};

	size_t i;
	for (i = 0; i < sizeof b / sizeof *b; i++) {
		envvar_set(&envvars, b[i].name, b[i].value,
			HASH_ASSIGN, HASH_DEFAULT);
	}
}

void init_tmp_envvars(char *root_path)
{
	const char *temp_env = getenv("TMPDIR");
	if (temp_env) {
		envvar_set(&envvars, "PREFIX_TMP", temp_env,
			HASH_ASSIGN, HASH_DEFAULT);
	} else {
		envvar_set(&envvars, "PREFIX_TMP", "/tmp",
			HASH_ASSIGN, HASH_DEFAULT);
	}
}

void init_tccenv_envvars(char *root_path)
{
	const char *tcc_env = getenv(TCCENV_VAR);
	if (tcc_env != NULL) {
		envvar_set(&envvars, "ENVPATH", tcc_env,
			HASH_ASSIGN, HASH_TCCENV);
	} else {
		char *relative_env = path_join(root_path, "lib/tcc/env");
		envvar_set(&envvars, "ENVPATH", relative_env,
			HASH_ASSIGN, HASH_TCCENV);
		free(relative_env);
	}

	char *tspec_env = path_join(root_path, "share/tspec/TenDRA/env");
	envvar_set(&envvars, "ENVPATH", tspec_env,
		HASH_APPEND, HASH_SYSENV);
	free(tspec_env);
} 

/*
 * MAIN INITIALISATION ROUTINE
 *
 * This is the initialisation routine called at the very start of the program.
 */

static void
main_start(char *prog, const char *rel_executable_path)
{
	atexit(main_end);

	buffer = xmalloc(buffer_size);
	realpath(rel_executable_path, buffer);

	char *executable_path = xstrdup(buffer);

	const char *prog_name = find_basename(prog);
	set_progname(prog_name, VERSION);

	srand(time(NULL));

	char *root_path = find_compiler_root(executable_path, prog_name);

	init_prefix_envvars(root_path);
	init_platform_envvars();
	init_tmp_envvars(root_path);
	init_tccenv_envvars(root_path);

	free(root_path);
	free(executable_path);

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
	main_start(PROGNAME_TCC, argv[0]);

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
