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

#ifndef LINK_OPS_H_INCLUDED
#define LINK_OPS_H_INCLUDED

/* Operations for union LINKAGE */

#pragma token PROC ( EXP : LINKAGE : ) EXP : unsigned : TAG_link #
#pragma interface TAG_link


/* Operations for component name of union LINKAGE */

#pragma token PROC ( EXP : LINKAGE : )\
    EXP : PTR ( string ) : link_name #
#pragma interface link_name

/* Operations for component type of union LINKAGE */

#pragma token PROC ( EXP : LINKAGE : )\
    EXP : PTR ( SORT ) : link_type #
#pragma interface link_type

/* Operations for field basic of union LINKAGE */

#pragma token EXP const : unsigned : link_basic_tag #
#pragma token PROC ( EXP : LINKAGE : ) EXP : int : IS_link_basic #
#pragma interface link_basic_tag IS_link_basic

#pragma token PROC (\
	EXP : string :,\
	EXP : SORT :,\
	EXP lvalue : LINKAGE :\
    ) STATEMENT MAKE_link_basic #
#pragma interface MAKE_link_basic

#pragma token PROC (\
	EXP lvalue : string :,\
	EXP lvalue : SORT :,\
	EXP : LINKAGE :\
    ) STATEMENT DECONS_link_basic #
#pragma interface DECONS_link_basic

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : SORT :,\
	EXP : LINKAGE :\
    ) STATEMENT DESTROY_link_basic #
#pragma interface DESTROY_link_basic


#endif
