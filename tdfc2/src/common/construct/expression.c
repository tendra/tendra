/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "exp_ops.h"
#include "id_ops.h"
#include "nat_ops.h"
#include "off_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "basetype.h"
#include "cast.h"
#include "check.h"
#include "chktype.h"
#include "class.h"
#include "compile.h"
#include "constant.h"
#include "construct.h"
#include "convert.h"
#include "derive.h"
#include "expression.h"
#include "identifier.h"
#include "initialise.h"
#include "literal.h"
#include "member.h"
#include "operator.h"
#include "overload.h"
#include "predict.h"
#include "quality.h"
#include "statement.h"
#include "syntax.h"
#include "template.h"


/*
    This routine creates an error expression.  The result is an lvalue
    if lv is true.
*/

EXP
make_error_exp(int lv)
{
	EXP a;
	TYPE t = type_error;
	if (lv) {
		t = lvalue_type(t);
	}
	MAKE_exp_value(t, a);
	return a;
}


/*
    This routine checks converts the integral expression a into a null
    pointer (or pointer to member) constant of type t.  Basically this
    consists of testing whether a evaluates to zero, however writing
    anything other than a plain literal '0' for the null pointer (for
    example '1 - 1') is considered bad practice, so there is a test
    for this.  The null expression is returns if a is non-zero.
*/

EXP
make_null_ptr(EXP a, TYPE t)
{
	EXP e = NULL_exp;
	if (IS_NULL_exp(a)) {
		/* Allow null expressions */
		MAKE_exp_null(t, e);
	} else {
		if (is_zero_exp(a)) {
			if (!is_literal(a)) {
				/* Report complex literals */
				report(crt_loc, ERR_conv_ptr_null_complex());
			}
			MAKE_exp_null(t, e);
		} else {
			if (in_template_decl && IS_exp_int_lit(a)) {
				if (depends_on_exp(a, any_templ_param, 0)) {
					/* Check for template parameters */
					report(crt_loc,
					       ERR_conv_ptr_null_complex());
					MAKE_exp_op(t, lex_pointer, a,
						    NULL_exp, e);
				}
			}
		}
	}
	return e;
}


/*
    This routine constructs the expression '( a )'.  Note that parentheses
    are only needed in order to perform analysis for odd precedence in
    expressions.  It is otherwise just an identity operation.
*/

EXP
make_paren_exp(EXP a)
{
	EXP e;
	TYPE ta = DEREF_type(exp_type(a));
	if (IS_exp_int_lit(a)) {
		/* Deal with integer constant expressions */
		unsigned etag = DEREF_unsigned(exp_int_lit_etag(a));
		switch (etag) {
		case exp_int_lit_tag:
		case exp_null_tag:
		case exp_identifier_tag: {
			/* Don't bother with literals and enumerators */
			e = a;
			break;
		}
		default: {
			/* Mark other values as parenthesised */
			NAT n = DEREF_nat(exp_int_lit_nat(a));
			MAKE_exp_int_lit(ta, n, exp_paren_tag, e);
			break;
		}
		}
	} else {
		MAKE_exp_paren(ta, a, e);
	}
	return e;
}


/*
    This routine constructs an offset of a times the offset of the type t.
    This is negated if neg is true.
*/

OFFSET
make_off_mult(TYPE t, EXP a, int neg)
{
	OFFSET off;
	if (IS_type_top_etc(t)) {
		/* Map 'void *' to 'char *' */
		t = type_char;
	}
	if (IS_exp_int_lit(a)) {
		/* Constant offsets */
		int neg1 = neg;
		NAT n = DEREF_nat(exp_int_lit_nat(a));
		if (IS_nat_neg(n)) {
			n = DEREF_nat(nat_neg_arg(n));
			neg1 = !neg1;
		}
		if (IS_nat_small(n)) {
			unsigned v = DEREF_unsigned(nat_small_value(n));
			if (v < 100) {
				if (v == 0) {
					MAKE_off_zero(t, off);
				} else if (v == 1) {
					MAKE_off_type(t, off);
				} else {
					MAKE_type_array(cv_none, t, n, t);
					MAKE_off_type(t, off);
				}
				if (neg1) {
					MAKE_off_negate(off, off);
				}
				return off;
			}
		}
	}
	MAKE_off_type(t, off);
	MAKE_off_mult(off, a, off);
	if (neg) {
		MAKE_off_negate(off, off);
	}
	return off;
}


/*
    This routine creates a pointer of type t by adding the offset off to
    the pointer expression a.  For pointers of type 'void *' conversions
    are performed to and from 'char *'.
*/

EXP
make_add_ptr(TYPE t, EXP a, OFFSET off)
{
	EXP e;
	if (IS_type_ptr(t)) {
		TYPE s = DEREF_type(type_ptr_sub(t));
		if (IS_type_top_etc(s)) {
			TYPE p = type_char_star;
			MAKE_exp_cast(p,(CONV_PTR_VOID | CONV_REVERSE), a, e);
			e = make_add_ptr(p, e, off);
			MAKE_exp_cast(t, CONV_PTR_VOID, e, e);
			return e;
		}
	}
	MAKE_exp_add_ptr(t, a, off, 0, e);
	return e;
}


/*
    This routine constructs the expression 'a [b]'.  The result is an
    lvalue.  Note that if a is immediately derived from an array and b is
    an integer constant then bounds checks are applied to the operation.
    However once an array has been converted into a pointer any associated
    bounds information is lost.
*/

EXP
make_index_exp(EXP a, EXP b)
{
	TYPE t;
	EXP e, p;
	int z = 0;
	OFFSET off;
	TYPE ta, tb;
	unsigned ca, cb;
	ERROR err = NULL_err;
	TYPE sa = DEREF_type(exp_type(a));
	TYPE sb = DEREF_type(exp_type(b));

	/* Do reference conversions */
	a = convert_reference(a, REF_NORMAL);
	b = convert_reference(b, REF_NORMAL);

	/* Find the operand types */
	ta = DEREF_type(exp_type(a));
	ca = type_category(&ta);
	tb = DEREF_type(exp_type(b));
	cb = type_category(&tb);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca) || IS_TYPE_OVERLOAD(cb)) {
		if (overload_depth == 0) {
			e = binary_overload(lex_array_Hop, a, b);
			return e;
		}
	}
#endif

	/* Do lvalue conversions */
	if (IS_TYPE_ADDRESS(ca)) {
		a = convert_lvalue(a);
		ta = DEREF_type(exp_type(a));
		ca = type_category(&ta);
	}
	if (IS_TYPE_ADDRESS(cb)) {
		b = convert_lvalue(b);
		tb = DEREF_type(exp_type(b));
		cb = type_category(&tb);
	}

	/* Swap operands if the second is a pointer */
	if (IS_TYPE_PTR(cb)) {
		/* Alright because order of evaluation is undefined */
		EXP c = a;
		TYPE tc = ta;
		unsigned cc = ca;
		a = b;
		b = c;
		ta = tb;
		tb = tc;
		ca = cb;
		cb = cc;
		sa = sb;
	}

	/* The first operand should now be a pointer */
	if (!IS_TYPE_PTR(ca)) {
		if (!IS_TYPE_ERROR(ca) && !IS_TYPE_ERROR(cb)) {
			report(crt_loc, ERR_expr_sub_ptr_op(ta, tb));
		}
		return make_error_exp(0);
	}

	/* The second operand should be integral */
	if (!IS_TYPE_INT(cb)) {
		if (!IS_TYPE_ERROR(cb)) {
			report(crt_loc, ERR_expr_sub_int_op(tb));
		}
		/* Continue with zero index */
		z = 1;
	}

	/* Check index value */
	if (IS_exp_int_lit(b)) {
		if (IS_type_array(sa)) {
			check_bounds(lex_array_Hop, sa, b);
		}
		z = is_zero_exp(b);
	} else {
		if (eq_type_unqual(tb, type_char)) {
			report(crt_loc, ERR_expr_sub_char_op(tb));
		}
	}

	/* The pointer must be to a complete object type */
	t = check_pointer(ta, &err);
	if (!IS_NULL_err(err)) {
		err = concat_error(err, ERR_expr_sub_incompl());
		report(crt_loc, err);
	}

	/* Construct pointer to the result */
	if (z) {
		/* Zero offset */
		p = a;
	} else {
		/* Non-zero offset */
		if (IS_TYPE_BITF(cb)) {
			b = convert_bitfield(b);
		}
		off = make_off_mult(t, b, 0);
		p = make_add_ptr(ta, a, off);
	}

	/* The result is an lvalue */
	t = lvalue_type(t);

	/* Construct the result */
	MAKE_exp_indir(t, p, e);
	COPY_int(exp_indir_index(e), 1);
	return e;
}


/*
    This routine constructs the indirection expression '*a'.  The result
    is an lvalue.
*/

EXP
make_indir_exp(EXP a)
{
	EXP e;
	TYPE ta;
	unsigned ca;

	/* Do reference conversion */
	a = convert_reference(a, REF_NORMAL);

	/* Find operand type */
	ta = DEREF_type(exp_type(a));
	ca = type_category(&ta);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca)) {
		if (overload_depth == 0) {
			e = unary_overload(lex_star, a);
			return e;
		}
	}
#endif

	/* Do lvalue conversion */
	if (IS_TYPE_ADDRESS(ca)) {
		a = convert_lvalue(a);
		ta = DEREF_type(exp_type(a));
		ca = type_category(&ta);
	}

	/* Operand can be pointer ... */
	if (IS_TYPE_PTR(ca)) {
		TYPE t = check_pointer(ta, KILL_err);
		if (IS_type_top_etc(t)) {
			/* The pointer cannot be 'void *' */
			report(crt_loc, ERR_expr_unary_op_indir_void(ta));
		}
		if (IS_exp_null(a)) {
			/* Check for obvious null pointers */
			report(crt_loc, ERR_expr_unary_op_indir_null(lex_star));
		}

		/* The result is an lvalue */
		t = lvalue_type(t);

		/* Construct the result */
		MAKE_exp_indir(t, a, e);
		return e;
	}

	/* ... and nothing else */
	if (!IS_TYPE_ERROR(ca)) {
		report(crt_loc, ERR_expr_unary_op_indir_op(ta));
	}
	return make_error_exp(1);
}


/*
    This routine constructs a pointer to the expression a which designates
    an object.  Any errors arising are added to err.
*/

EXP
make_ref_object(EXP a, ERROR *err)
{
	EXP e;
	TYPE p;
	TYPE ta = DEREF_type(exp_type(a));
	unsigned ca = type_category(&ta);
	if (IS_TYPE_ERROR(ca)) {
		/* Error progagation */
		e = make_error_exp(0);
		return e;
	}
	if (!IS_TYPE_LVALUE(ca)) {
		/* Operand should be an lvalue */
		add_error(err, ERR_expr_unary_op_ref_lvalue());
	}
	if (IS_TYPE_BITF(ca)) {
		/* Can't apply to a bitfield */
		add_error(err, ERR_expr_unary_op_ref_bitf());
		ta = find_bitfield_type(ta);
	}
	if (option(OPT_addr_register) && used_register) {
		/* Can't apply to a register variable in C */
		EXP b = NULL_exp;
		DECL_SPEC ds = find_exp_linkage(a, &b, 1);
		if ((ds & dspec_register) && !(ds & dspec_temp)) {
			if (IS_exp_identifier(b)) {
				IDENTIFIER id = DEREF_id(exp_identifier_id(b));
				add_error(err,
					  ERR_expr_unary_op_ref_register(id));
			}
		}
	}
	if (IS_type_top_etc(ta)) {
		/* Can't apply to void */
		add_error(err, ERR_expr_unary_op_ref_void(ta));
	} else {
		/* Check for incomplete types */
		ERROR err2 = check_incomplete(ta);
		if (!IS_NULL_err(err2)) {
			add_error(err, err2);
			add_error(err, ERR_expr_unary_op_ref_incompl());
		}
	}

	/* Construct the result */
	ta = rvalue_type(ta);
	MAKE_type_ptr(cv_none, ta, p);
	MAKE_exp_address(p, a, e);
	return e;
}


/*
    This routine constructs a pointer to the expression a which designates
    a class member.  Note that a can represent an overloaded member function
    in which case the actual result type can only be determined after
    overload resolution.  Also the type of an inherited member is that
    of its base class rather than its derived class.
*/

#if LANGUAGE_CPP

static EXP
make_ref_member(EXP a, int paren, int res)
{
	EXP e;
	TYPE p;
	DECL_SPEC ds;

	/* Find the base class */
	IDENTIFIER id = DEREF_id(exp_member_id(a));
	IDENTIFIER uid = DEREF_id(id_alias(id));
	CLASS_TYPE tc = parent_class(uid);

	/* Find the result type */
	TYPE ta = DEREF_type(exp_type(a));
	ta = rvalue_type(ta);
	if (IS_type_bitfield(ta)) {
		/* Can't apply to a bitfield */
		report(crt_loc, ERR_expr_unary_op_ref_bitf());
		ta = find_bitfield_type(ta);
	}
	MAKE_type_ptr_mem(cv_none, tc, ta, p);

	/* Construct the result */
	if (!EQ_id(id, uid)) {
		QUALIFIER qual = DEREF_qual(exp_member_qual(a));
		MAKE_exp_member(ta, uid, qual, a);
	}
	MAKE_exp_address_mem(p, a, paren, e);
	if (res) {
		/* Mark identifier as used */
		if (res == 2) {
			use_id(id, suppress_usage);
		} else {
			reuse_id(id, suppress_usage);
		}
		ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_trivial) {
			/* Can take the address of a trivial function */
			CONS_id(id, pending_funcs, pending_funcs);
		}
	}
	return e;
}

#endif


/*
    This routine constructs the expression '&a' for constructing a pointer
    to a or a pointer member to a.  The res argument is true to indicate
    that any overloaded functions in a have been resolved.
*/

EXP
make_ref_exp(EXP a, int res)
{
	EXP e;
	ERROR err = NULL_err;

#if LANGUAGE_CPP
	TYPE ta;
	unsigned ca;
	int paren = IS_exp_paren(a);

	/* Perform reference conversions */
	a = convert_reference(a, REF_ADDRESS);

	/* Check for members */
	if (IS_exp_member(a)) {
		int is_mem = 1;
		IDENTIFIER id = DEREF_id(exp_member_id(a));
		QUALIFIER idtype = DEREF_qual(exp_member_qual(a));
		idtype &= ~qual_mark;
		if (!(idtype & qual_explicit)) {
			EXP b = make_this_field(id);
			if (!IS_NULL_exp(b)) {
				a = convert_reference(b, REF_ADDRESS);
				is_mem = 0;
			}
		}
		if (is_mem) {
			if (IS_id_member(id))res = 2;
			if (res) {
				if (idtype == qual_none) {
					/* Identifiers must be qualified */
					report(crt_loc,
					       ERR_expr_unary_op_ref_unqual());
				} else {
					if (idtype != qual_nested) {
						/* Shouldn't have fully
						 * qualified identifier */
						report(crt_loc, ERR_expr_unary_op_ref_full());
					}
					if (paren) {
						/* Identifier can't be
						 * parenthesised */
						report(crt_loc, ERR_expr_unary_op_ref_paren());
						paren = 0;
					}
				}
			}
			e = make_ref_member(a, paren, res);
			return e;
		}
	}

	/* Get operand type */
	ta = DEREF_type(exp_type(a));
	ca = type_category(&ta);
	if (IS_TYPE_OVERLOAD(ca)) {
		/* Check for overloading */
		if (overload_depth == 0) {
			e = unary_overload(lex_and_H1, a);
			return e;
		}
		if (IS_type_compound(ta)) {
			/* Mark class types */
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(ta));
			CLASS_USAGE cu = DEREF_cusage(ctype_usage(ct));
			cu |= cusage_address;
			COPY_cusage(ctype_usage(ct), cu);
		}
	}

#else

	/* Perform reference conversions */
	a = convert_reference(a, REF_ADDRESS);
	UNUSED(res);

#endif

	/* Construct the result */
	e = make_ref_object(a, &err);
	if (!IS_NULL_err(err)) {
		report(crt_loc, err);
	}
	return e;
}


/*
    This routine constructs the unary arithmetic expression 'op a'.  For
    '+a' the expression constructed is '( a )' rather than 'a'.  This is
    to prevent expressions like 'a << +( b + c )' confusing the dubious
    parenthesis checks.
*/

EXP
make_uminus_exp(int op, EXP a)
{
	TYPE ta;
	unsigned ca;

	/* Find operation information */
	unsigned cb = CTYPE_ARITH;
	unsigned tag = exp_negate_tag;
	switch (op) {
	case lex_plus: {
		tag = exp_paren_tag;
#if LANGUAGE_CPP
		cb = CTYPE_SCALAR;
#endif
		break;
	}
	case lex_compl_H1: {
		tag = exp_compl_tag;
		cb = CTYPE_INT;
		break;
	}
	case lex_abs: {
		tag = exp_abs_tag;
		break;
	}
	}

	/* Do reference conversion */
	a = convert_reference(a, REF_NORMAL);

	/* Find the operand type */
	ta = DEREF_type(exp_type(a));
	ca = type_category(&ta);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca)) {
		if (overload_depth == 0) {
			EXP e = unary_overload(op, a);
			return e;
		}
	}
#endif

	/* Do lvalue conversion */
	if (IS_TYPE_ADDRESS(ca)) {
		a = convert_lvalue(a);
		ta = DEREF_type(exp_type(a));
		ca = type_category(&ta);
	}

	/* Check operand type ... */
	if (ca & cb) {
		EXP e;
		TYPE pta = promote_type(ta);
		a = convert_promote(pta, a);
		if (tag == exp_paren_tag) {
			e = make_paren_exp(a);
		} else {
			if (IS_exp_int_lit(a)) {
				e = make_unary_nat(tag, a);
			} else {
				MAKE_exp_negate_etc(tag, pta, a, e);
			}
		}
		return e;
	}

	/* ... and report error otherwise */
	if (!IS_TYPE_ERROR(ca)) {
		ERROR err;
		if (cb == CTYPE_SCALAR) {
			err = ERR_expr_unary_op_uplus_op(op, ta);
		} else if (cb == CTYPE_ARITH) {
			err = ERR_expr_unary_op_uminus_op(op, ta);
		} else {
			err = ERR_expr_unary_op_compl_op(op, ta);
		}
		report(crt_loc, err);
	}
	return make_error_exp(0);
}


/*
    This routine constructs the expression '!a'.
*/

EXP
make_not_exp(EXP a)
{
	TYPE ta;
	EXP e, b;
	unsigned ca;
	ERROR err = NULL_err;
	unsigned tag = TAG_exp(a);

	/* Do reference conversion */
	a = convert_reference(a, REF_NORMAL);

	/* Find the operand type */
	ta = DEREF_type(exp_type(a));
	ca = type_category(&ta);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca)) {
		if (overload_depth == 0) {
			e = unary_overload(lex_not_H1, a);
			return e;
		}
	}
#endif

	/* Do lvalue conversion */
	if (IS_TYPE_ADDRESS(ca)) {
		a = convert_lvalue(a);
	}

	/* Convert the operand to a boolean */
	b = convert_boolean(a, tag, &err);
	if (!IS_NULL_err(err)) {
		err = concat_error(err, ERR_expr_unary_op_not_op());
		report(crt_loc, err);
	}

	/* Construct the result */
	if (IS_exp_int_lit(b)) {
		e = make_unary_nat(exp_not_tag, b);
	} else {
		MAKE_exp_not(type_bool, b, e);
	}
	return e;
}


/*
    This flag gives the mode to be used in integer division and remainder
    operations.  The values 0, 1 and 2 correspond to the TDF operations
    div0, div1 and div2 and rem0, rem1 and rem2 respectively.  The value 3
    indicates that the decision should be postponed to the installers.
*/

int division_mode = 3;


/*
    This routine checks the division operation 'a / b' or 'a % b' for
    dubious constant operands.  All the necessary operand and arithmetic
    type conversions have already been performed on a and b.  The routine
    returns 1 if both operands are integer constants and b is not zero.
*/

int
check_div_exp(int op, EXP a, EXP b)
{
	int eval = 1;
	int div_mode = division_mode;
	if (IS_exp_int_lit(b)) {
		/* Check the second operand */
		NAT n = DEREF_nat(exp_int_lit_nat(b));
		if (is_zero_nat(n)) {
			/* Report division by zero */
			report(crt_loc, ERR_expr_mul_div_zero(op));
			return 0;
		}
		if (div_mode != 1 && div_mode != 2) {
			if (is_negative_nat(n) && !divides_nat(a, b)) {
				/* Division by negative is undefined */
				report(crt_loc, ERR_expr_mul_div_neg(op, n));
			}
		}
	} else {
		eval = 0;
	}
	if (IS_exp_int_lit(a)) {
		/* Check the first operand */
		if (div_mode != 1 && div_mode != 2) {
			NAT n = DEREF_nat(exp_int_lit_nat(a));
			if (is_negative_nat(n) && !divides_nat(a, b)) {
				/* Division of negative is undefined */
				report(crt_loc, ERR_expr_mul_div_neg(op, n));
			}
		}
	} else {
		eval = 0;
	}
	return eval;
}


/*
    This routine constructs the expressions 'a * b' and 'a / b'.
*/

EXP
make_mult_exp(int op, EXP a, EXP b)
{
	TYPE ta, tb;
	unsigned ca, cb;

	/* Do reference conversions */
	a = convert_reference(a, REF_NORMAL);
	b = convert_reference(b, REF_NORMAL);

	/* Find operand types */
	ta = DEREF_type(exp_type(a));
	tb = DEREF_type(exp_type(b));
	ca = type_category(&ta);
	cb = type_category(&tb);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca) || IS_TYPE_OVERLOAD(cb)) {
		if (overload_depth == 0) {
			EXP e = binary_overload(op, a, b);
			return e;
		}
	}
#endif

	/* Do lvalue conversions */
	if (IS_TYPE_ADDRESS(ca)) {
		a = convert_lvalue(a);
		ta = DEREF_type(exp_type(a));
		ca = type_category(&ta);
	}
	if (IS_TYPE_ADDRESS(cb)) {
		b = convert_lvalue(b);
		tb = DEREF_type(exp_type(b));
		cb = type_category(&tb);
	}

	/* Operands can be arithmetic ... */
	if (IS_TYPE_ARITH(ca) && IS_TYPE_ARITH(cb)) {
		EXP e;
		unsigned tag;
		TYPE t = arith_type(ta, tb, a, b);
		a = convert_arith(t, a, op, 1);
		b = convert_arith(t, b, op, 2);

		/* Check for constant operands */
		if (op == lex_div) {
			tag = exp_div_tag;
			if (check_div_exp(op, a, b)) {
				e = make_binary_nat(tag, a, b);
				return e;
			}
		} else {
			if (op == lex_star) {
				tag = exp_mult_tag;
			} else if (op == lex_max) {
				tag = exp_max_tag;
			} else {
				tag = exp_min_tag;
			}
			if (IS_exp_int_lit(a) && IS_exp_int_lit(b)) {
				e = make_binary_nat(tag, a, b);
				return e;
			}
		}

		/* Construct the result */
		MAKE_exp_plus_etc(tag, t, a, b, e);
		return e;
	}

	/* ... and nothing else */
	if (!IS_TYPE_ERROR(ca) && !IS_TYPE_ERROR(cb)) {
		report(crt_loc, ERR_expr_mul_mul_op(op, ta, tb));
	}
	return make_error_exp(0);
}


/*
    This routine constructs the expression 'a % b'.
*/

EXP
make_rem_exp(EXP a, EXP b)
{
	TYPE ta, tb;
	unsigned ca, cb;

	/* Do reference conversions */
	a = convert_reference(a, REF_NORMAL);
	b = convert_reference(b, REF_NORMAL);

	/* Find operand types */
	ta = DEREF_type(exp_type(a));
	tb = DEREF_type(exp_type(b));
	ca = type_category(&ta);
	cb = type_category(&tb);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca) || IS_TYPE_OVERLOAD(cb)) {
		if (overload_depth == 0) {
			EXP e = binary_overload(lex_rem, a, b);
			return e;
		}
	}
#endif

	/* Do lvalue conversions */
	if (IS_TYPE_ADDRESS(ca)) {
		a = convert_lvalue(a);
		ta = DEREF_type(exp_type(a));
		ca = type_category(&ta);
	}
	if (IS_TYPE_ADDRESS(cb)) {
		b = convert_lvalue(b);
		tb = DEREF_type(exp_type(b));
		cb = type_category(&tb);
	}

	/* Operands can be integral ... */
	if (IS_TYPE_INT(ca) && IS_TYPE_INT(cb)) {
		EXP e;
		TYPE t = arith_type(ta, tb, a, b);
		a = convert_arith(t, a, lex_rem, 1);
		b = convert_arith(t, b, lex_rem, 2);

		/* Check for constant operands */
		if (check_div_exp(lex_rem, a, b)) {
			e = make_binary_nat(exp_rem_tag, a, b);
			return e;
		}

		/* Construct the result */
		MAKE_exp_rem(t, a, b, e);
		return e;
	}

	/* ... and nothing else */
	if (!IS_TYPE_ERROR(ca) && !IS_TYPE_ERROR(cb)) {
		report(crt_loc, ERR_expr_mul_rem_op(lex_rem, ta, tb));
	}
	return make_error_exp(0);
}


/*
    This routine constructs the expression 'a + b'.
*/

EXP
make_plus_exp(EXP a, EXP b)
{
	EXP e;
	TYPE t;
	OFFSET off;
	TYPE ta, tb;
	unsigned ca, cb;
	int op = lex_plus;
	ERROR err = NULL_err;
	TYPE sa = DEREF_type(exp_type(a));
	TYPE sb = DEREF_type(exp_type(b));

	/* Do reference conversions */
	a = convert_reference(a, REF_NORMAL);
	b = convert_reference(b, REF_NORMAL);

	/* Find operand types */
	ta = DEREF_type(exp_type(a));
	tb = DEREF_type(exp_type(b));
	ca = type_category(&ta);
	cb = type_category(&tb);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca) || IS_TYPE_OVERLOAD(cb)) {
		if (overload_depth == 0) {
			e = binary_overload(op, a, b);
			return e;
		}
	}
#endif

	/* Do lvalue conversions */
	if (IS_TYPE_ADDRESS(ca)) {
		a = convert_lvalue(a);
		ta = DEREF_type(exp_type(a));
		ca = type_category(&ta);
	}
	if (IS_TYPE_ADDRESS(cb)) {
		b = convert_lvalue(b);
		tb = DEREF_type(exp_type(b));
		cb = type_category(&tb);
	}

	/* Operands can be arithmetic ... */
	if (IS_TYPE_ARITH(ca) && IS_TYPE_ARITH(cb)) {
		t = arith_type(ta, tb, a, b);
		a = convert_arith(t, a, op, 1);
		b = convert_arith(t, b, op, 2);
		if (IS_exp_int_lit(a) && IS_exp_int_lit(b)) {
			e = make_binary_nat(exp_plus_tag, a, b);
		} else {
			MAKE_exp_plus(t, a, b, e);
		}
		return e;
	}

	/* Swap operands if the second is a pointer */
	if (IS_TYPE_PTR(cb)) {
		/* Alright because order of evaluation is undefined */
		EXP c = a;
		TYPE tc = ta;
		unsigned cc = ca;
		a = b;
		b = c;
		ta = tb;
		tb = tc;
		ca = cb;
		cb = cc;
		sa = sb;
	}

	/* The first operand should now be a pointer */
	if (!IS_TYPE_PTR(ca)) {
		if (!IS_TYPE_ERROR(ca) && !IS_TYPE_ERROR(cb)) {
			report(crt_loc, ERR_expr_add_op(op, ta, tb));
		}
		return make_error_exp(0);
	}

	/* The second operand should be integral */
	if (!IS_TYPE_INT(cb)) {
		if (!IS_TYPE_ERROR(cb)) {
			report(crt_loc, ERR_expr_add_op(op, ta, tb));
		}
		return make_paren_exp(a);
	}

	/* Do bounds checks */
	if (IS_exp_int_lit(b) && IS_type_array(sa)) {
		check_bounds(op, sa, b);
	}

	/* The pointer must be to a complete object type */
	t = check_pointer(ta, &err);
	if (!IS_NULL_err(err)) {
		err = concat_error(err, ERR_expr_add_incompl(op));
		report(crt_loc, err);
	}

	/* Construct the result */
	if (IS_TYPE_BITF(cb)) {
		b = convert_bitfield(b);
	}
	off = make_off_mult(t, b, 0);
	e = make_add_ptr(ta, a, off);
	return e;
}


/*
    This routine constructs the expression 'a - b'.
*/

EXP
make_minus_exp(EXP a, EXP b)
{
	EXP e;
	TYPE ta, tb;
	unsigned ca, cb;
	int op = lex_minus;
	TYPE sa = DEREF_type(exp_type(a));

	/* Do reference conversions */
	a = convert_reference(a, REF_NORMAL);
	b = convert_reference(b, REF_NORMAL);

	/* Find operand types */
	ta = DEREF_type(exp_type(a));
	tb = DEREF_type(exp_type(b));
	ca = type_category(&ta);
	cb = type_category(&tb);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca) || IS_TYPE_OVERLOAD(cb)) {
		if (overload_depth == 0) {
			e = binary_overload(op, a, b);
			return e;
		}
	}
#endif

	/* Do lvalue conversions */
	if (IS_TYPE_ADDRESS(ca)) {
		a = convert_lvalue(a);
		ta = DEREF_type(exp_type(a));
		ca = type_category(&ta);
	}
	if (IS_TYPE_ADDRESS(cb)) {
		b = convert_lvalue(b);
		tb = DEREF_type(exp_type(b));
		cb = type_category(&tb);
	}

	/* Operands can be arithmetic ... */
	if (IS_TYPE_ARITH(ca) && IS_TYPE_ARITH(cb)) {
		TYPE t = arith_type(ta, tb, a, b);
		a = convert_arith(t, a, op, 1);
		b = convert_arith(t, b, op, 2);
		if (IS_exp_int_lit(a) && IS_exp_int_lit(b)) {
			e = make_binary_nat(exp_minus_tag, a, b);
		} else {
			MAKE_exp_minus(t, a, b, e);
		}
		return e;
	}

	/* ... or a pointer and an integer ... */
	if (IS_TYPE_PTR(ca) && IS_TYPE_INT(cb)) {
		TYPE t;
		OFFSET off;
		ERROR err = NULL_err;

		/* Do bounds checks */
		if (IS_exp_int_lit(b) && IS_type_array(sa)) {
			check_bounds(op, sa, b);
		}

		/* The pointer must be to a complete object type */
		t = check_pointer(ta, &err);
		if (!IS_NULL_err(err)) {
			err = concat_error(err, ERR_expr_add_incompl(op));
			report(crt_loc, err);
		}

		/* Construct the result */
		if (IS_TYPE_BITF(cb)) {
			b = convert_bitfield(b);
		}
		off = make_off_mult(t, b, 1);
		e = make_add_ptr(ta, a, off);
		return e;
	}

	/* ... or both pointers ... */
	if (IS_TYPE_PTR(ca) && IS_TYPE_PTR(cb)) {
		OFFSET off;
		int suspect = 0;
		ERROR err = NULL_err;
		TYPE tc = ptr_common_type(ta, tb, 0, &suspect);
		if (suspect > 0) {
			/* Should have pointers to compatible types */
			err = ERR_basic_link_incompat(ta, tb);
			err = concat_error(err, ERR_expr_add_ptrdiff());
			report(crt_loc, err);
			err = NULL_err;
		}
		IGNORE check_pointer(ta, &err);
		if (!IS_NULL_err(err)) {
			/* Can't have pointer to incomplete type */
			err = concat_error(err, ERR_expr_add_incompl(op));
			report(crt_loc, err);
			err = NULL_err;
		}
		IGNORE check_pointer(tb, &err);
		if (!IS_NULL_err(err)) {
			/* Can't have pointer to incomplete type */
			if (eq_type_unqual(ta, tb)) {
				destroy_error(err, 1);
			} else {
				err = concat_error(err,
						   ERR_expr_add_incompl(op));
				report(crt_loc, err);
			}
		}

		/* Construct the result */
		if (suspect == -1) {
			MAKE_exp_op(type_ptrdiff_t, op, a, b, e);
		} else {
			TYPE pc = DEREF_type(type_ptr_sub(tc));
			if (option(OPT_ptr_operator)) {
				EXP ra = NULL_exp;
				EXP rb = NULL_exp;
				IGNORE find_exp_linkage(a, &ra, 1);
				IGNORE find_exp_linkage(b, &rb, 1);
				if (!IS_NULL_exp(ra) && !IS_NULL_exp(rb)) {
					if (IS_exp_string_lit(ra) ||
					    !eq_exp(ra, rb, 0)) {
						report(crt_loc, ERR_expr_add_different());
					}
				}
			}
			a = convert_ptr_common(tc, a, op, 1);
			b = convert_ptr_common(tc, b, op, 2);
			if (IS_type_top_etc(pc)) {
				/* Map 'void *' to 'char *' */
				unsigned conv = (CONV_PTR_VOID | CONV_REVERSE);
				tc = type_char_star;
				pc = type_char;
				MAKE_exp_cast(tc, conv, a, a);
				MAKE_exp_cast(tc, conv, b, b);
			}
			MAKE_off_ptr_diff(a, b, off);
			MAKE_exp_offset_size(type_ptrdiff_t, off, pc, 0, e);
		}
		return e;
	}

	/* ... and nothing else */
	if (!IS_TYPE_ERROR(ca) && !IS_TYPE_ERROR(cb)) {
		report(crt_loc, ERR_expr_add_op(op, ta, tb));
	}
	return make_error_exp(0);
}


/*
    This routine checks the shift operation 'a << b' or 'a >> b' for
    dubious constant operands.  All the necessary operand and arithmetic
    type conversions have already been performed on a and b, and the type
    of a is passed in as t.  The routine returns 1 if both operands are
    integer constants.
*/

int
check_shift_exp(int op, TYPE t, EXP a, EXP b)
{
	int ret = 1;
	ERROR err = NULL_err;

	/* Check first operand */
	if (IS_exp_int_lit(a)) {
		NAT n = DEREF_nat(exp_int_lit_nat(a));
		if (is_negative_nat(n)) {
			err = ERR_expr_shift_op1_neg(op, n);
		}
	} else {
		if (check_int_type(t, btype_signed)) {
			err = ERR_expr_shift_op1_sign(op);
		}
		ret = 0;
	}

	/* Check second operand */
	if (IS_exp_int_lit(b)) {
		NAT n = DEREF_nat(exp_int_lit_nat(b));
		if (is_negative_nat(n)) {
			err = concat_error(err, ERR_expr_shift_op2_neg(op, n));
		} else if (check_type_size(t, n) >= 0) {
			err = concat_error(err,
					   ERR_expr_shift_op2_big(op, n, t));
		}
	} else {
		ret = 0;
	}

	/* Report any accumulated errors */
	if (!IS_NULL_err(err)) {
		report(crt_loc, err);
	}
	return ret;
}


/*
    This routine constructs the expressions 'a << b' and 'a >> b'.  Note
    that this has a lower priority than plus and minus.
*/

EXP
make_shift_exp(int op, EXP a, EXP b)
{
	EXP e;
	TYPE ta, tb;
	unsigned ca, cb;

	/* Check for non-obvious resolutions */
	if (option(OPT_paren)) {
		check_paren(PAREN_PLUS, op, a, b);
	}

	/* Do reference conversions */
	a = convert_reference(a, REF_NORMAL);
	b = convert_reference(b, REF_NORMAL);

	/* Find operand types */
	ta = DEREF_type(exp_type(a));
	tb = DEREF_type(exp_type(b));
	ca = type_category(&ta);
	cb = type_category(&tb);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca) || IS_TYPE_OVERLOAD(cb)) {
		if (overload_depth == 0) {
			e = binary_overload(op, a, b);
			return e;
		}
	}
#endif

	/* Do lvalue conversions */
	if (IS_TYPE_ADDRESS(ca)) {
		a = convert_lvalue(a);
		ta = DEREF_type(exp_type(a));
		ca = type_category(&ta);
	}
	if (IS_TYPE_ADDRESS(cb)) {
		b = convert_lvalue(b);
		tb = DEREF_type(exp_type(b));
		cb = type_category(&tb);
	}

	/* Operands can be integral ... */
	if (IS_TYPE_INT(ca) && IS_TYPE_INT(cb)) {
		unsigned tag;
		ERROR err = NULL_err;
		TYPE pta = promote_type(ta);
		TYPE ptb = promote_type(tb);
		a = convert_promote(pta, a);
		b = convert_promote(ptb, b);
		tag = (op == lex_lshift ? exp_lshift_tag : exp_rshift_tag);

		/* Check for dubious shifts */
		if (check_shift_exp(op, pta, a, b)) {
			/* Allow for constant evaluation */
			if (!IS_NULL_err(err)) {
				report(crt_loc, err);
			}
			e = make_binary_nat(tag, a, b);
			return e;
		}

		/* Construct the result */
		MAKE_exp_plus_etc(tag, pta, a, b, e);
		return e;
	}

	/* ... and nothing else */
	if (!IS_TYPE_ERROR(ca) && !IS_TYPE_ERROR(cb)) {
		report(crt_loc, ERR_expr_shift_op(op, ta, tb));
	}
	return make_error_exp(0);
}


/*
    This routine converts the lexical token op to a relational operator.
*/

static NTEST
make_ntest(int op)
{
	switch (op) {
	case lex_eq:
		return ntest_eq;
	case lex_not_Heq_H1:
		return ntest_not_eq;
	case lex_less:
		return ntest_less;
	case lex_less_Heq:
		return ntest_less_eq;
	case lex_greater:
		return ntest_greater;
	case lex_greater_Heq:
		return ntest_greater_eq;
	}
	return ntest_none;
}


/*
    This routine constructs the expressions 'a < b', 'a > b', 'a <= b' and
    'a >= b'.
*/

EXP
make_relation_exp(int op, EXP a, EXP b)
{
	EXP e;
	NTEST tst;
	TYPE ta, tb;
	unsigned ca, cb;

	/* Check for dubious relations */
	if (option(OPT_paren)) {
		check_relation(op, a, b);
	}

	/* Do reference conversions */
	a = convert_reference(a, REF_NORMAL);
	b = convert_reference(b, REF_NORMAL);

	/* Find operand types */
	ta = DEREF_type(exp_type(a));
	tb = DEREF_type(exp_type(b));
	ca = type_category(&ta);
	cb = type_category(&tb);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca) || IS_TYPE_OVERLOAD(cb)) {
		if (overload_depth == 0) {
			e = binary_overload(op, a, b);
			return e;
		}
	}
#endif

	/* Do lvalue conversions */
	if (IS_TYPE_ADDRESS(ca)) {
		a = convert_lvalue(a);
		ta = DEREF_type(exp_type(a));
		ca = type_category(&ta);
	}
	if (IS_TYPE_ADDRESS(cb)) {
		b = convert_lvalue(b);
		tb = DEREF_type(exp_type(b));
		cb = type_category(&tb);
	}

	/* Operands can both be arithmetic ... */
	if (IS_TYPE_ARITH(ca) && IS_TYPE_ARITH(cb)) {
		TYPE t = arith_type(ta, tb, a, b);
		a = convert_arith(t, a, op, 1);
		b = convert_arith(t, b, op, 2);

		if (IS_exp_int_lit(a)) {
			/* Allow for constant evaluation */
			if (IS_exp_int_lit(b)) {
				tst = make_ntest(op);
				e = make_compare_nat(tst, a, b);
				return e;
			}

			/* Check for unsigned comparisons against zero */
			if (is_zero_exp(a) &&
			    check_int_type(t, btype_unsigned)) {
				if (op == lex_greater) {
					report(crt_loc, ERR_expr_rel_false());
				} else if (op == lex_less_Heq) {
					report(crt_loc, ERR_expr_rel_true());
				}
			}
		}

		/* Check for unsigned comparisons against zero */
		if (IS_exp_int_lit(b)) {
			if (is_zero_exp(b) &&
			    check_int_type(t, btype_unsigned)) {
				if (op == lex_less) {
					report(crt_loc, ERR_expr_rel_false());
				} else if (op == lex_greater_Heq) {
					report(crt_loc, ERR_expr_rel_true());
				}
			}
		}

		/* Construct the result */
		tst = make_ntest(op);
		MAKE_exp_compare(type_bool, tst, a, b, e);
		return e;
	}

	/* ... or both pointers ... */
	if (IS_TYPE_PTR(ca)) {
		if (IS_TYPE_PTR(cb)) {
			int suspect = 0;
			TYPE t = ptr_common_type(ta, tb, 1, &suspect);
			if (suspect == -1) {
				/* Allow for template types */
				MAKE_exp_op(type_bool, op, a, b, e);
				return e;
			}
			if (suspect == 2) {
				/* Can't bring to a common type */
				ERROR err = ERR_basic_link_incompat(ta, tb);
				err = concat_error(err, ERR_conv_ptr_common());
				err = concat_error(err, ERR_expr_rel_ptr(op));
				report(crt_loc, err);
			} else if (suspect == 1) {
				/* These comparisons are suspect */
				report(crt_loc,
				       ERR_expr_rel_ptr_void(op, ta, tb));
			}
			a = convert_ptr_common(t, a, op, 1);
			b = convert_ptr_common(t, b, op, 2);
			tst = make_ntest(op);
			MAKE_exp_compare(type_bool, tst, a, b, e);
			return e;
		}
		if (IS_TYPE_INT(cb)) {
			/* Allow zero integer as a null pointer */
			b = make_null_ptr(b, ta);
			if (IS_NULL_exp(b)) {
				report(crt_loc,
				       ERR_expr_rel_nonzero(op, ta, tb));
				b = make_null_ptr(NULL_exp, ta);
			} else {
				report(crt_loc, ERR_expr_rel_null(op));
			}
			tst = make_ntest(op);
			MAKE_exp_compare(type_bool, tst, a, b, e);
			return e;
		}
	} else if (IS_TYPE_PTR(cb)) {
		if (IS_TYPE_INT(ca)) {
			/* Allow zero integer as a null pointer */
			a = make_null_ptr(a, tb);
			if (IS_NULL_exp(a)) {
				report(crt_loc,
				       ERR_expr_rel_nonzero(op, tb, ta));
				a = make_null_ptr(NULL_exp, tb);
			} else {
				report(crt_loc, ERR_expr_rel_null(op));
			}
			tst = make_ntest(op);
			MAKE_exp_compare(type_bool, tst, a, b, e);
			return e;
		}
	}

	/* ... and nothing else */
	if (!IS_TYPE_ERROR(ca) && !IS_TYPE_ERROR(cb)) {
		report(crt_loc, ERR_expr_rel_op(op, ta, tb));
	}
	tst = make_ntest(op);
	MAKE_exp_test(type_bool, tst, b, e);
	return e;
}


/*
    This routine constructs the expressions 'a == b' and 'a != b'.
*/

EXP
make_equality_exp(int op, EXP a, EXP b)
{
	EXP e;
	NTEST tst;
	TYPE ta, tb;
	unsigned ca, cb;

	/* Check for dubious relations */
	if (option(OPT_paren)) {
		check_relation(op, a, b);
	}

	/* Do reference conversions */
	a = convert_reference(a, REF_NORMAL);
	b = convert_reference(b, REF_NORMAL);

	/* Find operand types */
	ta = DEREF_type(exp_type(a));
	tb = DEREF_type(exp_type(b));
	ca = type_category(&ta);
	cb = type_category(&tb);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca) || IS_TYPE_OVERLOAD(cb)) {
		if (overload_depth == 0) {
			e = binary_overload(op, a, b);
			return e;
		}
	}
#endif

	/* Do lvalue conversions */
	if (IS_TYPE_ADDRESS(ca)) {
		a = convert_lvalue(a);
		ta = DEREF_type(exp_type(a));
		ca = type_category(&ta);
	}
	if (IS_TYPE_ADDRESS(cb)) {
		b = convert_lvalue(b);
		tb = DEREF_type(exp_type(b));
		cb = type_category(&tb);
	}

	/* Operands can both be arithmetic ... */
	if (IS_TYPE_ARITH(ca) && IS_TYPE_ARITH(cb)) {
		TYPE t = arith_type(ta, tb, a, b);
		if (IS_type_floating(t)) {
			report(crt_loc, ERR_expr_eq_float(op));
		}
		a = convert_arith(t, a, op, 1);
		b = convert_arith(t, b, op, 2);
		tst = make_ntest(op);
		if (IS_exp_int_lit(a) && IS_exp_int_lit(b)) {
			e = make_compare_nat(tst, a, b);
		} else {
			MAKE_exp_compare(type_bool, tst, a, b, e);
		}
		return e;
	}

	/* ... or both pointers ... */
	if (IS_TYPE_PTR(ca)) {
		if (IS_TYPE_PTR(cb)) {
			int suspect = 0;
			TYPE t = ptr_common_type(ta, tb, 1, &suspect);
			if (suspect == -1) {
				/* Allow for template types */
				MAKE_exp_op(type_bool, op, a, b, e);
				return e;
			}
			if (suspect == 2) {
				ERROR err = ERR_basic_link_incompat(ta, tb);
				err = concat_error(err, ERR_conv_ptr_common());
				err = concat_error(err, ERR_expr_eq_ptr(op));
				report(crt_loc, err);
			}
			a = convert_ptr_common(t, a, op, 1);
			b = convert_ptr_common(t, b, op, 2);
			if (IS_exp_null(a)) {
				/* Make null pointer the second argument */
				EXP c = a;
				a = b;
				b = c;
			}
			tst = make_ntest(op);
			MAKE_exp_compare(type_bool, tst, a, b, e);
			return e;
		}
		if (IS_TYPE_INT(cb)) {
			/* Allow zero integer as a null pointer */
			b = make_null_ptr(b, ta);
			if (IS_NULL_exp(b)) {
				report(crt_loc,
				       ERR_expr_eq_nonzero(op, ta, tb));
				b = make_null_ptr(NULL_exp, ta);
			}
			tst = make_ntest(op);
			MAKE_exp_compare(type_bool, tst, a, b, e);
			return e;
		}
	} else if (IS_TYPE_PTR(cb)) {
		if (IS_TYPE_INT(ca)) {
			/* Allow zero integer as a null pointer */
			a = make_null_ptr(a, tb);
			if (IS_NULL_exp(a)) {
				report(crt_loc,
				       ERR_expr_eq_nonzero(op, tb, ta));
				a = make_null_ptr(NULL_exp, tb);
			}
			tst = make_ntest(op);
			MAKE_exp_compare(type_bool, tst, b, a, e);
			return e;
		}
	}

#if LANGUAGE_CPP
	/* ... or both pointers to members ... */
	if (IS_TYPE_PTR_MEM(ca)) {
		if (IS_TYPE_PTR_MEM(cb)) {
			int suspect = 0;
			TYPE t = ptr_mem_common_type(ta, tb, &suspect);
			if (suspect == -1) {
				/* Allow for template types */
				MAKE_exp_op(type_bool, op, a, b, e);
				return e;
			}
			if (suspect == 2) {
				ERROR err = ERR_basic_link_incompat(ta, tb);
				err = concat_error(err, ERR_conv_mem_common());
				err = concat_error(err, ERR_expr_eq_mptr(op));
				report(crt_loc, err);
			} else {
				a = convert_ptr_mem_common(t, a, op, 1);
				b = convert_ptr_mem_common(t, b, op, 2);
			}
			if (IS_exp_null(a)) {
				/* Make null pointer the second argument */
				EXP c = a;
				a = b;
				b = c;
			}
			tst = make_ntest(op);
			MAKE_exp_compare(type_bool, tst, a, b, e);
			return e;
		}
		if (IS_TYPE_INT(cb)) {
			/* Allow zero integer as a null pointer member */
			b = make_null_ptr(b, ta);
			if (IS_NULL_exp(b)) {
				report(crt_loc,
				       ERR_expr_eq_nonzero(op, ta, tb));
				b = make_null_ptr(NULL_exp, ta);
			}
			tst = make_ntest(op);
			MAKE_exp_compare(type_bool, tst, a, b, e);
			return e;
		}
	} else if (IS_TYPE_PTR_MEM(cb)) {
		if (IS_TYPE_INT(ca)) {
			/* Allow zero integer as a null pointer member */
			a = make_null_ptr(a, tb);
			if (IS_NULL_exp(a)) {
				report(crt_loc,
				       ERR_expr_eq_nonzero(op, tb, ta));
				a = make_null_ptr(NULL_exp, tb);
			}
			tst = make_ntest(op);
			MAKE_exp_compare(type_bool, tst, b, a, e);
			return e;
		}
	}
#endif

	/* ... and nothing else */
	if (!IS_TYPE_ERROR(ca) && !IS_TYPE_ERROR(cb)) {
		report(crt_loc, ERR_expr_eq_op(op, ta, tb));
	}
	tst = make_ntest(op);
	MAKE_exp_compare(type_bool, tst, a, b, e);
	return e;
}


/*
    This routine constructs the expressions 'a & b', 'a ^ b' and 'a | b'.
*/

static EXP
make_bit_exp(int op, unsigned tag, EXP a, EXP b)
{
	EXP e;
	TYPE ta, tb;
	unsigned ca, cb;

	/* Do reference conversions */
	a = convert_reference(a, REF_NORMAL);
	b = convert_reference(b, REF_NORMAL);

	/* Find operand types */
	ta = DEREF_type(exp_type(a));
	tb = DEREF_type(exp_type(b));
	ca = type_category(&ta);
	cb = type_category(&tb);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca) || IS_TYPE_OVERLOAD(cb)) {
		if (overload_depth == 0) {
			e = binary_overload(op, a, b);
			return e;
		}
	}
#endif

	/* Do lvalue conversions */
	if (IS_TYPE_ADDRESS(ca)) {
		a = convert_lvalue(a);
		ta = DEREF_type(exp_type(a));
		ca = type_category(&ta);
	}
	if (IS_TYPE_ADDRESS(cb)) {
		b = convert_lvalue(b);
		tb = DEREF_type(exp_type(b));
		cb = type_category(&tb);
	}

	/* Operands can both be integral ... */
	if (IS_TYPE_INT(ca) && IS_TYPE_INT(cb)) {
		TYPE t = arith_type(ta, tb, a, b);
		a = convert_arith(t, a, op, 1);
		b = convert_arith(t, b, op, 2);
		if (IS_exp_int_lit(a) && IS_exp_int_lit(b)) {
			e = make_binary_nat(tag, a, b);
		} else {
			MAKE_exp_plus_etc(tag, t, a, b, e);
		}
		return e;
	}

	/* ... and nothing else */
	if (!IS_TYPE_ERROR(ca) && !IS_TYPE_ERROR(cb)) {
		switch (tag) {
		case exp_and_tag: {
			report(crt_loc, ERR_expr_bit_and_op(op, ta, tb));
			break;
		}
		case exp_or_tag: {
			report(crt_loc, ERR_expr_or_op(op, ta, tb));
			break;
		}
		case exp_xor_tag: {
			report(crt_loc, ERR_expr_xor_op(op, ta, tb));
			break;
		}
		}
	}
	return make_error_exp(0);
}


/*
    This routine constructs the expression 'a & b'.  Note that this
    has lower priority than plus or minus and the equality operators.
*/

EXP
make_and_exp(EXP a, EXP b)
{
	EXP e;
	int op = lex_and_H1;
	if (option(OPT_paren)) {
		check_paren(PAREN_EQUALITY, op, a, b);
	}
	e = make_bit_exp(op, exp_and_tag, a, b);
	return e;
}


/*
    This routine constructs the expression 'a ^ b'.  Note that this has
    a lower priority than bitwise and, plus and minus.
*/

EXP
make_xor_exp(EXP a, EXP b)
{
	EXP e;
	int op = lex_xor_H1;
	if (option(OPT_paren)) {
		check_paren(PAREN_AND, op, a, b);
	}
	e = make_bit_exp(op, exp_xor_tag, a, b);
	return e;
}


/*
    This routine constructs the expression 'a | b'.  Note that this has
    a lower priority than bitwise and, bitwise xor, plus and minus.
*/

EXP
make_or_exp(EXP a, EXP b)
{
	EXP e;
	int op = lex_or_H1;
	if (option(OPT_paren)) {
		check_paren(PAREN_XOR, op, a, b);
	}
	e = make_bit_exp(op, exp_or_tag, a, b);
	return e;
}


/*
    This routine constructs the expressions 'a && b' and 'a || b'.
*/

static EXP
make_logic_exp(int op, unsigned tag, EXP a, EXP b)
{
	EXP e;
	TYPE ta, tb;
	unsigned ca, cb;
	ERROR err = NULL_err;
	unsigned taga = TAG_exp(a);
	unsigned tagb = TAG_exp(b);

	/* Do reference conversions */
	a = convert_reference(a, REF_NORMAL);
	b = convert_reference(b, REF_NORMAL);

	/* Find operand types */
	ta = DEREF_type(exp_type(a));
	tb = DEREF_type(exp_type(b));
	ca = type_category(&ta);
	cb = type_category(&tb);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca) || IS_TYPE_OVERLOAD(cb)) {
		if (overload_depth == 0) {
			e = binary_overload(op, a, b);
			return e;
		}
	}
#endif

	/* Do lvalue conversions */
	if (IS_TYPE_ADDRESS(ca)) {
		a = convert_lvalue(a);
	}
	if (IS_TYPE_ADDRESS(cb)) {
		b = convert_lvalue(b);
	}

	/* Convert first operand to a boolean */
	a = convert_boolean(a, taga, &err);
	if (!IS_NULL_err(err)) {
		ERROR err2;
		if (tag == exp_log_and_tag) {
			err2 = ERR_expr_log_and_op(op);
		} else {
			err2 = ERR_expr_log_or_op(op);
		}
		err = concat_error(err, err2);
		report(crt_loc, err);
		err = NULL_err;
	}

	/* Convert second operand to a boolean */
	b = convert_boolean(b, tagb, &err);
	if (!IS_NULL_err(err)) {
		ERROR err2;
		if (tag == exp_log_and_tag) {
			err2 = ERR_expr_log_and_op(op);
		} else {
			err2 = ERR_expr_log_or_op(op);
		}
		err = concat_error(err, err2);
		report(crt_loc, err);
	}

	/* Construct the result */
	if (IS_exp_int_lit(a) && IS_exp_int_lit(b)) {
		e = make_binary_nat(tag, a, b);
	} else {
		MAKE_exp_plus_etc(tag, type_bool, a, b, e);
	}
	return e;
}


/*
    This routine constructs the expression 'a && b'.
*/

EXP
make_log_and_exp(EXP a, EXP b)
{
	EXP e;
	e = make_logic_exp(lex_logical_Hand_H1, exp_log_and_tag, a, b);
	return e;
}


/*
    This routine constructs the expression 'a || b'.  Note that this
    has a lower priority than logical and.
*/

EXP
make_log_or_exp(EXP a, EXP b)
{
	EXP e;
	if (option(OPT_paren)) {
		check_logic(a, b);
	}
	e = make_logic_exp(lex_logical_Hor_H1, exp_log_or_tag, a, b);
	return e;
}


/*
    This routine constructs the expression 'a ? b : c' where one of b
    and c depends on a template parameter.
*/

#if LANGUAGE_CPP

static EXP
make_templ_cond(EXP a, EXP b, EXP c)
{
	EXP e;
	TYPE t = type_templ_param;
	LIST(EXP)p = NULL_list(EXP);
	CONS_exp(c, p, p);
	CONS_exp(b, p, p);
	CONS_exp(a, p, p);
	MAKE_exp_opn(t, lex_cond_Hop, p, e);
	return e;
}

#endif


/*
    This routine is used to turn the throw expression a into an expression
    of type t.  This is required so that a conditional involving a throw
    expression satisfies the shape requirements of a TDF conditional
    construct.
*/

static EXP
make_except_value(TYPE t, EXP a)
{
	if (!IS_type_top_etc(t)) {
		EXP b;
		MAKE_exp_value(t, b);
		a = join_exp(a, b);
	}
	return a;
}


/*
    This routine constructs the expression 'a ? b : c'.  Although '?:'
    cannot be overloaded, user-defined conversions which bring the second
    and third operands to a common type are considered.  This is done
    using a dummy binary operation 'b : c' given by 'NULL_exp ? b : c'.
*/

EXP
make_cond_exp(EXP a, EXP b, EXP c)
{
	EXP e;
	TYPE t;
	TYPE tb, tc;
	unsigned cb, cc;
	int op = lex_cond_Hop;

	/* First operand is converted to a boolean */
	if (!IS_NULL_exp(a)) {
		unsigned cr = crt_condition;
		a = check_cond(a, &e, op);
		crt_condition = cr;
	}

	/* Do reference conversion on second and third operands */
	b = convert_reference(b, REF_NORMAL);
	c = convert_reference(c, REF_NORMAL);

	/* Find operand types */
	tb = DEREF_type(exp_type(b));
	cb = type_category(&tb);
	tc = DEREF_type(exp_type(c));
	cc = type_category(&tc);

	/* Check for template parameters */
#if LANGUAGE_CPP
	if (IS_TYPE_TEMPL(cb) || IS_TYPE_TEMPL(cc)) {
		e = make_templ_cond(a, b, c);
		return e;
	}
#endif

	/* Check for throw expressions */
	if (IS_exp_exception(b)) {
		c = convert_lvalue(c);
		t = DEREF_type(exp_type(c));
		b = make_except_value(t, b);
		goto return_lab;
	}
	if (IS_exp_exception(c)) {
		b = convert_lvalue(b);
		t = DEREF_type(exp_type(b));
		c = make_except_value(t, c);
		goto return_lab;
	}

	/* Allow for overload resolution */
#if LANGUAGE_CPP
	if (IS_TYPE_CLASS(cb) || IS_TYPE_CLASS(cc)) {
		if (overload_depth == 0) {
			e = binary_overload(lex_colon, b, c);
			if (!IS_NULL_exp(e)) {
				/* Fill in condition */
				if (IS_exp_if_stmt(e)) {
					COPY_exp(exp_if_stmt_cond(e), a);
				} else if (IS_exp_opn(e)) {
					LIST(EXP) p =
					    DEREF_list(exp_opn_args(e));
					COPY_exp(HEAD_list(p), a);
				}
			}
			return e;
		}
	}
#endif

	/* Check operands */
	b = convert_none(b);
	c = convert_none(c);

	/* Can have lvalues of the same type ... */
	if (IS_TYPE_LVALUE(cb)) {
		if (cb == cc && !option(OPT_cond_lvalue)) {
			/* Operands are lvalues of the same category */
			if (eq_type_unqual(tb, tc)) {
				CV_SPEC qb = find_cv_qual(tb);
				CV_SPEC qc = find_cv_qual(tc);
				t = tb;
				if (qb != qc) {
					/* Adjust qualifiers */
					report(crt_loc,
					       ERR_expr_cond_qual(tb, tc));
					t = qualify_type(t,(qb | qc), 0);
				}
				goto return_lab;
			}
		}
	}

	/* ...otherwise do lvalue conversion ... */
	if (IS_TYPE_ADDRESS(cb)) {
		b = convert_lvalue(b);
		tb = DEREF_type(exp_type(b));
		cb = type_category(&tb);
	}
	if (IS_TYPE_ADDRESS(cc)) {
		c = convert_lvalue(c);
		tc = DEREF_type(exp_type(c));
		cc = type_category(&tc);
	}

	/* ... can have rvalues of the same type ... */
	if (cb == cc) {
#if LANGUAGE_C
		if (IS_TYPE_SCALAR(cb)) {
			/* Normal arithmetic conversions are applied in C */
			/* EMPTY */
		} else /* continues ... */
#endif
			if (eq_type_unqual(tb, tc)) {
				CV_SPEC qb = find_cv_qual(tb);
				CV_SPEC qc = find_cv_qual(tc);
				t = tb;
				if (qb != qc) {
					/* Adjust qualifiers */
					report(crt_loc,
					       ERR_expr_cond_qual(tb, tc));
					t = qualify_type(t,(qb | qc), 0);
				}
				if (IS_exp_int_lit(b) && IS_exp_int_lit(c)) {
					if (!IS_NULL_exp(a) &&
					    IS_exp_int_lit(a)) {
						/* Allow for integral constants */
						e = make_cond_nat(a, b, c);
						return e;
					}
				}
				goto return_lab;
			}
		if (IS_TYPE_VOID(cb)) {
			/* ... or 'void' and 'bottom' ... */
			t = type_void;
			goto return_lab;
		}
	}

	/* ... or both operands can be arithmetic ... */
	if (IS_TYPE_ARITH(cb) && IS_TYPE_ARITH(cc)) {
		t = arith_type(tb, tc, b, c);
		b = convert_arith(t, b, op, 2);
		c = convert_arith(t, c, op, 3);
		if (IS_exp_int_lit(b) && IS_exp_int_lit(c)) {
			if (!IS_NULL_exp(a) && IS_exp_int_lit(a)) {
				/* Allow for integral constants */
				e = make_cond_nat(a, b, c);
				return e;
			}
		}
		goto return_lab;
	}

	/* ... or both pointers ... */
	if (IS_TYPE_PTR(cb)) {
		if (IS_TYPE_PTR(cc)) {
			int suspect = 0;
			t = ptr_common_type(tb, tc, 1, &suspect);
#if LANGUAGE_CPP
			if (suspect == -1) {
				/* Allow for template types */
				e = make_templ_cond(a, b, c);
				return e;
			}
#endif
			if (suspect == 2) {
				ERROR err = ERR_basic_link_incompat(tb, tc);
				err = concat_error(err, ERR_conv_ptr_common());
				err = concat_error(err, ERR_expr_cond_ptr());
				report(crt_loc, err);
			}
			b = convert_ptr_common(t, b, op, 2);
			c = convert_ptr_common(t, c, op, 3);
			goto return_lab;
		}
		if (IS_TYPE_INT(cc)) {
			/* Allow zero integer as a null pointer */
			t = tb;
			c = make_null_ptr(c, t);
			if (IS_NULL_exp(c)) {
				report(crt_loc, ERR_expr_cond_nonzero(tb, tc));
				c = make_null_ptr(NULL_exp, t);
			}
			goto return_lab;
		}
	} else if (IS_TYPE_PTR(cc)) {
		if (IS_TYPE_INT(cb)) {
			/* Allow zero integer as a null pointer */
			t = tc;
			b = make_null_ptr(b, t);
			if (IS_NULL_exp(b)) {
				report(crt_loc, ERR_expr_cond_nonzero(tc, tb));
				b = make_null_ptr(NULL_exp, t);
			}
			goto return_lab;
		}
	}

#if LANGUAGE_CPP
	/* ... or both pointers to members ... */
	if (IS_TYPE_PTR_MEM(cb)) {
		if (IS_TYPE_PTR_MEM(cc)) {
			int suspect = 0;
			t = ptr_mem_common_type(tb, tc, &suspect);
			if (suspect == -1) {
				/* Allow for template types */
				e = make_templ_cond(a, b, c);
				return e;
			}
			if (suspect == 2 || suspect == 1) {
				ERROR err = ERR_basic_link_incompat(tb, tc);
				err = concat_error(err, ERR_conv_mem_common());
				err = concat_error(err, ERR_expr_cond_mptr());
				report(crt_loc, err);
			} else {
				b = convert_ptr_mem_common(t, b, op, 2);
				c = convert_ptr_mem_common(t, c, op, 3);
			}
			goto return_lab;
		}
		if (IS_TYPE_INT(cc)) {
			/* Allow zero integer as a null pointer member */
			t = tb;
			c = make_null_ptr(c, t);
			if (IS_NULL_exp(c)) {
				report(crt_loc, ERR_expr_cond_nonzero(tb, tc));
				c = make_null_ptr(NULL_exp, t);
			}
			goto return_lab;
		}
	} else if (IS_TYPE_PTR_MEM(cc)) {
		if (IS_TYPE_INT(cb)) {
			/* Allow zero integer as a null pointer member */
			t = tc;
			b = make_null_ptr(b, t);
			if (IS_NULL_exp(b)) {
				report(crt_loc, ERR_expr_cond_nonzero(tc, tb));
				b = make_null_ptr(NULL_exp, t);
			}
			goto return_lab;
		}
	}
#endif

	/* ... and nothing else */
	if (!IS_TYPE_ERROR(cb) && !IS_TYPE_ERROR(cc)) {
		report(crt_loc, ERR_expr_cond_op(tb, tc));
	}
	if (IS_TYPE_VOID(cb)) {
		c = make_discard_exp(c);
		t = tb;
		goto return_lab;
	}
	if (IS_TYPE_VOID(cc)) {
		b = make_discard_exp(b);
		t = tc;
		goto return_lab;
	}
	e = make_error_exp(0);
	return e;

	/* Construct the result */
return_lab:
	MAKE_exp_if_stmt(t, a, b, c, NULL_id, e);
	return e;
}


/*
    This routine joins the expressions a and b by forming a comma
    expression, 'a, b'.
*/

EXP
join_exp(EXP a, EXP b)
{
	EXP e;
	TYPE t;
	LIST(EXP)p;
	if (IS_NULL_exp(a)) {
		return b;
	}
	if (IS_NULL_exp(b)) {
		return a;
	}
	CONS_exp(b, NULL_list(EXP), p);
	CONS_exp(a, p, p);
	t = DEREF_type(exp_type(b));
	MAKE_exp_comma(t, p, e);
	return e;
}


/*
    This routine constructs the simple comma expression 'a, b'.  If started
    is true and a is itself a comma expression then b is added to the end
    of a.  Otherwise a new comma expression is created.  Note that discard
    analysis is applied to a, and unreached code analysis to b.
*/

static EXP
make_comma_simple(EXP a, EXP b, int started)
{
	EXP e;
	int uc;
	TYPE ta, tb;
#if LANGUAGE_CPP
	unsigned ca, cb;
#endif

	/* Do reference conversions */
	a = convert_reference(a, REF_NORMAL);
	b = convert_reference(b, REF_NORMAL);

	/* Find operand types */
#if LANGUAGE_CPP
	ta = DEREF_type(exp_type(a));
	tb = DEREF_type(exp_type(b));
	ca = type_category(&ta);
	cb = type_category(&tb);

	/* Check for overloading */
	if (IS_TYPE_OVERLOAD(ca) || IS_TYPE_OVERLOAD(cb)) {
		if (overload_depth == 0) {
			e = binary_overload(lex_comma, a, b);
			if (!IS_NULL_exp(e)) {
				return e;
			}
		}
		/* Continue if not overloaded */
	}
#endif

	/* Do discard analysis on first operand */
	uc = unreached_code;
	a = make_exp_stmt(a);
	ta = DEREF_type(exp_type(a));
	if (IS_type_bottom(ta)) {
		if (!unreached_last) {
			/* Report unreached code */
			report(crt_loc, ERR_stmt_stmt_unreach());
			unreached_last = 1;
		}
	}
	unreached_code = uc;

	/* Check second operand */
#if LANGUAGE_C
	b = convert_lvalue(b);
#endif
	b = convert_none(b);
	tb = DEREF_type(exp_type(b));

	/* Construct the result */
	if (started && IS_exp_comma(a)) {
		LIST(EXP)q;
		LIST(EXP)p = DEREF_list(exp_comma_args(a));
		CONS_exp(b, NULL_list(EXP), q);
		p = APPEND_list(p, q);
		COPY_list(exp_comma_args(a), p);
		COPY_type(exp_type(a), tb);
		e = a;
	} else {
		LIST(EXP)p;
		CONS_exp(b, NULL_list(EXP), p);
		CONS_exp(a, p, p);
		MAKE_exp_comma(tb, p, e);
	}
	return e;
}


/*
    This routine constructs the n-ary comma expression 'p1, p2, ..., pn' for
    the expression list p = ( p1, p2, ..., pn ).  Note that this groups from
    left to right as '( ( ... ( p1, p2 ), ... ), pn )'.
*/

EXP
make_comma_exp(LIST(EXP)p)
{
	EXP e;
	if (IS_NULL_list(p)) {
		/* This shouldn't happen */
		e = make_error_exp(LANGUAGE_CPP);
	} else {
		int started = 0;
		DESTROY_CONS_exp(destroy, e, p, p);
		while (!IS_NULL_list(p)) {
			EXP a;
			DESTROY_CONS_exp(destroy, a, p, p);
			e = make_comma_simple(e, a, started);
			started = 1;
		}
		if (!started) {
			/* This shouldn't happen */
			e = convert_reference(e, REF_NORMAL);
		}
	}
	return e;
}
