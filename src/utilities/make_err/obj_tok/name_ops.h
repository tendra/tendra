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

#ifndef NAME_OPS_H_INCLUDED
#define NAME_OPS_H_INCLUDED

/* Operations for union NAME */

#pragma token PROC ( EXP : NAME : ) EXP : unsigned : TAG_name #
#pragma interface TAG_name


/* Operations for component id of union NAME */

#pragma token PROC ( EXP : NAME : )\
    EXP : PTR ( string ) : name_id #
#pragma interface name_id

/* Operations for component number of union NAME */

#pragma token PROC ( EXP : NAME : )\
    EXP : PTR ( int ) : name_number #
#pragma interface name_number

/* Operations for field basic of union NAME */

#pragma token EXP const : unsigned : name_basic_tag #
#pragma token PROC ( EXP : NAME : ) EXP : int : IS_name_basic #
#pragma interface name_basic_tag IS_name_basic

#pragma token PROC (\
	EXP : string :,\
	EXP : int :,\
	EXP lvalue : NAME :\
    ) STATEMENT MAKE_name_basic #
#pragma interface MAKE_name_basic

#pragma token PROC (\
	EXP lvalue : string :,\
	EXP lvalue : int :,\
	EXP : NAME :\
    ) STATEMENT DECONS_name_basic #
#pragma interface DECONS_name_basic

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : int :,\
	EXP : NAME :\
    ) STATEMENT DESTROY_name_basic #
#pragma interface DESTROY_name_basic


#endif
