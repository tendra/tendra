/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/ustring.h>
#include <utility/buffer.h>

#include <syntax/syntax.h>

#include <parse/literal.h>
#include <parse/predict.h>

#include <construct/assign.h>
#include <construct/basetype.h>
#include <construct/cast.h>
#include <construct/construct.h>
#include <construct/convert.h>
#include <construct/chktype.h>
#include <construct/expression.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/member.h>
#include <construct/operator.h>
#include <construct/link.h>

#include "exp_ops.h"
#include "id_ops.h"
#include "off_ops.h"
#include "type_ops.h"


/*
    This routine converts the expression a to the type t, as if by
    assignment.  The cases where t is a class type or a reference are
    handled elsewhere.
*/

EXP
convert_assign(TYPE t, EXP a, ERROR *err)
{
	EXP e = cast_exp(t, a, err, CAST_IMPLICIT);
	return e;
}


/*
    This routine converts the expression a to the class t, as if by
    assignment.  The constructors of t are ignored, only base class
    conversions and conversion operators being considered.
*/

EXP
convert_class(TYPE t, EXP a, ERROR *err)
{
	EXP e;
	TYPE s = DEREF_type(exp_type(a));
	if (IS_type_compound(s)) {
		e = cast_class_class(t, a, err, CAST_IMPLICIT, 0);
		if (!IS_NULL_exp(e)) {
			return e;
		}
	}
	e = convert_conv(t, a, err, CAST_IMPLICIT);
	return e;
}


/*
    This routine constructs the expressions 'a++' and 'a--'.  Note that
    in this and other assignment expressions, a cannot have array type,
    so that no bounds checks are appropriate.  The result is an rvalue.
*/

EXP
make_postfix_exp(int op, EXP a)
{
	EXP e;
	TYPE ta;
	ERROR err;
	unsigned ca;

	/* An assignment is a side effect */
	no_side_effects++;

	/* Allow for reference conversions */
	a = convert_reference(a, REF_NORMAL);
	ta = DEREF_type(exp_type(a));
	ca = type_category(&ta);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca)) {
		if (overload_depth == 0) {
			/* Overloads as 'operator op ( a, 0 )' */
			EXP b = make_null_exp(type_sint);
			e = binary_overload(op, a, b);
			return e;
		}
		if (IS_TYPE_CLASS(ca)) {
			goto error_lab;
		}
	}
#else
	if (IS_TYPE_CLASS(ca)) {
		goto error_lab;
	}
#endif

	/* Operand should be a modifiable lvalue */
	err = check_modifiable(ta, a);
	if (!IS_NULL_err(err)) {
		err = concat_error(err, ERR_expr_post_incr_mod(op));
		report(crt_loc, err);
		err = NULL_err;
	}

	/* Operand can be arithmetic ... */
	if (IS_TYPE_ARITH(ca)) {
		EXP b;
		TYPE t;
		TYPE tb;
		OFFSET off = NULL_off;

		/* Allow for bitfields */
		if (IS_TYPE_BITF(ca)) {
			off = decons_bitf_exp(&a);
		}

		/* Form the result */
		MAKE_exp_dummy(ta, a, LINK_NONE, off, 0, a);
		b = convert_lvalue(a);
		tb = DEREF_type(exp_type(b));
		t = promote_type(tb);
		if (IS_NULL_off(off)) {
			MAKE_exp_dummy(tb, b, LINK_NONE, NULL_off, 0, b);
			e = convert_promote(t, b);
		} else {
			b = convert_promote(t, b);
			MAKE_exp_dummy(t, b, LINK_NONE, NULL_off, 0, b);
			e = b;
			tb = t;
		}
		if (check_int_type(ta, btype_bool)) {
			/* Booleans are weird */
			unsigned v = BOOL_TRUE;
			if (op == lex_plus_Hplus) {
				report(crt_loc,
				       ERR_expr_post_incr_bool_inc(op, ta));
			} else {
				report(crt_loc,
				       ERR_expr_post_incr_bool_dec(op, ta));
				v = BOOL_FALSE;
			}
			e = make_bool_exp(v, exp_int_lit_tag);
		} else {
			/* Other types are simple */
			EXP c = make_unit_exp(t);
			if (op == lex_plus_Hplus) {
				MAKE_exp_plus(t, e, c, e);
			} else {
				MAKE_exp_minus(t, e, c, e);
			}
			e = convert_assign(ta, e, &err);
			if (!IS_NULL_err(err)) {
				err = concat_warning(err, ERR_expr_ass_conv());
				report(crt_loc, err);
			}
		}
		MAKE_exp_postinc(tb, a, b, e, e);
		return e;
	}

	/* ... or pointer ... */
	if (IS_TYPE_PTR(ca)) {
		/* Pointer must be to complete object type */
		EXP b;
		OFFSET off;
		TYPE t = check_pointer(ta, &err);
		if (!IS_NULL_err(err)) {
			err = concat_error(err, ERR_expr_post_incr_incompl(op));
			report(crt_loc, err);
		}
		if (IS_type_top_etc(t)) {
			t = type_char;
		}

		/* Create the identities */
		MAKE_exp_dummy(ta, a, LINK_NONE, NULL_off, 0, a);
		b = convert_lvalue(a);
		ta = DEREF_type(exp_type(b));
		MAKE_exp_dummy(ta, b, LINK_NONE, NULL_off, 0, b);

		/* Form the result */
		MAKE_off_type(t, off);
		if (op == lex_minus_Hminus) {
			MAKE_off_negate(off, off);
		}
		e = make_add_ptr(ta, b, off);
		MAKE_exp_postinc(ta, a, b, e, e);
		return e;
	}

	/* ... and nothing else */
error_lab:
	if (!IS_TYPE_ERROR(ca)) {
		report(crt_loc, ERR_expr_post_incr_op(op, ta));
	}
	e = make_error_exp(0);
	return e;
}


/*
    This routine creates a pre-increment or assignment expression for
    the expression a of type t given by the operation b.  If a is a
    bitfield then off gives the bitfield offset.  The result is an
    lvalue in C++, but an rvalue in C.  There is a slight problem in the
    latter case when t is a bitfield: the value is not b, but
    convert_bitfield ( b ).  This conversion is left implicit, and is
    only made explicit in the TDF output routines.
*/

static EXP
make_preinc_exp(TYPE t, EXP a, EXP b, OFFSET off, int op)
{
	EXP e;
#if LANGUAGE_C
	t = rvalue_type(t);
#endif
	if (IS_NULL_off(off)) {
		/* Simple case */
		if (op == lex_assign) {
			MAKE_exp_assign(t, a, b, e);
		} else {
			MAKE_exp_preinc(t, a, b, op, e);
		}
	} else {
		/* Bitfield case */
#if LANGUAGE_C
		MAKE_exp_preinc(t, a, b, op, e);
		t = promote_type(t);
#else
		TYPE p;
		TYPE s = find_bitfield_type(t);
		MAKE_type_ptr(cv_none, s, p);
		s = lvalue_type(s);
		MAKE_exp_preinc(s, a, b, op, e);
		MAKE_exp_address(p, e, e);
		MAKE_exp_add_ptr(p, e, off, 0, e);
		MAKE_exp_indir(t, e, e);
#endif
	}
#if LANGUAGE_C
	MAKE_exp_contents(t, e, e);
#endif
	return e;
}


/*
    This routine constructs the expressions '++a' and '--a'.  The result is
    an lvalue in C++ but an rvalue in C.
*/

EXP
make_prefix_exp(int op, EXP a)
{
	EXP e;
	TYPE ta;
	ERROR err;
	unsigned ca;

	/* An assignment is a side effect */
	no_side_effects++;

	/* Allow for reference conversions */
	a = convert_reference(a, REF_NORMAL);
	ta = DEREF_type(exp_type(a));
	ca = type_category(&ta);

	/* Check for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca)) {
		if (overload_depth == 0) {
			/* Overloads as 'operator op ( a )' */
			e = unary_overload(op, a);
			return e;
		}
		if (IS_TYPE_CLASS(ca)) {
			goto error_lab;
		}
	}
#else
	if (IS_TYPE_CLASS(ca)) {
		goto error_lab;
	}
#endif

	/* Operand should be a modifiable lvalue */
	err = check_modifiable(ta, a);
	if (!IS_NULL_err(err)) {
		err = concat_error(err, ERR_expr_pre_incr_mod(op));
		report(crt_loc, err);
		err = NULL_err;
	}

	/* Operand can be arithmetic ... */
	if (IS_TYPE_ARITH(ca)) {
		EXP c;
		TYPE t;
		OFFSET off = NULL_off;

		/* Booleans are weird */
		if (check_int_type(ta, btype_bool)) {
			unsigned v = BOOL_TRUE;
			if (op == lex_plus_Hplus) {
				report(crt_loc,
				       ERR_expr_pre_incr_bool_inc(op, ta));
			} else {
				report(crt_loc,
				       ERR_expr_pre_incr_bool_dec(op, ta));
				v = BOOL_FALSE;
			}
			c = make_bool_exp(v, exp_int_lit_tag);
			e = make_preinc_exp(ta, a, c, NULL_off, lex_assign);
			return e;
		}

		/* Allow for bitfields */
		if (IS_TYPE_BITF(ca)) {
			off = decons_bitf_exp(&a);
		}

		/* Form the result */
		MAKE_exp_dummy(ta, a, LINK_NONE, off, 0, a);
		e = convert_lvalue(a);
		t = DEREF_type(exp_type(e));
		t = promote_type(t);
		e = convert_promote(t, e);
		c = make_unit_exp(t);
		if (op == lex_plus_Hplus) {
			MAKE_exp_plus(t, e, c, e);
		} else {
			MAKE_exp_minus(t, e, c, e);
		}
		e = convert_assign(ta, e, &err);
		if (!IS_NULL_err(err)) {
			err = concat_warning(err, ERR_expr_ass_conv());
			report(crt_loc, err);
		}
		e = make_preinc_exp(ta, a, e, off, op);
		return e;
	}

	/* ... or pointer ... */
	if (IS_TYPE_PTR(ca)) {
		/* Pointer must be to complete object type */
		OFFSET off;
		TYPE t = check_pointer(ta, &err);
		if (!IS_NULL_err(err)) {
			err = concat_error(err, ERR_expr_pre_incr_incompl(op));
			report(crt_loc, err);
		}
		if (IS_type_top_etc(t)) {
			t = type_char;
		}

		/* Form the result */
		MAKE_exp_dummy(ta, a, LINK_NONE, NULL_off, 0, a);
		e = convert_lvalue(a);
		if (!IS_type_ptr(ta)) {
			ta = DEREF_type(exp_type(e));
		}
		MAKE_off_type(t, off);
		if (op == lex_minus_Hminus) {
			MAKE_off_negate(off, off);
		}
		e = make_add_ptr(ta, e, off);
		e = make_preinc_exp(ta, a, e, NULL_off, op);
		return e;
	}

	/* ... and nothing else */
error_lab:
	if (!IS_TYPE_ERROR(ca)) {
		report(crt_loc, ERR_expr_pre_incr_op(op, ta));
	}
	e = make_error_exp(LANGUAGE_CPP);
	return e;
}


/*
    This routine constructs the expression 'a = b'.  If c is true then
    assignment of classes is done directly rather than via an assignment
    operator.  The result is an lvalue in C++ but an rvalue in C.
*/

EXP
make_assign_exp(EXP a, EXP b, int c)
{
	EXP e;
	ERROR err;
	TYPE ta, tb;
	unsigned ca, cb;
	int to_class = 0;
	int op = lex_assign;
	OFFSET off = NULL_off;

	/* An assignment is a side effect */
	no_side_effects++;

	/* Apply reference conversion on first operand */
	a = convert_reference(a, REF_NORMAL);
	ta = DEREF_type(exp_type(a));
	ca = type_category(&ta);

	/* Apply reference conversion on second operand */
	b = convert_reference(b, REF_ASSIGN);
	tb = DEREF_type(exp_type(b));
	cb = type_category(&tb);

	/* Check for template parameters */
#if LANGUAGE_CPP
	if (IS_TYPE_TEMPL(ca) || IS_TYPE_TEMPL(cb)) {
		if (overload_depth == 0) {
			e = binary_overload(op, a, b);
			return e;
		}
	}
#endif

	/* Check for overloading (classes only) */
	if (IS_TYPE_CLASS(ca)) {
#if LANGUAGE_CPP
		if (c == 0) {
			if (overload_depth == 0) {
				e = binary_overload(op, a, b);
				return e;
			}
			if (!IS_TYPE_ERROR(cb)) {
				/* Find reason for failure */
				err = check_incomplete(ta);
				if (IS_NULL_err(err) && IS_type_compound(ta)) {
					CLASS_TYPE ct;
					IDENTIFIER id;
					ct = DEREF_ctype(type_compound_defn(ta));
					id = find_operator(ct, op);
					if (!IS_NULL_id(id)) {
						err = ERR_over_match_viable_none(id);
					}
				}
				err = concat_error(err, ERR_expr_ass_op(op, ta, tb));
				report(crt_loc, err);
			}
			e = make_error_exp(LANGUAGE_CPP);
			return e;
		}
#else
		UNUSED(c);
		UNUSED(cb);
#endif
		to_class = 1;
	}

	/* First operand should be a modifiable lvalue */
	err = check_modifiable(ta, a);
	if (!IS_NULL_err(err)) {
		err = concat_error(err, ERR_expr_ass_mod(op));
		report(crt_loc, err);
	}

	/* Do operand conversion */
	err = NULL_err;
	if (to_class) {
		b = convert_none(b);
		b = convert_class(ta, b, &err);
		b = remove_temporary(b, a);
	} else {
		b = convert_assign(ta, b, &err);
	}
	if (!IS_NULL_err(err)) {
		err = concat_warning(err, ERR_expr_ass_conv());
		report(crt_loc, err);
	}

	/* Construct the result */
	if (IS_type_bitfield(ta)) {
		off = decons_bitf_exp(&a);
		MAKE_exp_dummy(ta, a, LINK_NONE, off, 0, a);
	}
	e = make_preinc_exp(ta, a, b, off, op);
	return e;
}


/*
    This routine constructs the expression 'a op b' where op is one of the
    assignment operators, '*=', '/=' etc.  The result is an lvalue in
    C++, but an rvalue in C.
*/

EXP
make_become_exp(int op, EXP a, EXP b)
{
	EXP e;
	EXP d;
	TYPE td;
	ERROR err;
	TYPE ta, tb;
	unsigned tag;
	unsigned ca, cb;
	OFFSET off = NULL_off;

	/* An assignment is a side effect */
	no_side_effects++;

	/* Apply reference conversion on first operand */
	a = convert_reference(a, REF_NORMAL);
	ta = DEREF_type(exp_type(a));
	ca = type_category(&ta);

	/* Apply reference conversion on second operand */
	b = convert_reference(b, REF_NORMAL);
	tb = DEREF_type(exp_type(b));
	cb = type_category(&tb);

	/* Allow for overloading */
#if LANGUAGE_CPP
	if (IS_TYPE_OVERLOAD(ca) || IS_TYPE_OVERLOAD(cb)) {
		if (overload_depth == 0) {
			e = binary_overload(op, a, b);
			return e;
		}
		if (IS_TYPE_CLASS(ca)) {
			goto error_lab;
		}
	}
#else
	if (IS_TYPE_CLASS(ca)) {
		goto error_lab;
	}
#endif

	/* First operand should be a modifiable lvalue */
	err = check_modifiable(ta, a);
	if (!IS_NULL_err(err)) {
		err = concat_error(err, ERR_expr_ass_mod(op));
		report(crt_loc, err);
		err = NULL_err;
	}

	/* Allow for bitfields */
	if (IS_TYPE_BITF(ca)) {
		off = decons_bitf_exp(&a);
	}

	/* Introduce identity for assignment variable */
	td = ta;
	MAKE_exp_dummy(td, a, LINK_NONE, off, 0, d);
	a = convert_lvalue(d);
	ta = DEREF_type(exp_type(a));
	ca = type_category(&ta);

	/* Do lvalue conversions */
	if (IS_TYPE_ADDRESS(cb)) {
		b = convert_lvalue(b);
		tb = DEREF_type(exp_type(b));
		cb = type_category(&tb);
	}

	/* Weed out booleans immediately */
	if (IS_TYPE_INT(ca) && check_int_type(ta, btype_bool)) {
		report(crt_loc, ERR_expr_ass_op(op, ta, tb));
		e = make_error_exp(LANGUAGE_CPP);
		return e;
	}

	/* Find the operation type */
	switch (op) {
	case lex_and_Heq_H1: tag = exp_and_tag;    goto integral_lab;
	case lex_div_Heq:    tag = exp_div_tag;    goto arithmetic_lab;
	case lex_lshift_Heq: tag = exp_lshift_tag; goto shift_lab;
	case lex_minus_Heq:  tag = exp_minus_tag;  goto pointer_lab;
	case lex_or_Heq_H1:  tag = exp_or_tag;     goto integral_lab;
	case lex_plus_Heq:   tag = exp_plus_tag;   goto pointer_lab;
	case lex_rem_Heq:    tag = exp_rem_tag;    goto integral_lab;
	case lex_rshift_Heq: tag = exp_rshift_tag; goto shift_lab;
	case lex_star_Heq:   tag = exp_mult_tag;   goto arithmetic_lab;
	case lex_xor_Heq_H1: tag = exp_xor_tag;    goto integral_lab;

	default:
		goto error_lab;
	}

integral_lab:
	/* Integral operations */
	if (IS_TYPE_INT(ca) && IS_TYPE_INT(cb)) {
		TYPE t = arith_type(ta, tb, a, b);
		a = convert_arith(t, a, op, 1);
		b = convert_arith(t, b, op, 2);
		if (op == lex_rem_Heq) {
			IGNORE check_div_exp(op, a, b);
		}
		MAKE_exp_plus_etc(tag, t, a, b, e);
		e = convert_assign(td, e, &err);
		if (!IS_NULL_err(err)) {
			err = concat_warning(err, ERR_expr_ass_conv());
			report(crt_loc, err);
		}
		e = make_preinc_exp(td, d, e, off, op);
		return e;
	}
	goto error_lab;

arithmetic_lab:
	/* Arithmetic operations */
	if (IS_TYPE_ARITH(ca) && IS_TYPE_ARITH(cb)) {
		TYPE t = arith_type(ta, tb, a, b);
		a = convert_arith(t, a, op, 1);
		b = convert_arith(t, b, op, 2);
		if (op == lex_div_Heq) {
			IGNORE check_div_exp(op, a, b);
		}
		MAKE_exp_plus_etc(tag, t, a, b, e);
		e = convert_assign(td, e, &err);
		if (!IS_NULL_err(err)) {
			err = concat_warning(err, ERR_expr_ass_conv());
			report(crt_loc, err);
		}
		e = make_preinc_exp(td, d, e, off, op);
		return e;
	}
	goto error_lab;

shift_lab:
	/* Shift operations */
	if (IS_TYPE_INT(ca) && IS_TYPE_INT(cb)) {
		TYPE pta = promote_type(ta);
		TYPE ptb = promote_type(tb);
		a = convert_promote(pta, a);
		b = convert_promote(ptb, b);
		IGNORE check_shift_exp(op, pta, a, b);
		MAKE_exp_plus_etc(tag, pta, a, b, e);
		e = convert_assign(td, e, &err);
		if (!IS_NULL_err(err)) {
			err = concat_warning(err, ERR_expr_ass_conv());
			report(crt_loc, err);
		}
		e = make_preinc_exp(td, d, e, off, op);
		return e;
	}
	goto error_lab;

pointer_lab:
	/* Pointer or arithmetic operations */
	if (IS_TYPE_PTR(ca) && IS_TYPE_INT(cb)) {
		OFFSET off1;
		int neg = 0;
		TYPE t = check_pointer(ta, &err);
		if (!IS_NULL_err(err)) {
			err = concat_error(err, ERR_expr_ass_incompl(op));
			report(crt_loc, err);
		}
		if (op == lex_minus_Heq) {
			neg = 1;
		}
		off1 = make_off_mult(t, b, neg);
		e = make_add_ptr(ta, a, off1);
		e = make_preinc_exp(td, d, e, NULL_off, op);
		return e;
	}
	goto arithmetic_lab;

error_lab:
	/* Bad operations */
	if (!IS_TYPE_ERROR(ca) && !IS_TYPE_ERROR(cb)) {
		report(crt_loc, ERR_expr_ass_op(op, ta, tb));
	}
	e = make_error_exp(LANGUAGE_CPP);
	return e;
}
