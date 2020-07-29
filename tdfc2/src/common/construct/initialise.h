/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef INITIALISE_INCLUDED
#define INITIALISE_INCLUDED


/*
    INITIALISATION ROUTINES

    The routines in this module are concerned with the initialisation of
    variables.
*/

extern EXP init_empty(TYPE, CV_SPEC, int, ERROR *);
extern EXP init_assign(TYPE, CV_SPEC, EXP, ERROR *);
extern EXP init_constr(TYPE, LIST(EXP), ERROR *);
extern EXP init_direct(TYPE, EXP, ERROR *);
extern EXP init_ref_lvalue(TYPE, EXP, ERROR *);
extern EXP init_array(TYPE, CV_SPEC, EXP, int, ERROR *);
extern EXP init_aggregate(TYPE, EXP, IDENTIFIER, ERROR *);
extern EXP init_general(TYPE, EXP, IDENTIFIER, int);
extern EXP dynamic_init(IDENTIFIER, string, EXP);
extern EXP destroy_general(TYPE, IDENTIFIER);
extern ERROR init_error(ERROR, int);
extern void init_initialise(void);
extern BUFFER field_buff;

extern MEMBER next_data_member(MEMBER, int);
extern EXP make_ref_init(TYPE, EXP);
extern EXP make_null_exp(TYPE);
extern EXP make_unit_exp(TYPE);
extern int is_null_exp(EXP);
extern EXP check_init(EXP);
extern unsigned long member_no;

extern EXP make_temporary(TYPE, EXP, EXP, int, ERROR *);
extern EXP remove_temporary(EXP, EXP);
extern IDENTIFIER made_temporary;
extern int keep_temporary;

extern int init_object(IDENTIFIER, EXP);
extern int init_member(IDENTIFIER, EXP);
extern void init_param(IDENTIFIER, EXP);
extern void allow_initialiser(IDENTIFIER);
extern int init_ref_force;


#endif
