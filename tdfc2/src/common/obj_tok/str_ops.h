/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef STR_OPS_H_INCLUDED
#define STR_OPS_H_INCLUDED

/* Operations for union STRING */

#pragma token PROC(EXP : STRING :) EXP : unsigned : TAG_str #
#pragma interface TAG_str


/* Operations for component next of union STRING */

#pragma token PROC(EXP : STRING :)\
    EXP : PTR(STRING) : str_next #
#pragma interface str_next

/* Operations for field simple of union STRING */

#pragma token EXP const : unsigned : str_simple_tag #
#pragma token PROC(EXP : STRING :) EXP : int : IS_str_simple #
#pragma interface str_simple_tag IS_str_simple

#pragma token PROC(EXP : STRING :)\
    EXP : PTR(ulong_type) : str_simple_len #
#pragma interface str_simple_len

#pragma token PROC(EXP : STRING :)\
    EXP : PTR(string) : str_simple_text #
#pragma interface str_simple_text

#pragma token PROC(EXP : STRING :)\
    EXP : PTR(unsigned) : str_simple_kind #
#pragma interface str_simple_kind

#pragma token PROC(EXP : STRING :)\
    EXP : PTR(ulong_type) : str_simple_tok #
#pragma interface str_simple_tok

#pragma token PROC(\
	EXP : ulong_type :,\
	EXP : string :,\
	EXP : unsigned :,\
	EXP lvalue : STRING :\
    ) STATEMENT MAKE_str_simple #
#pragma interface MAKE_str_simple

#pragma token PROC(\
	EXP lvalue : STRING :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : ulong_type :,\
	EXP : STRING :\
    ) STATEMENT DECONS_str_simple #
#pragma interface DECONS_str_simple

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : STRING :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : ulong_type :,\
	EXP : STRING :\
    ) STATEMENT DESTROY_str_simple #
#pragma interface DESTROY_str_simple


#endif
