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

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA calculus (VERSION 1.2)
    BY calculus (VERSION 1.2)
*/

#ifndef CMD_OPS_H_INCLUDED
#define CMD_OPS_H_INCLUDED

/* Operations for union COMMAND */

#pragma token PROC ( EXP : COMMAND : ) EXP : unsigned : TAG_cmd #
#pragma interface TAG_cmd


/* Operations for component line of union COMMAND */

#pragma token PROC ( EXP : COMMAND : )\
    EXP : PTR ( int ) : cmd_line #
#pragma interface cmd_line

/* Operations for field simple of union COMMAND */

#pragma token EXP const : unsigned : cmd_simple_tag #
#pragma token PROC ( EXP : COMMAND : ) EXP : int : IS_cmd_simple #
#pragma interface cmd_simple_tag IS_cmd_simple

#pragma token PROC ( EXP : COMMAND : )\
    EXP : PTR ( string ) : cmd_simple_text #
#pragma interface cmd_simple_text

#pragma token PROC (\
	EXP : int :,\
	EXP : string :,\
	EXP lvalue : COMMAND :\
    ) STATEMENT MAKE_cmd_simple #
#pragma interface MAKE_cmd_simple

#pragma token PROC (\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP : COMMAND :\
    ) STATEMENT DECONS_cmd_simple #
#pragma interface DECONS_cmd_simple

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP : COMMAND :\
    ) STATEMENT DESTROY_cmd_simple #
#pragma interface DESTROY_cmd_simple


/* Operations for field compound of union COMMAND */

#pragma token EXP const : unsigned : cmd_compound_tag #
#pragma token PROC ( EXP : COMMAND : ) EXP : int : IS_cmd_compound #
#pragma interface cmd_compound_tag IS_cmd_compound

#pragma token PROC ( EXP : COMMAND : )\
    EXP : PTR ( LIST ( COMMAND ) ) : cmd_compound_seq #
#pragma interface cmd_compound_seq

#pragma token PROC (\
	EXP : int :,\
	EXP : LIST ( COMMAND ) :,\
	EXP lvalue : COMMAND :\
    ) STATEMENT MAKE_cmd_compound #
#pragma interface MAKE_cmd_compound

#pragma token PROC (\
	EXP lvalue : int :,\
	EXP lvalue : LIST ( COMMAND ) :,\
	EXP : COMMAND :\
    ) STATEMENT DECONS_cmd_compound #
#pragma interface DECONS_cmd_compound

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : int :,\
	EXP lvalue : LIST ( COMMAND ) :,\
	EXP : COMMAND :\
    ) STATEMENT DESTROY_cmd_compound #
#pragma interface DESTROY_cmd_compound


/* Operations for field loop of union COMMAND */

#pragma token EXP const : unsigned : cmd_loop_tag #
#pragma token PROC ( EXP : COMMAND : ) EXP : int : IS_cmd_loop #
#pragma interface cmd_loop_tag IS_cmd_loop

#pragma token PROC ( EXP : COMMAND : )\
    EXP : PTR ( string ) : cmd_loop_control #
#pragma interface cmd_loop_control

#pragma token PROC ( EXP : COMMAND : )\
    EXP : PTR ( COMMAND ) : cmd_loop_body #
#pragma interface cmd_loop_body

#pragma token PROC (\
	EXP : int :,\
	EXP : string :,\
	EXP : COMMAND :,\
	EXP lvalue : COMMAND :\
    ) STATEMENT MAKE_cmd_loop #
#pragma interface MAKE_cmd_loop

#pragma token PROC (\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP lvalue : COMMAND :,\
	EXP : COMMAND :\
    ) STATEMENT DECONS_cmd_loop #
#pragma interface DECONS_cmd_loop

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP lvalue : COMMAND :,\
	EXP : COMMAND :\
    ) STATEMENT DESTROY_cmd_loop #
#pragma interface DESTROY_cmd_loop


/* Operations for field cond of union COMMAND */

#pragma token EXP const : unsigned : cmd_cond_tag #
#pragma token PROC ( EXP : COMMAND : ) EXP : int : IS_cmd_cond #
#pragma interface cmd_cond_tag IS_cmd_cond

#pragma token PROC ( EXP : COMMAND : )\
    EXP : PTR ( string ) : cmd_cond_control #
#pragma interface cmd_cond_control

#pragma token PROC ( EXP : COMMAND : )\
    EXP : PTR ( COMMAND ) : cmd_cond_true_code #
#pragma interface cmd_cond_true_code

#pragma token PROC ( EXP : COMMAND : )\
    EXP : PTR ( COMMAND ) : cmd_cond_false_code #
#pragma interface cmd_cond_false_code

#pragma token PROC (\
	EXP : int :,\
	EXP : string :,\
	EXP : COMMAND :,\
	EXP : COMMAND :,\
	EXP lvalue : COMMAND :\
    ) STATEMENT MAKE_cmd_cond #
#pragma interface MAKE_cmd_cond

#pragma token PROC (\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP lvalue : COMMAND :,\
	EXP lvalue : COMMAND :,\
	EXP : COMMAND :\
    ) STATEMENT DECONS_cmd_cond #
#pragma interface DECONS_cmd_cond

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : int :,\
	EXP lvalue : string :,\
	EXP lvalue : COMMAND :,\
	EXP lvalue : COMMAND :,\
	EXP : COMMAND :\
    ) STATEMENT DESTROY_cmd_cond #
#pragma interface DESTROY_cmd_cond


#endif
