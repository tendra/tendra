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

#ifndef NSPACE_OPS_H_INCLUDED
#define NSPACE_OPS_H_INCLUDED

/* Operations for union NAMESPACE */

#pragma token PROC(EXP : NAMESPACE :) EXP : unsigned : TAG_nspace #
#pragma interface TAG_nspace


/* Operations for component name of union NAMESPACE */

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(IDENTIFIER) : nspace_name #
#pragma interface nspace_name

/* Operations for component last of union NAMESPACE */

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(MEMBER) : nspace_last #
#pragma interface nspace_last

/* Operations for component prev of union NAMESPACE */

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(MEMBER) : nspace_prev #
#pragma interface nspace_prev

/* Operations for component parent of union NAMESPACE */

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(NAMESPACE) : nspace_parent #
#pragma interface nspace_parent

/* Operations for component use of union NAMESPACE */

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(LIST(NAMESPACE)) : nspace_use #
#pragma interface nspace_use

/* Operations for component join of union NAMESPACE */

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(LIST(NAMESPACE)) : nspace_join #
#pragma interface nspace_join

/* Operations for component set of union NAMESPACE */

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(STACK(IDENTIFIER)) : nspace_set #
#pragma interface nspace_set

/* Operations for component dump of union NAMESPACE */

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(ulong_type) : nspace_dump #
#pragma interface nspace_dump

/* Operations for field set block_etc of union NAMESPACE */

#pragma token EXP const : unsigned : nspace_block_etc_tag #
#pragma token PROC(EXP : NAMESPACE :) EXP : int : IS_nspace_block_etc #
#pragma interface nspace_block_etc_tag IS_nspace_block_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : IDENTIFIER :,\
	EXP : NAMESPACE :,\
	EXP lvalue : NAMESPACE :\
    ) STATEMENT MAKE_nspace_block_etc #
#pragma interface MAKE_nspace_block_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : NAMESPACE :\
    ) STATEMENT MODIFY_nspace_block_etc #
#pragma interface MODIFY_nspace_block_etc

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP : NAMESPACE :\
    ) STATEMENT DECONS_nspace_block_etc #
#pragma interface DECONS_nspace_block_etc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP : NAMESPACE :\
    ) STATEMENT DESTROY_nspace_block_etc #
#pragma interface DESTROY_nspace_block_etc


/* Operations for field block of union NAMESPACE */

#pragma token EXP const : unsigned : nspace_block_tag #
#pragma token PROC(EXP : NAMESPACE :) EXP : int : IS_nspace_block #
#pragma interface nspace_block_tag IS_nspace_block

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : NAMESPACE :,\
	EXP lvalue : NAMESPACE :\
    ) STATEMENT MAKE_nspace_block #
#pragma interface MAKE_nspace_block

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP : NAMESPACE :\
    ) STATEMENT DECONS_nspace_block #
#pragma interface DECONS_nspace_block

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP : NAMESPACE :\
    ) STATEMENT DESTROY_nspace_block #
#pragma interface DESTROY_nspace_block


/* Operations for field param of union NAMESPACE */

#pragma token EXP const : unsigned : nspace_param_tag #
#pragma token PROC(EXP : NAMESPACE :) EXP : int : IS_nspace_param #
#pragma interface nspace_param_tag IS_nspace_param

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : NAMESPACE :,\
	EXP lvalue : NAMESPACE :\
    ) STATEMENT MAKE_nspace_param #
#pragma interface MAKE_nspace_param

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP : NAMESPACE :\
    ) STATEMENT DECONS_nspace_param #
#pragma interface DECONS_nspace_param

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP : NAMESPACE :\
    ) STATEMENT DESTROY_nspace_param #
#pragma interface DESTROY_nspace_param


/* Operations for field dummy of union NAMESPACE */

#pragma token EXP const : unsigned : nspace_dummy_tag #
#pragma token PROC(EXP : NAMESPACE :) EXP : int : IS_nspace_dummy #
#pragma interface nspace_dummy_tag IS_nspace_dummy

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : NAMESPACE :,\
	EXP lvalue : NAMESPACE :\
    ) STATEMENT MAKE_nspace_dummy #
#pragma interface MAKE_nspace_dummy

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP : NAMESPACE :\
    ) STATEMENT DECONS_nspace_dummy #
#pragma interface DECONS_nspace_dummy

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP : NAMESPACE :\
    ) STATEMENT DESTROY_nspace_dummy #
#pragma interface DESTROY_nspace_dummy


/* Operations for field label of union NAMESPACE */

#pragma token EXP const : unsigned : nspace_label_tag #
#pragma token PROC(EXP : NAMESPACE :) EXP : int : IS_nspace_label #
#pragma interface nspace_label_tag IS_nspace_label

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : NAMESPACE :,\
	EXP lvalue : NAMESPACE :\
    ) STATEMENT MAKE_nspace_label #
#pragma interface MAKE_nspace_label

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP : NAMESPACE :\
    ) STATEMENT DECONS_nspace_label #
#pragma interface DECONS_nspace_label

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP : NAMESPACE :\
    ) STATEMENT DESTROY_nspace_label #
#pragma interface DESTROY_nspace_label


/* Operations for field templ of union NAMESPACE */

#pragma token EXP const : unsigned : nspace_templ_tag #
#pragma token PROC(EXP : NAMESPACE :) EXP : int : IS_nspace_templ #
#pragma interface nspace_templ_tag IS_nspace_templ

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : NAMESPACE :,\
	EXP lvalue : NAMESPACE :\
    ) STATEMENT MAKE_nspace_templ #
#pragma interface MAKE_nspace_templ

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP : NAMESPACE :\
    ) STATEMENT DECONS_nspace_templ #
#pragma interface DECONS_nspace_templ

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP : NAMESPACE :\
    ) STATEMENT DESTROY_nspace_templ #
#pragma interface DESTROY_nspace_templ


/* Operations for field set named_etc of union NAMESPACE */

#pragma token EXP const : unsigned : nspace_named_etc_tag #
#pragma token PROC(EXP : NAMESPACE :) EXP : int : IS_nspace_named_etc #
#pragma interface nspace_named_etc_tag IS_nspace_named_etc

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(MEMBER) : nspace_named_etc_first #
#pragma interface nspace_named_etc_first

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(LIST(IDENTIFIER)) : nspace_named_etc_extra #
#pragma interface nspace_named_etc_extra

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(ulong_type) : nspace_named_etc_size #
#pragma interface nspace_named_etc_size

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(PTR(MEMBER)) : nspace_named_etc_table #
#pragma interface nspace_named_etc_table

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : IDENTIFIER :,\
	EXP : NAMESPACE :,\
	EXP : ulong_type :,\
	EXP : PTR(MEMBER) :,\
	EXP lvalue : NAMESPACE :\
    ) STATEMENT MAKE_nspace_named_etc #
#pragma interface MAKE_nspace_named_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : NAMESPACE :\
    ) STATEMENT MODIFY_nspace_named_etc #
#pragma interface MODIFY_nspace_named_etc

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : PTR(MEMBER) :,\
	EXP : NAMESPACE :\
    ) STATEMENT DECONS_nspace_named_etc #
#pragma interface DECONS_nspace_named_etc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : PTR(MEMBER) :,\
	EXP : NAMESPACE :\
    ) STATEMENT DESTROY_nspace_named_etc #
#pragma interface DESTROY_nspace_named_etc


/* Operations for field named of union NAMESPACE */

#pragma token EXP const : unsigned : nspace_named_tag #
#pragma token PROC(EXP : NAMESPACE :) EXP : int : IS_nspace_named #
#pragma interface nspace_named_tag IS_nspace_named

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(MEMBER) : nspace_named_first #
#pragma interface nspace_named_first

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(LIST(IDENTIFIER)) : nspace_named_extra #
#pragma interface nspace_named_extra

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(ulong_type) : nspace_named_size #
#pragma interface nspace_named_size

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(PTR(MEMBER)) : nspace_named_table #
#pragma interface nspace_named_table

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : NAMESPACE :,\
	EXP : ulong_type :,\
	EXP : PTR(MEMBER) :,\
	EXP lvalue : NAMESPACE :\
    ) STATEMENT MAKE_nspace_named #
#pragma interface MAKE_nspace_named

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : PTR(MEMBER) :,\
	EXP : NAMESPACE :\
    ) STATEMENT DECONS_nspace_named #
#pragma interface DECONS_nspace_named

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : PTR(MEMBER) :,\
	EXP : NAMESPACE :\
    ) STATEMENT DESTROY_nspace_named #
#pragma interface DESTROY_nspace_named


/* Operations for field unnamed of union NAMESPACE */

#pragma token EXP const : unsigned : nspace_unnamed_tag #
#pragma token PROC(EXP : NAMESPACE :) EXP : int : IS_nspace_unnamed #
#pragma interface nspace_unnamed_tag IS_nspace_unnamed

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(MEMBER) : nspace_unnamed_first #
#pragma interface nspace_unnamed_first

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(LIST(IDENTIFIER)) : nspace_unnamed_extra #
#pragma interface nspace_unnamed_extra

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(ulong_type) : nspace_unnamed_size #
#pragma interface nspace_unnamed_size

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(PTR(MEMBER)) : nspace_unnamed_table #
#pragma interface nspace_unnamed_table

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : NAMESPACE :,\
	EXP : ulong_type :,\
	EXP : PTR(MEMBER) :,\
	EXP lvalue : NAMESPACE :\
    ) STATEMENT MAKE_nspace_unnamed #
#pragma interface MAKE_nspace_unnamed

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : PTR(MEMBER) :,\
	EXP : NAMESPACE :\
    ) STATEMENT DECONS_nspace_unnamed #
#pragma interface DECONS_nspace_unnamed

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : PTR(MEMBER) :,\
	EXP : NAMESPACE :\
    ) STATEMENT DESTROY_nspace_unnamed #
#pragma interface DESTROY_nspace_unnamed


/* Operations for field global of union NAMESPACE */

#pragma token EXP const : unsigned : nspace_global_tag #
#pragma token PROC(EXP : NAMESPACE :) EXP : int : IS_nspace_global #
#pragma interface nspace_global_tag IS_nspace_global

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(MEMBER) : nspace_global_first #
#pragma interface nspace_global_first

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(LIST(IDENTIFIER)) : nspace_global_extra #
#pragma interface nspace_global_extra

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(ulong_type) : nspace_global_size #
#pragma interface nspace_global_size

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(PTR(MEMBER)) : nspace_global_table #
#pragma interface nspace_global_table

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : NAMESPACE :,\
	EXP : ulong_type :,\
	EXP : PTR(MEMBER) :,\
	EXP lvalue : NAMESPACE :\
    ) STATEMENT MAKE_nspace_global #
#pragma interface MAKE_nspace_global

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : PTR(MEMBER) :,\
	EXP : NAMESPACE :\
    ) STATEMENT DECONS_nspace_global #
#pragma interface DECONS_nspace_global

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : PTR(MEMBER) :,\
	EXP : NAMESPACE :\
    ) STATEMENT DESTROY_nspace_global #
#pragma interface DESTROY_nspace_global


/* Operations for field ctype of union NAMESPACE */

#pragma token EXP const : unsigned : nspace_ctype_tag #
#pragma token PROC(EXP : NAMESPACE :) EXP : int : IS_nspace_ctype #
#pragma interface nspace_ctype_tag IS_nspace_ctype

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(MEMBER) : nspace_ctype_first #
#pragma interface nspace_ctype_first

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(LIST(IDENTIFIER)) : nspace_ctype_extra #
#pragma interface nspace_ctype_extra

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(ulong_type) : nspace_ctype_size #
#pragma interface nspace_ctype_size

#pragma token PROC(EXP : NAMESPACE :)\
    EXP : PTR(PTR(MEMBER)) : nspace_ctype_table #
#pragma interface nspace_ctype_table

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : NAMESPACE :,\
	EXP : ulong_type :,\
	EXP : PTR(MEMBER) :,\
	EXP lvalue : NAMESPACE :\
    ) STATEMENT MAKE_nspace_ctype #
#pragma interface MAKE_nspace_ctype

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : PTR(MEMBER) :,\
	EXP : NAMESPACE :\
    ) STATEMENT DECONS_nspace_ctype #
#pragma interface DECONS_nspace_ctype

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : LIST(NAMESPACE) :,\
	EXP lvalue : STACK(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : MEMBER :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : PTR(MEMBER) :,\
	EXP : NAMESPACE :\
    ) STATEMENT DESTROY_nspace_ctype #
#pragma interface DESTROY_nspace_ctype


#endif
