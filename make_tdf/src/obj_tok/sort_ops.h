/*
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef SORT_OPS_H_INCLUDED
#define SORT_OPS_H_INCLUDED

/* Operations for union SORT */

#pragma token PROC(EXP : SORT :) EXP : unsigned : TAG_sort #
#pragma interface TAG_sort


/* Operations for component name of union SORT */

#pragma token PROC(EXP : SORT :)\
    EXP : PTR(string) : sort_name #
#pragma interface sort_name

/* Operations for component caps of union SORT */

#pragma token PROC(EXP : SORT :)\
    EXP : PTR(string) : sort_caps #
#pragma interface sort_caps

/* Operations for component link of union SORT */

#pragma token PROC(EXP : SORT :)\
    EXP : PTR(string) : sort_link #
#pragma interface sort_link

/* Operations for component unit of union SORT */

#pragma token PROC(EXP : SORT :)\
    EXP : PTR(string) : sort_unit #
#pragma interface sort_unit

/* Operations for component code of union SORT */

#pragma token PROC(EXP : SORT :)\
    EXP : PTR(int) : sort_code #
#pragma interface sort_code

/* Operations for component mark of union SORT */

#pragma token PROC(EXP : SORT :)\
    EXP : PTR(int) : sort_mark #
#pragma interface sort_mark

/* Operations for component special of union SORT */

#pragma token PROC(EXP : SORT :)\
    EXP : PTR(int) : sort_special #
#pragma interface sort_special

/* Operations for component edge of union SORT */

#pragma token PROC(EXP : SORT :)\
    EXP : PTR(int) : sort_edge #
#pragma interface sort_edge

/* Operations for component info of union SORT */

#pragma token PROC(EXP : SORT :)\
    EXP : PTR(SORT_INFO) : sort_info #
#pragma interface sort_info

/* Operations for field basic of union SORT */

#pragma token EXP const : unsigned : sort_basic_tag #
#pragma token PROC(EXP : SORT :) EXP : int : IS_sort_basic #
#pragma interface sort_basic_tag IS_sort_basic

#pragma token PROC(\
	EXP : string :,\
	EXP : string :,\
	EXP : string :,\
	EXP : string :,\
	EXP : int :,\
	EXP : int :,\
	EXP : int :,\
	EXP : int :,\
	EXP : SORT_INFO :,\
	EXP lvalue : SORT :\
    ) STATEMENT MAKE_sort_basic #
#pragma interface MAKE_sort_basic

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : SORT_INFO :,\
	EXP : SORT :\
    ) STATEMENT DECONS_sort_basic #
#pragma interface DECONS_sort_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : SORT_INFO :,\
	EXP : SORT :\
    ) STATEMENT DESTROY_sort_basic #
#pragma interface DESTROY_sort_basic


#endif
