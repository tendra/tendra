/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef DESTROY_INCLUDED
#define DESTROY_INCLUDED


/*
    EXPRESSION DESTRUCTION ROUTINES

    The routines in this module are concerned with the destruction and
    recycling of expressions.
*/

extern void free_exp(EXP, int);
extern void free_exp_list(LIST(EXP), int);
extern void free_function(IDENTIFIER);
extern void free_nspace(NAMESPACE);
extern void free_offset(OFFSET, int);


#endif
