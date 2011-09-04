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

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <shared/error.h>
#include <shared/fmt.h>


/*
    ERROR FLAGS AND VARIABLES

    These variables are used or set in the error routines.
*/

const char *progname = NULL;
const char *progvers = NULL;
int exit_status = EXIT_SUCCESS;
int maximum_errors = 20;
int number_errors = 0;

int crt_line_no = 1;
const char *crt_file_name = NULL;


/*
    SET PROGRAM NAME

    This routine sets the program name to nm and the program version to
    vers.
*/

void
set_progname(const char *nm, const char *vers)
{
	char *r = strrchr(nm, '/'); /* XXX: basename(3) ? */
	progname = (r ? r + 1 : nm);
	progvers = vers;
}


/*
    PRINT VERSION NUMBER

    This routine prints the program name and version number.
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
    PRINT AN ERROR MESSAGE

    This routine prints an error message s with arguments args and severity
    e.  fn and ln give the error position.
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
    PRINT AN ERROR AT CURRENT POSITION

    This routine prints the error message s of severity e at the current
    file position.  s is a printf format string whose arguments are passed
    as the optional procedure parameters.
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
    PRINT AN ERROR AT A GIVEN POSITION

    This routine prints the error message s of severity e at the file
    position given by fn and ln.  s is as above.
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
    PRINT AN ASSERTION

    This routine prints the assertion s which occurred at the location
    given by file and line.
*/

void
assertion(const char *s, const char *file, int line)
{
    if (progname) fprintf(stderr, "%s: ", progname);
    fprintf(stderr, "Assertion: %s: line %d: '%s'.\n", file, line, s);
    abort();
}

#endif
