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


#ifndef LABEL_INCLUDED
#define LABEL_INCLUDED


/*
    LABEL DECLARATIONS

    The routines in this module are concerned with labels and labelled
    statements.
*/

extern EXP begin_label_stmt PROTO_S ( ( IDENTIFIER, int ) ) ;
extern EXP end_label_stmt PROTO_S ( ( EXP, EXP ) ) ;
extern EXP make_goto_stmt PROTO_S ( ( IDENTIFIER ) ) ;
extern EXP make_jump_stmt PROTO_S ( ( IDENTIFIER, EXP ) ) ;
extern IDENTIFIER postlude_label PROTO_S ( ( void ) ) ;
extern IDENTIFIER find_postlude_label PROTO_S ( ( void ) ) ;
extern NAT find_case_nat PROTO_S ( ( IDENTIFIER ) ) ;
extern int used_label PROTO_S ( ( IDENTIFIER ) ) ;
extern unsigned check_labels PROTO_S ( ( void ) ) ;
extern EXP solve_labels PROTO_S ( ( EXP ) ) ;
extern EXP solve_switch PROTO_S ( ( EXP ) ) ;
extern void end_solve_stmts PROTO_S ( ( void ) ) ;
extern LIST ( EXP ) all_solve_stmts ;
extern LIST ( EXP ) all_try_blocks ;
extern NAMESPACE label_namespace ;


#endif
