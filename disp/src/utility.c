/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdarg.h>
#include <stdlib.h>

#include <shared/check.h>
#include <shared/error.h>

#include "types.h"
#include "file.h"
#include "pretty.h"
#include "utility.h"


/*
 * RECOVERY FLAG
 *
 * This flag controls whether an attempt is made to recover from
 * non-fatal errors.  Anything after an error is likely to be of very
 * little use.
 */
int recover = 0;


/*
 * REPORT A FATAL ERROR
 *
 * An error is reported and the program aborts immediately.
 */
void
fatal_error(char *s, ...) /* VARARGS */
{
    va_list args;
    va_start(args, s);
    if (progname)IGNORE fprintf(stderr, "%s: ", progname);
    IGNORE fprintf(stderr, "Error: ");
    IGNORE vfprintf(stderr, s, args);
    IGNORE fprintf(stderr, ".\n");
    va_end(args);
    exit(EXIT_FAILURE);
}


/*
 * REPORT AN INPUT ERROR
 *
 * An error is reported together with the position within the input
 * file where it occured, and the program either attempts to recover
 * (if the recover flag is true) or outputs what it has read so far
 * and then exits (otherwise).
 */
void
input_error(char *s, ...) /* VARARGS */
{
    va_list args;
    long b = here.byte;
    va_start(args, s);
    if (progname)IGNORE fprintf(stderr, "%s: ", progname);
    IGNORE fprintf(stderr, "Error: ");
    IGNORE vfprintf(stderr, s, args);
    IGNORE fprintf(stderr, ", byte %ld, bit %d.\n", b, here.bit);
    va_end(args);
    exit_status = EXIT_FAILURE;
    if (!recover) {
	pretty_tree();
	exit(EXIT_FAILURE);
    }
    return;
}
