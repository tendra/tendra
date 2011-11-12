/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef INST_OPS_H_INCLUDED
#define INST_OPS_H_INCLUDED

/* Operations for union INSTANCE */

#pragma token PROC(EXP : INSTANCE :) EXP : unsigned : TAG_inst #
#pragma interface TAG_inst


/* Operations for component form of union INSTANCE */

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(TYPE) : inst_form #
#pragma interface inst_form

/* Operations for component alias of union INSTANCE */

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(INSTANCE) : inst_alias #
#pragma interface inst_alias

/* Operations for component next of union INSTANCE */

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(INSTANCE) : inst_next #
#pragma interface inst_next

/* Operations for field templ of union INSTANCE */

#pragma token EXP const : unsigned : inst_templ_tag #
#pragma token PROC(EXP : INSTANCE :) EXP : int : IS_inst_templ #
#pragma interface inst_templ_tag IS_inst_templ

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(IDENTIFIER) : inst_templ_id #
#pragma interface inst_templ_id

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(TYPE) : inst_templ_spec #
#pragma interface inst_templ_spec

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(DECL_SPEC) : inst_templ_access #
#pragma interface inst_templ_access

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(PPTOKEN_P) : inst_templ_mode #
#pragma interface inst_templ_mode

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(LIST(IDENTIFIER)) : inst_templ_mems #
#pragma interface inst_templ_mems

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(INSTANCE) : inst_templ_prev #
#pragma interface inst_templ_prev

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : INSTANCE :,\
	EXP : IDENTIFIER :,\
	EXP : DECL_SPEC :,\
	EXP : INSTANCE :,\
	EXP lvalue : INSTANCE :\
    ) STATEMENT MAKE_inst_templ #
#pragma interface MAKE_inst_templ

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : PPTOKEN_P :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : INSTANCE :,\
	EXP : INSTANCE :\
    ) STATEMENT DECONS_inst_templ #
#pragma interface DECONS_inst_templ

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : PPTOKEN_P :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : INSTANCE :,\
	EXP : INSTANCE :\
    ) STATEMENT DESTROY_inst_templ #
#pragma interface DESTROY_inst_templ


/* Operations for field token of union INSTANCE */

#pragma token EXP const : unsigned : inst_token_tag #
#pragma token PROC(EXP : INSTANCE :) EXP : int : IS_inst_token #
#pragma interface inst_token_tag IS_inst_token

#pragma token PROC(EXP : INSTANCE :)\
    EXP : PTR(ulong_type) : inst_token_no #
#pragma interface inst_token_no

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : INSTANCE :,\
	EXP lvalue : INSTANCE :\
    ) STATEMENT MAKE_inst_token #
#pragma interface MAKE_inst_token

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : ulong_type :,\
	EXP : INSTANCE :\
    ) STATEMENT DECONS_inst_token #
#pragma interface DECONS_inst_token

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : ulong_type :,\
	EXP : INSTANCE :\
    ) STATEMENT DESTROY_inst_token #
#pragma interface DESTROY_inst_token


#endif
