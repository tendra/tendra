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
#include "version.h"

#include "c_types.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "error.h"
#include "tdf.h"
#include "basetype.h"
#include "capsule.h"
#include "check.h"
#include "compile.h"
#include "destroy.h"
#include "diag3.h"
#include "encode.h"
#include "exp.h"
#include "init.h"
#include "redeclare.h"
#include "shape.h"
#include "statement.h"
#include "struct.h"
#include "stmt.h"
#include "syntax.h"
#include "throw.h"
#include "tok.h"


/*
    This variable keeps track of the number of destructors for local
    variables which are pending at any moment during the TDF generation.
    This includes such pseudo-destructors as for jump locations in
    try blocks.
*/

unsigned long no_destructors = 0;


/*
    This routine finds the number of components in the statement e,
    ignoring trivial statements and expanding compound statements
    recursively.  The result equals the number of statements added to
    the bitstream by enc_compound_stmt.
*/

unsigned
stmt_length(EXP e)
{
	if (!IS_NULL_exp(e)) {
		switch (TAG_exp(e)) {
		case exp_sequence_tag: {
			/* Compound statements */
			unsigned n = 0;
			LIST(EXP)p = DEREF_list(exp_sequence_first(e));
			while (!IS_NULL_list(p)) {
				EXP a = DEREF_exp(HEAD_list(p));
				if (!IS_NULL_exp(a)) {
					n += stmt_length(a);
				}
				p = TAIL_list(p);
			}
			return n;
		}
		case exp_location_tag: {
			/* Location statements */
			EXP a = DEREF_exp(exp_location_arg(e));
			if (!IS_NULL_exp(a)) {
				if (is_diag_stmt(a)) {
					return 1;
				}
				return stmt_length(a);
			}
			break;
		}
		case exp_reach_tag:
		case exp_unreach_tag: {
			/* Flow control statement */
			EXP a = DEREF_exp(exp_reach_etc_body(e));
			return stmt_length(a);
		}
		case exp_set_tag:
		case exp_unused_tag: {
			/* Variable flow statements */
			break;
		}
		default : {
			/* Other statements */
			return 1;
		}
		}
	}
	return 0;
}


/*
    This routine adds the statement e to the bitstream bs, ignoring
    trivial statements and expanding compound statements recursively.
*/

BITSTREAM *
enc_compound_stmt(BITSTREAM *bs, EXP e)
{
	if (!IS_NULL_exp(e)) {
		switch (TAG_exp(e)) {
		case exp_sequence_tag: {
			/* Compound statements */
			LIST(EXP)p = DEREF_list(exp_sequence_first(e));
			while (!IS_NULL_list(p)) {
				EXP a = DEREF_exp(HEAD_list(p));
				if (!IS_NULL_exp(a)) {
					bs = enc_compound_stmt(bs, a);
				}
				p = TAIL_list(p);
			}
			break;
		}
		case exp_location_tag: {
			/* Location statements */
			EXP a = DEREF_exp(exp_location_arg(e));
			if (!IS_NULL_exp(a)) {
				if (is_diag_stmt(a)) {
					BITSTREAM *ts = enc_diag_begin(&bs);
					ts = enc_stmt(ts, a);
					bs = enc_diag_end(bs, ts, a, 1);
				} else {
					bs = enc_compound_stmt(bs, a);
				}
			}
			crt_enc_loc = exp_location_end(e);
			break;
		}
		case exp_reach_tag:
		case exp_unreach_tag: {
			/* Flow control statement */
			EXP a = DEREF_exp(exp_reach_etc_body(e));
			bs = enc_compound_stmt(bs, a);
			break;
		}
		case exp_set_tag:
		case exp_unused_tag: {
			/* Variable flow statements */
			break;
		}
		default: {
			/* Other statements */
			bs = enc_stmt(bs, e);
			break;
		}
		}
	}
	return bs;
}


/*
    This routine adds all the destructors and pseudo-destructors called
    by a jump from e to d to the bitstream bs.
*/

static BITSTREAM *
enc_destructors(BITSTREAM *bs, EXP e, EXP d)
{
	unsigned long m = no_destructors;
	if (m && !unreached_code) {
		unsigned long n = 0;
		unsigned long extra = 0;
#if LANGUAGE_CPP
		unsigned ptag = null_tag;
#endif
		BITSTREAM *ts = start_bitstream(NIL(FILE), bs->link);
		while (!EQ_exp(e, d) && !IS_NULL_exp(e) && n < m) {
			unsigned tag = TAG_exp(e);
			if (tag == exp_decl_stmt_tag) {
				/* Jump out of variable scope */
				IDENTIFIER id = DEREF_id(exp_decl_stmt_id(e));
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				if (ds & dspec_auto) {
					EXP a = DEREF_exp(id_variable_term(id));
					if (!IS_NULL_exp(a)) {
						/* Destructor found */
						ulong v;
						int var = 1;
						TYPE t = DEREF_type(id_variable_type(id));
						if (ds & dspec_explicit) {
							if (ds & dspec_temp) {
								var = 4;
							}
						}
						v = unit_no(ts, id, VAR_tag, 0);
						ts = enc_term_local(ts, v,
								    NULL_off,
								    0, t, a,
								    var);
						extra++;
						n++;
					}
				}
			}
#if LANGUAGE_CPP
			/* ... continued */
			else if (tag == exp_try_block_tag) {
				/* Jump out of try block */
				if (ptag != exp_handler_tag) {
					ulong ex =
					    DEREF_ulong(exp_try_block_no(e));
					ts = enc_try_end(ts, ex);
					n++;
				}
			} else if (tag == exp_handler_tag) {
				/* Jump out of exception handler */
				ts = enc_special(ts, TOK_except_end);
				n++;
			}
			ptag = tag;
#endif
			e = get_parent_stmt(e);
		}

		/* Check for exception specifications */
#if LANGUAGE_CPP
		if (IS_NULL_exp(e) && n < m && in_exception_spec) {
			ts = enc_try_end(ts, last_params[DUMMY_catch]);
			n++;
		}
#endif

		/* Add destructors to main list */
		if (n) {
			ENC_SEQUENCE(bs, n + extra);
		}
		bs = join_bitstreams(bs, ts);
	}
	return bs;
}


/*
    If a condition-declaration in a while or for loop has a destructor
    then this destructor needs to be called at the completion of the
    loop (this is the normal end-of-scope destructor) and just before
    the second and subsequent evaluations of the condition.  This
    routine adds the latter such destructors for the variable ids to
    the bitstream bs
*/

static BITSTREAM *
enc_while_destr(BITSTREAM *bs, LIST(IDENTIFIER)ids)
{
	while (!IS_NULL_list(ids)) {
		IDENTIFIER id = DEREF_id(HEAD_list(ids));
		EXP d = DEREF_exp(id_variable_term(id));
		if (!IS_NULL_exp(d)) {
			int var = 1;
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			TYPE t = DEREF_type(id_variable_type(id));
			ulong n = unit_no(bs, id, VAR_tag, 0);
			ENC_SEQ_SMALL(bs, 2);
			if ((ds & dspec_explicit) && (ds & dspec_temp)) {
				var = 4;
			}
			bs = enc_term_local(bs, n, NULL_off, 0, t, d, var);
		}
		ids = TAIL_list(ids);
	}
	return bs;
}


/*
    This routine adds the labelled statement 'e' to the bitstream bs.
*/

static BITSTREAM *
enc_label_stmt(BITSTREAM *bs, EXP e)
{
	EXP a = DEREF_exp(exp_label_stmt_body(e));
	IDENTIFIER lab = DEREF_id(exp_label_stmt_label(e));
	IDENTIFIER flab = DEREF_id(id_alias(lab));
	if (EQ_id(lab, flab)) {
		/* Simple label */
		ulong n = DEREF_ulong(id_no(flab));
		if (n == LINK_NONE) {
			/* Label not previously output */
			DECL_SPEC info = DEREF_dspec(id_storage(flab));
			if (info & dspec_used) {
				n = unit_no(bs, flab, VAR_label, 1);
				ENC_repeat(bs);
				ENC_make_label(bs, n);
				ENC_make_top(bs);
				unreached_code = 0;
				bs = enc_stmt(bs, a);
				clear_no(flab);
			} else {
				bs = enc_stmt(bs, a);
			}
		} else {
			/* Label body output separately */
			ENC_goto(bs);
			ENC_make_label(bs, n);
			unreached_code = 1;
		}
	} else {
		/* Label alias */
		bs = enc_stmt(bs, a);
	}
	return bs;
}


/*
    This routine adds the label lab to the list q if it has not been
    output in bitstream bs and is not already a member of the list.
*/

static LIST(IDENTIFIER)
add_label(BITSTREAM *bs, IDENTIFIER lab, LIST(IDENTIFIER)q)
{
	if (!IS_NULL_id(lab)) {
		IDENTIFIER flab = DEREF_id(id_alias(lab));
		ulong n = DEREF_ulong(id_no(flab));
		if (n == LINK_NONE) {
			/* Not previously output */
			IGNORE unit_no(bs, flab, VAR_label, 1);
			CONS_id(flab, q, q);
		}
	}
	return q;
}


/*
    This routine adds the those labels in the list p which have not been
    output in bitstream bs to the list q.
*/

static LIST(IDENTIFIER)
add_labels(BITSTREAM *bs, LIST(IDENTIFIER)p, LIST(IDENTIFIER)q)
{
	while (!IS_NULL_list(p)) {
		IDENTIFIER lab = DEREF_id(HEAD_list(p));
		q = add_label(bs, lab, q);
		p = TAIL_list(p);
	}
	return q;
}


/*
    This routine adds the start of a labelled statement for the labels
    lbs to the bitstream bs.  This comprises outputting the list of
    labels.  vars gives a list of variable declarations which need to
    be moved outside the labelled statement.
*/

static BITSTREAM *
enc_labelled_start(BITSTREAM *bs, LIST(IDENTIFIER)lbs,
		   LIST(IDENTIFIER)vars)
{
	unsigned nl = LENGTH_list(lbs);
	while (!IS_NULL_list(vars)) {
		/* Declare variables */
		IDENTIFIER id = DEREF_id(HEAD_list(vars));
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (!(ds & dspec_reserve) || !is_anon_member(id)) {
			int var = 2;
			EXP d = NULL_exp;
			if ((ds & dspec_explicit) && (ds & dspec_temp)) {
				var = 4;
			}
			bs = enc_variable(bs, id, var, &d, NULL_exp);
			if (!IS_NULL_exp(d)) {
				no_destructors++;
			}
		}
		vars = TAIL_list(vars);
	}
	if (nl == 0) {
		/* No labels */
		/* EMPTY */
	} else if (nl == 1) {
		/* Single label can be mapped to conditional */
		IDENTIFIER lab = DEREF_id(HEAD_list(lbs));
		ulong n = unit_no(bs, lab, VAR_label, 1);
		ENC_conditional(bs);
		ENC_make_label(bs, n);
	} else {
		/* Multiple labels require labelled */
		ENC_labelled(bs);
		ENC_LIST(bs, nl);
		while (!IS_NULL_list(lbs)) {
			IDENTIFIER lab = DEREF_id(HEAD_list(lbs));
			ulong n = unit_no(bs, lab, VAR_label, 1);
			ENC_make_label(bs, n);
			lbs = TAIL_list(lbs);
		}
	}
	return bs;
}


/*
    This routine adds the branch of the labelled statement d corresponding
    to the label lab to the bitstream bs.  Note that each such branch is
    terminated by a jump to an immediately following label, a jump to an
    enclosing break or continue label, or by falling through to the end
    of the labelled statement (see end_solve_branch).
*/

static BITSTREAM *
enc_labelled_branch(BITSTREAM *bs, IDENTIFIER lab, EXP d)
{
	ulong n;
	IDENTIFIER nlab;
	EXP e = DEREF_exp(id_label_stmt(lab));
	EXP f = e;
	EXP g = NULL_exp;

	/* Examine label type */
	int op = DEREF_int(id_label_op(lab));
	switch (op) {

	case lex_while:
	case lex_for: {
		/* While or for label */
		e = DEREF_exp(exp_label_stmt_parent(e));
		nlab = DEREF_id(exp_while_stmt_cont_lab(e));
		e = DEREF_exp(exp_while_stmt_body(e));
		if (is_diag_stmt(e)) {
			g = e;
		}
		break;
	}

	case lex_do: {
		/* Do label */
		e = DEREF_exp(exp_label_stmt_parent(e));
		nlab = DEREF_id(exp_do_stmt_cont_lab(e));
		e = DEREF_exp(exp_do_stmt_body(e));
		if (is_diag_stmt(e)) {
			g = e;
		}
		break;
	}

	case lex_if: {
		/* Conditional label */
		EXP c;
		int sw = 0;
		nlab = DEREF_id(exp_label_stmt_next(e));
		e = DEREF_exp(exp_label_stmt_parent(e));
		c = DEREF_exp(exp_if_stmt_cond(e));
		IGNORE simplify_cond(c, &sw);
		if (sw) {
			e = DEREF_exp(exp_if_stmt_true_code(e));
		} else {
			e = DEREF_exp(exp_if_stmt_false_code(e));
		}
		if (is_diag_stmt(e)) {
			g = e;
		}
		break;
	}

	case lex_continue: {
		/* Continue label */
		EXP c;
		unsigned m;
		IDENTIFIER rlab;
		LIST(IDENTIFIER)cids;
		EXP b = DEREF_exp(exp_label_stmt_body(e));
		e = DEREF_exp(exp_label_stmt_parent(e));
		if (IS_exp_while_stmt(e)) {
			c = DEREF_exp(exp_while_stmt_cond(e));
			rlab = DEREF_id(exp_while_stmt_loop_lab(e));
			nlab = DEREF_id(exp_while_stmt_break_lab(e));
			cids = DEREF_list(exp_while_stmt_cond_id(e));
		} else {
			c = DEREF_exp(exp_do_stmt_cond(e));
			rlab = DEREF_id(exp_do_stmt_loop_lab(e));
			nlab = DEREF_id(exp_do_stmt_break_lab(e));
			cids = NULL_list(IDENTIFIER);
		}
		m = stmt_length(b);
		ENC_SEQUENCE(bs, m + 1);
		if (m) {
			bs = enc_compound_stmt(bs, b);
		}

		/* Output conditional jump */
		n = unit_no(bs, rlab, VAR_label, 0);
		if (!IS_NULL_list(cids)) {
			bs = enc_while_destr(bs, cids);
		}
		bs = enc_condition(bs, c, LINK_NONE, n);
		n = unit_no(bs, nlab, VAR_label, 0);
		ENC_goto(bs);
		ENC_make_label(bs, n);
		unreached_code = 1;
		return bs;
	}

	default : {
		/* Other labels */
		if (!IS_NULL_exp(e)) {
			if (is_diag_stmt(e)) {
				g = e;
			}
			nlab = DEREF_id(exp_label_stmt_next(e));
			e = DEREF_exp(exp_label_stmt_body(e));
		} else {
			nlab = NULL_id;
		}
		break;
	}
	}

	/* Output label body */
	if (IS_NULL_id(nlab)) {
		/* Fall through to end of labelled statement */
		if (no_destructors) {
			if (!IS_NULL_exp(e)) {
				ENC_SEQ_SMALL(bs, 1);
				if (!IS_NULL_exp(g)) {
					BITSTREAM *ts = enc_diag_begin(&bs);
					ts = enc_stmt(ts, e);
					bs = enc_diag_end(bs, ts, g, 1);
				} else {
					bs = enc_stmt(bs, e);
				}
			}
			bs = enc_destructors(bs, f, d);
			ENC_make_top(bs);
		} else {
			if (!IS_NULL_exp(g)) {
				BITSTREAM *ts = enc_diag_begin(&bs);
				ts = enc_stmt(ts, e);
				bs = enc_diag_end(bs, ts, g, 1);
			} else {
				bs = enc_stmt(bs, e);
			}
		}
	} else {
		/* Jump to following label */
		if (!IS_NULL_exp(e)) {
			ENC_SEQ_SMALL(bs, 1);
			if (!IS_NULL_exp(g)) {
				BITSTREAM *ts = enc_diag_begin(&bs);
				ts = enc_stmt(ts, e);
				bs = enc_diag_end(bs, ts, g, 1);
			} else {
				bs = enc_stmt(bs, e);
			}
		}
		op = DEREF_int(id_label_op(nlab));
		if (op == lex_break || op == lex_continue) {
			/* Need to call destructors for jump */
			EXP b = DEREF_exp(id_label_stmt(nlab));
			b = DEREF_exp(exp_label_stmt_parent(b));
			bs = enc_destructors(bs, f, b);
		}
		n = unit_no(bs, nlab, VAR_label, 0);
		ENC_goto(bs);
		ENC_make_label(bs, n);
		unreached_code = 1;
	}
	return bs;
}


/*
    This routine adds the end of the labelled statement e to the bitstream
    bs.  This comprises outputting the list of label bodies for the labels
    lbs and then taking the labels and the variables vars out of scope.
*/

static BITSTREAM *
enc_labelled_end(BITSTREAM *bs, LIST(IDENTIFIER)lbs, LIST(IDENTIFIER)vars,
		 EXP e)
{
	int uc = unreached_code;
	unsigned nl = LENGTH_list(lbs);
	if (nl == 0) {
		/* No labels */
		/* EMPTY */
	} else if (nl == 1) {
		/* Single label */
		IDENTIFIER lab = DEREF_id(HEAD_list(lbs));
		unreached_code = 0;
		bs = enc_labelled_branch(bs, lab, e);
		if (!unreached_code) {
			uc = 0;
		}
		clear_no(lab);
	} else {
		/* Multiple labels */
		LIST(IDENTIFIER)p = lbs;
		ENC_LIST(bs, nl);
		while (!IS_NULL_list(p)) {
			IDENTIFIER lab = DEREF_id(HEAD_list(p));
			unreached_code = 0;
			bs = enc_labelled_branch(bs, lab, e);
			if (!unreached_code) {
				uc = 0;
			}
			p = TAIL_list(p);
		}
		p = lbs;
		while (!IS_NULL_list(p)) {
			IDENTIFIER lab = DEREF_id(HEAD_list(p));
			clear_no(lab);
			p = TAIL_list(p);
		}
	}
	while (!IS_NULL_list(vars)) {
		/* Take variables out of scope */
		IDENTIFIER id = DEREF_id(HEAD_list(vars));
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_auto) {
			clear_no(id);
		}
		vars = TAIL_list(vars);
	}
	unreached_code = uc;
	return bs;
}


/*
    This location is used to store the current location during the
    encoding of statements.
*/

PTR(LOCATION)crt_enc_loc = NULL_ptr(LOCATION);


/*
    This routine adds the declaration statement e to the bitstream bs.
*/

static BITSTREAM *
enc_decl_stmt(BITSTREAM *bs, EXP e)
{
	int var = 1;
	int scope = 0;
	BITSTREAM *ts;
	ulong nlabs = 0;
	EXP d = NULL_exp;
	int diag = output_diag;
	EXP a = DEREF_exp(exp_decl_stmt_body(e));
	IDENTIFIER id = DEREF_id(exp_decl_stmt_id(e));
	TYPE t = DEREF_type(id_variable_type(id));
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (!(ds & dspec_reserve) || !is_anon_member(id)) {
		EXP b = DEREF_exp(id_variable_init(id));
		if (IS_NULL_exp(b) || !output_diag) {
			/* Don't output diagnostics */
			e = NULL_exp;
		}
		if (ds & dspec_explicit) {
			/* Only declare explicitly initialised variables */
			if (ds & dspec_temp) {
				nlabs = no_labels(bs);
				e = NULL_exp;
				var = 4;
			} else {
				var = 3;
			}
		}
		if (ds & dspec_done) {
			/* Variable previously declared */
			int dummy = 0;
			EXP d1 = DEREF_exp(id_variable_term(id));
			if (!IS_NULL_exp(d1)) {
				/* Allow for terminator expressions */
				if (output_except) {
					while (IS_exp_nof(d1)) {
						d1 = DEREF_exp(exp_nof_pad(d1));
					}
					if (IS_NULL_exp(b) && var == 1) {
						/* Force initialisation */
						b = make_dummy_init(t);
						dummy = 1;
					}
				} else {
					d1 = NULL_exp;
				}
			}
			if (!IS_NULL_exp(b)) {
				ulong n = unit_no(bs, id, VAR_tag, 0);
				bs = enc_assign_local(bs, b, d1, n, t, e);
				if (IS_exp_thrown(b) && output_new_diag) {
					diag = 0;
				}
				if (dummy)free_exp(b, 1);
			}
		} else {
			/* Variable not previously declared */
			bs = enc_variable(bs, id, var, &d, e);
			if (ds & dspec_auto) {
				scope = 1;
			}
		}
	}
	if (diag && !(ds & dspec_temp)) {
		HASHID nm = DEREF_hashid(id_name(id));
		if (!IS_hashid_anon(nm)) {
			ts = start_bitstream(NIL(FILE), bs->link);
		} else {
			ts = bs;
			diag = 0;
		}
	} else {
		ts = bs;
		diag = 0;
	}
	if (IS_NULL_exp(d)) {
		ts = enc_stmt(ts, a);
	} else {
		unsigned seq = stmt_length(a) + 1;
		no_destructors++;
		ENC_SEQUENCE(ts, seq);
		ts = enc_compound_stmt(ts, a);
		if (unreached_code) {
			ENC_make_top(ts);
			ENC_make_top(ts);
		} else {
			ulong n = unit_no(ts, id, VAR_tag, 0);
			if (var == 4 && nlabs == no_labels(bs)) {
				var = 3;
			}
			ts = enc_term_local(ts, n, NULL_off, 0, t, d, var);
		}
		no_destructors--;
	}
	if (diag) {
		bs = enc_diag_local(bs, id, ts);
	} else {
		bs = ts;
	}
	if (scope) {
		/* Take variable out of scope */
		clear_no(id);
	}
	return bs;
}


/*
    This routine is identical to enc_stmt except that it makes explicit
    provision for diagnostic information.
*/

static BITSTREAM *
enc_body_stmt(BITSTREAM *bs, EXP e)
{
	if (output_diag && is_diag_stmt(e)) {
		BITSTREAM *ts = enc_diag_begin(&bs);
		ts = enc_stmt(ts, e);
		bs = enc_diag_end(bs, ts, e, 1);
	} else {
		bs = enc_stmt(bs, e);
	}
	return bs;
}


/*
    This routine adds the statement e to the bitstream bs as a TDF EXP.
*/

BITSTREAM *
enc_stmt(BITSTREAM *bs, EXP e)
{
	if (IS_NULL_exp(e)) {
		/* Deal with null expressions */
		ENC_make_top(bs);
		return bs;
	}

	/* Examine expression cases */
	switch (TAG_exp(e)) {

	case exp_sequence_tag: {
		/* Sequences of statements */
		unsigned n = stmt_length(e);
		if (n == 0) {
			ENC_make_top(bs);
		} else {
			if (n > 1) {
				ENC_SEQUENCE(bs, n - 1);
			}
			bs = enc_compound_stmt(bs, e);
		}
		break;
	}

	case exp_solve_stmt_tag: {
		/* Solve statements */
		LIST(IDENTIFIER)p;
		EXP a = DEREF_exp(exp_solve_stmt_body(e));
		p = DEREF_list(exp_solve_stmt_labels(e));
		if (IS_NULL_list(p)) {
			/* No labels */
			bs = enc_stmt(bs, a);
		} else {
			LIST(IDENTIFIER)lbs;
			LIST(IDENTIFIER)vars;
			ulong nd = no_destructors;
			lbs = add_labels(bs, p, NULL_list(IDENTIFIER));
			vars = DEREF_list(exp_solve_stmt_vars(e));
			bs = enc_labelled_start(bs, lbs, vars);
			bs = enc_stmt(bs, a);
			bs = enc_labelled_end(bs, lbs, vars, e);
			DESTROY_list(lbs, SIZE_id);
			no_destructors = nd;
		}
		break;
	}

	case exp_decl_stmt_tag: {
		/* Variable declarations */
		bs = enc_decl_stmt(bs, e);
		break;
	}

	case exp_while_stmt_tag: {
		/* 'while' and 'for' statements */
		EXP d;
		int uc;
		unsigned m;
		ulong an, bn;
		DECL_SPEC ds;
		LIST(IDENTIFIER)cids;
		EXP c = DEREF_exp(exp_while_stmt_cond(e));
		EXP a = DEREF_exp(exp_while_stmt_body(e));
		IDENTIFIER lab = DEREF_id(exp_while_stmt_break_lab(e));
		IDENTIFIER loop = DEREF_id(exp_while_stmt_loop_lab(e));
		cids = DEREF_list(exp_while_stmt_cond_id(e));

		/* Check for labelled statements */
		an = DEREF_ulong(id_no(loop));
		if (an != LINK_NONE) {
			bn = unit_no(bs, lab, VAR_label, 0);
			an = unit_no(bs, loop, VAR_label, 0);
			ENC_SEQ_SMALL(bs, 1);
			bs = enc_condition(bs, c, bn, LINK_NONE);
			ENC_goto(bs);
			ENC_make_label(bs, an);
			unreached_code = 1;
			break;
		}

		/* Encode the start of the loop */
		bn = unit_no(bs, lab, VAR_label, 1);
		an = unit_no(bs, loop, VAR_label, 1);
		ENC_conditional(bs);
		ENC_make_label(bs, bn);
		ENC_SEQ_SMALL(bs, 1);
		bs = enc_condition(bs, c, bn, LINK_NONE);
		ENC_repeat(bs);
		ENC_make_label(bs, an);
		ENC_make_top(bs);
		uc = unreached_code;

		/* Check for continue jump */
		ENC_SEQ_SMALL(bs, 1);
		lab = DEREF_id(exp_while_stmt_cont_lab(e));
		ds = DEREF_dspec(id_storage(lab));
		if (ds & dspec_used) {
			/* Body contains a continue jump */
			ulong cn = unit_no(bs, lab, VAR_label, 1);
			ENC_conditional(bs);
			ENC_make_label(bs, cn);
			bs = enc_body_stmt(bs, a);
			ENC_make_top(bs);
		} else {
			/* No continue jump */
			bs = enc_body_stmt(bs, a);
		}

		/* Encode end of label */
		d = DEREF_exp(id_label_stmt(lab));
		d = DEREF_exp(exp_label_stmt_body(d));
		m = stmt_length(d);
		if (m) {
			ENC_SEQUENCE(bs, m);
			bs = enc_compound_stmt(bs, d);
		}
		if (!IS_NULL_list(cids)) {
			bs = enc_while_destr(bs, cids);
		}
		bs = enc_condition(bs, c, LINK_NONE, an);
		ENC_make_top(bs);
		if (!uc) {
			unreached_code = 0;
		}
		clear_no(loop);
		clear_no(lab);
		break;
	}

	case exp_do_stmt_tag: {
		/* 'do' statements */
		ulong an;
		DECL_SPEC ds;
		int have_break = 0;
		EXP c = DEREF_exp(exp_do_stmt_cond(e));
		EXP a = DEREF_exp(exp_do_stmt_body(e));
		IDENTIFIER lab = DEREF_id(exp_do_stmt_break_lab(e));
		IDENTIFIER loop = DEREF_id(exp_do_stmt_loop_lab(e));

		/* Check for labelled statements */
		an = DEREF_ulong(id_no(loop));
		if (an != LINK_NONE) {
			an = unit_no(bs, loop, VAR_label, 0);
			ENC_goto(bs);
			ENC_make_label(bs, an);
			unreached_code = 1;
			break;
		}

		/* Check for break label */
		ds = DEREF_dspec(id_storage(lab));
		if (ds & dspec_used) {
			ulong bn = unit_no(bs, lab, VAR_label, 1);
			ENC_conditional(bs);
			ENC_make_label(bs, bn);
			have_break = 1;
		}

		/* Encode the start of the loop */
		an = unit_no(bs, loop, VAR_label, 1);
		ENC_repeat(bs);
		ENC_make_label(bs, an);
		ENC_make_top(bs);
		ENC_SEQ_SMALL(bs, 1);

		/* Check for continue label */
		lab = DEREF_id(exp_do_stmt_cont_lab(e));
		ds = DEREF_dspec(id_storage(lab));
		if (ds & dspec_used) {
			ulong cn = unit_no(bs, lab, VAR_label, 1);
			ENC_conditional(bs);
			ENC_make_label(bs, cn);
			bs = enc_body_stmt(bs, a);
			ENC_make_top(bs);
		} else {
			bs = enc_body_stmt(bs, a);
		}

		/* Encode the end of the loop */
		bs = enc_condition(bs, c, LINK_NONE, an);
		if (have_break) {
			ENC_make_top(bs);
			unreached_code = 0;
		}
		clear_no(loop);
		clear_no(lab);
		break;
	}

	case exp_switch_stmt_tag: {
		/* 'switch' statements */
		EXP a;
		EXP b;
		ulong n;
		unsigned nc;
		LIST(NAT)cns;
		IDENTIFIER dl, bl;
		LIST(IDENTIFIER)cls;
		LIST(IDENTIFIER)lbs;
		LIST(IDENTIFIER)els;
		LIST(IDENTIFIER)vars;
		unsigned long nd = no_destructors;

		/* Start labelled statement */
		b = DEREF_exp(exp_switch_stmt_body(e));
		cns = DEREF_list(exp_switch_stmt_cases(e));
		cls = DEREF_list(exp_switch_stmt_case_labs(e));
		dl = DEREF_id(exp_switch_stmt_default_lab(e));
		bl = DEREF_id(exp_switch_stmt_break_lab(e));
		els = DEREF_list(exp_solve_stmt_labels(b));
		nc = LENGTH_list(cls);

		/* Create list of labels */
		vars = DEREF_list(exp_solve_stmt_vars(b));
		lbs = add_labels(bs, cls, NULL_list(IDENTIFIER));
		lbs = add_label(bs, dl, lbs);
		lbs = add_label(bs, bl, lbs);
		lbs = add_labels(bs, els, lbs);
		lbs = REVERSE_list(lbs);
		bs = enc_labelled_start(bs, lbs, vars);

		/* Encode case jump */
		ENC_SEQ_SMALL(bs, 1);
		a = DEREF_exp(exp_switch_stmt_control(e));
		if (IS_NULL_list(cls)) {
			/* No cases */
			bs = enc_exp(bs, a);
		} else {
			ENC_case(bs);
			ENC_false(bs);
			bs = enc_exp(bs, a);
			ENC_LIST(bs, nc);
			while (!IS_NULL_list(cls)) {
				/* Encode case limbs */
				NAT cn = DEREF_nat(HEAD_list(cns));
				IDENTIFIER cl = DEREF_id(HEAD_list(cls));
				n = unit_no(bs, cl, VAR_label, 0);
				ENC_make_label(bs, n);
				bs = enc_snat(bs, cn, 0, 1);
				bs = enc_snat(bs, cn, 0, 1);
				cns = TAIL_list(cns);
				cls = TAIL_list(cls);
			}
		}

		/* Default or break jump */
		if (IS_NULL_id(dl)) {
			dl = bl;
		}
		n = unit_no(bs, dl, VAR_label, 0);
		ENC_goto(bs);
		ENC_make_label(bs, n);
		unreached_code = 1;

		/* End labelled statement */
		bs = enc_labelled_end(bs, lbs, vars, e);
		DESTROY_list(lbs, SIZE_id);
		no_destructors = nd;
		break;
	}

	case exp_return_stmt_tag: {
		/* Return expressions */
		ulong r = last_params[DUMMY_return];
		EXP a = DEREF_exp(exp_return_stmt_value(e));
		if (IS_NULL_exp(a)) {
			/* Plain return */
			bs = enc_destructors(bs, e, NULL_exp);
			ENC_return(bs);
			ENC_make_top(bs);
		} else if (r != LINK_NONE) {
			/* Reference return */
			ENC_SEQ_SMALL(bs, 1);
			if (r == LINK_ZERO) {
				bs = enc_exp(bs, a);
			} else {
				OFFSET off = NULL_off;
				TYPE t = DEREF_type(exp_type(a));
				bs = enc_init_tag(bs, r, off, 1, t, a,
						  NULL_exp, 0);
			}
			bs = enc_destructors(bs, e, NULL_exp);
			ENC_return(bs);
			ENC_make_top(bs);
		} else {
			if (no_destructors) {
				/* Return with destructors */
				if (is_const_exp(a, -1)) {
					bs = enc_destructors(bs, e, NULL_exp);
					ENC_return(bs);
					bs = enc_exp(bs, a);
				} else {
					ulong n = unit_no(bs, NULL_id, VAR_tag, 1);
					ENC_identify(bs);
					bs = enc_access(bs, dspec_none);
					ENC_make_tag(bs, n);
					bs = enc_exp(bs, a);
					bs = enc_destructors(bs, e, NULL_exp);
					ENC_return(bs);
					ENC_obtain_tag(bs);
					ENC_make_tag(bs, n);
				}
			} else {
				/* Simple return */
				ENC_return(bs);
				bs = enc_exp(bs, a);
			}
		}
		unreached_code = 1;
		break;
	}

	case exp_goto_stmt_tag: {
		/* Goto expressions */
		EXP a = DEREF_exp(exp_goto_stmt_join(e));
		IDENTIFIER lab = DEREF_id(exp_goto_stmt_label(e));
		ulong n = unit_no(bs, lab, VAR_label, 0);
		bs = enc_destructors(bs, e, a);
		ENC_goto(bs);
		ENC_make_label(bs, n);
		unreached_code = 1;
		break;
	}

	case exp_label_stmt_tag: {
		/* Labelled expressions */
		if (is_diag_stmt(e)) {
			IDENTIFIER lab = DEREF_id(exp_label_stmt_label(e));
			ulong n = DEREF_ulong(id_no(lab));
			if (n == LINK_NONE) {
				BITSTREAM *ts = enc_diag_begin(&bs);
				ts = enc_label_stmt(ts, e);
				bs = enc_diag_end(bs, ts, e, 1);
			} else {
				bs = enc_label_stmt(bs, e);
			}
		} else {
			bs = enc_label_stmt(bs, e);
		}
		break;
	}

#if LANGUAGE_CPP
	case exp_try_block_tag: {
		/* Try block */
		bs = enc_try(bs, e);
		break;
	}

	case exp_handler_tag: {
		/* Exception handler */
		BITSTREAM *ts;
		EXP a = DEREF_exp(exp_handler_body(e));
		IDENTIFIER id = DEREF_id(exp_handler_except(e));
		if (!IS_NULL_id(id)) {
			/* Declare exception variable */
			EXP d = NULL_exp;
			bs = enc_variable(bs, id, 2, &d, NULL_exp);
			if (!IS_NULL_exp(d)) {
				no_destructors++;
			}
		}
		ts = enc_diag_begin(&bs);
		ts = enc_stmt(ts, a);
		bs = enc_diag_end(bs, ts, e, 1);
		clear_no(id);
		break;
	}
#endif

	case exp_location_tag: {
		/* Location statement */
		EXP a = DEREF_exp(exp_location_arg(e));
		bs = enc_body_stmt(bs, a);
		crt_enc_loc = exp_location_end(e);
		break;
	}

	case exp_reach_tag:
	case exp_unreach_tag: {
		/* Flow control statement */
		EXP a = DEREF_exp(exp_reach_etc_body(e));
		bs = enc_stmt(bs, a);
		break;
	}

	case exp_if_stmt_tag:
	case exp_hash_if_tag:
	default: {
		/* Expression statements */
		bs = enc_stmt_exp(bs, e, type_void, 0);
		break;
	}
	}
	return bs;
}


/*
    This routine adds the expression statement e to the bitstream bs as
    a TDF EXP.  use indicates how the value of the expression is used.
*/

BITSTREAM *
enc_stmt_exp(BITSTREAM *bs, EXP e, TYPE t, int use)
{
	if (IS_NULL_exp(e)) {
		/* Deal with null expressions */
		ENC_make_top(bs);
		return bs;
	}

	/* Examine expression cases */
	switch (TAG_exp(e)) {

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
		/* Simple statements */
		bs = enc_stmt(bs, e);
		break;
	}

	case exp_sequence_tag: {
		/* Lexical blocks */
		bs = enc_body_stmt(bs, e);
		break;
	}

	case exp_if_stmt_tag: {
		/* Conditional statements */
		ulong n;
		int ua, ub;
		int sw = 0;
		int whole = 1;
		ulong m = LINK_NONE;
		EXP c = DEREF_exp(exp_if_stmt_cond(e));
		EXP a = DEREF_exp(exp_if_stmt_true_code(e));
		EXP b = DEREF_exp(exp_if_stmt_false_code(e));

		/* Check for labelled statements */
		IDENTIFIER lab = DEREF_id(exp_if_stmt_label(e));
		if (!IS_NULL_id(lab)) {
			n = DEREF_ulong(id_no(lab));
			if (n != LINK_NONE) {
				whole = 0;
			}
		}
		n = unit_no(bs, lab, VAR_label, whole);
		if (whole) {
			/* Introduce conditional label */
			ENC_conditional(bs);
			ENC_make_label(bs, n);
		}
		c = simplify_cond(c, &sw);
		if (sw) {
			/* Switch conditions */
			EXP d = a;
			a = b;
			b = d;
			m = n;
			n = LINK_NONE;
		}
		if (!IS_NULL_exp(a)) {
			ENC_SEQ_SMALL(bs, 1);
		}
		bs = enc_condition(bs, c, n, m);
		ub = unreached_code;
		if (!IS_NULL_exp(a)) {
			bs = enc_stmt_exp(bs, a, t, use);
		}
		ua = unreached_code;
		if (whole) {
			/* Conditional label body */
			unreached_code = ub;
			bs = enc_stmt_exp(bs, b, t, use);
			ub = unreached_code;
			clear_no(lab);
		}
		unreached_code = (ua && ub);
		break;
	}

	case exp_hash_if_tag: {
		/* Conditional compilations */
		int ua, ub;
		BITSTREAM *ts;
		EXP c = DEREF_exp(exp_hash_if_cond(e));
		EXP a = DEREF_exp(exp_hash_if_true_code(e));
		EXP b = DEREF_exp(exp_hash_if_false_code(e));
		ENC_exp_cond(bs);
		bs = enc_exp(bs, c);
		ts = start_bitstream(NIL(FILE), bs->link);
		ub = unreached_code;
		ts = enc_stmt_exp(ts, a, t, use);
		ua = unreached_code;
		bs = enc_bitstream(bs, ts);
		ts = start_bitstream(NIL(FILE), bs->link);
		unreached_code = ub;
		ts = enc_stmt_exp(ts, b, t, use);
		ub = unreached_code;
		bs = enc_bitstream(bs, ts);
		unreached_code = (ua && ub);
		break;
	}

	case exp_location_tag: {
		/* Location statements */
		EXP a = DEREF_exp(exp_location_arg(e));
		BITSTREAM *ts = enc_diag_begin(&bs);
		ts = enc_stmt_exp(ts, a, t, use);
		crt_enc_loc = exp_location_end(e);
		bs = enc_diag_end(bs, ts, a, 0);
		break;
	}

	case exp_comma_tag: {
		/* Comma expressions */
		EXP a;
		LIST(EXP)p = DEREF_list(exp_comma_args(e));
		unsigned m = LENGTH_list(p);
		if (m > 1) {
			ENC_SEQUENCE(bs, m - 1);
		}
		for (;;) {
			a = DEREF_exp(HEAD_list(p));
			p = TAIL_list(p);
			if (IS_NULL_list(p)) {
				break;
			}
			bs = enc_stmt_exp(bs, a, type_void, 0);
		}
		if (use != -1) {
			bs = enc_stmt_exp(bs, a, t, use);
		}
		break;
	}

	case exp_paren_tag:
	case exp_copy_tag: {
		/* Parenthesised expressions */
		EXP a = DEREF_exp(exp_paren_etc_arg(e));
		bs = enc_stmt_exp(bs, a, t, use);
		break;
	}

	case exp_contents_tag: {
		/* Contents expressions */
		if (use == 0) {
			EXP a = DEREF_exp(exp_contents_ptr(e));
			bs = enc_exp(bs, a);
			break;
		}
		goto default_lab;
	}

	default:
default_lab: {
		      /* Simple expressions */
		      switch (use) {
		      case 2: {
			      bs = enc_addr_exp(bs, t, e);
			      break;
		      }
		      case 3: {
			      bs = enc_cont_exp(bs, t, e);
			      break;
		      }
		      default : {
			      bs = enc_exp(bs, e);
			      break;
		      }
		      }
		      break;
	      }
	}
	return bs;
}

