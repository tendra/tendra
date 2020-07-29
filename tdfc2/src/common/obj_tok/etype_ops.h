/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef ETYPE_OPS_H_INCLUDED
#define ETYPE_OPS_H_INCLUDED

/* Operations for union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :) EXP : unsigned : TAG_etype #
#pragma interface TAG_etype


/* Operations for component name of union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :)\
    EXP : PTR(IDENTIFIER) : etype_name #
#pragma interface etype_name

/* Operations for component info of union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :)\
    EXP : PTR(CLASS_INFO) : etype_info #
#pragma interface etype_info

/* Operations for component rep of union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :)\
    EXP : PTR(TYPE) : etype_rep #
#pragma interface etype_rep

/* Operations for component form of union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :)\
    EXP : PTR(TYPE) : etype_form #
#pragma interface etype_form

/* Operations for component values of union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :)\
    EXP : PTR(LIST(IDENTIFIER)) : etype_values #
#pragma interface etype_values

/* Operations for component value of union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :)\
    EXP : PTR(EXP) : etype_value #
#pragma interface etype_value

/* Operations for component plus of union ENUM_TYPE */

#pragma token PROC(EXP : ENUM_TYPE :)\
    EXP : PTR(ulong_type) : etype_plus #
#pragma interface etype_plus

/* Operations for field basic of union ENUM_TYPE */

#pragma token EXP const : unsigned : etype_basic_tag #
#pragma token PROC(EXP : ENUM_TYPE :) EXP : int : IS_etype_basic #
#pragma interface etype_basic_tag IS_etype_basic

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : CLASS_INFO :,\
	EXP : TYPE :,\
	EXP lvalue : ENUM_TYPE :\
    ) STATEMENT MAKE_etype_basic #
#pragma interface MAKE_etype_basic

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : CLASS_INFO :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : EXP :,\
	EXP lvalue : ulong_type :,\
	EXP : ENUM_TYPE :\
    ) STATEMENT DECONS_etype_basic #
#pragma interface DECONS_etype_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : CLASS_INFO :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : EXP :,\
	EXP lvalue : ulong_type :,\
	EXP : ENUM_TYPE :\
    ) STATEMENT DESTROY_etype_basic #
#pragma interface DESTROY_etype_basic


#endif
