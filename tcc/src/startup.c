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
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <shared/string.h>

#include "config.h"
#include "filename.h"
#include "list.h"
#include "execute.h"
#include "flags.h"
#include "startup.h"
#include "utility.h"
#include "table.h"
#include "temp.h"


/*
 * THE STARTUP AND ENDUP FILES
 *
 * These variables give the names and file descriptors for the startup and
 * endup files, plus the command-line options to pass them to the producer.
 */

static FILE *startup_file = NULL, *endup_file = NULL;
static char *startup_name = NULL, *endup_name = NULL;
char *startup_opt = NULL, *endup_opt = NULL;


/*
 * THE TOKEN DEFINITION FILE
 *
 * This file is used to hold TDF notation for the definition of the
 * command-line tokens.
 */

static FILE *tokdef_file = NULL;
char *tokdef_name = NULL;


static void
add_to_file(FILE **file, char **name, const char *prefix)
{
	assert(file != NULL);
	assert(name != NULL);
	assert(prefix != NULL);

	/*
	 * Note that we cannot use tempdir here, because add_to_file may be called
	 * before the temporary directory is set (e.g. by an environment).
	 * TODO: if the options shuffling doesn't solve this, then what is it for?
	 */
	if (*name == NULL) {
		*file = temp_fopen(&startup_name, temporary_dir, prefix);
		if (*file == NULL) {
			return;
		}
	}

	assert(*name != NULL);
	assert(*file != NULL || dry_run);

	if (dry_run) {
		*file = NULL;
		return;
	}
}


/*
 * ADD A MESSAGE TO THE STARTUP FILE
 *
 * This routine prints the message s to the tcc startup file.
 */

void
add_to_startup(const char *fmt, ...)
{
	va_list ap;

	add_to_file(&startup_file, &startup_name, "ts");

	startup_opt = xstrcat("-f", startup_name);

	if (startup_file == NULL) {
		return;
	}

	IGNORE fprintf(startup_file, "#line 1 \"%s\"\n", name_h_file);

	va_start(ap, fmt);
	IGNORE vfprintf(startup_file, fmt, ap);
	va_end(ap);
}


/*
 * ADD A MESSAGE TO THE ENDUP FILE
 *
 * This routine prints the message s to the tcc endup file.
 */

void
add_to_endup(const char *fmt, ...)
{
	va_list ap;

	add_to_file(&endup_file, &endup_name, "te");

	startup_opt = xstrcat("-f", endup_name);

	if (endup_file == NULL) {
		return;
	}

	IGNORE fprintf(endup_file, "#line 1 \"%s\"\n", name_E_file);

	va_start(ap, fmt);
	IGNORE vfprintf(endup_file, fmt, ap);
	va_end(ap);
}


/*
 * ADD A MESSAGE TO THE TOKEN DEFINITION FILE
 *
 * This routine prints the message s to the tcc token definition file.
 */

static void
add_to_tokdef(const char *fmt, ...)
{
	va_list ap;

	add_to_file(&tokdef_file, &tokdef_name, "td");

	if (tokdef_file == NULL) {
		return;
	}

	IGNORE fputs("( make_tokdec ~char variety )\n", tokdef_file);
	IGNORE fputs("( make_tokdec ~signed_int variety )\n\n", tokdef_file);

	va_start(ap, fmt);
	IGNORE vfprintf(tokdef_file, fmt, ap);
	va_end(ap);
}


/*
 * CLOSE THE STARTUP AND ENDUP FILES
 *
 * This routine closes the startup and endup files.
 */

void
close_startup(void)
{
	if (startup_file) {
		IGNORE fclose(startup_file);
		startup_file = NULL;
	}
	if (endup_file) {
		IGNORE fclose(endup_file);
		endup_file = NULL;
	}
	if (tokdef_file) {
		IGNORE fclose(tokdef_file);
		tokdef_file = NULL;
	}
}


/*
 * CLEAN UP THE STARTUP AND ENDUP FILES
 *
 * This routine is called before the program terminates either to remove the
 * tcc startup and endup files or to move them if they are to be preserved.
 */

void
remove_startup(void)
{
	if (table_keep(STARTUP_FILE)) {
		if (startup_name) {
			cmd_list(exec_move);
			cmd_string(startup_name);
			cmd_string(name_h_file);
			IGNORE execute(no_filename, no_filename);
		}
		if (endup_name) {
			cmd_list(exec_move);
			cmd_string(endup_name);
			cmd_string(name_E_file);
			IGNORE execute(no_filename, no_filename);
		}
		if (tokdef_name) {
			cmd_list(exec_move);
			cmd_string(tokdef_name);
			cmd_string(name_p_file);
			IGNORE execute(no_filename, no_filename);
		}
	} else {
		if (startup_name) {
			cmd_list(exec_rmfile);
			cmd_string(startup_name);
			IGNORE execute(no_filename, no_filename);
		}
		if (endup_name) {
			cmd_list(exec_rmfile);
			cmd_string(endup_name);
			IGNORE execute(no_filename, no_filename);
		}
		if (tokdef_name) {
			cmd_list(exec_rmfile);
			cmd_string(tokdef_name);
			IGNORE execute(no_filename, no_filename);
		}
	}
}


/*
 * DEAL WITH STARTUP PRAGMA OPTIONS
 *
 * This routine translates command-line compilation mode options into the
 * corresponding pragma statements.
 */

void
add_pragma(const char *s)
{
	char *e;
	char *level = "warning";
	static char *start_scope = "#pragma TenDRA begin\n";
	if (start_scope) {
		add_to_startup(start_scope);
		start_scope = NULL;
	}
	e = strchr(s, '=');
	if (e) {
		level = e + 1;
		*e = 0;
	}

	/* Write option to startup file */
	add_to_startup("#pragma TenDRA option \"%s\" %s\n", s, level);
}


/*
 * DEAL WITH STARTUP TOKEN OPTIONS
 *
 * This routine translates command-line token definition options into the
 * corresponding pragma statements.
 */

void
add_token(const char *s)
{
	char *type = "int";
	char *defn = "1";
	char *e = strchr(s, '=');
	if (e) {
		defn = e + 1;
		*e = 0;
	}

	/* Write token description to startup file */
	add_to_startup("#pragma token EXP const : %s : %s #\n", type, s);
	add_to_startup("#pragma interface %s\n", s);

	/* Write definition to token definition file */
	add_to_tokdef("( make_tokdef %s exp\n", s);
	add_to_tokdef("  ( make_int ~signed_int %s ) )\n\n", defn);
}
