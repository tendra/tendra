/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef NAME_OPS_H_INCLUDED
#define NAME_OPS_H_INCLUDED

/* Operations for union NAME */

#pragma token PROC(EXP : NAME :) EXP : unsigned : TAG_name #
#pragma interface TAG_name


/* Operations for component id of union NAME */

#pragma token PROC(EXP : NAME :)\
    EXP : PTR(string) : name_id #
#pragma interface name_id

/* Operations for component number of union NAME */

#pragma token PROC(EXP : NAME :)\
    EXP : PTR(int) : name_number #
#pragma interface name_number

/* Operations for field basic of union NAME */

#pragma token EXP const : unsigned : name_basic_tag #
#pragma token PROC(EXP : NAME :) EXP : int : IS_name_basic #
#pragma interface name_basic_tag IS_name_basic

#pragma token PROC(\
	EXP : string :,\
	EXP : int :,\
	EXP lvalue : NAME :\
    ) STATEMENT MAKE_name_basic #
#pragma interface MAKE_name_basic

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP lvalue : int :,\
	EXP : NAME :\
    ) STATEMENT DECONS_name_basic #
#pragma interface DECONS_name_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : int :,\
	EXP : NAME :\
    ) STATEMENT DESTROY_name_basic #
#pragma interface DESTROY_name_basic


#endif
