/*
    AUTOMATICALLY GENERATED FROM ALGEBRA calculus (VERSION 1.2)
    BY calculus (VERSION 1.3)
*/

#ifndef TYPE_OPS_H_INCLUDED
#define TYPE_OPS_H_INCLUDED

/* Operations for union TYPE */

#pragma token PROC(EXP : TYPE :) EXP : unsigned : TAG_type #
#pragma interface TAG_type


/* Operations for component size of union TYPE */

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(zero_int) : type_size #
#pragma interface type_size

/* Operations for field primitive of union TYPE */

#pragma token EXP const : unsigned : type_primitive_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_primitive #
#pragma interface type_primitive_tag IS_type_primitive

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(PRIMITIVE_P) : type_primitive_prim #
#pragma interface type_primitive_prim

#pragma token PROC(\
	EXP : zero_int :,\
	EXP : PRIMITIVE_P :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_primitive #
#pragma interface MAKE_type_primitive

#pragma token PROC(\
	EXP lvalue : zero_int :,\
	EXP lvalue : PRIMITIVE_P :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_primitive #
#pragma interface DECONS_type_primitive

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : zero_int :,\
	EXP lvalue : PRIMITIVE_P :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_primitive #
#pragma interface DESTROY_type_primitive

#ifdef calculus_IO_ROUTINES

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : unsigned :\
    ) STATEMENT NEW_ALIAS_type_primitive #
#pragma interface NEW_ALIAS_type_primitive

#pragma token PROC(EXP : TYPE :)\
    EXP : unsigned : GET_ALIAS_type_primitive #
#pragma token PROC(EXP : TYPE :, EXP : unsigned :)\
    EXP : void : SET_ALIAS_type_primitive #
#pragma token PROC(EXP : unsigned :)\
    EXP : TYPE : FIND_ALIAS_type_primitive #

#pragma interface GET_ALIAS_type_primitive SET_ALIAS_type_primitive FIND_ALIAS_type_primitive

#endif


/* Operations for field ident of union TYPE */

#pragma token EXP const : unsigned : type_ident_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_ident #
#pragma interface type_ident_tag IS_type_ident

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(IDENTITY_P) : type_ident_id #
#pragma interface type_ident_id

#pragma token PROC(\
	EXP : zero_int :,\
	EXP : IDENTITY_P :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_ident #
#pragma interface MAKE_type_ident

#pragma token PROC(\
	EXP lvalue : zero_int :,\
	EXP lvalue : IDENTITY_P :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_ident #
#pragma interface DECONS_type_ident

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : zero_int :,\
	EXP lvalue : IDENTITY_P :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_ident #
#pragma interface DESTROY_type_ident

#ifdef calculus_IO_ROUTINES

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : unsigned :\
    ) STATEMENT NEW_ALIAS_type_ident #
#pragma interface NEW_ALIAS_type_ident

#pragma token PROC(EXP : TYPE :)\
    EXP : unsigned : GET_ALIAS_type_ident #
#pragma token PROC(EXP : TYPE :, EXP : unsigned :)\
    EXP : void : SET_ALIAS_type_ident #
#pragma token PROC(EXP : unsigned :)\
    EXP : TYPE : FIND_ALIAS_type_ident #

#pragma interface GET_ALIAS_type_ident SET_ALIAS_type_ident FIND_ALIAS_type_ident

#endif


/* Operations for field enumeration of union TYPE */

#pragma token EXP const : unsigned : type_enumeration_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_enumeration #
#pragma interface type_enumeration_tag IS_type_enumeration

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(ENUM_P) : type_enumeration_en #
#pragma interface type_enumeration_en

#pragma token PROC(\
	EXP : zero_int :,\
	EXP : ENUM_P :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_enumeration #
#pragma interface MAKE_type_enumeration

#pragma token PROC(\
	EXP lvalue : zero_int :,\
	EXP lvalue : ENUM_P :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_enumeration #
#pragma interface DECONS_type_enumeration

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : zero_int :,\
	EXP lvalue : ENUM_P :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_enumeration #
#pragma interface DESTROY_type_enumeration

#ifdef calculus_IO_ROUTINES

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : unsigned :\
    ) STATEMENT NEW_ALIAS_type_enumeration #
#pragma interface NEW_ALIAS_type_enumeration

#pragma token PROC(EXP : TYPE :)\
    EXP : unsigned : GET_ALIAS_type_enumeration #
#pragma token PROC(EXP : TYPE :, EXP : unsigned :)\
    EXP : void : SET_ALIAS_type_enumeration #
#pragma token PROC(EXP : unsigned :)\
    EXP : TYPE : FIND_ALIAS_type_enumeration #

#pragma interface GET_ALIAS_type_enumeration SET_ALIAS_type_enumeration FIND_ALIAS_type_enumeration

#endif


/* Operations for field structure of union TYPE */

#pragma token EXP const : unsigned : type_structure_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_structure #
#pragma interface type_structure_tag IS_type_structure

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(STRUCTURE_P) : type_structure_struc #
#pragma interface type_structure_struc

#pragma token PROC(\
	EXP : zero_int :,\
	EXP : STRUCTURE_P :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_structure #
#pragma interface MAKE_type_structure

#pragma token PROC(\
	EXP lvalue : zero_int :,\
	EXP lvalue : STRUCTURE_P :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_structure #
#pragma interface DECONS_type_structure

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : zero_int :,\
	EXP lvalue : STRUCTURE_P :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_structure #
#pragma interface DESTROY_type_structure

#ifdef calculus_IO_ROUTINES

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : unsigned :\
    ) STATEMENT NEW_ALIAS_type_structure #
#pragma interface NEW_ALIAS_type_structure

#pragma token PROC(EXP : TYPE :)\
    EXP : unsigned : GET_ALIAS_type_structure #
#pragma token PROC(EXP : TYPE :, EXP : unsigned :)\
    EXP : void : SET_ALIAS_type_structure #
#pragma token PROC(EXP : unsigned :)\
    EXP : TYPE : FIND_ALIAS_type_structure #

#pragma interface GET_ALIAS_type_structure SET_ALIAS_type_structure FIND_ALIAS_type_structure

#endif


/* Operations for field onion of union TYPE */

#pragma token EXP const : unsigned : type_onion_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_onion #
#pragma interface type_onion_tag IS_type_onion

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(UNION_P) : type_onion_un #
#pragma interface type_onion_un

#pragma token PROC(\
	EXP : zero_int :,\
	EXP : UNION_P :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_onion #
#pragma interface MAKE_type_onion

#pragma token PROC(\
	EXP lvalue : zero_int :,\
	EXP lvalue : UNION_P :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_onion #
#pragma interface DECONS_type_onion

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : zero_int :,\
	EXP lvalue : UNION_P :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_onion #
#pragma interface DESTROY_type_onion

#ifdef calculus_IO_ROUTINES

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : unsigned :\
    ) STATEMENT NEW_ALIAS_type_onion #
#pragma interface NEW_ALIAS_type_onion

#pragma token PROC(EXP : TYPE :)\
    EXP : unsigned : GET_ALIAS_type_onion #
#pragma token PROC(EXP : TYPE :, EXP : unsigned :)\
    EXP : void : SET_ALIAS_type_onion #
#pragma token PROC(EXP : unsigned :)\
    EXP : TYPE : FIND_ALIAS_type_onion #

#pragma interface GET_ALIAS_type_onion SET_ALIAS_type_onion FIND_ALIAS_type_onion

#endif


/* Operations for field set ptr_etc of union TYPE */

#pragma token EXP const : unsigned : type_ptr_etc_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_ptr_etc #
#pragma interface type_ptr_etc_tag IS_type_ptr_etc

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(TYPE_P) : type_ptr_etc_sub #
#pragma interface type_ptr_etc_sub

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : zero_int :,\
	EXP : TYPE_P :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_ptr_etc #
#pragma interface MAKE_type_ptr_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : TYPE :\
    ) STATEMENT MODIFY_type_ptr_etc #
#pragma interface MODIFY_type_ptr_etc

#pragma token PROC(\
	EXP lvalue : zero_int :,\
	EXP lvalue : TYPE_P :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_ptr_etc #
#pragma interface DECONS_type_ptr_etc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : zero_int :,\
	EXP lvalue : TYPE_P :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_ptr_etc #
#pragma interface DESTROY_type_ptr_etc


/* Operations for field ptr of union TYPE */

#pragma token EXP const : unsigned : type_ptr_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_ptr #
#pragma interface type_ptr_tag IS_type_ptr

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(TYPE_P) : type_ptr_sub #
#pragma interface type_ptr_sub

#pragma token PROC(\
	EXP : zero_int :,\
	EXP : TYPE_P :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_ptr #
#pragma interface MAKE_type_ptr

#pragma token PROC(\
	EXP lvalue : zero_int :,\
	EXP lvalue : TYPE_P :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_ptr #
#pragma interface DECONS_type_ptr

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : zero_int :,\
	EXP lvalue : TYPE_P :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_ptr #
#pragma interface DESTROY_type_ptr

#ifdef calculus_IO_ROUTINES

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : unsigned :\
    ) STATEMENT NEW_ALIAS_type_ptr #
#pragma interface NEW_ALIAS_type_ptr

#pragma token PROC(EXP : TYPE :)\
    EXP : unsigned : GET_ALIAS_type_ptr #
#pragma token PROC(EXP : TYPE :, EXP : unsigned :)\
    EXP : void : SET_ALIAS_type_ptr #
#pragma token PROC(EXP : unsigned :)\
    EXP : TYPE : FIND_ALIAS_type_ptr #

#pragma interface GET_ALIAS_type_ptr SET_ALIAS_type_ptr FIND_ALIAS_type_ptr

#endif


/* Operations for field list of union TYPE */

#pragma token EXP const : unsigned : type_list_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_list #
#pragma interface type_list_tag IS_type_list

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(TYPE_P) : type_list_sub #
#pragma interface type_list_sub

#pragma token PROC(\
	EXP : zero_int :,\
	EXP : TYPE_P :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_list #
#pragma interface MAKE_type_list

#pragma token PROC(\
	EXP lvalue : zero_int :,\
	EXP lvalue : TYPE_P :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_list #
#pragma interface DECONS_type_list

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : zero_int :,\
	EXP lvalue : TYPE_P :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_list #
#pragma interface DESTROY_type_list

#ifdef calculus_IO_ROUTINES

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : unsigned :\
    ) STATEMENT NEW_ALIAS_type_list #
#pragma interface NEW_ALIAS_type_list

#pragma token PROC(EXP : TYPE :)\
    EXP : unsigned : GET_ALIAS_type_list #
#pragma token PROC(EXP : TYPE :, EXP : unsigned :)\
    EXP : void : SET_ALIAS_type_list #
#pragma token PROC(EXP : unsigned :)\
    EXP : TYPE : FIND_ALIAS_type_list #

#pragma interface GET_ALIAS_type_list SET_ALIAS_type_list FIND_ALIAS_type_list

#endif


/* Operations for field stack of union TYPE */

#pragma token EXP const : unsigned : type_stack_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_stack #
#pragma interface type_stack_tag IS_type_stack

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(TYPE_P) : type_stack_sub #
#pragma interface type_stack_sub

#pragma token PROC(\
	EXP : zero_int :,\
	EXP : TYPE_P :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_stack #
#pragma interface MAKE_type_stack

#pragma token PROC(\
	EXP lvalue : zero_int :,\
	EXP lvalue : TYPE_P :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_stack #
#pragma interface DECONS_type_stack

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : zero_int :,\
	EXP lvalue : TYPE_P :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_stack #
#pragma interface DESTROY_type_stack

#ifdef calculus_IO_ROUTINES

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : unsigned :\
    ) STATEMENT NEW_ALIAS_type_stack #
#pragma interface NEW_ALIAS_type_stack

#pragma token PROC(EXP : TYPE :)\
    EXP : unsigned : GET_ALIAS_type_stack #
#pragma token PROC(EXP : TYPE :, EXP : unsigned :)\
    EXP : void : SET_ALIAS_type_stack #
#pragma token PROC(EXP : unsigned :)\
    EXP : TYPE : FIND_ALIAS_type_stack #

#pragma interface GET_ALIAS_type_stack SET_ALIAS_type_stack FIND_ALIAS_type_stack

#endif


/* Operations for field vec of union TYPE */

#pragma token EXP const : unsigned : type_vec_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_vec #
#pragma interface type_vec_tag IS_type_vec

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(TYPE_P) : type_vec_sub #
#pragma interface type_vec_sub

#pragma token PROC(\
	EXP : zero_int :,\
	EXP : TYPE_P :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_vec #
#pragma interface MAKE_type_vec

#pragma token PROC(\
	EXP lvalue : zero_int :,\
	EXP lvalue : TYPE_P :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_vec #
#pragma interface DECONS_type_vec

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : zero_int :,\
	EXP lvalue : TYPE_P :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_vec #
#pragma interface DESTROY_type_vec

#ifdef calculus_IO_ROUTINES

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : unsigned :\
    ) STATEMENT NEW_ALIAS_type_vec #
#pragma interface NEW_ALIAS_type_vec

#pragma token PROC(EXP : TYPE :)\
    EXP : unsigned : GET_ALIAS_type_vec #
#pragma token PROC(EXP : TYPE :, EXP : unsigned :)\
    EXP : void : SET_ALIAS_type_vec #
#pragma token PROC(EXP : unsigned :)\
    EXP : TYPE : FIND_ALIAS_type_vec #

#pragma interface GET_ALIAS_type_vec SET_ALIAS_type_vec FIND_ALIAS_type_vec

#endif


/* Operations for field vec_ptr of union TYPE */

#pragma token EXP const : unsigned : type_vec_ptr_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_vec_ptr #
#pragma interface type_vec_ptr_tag IS_type_vec_ptr

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(TYPE_P) : type_vec_ptr_sub #
#pragma interface type_vec_ptr_sub

#pragma token PROC(\
	EXP : zero_int :,\
	EXP : TYPE_P :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_vec_ptr #
#pragma interface MAKE_type_vec_ptr

#pragma token PROC(\
	EXP lvalue : zero_int :,\
	EXP lvalue : TYPE_P :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_vec_ptr #
#pragma interface DECONS_type_vec_ptr

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : zero_int :,\
	EXP lvalue : TYPE_P :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_vec_ptr #
#pragma interface DESTROY_type_vec_ptr

#ifdef calculus_IO_ROUTINES

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : unsigned :\
    ) STATEMENT NEW_ALIAS_type_vec_ptr #
#pragma interface NEW_ALIAS_type_vec_ptr

#pragma token PROC(EXP : TYPE :)\
    EXP : unsigned : GET_ALIAS_type_vec_ptr #
#pragma token PROC(EXP : TYPE :, EXP : unsigned :)\
    EXP : void : SET_ALIAS_type_vec_ptr #
#pragma token PROC(EXP : unsigned :)\
    EXP : TYPE : FIND_ALIAS_type_vec_ptr #

#pragma interface GET_ALIAS_type_vec_ptr SET_ALIAS_type_vec_ptr FIND_ALIAS_type_vec_ptr

#endif


/* Operations for field quote of union TYPE */

#pragma token EXP const : unsigned : type_quote_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_quote #
#pragma interface type_quote_tag IS_type_quote

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(string) : type_quote_defn #
#pragma interface type_quote_defn

#pragma token PROC(\
	EXP : zero_int :,\
	EXP : string :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_quote #
#pragma interface MAKE_type_quote

#pragma token PROC(\
	EXP lvalue : zero_int :,\
	EXP lvalue : string :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_quote #
#pragma interface DECONS_type_quote

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : zero_int :,\
	EXP lvalue : string :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_quote #
#pragma interface DESTROY_type_quote


/* Operations for field undef of union TYPE */

#pragma token EXP const : unsigned : type_undef_tag #
#pragma token PROC(EXP : TYPE :) EXP : int : IS_type_undef #
#pragma interface type_undef_tag IS_type_undef

#pragma token PROC(EXP : TYPE :)\
    EXP : PTR(string) : type_undef_name #
#pragma interface type_undef_name

#pragma token PROC(\
	EXP : zero_int :,\
	EXP : string :,\
	EXP lvalue : TYPE :\
    ) STATEMENT MAKE_type_undef #
#pragma interface MAKE_type_undef

#pragma token PROC(\
	EXP lvalue : zero_int :,\
	EXP lvalue : string :,\
	EXP : TYPE :\
    ) STATEMENT DECONS_type_undef #
#pragma interface DECONS_type_undef

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : zero_int :,\
	EXP lvalue : string :,\
	EXP : TYPE :\
    ) STATEMENT DESTROY_type_undef #
#pragma interface DESTROY_type_undef


#endif
