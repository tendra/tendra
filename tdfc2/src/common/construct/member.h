/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef MEMBER_INCLUDED
#define MEMBER_INCLUDED


/*
    MEMBER SELECTOR DECLARATIONS

    The routines in this module are concerned with the construction and
    manipulation of class member selectors.
*/

extern EXP begin_field_exp(int, EXP, TYPE *, NAMESPACE *);
extern EXP end_field_exp(int, EXP, TYPE, NAMESPACE, IDENTIFIER, int);
extern EXP make_field_exp(int, EXP, EXP);
extern EXP make_member_exp(int, EXP, EXP);
extern EXP make_this_field(IDENTIFIER);

extern OFFSET decons_bitf_exp(EXP *);
extern OFFSET decons_bitf_off(OFFSET *);
extern NAMESPACE offset_nspace(TYPE);
extern OFFSET offset_member(TYPE, IDENTIFIER, TYPE *, NAMESPACE, int);
extern OFFSET offset_index(TYPE, EXP, TYPE *);
extern OFFSET offset_add(OFFSET, OFFSET);


#endif
