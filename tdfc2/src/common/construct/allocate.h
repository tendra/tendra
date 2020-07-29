/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef ALLOCATE_INCLUDED
#define ALLOCATE_INCLUDED


/*
    ALLOCATION EXPRESSION DECLARATIONS

    The routines in this module are used to build up the new and delete
    expressions.  sizeof expressions are also included for no very good
    reason.
*/

extern IDENTIFIER find_allocator(TYPE, int, int, IDENTIFIER);
extern TYPE check_allocator(TYPE, IDENTIFIER, int, int);
extern void recheck_allocator(IDENTIFIER, int);
extern EXP make_delete_exp(int, int, EXP);
extern EXP make_new_exp(TYPE, int, int, LIST(EXP), EXP);
extern EXP make_new_init(TYPE, LIST(EXP), int);
extern EXP begin_new_try(void);
extern EXP end_new_try(EXP, EXP);
extern EXP new_try_body(EXP);
extern EXP make_sizeof_exp(TYPE, EXP, int, int);
extern TYPE typeof_exp(EXP *, int, int);
extern NAT make_new_array_dim(EXP);
extern void old_delete_array(EXP);
extern EXP sizeof_array(TYPE *, TYPE);
extern EXP sizeof_init(EXP, TYPE);
extern EXP sizeof_exp(TYPE);


#endif
