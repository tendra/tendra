/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/fmt.h>

const char *progname = NULL;
const char *progvers = NULL;

int exit_status = EXIT_SUCCESS;
int maximum_errors = 20;
int number_errors = 0;

int crt_line_no = 1;
const char *crt_file_name = NULL;

#ifndef RELEASE
#define RELEASE			""
#endif

/*
 * SET PROGRAM NAME
 *
 * This routine sets the program name to nm and the program version to vers.
 */
void
set_progname(const char *nm, const char *vers)
{
	char *r = strrchr(nm, '/'); /* XXX: basename(3) ? */
	progname = (r ? r + 1 : nm);
	progvers = vers;
}

/*
 * PRINT VERSION NUMBER
 *
 * This routine prints the program name and version number.
 */
void
report_version(FILE *f)
{
	const char *nm   = progname;
	const char *vers = progvers;
	const char *tver = "";

	if (nm == NULL) {
		nm = "unknown";
	}

	if (vers == NULL) {
		vers = "unknown";
	}

	if (RELEASE[0] != '\0') {
		tver = " " RELEASE;
	}

	IGNORE fprintf(f, "%s: Version %s%s (tendra.org)\n", nm, vers, tver);
}

/*
 * PRINT AN ERROR MESSAGE
 *
 * This routine prints an error message s with arguments args and severity
 * e.  fn and ln give the error position.
 */
static void
error_msg(enum error_severity e, const char *fn, int ln, const char *s, va_list args)
{
	if (progname != NULL) {
		IGNORE fprintf(stderr, "%s: ", progname);
	}

	switch (e) {
	case ERR_WARN:
		IGNORE fprintf(stderr, "Warning: ");
		break;

	case ERR_FATAL:
		IGNORE fprintf(stderr, "Fatal: ");
		exit_status = EXIT_FAILURE;
		break;

	case ERR_USAGE:
		IGNORE fprintf(stderr, "Usage: ");
		exit_status = EXIT_FAILURE;
		break;

	case ERR_INTERNAL:
		IGNORE fprintf(stderr, "Internal Error: ");
		exit_status = EXIT_FAILURE;
		number_errors++;
		break;

	case ERR_SERIOUS:
		IGNORE fprintf(stderr, "Error: ");
		exit_status = EXIT_FAILURE;
		number_errors++;
		break;

	default:
		IGNORE fprintf(stderr, "Unknown error level");
		abort();
	}

	if (fn != NULL) {
		IGNORE fprintf(stderr, "%s: ", fn);
		if (ln != -1) {
			IGNORE fprintf(stderr, "line %d: ", ln);
		}
	}

	IGNORE vefprintf(stderr, s, args);
	IGNORE fprintf(stderr, "\n");

	if (e == ERR_FATAL || e == ERR_USAGE) {
		exit(exit_status);
	}

	if (number_errors >= maximum_errors && maximum_errors) {
		error(ERR_FATAL, "Too many errors (%d) - aborting", number_errors);
	}
}

/*
 * PRINT AN ERROR AT CURRENT POSITION
 *
 * This routine prints the error message s of severity e at the current
 * file position.  s is a printf format string whose arguments are passed
 * as the optional procedure parameters.
 */
void
error(enum error_severity e, const char *s, ...)
{
	va_list args;
	va_start(args, s);
	error_msg(e, crt_file_name, crt_line_no, s, args);
	va_end(args);
}

/*
 * PRINT AN ERROR AT A GIVEN POSITION
 *
 * This routine prints the error message s of severity e at the file
 * position given by fn and ln.  s is as above.
 */
void
error_posn(enum error_severity e, const char *fn, int ln, const char *s, ...)
{
	va_list args;
	va_start(args, s);
	error_msg(e, fn, ln, s, args);
	va_end(args);
}

