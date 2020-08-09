/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef TYPE_OPS_H_INCLUDED
#define TYPE_OPS_H_INCLUDED

/* Operations for union TYPE */

#pragma token PROC(EXP : TYPE :) EXP : unsigned : TAG_type #
#pragma interface TAG_type


/* Operations for component qual of union TYPE */

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(CV_SPEC) : type_qual #
#pragma interface type_qual

/* Operations for component name of union TYPE */

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(IDENTIFIER) : type_name #
#pragma interface type_name

/* Operations for field pre of union TYPE */

#pragma token EXP const : unsigned : type_pre_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_pre #
#pragma interface type_pre_tag IS_type_pre

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(BASE_TYPE) : type_pre_rep #
#pragma interface type_pre_rep

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(QUALIFIER) : type_pre_nqual #
#pragma interface type_pre_nqual

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : BASE_TYPE :,\
	EXP : QUALIFIER :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_pre #
#pragma interface MAKE_type_pre

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : BASE_TYPE :,\
	EXP lvalue : QUALIFIER :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_pre #
#pragma interface DECONS_type_pre

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : BASE_TYPE :,\
	EXP lvalue : QUALIFIER :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_pre #
#pragma interface DESTROY_type_pre


/* Operations for field integer of union TYPE */

#pragma token EXP const : unsigned : type_integer_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_integer #
#pragma interface type_integer_tag IS_type_integer

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(INT_TYPE) : type_integer_rep #
#pragma interface type_integer_rep

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(INT_TYPE) : type_integer_sem #
#pragma interface type_integer_sem

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : INT_TYPE :,\
	EXP : INT_TYPE :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_integer #
#pragma interface MAKE_type_integer

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : INT_TYPE :,\
	EXP lvalue : INT_TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_integer #
#pragma interface DECONS_type_integer

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : INT_TYPE :,\
	EXP lvalue : INT_TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_integer #
#pragma interface DESTROY_type_integer


/* Operations for field floating of union TYPE */

#pragma token EXP const : unsigned : type_floating_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_floating #
#pragma interface type_floating_tag IS_type_floating

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(FLOAT_TYPE) : type_floating_rep #
#pragma interface type_floating_rep

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(FLOAT_TYPE) : type_floating_sem #
#pragma interface type_floating_sem

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : FLOAT_TYPE :,\
	EXP : FLOAT_TYPE :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_floating #
#pragma interface MAKE_type_floating

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : FLOAT_TYPE :,\
	EXP lvalue : FLOAT_TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_floating #
#pragma interface DECONS_type_floating

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : FLOAT_TYPE :,\
	EXP lvalue : FLOAT_TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_floating #
#pragma interface DESTROY_type_floating


/* Operations for field set top_etc of union TYPE */

#pragma token EXP const : unsigned : type_top_etc_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_top_etc #
#pragma interface type_top_etc_tag IS_type_top_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : CV_SPEC :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_top_etc #
#pragma interface MAKE_type_top_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : TYPE :\
    ) STATEMENT MODIFY_type_top_etc #
#pragma interface MODIFY_type_top_etc

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_top_etc #
#pragma interface DECONS_type_top_etc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_top_etc #
#pragma interface DESTROY_type_top_etc


/* Operations for field top of union TYPE */

#pragma token EXP const : unsigned : type_top_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_top #
#pragma interface type_top_tag IS_type_top

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_top #
#pragma interface MAKE_type_top

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_top #
#pragma interface DECONS_type_top

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_top #
#pragma interface DESTROY_type_top


/* Operations for field bottom of union TYPE */

#pragma token EXP const : unsigned : type_bottom_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_bottom #
#pragma interface type_bottom_tag IS_type_bottom

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_bottom #
#pragma interface MAKE_type_bottom

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_bottom #
#pragma interface DECONS_type_bottom

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_bottom #
#pragma interface DESTROY_type_bottom


/* Operations for field set ptr_etc of union TYPE */

#pragma token EXP const : unsigned : type_ptr_etc_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_ptr_etc #
#pragma interface type_ptr_etc_tag IS_type_ptr_etc

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(TYPE) : type_ptr_etc_sub #
#pragma interface type_ptr_etc_sub

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : CV_SPEC :,\
	EXP : TYPE :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_ptr_etc #
#pragma interface MAKE_type_ptr_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : TYPE :\
    ) STATEMENT MODIFY_type_ptr_etc #
#pragma interface MODIFY_type_ptr_etc

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_ptr_etc #
#pragma interface DECONS_type_ptr_etc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_ptr_etc #
#pragma interface DESTROY_type_ptr_etc


/* Operations for field ptr of union TYPE */

#pragma token EXP const : unsigned : type_ptr_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_ptr #
#pragma interface type_ptr_tag IS_type_ptr

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(TYPE) : type_ptr_sub #
#pragma interface type_ptr_sub

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : TYPE :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_ptr #
#pragma interface MAKE_type_ptr

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_ptr #
#pragma interface DECONS_type_ptr

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_ptr #
#pragma interface DESTROY_type_ptr


/* Operations for field ref of union TYPE */

#pragma token EXP const : unsigned : type_ref_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_ref #
#pragma interface type_ref_tag IS_type_ref

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(TYPE) : type_ref_sub #
#pragma interface type_ref_sub

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : TYPE :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_ref #
#pragma interface MAKE_type_ref

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_ref #
#pragma interface DECONS_type_ref

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_ref #
#pragma interface DESTROY_type_ref


/* Operations for field ptr_mem of union TYPE */

#pragma token EXP const : unsigned : type_ptr_mem_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_ptr_mem #
#pragma interface type_ptr_mem_tag IS_type_ptr_mem

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(CLASS_TYPE) : type_ptr_mem_of #
#pragma interface type_ptr_mem_of

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(TYPE) : type_ptr_mem_sub #
#pragma interface type_ptr_mem_sub

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : CLASS_TYPE :,\
	EXP : TYPE :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_ptr_mem #
#pragma interface MAKE_type_ptr_mem

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : CLASS_TYPE :,\
	EXP lvalue : TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_ptr_mem #
#pragma interface DECONS_type_ptr_mem

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : CLASS_TYPE :,\
	EXP lvalue : TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_ptr_mem #
#pragma interface DESTROY_type_ptr_mem


/* Operations for field func of union TYPE */

#pragma token EXP const : unsigned : type_func_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_func #
#pragma interface type_func_tag IS_type_func

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(TYPE) : type_func_ret #
#pragma interface type_func_ret

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(LIST(TYPE)) : type_func_ptypes #
#pragma interface type_func_ptypes

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(int) : type_func_ellipsis #
#pragma interface type_func_ellipsis

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(CV_SPEC) : type_func_mqual #
#pragma interface type_func_mqual

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(LIST(TYPE)) : type_func_mtypes #
#pragma interface type_func_mtypes

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(NAMESPACE) : type_func_pars #
#pragma interface type_func_pars

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(LIST(IDENTIFIER)) : type_func_pids #
#pragma interface type_func_pids

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(LIST(TYPE)) : type_func_except #
#pragma interface type_func_except

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : TYPE :,\
	EXP : LIST(TYPE) :,\
	EXP : int :,\
	EXP : CV_SPEC :,\
	EXP : LIST(TYPE) :,\
	EXP : NAMESPACE :,\
	EXP : LIST(IDENTIFIER) :,\
	EXP : LIST(TYPE) :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_func #
#pragma interface MAKE_type_func

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : int :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_func #
#pragma interface DECONS_type_func

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : int :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_func #
#pragma interface DESTROY_type_func


/* Operations for field array of union TYPE */

#pragma token EXP const : unsigned : type_array_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_array #
#pragma interface type_array_tag IS_type_array

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(TYPE) : type_array_sub #
#pragma interface type_array_sub

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(NAT) : type_array_size #
#pragma interface type_array_size

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : TYPE :,\
	EXP : NAT :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_array #
#pragma interface MAKE_type_array

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : NAT :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_array #
#pragma interface DECONS_type_array

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : NAT :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_array #
#pragma interface DESTROY_type_array


/* Operations for field bitfield of union TYPE */

#pragma token EXP const : unsigned : type_bitfield_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_bitfield #
#pragma interface type_bitfield_tag IS_type_bitfield

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(INT_TYPE) : type_bitfield_defn #
#pragma interface type_bitfield_defn

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : INT_TYPE :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_bitfield #
#pragma interface MAKE_type_bitfield

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : INT_TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_bitfield #
#pragma interface DECONS_type_bitfield

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : INT_TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_bitfield #
#pragma interface DESTROY_type_bitfield


/* Operations for field compound of union TYPE */

#pragma token EXP const : unsigned : type_compound_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_compound #
#pragma interface type_compound_tag IS_type_compound

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(CLASS_TYPE) : type_compound_defn #
#pragma interface type_compound_defn

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : CLASS_TYPE :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_compound #
#pragma interface MAKE_type_compound

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : CLASS_TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_compound #
#pragma interface DECONS_type_compound

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : CLASS_TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_compound #
#pragma interface DESTROY_type_compound


/* Operations for field enumerate of union TYPE */

#pragma token EXP const : unsigned : type_enumerate_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_enumerate #
#pragma interface type_enumerate_tag IS_type_enumerate

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(ENUM_TYPE) : type_enumerate_defn #
#pragma interface type_enumerate_defn

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : ENUM_TYPE :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_enumerate #
#pragma interface MAKE_type_enumerate

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ENUM_TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_enumerate #
#pragma interface DECONS_type_enumerate

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ENUM_TYPE :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_enumerate #
#pragma interface DESTROY_type_enumerate


/* Operations for field token of union TYPE */

#pragma token EXP const : unsigned : type_token_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_token #
#pragma interface type_token_tag IS_type_token

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(IDENTIFIER) : type_token_tok #
#pragma interface type_token_tok

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(LIST(TOKEN)) : type_token_args #
#pragma interface type_token_args

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(INSTANCE) : type_token_app #
#pragma interface type_token_app

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : IDENTIFIER :,\
	EXP : LIST(TOKEN) :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_token #
#pragma interface MAKE_type_token

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(TOKEN) :,\
	EXP lvalue : INSTANCE :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_token #
#pragma interface DECONS_type_token

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(TOKEN) :,\
	EXP lvalue : INSTANCE :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_token #
#pragma interface DESTROY_type_token


/* Operations for field templ of union TYPE */

#pragma token EXP const : unsigned : type_templ_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_templ #
#pragma interface type_templ_tag IS_type_templ

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(TOKEN) : type_templ_sort #
#pragma interface type_templ_sort

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(TYPE) : type_templ_defn #
#pragma interface type_templ_defn

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(int) : type_templ_fix #
#pragma interface type_templ_fix

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : TOKEN :,\
	EXP : TYPE :,\
	EXP : int :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_templ #
#pragma interface MAKE_type_templ

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TOKEN :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_templ #
#pragma interface DECONS_type_templ

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TOKEN :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_templ #
#pragma interface DESTROY_type_templ


/* Operations for field instance of union TYPE */

#pragma token EXP const : unsigned : type_instance_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_instance #
#pragma interface type_instance_tag IS_type_instance

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(IDENTIFIER) : type_instance_id #
#pragma interface type_instance_id

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(DECL_SPEC) : type_instance_access #
#pragma interface type_instance_access

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : IDENTIFIER :,\
	EXP : DECL_SPEC :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_instance #
#pragma interface MAKE_type_instance

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : DECL_SPEC :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_instance #
#pragma interface DECONS_type_instance

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : DECL_SPEC :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_instance #
#pragma interface DESTROY_type_instance


/* Operations for field dummy of union TYPE */

#pragma token EXP const : unsigned : type_dummy_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_dummy #
#pragma interface type_dummy_tag IS_type_dummy

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(int) : type_dummy_tok #
#pragma interface type_dummy_tok

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP : int :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_dummy #
#pragma interface MAKE_type_dummy

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : int :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_dummy #
#pragma interface DECONS_type_dummy

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : int :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_dummy #
#pragma interface DESTROY_type_dummy


/* Operations for field error of union TYPE */

#pragma token EXP const : unsigned : type_error_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_error #
#pragma interface type_error_tag IS_type_error

#pragma token PROC(\
	EXP : CV_SPEC :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_error #
#pragma interface MAKE_type_error

#pragma token PROC(\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_error #
#pragma interface DECONS_type_error

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : CV_SPEC :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_error #
#pragma interface DESTROY_type_error


#endif
