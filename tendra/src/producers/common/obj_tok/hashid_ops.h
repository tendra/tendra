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

#ifndef HASHID_OPS_H_INCLUDED
#define HASHID_OPS_H_INCLUDED

/* Operations for union HASHID */

#pragma token PROC ( EXP : HASHID : ) EXP : unsigned : TAG_hashid #
#pragma interface TAG_hashid


/* Operations for component id of union HASHID */

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( IDENTIFIER ) : hashid_id #
#pragma interface hashid_id

/* Operations for component cache of union HASHID */

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( IDENTIFIER ) : hashid_cache #
#pragma interface hashid_cache

/* Operations for component next of union HASHID */

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( HASHID ) : hashid_next #
#pragma interface hashid_next

/* Operations for component hash of union HASHID */

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( ulong_type ) : hashid_hash #
#pragma interface hashid_hash

/* Operations for field set name_etc of union HASHID */

#pragma token EXP const : unsigned : hashid_name_etc_tag #
#pragma token PROC ( EXP : HASHID : ) EXP : int : IS_hashid_name_etc #
#pragma interface hashid_name_etc_tag IS_hashid_name_etc

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( string ) : hashid_name_etc_text #
#pragma interface hashid_name_etc_text

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : HASHID :,\
	EXP : ulong_type :,\
	EXP : string :,\
	EXP lvalue : HASHID :\
    ) STATEMENT MAKE_hashid_name_etc #
#pragma interface MAKE_hashid_name_etc

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : HASHID :\
    ) STATEMENT MODIFY_hashid_name_etc #
#pragma interface MODIFY_hashid_name_etc

#pragma token PROC (\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP : HASHID :\
    ) STATEMENT DECONS_hashid_name_etc #
#pragma interface DECONS_hashid_name_etc

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP : HASHID :\
    ) STATEMENT DESTROY_hashid_name_etc #
#pragma interface DESTROY_hashid_name_etc


/* Operations for field name of union HASHID */

#pragma token EXP const : unsigned : hashid_name_tag #
#pragma token PROC ( EXP : HASHID : ) EXP : int : IS_hashid_name #
#pragma interface hashid_name_tag IS_hashid_name

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( string ) : hashid_name_text #
#pragma interface hashid_name_text

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : ulong_type :,\
	EXP : string :,\
	EXP lvalue : HASHID :\
    ) STATEMENT MAKE_hashid_name #
#pragma interface MAKE_hashid_name

#pragma token PROC (\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP : HASHID :\
    ) STATEMENT DECONS_hashid_name #
#pragma interface DECONS_hashid_name

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP : HASHID :\
    ) STATEMENT DESTROY_hashid_name #
#pragma interface DESTROY_hashid_name


/* Operations for field ename of union HASHID */

#pragma token EXP const : unsigned : hashid_ename_tag #
#pragma token PROC ( EXP : HASHID : ) EXP : int : IS_hashid_ename #
#pragma interface hashid_ename_tag IS_hashid_ename

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( string ) : hashid_ename_text #
#pragma interface hashid_ename_text

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : ulong_type :,\
	EXP : string :,\
	EXP lvalue : HASHID :\
    ) STATEMENT MAKE_hashid_ename #
#pragma interface MAKE_hashid_ename

#pragma token PROC (\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP : HASHID :\
    ) STATEMENT DECONS_hashid_ename #
#pragma interface DECONS_hashid_ename

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : string :,\
	EXP : HASHID :\
    ) STATEMENT DESTROY_hashid_ename #
#pragma interface DESTROY_hashid_ename


/* Operations for field set constr_etc of union HASHID */

#pragma token EXP const : unsigned : hashid_constr_etc_tag #
#pragma token PROC ( EXP : HASHID : ) EXP : int : IS_hashid_constr_etc #
#pragma interface hashid_constr_etc_tag IS_hashid_constr_etc

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( TYPE ) : hashid_constr_etc_type #
#pragma interface hashid_constr_etc_type

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( IDENTIFIER ) : hashid_constr_etc_tid #
#pragma interface hashid_constr_etc_tid

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : HASHID :,\
	EXP : ulong_type :,\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : HASHID :\
    ) STATEMENT MAKE_hashid_constr_etc #
#pragma interface MAKE_hashid_constr_etc

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : HASHID :\
    ) STATEMENT MODIFY_hashid_constr_etc #
#pragma interface MODIFY_hashid_constr_etc

#pragma token PROC (\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : HASHID :\
    ) STATEMENT DECONS_hashid_constr_etc #
#pragma interface DECONS_hashid_constr_etc

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : HASHID :\
    ) STATEMENT DESTROY_hashid_constr_etc #
#pragma interface DESTROY_hashid_constr_etc


/* Operations for field constr of union HASHID */

#pragma token EXP const : unsigned : hashid_constr_tag #
#pragma token PROC ( EXP : HASHID : ) EXP : int : IS_hashid_constr #
#pragma interface hashid_constr_tag IS_hashid_constr

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( TYPE ) : hashid_constr_type #
#pragma interface hashid_constr_type

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( IDENTIFIER ) : hashid_constr_tid #
#pragma interface hashid_constr_tid

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : ulong_type :,\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : HASHID :\
    ) STATEMENT MAKE_hashid_constr #
#pragma interface MAKE_hashid_constr

#pragma token PROC (\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : HASHID :\
    ) STATEMENT DECONS_hashid_constr #
#pragma interface DECONS_hashid_constr

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : HASHID :\
    ) STATEMENT DESTROY_hashid_constr #
#pragma interface DESTROY_hashid_constr


/* Operations for field destr of union HASHID */

#pragma token EXP const : unsigned : hashid_destr_tag #
#pragma token PROC ( EXP : HASHID : ) EXP : int : IS_hashid_destr #
#pragma interface hashid_destr_tag IS_hashid_destr

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( TYPE ) : hashid_destr_type #
#pragma interface hashid_destr_type

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( IDENTIFIER ) : hashid_destr_tid #
#pragma interface hashid_destr_tid

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : ulong_type :,\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : HASHID :\
    ) STATEMENT MAKE_hashid_destr #
#pragma interface MAKE_hashid_destr

#pragma token PROC (\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : HASHID :\
    ) STATEMENT DECONS_hashid_destr #
#pragma interface DECONS_hashid_destr

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : HASHID :\
    ) STATEMENT DESTROY_hashid_destr #
#pragma interface DESTROY_hashid_destr


/* Operations for field conv of union HASHID */

#pragma token EXP const : unsigned : hashid_conv_tag #
#pragma token PROC ( EXP : HASHID : ) EXP : int : IS_hashid_conv #
#pragma interface hashid_conv_tag IS_hashid_conv

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( TYPE ) : hashid_conv_type #
#pragma interface hashid_conv_type

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( IDENTIFIER ) : hashid_conv_tid #
#pragma interface hashid_conv_tid

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : ulong_type :,\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : HASHID :\
    ) STATEMENT MAKE_hashid_conv #
#pragma interface MAKE_hashid_conv

#pragma token PROC (\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : HASHID :\
    ) STATEMENT DECONS_hashid_conv #
#pragma interface DECONS_hashid_conv

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : HASHID :\
    ) STATEMENT DESTROY_hashid_conv #
#pragma interface DESTROY_hashid_conv


/* Operations for field op of union HASHID */

#pragma token EXP const : unsigned : hashid_op_tag #
#pragma token PROC ( EXP : HASHID : ) EXP : int : IS_hashid_op #
#pragma interface hashid_op_tag IS_hashid_op

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( int ) : hashid_op_lex #
#pragma interface hashid_op_lex

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : ulong_type :,\
	EXP : int :,\
	EXP lvalue : HASHID :\
    ) STATEMENT MAKE_hashid_op #
#pragma interface MAKE_hashid_op

#pragma token PROC (\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : int :,\
	EXP : HASHID :\
    ) STATEMENT DECONS_hashid_op #
#pragma interface DECONS_hashid_op

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : int :,\
	EXP : HASHID :\
    ) STATEMENT DESTROY_hashid_op #
#pragma interface DESTROY_hashid_op


/* Operations for field anon of union HASHID */

#pragma token EXP const : unsigned : hashid_anon_tag #
#pragma token PROC ( EXP : HASHID : ) EXP : int : IS_hashid_anon #
#pragma interface hashid_anon_tag IS_hashid_anon

#pragma token PROC ( EXP : HASHID : )\
    EXP : PTR ( ulong_type ) : hashid_anon_uniq #
#pragma interface hashid_anon_uniq

#pragma token PROC (\
	EXP : HASHID :,\
	EXP : ulong_type :,\
	EXP : ulong_type :,\
	EXP lvalue : HASHID :\
    ) STATEMENT MAKE_hashid_anon #
#pragma interface MAKE_hashid_anon

#pragma token PROC (\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : HASHID :\
    ) STATEMENT DECONS_hashid_anon #
#pragma interface DECONS_hashid_anon

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : HASHID :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP : HASHID :\
    ) STATEMENT DESTROY_hashid_anon #
#pragma interface DESTROY_hashid_anon


#endif
