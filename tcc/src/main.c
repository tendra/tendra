/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
	error(INFO, "%s%s, Machine: %s, Release: %s", VERSION_STRING,
	      (checker ? " (checker)" : ""), machine_name, RELEASE);
	flag_no_files = 1;
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
		error(SERIOUS, "Caught signal %d in '%s'", sig, cmd);
	}

	exit_status = EXIT_FAILURE;
	main_end();
}


/*
 * TEMPORARY DIRECTORY FLAG
 *
 * This flag is true to indicate that the temporary directory needs removing.
 */

static boolean made_tempdir = 0;


/*
 * MAIN INITIALISATION ROUTINE
 *
 * This is the initialisation routine called at the very start of the program.
 */

static void
main_start(char *prog)
{
	const struct optmap *t;

	buffer = alloc_nof(char, buffer_size);
	progname = find_basename(prog);
	IGNORE signal(SIGINT, handler);
	IGNORE signal(SIGTERM, handler);

	srand(time(NULL));

    /* initialize hash table with tccenv keys */
	for (t = environ_optmap; t->in != NULL; t++) {
		char *name;

		if (t->explain == NULL) {
			continue;
		}

		name = string_copy(t->in + 1);
		name[strcspn(name, " ")] = '\0';

		envvar_set(&envvars, name, t->explain,
			HASH_ASSIGN, HASH_DEFAULT);
	}

	initialise_options();
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
		error(FATAL, "Can't create temporary directory");
	}

	made_tempdir = 1;
}


/*
 * MAIN CLEAN UP ROUTINE
 *
 * This routine always used to exit the program, except when an exec fails in
 * the child process. It cleans up the temporary directory etc. and returns
 * exit_status to the calling process.
 */
/* TODO we could use atexit() to register this, make it static, and simply exit() elsewhere */

void
main_end(void)
{
	IGNORE signal(SIGINT, SIG_IGN);
	remove_junk();
	remove_startup();
	if (made_tempdir &&
	    !(exit_status != EXIT_SUCCESS && flag_keep_err)) {
		made_tempdir = 0;
		cmd_string(NULL);
		cmd_list(exec_remove);
		cmd_string(tempdir);
		IGNORE execute(no_filename, no_filename);
	}
	kill_stray();
	exit(exit_status);
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
		process_options(opts, main_optmap, 0, HASH_SYSENV);
		free_list(opts);
		opts = NULL;
	}

	/* Process command line options */
	for (a = argc - 1; a >= 1; a--) {
		opts = insert_item(argv[a], opts);
	}
	process_options(opts, main_optmap, 0, HASH_CLI);
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
		error(FATAL, "No input files specified");
	}

	/* Apply compilation */
	main_middle();
	output = apply_all(input_files);

	/* Check for unprocessed files */
	while (output != NULL) {
		if (output->storage == INPUT_FILE) {
			error(WARNING, "Input file '%s' not processed", output->name);
		}
		output = output->next;
	}

	/* Exit from program */
	main_end();
	return 0;
}
