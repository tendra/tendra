/*
    		 Crown Copyright (c) 1997
    
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
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.2)
*/

#ifndef PAR_OPS_H_INCLUDED
#define PAR_OPS_H_INCLUDED

/* Operations for union PARAMETER */

#pragma token PROC ( EXP : PARAMETER : ) EXP : unsigned : TAG_par #
#pragma interface TAG_par


/* Operations for component name of union PARAMETER */

#pragma token PROC ( EXP : PARAMETER : )\
    EXP : PTR ( string ) : par_name #
#pragma interface par_name

/* Operations for component type of union PARAMETER */

#pragma token PROC ( EXP : PARAMETER : )\
    EXP : PTR ( SORT ) : par_type #
#pragma interface par_type

/* Operations for component brk of union PARAMETER */

#pragma token PROC ( EXP : PARAMETER : )\
    EXP : PTR ( int ) : par_brk #
#pragma interface par_brk

/* Operations for component align of union PARAMETER */

#pragma token PROC ( EXP : PARAMETER : )\
    EXP : PTR ( int ) : par_align #
#pragma interface par_align

/* Operations for component intro of union PARAMETER */

#pragma token PROC ( EXP : PARAMETER : )\
    EXP : PTR ( int ) : par_intro #
#pragma interface par_intro

/* Operations for field basic of union PARAMETER */

#pragma token EXP const : unsigned : par_basic_tag #
#pragma token PROC ( EXP : PARAMETER : ) EXP : int : IS_par_basic #
#pragma interface par_basic_tag IS_par_basic

#pragma token PROC (\
	EXP : string :,\
	EXP : SORT :,\
	EXP : int :,\
	EXP : int :,\
	EXP : int :,\
	EXP lvalue : PARAMETER :\
    ) STATEMENT MAKE_par_basic #
#pragma interface MAKE_par_basic

#pragma token PROC (\
	EXP lvalue : string :,\
	EXP lvalue : SORT :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP : PARAMETER :\
    ) STATEMENT DECONS_par_basic #
#pragma interface DECONS_par_basic

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : SORT :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP : PARAMETER :\
    ) STATEMENT DESTROY_par_basic #
#pragma interface DESTROY_par_basic


#endif
