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

#ifndef CONS_OPS_H_INCLUDED
#define CONS_OPS_H_INCLUDED

/* Operations for union CONSTRUCT */

#pragma token PROC ( EXP : CONSTRUCT : ) EXP : unsigned : TAG_cons #
#pragma interface TAG_cons


/* Operations for component name of union CONSTRUCT */

#pragma token PROC ( EXP : CONSTRUCT : )\
    EXP : PTR ( string ) : cons_name #
#pragma interface cons_name

/* Operations for component encode of union CONSTRUCT */

#pragma token PROC ( EXP : CONSTRUCT : )\
    EXP : PTR ( unsigned ) : cons_encode #
#pragma interface cons_encode

/* Operations for component res of union CONSTRUCT */

#pragma token PROC ( EXP : CONSTRUCT : )\
    EXP : PTR ( SORT ) : cons_res #
#pragma interface cons_res

/* Operations for component pars of union CONSTRUCT */

#pragma token PROC ( EXP : CONSTRUCT : )\
    EXP : PTR ( LIST ( PARAMETER ) ) : cons_pars #
#pragma interface cons_pars

/* Operations for component kind of union CONSTRUCT */

#pragma token PROC ( EXP : CONSTRUCT : )\
    EXP : PTR ( unsigned ) : cons_kind #
#pragma interface cons_kind

/* Operations for field basic of union CONSTRUCT */

#pragma token EXP const : unsigned : cons_basic_tag #
#pragma token PROC ( EXP : CONSTRUCT : ) EXP : int : IS_cons_basic #
#pragma interface cons_basic_tag IS_cons_basic

#pragma token PROC (\
	EXP : string :,\
	EXP : unsigned :,\
	EXP : SORT :,\
	EXP : LIST ( PARAMETER ) :,\
	EXP : unsigned :,\
	EXP lvalue : CONSTRUCT :\
    ) STATEMENT MAKE_cons_basic #
#pragma interface MAKE_cons_basic

#pragma token PROC (\
	EXP lvalue : string :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : SORT :,\
	EXP lvalue : LIST ( PARAMETER ) :,\
	EXP lvalue : unsigned :,\
	EXP : CONSTRUCT :\
    ) STATEMENT DECONS_cons_basic #
#pragma interface DECONS_cons_basic

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : SORT :,\
	EXP lvalue : LIST ( PARAMETER ) :,\
	EXP lvalue : unsigned :,\
	EXP : CONSTRUCT :\
    ) STATEMENT DESTROY_cons_basic #
#pragma interface DESTROY_cons_basic


#endif
