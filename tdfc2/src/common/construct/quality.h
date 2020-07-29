/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef QUALITY_INCLUDED
#define QUALITY_INCLUDED


/*
    QUALITY CHECKING DECLARATIONS

    The routines in this module are concerned with quality style checks.
    These include detection of possible precedence errors.
*/

extern void check_logic(EXP, EXP);
extern void check_relation(int, EXP, EXP);
extern void check_paren(int, int, EXP, EXP);
extern int suppress_quality;


/*
    PARENTHESIS CHECKING VALUES

    These values are used to specify the level of parenthesis checking
    to be applied by check_paren.
*/

enum {
	PAREN_OR,
	PAREN_XOR,
	PAREN_AND,
	PAREN_EQUALITY,
	PAREN_RELATION,
	PAREN_PLUS,
	PAREN_MINUS
};


#endif
