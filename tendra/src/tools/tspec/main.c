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
#include "msgcat.h"
#include "ostream.h"
#include "tenapp.h"

#include <signal.h>
#include "release.h"
#include "object.h"
#include "hash.h"
#include "index.h"
#include "lex.h"
#include "makefile.h"
#include "name.h"
#include "syntax.h"
#include "type.h"
#include "print.h"
#include "utility.h"

extern void tspec_on_message(MSG_DATA *);

/*
 *    SIGNAL HANDLER
 *
 *    This routine handles caught signals.
 */

static void
exit_handler(void)
{
    hash_elem *e;

    if (exit_status == 0)
	return;
    e = sort_hash (files);
    while (e) {
		object *p = e->obj;
		FILE *f = p->u.u_file;
		if (f) {
			char *nm = p->name;
			if (verbose) IGNORE printf ("Removing %s ...\n", nm);
			IGNORE fclose (f);
			IGNORE remove (nm);
		}
		e = e->next;
    }
}


/*
 *    SEPARATE COMPILATION ROUTINE
 *
 *    This routine performs the separate compilation of the set object p.
 */

static void
separate(object *p)
{
    info *i = p->u.u_info;
    static char *exec = null;
    if (i->subset || i->file == null) return;
    if (exec == null) exec = buffer + strlen (buffer);
    IGNORE sprintf (exec, "%s %s", i->api, i->file);
    if (verbose > 1) IGNORE printf ("Executing '%s' ...\n", buffer);
    if (system (buffer)) {
		MSG_separate_compilation_failed (p->name);
    }
    return;
}


/*
 *    MARK A SET AS IMPLEMENTED
 *
 *    This routine recursively marks all implemented subsets of p.
 */

static void
implement(object *p, int depth)
{
    object *q;
    info *i = p->u.u_info;
    if (i == null || i->implemented >= depth) return;
    i->implemented = depth;
    for (q = i->elements; q != null; q = q->next) {
		if (q->objtype == OBJ_IMPLEMENT) {
			implement (q->u.u_obj, depth + 1);
		}
    }
    return;
}

static void
msg_uh_fileline(char ch, void *pp)
{
	UNUSED(ch);
	UNUSED(pp);
	if (filename)
		write_fmt(msg_stream, "%s: %d: ", filename, line_no);
}


/*
 *    MAIN ROUTINE
 *
 *    This is the main routine which interprets the command-line options
 *    and calls the appropriate routines.
 */

int
main(int argc, char **argv)
{
    int a;
    char *env;
    char *dir = ".";
    char *api = null;
    char *file = null;
    char *subset = null;
    object *commands = null;
    FILE *preproc_file = null;
    int show_index = 0;
    boolean check_only = 0;
    boolean preproc_input = 0;
    boolean separate_files = 0;

    /* Initialisation */
    tenapp_init (argc, argv, "An API specification tool", "2.9");
    tenapp_add_eh (exit_handler);
    msg_uh_add(MSG_GLOB_fileline, msg_uh_fileline);
    msg_on_message = tspec_on_message;

    line_no = 1;
    filename = "built-in definitions";
    init_hash ();
    init_keywords ();
    init_types ();
    filename = "command line";

    /* Read system variables */
    env = getenv (INPUT_ENV);
    if (env) input_dir = string_copy (env);
    env = getenv (OUTPUT_ENV);
    if (env) {
		output_incl_dir = string_printf ("%s/include", env);
		output_incl_len = (int) strlen (output_incl_dir) + 1;
		output_src_dir = string_printf ("%s/src", env);
		output_src_len = (int) strlen (output_src_dir) + 1;
    }
    env = getenv (INCLUDE_ENV);
    if (env) {
		output_incl_dir = string_copy (env);
		output_incl_len = (int) strlen (output_incl_dir) + 1;
    }
    env = getenv (SRC_ENV);
    if (env) {
		output_src_dir = string_copy (env);
		output_src_len = (int) strlen (output_src_dir) + 1;
    }
    env = getenv (COPYRIGHT_ENV);
    if (env) copyright = string_copy (env);

    /* Process options */
    for (a = 1; a < argc; a++) {
		char *arg = argv [a];
		line_no = a;
		if (arg [0] == '-') {
			if (arg [1] == 'I') {
				dir = string_printf ("%s:%s", dir, arg + 2);
			} else if (arg [1] == 'O') {
				output_incl_dir = arg + 2;
				output_incl_len = (int) strlen (arg + 2) + 1;
			} else if (arg [1] == 'S') {
				output_src_dir = arg + 2;
				output_src_len = (int) strlen (arg + 2) + 1;
			} else if (arg [1] == 'C') {
				copyright = arg + 2;
			} else {
				char *s;
				for (s = arg + 1; *s; s++) {
					switch (*s) {
					case 'a' : separate_files = 0; break;
					case 'c' : check_only = 1; break;
					case 'd' : restrict_depth = 0; break;
					case 'e' : preproc_file = stdout; break;
					case 'f' : force_output = 1; break;
					case 'i' : show_index = 1; break;
					case 'l' : local_input = 1; break;
					case 'm' : show_index = 2; break;
					case 'n' : progdate = date_stamp (argv [0]); break;
					case 'p' : preproc_input = 1; break;
					case 'r' : restrict_use = 1; break;
					case 's' : separate_files = 1; break;
					case 't' : allow_long_long = 1; break;
					case 'u' : unique_names = 1; break;
					case 'v' : verbose++; break;
					case 'w' : msg_sev_set (MSG_SEV_WARNING, 0); break;
					case 'V' : {
						tenapp_report_version ();
						break;
					}
					default : {
						MSG_getopt_unknown_option (s);
						break;
					}
					}
				}
			}
		} else {
			if (api == null) {
				api = arg;
			} else if (file == null) {
				file = arg;
			} else if (subset == null) {
				subset = arg;
			} else {
				MSG_getopt_too_many_arguments ();
			}
		}
    }
    if (local_input) {
		if (subset) MSG_getopt_too_many_arguments ();
		subset = file;
		file = api;
		api = LOCAL_API;
    }
    if (api == null) MSG_getopt_not_enough_arguments ();
    input_dir = string_printf ("%s:%s", dir, input_dir);

    if (preproc_input) {
		/* Open preprocessed input */
		if (file != null) MSG_getopt_not_enough_arguments ();
		preproc_file = fopen (api, "r");
		filename = api;
		line_no = 1;
		if (preproc_file == null) {
			MSG_cant_open_input_file (api);
		}
    } else {
		/* Find the temporary file */
		int n;
		if (preproc_file == null) {
			preproc_file = tmpfile ();
			if (preproc_file == null) {
				MSG_cant_open_temporary_file ();
			}
		}
		/* Do the preprocessing */
		preproc (preproc_file, api, file, subset);
		n = no_errors;
		if (n) {
			filename = null;
			MSG_errors_in_preprocessor_phase (n);
		}
		if (preproc_file == stdout) exit (exit_status);
		filename = "temporary file";
		line_no = 1;
    }

    /* Deal with separate compilation */
    if (separate_files) {
		int n;
		hash_elem *e;
		char *s = buffer;
		IGNORE sprintf (s, "%s ", argv [0]);
		for (a = 1; a < argc; a++) {
			char *arg = argv [a];
			if (arg [0] == '-') {
				s = s + strlen (s);
				IGNORE sprintf (s, "%s ", arg);
			}
		}
		s = s + strlen (s);
		IGNORE strcpy (s, "-ac ");
		filename = null;
		e = sort_hash (subsets);
		while (e) {
			separate (e->obj);
			e = e->next;
		}
		n = no_errors;
		if (n) {
			MSG_errors_in_separate_compilation (n);
		}
		exit (exit_status);
    }

    /* Process the input */
    input_file = preproc_file;
    input_pending = LEX_EOF;
    rewind (input_file);
    ADVANCE_LEXER;
    read_spec (&commands);
    if (no_errors) {
		filename = null;
		MSG_errors_in_analyser_phase (no_errors);
    }

    /* Perform the output */
    if (!check_only) {
		filename = null;
		if (commands && commands->objtype == OBJ_SET) {
			implement (commands->u.u_obj, 1);
			if (show_index == 0) {
				print_set (commands, 0);
				print_set (commands, 1);
				if (file == null) {
					hash_elem *e = sort_hash (subsets);
					print_makefile (api, e, 0);
					print_makefile (api, e, 1);
				}
			} else {
				if (show_index == 1) {
					print_index (commands);
				} else {
					print_machine_index (commands);
				}
			}
		}
    }
    return (exit_status);
}
