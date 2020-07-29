/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef PARAM_OPS_H_INCLUDED
#define PARAM_OPS_H_INCLUDED

/* Operations for union PARAM */

#pragma token PROC(EXP : PARAM :) EXP : unsigned : TAG_param #
#pragma interface TAG_param


/* Operations for component type of union PARAM */

#pragma token PROC(EXP : PARAM :)\
    EXP : PTR(TYPE) : param_type #
#pragma interface param_type

/* Operations for component name of union PARAM */

#pragma token PROC(EXP : PARAM :)\
    EXP : PTR(string) : param_name #
#pragma interface param_name

/* Operations for component number of union PARAM */

#pragma token PROC(EXP : PARAM :)\
    EXP : PTR(int) : param_number #
#pragma interface param_number

/* Operations for field basic of union PARAM */

#pragma token EXP const : unsigned : param_basic_tag #
#pragma token PROC(EXP : PARAM :) EXP : int : IS_param_basic #
#pragma interface param_basic_tag IS_param_basic

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : string :,\
	EXP : int :,\
	EXP lvalue : PARAM :\
    ) STATEMENT MAKE_param_basic #
#pragma interface MAKE_param_basic

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : string :,\
	EXP lvalue : int :,\
	EXP : PARAM :\
    ) STATEMENT DECONS_param_basic #
#pragma interface DECONS_param_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : string :,\
	EXP lvalue : int :,\
	EXP : PARAM :\
    ) STATEMENT DESTROY_param_basic #
#pragma interface DESTROY_param_basic


#endif
