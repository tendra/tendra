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


#ifndef ERROR_INCLUDED
#define ERROR_INCLUDED


/*
 *    ERROR SEVERITY LEVELS
 *
 *    These macros give the various error types recognised by the error
 *    routines.  Their values are in order of increasing severity.
 */

#define ERROR_WHATEVER		0
#define ERROR_NONE		1
#define ERROR_WARNING		2
#define ERROR_OPTION		3
#define ERROR_SERIOUS		4
#define ERROR_INTERNAL		5
#define ERROR_FATAL		6


/*
 *    ERROR ROUTINE DECLARATIONS
 *
 *    The routines in this module are concerned with error reporting and
 *    related areas.
 */

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

#define report(A, B)		print_error (&(A), (B))
#define fail(A)		print_error (NIL (LOCATION), (A))
#define KILL_err		NIL (ERROR)


/*
 *    ERROR REPORTING VARIABLES
 *
 *    These variables are used in the configuration of the error reporting
 *    routines.
 */

extern const char *progname;
extern const char *progvers;
extern int exit_status;
extern unsigned long number_errors;
extern unsigned long number_warnings;
extern unsigned long max_errors;
extern int error_severity [];
extern int default_severity [];
extern int verbose;
extern int error_threshold;
extern int no_error_args;
extern LOCATION crt_loc;
extern LOCATION builtin_loc;
extern FILE *error_file;


/*
 *    ASSERTION ROUTINE DECLARATIONS
 *
 *    These macros are used to define assertions for aiding program
 *    development.  If the macro ASSERTS is defined then code for checking
 *    these assertions is output, otherwise the macros have no effect.
 *    Note that ASSERTS is automatically defined if DEBUG is (see config.h).
 *    FAIL_COMPILER is intended as an alternative to #error blows up some
 *    compilers even if it is not on the main compilation path.
 */

#ifdef ASSERTS
extern int is_true(int);
extern void assertion(const char *, const char *, int);
#define ASSERT(A)	if (is_true (!(A)))\
			    assertion (#A, __FILE__, __LINE__)
#define FAIL(A)	assertion (#A, __FILE__, __LINE__)
#else
#if FS_LINT
#define ASSERT(A)	/* empty */
#define FAIL(A)	/* empty */
#else
#define ASSERT(A)	(IGNORE 0)
#define FAIL(A)	(IGNORE 0)
#endif
#endif

#define FAIL_COMPILER	ERROR [!]


#endif
