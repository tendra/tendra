/*
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef INFO_OPS_H_INCLUDED
#define INFO_OPS_H_INCLUDED

/* Operations for union SORT_INFO */

#pragma token PROC(EXP : SORT_INFO :) EXP : unsigned : TAG_info #
#pragma interface TAG_info


/* Operations for component name of union SORT_INFO */

#pragma token PROC(EXP : SORT_INFO :)\
    EXP : PTR(string) : info_name #
#pragma interface info_name

/* Operations for field builtin of union SORT_INFO */

#pragma token EXP const : unsigned : info_builtin_tag #
#pragma token PROC(EXP : SORT_INFO :) EXP : int : IS_info_builtin #
#pragma interface info_builtin_tag IS_info_builtin

#pragma token PROC(\
	EXP : string :,\
	EXP lvalue : SORT_INFO :\
    ) STATEMENT MAKE_info_builtin #
#pragma interface MAKE_info_builtin

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP : SORT_INFO :\
    ) STATEMENT DECONS_info_builtin #
#pragma interface DECONS_info_builtin

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP : SORT_INFO :\
    ) STATEMENT DESTROY_info_builtin #
#pragma interface DESTROY_info_builtin


/* Operations for field basic of union SORT_INFO */

#pragma token EXP const : unsigned : info_basic_tag #
#pragma token PROC(EXP : SORT_INFO :) EXP : int : IS_info_basic #
#pragma interface info_basic_tag IS_info_basic

#pragma token PROC(EXP : SORT_INFO :)\
    EXP : PTR(unsigned) : info_basic_bits #
#pragma interface info_basic_bits

#pragma token PROC(EXP : SORT_INFO :)\
    EXP : PTR(unsigned) : info_basic_extend #
#pragma interface info_basic_extend

#pragma token PROC(EXP : SORT_INFO :)\
    EXP : PTR(unsigned) : info_basic_max #
#pragma interface info_basic_max

#pragma token PROC(EXP : SORT_INFO :)\
    EXP : PTR(LIST(CONSTRUCT)) : info_basic_cons #
#pragma interface info_basic_cons

#pragma token PROC(EXP : SORT_INFO :)\
    EXP : PTR(CONSTRUCT) : info_basic_sortname #
#pragma interface info_basic_sortname

#pragma token PROC(\
	EXP : string :,\
	EXP : unsigned :,\
	EXP : unsigned :,\
	EXP : unsigned :,\
	EXP : LIST(CONSTRUCT) :,\
	EXP : CONSTRUCT :,\
	EXP lvalue : SORT_INFO :\
    ) STATEMENT MAKE_info_basic #
#pragma interface MAKE_info_basic

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : LIST(CONSTRUCT) :,\
	EXP lvalue : CONSTRUCT :,\
	EXP : SORT_INFO :\
    ) STATEMENT DECONS_info_basic #
#pragma interface DECONS_info_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : LIST(CONSTRUCT) :,\
	EXP lvalue : CONSTRUCT :,\
	EXP : SORT_INFO :\
    ) STATEMENT DESTROY_info_basic #
#pragma interface DESTROY_info_basic


/* Operations for field dummy of union SORT_INFO */

#pragma token EXP const : unsigned : info_dummy_tag #
#pragma token PROC(EXP : SORT_INFO :) EXP : int : IS_info_dummy #
#pragma interface info_dummy_tag IS_info_dummy

#pragma token PROC(EXP : SORT_INFO :)\
    EXP : PTR(CONSTRUCT) : info_dummy_cons #
#pragma interface info_dummy_cons

#pragma token PROC(\
	EXP : string :,\
	EXP : CONSTRUCT :,\
	EXP lvalue : SORT_INFO :\
    ) STATEMENT MAKE_info_dummy #
#pragma interface MAKE_info_dummy

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP lvalue : CONSTRUCT :,\
	EXP : SORT_INFO :\
    ) STATEMENT DECONS_info_dummy #
#pragma interface DECONS_info_dummy

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : CONSTRUCT :,\
	EXP : SORT_INFO :\
    ) STATEMENT DESTROY_info_dummy #
#pragma interface DESTROY_info_dummy


/* Operations for field set clist_etc of union SORT_INFO */

#pragma token EXP const : unsigned : info_clist_etc_tag #
#pragma token PROC(EXP : SORT_INFO :) EXP : int : IS_info_clist_etc #
#pragma interface info_clist_etc_tag IS_info_clist_etc

#pragma token PROC(EXP : SORT_INFO :)\
    EXP : PTR(SORT) : info_clist_etc_arg #
#pragma interface info_clist_etc_arg

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : string :,\
	EXP : SORT :,\
	EXP lvalue : SORT_INFO :\
    ) STATEMENT MAKE_info_clist_etc #
#pragma interface MAKE_info_clist_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : SORT_INFO :\
    ) STATEMENT MODIFY_info_clist_etc #
#pragma interface MODIFY_info_clist_etc

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP lvalue : SORT :,\
	EXP : SORT_INFO :\
    ) STATEMENT DECONS_info_clist_etc #
#pragma interface DECONS_info_clist_etc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : SORT :,\
	EXP : SORT_INFO :\
    ) STATEMENT DESTROY_info_clist_etc #
#pragma interface DESTROY_info_clist_etc


/* Operations for field clist of union SORT_INFO */

#pragma token EXP const : unsigned : info_clist_tag #
#pragma token PROC(EXP : SORT_INFO :) EXP : int : IS_info_clist #
#pragma interface info_clist_tag IS_info_clist

#pragma token PROC(EXP : SORT_INFO :)\
    EXP : PTR(SORT) : info_clist_arg #
#pragma interface info_clist_arg

#pragma token PROC(\
	EXP : string :,\
	EXP : SORT :,\
	EXP lvalue : SORT_INFO :\
    ) STATEMENT MAKE_info_clist #
#pragma interface MAKE_info_clist

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP lvalue : SORT :,\
	EXP : SORT_INFO :\
    ) STATEMENT DECONS_info_clist #
#pragma interface DECONS_info_clist

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : SORT :,\
	EXP : SORT_INFO :\
    ) STATEMENT DESTROY_info_clist #
#pragma interface DESTROY_info_clist


/* Operations for field slist of union SORT_INFO */

#pragma token EXP const : unsigned : info_slist_tag #
#pragma token PROC(EXP : SORT_INFO :) EXP : int : IS_info_slist #
#pragma interface info_slist_tag IS_info_slist

#pragma token PROC(EXP : SORT_INFO :)\
    EXP : PTR(SORT) : info_slist_arg #
#pragma interface info_slist_arg

#pragma token PROC(\
	EXP : string :,\
	EXP : SORT :,\
	EXP lvalue : SORT_INFO :\
    ) STATEMENT MAKE_info_slist #
#pragma interface MAKE_info_slist

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP lvalue : SORT :,\
	EXP : SORT_INFO :\
    ) STATEMENT DECONS_info_slist #
#pragma interface DECONS_info_slist

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : SORT :,\
	EXP : SORT_INFO :\
    ) STATEMENT DESTROY_info_slist #
#pragma interface DESTROY_info_slist


/* Operations for field option of union SORT_INFO */

#pragma token EXP const : unsigned : info_option_tag #
#pragma token PROC(EXP : SORT_INFO :) EXP : int : IS_info_option #
#pragma interface info_option_tag IS_info_option

#pragma token PROC(EXP : SORT_INFO :)\
    EXP : PTR(SORT) : info_option_arg #
#pragma interface info_option_arg

#pragma token PROC(\
	EXP : string :,\
	EXP : SORT :,\
	EXP lvalue : SORT_INFO :\
    ) STATEMENT MAKE_info_option #
#pragma interface MAKE_info_option

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP lvalue : SORT :,\
	EXP : SORT_INFO :\
    ) STATEMENT DECONS_info_option #
#pragma interface DECONS_info_option

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : SORT :,\
	EXP : SORT_INFO :\
    ) STATEMENT DESTROY_info_option #
#pragma interface DESTROY_info_option


#endif
