/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef OPERATOR_INCLUDED
#define OPERATOR_INCLUDED


/*
    OPERATOR OVERLOADING DECLARATIONS

    The routines in this module are concerned with operator overloading.
*/

extern EXP apply_unary(int, EXP, TYPE, TYPE, int);
extern EXP apply_binary(int, EXP, EXP, TYPE, TYPE, int);
extern EXP apply_nary(int, LIST(EXP), TYPE, TYPE, int);
extern EXP unary_overload(int, EXP);
extern EXP binary_overload(int, EXP, EXP);
extern EXP function_overload(EXP, LIST(EXP));
extern TYPE check_operator(TYPE, IDENTIFIER, int, int *);
extern EXP apply_builtin(IDENTIFIER, LIST(EXP));
extern int ntest_token(NTEST, int);
extern int op_token(EXP, int);
extern int overload_depth;
extern int overload_warn;


#endif
