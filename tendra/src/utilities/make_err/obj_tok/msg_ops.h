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
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.2)
*/

#ifndef MSG_OPS_H_INCLUDED
#define MSG_OPS_H_INCLUDED

/* Operations for union MESSAGE */

#pragma token PROC ( EXP : MESSAGE : ) EXP : unsigned : TAG_msg #
#pragma interface TAG_msg


/* Operations for field param of union MESSAGE */

#pragma token EXP const : unsigned : msg_param_tag #
#pragma token PROC ( EXP : MESSAGE : ) EXP : int : IS_msg_param #
#pragma interface msg_param_tag IS_msg_param

#pragma token PROC ( EXP : MESSAGE : )\
    EXP : PTR ( PARAM ) : msg_param_arg #
#pragma interface msg_param_arg

#pragma token PROC (\
	EXP : PARAM :,\
	EXP lvalue : MESSAGE :\
    ) STATEMENT MAKE_msg_param #
#pragma interface MAKE_msg_param

#pragma token PROC (\
	EXP lvalue : PARAM :,\
	EXP : MESSAGE :\
    ) STATEMENT DECONS_msg_param #
#pragma interface DECONS_msg_param

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : PARAM :,\
	EXP : MESSAGE :\
    ) STATEMENT DESTROY_msg_param #
#pragma interface DESTROY_msg_param


/* Operations for field text of union MESSAGE */

#pragma token EXP const : unsigned : msg_text_tag #
#pragma token PROC ( EXP : MESSAGE : ) EXP : int : IS_msg_text #
#pragma interface msg_text_tag IS_msg_text

#pragma token PROC ( EXP : MESSAGE : )\
    EXP : PTR ( string ) : msg_text_arg #
#pragma interface msg_text_arg

#pragma token PROC (\
	EXP : string :,\
	EXP lvalue : MESSAGE :\
    ) STATEMENT MAKE_msg_text #
#pragma interface MAKE_msg_text

#pragma token PROC (\
	EXP lvalue : string :,\
	EXP : MESSAGE :\
    ) STATEMENT DECONS_msg_text #
#pragma interface DECONS_msg_text

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP : MESSAGE :\
    ) STATEMENT DESTROY_msg_text #
#pragma interface DESTROY_msg_text


#endif
