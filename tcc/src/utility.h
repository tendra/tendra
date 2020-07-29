/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef UTILITY_H
#define UTILITY_H

#include <stddef.h>


/*
 * TEMPORARY WORK SPACE
 *
 * This is used as a scratch work area.
 */

extern char *buffer;
#define buffer_size	5000


/*
 * PROCEDURE DECLARATIONS
 *
 * These routines are concerned with error reporting and memory allocation.
 * TODO these ought to use shared/ instead.
 */

extern void comment(int, char *, ...);
extern char *string_append(const char *, const char *, char);


/*
 * UTILITY MACROS
 *
 * These macros give convenient shorthands for various constructs.
 */

#define alloc_size(T, N)	((N) * sizeof(T))
#define array_size(A)		(sizeof(A) / sizeof(A[0]))


#endif /* UTILITY_H */
