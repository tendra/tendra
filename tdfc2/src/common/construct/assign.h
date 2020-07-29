/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef ASSIGN_INCLUDED
#define ASSIGN_INCLUDED


/*
    ASSIGNMENT EXPRESSION DECLARATIONS

    The routines in this module are concerned with the construction of the
    assignment expressions.
*/

extern EXP make_assign_exp(EXP, EXP, int);
extern EXP make_become_exp(int, EXP, EXP);
extern EXP make_postfix_exp(int, EXP);
extern EXP make_prefix_exp(int, EXP);
extern EXP convert_assign(TYPE, EXP, ERROR *);
extern EXP convert_class(TYPE, EXP, ERROR *);


#endif
