/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef FLT_OPS_H_INCLUDED
#define FLT_OPS_H_INCLUDED

/* Operations for union FLOAT */

#pragma token PROC(EXP : FLOAT :) EXP : unsigned : TAG_flt #
#pragma interface TAG_flt


/* Operations for component tok of union FLOAT */

#pragma token PROC(EXP : FLOAT :)\
    EXP : PTR(ulong_type) : flt_tok #
#pragma interface flt_tok

/* Operations for field simple of union FLOAT */

#pragma token EXP const : unsigned : flt_simple_tag #
#pragma token PROC(EXP : FLOAT :) EXP : int : IS_flt_simple #
#pragma interface flt_simple_tag IS_flt_simple

#pragma token PROC(EXP : FLOAT :)\
    EXP : PTR(string) : flt_simple_int_part #
#pragma interface flt_simple_int_part

#pragma token PROC(EXP : FLOAT :)\
    EXP : PTR(string) : flt_simple_frac_part #
#pragma interface flt_simple_frac_part

#pragma token PROC(EXP : FLOAT :)\
    EXP : PTR(NAT) : flt_simple_exponent #
#pragma interface flt_simple_exponent

#pragma token PROC(\
	EXP : string :,\
	EXP : string :,\
	EXP : NAT :,\
	EXP lvalue : FLOAT :\
    ) STATEMENT MAKE_flt_simple #
#pragma interface MAKE_flt_simple

#pragma token PROC(\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : NAT :,\
	EXP : FLOAT :\
    ) STATEMENT DECONS_flt_simple #
#pragma interface DECONS_flt_simple

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : NAT :,\
	EXP : FLOAT :\
    ) STATEMENT DESTROY_flt_simple #
#pragma interface DESTROY_flt_simple


#endif
