/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/string.h>

#include "filename.h"
#include "list.h"
#include "execute.h"
#include "flags.h"
#include "startup.h"
#include "suffix.h"
#include "utility.h"
#include "table.h"
#include "temp.h"


/*
 * THE STARTUP AND ENDUP FILES
 *
 * These variables give the names for the startup and endup files,
 * to pass them to the producer.
 */

const char *startup_name, *endup_name;
FILE *startup_file, *endup_file;


/*
 * THE TOKEN DEFINITION FILE
 *
 * This file is used to hold TDF notation for the definition of the
 * command-line tokens.
 */

const char *tokdef_name;
FILE *tokdef_file;


/*
 * ADD A MESSAGE TO THE STARTUP FILE
 *
 * This routine prints the message s to the tcc startup file.
 */

void
add_to_startup(const char *fmt, ...)
{
	static char a[FILENAME_MAX];
	va_list ap;

	/* TODO: name (STARTUP_NAME etc) from env */

	if (startup_file == NULL) {
		assert(startup_name == NULL);

		startup_file = temp_fopen(a, sizeof a, STARTUP_NAME, "a");
		if (startup_file == NULL) {
			return;
		}

		startup_name = a;

		if (!dry_run) {
			IGNORE fprintf(startup_file, "#line 1 \"%s\"\n", STARTUP_NAME);
		}
	}

	if (dry_run) {
		return;
	}

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
	static char a[FILENAME_MAX];
	va_list ap;

	if (endup_file == NULL) {
		assert(endup_name == NULL);

		endup_file = temp_fopen(a, sizeof a, ENDUP_NAME, "a");
		if (endup_file == NULL) {
			return;
		}

		endup_name = a;

		if (!dry_run) {
			IGNORE fprintf(endup_file, "#line 1 \"%s\"\n", ENDUP_NAME);
		}
	}

	if (dry_run) {
		return;
	}

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
	static char a[FILENAME_MAX];
	va_list ap;

	if (tokdef_file == NULL) {
		assert(tokdef_name == NULL);

		tokdef_file = temp_fopen(a, sizeof a, TOKDEF_NAME, "a");
		if (tokdef_file == NULL) {
			return;
		}

		tokdef_name = a;

		if (!dry_run) {
			IGNORE fputs("( make_tokdec ~char variety )\n", tokdef_file);
			IGNORE fputs("( make_tokdec ~signed_int variety )\n", tokdef_file);
			IGNORE fputc('\n', tokdef_file);
		}
	}

	if (dry_run) {
		return;
	}

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
	if (startup_file != NULL) {
		IGNORE fclose(startup_file);
		startup_file = NULL;
	}
	if (endup_file != NULL) {
		IGNORE fclose(endup_file);
		endup_file = NULL;
	}
	if (tokdef_file != NULL) {
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
		if (startup_name != NULL) {
			cmd_env("MOVE");
			cmd_string(startup_name);
			cmd_string(name_h_file);
			IGNORE execute(no_filename, no_filename);
		}
		if (endup_name != NULL) {
			cmd_env("MOVE");
			cmd_string(endup_name);
			cmd_string(name_E_file);
			IGNORE execute(no_filename, no_filename);
		}
		if (tokdef_name != NULL) {
			cmd_env("MOVE");
			cmd_string(tokdef_name);
			cmd_string(name_p_file);
			IGNORE execute(no_filename, no_filename);
		}
	} else {
		if (startup_name != NULL) {
			cmd_env("RMFILE");
			cmd_string(startup_name);
			IGNORE execute(no_filename, no_filename);
		}
		if (endup_name != NULL) {
			cmd_env("RMFILE");
			cmd_string(endup_name);
			IGNORE execute(no_filename, no_filename);
		}
		if (tokdef_name != NULL) {
			cmd_env("RMFILE");
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
 *
 * TODO: why does this exist? it seems of very limited use
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
