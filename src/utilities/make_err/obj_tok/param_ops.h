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
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.2)
*/

#ifndef PARAM_OPS_H_INCLUDED
#define PARAM_OPS_H_INCLUDED

/* Operations for union PARAM */

#pragma token PROC ( EXP : PARAM : ) EXP : unsigned : TAG_param #
#pragma interface TAG_param


/* Operations for component type of union PARAM */

#pragma token PROC ( EXP : PARAM : )\
    EXP : PTR ( TYPE ) : param_type #
#pragma interface param_type

/* Operations for component name of union PARAM */

#pragma token PROC ( EXP : PARAM : )\
    EXP : PTR ( string ) : param_name #
#pragma interface param_name

/* Operations for component number of union PARAM */

#pragma token PROC ( EXP : PARAM : )\
    EXP : PTR ( int ) : param_number #
#pragma interface param_number

/* Operations for field basic of union PARAM */

#pragma token EXP const : unsigned : param_basic_tag #
#pragma token PROC ( EXP : PARAM : ) EXP : int : IS_param_basic #
#pragma interface param_basic_tag IS_param_basic

#pragma token PROC (\
	EXP : TYPE :,\
	EXP : string :,\
	EXP : int :,\
	EXP lvalue : PARAM :\
    ) STATEMENT MAKE_param_basic #
#pragma interface MAKE_param_basic

#pragma token PROC (\
	EXP lvalue : TYPE :,\
	EXP lvalue : string :,\
	EXP lvalue : int :,\
	EXP : PARAM :\
    ) STATEMENT DECONS_param_basic #
#pragma interface DECONS_param_basic

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : string :,\
	EXP lvalue : int :,\
	EXP : PARAM :\
    ) STATEMENT DESTROY_param_basic #
#pragma interface DESTROY_param_basic


#endif
