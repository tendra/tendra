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

#ifndef STR_OPS_H_INCLUDED
#define STR_OPS_H_INCLUDED

/* Operations for union STRING */

#pragma token PROC ( EXP : STRING : ) EXP : unsigned : TAG_str #
#pragma interface TAG_str


/* Operations for component next of union STRING */

#pragma token PROC ( EXP : STRING : )\
    EXP : PTR ( STRING ) : str_next #
#pragma interface str_next

/* Operations for field simple of union STRING */

#pragma token EXP const : unsigned : str_simple_tag #
#pragma token PROC ( EXP : STRING : ) EXP : int : IS_str_simple #
#pragma interface str_simple_tag IS_str_simple

#pragma token PROC ( EXP : STRING : )\
    EXP : PTR ( ulong_type ) : str_simple_len #
#pragma interface str_simple_len

#pragma token PROC ( EXP : STRING : )\
    EXP : PTR ( string ) : str_simple_text #
#pragma interface str_simple_text

#pragma token PROC ( EXP : STRING : )\
    EXP : PTR ( unsigned ) : str_simple_kind #
#pragma interface str_simple_kind

#pragma token PROC ( EXP : STRING : )\
    EXP : PTR ( ulong_type ) : str_simple_tok #
#pragma interface str_simple_tok

#pragma token PROC (\
	EXP : ulong_type :,\
	EXP : string :,\
	EXP : unsigned :,\
	EXP lvalue : STRING :\
    ) STATEMENT MAKE_str_simple #
#pragma interface MAKE_str_simple

#pragma token PROC (\
	EXP lvalue : STRING :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : ulong_type :,\
	EXP : STRING :\
    ) STATEMENT DECONS_str_simple #
#pragma interface DECONS_str_simple

#pragma token PROC (\
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
