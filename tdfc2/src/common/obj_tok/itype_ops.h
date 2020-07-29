/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef ITYPE_OPS_H_INCLUDED
#define ITYPE_OPS_H_INCLUDED

/* Operations for union INT_TYPE */

#pragma token PROC(EXP : INT_TYPE :) EXP : unsigned : TAG_itype #
#pragma interface TAG_itype


/* Operations for component prom of union INT_TYPE */

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(TYPE) : itype_prom #
#pragma interface itype_prom

/* Operations for component cases of union INT_TYPE */

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(LIST(TYPE)) : itype_cases #
#pragma interface itype_cases

/* Operations for component unprom of union INT_TYPE */

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(BUILTIN_TYPE) : itype_unprom #
#pragma interface itype_unprom

/* Operations for component itok of union INT_TYPE */

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(ulong_type) : itype_itok #
#pragma interface itype_itok

/* Operations for component ntok of union INT_TYPE */

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(ulong_type) : itype_ntok #
#pragma interface itype_ntok

/* Operations for component diag of union INT_TYPE */

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(ulong_type) : itype_diag #
#pragma interface itype_diag

/* Operations for field basic of union INT_TYPE */

#pragma token EXP const : unsigned : itype_basic_tag #
#pragma token PROC(EXP : INT_TYPE :) EXP : int : IS_itype_basic #
#pragma interface itype_basic_tag IS_itype_basic

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(BASE_TYPE) : itype_basic_rep #
#pragma interface itype_basic_rep

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(BUILTIN_TYPE) : itype_basic_no #
#pragma interface itype_basic_no

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : LIST(TYPE) :,\
	EXP : BASE_TYPE :,\
	EXP : BUILTIN_TYPE :,\
	EXP lvalue : INT_TYPE :\
    ) STATEMENT MAKE_itype_basic #
#pragma interface MAKE_itype_basic

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : BASE_TYPE :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP : INT_TYPE :\
    ) STATEMENT DECONS_itype_basic #
#pragma interface DECONS_itype_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : BASE_TYPE :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP : INT_TYPE :\
    ) STATEMENT DESTROY_itype_basic #
#pragma interface DESTROY_itype_basic


/* Operations for field bitfield of union INT_TYPE */

#pragma token EXP const : unsigned : itype_bitfield_tag #
#pragma token PROC(EXP : INT_TYPE :) EXP : int : IS_itype_bitfield #
#pragma interface itype_bitfield_tag IS_itype_bitfield

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(TYPE) : itype_bitfield_sub #
#pragma interface itype_bitfield_sub

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(BASE_TYPE) : itype_bitfield_rep #
#pragma interface itype_bitfield_rep

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(NAT) : itype_bitfield_size #
#pragma interface itype_bitfield_size

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(DECL_SPEC) : itype_bitfield_info #
#pragma interface itype_bitfield_info

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : LIST(TYPE) :,\
	EXP : TYPE :,\
	EXP : BASE_TYPE :,\
	EXP : NAT :,\
	EXP : DECL_SPEC :,\
	EXP lvalue : INT_TYPE :\
    ) STATEMENT MAKE_itype_bitfield #
#pragma interface MAKE_itype_bitfield

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : BASE_TYPE :,\
	EXP lvalue : NAT :,\
	EXP lvalue : DECL_SPEC :,\
	EXP : INT_TYPE :\
    ) STATEMENT DECONS_itype_bitfield #
#pragma interface DECONS_itype_bitfield

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : BASE_TYPE :,\
	EXP lvalue : NAT :,\
	EXP lvalue : DECL_SPEC :,\
	EXP : INT_TYPE :\
    ) STATEMENT DESTROY_itype_bitfield #
#pragma interface DESTROY_itype_bitfield


/* Operations for field promote of union INT_TYPE */

#pragma token EXP const : unsigned : itype_promote_tag #
#pragma token PROC(EXP : INT_TYPE :) EXP : int : IS_itype_promote #
#pragma interface itype_promote_tag IS_itype_promote

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(INT_TYPE) : itype_promote_arg #
#pragma interface itype_promote_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : LIST(TYPE) :,\
	EXP : INT_TYPE :,\
	EXP lvalue : INT_TYPE :\
    ) STATEMENT MAKE_itype_promote #
#pragma interface MAKE_itype_promote

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : INT_TYPE :,\
	EXP : INT_TYPE :\
    ) STATEMENT DECONS_itype_promote #
#pragma interface DECONS_itype_promote

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : INT_TYPE :,\
	EXP : INT_TYPE :\
    ) STATEMENT DESTROY_itype_promote #
#pragma interface DESTROY_itype_promote


/* Operations for field arith of union INT_TYPE */

#pragma token EXP const : unsigned : itype_arith_tag #
#pragma token PROC(EXP : INT_TYPE :) EXP : int : IS_itype_arith #
#pragma interface itype_arith_tag IS_itype_arith

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(INT_TYPE) : itype_arith_arg1 #
#pragma interface itype_arith_arg1

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(INT_TYPE) : itype_arith_arg2 #
#pragma interface itype_arith_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : LIST(TYPE) :,\
	EXP : INT_TYPE :,\
	EXP : INT_TYPE :,\
	EXP lvalue : INT_TYPE :\
    ) STATEMENT MAKE_itype_arith #
#pragma interface MAKE_itype_arith

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : INT_TYPE :,\
	EXP lvalue : INT_TYPE :,\
	EXP : INT_TYPE :\
    ) STATEMENT DECONS_itype_arith #
#pragma interface DECONS_itype_arith

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : INT_TYPE :,\
	EXP lvalue : INT_TYPE :,\
	EXP : INT_TYPE :\
    ) STATEMENT DESTROY_itype_arith #
#pragma interface DESTROY_itype_arith


/* Operations for field literal of union INT_TYPE */

#pragma token EXP const : unsigned : itype_literal_tag #
#pragma token PROC(EXP : INT_TYPE :) EXP : int : IS_itype_literal #
#pragma interface itype_literal_tag IS_itype_literal

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(NAT) : itype_literal_nat #
#pragma interface itype_literal_nat

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(int) : itype_literal_spec #
#pragma interface itype_literal_spec

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(int) : itype_literal_form #
#pragma interface itype_literal_form

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(int) : itype_literal_suff #
#pragma interface itype_literal_suff

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(IDENTIFIER) : itype_literal_tok #
#pragma interface itype_literal_tok

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : LIST(TYPE) :,\
	EXP : NAT :,\
	EXP : int :,\
	EXP : int :,\
	EXP : int :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : INT_TYPE :\
    ) STATEMENT MAKE_itype_literal #
#pragma interface MAKE_itype_literal

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : NAT :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : INT_TYPE :\
    ) STATEMENT DECONS_itype_literal #
#pragma interface DECONS_itype_literal

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : NAT :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : INT_TYPE :\
    ) STATEMENT DESTROY_itype_literal #
#pragma interface DESTROY_itype_literal


/* Operations for field token of union INT_TYPE */

#pragma token EXP const : unsigned : itype_token_tag #
#pragma token PROC(EXP : INT_TYPE :) EXP : int : IS_itype_token #
#pragma interface itype_token_tag IS_itype_token

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(IDENTIFIER) : itype_token_tok #
#pragma interface itype_token_tok

#pragma token PROC(EXP : INT_TYPE :)\
    EXP : PTR(LIST(TOKEN)) : itype_token_args #
#pragma interface itype_token_args

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : LIST(TYPE) :,\
	EXP : IDENTIFIER :,\
	EXP : LIST(TOKEN) :,\
	EXP lvalue : INT_TYPE :\
    ) STATEMENT MAKE_itype_token #
#pragma interface MAKE_itype_token

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(TOKEN) :,\
	EXP : INT_TYPE :\
    ) STATEMENT DECONS_itype_token #
#pragma interface DECONS_itype_token

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(TOKEN) :,\
	EXP : INT_TYPE :\
    ) STATEMENT DESTROY_itype_token #
#pragma interface DESTROY_itype_token


#endif
