/*
    		 Crown Copyright (c) 1997, 1998
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.2)
*/

#ifndef FTYPE_OPS_H_INCLUDED
#define FTYPE_OPS_H_INCLUDED

/* Operations for union FLOAT_TYPE */

#pragma token PROC ( EXP : FLOAT_TYPE : ) EXP : unsigned : TAG_ftype #
#pragma interface TAG_ftype


/* Operations for component arg_prom of union FLOAT_TYPE */

#pragma token PROC ( EXP : FLOAT_TYPE : )\
    EXP : PTR ( TYPE ) : ftype_arg_prom #
#pragma interface ftype_arg_prom

/* Operations for component ftok of union FLOAT_TYPE */

#pragma token PROC ( EXP : FLOAT_TYPE : )\
    EXP : PTR ( ulong_type ) : ftype_ftok #
#pragma interface ftype_ftok

/* Operations for component ntok of union FLOAT_TYPE */

#pragma token PROC ( EXP : FLOAT_TYPE : )\
    EXP : PTR ( ulong_type ) : ftype_ntok #
#pragma interface ftype_ntok

/* Operations for component diag of union FLOAT_TYPE */

#pragma token PROC ( EXP : FLOAT_TYPE : )\
    EXP : PTR ( ulong_type ) : ftype_diag #
#pragma interface ftype_diag

/* Operations for component small of union FLOAT_TYPE */

#pragma token PROC ( EXP : FLOAT_TYPE : )\
    EXP : PTR ( LIST ( FLOAT ) ) : ftype_small #
#pragma interface ftype_small

/* Operations for field basic of union FLOAT_TYPE */

#pragma token EXP const : unsigned : ftype_basic_tag #
#pragma token PROC ( EXP : FLOAT_TYPE : ) EXP : int : IS_ftype_basic #
#pragma interface ftype_basic_tag IS_ftype_basic

#pragma token PROC ( EXP : FLOAT_TYPE : )\
    EXP : PTR ( BASE_TYPE ) : ftype_basic_rep #
#pragma interface ftype_basic_rep

#pragma token PROC ( EXP : FLOAT_TYPE : )\
    EXP : PTR ( BUILTIN_TYPE ) : ftype_basic_no #
#pragma interface ftype_basic_no

#pragma token PROC (\
	EXP : TYPE :,\
	EXP : BASE_TYPE :,\
	EXP : BUILTIN_TYPE :,\
	EXP lvalue : FLOAT_TYPE :\
    ) STATEMENT MAKE_ftype_basic #
#pragma interface MAKE_ftype_basic

#pragma token PROC (\
	EXP lvalue : TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : LIST ( FLOAT ) :,\
	EXP lvalue : BASE_TYPE :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP : FLOAT_TYPE :\
    ) STATEMENT DECONS_ftype_basic #
#pragma interface DECONS_ftype_basic

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : LIST ( FLOAT ) :,\
	EXP lvalue : BASE_TYPE :,\
	EXP lvalue : BUILTIN_TYPE :,\
	EXP : FLOAT_TYPE :\
    ) STATEMENT DESTROY_ftype_basic #
#pragma interface DESTROY_ftype_basic


/* Operations for field arg_promote of union FLOAT_TYPE */

#pragma token EXP const : unsigned : ftype_arg_promote_tag #
#pragma token PROC ( EXP : FLOAT_TYPE : ) EXP : int : IS_ftype_arg_promote #
#pragma interface ftype_arg_promote_tag IS_ftype_arg_promote

#pragma token PROC ( EXP : FLOAT_TYPE : )\
    EXP : PTR ( FLOAT_TYPE ) : ftype_arg_promote_arg #
#pragma interface ftype_arg_promote_arg

#pragma token PROC (\
	EXP : TYPE :,\
	EXP : FLOAT_TYPE :,\
	EXP lvalue : FLOAT_TYPE :\
    ) STATEMENT MAKE_ftype_arg_promote #
#pragma interface MAKE_ftype_arg_promote

#pragma token PROC (\
	EXP lvalue : TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : LIST ( FLOAT ) :,\
	EXP lvalue : FLOAT_TYPE :,\
	EXP : FLOAT_TYPE :\
    ) STATEMENT DECONS_ftype_arg_promote #
#pragma interface DECONS_ftype_arg_promote

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : LIST ( FLOAT ) :,\
	EXP lvalue : FLOAT_TYPE :,\
	EXP : FLOAT_TYPE :\
    ) STATEMENT DESTROY_ftype_arg_promote #
#pragma interface DESTROY_ftype_arg_promote


/* Operations for field arith of union FLOAT_TYPE */

#pragma token EXP const : unsigned : ftype_arith_tag #
#pragma token PROC ( EXP : FLOAT_TYPE : ) EXP : int : IS_ftype_arith #
#pragma interface ftype_arith_tag IS_ftype_arith

#pragma token PROC ( EXP : FLOAT_TYPE : )\
    EXP : PTR ( FLOAT_TYPE ) : ftype_arith_arg1 #
#pragma interface ftype_arith_arg1

#pragma token PROC ( EXP : FLOAT_TYPE : )\
    EXP : PTR ( FLOAT_TYPE ) : ftype_arith_arg2 #
#pragma interface ftype_arith_arg2

#pragma token PROC (\
	EXP : TYPE :,\
	EXP : FLOAT_TYPE :,\
	EXP : FLOAT_TYPE :,\
	EXP lvalue : FLOAT_TYPE :\
    ) STATEMENT MAKE_ftype_arith #
#pragma interface MAKE_ftype_arith

#pragma token PROC (\
	EXP lvalue : TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : LIST ( FLOAT ) :,\
	EXP lvalue : FLOAT_TYPE :,\
	EXP lvalue : FLOAT_TYPE :,\
	EXP : FLOAT_TYPE :\
    ) STATEMENT DECONS_ftype_arith #
#pragma interface DECONS_ftype_arith

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : LIST ( FLOAT ) :,\
	EXP lvalue : FLOAT_TYPE :,\
	EXP lvalue : FLOAT_TYPE :,\
	EXP : FLOAT_TYPE :\
    ) STATEMENT DESTROY_ftype_arith #
#pragma interface DESTROY_ftype_arith


/* Operations for field token of union FLOAT_TYPE */

#pragma token EXP const : unsigned : ftype_token_tag #
#pragma token PROC ( EXP : FLOAT_TYPE : ) EXP : int : IS_ftype_token #
#pragma interface ftype_token_tag IS_ftype_token

#pragma token PROC ( EXP : FLOAT_TYPE : )\
    EXP : PTR ( IDENTIFIER ) : ftype_token_tok #
#pragma interface ftype_token_tok

#pragma token PROC ( EXP : FLOAT_TYPE : )\
    EXP : PTR ( LIST ( TOKEN ) ) : ftype_token_args #
#pragma interface ftype_token_args

#pragma token PROC (\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP : LIST ( TOKEN ) :,\
	EXP lvalue : FLOAT_TYPE :\
    ) STATEMENT MAKE_ftype_token #
#pragma interface MAKE_ftype_token

#pragma token PROC (\
	EXP lvalue : TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : LIST ( FLOAT ) :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST ( TOKEN ) :,\
	EXP : FLOAT_TYPE :\
    ) STATEMENT DECONS_ftype_token #
#pragma interface DECONS_ftype_token

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : LIST ( FLOAT ) :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST ( TOKEN ) :,\
	EXP : FLOAT_TYPE :\
    ) STATEMENT DESTROY_ftype_token #
#pragma interface DESTROY_ftype_token


#endif
