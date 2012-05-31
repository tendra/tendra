/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

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


/*
 * CURRENT VERSION NUMBER
 *
 * Version 4.0 of tcc is a complete rewrite from version 3.x. The revision
 * number is automatically generated from the RCS revision and is stored in
 * version.h.
 */

#define VERSION_STRING		"Version: 4.0"

#ifndef RELEASE
#define RELEASE			"unknown"
#endif


/*
 * PRINT THE CURRENT VERSION
 *
 * This routine prints the version number.
 */

void
print_version(void)
{
	printf("%s%s, Machine: %s, Release: %s", VERSION_STRING,
	      (checker ? " (checker)" : ""), machine_name, RELEASE);
	flag_no_files = 1;
}


/*
 * TEMPORARY DIRECTORY FLAG
 *
 * This flag is true to indicate that the temporary directory needs removing.
 */

static boolean made_tempdir = 0;


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
	IGNORE signal(SIGINT, SIG_IGN);
	remove_junk();
	remove_startup();
	if (made_tempdir &&
	    !(exit_status != EXIT_SUCCESS && flag_keep_err)) {
		made_tempdir = 0;
		cmd_string(NULL);
		cmd_env("RMDIR");
		cmd_string(tempdir);
		IGNORE execute(no_filename, no_filename);
	}
	kill_stray();
}


/*
 * MAIN CONSOLIDATION ROUTINE
 *
 * This routine is called after all the command-line arguments have been
 * processed, but before any actual compilation takes place.
 */

static void
main_middle(void)
{
	tempdir = temp_mkdir(temporary_dir, progname);
	if (tempdir == NULL) {
		error(ERROR_FATAL, "Can't create temporary directory");
	}

	made_tempdir = 1;
}


/*
 * MAIN INITIALISATION ROUTINE
 *
 * This is the initialisation routine called at the very start of the program.
 */

static void
main_start(char *prog)
{
	const struct optmap *t;

	atexit(main_end);

	buffer = xmalloc_nof(char, buffer_size);
	set_progname(find_basename(prog), RELEASE);
	IGNORE signal(SIGINT, handler);
	IGNORE signal(SIGTERM, handler);

	srand(time(NULL));

    /* initialize hash table with tccenv keys */
	for (t = environ_optmap; t->in != NULL; t++) {
		char *name;

		if (t->explain == NULL) {
			continue;
		}

		name = xstrdup(t->in + 1);
		name[strcspn(name, " ")] = '\0';

		envvar_set(&envvars, name, t->explain,
			HASH_ASSIGN, HASH_DEFAULT);
	}

	initialise_options();
}


/*
 * SIGNAL HANDLER
 *
 * This routine is the main signal handler. It reports any interesting signals
 * and then cleans up.
 */

void
handler(int sig)
{
	IGNORE signal(SIGINT, SIG_IGN);
	if (verbose)
		comment(1, "\n");

	if (sig != SIGINT) {
		const char *cmd = (last_command ? last_command : "unknown");
		error(ERROR_SERIOUS, "Caught signal %d in '%s'", sig, cmd);
	}

	exit_status = EXIT_FAILURE;
	main_end();
	_exit(exit_status);
}


/*
 * MAIN ROUTINE
 *
 * This is the main routine.
 */

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
		}
		error(ERROR_FATAL, "No input files specified");
	}

	/* Apply compilation */
	main_middle();
	output = apply_all(input_files);

	/* Check for unprocessed files */
	while (output != NULL) {
		if (output->storage == INPUT_FILE) {
			error(ERROR_WARNING, "Input file '%s' not processed", output->name);
		}
		output = output->next;
	}

	/* Exit from program */
	main_end();

	return exit_status;
}
