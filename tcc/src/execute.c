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


#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <shared/error.h>
#include <shared/xalloc.h>

#include "config.h"
#include "external.h"
#include "filename.h"
#include "list.h"
#include "archive.h"
#include "execute.h"
#include "flags.h"
#include "main.h"
#include "utility.h"


/*
 * CURRENT COMMAND
 *
 * The current command is a variable sized array of strings, command. A
 * complete command is terminated by a null string.
 */

static const char **command = NULL;
static int command_size = 0;
static int cmd_no = 0;


/*
 * DELAY SIGNAL HANDLING
 *
 * Because the producer occasionally dies with a signal after it has output
 * some useful errors it is benificial to run the tot even after the signal has
 * been caught. These globals and the functions below for using them tell the
 * execute function to delay calling the signal handler until after the tot is
 * called.
 */

static char *last_signaled_cmd = NULL;
static int last_signal = 0;
static int delay_signal_handling = 0;

void
enable_delayed_signal(void)
{
	delay_signal_handling = 1;
}

void
disable_delayed_signal(void)
{
	delay_signal_handling = 0;
}

void
process_delayed_signal(void)
{
	if (last_signal != 0) {
		last_command = last_signaled_cmd;
		handler(last_signal);
	}
}


/*
 * ADD A STRING TO THE CURRENT COMMAND
 *
 * This routine adds the string s to the command array. If s is null then the
 * array counter is reset to the beginning. The array counter is not advanced
 * for empty strings.
 */

void
cmd_string(const char *s)
{
	if (cmd_no >= command_size) {
		command_size += 1000;
		command = xrealloc_nof(command, char *, command_size);
	}
	command[cmd_no] = s;
	if (s == NULL) {
		cmd_no = 0;
	} else if (*s) {
		cmd_no++;
	}
}


/*
 * ADD A FILENAME TO THE CURRENT COMMAND
 *
 * This routine adds the names of the files given by p to the command array.
 */

void
cmd_filename(const filename *p)
{
	for (; p != NULL; p = p->next) {
		cmd_string(p->name);
	}
}


/*
 * ADD A LIST TO THE CURRENT COMMAND
 *
 * This routine adds the list of strings given by p to the command array.
 */

void
cmd_list(const list *p)
{
	for (; p != NULL; p = p->next) {
		cmd_string(p->item.s);
	}
}


/*
 * OVERALL COMPILATION STATUS
 *
 * This flag is true is an execution error occurs.
 */

boolean exec_error = 0;

void
reset_exec_error(void)
{
	exec_error = 0;
}


/*
 * LAST COMMAND
 *
 * The name of the last command executed, and its return value (zero indicating
 * success) are stored.
 */

const char *last_command = NULL;
int last_return = 0;


/*
 * THE CURRENT PROCESS
 *
 * When a process is active, its pid is stored as running_pid. The value -1 is
 * used to indicate that no process is active.
 */

static long running_pid = -1;


/*
 * KILL ANY STRAY PROCESSES
 *
 * Occasionally a runaway process may occur. This routine is indended to deal
 * with these by sending the signal SIGTERM to the process. This routine is
 * POSIX compliant.
 */

void
kill_stray(void)
{
	if (running_pid == -1) {
		return;
	}

	IGNORE kill((pid_t)running_pid, SIGTERM);
	running_pid = -1;
}


/*
 * LIST OF FILES TO BE REMOVED BY REMOVE_JUNK
 *
 * This gives the list of the files which are to be removed if an error occurs.
 */

static const filename *junk = NULL;


/*
 * REMOVE ANY INCOMPLETE OUTPUT FILES
 *
 * Any files which are being created when an error occurs should be removed.
 */

void
remove_junk(void)
{
	const filename *p;

	if (dry_run || flag_keep_err) {
		return;
	}

	for (p = junk; p != NULL; p = p->next) {
		if (p->storage == OUTPUT_FILE) {
			IGNORE remove_file(p->name);
		}
	}
	junk = NULL;
}


/*
 * PRINT COMMAND INTO BUFFER
 *
 * This routine prints the current command into a buffer and returns a pointer
 * to the result.
 */

static void
print_cmd(char *b)
{
	const char **s;
	for (s = command; *s != NULL; s++) {
		*b = ' ';
		IGNORE strcpy(b + 1, *s);
		b += strlen(b);
	}
}


/*
 * EXECUTE THE CURRENT COMMAND
 *
 * This routine executes the command given by the command array. It returns
 * either output, the list of all output files, if successful, or null,
 * otherwise. The routine is POSIX compliant. It uses fork and execv from
 * unistd.h to fork a process and various routines from sys/wait.h to analyse
 * the result. The interface with sys/wait.h has been abstracted to also allow
 * the BSD implementation.
 *
 * TODO explain what happens when called with no_filename, no_filename
 */

filename *
execute(filename *input, filename *output)
{
	const char *cmd;
	int err = 0;
	boolean filled_buff = 0;
	char buff[buffer_size];

	cmd_string(NULL);
	cmd = command[0];

	assert(cmd != NULL);

	last_command = cmd;
	last_return = 0;
	junk = output;

	if (taciturn) {
		/* Print input files if in taciturn mode */
		const filename *p;
		for (p = input; p != NULL; p = p->next) {
			if (p->storage == INPUT_FILE) {
				comment(1, "%s:\n", p->name);
			}
		}
	}

	if (verbose) {
		/* Print command if in verbose mode */
		print_cmd(buff);
		filled_buff = 1;
		comment(1, "%s\n", buff + 1);
	}

	if (cmd && strneq(cmd, "builtin/", 8)) {
		/* Check built in commands */
		/* XXX this is optimisation at the expense of readability; simplify */
		cmd += 8;
		switch (*cmd) {
		case 'b':
			if (streq(cmd, "build_archive")) {
				err = build_archive(command[1], command + 2);
				goto execute_error;
			}
			break;
		case 'c':
			if (streq(cmd, "cat")) {
				err = cat_file(command[1]);
				goto execute_error;
			}
			break;
		case 'm':
			if (streq(cmd, "mkdir")) {
				err = make_dir(command[1]);
				goto execute_error;
			}
			if (streq(cmd, "move")) {
				err = move_file(command[1], command[2]);
				goto execute_error;
			}
			break;
		case 'r':
			if (streq(cmd, "remove")) {
				err = remove_recursive(command[1]);
				goto execute_error;
			}
			break;
		case 's':
			if (streq(cmd, "split_archive")) {
				err = split_archive(command[1], &output);
				goto execute_error;
			}
			break;
		case 't':
			if (streq(cmd, "touch")) {
				err = touch_file(command[1], command[2]);
				goto execute_error;
			}
			break;
		case 'u':
			if (streq(cmd, "undef")) {
				int sev;
				if (dry_run) {
					sev = ERROR_WARNING;
				} else {
					sev = ERROR_SERIOUS;
					err = 1;
				}
				cmd = command[1];
				error(sev, "The tool '%s' is not available", cmd);
				goto execute_error;
			}
			break;
		}
		error(ERROR_SERIOUS, "Built-in '%s' command not implemented", cmd);
		err = 1;

	} else if (!dry_run) {
		/* Call system commands */
		pid_t pid = fork();
		if (pid == (pid_t) -1) {
			error(ERROR_SERIOUS, "Can't fork process");
			err = 1;
		} else {
			if (pid) {
				wait_type status;
				running_pid = (long)pid;
				while (process_wait ( &status ) != pid ) {
					;	/* empty */
				}
				running_pid = -1;
				if (process_exited(status)) {
					err = process_exit_value(status);
					/* This only returns if there was no
					 * remembered signal. */
					process_delayed_signal();
				} else {
					if (process_signaled(status)) {
						/* delay_signal_handling is a
						 * global that tells us
						 * that it is ok to let the
						 * next call to execute report
						 * that the command received a
						 * signal. This supports the
						 * way that the producer is
						 * called. */
						int sig = process_signal_value(status);
						if (delay_signal_handling &&
						    last_signal == 0) {
							last_signaled_cmd =
							    string_copy(cmd);
							last_signal = sig;
						} else {
							handler(sig);
						}
					}
					err = 1;
				}
				goto execute_error;
			}

			/* print tool chain commands sent to execv */
			if (tool_chain) {
				const char **curr = command;
				IGNORE printf ("\n%s \\\n", *curr++);

				while (*curr) {
					IGNORE printf ("\t%s", *curr++);

					if (*curr) {
						IGNORE printf (" \\");
					}

					IGNORE printf ("\n");
				}
			}

			/* XXX The cast to void * is to const-ness. Perhaps copy first */
			IGNORE execv(cmd, (void *) command);
			running_pid = -1;
			error(ERROR_SERIOUS, "Can't execute '%s'", cmd);
			exit(2);
		}
	}

	/* Deal with errors */
execute_error:
	disable_delayed_signal();
	last_return = err;
	if (tidy_up) {
		/* Remove unneeded files */
		const filename *p;
		for (p = input; p != NULL; p = p->next) {
			if (p->storage == TEMP_FILE && p->type != BINARY_OBJ) {
				IGNORE remove_file(p->name);
			}
		}
	}
	if (err) {
		exec_error = 1;
		exit_status = EXIT_FAILURE;
		if (show_errors) {
			/* Show when the error occurred */
			if (!filled_buff) {
				print_cmd(buff);
			}
			error(ERROR_SERIOUS, "Error in '%s'", buff + 1);
		}
		remove_junk();
		return NULL;
	}
	junk = NULL;
	return output;
}
