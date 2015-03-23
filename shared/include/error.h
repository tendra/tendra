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

enum error_severity {
	ERR_WARN,    	/* Warning */
	ERR_SERIOUS, 	/* Error, does exit after N errors */
	ERR_USAGE,   	/* Error in command line usage; exits immediately */
	ERR_INTERNAL,	/* Internal error, does exit after N errors */
	ERR_FATAL    	/* Fatal exits immediately */
};

void error(enum error_severity, const char *, ...);
void error_posn(enum error_severity, const char *, int, const char *, ...);
void set_progname(const char *, const char *);
void report_version(FILE *);
void fmt_register(char c, void (*f)(FILE *fp, void *));

extern const char *progname;
extern const char *progvers;
extern int exit_status;
extern unsigned long maximum_errors;
extern unsigned long number_errors;
extern int crt_line_no;
extern const char *crt_file_name;

#endif

