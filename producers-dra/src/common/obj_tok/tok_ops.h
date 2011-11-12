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

#ifndef TOK_OPS_H_INCLUDED
#define TOK_OPS_H_INCLUDED

/* Operations for union TOKEN */

#pragma token PROC(EXP : TOKEN :) EXP : unsigned : TAG_tok #
#pragma interface TAG_tok


/* Operations for field exp of union TOKEN */

#pragma token EXP const : unsigned : tok_exp_tag #
#pragma token PROC(EXP : TOKEN :) EXP : int : IS_tok_exp #
#pragma interface tok_exp_tag IS_tok_exp

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(TYPE) : tok_exp_type #
#pragma interface tok_exp_type

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(int) : tok_exp_constant #
#pragma interface tok_exp_constant

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(EXP) : tok_exp_value #
#pragma interface tok_exp_value

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : int :,\
	EXP : EXP :,\
	EXP lvalue : TOKEN :\
    ) STATEMENT MAKE_tok_exp #
#pragma interface MAKE_tok_exp

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP lvalue : EXP :,\
	EXP : TOKEN :\
    ) STATEMENT DECONS_tok_exp #
#pragma interface DECONS_tok_exp

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP lvalue : EXP :,\
	EXP : TOKEN :\
    ) STATEMENT DESTROY_tok_exp #
#pragma interface DESTROY_tok_exp


/* Operations for field stmt of union TOKEN */

#pragma token EXP const : unsigned : tok_stmt_tag #
#pragma token PROC(EXP : TOKEN :) EXP : int : IS_tok_stmt #
#pragma interface tok_stmt_tag IS_tok_stmt

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(EXP) : tok_stmt_value #
#pragma interface tok_stmt_value

#pragma token PROC(\
	EXP : EXP :,\
	EXP lvalue : TOKEN :\
    ) STATEMENT MAKE_tok_stmt #
#pragma interface MAKE_tok_stmt

#pragma token PROC(\
	EXP lvalue : EXP :,\
	EXP : TOKEN :\
    ) STATEMENT DECONS_tok_stmt #
#pragma interface DECONS_tok_stmt

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : EXP :,\
	EXP : TOKEN :\
    ) STATEMENT DESTROY_tok_stmt #
#pragma interface DESTROY_tok_stmt


/* Operations for field set nat_etc of union TOKEN */

#pragma token EXP const : unsigned : tok_nat_etc_tag #
#pragma token PROC(EXP : TOKEN :) EXP : int : IS_tok_nat_etc #
#pragma interface tok_nat_etc_tag IS_tok_nat_etc

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(NAT) : tok_nat_etc_value #
#pragma interface tok_nat_etc_value

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : NAT :,\
	EXP lvalue : TOKEN :\
    ) STATEMENT MAKE_tok_nat_etc #
#pragma interface MAKE_tok_nat_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : TOKEN :\
    ) STATEMENT MODIFY_tok_nat_etc #
#pragma interface MODIFY_tok_nat_etc

#pragma token PROC(\
	EXP lvalue : NAT :,\
	EXP : TOKEN :\
    ) STATEMENT DECONS_tok_nat_etc #
#pragma interface DECONS_tok_nat_etc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : NAT :,\
	EXP : TOKEN :\
    ) STATEMENT DESTROY_tok_nat_etc #
#pragma interface DESTROY_tok_nat_etc


/* Operations for field nat of union TOKEN */

#pragma token EXP const : unsigned : tok_nat_tag #
#pragma token PROC(EXP : TOKEN :) EXP : int : IS_tok_nat #
#pragma interface tok_nat_tag IS_tok_nat

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(NAT) : tok_nat_value #
#pragma interface tok_nat_value

#pragma token PROC(\
	EXP : NAT :,\
	EXP lvalue : TOKEN :\
    ) STATEMENT MAKE_tok_nat #
#pragma interface MAKE_tok_nat

#pragma token PROC(\
	EXP lvalue : NAT :,\
	EXP : TOKEN :\
    ) STATEMENT DECONS_tok_nat #
#pragma interface DECONS_tok_nat

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : NAT :,\
	EXP : TOKEN :\
    ) STATEMENT DESTROY_tok_nat #
#pragma interface DESTROY_tok_nat


/* Operations for field snat of union TOKEN */

#pragma token EXP const : unsigned : tok_snat_tag #
#pragma token PROC(EXP : TOKEN :) EXP : int : IS_tok_snat #
#pragma interface tok_snat_tag IS_tok_snat

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(NAT) : tok_snat_value #
#pragma interface tok_snat_value

#pragma token PROC(\
	EXP : NAT :,\
	EXP lvalue : TOKEN :\
    ) STATEMENT MAKE_tok_snat #
#pragma interface MAKE_tok_snat

#pragma token PROC(\
	EXP lvalue : NAT :,\
	EXP : TOKEN :\
    ) STATEMENT DECONS_tok_snat #
#pragma interface DECONS_tok_snat

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : NAT :,\
	EXP : TOKEN :\
    ) STATEMENT DESTROY_tok_snat #
#pragma interface DESTROY_tok_snat


/* Operations for field type of union TOKEN */

#pragma token EXP const : unsigned : tok_type_tag #
#pragma token PROC(EXP : TOKEN :) EXP : int : IS_tok_type #
#pragma interface tok_type_tag IS_tok_type

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(BASE_TYPE) : tok_type_kind #
#pragma interface tok_type_kind

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(TYPE) : tok_type_value #
#pragma interface tok_type_value

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(TYPE) : tok_type_alt #
#pragma interface tok_type_alt

#pragma token PROC(\
	EXP : BASE_TYPE :,\
	EXP : TYPE :,\
	EXP lvalue : TOKEN :\
    ) STATEMENT MAKE_tok_type #
#pragma interface MAKE_tok_type

#pragma token PROC(\
	EXP lvalue : BASE_TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP : TOKEN :\
    ) STATEMENT DECONS_tok_type #
#pragma interface DECONS_tok_type

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : BASE_TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP : TOKEN :\
    ) STATEMENT DESTROY_tok_type #
#pragma interface DESTROY_tok_type


/* Operations for field func of union TOKEN */

#pragma token EXP const : unsigned : tok_func_tag #
#pragma token PROC(EXP : TOKEN :) EXP : int : IS_tok_func #
#pragma interface tok_func_tag IS_tok_func

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(TYPE) : tok_func_type #
#pragma interface tok_func_type

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(IDENTIFIER) : tok_func_defn #
#pragma interface tok_func_defn

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(TOKEN) : tok_func_proc #
#pragma interface tok_func_proc

#pragma token PROC(\
	EXP : TYPE :,\
	EXP lvalue : TOKEN :\
    ) STATEMENT MAKE_tok_func #
#pragma interface MAKE_tok_func

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TOKEN :,\
	EXP : TOKEN :\
    ) STATEMENT DECONS_tok_func #
#pragma interface DECONS_tok_func

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TOKEN :,\
	EXP : TOKEN :\
    ) STATEMENT DESTROY_tok_func #
#pragma interface DESTROY_tok_func


/* Operations for field member of union TOKEN */

#pragma token EXP const : unsigned : tok_member_tag #
#pragma token PROC(EXP : TOKEN :) EXP : int : IS_tok_member #
#pragma interface tok_member_tag IS_tok_member

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(TYPE) : tok_member_of #
#pragma interface tok_member_of

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(TYPE) : tok_member_type #
#pragma interface tok_member_type

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(OFFSET) : tok_member_value #
#pragma interface tok_member_value

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : TYPE :,\
	EXP : OFFSET :,\
	EXP lvalue : TOKEN :\
    ) STATEMENT MAKE_tok_member #
#pragma interface MAKE_tok_member

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : OFFSET :,\
	EXP : TOKEN :\
    ) STATEMENT DECONS_tok_member #
#pragma interface DECONS_tok_member

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : OFFSET :,\
	EXP : TOKEN :\
    ) STATEMENT DESTROY_tok_member #
#pragma interface DESTROY_tok_member


/* Operations for field class of union TOKEN */

#pragma token EXP const : unsigned : tok_class_tag #
#pragma token PROC(EXP : TOKEN :) EXP : int : IS_tok_class #
#pragma interface tok_class_tag IS_tok_class

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(TYPE) : tok_class_type #
#pragma interface tok_class_type

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(IDENTIFIER) : tok_class_value #
#pragma interface tok_class_value

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(TYPE) : tok_class_alt #
#pragma interface tok_class_alt

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : TOKEN :\
    ) STATEMENT MAKE_tok_class #
#pragma interface MAKE_tok_class

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP : TOKEN :\
    ) STATEMENT DECONS_tok_class #
#pragma interface DECONS_tok_class

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP : TOKEN :\
    ) STATEMENT DESTROY_tok_class #
#pragma interface DESTROY_tok_class


/* Operations for field proc of union TOKEN */

#pragma token EXP const : unsigned : tok_proc_tag #
#pragma token PROC(EXP : TOKEN :) EXP : int : IS_tok_proc #
#pragma interface tok_proc_tag IS_tok_proc

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(TOKEN) : tok_proc_res #
#pragma interface tok_proc_res

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(NAMESPACE) : tok_proc_pars #
#pragma interface tok_proc_pars

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(int) : tok_proc_key #
#pragma interface tok_proc_key

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(INSTANCE) : tok_proc_apps #
#pragma interface tok_proc_apps

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(LIST(IDENTIFIER)) : tok_proc_bids #
#pragma interface tok_proc_bids

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(LIST(IDENTIFIER)) : tok_proc_pids #
#pragma interface tok_proc_pids

#pragma token PROC(\
	EXP : TOKEN :,\
	EXP : NAMESPACE :,\
	EXP : int :,\
	EXP lvalue : TOKEN :\
    ) STATEMENT MAKE_tok_proc #
#pragma interface MAKE_tok_proc

#pragma token PROC(\
	EXP lvalue : TOKEN :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : int :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP : TOKEN :\
    ) STATEMENT DECONS_tok_proc #
#pragma interface DECONS_tok_proc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TOKEN :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : int :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP : TOKEN :\
    ) STATEMENT DESTROY_tok_proc #
#pragma interface DESTROY_tok_proc


/* Operations for field templ of union TOKEN */

#pragma token EXP const : unsigned : tok_templ_tag #
#pragma token PROC(EXP : TOKEN :) EXP : int : IS_tok_templ #
#pragma interface tok_templ_tag IS_tok_templ

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(DECL_SPEC) : tok_templ_usage #
#pragma interface tok_templ_usage

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(NAMESPACE) : tok_templ_pars #
#pragma interface tok_templ_pars

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(INSTANCE) : tok_templ_apps #
#pragma interface tok_templ_apps

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(LIST(IDENTIFIER)) : tok_templ_pids #
#pragma interface tok_templ_pids

#pragma token PROC(EXP : TOKEN :)\
    EXP : PTR(LIST(TOKEN)) : tok_templ_dargs #
#pragma interface tok_templ_dargs

#pragma token PROC(\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP lvalue : TOKEN :\
    ) STATEMENT MAKE_tok_templ #
#pragma interface MAKE_tok_templ

#pragma token PROC(\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : LIST(TOKEN) :,\
	EXP : TOKEN :\
    ) STATEMENT DECONS_tok_templ #
#pragma interface DECONS_tok_templ

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : INSTANCE :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : LIST(TOKEN) :,\
	EXP : TOKEN :\
    ) STATEMENT DESTROY_tok_templ #
#pragma interface DESTROY_tok_templ


#endif
