/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED


/*
    GENERAL UTILITY ROUTINES

    These fall into two types, error reporting and memory allocation.
*/

extern void fatal_error(char *, ...);
extern void input_error(char *, ...);
extern int recover;


#endif
