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


#ifndef INITIALISE_INCLUDED
#define INITIALISE_INCLUDED


/*
    INITIALISATION ROUTINES

    The routines in this module are concerned with the initialisation of
    variables.
*/

extern EXP init_empty PROTO_S ( ( TYPE, CV_SPEC, int, ERROR * ) ) ;
extern EXP init_assign PROTO_S ( ( TYPE, CV_SPEC, EXP, ERROR * ) ) ;
extern EXP init_constr PROTO_S ( ( TYPE, LIST ( EXP ), ERROR * ) ) ;
extern EXP init_direct PROTO_S ( ( TYPE, EXP, ERROR * ) ) ;
extern EXP init_ref_lvalue PROTO_S ( ( TYPE, EXP, ERROR * ) ) ;
extern EXP init_array PROTO_S (  ( TYPE, CV_SPEC, EXP, int, ERROR * ) ) ;
extern EXP init_aggregate PROTO_S ( ( TYPE, EXP, IDENTIFIER, ERROR * ) ) ;
extern EXP init_general PROTO_S ( ( TYPE, EXP, IDENTIFIER, int ) ) ;
extern EXP dynamic_init PROTO_S ( ( IDENTIFIER, string, EXP ) ) ;
extern EXP destroy_general PROTO_S ( ( TYPE, IDENTIFIER ) ) ;
extern ERROR init_error PROTO_S ( ( ERROR, int ) ) ;
extern void init_initialise PROTO_S ( ( void ) ) ;
extern BUFFER field_buff ;

extern MEMBER next_data_member PROTO_S ( ( MEMBER, int ) ) ;
extern EXP make_ref_init PROTO_S ( ( TYPE, EXP ) ) ;
extern EXP make_null_exp PROTO_S ( ( TYPE ) ) ;
extern EXP make_unit_exp PROTO_S ( ( TYPE ) ) ;
extern int is_null_exp PROTO_S ( ( EXP ) ) ;
extern EXP check_init PROTO_S ( ( EXP ) ) ;
extern unsigned long member_no ;

extern EXP make_temporary PROTO_S ( ( TYPE, EXP, EXP, int, ERROR * ) ) ;
extern EXP remove_temporary PROTO_S ( ( EXP, EXP ) ) ;
extern IDENTIFIER made_temporary ;
extern int keep_temporary ;

extern int init_object PROTO_S ( ( IDENTIFIER, EXP ) ) ;
extern int init_member PROTO_S ( ( IDENTIFIER, EXP ) ) ;
extern void init_param PROTO_S ( ( IDENTIFIER, EXP ) ) ;
extern void allow_initialiser PROTO_S ( ( IDENTIFIER ) ) ;
extern int init_ref_force ;


#endif
