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

#ifndef CTYPE_OPS_H_INCLUDED
#define CTYPE_OPS_H_INCLUDED

/* Operations for union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : ) EXP : unsigned : TAG_ctype #
#pragma interface TAG_ctype


/* Operations for component name of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( IDENTIFIER ) : ctype_name #
#pragma interface ctype_name

/* Operations for component info of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( CLASS_INFO ) : ctype_info #
#pragma interface ctype_info

/* Operations for component usage of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( CLASS_USAGE ) : ctype_usage #
#pragma interface ctype_usage

/* Operations for component member of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( NAMESPACE ) : ctype_member #
#pragma interface ctype_member

/* Operations for component base of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( GRAPH ) : ctype_base #
#pragma interface ctype_base

/* Operations for component no_bases of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( unsigned ) : ctype_no_bases #
#pragma interface ctype_no_bases

/* Operations for component prev of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( TYPE ) : ctype_prev #
#pragma interface ctype_prev

/* Operations for component form of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( TYPE ) : ctype_form #
#pragma interface ctype_form

/* Operations for component constr of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( IDENTIFIER ) : ctype_constr #
#pragma interface ctype_constr

/* Operations for component destr of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( IDENTIFIER ) : ctype_destr #
#pragma interface ctype_destr

/* Operations for component virt of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( VIRTUAL ) : ctype_virt #
#pragma interface ctype_virt

/* Operations for component vbase of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( LIST ( GRAPH ) ) : ctype_vbase #
#pragma interface ctype_vbase

/* Operations for component conv of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( LIST ( IDENTIFIER ) ) : ctype_conv #
#pragma interface ctype_conv

/* Operations for component chums of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( LIST ( CLASS_TYPE ) ) : ctype_chums #
#pragma interface ctype_chums

/* Operations for component pals of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( LIST ( IDENTIFIER ) ) : ctype_pals #
#pragma interface ctype_pals

/* Operations for component nest of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( LIST ( IDENTIFIER ) ) : ctype_nest #
#pragma interface ctype_nest

/* Operations for component tok1 of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( ulong_type ) : ctype_tok1 #
#pragma interface ctype_tok1

/* Operations for component tok2 of union CLASS_TYPE */

#pragma token PROC ( EXP : CLASS_TYPE : )\
    EXP : PTR ( ulong_type ) : ctype_tok2 #
#pragma interface ctype_tok2

/* Operations for field basic of union CLASS_TYPE */

#pragma token EXP const : unsigned : ctype_basic_tag #
#pragma token PROC ( EXP : CLASS_TYPE : ) EXP : int : IS_ctype_basic #
#pragma interface ctype_basic_tag IS_ctype_basic

#pragma token PROC (\
	EXP : IDENTIFIER :,\
	EXP : CLASS_INFO :,\
	EXP : CLASS_USAGE :,\
	EXP : NAMESPACE :,\
	EXP : GRAPH :,\
	EXP : unsigned :,\
	EXP : TYPE :,\
	EXP lvalue : CLASS_TYPE :\
    ) STATEMENT MAKE_ctype_basic #
#pragma interface MAKE_ctype_basic

#pragma token PROC (\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : CLASS_INFO :,\
	EXP lvalue : CLASS_USAGE :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : LIST ( GRAPH ) :,\
	EXP lvalue : LIST ( IDENTIFIER ) :,\
	EXP lvalue : LIST ( CLASS_TYPE ) :,\
	EXP lvalue : LIST ( IDENTIFIER ) :,\
	EXP lvalue : LIST ( IDENTIFIER ) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : CLASS_TYPE :\
    ) STATEMENT DECONS_ctype_basic #
#pragma interface DECONS_ctype_basic

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : CLASS_INFO :,\
	EXP lvalue : CLASS_USAGE :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : LIST ( GRAPH ) :,\
	EXP lvalue : LIST ( IDENTIFIER ) :,\
	EXP lvalue : LIST ( CLASS_TYPE ) :,\
	EXP lvalue : LIST ( IDENTIFIER ) :,\
	EXP lvalue : LIST ( IDENTIFIER ) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : CLASS_TYPE :\
    ) STATEMENT DESTROY_ctype_basic #
#pragma interface DESTROY_ctype_basic


#endif
