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

#ifndef ENTRY_OPS_H_INCLUDED
#define ENTRY_OPS_H_INCLUDED

/* Operations for union ENTRY */

#pragma token PROC ( EXP : ENTRY : ) EXP : unsigned : TAG_entry #
#pragma interface TAG_entry


/* Operations for component name of union ENTRY */

#pragma token PROC ( EXP : ENTRY : )\
    EXP : PTR ( string ) : entry_name #
#pragma interface entry_name

/* Operations for component alt_name of union ENTRY */

#pragma token PROC ( EXP : ENTRY : )\
    EXP : PTR ( string ) : entry_alt_name #
#pragma interface entry_alt_name

/* Operations for component signature of union ENTRY */

#pragma token PROC ( EXP : ENTRY : )\
    EXP : PTR ( LIST ( PARAM ) ) : entry_signature #
#pragma interface entry_signature

/* Operations for component use of union ENTRY */

#pragma token PROC ( EXP : ENTRY : )\
    EXP : PTR ( USAGE ) : entry_use #
#pragma interface entry_use

/* Operations for component alt_use of union ENTRY */

#pragma token PROC ( EXP : ENTRY : )\
    EXP : PTR ( USAGE ) : entry_alt_use #
#pragma interface entry_alt_use

/* Operations for component props of union ENTRY */

#pragma token PROC ( EXP : ENTRY : )\
    EXP : PTR ( LIST ( PROPERTY ) ) : entry_props #
#pragma interface entry_props

/* Operations for component maps of union ENTRY */

#pragma token PROC ( EXP : ENTRY : )\
    EXP : PTR ( LIST ( MAP ) ) : entry_maps #
#pragma interface entry_maps

/* Operations for field basic of union ENTRY */

#pragma token EXP const : unsigned : entry_basic_tag #
#pragma token PROC ( EXP : ENTRY : ) EXP : int : IS_entry_basic #
#pragma interface entry_basic_tag IS_entry_basic

#pragma token PROC (\
	EXP : string :,\
	EXP : string :,\
	EXP : LIST ( PARAM ) :,\
	EXP : USAGE :,\
	EXP : USAGE :,\
	EXP : LIST ( PROPERTY ) :,\
	EXP : LIST ( MAP ) :,\
	EXP lvalue : ENTRY :\
    ) STATEMENT MAKE_entry_basic #
#pragma interface MAKE_entry_basic

#pragma token PROC (\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : LIST ( PARAM ) :,\
	EXP lvalue : USAGE :,\
	EXP lvalue : USAGE :,\
	EXP lvalue : LIST ( PROPERTY ) :,\
	EXP lvalue : LIST ( MAP ) :,\
	EXP : ENTRY :\
    ) STATEMENT DECONS_entry_basic #
#pragma interface DECONS_entry_basic

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : LIST ( PARAM ) :,\
	EXP lvalue : USAGE :,\
	EXP lvalue : USAGE :,\
	EXP lvalue : LIST ( PROPERTY ) :,\
	EXP lvalue : LIST ( MAP ) :,\
	EXP : ENTRY :\
    ) STATEMENT DESTROY_entry_basic #
#pragma interface DESTROY_entry_basic


#endif
