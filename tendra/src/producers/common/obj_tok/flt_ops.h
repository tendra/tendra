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

#ifndef FLT_OPS_H_INCLUDED
#define FLT_OPS_H_INCLUDED

/* Operations for union FLOAT */

#pragma token PROC ( EXP : FLOAT : ) EXP : unsigned : TAG_flt #
#pragma interface TAG_flt


/* Operations for component tok of union FLOAT */

#pragma token PROC ( EXP : FLOAT : )\
    EXP : PTR ( ulong_type ) : flt_tok #
#pragma interface flt_tok

/* Operations for field simple of union FLOAT */

#pragma token EXP const : unsigned : flt_simple_tag #
#pragma token PROC ( EXP : FLOAT : ) EXP : int : IS_flt_simple #
#pragma interface flt_simple_tag IS_flt_simple

#pragma token PROC ( EXP : FLOAT : )\
    EXP : PTR ( string ) : flt_simple_int_part #
#pragma interface flt_simple_int_part

#pragma token PROC ( EXP : FLOAT : )\
    EXP : PTR ( string ) : flt_simple_frac_part #
#pragma interface flt_simple_frac_part

#pragma token PROC ( EXP : FLOAT : )\
    EXP : PTR ( NAT ) : flt_simple_exponent #
#pragma interface flt_simple_exponent

#pragma token PROC (\
	EXP : string :,\
	EXP : string :,\
	EXP : NAT :,\
	EXP lvalue : FLOAT :\
    ) STATEMENT MAKE_flt_simple #
#pragma interface MAKE_flt_simple

#pragma token PROC (\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : NAT :,\
	EXP : FLOAT :\
    ) STATEMENT DECONS_flt_simple #
#pragma interface DECONS_flt_simple

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : NAT :,\
	EXP : FLOAT :\
    ) STATEMENT DESTROY_flt_simple #
#pragma interface DESTROY_flt_simple


#endif
