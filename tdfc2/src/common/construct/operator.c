/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include "config.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "nat_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "allocate.h"
#include "assign.h"
#include "basetype.h"
#include "cast.h"
#include "chktype.h"
#include "class.h"
#include "constant.h"
#include "construct.h"
#include "convert.h"
#include "copy.h"
#include "derive.h"
#include "dump.h"
#include "exception.h"
#include "expression.h"
#include "function.h"
#include "hash.h"
#include "identifier.h"
#include "initialise.h"
#include "instance.h"
#include "inttype.h"
#include "member.h"
#include "namespace.h"
#include "operator.h"
#include "overload.h"
#include "quality.h"
#include "statement.h"
#include "syntax.h"
#include "template.h"
#include "typeid.h"


/*
    This routine returns the lexical token number of associated with
    the test ntst.  The default value returned is lex.
*/

int
ntest_token(NTEST ntst, int lex)
{
	switch (ntst) {
	case ntest_eq:
		lex = lex_eq;
		break;
	case ntest_not_eq:
		lex = lex_not_Heq_H1;
		break;
	case ntest_less:
		lex = lex_less;
		break;
	case ntest_less_eq:
		lex = lex_less_Heq;
		break;
	case ntest_greater:
		lex = lex_greater;
		break;
	case ntest_greater_eq:
		lex = lex_greater_Heq;
		break;
	}
	return lex;
}


/*
    This routine returns the lexical token number associated with the
    expression e.  The default value returned is lex.
*/

int
op_token(EXP e, int lex)
{
	if (!IS_NULL_exp(e)) {
		switch (TAG_exp(e)) {
		case exp_negate_tag:
			lex = lex_minus;
			break;
		case exp_compl_tag:
			lex = lex_compl_H1;
			break;
		case exp_not_tag:
			lex = lex_not_H1;
			break;
		case exp_abs_tag:
			lex = lex_abs;
			break;
		case exp_plus_tag:
			lex = lex_plus;
			break;
		case exp_minus_tag:
			lex = lex_minus;
			break;
		case exp_mult_tag:
			lex = lex_star;
			break;
		case exp_div_tag:
			lex = lex_div;
			break;
		case exp_rem_tag:
			lex = lex_rem;
			break;
		case exp_and_tag:
			lex = lex_and_H1;
			break;
		case exp_or_tag:
			lex = lex_or_H1;
			break;
		case exp_xor_tag:
			lex = lex_xor_H1;
			break;
		case exp_log_and_tag:
			lex = lex_logical_Hand_H1;
			break;
		case exp_log_or_tag:
			lex = lex_logical_Hor_H1;
			break;
		case exp_lshift_tag:
			lex = lex_lshift;
			break;
		case exp_rshift_tag:
			lex = lex_rshift;
			break;
		case exp_max_tag:
			lex = lex_max;
			break;
		case exp_min_tag:
			lex = lex_min;
			break;
		case exp_test_tag: {
			NTEST ntst = DEREF_ntest(exp_test_tst(e));
			lex = ntest_token(ntst, lex);
			break;
		}
		case exp_compare_tag: {
			NTEST ntst = DEREF_ntest(exp_compare_tst(e));
			lex = ntest_token(ntst, lex);
			break;
		}
		case exp_paren_tag: {
			EXP a = DEREF_exp(exp_paren_arg(e));
			lex = op_token(a, lex);
			break;
		}
		case exp_copy_tag: {
			EXP a = DEREF_exp(exp_copy_arg(e));
			lex = op_token(a, lex);
			break;
		}
		}
	}
	return lex;
}


/*
    This routine applies the unary operator op to the argument a.  The
    type t2 gives the destination for any cast operator.
*/

EXP
apply_unary(int op, EXP a, TYPE t1, TYPE t2, int cpy)
{
	EXP e;
	if (cpy) {
		/* Copy argument if necessary */
		switch (op) {
		case lex_function:
			a = copy_func_exp(a, t1, t2);
			break;
		case lex_sizeof:
		case lex_alignof:
		case lex_typeid:
		case lex_vtable:
			suppress_usage++;
			a = copy_exp(a, t1, t2);
			suppress_usage--;
			break;
		default:
			a = copy_exp(a, t1, t2);
			break;
		}
	}
	suppress_quality++;
	switch (op) {
	case lex_and_H1:
		/* Construct '&a' */
		e = make_ref_exp(a, 0);
		break;
	case lex_abs:
	case lex_plus:
	case lex_minus:
	case lex_compl_H1:
		/* Construct '+a', '-a', '~a' and 'abs a' */
		e = make_uminus_exp(op, a);
		break;
	case lex_not_H1:
		/* Construct '!a' */
		e = make_not_exp(a);
		break;
	case lex_plus_Hplus:
	case lex_minus_Hminus:
		/* Construct '++a' and '--a' */
		e = make_prefix_exp(op, a);
		break;
	case lex_star:
		/* Construct '*a' */
		e = make_indir_exp(a);
		break;
	case lex_pointer:
		/* Construct null pointer constant */
		e = make_null_ptr(a, t2);
		if (IS_NULL_exp(e)) {
			/* Force conversion error */
			e = apply_unary(lex_implicit, a, t1, t2, 0);
		}
		break;
	case lex_sizeof:
	case lex_alignof: {
		/* Construct 'sizeof ( a )' */
		TYPE s;
		EXP b = a;
		suppress_usage++;
		s = typeof_exp(&b, 0, op);
		e = make_sizeof_exp(s, b, 0, op);
		suppress_usage--;
		break;
	}
	case lex_function: {
		/* Dummy function resolution operator */
		ERROR err = NULL_err;
		LIST(IDENTIFIER) pids = NULL_list(IDENTIFIER);
		a = resolve_cast(t2, a, &err, 1, 1, pids);
		e = cast_exp(t2, a, &err, CAST_IMPLICIT);
		if (!IS_NULL_err(err)) {
			report(crt_loc, err);
		}
		break;
	}
	case lex_implicit: {
		/* Dummy implicit cast operator */
		ERROR err = NULL_err;
		if (IS_exp_initialiser(a)) {
			LIST(EXP) args;
			args = DEREF_list(exp_initialiser_args(a));
			e = init_constr(t2, args, &err);
		} else {
			a = convert_reference(a, REF_ASSIGN);
			e = cast_exp(t2, a, &err, CAST_IMPLICIT);
		}
		if (!IS_NULL_err(err)) {
			report(crt_loc, err);
		}
		break;
	}
	case lex_cast: {
		/* Construct '( t2 ) a' */
		if (IS_NULL_exp(a)) {
			ERROR err = NULL_err;
			e = init_empty(t2, cv_none, 1, &err);
			if (!IS_NULL_err(err))report(crt_loc, err);
		} else {
			e = make_cast_exp(t2, a, 0);
		}
		break;
	}
	case lex_if:
	case lex_do:
	case lex_for:
	case lex_while:
	case lex_cond_Hop: {
		/* Dummy conditional operators */
		EXP b = NULL_exp;
		e = check_cond(a, &b, op);
		break;
	}
	case lex_switch: {
		/* Dummy control operator */
		EXP b = NULL_exp;
		EXP c = NULL_exp;
		e = check_control(a, &b, &c);
		break;
	}
	case lex_fall:
	case lex_return: {
		/* Dummy return operator */
		IDENTIFIER lab = NULL_id;
		e = find_return_exp(a, &lab, op);
		break;
	}
	case lex_discard:
		/* Dummy expression statement operator */
		e = make_exp_stmt(a);
		break;
	case lex_void:
		/* Dummy discard operator */
		e = make_discard_exp(a);
		break;
	case lex_question:
		/* Dummy identity operator */
		e = a;
		break;
#if LANGUAGE_CPP
	case lex_delete:
		/* Construct 'delete a' */
		e = make_delete_exp(lex_delete, 0, a);
		break;
	case lex_delete_Hfull:
		/* Construct '::delete a' */
		e = make_delete_exp(lex_delete, 1, a);
		break;
	case lex_delete_Harray:
		/* Construct 'delete [] a' */
		e = make_delete_exp(lex_delete_Harray, 0, a);
		break;
	case lex_delete_Harray_Hfull:
		/* Construct '::delete [] a' */
		e = make_delete_exp(lex_delete_Harray, 1, a);
		break;
	case lex_compute:
		/* Construct empty new-initialiser */
		e = make_new_init(t2, NULL_list(EXP), 0);
		break;
	case lex_typeid:
	case lex_vtable:
		/* Construct 'typeid ( a )' */
		suppress_usage++;
		e = make_typeid_exp(op, a, 0);
		suppress_usage--;
		break;
	case lex_static_Hcast:
	case lex_reinterpret_Hcast:
	case lex_const_Hcast:
	case lex_dynamic_Hcast:
		/* Construct 'op < t2 > ( a )' */
		e = make_new_cast_exp(op, t2, a, 0);
		break;
#endif
	default:
		/* Illegal operations */
		error(ERR_INTERNAL, "Unexpected unary operation");
		e = make_error_exp(0);
		break;
	}
	suppress_quality--;
	return e;
}


/*
    This routine applies the binary operator op to the arguments a and b.
*/

EXP
apply_binary(int op, EXP a, EXP b, TYPE t1, TYPE t2, int cpy)
{
	EXP e;
	if (cpy) {
		/* Copy arguments if necessary */
		a = copy_exp(a, t1, t2);
		b = copy_exp(b, t1, t2);
	}
	suppress_quality++;
	switch (op) {
	case lex_and_H1:
		/* Construct 'a & b' */
		e = make_and_exp(a, b);
		break;
	case lex_and_Heq_H1:
	case lex_div_Heq:
	case lex_lshift_Heq:
	case lex_minus_Heq:
	case lex_or_Heq_H1:
	case lex_plus_Heq:
	case lex_rem_Heq:
	case lex_rshift_Heq:
	case lex_star_Heq:
	case lex_xor_Heq_H1:
		/* Construct 'a &= b', 'a /= b' etc. */
		e = make_become_exp(op, a, b);
		break;
	case lex_array_Hop:
		/* Construct 'a [b]' */
		e = make_index_exp(a, b);
		break;
	case lex_arrow:
	case lex_dot:
		/* Construct 'a->b' and 'a.b' */
		e = make_field_exp(op, a, b);
		break;
	case lex_assign:
		/* Construct 'a = b' */
		e = make_assign_exp(a, b, LANGUAGE_C);
		break;
	case lex_comma: {
		/* Construct 'a, b' */
		LIST(EXP) p = NULL_list(EXP);
		CONS_exp(b, p, p);
		CONS_exp(a, p, p);
		e = make_comma_exp(p);
		break;
	}
	case lex_eq:
	case lex_not_Heq_H1:
		/* Construct 'a == b' and 'a != b' */
		e = make_equality_exp(op, a, b);
		break;
	case lex_greater:
	case lex_greater_Heq:
	case lex_less:
	case lex_less_Heq:
		/* Construct 'a > b', 'a >= b', 'a < b' and 'a <= b' */
		e = make_relation_exp(op, a, b);
		break;
	case lex_logical_Hand_H1:
		/* Construct 'a && b' */
		e = make_log_and_exp(a, b);
		break;
	case lex_logical_Hor_H1:
		/* Construct 'a || b' */
		e = make_log_or_exp(a, b);
		break;
	case lex_lshift:
	case lex_rshift:
		/* Construct 'a << b' and 'a >> b' */
		e = make_shift_exp(op, a, b);
		break;
	case lex_minus:
		/* Construct 'a - b' */
		e = make_minus_exp(a, b);
		break;
	case lex_plus:
		/* Construct 'a + b' */
		e = make_plus_exp(a, b);
		break;
	case lex_plus_Hplus:
	case lex_minus_Hminus:
		/* Construct 'a++' and 'a--' */
		e = make_postfix_exp(op, a);
		break;
	case lex_or_H1:
		/* Construct 'a | b' */
		e = make_or_exp(a, b);
		break;
	case lex_rem:
		/* Construct 'a % b' */
		e = make_rem_exp(a, b);
		break;
	case lex_star:
	case lex_div:
	case lex_max:
	case lex_min:
		/* Construct 'a * b' and 'a / b' */
		e = make_mult_exp(op, a, b);
		break;
	case lex_xor_H1:
		/* Construct 'a ^ b' */
		e = make_xor_exp(a, b);
		break;
	case lex_colon:
		/* Construct 'NULL_exp ? a : b' */
		e = make_cond_exp(NULL_exp, a, b);
		break;
#if LANGUAGE_CPP
	case lex_arrow_Hstar:
	case lex_dot_Hstar:
		/* Construct 'a->*b' and 'a.*b' */
		e = make_member_exp(op, a, b);
		break;
#endif
	default:
		/* Illegal operations */
		error(ERR_INTERNAL, "Unexpected binary operation");
		e = make_error_exp(0);
		break;
	}
	suppress_quality--;
	return e;
}


/*
    This routine applies the n-ary operator op to the arguments p.  The
    type t2 gives the destination for any cast operator.
*/

EXP
apply_nary(int op, LIST(EXP)p, TYPE t1, TYPE t2, int cpy)
{
	EXP e;
	suppress_quality++;
	switch (op) {
	case lex_comma: {
		/* Construct 'p0, p1, ..., pn' */
		if (cpy) {
			p = copy_exp_list(p, t1, t2);
		}
		e = make_comma_exp(p);
		break;
	}
	case lex_cond_Hop: {
		/* Construct 'p0 ? p1 : p2' */
		EXP c, a, b;
		c = DEREF_exp(HEAD_list(p));
		p = TAIL_list(p);
		a = DEREF_exp(HEAD_list(p));
		p = TAIL_list(p);
		b = DEREF_exp(HEAD_list(p));
		if (cpy) {
			c = copy_exp(c, type_bool, type_bool);
			a = copy_exp(a, t1, t2);
			b = copy_exp(b, t1, t2);
		}
		e = make_cond_exp(c, a, b);
		break;
	}
	case lex_func_Hop: {
		/* Construct 'p0 ( p1, ..., pn )' */
		EXP a = DEREF_exp(HEAD_list(p));
		p = TAIL_list(p);
		if (cpy) {
			a = copy_func_exp(a, t1, t2);
			p = copy_exp_list(p, t1, t2);
		}
		e = make_func_exp(a, p, 1);
		break;
	}
	case lex_cast:
		/* Construct 't2 ( p0, ..., pn )' */
		if (cpy) {
			p = copy_exp_list(p, t1, t2);
		}
		e = make_func_cast_exp(t2, p);
		break;
	case lex_static_Hcast: {
		/* Construct 't2 ( p0, ..., pn )' */
		ERROR err = NULL_err;
		if (cpy) {
			p = copy_exp_list(p, t1, t2);
		}
		p = convert_args(p);
		e = convert_constr(t2, p, &err, CAST_STATIC);
		if (!IS_NULL_err(err)) {
			report(crt_loc, err);
		}
		break;
	}
#if LANGUAGE_CPP
	case lex_new:
	case lex_new_Hfull: {
		/* Construct 'new ( p3, ..., pn ) ( t0 [ p1 ] ) ( p2 )' */
		EXP a;
		TYPE s;
		int b = 0;
		if (op == lex_new_Hfull) {
			b = 1;
		}
		if (cpy) {
			p = copy_exp_list(p, t1, t2);
		}
		a = DEREF_exp(HEAD_list(p));
		p = TAIL_list(p);
		s = DEREF_type(exp_type(a));
		a = DEREF_exp(HEAD_list(p));
		p = TAIL_list(p);
		if (!IS_NULL_exp(a)) {
			/* Array dimension */
			NAT n;
			MAKE_nat_calc(a, n);
			MAKE_type_array(cv_none, s, n, s);
		}
		a = DEREF_exp(HEAD_list(p));
		p = TAIL_list(p);
		e = make_new_exp(s, 0, b, p, a);
		break;
	}
	case lex_compute:
		/* Construct new-initialiser, '( p0, ..., pn )' */
		if (cpy) {
			p = copy_exp_list(p, t1, t2);
		}
		e = make_new_init(t2, p, 1);
		break;
#endif
	default:
		/* Illegal operations */
		error(ERR_INTERNAL, "Unexpected nary operation");
		e = make_error_exp(0);
		break;
	}
	suppress_quality--;
	return e;
}


/*
    This routine converts the nth operand a to the built-in operator op
    to type t.
*/

static EXP
convert_builtin(TYPE t, EXP a, int op, unsigned n)
{
	ERROR err = NULL_err;
	if (IS_type_compound(t)) {
		a = convert_class(t, a, &err);
	} else {
		a = init_assign(t, cv_none, a, &err);
	}
	if (!IS_NULL_err(err)) {
		err = init_error(err, 0);
		err = concat_error(err, ERR_expr_convert_op(n, op));
		report(crt_loc, err);
	}
	return a;
}


/*
    This routine applies the built-in operator id to the arguments args.
*/

EXP
apply_builtin(IDENTIFIER id, LIST(EXP) args)
{
	EXP e;
	TYPE t;
	int op;
	EXP a, b;
	HASHID nm = DEREF_hashid(id_name(id));
	LIST(TYPE) ts = DEREF_list(id_builtin_ptypes(id));

	/* Find operator */
	if (IS_hashid_op(nm)) {
		op = DEREF_int(hashid_op_lex(nm));
	} else {
		op = lex_func_Hop;
	}

	/* Shouldn't have no arguments */
	if (IS_NULL_list(args)) {
		e = make_error_exp(0);
		return e;
	}

	/* Convert first argument */
	DESTROY_CONS_exp(destroy, a, args, args);
	t = DEREF_type(HEAD_list(ts));
	a = convert_builtin(t, a, op,(unsigned)1);

	/* Allow for 'operator ()' */
	if (op == lex_func_Hop) {
		overload_depth++;
		e = make_func_exp(a, args, 0);
		overload_depth--;
		return e;
	}

	/* Allow for unary operators */
	if (IS_NULL_list(args)) {
		overload_depth++;
		e = apply_unary(op, a, NULL_type, NULL_type, 0);
		overload_depth--;
		return e;
	}

	/* Convert second argument */
	DESTROY_CONS_exp(destroy, b, args, args);
	t = DEREF_type(HEAD_list(TAIL_list(ts)));
	b = convert_builtin(t, b, op,(unsigned)1);

	/* Allow for binary operators */
	if (IS_NULL_list(args)) {
		overload_depth++;
		e = apply_binary(op, a, b, NULL_type, NULL_type, 0);
		overload_depth--;
		return e;
	}

	/* Shouldn't have more than two arguments */
	DESTROY_list(args, SIZE_exp);
	e = make_error_exp(0);
	return e;
}


/*
    This flag is used to keep track of the depth of overloaded operator
    resolutions.
*/

int overload_depth = 0;
int overload_warn = 1;


/*
    The operator overloading routines are only included in the C++
    producer.
*/

#if LANGUAGE_CPP


/*
    This routine checks the function type t for the overloaded operator id.
    The argument mem is true if id represents a non-static member function.
    Most operators have restrictions on the number and types of their
    parameters, others must be member functions.  Note that this routine
    only covers genuine overloading operators such as 'operator +', the
    allocation operators such as 'operator new' are handled by the routine
    check_allocator and alloc is set accordingly.
*/

TYPE
check_operator(TYPE t, IDENTIFIER id, int mem, int *alloc)
{
	int op;
	int ell;
	HASHID nm;
	int dargs = 0;
	unsigned n, m;
	unsigned npars;
	LIST(TYPE) ptypes;

	/* Allow for template types */
	if (IS_type_templ(t)) {
		TYPE s = DEREF_type(type_templ_defn(t));
		s = check_operator(s, id, mem, alloc);
		COPY_type(type_templ_defn(t), s);
		return t;
	}

	/* Find the operator */
	nm = DEREF_hashid(id_name(id));
	op = DEREF_int(hashid_op_lex(nm));
	switch (op) {
	case lex_new:
	case lex_new_Harray:
		/* Check for allocation operators */
		*alloc = 1;
		t = check_allocator(t, id, mem, 0);
		return t;
	case lex_delete:
	case lex_delete_Harray:
		/* Check for deallocation operators */
		*alloc = 2;
		t = check_allocator(t, id, mem, 0);
		return t;
	default:
		*alloc = 0;
		break;
	}

	/* Decompose function type */
	ptypes = DEREF_list(type_func_ptypes(t));
	npars = LENGTH_list(ptypes);
	ell = DEREF_int(type_func_ellipsis(t));
	if (ell) {
		/* Set number of parameters to dummy large value */
		npars = 10000;
	}

	/* Check function arguments */
	if (mem) {
		/* Member functions have implicit extra parameter */
		npars++;
		n = 0;
		m = 1;
	} else {
		/* Should have an overloadable parameter */
		LIST(TYPE) p = ptypes;
		while (!IS_NULL_list(p)) {
			TYPE a = DEREF_type(HEAD_list(p));
			unsigned ca = type_category(&a);
			if (IS_TYPE_OVERLOAD(ca)) {
				break;
			}
			p = TAIL_list(p);
		}
		if (IS_NULL_list(p)) {
			report(crt_loc, ERR_over_oper_type(nm));
		}
		n = 1;
		m = 2;
	}

	/* Check number of arguments */
	switch (op) {
	case lex_compl_H1:
	case lex_not_H1:
	case lex_abs:
	case lex_alignof:
	case lex_sizeof:
	case lex_typeid:
	case lex_vtable:
		/* Unary operators */
		if (npars != 1) {
			ERROR err = ERR_over_unary_pars(nm, n, n);
			report(crt_loc, err);
		}
		break;
	case lex_plus:
	case lex_minus:
	case lex_star:
	case lex_and_H1:
		/* Either unary or binary operators */
		if (npars != 1 && npars != 2) {
			ERROR err = ERR_over_binary_pars_p1(nm, n, m, m);
			report(crt_loc, err);
		}
		break;
	default:
		/* Binary operators */
		if (npars != 2) {
			ERROR err = ERR_over_binary_pars_p2(nm, m, m);
			report(crt_loc, err);
		}
		break;
	case lex_assign:
		/* Assignment */
		if (!mem) {
			report(crt_loc, ERR_over_ass_mem(nm));
		}
		if (npars != 2) {
			ERROR err = ERR_over_ass_pars(nm, m, m);
			report(crt_loc, err);
		}
		break;
	case lex_func_Hop:
		/* Function call (can have default arguments) */
		if (!mem) {
			report(crt_loc, ERR_over_call_mem(nm));
		}
		dargs = 1;
		break;
	case lex_array_Hop:
		/* Subscripting */
		if (!mem) {
			report(crt_loc, ERR_over_sub_mem(nm));
		}
		if (npars != 2) {
			ERROR err = ERR_over_sub_pars(nm, m, m);
			report(crt_loc, err);
		}
		break;
	case lex_arrow:
		/* Class member access */
		if (!mem) {
			report(crt_loc, ERR_over_ref_mem(nm));
		}
		if (npars != 1) {
			ERROR err = ERR_over_ref_pars(nm, n, n);
			report(crt_loc, err);
		}
		break;
	case lex_plus_Hplus:
	case lex_minus_Hminus:
		/* Increment and decrement */
		if (npars == 1) {
			/* One argument form is fine */
			/* EMPTY */
		} else if (npars == 2) {
			/* Two argument form needs checking */
			TYPE a;
			TYPE b = type_sint;
			LIST(TYPE) p = ptypes;
			if (!mem) {
				p = TAIL_list(p);
			}
			a = DEREF_type(HEAD_list(p));
			if (!eq_type_unqual(a, b) && !is_templ_type(a)) {
				/* Second argument should be 'int' */
				report(crt_loc, ERR_over_inc_pars_p2(nm, b));
			}
		} else {
			/* Anything else is illegal */
			ERROR err = ERR_over_inc_pars(nm, n, m, m);
			report(crt_loc, err);
		}
		break;
	case lex_cond_Hop:
		/* Tertiary operators */
		if (npars != 3) {
			unsigned p = n + 2;
			ERROR err = ERR_over_binary_pars_p2(nm, p, p);
			report(crt_loc, err);
		}
		break;
	}

	/* Check for default arguments */
	if (!dargs && check_func_dargs(t, 0, 0)) {
		report(crt_loc, ERR_over_oper_default(nm));
	}
	return t;
}


/*
    These values are used in the allocation and deallocation of built-in
    operators.
*/

static IDENTIFIER unary_free = NULL_id;
static IDENTIFIER unary_all = NULL_id;
static IDENTIFIER binary_free = NULL_id;
static IDENTIFIER binary_all = NULL_id;
static IDENTIFIER nary_free = NULL_id;
static IDENTIFIER nary_all = NULL_id;


/*
    This routine constructs the built-in unary operator 'r nm ( a )'.
*/

static IDENTIFIER
unary_builtin(HASHID nm, TYPE a, TYPE r)
{
	LIST(TYPE) p;
	IDENTIFIER id = unary_free;
	if (IS_NULL_id(id)) {
		/* Allocate new identifier */
		NAMESPACE ns = NULL_nspace;
		CONS_type(a, NULL_list(TYPE), p);
		MAKE_id_builtin(nm, dspec_none, ns, builtin_loc, r, p, id);
		COPY_id(id_alias(id), unary_all);
		unary_all = id;
	} else {
		/* Use existing identifier */
		COPY_hashid(id_name(id), nm);
		COPY_ulong(id_dump(id), LINK_NONE);
		COPY_type(id_builtin_ret(id), r);
		p = DEREF_list(id_builtin_ptypes(id));
		COPY_type(HEAD_list(p), a);
		unary_free = DEREF_id(id_alias(id));
	}
	return id;
}


/*
    This routine constructs the built-in binary operator 'r nm ( a, b )'.
*/

static IDENTIFIER
binary_builtin(HASHID nm, TYPE a, TYPE b, TYPE r)
{
	LIST(TYPE) p;
	IDENTIFIER id = binary_free;
	if (IS_NULL_id(id)) {
		/* Allocate new identifier */
		NAMESPACE ns = NULL_nspace;
		CONS_type(b, NULL_list(TYPE), p);
		CONS_type(a, p, p);
		MAKE_id_builtin(nm, dspec_none, ns, builtin_loc, r, p, id);
		COPY_id(id_alias(id), binary_all);
		binary_all = id;
	} else {
		/* Use existing identifier */
		COPY_hashid(id_name(id), nm);
		COPY_ulong(id_dump(id), LINK_NONE);
		COPY_type(id_builtin_ret(id), r);
		p = DEREF_list(id_builtin_ptypes(id));
		COPY_type(HEAD_list(p), a);
		p = TAIL_list(p);
		COPY_type(HEAD_list(p), b);
		binary_free = DEREF_id(id_alias(id));
	}
	return id;
}


/*
    This routine constructs the built-in n-ary operator 'r nm ( a, p )'.
*/

static IDENTIFIER
nary_builtin(HASHID nm, TYPE a, LIST(TYPE) p, TYPE r)
{
	IDENTIFIER id = nary_free;
	if (IS_NULL_id(id)) {
		/* Allocate new identifier */
		NAMESPACE ns = NULL_nspace;
		CONS_type(a, p, p);
		MAKE_id_builtin(nm, dspec_none, ns, builtin_loc, r, p, id);
		COPY_id(id_alias(id), nary_all);
		nary_all = id;
	} else {
		/* Use existing identifier */
		LIST(TYPE) q;
		COPY_hashid(id_name(id), nm);
		COPY_ulong(id_dump(id), LINK_NONE);
		COPY_type(id_builtin_ret(id), r);
		q = DEREF_list(id_builtin_ptypes(id));
		COPY_type(HEAD_list(q), a);
		COPY_list(PTR_TAIL_list(q), p);
		nary_free = DEREF_id(id_alias(id));
	}
	return id;
}


/*
    This routine constructs the candidate list for the overloaded n-ary
    operation op, adding the result to p.  The candidates come from the
    current namespace and the type t, if this is a class.  The routine
    returns the hash table entry for 'operator op'.
*/

static HASHID
overload_candidates(CANDIDATE_LIST *p, int op, TYPE t, TYPE s)
{
	/* Look up 'operator op' (non-standard) */
	HASHID nm = lookup_op(op);
	switch (op) {
	case lex_assign:
	case lex_func_Hop:
	case lex_array_Hop:
	case lex_arrow:
		/* These can only be member functions */
		break;
	default: {
		/* These can be non-member functions */
		IDENTIFIER id = find_op_id(nm);
		if (!IS_NULL_type(s)) {
			IGNORE koenig_candidates(p, id, s, KIND_OP);
		}
		IGNORE koenig_candidates(p, id, t, KIND_OP);
		if (!IS_id_dummy(id)) {
			/* Function declared */
			add_candidates(p, id, 1, KIND_OP);
		}
		break;
	}
	}

	/* Look up 't::operator op' */
	if (IS_type_compound(t)) {
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		NAMESPACE ns = DEREF_nspace(ctype_member(ct));
		IDENTIFIER id = search_field(ns, nm, 0, 0);
		if (!IS_NULL_id(id)) {
			if (IS_id_ambig(id)) {
				/* Ambiguous look-up */
				IGNORE report_ambiguous(id, 0, 1, 0);
			}
			add_candidates(p, id, 1, KIND_MEM_OP);
		}
	}
	return nm;
}


/*
    This routine adds all the promoted integral types to the list res.
*/

static LIST(TYPE)
add_int_types(LIST(TYPE) res)
{
	if (basetype_info[ntype_sllong].key) {
		res = cons_type_set(res, type_ullong);
		res = cons_type_set(res, type_sllong);
	}
	res = cons_type_set(res, type_ulong);
	res = cons_type_set(res, type_slong);
	res = cons_type_set(res, type_uint);
	res = cons_type_set(res, type_sint);
	return res;
}


/*
    This routine adds all the floating point types to the list res.
*/

static LIST(TYPE)
add_float_types(LIST(TYPE) res)
{
	res = cons_type_set(res, type_ldouble);
	res = cons_type_set(res, type_double);
	res = cons_type_set(res, type_float);
	return res;
}


/*
    This routine constructs a list of types consisting of all the types
    of a certain kind to which the type t can be converted.  Conversions
    which are worse that existing conversions are omitted.  The type kind
    is indicated by the CTYPE macros defined in chktype.h, except that
    CTYPE_INTEGER refers to promoted integer types unless qualified using
    CTYPE_LVALUE.
*/

static LIST(TYPE)
find_type_convs(TYPE t, EXP a, unsigned kind)
{
	LIST(TYPE) res = NULL_list(TYPE);
	unsigned nt = TAG_type(t);
	switch (nt) {
	case type_compound_tag: {
		/* Class types */
		LIST(IDENTIFIER) conv;
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		complete_class(ct, 1);
		conv = DEREF_list(ctype_conv(ct));
		for (; !IS_NULL_list(conv); conv = TAIL_list(conv)) {
			/* Scan through conversion operations */
			TYPE r;
			HASHID nm;
			unsigned nr;
			IDENTIFIER id = DEREF_id(HEAD_list(conv));
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_explicit) {
				continue;
			}

			/* Check for reference types */
			nm = DEREF_hashid(id_name(id));
			r = DEREF_type(hashid_conv_type(nm));
			if (kind == CTYPE_NONE) {
				/* Include all types in this case */
				res = cons_type_set(res, r);
				continue;
			}
			nr = TAG_type(r);
			if (nr == type_ref_tag) {
				/* Allow for reference bindings */
				if (IS_TYPE_LVALUE(kind)) {
					TYPE s = DEREF_type(type_ref_sub(r));
					CV_SPEC cv = find_cv_qual(s);
					if (!(cv & cv_const)) {
						/* Don't include const
						 * references */
						unsigned ns = TAG_type(s);
						switch (ns) {
						case type_integer_tag:
						case type_bitfield_tag:
						case type_enumerate_tag:
							if (IS_TYPE_INTEGER(kind)) {
								res = cons_type_set(res, r);
							}
							break;
						case type_floating_tag:
							if (IS_TYPE_FLOAT(kind)) {
								res = cons_type_set(res, r);
							}
							break;
						case type_ptr_tag:
							if (IS_TYPE_PTR(kind)) {
								res = cons_type_set(res, r);
							}
							break;
						case type_ptr_mem_tag:
							if (IS_TYPE_PTR_MEM(kind)) {
								res = cons_type_set(res, r);
							}
							break;
						}
					}
				} else {
					/* Allow for reference conversions */
					r = DEREF_type(type_ref_sub(r));
					nr = TAG_type(r);
				}
			}

			/* Check return type */
			switch (nr) {
			case type_integer_tag:
			case type_bitfield_tag:
			case type_enumerate_tag:
				/* Integral types */
				if (IS_TYPE_INTEGER(kind)) {
					/* Means promoted integer type */
					TYPE s = promote_type(r);
					res = cons_type_set(res, s);
				} else if (IS_TYPE_FLOAT(kind)) {
					/* Can convert to any floating type */
					res = add_float_types(res);
				}
				break;
			case type_floating_tag:
				/* Floating point types */
				if (IS_TYPE_FLOAT(kind)) {
					res = cons_type_set(res, r);
				} else if (IS_TYPE_INTEGER(kind)) {
					/* Can convert to any promoted integer
					 * type */
					res = add_int_types(res);
				}
				break;
			case type_ptr_tag:
				/* Pointer types */
				if (IS_TYPE_PTR(kind)) {
					res = cons_type_set(res, r);
				}
				break;
			case type_ptr_mem_tag:
				/* Pointer to member types */
				if (IS_TYPE_PTR_MEM(kind)) {
					res = cons_type_set(res, r);
				}
				break;
			}
		}
		res = REVERSE_list(res);
		break;
	}
	case type_integer_tag:
	case type_bitfield_tag:
	case type_enumerate_tag:
		/* Integral types */
		if (IS_TYPE_LVALUE(kind)) {
			/* Lvalue of integral type */
			if (IS_TYPE_INTEGER(kind)) {
				if (nt == type_integer_tag) {
					t = lvalue_type(t);
					MAKE_type_ref(cv_none, t, t);
					CONS_type(t, res, res);
				}
			}
		} else if (IS_TYPE_INTEGER(kind)) {
			/* Means promoted integer type */
			TYPE s = promote_type(t);
			CONS_type(s, res, res);
		} else if (IS_TYPE_FLOAT(kind)) {
			/* Can convert to any floating type */
			res = add_float_types(res);
		}
		break;
	case type_floating_tag:
		/* Floating point types */
		if (IS_TYPE_LVALUE(kind)) {
			/* Lvalue of floating point type */
			if (IS_TYPE_FLOAT(kind)) {
				t = lvalue_type(t);
				MAKE_type_ref(cv_none, t, t);
				CONS_type(t, res, res);
			}
		} else if (IS_TYPE_FLOAT(kind)) {
			/* Floating point type */
			CONS_type(t, res, res);
		} else if (IS_TYPE_INTEGER(kind)) {
			/* Can convert to any promoted integer type */
			if (basetype_info[ntype_sllong].key) {
				CONS_type(type_ullong, res, res);
				CONS_type(type_sllong, res, res);
			}
			CONS_type(type_ulong, res, res);
			CONS_type(type_slong, res, res);
			CONS_type(type_uint, res, res);
			CONS_type(type_sint, res, res);
		}
		break;
	case type_ptr_tag:
		/* Pointer types */
		if (IS_TYPE_PTR(kind)) {
			if (IS_TYPE_LVALUE(kind)) {
				t = lvalue_type(t);
				MAKE_type_ref(cv_none, t, t);
			}
			CONS_type(t, res, res);
		}
		break;
	case type_ptr_mem_tag:
		/* Pointer to member types */
		if (IS_TYPE_PTR_MEM(kind)) {
			if (IS_TYPE_LVALUE(kind)) {
				t = lvalue_type(t);
				MAKE_type_ref(cv_none, t, t);
			}
			CONS_type(t, res, res);
		}
		break;
	case type_array_tag:
		/* Allow for array-to-pointer conversion */
		if (IS_TYPE_PTR(kind) && !IS_TYPE_LVALUE(kind)) {
			TYPE s = DEREF_type(type_array_sub(t));
			MAKE_type_ptr(cv_none, s, s);
			CONS_type(s, res, res);
		}
		if (kind == CTYPE_NONE) {
			TYPE s = DEREF_type(type_array_sub(t));
			MAKE_type_ptr(cv_none, s, t);
		}
		break;
	case type_func_tag:
		/* Allow for function-to-pointer conversion */
		if (IS_TYPE_PTR(kind) && !IS_TYPE_LVALUE(kind)) {
			TYPE s;
			MAKE_type_ptr(cv_none, t, s);
			CONS_type(s, res, res);
		}
		if (kind == CTYPE_NONE) {
			MAKE_type_ptr(cv_none, t, t);
		}
		break;
	}
	if (kind == CTYPE_NONE) {
		/* Include all types in this case */
		CV_SPEC cv = DEREF_cv(type_qual(t));
		if (cv & cv_lvalue) {
			/* Turn lvalues into references */
			MAKE_type_ref(cv_none, t, t);
		}
		res = cons_type_set(res, t);
	}
	UNUSED(a);
	return res;
}


/*
    This routine scans through the list of pointer or pointer to member
    types pa replacing any types which are not pointers to complete object
    types by the null type.  If fn is true pointer to function types are
    also allowed.
*/

static void
filter_ptr(LIST(TYPE) pa, int fn)
{
	while (!IS_NULL_list(pa)) {
		TYPE ta = DEREF_type(HEAD_list(pa));
		TYPE sa = ta;
		if (IS_type_ref(sa)) {
			sa = DEREF_type(type_ref_sub(sa));
		}
		if (IS_type_ptr(sa)) {
			sa = DEREF_type(type_ptr_sub(sa));
		} else {
			sa = DEREF_type(type_ptr_mem_sub(sa));
		}
		switch (TAG_type(sa)) {
		case type_array_tag: {
			/* Check for incomplete arrays */
			NAT n = DEREF_nat(type_array_size(sa));
			if (IS_NULL_nat(n)) {
				ta = NULL_type;
			}
			break;
		}
		case type_compound_tag: {
			/* Check for incomplete classes */
			CLASS_TYPE cs = DEREF_ctype(type_compound_defn(sa));
			CLASS_INFO ci = DEREF_cinfo(ctype_info(cs));
			if (!(ci & cinfo_complete)) {
				ta = NULL_type;
			}
			break;
		}
		case type_enumerate_tag: {
			/* Check for incomplete enumerations */
			ENUM_TYPE es = DEREF_etype(type_enumerate_defn(sa));
			CLASS_INFO ei = DEREF_cinfo(etype_info(es));
			if (!(ei & cinfo_complete)) {
				ta = NULL_type;
			}
			break;
		}
		case type_top_tag:
		case type_bottom_tag:
			/* These are always incomplete */
			ta = NULL_type;
			break;
		case type_func_tag:
			/* Deal with function types */
			if (!fn) {
				ta = NULL_type;
			}
			break;
		}
		COPY_type(HEAD_list(pa), ta);
		pa = TAIL_list(pa);
	}
	return;
}


/*
    The following macros are used to describe the return types and the
    constraints on the operand types of the built-in operators.
*/

#define RTYPE_ARG_1		0
#define RTYPE_ARG_2		1
#define RTYPE_CONT_1		2
#define RTYPE_CONT_2		3
#define RTYPE_ARITH		4
#define RTYPE_BOOL		5
#define RTYPE_PTRDIFF		6
#define RTYPE_OP		7

#define OTYPE_NONE		0
#define OTYPE_PTR		1
#define OTYPE_PTR_MEM		2
#define OTYPE_REF_PTR		3
#define OTYPE_REF_MEM		4
#define OTYPE_SELECT		5
#define OTYPE_COND		6


/*
    This routine finds the return type for a built-in operator with
    operand types ta and tb and return descriptor rtype.  tc gives the
    default return type.  The return type is not used in overload
    resolution but is included for error reporting purposes.
*/

static TYPE
find_builtin_ret(TYPE ta, TYPE tb, int rtype, TYPE tc)
{
	switch (rtype) {
	case RTYPE_ARG_1:
		tc = ta;
		break;
	case RTYPE_ARG_2:
		tc = tb;
		break;
	case RTYPE_CONT_1:
		if (IS_type_ptr_etc(ta)) {
			tc = DEREF_type(type_ptr_etc_sub(ta));
		}
		break;
	case RTYPE_CONT_2:
		if (IS_type_ptr_etc(tb)) {
			tc = DEREF_type(type_ptr_etc_sub(tb));
		}
		break;
	case RTYPE_ARITH:
		tc = arith_type(ta, tb, NULL_exp, NULL_exp);
		break;
	case RTYPE_BOOL:
		tc = type_bool;
		break;
	case RTYPE_PTRDIFF:
		tc = type_ptrdiff_t;
		break;
	}
	return tc;
}


/*
    This routine checks whether the operand types ta and tb are valid for
    a built-in operator with operand constraints otype.  In some cases
    the return type is returned via pt.
*/

static int
check_builtin_args(TYPE ta, TYPE tb, int otype, TYPE *pt)
{
	int ok = 1;
	switch (otype) {
	case OTYPE_PTR: {
		/* Allow equal pointer types */
		TYPE sa = DEREF_type(type_ptr_sub(ta));
		TYPE sb = DEREF_type(type_ptr_sub(tb));
		ok = eq_type_unqual(sa, sb);
		break;
	}
	case OTYPE_PTR_MEM: {
		/* Allow equal pointer member types */
		CLASS_TYPE ca = DEREF_ctype(type_ptr_mem_of(ta));
		CLASS_TYPE cb = DEREF_ctype(type_ptr_mem_of(tb));
		if (eq_ctype(ca, cb)) {
			TYPE sa = DEREF_type(type_ptr_mem_sub(ta));
			TYPE sb = DEREF_type(type_ptr_mem_sub(tb));
			ok = eq_type_unqual(sa, sb);
		} else {
			ok = 0;
		}
		break;
	}
	case OTYPE_REF_PTR:
		/* Allow equal pointer types */
		if (IS_type_ref(ta)) {
			ta = DEREF_type(type_ref_sub(ta));
		}
		return check_builtin_args(ta, tb, OTYPE_PTR, pt);
	case OTYPE_REF_MEM:
		/* Allow equal pointer member types */
		if (IS_type_ref(ta)) {
			ta = DEREF_type(type_ref_sub(ta));
		}
		return check_builtin_args(ta, tb, OTYPE_PTR_MEM, pt);
	case OTYPE_SELECT: {
		/* Allow pointer member selection */
		TYPE sa = DEREF_type(type_ptr_sub(ta));
		if (IS_type_compound(sa)) {
			CLASS_TYPE ca = DEREF_ctype(type_compound_defn(sa));
			CLASS_TYPE cb = DEREF_ctype(type_ptr_mem_of(tb));
			GRAPH gr = find_base_class(ca, cb, 0);
			if (IS_NULL_graph(gr))ok = 0;
			*pt = DEREF_type(type_ptr_mem_sub(tb));
		} else {
			ok = 0;
		}
		break;
	}
	case OTYPE_COND: {
		/* Allow for conditional expressions */
		int suspect = 0;
		TYPE r = common_type(ta, tb, &suspect);
		if (IS_NULL_type(r)) {
			ok = 0;
			if (IS_type_ref(ta)) {
				ta = DEREF_type(type_ref_sub(ta));
				ok = 1;
			}
			if (IS_type_ref(tb)) {
				tb = DEREF_type(type_ref_sub(tb));
				ok = 1;
			}
			if (ok) {
				suspect = 0;
				r = common_type(ta, tb, &suspect);
				if (IS_NULL_type(r)) {
					ok = 0;
				} else {
					*pt = r;
				}
			}
		} else {
			*pt = r;
		}
		break;
	}
	}
	return ok;
}


/*
    This routine adds a series of built-in unary candidates for the
    operator nm to the list p.  The possible operand types are given by pa.
    rtype describes how to form the return type from the operand type.
*/

static void
add_unary_builtin(CANDIDATE_LIST *p, HASHID nm, LIST(TYPE) pa, int rtype)
{
	while (!IS_NULL_list(pa)) {
		TYPE ta = DEREF_type(HEAD_list(pa));
		if (!IS_NULL_type(ta)) {
			TYPE tb = find_builtin_ret(ta, ta, rtype, type_error);
			IDENTIFIER id = unary_builtin(nm, ta, tb);
			add_candidates(p, id, 1, KIND_BUILTIN);
		}
		pa = TAIL_list(pa);
	}
	DESTROY_list(pa, SIZE_type);
	return;
}


/*
    This routine adds a series of built-in binary candidates for the
    operator nm to the list p.  The possible first and second operand types
    are given by pa and pb.  rtype describes how to form the return type
    from the operand types, otype describes any restrictions on the operand
    types.
*/

static void
add_binary_builtin(CANDIDATE_LIST *p, HASHID nm, LIST(TYPE) pa, LIST(TYPE) pb,
		   int rtype, int otype)
{
    while (!IS_NULL_list(pa)) {
	TYPE ta = DEREF_type(HEAD_list(pa));
	if (!IS_NULL_type(ta)) {
	    LIST(TYPE) pc = pb;
	    while (!IS_NULL_list(pc)) {
		TYPE tb = DEREF_type(HEAD_list(pc));
		if (!IS_NULL_type(tb)) {
		    /* Check operand types */
		    TYPE tc = type_error;
		    if (check_builtin_args(ta, tb, otype, &tc)) {
			IDENTIFIER id;
			tc = find_builtin_ret(ta, tb, rtype, tc);
			if (otype == OTYPE_COND) {
			    ta = tc;
			    tb = tc;
			}
			id = binary_builtin(nm, ta, tb, tc);
			add_candidates(p, id, 1, KIND_BUILTIN);
		    }
		}
		pc = TAIL_list(pc);
	    }
	}
	pa = TAIL_list(pa);
    }
    if (!EQ_list(pa, pb)) {
	    DESTROY_list(pa, SIZE_type);
    }
    DESTROY_list(pb, SIZE_type);
    return;
}


/*
    This routine calculates the unary overload operator 'op a'.  This can
    be 'a.operator op ()', 'operator op ( a )' or 'op t ( a )' for some
    type t.  Note that '->' is a special case for op, with 'a->b' being
    expanded as '( a.operator -> () )->b'.  This expansion is done in
    begin_field_exp, this routine returning the null expression to indicate
    that '->' is not overloaded.
*/

EXP
unary_overload(int op, EXP a)
{
	EXP e;
	HASHID nm;
	IDENTIFIER id;
	LIST(TYPE) pa;
	CANDIDATE_LIST *p = &candidates;

	/* Check for template parameters */
	TYPE t = DEREF_type(exp_type(a));
	if (is_templ_type(t)) {
		MAKE_exp_op(t, op, a, NULL_exp, e);
		return e;
	}

	/* Construct candidate list */
	p->size = 0;
	nm = overload_candidates(p, op, t, NULL_type);

	/* Construct built-in candidates */
	switch (op) {
	case lex_plus:
		/* Built-in candidates for '+a' */
		pa = find_type_convs(t, a, CTYPE_SCALAR);
		add_unary_builtin(p, nm, pa, RTYPE_ARG_1);
		break;
	case lex_minus:
	case lex_abs:
		/* Built-in candidates for '-a' */
		pa = find_type_convs(t, a, CTYPE_ARITH);
		add_unary_builtin(p, nm, pa, RTYPE_ARG_1);
		break;
	case lex_compl_H1:
		/* Built-in candidates for '~a' */
		pa = find_type_convs(t, a, CTYPE_INT);
		add_unary_builtin(p, nm, pa, RTYPE_ARG_1);
		break;
	case lex_not_H1:
		/* Built-in candidate for '!a' */
		id = unary_builtin(nm, type_bool, type_bool);
		add_candidates(p, id, 1, KIND_BUILTIN);
		break;
	case lex_star:
		/* Built-in candidates for '*a' */
		pa = find_type_convs(t, a, CTYPE_PTR);
		filter_ptr(pa, 1);
		add_unary_builtin(p, nm, pa, RTYPE_CONT_1);
		break;
	case lex_plus_Hplus:
	case lex_minus_Hminus:
		/* Built-in candidates for '++a' and '--a' */
		pa = find_type_convs(t, a,(CTYPE_LVALUE | CTYPE_PTR));
		filter_ptr(pa, 0);
		add_unary_builtin(p, nm, pa, RTYPE_ARG_1);
		pa = find_type_convs(t, a,(CTYPE_LVALUE | CTYPE_ARITH));
		add_unary_builtin(p, nm, pa, RTYPE_ARG_1);
		break;
	case lex_and_H1:
		/* No built-in candidates for '&a' */
		break;
	case lex_arrow:
		/* No built-in candidates for 'a->' */
		break;
	}

	/* Search for overload operator */
	if (p->size) {
		CANDIDATE *q;
		unsigned rank;
		LIST(EXP) args;
		CONS_exp(a, NULL_list(EXP), args);
		q = resolve_overload(p, args, NULL_type, 0);
		unary_free = unary_all;
		rank = q->rank;
		if (rank >= RANK_VIABLE) {
			/* Only allow viable resolutions */
			int kind = q->kind;
			IDENTIFIER qid = q->func;
			int ow = overload_warn;
			if (rank == RANK_BEST) {
				/* Unambiguous resolution */
				if (match_no_viable > 1 && ow) {
					if (do_dump) {
						dump_builtin(qid);
					}
					report(crt_loc,
					       ERR_over_match_oper_ok(qid));
				}
			} else {
				/* Ambiguous resolution */
				q = resolve_ambiguous(p, args, NULL_type, 0);
				qid = q->func;
				rank = q->rank;
				if (rank == RANK_TARGET) {
					ERROR err2 =
					    ERR_over_match_oper_target(op);
					qid = make_ambig_func(p, qid, args,
							      qual_none,
							      &err2);
					kind = KIND_OP;
					if (do_dump) {
						dump_builtin(qid);
					}
					report(crt_loc, err2);
				} else if (rank == RANK_VIABLE) {
					ERROR err2 =
					    ERR_over_match_oper_ambig(op);
					err2 = list_candidates(err2, p,
							       RANK_VIABLE);
					report(crt_loc, err2);
				}
				overload_warn = 0;
			}
			if (kind == KIND_BUILTIN) {
				/* Built-in resolution */
				if (op == lex_arrow) {
					/* For 'a->' return the null
					 * expression */
					DESTROY_list(args, SIZE_exp);
					e = NULL_exp;
				} else {
					e = apply_builtin(qid, args);
				}
			} else {
				/* Function resolution */
				use_func_id(qid, 0, suppress_usage);
				e = apply_func_id(qid, qual_none, NULL_graph,
						  args);
			}
			overload_warn = ow;
			return e;
		}
		DESTROY_list(args, SIZE_exp);
	}

	/* Try operation again */
	if (op == lex_arrow) {
		/* For 'a->' return the null expression */
		e = NULL_exp;
	} else {
		overload_depth++;
		e = apply_unary(op, a, NULL_type, NULL_type, 0);
		overload_depth--;
	}
	return e;
}


/*
    This routine calculates the binary overload operator 'a op b'.  This can
    be 'a.operator op ( b )', 'operator op ( a, b )' or 't ( a ) op s ( b )'
    for some types t and s.  Note that postfix '++' and '--' are special
    cases for op in which b is a dummy zero operand.
*/

EXP
binary_overload(int op, EXP a, EXP b)
{
	EXP e;
	HASHID nm;
	LIST(TYPE) pa, pb;
	CANDIDATE_LIST *p = &candidates;

	/* Check for template parameters */
	TYPE t = DEREF_type(exp_type(a));
	TYPE s = DEREF_type(exp_type(b));
	if (is_templ_type(t)) {
		MAKE_exp_op(t, op, a, b, e);
		return e;
	}
	if (is_templ_type(s)) {
		MAKE_exp_op(s, op, a, b, e);
		return e;
	}

	/* Construct candidate list */
	p->size = 0;
	nm = overload_candidates(p, op, t, s);

	/* Construct built-in candidates */
	/* QUERY - overloaded function operands */
	switch (op) {
	case lex_logical_Hand_H1:
	case lex_logical_Hor_H1: {
		/* Built-in candidates for 'a && b' and 'a || b' */
		IDENTIFIER id;
		id = binary_builtin(nm, type_bool, type_bool, type_bool);
		add_candidates(p, id, 1, KIND_BUILTIN);
		break;
	}
	case lex_and_H1:
	case lex_or_H1:
	case lex_rem:
	case lex_xor_H1:
		/* Built-in candidates for 'a & b' etc. */
		pa = find_type_convs(t, a, CTYPE_INT);
		pb = find_type_convs(s, b, CTYPE_INT);
		add_binary_builtin(p, nm, pa, pb, RTYPE_ARITH, OTYPE_NONE);
		break;
	case lex_lshift:
	case lex_rshift:
		/* Built-in candidates for 'a << b' and 'a >> b' */
		pa = find_type_convs(t, a, CTYPE_INT);
		pb = find_type_convs(s, b, CTYPE_INT);
		add_binary_builtin(p, nm, pa, pb, RTYPE_ARG_1, OTYPE_NONE);
		break;
	case lex_minus:
		/* Built-in candidates for 'a - b' */
		pa = find_type_convs(t, a, CTYPE_PTR);
		pb = find_type_convs(s, b, CTYPE_PTR);
		filter_ptr(pa, 0);
		add_binary_builtin(p, nm, pa, pb, RTYPE_PTRDIFF, OTYPE_PTR);
		pa = find_type_convs(t, a, CTYPE_PTR);
		CONS_type(type_ptrdiff_t, NULL_list(TYPE), pb);
		filter_ptr(pa, 0);
		add_binary_builtin(p, nm, pa, pb, RTYPE_ARG_1, OTYPE_NONE);
		goto arith_op_lab;
	case lex_plus:
		/* Built-in candidates for 'a + b' */
		pa = find_type_convs(t, a, CTYPE_PTR);
		CONS_type(type_ptrdiff_t, NULL_list(TYPE), pb);
		filter_ptr(pa, 0);
		add_binary_builtin(p, nm, pa, pb, RTYPE_ARG_1, OTYPE_NONE);
		CONS_type(type_ptrdiff_t, NULL_list(TYPE), pa);
		pb = find_type_convs(s, b, CTYPE_PTR);
		filter_ptr(pb, 0);
		add_binary_builtin(p, nm, pa, pb, RTYPE_ARG_2, OTYPE_NONE);
		goto arith_op_lab;
	case lex_array_Hop:
		/* Built-in candidates for 'a [b]' */
		pa = find_type_convs(t, a, CTYPE_PTR);
		CONS_type(type_ptrdiff_t, NULL_list(TYPE), pb);
		filter_ptr(pa, 0);
		add_binary_builtin(p, nm, pa, pb, RTYPE_CONT_1, OTYPE_NONE);
		CONS_type(type_ptrdiff_t, NULL_list(TYPE), pa);
		pb = find_type_convs(s, b, CTYPE_PTR);
		filter_ptr(pb, 0);
		add_binary_builtin(p, nm, pa, pb, RTYPE_CONT_2, OTYPE_NONE);
		break;
	case lex_star:
	case lex_div:
	case lex_max:
	case lex_min:
arith_op_lab:
		/* Built-in candidates for 'a * b' and 'a / b' */
		pa = find_type_convs(t, a, CTYPE_ARITH);
		pb = find_type_convs(s, b, CTYPE_ARITH);
		add_binary_builtin(p, nm, pa, pb, RTYPE_ARITH, OTYPE_NONE);
		break;
	case lex_eq:
	case lex_not_Heq_H1:
		/* Built-in candidates for 'a == b' and 'a != b' */
		pa = find_type_convs(t, a, CTYPE_PTR_MEM);
		pb = find_type_convs(s, b, CTYPE_PTR_MEM);
		if (is_zero_exp(a)) {
			pa = pb;
		}
		if (is_zero_exp(b)) {
			pb = pa;
		}
		add_binary_builtin(p, nm, pa, pb, RTYPE_BOOL, OTYPE_PTR_MEM);
		goto relation_op_lab;
	case lex_greater:
	case lex_greater_Heq:
	case lex_less:
	case lex_less_Heq:
relation_op_lab:
		/* Built-in candidates for 'a > b' etc. */
		pa = find_type_convs(t, a, CTYPE_PTR);
		pb = find_type_convs(s, b, CTYPE_PTR);
		if (is_zero_exp(a)) {
			pa = pb;
		}
		if (is_zero_exp(b)) {
			pb = pa;
		}
		add_binary_builtin(p, nm, pa, pb, RTYPE_BOOL, OTYPE_PTR);
		pa = find_type_convs(t, a, CTYPE_ARITH);
		pb = find_type_convs(s, b, CTYPE_ARITH);
		add_binary_builtin(p, nm, pa, pb, RTYPE_BOOL, OTYPE_NONE);
		break;
	case lex_arrow_Hstar:
		/* Built-in candidates for 'a->*b' */
		pa = find_type_convs(t, a, CTYPE_PTR);
		pb = find_type_convs(s, b, CTYPE_PTR_MEM);
		filter_ptr(pb, 1);
		add_binary_builtin(p, nm, pa, pb, RTYPE_OP, OTYPE_SELECT);
		break;
	case lex_plus_Hplus:
	case lex_minus_Hminus:
		/* Built-in candidates for 'a++' and 'a--' */
		pa = find_type_convs(t, a,(CTYPE_LVALUE | CTYPE_PTR));
		CONS_type(type_sint, NULL_list(TYPE), pb);
		filter_ptr(pa, 0);
		add_binary_builtin(p, nm, pa, pb, RTYPE_CONT_1, OTYPE_NONE);
		pa = find_type_convs(t, a,(CTYPE_LVALUE | CTYPE_ARITH));
		CONS_type(type_sint, NULL_list(TYPE), pb);
		add_binary_builtin(p, nm, pa, pb, RTYPE_CONT_1, OTYPE_NONE);
		break;
	case lex_and_Heq_H1:
	case lex_lshift_Heq:
	case lex_or_Heq_H1:
	case lex_rem_Heq:
	case lex_rshift_Heq:
	case lex_xor_Heq_H1:
		/* Built-in candidates for 'a &= b' etc. */
		pa = find_type_convs(t, a,(CTYPE_LVALUE | CTYPE_INT));
		pb = find_type_convs(s, b, CTYPE_INT);
		add_binary_builtin(p, nm, pa, pb, RTYPE_ARG_1, OTYPE_NONE);
		break;
	case lex_div_Heq:
	case lex_star_Heq:
		/* Built-in candidates for 'a /= b' and 'a *= b' */
		pa = find_type_convs(t, a,(CTYPE_LVALUE | CTYPE_ARITH));
		pb = find_type_convs(s, b, CTYPE_ARITH);
		add_binary_builtin(p, nm, pa, pb, RTYPE_ARG_1, OTYPE_NONE);
		break;
	case lex_plus_Heq:
	case lex_minus_Heq:
		/* Built-in candidates for 'a += b' and 'a -= b' */
		pa = find_type_convs(t, a,(CTYPE_LVALUE | CTYPE_PTR));
		CONS_type(type_ptrdiff_t, NULL_list(TYPE), pb);
		add_binary_builtin(p, nm, pa, pb, RTYPE_ARG_1, OTYPE_NONE);
		pa = find_type_convs(t, a,(CTYPE_LVALUE | CTYPE_ARITH));
		pb = find_type_convs(s, b, CTYPE_ARITH);
		add_binary_builtin(p, nm, pa, pb, RTYPE_ARG_1, OTYPE_NONE);
		break;
	case lex_assign:
		/* Built-in candidates for 'a = b' */
		pa = find_type_convs(t, a,(CTYPE_LVALUE | CTYPE_PTR_MEM));
		pb = find_type_convs(s, b, CTYPE_PTR_MEM);
		add_binary_builtin(p, nm, pa, pb, RTYPE_ARG_1, OTYPE_REF_MEM);
		pa = find_type_convs(t, a,(CTYPE_LVALUE | CTYPE_PTR));
		pb = find_type_convs(s, b, CTYPE_PTR);
		add_binary_builtin(p, nm, pa, pb, RTYPE_ARG_1, OTYPE_REF_PTR);
		pa = find_type_convs(t, a,(CTYPE_LVALUE | CTYPE_ARITH));
		pb = find_type_convs(s, b, CTYPE_ARITH);
		add_binary_builtin(p, nm, pa, pb, RTYPE_ARG_1, OTYPE_NONE);
		break;
	case lex_comma:
		/* No built-in candidates for 'a, b' */
		break;
	case lex_colon: {
		/* Built-in candidates for '<condition> ? a : b' */
		LIST(TYPE) pc;
		pa = find_type_convs(t, a, CTYPE_NONE);
		pb = find_type_convs(s, b, CTYPE_NONE);
		if (is_zero_exp(a)) {
			/* Allow for null pointers */
			pc = find_type_convs(s, b,(CTYPE_PTR | CTYPE_PTR_MEM));
			pa = APPEND_list(pa, pc);
		}
		if (is_zero_exp(b)) {
			/* Allow for null pointers */
			pc = find_type_convs(t, a,(CTYPE_PTR | CTYPE_PTR_MEM));
			pb = APPEND_list(pb, pc);
		}
		add_binary_builtin(p, nm, pa, pb, RTYPE_OP, OTYPE_COND);
		break;
	}
	}

	/* Search for overload operator */
	if (p->size) {
		CANDIDATE *q;
		unsigned rank;
		LIST(EXP) args;
		CONS_exp(b, NULL_list(EXP), args);
		CONS_exp(a, args, args);
		q = resolve_overload(p, args, NULL_type, 0);
		binary_free = binary_all;
		rank = q->rank;
		if (rank >= RANK_VIABLE) {
			/* Only allow viable resolutions */
			int kind = q->kind;
			IDENTIFIER qid = q->func;
			int ow = overload_warn;
			if (rank == RANK_BEST) {
				/* Unambiguous resolution */
				if (match_no_viable > 1 && ow) {
					if (do_dump) {
						dump_builtin(qid);
					}
					report(crt_loc,
					       ERR_over_match_oper_ok(qid));
				}
			} else {
				/* Ambiguous resolution */
				q = resolve_ambiguous(p, args, NULL_type, 0);
				qid = q->func;
				rank = q->rank;
				if (rank == RANK_TARGET) {
					ERROR err2 =
					    ERR_over_match_oper_target(op);
					qid = make_ambig_func(p, qid, args,
							      qual_none,
							      &err2);
					kind = KIND_OP;
					if (do_dump) {
						dump_builtin(qid);
					}
					report(crt_loc, err2);
				} else if (rank == RANK_VIABLE) {
					ERROR err2 =
					    ERR_over_match_oper_ambig(op);
					err2 = list_candidates(err2, p,
							       RANK_VIABLE);
					report(crt_loc, err2);
				}
				overload_warn = 0;
			}
			if (kind == KIND_BUILTIN) {
				/* Built-in resolution */
				if (op == lex_comma) {
					/* Return null expression for 'a, b' */
					DESTROY_list(args, SIZE_exp);
					e = NULL_exp;
				} else {
					e = apply_builtin(qid, args);
				}
			} else {
				/* Function resolution */
				use_func_id(qid, 0, suppress_usage);
				e = apply_func_id(qid, qual_none, NULL_graph,
						  args);
			}
			overload_warn = ow;
			return e;
		}
		DESTROY_list(args, SIZE_exp);
	}

	/* Try operation again */
	if (op == lex_comma) {
		/* Return null expression for 'a, b' */
		e = NULL_exp;
	} else {
		overload_depth++;
		e = apply_binary(op, a, b, NULL_type, NULL_type, 0);
		overload_depth--;
	}
	return e;
}


/*
    This routine calculates the function overload operator 'a ( args )'.
    This is expanded as 'a.operator () ( args )'.
*/

EXP
function_overload(EXP a, LIST(EXP)args)
{
	EXP e;
	int op = lex_func_Hop;

	/* Construct candidate list */
	TYPE t = DEREF_type(exp_type(a));
	CANDIDATE_LIST *p = &candidates;
	p->size = 0;
	IGNORE overload_candidates(p, op, t, NULL_type);

	if (IS_type_compound(t)) {
		LIST(IDENTIFIER) conv;
		HASHID nm = KEYWORD(lex_zzzz);
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		complete_class(ct, 1);
		conv = DEREF_list(ctype_conv(ct));
		while (!IS_NULL_list(conv)) {
			/* Scan through conversion operations */
			IDENTIFIER cid = DEREF_id(HEAD_list(conv));
			DECL_SPEC ds = DEREF_dspec(id_storage(cid));
			if (!(ds & dspec_explicit)) {
				HASHID cnm = DEREF_hashid(id_name(cid));
				TYPE r = DEREF_type(hashid_conv_type(cnm));
				unsigned nr = TAG_type(r);

				/* Search for pointer or reference to
				 * functions */
				if (nr == type_ptr_tag || nr == type_ref_tag) {
					TYPE s =
					    DEREF_type(type_ptr_etc_sub(r));
					if (IS_type_func(s)) {
						LOCATION loc;
						LIST(TYPE) ptypes;
						TYPE ret = DEREF_type(type_func_ret(s));
						ptypes = DEREF_list(type_func_ptypes(s));
						DEREF_loc(id_loc(cid), loc);
						cid = nary_builtin(nm, r,
								   ptypes,
								   ret);
						COPY_loc(id_loc(cid), loc);
						add_candidates(p, cid, 1,
							       KIND_BUILTIN);
					}
				}
			}
			conv = TAIL_list(conv);
		}
	}

	/* Search for overload operator */
	if (p->size) {
		CANDIDATE *q;
		unsigned rank;
		CONS_exp(a, args, args);
		q = resolve_overload(p, args, NULL_type, 0);
		nary_free = nary_all;
		rank = q->rank;
		if (rank >= RANK_VIABLE) {
			/* Only allow viable resolutions */
			int kind = q->kind;
			IDENTIFIER qid = q->func;
			int ow = overload_warn;
			if (rank == RANK_BEST) {
				/* Unambiguous resolution */
				if (match_no_viable > 1 && ow) {
					if (do_dump) {
						dump_builtin(qid);
					}
					report(crt_loc,
					       ERR_over_match_oper_ok(qid));
				}
			} else {
				/* Ambiguous resolution */
				q = resolve_ambiguous(p, args, NULL_type, 0);
				qid = q->func;
				rank = q->rank;
				if (rank == RANK_TARGET) {
					ERROR err =
					    ERR_over_match_oper_target(op);
					qid = make_ambig_func(p, qid, args,
							      qual_none, &err);
					kind = KIND_OP;
					if (do_dump) {
						dump_builtin(qid);
					}
					report(crt_loc, err);
				} else if (rank == RANK_VIABLE) {
					ERROR err =
					    ERR_over_match_oper_ambig(op);
					err = list_candidates(err, p,
							      RANK_VIABLE);
					report(crt_loc, err);
				}
				overload_warn = 0;
			}
			if (kind == KIND_BUILTIN) {
				/* Built-in resolution */
				e = apply_builtin(qid, args);
			} else {
				/* Function resolution */
				use_func_id(qid, 0, suppress_usage);
				e = apply_func_id(qid, qual_none, NULL_graph,
						  args);
			}
			overload_warn = ow;
			return e;
		}
		DESTROY_CONS_exp(destroy, a, args, args);
	}

	/* Try operation again with increased overload depth */
	overload_depth++;
	e = make_func_exp(a, args, 0);
	overload_depth--;
	return e;
}


#endif /* LANGUAGE_CPP */
