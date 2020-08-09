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

#ifndef EXP_OPS_H_INCLUDED
#define EXP_OPS_H_INCLUDED

/* Operations for union EXP */

#pragma token PROC(EXP : EXP :) EXP : unsigned : TAG_exp #
#pragma interface TAG_exp


/* Operations for component type of union EXP */

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(TYPE) : exp_type #
#pragma interface exp_type

/* Operations for field set identifier_etc of union EXP */

#pragma token EXP const : unsigned : exp_identifier_etc_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_identifier_etc #
#pragma interface exp_identifier_etc_tag IS_exp_identifier_etc

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_identifier_etc_id #
#pragma interface exp_identifier_etc_id

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(QUALIFIER) : exp_identifier_etc_qual #
#pragma interface exp_identifier_etc_qual

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP : QUALIFIER :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_identifier_etc #
#pragma interface MAKE_exp_identifier_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : EXP :\
    ) STATEMENT MODIFY_exp_identifier_etc #
#pragma interface MODIFY_exp_identifier_etc

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : QUALIFIER :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_identifier_etc #
#pragma interface DECONS_exp_identifier_etc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : QUALIFIER :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_identifier_etc #
#pragma interface DESTROY_exp_identifier_etc


/* Operations for field identifier of union EXP */

#pragma token EXP const : unsigned : exp_identifier_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_identifier #
#pragma interface exp_identifier_tag IS_exp_identifier

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_identifier_id #
#pragma interface exp_identifier_id

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(QUALIFIER) : exp_identifier_qual #
#pragma interface exp_identifier_qual

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP : QUALIFIER :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_identifier #
#pragma interface MAKE_exp_identifier

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : QUALIFIER :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_identifier #
#pragma interface DECONS_exp_identifier

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : QUALIFIER :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_identifier #
#pragma interface DESTROY_exp_identifier


/* Operations for field member of union EXP */

#pragma token EXP const : unsigned : exp_member_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_member #
#pragma interface exp_member_tag IS_exp_member

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_member_id #
#pragma interface exp_member_id

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(QUALIFIER) : exp_member_qual #
#pragma interface exp_member_qual

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP : QUALIFIER :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_member #
#pragma interface MAKE_exp_member

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : QUALIFIER :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_member #
#pragma interface DECONS_exp_member

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : QUALIFIER :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_member #
#pragma interface DESTROY_exp_member


/* Operations for field ambiguous of union EXP */

#pragma token EXP const : unsigned : exp_ambiguous_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_ambiguous #
#pragma interface exp_ambiguous_tag IS_exp_ambiguous

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_ambiguous_id #
#pragma interface exp_ambiguous_id

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(QUALIFIER) : exp_ambiguous_qual #
#pragma interface exp_ambiguous_qual

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP : QUALIFIER :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_ambiguous #
#pragma interface MAKE_exp_ambiguous

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : QUALIFIER :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_ambiguous #
#pragma interface DECONS_exp_ambiguous

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : QUALIFIER :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_ambiguous #
#pragma interface DESTROY_exp_ambiguous


/* Operations for field undeclared of union EXP */

#pragma token EXP const : unsigned : exp_undeclared_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_undeclared #
#pragma interface exp_undeclared_tag IS_exp_undeclared

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_undeclared_id #
#pragma interface exp_undeclared_id

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(QUALIFIER) : exp_undeclared_qual #
#pragma interface exp_undeclared_qual

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP : QUALIFIER :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_undeclared #
#pragma interface MAKE_exp_undeclared

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : QUALIFIER :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_undeclared #
#pragma interface DECONS_exp_undeclared

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : QUALIFIER :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_undeclared #
#pragma interface DESTROY_exp_undeclared


/* Operations for field int_lit of union EXP */

#pragma token EXP const : unsigned : exp_int_lit_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_int_lit #
#pragma interface exp_int_lit_tag IS_exp_int_lit

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(NAT) : exp_int_lit_nat #
#pragma interface exp_int_lit_nat

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(unsigned) : exp_int_lit_etag #
#pragma interface exp_int_lit_etag

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : NAT :,\
	EXP : unsigned :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_int_lit #
#pragma interface MAKE_exp_int_lit

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : NAT :,\
	EXP lvalue : unsigned :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_int_lit #
#pragma interface DECONS_exp_int_lit

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : NAT :,\
	EXP lvalue : unsigned :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_int_lit #
#pragma interface DESTROY_exp_int_lit


/* Operations for field float_lit of union EXP */

#pragma token EXP const : unsigned : exp_float_lit_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_float_lit #
#pragma interface exp_float_lit_tag IS_exp_float_lit

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(FLOAT) : exp_float_lit_flt #
#pragma interface exp_float_lit_flt

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : FLOAT :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_float_lit #
#pragma interface MAKE_exp_float_lit

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : FLOAT :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_float_lit #
#pragma interface DECONS_exp_float_lit

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : FLOAT :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_float_lit #
#pragma interface DESTROY_exp_float_lit


/* Operations for field char_lit of union EXP */

#pragma token EXP const : unsigned : exp_char_lit_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_char_lit #
#pragma interface exp_char_lit_tag IS_exp_char_lit

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(STRING) : exp_char_lit_str #
#pragma interface exp_char_lit_str

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_char_lit_digit #
#pragma interface exp_char_lit_digit

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : STRING :,\
	EXP : int :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_char_lit #
#pragma interface MAKE_exp_char_lit

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : STRING :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_char_lit #
#pragma interface DECONS_exp_char_lit

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : STRING :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_char_lit #
#pragma interface DESTROY_exp_char_lit


/* Operations for field string_lit of union EXP */

#pragma token EXP const : unsigned : exp_string_lit_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_string_lit #
#pragma interface exp_string_lit_tag IS_exp_string_lit

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(STRING) : exp_string_lit_str #
#pragma interface exp_string_lit_str

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : STRING :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_string_lit #
#pragma interface MAKE_exp_string_lit

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : STRING :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_string_lit #
#pragma interface DECONS_exp_string_lit

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : STRING :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_string_lit #
#pragma interface DESTROY_exp_string_lit


/* Operations for field value of union EXP */

#pragma token EXP const : unsigned : exp_value_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_value #
#pragma interface exp_value_tag IS_exp_value

#pragma token PROC(\
	EXP : TYPE :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_value #
#pragma interface MAKE_exp_value

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_value #
#pragma interface DECONS_exp_value

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_value #
#pragma interface DESTROY_exp_value


/* Operations for field set null_etc of union EXP */

#pragma token EXP const : unsigned : exp_null_etc_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_null_etc #
#pragma interface exp_null_etc_tag IS_exp_null_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : TYPE :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_null_etc #
#pragma interface MAKE_exp_null_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : EXP :\
    ) STATEMENT MODIFY_exp_null_etc #
#pragma interface MODIFY_exp_null_etc

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_null_etc #
#pragma interface DECONS_exp_null_etc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_null_etc #
#pragma interface DESTROY_exp_null_etc


/* Operations for field null of union EXP */

#pragma token EXP const : unsigned : exp_null_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_null #
#pragma interface exp_null_tag IS_exp_null

#pragma token PROC(\
	EXP : TYPE :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_null #
#pragma interface MAKE_exp_null

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_null #
#pragma interface DECONS_exp_null

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_null #
#pragma interface DESTROY_exp_null


/* Operations for field zero of union EXP */

#pragma token EXP const : unsigned : exp_zero_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_zero #
#pragma interface exp_zero_tag IS_exp_zero

#pragma token PROC(\
	EXP : TYPE :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_zero #
#pragma interface MAKE_exp_zero

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_zero #
#pragma interface DECONS_exp_zero

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_zero #
#pragma interface DESTROY_exp_zero


/* Operations for field set paren_etc of union EXP */

#pragma token EXP const : unsigned : exp_paren_etc_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_paren_etc #
#pragma interface exp_paren_etc_tag IS_exp_paren_etc

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_paren_etc_arg #
#pragma interface exp_paren_etc_arg

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_paren_etc #
#pragma interface MAKE_exp_paren_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : EXP :\
    ) STATEMENT MODIFY_exp_paren_etc #
#pragma interface MODIFY_exp_paren_etc

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_paren_etc #
#pragma interface DECONS_exp_paren_etc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_paren_etc #
#pragma interface DESTROY_exp_paren_etc


/* Operations for field paren of union EXP */

#pragma token EXP const : unsigned : exp_paren_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_paren #
#pragma interface exp_paren_tag IS_exp_paren

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_paren_arg #
#pragma interface exp_paren_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_paren #
#pragma interface MAKE_exp_paren

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_paren #
#pragma interface DECONS_exp_paren

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_paren #
#pragma interface DESTROY_exp_paren


/* Operations for field copy of union EXP */

#pragma token EXP const : unsigned : exp_copy_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_copy #
#pragma interface exp_copy_tag IS_exp_copy

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_copy_arg #
#pragma interface exp_copy_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_copy #
#pragma interface MAKE_exp_copy

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_copy #
#pragma interface DECONS_exp_copy

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_copy #
#pragma interface DESTROY_exp_copy


/* Operations for field assign of union EXP */

#pragma token EXP const : unsigned : exp_assign_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_assign #
#pragma interface exp_assign_tag IS_exp_assign

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_assign_ref #
#pragma interface exp_assign_ref

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_assign_arg #
#pragma interface exp_assign_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_assign #
#pragma interface MAKE_exp_assign

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_assign #
#pragma interface DECONS_exp_assign

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_assign #
#pragma interface DESTROY_exp_assign


/* Operations for field init of union EXP */

#pragma token EXP const : unsigned : exp_init_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_init #
#pragma interface exp_init_tag IS_exp_init

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_init_id #
#pragma interface exp_init_id

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_init_arg #
#pragma interface exp_init_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_init #
#pragma interface MAKE_exp_init

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_init #
#pragma interface DECONS_exp_init

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_init #
#pragma interface DESTROY_exp_init


/* Operations for field preinc of union EXP */

#pragma token EXP const : unsigned : exp_preinc_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_preinc #
#pragma interface exp_preinc_tag IS_exp_preinc

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_preinc_ref #
#pragma interface exp_preinc_ref

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_preinc_op #
#pragma interface exp_preinc_op

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_preinc_becomes #
#pragma interface exp_preinc_becomes

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : int :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_preinc #
#pragma interface MAKE_exp_preinc

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_preinc #
#pragma interface DECONS_exp_preinc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_preinc #
#pragma interface DESTROY_exp_preinc


/* Operations for field postinc of union EXP */

#pragma token EXP const : unsigned : exp_postinc_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_postinc #
#pragma interface exp_postinc_tag IS_exp_postinc

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_postinc_ref #
#pragma interface exp_postinc_ref

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_postinc_value #
#pragma interface exp_postinc_value

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_postinc_op #
#pragma interface exp_postinc_op

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_postinc #
#pragma interface MAKE_exp_postinc

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_postinc #
#pragma interface DECONS_exp_postinc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_postinc #
#pragma interface DESTROY_exp_postinc


/* Operations for field indir of union EXP */

#pragma token EXP const : unsigned : exp_indir_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_indir #
#pragma interface exp_indir_tag IS_exp_indir

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_indir_ptr #
#pragma interface exp_indir_ptr

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_indir_index #
#pragma interface exp_indir_index

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_indir #
#pragma interface MAKE_exp_indir

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_indir #
#pragma interface DECONS_exp_indir

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_indir #
#pragma interface DESTROY_exp_indir


/* Operations for field contents of union EXP */

#pragma token EXP const : unsigned : exp_contents_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_contents #
#pragma interface exp_contents_tag IS_exp_contents

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_contents_ptr #
#pragma interface exp_contents_ptr

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_contents #
#pragma interface MAKE_exp_contents

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_contents #
#pragma interface DECONS_exp_contents

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_contents #
#pragma interface DESTROY_exp_contents


/* Operations for field address of union EXP */

#pragma token EXP const : unsigned : exp_address_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_address #
#pragma interface exp_address_tag IS_exp_address

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_address_arg #
#pragma interface exp_address_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_address #
#pragma interface MAKE_exp_address

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_address #
#pragma interface DECONS_exp_address

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_address #
#pragma interface DESTROY_exp_address


/* Operations for field address_mem of union EXP */

#pragma token EXP const : unsigned : exp_address_mem_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_address_mem #
#pragma interface exp_address_mem_tag IS_exp_address_mem

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_address_mem_arg #
#pragma interface exp_address_mem_arg

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_address_mem_paren #
#pragma interface exp_address_mem_paren

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : int :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_address_mem #
#pragma interface MAKE_exp_address_mem

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_address_mem #
#pragma interface DECONS_exp_address_mem

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_address_mem #
#pragma interface DESTROY_exp_address_mem


/* Operations for field func of union EXP */

#pragma token EXP const : unsigned : exp_func_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_func #
#pragma interface exp_func_tag IS_exp_func

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_func_fn #
#pragma interface exp_func_fn

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(EXP)) : exp_func_args #
#pragma interface exp_func_args

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(unsigned) : exp_func_extra #
#pragma interface exp_func_extra

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : LIST(EXP) :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_func #
#pragma interface MAKE_exp_func

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : LIST(EXP) :,\
	EXP lvalue : unsigned :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_func #
#pragma interface DECONS_exp_func

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : LIST(EXP) :,\
	EXP lvalue : unsigned :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_func #
#pragma interface DESTROY_exp_func


/* Operations for field func_id of union EXP */

#pragma token EXP const : unsigned : exp_func_id_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_func_id #
#pragma interface exp_func_id_tag IS_exp_func_id

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_func_id_id #
#pragma interface exp_func_id_id

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(EXP)) : exp_func_id_args #
#pragma interface exp_func_id_args

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_func_id_virt #
#pragma interface exp_func_id_virt

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(unsigned) : exp_func_id_extra #
#pragma interface exp_func_id_extra

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP : LIST(EXP) :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_func_id #
#pragma interface MAKE_exp_func_id

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(EXP) :,\
	EXP lvalue : EXP :,\
	EXP lvalue : unsigned :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_func_id #
#pragma interface DECONS_exp_func_id

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(EXP) :,\
	EXP lvalue : EXP :,\
	EXP lvalue : unsigned :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_func_id #
#pragma interface DESTROY_exp_func_id


/* Operations for field call of union EXP */

#pragma token EXP const : unsigned : exp_call_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_call #
#pragma interface exp_call_tag IS_exp_call

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_call_ptr #
#pragma interface exp_call_ptr

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_call_arg #
#pragma interface exp_call_arg

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(GRAPH) : exp_call_base #
#pragma interface exp_call_base

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : GRAPH :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_call #
#pragma interface MAKE_exp_call

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : GRAPH :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_call #
#pragma interface DECONS_exp_call

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : GRAPH :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_call #
#pragma interface DESTROY_exp_call


/* Operations for field set negate_etc of union EXP */

#pragma token EXP const : unsigned : exp_negate_etc_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_negate_etc #
#pragma interface exp_negate_etc_tag IS_exp_negate_etc

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_negate_etc_arg #
#pragma interface exp_negate_etc_arg

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_negate_etc #
#pragma interface MAKE_exp_negate_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : EXP :\
    ) STATEMENT MODIFY_exp_negate_etc #
#pragma interface MODIFY_exp_negate_etc

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_negate_etc #
#pragma interface DECONS_exp_negate_etc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_negate_etc #
#pragma interface DESTROY_exp_negate_etc


/* Operations for field negate of union EXP */

#pragma token EXP const : unsigned : exp_negate_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_negate #
#pragma interface exp_negate_tag IS_exp_negate

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_negate_arg #
#pragma interface exp_negate_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_negate #
#pragma interface MAKE_exp_negate

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_negate #
#pragma interface DECONS_exp_negate

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_negate #
#pragma interface DESTROY_exp_negate


/* Operations for field compl of union EXP */

#pragma token EXP const : unsigned : exp_compl_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_compl #
#pragma interface exp_compl_tag IS_exp_compl

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_compl_arg #
#pragma interface exp_compl_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_compl #
#pragma interface MAKE_exp_compl

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_compl #
#pragma interface DECONS_exp_compl

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_compl #
#pragma interface DESTROY_exp_compl


/* Operations for field not of union EXP */

#pragma token EXP const : unsigned : exp_not_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_not #
#pragma interface exp_not_tag IS_exp_not

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_not_arg #
#pragma interface exp_not_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_not #
#pragma interface MAKE_exp_not

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_not #
#pragma interface DECONS_exp_not

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_not #
#pragma interface DESTROY_exp_not


/* Operations for field abs of union EXP */

#pragma token EXP const : unsigned : exp_abs_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_abs #
#pragma interface exp_abs_tag IS_exp_abs

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_abs_arg #
#pragma interface exp_abs_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_abs #
#pragma interface MAKE_exp_abs

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_abs #
#pragma interface DECONS_exp_abs

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_abs #
#pragma interface DESTROY_exp_abs


/* Operations for field set plus_etc of union EXP */

#pragma token EXP const : unsigned : exp_plus_etc_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_plus_etc #
#pragma interface exp_plus_etc_tag IS_exp_plus_etc

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_plus_etc_arg1 #
#pragma interface exp_plus_etc_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_plus_etc_arg2 #
#pragma interface exp_plus_etc_arg2

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_plus_etc #
#pragma interface MAKE_exp_plus_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : EXP :\
    ) STATEMENT MODIFY_exp_plus_etc #
#pragma interface MODIFY_exp_plus_etc

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_plus_etc #
#pragma interface DECONS_exp_plus_etc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_plus_etc #
#pragma interface DESTROY_exp_plus_etc


/* Operations for field plus of union EXP */

#pragma token EXP const : unsigned : exp_plus_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_plus #
#pragma interface exp_plus_tag IS_exp_plus

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_plus_arg1 #
#pragma interface exp_plus_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_plus_arg2 #
#pragma interface exp_plus_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_plus #
#pragma interface MAKE_exp_plus

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_plus #
#pragma interface DECONS_exp_plus

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_plus #
#pragma interface DESTROY_exp_plus


/* Operations for field minus of union EXP */

#pragma token EXP const : unsigned : exp_minus_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_minus #
#pragma interface exp_minus_tag IS_exp_minus

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_minus_arg1 #
#pragma interface exp_minus_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_minus_arg2 #
#pragma interface exp_minus_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_minus #
#pragma interface MAKE_exp_minus

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_minus #
#pragma interface DECONS_exp_minus

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_minus #
#pragma interface DESTROY_exp_minus


/* Operations for field mult of union EXP */

#pragma token EXP const : unsigned : exp_mult_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_mult #
#pragma interface exp_mult_tag IS_exp_mult

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_mult_arg1 #
#pragma interface exp_mult_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_mult_arg2 #
#pragma interface exp_mult_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_mult #
#pragma interface MAKE_exp_mult

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_mult #
#pragma interface DECONS_exp_mult

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_mult #
#pragma interface DESTROY_exp_mult


/* Operations for field div of union EXP */

#pragma token EXP const : unsigned : exp_div_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_div #
#pragma interface exp_div_tag IS_exp_div

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_div_arg1 #
#pragma interface exp_div_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_div_arg2 #
#pragma interface exp_div_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_div #
#pragma interface MAKE_exp_div

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_div #
#pragma interface DECONS_exp_div

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_div #
#pragma interface DESTROY_exp_div


/* Operations for field rem of union EXP */

#pragma token EXP const : unsigned : exp_rem_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_rem #
#pragma interface exp_rem_tag IS_exp_rem

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_rem_arg1 #
#pragma interface exp_rem_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_rem_arg2 #
#pragma interface exp_rem_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_rem #
#pragma interface MAKE_exp_rem

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_rem #
#pragma interface DECONS_exp_rem

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_rem #
#pragma interface DESTROY_exp_rem


/* Operations for field and of union EXP */

#pragma token EXP const : unsigned : exp_and_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_and #
#pragma interface exp_and_tag IS_exp_and

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_and_arg1 #
#pragma interface exp_and_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_and_arg2 #
#pragma interface exp_and_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_and #
#pragma interface MAKE_exp_and

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_and #
#pragma interface DECONS_exp_and

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_and #
#pragma interface DESTROY_exp_and


/* Operations for field or of union EXP */

#pragma token EXP const : unsigned : exp_or_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_or #
#pragma interface exp_or_tag IS_exp_or

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_or_arg1 #
#pragma interface exp_or_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_or_arg2 #
#pragma interface exp_or_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_or #
#pragma interface MAKE_exp_or

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_or #
#pragma interface DECONS_exp_or

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_or #
#pragma interface DESTROY_exp_or


/* Operations for field xor of union EXP */

#pragma token EXP const : unsigned : exp_xor_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_xor #
#pragma interface exp_xor_tag IS_exp_xor

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_xor_arg1 #
#pragma interface exp_xor_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_xor_arg2 #
#pragma interface exp_xor_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_xor #
#pragma interface MAKE_exp_xor

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_xor #
#pragma interface DECONS_exp_xor

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_xor #
#pragma interface DESTROY_exp_xor


/* Operations for field log_and of union EXP */

#pragma token EXP const : unsigned : exp_log_and_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_log_and #
#pragma interface exp_log_and_tag IS_exp_log_and

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_log_and_arg1 #
#pragma interface exp_log_and_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_log_and_arg2 #
#pragma interface exp_log_and_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_log_and #
#pragma interface MAKE_exp_log_and

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_log_and #
#pragma interface DECONS_exp_log_and

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_log_and #
#pragma interface DESTROY_exp_log_and


/* Operations for field log_or of union EXP */

#pragma token EXP const : unsigned : exp_log_or_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_log_or #
#pragma interface exp_log_or_tag IS_exp_log_or

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_log_or_arg1 #
#pragma interface exp_log_or_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_log_or_arg2 #
#pragma interface exp_log_or_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_log_or #
#pragma interface MAKE_exp_log_or

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_log_or #
#pragma interface DECONS_exp_log_or

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_log_or #
#pragma interface DESTROY_exp_log_or


/* Operations for field lshift of union EXP */

#pragma token EXP const : unsigned : exp_lshift_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_lshift #
#pragma interface exp_lshift_tag IS_exp_lshift

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_lshift_arg1 #
#pragma interface exp_lshift_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_lshift_arg2 #
#pragma interface exp_lshift_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_lshift #
#pragma interface MAKE_exp_lshift

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_lshift #
#pragma interface DECONS_exp_lshift

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_lshift #
#pragma interface DESTROY_exp_lshift


/* Operations for field rshift of union EXP */

#pragma token EXP const : unsigned : exp_rshift_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_rshift #
#pragma interface exp_rshift_tag IS_exp_rshift

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_rshift_arg1 #
#pragma interface exp_rshift_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_rshift_arg2 #
#pragma interface exp_rshift_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_rshift #
#pragma interface MAKE_exp_rshift

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_rshift #
#pragma interface DECONS_exp_rshift

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_rshift #
#pragma interface DESTROY_exp_rshift


/* Operations for field max of union EXP */

#pragma token EXP const : unsigned : exp_max_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_max #
#pragma interface exp_max_tag IS_exp_max

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_max_arg1 #
#pragma interface exp_max_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_max_arg2 #
#pragma interface exp_max_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_max #
#pragma interface MAKE_exp_max

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_max #
#pragma interface DECONS_exp_max

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_max #
#pragma interface DESTROY_exp_max


/* Operations for field min of union EXP */

#pragma token EXP const : unsigned : exp_min_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_min #
#pragma interface exp_min_tag IS_exp_min

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_min_arg1 #
#pragma interface exp_min_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_min_arg2 #
#pragma interface exp_min_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_min #
#pragma interface MAKE_exp_min

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_min #
#pragma interface DECONS_exp_min

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_min #
#pragma interface DESTROY_exp_min


/* Operations for field test of union EXP */

#pragma token EXP const : unsigned : exp_test_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_test #
#pragma interface exp_test_tag IS_exp_test

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(NTEST) : exp_test_tst #
#pragma interface exp_test_tst

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_test_arg #
#pragma interface exp_test_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : NTEST :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_test #
#pragma interface MAKE_exp_test

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : NTEST :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_test #
#pragma interface DECONS_exp_test

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : NTEST :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_test #
#pragma interface DESTROY_exp_test


/* Operations for field compare of union EXP */

#pragma token EXP const : unsigned : exp_compare_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_compare #
#pragma interface exp_compare_tag IS_exp_compare

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(NTEST) : exp_compare_tst #
#pragma interface exp_compare_tst

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_compare_arg1 #
#pragma interface exp_compare_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_compare_arg2 #
#pragma interface exp_compare_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : NTEST :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_compare #
#pragma interface MAKE_exp_compare

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : NTEST :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_compare #
#pragma interface DECONS_exp_compare

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : NTEST :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_compare #
#pragma interface DESTROY_exp_compare


/* Operations for field cast of union EXP */

#pragma token EXP const : unsigned : exp_cast_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_cast #
#pragma interface exp_cast_tag IS_exp_cast

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(unsigned) : exp_cast_conv #
#pragma interface exp_cast_conv

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_cast_arg #
#pragma interface exp_cast_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : unsigned :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_cast #
#pragma interface MAKE_exp_cast

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_cast #
#pragma interface DECONS_exp_cast

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_cast #
#pragma interface DESTROY_exp_cast


/* Operations for field base_cast of union EXP */

#pragma token EXP const : unsigned : exp_base_cast_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_base_cast #
#pragma interface exp_base_cast_tag IS_exp_base_cast

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(unsigned) : exp_base_cast_conv #
#pragma interface exp_base_cast_conv

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_base_cast_arg #
#pragma interface exp_base_cast_arg

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(OFFSET) : exp_base_cast_off #
#pragma interface exp_base_cast_off

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : unsigned :,\
	EXP : EXP :,\
	EXP : OFFSET :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_base_cast #
#pragma interface MAKE_exp_base_cast

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : EXP :,\
	EXP lvalue : OFFSET :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_base_cast #
#pragma interface DECONS_exp_base_cast

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : EXP :,\
	EXP lvalue : OFFSET :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_base_cast #
#pragma interface DESTROY_exp_base_cast


/* Operations for field dyn_cast of union EXP */

#pragma token EXP const : unsigned : exp_dyn_cast_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_dyn_cast #
#pragma interface exp_dyn_cast_tag IS_exp_dyn_cast

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_dyn_cast_arg #
#pragma interface exp_dyn_cast_arg

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_dyn_cast_except #
#pragma interface exp_dyn_cast_except

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_dyn_cast #
#pragma interface MAKE_exp_dyn_cast

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_dyn_cast #
#pragma interface DECONS_exp_dyn_cast

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_dyn_cast #
#pragma interface DESTROY_exp_dyn_cast


/* Operations for field add_ptr of union EXP */

#pragma token EXP const : unsigned : exp_add_ptr_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_add_ptr #
#pragma interface exp_add_ptr_tag IS_exp_add_ptr

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_add_ptr_ptr #
#pragma interface exp_add_ptr_ptr

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(OFFSET) : exp_add_ptr_off #
#pragma interface exp_add_ptr_off

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_add_ptr_virt #
#pragma interface exp_add_ptr_virt

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : OFFSET :,\
	EXP : int :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_add_ptr #
#pragma interface MAKE_exp_add_ptr

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_add_ptr #
#pragma interface DECONS_exp_add_ptr

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_add_ptr #
#pragma interface DESTROY_exp_add_ptr


/* Operations for field offset_size of union EXP */

#pragma token EXP const : unsigned : exp_offset_size_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_offset_size #
#pragma interface exp_offset_size_tag IS_exp_offset_size

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(OFFSET) : exp_offset_size_off #
#pragma interface exp_offset_size_off

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(TYPE) : exp_offset_size_step #
#pragma interface exp_offset_size_step

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_offset_size_pad #
#pragma interface exp_offset_size_pad

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : OFFSET :,\
	EXP : TYPE :,\
	EXP : int :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_offset_size #
#pragma interface MAKE_exp_offset_size

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_offset_size #
#pragma interface DECONS_exp_offset_size

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_offset_size #
#pragma interface DESTROY_exp_offset_size


/* Operations for field constr of union EXP */

#pragma token EXP const : unsigned : exp_constr_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_constr #
#pragma interface exp_constr_tag IS_exp_constr

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_constr_call #
#pragma interface exp_constr_call

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_constr_obj #
#pragma interface exp_constr_obj

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_constr_alt #
#pragma interface exp_constr_alt

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_constr_info #
#pragma interface exp_constr_info

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : int :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_constr #
#pragma interface MAKE_exp_constr

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_constr #
#pragma interface DECONS_exp_constr

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_constr #
#pragma interface DESTROY_exp_constr


/* Operations for field destr of union EXP */

#pragma token EXP const : unsigned : exp_destr_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_destr #
#pragma interface exp_destr_tag IS_exp_destr

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_destr_call #
#pragma interface exp_destr_call

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_destr_obj #
#pragma interface exp_destr_obj

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_destr_count #
#pragma interface exp_destr_count

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_destr #
#pragma interface MAKE_exp_destr

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_destr #
#pragma interface DECONS_exp_destr

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_destr #
#pragma interface DESTROY_exp_destr


/* Operations for field alloc of union EXP */

#pragma token EXP const : unsigned : exp_alloc_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_alloc #
#pragma interface exp_alloc_tag IS_exp_alloc

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_alloc_call #
#pragma interface exp_alloc_call

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_alloc_init #
#pragma interface exp_alloc_init

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_alloc_garbage #
#pragma interface exp_alloc_garbage

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_alloc_size #
#pragma interface exp_alloc_size

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_alloc #
#pragma interface MAKE_exp_alloc

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_alloc #
#pragma interface DECONS_exp_alloc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_alloc #
#pragma interface DESTROY_exp_alloc


/* Operations for field dealloc of union EXP */

#pragma token EXP const : unsigned : exp_dealloc_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_dealloc #
#pragma interface exp_dealloc_tag IS_exp_dealloc

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_dealloc_term #
#pragma interface exp_dealloc_term

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_dealloc_call #
#pragma interface exp_dealloc_call

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_dealloc_arg #
#pragma interface exp_dealloc_arg

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_dealloc_size #
#pragma interface exp_dealloc_size

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_dealloc #
#pragma interface MAKE_exp_dealloc

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_dealloc #
#pragma interface DECONS_exp_dealloc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_dealloc #
#pragma interface DESTROY_exp_dealloc


/* Operations for field rtti of union EXP */

#pragma token EXP const : unsigned : exp_rtti_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_rtti #
#pragma interface exp_rtti_tag IS_exp_rtti

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_rtti_arg #
#pragma interface exp_rtti_arg

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_rtti_except #
#pragma interface exp_rtti_except

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_rtti_op #
#pragma interface exp_rtti_op

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : int :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_rtti #
#pragma interface MAKE_exp_rtti

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_rtti #
#pragma interface DECONS_exp_rtti

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_rtti #
#pragma interface DESTROY_exp_rtti


/* Operations for field rtti_type of union EXP */

#pragma token EXP const : unsigned : exp_rtti_type_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_rtti_type #
#pragma interface exp_rtti_type_tag IS_exp_rtti_type

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(TYPE) : exp_rtti_type_arg #
#pragma interface exp_rtti_type_arg

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_rtti_type_op #
#pragma interface exp_rtti_type_op

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : TYPE :,\
	EXP : int :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_rtti_type #
#pragma interface MAKE_exp_rtti_type

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_rtti_type #
#pragma interface DECONS_exp_rtti_type

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_rtti_type #
#pragma interface DESTROY_exp_rtti_type


/* Operations for field rtti_no of union EXP */

#pragma token EXP const : unsigned : exp_rtti_no_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_rtti_no #
#pragma interface exp_rtti_no_tag IS_exp_rtti_no

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(TYPE) : exp_rtti_no_arg #
#pragma interface exp_rtti_no_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : TYPE :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_rtti_no #
#pragma interface MAKE_exp_rtti_no

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_rtti_no #
#pragma interface DECONS_exp_rtti_no

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : TYPE :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_rtti_no #
#pragma interface DESTROY_exp_rtti_no


/* Operations for field dynamic of union EXP */

#pragma token EXP const : unsigned : exp_dynamic_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_dynamic #
#pragma interface exp_dynamic_tag IS_exp_dynamic

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_dynamic_arg #
#pragma interface exp_dynamic_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_dynamic #
#pragma interface MAKE_exp_dynamic

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_dynamic #
#pragma interface DECONS_exp_dynamic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_dynamic #
#pragma interface DESTROY_exp_dynamic


/* Operations for field aggregate of union EXP */

#pragma token EXP const : unsigned : exp_aggregate_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_aggregate #
#pragma interface exp_aggregate_tag IS_exp_aggregate

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(EXP)) : exp_aggregate_args #
#pragma interface exp_aggregate_args

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(OFFSET)) : exp_aggregate_offs #
#pragma interface exp_aggregate_offs

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : LIST(EXP) :,\
	EXP : LIST(OFFSET) :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_aggregate #
#pragma interface MAKE_exp_aggregate

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(EXP) :,\
	EXP lvalue : LIST(OFFSET) :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_aggregate #
#pragma interface DECONS_exp_aggregate

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(EXP) :,\
	EXP lvalue : LIST(OFFSET) :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_aggregate #
#pragma interface DESTROY_exp_aggregate


/* Operations for field initialiser of union EXP */

#pragma token EXP const : unsigned : exp_initialiser_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_initialiser #
#pragma interface exp_initialiser_tag IS_exp_initialiser

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(EXP)) : exp_initialiser_args #
#pragma interface exp_initialiser_args

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(OFFSET)) : exp_initialiser_offs #
#pragma interface exp_initialiser_offs

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_initialiser_kind #
#pragma interface exp_initialiser_kind

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(unsigned) : exp_initialiser_virt #
#pragma interface exp_initialiser_virt

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(unsigned) : exp_initialiser_base #
#pragma interface exp_initialiser_base

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : LIST(EXP) :,\
	EXP : LIST(OFFSET) :,\
	EXP : int :,\
	EXP : unsigned :,\
	EXP : unsigned :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_initialiser #
#pragma interface MAKE_exp_initialiser

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(EXP) :,\
	EXP lvalue : LIST(OFFSET) :,\
	EXP lvalue : int :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : unsigned :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_initialiser #
#pragma interface DECONS_exp_initialiser

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(EXP) :,\
	EXP lvalue : LIST(OFFSET) :,\
	EXP lvalue : int :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : unsigned :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_initialiser #
#pragma interface DESTROY_exp_initialiser


/* Operations for field nof of union EXP */

#pragma token EXP const : unsigned : exp_nof_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_nof #
#pragma interface exp_nof_tag IS_exp_nof

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_nof_start #
#pragma interface exp_nof_start

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(NAT) : exp_nof_size #
#pragma interface exp_nof_size

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_nof_pad #
#pragma interface exp_nof_pad

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_nof_end #
#pragma interface exp_nof_end

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : NAT :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_nof #
#pragma interface MAKE_exp_nof

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : NAT :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_nof #
#pragma interface DECONS_exp_nof

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : NAT :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_nof #
#pragma interface DESTROY_exp_nof


/* Operations for field comma of union EXP */

#pragma token EXP const : unsigned : exp_comma_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_comma #
#pragma interface exp_comma_tag IS_exp_comma

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(EXP)) : exp_comma_args #
#pragma interface exp_comma_args

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : LIST(EXP) :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_comma #
#pragma interface MAKE_exp_comma

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(EXP) :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_comma #
#pragma interface DECONS_exp_comma

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LIST(EXP) :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_comma #
#pragma interface DESTROY_exp_comma


/* Operations for field set set_etc of union EXP */

#pragma token EXP const : unsigned : exp_set_etc_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_set_etc #
#pragma interface exp_set_etc_tag IS_exp_set_etc

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_set_etc_arg #
#pragma interface exp_set_etc_arg

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_set_etc #
#pragma interface MAKE_exp_set_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : EXP :\
    ) STATEMENT MODIFY_exp_set_etc #
#pragma interface MODIFY_exp_set_etc

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_set_etc #
#pragma interface DECONS_exp_set_etc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_set_etc #
#pragma interface DESTROY_exp_set_etc


/* Operations for field set of union EXP */

#pragma token EXP const : unsigned : exp_set_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_set #
#pragma interface exp_set_tag IS_exp_set

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_set_arg #
#pragma interface exp_set_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_set #
#pragma interface MAKE_exp_set

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_set #
#pragma interface DECONS_exp_set

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_set #
#pragma interface DESTROY_exp_set


/* Operations for field unused of union EXP */

#pragma token EXP const : unsigned : exp_unused_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_unused #
#pragma interface exp_unused_tag IS_exp_unused

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_unused_arg #
#pragma interface exp_unused_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_unused #
#pragma interface MAKE_exp_unused

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_unused #
#pragma interface DECONS_exp_unused

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_unused #
#pragma interface DESTROY_exp_unused


/* Operations for field set reach_etc of union EXP */

#pragma token EXP const : unsigned : exp_reach_etc_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_reach_etc #
#pragma interface exp_reach_etc_tag IS_exp_reach_etc

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_reach_etc_parent #
#pragma interface exp_reach_etc_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_reach_etc_body #
#pragma interface exp_reach_etc_body

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_reach_etc #
#pragma interface MAKE_exp_reach_etc

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : EXP :\
    ) STATEMENT MODIFY_exp_reach_etc #
#pragma interface MODIFY_exp_reach_etc

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_reach_etc #
#pragma interface DECONS_exp_reach_etc

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_reach_etc #
#pragma interface DESTROY_exp_reach_etc


/* Operations for field reach of union EXP */

#pragma token EXP const : unsigned : exp_reach_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_reach #
#pragma interface exp_reach_tag IS_exp_reach

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_reach_parent #
#pragma interface exp_reach_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_reach_body #
#pragma interface exp_reach_body

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_reach #
#pragma interface MAKE_exp_reach

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_reach #
#pragma interface DECONS_exp_reach

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_reach #
#pragma interface DESTROY_exp_reach


/* Operations for field unreach of union EXP */

#pragma token EXP const : unsigned : exp_unreach_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_unreach #
#pragma interface exp_unreach_tag IS_exp_unreach

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_unreach_parent #
#pragma interface exp_unreach_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_unreach_body #
#pragma interface exp_unreach_body

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_unreach #
#pragma interface MAKE_exp_unreach

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_unreach #
#pragma interface DECONS_exp_unreach

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_unreach #
#pragma interface DESTROY_exp_unreach


/* Operations for field sequence of union EXP */

#pragma token EXP const : unsigned : exp_sequence_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_sequence #
#pragma interface exp_sequence_tag IS_exp_sequence

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_sequence_parent #
#pragma interface exp_sequence_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(EXP)) : exp_sequence_first #
#pragma interface exp_sequence_first

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(EXP)) : exp_sequence_last #
#pragma interface exp_sequence_last

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(NAMESPACE) : exp_sequence_decl #
#pragma interface exp_sequence_decl

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_sequence_block #
#pragma interface exp_sequence_block

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : LIST(EXP) :,\
	EXP : LIST(EXP) :,\
	EXP : NAMESPACE :,\
	EXP : int :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_sequence #
#pragma interface MAKE_exp_sequence

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : LIST(EXP) :,\
	EXP lvalue : LIST(EXP) :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_sequence #
#pragma interface DECONS_exp_sequence

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : LIST(EXP) :,\
	EXP lvalue : LIST(EXP) :,\
	EXP lvalue : NAMESPACE :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_sequence #
#pragma interface DESTROY_exp_sequence


/* Operations for field solve_stmt of union EXP */

#pragma token EXP const : unsigned : exp_solve_stmt_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_solve_stmt #
#pragma interface exp_solve_stmt_tag IS_exp_solve_stmt

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_solve_stmt_parent #
#pragma interface exp_solve_stmt_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_solve_stmt_body #
#pragma interface exp_solve_stmt_body

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(IDENTIFIER)) : exp_solve_stmt_labels #
#pragma interface exp_solve_stmt_labels

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(IDENTIFIER)) : exp_solve_stmt_vars #
#pragma interface exp_solve_stmt_vars

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_solve_stmt #
#pragma interface MAKE_exp_solve_stmt

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_solve_stmt #
#pragma interface DECONS_exp_solve_stmt

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_solve_stmt #
#pragma interface DESTROY_exp_solve_stmt


/* Operations for field decl_stmt of union EXP */

#pragma token EXP const : unsigned : exp_decl_stmt_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_decl_stmt #
#pragma interface exp_decl_stmt_tag IS_exp_decl_stmt

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_decl_stmt_parent #
#pragma interface exp_decl_stmt_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_decl_stmt_id #
#pragma interface exp_decl_stmt_id

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_decl_stmt_body #
#pragma interface exp_decl_stmt_body

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_decl_stmt #
#pragma interface MAKE_exp_decl_stmt

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_decl_stmt #
#pragma interface DECONS_exp_decl_stmt

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_decl_stmt #
#pragma interface DESTROY_exp_decl_stmt


/* Operations for field if_stmt of union EXP */

#pragma token EXP const : unsigned : exp_if_stmt_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_if_stmt #
#pragma interface exp_if_stmt_tag IS_exp_if_stmt

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_if_stmt_parent #
#pragma interface exp_if_stmt_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_if_stmt_cond #
#pragma interface exp_if_stmt_cond

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_if_stmt_true_code #
#pragma interface exp_if_stmt_true_code

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_if_stmt_false_code #
#pragma interface exp_if_stmt_false_code

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_if_stmt_label #
#pragma interface exp_if_stmt_label

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_if_stmt #
#pragma interface MAKE_exp_if_stmt

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_if_stmt #
#pragma interface DECONS_exp_if_stmt

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_if_stmt #
#pragma interface DESTROY_exp_if_stmt


/* Operations for field while_stmt of union EXP */

#pragma token EXP const : unsigned : exp_while_stmt_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_while_stmt #
#pragma interface exp_while_stmt_tag IS_exp_while_stmt

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_while_stmt_parent #
#pragma interface exp_while_stmt_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_while_stmt_cond #
#pragma interface exp_while_stmt_cond

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_while_stmt_body #
#pragma interface exp_while_stmt_body

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_while_stmt_break_lab #
#pragma interface exp_while_stmt_break_lab

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_while_stmt_cont_lab #
#pragma interface exp_while_stmt_cont_lab

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_while_stmt_loop_lab #
#pragma interface exp_while_stmt_loop_lab

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(IDENTIFIER)) : exp_while_stmt_cond_id #
#pragma interface exp_while_stmt_cond_id

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : IDENTIFIER :,\
	EXP : IDENTIFIER :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_while_stmt #
#pragma interface MAKE_exp_while_stmt

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_while_stmt #
#pragma interface DECONS_exp_while_stmt

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_while_stmt #
#pragma interface DESTROY_exp_while_stmt


/* Operations for field do_stmt of union EXP */

#pragma token EXP const : unsigned : exp_do_stmt_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_do_stmt #
#pragma interface exp_do_stmt_tag IS_exp_do_stmt

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_do_stmt_parent #
#pragma interface exp_do_stmt_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_do_stmt_cond #
#pragma interface exp_do_stmt_cond

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_do_stmt_body #
#pragma interface exp_do_stmt_body

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_do_stmt_break_lab #
#pragma interface exp_do_stmt_break_lab

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_do_stmt_cont_lab #
#pragma interface exp_do_stmt_cont_lab

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_do_stmt_loop_lab #
#pragma interface exp_do_stmt_loop_lab

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : IDENTIFIER :,\
	EXP : IDENTIFIER :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_do_stmt #
#pragma interface MAKE_exp_do_stmt

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_do_stmt #
#pragma interface DECONS_exp_do_stmt

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_do_stmt #
#pragma interface DESTROY_exp_do_stmt


/* Operations for field switch_stmt of union EXP */

#pragma token EXP const : unsigned : exp_switch_stmt_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_switch_stmt #
#pragma interface exp_switch_stmt_tag IS_exp_switch_stmt

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_switch_stmt_parent #
#pragma interface exp_switch_stmt_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_switch_stmt_control #
#pragma interface exp_switch_stmt_control

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_switch_stmt_body #
#pragma interface exp_switch_stmt_body

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(NAT)) : exp_switch_stmt_cases #
#pragma interface exp_switch_stmt_cases

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(IDENTIFIER)) : exp_switch_stmt_case_labs #
#pragma interface exp_switch_stmt_case_labs

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_switch_stmt_default_lab #
#pragma interface exp_switch_stmt_default_lab

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_switch_stmt_exhaust #
#pragma interface exp_switch_stmt_exhaust

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_switch_stmt_break_lab #
#pragma interface exp_switch_stmt_break_lab

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : int :,\
	EXP : IDENTIFIER :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_switch_stmt #
#pragma interface MAKE_exp_switch_stmt

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : LIST(NAT) :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : int :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_switch_stmt #
#pragma interface DECONS_exp_switch_stmt

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : LIST(NAT) :,\
	EXP lvalue : LIST(IDENTIFIER) :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : int :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_switch_stmt #
#pragma interface DESTROY_exp_switch_stmt


/* Operations for field hash_if of union EXP */

#pragma token EXP const : unsigned : exp_hash_if_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_hash_if #
#pragma interface exp_hash_if_tag IS_exp_hash_if

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_hash_if_parent #
#pragma interface exp_hash_if_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_hash_if_cond #
#pragma interface exp_hash_if_cond

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_hash_if_true_code #
#pragma interface exp_hash_if_true_code

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_hash_if_false_code #
#pragma interface exp_hash_if_false_code

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_hash_if_last #
#pragma interface exp_hash_if_last

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_hash_if #
#pragma interface MAKE_exp_hash_if

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_hash_if #
#pragma interface DECONS_exp_hash_if

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_hash_if #
#pragma interface DESTROY_exp_hash_if


/* Operations for field return_stmt of union EXP */

#pragma token EXP const : unsigned : exp_return_stmt_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_return_stmt #
#pragma interface exp_return_stmt_tag IS_exp_return_stmt

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_return_stmt_parent #
#pragma interface exp_return_stmt_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_return_stmt_value #
#pragma interface exp_return_stmt_value

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_return_stmt #
#pragma interface MAKE_exp_return_stmt

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_return_stmt #
#pragma interface DECONS_exp_return_stmt

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_return_stmt #
#pragma interface DESTROY_exp_return_stmt


/* Operations for field goto_stmt of union EXP */

#pragma token EXP const : unsigned : exp_goto_stmt_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_goto_stmt #
#pragma interface exp_goto_stmt_tag IS_exp_goto_stmt

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_goto_stmt_parent #
#pragma interface exp_goto_stmt_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_goto_stmt_label #
#pragma interface exp_goto_stmt_label

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_goto_stmt_join #
#pragma interface exp_goto_stmt_join

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_goto_stmt_next #
#pragma interface exp_goto_stmt_next

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_goto_stmt #
#pragma interface MAKE_exp_goto_stmt

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_goto_stmt #
#pragma interface DECONS_exp_goto_stmt

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_goto_stmt #
#pragma interface DESTROY_exp_goto_stmt


/* Operations for field label_stmt of union EXP */

#pragma token EXP const : unsigned : exp_label_stmt_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_label_stmt #
#pragma interface exp_label_stmt_tag IS_exp_label_stmt

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_label_stmt_parent #
#pragma interface exp_label_stmt_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_label_stmt_label #
#pragma interface exp_label_stmt_label

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_label_stmt_body #
#pragma interface exp_label_stmt_body

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_label_stmt_next #
#pragma interface exp_label_stmt_next

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_label_stmt #
#pragma interface MAKE_exp_label_stmt

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_label_stmt #
#pragma interface DECONS_exp_label_stmt

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_label_stmt #
#pragma interface DESTROY_exp_label_stmt


/* Operations for field try_block of union EXP */

#pragma token EXP const : unsigned : exp_try_block_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_try_block #
#pragma interface exp_try_block_tag IS_exp_try_block

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_try_block_parent #
#pragma interface exp_try_block_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_try_block_body #
#pragma interface exp_try_block_body

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_try_block_func #
#pragma interface exp_try_block_func

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(EXP)) : exp_try_block_handlers #
#pragma interface exp_try_block_handlers

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(TYPE)) : exp_try_block_htypes #
#pragma interface exp_try_block_htypes

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_try_block_ellipsis #
#pragma interface exp_try_block_ellipsis

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(TYPE)) : exp_try_block_ttypes #
#pragma interface exp_try_block_ttypes

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(LOCATION)) : exp_try_block_tlocs #
#pragma interface exp_try_block_tlocs

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(ulong_type) : exp_try_block_no #
#pragma interface exp_try_block_no

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : int :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_try_block #
#pragma interface MAKE_exp_try_block

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : int :,\
	EXP lvalue : LIST(EXP) :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : EXP :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : LIST(LOCATION) :,\
	EXP lvalue : ulong_type :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_try_block #
#pragma interface DECONS_exp_try_block

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : int :,\
	EXP lvalue : LIST(EXP) :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : EXP :,\
	EXP lvalue : LIST(TYPE) :,\
	EXP lvalue : LIST(LOCATION) :,\
	EXP lvalue : ulong_type :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_try_block #
#pragma interface DESTROY_exp_try_block


/* Operations for field handler of union EXP */

#pragma token EXP const : unsigned : exp_handler_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_handler #
#pragma interface exp_handler_tag IS_exp_handler

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_handler_parent #
#pragma interface exp_handler_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_handler_except #
#pragma interface exp_handler_except

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_handler_body #
#pragma interface exp_handler_body

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(ulong_type) : exp_handler_diag #
#pragma interface exp_handler_diag

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_handler #
#pragma interface MAKE_exp_handler

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : EXP :,\
	EXP lvalue : ulong_type :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_handler #
#pragma interface DECONS_exp_handler

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : EXP :,\
	EXP lvalue : ulong_type :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_handler #
#pragma interface DESTROY_exp_handler


/* Operations for field exception of union EXP */

#pragma token EXP const : unsigned : exp_exception_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_exception #
#pragma interface exp_exception_tag IS_exp_exception

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_exception_arg #
#pragma interface exp_exception_arg

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_exception_size #
#pragma interface exp_exception_size

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_exception_destr #
#pragma interface exp_exception_destr

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_exception_expl #
#pragma interface exp_exception_expl

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP : int :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_exception #
#pragma interface MAKE_exp_exception

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_exception #
#pragma interface DECONS_exp_exception

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_exception #
#pragma interface DESTROY_exp_exception


/* Operations for field thrown of union EXP */

#pragma token EXP const : unsigned : exp_thrown_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_thrown #
#pragma interface exp_thrown_tag IS_exp_thrown

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_thrown_done #
#pragma interface exp_thrown_done

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : int :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_thrown #
#pragma interface MAKE_exp_thrown

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_thrown #
#pragma interface DECONS_exp_thrown

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_thrown #
#pragma interface DESTROY_exp_thrown


/* Operations for field op of union EXP */

#pragma token EXP const : unsigned : exp_op_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_op #
#pragma interface exp_op_tag IS_exp_op

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_op_lex #
#pragma interface exp_op_lex

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_op_arg1 #
#pragma interface exp_op_arg1

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_op_arg2 #
#pragma interface exp_op_arg2

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : int :,\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_op #
#pragma interface MAKE_exp_op

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_op #
#pragma interface DECONS_exp_op

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_op #
#pragma interface DESTROY_exp_op


/* Operations for field opn of union EXP */

#pragma token EXP const : unsigned : exp_opn_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_opn #
#pragma interface exp_opn_tag IS_exp_opn

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_opn_lex #
#pragma interface exp_opn_lex

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(EXP)) : exp_opn_args #
#pragma interface exp_opn_args

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : int :,\
	EXP : LIST(EXP) :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_opn #
#pragma interface MAKE_exp_opn

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP lvalue : LIST(EXP) :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_opn #
#pragma interface DECONS_exp_opn

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP lvalue : LIST(EXP) :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_opn #
#pragma interface DESTROY_exp_opn


/* Operations for field assembler of union EXP */

#pragma token EXP const : unsigned : exp_assembler_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_assembler #
#pragma interface exp_assembler_tag IS_exp_assembler

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(STRING) : exp_assembler_op #
#pragma interface exp_assembler_op

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(EXP)) : exp_assembler_args #
#pragma interface exp_assembler_args

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : STRING :,\
	EXP : LIST(EXP) :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_assembler #
#pragma interface MAKE_exp_assembler

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : STRING :,\
	EXP lvalue : LIST(EXP) :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_assembler #
#pragma interface DECONS_exp_assembler

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : STRING :,\
	EXP lvalue : LIST(EXP) :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_assembler #
#pragma interface DESTROY_exp_assembler


/* Operations for field uncompiled of union EXP */

#pragma token EXP const : unsigned : exp_uncompiled_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_uncompiled #
#pragma interface exp_uncompiled_tag IS_exp_uncompiled

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LOCATION) : exp_uncompiled_start #
#pragma interface exp_uncompiled_start

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(PPTOKEN_P) : exp_uncompiled_defn #
#pragma interface exp_uncompiled_defn

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : LOCATION :,\
	EXP : PPTOKEN_P :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_uncompiled #
#pragma interface MAKE_exp_uncompiled

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : PPTOKEN_P :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_uncompiled #
#pragma interface DECONS_exp_uncompiled

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : PPTOKEN_P :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_uncompiled #
#pragma interface DESTROY_exp_uncompiled


/* Operations for field location of union EXP */

#pragma token EXP const : unsigned : exp_location_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_location #
#pragma interface exp_location_tag IS_exp_location

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LOCATION) : exp_location_end #
#pragma interface exp_location_end

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_location_arg #
#pragma interface exp_location_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : LOCATION :,\
	EXP : EXP :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_location #
#pragma interface MAKE_exp_location

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_location #
#pragma interface DECONS_exp_location

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : LOCATION :,\
	EXP lvalue : EXP :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_location #
#pragma interface DESTROY_exp_location


/* Operations for field fail of union EXP */

#pragma token EXP const : unsigned : exp_fail_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_fail #
#pragma interface exp_fail_tag IS_exp_fail

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(string) : exp_fail_msg #
#pragma interface exp_fail_msg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : string :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_fail #
#pragma interface MAKE_exp_fail

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : string :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_fail #
#pragma interface DECONS_exp_fail

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : string :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_fail #
#pragma interface DESTROY_exp_fail


/* Operations for field token of union EXP */

#pragma token EXP const : unsigned : exp_token_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_token #
#pragma interface exp_token_tag IS_exp_token

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_token_parent #
#pragma interface exp_token_parent

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(IDENTIFIER) : exp_token_tok #
#pragma interface exp_token_tok

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(LIST(TOKEN)) : exp_token_args #
#pragma interface exp_token_args

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : IDENTIFIER :,\
	EXP : LIST(TOKEN) :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_token #
#pragma interface MAKE_exp_token

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(TOKEN) :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_token #
#pragma interface DECONS_exp_token

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(TOKEN) :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_token #
#pragma interface DESTROY_exp_token


/* Operations for field dummy of union EXP */

#pragma token EXP const : unsigned : exp_dummy_tag #
#pragma token PROC(EXP : EXP :) EXP : int : IS_exp_dummy #
#pragma interface exp_dummy_tag IS_exp_dummy

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(EXP) : exp_dummy_value #
#pragma interface exp_dummy_value

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(ulong_type) : exp_dummy_no #
#pragma interface exp_dummy_no

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(OFFSET) : exp_dummy_off #
#pragma interface exp_dummy_off

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_dummy_virt #
#pragma interface exp_dummy_virt

#pragma token PROC(EXP : EXP :)\
    EXP : PTR(int) : exp_dummy_cont #
#pragma interface exp_dummy_cont

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : EXP :,\
	EXP : ulong_type :,\
	EXP : OFFSET :,\
	EXP : int :,\
	EXP lvalue : EXP :\
    ) STATEMENT MAKE_exp_dummy #
#pragma interface MAKE_exp_dummy

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DECONS_exp_dummy #
#pragma interface DECONS_exp_dummy

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : EXP :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : int :,\
	EXP lvalue : int :,\
	EXP : EXP :\
    ) STATEMENT DESTROY_exp_dummy #
#pragma interface DESTROY_exp_dummy


#endif
