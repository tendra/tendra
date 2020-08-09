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

#ifndef OFF_OPS_H_INCLUDED
#define OFF_OPS_H_INCLUDED

/* Operations for union OFFSET */

#pragma token PROC(EXP : OFFSET :) EXP : unsigned : TAG_off #
#pragma interface TAG_off


/* Operations for field zero of union OFFSET */

#pragma token EXP const : unsigned : off_zero_tag #
#pragma token PROC(EXP : OFFSET :) EXP : int : IS_off_zero #
#pragma interface off_zero_tag IS_off_zero

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(TYPE) : off_zero_type #
#pragma interface off_zero_type

#pragma token PROC(\
	EXP : TYPE :,\
	EXP lvalue : OFFSET :\
    ) STATEMENT MAKE_off_zero #
#pragma interface MAKE_off_zero

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : OFFSET :\
    ) STATEMENT DECONS_off_zero #
#pragma interface DECONS_off_zero

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP : OFFSET :\
    ) STATEMENT DESTROY_off_zero #
#pragma interface DESTROY_off_zero


/* Operations for field type of union OFFSET */

#pragma token EXP const : unsigned : off_type_tag #
#pragma token PROC(EXP : OFFSET :) EXP : int : IS_off_type #
#pragma interface off_type_tag IS_off_type

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(TYPE) : off_type_type #
#pragma interface off_type_type

#pragma token PROC(\
	EXP : TYPE :,\
	EXP lvalue : OFFSET :\
    ) STATEMENT MAKE_off_type #
#pragma interface MAKE_off_type

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP : OFFSET :\
    ) STATEMENT DECONS_off_type #
#pragma interface DECONS_off_type

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP : OFFSET :\
    ) STATEMENT DESTROY_off_type #
#pragma interface DESTROY_off_type


/* Operations for field array of union OFFSET */

#pragma token EXP const : unsigned : off_array_tag #
#pragma token PROC(EXP : OFFSET :) EXP : int : IS_off_array #
#pragma interface off_array_tag IS_off_array

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(TYPE) : off_array_type #
#pragma interface off_array_type

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(unsigned) : off_array_arg #
#pragma interface off_array_arg

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : unsigned :,\
	EXP lvalue : OFFSET :\
    ) STATEMENT MAKE_off_array #
#pragma interface MAKE_off_array

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : unsigned :,\
	EXP : OFFSET :\
    ) STATEMENT DECONS_off_array #
#pragma interface DECONS_off_array

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : unsigned :,\
	EXP : OFFSET :\
    ) STATEMENT DESTROY_off_array #
#pragma interface DESTROY_off_array


/* Operations for field extra of union OFFSET */

#pragma token EXP const : unsigned : off_extra_tag #
#pragma token PROC(EXP : OFFSET :) EXP : int : IS_off_extra #
#pragma interface off_extra_tag IS_off_extra

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(TYPE) : off_extra_type #
#pragma interface off_extra_type

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(int) : off_extra_scale #
#pragma interface off_extra_scale

#pragma token PROC(\
	EXP : TYPE :,\
	EXP : int :,\
	EXP lvalue : OFFSET :\
    ) STATEMENT MAKE_off_extra #
#pragma interface MAKE_off_extra

#pragma token PROC(\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP : OFFSET :\
    ) STATEMENT DECONS_off_extra #
#pragma interface DECONS_off_extra

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : TYPE :,\
	EXP lvalue : int :,\
	EXP : OFFSET :\
    ) STATEMENT DESTROY_off_extra #
#pragma interface DESTROY_off_extra


/* Operations for field base of union OFFSET */

#pragma token EXP const : unsigned : off_base_tag #
#pragma token PROC(EXP : OFFSET :) EXP : int : IS_off_base #
#pragma interface off_base_tag IS_off_base

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(GRAPH) : off_base_graph #
#pragma interface off_base_graph

#pragma token PROC(\
	EXP : GRAPH :,\
	EXP lvalue : OFFSET :\
    ) STATEMENT MAKE_off_base #
#pragma interface MAKE_off_base

#pragma token PROC(\
	EXP lvalue : GRAPH :,\
	EXP : OFFSET :\
    ) STATEMENT DECONS_off_base #
#pragma interface DECONS_off_base

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : GRAPH :,\
	EXP : OFFSET :\
    ) STATEMENT DESTROY_off_base #
#pragma interface DESTROY_off_base


/* Operations for field deriv of union OFFSET */

#pragma token EXP const : unsigned : off_deriv_tag #
#pragma token PROC(EXP : OFFSET :) EXP : int : IS_off_deriv #
#pragma interface off_deriv_tag IS_off_deriv

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(GRAPH) : off_deriv_graph #
#pragma interface off_deriv_graph

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(OFFSET) : off_deriv_direct #
#pragma interface off_deriv_direct

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(OFFSET) : off_deriv_indirect #
#pragma interface off_deriv_indirect

#pragma token PROC(\
	EXP : GRAPH :,\
	EXP : OFFSET :,\
	EXP : OFFSET :,\
	EXP lvalue : OFFSET :\
    ) STATEMENT MAKE_off_deriv #
#pragma interface MAKE_off_deriv

#pragma token PROC(\
	EXP lvalue : GRAPH :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : OFFSET :,\
	EXP : OFFSET :\
    ) STATEMENT DECONS_off_deriv #
#pragma interface DECONS_off_deriv

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : OFFSET :,\
	EXP : OFFSET :\
    ) STATEMENT DESTROY_off_deriv #
#pragma interface DESTROY_off_deriv


/* Operations for field member of union OFFSET */

#pragma token EXP const : unsigned : off_member_tag #
#pragma token PROC(EXP : OFFSET :) EXP : int : IS_off_member #
#pragma interface off_member_tag IS_off_member

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(IDENTIFIER) : off_member_id #
#pragma interface off_member_id

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP lvalue : OFFSET :\
    ) STATEMENT MAKE_off_member #
#pragma interface MAKE_off_member

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP : OFFSET :\
    ) STATEMENT DECONS_off_member #
#pragma interface DECONS_off_member

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP : OFFSET :\
    ) STATEMENT DESTROY_off_member #
#pragma interface DESTROY_off_member


/* Operations for field ptr_mem of union OFFSET */

#pragma token EXP const : unsigned : off_ptr_mem_tag #
#pragma token PROC(EXP : OFFSET :) EXP : int : IS_off_ptr_mem #
#pragma interface off_ptr_mem_tag IS_off_ptr_mem

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(EXP) : off_ptr_mem_arg #
#pragma interface off_ptr_mem_arg

#pragma token PROC(\
	EXP : EXP :,\
	EXP lvalue : OFFSET :\
    ) STATEMENT MAKE_off_ptr_mem #
#pragma interface MAKE_off_ptr_mem

#pragma token PROC(\
	EXP lvalue : EXP :,\
	EXP : OFFSET :\
    ) STATEMENT DECONS_off_ptr_mem #
#pragma interface DECONS_off_ptr_mem

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : EXP :,\
	EXP : OFFSET :\
    ) STATEMENT DESTROY_off_ptr_mem #
#pragma interface DESTROY_off_ptr_mem


/* Operations for field negate of union OFFSET */

#pragma token EXP const : unsigned : off_negate_tag #
#pragma token PROC(EXP : OFFSET :) EXP : int : IS_off_negate #
#pragma interface off_negate_tag IS_off_negate

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(OFFSET) : off_negate_arg #
#pragma interface off_negate_arg

#pragma token PROC(\
	EXP : OFFSET :,\
	EXP lvalue : OFFSET :\
    ) STATEMENT MAKE_off_negate #
#pragma interface MAKE_off_negate

#pragma token PROC(\
	EXP lvalue : OFFSET :,\
	EXP : OFFSET :\
    ) STATEMENT DECONS_off_negate #
#pragma interface DECONS_off_negate

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : OFFSET :,\
	EXP : OFFSET :\
    ) STATEMENT DESTROY_off_negate #
#pragma interface DESTROY_off_negate


/* Operations for field plus of union OFFSET */

#pragma token EXP const : unsigned : off_plus_tag #
#pragma token PROC(EXP : OFFSET :) EXP : int : IS_off_plus #
#pragma interface off_plus_tag IS_off_plus

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(OFFSET) : off_plus_arg1 #
#pragma interface off_plus_arg1

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(OFFSET) : off_plus_arg2 #
#pragma interface off_plus_arg2

#pragma token PROC(\
	EXP : OFFSET :,\
	EXP : OFFSET :,\
	EXP lvalue : OFFSET :\
    ) STATEMENT MAKE_off_plus #
#pragma interface MAKE_off_plus

#pragma token PROC(\
	EXP lvalue : OFFSET :,\
	EXP lvalue : OFFSET :,\
	EXP : OFFSET :\
    ) STATEMENT DECONS_off_plus #
#pragma interface DECONS_off_plus

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : OFFSET :,\
	EXP : OFFSET :\
    ) STATEMENT DESTROY_off_plus #
#pragma interface DESTROY_off_plus


/* Operations for field mult of union OFFSET */

#pragma token EXP const : unsigned : off_mult_tag #
#pragma token PROC(EXP : OFFSET :) EXP : int : IS_off_mult #
#pragma interface off_mult_tag IS_off_mult

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(OFFSET) : off_mult_arg1 #
#pragma interface off_mult_arg1

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(EXP) : off_mult_arg2 #
#pragma interface off_mult_arg2

#pragma token PROC(\
	EXP : OFFSET :,\
	EXP : EXP :,\
	EXP lvalue : OFFSET :\
    ) STATEMENT MAKE_off_mult #
#pragma interface MAKE_off_mult

#pragma token PROC(\
	EXP lvalue : OFFSET :,\
	EXP lvalue : EXP :,\
	EXP : OFFSET :\
    ) STATEMENT DECONS_off_mult #
#pragma interface DECONS_off_mult

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : EXP :,\
	EXP : OFFSET :\
    ) STATEMENT DESTROY_off_mult #
#pragma interface DESTROY_off_mult


/* Operations for field ptr_diff of union OFFSET */

#pragma token EXP const : unsigned : off_ptr_diff_tag #
#pragma token PROC(EXP : OFFSET :) EXP : int : IS_off_ptr_diff #
#pragma interface off_ptr_diff_tag IS_off_ptr_diff

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(EXP) : off_ptr_diff_ptr1 #
#pragma interface off_ptr_diff_ptr1

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(EXP) : off_ptr_diff_ptr2 #
#pragma interface off_ptr_diff_ptr2

#pragma token PROC(\
	EXP : EXP :,\
	EXP : EXP :,\
	EXP lvalue : OFFSET :\
    ) STATEMENT MAKE_off_ptr_diff #
#pragma interface MAKE_off_ptr_diff

#pragma token PROC(\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : OFFSET :\
    ) STATEMENT DECONS_off_ptr_diff #
#pragma interface DECONS_off_ptr_diff

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : EXP :,\
	EXP lvalue : EXP :,\
	EXP : OFFSET :\
    ) STATEMENT DESTROY_off_ptr_diff #
#pragma interface DESTROY_off_ptr_diff


/* Operations for field token of union OFFSET */

#pragma token EXP const : unsigned : off_token_tag #
#pragma token PROC(EXP : OFFSET :) EXP : int : IS_off_token #
#pragma interface off_token_tag IS_off_token

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(IDENTIFIER) : off_token_tok #
#pragma interface off_token_tok

#pragma token PROC(EXP : OFFSET :)\
    EXP : PTR(LIST(TOKEN)) : off_token_args #
#pragma interface off_token_args

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : LIST(TOKEN) :,\
	EXP lvalue : OFFSET :\
    ) STATEMENT MAKE_off_token #
#pragma interface MAKE_off_token

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(TOKEN) :,\
	EXP : OFFSET :\
    ) STATEMENT DECONS_off_token #
#pragma interface DECONS_off_token

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : LIST(TOKEN) :,\
	EXP : OFFSET :\
    ) STATEMENT DESTROY_off_token #
#pragma interface DESTROY_off_token


#endif
