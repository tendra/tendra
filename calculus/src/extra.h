/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef EXTRA_INCLUDED
#define EXTRA_INCLUDED


/*
 * EXTRA CALCULUS TOKEN SPECIFICATIONS
 *
 * This file contains the specifications for calculus-like tokens used
 * within the program.
 */

#if calculus_SPECIFICATION

#pragma token PROC {\
	TYPE t, EXP : LIST(t): e1,\
	EXP : LIST(t): e2, EXP : SIZE(t): e3 |\
	EXP e1, EXP e2, EXP e3\
    } EXP : LIST(t): ADD_list #

#pragma interface ADD_list

#endif


/*
 * EXTRA CALCULUS TOKEN IMPLEMENTATIONS
 *
 * The token specified above are implemented as follows.  The token
 * definitions are implementation specific.  The functions used are
 * defined in calculus.c.
 */

#if calculus_IMPLEMENTATION

extern calculus *add_calculus_list(calculus *, calculus *, int);

#define ADD_list(X, Y, Z)	add_calculus_list((X), (Y), (Z))

#endif


#endif
