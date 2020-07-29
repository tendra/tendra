/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef COPY_INCLUDED
#define COPY_INCLUDED


/*
    EXPRESSION COPYING DECLARATIONS

    The routines in this module are concerned with copying of expressions.
*/

extern EXP copy_exp(EXP, TYPE, TYPE);
extern EXP copy_func_exp(EXP, TYPE, TYPE);
extern LIST(EXP) copy_exp_list(LIST(EXP), TYPE, TYPE);
extern EXP eval_exp(EXP, int);
extern OFFSET copy_offset(OFFSET, int);
extern void copy_object(IDENTIFIER, EXP);
extern IDENTIFIER rescan_member(IDENTIFIER);
extern IDENTIFIER rescan_id(IDENTIFIER, QUALIFIER, int);
extern IDENTIFIER rescan_func_id(IDENTIFIER, QUALIFIER);
extern NAMESPACE rescan_nspace(NAMESPACE);
extern EXP implicit_cast_exp(EXP);


#endif
