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

#ifndef NAT_OPS_H_INCLUDED
#define NAT_OPS_H_INCLUDED

/* Operations for union NAT */

#pragma token PROC ( EXP : NAT : ) EXP : unsigned : TAG_nat #
#pragma interface TAG_nat


/* Operations for field small of union NAT */

#pragma token EXP const : unsigned : nat_small_tag #
#pragma token PROC ( EXP : NAT : ) EXP : int : IS_nat_small #
#pragma interface nat_small_tag IS_nat_small

#pragma token PROC ( EXP : NAT : )\
    EXP : PTR ( unsigned ) : nat_small_value #
#pragma interface nat_small_value

#pragma token PROC (\
	EXP : unsigned :,\
	EXP lvalue : NAT :\
    ) STATEMENT MAKE_nat_small #
#pragma interface MAKE_nat_small

#pragma token PROC (\
	EXP lvalue : unsigned :,\
	EXP : NAT :\
    ) STATEMENT DECONS_nat_small #
#pragma interface DECONS_nat_small

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : unsigned :,\
	EXP : NAT :\
    ) STATEMENT DESTROY_nat_small #
#pragma interface DESTROY_nat_small


/* Operations for field large of union NAT */

#pragma token EXP const : unsigned : nat_large_tag #
#pragma token PROC ( EXP : NAT : ) EXP : int : IS_nat_large #
#pragma interface nat_large_tag IS_nat_large

#pragma token PROC ( EXP : NAT : )\
    EXP : PTR ( LIST ( unsigned ) ) : nat_large_values #
#pragma interface nat_large_values

#pragma token PROC (\
	EXP : LIST ( unsigned ) :,\
	EXP lvalue : NAT :\
    ) STATEMENT MAKE_nat_large #
#pragma interface MAKE_nat_large

#pragma token PROC (\
	EXP lvalue : LIST ( unsigned ) :,\
	EXP : NAT :\
    ) STATEMENT DECONS_nat_large #
#pragma interface DECONS_nat_large

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : LIST ( unsigned ) :,\
	EXP : NAT :\
    ) STATEMENT DESTROY_nat_large #
#pragma interface DESTROY_nat_large


/* Operations for field calc of union NAT */

#pragma token EXP const : unsigned : nat_calc_tag #
#pragma token PROC ( EXP : NAT : ) EXP : int : IS_nat_calc #
#pragma interface nat_calc_tag IS_nat_calc

#pragma token PROC ( EXP : NAT : )\
    EXP : PTR ( EXP ) : nat_calc_value #
#pragma interface nat_calc_value

#pragma token PROC ( EXP : NAT : )\
    EXP : PTR ( ulong_type ) : nat_calc_tok #
#pragma interface nat_calc_tok

#pragma token PROC (\
	EXP : EXP :,\
	EXP lvalue : NAT :\
    ) STATEMENT MAKE_nat_calc #
#pragma interface MAKE_nat_calc

#pragma token PROC (\
	EXP lvalue : EXP :,\
	EXP lvalue : ulong_type :,\
	EXP : NAT :\
    ) STATEMENT DECONS_nat_calc #
#pragma interface DECONS_nat_calc

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : EXP :,\
	EXP lvalue : ulong_type :,\
	EXP : NAT :\
    ) STATEMENT DESTROY_nat_calc #
#pragma interface DESTROY_nat_calc


/* Operations for field neg of union NAT */

#pragma token EXP const : unsigned : nat_neg_tag #
#pragma token PROC ( EXP : NAT : ) EXP : int : IS_nat_neg #
#pragma interface nat_neg_tag IS_nat_neg

#pragma token PROC ( EXP : NAT : )\
    EXP : PTR ( NAT ) : nat_neg_arg #
#pragma interface nat_neg_arg

#pragma token PROC (\
	EXP : NAT :,\
	EXP lvalue : NAT :\
    ) STATEMENT MAKE_nat_neg #
#pragma interface MAKE_nat_neg

#pragma token PROC (\
	EXP lvalue : NAT :,\
	EXP : NAT :\
    ) STATEMENT DECONS_nat_neg #
#pragma interface DECONS_nat_neg

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : NAT :,\
	EXP : NAT :\
    ) STATEMENT DESTROY_nat_neg #
#pragma interface DESTROY_nat_neg


/* Operations for field token of union NAT */

#pragma token EXP const : unsigned : nat_token_tag #
#pragma token PROC ( EXP : NAT : ) EXP : int : IS_nat_token #
#pragma interface nat_token_tag IS_nat_token

#pragma token PROC ( EXP : NAT : )\
    EXP : PTR ( IDENTIFIER ) : nat_token_tok #
#pragma interface nat_token_tok

#pragma token PROC ( EXP : NAT : )\
    EXP : PTR ( LIST ( TOKEN ) ) : nat_token_args #
#pragma interface nat_token_args

#pragma token PROC (\
	EXP : IDENTIFIER :,\
	EXP : LIST ( TOKEN ) :,\
	EXP lvalue : NAT :\
    ) STATEMENT MAKE_nat_token #
#pragma interface MAKE_nat_token

#pragma token PROC (\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST ( TOKEN ) :,\
	EXP : NAT :\
    ) STATEMENT DECONS_nat_token #
#pragma interface DECONS_nat_token

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST ( TOKEN ) :,\
	EXP : NAT :\
    ) STATEMENT DESTROY_nat_token #
#pragma interface DESTROY_nat_token


#endif
