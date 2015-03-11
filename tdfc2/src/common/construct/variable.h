/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef VARIABLE_INCLUDED
#define VARIABLE_INCLUDED


/*
    VARIABLE ANALYSIS DECLARATIONS

    The routines in this module are concerned with the variable analysis
    checks.
*/

extern unsigned long check_global(int);
extern unsigned long check_namespace(NAMESPACE, EXP, int, int);
extern unsigned long check_identifier(IDENTIFIER, NAMESPACE, EXP, int, int);
extern void check_flow(IDENTIFIER, EXP, int);
extern void preserve_id(IDENTIFIER, int);
extern EXP make_unused_exp(EXP);
extern EXP make_set_exp(EXP);
extern int suppress_variable;
extern int anon_c_linkage;
extern int preserve_all;


/*
    VARIABLE CHECK STATES

    These values are used to indicate the checking level in check_namespace,
    check_identifier etc.
*/

enum {
	ANON_NONE,
	ANON_INLINE,
	ANON_NAMESPACE,
	ANON_CLASS,
	ANON_GLOBAL
};


#endif
