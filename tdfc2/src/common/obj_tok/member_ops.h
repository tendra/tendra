/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef MEMBER_OPS_H_INCLUDED
#define MEMBER_OPS_H_INCLUDED

/* Operations for union MEMBER */

#pragma token PROC(EXP : MEMBER :) EXP : unsigned : TAG_member #
#pragma interface TAG_member


/* Operations for component id of union MEMBER */

#pragma token PROC(EXP : MEMBER :)\
    EXP : PTR(IDENTIFIER) : member_id #
#pragma interface member_id

/* Operations for component alt of union MEMBER */

#pragma token PROC(EXP : MEMBER :)\
    EXP : PTR(IDENTIFIER) : member_alt #
#pragma interface member_alt

/* Operations for component next of union MEMBER */

#pragma token PROC(EXP : MEMBER :)\
    EXP : PTR(MEMBER) : member_next #
#pragma interface member_next

/* Operations for field small of union MEMBER */

#pragma token EXP const : unsigned : member_small_tag #
#pragma token PROC(EXP : MEMBER :) EXP : int : IS_member_small #
#pragma interface member_small_tag IS_member_small

#pragma token PROC(\
	EXP : MEMBER :,\
	EXP lvalue : MEMBER :\
    ) STATEMENT MAKE_member_small #
#pragma interface MAKE_member_small

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP : MEMBER :\
    ) STATEMENT DECONS_member_small #
#pragma interface DECONS_member_small

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP : MEMBER :\
    ) STATEMENT DESTROY_member_small #
#pragma interface DESTROY_member_small


/* Operations for field large of union MEMBER */

#pragma token EXP const : unsigned : member_large_tag #
#pragma token PROC(EXP : MEMBER :) EXP : int : IS_member_large #
#pragma interface member_large_tag IS_member_large

#pragma token PROC(EXP : MEMBER :)\
    EXP : PTR(MEMBER) : member_large_tnext #
#pragma interface member_large_tnext

#pragma token PROC(\
	EXP : MEMBER :,\
	EXP : MEMBER :,\
	EXP lvalue : MEMBER :\
    ) STATEMENT MAKE_member_large #
#pragma interface MAKE_member_large

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP : MEMBER :\
    ) STATEMENT DECONS_member_large #
#pragma interface DECONS_member_large

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP : MEMBER :\
    ) STATEMENT DESTROY_member_large #
#pragma interface DESTROY_member_large


#endif
