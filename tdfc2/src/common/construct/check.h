/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CHECK_INCLUDED
#define CHECK_INCLUDED


/*
    EXPRESSION CHECKING DECLARATIONS

    The routines in this module are concerned with checking various
    properties of expressions.
*/

extern int eq_token(TOKEN, TOKEN);
extern int eq_token_args(IDENTIFIER, IDENTIFIER, LIST(TOKEN), LIST(TOKEN));
extern DECL_SPEC find_exp_linkage(EXP, EXP *, int);
extern int eq_offset(OFFSET, OFFSET, int);
extern int eq_exp_exact(EXP, EXP);
extern int eq_exp(EXP, EXP, int);
extern int is_const_exp(EXP, int);
extern int is_const_offset(OFFSET, int, int);
extern int is_zero_offset(OFFSET);
extern int overflow_exp(EXP);
extern int know_type(EXP);


#endif
