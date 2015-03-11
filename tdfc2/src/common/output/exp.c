/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <shared/check.h>

#include <tdf/capsule.h>

#include <utility/config.h>
#include <utility/version.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/ustring.h>

#include <syntax/syntax.h>

#include <parse/constant.h>
#include <parse/literal.h>

#include <construct/assign.h>
#include <construct/basetype.h>
#include <construct/check.h>
#include <construct/class.h>
#include <construct/convert.h>
#include <construct/derive.h>
#include <construct/destroy.h>
#include <construct/expression.h>
#include <construct/function.h>
#include <construct/identifier.h>
#include <construct/member.h>
#include <construct/redeclare.h>
#include <construct/statement.h>
#include <construct/virtual.h>

#include <output/tdf.h>
#include <output/capsule.h>
#include <output/compile.h>
#include <output/diag3.h>
#include <output/encode.h>
#include <output/exp.h>
#include <output/init.h>
#include <output/shape.h>
#include <output/stmt.h>
#include <output/struct.h>
#include <output/tok.h>
#include <output/throw.h>

#include "ctype_ops.h"
#include "exp_ops.h"
#include "etype_ops.h"
#include "graph_ops.h"
#include "id_ops.h"
#include "nat_ops.h"
#include "off_ops.h"
#include "str_ops.h"
#include "type_ops.h"
#include "virt_ops.h"


/*
    This routine adds the small integer n to the bitstream bs as a TDF
    SIGNED_NAT.
*/

BITSTREAM *
enc_make_snat(BITSTREAM *bs, int n)
{
	ENC_make_signed_nat(bs);
	if (n >= 0) {
		ENC_OFF(bs);
	} else {
		ENC_ON(bs);
		n = -n;
	}
	ENC_INT(bs, n);
	return bs;
}


/*
    This routine adds the small integer n of type t to the bitstream bs
    as a TDF EXP.
*/

BITSTREAM *
enc_make_int(BITSTREAM *bs, TYPE t, int n)
{
	ENC_make_int(bs);
	bs = enc_variety(bs, t);
	bs = enc_make_snat(bs, n);
	return bs;
}


/*
    This routine adds a null TDF EXP with shape corresponding to the type
    t to the bitstream bs.
*/

BITSTREAM *
enc_null_exp(BITSTREAM *bs, TYPE t)
{
	if (IS_NULL_type(t)) {
		/* This shouldn't happen */
		t = type_sint;
	}
	switch (TAG_type(t)) {
	case type_integer_tag:
	case type_enumerate_tag: {
		/* Integral types */
		bs = enc_make_int(bs, t, 0);
		break;
	}
	case type_floating_tag: {
		/* Floating types */
		bs = enc_float_int(bs, 0, t);
		break;
	}
	case type_top_tag:
	case type_bottom_tag: {
		/* Top type */
		ENC_make_top(bs);
		break;
	}
	case type_ptr_tag:
	case type_ref_tag: {
		/* Pointer types */
		TYPE s = DEREF_type(type_ptr_etc_sub(t));
		switch (TAG_type(s)) {
		case type_top_tag:
		case type_bottom_tag: {
			/* Generic pointer */
			bs = enc_special(bs, TOK_null_pv);
			break;
		}
		case type_func_tag: {
			/* Function pointer */
			ENC_make_null_proc(bs);
			break;
		}
		default: {
			/* Normal pointer */
			ENC_make_null_ptr(bs);
			bs = enc_alignment(bs, s);
			break;
		}
		}
		break;
	}
	case type_ptr_mem_tag: {
		/* Pointer to member types */
		TYPE s = DEREF_type(type_ptr_mem_sub(t));
		if (IS_type_func(s)) {
			if (in_static_init) {
				bs = enc_special(bs, TOK_pmf_null);
			} else {
				bs = enc_special(bs, TOK_pmf_null2);
			}
		} else {
			bs = enc_special(bs, TOK_pm_null);
		}
		break;
	}
	case type_array_tag: {
		/* Array types */
		NAT n = DEREF_nat(type_array_size(t));
		TYPE s = DEREF_type(type_array_sub(t));
		ENC_n_copies(bs);
		bs = enc_nat(bs, n, 1);
		bs = enc_null_exp(bs, s);
		break;
	}
	case type_bitfield_tag: {
		/* Bitfield types */
		TYPE s = find_bitfield_type(t);
		ENC_change_int_to_bitfield(bs);
		bs = enc_bfvar(bs, t);
		bs = enc_null_exp(bs, s);
		break;
	}
	case type_compound_tag: {
		/* Compound types */
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		TYPE s = DEREF_type(ctype_form(ct));
		if (is_tokenised_class(s)) {
			ENC_make_value(bs);
			bs = enc_shape(bs, s);
		} else {
			bs = enc_null_class(bs, ct);
		}
		break;
	}
	default: {
		/* Other types */
		ENC_make_value(bs);
		bs = enc_shape(bs, t);
		break;
	}
	}
	return bs;
}


/*
    This routine checks whether the identifier expression a arises from a
    member of an anonymous union.  The routine also marks any external
    variables.
*/

static int
is_anon_exp(EXP a)
{
	IDENTIFIER id = DEREF_id(exp_identifier_id(a));
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (!(ds & dspec_auto)) {
		/* Mark external variables */
		IGNORE capsule_id(id, VAR_tag);
	}
	if (ds & dspec_reserve) {
		/* Check for anonymous union members */
		return is_anon_member(id);
	}
	return 0;
}


/*
    This routine adds the start of an identity declaration for the
    expression a to the bitstream bs.  The identity body will consist
    of a sequence of seq + 1 expressions.  The identity tag number is
    returned via pn.
*/

static BITSTREAM *
make_identity(BITSTREAM *bs, EXP a, ulong *pn, int cnt, int seq)
{
	ulong n;
	if (IS_exp_identifier(a)) {
		/* No identity required in this case */
		IDENTIFIER id = DEREF_id(exp_identifier_id(a));
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if ((ds & dspec_auto) && !is_anon_exp(a)) {
			n = unit_no(bs, id, VAR_tag, 0);
			if (seq) {
				ENC_SEQUENCE(bs, seq);
			}
			*pn = n;
			return bs;
		}
	}
	/* Declare new identity */
	n = unit_no(bs, NULL_id, VAR_tag, 1);
	ENC_identify(bs);
	bs = enc_access(bs, crt_func_access);
	ENC_make_tag(bs, n);
	if (cnt) {
		bs = enc_exp(bs, a);
	} else {
		TYPE t = DEREF_type(exp_type(a));
		bs = enc_addr_exp(bs, t, a);
	}
	if (seq) {
		ENC_SEQUENCE(bs, seq);
	}
	*pn = n;
	return bs;
}


/*
    This routine adds the start of an identity or variable declaration
    for the pointer to member function or similar expression a to the
    bitstream bs.  If var is true then a variable declaration is forced.
    The tag number is returned via pn.
*/

static BITSTREAM *
make_ptr_mem_func(BITSTREAM *bs, EXP a, ulong *pn, int var)
{
	if (IS_exp_contents(a) && !var) {
		EXP b = DEREF_exp(exp_contents_ptr(a));
		bs = make_identity(bs, b, pn, 0, 0);
	} else {
		ulong n = unit_no(bs, NULL_id, VAR_tag, 1);
		ENC_variable(bs);
		bs = enc_access(bs, crt_func_access);
		ENC_make_tag(bs, n);
		bs = enc_exp(bs, a);
		*pn = n;
	}
	return bs;
}


/*
    This routine encodes an assignment operator for an expression of
    type t.  bf is set to true for bitfields.
*/

BITSTREAM *
enc_assign_op(BITSTREAM *bs, TYPE t, int *bf)
{
	CV_SPEC cv = DEREF_cv(type_qual(t));
	if (IS_type_bitfield(t)) {
		if (cv & cv_volatile) {
			ENC_bitfield_assign_with_mode(bs);
			ENC_volatile(bs);
		} else {
			ENC_bitfield_assign(bs);
		}
		*bf = 1;
	} else {
		if (cv & cv_volatile) {
			ENC_assign_with_mode(bs);
			ENC_volatile(bs);
		} else {
			ENC_assign(bs);
		}
	}
	return bs;
}


/*
    This routine adds the address of the expression e to the bitstream
    bs as a TDF EXP.
*/

BITSTREAM *
enc_addr_exp(BITSTREAM *bs, TYPE t, EXP e)
{
	ulong n;
	int anon = 0;
	TYPE s = DEREF_type(exp_type(e));
	switch (TAG_exp(e)) {

	case exp_identifier_tag: {
		/* Find tag corresponding to identifier */
		IDENTIFIER id = DEREF_id(exp_identifier_id(e));
		anon = is_anon_exp(e);
		n = unit_no(bs, id, VAR_tag, 0);
		break;
	}

	case exp_string_lit_tag: {
		/* Introduce tag for string literal */
		CV_SPEC qual = cv_none;
		STRING str = DEREF_str(exp_string_lit_str(e));
		if (IS_type_ptr(t)) {
			t = DEREF_type(type_ptr_sub(t));
			qual = DEREF_cv(type_qual(t));
		}
		if ((qual & cv_const) && output_shared) {
			/* Share const strings */
			n = DEREF_ulong(str_simple_tok(str));
			if (n == LINK_NONE) {
				n = make_tagdef(NULL_id, s, e, NULL_exp, 1);
				COPY_ulong(str_simple_tok(str), n);
			}
		} else {
			/* Don't share non-const strings */
			n = make_tagdef(NULL_id, s, e, NULL_exp, 1);
		}
		n = link_no(bs, n, VAR_tag);
		break;
	}

	case exp_indir_tag: {
		/* Indirections are simple */
		EXP a = DEREF_exp(exp_indir_ptr(e));
		bs = enc_exp(bs, a);
		return bs;
	}

	case exp_assign_tag: {
		/* Introduce identity for assignment */
		EXP a = DEREF_exp(exp_assign_ref(e));
		EXP b = DEREF_exp(exp_assign_arg(e));
		bs = make_identity(bs, a, &n, 0, 1);
		bs = enc_init_tag(bs, n, NULL_off, 0, s, b, NULL_exp, 0);
		break;
	}

	case exp_init_tag: {
		/* Introduce identity for initialisation */
		int context = 1;
		unsigned seq = 1;
		IDENTIFIER id = DEREF_id(exp_init_id(e));
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		EXP a = DEREF_exp(exp_init_arg(e));
		EXP d = DEREF_exp(id_variable_etc_term(id));
		if (!IS_NULL_exp(d)) {
			while (IS_exp_nof(d)) {
				d = DEREF_exp(exp_nof_pad(d));
			}
			seq++;
		}
		ENC_SEQ_SMALL(bs, seq);
		if (!(ds & dspec_auto)) {
			/* Allow for external variables */
			if (capsule_id(id, VAR_tag)) {
				make_term_global(s, &d);
			}
			context = 2;
		}
		n = unit_no(bs, id, VAR_tag, 0);
		bs = enc_init_tag(bs, n, NULL_off, 0, s, a, d, context);
		break;
	}

	case exp_preinc_tag: {
		/* Pre-increment expressions */
		EXP a = DEREF_exp(exp_preinc_ref(e));
		EXP b = DEREF_exp(exp_preinc_op(e));
		EXP a1 = DEREF_exp(exp_dummy_value(a));
		OFFSET off = DEREF_off(exp_dummy_off(a));
		COPY_exp(exp_dummy_value(a), NULL_exp);
		bs = make_identity(bs, a1, &n, 0, 1);
		COPY_ulong(exp_dummy_no(a), n);
		s = DEREF_type(exp_type(a));
		bs = enc_init_tag(bs, n, off, 0, s, b, NULL_exp, 0);
		COPY_exp(exp_dummy_value(a), a1);
		break;
	}

	case exp_cast_tag: {
		/* Cast expressions */
		EXP a = DEREF_exp(exp_cast_arg(e));
		bs = enc_addr_exp(bs, t, a);
		return bs;
	}

	case exp_decl_stmt_tag: {
		/* Variable declarations */
		IDENTIFIER id = DEREF_id(exp_decl_stmt_id(e));
		EXP a = DEREF_exp(exp_decl_stmt_body(e));
		bs = enc_variable(bs, id, 1, NIL(EXP), NULL_exp);
		ENC_SEQ_SMALL(bs, 1);
		bs = enc_exp(bs, a);
		n = unit_no(bs, id, VAR_tag, 0);
		break;
	}

	case exp_comma_tag:
	case exp_if_stmt_tag:
	case exp_hash_if_tag: {
		/* Statement-like expressions */
		bs = enc_stmt_exp(bs, e, s, 2);
		return bs;
	}

	case exp_rtti_tag:
	case exp_rtti_type_tag:
	case exp_thrown_tag:
	case exp_dummy_tag: {
		/* lvalue expressions */
		bs = enc_exp(bs, e);
		return bs;
	}

	case exp_token_tag: {
		/* Tokenised expressions */
		CV_SPEC qual = DEREF_cv(type_qual(s));
		if (qual & cv_lvalue) {
			bs = enc_exp(bs, e);
			return bs;
		}
		n = make_tagdef(NULL_id, s, e, NULL_exp, 1);
		n = link_no(bs, n, VAR_tag);
		break;
	}

	default: {
		/* Create temporary variable */
		CV_SPEC qual = DEREF_cv(type_qual(s));
		if (qual & cv_lvalue) {
			bs = enc_exp(bs, e);
			return bs;
		}
		n = unit_no(bs, NULL_id, VAR_tag, 1);
		ENC_variable(bs);
		bs = enc_access(bs, dspec_none);
		ENC_make_tag(bs, n);
		bs = enc_exp(bs, e);
		break;
	}
	}

	/* Encode an obtain_tag expression */
	if (anon) {
		ENC_add_to_ptr(bs);
	}
	if (IS_type_ref(s)) {
		int bf = 0;
		bs = enc_cont_op(bs, s, &bf);
		bs = enc_shape(bs, s);
		assert(bf == 0);
	}
	ENC_obtain_tag(bs);
	ENC_make_tag(bs, n);
	if (anon) {
		/* Allow for differing identifier types */
		ENC_offset_zero(bs);
		bs = enc_alignment(bs, s);
	}
	return bs;
}


/*
    This routine encodes a contents operator for an expression of type t.
    bf is set to true for bitfields.
*/

BITSTREAM *
enc_cont_op(BITSTREAM *bs, TYPE t, int *bf)
{
	CV_SPEC cv = DEREF_cv(type_qual(t));
	if (IS_type_bitfield(t)) {
		if (cv & cv_volatile) {
			ENC_bitfield_contents_with_mode(bs);
			ENC_volatile(bs);
		} else {
			ENC_bitfield_contents(bs);
		}
		*bf = 1;
	} else {
		if (cv & cv_volatile) {
			ENC_contents_with_mode(bs);
			ENC_volatile(bs);
		} else {
			ENC_contents(bs);
		}
	}
	return bs;
}


/*
    This routine adds the contents of the expression e of type t to the
    bitstream bs as a TDF EXP.
*/

BITSTREAM *
enc_cont_exp(BITSTREAM *bs, TYPE t, EXP e)
{
	ulong n;
	int bf = 0;
	OFFSET off = NULL_off;
	TYPE s = DEREF_type(exp_type(e));

	switch (TAG_exp(e)) {

	case exp_assign_tag: {
		/* Assignment (can't be bitfield) */
		EXP a = DEREF_exp(exp_assign_ref(e));
		EXP b = DEREF_exp(exp_assign_arg(e));
		CV_SPEC cv = DEREF_cv(type_qual(s));
		if (!(cv & cv_lvalue)) {
			if ((cv & cv_volatile) && !is_init_complex(b)) {
				/* Introduce identity for right hand side */
				bs = make_identity(bs, b, &n, 1, 1);
				bs = enc_assign_op(bs, s, &bf);
				bs = enc_exp(bs, a);
				ENC_obtain_tag(bs);
				ENC_make_tag(bs, n);
				ENC_obtain_tag(bs);
				ENC_make_tag(bs, n);
				return bs;
			}
		}
		/* Introduce identity for left hand side */
		bs = make_identity(bs, a, &n, 0, 1);
		bs = enc_init_tag(bs, n, NULL_off, 0, t, b, NULL_exp, 0);
		break;
	}

	case exp_init_tag: {
		/* Introduce identity for initialisation */
		int context = 1;
		unsigned seq = 1;
		IDENTIFIER id = DEREF_id(exp_init_id(e));
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		EXP a = DEREF_exp(exp_init_arg(e));
		EXP d = DEREF_exp(id_variable_etc_term(id));
		if (!IS_NULL_exp(d)) {
			while (IS_exp_nof(d)) {
				d = DEREF_exp(exp_nof_pad(d));
			}
			seq++;
		}
		ENC_SEQ_SMALL(bs, seq);
		if (!(ds & dspec_auto)) {
			/* Allow for external variables */
			if (capsule_id(id, VAR_tag)) {
				make_term_global(t, &d);
			}
			context = 2;
		}
		n = unit_no(bs, id, VAR_tag, 0);
		bs = enc_init_tag(bs, n, NULL_off, 0, t, a, d, context);
		break;
	}

	case exp_preinc_tag: {
		/* Pre-increment expressions */
		ulong m = LINK_NONE;
		CV_SPEC cv = DEREF_cv(type_qual(s));
		EXP a = DEREF_exp(exp_preinc_ref(e));
		EXP b = DEREF_exp(exp_preinc_op(e));
		EXP a1 = DEREF_exp(exp_dummy_value(a));
		COPY_exp(exp_dummy_value(a), NULL_exp);
		bs = make_identity(bs, a1, &n, 0, 0);
		COPY_ulong(exp_dummy_no(a), n);
		if (!(cv & cv_lvalue) || !(cv & cv_volatile)) {
			/* Introduce identity for right hand side */
			bs = make_identity(bs, b, &m, 1, 0);
		}
		ENC_SEQ_SMALL(bs, 1);
		s = DEREF_type(exp_type(a));
		bs = enc_assign_op(bs, s, &bf);
		ENC_obtain_tag(bs);
		ENC_make_tag(bs, n);
		if (bf) {
			off = DEREF_off(exp_dummy_off(a));
			bs = enc_offset(bs, off);
		}
		COPY_exp(exp_dummy_value(a), a1);
		if (m == LINK_NONE) {
			bs = enc_exp(bs, b);
		} else {
			ENC_obtain_tag(bs);
			ENC_make_tag(bs, m);
		}
		if (bf && !IS_type_bitfield(t)) {
			/* Promotion conversion (see make_preinc_exp) */
			ENC_change_bitfield_to_int(bs);
			bs = enc_variety(bs, t);
			t = s;
		}
		if (m == LINK_NONE) {
			break;
		}
		ENC_obtain_tag(bs);
		ENC_make_tag(bs, m);
		return bs;
	}

	case exp_decl_stmt_tag: {
		/* Variable declarations */
		IDENTIFIER id = DEREF_id(exp_decl_stmt_id(e));
		EXP a = DEREF_exp(exp_decl_stmt_body(e));
		bs = enc_variable(bs, id, 1, NIL(EXP), NULL_exp);
		ENC_SEQ_SMALL(bs, 1);
		bs = enc_exp(bs, a);
		n = unit_no(bs, id, VAR_tag, 0);
		break;
	}

	case exp_comma_tag:
	case exp_if_stmt_tag:
	case exp_hash_if_tag: {
		/* Statement-like expressions */
		bs = enc_stmt_exp(bs, e, t, 3);
		return bs;
	}

	case exp_dummy_tag: {
		/* Dummy expressions */
		EXP a = DEREF_exp(exp_dummy_value(e));
		if (IS_NULL_exp(a)) {
			int cnt = DEREF_int(exp_dummy_cont(e));
			int virt = DEREF_int(exp_dummy_virt(e));
			n = DEREF_ulong(exp_dummy_no(e));
			bs = enc_cont_op(bs, s, &bf);
			off = DEREF_off(exp_dummy_off(e));
			if (bf) {
				OFFSET off1 = decons_bitf_off(&off);
				bs = enc_bfvar(bs, t);
				bs = enc_dummy_exp(bs, t, n, off, cnt, virt);
				bs = enc_offset(bs, off1);
			} else {
				bs = enc_shape(bs, t);
				bs = enc_dummy_exp(bs, t, n, off, cnt, virt);
			}
			return bs;
		}
		n = LINK_NONE;
		break;
	}

	default: {
		/* This is the easy case */
		n = LINK_NONE;
		break;
	}
	}

	/* Encode a contents expression */
	bs = enc_cont_op(bs, s, &bf);
	if (bf) {
		if (IS_NULL_off(off)) {
			/* Find bitfield offset */
			off = decons_bitf_exp(&e);
		}
		bs = enc_bfvar(bs, t);
		if (n == LINK_NONE) {
			bs = enc_addr_exp(bs, t, e);
		} else {
			ENC_obtain_tag(bs);
			ENC_make_tag(bs, n);
		}
		bs = enc_offset(bs, off);
	} else {
		bs = enc_shape(bs, t);
		if (n == LINK_NONE) {
			bs = enc_exp(bs, e);
		} else {
			ENC_obtain_tag(bs);
			ENC_make_tag(bs, n);
		}
	}
	return bs;
}


/*
    This routines adds the expressions p to the bitstream bs as a list
    of TDF EXPs.
*/

BITSTREAM *
enc_exp_list(BITSTREAM *bs, LIST(EXP)p)
{
	unsigned n = LENGTH_list(p);
	ENC_LIST(bs, n);
	while (!IS_NULL_list(p)) {
		EXP e = DEREF_exp(HEAD_list(p));
		bs = enc_exp(bs, e);
		p = TAIL_list(p);
	}
	return bs;
}


/*
    This routine adds the comparison operator tst to the bitstream bs as
    a TDF NTEST.  The macro ENC_NTEST exploits the correlation between
    the internal representation of NTESTs and the TDF encoding.
*/

BITSTREAM *
enc_ntest(BITSTREAM *bs, NTEST tst)
{
	ENC_NTEST(bs, tst);
	return bs;
}


/*
    This routine adds a comparison expression to the bitstream bs for
    comparing a with b using test tst.  lab gives the destination label
    number.
*/

BITSTREAM *
enc_compare(BITSTREAM *bs, EXP a, EXP b, NTEST tst, ulong lab, ulong nlab)
{
	/* Find the test */
	TYPE t = DEREF_type(exp_type(a));
	unsigned tag = TAG_type(t);
	if (lab == LINK_NONE) {
		if (tst > ntest_not) {
			tst -= ntest_not;
		}
		tst = ntest_negate - tst;
		lab = nlab;
	}

	/* Encode the comparison operation */
	switch (tag) {

	case type_floating_tag: {
		/* Floating point comparisons */
		ENC_floating_test(bs);
		ENC_OFF(bs);
		ENC_impossible(bs);
		break;
	}

	case type_ptr_tag:
	case type_ref_tag: {
		/* Pointer comparisons */
		TYPE s = DEREF_type(type_ptr_etc_sub(t));
		switch (TAG_type(s)) {
		case type_top_tag:
		case type_bottom_tag: {
			/* 'void *' comparisons */
			int spec;
			BITSTREAM *ts;
			if (IS_NULL_exp(b) || IS_exp_null(b)) {
				spec = TOK_pv_test;
				b = NULL_exp;
			} else {
				spec = TOK_pv_compare;
			}
			bs = enc_special(bs, spec);
			ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_exp(ts, a);
			if (!IS_NULL_exp(b)) {
				ts = enc_exp(ts, b);
			}
			ENC_make_label(ts, lab);
			ts = enc_ntest(ts, tst);
			bs = enc_bitstream(bs, ts);
			return bs;
		}
		case type_func_tag: {
			/* Function pointers */
			ENC_proc_test(bs);
			break;
		}
		default: {
			/* Object pointers */
			ENC_pointer_test(bs);
			break;
		}
		}
		ENC_OFF(bs);
		break;
	}

	case type_ptr_mem_tag: {
		/* Pointer to member comparisons */
		int spec;
		BITSTREAM *ts;
		TYPE s = DEREF_type(type_ptr_mem_sub(t));
		if (IS_type_func(s)) {
			/* Pointer to member functions */
			ulong n = LINK_NONE;
			ulong m = LINK_NONE;
			bs = make_ptr_mem_func(bs, a, &n, 0);
			if (IS_NULL_exp(b) || IS_exp_null(b)) {
				spec = TOK_pmf_test;
				b = NULL_exp;
			} else {
				bs = make_ptr_mem_func(bs, b, &m, 0);
				spec = TOK_pmf_compare;
			}
			bs = enc_special(bs, spec);
			ts = start_bitstream(NIL(FILE), bs->link);
			ENC_obtain_tag(ts);
			ENC_make_tag(ts, n);
			if (!IS_NULL_exp(b)) {
				ENC_obtain_tag(ts);
				ENC_make_tag(ts, m);
			}
			ENC_make_label(ts, lab);
			ts = enc_ntest(ts, tst);
			bs = enc_bitstream(bs, ts);
		} else {
			/* Pointer to data members */
			if (IS_NULL_exp(b) || IS_exp_null(b)) {
				spec = TOK_pm_test;
				b = NULL_exp;
			} else {
				spec = TOK_pm_compare;
			}
			bs = enc_special(bs, spec);
			ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_exp(ts, a);
			if (!IS_NULL_exp(b))ts = enc_exp(ts, b);
			ENC_make_label(ts, lab);
			ts = enc_ntest(ts, tst);
			bs = enc_bitstream(bs, ts);
		}
		return bs;
	}

	default: {
		/* Integer comparisons */
		ENC_integer_test(bs);
		ENC_OFF(bs);
		break;
	}
	}

	/* Encode the comparison arguments */
	bs = enc_ntest(bs, tst);
	ENC_make_label(bs, lab);
	bs = enc_exp(bs, a);
	if (IS_NULL_exp(b)) {
		bs = enc_null_exp(bs, t);
	} else {
		bs = enc_exp(bs, b);
	}
	return bs;
}


/*
    This routine simplifies the condition e by removing any double
    negations.  sw is set to 1 if the result has the form 'a || b' or
    '!( a && b )'.
*/

EXP
simplify_cond(EXP e, int *sw)
{
	EXP a = e;
	unsigned tag = TAG_exp(a);
	if (tag == exp_location_tag) {
		/* Can have location markers */
		EXP b;
		a = DEREF_exp(exp_location_arg(e));
		b = simplify_cond(a, sw);
		if (!EQ_exp(b, a)) {
			LOCATION loc;
			TYPE t = DEREF_type(exp_type(e));
			DEREF_loc(exp_location_end(e), loc);
			MAKE_exp_location(t, loc, b, e);
		}
		return e;
	}
	while (tag == exp_not_tag) {
		EXP b = DEREF_exp(exp_not_arg(a));
		tag = TAG_exp(b);
		if (tag != exp_not_tag) {
			if (tag == exp_log_and_tag) {
				*sw = 1;
			}
			return a;
		}
		a = DEREF_exp(exp_not_arg(b));
		tag = TAG_exp(a);
	}
	if (tag == exp_log_or_tag) {
		*sw = 1;
	}
	return a;
}


/*
    This routine adds the expression e as a conditional jump to the label
    lab if true or label nlab if false to the bitstream bs.  Either label
    may be LINK_NONE.
*/

BITSTREAM *
enc_condition(BITSTREAM *bs, EXP e, ulong lab, ulong nlab)
{
	switch (TAG_exp(e)) {

	case exp_int_lit_tag: {
		/* Constant conditions */
		NAT n = DEREF_nat(exp_int_lit_nat(e));
		if (IS_nat_small(n)) {
			unsigned v = DEREF_unsigned(nat_small_value(n));
			if (v == BOOL_FALSE) {
				nlab = lab;
			}
			if (nlab == LINK_NONE) {
				ENC_make_top(bs);
			} else {
				ENC_goto(bs);
				ENC_make_label(bs, nlab);
			}
			break;
		}
		if (IS_nat_calc(n)) {
			EXP a = DEREF_exp(nat_calc_value(n));
			bs = enc_condition(bs, a, lab, nlab);
			break;
		}
		goto default_lab;
	}

	case exp_not_tag: {
		/* Negated conditions */
		EXP a = DEREF_exp(exp_not_arg(e));
		bs = enc_condition(bs, a, nlab, lab);
		break;
	}

	case exp_log_and_tag: {
		/* Logical and conditions */
		EXP a = DEREF_exp(exp_log_and_arg1(e));
		EXP b = DEREF_exp(exp_log_and_arg2(e));
		if (lab == LINK_NONE) {
			/* '!( a && b )' equals '!a || !b' */
			ulong mlab = unit_no(bs, NULL_id, VAR_label, 1);
			ENC_conditional(bs);
			ENC_make_label(bs, mlab);
			ENC_SEQ_SMALL(bs, 1);
			bs = enc_condition(bs, a, mlab, LINK_NONE);
			bs = enc_condition(bs, b, LINK_NONE, nlab);
			ENC_make_top(bs);
		} else {
			/* Encode 'a && b' */
			ENC_SEQ_SMALL(bs, 1);
			bs = enc_condition(bs, a, lab, nlab);
			bs = enc_condition(bs, b, lab, nlab);
		}
		break;
	}

	case exp_log_or_tag: {
		/* Logical or conditions */
		EXP a = DEREF_exp(exp_log_or_arg1(e));
		EXP b = DEREF_exp(exp_log_or_arg2(e));
		if (nlab == LINK_NONE) {
			/* Encode 'a || b' */
			ulong mlab = unit_no(bs, NULL_id, VAR_label, 1);
			ENC_conditional(bs);
			ENC_make_label(bs, mlab);
			ENC_SEQ_SMALL(bs, 1);
			bs = enc_condition(bs, a, LINK_NONE, mlab);
			bs = enc_condition(bs, b, lab, LINK_NONE);
			ENC_make_top(bs);
		} else {
			/* '!( a || b )' equals '!a && !b' */
			ENC_SEQ_SMALL(bs, 1);
			bs = enc_condition(bs, a, lab, nlab);
			bs = enc_condition(bs, b, lab, nlab);
		}
		break;
	}

	case exp_test_tag: {
		/* Test conditions */
		NTEST tst = DEREF_ntest(exp_test_tst(e));
		EXP a = DEREF_exp(exp_test_arg(e));
		bs = enc_compare(bs, a, NULL_exp, tst, lab, nlab);
		break;
	}

	case exp_compare_tag: {
		/* Comparison conditions */
		NTEST tst = DEREF_ntest(exp_compare_tst(e));
		EXP a = DEREF_exp(exp_compare_arg1(e));
		EXP b = DEREF_exp(exp_compare_arg2(e));
		bs = enc_compare(bs, a, b, tst, lab, nlab);
		break;
	}

	case exp_comma_tag: {
		/* Comma conditions */
		EXP a;
		LIST(EXP)p = DEREF_list(exp_comma_args(e));
		bs = enc_stmt_exp(bs, e, type_void, -1);
		p = END_list(p);
		a = DEREF_exp(HEAD_list(p));
		bs = enc_condition(bs, a, lab, nlab);
		break;
	}

	case exp_location_tag: {
		/* Location marker */
		PTR(LOCATION)loc = crt_enc_loc;
		EXP a = DEREF_exp(exp_location_arg(e));
		BITSTREAM *ts = enc_diag_begin(&bs);
		ts = enc_condition(ts, a, lab, nlab);
		crt_enc_loc = exp_location_end(e);
		bs = enc_diag_end(bs, ts, a, 2);
		crt_enc_loc = loc;
		break;
	}

	default:
default_lab: {
		     /* Other conditions */
		     NTEST tst = ntest_not_eq;
		     bs = enc_compare(bs, e, NULL_exp, tst, lab, nlab);
		     break;
	     }
	}
	return bs;
}


/*
    This routine adds the logical expression e of type t to the bitstream
    bs.  The code added is equivalent to '( e ? 1 : 0 )'.
*/

static BITSTREAM *
enc_logical(BITSTREAM *bs, EXP e, TYPE t)
{
	int sw = 0;
	ulong nlab = LINK_NONE;
	ulong n = unit_no(bs, NULL_id, VAR_tag, 1);
	ulong lab = unit_no(bs, NULL_id, VAR_label, 1);
	e = simplify_cond(e, &sw);

	/* Introduce variable for boolean value */
	ENC_variable(bs);
	bs = enc_access(bs, dspec_none);
	ENC_make_tag(bs, n);
	bs = enc_make_int(bs, t, sw);
	ENC_SEQ_SMALL(bs, 1);
	ENC_conditional(bs);
	ENC_make_label(bs, lab);
	ENC_SEQ_SMALL(bs, 1);

	/* Conditionally assign to boolean variable */
	if (sw) {
		nlab = lab;
		lab = LINK_NONE;
	}
	bs = enc_condition(bs, e, lab, nlab);
	ENC_assign(bs);
	ENC_obtain_tag(bs);
	ENC_make_tag(bs, n);
	bs = enc_make_int(bs, t, !sw);
	ENC_make_top(bs);

	/* Return the contents of the boolean */
	ENC_contents(bs);
	bs = enc_shape(bs, t);
	ENC_obtain_tag(bs);
	ENC_make_tag(bs, n);
	return bs;
}


/*
    This routine checks whether the expression e consists of a cast of the
    address of a member of some class.  If so it returns the corresponding
    member identifier.
*/

static IDENTIFIER
is_const_ptr_mem(EXP e, int rev)
{
	if (!IS_NULL_exp(e)) {
		unsigned tag = TAG_exp(e);
		if (tag == exp_address_mem_tag) {
			/* Allow for addresses of members */
			EXP a = DEREF_exp(exp_address_mem_arg(e));
			IDENTIFIER id = DEREF_id(exp_member_id(a));
			return id;
		} else if (tag == exp_base_cast_tag) {
			/* Allow for base casts */
			EXP a = DEREF_exp(exp_base_cast_arg(e));
			unsigned conv = DEREF_unsigned(exp_base_cast_conv(e));
			if (rev || !(conv & CONV_REVERSE)) {
				IDENTIFIER id = is_const_ptr_mem(a, rev);
				return id;
			}
		} else if (tag == exp_dummy_tag) {
			/* Allow for dummy expressions */
			EXP a = DEREF_exp(exp_dummy_value(e));
			IDENTIFIER id = is_const_ptr_mem(a, rev);
			return id;
		}
	}
	return NULL_id;
}


/*
    This routine adds the address of the member id plus the base class
    offset gr, converted to type t, to the bitstream bs.
*/

static BITSTREAM *
enc_ptr_mem(BITSTREAM *bs, TYPE t, IDENTIFIER id, GRAPH gr)
{
	BITSTREAM *ts = start_bitstream(NIL(FILE), bs->link);
	if (IS_id_mem_func(id)) {
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		CLASS_TYPE ct = DEREF_ctype(type_ptr_mem_of(t));
		assert(!(ds & dspec_inherit));
		if (ds & dspec_virtual) {
			/* Virtual member function */
			ulong m;
			ulong tok;
			VIRTUAL vt;
			OFFSET off;
			IGNORE compile_class(ct);
			vt = DEREF_virt(ctype_virt(ct));
			off = DEREF_off(virt_table_off(vt));
			tok = DEREF_ulong(virt_table_tok(vt));
			if (!IS_NULL_graph(gr)) {
				/* Allow for overriding virtual functions */
				GRAPH gs = NULL_graph;
				VIRTUAL at = find_overrider(ct, id, gr, &gs);
				if (!IS_NULL_virt(at)) {
					id = DEREF_id(virt_func(at));
				}
			}
			m = virtual_no(id, vt);
			bs = enc_special(bs, TOK_pmf_vmake);
			ts = enc_make_snat(ts,(int)m);
			if (!is_zero_offset(off)) {
				ENC_offset_add(ts);
				ts = enc_offset(ts, off);
			}
			tok = link_no(ts, tok, VAR_token);
			ENC_exp_apply_token(ts);
			ENC_make_tok(ts, tok);
			ENC_LEN_SMALL(ts, 0);
			ENC_offset_zero(ts);
			ts = enc_al_ctype(ts, ct);
			ENC_offset_zero(ts);
			ts = enc_al_ctype(ts, ct);
		} else {
			/* Member function */
			bs = enc_special(bs, TOK_pmf_make);
			ts = enc_member(ts, id);
			if (IS_NULL_graph(gr)) {
				ENC_offset_zero(ts);
				ts = enc_al_ctype(ts, ct);
			} else {
				ts = enc_base(ts, gr, 0);
			}
			ENC_offset_zero(ts);
			ts = enc_al_ctype(ts, ct);
		}
	} else {
		/* Data member */
		bs = enc_special(bs, TOK_pm_make);
		if (!IS_NULL_graph(gr)) {
			DECL_SPEC acc = DEREF_dspec(graph_access(gr));
			if (!(acc & dspec_ignore)) {
				ENC_offset_add(ts);
				ts = enc_base(ts, gr, 0);
			}
		}
		ts = enc_member(ts, id);
	}
	bs = enc_bitstream(bs, ts);
	return bs;
}


/*
    This routine adds a TDF EXP to the bitstream bs representing a cast
    of the expression e to the type t.  conv represents the conversion
    type (see cast.c).
*/

static BITSTREAM *
enc_cast_exp(BITSTREAM *bs, TYPE t, EXP e, unsigned conv)
{
	BITSTREAM *ts;
	switch (conv) {

	case CONV_EXACT:
	case CONV_FUNC:
	case CONV_STRING:
	case CONV_PTR_PTR_ALIGN:
	case CONV_PTR_MEM_PTR_MEM: {
		/* Trivial conversions */
		bs = enc_exp(bs, e);
		break;
	}

	case CONV_QUAL: {
		/* Qualification conversions */
		if (IS_exp_address(e)) {
			EXP a = DEREF_exp(exp_address_arg(e));
			bs = enc_addr_exp(bs, t, a);
		} else {
			bs = enc_exp(bs, e);
		}
		break;
	}

	case CONV_ELLIPSIS: {
		/* Discarded expression */
		if (overflow_exp(e)) {
			bs = enc_stmt_exp(bs, e, t, 0);
		} else {
			bs = enc_null_exp(bs, t);
		}
		break;
	}

	case CONV_INT_INT:
	case CONV_ENUM: {
		/* Integer to integer conversion */
		TYPE u = DEREF_type(exp_type(e));
		switch (TAG_exp(e)) {
		case exp_char_lit_tag: {
			STRING s = DEREF_str(exp_char_lit_str(e));
			bs = enc_char(bs, s, t, u);
			break;
		}
		case exp_cast_tag: {
			conv = DEREF_unsigned(exp_cast_conv(e));
			if (conv == CONV_BITFIELD) {
				/* Elide following bitfield conversion */
				e = DEREF_exp(exp_cast_arg(e));
				ENC_change_bitfield_to_int(bs);
				bs = enc_variety(bs, t);
				bs = enc_exp(bs, e);
				break;
			}
			goto int_int_label;
		}
		case exp_not_tag:
		case exp_log_and_tag:
		case exp_log_or_tag:
		case exp_test_tag:
		case exp_compare_tag: {
			/* Logical expressions */
			bs = enc_logical(bs, e, t);
			break;
		}
		default :
int_int_label: {
		       if (!eq_type_rep(u, t, 0)) {
			       ENC_change_variety(bs);
			       bs = enc_error_treatment(bs, t);
			       bs = enc_variety(bs, t);
		       }
		       bs = enc_exp(bs, e);
		       break;
	       }
		}
		break;
	}

	case CONV_BITFIELD: {
		/* Bitfield to integer conversion */
		ENC_change_bitfield_to_int(bs);
		bs = enc_variety(bs, t);
		bs = enc_exp(bs, e);
		break;
	}

	case CONV_BITFIELD | CONV_REVERSE: {
		/* Integer to bitfield conversion */
		if (IS_exp_cast(e)) {
			conv = DEREF_unsigned(exp_cast_conv(e));
			if (conv == CONV_INT_INT) {
				/* Elide following integer conversion */
				e = DEREF_exp(exp_cast_arg(e));
			}
		}
		ENC_change_int_to_bitfield(bs);
		bs = enc_bfvar(bs, t);
		bs = enc_exp(bs, e);
		break;
	}

	case CONV_INT_FLT: {
		/* Integer to float conversion */
		if (IS_exp_int_lit(e)) {
			NAT n = DEREF_nat(exp_int_lit_nat(e));
			unsigned long v = get_nat_value(n);
			if (v < SMALL_FLOAT_CONST) {
				/* Small floating point constants */
				bs = enc_float_int(bs,(int)v, t);
				break;
			}
		}
		ENC_float_int(bs);
		ENC_impossible(bs);
		bs = enc_flvar(bs, t);
		bs = enc_exp(bs, e);
		break;
	}

	case CONV_FLT_INT: {
		/* Float to integer conversion */
		ENC_round_with_mode(bs);
		ENC_impossible(bs);
		ENC_RMODE(bs, crt_round_mode);
		bs = enc_variety(bs, t);
		bs = enc_exp(bs, e);
		break;
	}

	case CONV_FLT_FLT: {
		/* Float to float conversion */
		ENC_change_floating_variety(bs);
		ENC_impossible(bs);
		bs = enc_flvar(bs, t);
		bs = enc_exp(bs, e);
		break;
	}

	case CONV_PTR_VOID:
	case CONV_PTR_VOID | CONV_REVERSE :
pointer_void_label: {
			    /* Object pointer and 'void *' conversions */
			    if (conv & CONV_REVERSE) {
				    bs = enc_special(bs, TOK_from_ptr_void);
			    } else {
				    bs = enc_special(bs, TOK_to_ptr_void);
				    t = DEREF_type(exp_type(e));
			    }
			    ts = start_bitstream(NIL(FILE), bs->link);
			    t = DEREF_type(type_ptr_etc_sub(t));
			    ts = enc_alignment(ts, t);
			    ts = enc_exp(ts, e);
			    bs = enc_bitstream(bs, ts);
			    break;
		    }

	case CONV_PTR_PTR:
	case CONV_PTR_BASE:
	case CONV_PTR_PTR | CONV_REVERSE :
	case CONV_PTR_BASE | CONV_REVERSE: {
		/* Pointer to pointer conversion */
		TYPE s = DEREF_type(exp_type(e));
		TYPE ps = DEREF_type(type_ptr_etc_sub(s));
		TYPE pt = DEREF_type(type_ptr_etc_sub(t));
		switch (TAG_type(pt)) {
		case type_top_tag:
		case type_bottom_tag: {
			switch (TAG_type(ps)) {
			case type_top_tag:
			case type_bottom_tag: {
				/* 'void *' to 'void *' */
				bs = enc_exp(bs, e);
				break;
			}
			case type_func_tag: {
				/* Function to 'void *' */
				bs = enc_special(bs, TOK_f_to_pv);
				ts = start_bitstream(NIL(FILE), bs->link);
				ts = enc_exp(ts, e);
				bs = enc_bitstream(bs, ts);
				break;
			}
			default: {
				/* Object pointer to 'void *' */
				conv = CONV_PTR_VOID;
				goto pointer_void_label;
			}
			}
			break;
		}
		case type_func_tag: {
			switch (TAG_type(ps)) {
			case type_top_tag:
			case type_bottom_tag: {
				/* 'void *' to function */
				bs = enc_special(bs, TOK_pv_to_f);
				ts = start_bitstream(NIL(FILE), bs->link);
				ts = enc_exp(ts, e);
				bs = enc_bitstream(bs, ts);
				break;
			}
			case type_func_tag: {
				/* Function to function */
				bs = enc_exp(bs, e);
				break;
			}
			default: {
				/* Object pointer to function */
				BITSTREAM *us;
				bs = enc_special(bs, TOK_pv_to_f);
				ts = start_bitstream(NIL(FILE), bs->link);
				ts = enc_special(ts, TOK_to_ptr_void);
				us = start_bitstream(NIL(FILE), ts->link);
				us = enc_alignment(us, ps);
				us = enc_exp(us, e);
				ts = enc_bitstream(ts, us);
				bs = enc_bitstream(bs, ts);
				break;
			}
			}
			break;
		}
		default: {
			switch (TAG_type(ps)) {
			case type_top_tag:
			case type_bottom_tag: {
				/* 'void *' to object pointer */
				conv = (CONV_PTR_VOID | CONV_REVERSE);
				goto pointer_void_label;
			}
			case type_func_tag: {
				/* Function to object pointer */
				BITSTREAM *us;
				bs = enc_special(bs, TOK_from_ptr_void);
				ts = start_bitstream(NIL(FILE), bs->link);
				ts = enc_alignment(ts, pt);
				ts = enc_special(ts, TOK_f_to_pv);
				us = start_bitstream(NIL(FILE), ts->link);
				us = enc_exp(us, e);
				ts = enc_bitstream(ts, us);
				bs = enc_bitstream(bs, ts);
				break;
			}
			default: {
				/* Object pointer to object pointer */
				if (conv & CONV_REVERSE) {
					/* Force conversion in these cases */
					/* EMPTY */
				} else {
					if (eq_type_rep(ps, pt, 1)) {
						bs = enc_exp(bs, e);
						break;
					}
				}
				bs = enc_special(bs, TOK_ptr_to_ptr);
				ts = start_bitstream(NIL(FILE), bs->link);
				ts = enc_alignment(ts, ps);
				ts = enc_alignment(ts, pt);
				ts = enc_exp(ts, e);
				bs = enc_bitstream(bs, ts);
				break;
			}
			}
			break;
		}
		}
		break;
	}

	case CONV_INT_PTR: {
		/* Integer to pointer conversion */
		TYPE s = DEREF_type(exp_type(e));
		TYPE pt = DEREF_type(type_ptr_etc_sub(t));
		switch (TAG_type(pt)) {
		case type_top_tag:
		case type_bottom_tag: {
			/* Integer to 'void *' */
			bs = enc_special(bs, TOK_i_to_pv);
			ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_variety(ts, s);
			ts = enc_exp(ts, e);
			bs = enc_bitstream(bs, ts);
			break;
		}
		case type_func_tag: {
			/* Integer to function */
			BITSTREAM *us;
			bs = enc_special(bs, TOK_pv_to_f);
			ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_special(ts, TOK_i_to_pv);
			us = start_bitstream(NIL(FILE), ts->link);
			us = enc_variety(us, s);
			us = enc_exp(us, e);
			ts = enc_bitstream(ts, us);
			bs = enc_bitstream(bs, ts);
			break;
		}
		default: {
			/* Integer to object pointer */
			bs = enc_special(bs, TOK_i_to_p);
			ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_variety(ts, s);
			ts = enc_alignment(ts, pt);
			ts = enc_exp(ts, e);
			bs = enc_bitstream(bs, ts);
			break;
		}
		}
		break;
	}

	case CONV_PTR_INT: {
		/* Pointer to integer conversion */
		TYPE s = DEREF_type(exp_type(e));
		TYPE ps = DEREF_type(type_ptr_etc_sub(s));
		switch (TAG_type(ps)) {
		case type_top_tag:
		case type_bottom_tag: {
			/* 'void *' to integer */
			bs = enc_special(bs, TOK_pv_to_i);
			ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_variety(ts, t);
			ts = enc_exp(ts, e);
			bs = enc_bitstream(bs, ts);
			break;
		}
		case type_func_tag: {
			/* Function to integer */
			BITSTREAM *us;
			bs = enc_special(bs, TOK_pv_to_i);
			ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_variety(ts, t);
			ts = enc_special(ts, TOK_f_to_pv);
			us = start_bitstream(NIL(FILE), ts->link);
			us = enc_exp(us, e);
			ts = enc_bitstream(ts, us);
			bs = enc_bitstream(bs, ts);
			break;
		}
		default: {
			/* Object pointer to integer */
			bs = enc_special(bs, TOK_p_to_i);
			ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_alignment(ts, ps);
			ts = enc_variety(ts, t);
			ts = enc_exp(ts, e);
			bs = enc_bitstream(bs, ts);
			break;
		}
		}
		break;
	}

	case CONV_NULL: {
		/* Null pointer conversion */
		bs = enc_null_exp(bs, t);
		break;
	}

	case CONV_PTR_MEM_FUNC: {
		/* Pointer to member function to function conversion */
		IDENTIFIER fn = is_const_ptr_mem(e, 1);
		if (!IS_NULL_id(fn)) {
			/* Constant function */
			ulong n = unit_no(bs, fn, VAR_tag, 0);
			ENC_obtain_tag(bs);
			ENC_make_tag(bs, n);
		} else {
			/* Non-constant function */
			ulong n = LINK_NONE;
			bs = make_ptr_mem_func(bs, e, &n, 0);
			bs = enc_special(bs, TOK_pmf_func);
			ts = start_bitstream(NIL(FILE), bs->link);
			ENC_obtain_tag(ts);
			ENC_make_tag(ts, n);
			bs = enc_bitstream(bs, ts);
		}
		break;
	}

	default: {
		/* Other conversions */
		TYPE s = DEREF_type(exp_type(e));
		if (eq_type_rep(s, t, 0)) {
			bs = enc_exp(bs, e);
		} else {
			ENC_component(bs);
			bs = enc_shape(bs, t);
			ENC_make_compound(bs);
			ENC_offset_max(bs);
			ENC_shape_offset(bs);
			bs = enc_shape(bs, s);
			ENC_shape_offset(bs);
			bs = enc_shape(bs, t);
			ENC_LIST_SMALL(bs, 2);
			ENC_offset_zero(bs);
			bs = enc_alignment(bs, s);
			bs = enc_exp(bs, e);
			ENC_offset_zero(bs);
			bs = enc_alignment(bs, t);
		}
		break;
	}
	}
	return bs;
}


/*
    This routine adds the base class conversion of e using the base
    offset off to the bitstream bs.  conv represents the conversion type.
*/

static BITSTREAM *
enc_base_cast_exp(BITSTREAM *bs, EXP e, OFFSET off, unsigned conv)
{
	if (is_zero_offset(off)) {
		/* Single inheritance */
		bs = enc_exp(bs, e);
	} else {
		/* Multiple inheritance */
		int ctok;
		ulong lab;
		BITSTREAM *ts;
		int non_null = 0;
		ulong n = LINK_NONE;
		TYPE s = DEREF_type(exp_type(e));
		EXP a = DEREF_exp(exp_dummy_value(e));

		/* Check for pointers to member functions */
		if (IS_type_ptr_mem(s)) {
			TYPE ps = DEREF_type(type_ptr_mem_sub(s));
			if (IS_type_func(ps)) {
				VIRTUAL vt;
				CLASS_TYPE ct = DEREF_ctype(type_ptr_mem_of(s));
				IGNORE compile_class(ct);
				vt = DEREF_virt(ctype_virt(ct));
				bs = make_ptr_mem_func(bs, a, &n, 1);
				ENC_SEQ_SMALL(bs, 1);
				if (conv & CONV_REVERSE) {
					bs = enc_special(bs, TOK_pmf_uncast);
				} else {
					bs = enc_special(bs, TOK_pmf_cast);
				}
				ts = start_bitstream(NIL(FILE), bs->link);
				ENC_obtain_tag(ts);
				ENC_make_tag(ts, n);
				ts = enc_offset(ts, off);
				ENC_make_int(ts);
				ts = enc_variety(ts, type_sint);
				ENC_make_signed_nat(ts);
				ENC_OFF(ts);
				if (IS_NULL_virt(vt)) {
					ENC_INT(ts, 0);
					ENC_offset_zero(ts);
					ENC_alignment(ts);
					ts = enc_special(ts, TOK_vtab_diag);
				} else {
					ulong vs = 0;
					OFFSET voff =
					    DEREF_off(virt_table_off(vt));
					ulong tok =
					    DEREF_ulong(virt_table_tok(vt));
					if (IS_off_base(off)) {
						GRAPH gs = DEREF_graph(off_base_graph(off));
						vs = virtual_start(gs);
					} else if (IS_off_deriv(off)) {
						GRAPH gs = DEREF_graph(off_deriv_graph(off));
						vs = virtual_start(gs);
					}
					ENC_INT(ts, vs);
					if (!is_zero_offset(voff)) {
						ENC_offset_add(ts);
						ts = enc_offset(ts, voff);
					}
					tok = link_no(ts, tok, VAR_token);
					ENC_exp_apply_token(ts);
					ENC_make_tok(ts, tok);
					ENC_LEN_SMALL(ts, 0);
				}
				bs = enc_bitstream(bs, ts);
				ENC_contents(bs);
				bs = enc_special(bs, TOK_pmf_type);
				ENC_obtain_tag(bs);
				ENC_make_tag(bs, n);
				return bs;
			}
		}

		/* Check for null pointers */
		switch (TAG_exp(a)) {
		case exp_address_tag:
		case exp_address_mem_tag: {
			/* These can't be null */
			non_null = 1;
			break;
		}
		}
		if (!non_null) {
			/* Set up dummy variable */
			COPY_exp(exp_dummy_value(e), NULL_exp);
			n = unit_no(bs, NULL_id, VAR_tag, 1);
			COPY_ulong(exp_dummy_no(e), n);

			/* Introduce variable */
			ENC_variable(bs);
			bs = enc_access(bs, dspec_none);
			ENC_make_tag(bs, n);
			bs = enc_exp(bs, a);
			ENC_SEQ_SMALL(bs, 1);

			/* Check for null pointer */
			ENC_conditional(bs);
			lab = unit_no(bs, NULL_id, VAR_label, 1);
			ENC_make_label(bs, lab);
			bs = enc_compare(bs, e, NULL_exp, ntest_eq, lab,
					 LINK_NONE);

			/* Assign to variable */
			ENC_assign(bs);
			ENC_obtain_tag(bs);
			ENC_make_tag(bs, n);
		}

		/* Add base class offset */
		ctok = TOK_pm_uncast;
		switch (conv) {
		case CONV_PTR_MEM_BASE: {
			/* Pointer to data member conversions */
			ctok = TOK_pm_cast;
			goto ptr_mem_label;
		}
ptr_mem_label:
		case CONV_PTR_MEM_BASE | CONV_REVERSE: {
			/* Pointer to data member conversions */
			bs = enc_special(bs, ctok);
			ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_exp(ts, e);
			ts = enc_offset(ts, off);
			bs = enc_bitstream(bs, ts);
			break;
		}
		default: {
			/* Pointer conversions */
			if (conv & CONV_REVERSE) {
				TYPE ps = DEREF_type(type_ptr_etc_sub(s));
				bs = enc_special(bs, TOK_down_cast);
				ts = start_bitstream(NIL(FILE), bs->link);
				ts = enc_alignment(ts, ps);
				ts = enc_exp(ts, e);
				ts = enc_offset(ts, off);
				bs = enc_bitstream(bs, ts);
			} else {
				bs = enc_add_ptr(bs, e, LINK_NONE, off, 1);
			}
			break;
		}
		}

		/* Return variable contents */
		if (!non_null) {
			bs = enc_exp(bs, e);
			COPY_exp(exp_dummy_value(e), a);
		}
	}
	return bs;
}


/*
    This routine adds an error treatment corresponding to arithmetic
    operations on the arithmetic type t to the bitstream bs.
*/

BITSTREAM *
enc_error_treatment(BITSTREAM *bs, TYPE t)
{
	if (IS_type_floating(t) || check_int_type(t, btype_signed)) {
		ENC_impossible(bs);
	} else {
		ENC_wrap(bs);
	}
	return bs;
}


/*
    This routine adds the list of virtual function arguments p to the
    bitstream bs.  m is a tag number giving a pointer into the virtual
    function table and j gives the number of the argument corresponding
    to the object pointer.
*/

static BITSTREAM *
enc_virt_args(BITSTREAM *bs, LIST(EXP)p, ulong m, unsigned j)
{
	unsigned i;
	unsigned n = LENGTH_list(p);
	ENC_LIST(bs, n);
	for (i = 0; i < n; i++) {
		EXP e = DEREF_exp(HEAD_list(p));
		if (i == j) {
			TYPE t;
			BITSTREAM *ts;
			ENC_add_to_ptr(bs);
			bs = enc_exp(bs, e);
			bs = enc_special(bs, TOK_pmf_delta);
			ts = start_bitstream(NIL(FILE), bs->link);
			t = DEREF_type(exp_type(e));
			if (IS_type_ptr_etc(t)) {
				t = DEREF_type(type_ptr_etc_sub(t));
			}
			ts = enc_alignment(ts, t);
			ENC_obtain_tag(ts);
			ENC_make_tag(ts, m);
			bs = enc_bitstream(bs, ts);
		} else {
			bs = enc_exp(bs, e);
		}
		p = TAIL_list(p);
	}
	return bs;
}


/*
    This routine outputs an apply_proc construct for the identifier
    function call given by e to the bitstream bs.  t gives the return
    type.
*/

static BITSTREAM *
enc_func_id_call(BITSTREAM *bs, TYPE t, EXP e)
{
	IDENTIFIER id = DEREF_id(exp_func_id_id(e));
	LIST(EXP)args = DEREF_list(exp_func_id_args(e));
	EXP virt = DEREF_exp(exp_func_id_virt(e));

	/* Check for static member functions */
	unsigned tag = TAG_id(id);
	if (tag == id_stat_mem_func_tag) {
		EXP a = DEREF_exp(HEAD_list(args));
		if (!IS_NULL_exp(a)) {
			ENC_SEQ_SMALL(bs, 1);
			bs = enc_exp(bs, a);
		}
		args = TAIL_list(args);
	}

	/* Output the procedure application */
	if (tag == id_token_tag) {
		/* Function token */
		ulong n;
		IGNORE enc_tokdef(id, 0);
		ENC_exp_apply_token(bs);
		n = unit_no(bs, id, VAR_token, 0);
		ENC_make_tok(bs, n);
		if (IS_NULL_list(args)) {
			ENC_LEN_SMALL(bs, 0);
		} else {
			BITSTREAM *ts = start_bitstream(NIL(FILE), bs->link);
			while (!IS_NULL_list(args)) {
				EXP a = DEREF_exp(HEAD_list(args));
				ts = enc_exp(ts, a);
				args = TAIL_list(args);
			}
			bs = enc_bitstream(bs, ts);
		}

	} else if (!IS_NULL_exp(virt)) {
		/* Virtual function */
		EXP a;
		ulong tok;
		VIRTUAL vt;
		unsigned i;
		OFFSET off;
		BITSTREAM *ts;
		ulong n, m, p;

		/* Find class information */
		CLASS_TYPE ct = parent_class(id);
		IGNORE compile_class(ct);
		vt = DEREF_virt(ctype_virt(ct));
		off = DEREF_off(virt_table_off(vt));
		tok = DEREF_ulong(virt_table_tok(vt));
		m = virtual_no(id, vt);

		/* Introduce variable for argument */
		a = DEREF_exp(exp_dummy_value(virt));
		bs = make_ptr_mem_func(bs, a, &n, 0);
		COPY_exp(exp_dummy_value(virt), NULL_exp);
		COPY_ulong(exp_dummy_no(virt), n);

		/* Find pointer to member function */
		p = unit_no(bs, NULL_id, VAR_tag, 1);
		ENC_identify(bs);
		bs = enc_access(bs, dspec_none);
		ENC_make_tag(bs, p);
		bs = enc_special(bs, TOK_vtab_func);
		ts = start_bitstream(NIL(FILE), bs->link);
		ENC_add_to_ptr(ts);
		ts = enc_add_ptr(ts, virt, LINK_NONE, off, 0);
		tok = link_no(ts, tok, VAR_token);
		ENC_exp_apply_token(ts);
		ENC_make_tok(ts, tok);
		ENC_LEN_SMALL(ts, 0);
		ts = enc_make_snat(ts,(int)m);
		bs = enc_bitstream(bs, ts);

		/* Encode function call */
		ENC_apply_proc(bs);
		bs = enc_shape(bs, t);
		bs = enc_special(bs, TOK_pmf_func);
		ts = start_bitstream(NIL(FILE), bs->link);
		ENC_obtain_tag(ts);
		ENC_make_tag(ts, p);
		bs = enc_bitstream(bs, ts);
		i = DEREF_unsigned(exp_func_id_extra(e));
		bs = enc_virt_args(bs, args, p, i);
		ENC_OFF(bs);
		COPY_exp(exp_dummy_value(virt), a);

	} else {
		/* Simple function */
		ulong n;
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if ((ds & dspec_inline) && !(ds & dspec_temp)) {
			/* Check for function inlining */
			if (output_inline) {
				EXP a = check_inline(id, args, t);
				if (!IS_NULL_exp(a)) {
					COPY_dspec(id_storage(id),
						   (ds | dspec_temp));
					bs = enc_exp(bs, a);
					free_exp(a, 1);
					COPY_dspec(id_storage(id), ds);
					return bs;
				}
			}
		}
		ENC_apply_proc(bs);
		bs = enc_shape(bs, t);
		IGNORE capsule_id(id, VAR_tag);
		n = unit_no(bs, id, VAR_tag, 0);
		ENC_obtain_tag(bs);
		ENC_make_tag(bs, n);
		bs = enc_exp_list(bs, args);
		ENC_OFF(bs);
	}
	return bs;
}


/*
    This routine outputs an apply_proc construct for the expression
    function call given by e to the bitstream bs.  t gives the return
    type.
*/

static BITSTREAM *
enc_func_call(BITSTREAM *bs, TYPE t, EXP e)
{
	EXP a = DEREF_exp(exp_func_fn(e));
	LIST(EXP)args = DEREF_list(exp_func_args(e));
	if (IS_exp_call(a)) {
		/* Pointer to member function call */
		EXP b;
		EXP b1;
		TYPE s;
		ulong n;
		unsigned i;
		BITSTREAM *ts;
		CLASS_TYPE ct;
		ulong m = LINK_NONE;

		/* Decompose pointer to member */
		b = DEREF_exp(exp_call_arg(a));
		b1 = DEREF_exp(exp_dummy_value(b));
		a = DEREF_exp(exp_call_ptr(a));
		s = DEREF_type(exp_type(a));
		ct = DEREF_ctype(type_ptr_mem_of(s));

		/* Introduce variable for argument */
		bs = make_ptr_mem_func(bs, b1, &m, 0);
		COPY_exp(exp_dummy_value(b), NULL_exp);
		COPY_ulong(exp_dummy_no(b), m);
		IGNORE compile_class(ct);

		/* Allow for virtual functions */
		bs = make_ptr_mem_func(bs, a, &n, 1);
		ENC_SEQ_SMALL(bs, 1);
		bs = enc_special(bs, TOK_pmf_virt);
		ts = start_bitstream(NIL(FILE), bs->link);
		ENC_obtain_tag(ts);
		ENC_make_tag(ts, n);
		ts = enc_exp(ts, b);
		ts = enc_al_ctype(ts, ct);
		bs = enc_bitstream(bs, ts);

		/* Encode call */
		ENC_apply_proc(bs);
		bs = enc_shape(bs, t);
		bs = enc_special(bs, TOK_pmf_func);
		ts = start_bitstream(NIL(FILE), bs->link);
		ENC_obtain_tag(ts);
		ENC_make_tag(ts, n);
		bs = enc_bitstream(bs, ts);
		i = DEREF_unsigned(exp_func_extra(e));
		bs = enc_virt_args(bs, args, n, i);
		ENC_OFF(bs);
		COPY_exp(exp_dummy_value(b), b1);
	} else {
		/* Simple function call */
		ENC_apply_proc(bs);
		bs = enc_shape(bs, t);
		bs = enc_exp(bs, a);
		bs = enc_exp_list(bs, args);
		ENC_OFF(bs);
	}
	return bs;
}


/*
    This routine adds the dummy expression given by the tag n plus the
    offset off to the bitstream bs.  cnt gives the expression type.
*/

BITSTREAM *
enc_dummy_exp(BITSTREAM *bs, TYPE t, ulong n, OFFSET off, int cnt, int virt)
{
	int bf = 0;
	OFFSET off1 = NULL_off;
	if (cnt > 2) {
		/* Special tag */
		n = last_params[cnt];
		cnt = last_conts[cnt];
	}
	if (n == LINK_NONE) {
		/* This shouldn't happen */
		n = capsule_no(NULL_string, VAR_tag);
	}
	if (n & LINK_EXTERN) {
		/* Allow for global tags */
		n = link_no(bs, n, VAR_tag);
	}
	if (cnt == 1) {
		/* Contents */
		bs = enc_cont_op(bs, t, &bf);
		if (bf) {
			off1 = decons_bitf_off(&off);
			bs = enc_bfvar(bs, t);
		} else {
			bs = enc_shape(bs, t);
		}
	} else if (cnt == 2) {
		/* Contents of pointer */
		ENC_contents(bs);
		ENC_pointer(bs);
		bs = enc_alignment(bs, t);
	}
	if (is_zero_offset(off)) {
		/* Zero offset */
		ENC_obtain_tag(bs);
		ENC_make_tag(bs, n);
	} else if (virt) {
		/* Virtual base offset */
		EXP e;
		MAKE_exp_dummy(t, NULL_exp, n, NULL_off, 0, e);
		bs = enc_add_ptr(bs, e, LINK_NONE, off, 1);
		free_exp(e, 1);
	} else {
		/* Non-virtual base offset */
		ENC_add_to_ptr(bs);
		ENC_obtain_tag(bs);
		ENC_make_tag(bs, n);
		bs = enc_offset(bs, off);
	}
	if (bf) {
		/* End of bitfield contents */
		bs = enc_offset(bs, off1);
	}
	return bs;
}


/*
    This routine adds the assignment or initialisation expression 'a = b'
    to the bitstream bs.
*/

static BITSTREAM *
enc_assign_exp(BITSTREAM *bs, EXP a, EXP b)
{
	TYPE s = DEREF_type(exp_type(a));
	if (IS_exp_dummy(a)) {
		/* Check for dummy expressions */
		EXP c = DEREF_exp(exp_dummy_value(a));
		if (IS_NULL_exp(c)) {
			ulong n = DEREF_ulong(exp_dummy_no(a));
			OFFSET off = DEREF_off(exp_dummy_off(a));
			int cnt = DEREF_int(exp_dummy_cont(a));
			bs = enc_init_tag(bs, n, off, cnt, s, b, NULL_exp, 0);
			return bs;
		}
	}
	if (is_init_complex(b)) {
		/* Introduce identity for complex assignment */
		ulong n;
		bs = make_identity(bs, a, &n, 0, 0);
		bs = enc_init_tag(bs, n, NULL_off, 0, s, b, NULL_exp, 0);
	} else {
		/* Simple assignment */
		int bf = 0;
		bs = enc_assign_op(bs, s, &bf);
		if (bf) {
			/* Bitfield assignment */
			OFFSET off = decons_bitf_exp(&a);
			bs = enc_addr_exp(bs, s, a);
			bs = enc_offset(bs, off);
		} else {
			/* Non-bitfield assignment */
			bs = enc_addr_exp(bs, s, a);
		}
		bs = enc_exp(bs, b);
	}
	return bs;
}


/*
    This routine adds the expression e to the bitstream bs as a TDF EXP.
*/

BITSTREAM *
enc_exp(BITSTREAM *bs, EXP e)
{
	TYPE t;
	if (IS_NULL_exp(e)) {
		/* Deal with null expressions */
		ENC_make_top(bs);
		return bs;
	}

	/* Examine expression cases */
	t = DEREF_type(exp_type(e));
	assert(ORDER_exp == 88);
	switch (TAG_exp(e)) {

	case exp_identifier_tag: {
		/* Identifier lvalue expressions */
		bs = enc_addr_exp(bs, t, e);
		break;
	}

	case exp_int_lit_tag: {
		/* Integer literals */
		NAT n = DEREF_nat(exp_int_lit_nat(e));
		unsigned etag = DEREF_unsigned(exp_int_lit_etag(e));
		bs = enc_int_lit(bs, n, t, etag);
		break;
	}

	case exp_float_lit_tag: {
		/* Floating literals */
		FLOAT f = DEREF_flt(exp_float_lit_flt(e));
		bs = enc_float(bs, f, t);
		break;
	}

	case exp_char_lit_tag: {
		/* Character literals */
		STRING s = DEREF_str(exp_char_lit_str(e));
		bs = enc_char(bs, s, t, t);
		break;
	}

	case exp_string_lit_tag: {
		/* String literals */
		STRING s = DEREF_str(exp_string_lit_str(e));
		bs = enc_string(bs, s, t);
		break;
	}

	case exp_value_tag: {
		/* Undefined values */
		if (IS_type_top(t)) {
			ENC_make_top(bs);
		} else {
			ENC_make_value(bs);
			bs = enc_shape(bs, t);
		}
		break;
	}

	case exp_null_tag:
	case exp_zero_tag: {
		/* Null expressions */
		bs = enc_null_exp(bs, t);
		break;
	}

	case exp_paren_tag:
	case exp_copy_tag: {
		/* Parenthesised expressions */
		EXP a = DEREF_exp(exp_paren_etc_arg(e));
		bs = enc_exp(bs, a);
		break;
	}

	case exp_assign_tag: {
		/* Assignment expressions */
		EXP a = DEREF_exp(exp_assign_ref(e));
		EXP b = DEREF_exp(exp_assign_arg(e));
		bs = enc_assign_exp(bs, a, b);
		break;
	}

	case exp_init_tag: {
		/* Initialisation expressions */
		ulong n;
		int context = 1;
		IDENTIFIER id = DEREF_id(exp_init_id(e));
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		EXP a = DEREF_exp(exp_init_arg(e));
		EXP d = DEREF_exp(id_variable_etc_term(id));
		if (!IS_NULL_exp(d)) {
			while (IS_exp_nof(d)) {
				d = DEREF_exp(exp_nof_pad(d));
			}
			ENC_SEQ_SMALL(bs, 1);
		}
		if (!(ds & dspec_auto)) {
			/* Allow for external variables */
			if (capsule_id(id, VAR_tag)) {
				make_term_global(t, &d);
			}
			context = 2;
		}
		n = unit_no(bs, id, VAR_tag, 0);
		bs = enc_init_tag(bs, n, NULL_off, 0, t, a, d, context);
		break;
	}

	case exp_preinc_tag: {
		/* Pre-increment expressions */
		int bf = 0;
		ulong n = LINK_NONE;
		EXP a = DEREF_exp(exp_preinc_ref(e));
		EXP b = DEREF_exp(exp_preinc_op(e));
		EXP a1 = DEREF_exp(exp_dummy_value(a));
		TYPE s = DEREF_type(exp_type(a));
		int op = DEREF_int(exp_preinc_becomes(e));

		/* Declare identity for complex operations */
		if (op != lex_assign) {
			COPY_exp(exp_dummy_value(a), NULL_exp);
			bs = make_identity(bs, a1, &n, 0, 0);
			COPY_ulong(exp_dummy_no(a), n);
		}

		/* Encode the result */
		bs = enc_assign_op(bs, s, &bf);
		if (n == LINK_NONE) {
			bs = enc_exp(bs, a1);
		} else {
			ENC_obtain_tag(bs);
			ENC_make_tag(bs, n);
		}
		if (bf) {
			OFFSET off = DEREF_off(exp_dummy_off(a));
			bs = enc_offset(bs, off);
		}
		bs = enc_exp(bs, b);
		COPY_exp(exp_dummy_value(a), a1);
		break;
	}

	case exp_postinc_tag: {
		/* Post-increment expressions */
		ulong n;
		int bf = 0;
		EXP a = DEREF_exp(exp_postinc_ref(e));
		EXP b = DEREF_exp(exp_postinc_value(e));
		EXP c = DEREF_exp(exp_postinc_op(e));
		EXP a1 = DEREF_exp(exp_dummy_value(a));
		EXP b1 = NULL_exp;
		TYPE s = DEREF_type(exp_type(a));

		/* Declare outer identity */
		COPY_exp(exp_dummy_value(a), NULL_exp);
		bs = make_identity(bs, a1, &n, 0, 0);
		COPY_ulong(exp_dummy_no(a), n);

		/* Declare inner identity if necessary */
		if (!IS_NULL_exp(b)) {
			ulong m;
			b1 = DEREF_exp(exp_dummy_value(b));
			COPY_exp(exp_dummy_value(b), NULL_exp);
			bs = make_identity(bs, b1, &m, 1, 1);
			COPY_ulong(exp_dummy_no(b), m);
		}

		/* Encode the result */
		bs = enc_assign_op(bs, s, &bf);
		ENC_obtain_tag(bs);
		ENC_make_tag(bs, n);
		if (bf) {
			OFFSET off = DEREF_off(exp_dummy_off(a));
			bs = enc_offset(bs, off);
		}
		bs = enc_exp(bs, c);
		if (!IS_NULL_exp(b)) {
			bs = enc_exp(bs, b);
			COPY_exp(exp_dummy_value(b), b1);
		}
		COPY_exp(exp_dummy_value(a), a1);
		break;
	}

	case exp_indir_tag: {
		/* Indirection expressions */
		EXP a = DEREF_exp(exp_indir_ptr(e));
		bs = enc_exp(bs, a);
		break;
	}

	case exp_contents_tag: {
		/* Contents expressions */
		EXP a = DEREF_exp(exp_contents_ptr(e));
		bs = enc_cont_exp(bs, t, a);
		break;
	}

	case exp_address_tag: {
		/* Address expressions */
		EXP a = DEREF_exp(exp_address_arg(e));
		bs = enc_addr_exp(bs, t, a);
		break;
	}

	case exp_address_mem_tag: {
		/* Member address expressions */
		EXP a = DEREF_exp(exp_address_mem_arg(e));
		IDENTIFIER id = DEREF_id(exp_member_id(a));
		bs = enc_ptr_mem(bs, t, id, NULL_graph);
		break;
	}

	case exp_func_tag: {
		/* Function applications */
		bs = enc_func_call(bs, t, e);
		break;
	}

	case exp_func_id_tag: {
		/* Function identifier applications */
		bs = enc_func_id_call(bs, t, e);
		break;
	}

	case exp_negate_tag: {
		/* Negation expressions */
		if (IS_type_floating(t)) {
			ENC_floating_negate(bs);
		} else {
			ENC_negate(bs);
		}
		goto unary_err_label;
	}

	case exp_compl_tag: {
		/* Complement expressions */
		ENC_not(bs);
		goto unary_label;
	}

	case exp_abs_tag: {
		/* Absolute expressions */
		if (IS_type_floating(t)) {
			ENC_floating_abs(bs);
		} else {
			ENC_abs(bs);
		}
		goto unary_err_label;
	}

unary_err_label: {
			 /* Unary operands with error treatment */
			 bs = enc_error_treatment(bs, t);
			 goto unary_label;
		 }

unary_label: {
		     /* Unary operands */
		     EXP a = DEREF_exp(exp_negate_etc_arg(e));
		     bs = enc_exp(bs, a);
		     break;
	     }

	case exp_plus_tag: {
		/* Addition expressions */
		unsigned tag = TAG_type(t);
		if (tag == type_floating_tag) {
			ENC_floating_plus(bs);
			ENC_impossible(bs);
			ENC_LIST_SMALL(bs, 2);
		} else {
			if (tag == type_enumerate_tag) {
				/* Special case for enumerators */
				t = promote_type(t);
			}
			ENC_plus(bs);
			bs = enc_error_treatment(bs, t);
		}
		goto binary_label;
	}

	case exp_minus_tag: {
		/* Subtraction expressions */
		if (IS_type_floating(t)) {
			ENC_floating_minus(bs);
		} else {
			ENC_minus(bs);
		}
		goto binary_err_label;
	}

	case exp_mult_tag: {
		/* Multiplication expressions */
		if (IS_type_floating(t)) {
			ENC_floating_mult(bs);
			ENC_impossible(bs);
			ENC_LIST_SMALL(bs, 2);
		} else {
			ENC_mult(bs);
			bs = enc_error_treatment(bs, t);
		}
		goto binary_label;
	}

	case exp_div_tag: {
		/* Division expressions */
		if (IS_type_floating(t)) {
			ENC_floating_div(bs);
		} else {
			int div_mode = division_mode;
			if (div_mode == 3) {
				/* Tokenised division */
				bs = enc_special(bs, TOK_div);
				goto division_label;
			}
			switch (div_mode) {
			case 0:
				ENC_div0(bs);
				break;
			case 1:
				ENC_div1(bs);
				break;
			case 2:
				ENC_div2(bs);
				break;
			}
			ENC_impossible(bs);
		}
		goto binary_err_label;
	}

	case exp_rem_tag: {
		/* Remainder expressions */
		int div_mode = division_mode;
		if (div_mode == 3) {
			/* Tokenised division */
			bs = enc_special(bs, TOK_rem);
			goto division_label;
		}
		switch (div_mode) {
		case 0:
			ENC_rem0(bs);
			break;
		case 1:
			ENC_rem1(bs);
			break;
		case 2:
			ENC_rem2(bs);
			break;
		}
		ENC_impossible(bs);
		goto binary_err_label;
	}

division_label: {
			/* Division operands */
			EXP a = DEREF_exp(exp_plus_etc_arg1(e));
			EXP b = DEREF_exp(exp_plus_etc_arg2(e));
			BITSTREAM *ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_exp(ts, a);
			ts = enc_exp(ts, b);
			bs = enc_bitstream(bs, ts);
			break;
		}

	case exp_and_tag: {
		/* Bitwise and expressions */
		ENC_and(bs);
		goto binary_label;
	}

	case exp_or_tag: {
		/* Bitwise or expressions */
		ENC_or(bs);
		goto binary_label;
	}

	case exp_xor_tag: {
		/* Bitwise xor expressions */
		ENC_xor(bs);
		goto binary_label;
	}

	case exp_lshift_tag: {
		/* Left shift expressions */
		ENC_shift_left(bs);
		goto binary_err_label;
	}

	case exp_rshift_tag: {
		/* Right shift expressions */
		ENC_shift_right(bs);
		goto binary_label;
	}

	case exp_max_tag: {
		/* Maximum expressions */
		if (IS_type_floating(t)) {
			ENC_floating_maximum(bs);
#if (TDF_major >= 4)
			ENC_impossible(bs);
#endif
		} else {
			ENC_maximum(bs);
		}
		goto binary_label;
	}

	case exp_min_tag: {
		/* Minimum expressions */
		if (IS_type_floating(t)) {
			ENC_floating_minimum(bs);
#if (TDF_major >= 4)
			ENC_impossible(bs);
#endif
		} else {
			ENC_minimum(bs);
		}
		goto binary_label;
	}

binary_err_label: {
			  /* Binary operands with error treatment */
			  bs = enc_error_treatment(bs, t);
			  goto binary_label;
		  }

binary_label: {
		      /* Binary operands */
		      EXP a = DEREF_exp(exp_plus_etc_arg1(e));
		      EXP b = DEREF_exp(exp_plus_etc_arg2(e));
		      bs = enc_exp(bs, a);
		      bs = enc_exp(bs, b);
		      break;
	      }

	case exp_cast_tag: {
		/* Cast expressions */
		EXP a = DEREF_exp(exp_cast_arg(e));
		unsigned conv = DEREF_unsigned(exp_cast_conv(e));
		bs = enc_cast_exp(bs, t, a, conv);
		break;
	}

	case exp_base_cast_tag: {
		/* Base class cast expressions */
		EXP a = DEREF_exp(exp_base_cast_arg(e));
		OFFSET off = DEREF_off(exp_base_cast_off(e));
		unsigned conv = DEREF_unsigned(exp_base_cast_conv(e));
		if (conv == CONV_PTR_MEM_BASE) {
			/* Check for constant pointer to members */
			IDENTIFIER fn = is_const_ptr_mem(a, 0);
			if (!IS_NULL_id(fn)) {
				CLASS_TYPE cs = parent_class(fn);
				CLASS_TYPE ct = DEREF_ctype(type_ptr_mem_of(t));
				GRAPH gr = find_base_class(ct, cs, 0);
				bs = enc_ptr_mem(bs, t, fn, gr);
				break;
			}
		}
		bs = enc_base_cast_exp(bs, a, off, conv);
		break;
	}

	case exp_add_ptr_tag: {
		/* Pointer additions */
		EXP a = DEREF_exp(exp_add_ptr_ptr(e));
		OFFSET off = DEREF_off(exp_add_ptr_off(e));
		int virt = DEREF_int(exp_add_ptr_virt(e));
		bs = enc_add_ptr(bs, a, LINK_NONE, off, virt);
		break;
	}

	case exp_offset_size_tag: {
		/* Size of offset */
		OFFSET off = DEREF_off(exp_offset_size_off(e));
		TYPE s = DEREF_type(exp_offset_size_step(e));
		ENC_offset_div(bs);
		bs = enc_variety(bs, t);
		bs = enc_offset(bs, off);
		bs = enc_shape_offset(bs, s);
		break;
	}

	case exp_constr_tag: {
		/* Constructor calls */
		EXP a = DEREF_exp(exp_constr_call(e));
		bs = enc_exp(bs, a);
		break;
	}

	case exp_destr_tag: {
		/* Destructor calls */
		EXP a = DEREF_exp(exp_destr_call(e));
		bs = enc_exp(bs, a);
		break;
	}

	case exp_rtti_no_tag: {
		/* Link-time type information */
		TYPE s = DEREF_type(exp_rtti_no_arg(e));
		ENC_make_int(bs);
		bs = enc_variety(bs, t);
		bs = enc_arith(bs, s, 0);
		break;
	}

	case exp_dynamic_tag: {
		/* Dynamic initialisers */
		EXP a = DEREF_exp(exp_dynamic_arg(e));
		bs = enc_exp(bs, a);
		break;
	}

	case exp_aggregate_tag: {
		/* Aggregate initialisers */
		unsigned tt = TAG_type(t);
		if (tt == type_array_tag) {
			bs = enc_init_array(bs, e, NULL_nat, t);
		} else if (tt == type_compound_tag) {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			bs = enc_init_class(bs, e, ct);
		}
		break;
	}

	case exp_nof_tag: {
		/* Array initialisers */
		int pad = 1;
		EXP a = DEREF_exp(exp_nof_start(e));
		NAT n = DEREF_nat(exp_nof_size(e));
		EXP b = DEREF_exp(exp_nof_pad(e));
		EXP c = DEREF_exp(exp_nof_end(e));
		if (!IS_NULL_exp(c))ENC_concat_nof(bs);
		if (!IS_NULL_exp(a)) {
			/* Encode initial component */
			if (IS_exp_aggregate(a) && is_zero_exp(b)) {
				/* Deal with integral arrays */
				bs = enc_init_array(bs, a, n, t);
				break;
			}
			if (is_zero_nat(n)) {
				pad = 0;
			} else {
				ENC_concat_nof(bs);
			}
			bs = enc_exp(bs, a);
		}
		if (pad) {
			ENC_n_copies(bs);
			bs = enc_nat(bs, n, 1);
			if (IS_NULL_exp(b)) {
				TYPE s = DEREF_type(type_array_sub(t));
				bs = enc_null_exp(bs, s);
			} else {
				bs = enc_exp(bs, b);
			}
		}
		if (!IS_NULL_exp(c)) {
			bs = enc_exp(bs, c);
		}
		break;
	}

	case exp_call_tag: {
		/* Shouldn't happen */
		EXP a = DEREF_exp(exp_call_ptr(e));
		EXP b = DEREF_exp(exp_call_arg(e));
		ENC_SEQ_SMALL(bs, 1);
		bs = enc_exp(bs, a);
		bs = enc_exp(bs, b);
		break;
	}

	case exp_not_tag:
	case exp_log_and_tag:
	case exp_log_or_tag:
	case exp_test_tag:
	case exp_compare_tag: {
		/* Logical expressions */
		bs = enc_logical(bs, e, t);
		break;
	}

	case exp_assembler_tag: {
		/* Assembler expression */
		bs = enc_asm(bs, e);
		break;
	}

	case exp_fail_tag: {
		/* Install-time failure expression */
		string s = DEREF_string(exp_fail_msg(e));
		ENC_fail_installer(bs);
		ENC_make_string(bs);
		bs = enc_ustring(bs, s);
		break;
	}

	case exp_token_tag: {
		/* Token applications */
		IDENTIFIER tok = DEREF_id(exp_token_tok(e));
		LIST(TOKEN)args = DEREF_list(exp_token_args(e));
		bs = enc_token(bs, tok, args);
		break;
	}

	case exp_dummy_tag: {
		/* Dummy identifier tag */
		EXP a = DEREF_exp(exp_dummy_value(e));
		if (IS_NULL_exp(a)) {
			ulong n = DEREF_ulong(exp_dummy_no(e));
			OFFSET off = DEREF_off(exp_dummy_off(e));
			int cnt = DEREF_int(exp_dummy_cont(e));
			int virt = DEREF_int(exp_dummy_virt(e));
			bs = enc_dummy_exp(bs, t, n, off, cnt, virt);
		} else {
			bs = enc_exp(bs, a);
		}
		break;
	}

#if LANGUAGE_CPP
	case exp_alloc_tag: {
		/* Allocator calls */
		bs = enc_alloc(bs, e);
		break;
	}

	case exp_dealloc_tag: {
		/* Deallocator calls */
		bs = enc_dealloc(bs, e, LINK_NONE);
		break;
	}

	case exp_rtti_tag: {
		/* Run-time type information */
		if (IS_type_compound(t)) {
			/* Make sure that 'type_info' is completed */
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			IGNORE compile_class(ct);
		}
		bs = enc_rtti_exp(bs, e);
		break;
	}

	case exp_rtti_type_tag: {
		/* Run-time type information */
		TYPE s = DEREF_type(exp_rtti_type_arg(e));
		int op = DEREF_int(exp_rtti_type_op(e));
		if (IS_type_compound(t)) {
			/* Make sure that 'type_info' is completed */
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			IGNORE compile_class(ct);
		}
		bs = enc_rtti_type(bs, s, op);
		break;
	}

	case exp_dyn_cast_tag: {
		/* Dynamic cast expressions */
		bs = enc_dyn_cast(bs, e);
		break;
	}

	case exp_initialiser_tag: {
		/* Constructor initialisers */
		bs = enc_ctor_init(bs, e);
		break;
	}

	case exp_exception_tag: {
		/* Throw expression */
		EXP a = DEREF_exp(exp_exception_arg(e));
		EXP b = DEREF_exp(exp_exception_size(e));
		EXP d = DEREF_exp(exp_exception_destr(e));
		bs = enc_throw(bs, a, b, d);
		break;
	}

	case exp_thrown_tag: {
		/* Thrown expression */
		int done = DEREF_int(exp_thrown_done(e));
		if (done) {
			bs = enc_special(bs, TOK_except_caught);
		} else {
			bs = enc_thrown(bs, t);
		}
		break;
	}
#endif

	case exp_comma_tag:
	case exp_if_stmt_tag:
	case exp_hash_if_tag:
	case exp_location_tag: {
		/* Statement-like expressions */
		bs = enc_stmt_exp(bs, e, t, 1);
		break;
	}

	case exp_reach_tag:
	case exp_unreach_tag:
	case exp_sequence_tag:
	case exp_solve_stmt_tag:
	case exp_decl_stmt_tag:
	case exp_while_stmt_tag:
	case exp_do_stmt_tag:
	case exp_switch_stmt_tag:
	case exp_return_stmt_tag:
	case exp_goto_stmt_tag:
	case exp_label_stmt_tag:
	case exp_try_block_tag:
	case exp_handler_tag: {
		/* Statements */
		bs = enc_stmt(bs, e);
		break;
	}

	case exp_member_tag:
	case exp_ambiguous_tag:
	case exp_undeclared_tag:
	case exp_set_tag:
	case exp_unused_tag:
	case exp_op_tag:
	case exp_opn_tag:
	case exp_uncompiled_tag:
	default: {
		/* Illegal expressions */
		ENC_make_top(bs);
		break;
	}
	}
	return bs;
}

