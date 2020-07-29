/*
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef CONS_OPS_H_INCLUDED
#define CONS_OPS_H_INCLUDED

/* Operations for union CONSTRUCT */

#pragma token PROC(EXP : CONSTRUCT :) EXP : unsigned : TAG_cons #
#pragma interface TAG_cons


/* Operations for component name of union CONSTRUCT */

#pragma token PROC(EXP : CONSTRUCT :)\
    EXP : PTR(string) : cons_name #
#pragma interface cons_name

/* Operations for component encode of union CONSTRUCT */

#pragma token PROC(EXP : CONSTRUCT :)\
    EXP : PTR(unsigned) : cons_encode #
#pragma interface cons_encode

/* Operations for component res of union CONSTRUCT */

#pragma token PROC(EXP : CONSTRUCT :)\
    EXP : PTR(SORT) : cons_res #
#pragma interface cons_res

/* Operations for component pars of union CONSTRUCT */

#pragma token PROC(EXP : CONSTRUCT :)\
    EXP : PTR(LIST(PARAMETER)) : cons_pars #
#pragma interface cons_pars

/* Operations for component kind of union CONSTRUCT */

#pragma token PROC(EXP : CONSTRUCT :)\
    EXP : PTR(unsigned) : cons_kind #
#pragma interface cons_kind

/* Operations for field basic of union CONSTRUCT */

#pragma token EXP const : unsigned : cons_basic_tag #
#pragma token PROC(EXP : CONSTRUCT :) EXP : int : IS_cons_basic #
#pragma interface cons_basic_tag IS_cons_basic

#pragma token PROC(\
	EXP : string :,\
	EXP : unsigned :,\
	EXP : SORT :,\
	EXP : LIST(PARAMETER) :,\
	EXP : unsigned :,\
	EXP lvalue : CONSTRUCT :\
    ) STATEMENT MAKE_cons_basic #
#pragma interface MAKE_cons_basic

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : SORT :,\
	EXP lvalue : LIST(PARAMETER) :,\
	EXP lvalue : unsigned :,\
	EXP : CONSTRUCT :\
    ) STATEMENT DECONS_cons_basic #
#pragma interface DECONS_cons_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : SORT :,\
	EXP lvalue : LIST(PARAMETER) :,\
	EXP lvalue : unsigned :,\
	EXP : CONSTRUCT :\
    ) STATEMENT DESTROY_cons_basic #
#pragma interface DESTROY_cons_basic


#endif
