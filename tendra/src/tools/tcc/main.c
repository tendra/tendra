/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#include "config.h"
#include "cstring.h"
#include "fmm.h"
#include "msgcat.h"
#include "tenapp.h"

#include "release.h"
#include "external.h"
#include "filename.h"
#include "list.h"
#include "execute.h"
#include "flags.h"
#include "compile.h"
#include "environ.h"
#include "main.h"
#include "options.h"
#include "startup.h"
#include "suffix.h"
#include "utility.h"


/*
 *    CURRENT VERSION NUMBER
 *
 *    Version 4.0 of tcc is a complete rewrite from version 3.x.  The
 *    revision number is automatically generated from the RCS revision
 *    and is stored in version.h.
 */

#define VERSION_STRING		"Version: 4.0"

#ifndef RELEASE
#define RELEASE 		"unknown"
#endif


/*
 *    PRINT THE CURRENT VERSION
 *
 *    This routine prints the version number.
 */

void
print_version(void)
{
    MSG_tcc_version(VERSION_STRING, checker ? " (checker)" : "", machine_name, RELEASE);
    flag_no_files = 1;
    return;
}


/*
 *    ENVIRONMENT
 *
 *    This variable given the array of environmental variables which is
 *    passed as the third argument to main.
 */

char **environment = null;


/*
 *    TEMPORARY DIRECTORY FLAG
 *
 *    This flag is true to indicate that the temporary directory needs
 *    removing.
 */

static boolean made_tempdir = 0;


/*
 *    MAIN INITIALISATION ROUTINE
 *
 *    This is the initialisation routine called at the very start of the
 *    program.  The signals SIGINT, SIGSEGV, SIGTERM and SIGFPE are all
 *    in ANSI.
 */

static void
main_start(char *prog, char **envp)
{
    environment = envp;
    buffer = xalloc (buffer_size * sizeof (char));
    progname = find_basename (prog);
    initialise_options ();
    return;
}


/*
 *    MAIN CONSOLIDATION ROUTINE
 *
 *    This routine is called after all the command-line arguments have
 *    been processed, but before any actual compilation takes place.
 */

static void
main_middle(void)
{
    char *s = temp_name (temporary_dir, progname);
    tempdir = string_copy (s);
    cmd_list (exec_mkdir);
    cmd_string (tempdir);
    IGNORE execute (no_filename, no_filename);
    if (last_return) {
		MSG_cant_create_temporary_directory ();
    }
    made_tempdir = 1;
    return;
}


/*
 *    MAIN CLEAN UP ROUTINE
 *
 *    This routine always used to exit the program, except when an
 *    exec fails in the child process.  It cleans up the temporary
 *    directory etc. and returns exit_status to the calling process.
 */

void
main_end(void)
{
    IGNORE signal (SIGINT, SIG_IGN);
    remove_junk ();
    remove_startup ();
    if (made_tempdir) {
		made_tempdir = 0;
		cmd_string ((char *) null);
		cmd_list (exec_remove);
		cmd_string (tempdir);
		IGNORE execute (no_filename, no_filename);
    }
    kill_stray ();
    exit (exit_status);
}


/*
 *    MAIN ROUTINE
 *
 *    This is the main routine.
 */

int
main(int argc, char **argv)
{
    int a;
    char *s;
    filename *output;
    list *opts = null;

    /* Initialisation */
    tenapp_init(argc, argv, "TCC", VERSION_STRING);
    tenapp_add_eh (main_end);
    main_start (PROGNAME_TCC, environ);

    /* Check TCCOPTS options */
    s = getenv (TCCOPT_VAR);
    if (s != null) {
    	opts = make_list (s);
        process_options (opts, main_optmap, 0);
        free_list (opts);
        opts = null;
    }

    /* Process command line options */
    for (a = argc - 1 ; a >= 1 ; a--) {
		opts = insert_item (argv [a], opts);
    }
    process_options (opts, main_optmap, 0);
    update_options ();
	reconcile_envopts();
    free_list (opts);

    /* Check for input files */
    if (input_files == null) {
		if (flag_no_files) main_end ();
		MSG_no_input_files_specified ();
    }

    /* Apply compilation */
    main_middle ();
    output = apply_all (input_files);

    /* Check for unprocessed files */
    while (output != null) {
		if (output->storage == INPUT_FILE) {
			MSG_input_file_not_processed (output->name);
		}
		output = output->next;
    }

    /* Exit from program */
    main_end ();
    return (0);
}
