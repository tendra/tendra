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

#ifndef MEMBER_OPS_H_INCLUDED
#define MEMBER_OPS_H_INCLUDED

/* Operations for union MEMBER */

#pragma token PROC ( EXP : MEMBER : ) EXP : unsigned : TAG_member #
#pragma interface TAG_member


/* Operations for component id of union MEMBER */

#pragma token PROC ( EXP : MEMBER : )\
    EXP : PTR ( IDENTIFIER ) : member_id #
#pragma interface member_id

/* Operations for component alt of union MEMBER */

#pragma token PROC ( EXP : MEMBER : )\
    EXP : PTR ( IDENTIFIER ) : member_alt #
#pragma interface member_alt

/* Operations for component next of union MEMBER */

#pragma token PROC ( EXP : MEMBER : )\
    EXP : PTR ( MEMBER ) : member_next #
#pragma interface member_next

/* Operations for field small of union MEMBER */

#pragma token EXP const : unsigned : member_small_tag #
#pragma token PROC ( EXP : MEMBER : ) EXP : int : IS_member_small #
#pragma interface member_small_tag IS_member_small

#pragma token PROC (\
	EXP : MEMBER :,\
	EXP lvalue : MEMBER :\
    ) STATEMENT MAKE_member_small #
#pragma interface MAKE_member_small

#pragma token PROC (\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP : MEMBER :\
    ) STATEMENT DECONS_member_small #
#pragma interface DECONS_member_small

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP : MEMBER :\
    ) STATEMENT DESTROY_member_small #
#pragma interface DESTROY_member_small


/* Operations for field large of union MEMBER */

#pragma token EXP const : unsigned : member_large_tag #
#pragma token PROC ( EXP : MEMBER : ) EXP : int : IS_member_large #
#pragma interface member_large_tag IS_member_large

#pragma token PROC ( EXP : MEMBER : )\
    EXP : PTR ( MEMBER ) : member_large_tnext #
#pragma interface member_large_tnext

#pragma token PROC (\
	EXP : MEMBER :,\
	EXP : MEMBER :,\
	EXP lvalue : MEMBER :\
    ) STATEMENT MAKE_member_large #
#pragma interface MAKE_member_large

#pragma token PROC (\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP : MEMBER :\
    ) STATEMENT DECONS_member_large #
#pragma interface DECONS_member_large

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP : MEMBER :\
    ) STATEMENT DESTROY_member_large #
#pragma interface DESTROY_member_large


#endif
