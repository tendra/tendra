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

#ifndef MAP_OPS_H_INCLUDED
#define MAP_OPS_H_INCLUDED

/* Operations for union MAP */

#pragma token PROC ( EXP : MAP : ) EXP : unsigned : TAG_map #
#pragma interface TAG_map


/* Operations for component key of union MAP */

#pragma token PROC ( EXP : MAP : )\
    EXP : PTR ( KEY ) : map_key #
#pragma interface map_key

/* Operations for component msg of union MAP */

#pragma token PROC ( EXP : MAP : )\
    EXP : PTR ( LIST ( MESSAGE ) ) : map_msg #
#pragma interface map_msg

/* Operations for component alt_msg of union MAP */

#pragma token PROC ( EXP : MAP : )\
    EXP : PTR ( LIST ( MESSAGE ) ) : map_alt_msg #
#pragma interface map_alt_msg

/* Operations for field basic of union MAP */

#pragma token EXP const : unsigned : map_basic_tag #
#pragma token PROC ( EXP : MAP : ) EXP : int : IS_map_basic #
#pragma interface map_basic_tag IS_map_basic

#pragma token PROC (\
	EXP : KEY :,\
	EXP : LIST ( MESSAGE ) :,\
	EXP : LIST ( MESSAGE ) :,\
	EXP lvalue : MAP :\
    ) STATEMENT MAKE_map_basic #
#pragma interface MAKE_map_basic

#pragma token PROC (\
	EXP lvalue : KEY :,\
	EXP lvalue : LIST ( MESSAGE ) :,\
	EXP lvalue : LIST ( MESSAGE ) :,\
	EXP : MAP :\
    ) STATEMENT DECONS_map_basic #
#pragma interface DECONS_map_basic

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : KEY :,\
	EXP lvalue : LIST ( MESSAGE ) :,\
	EXP lvalue : LIST ( MESSAGE ) :,\
	EXP : MAP :\
    ) STATEMENT DESTROY_map_basic #
#pragma interface DESTROY_map_basic


#endif
