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


#ifndef STATEMENT_INCLUDED
#define STATEMENT_INCLUDED


/*
    STATEMENT CONSTRUCTION DECLARATIONS

    The routines in this module are used in the construction of the
    basic language statements.
*/

extern EXP begin_case_stmt PROTO_S ( ( EXP, int ) ) ;
extern EXP begin_compound_stmt PROTO_S ( ( int ) ) ;
extern EXP begin_default_stmt PROTO_S ( ( int ) ) ;
extern EXP begin_do_stmt PROTO_S ( ( void ) ) ;
extern EXP begin_for_stmt PROTO_S ( ( void ) ) ;
extern EXP begin_hash_if_stmt PROTO_S ( ( EXP, EXP ) ) ;
extern EXP begin_if_stmt PROTO_S ( ( EXP ) ) ;
extern EXP begin_switch_stmt PROTO_S ( ( EXP ) ) ;
extern EXP begin_while_stmt PROTO_S ( ( EXP ) ) ;

extern void mark_compound_stmt PROTO_S ( ( EXP ) ) ;
extern EXP add_compound_stmt PROTO_S ( ( EXP, EXP ) ) ;
extern EXP cont_hash_if_stmt PROTO_S ( ( EXP, EXP, EXP ) ) ;
extern EXP cont_if_stmt PROTO_S ( ( EXP, EXP ) ) ;
extern EXP init_for_stmt PROTO_S ( ( EXP, EXP * ) ) ;
extern EXP cond_for_stmt PROTO_S ( ( EXP, EXP, EXP ) ) ;

extern EXP end_case_stmt PROTO_S ( ( EXP, EXP ) ) ;
extern EXP end_compound_stmt PROTO_S ( ( EXP ) ) ;
extern EXP end_default_stmt PROTO_S ( ( EXP, EXP ) ) ;
extern EXP end_do_stmt PROTO_S ( ( EXP, EXP, EXP ) ) ;
extern EXP end_for_stmt PROTO_S ( ( EXP, EXP ) ) ;
extern EXP end_hash_if_stmt PROTO_S ( ( EXP, EXP ) ) ;
extern EXP end_if_stmt PROTO_S ( ( EXP, EXP ) ) ;
extern EXP end_switch_stmt PROTO_S ( ( EXP, EXP, int ) ) ;
extern EXP end_while_stmt PROTO_S ( ( EXP, EXP ) ) ;

extern EXP make_break_stmt PROTO_S ( ( void ) ) ;
extern EXP make_continue_stmt PROTO_S ( ( void ) ) ;
extern EXP make_decl_stmt PROTO_S ( ( MEMBER, MEMBER, int * ) ) ;
extern EXP make_temp_decl PROTO_S ( ( MEMBER, MEMBER, EXP ) ) ;
extern EXP make_exp_stmt PROTO_S ( ( EXP ) ) ;
extern EXP make_return_stmt PROTO_S ( ( EXP, int ) ) ;
extern EXP make_discard_exp PROTO_S ( ( EXP ) ) ;
extern EXP make_reach_stmt PROTO_S ( ( EXP, int ) ) ;
extern EXP fall_return_stmt PROTO_S ( ( void ) ) ;
extern EXP find_return_exp PROTO_S ( ( EXP, IDENTIFIER *, int ) ) ;
extern EXP check_return_exp PROTO_S ( ( EXP, int ) ) ;

extern EXP bind_temporary PROTO_S ( ( EXP ) ) ;
extern void begin_cond PROTO_S ( ( void ) ) ;
extern EXP end_cond PROTO_S ( ( void ) ) ;
extern EXP inject_cond PROTO_S ( ( EXP, EXP ) ) ;
extern TYPE make_cond_type PROTO_S ( ( TYPE ) ) ;
extern EXP check_cond PROTO_S ( ( EXP, EXP *, int ) ) ;
extern EXP check_control PROTO_S ( ( EXP, EXP *, EXP * ) ) ;
extern void check_empty_stmt PROTO_S ( ( int ) ) ;
extern EXP make_if_cond PROTO_S ( ( EXP, EXP ) ) ;
extern EXP make_else_cond PROTO_S ( ( EXP ) ) ;
extern IDENTIFIER find_case PROTO_S ( ( LIST ( NAT ), LIST ( IDENTIFIER ), NAT ) ) ;
extern EXP make_asm PROTO_S ( ( EXP, LIST ( EXP ) ) ) ;

extern void set_parent_stmt PROTO_S ( ( EXP, EXP ) ) ;
extern EXP get_parent_stmt PROTO_S ( ( EXP ) ) ;
extern STACK ( EXP ) crt_loop_stack ;
extern NAMESPACE block_namespace ;
extern unsigned crt_condition ;
extern int record_location ;
extern int unreached_code ;
extern int unreached_last ;
extern int unreached_prev ;
extern int unreached_fall ;
extern int suppress_fall ;
extern EXP crt_hash_cond ;
extern LOCATION stmt_loc ;


#endif
