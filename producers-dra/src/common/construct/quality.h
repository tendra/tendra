/* $Id$ */

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

#define PAREN_OR			0
#define PAREN_XOR			1
#define PAREN_AND			2
#define PAREN_EQUALITY			3
#define PAREN_RELATION			4
#define PAREN_PLUS			5
#define PAREN_MINUS			6


#endif
