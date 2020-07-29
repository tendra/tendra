/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef MSG_OPS_H_INCLUDED
#define MSG_OPS_H_INCLUDED

/* Operations for union MESSAGE */

#pragma token PROC(EXP : MESSAGE :) EXP : unsigned : TAG_msg #
#pragma interface TAG_msg


/* Operations for field param of union MESSAGE */

#pragma token EXP const : unsigned : msg_param_tag #
#pragma token PROC(EXP : MESSAGE :) EXP : int : IS_msg_param #
#pragma interface msg_param_tag IS_msg_param

#pragma token PROC(EXP : MESSAGE :)\
    EXP : PTR(PARAM) : msg_param_arg #
#pragma interface msg_param_arg

#pragma token PROC(\
	EXP : PARAM :,\
	EXP lvalue : MESSAGE :\
    ) STATEMENT MAKE_msg_param #
#pragma interface MAKE_msg_param

#pragma token PROC(\
	EXP lvalue : PARAM :,\
	EXP : MESSAGE :\
    ) STATEMENT DECONS_msg_param #
#pragma interface DECONS_msg_param

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : PARAM :,\
	EXP : MESSAGE :\
    ) STATEMENT DESTROY_msg_param #
#pragma interface DESTROY_msg_param


/* Operations for field text of union MESSAGE */

#pragma token EXP const : unsigned : msg_text_tag #
#pragma token PROC(EXP : MESSAGE :) EXP : int : IS_msg_text #
#pragma interface msg_text_tag IS_msg_text

#pragma token PROC(EXP : MESSAGE :)\
    EXP : PTR(string) : msg_text_arg #
#pragma interface msg_text_arg

#pragma token PROC(\
	EXP : string :,\
	EXP lvalue : MESSAGE :\
    ) STATEMENT MAKE_msg_text #
#pragma interface MAKE_msg_text

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP : MESSAGE :\
    ) STATEMENT DECONS_msg_text #
#pragma interface DECONS_msg_text

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP : MESSAGE :\
    ) STATEMENT DESTROY_msg_text #
#pragma interface DESTROY_msg_text


#endif
