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

#ifndef ETYPE_OPS_H_INCLUDED
#define ETYPE_OPS_H_INCLUDED

/* Operations for union ENUM_TYPE */

#pragma token PROC ( EXP : ENUM_TYPE : ) EXP : unsigned : TAG_etype #
#pragma interface TAG_etype


/* Operations for component name of union ENUM_TYPE */

#pragma token PROC ( EXP : ENUM_TYPE : )\
    EXP : PTR ( IDENTIFIER ) : etype_name #
#pragma interface etype_name

/* Operations for component info of union ENUM_TYPE */

#pragma token PROC ( EXP : ENUM_TYPE : )\
    EXP : PTR ( CLASS_INFO ) : etype_info #
#pragma interface etype_info

/* Operations for component rep of union ENUM_TYPE */

#pragma token PROC ( EXP : ENUM_TYPE : )\
    EXP : PTR ( TYPE ) : etype_rep #
#pragma interface etype_rep

/* Operations for component form of union ENUM_TYPE */

#pragma token PROC ( EXP : ENUM_TYPE : )\
    EXP : PTR ( TYPE ) : etype_form #
#pragma interface etype_form

/* Operations for component values of union ENUM_TYPE */

#pragma token PROC ( EXP : ENUM_TYPE : )\
    EXP : PTR ( LIST ( IDENTIFIER ) ) : etype_values #
#pragma interface etype_values

/* Operations for component value of union ENUM_TYPE */

#pragma token PROC ( EXP : ENUM_TYPE : )\
    EXP : PTR ( EXP ) : etype_value #
#pragma interface etype_value

/* Operations for component plus of union ENUM_TYPE */

#pragma token PROC ( EXP : ENUM_TYPE : )\
    EXP : PTR ( ulong_type ) : etype_plus #
#pragma interface etype_plus

/* Operations for field basic of union ENUM_TYPE */

#pragma token EXP const : unsigned : etype_basic_tag #
#pragma token PROC ( EXP : ENUM_TYPE : ) EXP : int : IS_etype_basic #
#pragma interface etype_basic_tag IS_etype_basic

#pragma token PROC (\
	EXP : IDENTIFIER :,\
	EXP : CLASS_INFO :,\
	EXP : TYPE :,\
	EXP lvalue : ENUM_TYPE :\
    ) STATEMENT MAKE_etype_basic #
#pragma interface MAKE_etype_basic

#pragma token PROC (\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : CLASS_INFO :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST ( IDENTIFIER ) :,\
	EXP lvalue : EXP :,\
	EXP lvalue : ulong_type :,\
	EXP : ENUM_TYPE :\
    ) STATEMENT DECONS_etype_basic #
#pragma interface DECONS_etype_basic

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : CLASS_INFO :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST ( IDENTIFIER ) :,\
	EXP lvalue : EXP :,\
	EXP lvalue : ulong_type :,\
	EXP : ENUM_TYPE :\
    ) STATEMENT DESTROY_etype_basic #
#pragma interface DESTROY_etype_basic


#endif
