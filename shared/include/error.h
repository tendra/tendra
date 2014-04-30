/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SHARED_ERROR_H
#define SHARED_ERROR_H

#include <stdio.h>

/*
 * ERROR SEVERITY LEVELS
 *
 * These macros give the various error types recognised by the error
 * routines.
 */

enum error_severity {
	ERROR_NONE,	    /* Error reporting off */
	ERROR_WARNING,  /* Warning */
	ERROR_SERIOUS,  /* Error, does exit after N errors */
	ERROR_USAGE,    /* Error in command line usage; exits immediately */
	ERROR_INTERNAL, /* Internal error, does exit after N errors */
	ERROR_FATAL     /* Fatal exits immediately */
};

/*
 * DECLARATIONS FOR ERROR ROUTINES
 */

void error(enum error_severity, const char *, ...);
void error_posn(enum error_severity, const char *, int, const char *, ...);
void set_progname(const char *, const char *);
void report_version(void);
void fmt_register(char c, void (*f)(FILE *fp, void *));

extern const char *progname;
extern const char *progvers;
extern int exit_status;
extern int maximum_errors;
extern int number_errors;
extern int crt_line_no;
extern const char *crt_file_name;

/*
 * DECLARATIONS FOR ASSERTION ROUTINES
 */

#ifdef ASSERTS
extern void assertion(const char *, const char *, int);
#define ASSERT(A)	if (!(A))assertion(#A, __FILE__, __LINE__)
#define FAIL(A)	assertion(#A, __FILE__, __LINE__)
#else
#define ASSERT(A)	((void)0)
#define FAIL(A)	((void)0)
#endif

#endif

