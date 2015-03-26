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

#include <tdf/capsule.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/buffer.h>
#include <utility/option.h>

#include <syntax/syntax.h>

#include <parse/constant.h>
#include <parse/hash.h>
#include <parse/literal.h>
#include <parse/predict.h>
#include <parse/preproc.h>

#include <construct/allocate.h>
#include <construct/basetype.h>
#include <construct/cast.h>
#include <construct/check.h>
#include <construct/chktype.h>
#include <construct/class.h>
#include <construct/construct.h>
#include <construct/convert.h>
#include <construct/copy.h>
#include <construct/declare.h>
#include <construct/derive.h>
#include <construct/destroy.h>
#include <construct/exception.h>
#include <construct/expression.h>
#include <construct/function.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/instance.h>
#include <construct/label.h>
#include <construct/namespace.h>
#include <construct/operator.h>
#include <construct/redeclare.h>
#include <construct/rewrite.h>
#include <construct/statement.h>
#include <construct/template.h>
#include <construct/token.h>

#include <output/bitstream.h>
#include <output/capsule.h>
#include <output/compile.h>
#include <output/dump.h>

#include "ctype_ops.h"
#include "exp_ops.h"
#include "id_ops.h"
#include "graph_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "member_ops.h"
#include "off_ops.h"
#include "tok_ops.h"
#include "type_ops.h"


/*
    This routine checks whether the expression e denotes an unresolved
    implicit cast expression.  If so it returns the expression being
    cast.  Otherwise the null expression is returned.  The copying
    routines work perfectly well for such implicit casts however
    spotting them early can help to give a context to any error message.
*/

EXP
implicit_cast_exp(EXP e)
{
	if (!IS_NULL_exp(e)) {
		unsigned tag = TAG_exp(e);
		if (tag == exp_op_tag) {
			/* Check for implicit conversions */
			int op = DEREF_int(exp_op_lex(e));
			if (op == lex_implicit) {
				EXP a = DEREF_exp(exp_op_arg1(e));
				return a;
			}
		}
		if (tag == exp_aggregate_tag || tag == exp_nof_tag) {
			/* Check for aggregate initialisers */
			return e;
		}
	}
	return NULL_exp;
}


/*
    This routine defines the variable or static data member id to be e.
*/

static void
copy_variable(IDENTIFIER id, EXP e)
{
	EXP d;
	TYPE t1 = DEREF_type(id_variable_etc_type(id));
	TYPE t2 = expand_type(t1, 1);
	if (IS_NULL_exp(e)) {
		/* Empty initialiser */
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if ((ds & dspec_temp) && (ds & dspec_explicit)) {
			/* Explicitly initialised temporary */
			/* EMPTY */
		} else {
			e = init_general(t2, e, id, LANGUAGE_C);
		}
	} else {
		EXP a = implicit_cast_exp(e);
		if (!IS_NULL_exp(a)) {
			/* Implicit cast initialiser */
			a = copy_exp(a, t1, t2);
			e = init_general(t2, a, id, 0);
		} else {
			/* Simple initialiser */
			e = copy_exp(e, t1, t2);
			e = dynamic_init(id, NULL_string, e);
		}
		e = check_init(e);
	}
	d = destroy_general(t2, id);
	COPY_exp(id_variable_etc_term(id), d);
	COPY_exp(id_variable_etc_init(id), e);
	return;
}


/*
    This routine copies the local variable id.
*/

static
IDENTIFIER copy_local(IDENTIFIER id)
{
	IDENTIFIER cid = copy_id(id, 2);
	COPY_id(id_alias(id), cid);
	DEREF_loc(id_loc(id), crt_loc);
	decl_loc = crt_loc;
	if (IS_id_variable(cid)) {
		EXP e = DEREF_exp(id_variable_init(cid));
		copy_variable(cid, e);
	}
	return cid;
}


/*
    This routine copies the offset for the type t.  The result must be a
    complete object type.
*/

static TYPE
copy_type_offset(TYPE t, int op)
{
	TYPE s = expand_type(t, 1);
	if (!EQ_type(s, t)) {
		ERROR err = check_complete(s);
		if (!IS_NULL_err(err)) {
			err = concat_error(err, ERR_expr_add_incompl(op));
			report(crt_loc, err);
		}
	}
	return s;
}


/*
    This routine copies the offset off.
*/

OFFSET
copy_offset(OFFSET off, int op)
{
	if (IS_NULL_off(off)) {
		return NULL_off;
	}
	assert(ORDER_off == 13);
	switch (TAG_off(off)) {
	case off_zero_tag: {
		/* Zero offsets */
		TYPE t = DEREF_type(off_zero_type(off));
		t = copy_type_offset(t, op);
		MAKE_off_zero(t, off);
		break;
	}
	case off_type_tag: {
		/* Type offsets */
		TYPE t = DEREF_type(off_type_type(off));
		t = copy_type_offset(t, op);
		MAKE_off_type(t, off);
		break;
	}
	case off_array_tag: {
		/* Array type offsets */
		TYPE t = DEREF_type(off_array_type(off));
		unsigned n = DEREF_unsigned(off_array_arg(off));
		t = copy_type_offset(t, op);
		MAKE_off_array(t, n, off);
		break;
	}
	case off_extra_tag: {
		/* Extra allocation offsets */
		TYPE t = DEREF_type(off_extra_type(off));
		int n = DEREF_int(off_extra_scale(off));
		t = expand_type(t, 1);
		MAKE_off_extra(t, n, off);
		break;
	}
	case off_base_tag: {
		/* Direct base class offsets */
		GRAPH gr = DEREF_graph(off_base_graph(off));
		gr = expand_graph(gr, 1);
		if (!IS_NULL_graph(gr)) {
			off = DEREF_off(graph_off(gr));
		}
		break;
	}
	case off_deriv_tag: {
		/* Indirect base class offsets */
		GRAPH gr = DEREF_graph(off_deriv_graph(off));
		gr = expand_graph(gr, 1);
		if (!IS_NULL_graph(gr)) {
			off = DEREF_off(graph_off(gr));
		}
		break;
	}
	case off_member_tag: {
		/* Member offsets */
		IDENTIFIER id = DEREF_id(off_member_id(off));
		id = rescan_id(id, qual_nested, 0);
		if (IS_id_member(id)) {
			off = DEREF_off(id_member_off(id));
		}
		break;
	}
	case off_ptr_mem_tag: {
		/* Pointer to member offsets */
		EXP a = DEREF_exp(off_ptr_mem_arg(off));
		a = copy_exp(a, NULL_type, NULL_type);
		MAKE_off_ptr_mem(a, off);
		break;
	}
	case off_negate_tag: {
		/* Negated offsets */
		OFFSET a = DEREF_off(off_negate_arg(off));
		op = (lex_plus + lex_minus) - op;
		a = copy_offset(a, op);
		MAKE_off_negate(a, off);
		break;
	}
	case off_plus_tag: {
		/* Offset additions */
		OFFSET a = DEREF_off(off_plus_arg1(off));
		OFFSET b = DEREF_off(off_plus_arg2(off));
		a = copy_offset(a, op);
		b = copy_offset(b, op);
		MAKE_off_plus(a, b, off);
		break;
	}
	case off_mult_tag: {
		/* Offset multiplications */
		OFFSET a = DEREF_off(off_mult_arg1(off));
		EXP b = DEREF_exp(off_mult_arg2(off));
		a = copy_offset(a, op);
		b = copy_exp(b, NULL_type, NULL_type);
		MAKE_off_mult(a, b, off);
		break;
	}
	case off_ptr_diff_tag: {
		/* Pointer differences */
		EXP a = DEREF_exp(off_ptr_diff_ptr1(off));
		EXP b = DEREF_exp(off_ptr_diff_ptr2(off));
		TYPE s1 = DEREF_type(exp_type(a));
		TYPE s2 = expand_type(s1, 1);
		a = copy_exp(a, s1, s2);
		b = copy_exp(b, s1, s2);
		MAKE_off_ptr_diff(a, b, off);
		break;
	}
	case off_token_tag: {
		/* Offset tokens */
		IDENTIFIER tok = DEREF_id(off_token_tok(off));
		LIST(TOKEN)args = DEREF_list(off_token_args(off));
		tok = DEREF_id(id_alias(tok));
		args = expand_args(args, 1, 1);
		off = apply_mem_token(tok, args);
		break;
	}
	}
	return off;
}


/*
    This routine copies the list of offsets p.
*/

static LIST(OFFSET)
copy_off_list(LIST(OFFSET) p)
{
	LIST(OFFSET)q = NULL_list(OFFSET);
	while (!IS_NULL_list(p)) {
		OFFSET off = DEREF_off(HEAD_list(p));
		off = copy_offset(off, lex_plus);
		CONS_off(off, q, q);
		p = TAIL_list(p);
	}
	return REVERSE_list(q);
}


/*
    This routine copies the list of expressions p.
*/

LIST(EXP)
copy_exp_list(LIST(EXP) p, TYPE t1, TYPE t2)
{
	LIST(EXP)q = NULL_list(EXP);
	while (!IS_NULL_list(p)) {
		EXP e = DEREF_exp(HEAD_list(p));
		e = copy_exp(e, t1, t2);
		CONS_exp(e, q, q);
		p = TAIL_list(p);
	}
	return REVERSE_list(q);
}


/*
    This routine copies the function expression e.  Any name look-ups
    are postponed until make_func_exp.
*/

EXP
copy_func_exp(EXP e, TYPE t1, TYPE t2)
{
	if (!IS_NULL_exp(e)) {
		unsigned tag = TAG_exp(e);
		TYPE t = DEREF_type(exp_type(e));
		if (!EQ_type(t, t1)) {
			/* Expand type if necessary */
			t1 = t;
			t2 = expand_type(t, 1);
		}
		switch (tag) {
		case exp_identifier_tag:
		case exp_member_tag:
		case exp_ambiguous_tag: {
			/* Identifier expressions */
			IDENTIFIER id;
			QUALIFIER qual;
			id = DEREF_id(exp_identifier_etc_id(e));
			qual = DEREF_qual(exp_identifier_etc_qual(e));
			MAKE_exp_identifier_etc(tag, t2, id, qual, e);
			break;
		}
		case exp_undeclared_tag: {
			/* Undeclared identifiers */
			IDENTIFIER id;
			QUALIFIER qual;
			id = DEREF_id(exp_undeclared_id(e));
			qual = DEREF_qual(exp_undeclared_qual(e));
			MAKE_exp_identifier(type_func_void, id, qual, e);
			break;
		}
		case exp_paren_tag: {
			/* Parenthesised expressions */
			EXP a = DEREF_exp(exp_paren_arg(e));
			a = copy_func_exp(a, t1, t2);
			if (!IS_NULL_exp(a)) {
				t2 = DEREF_type(exp_type(a));
			}
			MAKE_exp_paren(t2, a, e);
			break;
		}
		case exp_address_tag: {
			/* Address expressions */
			EXP a = DEREF_exp(exp_address_arg(e));
			a = copy_func_exp(a, t1, t2);
			MAKE_exp_address(t2, a, e);
			break;
		}
		case exp_address_mem_tag: {
			/* Member address expressions */
			EXP a = DEREF_exp(exp_address_mem_arg(e));
			int paren = DEREF_int(exp_address_mem_paren(e));
			a = copy_func_exp(a, t1, t2);
			MAKE_exp_address_mem(t2, a, paren, e);
			break;
		}
		case exp_op_tag: {
			/* Check for undetermined address expressions */
			int op = DEREF_int(exp_op_lex(e));
			EXP a = DEREF_exp(exp_op_arg1(e));
			EXP b = DEREF_exp(exp_op_arg2(e));
			if (op == lex_and_H1 && IS_NULL_exp(b)) {
				a = copy_func_exp(a, t1, t2);
				e = make_ref_exp(a, 0);
				break;
			}
			e = copy_exp(e, t1, t2);
			break;
		}
		default : {
			/* Other expressions */
			e = copy_exp(e, t1, t2);
			break;
		}
		}
	}
	return e;
}


/*
    This routine copies the list of function arguments p.  id gives the
    function name (for error reporting purposes).
*/

static LIST(EXP)
copy_func_args(LIST(EXP)p, IDENTIFIER id)
{
	unsigned n = 1;
	LIST(EXP)q = NULL_list(EXP);
	while (!IS_NULL_list(p)) {
		EXP e = DEREF_exp(HEAD_list(p));
		EXP a = implicit_cast_exp(e);
		if (!IS_NULL_exp(a)) {
			/* Do implicit argument conversion */
			TYPE t;
			ERROR err = NULL_err;
			a = copy_exp(a, NULL_type, NULL_type);
			t = DEREF_type(exp_type(a));
			e = init_assign(t, cv_none, a, &err);
			if (!IS_NULL_err(err)) {
				err = init_error(err, 0);
				err = concat_error(err, ERR_expr_call_arg(n));
				if (!IS_NULL_id(id)) {
					err = concat_error(ERR_expr_call_func(id), err);
				}
				report(crt_loc, err);
			}
		} else {
			/* Simple argument copy */
			e = copy_exp(e, NULL_type, NULL_type);
		}
		CONS_exp(e, q, q);
		n++;
		p = TAIL_list(p);
	}
	return REVERSE_list(q);
}


/*
    This routine finds the copy of the label lab in the current label
    namespace, copying it if necessary.  If def is true then the labelled
    statement is also copied.
*/

static IDENTIFIER
copy_label(IDENTIFIER lab, int def)
{
	IDENTIFIER nlab = lab;
	if (!IS_NULL_id(nlab)) {
		NAMESPACE ns = label_namespace;
		if (!IS_NULL_nspace(ns)) {
			/* Look up name in label namespace */
			HASHID nm = DEREF_hashid(id_name(lab));
			MEMBER mem = search_member(ns, nm, 1);
			nlab = DEREF_id(member_id(mem));
			if (IS_NULL_id(nlab)) {
				/* Create new label */
				int op = DEREF_int(id_label_op(lab));
				IDENTIFIER alab = DEREF_id(id_alias(lab));
				DECL_SPEC ds = DEREF_dspec(id_storage(lab));
				DEREF_loc(id_loc(lab), crt_loc);
				ds &= ~dspec_temp;
				MAKE_id_label(nm, ds, ns, crt_loc, op, nlab);
				if (!EQ_id(lab, alab)) {
					alab = copy_label(alab, 0);
					COPY_id(id_alias(nlab), alab);
				}
				COPY_id(member_id(mem), nlab);
			}
		}
		if (def) {
			EXP e = DEREF_exp(id_label_stmt(lab));
			if (!IS_NULL_exp(e)) {
				/* Copy labelled statement */
				TYPE t = DEREF_type(exp_type(e));
				EXP a = DEREF_exp(exp_label_stmt_body(e));
				IDENTIFIER elab =
				    DEREF_id(exp_label_stmt_next(e));
				elab = copy_label(elab, 0);
				a = copy_exp(a, type_void, type_void);
				MAKE_exp_label_stmt(t, nlab, a, e);
				COPY_id(exp_label_stmt_next(e), elab);
				COPY_exp(id_label_stmt(nlab), e);
				set_parent_stmt(a, e);
			}
			DEREF_loc(id_loc(lab), crt_loc);
		}
	}
	return nlab;
}


/*
    This routine sets the join field for all jumps to the label lab to
    be e.
*/

static void
set_jump_joins(IDENTIFIER lab, EXP e)
{
	EXP a = DEREF_exp(id_label_gotos(lab));
	while (!IS_NULL_exp(a) && IS_exp_goto_stmt(a)) {
		COPY_exp(exp_goto_stmt_join(a), e);
		a = DEREF_exp(exp_goto_stmt_next(a));
	}
	return;
}


/*
    This routine copies the switch statement e.
*/

static EXP
copy_switch_stmt(EXP e, TYPE t1, TYPE t2)
{
	/* Decompose switch statement */
	int changed = 0;
	LIST(NAT)an = NULL_list(NAT);
	LIST(IDENTIFIER)al = NULL_list(IDENTIFIER);
	EXP c = DEREF_exp(exp_switch_stmt_control(e));
	EXP a = DEREF_exp(exp_switch_stmt_body(e));
	int exhaust = DEREF_int(exp_switch_stmt_exhaust(e));
	IDENTIFIER blab = DEREF_id(exp_switch_stmt_break_lab(e));
	IDENTIFIER dlab = DEREF_id(exp_switch_stmt_default_lab(e));
	LIST(NAT)cn = DEREF_list(exp_switch_stmt_cases(e));
	LIST(IDENTIFIER)cl = DEREF_list(exp_switch_stmt_case_labs(e));

	/* Copy basic components */
	c = copy_exp(c, type_sint, type_sint);
	blab = copy_label(blab, 1);
	a = copy_exp(a, t1, t2);
	MAKE_exp_switch_stmt(t2, c, a, exhaust, blab, e);
	set_jump_joins(blab, e);
	set_parent_stmt(a, e);

	/* Copy cases */
	while (!IS_NULL_list(cn)) {
		ERROR err = NULL_err;
		NAT n = DEREF_nat(HEAD_list(cn));
		IDENTIFIER clab = DEREF_id(HEAD_list(cl));
		NAT m = expand_nat(n, 1, 0, &err);
		if (!EQ_nat(n, m)) {
			if (!IS_NULL_err(err)) {
				err = concat_error(err, ERR_stmt_switch_case_const());
				report(crt_loc, err);
			}
			changed = 1;
		}
		clab = copy_label(clab, 0);
		COPY_exp(id_label_gotos(clab), e);
		if (changed) {
			IDENTIFIER plab = find_case(an, al, m);
			if (!IS_NULL_id(plab) && !is_error_nat(m)) {
				/* New duplicate case created */
				LOCATION loc;
				PTR(LOCATION)ploc = id_loc(plab);
				DEREF_loc(id_loc(clab), loc);
				report(loc, ERR_stmt_switch_case_dup(m, ploc));
			}
		}
		CONS_id(clab, al, al);
		CONS_nat(m, an, an);
		cl = TAIL_list(cl);
		cn = TAIL_list(cn);
	}
	an = REVERSE_list(an);
	al = REVERSE_list(al);
	COPY_list(exp_switch_stmt_cases(e), an);
	COPY_list(exp_switch_stmt_case_labs(e), al);
	if (!IS_NULL_id(dlab)) {
		dlab = copy_label(dlab, 0);
		COPY_exp(id_label_gotos(dlab), e);
		COPY_id(exp_switch_stmt_default_lab(e), dlab);
	}
	e = solve_switch (e);
	return e;
}


/*
    This routine copies the try block e.
*/

#if LANGUAGE_CPP

static EXP
copy_try_stmt(EXP e, TYPE t1, TYPE t2)
{
	int empty = 1;
	int changed = 0;
	EXP a = DEREF_exp(exp_try_block_body(e));
	LIST(EXP)h = DEREF_list(exp_try_block_handlers(e));
	LIST(TYPE)s = DEREF_list(exp_try_block_htypes(e));
	LIST(TYPE)t = DEREF_list(exp_try_block_ttypes(e));
	LIST(LOCATION)tl = DEREF_list(exp_try_block_tlocs(e));
	LIST(LOCATION)sl = NULL_list(LOCATION);
	EXP b = DEREF_exp(exp_try_block_ellipsis(e));
	int func = DEREF_int(exp_try_block_func(e));
	e = begin_try_stmt(func);
	t = expand_exceptions(t, 1, &changed);
	while (!IS_NULL_list(tl)) {
		LOCATION loc;
		DEREF_loc(HEAD_list(tl), loc);
		CONS_loc(loc, sl, sl);
		tl = TAIL_list(tl);
	}
	sl = REVERSE_list(sl);
	COPY_list(exp_try_block_ttypes(e), t);
	COPY_list(exp_try_block_tlocs(e), sl);
	a = copy_exp(a, t1, t2);
	e = cont_try_stmt(e, a);
	h = copy_exp_list(h, t1, t2);
	s = expand_exceptions(s, 1, &changed);
	b = copy_exp(b, t1, t2);
	COPY_list(exp_try_block_handlers(e), h);
	COPY_list(exp_try_block_htypes(e), s);
	COPY_exp(exp_try_block_ellipsis(e), b);
	while (!IS_NULL_list(h)) {
		EXP c = DEREF_exp(HEAD_list(h));
		set_parent_stmt(c, e);
		empty = 0;
		h = TAIL_list(h);
	}
	set_parent_stmt(b, e);
	if (!IS_NULL_exp(b) && IS_exp_handler(b)) {
		empty = 0;
	}
	e = end_try_stmt(e, empty);
	return e;
}

#endif


/*
    This routine copies the object id declared in block scope.  This is
    primarily to handle local classes and the like, local variables being
    handled by copy_local when their declaration is encountered.
*/

static void
copy_local_decl(IDENTIFIER id)
{
	switch (TAG_id(id)) {
	case id_variable_tag: {
		/* Local variable declaration */
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_linkage) {
			IDENTIFIER pid;
			TYPE t = DEREF_type(id_variable_type(id));
			t = expand_type(t, 1);
			pid = make_object_decl(dspec_extern, t, id, 0);
			pid = DEREF_id(id_alias(pid));
			COPY_id(id_alias(id), pid);
		}
		break;
	}
	case id_function_tag: {
		/* Local function declaration */
		IDENTIFIER pid;
		TYPE t = DEREF_type(id_function_type(id));
		IDENTIFIER over = DEREF_id(id_function_over(id));
		if (!IS_NULL_id(over)) {
			copy_local_decl(over);
		}
		t = expand_type(t, 1);
		pid = make_func_decl(dspec_extern, t, id, 0);
		pid = DEREF_id(id_alias(pid));
		COPY_id(id_alias(id), pid);
		break;
	}
	case id_class_name_tag: {
		/* Local class */
		TYPE t = DEREF_type(id_class_name_defn(id));
		if (IS_type_compound(t)) {
			/* Can't be a template class */
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
			if (ci & cinfo_force_copy) {
				TYPE s;
				CLASS_TYPE cs;
				COPY_type(ctype_form(ct), NULL_type);
				s = copy_class(t, dspec_none);
				cs = DEREF_ctype(type_compound_defn(s));
				COPY_type(ctype_form(ct), s);
				copy_members(cs, ct, cinfo_none, 1);
			}
		}
		break;
	}
	case id_enumerator_tag:
		/* Check enumerator values */
		IGNORE copy_id(id, 2);
		break;
	}
	return;
}


/*
    This routine copies the compound statement e.
*/

static EXP
copy_compound_stmt(EXP e, TYPE t1, TYPE t2)
{
	int block = DEREF_int(exp_sequence_block(e));
	NAMESPACE pns = DEREF_nspace(exp_sequence_decl(e));
	LIST(EXP)p = DEREF_list(exp_sequence_first(e));

	/* Copy the dummy first statement */
	LIST(EXP)q;
	EXP a = DEREF_exp(HEAD_list(p));
	if (!IS_NULL_exp(a)) {
		a = copy_exp(a, t1, t2);
	}
	CONS_exp(a, NULL_list(EXP), q);
	p = TAIL_list(p);

	/* Create the compound statement */
	MAKE_exp_sequence(t2, q, q, NULL_nspace, block, e);
	if (!IS_NULL_list(p)) {
		/* Construct namespace for copied block */
		MEMBER mem = NULL_member;
		NAMESPACE ns = make_namespace(crt_func_id, nspace_block_tag, 0);
		COPY_nspace(exp_sequence_decl(e), ns);
		push_namespace(ns);

		/* Copy members of block namespace */
		if (!IS_NULL_nspace(pns)) {
			MEMBER mem2 = DEREF_member(nspace_last(pns));
			while (!IS_NULL_member(mem2)) {
				IDENTIFIER id = DEREF_id(member_id(mem2));
				IDENTIFIER alt = DEREF_id(member_alt(mem2));
				if (!IS_NULL_id(id)) {
					copy_local_decl(id);
				}
				if (!IS_NULL_id(alt) && !EQ_id(id, alt)) {
					copy_local_decl(alt);
				}
				mem2 = DEREF_member(member_next(mem2));
			}
		}

		/* Copy list of components */
		while (!IS_NULL_list(p)) {
			MEMBER mem2;
			LIST(EXP)r;
			a = DEREF_exp(HEAD_list(p));
			a = copy_exp(a, t1, t2);
			mem2 = DEREF_member(nspace_last(ns));
			if (!EQ_member(mem2, mem)) {
				/* Introduced new temporary variables */
				a = make_temp_decl(mem2, mem, a);
				mem = mem2;
			}
			set_parent_stmt(a, e);
			CONS_exp(a, NULL_list(EXP), r);
			COPY_list(PTR_TAIL_list(q), r);
			q = r;
			p = TAIL_list(p);
		}

		/* Update compound statement */
		IGNORE pop_namespace();
		COPY_member(nspace_prev(ns), mem);
		COPY_list(exp_sequence_last(e), q);
	}
	return e;
}


/*
    Dummy expressions are used to point to a component of a complex
    expression.  These lists are used to hold all the dummy expressions to
    be copied by copy_exp.  They are updated as they are copied.
*/

static LIST(EXP) input_dummy_exps = NULL_list(EXP);
static LIST(EXP) output_dummy_exps = NULL_list(EXP);


/*
    This routine adds the expression e to the lists of dummy expressions.
*/

static void
save_dummy_exp(EXP e)
{
	CONS_exp(e, input_dummy_exps, input_dummy_exps);
	CONS_exp(NULL_exp, output_dummy_exps, output_dummy_exps);
	return;
}


/*
    This routine removes an expression from the lists of dummy expressions.
    It returns the copied values.
*/

static EXP
restore_dummy_exp(void)
{
	EXP a, b;
	DESTROY_CONS_exp(destroy, a, input_dummy_exps, input_dummy_exps);
	DESTROY_CONS_exp(destroy, b, output_dummy_exps, output_dummy_exps);
	if (IS_NULL_exp(b) && !IS_NULL_exp(a)) {
		/* Do a straight copy if not copied already */
		b = copy_exp(a, NULL_type, NULL_type);
	}
	return b;
}


/*
    This routine copies the dummy expression e, including updating the lists
    of dummy expressions.
*/

static EXP
copy_dummy_exp(EXP e, TYPE t1, TYPE t2)
{
	EXP f;
	LIST(EXP)p = input_dummy_exps;
	LIST(EXP)q = output_dummy_exps;
	EXP a = DEREF_exp(exp_dummy_value(e));
	ulong_type no = DEREF_ulong(exp_dummy_no(e));
	OFFSET off = DEREF_off(exp_dummy_off(e));
	int virt = DEREF_int(exp_dummy_virt(e));
	int cont = DEREF_int(exp_dummy_cont(e));
	a = copy_exp(a, t1, t2);
	off = copy_offset(off, lex_plus);
	MAKE_exp_dummy(t2, a, no, off, cont, f);
	COPY_int(exp_dummy_virt(f), virt);
	while (!IS_NULL_list(p)) {
		EXP b = DEREF_exp(HEAD_list(p));
		if (EQ_exp(b, e)) {
			/* Update output lists */
			COPY_exp(HEAD_list(q), f);
		}
		q = TAIL_list(q);
		p = TAIL_list(p);
	}
	return f;
}


/*
    This routine copies the expression e, expanding any template parameters
    and tokens.  It is used in the instantiation of template functions.
    t1 and t2 are used to prevent repeated type expansions.  t1 gives the
    previous expression type and t2 gives its expanded form.
*/

EXP
copy_exp(EXP e, TYPE t1, TYPE t2)
{
	TYPE t;
	unsigned tag;
	if (IS_NULL_exp(e)) {
		return NULL_exp;
	}
	t = DEREF_type(exp_type(e));
	if (!EQ_type(t, t1)) {
		/* Expand type if necessary */
		t1 = t;
		t2 = expand_type(t, 1);
	}
	assert(ORDER_exp == 88);
	tag = TAG_exp(e);
	switch (tag) {
	case exp_identifier_tag:
	case exp_member_tag:
	case exp_ambiguous_tag: {
		/* Identifier expressions */
		IDENTIFIER id = DEREF_id(exp_identifier_etc_id(e));
		QUALIFIER qual = DEREF_qual(exp_identifier_etc_qual(e));
		id = DEREF_id(id_alias(id));
		id = rescan_member(id);
		MAKE_exp_identifier_etc(tag, t2, id, qual, e);
		break;
	}
	case exp_undeclared_tag: {
		/* Undeclared identifier expressions */
		IDENTIFIER id = DEREF_id(exp_undeclared_id(e));
		QUALIFIER qual = DEREF_qual(exp_undeclared_qual(e));
		id = rescan_id(id, qual, 0);
		crt_id_qualifier = qual;
		e = make_id_exp(id);
		break;
	}
	case exp_int_lit_tag: {
		/* Integer literals */
		ERROR err = NULL_err;
		NAT n = DEREF_nat(exp_int_lit_nat(e));
		unsigned etag = DEREF_unsigned(exp_int_lit_etag(e));
		n = expand_nat(n, 1, 0, &err);
		if (!IS_NULL_err(err)) {
			report(crt_loc, err);
		}
		MAKE_exp_int_lit(t2, n, etag, e);
		break;
	}
	case exp_float_lit_tag: {
		/* Floating point literals */
		FLOAT flt = DEREF_flt(exp_float_lit_flt(e));
		MAKE_exp_float_lit(t2, flt, e);
		break;
	}
	case exp_char_lit_tag: {
		/* Character literals */
		STRING str = DEREF_str(exp_char_lit_str(e));
		int digit = DEREF_int(exp_char_lit_digit(e));
		MAKE_exp_char_lit(t2, str, digit, e);
		break;
	}
	case exp_string_lit_tag: {
		/* String literals */
		STRING str = DEREF_str(exp_string_lit_str(e));
		MAKE_exp_string_lit(t2, str, e);
		break;
	}
	case exp_value_tag: {
		/* Uninitiated expressions */
		MAKE_exp_value(t2, e);
		break;
	}
	case exp_null_tag: {
		/* Null expressions */
		MAKE_exp_null(t2, e);
		break;
	}
	case exp_zero_tag: {
		/* Zero expressions */
		MAKE_exp_zero(t2, e);
		break;
	}
	case exp_paren_tag: {
		/* Parenthesised expressions */
		EXP a = DEREF_exp(exp_paren_arg(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_paren(t2, a, e);
		break;
	}
	case exp_copy_tag: {
		/* Copy expressions */
		EXP a = DEREF_exp(exp_copy_arg(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_copy(t2, a, e);
		break;
	}
	case exp_assign_tag: {
		/* Assignment expressions */
		EXP a = DEREF_exp(exp_assign_ref(e));
		EXP b = DEREF_exp(exp_assign_arg(e));
		a = copy_exp(a, t1, t2);
		b = copy_exp(b, t1, t2);
		MAKE_exp_assign(t2, a, b, e);
		break;
	}
	case exp_init_tag: {
		/* Initialisation expressions */
		IDENTIFIER id = DEREF_id(exp_init_id(e));
		EXP a = DEREF_exp(exp_init_arg(e));
		id = DEREF_id(id_alias(id));
		a = copy_exp(a, t1, t2);
		MAKE_exp_init(t2, id, a, e);
		break;
	}
	case exp_preinc_tag: {
		/* Pre-increment expressions */
		EXP a = DEREF_exp(exp_preinc_ref(e));
		EXP b = DEREF_exp(exp_preinc_op(e));
		int becomes = DEREF_int(exp_preinc_becomes(e));
		save_dummy_exp(a);
		b = copy_exp(b, t1, t2);
		a = restore_dummy_exp();
		MAKE_exp_preinc(t2, a, b, becomes, e);
		break;
	}
	case exp_postinc_tag: {
		/* Post-increment expressions */
		EXP a = DEREF_exp(exp_postinc_ref(e));
		EXP b = DEREF_exp(exp_postinc_value(e));
		EXP c = DEREF_exp(exp_postinc_op(e));
		save_dummy_exp(a);
		if (!IS_NULL_exp(b)) {
			save_dummy_exp(b);
			c = copy_exp(c, t1, t2);
			b = restore_dummy_exp();
		} else {
			c = copy_exp(c, t1, t2);
		}
		a = restore_dummy_exp();
		MAKE_exp_postinc(t2, a, b, c, e);
		break;
	}
	case exp_indir_tag: {
		/* Indirection expressions */
		EXP a = DEREF_exp(exp_indir_ptr(e));
		int i = DEREF_int(exp_indir_index(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_indir(t2, a, e);
		COPY_int(exp_indir_index(e), i);
		break;
	}
	case exp_contents_tag: {
		/* Contents expressions */
		EXP a = DEREF_exp(exp_contents_ptr(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_contents(t2, a, e);
		break;
	}
	case exp_address_tag: {
		/* Address expressions */
		EXP a = DEREF_exp(exp_address_arg(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_address(t2, a, e);
		break;
	}
	case exp_address_mem_tag: {
		/* Member address expressions */
		EXP a = DEREF_exp(exp_address_mem_arg(e));
		int paren = DEREF_int(exp_address_mem_paren(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_address_mem(t2, a, paren, e);
		break;
	}
	case exp_func_tag: {
		/* Function expresssions */
		EXP a = DEREF_exp(exp_func_fn(e));
		LIST(EXP)args = DEREF_list(exp_func_args(e));
		unsigned extra = DEREF_unsigned(exp_func_extra(e));
		a = copy_exp(a, t1, t2);
		args = copy_func_args(args, NULL_id);
		MAKE_exp_func(t2, a, args, e);
		COPY_unsigned(exp_func_extra(e), extra);
		break;
	}
	case exp_func_id_tag: {
		/* Function expresssions */
		IDENTIFIER id = DEREF_id(exp_func_id_id(e));
		LIST(EXP)args = DEREF_list(exp_func_id_args(e));
		EXP a = DEREF_exp(exp_func_id_virt(e));
		unsigned extra = DEREF_unsigned(exp_func_id_extra(e));
		id = DEREF_id(id_alias(id));
		id = rescan_member(id);
		save_dummy_exp(a);
		args = copy_func_args(args, id);
		a = restore_dummy_exp();
		MAKE_exp_func_id(t2, id, args, a, e);
		COPY_unsigned(exp_func_id_extra(e), extra);
		break;
	}
	case exp_call_tag: {
		/* Member call expressions */
		EXP a = DEREF_exp(exp_call_ptr(e));
		EXP b = DEREF_exp(exp_call_arg(e));
		GRAPH gr = DEREF_graph(exp_call_base(e));
		a = copy_exp(a, t1, t2);
		b = copy_exp(b, t1, t2);
		gr = expand_graph(gr, 1);
		MAKE_exp_call(t2, a, b, gr, e);
		break;
	}
	case exp_negate_tag:
	case exp_compl_tag:
	case exp_not_tag:
	case exp_abs_tag: {
		/* Unary operations */
		EXP a = DEREF_exp(exp_negate_etc_arg(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_negate_etc(tag, t2, a, e);
		break;
	}
	case exp_plus_tag:
	case exp_minus_tag:
	case exp_mult_tag:
	case exp_div_tag:
	case exp_rem_tag:
	case exp_and_tag:
	case exp_or_tag:
	case exp_xor_tag:
	case exp_log_and_tag:
	case exp_log_or_tag:
	case exp_lshift_tag:
	case exp_rshift_tag:
	case exp_max_tag:
	case exp_min_tag: {
		/* Binary operations */
		EXP a = DEREF_exp(exp_plus_etc_arg1(e));
		EXP b = DEREF_exp(exp_plus_etc_arg2(e));
		a = copy_exp(a, t1, t2);
		b = copy_exp(b, t1, t2);
		MAKE_exp_plus_etc(tag, t2, a, b, e);
		break;
	}
	case exp_test_tag: {
		/* Test expressions */
		NTEST tst = DEREF_ntest(exp_test_tst(e));
		EXP a = DEREF_exp(exp_test_arg(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_test(t2, tst, a, e);
		break;
	}
	case exp_compare_tag: {
		/* Comparison expressions */
		NTEST tst = DEREF_ntest(exp_compare_tst(e));
		EXP a = DEREF_exp(exp_compare_arg1(e));
		EXP b = DEREF_exp(exp_compare_arg2(e));
		TYPE s1 = DEREF_type(exp_type(a));
		TYPE s2 = expand_type(s1, 1);
		a = copy_exp(a, s1, s2);
		b = copy_exp(b, s1, s2);
		MAKE_exp_compare(t2, tst, a, b, e);
		break;
	}
	case exp_cast_tag: {
		/* Cast expressions */
		unsigned conv = DEREF_unsigned(exp_cast_conv(e));
		EXP a = DEREF_exp(exp_cast_arg(e));
		a = copy_exp(a, t1, t2);
		if (conv == CONV_EXACT && IS_exp_cast(a)) {
			/* Exact casts are idempotent */
			unsigned conv2 = DEREF_unsigned(exp_cast_conv(a));
			if (conv2 == CONV_EXACT) {
				a = DEREF_exp(exp_cast_arg(a));
			}
		}
		MAKE_exp_cast(t2, conv, a, e);
		break;
	}
	case exp_base_cast_tag: {
		/* Base cast expressions */
		unsigned conv = DEREF_unsigned(exp_base_cast_conv(e));
		EXP a = DEREF_exp(exp_base_cast_arg(e));
		OFFSET off = DEREF_off(exp_base_cast_off(e));
		a = copy_exp(a, t1, t2);
		off = copy_offset(off, lex_plus);
		MAKE_exp_base_cast(t2, conv, a, off, e);
		break;
	}
	case exp_dyn_cast_tag: {
		/* Dynamic cast expressions */
		EXP a = DEREF_exp(exp_dyn_cast_arg(e));
		EXP b = DEREF_exp(exp_dyn_cast_except(e));
		a = copy_exp(a, t1, t2);
		b = copy_exp(b, t1, t2);
		MAKE_exp_dyn_cast(t2, a, b, e);
		break;
	}
	case exp_add_ptr_tag: {
		/* Pointer addition expressions */
		EXP a = DEREF_exp(exp_add_ptr_ptr(e));
		OFFSET off = DEREF_off(exp_add_ptr_off(e));
		int virt = DEREF_int(exp_add_ptr_virt(e));
		a = copy_exp(a, t1, t2);
		off = copy_offset(off, lex_plus);
		MAKE_exp_add_ptr(t2, a, off, virt, e);
		break;
	}
	case exp_offset_size_tag: {
		/* Offset division expressions */
		OFFSET off = DEREF_off(exp_offset_size_off(e));
		TYPE s = DEREF_type(exp_offset_size_step(e));
		int pad = DEREF_int(exp_offset_size_pad(e));
		off = copy_offset(off, lex_minus);
		s = copy_type_offset(s, lex_minus);
		MAKE_exp_offset_size(t2, off, s, pad, e);
		break;
	}
	case exp_constr_tag: {
		/* Constructor call expressions */
		EXP a = DEREF_exp(exp_constr_call(e));
		EXP b = DEREF_exp(exp_constr_obj(e));
		EXP c = DEREF_exp(exp_constr_alt(e));
		int info = DEREF_int(exp_constr_info(e));
		save_dummy_exp(b);
		save_dummy_exp(c);
		a = copy_exp(a, t1, t2);
		c = restore_dummy_exp();
		b = restore_dummy_exp();
		MAKE_exp_constr(t2, a, b, c, info, e);
		break;
	}
	case exp_destr_tag: {
		/* Destructor call expressions */
		EXP a = DEREF_exp(exp_destr_call(e));
		EXP b = DEREF_exp(exp_destr_obj(e));
		save_dummy_exp(b);
		a = copy_exp(a, t1, t2);
		b = restore_dummy_exp();
		MAKE_exp_destr(t2, a, b, e);
		break;
	}
	case exp_alloc_tag: {
		/* Allocation call expressions */
		EXP a = DEREF_exp(exp_alloc_call(e));
		EXP b = DEREF_exp(exp_alloc_init(e));
		EXP c = DEREF_exp(exp_alloc_garbage(e));
		EXP d = DEREF_exp(exp_alloc_size(e));
		save_dummy_exp(d);
		a = copy_exp(a, t1, t2);
		b = copy_exp(b, t1, t2);
		c = copy_exp(c, t1, t2);
		d = restore_dummy_exp();
		MAKE_exp_alloc(t2, a, b, c, d, e);
		break;
	}
	case exp_dealloc_tag: {
		/* Deallocation call expressions */
		EXP a = DEREF_exp(exp_dealloc_term(e));
		EXP b = DEREF_exp(exp_dealloc_call(e));
		EXP c = DEREF_exp(exp_dealloc_arg(e));
		EXP d = DEREF_exp(exp_dealloc_size(e));
		save_dummy_exp(c);
		save_dummy_exp(d);
		a = copy_exp(a, t1, t2);
		b = copy_exp(b, t1, t2);
		d = restore_dummy_exp();
		c = restore_dummy_exp();
		MAKE_exp_dealloc(t2, a, b, c, d, e);
		break;
	}
	case exp_rtti_tag: {
		/* Run-time type information expressions */
		EXP a = DEREF_exp(exp_rtti_arg(e));
		EXP b = DEREF_exp(exp_rtti_except(e));
		int op = DEREF_int(exp_rtti_op(e));
		a = copy_exp(a, t1, t2);
		b = copy_exp(b, t1, t2);
		MAKE_exp_rtti(t2, a, b, op, e);
		break;
	}
	case exp_rtti_type_tag: {
		/* Run-time type information expressions */
		TYPE s = DEREF_type(exp_rtti_type_arg(e));
		int op = DEREF_int(exp_rtti_type_op(e));
		s = expand_type(s, 1);
		MAKE_exp_rtti_type(t2, s, op, e);
		break;
	}
	case exp_rtti_no_tag: {
		/* Run-time type information expressions */
		TYPE s = DEREF_type(exp_rtti_no_arg(e));
		s = expand_type(s, 1);
		MAKE_exp_rtti_no(t2, s, e);
		break;
	}
	case exp_dynamic_tag: {
		/* Dynamic initialiser expressions */
		EXP a = DEREF_exp(exp_dynamic_arg(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_dynamic(t2, a, e);
		break;
	}
	case exp_aggregate_tag: {
		/* Aggregate initialisers */
		LIST(EXP)args = DEREF_list(exp_aggregate_args(e));
		LIST(OFFSET)offs = DEREF_list(exp_aggregate_offs(e));
		args = copy_exp_list(args, t1, t2);
		offs = copy_off_list(offs);
		MAKE_exp_aggregate(t2, args, offs, e);
		break;
	}
	case exp_initialiser_tag: {
		/* Constructor initialisers */
		int kind = DEREF_int(exp_initialiser_kind(e));
		if (kind) {
			/* Copy ctor-initialiser */
			e = copy_ctor(e, kind);
		} else {
			unsigned nv, nb;
			LIST(EXP)args;
			LIST(OFFSET)offs;
			args = DEREF_list(exp_initialiser_args(e));
			offs = DEREF_list(exp_initialiser_offs(e));
			nv = DEREF_unsigned(exp_initialiser_virt(e));
			nb = DEREF_unsigned(exp_initialiser_base(e));
			args = copy_exp_list(args, t1, t2);
			offs = copy_off_list(offs);
			MAKE_exp_initialiser(t2, args, offs, kind, nv, nb, e);
		}
		break;
	}
	case exp_nof_tag: {
		/* Array initialisers */
		ERROR err = NULL_err;
		EXP a = DEREF_exp(exp_nof_start(e));
		EXP b = DEREF_exp(exp_nof_pad(e));
		EXP c = DEREF_exp(exp_nof_end(e));
		NAT n = DEREF_nat(exp_nof_size(e));
		NAT m = expand_nat(n, 1, 0, &err);
		a = copy_exp(a, t1, t2);
		if (!EQ_nat(n, m)) {
			if (!IS_NULL_err(err))report(crt_loc, err);
			if (is_zero_nat(m)) {
				/* No extra elements */
				e = a;
				break;
			}
			if (is_negative_nat(m)) {
				/* Number of extra elements has gone negative */
				report(crt_loc, ERR_dcl_init_aggr_excess(t2));
				e = a;
				break;
			}
		}
		b = copy_exp(b, t1, t2);
		c = copy_exp(c, t1, t2);
		MAKE_exp_nof(t2, a, m, b, c, e);
		break;
	}
	case exp_comma_tag: {
		/* Comma expressions */
		LIST(EXP)args = DEREF_list(exp_comma_args(e));
		args = copy_exp_list(args, t1, t2);
		MAKE_exp_comma(t2, args, e);
		break;
	}
	case exp_set_tag: {
		/* Variable set expressions */
		EXP a = DEREF_exp(exp_set_arg(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_set(t2, a, e);
		break;
	}
	case exp_unused_tag: {
		/* Variable unset expressions */
		EXP a = DEREF_exp(exp_unused_arg(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_unused(t2, a, e);
		break;
	}
	case exp_reach_tag: {
		/* Reached statements */
		EXP a = DEREF_exp(exp_reach_body(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_reach(t2, a, e);
		set_parent_stmt(a, e);
		break;
	}
	case exp_unreach_tag: {
		/* Unreached statements */
		EXP a = DEREF_exp(exp_unreach_body(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_unreach(t2, a, e);
		set_parent_stmt(a, e);
		break;
	}
	case exp_sequence_tag: {
		/* Block statements */
		e = copy_compound_stmt(e, t1, t2);
		break;
	}
	case exp_solve_stmt_tag: {
		/* Solve statements */
		EXP a = DEREF_exp(exp_solve_stmt_body(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_solve_stmt(t2, a, e);
		CONS_exp(e, all_solve_stmts, all_solve_stmts);
		set_parent_stmt(a, e);
		break;
	}
	case exp_decl_stmt_tag: {
		/* Declaration statements */
		IDENTIFIER id = DEREF_id(exp_decl_stmt_id(e));
		IDENTIFIER aid = DEREF_id(id_alias(id));
		IDENTIFIER cid = copy_local(id);
		EXP a = DEREF_exp(exp_decl_stmt_body(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_decl_stmt(t2, cid, a, e);
		set_parent_stmt(a, e);
		COPY_id(id_alias(id), aid);
		break;
	}
	case exp_if_stmt_tag: {
		/* Conditional statements */
		EXP c = DEREF_exp(exp_if_stmt_cond(e));
		EXP a = DEREF_exp(exp_if_stmt_true_code(e));
		EXP b = DEREF_exp(exp_if_stmt_false_code(e));
		IDENTIFIER lab = DEREF_id(exp_if_stmt_label(e));
		c = copy_exp(c, type_bool, type_bool);
		lab = copy_label(lab, 1);
		a = copy_exp(a, t1, t2);
		b = copy_exp(b, t1, t2);
		MAKE_exp_if_stmt(t2, c, a, b, lab, e);
		set_parent_stmt(a, e);
		set_parent_stmt(b, e);
		break;
	}
	case exp_while_stmt_tag: {
		/* While statements */
		LIST(IDENTIFIER)pids;
		EXP c = DEREF_exp(exp_while_stmt_cond(e));
		EXP a = DEREF_exp(exp_while_stmt_body(e));
		IDENTIFIER blab = DEREF_id(exp_while_stmt_break_lab(e));
		IDENTIFIER clab = DEREF_id(exp_while_stmt_cont_lab(e));
		IDENTIFIER llab = DEREF_id(exp_while_stmt_loop_lab(e));
		c = copy_exp(c, type_bool, type_bool);
		blab = copy_label(blab, 1);
		clab = copy_label(clab, 1);
		llab = copy_label(llab, 1);
		pids = DEREF_list(exp_while_stmt_cond_id(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_while_stmt(t2, c, blab, clab, llab, e);
		COPY_exp(exp_while_stmt_body(e), a);
		set_jump_joins(blab, e);
		set_jump_joins(clab, e);
		set_parent_stmt(a, e);
		if (!IS_NULL_list(pids)) {
			LIST(IDENTIFIER)qids = NULL_list(IDENTIFIER);
			while (!IS_NULL_list(pids)) {
				IDENTIFIER id = DEREF_id(HEAD_list(pids));
				id = DEREF_id(id_alias(id));
				CONS_id(id, qids, qids);
				pids = TAIL_list(pids);
			}
			qids = REVERSE_list(qids);
			COPY_list(exp_while_stmt_cond_id(e), qids);
		}
		break;
	}
	case exp_do_stmt_tag: {
		/* Do statements */
		EXP c = DEREF_exp(exp_do_stmt_cond(e));
		EXP a = DEREF_exp(exp_do_stmt_body(e));
		IDENTIFIER blab = DEREF_id(exp_do_stmt_break_lab(e));
		IDENTIFIER clab = DEREF_id(exp_do_stmt_cont_lab(e));
		IDENTIFIER llab = DEREF_id(exp_do_stmt_loop_lab(e));
		blab = copy_label(blab, 1);
		clab = copy_label(clab, 1);
		llab = copy_label(llab, 1);
		a = copy_exp(a, t1, t2);
		c = copy_exp(c, type_bool, type_bool);
		MAKE_exp_do_stmt(t2, c, blab, clab, llab, e);
		COPY_exp(exp_do_stmt_body(e), a);
		set_jump_joins(blab, e);
		set_jump_joins(clab, e);
		set_parent_stmt(a, e);
		break;
	}
	case exp_switch_stmt_tag: {
		/* Switch statements */
		e = copy_switch_stmt(e, t1, t2);
		break;
	}
	case exp_hash_if_tag: {
		/* Target dependent conditional statements */
		EXP c = DEREF_exp(exp_hash_if_cond(e));
		EXP a = DEREF_exp(exp_hash_if_true_code(e));
		EXP b = DEREF_exp(exp_hash_if_false_code(e));
		c = copy_exp(c, type_bool, type_bool);
		a = copy_exp(a, t1, t2);
		b = copy_exp(b, t1, t2);
		MAKE_exp_hash_if (t2, c, a, b, e);
		set_parent_stmt(a, e);
		set_parent_stmt(b, e);
		break;
	}
	case exp_return_stmt_tag: {
		/* Return statements */
		EXP a = DEREF_exp(exp_return_stmt_value(e));
		EXP b = implicit_cast_exp(a);
		if (!IS_NULL_exp(b)) {
			IDENTIFIER lab = NULL_id;
			b = copy_exp(b, t1, t2);
			a = find_return_exp(b, &lab, lex_return);
		} else {
			a = copy_exp(a, t1, t2);
		}
		MAKE_exp_return_stmt(t2, a, e);
		break;
	}
	case exp_goto_stmt_tag: {
		/* Goto statements */
		IDENTIFIER lab = DEREF_id(exp_goto_stmt_label(e));
		lab = copy_label(lab, 0);
		e = make_jump_stmt(lab, NULL_exp);
		break;
	}
	case exp_label_stmt_tag: {
		/* Labelled statements */
		IDENTIFIER lab = DEREF_id(exp_label_stmt_label(e));
		lab = copy_label(lab, 1);
		e = DEREF_exp(id_label_stmt(lab));
		break;
	}
#if LANGUAGE_CPP
	case exp_try_block_tag: {
		/* Try blocks */
		e = copy_try_stmt(e, t1, t2);
		break;
	}
	case exp_handler_tag: {
		/* Exception handlers */
		IDENTIFIER id = DEREF_id(exp_handler_except(e));
		IDENTIFIER aid = DEREF_id(id_alias(id));
		IDENTIFIER cid = copy_local(id);
		EXP a = DEREF_exp(exp_handler_body(e));
		a = copy_exp(a, t1, t2);
		MAKE_exp_handler(t2, cid, a, e);
		set_parent_stmt(a, e);
		COPY_id(id_alias(id), aid);
		break;
	}
	case exp_exception_tag: {
		/* Exception expressions */
		EXP a = DEREF_exp(exp_exception_arg(e));
		EXP b = DEREF_exp(exp_exception_size(e));
		EXP c = DEREF_exp(exp_exception_destr(e));
		int expl = DEREF_int(exp_exception_expl(e));
		a = copy_exp(a, t1, t2);
		b = copy_exp(b, t1, t2);
		c = copy_exp(c, t1, t2);
		MAKE_exp_exception(t2, a, b, c, expl, e);
		break;
	}
	case exp_thrown_tag: {
		/* Thrown expressions */
		int d = DEREF_int(exp_thrown_done(e));
		MAKE_exp_thrown(t2, d, e);
		break;
	}
#endif
	case exp_op_tag: {
		/* Undetermined expressions */
		int op = DEREF_int(exp_op_lex(e));
		EXP a = DEREF_exp(exp_op_arg1(e));
		EXP b = DEREF_exp(exp_op_arg2(e));
		if (IS_NULL_exp(b)) {
			e = apply_unary(op, a, t1, t2, 1);
		} else {
			e = apply_binary(op, a, b, t1, t2, 1);
		}
		break;
	}
	case exp_opn_tag: {
		/* Undetermined expressions */
		int op = DEREF_int(exp_opn_lex(e));
		LIST(EXP)args = DEREF_list(exp_opn_args(e));
		e = apply_nary(op, args, t1, t2, 1);
		break;
	}
	case exp_assembler_tag: {
		/* Assembler expressions */
		STRING op = DEREF_str(exp_assembler_op(e));
		LIST(EXP)args = DEREF_list(exp_assembler_args(e));
		args = copy_exp_list(args, t1, t2);
		MAKE_exp_assembler(t2, op, args, e);
		break;
	}
	case exp_uncompiled_tag: {
		/* Uncompiled expressions */
		PPTOKEN *p = DEREF_pptok(exp_uncompiled_defn(e));
		DEREF_loc(exp_uncompiled_start(e), crt_loc);
		MAKE_exp_uncompiled(t2, crt_loc, p, e);
		break;
	}
	case exp_location_tag: {
		/* Location expressions */
		EXP a = DEREF_exp(exp_location_arg(e));
		a = copy_exp(a, t1, t2);
		DEREF_loc(exp_location_end(e), crt_loc);
		MAKE_exp_location(t2, crt_loc, a, e);
		break;
	}
	case exp_fail_tag: {
		/* Installer error expressions */
		string msg = DEREF_string(exp_fail_msg(e));
		MAKE_exp_fail(t2, msg, e);
		break;
	}
	case exp_dummy_tag: {
		/* Dummy expressions */
		e = copy_dummy_exp(e, t1, t2);
		break;
	}
	case exp_token_tag: {
		/* Expression tokens */
		e = expand_exp(e, 1, 0);
		break;
	}
	}
	return e;
}


/*
    This routine evaluates the integer constant expression e, expanding
    any template parameters and tokens.  If ch is true then any character
    literals are replaced by their ASCII values.
*/

EXP
eval_exp(EXP e, int ch)
{
	unsigned tag;
	if (IS_NULL_exp(e)) {
		return NULL_exp;
	}
	assert(ORDER_exp == 88);
	tag = TAG_exp(e);
	switch (tag) {
	case exp_int_lit_tag: {
		/* Integer literals */
		ERROR err = NULL_err;
		NAT n1 = DEREF_nat(exp_int_lit_nat(e));
		NAT n2 = expand_nat(n1, 1, ch, &err);
		if (!EQ_nat(n1, n2)) {
			TYPE t;
			unsigned etag = DEREF_unsigned(exp_int_lit_etag(e));
			if (!IS_NULL_err(err)) {
				report(crt_loc, err);
			}
			if (IS_nat_calc(n2)) {
				if (etag == exp_identifier_tag) {
					break;
				}
				e = DEREF_exp(nat_calc_value(n2));
				if (IS_exp_int_lit(e)) {
					break;
				}
			}
			t = DEREF_type(exp_type(e));
			t = expand_type(t, 1);
			MAKE_exp_int_lit(t, n2, etag, e);
		}
		break;
	}
	case exp_char_lit_tag: {
		/* Character literals */
		if (ch) {
			TYPE t = DEREF_type(exp_type(e));
			STRING s = DEREF_str(exp_char_lit_str(e));
			NAT n = eval_char_lit(s);
			if (check_nat_range(t, n)!= 0) {
				/* n may not fit into t */
				TYPE u = find_char_type(n);
				MAKE_exp_int_lit(u, n, tag, e);
				MAKE_exp_cast(t, CONV_INT_INT, e, e);
				MAKE_nat_calc(e, n);
				tag = exp_cast_tag;
			}
			MAKE_exp_int_lit(t, n, tag, e);
		} else {
			e = copy_exp(e, NULL_type, NULL_type);
		}
		break;
	}
	case exp_paren_tag: {
		/* Parenthesised expressions */
		EXP a = DEREF_exp(exp_paren_arg(e));
		e = eval_exp(a, ch);
		break;
	}
	case exp_negate_tag:
	case exp_compl_tag:
	case exp_not_tag:
	case exp_abs_tag: {
		/* Unary operations */
		EXP a1 = DEREF_exp(exp_negate_etc_arg(e));
		EXP a2 = eval_exp(a1, ch);
		if (!EQ_exp(a1, a2)) {
			int op = op_token(e, lex_unknown);
			e = apply_unary(op, a2, NULL_type, NULL_type, 0);
		}
		break;
	}
	case exp_plus_tag:
	case exp_minus_tag:
	case exp_mult_tag:
	case exp_div_tag:
	case exp_rem_tag:
	case exp_and_tag:
	case exp_or_tag:
	case exp_xor_tag:
	case exp_log_and_tag:
	case exp_log_or_tag:
	case exp_lshift_tag:
	case exp_rshift_tag:
	case exp_max_tag:
	case exp_min_tag: {
		/* Binary operations */
		EXP a1 = DEREF_exp(exp_plus_etc_arg1(e));
		EXP b1 = DEREF_exp(exp_plus_etc_arg2(e));
		EXP a2 = eval_exp(a1, ch);
		EXP b2 = eval_exp(b1, ch);
		if (!EQ_exp(a1, a2) || !EQ_exp(b1, b2)) {
			int op = op_token(e, lex_unknown);
			e = apply_binary(op, a2, b2, NULL_type, NULL_type, 0);
		}
		break;
	}
	case exp_test_tag: {
		/* Test expressions */
		EXP a1 = DEREF_exp(exp_test_arg(e));
		EXP a2 = eval_exp(a1, ch);
		if (!EQ_exp(a1, a2)) {
			int op = op_token(e, lex_unknown);
			TYPE t2 = DEREF_type(exp_type(a2));
			EXP b2 = make_null_exp(t2);
			e = apply_binary(op, a2, b2, NULL_type, NULL_type, 0);
		}
		break;
	}
	case exp_compare_tag: {
		/* Comparison expressions */
		EXP a1 = DEREF_exp(exp_compare_arg1(e));
		EXP b1 = DEREF_exp(exp_compare_arg2(e));
		EXP a2 = eval_exp(a1, ch);
		EXP b2 = eval_exp(b1, ch);
		if (!EQ_exp(a1, a2) || !EQ_exp(b1, b2)) {
			int op = op_token(e, lex_unknown);
			e = apply_binary(op, a2, b2, NULL_type, NULL_type, 0);
		}
		break;
	}
	case exp_cast_tag: {
		/* Cast expressions */
		unsigned conv = DEREF_unsigned(exp_cast_conv(e));
		EXP a1 = DEREF_exp(exp_cast_arg(e));
		EXP a2 = eval_exp(a1, ch);
		if (!EQ_exp(a1, a2) || conv == CONV_ENUM) {
			ERROR err = NULL_err;
			TYPE t = DEREF_type(exp_type(e));
			t = expand_type(t, 1);
			a2 = convert_reference(a2, REF_ASSIGN);
			e = cast_exp(t, a2, &err, CAST_STATIC);
			if (!IS_NULL_err(err)) {
				err = concat_warning(err, ERR_expr_cast_expl_bad());
				report(crt_loc, err);
			}
		}
		break;
	}
	case exp_offset_size_tag: {
		/* Offset division expressions */
		OFFSET off = DEREF_off(exp_offset_size_off(e));
		TYPE s = DEREF_type(exp_offset_size_step(e));
		if (IS_off_type(off) && EQ_type(s, type_char)) {
			TYPE t1 = DEREF_type(off_type_type(off));
			TYPE t2 = expand_type(t1, 1);
			if (!EQ_type(t1, t2)) {
				/* Evaluate sizeof expressions */
				e = make_sizeof_exp(t2, NULL_exp, 0,
						    lex_sizeof);
			}
		}
		break;
	}
	case exp_if_stmt_tag: {
		/* Conditional statements */
		EXP c1 = DEREF_exp(exp_if_stmt_cond(e));
		EXP a1 = DEREF_exp(exp_if_stmt_true_code(e));
		EXP b1 = DEREF_exp(exp_if_stmt_false_code(e));
		EXP c2 = eval_exp(c1, ch);
		EXP a2 = eval_exp(a1, ch);
		EXP b2 = eval_exp(b1, ch);
		if (!EQ_exp(c1, c2) ||
		    !EQ_exp(a1, a2) || !EQ_exp(b1, b2)) {
			e = make_cond_exp(c2, a2, b2);
		}
		break;
	}
	default : {
		/* Other expressions */
		EXP f = copy_exp(e, NULL_type, NULL_type);
		if (!EQ_exp(f, e) && !eq_exp_exact(f, e)) {
			e = f;
		}
		break;
	}
	}
	return e;
}


/*
    This defines the object id to be a copy of the expression e.  It
    is used in the instantiation of template functions and static data
    members of template classes.
*/

void
copy_object(IDENTIFIER id, EXP e)
{
	if (!IS_NULL_exp(e)) {
		int r = record_location;
		record_location = 0;
		begin_declarator(id, qual_none, NULL_nspace, 0);
		switch (TAG_id(id)) {
		case id_function_tag:
		case id_mem_func_tag:
		case id_stat_mem_func_tag: {
			/* Functions */
			TYPE fn = DEREF_type(id_function_etc_type(id));
			in_function_defn++;
			really_in_function_defn++;
			IGNORE begin_templ_scope(fn);
			begin_function(id);
			e = copy_exp(e, type_bottom, type_bottom);
			IGNORE pop_namespace();
			unreached_code = 1;
			IGNORE end_function(id, e);
			end_templ_scope(fn);
			really_in_function_defn--;
			in_function_defn--;
			break;
		}
		case id_stat_member_tag: {
			/* Static data members */
			copy_variable(id, e);
			if (!in_template_decl) {
				compile_variable(id, 0);
			}
			if (do_dump) {
				dump_declare(id, &crt_loc, 1);
			}
			break;
		}
		case id_class_name_tag: {
			/* Nested template classes */
			CLASS_TYPE ct, cs;
			TYPE t = DEREF_type(id_class_name_defn(id));
			TYPE s = DEREF_type(exp_type(e));
			while (IS_type_templ(t)) {
				t = DEREF_type(type_templ_defn(t));
			}
			ct = DEREF_ctype(type_compound_defn(t));
			while (IS_type_templ(s)) {
				s = DEREF_type(type_templ_defn(s));
			}
			cs = DEREF_ctype(type_compound_defn(s));
			copy_members(ct, cs, cinfo_none, 1);
			break;
		}
		}
		end_declarator(id, 0);
		record_location = r;
	}
	return;
}


/*
    Qualifiers of the form 'T::' where T is a template parameter can lead
    to repeated errors if T is bound to a non-class type.  This routine
    is used to keep track of those instances which have been reported
    to avoid duplication.
*/

static int
reported_nspace(NAMESPACE ns, TYPE t)
{
	static LIST(TYPE)types = NULL_list(TYPE);
	static LIST(NAMESPACE)nspaces = NULL_list(NAMESPACE);
	LIST(TYPE)p = types;
	LIST(NAMESPACE)q = nspaces;
	while (!IS_NULL_list(q)) {
		NAMESPACE pns = DEREF_nspace(HEAD_list(q));
		if (EQ_nspace(pns, ns)) {
			TYPE pt = DEREF_type(HEAD_list(p));
			if (eq_type(pt, t)) {
				return 1;
			}
		}
		p = TAIL_list(p);
		q = TAIL_list(q);
	}
	CONS_type(t, types, types);
	CONS_nspace(ns, nspaces, nspaces);
	return 0;
}


/*
    This routine expands the namespace ns by replacing any class namespace
    by the namespace of the expanded class.
*/

NAMESPACE
rescan_nspace(NAMESPACE ns)
{
	if (!IS_NULL_nspace(ns) && IS_nspace_ctype(ns)) {
		TYPE s;
		IDENTIFIER tid = DEREF_id(nspace_name(ns));
		TYPE t = DEREF_type(id_class_name_etc_defn(tid));
		while (IS_type_templ(t)) {
			t = DEREF_type(type_templ_defn(t));
		}
		s = expand_type(t, 1);
		if (!EQ_type(t, s)) {
			unsigned tag = TAG_type(s);
			while (tag == type_templ_tag) {
				s = DEREF_type(type_templ_defn(s));
				tag = TAG_type(s);
			}
			if (tag == type_compound_tag) {
				/* Expands to class type */
				CLASS_TYPE cs =
				    DEREF_ctype(type_compound_defn(s));
				complete_class(cs, 1);
				ns = DEREF_nspace(ctype_member(cs));
			} else if (tag == type_token_tag && is_templ_type(s)) {
				/* Allow template parameters */
				IDENTIFIER id = DEREF_id(type_token_tok(s));
				CLASS_TYPE cs = find_class(id);
				if (!IS_NULL_ctype(cs)) {
					ns = DEREF_nspace(ctype_member(cs));
				}
			} else {
				if (tag != type_error_tag &&
				    !reported_nspace(ns, s)) {
					/* Other types are not allowed */
					report(crt_loc,
					       ERR_temp_res_nspace(ns, s));
				}
			}
		}
	}
	return ns;
}


/*
    This routine looks up the identifier id again in the current context.
    The name is looked up as a type-name if type is true.  The routine is
    used in the resolution of dependent names in template instantiations.
*/

IDENTIFIER
rescan_id(IDENTIFIER id, QUALIFIER qual, int type)
{
	DECL_SPEC ds;
	int member = 0;
	IDENTIFIER rid = NULL_id;
	HASHID nm = DEREF_hashid(id_name(id));
	NAMESPACE ns = DEREF_nspace(id_parent(id));

	/* Allow for pseudo-template instances */
	if (IS_id_undef(id)) {
		TYPE form = DEREF_type(id_undef_form(id));
		if (!IS_NULL_type(form) && IS_type_token(form)) {
			int force = 0;
			IDENTIFIER tid = DEREF_id(type_token_tok(form));
			LIST(TOKEN)args = DEREF_list(type_token_args(form));
			tid = rescan_id(tid, qual, type);
			if (IS_id_undef(tid)) {
				force = 1;
			}
			args = expand_args(args, 1, 1);
			rid = apply_template(tid, args, 0, force);
			return rid;
		}
	}

	/* Allow for template instances */
	ds = DEREF_dspec(id_storage(id));
	if (ds & dspec_instance) {
		if (IS_id_function_etc(id)) {
			/* Template functions */
			TYPE form = DEREF_type(id_function_etc_form(id));
			if (!IS_NULL_type(form) && IS_type_token(form)) {
				IDENTIFIER tid = DEREF_id(type_token_tok(form));
				if (IS_id_function_etc(tid)) {
					LIST(TOKEN)args;
					tid = rescan_id(tid, qual, type);
					args =
					    DEREF_list(type_token_args(form));
					args = expand_args(args, 1, 1);
					rid = apply_template(tid, args, 0, 0);
					return rid;
				}
			}
		}
	}

	/* Look up identifier */
	nm = expand_name(nm, NULL_ctype);
	if (!IS_NULL_nspace(ns)) {
		if (qual != qual_none) {
			member = 1;
		} else if (IS_nspace_ctype(ns) && !IS_id_undef(id)) {
			member = 1;
		}
	}
	if (member) {
		/* Expand namespace */
		NAMESPACE cns = rescan_nspace(ns);
		if (IS_nspace_ctype(cns)) {
			rid = search_field(cns, nm, 0, type);
		} else {
			MEMBER mem = search_member(cns, nm, 0);
			if (!IS_NULL_member(mem)) {
				if (type) {
					rid = type_member(mem, type);
				} else {
					rid = DEREF_id(member_id(mem));
				}
			}
		}

		/* Check for undeclared identifiers */
		if (IS_NULL_id(rid)) {
			MAKE_id_undef(nm, dspec_none, cns, crt_loc, rid);
		}

	} else {
		/* Simple name look-up */
		rid = find_id(nm);
	}
	return rid;
}


/*
    This routine is a special case of rescan_id which is used to look up
    the names of functions in template instantiations.  If the look-ups
    in the contexts of both the template definition and the template
    instantiation are both functions then the result is an ambiguous
    identifier consisting of both sets of overloaded functions.
    Overload resolution is then used to select within these two sets.
*/

IDENTIFIER
rescan_func_id(IDENTIFIER id, QUALIFIER qual)
{
	IDENTIFIER pid = rescan_id(id, qual, 0);
	IDENTIFIER qid = rescan_member(id);
	NAMESPACE qns = DEREF_nspace(id_parent(qid));
	if (!IS_NULL_nspace(qns) && IS_nspace_block(qns)) {
		qid = pid;
	}
	/* QUERY: should qid be rescanned in context? */
	if (!EQ_id(pid, qid) && !IS_id_undef(qid)) {
		int eq = 0;
		if (IS_id_function_etc(pid) && IS_id_function_etc(qid)) {
			/* Check for overloaded functions */
			IDENTIFIER rid = pid;
			while (!IS_NULL_id(rid)) {
				if (EQ_id(rid, qid)) {
					eq = 1;
					break;
				}
				rid = DEREF_id(id_function_etc_over(rid));
			}
		}
		if (!eq) {
			/* Create ambiguous identifier */
			DECL_SPEC ds;
			LOCATION loc;
			LIST(IDENTIFIER)pids;
			HASHID nm = DEREF_hashid(id_name(pid));
			NAMESPACE ns = DEREF_nspace(id_parent(pid));
			DEREF_loc(id_loc(pid), loc);
			CONS_id(pid, NULL_list(IDENTIFIER), pids);
			CONS_id(qid, pids, pids);
			ds = find_ambig_dspec(pids);
			MAKE_id_ambig(nm, ds, ns, loc, pids, 1, pid);
		}
	}
	return pid;
}


/*
    This routine rescans the identifier id.  If id is a member of a template
    class then the corresponding member of the expanded class is returned.
    id is also marked as having been used and is instantiated if necessary.
*/

IDENTIFIER
rescan_member(IDENTIFIER id)
{
	IDENTIFIER lid;
	NAMESPACE ns = DEREF_nspace(id_parent(id));
	DECL_SPEC ds = DEREF_dspec(id_storage(id));

	/* Check for template functions */
	if (ds & dspec_instance) {
		if (IS_id_function_etc(id)) {
			/* Template functions */
			TYPE form = DEREF_type(id_function_etc_form(id));
			if (!IS_NULL_type(form) && IS_type_token(form)) {
				IDENTIFIER tid = DEREF_id(type_token_tok(form));
				if (IS_id_function_etc(tid)) {
					LIST(TOKEN) args;
					tid = rescan_member(tid);
					args = DEREF_list(type_token_args(form));
					args = expand_args(args, 1, 1);
					id = apply_template(tid, args, 0, 0);
					ns = NULL_nspace;
				}
			}
		}
	}

	/* Check for template class members */
	if (!IS_NULL_nspace(ns) && IS_nspace_ctype(ns)) {
		NAMESPACE pns = rescan_nspace(ns);
		if (!EQ_nspace(ns, pns)) {
			IDENTIFIER pid = DEREF_id(nspace_name(pns));
			lid = find_copied(pid, id, 1);
			if (!EQ_id(lid, id)) {
				define_template(lid, 0);
				id = lid;
				ds = DEREF_dspec(id_storage(id));
			}
		}
	}

	/* Handle implicitly declared parameters */
	if ((ds & dspec_implicit) && (ds & dspec_auto)) {
		HASHID nm = DEREF_hashid(id_name(id));
		id = find_id(nm);
		ds = DEREF_dspec(id_storage(id));
	}

	/* Mark as used */
	ds |= dspec_used;
	COPY_dspec(id_storage(id), ds);
	lid = DEREF_id(id_alias(id));
	if (!EQ_id(lid, id)) {
		ds = DEREF_dspec(id_storage(lid));
		ds |= dspec_used;
		COPY_dspec(id_storage(lid), ds);
	}
	return id;
}
