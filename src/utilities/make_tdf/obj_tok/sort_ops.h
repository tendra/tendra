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

#ifndef SORT_OPS_H_INCLUDED
#define SORT_OPS_H_INCLUDED

/* Operations for union SORT */

#pragma token PROC ( EXP : SORT : ) EXP : unsigned : TAG_sort #
#pragma interface TAG_sort


/* Operations for component name of union SORT */

#pragma token PROC ( EXP : SORT : )\
    EXP : PTR ( string ) : sort_name #
#pragma interface sort_name

/* Operations for component caps of union SORT */

#pragma token PROC ( EXP : SORT : )\
    EXP : PTR ( string ) : sort_caps #
#pragma interface sort_caps

/* Operations for component link of union SORT */

#pragma token PROC ( EXP : SORT : )\
    EXP : PTR ( string ) : sort_link #
#pragma interface sort_link

/* Operations for component unit of union SORT */

#pragma token PROC ( EXP : SORT : )\
    EXP : PTR ( string ) : sort_unit #
#pragma interface sort_unit

/* Operations for component code of union SORT */

#pragma token PROC ( EXP : SORT : )\
    EXP : PTR ( int ) : sort_code #
#pragma interface sort_code

/* Operations for component mark of union SORT */

#pragma token PROC ( EXP : SORT : )\
    EXP : PTR ( int ) : sort_mark #
#pragma interface sort_mark

/* Operations for component special of union SORT */

#pragma token PROC ( EXP : SORT : )\
    EXP : PTR ( int ) : sort_special #
#pragma interface sort_special

/* Operations for component edge of union SORT */

#pragma token PROC ( EXP : SORT : )\
    EXP : PTR ( int ) : sort_edge #
#pragma interface sort_edge

/* Operations for component info of union SORT */

#pragma token PROC ( EXP : SORT : )\
    EXP : PTR ( SORT_INFO ) : sort_info #
#pragma interface sort_info

/* Operations for field basic of union SORT */

#pragma token EXP const : unsigned : sort_basic_tag #
#pragma token PROC ( EXP : SORT : ) EXP : int : IS_sort_basic #
#pragma interface sort_basic_tag IS_sort_basic

#pragma token PROC (\
	EXP : string :,\
	EXP : string :,\
	EXP : string :,\
	EXP : string :,\
	EXP : int :,\
	EXP : int :,\
	EXP : int :,\
	EXP : int :,\
	EXP : SORT_INFO :,\
	EXP lvalue : SORT :\
    ) STATEMENT MAKE_sort_basic #
#pragma interface MAKE_sort_basic

#pragma token PROC (\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : SORT_INFO :,\
	EXP : SORT :\
    ) STATEMENT DECONS_sort_basic #
#pragma interface DECONS_sort_basic

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP lvalue : SORT_INFO :,\
	EXP : SORT :\
    ) STATEMENT DESTROY_sort_basic #
#pragma interface DESTROY_sort_basic


#endif
