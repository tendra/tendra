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

#ifndef ID_OPS_H_INCLUDED
#define ID_OPS_H_INCLUDED

/* Operations for union IDENTIFIER */

#pragma token PROC ( EXP : IDENTIFIER : ) EXP : unsigned : TAG_id #
#pragma interface TAG_id


/* Operations for component name of union IDENTIFIER */

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( HASHID ) : id_name #
#pragma interface id_name

/* Operations for component storage of union IDENTIFIER */

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( DECL_SPEC ) : id_storage #
#pragma interface id_storage

/* Operations for component parent of union IDENTIFIER */

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( NAMESPACE ) : id_parent #
#pragma interface id_parent

/* Operations for component loc of union IDENTIFIER */

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( LOCATION ) : id_loc #
#pragma interface id_loc

/* Operations for component alias of union IDENTIFIER */

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( IDENTIFIER ) : id_alias #
#pragma interface id_alias

/* Operations for component no of union IDENTIFIER */

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( ulong_type ) : id_no #
#pragma interface id_no

/* Operations for component dump of union IDENTIFIER */

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( ulong_type ) : id_dump #
#pragma interface id_dump

/* Operations for field dummy of union IDENTIFIER */

#pragma token EXP const : unsigned : id_dummy_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_dummy #
#pragma interface id_dummy_tag IS_id_dummy

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_dummy #
#pragma interface MAKE_id_dummy

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_dummy #
#pragma interface DECONS_id_dummy

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_dummy #
#pragma interface DESTROY_id_dummy


/* Operations for field set keyword_etc of union IDENTIFIER */

#pragma token EXP const : unsigned : id_keyword_etc_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_keyword_etc #
#pragma interface id_keyword_etc_tag IS_id_keyword_etc

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_keyword_etc #
#pragma interface MAKE_id_keyword_etc

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : IDENTIFIER :\
    ) STATEMENT MODIFY_id_keyword_etc #
#pragma interface MODIFY_id_keyword_etc

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_keyword_etc #
#pragma interface DECONS_id_keyword_etc

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_keyword_etc #
#pragma interface DESTROY_id_keyword_etc


/* Operations for field keyword of union IDENTIFIER */

#pragma token EXP const : unsigned : id_keyword_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_keyword #
#pragma interface id_keyword_tag IS_id_keyword

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_keyword #
#pragma interface MAKE_id_keyword

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_keyword #
#pragma interface DECONS_id_keyword

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_keyword #
#pragma interface DESTROY_id_keyword


/* Operations for field iso_keyword of union IDENTIFIER */

#pragma token EXP const : unsigned : id_iso_keyword_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_iso_keyword #
#pragma interface id_iso_keyword_tag IS_id_iso_keyword

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_iso_keyword #
#pragma interface MAKE_id_iso_keyword

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_iso_keyword #
#pragma interface DECONS_id_iso_keyword

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_iso_keyword #
#pragma interface DESTROY_id_iso_keyword


/* Operations for field reserved of union IDENTIFIER */

#pragma token EXP const : unsigned : id_reserved_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_reserved #
#pragma interface id_reserved_tag IS_id_reserved

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_reserved #
#pragma interface MAKE_id_reserved

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_reserved #
#pragma interface DECONS_id_reserved

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_reserved #
#pragma interface DESTROY_id_reserved


/* Operations for field builtin of union IDENTIFIER */

#pragma token EXP const : unsigned : id_builtin_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_builtin #
#pragma interface id_builtin_tag IS_id_builtin

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_builtin_ret #
#pragma interface id_builtin_ret

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( LIST ( TYPE ) ) : id_builtin_ptypes #
#pragma interface id_builtin_ptypes

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP : LIST ( TYPE ) :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_builtin #
#pragma interface MAKE_id_builtin

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST ( TYPE ) :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_builtin #
#pragma interface DECONS_id_builtin

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST ( TYPE ) :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_builtin #
#pragma interface DESTROY_id_builtin


/* Operations for field obj_macro of union IDENTIFIER */

#pragma token EXP const : unsigned : id_obj_macro_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_obj_macro #
#pragma interface id_obj_macro_tag IS_id_obj_macro

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( PPTOKEN_P ) : id_obj_macro_defn #
#pragma interface id_obj_macro_defn

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : PPTOKEN_P :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_obj_macro #
#pragma interface MAKE_id_obj_macro

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : PPTOKEN_P :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_obj_macro #
#pragma interface DECONS_id_obj_macro

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : PPTOKEN_P :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_obj_macro #
#pragma interface DESTROY_id_obj_macro


/* Operations for field func_macro of union IDENTIFIER */

#pragma token EXP const : unsigned : id_func_macro_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_func_macro #
#pragma interface id_func_macro_tag IS_id_func_macro

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( PPTOKEN_P ) : id_func_macro_defn #
#pragma interface id_func_macro_defn

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( LIST ( HASHID ) ) : id_func_macro_params #
#pragma interface id_func_macro_params

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( unsigned ) : id_func_macro_no_params #
#pragma interface id_func_macro_no_params

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : PPTOKEN_P :,\
	EXP : LIST ( HASHID ) :,\
	EXP : unsigned :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_func_macro #
#pragma interface MAKE_id_func_macro

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : PPTOKEN_P :,\
	EXP lvalue : LIST ( HASHID ) :,\
	EXP lvalue : unsigned :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_func_macro #
#pragma interface DECONS_id_func_macro

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : PPTOKEN_P :,\
	EXP lvalue : LIST ( HASHID ) :,\
	EXP lvalue : unsigned :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_func_macro #
#pragma interface DESTROY_id_func_macro


/* Operations for field predicate of union IDENTIFIER */

#pragma token EXP const : unsigned : id_predicate_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_predicate #
#pragma interface id_predicate_tag IS_id_predicate

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( LIST ( PPTOKEN_P ) ) : id_predicate_values #
#pragma interface id_predicate_values

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_predicate #
#pragma interface MAKE_id_predicate

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : LIST ( PPTOKEN_P ) :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_predicate #
#pragma interface DECONS_id_predicate

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : LIST ( PPTOKEN_P ) :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_predicate #
#pragma interface DESTROY_id_predicate


/* Operations for field set class_name_etc of union IDENTIFIER */

#pragma token EXP const : unsigned : id_class_name_etc_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_class_name_etc #
#pragma interface id_class_name_etc_tag IS_id_class_name_etc

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_class_name_etc_defn #
#pragma interface id_class_name_etc_defn

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( BASE_TYPE ) : id_class_name_etc_rep #
#pragma interface id_class_name_etc_rep

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_class_name_etc #
#pragma interface MAKE_id_class_name_etc

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : IDENTIFIER :\
    ) STATEMENT MODIFY_id_class_name_etc #
#pragma interface MODIFY_id_class_name_etc

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : BASE_TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_class_name_etc #
#pragma interface DECONS_id_class_name_etc

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : BASE_TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_class_name_etc #
#pragma interface DESTROY_id_class_name_etc


/* Operations for field class_name of union IDENTIFIER */

#pragma token EXP const : unsigned : id_class_name_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_class_name #
#pragma interface id_class_name_tag IS_id_class_name

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_class_name_defn #
#pragma interface id_class_name_defn

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( BASE_TYPE ) : id_class_name_rep #
#pragma interface id_class_name_rep

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_class_name #
#pragma interface MAKE_id_class_name

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : BASE_TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_class_name #
#pragma interface DECONS_id_class_name

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : BASE_TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_class_name #
#pragma interface DESTROY_id_class_name


/* Operations for field enum_name of union IDENTIFIER */

#pragma token EXP const : unsigned : id_enum_name_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_enum_name #
#pragma interface id_enum_name_tag IS_id_enum_name

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_enum_name_defn #
#pragma interface id_enum_name_defn

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( BASE_TYPE ) : id_enum_name_rep #
#pragma interface id_enum_name_rep

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_enum_name #
#pragma interface MAKE_id_enum_name

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : BASE_TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_enum_name #
#pragma interface DECONS_id_enum_name

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : BASE_TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_enum_name #
#pragma interface DESTROY_id_enum_name


/* Operations for field class_alias of union IDENTIFIER */

#pragma token EXP const : unsigned : id_class_alias_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_class_alias #
#pragma interface id_class_alias_tag IS_id_class_alias

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_class_alias_defn #
#pragma interface id_class_alias_defn

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( BASE_TYPE ) : id_class_alias_rep #
#pragma interface id_class_alias_rep

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_class_alias #
#pragma interface MAKE_id_class_alias

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : BASE_TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_class_alias #
#pragma interface DECONS_id_class_alias

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : BASE_TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_class_alias #
#pragma interface DESTROY_id_class_alias


/* Operations for field enum_alias of union IDENTIFIER */

#pragma token EXP const : unsigned : id_enum_alias_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_enum_alias #
#pragma interface id_enum_alias_tag IS_id_enum_alias

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_enum_alias_defn #
#pragma interface id_enum_alias_defn

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( BASE_TYPE ) : id_enum_alias_rep #
#pragma interface id_enum_alias_rep

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_enum_alias #
#pragma interface MAKE_id_enum_alias

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : BASE_TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_enum_alias #
#pragma interface DECONS_id_enum_alias

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : BASE_TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_enum_alias #
#pragma interface DESTROY_id_enum_alias


/* Operations for field type_alias of union IDENTIFIER */

#pragma token EXP const : unsigned : id_type_alias_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_type_alias #
#pragma interface id_type_alias_tag IS_id_type_alias

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_type_alias_defn #
#pragma interface id_type_alias_defn

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( BASE_TYPE ) : id_type_alias_rep #
#pragma interface id_type_alias_rep

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_type_alias #
#pragma interface MAKE_id_type_alias

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : BASE_TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_type_alias #
#pragma interface DECONS_id_type_alias

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : BASE_TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_type_alias #
#pragma interface DESTROY_id_type_alias


/* Operations for field set nspace_name_etc of union IDENTIFIER */

#pragma token EXP const : unsigned : id_nspace_name_etc_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_nspace_name_etc #
#pragma interface id_nspace_name_etc_tag IS_id_nspace_name_etc

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( NAMESPACE ) : id_nspace_name_etc_defn #
#pragma interface id_nspace_name_etc_defn

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : NAMESPACE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_nspace_name_etc #
#pragma interface MAKE_id_nspace_name_etc

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : IDENTIFIER :\
    ) STATEMENT MODIFY_id_nspace_name_etc #
#pragma interface MODIFY_id_nspace_name_etc

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : NAMESPACE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_nspace_name_etc #
#pragma interface DECONS_id_nspace_name_etc

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : NAMESPACE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_nspace_name_etc #
#pragma interface DESTROY_id_nspace_name_etc


/* Operations for field nspace_name of union IDENTIFIER */

#pragma token EXP const : unsigned : id_nspace_name_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_nspace_name #
#pragma interface id_nspace_name_tag IS_id_nspace_name

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( NAMESPACE ) : id_nspace_name_defn #
#pragma interface id_nspace_name_defn

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : NAMESPACE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_nspace_name #
#pragma interface MAKE_id_nspace_name

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : NAMESPACE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_nspace_name #
#pragma interface DECONS_id_nspace_name

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : NAMESPACE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_nspace_name #
#pragma interface DESTROY_id_nspace_name


/* Operations for field nspace_alias of union IDENTIFIER */

#pragma token EXP const : unsigned : id_nspace_alias_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_nspace_alias #
#pragma interface id_nspace_alias_tag IS_id_nspace_alias

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( NAMESPACE ) : id_nspace_alias_defn #
#pragma interface id_nspace_alias_defn

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : NAMESPACE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_nspace_alias #
#pragma interface MAKE_id_nspace_alias

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : NAMESPACE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_nspace_alias #
#pragma interface DECONS_id_nspace_alias

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : NAMESPACE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_nspace_alias #
#pragma interface DESTROY_id_nspace_alias


/* Operations for field set variable_etc of union IDENTIFIER */

#pragma token EXP const : unsigned : id_variable_etc_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_variable_etc #
#pragma interface id_variable_etc_tag IS_id_variable_etc

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_variable_etc_type #
#pragma interface id_variable_etc_type

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_variable_etc_init #
#pragma interface id_variable_etc_init

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_variable_etc_term #
#pragma interface id_variable_etc_term

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_variable_etc #
#pragma interface MAKE_id_variable_etc

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : IDENTIFIER :\
    ) STATEMENT MODIFY_id_variable_etc #
#pragma interface MODIFY_id_variable_etc

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_variable_etc #
#pragma interface DECONS_id_variable_etc

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_variable_etc #
#pragma interface DESTROY_id_variable_etc


/* Operations for field variable of union IDENTIFIER */

#pragma token EXP const : unsigned : id_variable_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_variable #
#pragma interface id_variable_tag IS_id_variable

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_variable_type #
#pragma interface id_variable_type

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_variable_init #
#pragma interface id_variable_init

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_variable_term #
#pragma interface id_variable_term

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_variable #
#pragma interface MAKE_id_variable

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_variable #
#pragma interface DECONS_id_variable

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_variable #
#pragma interface DESTROY_id_variable


/* Operations for field parameter of union IDENTIFIER */

#pragma token EXP const : unsigned : id_parameter_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_parameter #
#pragma interface id_parameter_tag IS_id_parameter

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_parameter_type #
#pragma interface id_parameter_type

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_parameter_init #
#pragma interface id_parameter_init

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_parameter_term #
#pragma interface id_parameter_term

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_parameter #
#pragma interface MAKE_id_parameter

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_parameter #
#pragma interface DECONS_id_parameter

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_parameter #
#pragma interface DESTROY_id_parameter


/* Operations for field stat_member of union IDENTIFIER */

#pragma token EXP const : unsigned : id_stat_member_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_stat_member #
#pragma interface id_stat_member_tag IS_id_stat_member

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_stat_member_type #
#pragma interface id_stat_member_type

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_stat_member_init #
#pragma interface id_stat_member_init

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_stat_member_term #
#pragma interface id_stat_member_term

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_stat_member #
#pragma interface MAKE_id_stat_member

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_stat_member #
#pragma interface DECONS_id_stat_member

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_stat_member #
#pragma interface DESTROY_id_stat_member


/* Operations for field weak_param of union IDENTIFIER */

#pragma token EXP const : unsigned : id_weak_param_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_weak_param #
#pragma interface id_weak_param_tag IS_id_weak_param

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_weak_param #
#pragma interface MAKE_id_weak_param

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_weak_param #
#pragma interface DECONS_id_weak_param

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_weak_param #
#pragma interface DESTROY_id_weak_param


/* Operations for field set function_etc of union IDENTIFIER */

#pragma token EXP const : unsigned : id_function_etc_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_function_etc #
#pragma interface id_function_etc_tag IS_id_function_etc

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_function_etc_type #
#pragma interface id_function_etc_type

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( IDENTIFIER ) : id_function_etc_over #
#pragma interface id_function_etc_over

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_function_etc_form #
#pragma interface id_function_etc_form

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( LIST ( CLASS_TYPE ) ) : id_function_etc_chums #
#pragma interface id_function_etc_chums

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_function_etc_defn #
#pragma interface id_function_etc_defn

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_function_etc #
#pragma interface MAKE_id_function_etc

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : IDENTIFIER :\
    ) STATEMENT MODIFY_id_function_etc #
#pragma interface MODIFY_id_function_etc

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST ( CLASS_TYPE ) :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_function_etc #
#pragma interface DECONS_id_function_etc

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST ( CLASS_TYPE ) :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_function_etc #
#pragma interface DESTROY_id_function_etc


/* Operations for field function of union IDENTIFIER */

#pragma token EXP const : unsigned : id_function_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_function #
#pragma interface id_function_tag IS_id_function

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_function_type #
#pragma interface id_function_type

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( IDENTIFIER ) : id_function_over #
#pragma interface id_function_over

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_function_form #
#pragma interface id_function_form

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( LIST ( CLASS_TYPE ) ) : id_function_chums #
#pragma interface id_function_chums

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_function_defn #
#pragma interface id_function_defn

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_function #
#pragma interface MAKE_id_function

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST ( CLASS_TYPE ) :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_function #
#pragma interface DECONS_id_function

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST ( CLASS_TYPE ) :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_function #
#pragma interface DESTROY_id_function


/* Operations for field mem_func of union IDENTIFIER */

#pragma token EXP const : unsigned : id_mem_func_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_mem_func #
#pragma interface id_mem_func_tag IS_id_mem_func

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_mem_func_type #
#pragma interface id_mem_func_type

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( IDENTIFIER ) : id_mem_func_over #
#pragma interface id_mem_func_over

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_mem_func_form #
#pragma interface id_mem_func_form

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( LIST ( CLASS_TYPE ) ) : id_mem_func_chums #
#pragma interface id_mem_func_chums

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_mem_func_defn #
#pragma interface id_mem_func_defn

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_mem_func #
#pragma interface MAKE_id_mem_func

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST ( CLASS_TYPE ) :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_mem_func #
#pragma interface DECONS_id_mem_func

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST ( CLASS_TYPE ) :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_mem_func #
#pragma interface DESTROY_id_mem_func


/* Operations for field stat_mem_func of union IDENTIFIER */

#pragma token EXP const : unsigned : id_stat_mem_func_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_stat_mem_func #
#pragma interface id_stat_mem_func_tag IS_id_stat_mem_func

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_stat_mem_func_type #
#pragma interface id_stat_mem_func_type

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( IDENTIFIER ) : id_stat_mem_func_over #
#pragma interface id_stat_mem_func_over

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_stat_mem_func_form #
#pragma interface id_stat_mem_func_form

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( LIST ( CLASS_TYPE ) ) : id_stat_mem_func_chums #
#pragma interface id_stat_mem_func_chums

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_stat_mem_func_defn #
#pragma interface id_stat_mem_func_defn

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_stat_mem_func #
#pragma interface MAKE_id_stat_mem_func

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST ( CLASS_TYPE ) :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_stat_mem_func #
#pragma interface DECONS_id_stat_mem_func

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST ( CLASS_TYPE ) :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_stat_mem_func #
#pragma interface DESTROY_id_stat_mem_func


/* Operations for field member of union IDENTIFIER */

#pragma token EXP const : unsigned : id_member_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_member #
#pragma interface id_member_tag IS_id_member

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_member_type #
#pragma interface id_member_type

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( OFFSET ) : id_member_off #
#pragma interface id_member_off

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( GRAPH ) : id_member_base #
#pragma interface id_member_base

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_member #
#pragma interface MAKE_id_member

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : GRAPH :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_member #
#pragma interface DECONS_id_member

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : GRAPH :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_member #
#pragma interface DESTROY_id_member


/* Operations for field enumerator of union IDENTIFIER */

#pragma token EXP const : unsigned : id_enumerator_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_enumerator #
#pragma interface id_enumerator_tag IS_id_enumerator

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_enumerator_etype #
#pragma interface id_enumerator_etype

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_enumerator_value #
#pragma interface id_enumerator_value

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_enumerator #
#pragma interface MAKE_id_enumerator

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_enumerator #
#pragma interface DECONS_id_enumerator

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_enumerator #
#pragma interface DESTROY_id_enumerator


/* Operations for field label of union IDENTIFIER */

#pragma token EXP const : unsigned : id_label_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_label #
#pragma interface id_label_tag IS_id_label

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( int ) : id_label_op #
#pragma interface id_label_op

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_label_stmt #
#pragma interface id_label_stmt

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( EXP ) : id_label_gotos #
#pragma interface id_label_gotos

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( LIST ( VARIABLE ) ) : id_label_vars #
#pragma interface id_label_vars

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : int :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_label #
#pragma interface MAKE_id_label

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : int :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : LIST ( VARIABLE ) :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_label #
#pragma interface DECONS_id_label

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : int :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : LIST ( VARIABLE ) :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_label #
#pragma interface DESTROY_id_label


/* Operations for field token of union IDENTIFIER */

#pragma token EXP const : unsigned : id_token_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_token #
#pragma interface id_token_tag IS_id_token

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TOKEN ) : id_token_sort #
#pragma interface id_token_sort

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( IDENTIFIER ) : id_token_alt #
#pragma interface id_token_alt

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : TOKEN :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_token #
#pragma interface MAKE_id_token

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TOKEN :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_token #
#pragma interface DECONS_id_token

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TOKEN :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_token #
#pragma interface DESTROY_id_token


/* Operations for field ambig of union IDENTIFIER */

#pragma token EXP const : unsigned : id_ambig_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_ambig #
#pragma interface id_ambig_tag IS_id_ambig

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( LIST ( IDENTIFIER ) ) : id_ambig_ids #
#pragma interface id_ambig_ids

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( int ) : id_ambig_over #
#pragma interface id_ambig_over

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : LIST ( IDENTIFIER ) :,\
	EXP : int :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_ambig #
#pragma interface MAKE_id_ambig

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : LIST ( IDENTIFIER ) :,\
	EXP lvalue : int :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_ambig #
#pragma interface DECONS_id_ambig

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : LIST ( IDENTIFIER ) :,\
	EXP lvalue : int :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_ambig #
#pragma interface DESTROY_id_ambig


/* Operations for field undef of union IDENTIFIER */

#pragma token EXP const : unsigned : id_undef_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_undef #
#pragma interface id_undef_tag IS_id_undef

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_undef_form #
#pragma interface id_undef_form

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_undef #
#pragma interface MAKE_id_undef

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_undef #
#pragma interface DECONS_id_undef

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_undef #
#pragma interface DESTROY_id_undef


/* Operations for field pending of union IDENTIFIER */

#pragma token EXP const : unsigned : id_pending_tag #
#pragma token PROC ( EXP : IDENTIFIER : ) EXP : int : IS_id_pending #
#pragma interface id_pending_tag IS_id_pending

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( unsigned ) : id_pending_itag #
#pragma interface id_pending_itag

#pragma token PROC ( EXP : IDENTIFIER : )\
    EXP : PTR ( TYPE ) : id_pending_type #
#pragma interface id_pending_type

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : DECL_SPEC :,\
	EXP : NAMESPACE :,\
	EXP : LOCATION :,\
	EXP : unsigned :,\
	EXP : TYPE :,\
	EXP lvalue : IDENTIFIER :\
    ) STATEMENT MAKE_id_pending #
#pragma interface MAKE_id_pending

#pragma token PROC (\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DECONS_id_pending #
#pragma interface DECONS_id_pending

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : DECL_SPEC :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : TYPE :,\
	EXP : IDENTIFIER :\
    ) STATEMENT DESTROY_id_pending #
#pragma interface DESTROY_id_pending


#endif
