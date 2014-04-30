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

#include <shared/error.h>
#include <shared/fmt.h>

const char *progname = NULL;
const char *progvers = NULL;
int exit_status = EXIT_SUCCESS;
int maximum_errors = 20;
int number_errors = 0;

int crt_line_no = 1;
const char *crt_file_name = NULL;

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
report_version(void)
{
	const char *nm = progname;
	const char *vers = progvers;

	if (nm == NULL)
		nm = "unknown";
	if (vers == NULL)
		vers = "unknown";

	(void) fprintf(stderr, "%s: Version %s (tendra.org)\n", nm, vers);
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
	if (e == ERROR_NONE) {
		/*
		 * XXX: This used to just switch all error reporting off,
		 * but it doesn't seem to be used anywhere except in the
		 * producer. Will see if it errors out
		 */
		(void) fprintf(stderr, "error_msg called with ERROR_NONE");
		abort();
	}

	if (progname)
		(void) fprintf(stderr, "%s: ", progname);

	switch (e) {
	case ERROR_WARNING:
		(void) fprintf(stderr, "Warning: ");
		break;
	case ERROR_FATAL:
		(void) fprintf(stderr, "Fatal: ");
		exit_status = EXIT_FAILURE;
		break;
	case ERROR_USAGE:
		(void) fprintf(stderr, "Usage: ");
		exit_status = EXIT_FAILURE;
		break;
	case ERROR_INTERNAL:
		(void) fprintf(stderr, "Internal Error: ");
		exit_status = EXIT_FAILURE;
		number_errors++;
		break;
	case ERROR_SERIOUS:
		(void) fprintf(stderr, "Error: ");
		exit_status = EXIT_FAILURE;
		number_errors++;
		break;
	default:
		(void) fprintf(stderr, "Unknown error level");
		abort();
	}

	if (fn) {
		(void) fprintf(stderr, "%s: ", fn);
		if (ln != -1)
			(void) fprintf(stderr, "line %d: ", ln);
	}

	(void) vefprintf(stderr, s, args);
	(void) fprintf(stderr, "\n");

	if (e == ERROR_FATAL || e == ERROR_USAGE)
		exit(exit_status);

	if (number_errors >= maximum_errors && maximum_errors)
		error(ERROR_FATAL, "Too many errors (%d) - aborting",
		    number_errors);
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

#ifdef DEBUG

/*
 * PRINT AN ASSERTION
 *
 * This routine prints the assertion s which occurred at the location
 * given by file and line.
 */
void
assertion(const char *s, const char *file, int line)
{
    if (progname) fprintf(stderr, "%s: ", progname);
    fprintf(stderr, "Assertion: %s: line %d: '%s'.\n", file, line, s);
    abort();
}

#endif

