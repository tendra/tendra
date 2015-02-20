/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>

#include <parse/constant.h>
#include <parse/hash.h>
#include <parse/literal.h>

#include "exp_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "basetype.h"
#include "check.h"
#include "chktype.h"
#include "convert.h"
#include "derive.h"
#include "function.h"
#include "merge.h"
#include "namespace.h"
#include "syntax.h"
#include "tokdef.h"


/*
    This routine checks whether the offsets a and b are equal.  The co
    argument is passed through to eq_exp.
*/

int
eq_offset(OFFSET a, OFFSET b, int co)
{
	unsigned taga, tagb;

	/* Check for obvious equality */
	if (EQ_off(a, b)) {
		return 1;
	}
	if (IS_NULL_off(a)) {
		return 0;
	}
	if (IS_NULL_off(b)) {
		return 0;
	}

	/* Check tags */
	taga = TAG_off(a);
	tagb = TAG_off(b);
	if (taga != tagb) {
		return 0;
	}

	/* Check individual cases */
	assert(ORDER_off == 13);
	switch (TAG_off(a)) {
	case off_zero_tag: {
		/* Zero offsets */
		TYPE ta = DEREF_type(off_zero_type(a));
		TYPE tb = DEREF_type(off_zero_type(b));
		return eq_type_offset(ta, tb);
	}
	case off_type_tag: {
		/* Type offsets */
		TYPE ta = DEREF_type(off_type_type(a));
		TYPE tb = DEREF_type(off_type_type(b));
		return eq_type_offset(ta, tb);
	}
	case off_extra_tag: {
		/* Extra allocator offsets */
		TYPE ta = DEREF_type(off_extra_type(a));
		TYPE tb = DEREF_type(off_extra_type(b));
		int na = DEREF_int(off_extra_scale(a));
		int nb = DEREF_int(off_extra_scale(b));
		return na == nb && eq_type_offset(ta, tb);
	}
	case off_array_tag: {
		/* Array offsets */
		TYPE ta = DEREF_type(off_array_type(a));
		TYPE tb = DEREF_type(off_array_type(b));
		unsigned na = DEREF_unsigned(off_array_arg(a));
		unsigned nb = DEREF_unsigned(off_array_arg(b));
		return na == nb && eq_type_offset(ta, tb);
	}
	case off_base_tag: {
		/* Base class offsets */
		GRAPH ga = DEREF_graph(off_base_graph(a));
		GRAPH gb = DEREF_graph(off_base_graph(b));
		return eq_graph(ga, gb);
	}
	case off_deriv_tag: {
		/* Derived class offsets */
		GRAPH ga = DEREF_graph(off_deriv_graph(a));
		GRAPH gb = DEREF_graph(off_deriv_graph(b));
		return eq_graph(ga, gb);
	}
	case off_member_tag: {
		/* Member offsets */
		IDENTIFIER ia = DEREF_id(off_member_id(a));
		IDENTIFIER ib = DEREF_id(off_member_id(b));
		return EQ_id(ia, ib);
	}
	case off_ptr_mem_tag: {
		/* Pointer member offsets */
		EXP xa = DEREF_exp(off_ptr_mem_arg(a));
		EXP xb = DEREF_exp(off_ptr_mem_arg(b));
		return eq_exp(xa, xb, co);
	}
	case off_negate_tag: {
		/* Offset negation */
		OFFSET sa = DEREF_off(off_negate_arg(a));
		OFFSET sb = DEREF_off(off_negate_arg(b));
		return eq_offset(sa, sb, co);
	}
	case off_plus_tag: {
		/* Offset addition */
		OFFSET sa = DEREF_off(off_plus_arg1(a));
		OFFSET sb = DEREF_off(off_plus_arg1(b));
		OFFSET ta = DEREF_off(off_plus_arg2(a));
		OFFSET tb = DEREF_off(off_plus_arg2(b));
		if (eq_offset(sa, sb, co) && eq_offset(ta, tb, co)) {
			return 1;
		}
		if (co && eq_offset(sa, tb, 1) && eq_offset(ta, sb, 1)) {
			return 1;
		}
		return 0;
	}
	case off_mult_tag: {
		/* Offset multiplication */
		OFFSET sa = DEREF_off(off_mult_arg1(a));
		OFFSET sb = DEREF_off(off_mult_arg1(b));
		EXP za = DEREF_exp(off_mult_arg2(a));
		EXP zb = DEREF_exp(off_mult_arg2(b));
		return eq_offset(sa, sb, co) && eq_exp(za, zb, co);
	}
	case off_ptr_diff_tag: {
		/* Pointer difference */
		EXP xa = DEREF_exp(off_ptr_diff_ptr1(a));
		EXP xb = DEREF_exp(off_ptr_diff_ptr1(b));
		EXP za = DEREF_exp(off_ptr_diff_ptr2(a));
		EXP zb = DEREF_exp(off_ptr_diff_ptr2(b));
		return eq_exp(xa, xb, co) && eq_exp(za, zb, co);
	}
	case off_token_tag: {
		/* Token application */
		IDENTIFIER ia = DEREF_id(off_token_tok(a));
		IDENTIFIER ib = DEREF_id(off_token_tok(b));
		LIST(TOKEN)pa = DEREF_list(off_token_args(a));
		LIST(TOKEN)pb = DEREF_list(off_token_args(b));
		return eq_token_args(ia, ib, pa, pb);
	}
	}
	return 0;
}


/*
    This routine checks whether the expression lists p and q are equal,
    in the sense that each of their components is equal.  The co argument
    is passed through to eq_exp.
*/

static int
eq_exp_list(LIST(EXP)p, LIST(EXP)q, int co)
{
	unsigned np = LENGTH_list(p);
	unsigned nq = LENGTH_list(q);
	if (np != nq) {
		return 0;
	}
	while (!IS_NULL_list(p)) {
		EXP a = DEREF_exp(HEAD_list(p));
		EXP b = DEREF_exp(HEAD_list(q));
		if (!eq_exp(a, b, co)) {
			return 0;
		}
		p = TAIL_list(p);
		q = TAIL_list(q);
	}
	return 1;
}


/*
    This is an auxiliary routine for eq_exp which checks whether the
    expressions a and b, which have the same tag value, are equal.
*/

static int
eq_exp_aux(EXP a, EXP b, int co)
{
	/* Check expressions */
	assert(ORDER_exp == 88);
	switch (TAG_exp(a)) {
	case exp_identifier_tag:
	case exp_member_tag:
	case exp_ambiguous_tag:
	case exp_undeclared_tag: {
		/* Identifier expressions */
		IDENTIFIER ia = DEREF_id(exp_identifier_etc_id(a));
		IDENTIFIER ib = DEREF_id(exp_identifier_etc_id(b));
		return EQ_id(ia, ib);
	}
	case exp_int_lit_tag: {
		/* Integer literal expressions */
		TYPE ta = DEREF_type(exp_type(a));
		TYPE tb = DEREF_type(exp_type(b));
		NAT na = DEREF_nat(exp_int_lit_nat(a));
		NAT nb = DEREF_nat(exp_int_lit_nat(b));
		if (!eq_type(ta, tb)) {
			return 0;
		}
		if (EQ_nat(na, nb) || eq_nat(na, nb)) {
			return 1;
		}
		return 0;
	}
	case exp_float_lit_tag: {
		/* Floating literal expressions */
		TYPE ta = DEREF_type(exp_type(a));
		TYPE tb = DEREF_type(exp_type(b));
		FLOAT fa = DEREF_flt(exp_float_lit_flt(a));
		FLOAT fb = DEREF_flt(exp_float_lit_flt(b));
		if (!eq_type(ta, tb)) {
			return 0;
		}
		if (EQ_flt(fa, fb)) {
			return 1;
		}
		return eq_float_lit(fa, fb);
	}
	case exp_char_lit_tag: {
		/* Character literal expressions */
		TYPE ta = DEREF_type(exp_type(a));
		TYPE tb = DEREF_type(exp_type(b));
		STRING ca = DEREF_str(exp_char_lit_str(a));
		STRING cb = DEREF_str(exp_char_lit_str(b));
		if (!eq_type(ta, tb)) {
			return 0;
		}
		if (EQ_str(ca, cb)) {
			return 1;
		}
		return eq_string_lit(ca, cb);
	}
	case exp_string_lit_tag: {
		/* String literal expressions */
		TYPE ta = DEREF_type(exp_type(a));
		TYPE tb = DEREF_type(exp_type(b));
		STRING ca = DEREF_str(exp_string_lit_str(a));
		STRING cb = DEREF_str(exp_string_lit_str(b));
		if (!eq_type(ta, tb)) {
			return 0;
		}
		if (EQ_str(ca, cb)) {
			return 1;
		}
		return eq_string_lit(ca, cb);
	}
	case exp_null_tag:
	case exp_zero_tag:
	case exp_value_tag: {
		/* Null expressions */
		TYPE ta = DEREF_type(exp_type(a));
		TYPE tb = DEREF_type(exp_type(b));
		if (eq_type(ta, tb) == 1) {
			return 1;
		}
		return 0;
	}
	case exp_paren_tag:
	case exp_copy_tag: {
		/* Parenthesised expressions */
		EXP sa = DEREF_exp(exp_paren_etc_arg(a));
		EXP sb = DEREF_exp(exp_paren_etc_arg(b));
		return eq_exp(sa, sb, co);
	}
	case exp_assign_tag: {
		/* Assignment expressions */
		EXP ra = DEREF_exp(exp_assign_ref(a));
		EXP rb = DEREF_exp(exp_assign_ref(b));
		EXP sa = DEREF_exp(exp_assign_arg(a));
		EXP sb = DEREF_exp(exp_assign_arg(b));
		return eq_exp(ra, rb, co) && eq_exp(sa, sb, co);
	}
	case exp_init_tag: {
		/* Initialisation expressions */
		IDENTIFIER ia = DEREF_id(exp_init_id(a));
		IDENTIFIER ib = DEREF_id(exp_init_id(b));
		EXP sa = DEREF_exp(exp_init_arg(a));
		EXP sb = DEREF_exp(exp_init_arg(b));
		return EQ_id(ia, ib) && eq_exp(sa, sb, co);
	}
	case exp_preinc_tag: {
		/* Pre-increment expressions */
		EXP sa = DEREF_exp(exp_preinc_op(a));
		EXP sb = DEREF_exp(exp_preinc_op(b));
		return eq_exp(sa, sb, co);
	}
	case exp_postinc_tag: {
		/* Post-increment expressions */
		EXP sa = DEREF_exp(exp_postinc_op(a));
		EXP sb = DEREF_exp(exp_postinc_op(b));
		return eq_exp(sa, sb, co);
	}
	case exp_indir_tag: {
		/* Indirection expressions */
		EXP sa = DEREF_exp(exp_indir_ptr(a));
		EXP sb = DEREF_exp(exp_indir_ptr(b));
		return eq_exp(sa, sb, co);
	}
	case exp_contents_tag: {
		/* Contents expressions */
		EXP sa = DEREF_exp(exp_contents_ptr(a));
		EXP sb = DEREF_exp(exp_contents_ptr(b));
		return eq_exp(sa, sb, co);
	}
	case exp_address_tag: {
		/* Address expressions */
		EXP sa = DEREF_exp(exp_address_arg(a));
		EXP sb = DEREF_exp(exp_address_arg(b));
		return eq_exp(sa, sb, co);
	}
	case exp_address_mem_tag: {
		/* Address expressions */
		EXP sa = DEREF_exp(exp_address_mem_arg(a));
		EXP sb = DEREF_exp(exp_address_mem_arg(b));
		return eq_exp(sa, sb, co);
	}
	case exp_func_tag: {
		/* Function expressions */
		EXP sa = DEREF_exp(exp_func_fn(a));
		EXP sb = DEREF_exp(exp_func_fn(b));
		LIST(EXP)pa = DEREF_list(exp_func_args(a));
		LIST(EXP)pb = DEREF_list(exp_func_args(b));
		return eq_exp(sa, sb, co) && eq_exp_list(pa, pb, co);
	}
	case exp_func_id_tag: {
		/* Function expressions */
		IDENTIFIER ia = DEREF_id(exp_func_id_id(a));
		IDENTIFIER ib = DEREF_id(exp_func_id_id(b));
		LIST(EXP)pa = DEREF_list(exp_func_id_args(a));
		LIST(EXP)pb = DEREF_list(exp_func_id_args(b));
		return EQ_id(ia, ib) && eq_exp_list(pa, pb, co);
	}
	case exp_call_tag: {
		/* Member function call expressions */
		EXP ra = DEREF_exp(exp_call_ptr(a));
		EXP rb = DEREF_exp(exp_call_ptr(b));
		EXP sa = DEREF_exp(exp_call_arg(a));
		EXP sb = DEREF_exp(exp_call_arg(b));
		return eq_exp(ra, rb, co) && eq_exp(sa, sb, co);
	}
	case exp_negate_tag:
	case exp_compl_tag:
	case exp_not_tag:
	case exp_abs_tag: {
		/* Unary expressions */
		EXP sa = DEREF_exp(exp_negate_etc_arg(a));
		EXP sb = DEREF_exp(exp_negate_etc_arg(b));
		return eq_exp(sa, sb, co);
	}
	case exp_plus_tag:
	case exp_mult_tag:
	case exp_and_tag:
	case exp_or_tag:
	case exp_xor_tag:
	case exp_log_and_tag:
	case exp_log_or_tag:
	case exp_max_tag:
	case exp_min_tag: {
		/* Commutative binary expressions */
		EXP ra = DEREF_exp(exp_plus_etc_arg1(a));
		EXP rb = DEREF_exp(exp_plus_etc_arg1(b));
		EXP sa = DEREF_exp(exp_plus_etc_arg2(a));
		EXP sb = DEREF_exp(exp_plus_etc_arg2(b));
		if (eq_exp(ra, rb, co) && eq_exp(sa, sb, co)) {
			return 1;
		}
		if (co && eq_exp(ra, sb, 1) && eq_exp(sa, rb, 1)) {
			return 1;
		}
		return 0;
	}
	case exp_minus_tag:
	case exp_div_tag:
	case exp_rem_tag:
	case exp_lshift_tag:
	case exp_rshift_tag: {
		/* Non-commutative binary expressions */
		EXP ra = DEREF_exp(exp_plus_etc_arg1(a));
		EXP rb = DEREF_exp(exp_plus_etc_arg1(b));
		EXP sa = DEREF_exp(exp_plus_etc_arg2(a));
		EXP sb = DEREF_exp(exp_plus_etc_arg2(b));
		return eq_exp(ra, rb, co) && eq_exp(sa, sb, co);
	}
	case exp_test_tag: {
		/* Test expressions */
		NTEST ca = DEREF_ntest(exp_test_tst(a));
		NTEST cb = DEREF_ntest(exp_test_tst(b));
		EXP sa = DEREF_exp(exp_test_arg(a));
		EXP sb = DEREF_exp(exp_test_arg(b));
		if (ca != cb) {
			return 0;
		}
		return eq_exp(sa, sb, co);
	}
	case exp_compare_tag: {
		/* Comparison expressions */
		NTEST ca = DEREF_ntest(exp_compare_tst(a));
		NTEST cb = DEREF_ntest(exp_compare_tst(b));
		EXP ra = DEREF_exp(exp_compare_arg1(a));
		EXP rb = DEREF_exp(exp_compare_arg1(b));
		EXP sa = DEREF_exp(exp_compare_arg2(a));
		EXP sb = DEREF_exp(exp_compare_arg2(b));
		if (ca != cb) {
			return 0;
		}
		if (eq_exp(ra, rb, co) && eq_exp(sa, sb, co)) {
			return 1;
		}
		if (co && (ca == ntest_eq || ca == ntest_not_eq)) {
			/* Commutative comparisons */
			if (eq_exp(ra, sb, 1) && eq_exp(sa, rb, 1)) {
				return 1;
			}
		}
		return 0;
	}
	case exp_cast_tag: {
		/* Cast expressions */
		EXP sa = DEREF_exp(exp_cast_arg(a));
		EXP sb = DEREF_exp(exp_cast_arg(b));
		unsigned va = DEREF_unsigned(exp_cast_conv(a));
		unsigned vb = DEREF_unsigned(exp_cast_conv(b));
		return va == vb && eq_exp(sa, sb, co);
	}
	case exp_base_cast_tag: {
		/* Base cast expressions */
		EXP ra = DEREF_exp(exp_base_cast_arg(a));
		EXP rb = DEREF_exp(exp_base_cast_arg(b));
		OFFSET za = DEREF_off(exp_base_cast_off(a));
		OFFSET zb = DEREF_off(exp_base_cast_off(b));
		unsigned va = DEREF_unsigned(exp_base_cast_conv(a));
		unsigned vb = DEREF_unsigned(exp_base_cast_conv(b));
		if (va != vb) {
			return 0;
		}
		return eq_exp(ra, rb, co) && eq_offset(za, zb, co);
	}
	case exp_dyn_cast_tag: {
		/* Dynamic cast expressions */
		EXP sa = DEREF_exp(exp_dyn_cast_arg(a));
		EXP sb = DEREF_exp(exp_dyn_cast_arg(b));
		EXP ra = DEREF_exp(exp_dyn_cast_except(a));
		EXP rb = DEREF_exp(exp_dyn_cast_except(b));
		return eq_exp(sa, sb, co) && eq_exp(ra, rb, co);
	}
	case exp_add_ptr_tag: {
		/* Pointer addition expressions */
		EXP ra = DEREF_exp(exp_add_ptr_ptr(a));
		EXP rb = DEREF_exp(exp_add_ptr_ptr(b));
		OFFSET za = DEREF_off(exp_add_ptr_off(a));
		OFFSET zb = DEREF_off(exp_add_ptr_off(b));
		return eq_exp(ra, rb, co) && eq_offset(za, zb, co);
	}
	case exp_offset_size_tag: {
		/* Offset size expressions */
		OFFSET xa = DEREF_off(exp_offset_size_off(a));
		OFFSET xb = DEREF_off(exp_offset_size_off(b));
		TYPE sa = DEREF_type(exp_offset_size_step(a));
		TYPE sb = DEREF_type(exp_offset_size_step(b));
		return eq_offset(xa, xb, co) && eq_type_offset(sa, sb);
	}
	case exp_constr_tag: {
		/* Constructors */
		EXP sa = DEREF_exp(exp_constr_call(a));
		EXP sb = DEREF_exp(exp_constr_call(b));
		return eq_exp(sa, sb, co);
	}
	case exp_destr_tag: {
		/* Destructors */
		EXP sa = DEREF_exp(exp_destr_call(a));
		EXP sb = DEREF_exp(exp_destr_call(b));
		return eq_exp(sa, sb, co);
	}
	case exp_alloc_tag: {
		/* Allocators */
		EXP sa = DEREF_exp(exp_alloc_call(a));
		EXP sb = DEREF_exp(exp_alloc_call(b));
		EXP ra = DEREF_exp(exp_alloc_init(a));
		EXP rb = DEREF_exp(exp_alloc_init(b));
		return eq_exp(sa, sb, co) && eq_exp(ra, rb, co);
	}
	case exp_dealloc_tag: {
		/* Deallocators */
		EXP sa = DEREF_exp(exp_dealloc_call(a));
		EXP sb = DEREF_exp(exp_dealloc_call(b));
		EXP ra = DEREF_exp(exp_dealloc_term(a));
		EXP rb = DEREF_exp(exp_dealloc_term(b));
		return eq_exp(sa, sb, co) && eq_exp(ra, rb, co);
	}
	case exp_rtti_tag: {
		/* Run-time type information */
		EXP sa = DEREF_exp(exp_rtti_arg(a));
		EXP sb = DEREF_exp(exp_rtti_arg(b));
		EXP ra = DEREF_exp(exp_rtti_except(a));
		EXP rb = DEREF_exp(exp_rtti_except(b));
		int ia = DEREF_int(exp_rtti_op(a));
		int ib = DEREF_int(exp_rtti_op(b));
		if (ia != ib) {
			return 0;
		}
		return eq_exp(sa, sb, co) && eq_exp(ra, rb, co);
	}
	case exp_rtti_type_tag: {
		/* Run-time type information */
		TYPE sa = DEREF_type(exp_rtti_type_arg(a));
		TYPE sb = DEREF_type(exp_rtti_type_arg(b));
		int ia = DEREF_int(exp_rtti_type_op(a));
		int ib = DEREF_int(exp_rtti_type_op(b));
		if (ia != ib) {
			return 0;
		}
		if (eq_type(sa, sb) == 1) {
			return 1;
		}
		return 0;
	}
	case exp_rtti_no_tag: {
		/* Link-time type information */
		TYPE sa = DEREF_type(exp_rtti_no_arg(a));
		TYPE sb = DEREF_type(exp_rtti_no_arg(b));
		if (eq_type(sa, sb) == 1) {
			return 1;
		}
		return 0;
	}
	case exp_dynamic_tag: {
		/* Dynamic initialisers */
		EXP sa = DEREF_exp(exp_dynamic_arg(a));
		EXP sb = DEREF_exp(exp_dynamic_arg(b));
		return eq_exp(sa, sb, co);
	}
	case exp_aggregate_tag: {
		/* Aggregate initialisers */
		LIST(EXP)pa = DEREF_list(exp_aggregate_args(a));
		LIST(EXP)pb = DEREF_list(exp_aggregate_args(b));
		return eq_exp_list(pa, pb, co);
	}
	case exp_initialiser_tag: {
		/* Function style initialisers */
		LIST(EXP)pa = DEREF_list(exp_initialiser_args(a));
		LIST(EXP)pb = DEREF_list(exp_initialiser_args(b));
		return eq_exp_list(pa, pb, co);
	}
	case exp_nof_tag: {
		/* Array initialisers */
		EXP ra = DEREF_exp(exp_nof_start(a));
		EXP rb = DEREF_exp(exp_nof_start(b));
		EXP sa = DEREF_exp(exp_nof_pad(a));
		EXP sb = DEREF_exp(exp_nof_pad(b));
		NAT na = DEREF_nat(exp_nof_size(a));
		NAT nb = DEREF_nat(exp_nof_size(b));
		EXP ua = DEREF_exp(exp_nof_end(a));
		EXP ub = DEREF_exp(exp_nof_end(b));
		if (!EQ_nat(na, nb)) {
			if (!eq_nat(na, nb)) {
				return 0;
			}
		}
		if (!eq_exp(sa, sb, co)) {
			return 0;
		}
		return eq_exp(ra, rb, co) && eq_exp(ua, ub, co);
	}
	case exp_comma_tag: {
		/* Comma expressions */
		LIST(EXP)pa = DEREF_list(exp_comma_args(a));
		LIST(EXP)pb = DEREF_list(exp_comma_args(b));
		return eq_exp_list(pa, pb, co);
	}
	case exp_set_tag:
	case exp_unused_tag: {
		/* Flow analysis expressions */
		EXP sa = DEREF_exp(exp_set_etc_arg(a));
		EXP sb = DEREF_exp(exp_set_etc_arg(b));
		return eq_exp(sa, sb, co);
	}
	case exp_if_stmt_tag: {
		/* Conditional expressions */
		EXP ca = DEREF_exp(exp_if_stmt_cond(a));
		EXP cb = DEREF_exp(exp_if_stmt_cond(b));
		EXP ra = DEREF_exp(exp_if_stmt_true_code(a));
		EXP rb = DEREF_exp(exp_if_stmt_true_code(b));
		EXP sa = DEREF_exp(exp_if_stmt_false_code(a));
		EXP sb = DEREF_exp(exp_if_stmt_false_code(b));
		if (!eq_exp(ca, cb, co)) {
			return 0;
		}
		return eq_exp(ra, rb, co) && eq_exp(sa, sb, co);
	}
	case exp_exception_tag: {
		/* Throw expressions */
		EXP sa = DEREF_exp(exp_exception_arg(a));
		EXP sb = DEREF_exp(exp_exception_arg(b));
		return eq_exp(sa, sb, co);
	}
	case exp_thrown_tag: {
		/* Thrown expressions */
		TYPE ta = DEREF_type(exp_type(a));
		TYPE tb = DEREF_type(exp_type(b));
		if (eq_type(ta, tb) == 1) {
			return 1;
		}
		return 0;
	}
	case exp_op_tag: {
		/* Undetermined expressions */
		int ca = DEREF_int(exp_op_lex(a));
		int cb = DEREF_int(exp_op_lex(b));
		EXP ra = DEREF_exp(exp_op_arg1(a));
		EXP rb = DEREF_exp(exp_op_arg1(b));
		EXP sa = DEREF_exp(exp_op_arg2(a));
		EXP sb = DEREF_exp(exp_op_arg2(b));
		if (ca != cb) {
			return 0;
		}
		return eq_exp(ra, rb, co) && eq_exp(sa, sb, co);
	}
	case exp_opn_tag: {
		/* Undetermined expressions */
		int ca = DEREF_int(exp_opn_lex(a));
		int cb = DEREF_int(exp_opn_lex(b));
		LIST(EXP)pa = DEREF_list(exp_opn_args(a));
		LIST(EXP)pb = DEREF_list(exp_opn_args(b));
		if (ca != cb) {
			return 0;
		}
		return eq_exp_list(pa, pb, co);
	}
	case exp_assembler_tag: {
		/* Assembler expressions */
		STRING ca = DEREF_str(exp_assembler_op(a));
		STRING cb = DEREF_str(exp_assembler_op(b));
		if (EQ_str(ca, cb) || eq_string_lit(ca, cb)) {
			LIST(EXP)pa = DEREF_list(exp_assembler_args(a));
			LIST(EXP)pb = DEREF_list(exp_assembler_args(b));
			return eq_exp_list(pa, pb, co);
		}
		break;
	}
	case exp_location_tag: {
		/* Location expressions */
		EXP sa = DEREF_exp(exp_location_arg(a));
		EXP sb = DEREF_exp(exp_location_arg(b));
		return eq_exp(sa, sb, co);
	}
	case exp_token_tag: {
		/* Token application */
		IDENTIFIER ia = DEREF_id(exp_token_tok(a));
		IDENTIFIER ib = DEREF_id(exp_token_tok(b));
		LIST(TOKEN)pa = DEREF_list(exp_token_args(a));
		LIST(TOKEN)pb = DEREF_list(exp_token_args(b));
		return eq_token_args(ia, ib, pa, pb);
	}
	case exp_dummy_tag: {
		/* Dummy expressions */
		EXP sa = DEREF_exp(exp_dummy_value(a));
		EXP sb = DEREF_exp(exp_dummy_value(b));
		return eq_exp(sa, sb, co);
	}
	case exp_reach_tag:
	case exp_unreach_tag:
	case exp_sequence_tag:
	case exp_solve_stmt_tag:
	case exp_decl_stmt_tag:
	case exp_while_stmt_tag:
	case exp_do_stmt_tag:
	case exp_switch_stmt_tag:
	case exp_hash_if_tag:
	case exp_return_stmt_tag:
	case exp_goto_stmt_tag:
	case exp_label_stmt_tag:
	case exp_try_block_tag:
	case exp_handler_tag:
	case exp_uncompiled_tag:
	case exp_fail_tag: {
		/* Statements are never equal */
		return 0;
	}
	}
	return 0;
}


/*
    This routine unifies the expressions a and b by defining tokens as
    necessary.  It returns true if a value is assigned to a token.  Note
    that it is necessary to consider integer constant tokens as well as
    expression tokens.
*/

static int
unify_exp(EXP a, EXP b)
{
	IDENTIFIER id;
	LIST(TOKEN)args;
	switch (TAG_exp(a)) {
	case exp_token_tag: {
		id = DEREF_id(exp_token_tok(a));
		args = DEREF_list(exp_token_args(a));
		break;
	}
	case exp_int_lit_tag: {
		NAT n = DEREF_nat(exp_int_lit_nat(a));
		if (!IS_nat_token(n)) {
			return 0;
		}
		id = DEREF_id(nat_token_tok(n));
		args = DEREF_list(nat_token_args(n));
		break;
	}
	default:
		return 0;
	}
	if (IS_NULL_list(args) && defining_token(id)) {
		return define_exp_token(id, b, 1);
	}
	return 0;
}


/*
    This routine checks whether the expressions a and b are equal.  If
    co is true then commutivity and other such relations are taken
    into account.
*/

int
eq_exp(EXP a, EXP b, int co)
{
	/* Check for obvious equality */
	unsigned ta, tb;
	if (EQ_exp(a, b)) {
		return 1;
	}
	if (IS_NULL_exp(a)) {
		return 0;
	}
	if (IS_NULL_exp(b)) {
		return 0;
	}

	/* Allow for parentheses */
	ta = TAG_exp(a);
	while (ta == exp_paren_tag || ta == exp_copy_tag) {
		a = DEREF_exp(exp_paren_etc_arg(a));
		ta = TAG_exp(a);
	}
	tb = TAG_exp(b);
	while (tb == exp_paren_tag || tb == exp_copy_tag) {
		b = DEREF_exp(exp_paren_etc_arg(b));
		tb = TAG_exp(b);
	}

	/* Check equality of expressions */
	if (ta == tb && eq_exp_aux(a, b, co)) {
		return 1;
	}
	if (force_tokdef || force_template || expand_tokdef) {
		TYPE sa = DEREF_type(exp_type(a));
		TYPE sb = DEREF_type(exp_type(b));
		if (eq_type(sa, sb) == 1) {
			if (unify_exp(a, b)) {
				return 1;
			}
			if (unify_exp(b, a)) {
				return 1;
			}
		}
	}
	return 0;
}


/*
    This routine is similar to eq_exp, but it disallows token and template
    unification and does not allow for commutivity relations.
*/

int
eq_exp_exact(EXP a, EXP b)
{
	int eq;
	int tok = force_tokdef;
	int templ = force_template;
	force_tokdef = 0;
	force_template = 0;
	eq = eq_exp(a, b, 0);
	force_template = templ;
	force_tokdef = tok;
	return eq;
}


/*
    This routine checks whether the tokens a and b are equal.
*/

int
eq_token(TOKEN a, TOKEN b)
{
	unsigned na, nb;
	if (EQ_tok(a, b)) {
		return 1;
	}
	if (IS_NULL_tok(a)) {
		return 0;
	}
	if (IS_NULL_tok(b)) {
		return 0;
	}
	na = TAG_tok(a);
	nb = TAG_tok(b);
	if (na != nb) {
		return 0;
	}
	switch (na) {
	case tok_exp_tag: {
		EXP va = DEREF_exp(tok_exp_value(a));
		EXP vb = DEREF_exp(tok_exp_value(b));
		return eq_exp(va, vb, 0);
	}
	case tok_stmt_tag: {
		EXP va = DEREF_exp(tok_stmt_value(a));
		EXP vb = DEREF_exp(tok_stmt_value(b));
		return eq_exp(va, vb, 0);
	}
	case tok_nat_tag:
	case tok_snat_tag: {
		NAT va = DEREF_nat(tok_nat_etc_value(a));
		NAT vb = DEREF_nat(tok_nat_etc_value(b));
		if (compare_nat(va, vb) == 0) {
			return 1;
		}
		break;
	}
	case tok_type_tag: {
		TYPE va = DEREF_type(tok_type_value(a));
		TYPE vb = DEREF_type(tok_type_value(b));
		if (eq_type(va, vb) == 1) {
			return 1;
		}
		return 0;
	}
	case tok_member_tag: {
		OFFSET va = DEREF_off(tok_member_value(a));
		OFFSET vb = DEREF_off(tok_member_value(b));
		return eq_offset(va, vb, 0);
	}
	case tok_class_tag: {
		IDENTIFIER ia = DEREF_id(tok_class_value(a));
		IDENTIFIER ib = DEREF_id(tok_class_value(b));
		return EQ_id(ia, ib);
	}
	}
	return 0;
}


/*
    This routine checks whether the token applications ia ( pa ) and
    ib ( pb ) are equal.
*/

int
eq_token_args(IDENTIFIER ia, IDENTIFIER ib, LIST(TOKEN)pa, LIST(TOKEN)pb)
{
	if (!EQ_id(ia, ib)) {
		/* Check that tokens are the same */
		ia = DEREF_id(id_alias(ia));
		ib = DEREF_id(id_alias(ib));
		if (!EQ_id(ia, ib)) {
			if (!force_merge || !merge_type(ia, ib)) {
				return 0;
			}
		}
	}
	if (EQ_list(pa, pb)) {
		return 1;
	}
	if (LENGTH_list(pa)!= LENGTH_list(pb)) {
		return 0;
	}
	while (!IS_NULL_list(pa)) {
		TOKEN a, b;
		if (EQ_list(pa, pb)) {
			return 1;
		}
		a = DEREF_tok(HEAD_list(pa));
		b = DEREF_tok(HEAD_list(pb));
		if (!eq_token(a, b)) {
			return 0;
		}
		pb = TAIL_list(pb);
		pa = TAIL_list(pa);
	}
	return 1;
}


/*
    This routine checks whether the token id applied to the arguments args
    is a constant.
*/

static int
is_const_token(IDENTIFIER id, LIST(TOKEN)args, int c)
{
	TOKEN tok = DEREF_tok(id_token_sort(id));
	if (IS_tok_proc(tok)) {
		/* Allow for procedure tokens */
		tok = DEREF_tok(tok_proc_res(tok));
	}
	switch (TAG_tok(tok)) {
	case tok_exp_tag: {
		/* Check for constant expression tokens */
		int cn = DEREF_int(tok_exp_constant(tok));
		if (cn) {
			/* Constant token */
			return 1;
		}
		if (c >= 0) {
			/* Constant expression expected */
			report(crt_loc, ERR_token_const(id));
		}
		if (option(OPT_token_const) == OPTION_DISALLOW) {
			/* Non-constant tokens not allowed */
			return 0;
		}
		break;
	}
	case tok_nat_tag: {
		/* Integer constants */
		return 1;
	}
	case tok_stmt_tag: {
		/* Statements are not constant */
		return 0;
	}
	}

	/* Check all token arguments */
	while (!IS_NULL_list(args)) {
		TOKEN a = DEREF_tok(HEAD_list(args));
		if (!IS_NULL_tok(a)) {
			switch (TAG_tok(a)) {
			case tok_exp_tag: {
				EXP e = DEREF_exp(tok_exp_value(a));
				if (!is_const_exp(e, c)) {
					return 0;
				}
				break;
			}
			case tok_stmt_tag: {
				EXP e = DEREF_exp(tok_stmt_value(a));
				if (!is_const_exp(e, c)) {
					return 0;
				}
				break;
			}
			case tok_member_tag: {
				OFFSET off = DEREF_off(tok_member_value(a));
				if (!is_const_offset(off, c, 1)) {
					return 0;
				}
				break;
			}
			}
		}
		args = TAIL_list(args);
	}
	return 1;
}


/*
    This routine checks whether the offset off is a constant offset.  virt
    is true if virtual base classes are to be taken into account.
*/

int
is_const_offset(OFFSET off, int c, int virt)
{
	assert(ORDER_off == 13);
	switch (TAG_off(off)) {
	case off_zero_tag:
	case off_type_tag:
	case off_extra_tag:
	case off_array_tag:
	case off_member_tag: {
		/* Constant offsets */
		return 1;
	}
	case off_base_tag: {
		/* Base class offsets */
		if (virt) {
			GRAPH gr = DEREF_graph(off_base_graph(off));
			DECL_SPEC acc = DEREF_dspec(graph_access(gr));
			if (!(acc & dspec_mutable)) {
				return 1;
			}
		} else {
			return 1;
		}
		break;
	}
	case off_deriv_tag: {
		/* Derived class offsets */
		if (virt) {
			GRAPH gr = DEREF_graph(off_deriv_graph(off));
			DECL_SPEC acc = DEREF_dspec(graph_access(gr));
			if (!(acc & dspec_mutable)) {
				return 1;
			}
		} else {
			return 1;
		}
		break;
	}
	case off_ptr_mem_tag: {
		/* Pointer member offsets */
		EXP a = DEREF_exp(off_ptr_mem_arg(off));
		return is_const_exp(a, c);
	}
	case off_negate_tag: {
		/* Offset negation */
		OFFSET off1 = DEREF_off(off_negate_arg(off));
		return is_const_offset(off1, c, 1);
	}
	case off_plus_tag: {
		/* Offset addition */
		OFFSET off1 = DEREF_off(off_plus_arg1(off));
		OFFSET off2 = DEREF_off(off_plus_arg2(off));
		if (!is_const_offset(off1, c, 1)) {
			return 0;
		}
		return is_const_offset(off2, c, 1);
	}
	case off_mult_tag: {
		/* Offset multiplication */
		OFFSET off1 = DEREF_off(off_mult_arg1(off));
		EXP a = DEREF_exp(off_mult_arg2(off));
		if (!is_const_offset(off1, c, 1)) {
			return 0;
		}
		return is_const_exp(a, c);
	}
	case off_ptr_diff_tag: {
		/* Pointer difference */
		EXP a = DEREF_exp(off_ptr_diff_ptr1(off));
		EXP b = DEREF_exp(off_ptr_diff_ptr2(off));
		if (is_const_exp(a, c) && is_const_exp(b, c)) {
			/* Only allow pointers from same array */
			EXP pa = NULL_exp;
			EXP pb = NULL_exp;
			IGNORE find_exp_linkage(a, &pa, 1);
			IGNORE find_exp_linkage(b, &pb, 1);
			if (!IS_NULL_exp(pa) && !IS_exp_string_lit(pa)) {
				return eq_exp(pa, pb, 0);
			}
		}
		break;
	}
	case off_token_tag: {
		/* All member tokens are constant */
		IDENTIFIER id = DEREF_id(off_token_tok(off));
		LIST(TOKEN)args = DEREF_list(off_token_args(off));
		return is_const_token(id, args, c);
	}
	}
	return 0;
}


/*
    This routine checks whether the address of e is a constant expression.
    c will be nonzero.
*/

static int
is_const_addr(EXP e, int c)
{
	if (IS_NULL_exp(e)) {
		return 1;
	}
	switch (TAG_exp(e)) {
	case exp_identifier_tag: {
		/* Identifier expressions */
		IDENTIFIER id = DEREF_id(exp_identifier_id(e));
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (!(ds & dspec_auto)) {
			TYPE t = DEREF_type(exp_type(e));
			if (!IS_type_ref(t)) {
				return 1;
			}
		}
		break;
	}
	case exp_indir_tag: {
		/* Indirection expressions */
		EXP a = DEREF_exp(exp_indir_ptr(e));
		return is_const_exp(a, c);
	}
	case exp_member_tag:
	case exp_string_lit_tag:
	case exp_rtti_type_tag: {
		/* lvalue expressions */
		return 1;
	}
	case exp_token_tag: {
		/* Tokenised expressions */
		return is_const_exp(e, c);
	}
	case exp_comma_tag: {
		/* Comma expressions (not allowed) */
		if (c < 0) {
			LIST(EXP)p = DEREF_list(exp_comma_args(e));
			while (!IS_NULL_list(p)) {
				EXP a = DEREF_exp(HEAD_list(p));
				p = TAIL_list(p);
				if (IS_NULL_list(p)) {
					return is_const_addr(a, c);
				}
				if (!is_const_exp(a, c)) {
					break;
				}
			}
		}
		break;
	}
	case exp_if_stmt_tag: {
		/* Conditional expressions */
		EXP d = DEREF_exp(exp_if_stmt_cond(e));
		EXP a = DEREF_exp(exp_if_stmt_true_code(e));
		EXP b = DEREF_exp(exp_if_stmt_false_code(e));
		if (!is_const_exp(d, c)) {
			break;
		}
		if (!is_const_addr(a, c)) {
			break;
		}
		return is_const_addr(b, c);
	}
	}
	return 0;
}


/*
    This routine checks whether e is a constant expression.  Note that
    most integer constant expressions are dealt with in a bottom-up
    fashion by means of the constant evaluation routines.  Other
    constants are dealt with in a top-down fashion by this routine.  If
    c is 0 then only valid integer constant expressions are allowed; c
    is -1 then only a check is intended.
*/

int
is_const_exp(EXP e, int c)
{
	TYPE t;
	if (IS_NULL_exp(e)) {
		return 1;
	}
	assert(ORDER_exp == 88);
	switch (TAG_exp(e)) {
	case exp_int_lit_tag:
	case exp_char_lit_tag: {
		/* Integer literals */
		return 1;
	}
	case exp_identifier_tag: {
		/* Identifiers */
		if (c) {
			IDENTIFIER id = DEREF_id(exp_identifier_id(e));
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (!(ds & dspec_auto)) {
				t = DEREF_type(exp_type(e));
				if (!IS_type_ref(t)) {
					return 1;
				}
			}
		}
		break;
	}
	case exp_string_lit_tag:
	case exp_float_lit_tag:
	case exp_null_tag:
	case exp_zero_tag:
	case exp_value_tag:
	case exp_rtti_type_tag:
	case exp_rtti_no_tag:
	case exp_set_tag:
	case exp_unused_tag: {
		/* Floating literals, null pointers etc. */
		if (c) {
			return 1;
		}
		break;
	}
	case exp_paren_tag:
	case exp_copy_tag: {
		/* Parenthesised expressions */
		EXP a = DEREF_exp(exp_paren_etc_arg(e));
		return is_const_exp(a, c);
	}
	case exp_indir_tag: {
		/* Indirection expressions */
		if (c) {
			EXP a = DEREF_exp(exp_indir_ptr(e));
			return is_const_exp(a, c);
		}
		break;
	}
	case exp_address_tag: {
		/* Address expressions */
		if (c) {
			EXP a = DEREF_exp(exp_address_arg(e));
			return is_const_addr(a, c);
		}
		break;
	}
	case exp_address_mem_tag: {
		/* Address expressions */
		if (c) {
			EXP a = DEREF_exp(exp_address_mem_arg(e));
			if (IS_exp_member(a)) {
				return 1;
			}
		}
		break;
	}
	case exp_negate_tag:
	case exp_compl_tag:
	case exp_not_tag:
	case exp_abs_tag: {
		/* Unary expressions */
		EXP a = DEREF_exp(exp_negate_etc_arg(e));
		return is_const_exp(a, c);
	}
	case exp_plus_tag:
	case exp_minus_tag:
	case exp_mult_tag:
	case exp_and_tag:
	case exp_or_tag:
	case exp_xor_tag:
	case exp_log_and_tag:
	case exp_log_or_tag:
	case exp_lshift_tag:
	case exp_rshift_tag:
	case exp_max_tag:
	case exp_min_tag: {
		/* Binary expressions */
		EXP a = DEREF_exp(exp_plus_etc_arg1(e));
		EXP b = DEREF_exp(exp_plus_etc_arg2(e));
		return is_const_exp(a, c) && is_const_exp(b, c);
	}
	case exp_div_tag:
	case exp_rem_tag: {
		/* Division expressions */
		EXP a = DEREF_exp(exp_plus_etc_arg1(e));
		EXP b = DEREF_exp(exp_plus_etc_arg2(e));
		if (c == 0 && is_zero_exp(b)) {
			/* Division by zero doesn't count */
			break;
		}
		return is_const_exp(a, c) && is_const_exp(b, c);
	}
	case exp_test_tag: {
		/* Test expressions */
		EXP a = DEREF_exp(exp_test_arg(e));
		return is_const_exp(a, c);
	}
	case exp_compare_tag: {
		/* Comparison expressions */
		EXP a = DEREF_exp(exp_compare_arg1(e));
		EXP b = DEREF_exp(exp_compare_arg2(e));
		return is_const_exp(a, c) && is_const_exp(b, c);
	}
	case exp_cast_tag: {
		/* Cast expressions */
		EXP a = DEREF_exp(exp_cast_arg(e));
		if (!c) {
			unsigned tc;
			t = DEREF_type(exp_type(a));
			tc = type_category(&t);
			if (!IS_TYPE_INT(tc)) {
				break;
			}
		}
		return is_const_exp(a, c);
	}
	case exp_base_cast_tag: {
		/* Base cast expressions */
		if (c) {
			EXP a = DEREF_exp(exp_base_cast_arg(e));
			OFFSET off = DEREF_off(exp_base_cast_off(e));
			unsigned conv = DEREF_unsigned(exp_base_cast_conv(e));
			if (conv & CONV_PTR_MEM_BASE) {
				/* Pointer to member conversions */
				if (conv & CONV_REVERSE) {
					return 0;
				}
			} else {
				/* Pointer conversions */
				if (!is_zero_offset(off)) {
					return 0;
				}
			}
			return is_const_exp(a, c);
		}
		break;
	}
	case exp_add_ptr_tag: {
		/* Pointer addition */
		if (c) {
			t = DEREF_type(exp_type(e));
			if (!IS_type_ref(t)) {
				EXP a = DEREF_exp(exp_add_ptr_ptr(e));
				OFFSET b = DEREF_off(exp_add_ptr_off(e));
				int v = DEREF_int(exp_add_ptr_virt(e));
				if (!is_const_exp(a, c)) {
					return 0;
				}
				return is_const_offset(b, c, v);
			}
		}
		break;
	}
	case exp_offset_size_tag: {
		/* Offset size */
		OFFSET a = DEREF_off(exp_offset_size_off(e));
		if (IS_off_type(a)) {
			/* Allow for sizeof expressions */
			TYPE s = DEREF_type(exp_offset_size_step(e));
			if (EQ_type(s, type_char)) {
				return 1;
			}
		}
		if (c) {
			return is_const_offset(a, c, c);
		}
		break;
	}
	case exp_aggregate_tag: {
		/* Aggregate initialisers */
		if (c) {
			LIST(EXP)p = DEREF_list(exp_aggregate_args(e));
			while (!IS_NULL_list(p)) {
				EXP a = DEREF_exp(HEAD_list(p));
				if (!is_const_exp(a, c)) {
					return 0;
				}
				p = TAIL_list(p);
			}
			return 1;
		}
		break;
	}
	case exp_nof_tag: {
		/* Array initialisers */
		if (c) {
			EXP a = DEREF_exp(exp_nof_start(e));
			EXP b = DEREF_exp(exp_nof_pad(e));
			EXP d = DEREF_exp(exp_nof_end(e));
			if (!is_const_exp(a, c)) {
				return 0;
			}
			if (!is_const_exp(b, c)) {
				return 0;
			}
			return is_const_exp(d, c);
		}
		break;
	}
	case exp_comma_tag: {
		/* Comma expressions (not allowed) */
		if (c < 0) {
			LIST(EXP)p = DEREF_list(exp_comma_args(e));
			while (!IS_NULL_list(p)) {
				EXP a = DEREF_exp(HEAD_list(p));
				if (!is_const_exp(a, c)) {
					return 0;
				}
				p = TAIL_list(p);
			}
			return 1;
		}
		break;
	}
	case exp_if_stmt_tag: {
		/* Conditional expressions */
		if (c) {
			EXP d = DEREF_exp(exp_if_stmt_cond(e));
			EXP a = DEREF_exp(exp_if_stmt_true_code(e));
			EXP b = DEREF_exp(exp_if_stmt_false_code(e));
			if (!is_const_exp(d, c)) {
				break;
			}
			if (!is_const_exp(a, c)) {
				break;
			}
			return is_const_exp(b, c);
		}
		break;
	}
	case exp_op_tag: {
		/* Undetermined expressions */
		EXP a = DEREF_exp(exp_op_arg1(e));
		EXP b = DEREF_exp(exp_op_arg2(e));
		return is_const_exp(a, c) && is_const_exp(b, c);
	}
	case exp_opn_tag: {
		/* Undetermined nary expressions */
		LIST(EXP)p = DEREF_list(exp_opn_args(e));
		while (!IS_NULL_list(p)) {
			EXP a = DEREF_exp(HEAD_list(p));
			if (!is_const_exp(a, c)) {
				return 0;
			}
			p = TAIL_list(p);
		}
		return 1;
	}
	case exp_token_tag: {
		/* Tokenised expressions (C compatibility) */
		IDENTIFIER id = DEREF_id(exp_token_tok(e));
		LIST(TOKEN)args = DEREF_list(exp_token_args(e));
		if (!c) {
			unsigned tc;
			t = DEREF_type(exp_type(e));
			tc = type_category(&t);
			if (!IS_TYPE_INT(tc)) {
				break;
			}
		}
		return is_const_token(id, args, c);
	}
	case exp_location_tag: {
		/* Location expressions */
		EXP a = DEREF_exp(exp_location_arg(e));
		return is_const_exp(a, c);
	}
	case exp_dummy_tag: {
		/* Dummy expressions */
		EXP a = DEREF_exp(exp_dummy_value(e));
		return is_const_exp(a, c);
	}
	}

	/* Allow for errors */
	t = DEREF_type(exp_type(e));
	if (IS_type_error(t)) {
		return 1;
	}
	return 0;
}


/*
    Certain evaluations on integer constant expressions are only valid
    if it can be shown that the operands cannot raise an exception.
    For example, 'a - a' can only safely be replaced by zero if the
    evaluation of a does not overflow.  This routine returns true if
    the evaluation of the expression a may raise an overflow exception
    or contains some other side effect.
*/

int
overflow_exp(EXP a)
{
	if (IS_NULL_exp(a)) {
		return 0;
	}
	switch (TAG_exp(a)) {
	case exp_int_lit_tag: {
		/* Check integer constant expressions */
		NAT n = DEREF_nat(exp_int_lit_nat(a));
		unsigned etag = DEREF_unsigned(exp_int_lit_etag(a));
		switch (etag) {
		case exp_char_lit_tag:
		case exp_offset_size_tag: {
			/* These never overflow */
			return 0;
		}
		}
		return is_calc_nat(n);
	}
	case exp_identifier_tag:
	case exp_member_tag:
	case exp_char_lit_tag:
	case exp_value_tag:
	case exp_null_tag:
	case exp_zero_tag: {
		return 0;
	}
	case exp_string_lit_tag: {
		/* String literals deliberately excluded */
		return 1;
	}
	case exp_paren_tag:
	case exp_copy_tag: {
		EXP b = DEREF_exp(exp_paren_etc_arg(a));
		return overflow_exp(b);
	}
	case exp_address_tag: {
		EXP b = DEREF_exp(exp_address_arg(a));
		return overflow_exp(b);
	}
	case exp_address_mem_tag: {
		EXP b = DEREF_exp(exp_address_mem_arg(a));
		return overflow_exp(b);
	}
	case exp_cast_tag: {
		/* Cast expressions */
		unsigned c = DEREF_unsigned(exp_cast_conv(a));
		if (c == CONV_ELLIPSIS) {
			EXP b = DEREF_exp(exp_cast_arg(a));
			return overflow_exp(b);
		}
		break;
	}
	case exp_comma_tag: {
		LIST(EXP)p = DEREF_list(exp_comma_args(a));
		while (!IS_NULL_list(p)) {
			EXP b = DEREF_exp(HEAD_list(p));
			if (overflow_exp(b)) {
				return 1;
			}
			p = TAIL_list(p);
		}
		return 0;
	}
	case exp_aggregate_tag: {
		LIST(EXP)p = DEREF_list(exp_aggregate_args(a));
		while (!IS_NULL_list(p)) {
			EXP b = DEREF_exp(HEAD_list(p));
			if (overflow_exp(b)) {
				return 1;
			}
			p = TAIL_list(p);
		}
		return 0;
	}
	case exp_nof_tag: {
		EXP b = DEREF_exp(exp_nof_start(a));
		EXP c = DEREF_exp(exp_nof_pad(a));
		EXP d = DEREF_exp(exp_nof_end(a));
		NAT n = DEREF_nat(exp_nof_size(a));
		if (overflow_exp(b)) {
			return 1;
		}
		if (overflow_exp(c)) {
			return 1;
		}
		if (overflow_exp(d)) {
			return 1;
		}
		return is_calc_nat(n);
	}
	}
	return 1;
}


/*
    This routine checks the linkage of the expression a.  If vol is true
    then the result is or-ed with dspec_implicit if a is derived from
    an implicitly volatile external identifier and or-ed with dspec_pure
    if a is derived from an implicitly const string literal.  The
    component of a which determines the linkage is returned via pa.
*/

DECL_SPEC
find_exp_linkage(EXP e, EXP *pa, int vol)
{
	if (!IS_NULL_exp(e)) {
		assert(ORDER_exp == 88);
		switch (TAG_exp(e)) {
		case exp_identifier_tag:
		case exp_member_tag: {
			/* Identifier expressions */
			IDENTIFIER id = DEREF_id(exp_identifier_etc_id(e));
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			ds &= (dspec_storage | dspec_temp);
			if (vol && IS_id_variable_etc(id)) {
				TYPE t = DEREF_type(id_variable_etc_type(id));
				CV_SPEC cv = find_cv_qual(t);
				if (!(cv & cv_volatile)) {
					ds |= dspec_implicit;
				}
			}
			*pa = e;
			return ds;
		}
		case exp_string_lit_tag: {
			/* String literals have internal linkage */
			*pa = e;
			return dspec_static | dspec_pure;
		}
		case exp_paren_tag:
		case exp_copy_tag: {
			/* Parenthesised expressions */
			EXP a = DEREF_exp(exp_paren_etc_arg(e));
			return find_exp_linkage(a, pa, vol);
		}
		case exp_indir_tag: {
			/* Indirection expressions */
			EXP a = DEREF_exp(exp_indir_ptr(e));
			return find_exp_linkage(a, pa, vol);
		}
		case exp_address_tag: {
			/* Address expressions */
			EXP a = DEREF_exp(exp_address_arg(e));
			return find_exp_linkage(a, pa, vol);
		}
		case exp_address_mem_tag: {
			/* Address expressions */
			EXP a = DEREF_exp(exp_address_mem_arg(e));
			if (IS_exp_member(a)) {
				return find_exp_linkage(a, pa, vol);
			}
			break;
		}
		case exp_cast_tag: {
			/* Cast expressions */
			EXP a = DEREF_exp(exp_cast_arg(e));
			DECL_SPEC ds = find_exp_linkage(a, pa, vol);
			ds &= ~(dspec_implicit | dspec_pure);
			return ds;
		}
		case exp_add_ptr_tag: {
			/* Pointer offset expressions */
			EXP a = DEREF_exp(exp_add_ptr_ptr(e));
			DECL_SPEC ds = find_exp_linkage(a, pa, vol);
			OFFSET off = DEREF_off(exp_add_ptr_off(e));
			if (vol) {
				/* Check for volatile members */
				while (IS_off_plus(off)) {
					off = DEREF_off(off_plus_arg2(off));
				}
				if (IS_off_member(off)) {
					TYPE t;
					CV_SPEC cv;
					IDENTIFIER id;
					id = DEREF_id(off_member_id(off));
					t = DEREF_type(id_member_type(id));
					cv = find_cv_qual(t);
					if (cv & cv_volatile)ds &= ~dspec_implicit;
				}
			} else {
				/* Only base class conversions allowed */
				if (!IS_off_base(off) && !IS_off_deriv(off)) {
					ds = dspec_none;
				}
			}
			return ds;
		}
		case exp_base_cast_tag: {
			/* Base cast expressions */
			EXP a = DEREF_exp(exp_base_cast_arg(e));
			return find_exp_linkage(a, pa, vol);
		}
		case exp_location_tag: {
			/* Location expressions */
			EXP a = DEREF_exp(exp_location_arg(e));
			return find_exp_linkage(a, pa, vol);
		}
		case exp_int_lit_tag:
		case exp_char_lit_tag:
		case exp_null_tag:
		case exp_zero_tag:
		case exp_value_tag:
		case exp_token_tag: {
			/* These count as external linkage */
			*pa = e;
			return dspec_extern;
		}
		}
	}
	return dspec_none;
}


/*
    This routine checks whether the offset off is zero.  The only
    non-trivial case is for base class offsets where the single
    inheritance (zero offset) cases are marked using dspec_ignore.
*/

int
is_zero_offset(OFFSET off)
{
	if (IS_NULL_off(off)) {
		return 1;
	}
	assert(ORDER_off == 13);
	switch (TAG_off(off)) {
	case off_zero_tag: {
		/* Zero offsets */
		return 1;
	}
	case off_array_tag: {
		/* Array offsets */
		unsigned n = DEREF_unsigned(off_array_arg(off));
		if (n == 0) {
			return 1;
		}
		break;
	}
	case off_base_tag: {
		/* Base class offsets */
		GRAPH gr = DEREF_graph(off_base_graph(off));
		DECL_SPEC acc = DEREF_dspec(graph_access(gr));
		if (acc & dspec_ignore) {
			return 1;
		}
		break;
	}
	case off_deriv_tag: {
		/* Derived class offsets */
		GRAPH gr = DEREF_graph(off_deriv_graph(off));
		DECL_SPEC acc = DEREF_dspec(graph_access(gr));
		if (acc & dspec_ignore) {
			return 1;
		}
		break;
	}
	case off_negate_tag: {
		/* Offset negations */
		OFFSET a = DEREF_off(off_negate_arg(off));
		return is_zero_offset(a);
	}
	case off_plus_tag: {
		/* Offset additions */
		OFFSET a = DEREF_off(off_plus_arg1(off));
		OFFSET b = DEREF_off(off_plus_arg2(off));
		return is_zero_offset(a) && is_zero_offset(b);
	}
	case off_mult_tag: {
		/* Offset multiplications */
		OFFSET a = DEREF_off(off_mult_arg1(off));
		return is_zero_offset(a);
	}
	}
	return 0;
}


/*
    This routine checks whether the type of a pointer plus the offset off
    can be statically determined.  It returns 2 if the type is known
    independent of the value of the pointer, 1 if it is known if the
    type of the pointer is known, and 0 otherwise.
*/

static int
know_offset(OFFSET off)
{
	if (!IS_NULL_off(off)) {
		switch (TAG_off(off)) {
		case off_base_tag:
		case off_deriv_tag:
		case off_ptr_mem_tag: {
			/* Base class offsets */
			return 0;
		}
		case off_member_tag: {
			/* Member offsets */
			return 2;
		}
		case off_plus_tag: {
			/* Check for derived member offsets */
			off = DEREF_off(off_plus_arg2(off));
			if (IS_off_member(off)) {
				return 2;
			}
			break;
		}
		}
	}
	return 1;
}


/*
    This routine checks whether the expression of class type or pointer to
    class type, e, is derived from an object so that its type can be
    statically determined.  It is used to check whether the virtual call
    mechanism and virtual base class conversions can be bypassed for e.
    A value of 2 is returned for non-obvious known types.
*/

int
know_type(EXP e)
{
	if (!IS_NULL_exp(e)) {
		unsigned tag = TAG_exp(e);
		switch (tag) {
		case exp_address_tag: {
			EXP a = DEREF_exp(exp_address_arg(e));
			tag = TAG_exp(a);
			if (tag == exp_identifier_tag) {
				return 1;
			}
			if (tag == exp_indir_tag) {
				EXP b = DEREF_exp(exp_indir_ptr(a));
				return know_type(b);
			}
			if (tag == exp_dummy_tag) {
				EXP b = DEREF_exp(exp_dummy_value(a));
				if (IS_NULL_exp(b)) {
					int v = DEREF_int(exp_dummy_virt(a));
					if (!v) {
						return 1;
					}
				}
			}
			break;
		}
		case exp_indir_tag: {
			EXP a = DEREF_exp(exp_indir_ptr(e));
			return know_type(a);
		}
		case exp_add_ptr_tag: {
			OFFSET off = DEREF_off(exp_add_ptr_off(e));
			int k = know_offset(off);
			if (k == 2) {
				return 1;
			}
			if (k == 1) {
				EXP a = DEREF_exp(exp_add_ptr_ptr(e));
				return know_type(a);
			}
			break;
		}
		case exp_contents_tag: {
			e = DEREF_exp(exp_contents_ptr(e));
			if (IS_exp_identifier(e)) {
				goto identifier_lab;
			}
			break;
		}
		case exp_identifier_tag:
identifier_lab: {
			 IDENTIFIER id = DEREF_id(exp_identifier_id(e));
			 HASHID nm = DEREF_hashid(id_name(id));
			 if (EQ_KEYWORD(nm, lex_this_Hname)) {
				 /* A 'this' expression */
				 NAMESPACE ns = DEREF_nspace(id_parent(id));
				 id = DEREF_id(nspace_name(ns));
				 nm = DEREF_hashid(id_name(id));
				 if (IS_hashid_constr(nm)) {
					 /* Function is a constructor */
					 return 2;
				 }
				 if (IS_hashid_destr(nm)) {
					 /* Function is a destructor */
					 return 2;
				 }
			 }
			 break;
		 }
		}
	}
	return 0;
}
