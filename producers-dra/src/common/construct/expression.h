/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef EXPRESSION_INCLUDED
#define EXPRESSION_INCLUDED


/*
    EXPRESSION CONSTRUCTION DECLARATIONS

    The routines in this module are used to build up the basic expressions.
    They, and the similar routines in statement.c and elsewhere, are the
    main interface between the parser and the internal processing routines.
*/

extern EXP make_and_exp(EXP, EXP);
extern EXP make_comma_exp(LIST(EXP));
extern EXP make_cond_exp(EXP, EXP, EXP);
extern EXP make_equality_exp(int, EXP, EXP);
extern EXP make_error_exp(int);
extern EXP make_index_exp(EXP, EXP);
extern EXP make_indir_exp(EXP);
extern EXP make_log_and_exp(EXP, EXP);
extern EXP make_log_or_exp(EXP, EXP);
extern EXP make_minus_exp(EXP, EXP);
extern EXP make_mult_exp(int, EXP, EXP);
extern EXP make_not_exp(EXP);
extern EXP make_or_exp(EXP, EXP);
extern EXP make_paren_exp(EXP);
extern EXP make_plus_exp(EXP, EXP);
extern EXP make_ref_exp(EXP, int);
extern EXP make_ref_object(EXP, ERROR *);
extern EXP make_relation_exp(int, EXP, EXP);
extern EXP make_rem_exp(EXP, EXP);
extern EXP make_shift_exp(int, EXP, EXP);
extern EXP make_uminus_exp(int, EXP);
extern EXP make_xor_exp(EXP, EXP);
extern EXP join_exp(EXP, EXP);

extern OFFSET make_off_mult(TYPE, EXP, int);
extern EXP make_add_ptr(TYPE, EXP, OFFSET);
extern EXP make_null_ptr(EXP, TYPE);
extern int check_div_exp(int, EXP, EXP);
extern int check_shift_exp(int, TYPE, EXP, EXP);
extern int division_mode;


#endif
