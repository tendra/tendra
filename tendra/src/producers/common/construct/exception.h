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


#ifndef EXCEPT_INCLUDED
#define EXCEPT_INCLUDED


/*
    EXCEPTION HANDLING DECLARATIONS

    The routines in this module are concerned with exception handling.
*/

extern EXP make_throw_exp PROTO_S ( ( EXP, int ) ) ;
extern EXP make_throw_arg PROTO_S ( ( TYPE, int ) ) ;
extern EXP begin_catch_stmt PROTO_S ( ( EXP, IDENTIFIER ) ) ;
extern EXP end_catch_stmt PROTO_S ( ( EXP, EXP ) ) ;
extern EXP begin_try_stmt PROTO_S ( ( int ) ) ;
extern EXP cont_try_stmt PROTO_S ( ( EXP, EXP ) ) ;
extern EXP end_try_stmt PROTO_S ( ( EXP, int ) ) ;
extern void inject_try_stmt PROTO_S ( ( EXP ) ) ;
extern void end_try_blocks PROTO_S ( ( IDENTIFIER ) ) ;
extern IDENTIFIER make_except_decl PROTO_S ( ( DECL_SPEC, TYPE, IDENTIFIER, int ) ) ;
extern int check_func_throw PROTO_S ( ( TYPE, IDENTIFIER ) ) ;
extern int check_throw PROTO_S ( ( TYPE, int ) ) ;
extern void start_try_check PROTO_S ( ( LIST ( TYPE ) ) ) ;
extern EXP end_try_check PROTO_S ( ( IDENTIFIER, EXP ) ) ;
extern int check_try_block PROTO_S ( ( EXP ) ) ;

extern int eq_except PROTO_S ( ( TYPE, TYPE ) ) ;
extern int in_type_set PROTO_S ( ( LIST ( TYPE ), TYPE ) ) ;
extern int eq_type_set PROTO_S ( ( LIST ( TYPE ), LIST ( TYPE ), int ) ) ;
extern LIST ( TYPE ) union_type_set PROTO_S ( ( LIST ( TYPE ), LIST ( TYPE ) ) ) ;
extern LIST ( TYPE ) cons_type_set PROTO_S ( ( LIST ( TYPE ), TYPE ) ) ;
extern LIST ( TYPE ) uniq_type_set PROTO_S ( ( LIST ( TYPE ) ) ) ;
extern TYPE check_except_type PROTO_S ( ( TYPE, int ) ) ;
extern TYPE exception_type PROTO_S ( ( TYPE, int ) ) ;
extern void init_exception PROTO_S ( ( void ) ) ;
extern STACK ( EXP ) crt_try_blocks ;
extern LIST ( TYPE ) empty_type_set ;
extern LIST ( TYPE ) univ_type_set ;
extern int in_func_handler ;


#endif
