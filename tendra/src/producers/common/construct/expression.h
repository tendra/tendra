/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


#ifndef EXPRESSION_INCLUDED
#define EXPRESSION_INCLUDED


/*
    EXPRESSION CONSTRUCTION DECLARATIONS

    The routines in this module are used to build up the basic expressions.
    They, and the similar routines in statement.c and elsewhere, are the
    main interface between the parser and the internal processing routines.
*/

extern EXP make_and_exp PROTO_S ( ( EXP, EXP ) ) ;
extern EXP make_comma_exp PROTO_S ( ( LIST ( EXP ) ) ) ;
extern EXP make_cond_exp PROTO_S ( ( EXP, EXP, EXP ) ) ;
extern EXP make_equality_exp PROTO_S ( ( int, EXP, EXP ) ) ;
extern EXP make_error_exp PROTO_S ( ( int ) ) ;
extern EXP make_index_exp PROTO_S ( ( EXP, EXP ) ) ;
extern EXP make_indir_exp PROTO_S ( ( EXP ) ) ;
extern EXP make_log_and_exp PROTO_S ( ( EXP, EXP ) ) ;
extern EXP make_log_or_exp PROTO_S ( ( EXP, EXP ) ) ;
extern EXP make_minus_exp PROTO_S ( ( EXP, EXP ) ) ;
extern EXP make_mult_exp PROTO_S ( ( int, EXP, EXP ) ) ;
extern EXP make_not_exp PROTO_S ( ( EXP ) ) ;
extern EXP make_or_exp PROTO_S ( ( EXP, EXP ) ) ;
extern EXP make_paren_exp PROTO_S ( ( EXP ) ) ;
extern EXP make_plus_exp PROTO_S ( ( EXP, EXP ) ) ;
extern EXP make_ref_exp PROTO_S ( ( EXP, int ) ) ;
extern EXP make_ref_object PROTO_S ( ( EXP, ERROR * ) ) ;
extern EXP make_relation_exp PROTO_S ( ( int, EXP, EXP ) ) ;
extern EXP make_rem_exp PROTO_S ( ( EXP, EXP ) ) ;
extern EXP make_shift_exp PROTO_S ( ( int, EXP, EXP ) ) ;
extern EXP make_uminus_exp PROTO_S ( ( int, EXP ) ) ;
extern EXP make_xor_exp PROTO_S ( ( EXP, EXP ) ) ;
extern EXP join_exp PROTO_S ( ( EXP, EXP ) ) ;

extern OFFSET make_off_mult PROTO_S ( ( TYPE, EXP, int ) ) ;
extern EXP make_add_ptr PROTO_S ( ( TYPE, EXP, OFFSET ) ) ;
extern EXP make_null_ptr PROTO_S ( ( EXP, TYPE ) ) ;
extern int check_div_exp PROTO_S ( ( int, EXP, EXP ) ) ;
extern int check_shift_exp PROTO_S ( ( int, TYPE, EXP, EXP ) ) ;
extern int division_mode ;


#endif
