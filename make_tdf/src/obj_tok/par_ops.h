/*
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef PAR_OPS_H_INCLUDED
#define PAR_OPS_H_INCLUDED

/* Operations for union PARAMETER */

#pragma token PROC(EXP : PARAMETER :) EXP : unsigned : TAG_par #
#pragma interface TAG_par


/* Operations for component name of union PARAMETER */

#pragma token PROC(EXP : PARAMETER :)\
    EXP : PTR(string) : par_name #
#pragma interface par_name

/* Operations for component type of union PARAMETER */

#pragma token PROC(EXP : PARAMETER :)\
    EXP : PTR(SORT) : par_type #
#pragma interface par_type

/* Operations for component brk of union PARAMETER */

#pragma token PROC(EXP : PARAMETER :)\
    EXP : PTR(int) : par_brk #
#pragma interface par_brk

/* Operations for component align of union PARAMETER */

#pragma token PROC(EXP : PARAMETER :)\
    EXP : PTR(int) : par_align #
#pragma interface par_align

/* Operations for component intro of union PARAMETER */

#pragma token PROC(EXP : PARAMETER :)\
    EXP : PTR(int) : par_intro #
#pragma interface par_intro

/* Operations for field basic of union PARAMETER */

#pragma token EXP const : unsigned : par_basic_tag #
#pragma token PROC(EXP : PARAMETER :) EXP : int : IS_par_basic #
#pragma interface par_basic_tag IS_par_basic

#pragma token PROC(\
	EXP : string :,\
	EXP : SORT :,\
	EXP : int :,\
	EXP : int :,\
	EXP : int :,\
	EXP lvalue : PARAMETER :\
    ) STATEMENT MAKE_par_basic #
#pragma interface MAKE_par_basic

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP lvalue : SORT :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP : PARAMETER :\
    ) STATEMENT DECONS_par_basic #
#pragma interface DECONS_par_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : SORT :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP : PARAMETER :\
    ) STATEMENT DESTROY_par_basic #
#pragma interface DESTROY_par_basic


#endif
