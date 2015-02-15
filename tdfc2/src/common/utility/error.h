/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef ERROR_INCLUDED
#define ERROR_INCLUDED


#define ERR_WHATEVER		0
#define ERR_NONE		1
#define ERR_WARN		2
#define ERROR_OPTION		3
#define ERR_SERIOUS		4
#define ERR_INTERNAL		5
#define ERR_FATAL		6


extern ERROR make_error(int, ...);
extern void error(int, const char *, ...);
extern void set_progname(const char *, const char *);
extern string report_version(int);
extern void error_option(string);
extern void print_error(LOCATION *, ERROR);
extern EXP install_error(LOCATION *, ERROR);
extern void commentary(IDENTIFIER);
extern void destroy_error(ERROR, int);
extern ERROR concat_error(ERROR, ERROR);
extern ERROR concat_warning(ERROR, ERROR);
extern void add_error(ERROR *, ERROR);
extern void term_error(int);
extern ERROR set_prefix(ERROR);
extern void restore_prefix(ERROR);

#define report(A, B)	print_error(&(A), (B))
#define fail(A)		print_error(NIL(LOCATION), (A))
#define KILL_err	NIL(ERROR)


extern const char *progname;
extern const char *progvers;
extern int exit_status;
extern unsigned long number_errors;
extern unsigned long number_warnings;
extern unsigned long max_errors;
extern int error_severity[];
extern int default_severity[];
extern int verbose;
extern int error_threshold;
extern int no_error_args;
extern LOCATION crt_loc;
extern LOCATION builtin_loc;
extern FILE *error_file;


#ifdef ASSERTS
extern void assertion(const char *, const char *, int);
#define ASSERT(A)	if (!(A))\
			    assertion(#A, __FILE__, __LINE__)
#else
#if FS_LINT
#define ASSERT(A)	/* empty */
#else
#define ASSERT(A)	(IGNORE 0)
#endif
#endif

#define FAIL_COMPILER	ERROR[!]


#endif
