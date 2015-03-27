/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <limits.h>
#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>
#include <utility/buffer.h>

#include <syntax/syntax.h>

#include <parse/preproc.h>
#include <parse/constant.h>
#include <parse/hash.h>
#include <parse/lex.h>
#include <parse/macro.h>
#include <parse/parse.h>
#include <parse/predict.h>
#include <parse/preproc.h>

#include <construct/access.h>
#include <construct/basetype.h>
#include <construct/check.h>
#include <construct/chktype.h>
#include <construct/class.h>
#include <construct/convert.h>
#include <construct/copy.h>
#include <construct/declare.h>
#include <construct/exception.h>
#include <construct/expression.h>
#include <construct/function.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/instance.h>
#include <construct/inttype.h>
#include <construct/namespace.h>
#include <construct/redeclare.h>
#include <construct/statement.h>
#include <construct/template.h>
#include <construct/tokdef.h>
#include <construct/token.h>
#include <construct/link.h>

#include <output/bitstream.h>
#include <output/dump.h>
#include <output/tok.h>

#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "ftype_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "member_ops.h"
#include "off_ops.h"
#include "tok_ops.h"
#include "type_ops.h"


/*
    This routine returns the keyword associated with a type token of
    kind bt.
*/

int
type_token_key(BASE_TYPE bt)
{
	int key = lex_type_Hcap;
	if (bt & btype_float) {
		if (bt & btype_star) {
			key = lex_scalar_Hcap;
		} else if (bt & btype_int) {
			key = lex_arith_Hcap;
		} else {
			key = lex_float_Hcap;
		}
	} else if (bt & btype_int) {
		if (bt & btype_signed) {
			key = lex_signed;
		} else if (bt & btype_unsigned) {
			key = lex_unsigned;
		} else {
			key = lex_variety_Hcap;
		}
	} else if (bt == btype_class) {
		key = lex_class_Hcap;
	} else if (bt == btype_struct) {
		key = lex_struct_Hcap;
	} else if (bt == btype_union) {
		key = lex_union_Hcap;
	}
	return key;
}


/*
    This routine creates a type token of kind bt.
*/

TOKEN
make_type_token(BASE_TYPE bt)
{
	TOKEN tok;
	MAKE_tok_type(bt, NULL_type, tok);
	return tok;
}


/*
    This routine creates an expression token of type t.
*/

TOKEN
make_exp_token(TYPE t, int lv, int c)
{
	TOKEN tok;
	if (lv) {
		t = lvalue_type(t);
	} else {
		t = rvalue_type(t);
	}
	object_type(t, id_token_tag);
	MAKE_tok_exp(t, c, NULL_exp, tok);
	return tok;
}


/*
    This routine creates a function token of type t.
*/

TOKEN
make_func_token(TYPE t)
{
	int ell;
	TOKEN tok;
	if (!IS_type_func(t)) {
		report(preproc_loc, ERR_token_func(t));
		tok = make_exp_token(t, 0, 0);
		return tok;
	}
	ell = DEREF_int(type_func_ellipsis(t));
	if (ell & FUNC_NO_PARAMS) {
		/* Map 't ()' to 't ( void )' */
		COPY_int(type_func_ellipsis(t), FUNC_NONE);
	}
	MAKE_tok_func(t, tok);
	return tok;
}


/*
    This routine creates a member selector token for a member of s of
    type t.  acc gives the member access.
*/

TOKEN
make_member_token(TYPE t, TYPE s, DECL_SPEC acc)
{
	TOKEN tok;
	if (!IS_type_compound(s)) {
		report(preproc_loc, ERR_token_mem(s));
		tok = make_exp_token(t, 0, 0);
		return tok;
	}
#if LANGUAGE_CPP
	crt_access = acc;
#else
	UNUSED(acc);
#endif
	MAKE_tok_member(s, t, NULL_off, tok);
	return tok;
}


/*
    Procedure tokens which take or return other procedure tokens are not
    allowed.  This routine checks the parameter token sort tok.
*/

static TOKEN
check_param_sort(TOKEN tok)
{
	if (!IS_NULL_tok(tok)) {
		if (IS_tok_func(tok)) {
			tok = func_proc_token(tok);
		}
		if (IS_tok_proc(tok)) {
			report(preproc_loc, ERR_token_proc_high());
			tok = DEREF_tok(tok_proc_res(tok));
		}
	}
	return tok;
}


/*
    This routine begins the construction of a procedure token.
*/

TOKEN
begin_proc_token(void)
{
	TOKEN tok;
	begin_param(NULL_id);
	MAKE_tok_proc(NULL_tok, crt_namespace, lex_identifier, tok);
	return tok;
}


/*
    This routine sets the token numbers for the list of procedure token
    parameters p.
*/

void
set_proc_token(LIST(IDENTIFIER) p)
{
	ulong n = 0;
	while (!IS_NULL_list(p)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(p));
		if (!IS_NULL_id(pid)) {
			COPY_ulong(id_no(pid), n);
		}
		n++;
		p = TAIL_list(p);
	}
	return;
}


/*
    This routine continues the definition of the procedure token prev
    by adding the lists of bound and program parameters, p and q.
*/

TOKEN
cont_proc_token(TOKEN prev, LIST(IDENTIFIER) p, LIST(IDENTIFIER) q)
{
	if (!IS_NULL_tok(prev)) {
		unsigned n;
		if (!EQ_list(p, q)) {
			int eq = 1;
			LIST(IDENTIFIER) ps = p;
			LIST(IDENTIFIER) qs = q;
			while (!IS_NULL_list(ps) && !IS_NULL_list(qs)) {
				IDENTIFIER ip = DEREF_id(HEAD_list(ps));
				IDENTIFIER iq = DEREF_id(HEAD_list(qs));
				if (!EQ_id(ip, iq)) {
					eq = 0;
					break;
				}
				ps = TAIL_list(ps);
				qs = TAIL_list(qs);
			}
			if (eq && EQ_list(ps, qs)) {
				/* Parameter lists match */
				DESTROY_list(q, SIZE_id);
				q = p;
			} else {
				set_proc_token(q);
			}
		}
		set_proc_token(p);
		COPY_list(tok_proc_bids(prev), p);
		COPY_list(tok_proc_pids(prev), q);
		n = LENGTH_list(q);
		IGNORE check_value(OPT_VAL_macro_pars,(ulong)n);
	}
	return prev;
}


/*
    This routine completes the definition of the procedure token prev by
    filling in the token result sort res.
*/

TOKEN
end_proc_token(TOKEN prev, TOKEN res)
{
	res = check_param_sort(res);
	if (!IS_NULL_tok(prev)) {
		COPY_tok(tok_proc_res(prev), res);
	}
	end_param();
	return prev;
}


/*
    This routine declares a token bound parameter of sort tok with name
    id, which belongs to the tag namespace if tag is true.
*/

IDENTIFIER
make_tok_param(TOKEN tok, int tag, IDENTIFIER id)
{
	if (IS_NULL_id(id)) {
		HASHID nm = lookup_anon();
		id = DEREF_id(hashid_id(nm));
	}
	tok = check_param_sort(tok);
	id = make_token_decl(tok, tag, id, NULL_id);
	if (do_dump) {
		dump_token_param(id);
	}
	return id;
}


/*
    This routine looks up a member id of the class type t.  If the member
    is not found or t is not a class type then an error message is printed
    and the null identifier is returned.
*/

IDENTIFIER
tok_member(IDENTIFIER id, TYPE t, int force)
{
	if (IS_type_compound(t)) {
		HASHID nm = DEREF_hashid(id_name(id));
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		NAMESPACE ns = DEREF_nspace(ctype_member(ct));
		IDENTIFIER fid = search_id(ns, nm, 0, 0);
		if (IS_NULL_id(fid)) {
			/* Member not declared */
			if (force) {
				/* Report error */
				report(preproc_loc,
				       ERR_lookup_qual_bad(id, ns));
			} else {
				/* Create token member */
				TOKEN tok;
				HASHID fnm = lookup_anon();
				fid = DEREF_id(hashid_id(fnm));
				MAKE_tok_member(t, type_error, NULL_off, tok);
				fid = make_token_decl(tok, 0, id, fid);
				fid = DEREF_id(id_token_alt(fid));
			}
		}
		return fid;
	}
	report(preproc_loc, ERR_token_mem(t));
	return NULL_id;
}


/*
    This routine declares a token program parameter named id.  tt gives
    the associated token sort, while t gives the structure type if this
    denotes a member token or the parameter type if this denotes a type
    token.
*/

IDENTIFIER
prog_tok_param(IDENTIFIER id, TYPE t, unsigned tt, LIST(IDENTIFIER) p)
{
	/* Look up member identifier */
	IDENTIFIER tid = id;
	if (tt == tok_member_tag) {
		tid = tok_member(tid, t, 1);
		if (IS_NULL_id(tid)) {
			return NULL_id;
		}
	}

	/* Check through tokens */
	while (!IS_NULL_list(p)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(p));
		if (!IS_NULL_id(pid) && IS_id_token(pid)) {
			IDENTIFIER qid = DEREF_id(id_token_alt(pid));
			if (EQ_id(qid, tid)) {
				/* Matching token found */
				TOKEN tok = DEREF_tok(id_token_sort(pid));
				unsigned pt = TAG_tok(tok);
				switch (pt) {
				case tok_nat_tag:
				case tok_snat_tag:
					pt = tok_exp_tag;
					break;
				case tok_templ_tag:
				case tok_func_tag:
					pt = tok_proc_tag;
					break;
				}
				if (pt != tt) {
					/* Wrong sort given for token
					 * parameter */
					report(preproc_loc,
					       ERR_token_arg_sort(pid));
				}
				return pid;
			}
		}
		p = TAIL_list(p);
	}

	/* Allow for complex type parameters */
	if (tt == tok_type_tag) {
		HASHID nm = lookup_anon();
		int tq = crt_templ_qualifier;
		QUALIFIER cq = crt_id_qualifier;
		crt_id_qualifier = qual_none;
		crt_templ_qualifier = 0;
		tid = DEREF_id(hashid_id(nm));
		tid = make_object_decl(dspec_typedef, t, tid, 0);
		crt_templ_qualifier = tq;
		crt_id_qualifier = cq;
		return tid;
	}
	report(preproc_loc, ERR_token_arg_bad(tid));
	return NULL_id;
}


/*
    This routine returns the procedure token underlying the function
    token tok, creating this if necessary.
*/

TOKEN
func_proc_token(TOKEN tok)
{
	TOKEN res;
	if (!IS_tok_func(tok)) {
		return tok;
	}
	res = DEREF_tok(tok_func_proc(tok));
	if (IS_NULL_tok(res)) {
		TYPE t = DEREF_type(tok_func_type(tok));
		int ell = DEREF_int(type_func_ellipsis(t));
		if (ell & FUNC_ELLIPSIS) {
			res = tok;
		} else {
			TOKEN rtok;
			IDENTIFIER pid;
			EXP e = NULL_exp;
			LIST(IDENTIFIER) qids;
			IDENTIFIER fn = DEREF_id(tok_func_defn(tok));
			TYPE r = DEREF_type(type_func_ret(t));
			LIST(TYPE) p = DEREF_list(type_func_mtypes(t));
			LIST(IDENTIFIER) pids = NULL_list(IDENTIFIER);
			res = begin_proc_token();
			while (!IS_NULL_list(p)) {
				/* Normal function parameters */
				TYPE s = DEREF_type(HEAD_list(p));
				if (pass_complex_type(s)) {
					MAKE_type_ptr(cv_none, s, s);
				}
				MAKE_tok_exp(s, 0, NULL_exp, rtok);
				pid = make_tok_param(rtok, 0, NULL_id);
				CONS_id(pid, pids, pids);
				p = TAIL_list(p);
			}
			/* Extra constructor parameters ... */
			pids = REVERSE_list(pids);
			qids = pids;
			if (pass_complex_type(r)) {
				/* Complex function return */
				TYPE s;
				MAKE_type_ptr(cv_none, r, s);
				MAKE_tok_exp(s, 0, NULL_exp, rtok);
				pid = make_tok_param(rtok, 0, NULL_id);
				CONS_id(pid, pids, pids);
				r = type_void;
			}
			res = cont_proc_token(res, pids, qids);
			if (!IS_NULL_id(fn)) {
				/* Token already defined */
				MAKE_exp_value(t, e);
			}
			MAKE_tok_exp(r, 0, e, rtok);
			res = end_proc_token(res, rtok);
		}
		COPY_tok(tok_func_proc(tok), res);
	}
	return res;
}


/*
    This routine expands the token value tok. If force is true then a copy
    is always made.
*/

TOKEN
expand_sort(TOKEN tok, int rec, int force)
{
	if (!IS_NULL_tok(tok)) {
		unsigned tag = TAG_tok(tok);
		switch (tag) {
		case tok_exp_tag: {
			/* Expression tokens */
			EXP a1 = DEREF_exp(tok_exp_value(tok));
			EXP a2 = expand_exp(a1, rec, 0);
			if (force || !eq_exp_exact(a1, a2)) {
				int c = DEREF_int(tok_exp_constant(tok));
				TYPE t = DEREF_type(tok_exp_type(tok));
				t = expand_type(t, rec);
				MAKE_tok_exp(t, c, a2, tok);
			}
			break;
		}
		case tok_nat_tag:
		case tok_snat_tag: {
			/* Integral constant tokens */
			ERROR err = NULL_err;
			NAT n1 = DEREF_nat(tok_nat_etc_value(tok));
			NAT n2 = expand_nat(n1, rec, 0, &err);
			if (!IS_NULL_err(err)) {
				report(crt_loc, err);
			}
			if (force || !EQ_nat(n1, n2)) {
				MAKE_tok_nat_etc(tag, n2, tok);
			}
			break;
		}
		case tok_stmt_tag: {
			/* Statement tokens */
			EXP a1 = DEREF_exp(tok_stmt_value(tok));
			EXP a2 = expand_exp(a1, rec, 1);
			if (force || !eq_exp_exact(a1, a2)) {
				EXP b = get_parent_stmt(a1);
				set_parent_stmt(a2, b);
				MAKE_tok_stmt(a2, tok);
			}
			break;
		}
		case tok_member_tag: {
			/* Member tokens */
			OFFSET a1 = DEREF_off(tok_member_value(tok));
			OFFSET a2 = expand_offset(a1, rec);
			if (force || !EQ_off(a1, a2)) {
				TYPE s = DEREF_type(tok_member_of(tok));
				TYPE t = DEREF_type(tok_member_type(tok));
				s = expand_type(s, rec);
				t = expand_type(t, rec);
				MAKE_tok_member(s, t, a2, tok);
			}
			break;
		}
		case tok_type_tag: {
			/* Type tokens */
			TYPE t1 = DEREF_type(tok_type_value(tok));
			TYPE t2 = expand_type(t1, rec);
			if (force || !EQ_type(t1, t2)) {
				BASE_TYPE bs = DEREF_btype(tok_type_kind(tok));
				MAKE_tok_type(bs, t2, tok);
			}
			break;
		}
		case tok_class_tag: {
			/* Template class tokens */
			IDENTIFIER cid = DEREF_id(tok_class_value(tok));
			/* NOT YET IMPLEMENTED */
			if (force) {
				TYPE s = DEREF_type(tok_class_type(tok));
				TYPE t = DEREF_type(tok_class_alt(tok));
				MAKE_tok_class(s, cid, tok);
				COPY_type(tok_class_alt(tok), t);
			}
			break;
		}
		case tok_templ_tag: {
			/* Template tokens */
			if (force) {
				int d;
				LIST(IDENTIFIER) pids;
				LIST(IDENTIFIER) rids;
				LIST(IDENTIFIER) qids = NULL_list(IDENTIFIER);
				DECL_SPEC ds =
				    DEREF_dspec(tok_templ_usage(tok));
				NAMESPACE ns =
				    DEREF_nspace(tok_templ_pars(tok));
				pids = DEREF_list(tok_templ_pids(tok));
				rids = pids;
				d = save_token_args(rids, NULL_list(TOKEN));
				while (!IS_NULL_list(pids)) {
					/* Copy template parameters */
					TOKEN arg;
					IDENTIFIER qid2;
					IDENTIFIER pid =
					    DEREF_id(HEAD_list(pids));
					IDENTIFIER pid2 =
					    DEREF_id(id_token_alt(pid));
					IDENTIFIER qid = copy_id(pid, 2);
					DECL_SPEC qds =
					    DEREF_dspec(id_storage(qid));
					qds |= dspec_pure;
					COPY_dspec(id_storage(qid), qds);
					arg = apply_token(qid,
							  NULL_list(TOKEN));
					assign_token(pid, arg);
					qid2 = copy_id(pid2, 2);
					COPY_id(id_token_alt(qid), qid2);
					CONS_id(qid, qids, qids);
					pids = TAIL_list(pids);
				}
				restore_token_args(rids, d);
				MAKE_tok_templ(ds, ns, tok);
				qids = REVERSE_list(qids);
				COPY_list(tok_templ_pids(tok), qids);
				set_proc_token(qids);
			}
			break;
		}
		}
	}
	return tok;
}


/*
    This routine expands the list of token arguments p passing the parameter
    rec to the individual expansion routines.  The null list is returned to
    indicate that the expansion has no effect.
*/

LIST(TOKEN)
expand_args(LIST(TOKEN) p, int rec, int force)
{
	int changed = 0;
	LIST(TOKEN) q = NULL_list(TOKEN);
	while (!IS_NULL_list(p)) {
		TOKEN a = DEREF_tok(HEAD_list(p));
		TOKEN b = expand_sort(a, rec, force);
		if (!EQ_tok(a, b)) {
			changed = 1;
		}
		CONS_tok(b, q, q);
		p = TAIL_list(p);
	}
	if (!changed) {
		/* No effect */
		DESTROY_list(q, SIZE_tok);
		return NULL_list(TOKEN);
	}
	q = REVERSE_list(q);
	return q;
}


/*
    This routine copies the given template sort producing a new sort
    comprising only those parameters which are unbound.  If all the
    parameters are bound then the null sort is returned.
*/

TOKEN
expand_templ_sort(TOKEN sort, int rec)
{
	NAMESPACE ns;
	int changed = 0;
	int all_unbound = 1;
	LIST(TOKEN) dargs = NULL_list(TOKEN);
	DECL_SPEC ex = DEREF_dspec(tok_templ_usage(sort));
	LIST(IDENTIFIER) p = DEREF_list(tok_templ_pids(sort));
	LIST(IDENTIFIER) q = NULL_list(IDENTIFIER);
	LIST(IDENTIFIER) p0 = p;
	while (!IS_NULL_list(p)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(p));
		if (!IS_NULL_id(pid) && IS_id_token(pid)) {
			TOKEN tok = DEREF_tok(id_token_sort(pid));
			if (is_bound_tok(tok, 0)) {
				/* Have bound parameter */
				all_unbound = 0;
				changed = 1;
			} else {
				/* Add unbound parameter to list */
				/* NOT YET IMPLEMENTED */
				CONS_id(pid, q, q);
			}
		}
		p = TAIL_list(p);
	}
	if (IS_NULL_list(q)) {
		/* All parameters are bound */
		return NULL_tok;
	}
	if (changed) {
		/* Get unbound parameters into order */
		q = REVERSE_list(q);
	} else {
		/* Use existing list */
		DESTROY_list(q, SIZE_id);
		q = p0;
	}
	if (all_unbound) {
		/* Preserve instances and default arguments */
		LIST(TOKEN) d;
		dargs = DEREF_list(tok_templ_dargs(sort));
		d = expand_args(dargs, rec, 0);
		if (!IS_NULL_list(d)) {
			dargs = d;
		}
	}
	ns = DEREF_nspace(tok_templ_pars(sort));
	MAKE_tok_templ(ex, ns, sort);
	COPY_list(tok_templ_pids(sort), q);
	COPY_list(tok_templ_dargs(sort), dargs);
	return sort;
}


/*
    This routine is called at the end of the expansion of a template
    type to restore the sort produced by expand_templ_sort.
*/

void
reset_templ_sort(TOKEN sort)
{
	UNUSED(sort);
	return;
}


/*
    This routine expands any token definitions in the expression e.
    rec gives the level of expansion, 0 for just the top level, 1 for a
    complete recursive expansion, and 2 for a recursive expansion of
    token parameters only.  Negative values just return e.
*/

EXP
expand_exp(EXP e, int rec, int stmt)
{
	unsigned etag;
	if (rec < 0) {
		return e;
	}
	if (IS_NULL_exp(e)) {
		return NULL_exp;
	}
	etag = TAG_exp(e);
	if (etag == exp_token_tag) {
		/* Tokenised values */
		TOKEN tok;
		DECL_SPEC ds;
		unsigned tag;
		IDENTIFIER id = DEREF_id(exp_token_tok(e));
		IDENTIFIER aid = DEREF_id(id_alias(id));
		LIST(TOKEN) p = DEREF_list(exp_token_args(e));
		if (!EQ_id(id, aid)) {
			/* Replace token by its alias */
			e = apply_exp_token(aid, p, 1);
			id = aid;
		}
		ds = DEREF_dspec(id_storage(id));
		tok = DEREF_tok(id_token_sort(id));
		tag = TAG_tok(tok);
		if (tag == tok_proc_tag) {
			tok = DEREF_tok(tok_proc_res(tok));
			tag = TAG_tok(tok);
		}
		if (rec) {
			/* Expand token arguments */
			p = expand_args(p, rec, 1);
			e = apply_exp_token(id, p, rec);
		}
		/* if ( rec == 2 && !( ds & dspec_auto ) ) break ; */
		if (ds & dspec_temp) {
			/* Check for recursive token expansions */
			report(crt_loc, ERR_token_recursive(id));
			return make_error_exp(0);
		}
		COPY_dspec(id_storage(id), (ds | dspec_temp));
		if (tag == tok_exp_tag) {
			EXP a = DEREF_exp(tok_exp_value(tok));
			if (!IS_NULL_exp(a)) {
				/* Expand token definition */
				e = expand_exp(a, rec, 0);
				if (ds & dspec_auto) {
					COPY_exp(tok_exp_value(tok), e);
				}
			}
		} else if (tag == tok_stmt_tag) {
			EXP a = DEREF_exp(tok_stmt_value(tok));
			if (!IS_NULL_exp(a)) {
				/* Expand token definition */
				EXP b = get_parent_stmt(a);
				e = expand_exp(a, rec, 1);
				set_parent_stmt(e, b);
				if (ds & dspec_auto) {
					COPY_exp(tok_stmt_value(tok), e);
				}
			}
		}
		COPY_dspec(id_storage(id), ds);

	} else if (etag == exp_int_lit_tag) {
		/* Integer constants */
		ERROR err = NULL_err;
		NAT n1 = DEREF_nat(exp_int_lit_nat(e));
		NAT n2 = expand_nat(n1, rec, 0, &err);
		if (rec || !EQ_nat(n1, n2)) {
			TYPE t = DEREF_type(exp_type(e));
			unsigned tag = DEREF_unsigned(exp_int_lit_etag(e));
			MAKE_exp_int_lit(t, n2, tag, e);
			if (!IS_NULL_err(err)) {
				report(crt_loc, err);
			}
		}
	} else {
		/* Other cases */
		if (rec && !stmt) {
			e = copy_exp(e, NULL_type, NULL_type);
		}
	}
	return e;
}


/*
    This routine expands any token definitions in the integer constant
    expression n.  rec is as above, ch is as in eval_exp.
*/

NAT
expand_nat(NAT n, int rec, int ch, ERROR *err)
{
	if (rec < 0) {
		return n;
	}
	if (IS_NULL_nat(n)) {
		return NULL_nat;
	}
	switch (TAG_nat(n)) {
	case nat_calc_tag: {
		/* Calculated values */
		EXP e2;
		EXP e1 = DEREF_exp(nat_calc_value(n));
		ulong tok = DEREF_ulong(nat_calc_tok(n));
		if (rec) {
			e2 = eval_exp(e1, ch);
		} else {
			e2 = expand_exp(e1, 0, 0);
		}
		e2 = convert_reference(e2, REF_NORMAL);
		e2 = convert_lvalue(e2);
		if (!EQ_exp(e1, e2) && !eq_exp_exact(e1, e2)) {
			n = make_nat_exp(e2, err);
			if (IS_nat_calc(n)) {
				COPY_ulong(nat_calc_tok(n), tok);
			}
		}
		break;
	}
	case nat_token_tag: {
		/* Tokenised values */
		TOKEN tok;
		DECL_SPEC ds;
		unsigned tag;
		IDENTIFIER id = DEREF_id(nat_token_tok(n));
		IDENTIFIER aid = DEREF_id(id_alias(id));
		LIST(TOKEN)p = DEREF_list(nat_token_args(n));
		if (!EQ_id(id, aid)) {
			/* Replace token by its alias */
			n = apply_nat_token(aid, p);
			id = aid;
		}
		ds = DEREF_dspec(id_storage(id));
		tok = DEREF_tok(id_token_sort(id));
		tag = TAG_tok(tok);
		if (tag == tok_proc_tag) {
			if (rec) {
				/* Expand token arguments */
				p = expand_args(p, rec, 0);
				if (!IS_NULL_list(p)) {
					n = apply_nat_token(id, p);
				}
			}
			tok = DEREF_tok(tok_proc_res(tok));
			tag = TAG_tok(tok);
		}
		/* if ( rec == 2 && !( ds & dspec_auto ) ) break ; */
		if (ds & dspec_temp) {
			/* Check for recursive token expansions */
			report(crt_loc, ERR_token_recursive(id));
			return small_nat[1];
		}
		COPY_dspec(id_storage(id), (ds | dspec_temp));
		if (tag == tok_nat_tag || tag == tok_snat_tag) {
			NAT m = DEREF_nat(tok_nat_etc_value(tok));
			if (!IS_NULL_nat(m)) {
				/* Expand token definition */
				n = expand_nat(m, rec, ch, err);
				if (ds & dspec_auto) {
					COPY_nat(tok_nat_etc_value(tok), n);
				}
			}
		}
		COPY_dspec(id_storage(id), ds);
		break;
	}
	}
	return n;
}


/*
    This routine expands any token definitions in the offset off.  rec
    is as above.
*/

OFFSET
expand_offset(OFFSET off, int rec)
{
	if (rec > 0) {
		off = copy_offset(off, lex_plus);
	}
	return off;
}


/*
    This routine is a special case of expand_type which deals with
    template types.
*/

static TYPE
expand_templ_type(TYPE t, int rec)
{
	CV_SPEC cv = DEREF_cv(type_qual(t));
	TYPE s = DEREF_type(type_templ_defn(t));
	TOKEN sort = DEREF_tok(type_templ_sort(t));
	sort = expand_templ_sort(sort, rec);
	if (IS_type_compound(s)) {
		/* Template classes */
		s = copy_class(s, dspec_instance);
	} else {
		/* Other template types */
		s = expand_type(s, rec);
	}
	if (IS_NULL_tok(sort)) {
		/* No unbound parameters */
		t = qualify_type(s, cv, 0);
	} else {
		/* Unbound parameters - result is a specialisation */
		MAKE_type_templ(cv, sort, s, 1, t);
	}
	reset_templ_sort(sort);
	return t;
}


/*
    This routine expands the list of exception types p, setting changed to
    true if any changes.
*/

LIST(TYPE)
expand_exceptions(LIST(TYPE) p, int rec, int *changed)
{
	LIST(TYPE) q = NULL_list(TYPE);
	if (EQ_list(p, univ_type_set)) {
		q = p;
	} else if (EQ_list(p, empty_type_set)) {
		q = p;
	} else {
		while (!IS_NULL_list(p)) {
			TYPE s1 = DEREF_type(HEAD_list(p));
			TYPE s2 = expand_type(s1, rec);
			if (!EQ_type(s1, s2)) {
				s2 = check_except_type(s2, 0);
				*changed = 1;
			}
			CONS_type(s2, q, q);
			p = TAIL_list(p);
		}
		q = REVERSE_list(q);
	}
	return q;
}


/*
    This routine is a special case of expand_type which deals with
    function types.  rec will not be zero.
*/

static TYPE
expand_func_type(TYPE t, int rec)
{
	int mf = 0;
	int expanded = 0;
	TYPE r1 = DEREF_type(type_func_ret(t));
	TYPE r2;
	LIST(TYPE) p1 = DEREF_list(type_func_ptypes(t));
	LIST(TYPE) p2;
	LIST(TYPE) m1 = DEREF_list(type_func_mtypes(t));
	LIST(TYPE) m2 = NULL_list(TYPE);
	LIST(TYPE) e1 = DEREF_list(type_func_except(t));
	LIST(TYPE) e2;
	if (!EQ_list(p1, m1)) {
		if (!IS_NULL_list(m1) && EQ_list(p1, TAIL_list(m1))) {
			/* Normal member function type */
			mf = 1;
		} else {
			/* Swapped member function type */
			mf = -1;
			m1 = p1;
		}
	}

	/* Copy return type */
	r2 = expand_type(r1, rec);
	if (!EQ_type(r1, r2)) {
		expanded = 1;
	}

	/* Copy parameter types */
	while (!IS_NULL_list(m1)) {
		TYPE s1 = DEREF_type(HEAD_list(m1));
		TYPE s2 = expand_type(s1, rec);
		if (!EQ_type(s1, s2)) {
			expanded = 1;
		}
		CONS_type(s2, m2, m2);
		m1 = TAIL_list(m1);
	}
	m2 = REVERSE_list(m2);

	/* Copy exception types */
	e2 = expand_exceptions(e1, rec, &expanded);

	/* Check for default arguments */
	if (!expanded) {
		LIST(IDENTIFIER) pids = DEREF_list(type_func_pids(t));
		while (!IS_NULL_list(pids)) {
			IDENTIFIER id = DEREF_id(HEAD_list(pids));
			EXP e = DEREF_exp(id_parameter_init(id));
			if (!IS_NULL_exp(e)) {
				if (depends_on_exp(e, any_token_param, 0)) {
					/* Needs expansion */
					expanded = 1;
					break;
				}
			}
			pids = TAIL_list(pids);
		}
	}

	/* Expand remaining items */
	if (expanded) {
		CV_SPEC cv = DEREF_cv(type_qual(t));
		CV_SPEC mq = DEREF_cv(type_func_mqual(t));
		int ell = DEREF_int(type_func_ellipsis(t));
		NAMESPACE pars = DEREF_nspace(type_func_pars(t));
		LIST(IDENTIFIER) pids = DEREF_list(type_func_pids(t));
		LIST(IDENTIFIER) qids = NULL_list(IDENTIFIER);

		/* Copy parameters */
		while (!IS_NULL_list(pids)) {
			TYPE s;
			IDENTIFIER id = DEREF_id(HEAD_list(pids));
			IDENTIFIER lid = chase_alias(id);
			EXP e = DEREF_exp(id_parameter_init(id));
			id = copy_id(id, 2);
			COPY_id(id_alias(id), lid);
			s = DEREF_type(id_parameter_type(id));
			check_par_decl(s, id, CONTEXT_WEAK_PARAM);
			if (!IS_NULL_exp(e)) {
				/* Copy default argument */
				EXP d;
				e = expand_exp(e, rec, 0);
				e = init_general(s, e, id, 0);
				d = destroy_general(s, id);
				COPY_exp(id_parameter_term(id), d);
				COPY_exp(id_parameter_init(id), e);
			}
			CONS_id(id, qids, qids);
			pids = TAIL_list(pids);
		}
		qids = REVERSE_list(qids);

		/* Form function type */
		if (mf == 0) {
			p2 = m2;
		} else if (mf == 1) {
			p2 = TAIL_list(m2);
		} else {
			p2 = m2;
			m2 = TAIL_list(p2);
		}
		MAKE_type_func(cv, NULL_type, p2, ell, mq, m2, pars, qids, e2,
			       t);
		t = inject_pre_type(t, r2, 0);
	} else {
		/* Free unused type lists */
		if (!EQ_list(m2, m1)) {
			DESTROY_list(m2, SIZE_type);
		}
		if (!EQ_list(e2, e1)) {
			DESTROY_list(e2, SIZE_type);
		}
	}
	return t;
}


/*
    This routine expands the class type ct by rescanning its name in the
    current context.  It returns the null type if the result is not a
    type name.
*/

static TYPE
rescan_class(CLASS_TYPE ct)
{
	IDENTIFIER cid = DEREF_id(ctype_name(ct));
	TYPE t = find_typename(cid, NULL_list(TOKEN), btype_none, 1);
	return t;
}


/*
    This routine expands the enumeration type et by rescanning its name
    in the current context.  It returns the null type if the result is
    not a type name.
*/

static TYPE
rescan_enum(ENUM_TYPE et)
{
	IDENTIFIER eid = DEREF_id(etype_name(et));
	TYPE t = find_typename(eid, NULL_list(TOKEN), btype_none, 1);
	return t;
}


/*
    This routine expands any token definitions in the class type ct.
    rec is as above.  The null class is returned if the result is not
    a class type with the actual type being assigned to pt.
*/

CLASS_TYPE
expand_ctype(CLASS_TYPE ct, int rec, TYPE *pt)
{
	if (rec >= 0) {
		TYPE s = NULL_type;
		TYPE t = DEREF_type(ctype_form(ct));
		if (!IS_NULL_type(t)) {
			if (IS_type_token(t)) {
				IDENTIFIER id = DEREF_id(type_token_tok(t));
				LIST(TOKEN) p = DEREF_list(type_token_args(t));
				if (IS_id_token(id)) {
					/* Tokenised classes */
					s = expand_type(t, rec);
				} else if (rec) {
					/* Template classes */
					p = expand_args(p, rec, 0);
					if (!IS_NULL_list(p)) {
						/* Template class instance */
						id = instance_type(id, p, 0, 1);
						s = DEREF_type(id_class_name_defn(id));
						while (IS_type_templ(s)) {
							s = DEREF_type(type_templ_defn(s));
						}
					}
				}
				if (EQ_type(s, t)) {
					/* No expansion possible */
					return ct;
				}
			} else if (IS_type_instance(t)) {
				s = rescan_class(ct);
				if (EQ_type(s, t)) {
					/* No expansion possible */
					return ct;
				}
			} else {
				/* Recursive template classes */
				s = expand_type(t, rec);
			}
		} else {
			CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
			if (ci & cinfo_rescan)s = rescan_class(ct);
		}
		if (!IS_NULL_type(s)) {
			if (IS_type_compound(s)) {
				ct = DEREF_ctype(type_compound_defn(s));
			} else {
				*pt = s;
				if (is_templ_type(s)) {
					IDENTIFIER id =
					    DEREF_id(type_token_tok(s));
					ct = find_class(id);
				} else {
					ct = NULL_ctype;
				}
			}
		}
	}
	return ct;
}


/*
    This flag may be set to true to allow for zero sized bitfields in
    expand_type.  The only way this can occur is in the expansion
    of an anonymous member type.
*/

int expand_anon_bitfield = 0;


/*
    This routine expands any token definitions in the type t.  rec is
    as above.
*/

TYPE
expand_type(TYPE t, int rec)
{
	CV_SPEC cv;
	int prom = 0;
	IDENTIFIER id;
	LIST(TOKEN) p;
	if (rec < 0) {
		return t;
	}
	if (IS_NULL_type(t)) {
		return NULL_type;
	}
	cv = DEREF_cv(type_qual(t));
	assert(ORDER_type == 18);
	switch (TAG_type(t)) {
	case type_integer_tag: {
		/* Integral types */
		INT_TYPE it = DEREF_itype(type_integer_rep(t));
		unsigned tag = TAG_itype(it);
		if (tag == itype_arith_tag) {
			/* Expand arithmetic types */
			INT_TYPE ir = DEREF_itype(itype_arith_arg1(it));
			INT_TYPE is = DEREF_itype(itype_arith_arg2(it));
			TYPE r1 = DEREF_type(itype_prom(ir));
			TYPE r2 = expand_type(r1, rec);
			TYPE s1 = DEREF_type(itype_prom(is));
			TYPE s2 = expand_type(s1, rec);
			if (!EQ_type(r1, r2) || !EQ_type(s1, s2)) {
				t = arith_type(r2, s2, NULL_exp, NULL_exp);
				if (cv) {
					t = qualify_type(t, cv, 0);
				}
			}
		} else {
			/* Expand other integral types */
			if (tag == itype_promote_tag) {
				it = DEREF_itype(itype_promote_arg(it));
				tag = TAG_itype(it);
				prom = 1;
			}
			if (tag == itype_token_tag) {
				id = DEREF_id(itype_token_tok(it));
				p = DEREF_list(itype_token_args(it));
				goto expand_label;
			}
			if (tag == itype_basic_tag) {
				/* Allow for special tokens */
				BUILTIN_TYPE n =
				    DEREF_ntype(itype_basic_no(it));
				id = get_special(base_token[n].tok, 0);
				if (!IS_NULL_id(id)) {
					p = NULL_list(TOKEN);
					goto expand_label;
				}
			}
		}
		break;
	}
	case type_floating_tag: {
		/* Floating point types */
		FLOAT_TYPE ft = DEREF_ftype(type_floating_rep(t));
		unsigned tag = TAG_ftype(ft);
		if (tag == ftype_arith_tag) {
			/* Expand arithmetic types */
			FLOAT_TYPE fr = DEREF_ftype(ftype_arith_arg1(ft));
			FLOAT_TYPE fs = DEREF_ftype(ftype_arith_arg2(ft));
			TYPE r1 = make_ftype(fr, NULL_ftype);
			TYPE r2 = expand_type(r1, rec);
			TYPE s1 = make_ftype(fs, NULL_ftype);
			TYPE s2 = expand_type(s1, rec);
			if (!EQ_type(r1, r2) || !EQ_type(s1, s2)) {
				t = arith_type(r2, s2, NULL_exp, NULL_exp);
				if (cv) {
					t = qualify_type(t, cv, 0);
				}
			}
		} else {
			/* Expand other floating point types */
			if (tag == ftype_arg_promote_tag) {
				ft = DEREF_ftype(ftype_arg_promote_arg(ft));
				tag = TAG_ftype(ft);
				prom = 2;
			}
			if (tag == ftype_token_tag) {
				id = DEREF_id(ftype_token_tok(ft));
				p = DEREF_list(ftype_token_args(ft));
				goto expand_label;
			}
		}
		break;
	}
	case type_ptr_tag:
		/* Pointer types */
		if (rec) {
			TYPE s1 = DEREF_type(type_ptr_sub(t));
			TYPE s2 = expand_type(s1, rec);
			if (!EQ_type(s1, s2)) {
				if (TAG_type(s1) == TAG_type(s2)) {
					/* Don't check in this case */
					MAKE_type_ptr(cv, s2, t);
				} else {
					MAKE_type_ptr(cv, NULL_type, t);
					t = inject_pre_type(t, s2, 0);
				}
			}
		}
		break;
	case type_ref_tag:
		/* Reference types */
		if (rec) {
			TYPE s1 = DEREF_type(type_ref_sub(t));
			TYPE s2 = expand_type(s1, rec);
			if (!EQ_type(s1, s2)) {
				MAKE_type_ref(cv, NULL_type, t);
				t = inject_pre_type(t, s2, 0);
			}
		}
		break;
	case type_ptr_mem_tag: {
		/* Pointer to member types */
		if (rec) {
			TYPE r2 = NULL_type;
			CLASS_TYPE c1 = DEREF_ctype(type_ptr_mem_of(t));
			CLASS_TYPE c2 = expand_ctype(c1, rec, &r2);
			TYPE s1 = DEREF_type(type_ptr_mem_sub(t));
			TYPE s2 = expand_type(s1, rec);
			if (!EQ_ctype(c1, c2)) {
				if (IS_NULL_ctype(c2)) {
					/* Illegal class type expansion */
					report(crt_loc, ERR_dcl_mptr_class(r2));
					MAKE_type_ptr(cv, NULL_type, t);
				} else {
					MAKE_type_ptr_mem(cv, c2, NULL_type, t);
				}
				t = inject_pre_type(t, s2, 0);
			} else if (!EQ_type(s1, s2)) {
				MAKE_type_ptr_mem(cv, c1, NULL_type, t);
				t = inject_pre_type(t, s2, 0);
			}
		}
		break;
	}
	case type_func_tag:
		/* Function types */
		if (rec) {
			t = expand_func_type(t, rec);
		}
		break;
	case type_array_tag:
		/* Array types */
		if (rec) {
			ERROR err = NULL_err;
			TYPE s1 = DEREF_type(type_array_sub(t));
			TYPE s2 = expand_type(s1, rec);
			NAT n1 = DEREF_nat(type_array_size(t));
			NAT n2 = expand_nat(n1, rec, 0, &err);
			if (!EQ_nat(n1, n2)) {
				if (!IS_NULL_err(err)) {
					ERROR err2 = ERR_dcl_array_dim_const();
					err = concat_error(err, err2);
					report(crt_loc, err);
				}
				n2 = check_array_dim(n2);
				MAKE_type_array(cv, NULL_type, n2, t);
				t = inject_pre_type(t, s2, 0);
			} else if (!EQ_type(s1, s2)) {
				MAKE_type_array(cv, NULL_type, n2, t);
				t = inject_pre_type(t, s2, 0);
			}
		}
		break;
	case type_bitfield_tag:
		/* Bitfield types */
		if (rec) {
			ERROR err = NULL_err;
			INT_TYPE it = DEREF_itype(type_bitfield_defn(t));
			TYPE s1 = DEREF_type(itype_bitfield_sub(it));
			NAT n1 = DEREF_nat(itype_bitfield_size(it));
			TYPE s2 = expand_type(s1, rec);
			NAT n2 = expand_nat(n1, rec, 0, &err);
			if (!EQ_type(s1, s2) || !EQ_nat(n1, n2)) {
				BASE_TYPE rep;
				int anon = expand_anon_bitfield;
				rep = DEREF_btype(itype_bitfield_rep(it));
				if (!IS_NULL_err(err)) {
					ERROR err2 = ERR_class_bit_dim_const();
					err = concat_error(err, err2);
					report(crt_loc, err);
				}
				rep = get_bitfield_rep(s2, rep);
				t = check_bitfield_type(cv, s2, rep, n2, anon);
			}
		}
		break;
	case type_compound_tag: {
		/* Class types */
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		TYPE s = DEREF_type(ctype_form(ct));
		if (!IS_NULL_type(s)) {
			if (IS_type_token(s)) {
				/* Tokenised and template classes */
				id = DEREF_id(type_token_tok(s));
				p = DEREF_list(type_token_args(s));
				if (IS_id_token(id)) {
					goto expand_label;
				}
				if (rec) {
					p = expand_args(p, rec, 0);
					if (!IS_NULL_list(p)) {
						/* Template class instance */
						id = instance_type(id, p, 0, 1);
						t = DEREF_type(id_class_name_defn(id));
						while (IS_type_templ(t)) {
							t = DEREF_type(type_templ_defn(t));
						}
						if (cv) {
							t = qualify_type(t, cv, 0);
						}
					}
				}
			} else if (IS_type_instance(s)) {
				s = rescan_class(ct);
				if (!IS_NULL_type(s)) {
					t = s;
					if (cv) {
						t = qualify_type(t, cv, 0);
					}
				}
			} else {
				/* Recursive template classes */
				t = expand_type(s, rec);
				if (cv) {
					t = qualify_type(t, cv, 0);
				}
			}
		} else {
			CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
			if (ci & cinfo_rescan) {
				/* Force rescan */
				s = rescan_class(ct);
				if (!IS_NULL_type(s)) {
					t = s;
					if (cv) {
						t = qualify_type(t, cv, 0);
					}
				}
			}
		}
		break;
	}
	case type_enumerate_tag: {
		/* Enumeration types */
		ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
		CLASS_INFO ei = DEREF_cinfo(etype_info(et));
		if (ei & cinfo_rescan) {
			/* Force rescan */
			TYPE s = rescan_enum(et);
			if (!IS_NULL_type(s)) {
				t = s;
				if (cv) {
					t = qualify_type(t, cv, 0);
				}
			}
		}
		break;
	}
	case type_token_tag:
		/* Tokenised types */
		id = DEREF_id(type_token_tok(t));
		p = DEREF_list(type_token_args(t));
expand_label: {
		      TOKEN tok;
		      unsigned tag;
		      DECL_SPEC ds;
		      IDENTIFIER aid;
		      int changed = 0;
		      if (!IS_id_token(id)) {
			      break;
		      }
		      aid = DEREF_id(id_alias(id));
		      if (!EQ_id(id, aid)) {
			      /* Replace token by its alias */
			      t = apply_type_token(aid, p, NULL_id);
			      changed = 1;
			      id = aid;
		      }
		      ds = DEREF_dspec(id_storage(id));
		      tok = DEREF_tok(id_token_sort(id));
		      tag = TAG_tok(tok);
		      if (tag == tok_proc_tag) {
			      if (rec) {
				      /* Expand token arguments */
				      p = expand_args(p, rec, 0);
				      if (!IS_NULL_list(p)) {
					      t = apply_type_token(id, p,
								   NULL_id);
					      changed = 1;
				      }
			      }
			      tok = DEREF_tok(tok_proc_res(tok));
			      tag = TAG_tok(tok);
		      }
		      /* if ( rec == 2 && !( ds & dspec_auto ) ) break ; */
		      if (ds & dspec_temp) {
			      /* Check for recursive token expansions */
			      report(crt_loc, ERR_token_recursive(id));
			      return type_error;
		      }
		      COPY_dspec(id_storage(id), (ds | dspec_temp));
		      if (tag == tok_type_tag) {
			      /* Tokenised type */
			      TYPE s = DEREF_type(tok_type_value(tok));
			      if (!IS_NULL_type(s)) {
				      /* Expand token definition */
				      t = expand_type(s, rec);
				      if (ds & dspec_auto) {
					      COPY_type(tok_type_value(tok), t);
				      }
				      changed = 1;
			      } else {
				      BASE_TYPE bt;
				      bt = DEREF_btype(tok_type_kind(tok));
				      if (bt & btype_typename) {
					      /* Allow for typename */
					      s = find_typename(id, p, bt, 0);
					      if (!IS_NULL_type(s)) {
						      t = expand_type(s, rec);
						      changed = 1;
					      }
				      }
			      }
		      } else if (tag == tok_class_tag) {
			      /* Template template parameter */
			      aid = DEREF_id(tok_class_value(tok));
			      if (!IS_NULL_id(aid) && rec) {
				      p = expand_args(p, rec, 1);
				      aid = apply_template(aid, p, 0, 0);
				      if (IS_id_class_name_etc(aid)) {
					      t = DEREF_type(id_class_name_etc_defn(aid));
					      changed = 1;
				      }
			      }
		      }
		      if (changed) {
			      /* Qualify modified type */
			      if (prom == 1) {
				      t = promote_type(t);
			      } else if (prom == 2) {
				      t = arg_promote_type(t, KILL_err);
			      }
			      if (cv) {
				      CV_SPEC qual = DEREF_cv(type_qual(t));
				      t = qualify_type(t,(qual | cv), 0);
			      }
		      }
		      COPY_dspec(id_storage(id), ds);
	      }
	      break;
	case type_templ_tag:
		/* Template types */
		t = expand_templ_type(t, rec);
		break;
	}
	return t;
}


/*
    This routine applies the expression, statement or integer constant
    token id to the arguments args.  If rec is true then the result
    type is expanded.
*/

EXP
apply_exp_token(IDENTIFIER id, LIST(TOKEN) args, int rec)
{
	EXP e;
	int is_proc = 0;
	TOKEN tok = DEREF_tok(id_token_sort(id));
	unsigned tag = TAG_tok(tok);
	if (tag == tok_func_tag) {
		tok = func_proc_token(tok);
		tag = TAG_tok(tok);
	}
	if (tag == tok_proc_tag) {
		is_proc = 1;
		tok = DEREF_tok(tok_proc_res(tok));
		tag = TAG_tok(tok);
	}
	switch (tag) {
	case tok_exp_tag: {
		/* Expression tokens */
		int pt = in_proc_token;
		TYPE t = DEREF_type(tok_exp_type(tok));
		int c = DEREF_int(tok_exp_constant(tok));
		if (rec > 0) {
			t = expand_type(t, rec);
		} else if (pt) {
			in_proc_token = 0;
			t = expand_type(t, 2);
			in_proc_token = pt;
		}
		t = convert_qual_type(t);
		MAKE_exp_token(t, id, args, e);
		if (c) {
			/* Check for integer constant tokens */
			unsigned tt = TAG_type(t);
			if (tt == type_integer_tag ||
			    tt == type_enumerate_tag) {
				NAT n;
				MAKE_nat_calc(e, n);
				MAKE_exp_int_lit(t, n, exp_token_tag, e);
			}
		} else {
			/* Allow for exceptions */
			if (is_proc) {
				IGNORE check_throw(NULL_type, 0);
			}
		}
		break;
	}
	case tok_stmt_tag:
		/* Statement tokens */
		MAKE_exp_token(type_void, id, args, e);
		while (!IS_NULL_list(args)) {
			TOKEN arg = DEREF_tok(HEAD_list(args));
			if (IS_tok_stmt(arg)) {
				/* Set parent statement for arguments */
				EXP a = DEREF_exp(tok_stmt_value(arg));
				set_parent_stmt(a, e);
			}
			args = TAIL_list(args);
		}
		IGNORE check_throw(NULL_type, 0);
		break;
	case tok_nat_tag:
	case tok_snat_tag: {
		/* Integer constant tokens */
		NAT n;
		MAKE_nat_token(id, args, n);
		MAKE_exp_int_lit(type_sint, n, exp_token_tag, e);
		break;
	}
	default:
		/* Other tokens */
		e = NULL_exp;
		break;
	}
	return e;
}


/*
    This routine applies the integer constant token id to the arguments args.
*/

NAT
apply_nat_token(IDENTIFIER id, LIST(TOKEN) args)
{
	NAT n;
	TOKEN tok = DEREF_tok(id_token_sort(id));
	unsigned tag = TAG_tok(tok);
	if (tag == tok_proc_tag) {
		tok = DEREF_tok(tok_proc_res(tok));
		tag = TAG_tok(tok);
	}
	if (tag == tok_nat_tag || tag == tok_snat_tag) {
		MAKE_nat_token(id, args, n);
	} else {
		n = NULL_nat;
	}
	return n;
}


/*
    Certain language extensions are implemented as built-in tokens (see
    define_keyword).  This routine applies such a token, given by the
    keyword lex, to the arguments args.
*/

static TYPE
key_type_token(int lex, LIST(TOKEN) args)
{
	TYPE t = NULL_type;
	switch (lex) {
	case lex_representation: {
		TOKEN arg = DEREF_tok(HEAD_list(args));
		t = DEREF_type(tok_type_value(arg));
		if (!IS_NULL_type(t) && IS_type_integer(t)) {
			TYPE s;
			args = TAIL_list(args);
			arg = DEREF_tok(HEAD_list(args));
			s = DEREF_type(tok_type_value(arg));
			if (!IS_NULL_type(s) && IS_type_integer(s)) {
				INT_TYPE it = DEREF_itype(type_integer_rep(t));
				INT_TYPE is = DEREF_itype(type_integer_rep(s));
				t = make_itype(it, is);
			}
		}
		break;
	}
	case lex_typeof: {
		TOKEN arg = DEREF_tok(HEAD_list(args));
		EXP e = DEREF_exp(tok_exp_value(arg));
		if (!IS_NULL_exp(e)) {
			t = DEREF_type(exp_type(e));
			if (IS_type_bitfield(t)) {
				t = promote_type(t);
			}
		}
		break;
	}
	}
	return t;
}


/*
    This routine applies the type token id to the arguments args.  tid
    gives the name, if any, to be given to any class created.
*/

TYPE
apply_type_token(IDENTIFIER id, LIST(TOKEN) args, IDENTIFIER tid)
{
	TYPE t;
	int pt = in_proc_token;
	TOKEN tok = DEREF_tok(id_token_sort(id));
	unsigned tag = TAG_tok(tok);
	if (tag == tok_proc_tag) {
		int lex = DEREF_int(tok_proc_key(tok));
		if (lex != lex_identifier) {
			t = key_type_token(lex, args);
			if (!IS_NULL_type(t)) {
				return t;
			}
		}
		tok = DEREF_tok(tok_proc_res(tok));
		tag = TAG_tok(tok);
	}
	if (tag == tok_type_tag) {
		BASE_TYPE bt = DEREF_btype(tok_type_kind(tok));
		if (bt & btype_scalar) {
			/* Scalar types */
			t = apply_itype_token(id, args);

		} else if (bt & btype_named) {
			/* Structure and union types */
			TYPE s;
			CLASS_TYPE ct;
			CLASS_INFO ci;
			int tq = crt_templ_qualifier;
			QUALIFIER cq = crt_id_qualifier;
			int td = have_type_declaration;
			if (IS_NULL_id(tid)) {
				/* Make up class name if necessary */
				HASHID tnm = lookup_anon();
				tid = DEREF_id(hashid_id(tnm));
			}

			/* Define the class */
			crt_id_qualifier = qual_none;
			crt_templ_qualifier = 0;
			tid = begin_class_defn(tid, bt, cinfo_token, NULL_type);
			if (IS_NULL_list(args)) {
				COPY_id(id_token_alt(id), tid);
			}
			t = DEREF_type(id_class_name_etc_defn(tid));
			while (IS_type_templ(t)) {
				t = DEREF_type(type_templ_defn(t));
			}
			ct = DEREF_ctype(type_compound_defn(t));
			ci = DEREF_cinfo(ctype_info(ct));
			ci &= ~cinfo_empty;
			COPY_cinfo(ctype_info(ct), ci);
			MAKE_type_token(cv_none, id, args, s);
			COPY_type(ctype_form(ct), s);
			in_class_defn++;
			really_in_class_defn++;
			IGNORE end_class_defn(tid);
			really_in_class_defn--;
			in_class_defn--;
			have_type_declaration = td;
			crt_templ_qualifier = tq;
			crt_id_qualifier = cq;

		} else {
			/* Generic types */
			MAKE_type_token(cv_none, id, args, t);
		}
	} else {
		/* Shouldn't occur */
		t = type_error;
	}
	if (pt) {
		/* Expand token arguments */
		in_proc_token = 0;
		t = expand_type(t, 2);
		in_proc_token = pt;
	}
	return t;
}


/*
    This routine applies the member token id to the arguments args.
*/

OFFSET
apply_mem_token(IDENTIFIER id, LIST(TOKEN) args)
{
	OFFSET off;
	MAKE_off_token(id, args, off);
	return off;
}


/*
    This routine applies the token id to the arguments args.
*/

TOKEN
apply_token(IDENTIFIER id, LIST(TOKEN) args)
{
	TOKEN tok = NULL_tok;
	TOKEN sort = DEREF_tok(id_token_sort(id));
	unsigned tag = TAG_tok(sort);
	if (tag == tok_proc_tag) {
		sort = DEREF_tok(tok_proc_res(sort));
		tag = TAG_tok(sort);
	}
	switch (tag) {
	case tok_exp_tag: {
		EXP e = apply_exp_token(id, args, 0);
		TYPE t = DEREF_type(exp_type(e));
		int c = DEREF_int(tok_exp_constant(sort));
		MAKE_tok_exp(t, c, e, tok);
		break;
	}
	case tok_nat_tag:
	case tok_snat_tag: {
		NAT n = apply_nat_token(id, args);
		MAKE_tok_nat_etc(tag, n, tok);
		break;
	}
	case tok_stmt_tag: {
		EXP e = apply_exp_token(id, args, 0);
		MAKE_tok_stmt(e, tok);
		break;
	}
	case tok_type_tag: {
		TYPE t;
		BASE_TYPE bt = DEREF_btype(tok_type_kind(sort));
		t = apply_type_token(id, args, NULL_id);
		MAKE_tok_type(bt, t, tok);
		break;
	}
	case tok_member_tag: {
		TYPE s = DEREF_type(tok_member_of(sort));
		TYPE t = DEREF_type(tok_member_type(sort));
		OFFSET off = apply_mem_token(id, args);
		MAKE_tok_member(s, t, off, tok);
		break;
	}
	case tok_class_tag: {
		TYPE t = DEREF_type(tok_class_type(sort));
		MAKE_tok_class(t, id, tok);
		break;
	}
	}
	return tok;
}


/*
    This routine compares the token sorts a and b.
*/

static int
eq_tok(TOKEN a, TOKEN b)
{
	/* Check for obvious equality */
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

	/* Compare tags */
	na = TAG_tok(a);
	nb = TAG_tok(b);
	if (na != nb) {
		return 0;
	}

	/* Compare token components */
	assert(ORDER_tok == 10);
	switch (na) {
	case tok_exp_tag: {
		/* Expression tokens */
		TYPE ta = DEREF_type(tok_exp_type(a));
		TYPE tb = DEREF_type(tok_exp_type(b));
		CV_SPEC qa = DEREF_cv(type_qual(ta));
		CV_SPEC qb = DEREF_cv(type_qual(tb));
		int ca = DEREF_int(tok_exp_constant(a));
		int cb = DEREF_int(tok_exp_constant(b));
		return ca == cb && qa == qb && eq_type(ta, tb);
	}
	case tok_nat_tag:
	case tok_snat_tag:
	case tok_stmt_tag:
		/* Trivial cases */
		break;
	case tok_func_tag: {
		/* Function tokens */
		TYPE ta = DEREF_type(tok_func_type(a));
		TYPE tb = DEREF_type(tok_func_type(b));
		return eq_type(ta, tb);
	}
	case tok_member_tag: {
		/* Member tokens */
		TYPE sa = DEREF_type(tok_member_of(a));
		TYPE sb = DEREF_type(tok_member_of(b));
		TYPE ta = DEREF_type(tok_member_type(a));
		TYPE tb = DEREF_type(tok_member_type(b));
		return eq_type(sa, sb) && eq_type(ta, tb);
	}
	case tok_proc_tag: {
		/* Procedure tokens */
		LIST(IDENTIFIER) pa, pb;
		TOKEN ra = DEREF_tok(tok_proc_res(a));
		TOKEN rb = DEREF_tok(tok_proc_res(b));
		if (!eq_tok(ra, rb)) {
			return 0;
		}

		/* Compare program parameters */
		pa = DEREF_list(tok_proc_pids(a));
		pb = DEREF_list(tok_proc_pids(b));
		if (LENGTH_list(pa)!= LENGTH_list(pb)) {
			return 0;
		}
		while (!IS_NULL_list(pa) && !IS_NULL_list(pb)) {
			IDENTIFIER u = DEREF_id(HEAD_list(pa));
			IDENTIFIER v = DEREF_id(HEAD_list(pb));
			if (IS_NULL_id(u) || !IS_id_token(u)) {
				return 0;
			}
			if (IS_NULL_id(v) || !IS_id_token(v)) {
				return 0;
			}
			ra = DEREF_tok(id_token_sort(u));
			rb = DEREF_tok(id_token_sort(v));
			if (!eq_tok(ra, rb)) {
				return 0;
			}
			pa = TAIL_list(pa);
			pb = TAIL_list(pb);
		}

		/* Compare bound parameters */
		pa = DEREF_list(tok_proc_bids(a));
		pb = DEREF_list(tok_proc_bids(b));
		if (LENGTH_list(pa) != LENGTH_list(pb)) {
			return 0;
		}
		while (!IS_NULL_list(pa) && !IS_NULL_list(pb)) {
			IDENTIFIER u = DEREF_id(HEAD_list(pa));
			IDENTIFIER v = DEREF_id(HEAD_list(pb));
			if (IS_NULL_id(u) || !IS_id_token(u)) {
				return 0;
			}
			if (IS_NULL_id(v) || !IS_id_token(v)) {
				return 0;
			}
			ra = DEREF_tok(id_token_sort(u));
			rb = DEREF_tok(id_token_sort(v));
			if (!eq_tok(ra, rb)) {
				return 0;
			}
			pa = TAIL_list(pa);
			pb = TAIL_list(pb);
		}
		break;
	}

	case tok_type_tag: {
		/* Type tokens */
		BASE_TYPE ta = DEREF_btype(tok_type_kind(a));
		BASE_TYPE tb = DEREF_btype(tok_type_kind(b));
		if (ta != tb) {
			return 0;
		}
		break;
	}

	case tok_class_tag: {
		/* Template class tokens */
		TYPE ta = DEREF_type(tok_class_type(a));
		TYPE tb = DEREF_type(tok_class_type(b));
		if (eq_type(ta, tb) == 1) {
			return 1;
		}
		return 0;
	}

	case tok_templ_tag:
		/* Templates */
		/* NOT YET IMPLEMENTED */
		return 0;
	}
	return 1;
}


/*
    This routine declares a token identifier id with sort tok and external
    name ext in the namespace ns.
*/

static IDENTIFIER
declare_token(IDENTIFIER id, TOKEN tok, NAMESPACE ns, IDENTIFIER ext)
{
	HASHID nm = DEREF_hashid(id_name(id));
	MEMBER mem = search_member(ns, nm, 1);

	/* Check identifier name */
	ERROR err = check_id_name(id, CONTEXT_OBJECT);
	if (!IS_NULL_err(err))report(crt_loc, err);

	/* Check for previous definition */
	id = DEREF_id(member_id(mem));
	if (!IS_NULL_id(id)) {
		id = redecl_inherit(id, qual_none, 0, 0);
		if (!IS_NULL_id(id)) {
			if (IS_id_token(id)) {
				/* Allow for redeclarations */
				IDENTIFIER tid = DEREF_id(id_token_alt(id));
				if (EQ_id(tid, ext)) {
					return id;
				}
			}
			if (IS_id_function(id) && IS_tok_proc(tok)) {
				IDENTIFIER pid = id;
				while (!IS_NULL_id(pid)) {
					TYPE t =
					    DEREF_type(id_function_type(pid));
					if (IS_type_func(t)) {
						TOKEN ptok;
						MAKE_tok_func(t, ptok);
						ptok = func_proc_token(ptok);
						if (eq_tok(ptok, tok)) {
							/* Procedure token
							 * matches function */
							return pid;
						}
					}
					pid = DEREF_id(id_function_over(pid));
				}
			}
		}
	}

	/* Declare the token */
	MAKE_id_token(nm, dspec_token, ns, preproc_loc, tok, ext, id);
	set_member(mem, id);
	return id;
}


/*
    This routine declares a token of sort tok with internal name id,
    which belongs to the tag namespace if tag is true, and external name
    ext.  It returns the external token identifier.
*/

IDENTIFIER
make_token_decl(TOKEN tok, int tag, IDENTIFIER id, IDENTIFIER ext)
{
	int tq;
	HASHID nm;
	MEMBER mem;
	unsigned tt;
	QUALIFIER cq;
	NAMESPACE ns;
	NAMESPACE gns;
	int macro = 0;
	int pushed = 0;
	int done_dump = 0;
	IDENTIFIER tid = NULL_id;
	DECL_SPEC ds = dspec_token;
	DECL_SPEC mark = dspec_token;

	/* Ignore illegal tokens */
	if (IS_NULL_tok(tok)) {
		return NULL_id;
	}

	/* Find token name */
	if (!IS_NULL_id(ext)) {
		/* Externally named token */
		ns = token_namespace;
		/* gns = global_namespace ; */
		gns = nonblock_namespace;
		nm = DEREF_hashid(id_name(ext));
		mem = search_member(ns, nm, 1);
		ext = DEREF_id(member_id(mem));
		if (!IS_NULL_id(ext)) {
			TOKEN tok2 = DEREF_tok(id_token_sort(ext));
			force_tokdef++;
			if (!eq_tok(tok, tok2)) {
				ERROR err = ERR_token_redecl(ext, id_loc(ext));
				report(preproc_loc, err);
				ext = NULL_id;
			}
			force_tokdef--;
		}
		if (IS_hashid_anon(nm)) {
			ds |= dspec_static;
		} else {
			ds |= dspec_extern;
		}
	} else {
		/* Token parameter */
		ns = crt_namespace;
		gns = ns;
		nm = DEREF_hashid(id_name(id));
		mem = NULL_member;
		ds |= (dspec_auto | dspec_pure);
	}

	/* Create the token */
	if (IS_NULL_id(ext)) {
		IDENTIFIER uid = underlying_id(id);
		MAKE_id_token(nm, ds, ns, preproc_loc, tok, uid, ext);
		if (!IS_NULL_member(mem)) {
			COPY_id(member_id(mem), ext);
		}
	}

	/* Declare the corresponding identifier */
	cq = crt_id_qualifier;
	tq = crt_templ_qualifier;
	crt_id_qualifier = qual_none;
	crt_templ_qualifier = 0;
	if (!EQ_nspace(gns, crt_namespace)) {
		push_namespace(gns);
		pushed = 1;
	}
	tt = TAG_tok(tok);
	if (tt == tok_type_tag) {
		BASE_TYPE bt = DEREF_btype(tok_type_kind(tok));
		if (bt & btype_named) {
			/* Allow structure and union tags */
			if (tag) {
				tid = id;
			}
		} else {
			tag = 0;
		}
	} else {
		/* Other tags are not allowed */
		tag = 0;
	}
	switch (tt) {
	case tok_type_tag: {
		/* Simple type tokens */
		TYPE t = apply_type_token(ext, NULL_list(TOKEN), tid);
		if (tag) {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			id = DEREF_id(ctype_name(ct));
			done_dump = 1;
		} else {
			id = make_object_decl(dspec_typedef, t, id, 0);
			if (!(ds & dspec_auto)) {
				macro = 2;
			}
		}
		break;
	}
	case tok_func_tag: {
		/* Function tokens (C linkage by default) */
		TYPE t = DEREF_type(tok_func_type(tok));
		int ell = DEREF_int(type_func_ellipsis(t));
		DECL_SPEC ln = crt_linkage;
		if (ln == dspec_none) {
			crt_linkage = dspec_c;
		}
		id = make_func_decl(dspec_extern, t, id, 0);
		IGNORE init_object(id, NULL_exp);
		if (IS_id_function_etc(id) && ell == FUNC_NONE) {
			TYPE form;
			MAKE_type_token(cv_none, ext, NULL_list(TOKEN), form);
			COPY_type(id_function_etc_form(id), form);
			if (!(ds & dspec_auto)) {
				macro = 1;
			}
			if (is_redeclared) {
				/* Mark functions which have already been
				 * declared */
				ds |= dspec_explicit;
				COPY_dspec(id_storage(ext), ds);
			}
		} else {
			/* Ellipsis functions are not really tokenised */
			mark = dspec_none;
		}
		crt_linkage = ln;
		break;
	}
	case tok_member_tag: {
		/* Member tokens */
		int pt = in_proc_token;
		CLASS_TYPE cs = crt_class;
		TYPE t = DEREF_type(tok_member_of(tok));
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		NAMESPACE cns = DEREF_nspace(ctype_member(ct));
		crt_class = ct;
		in_class_defn++;
		really_in_class_defn++;
		push_namespace(cns);
		t = DEREF_type(tok_member_type(tok));
		if (pt) {
			in_proc_token = 0;
			t = expand_type(t, 2);
			in_proc_token = pt;
		}
		id = make_member_decl(dspec_token, t, id, 0);
		if (IS_id_member(id)) {
			OFFSET off = DEREF_off(id_member_off(id));
			if (!IS_NULL_off(off)) {
				t = DEREF_type(id_member_type(id));
				IGNORE define_mem_token(ext, off, t, 1);
				if (!IS_NULL_member(mem)) {
					if (IS_off_member(off)) {
						/* Record old member name */
						IDENTIFIER pid;
						pid = DEREF_id(off_member_id(off));
						COPY_id(member_alt(mem), pid);
					}
				}
			}
			off = apply_mem_token(ext, NULL_list(TOKEN));
			COPY_off(id_member_off(id), off);
			if (!(ds & dspec_auto)) {
				macro = 2;
			}
		}
		IGNORE pop_namespace();
		really_in_class_defn--;
		in_class_defn--;
		crt_class = cs;
		break;
	}
	case tok_class_tag: {
		/* Template template parameters */
		TYPE t;
		TYPE q = DEREF_type(tok_class_type(tok));
		MAKE_type_token(cv_none, ext, NULL_list(TOKEN), t);
		id = make_object_decl(dspec_typedef, t, id, 0);
		t = inject_pre_type(q, t, 0);
		COPY_type(id_class_name_etc_defn(id), t);
		COPY_type(tok_class_type(tok), t);
		mark |= dspec_template;
		break;
	}
	default:
		/* Other tokens */
		decl_loc = preproc_loc;
		id = declare_token(id, tok, gns, ext);
		if (IS_id_function(id)) {
			TYPE form;
			MAKE_type_token(cv_none, ext, NULL_list(TOKEN), form);
			COPY_type(id_function_form(id), form);
		}
		if (!(ds & dspec_auto)) {
			macro = 1;
		}
		break;
	}
	if (mark) {
		/* Mark object as a token */
		ds = DEREF_dspec(id_storage(id));
		ds |= mark;
		COPY_dspec(id_storage(id), ds);
	}
	COPY_id(id_token_alt(ext), id);
	if (!IS_NULL_member(mem)) {
		IDENTIFIER pid = DEREF_id(member_alt(mem));
		if (IS_NULL_id(pid)) {
			COPY_id(member_alt(mem), id);
		}
		if (do_dump) {
			if (!done_dump) {
				dump_declare(id, &preproc_loc, 0);
			}
			dump_token(id, ext);
		}
	}
	if (pushed) {
		IGNORE pop_namespace();
	}
	crt_templ_qualifier = tq;
	crt_id_qualifier = cq;

	/* Check for previous macro definition */
	if (macro) {
		IDENTIFIER mid;
		nm = DEREF_hashid(id_name(id));
		mid = DEREF_id(hashid_id(nm));
		switch (TAG_id(mid)) {
		case id_obj_macro_tag:
		case id_func_macro_tag: {
			LOCATION loc;
			loc = preproc_loc;
			DEREF_loc(id_loc(mid), preproc_loc);
			ds = DEREF_dspec(id_storage(mid));
			COPY_dspec(id_storage(mid), (ds | dspec_temp));
			if (define_token_macro(id, mid)) {
				ds |= dspec_used;
				if (do_macro && do_usage) {
					dump_use(mid, &loc, 1);
				}
				COPY_loc(id_loc(ext), preproc_loc);
				no_declarations++;
			}
			COPY_dspec(id_storage(mid), ds);
			preproc_loc = loc;
			break;
		}
		}
	}
	return ext;
}


/*
    This routine finds the token identifier associated with the identifier
    id.
*/

static IDENTIFIER
find_token_aux(IDENTIFIER id)
{
	switch (TAG_id(id)) {
	case id_class_name_tag:
	case id_class_alias_tag: {
		/* Classes */
		TYPE t = DEREF_type(id_class_name_etc_defn(id));
		if (IS_type_compound(t)) {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			t = DEREF_type(ctype_form(ct));
			if (!IS_NULL_type(t) && IS_type_token(t)) {
				id = DEREF_id(type_token_tok(t));
				return id;
			}
		}
		break;
	}
	case id_type_alias_tag: {
		/* Types */
		TYPE t = DEREF_type(id_type_alias_defn(id));
		if (IS_type_token(t)) {
			id = DEREF_id(type_token_tok(t));
			return id;
		}
		break;
	}
	case id_function_tag:
	case id_mem_func_tag:
	case id_stat_mem_func_tag: {
		/* Functions */
		TYPE form = DEREF_type(id_function_etc_form(id));
		if (!IS_NULL_type(form) && IS_type_token(form)) {
			IDENTIFIER ext = DEREF_id(type_token_tok(form));
			if (!IS_NULL_id(ext)) {
				return ext;
			}
		}
		return id;
	}
	case id_member_tag: {
		/* Members */
		OFFSET off = DEREF_off(id_member_off(id));
		if (IS_off_token(off)) {
			id = DEREF_id(off_token_tok(off));
			return id;
		}
		break;
	}
	case id_token_tag: {
		/* Tokens */
		IDENTIFIER alt = DEREF_id(id_token_alt(id));
		if (IS_id_token(alt)) {
			return alt;
		}
		return id;
	}
	}
	return id;
}


/*
    This routine finds the external token corresponding to the identifier id.
    For functions this refers only to the function id itself and not to
    any overloading functions.
*/

IDENTIFIER
find_token(IDENTIFIER id)
{
	MEMBER mem;
	DECL_SPEC ds;
	IDENTIFIER tid;
	HASHID nm = DEREF_hashid(id_name(id));
	if (IS_id_keyword_etc(id)) {
		/* Rescan keywords */
		id = find_id(nm);
	}
	ds = DEREF_dspec(id_storage(id));
	if (ds & dspec_token) {
		/* Deal with simple tokens */
		tid = find_token_aux(id);
		if (IS_id_token(tid)) {
			ds = DEREF_dspec(id_storage(tid));
			if (!(ds & dspec_auto)) {
				return tid;
			}
		}
	}

	/* Complex cases - check through token namespace */
	id = DEREF_id(id_alias(id));
	mem = DEREF_member(nspace_global_first(token_namespace));
	while (!IS_NULL_member(mem)) {
		tid = DEREF_id(member_alt(mem));
		if (EQ_id(tid, id)) {
			tid = DEREF_id(member_id(mem));
			return tid;
		}
		mem = DEREF_member(member_next(mem));
	}
	return id;
}


/*
    This routine finds the token corresponding to the tag identifier id.
*/

IDENTIFIER
find_tag_token(IDENTIFIER id)
{
	id = find_elaborate_type(id, btype_any, NULL_type, dspec_used);
	return id;
}


/*
    This routine finds the token corresponding to the member mid of cid.
*/

IDENTIFIER
find_mem_token(IDENTIFIER cid, IDENTIFIER mid)
{
	if (IS_id_class_name_etc(cid)) {
		TYPE t = DEREF_type(id_class_name_etc_defn(cid));
		IDENTIFIER fid = tok_member(mid, t, 1);
		if (!IS_NULL_id(fid)) {
			return fid;
		}
		return mid;
	}
	report(preproc_loc, ERR_dcl_type_simple_undef(cid));
	return mid;
}


/*
    This routine finds the token with external name given by id.
*/

IDENTIFIER
find_ext_token(IDENTIFIER id)
{
	HASHID nm = DEREF_hashid(id_name(id));
	id = search_id(token_namespace, nm, 0, 0);
	if (IS_NULL_id(id)) {
		id = DEREF_id(hashid_id(nm));
	}
	return id;
}


/*
    This routine is identical to find_token except that it does a primitive
    form of overload resolution on function tokens based on the number of
    arguments n.  A value of UINT_MAX indicates that any number of
    parameters is allowed.
*/

IDENTIFIER
find_func_token(IDENTIFIER id, unsigned n)
{
    if (IS_id_function_etc(id)) {
	int no = 0;
	IDENTIFIER tid = NULL_id;
	IDENTIFIER fid = id;
	while (!IS_NULL_id(fid)) {
	    TYPE form = DEREF_type(id_function_etc_form(fid));
	    if (!IS_NULL_type(form) && IS_type_token(form)) {
		IDENTIFIER ext = DEREF_id(type_token_tok(form));
		if (!IS_NULL_id(ext) && IS_id_token(ext)) {
		    if (n == (unsigned)UINT_MAX) {
			tid = ext;
			no++;
		    } else {
			TYPE t;
			int ell;
			LIST(TYPE)p;
			t = DEREF_type(id_function_etc_type(fid));
			while (IS_type_templ(t)) {
			    t = DEREF_type(type_templ_defn(t));
			}
			p = DEREF_list(type_func_ptypes(t));
			ell = DEREF_int(type_func_ellipsis(t));
			if (LENGTH_list(p) == n) {
			    if (!(ell & FUNC_ELLIPSIS)) {
				tid = ext;
				no++;
			    }
			}
		    }
		}
	    }
	    fid = DEREF_id(id_function_etc_over(fid));
	}
	if (no > 1) {
		report(preproc_loc, ERR_token_def_ambig(id));
	}
	return tid;
    }
    return find_token(id);
}


/*
    This flag is used to record the current interface method.  It gives the
    mapping of any '#pragma interface' to one of '#pragma define', '#pragma
    no_def' or '#pragma ignore'.
*/

int crt_interface = lex_no_Hdef;


/*
    This routine performs the token interface operation indicated by i
    (which will be lex_define, lex_no_Hdef, lex_ignore) on the token tid.
*/

static void
mark_interface(IDENTIFIER tid, int i)
{
	DECL_SPEC ds = DEREF_dspec(id_storage(tid));
	if (i == lex_define) {
		/* Token must be defined */
		ds |= dspec_static;
		ds &= ~dspec_pure;
	} else if (i == lex_no_Hdef) {
		/* Token must not be defined */
		ds |= dspec_pure;
		if (ds & dspec_defn) {
			/* Token already defined */
			PTR(LOCATION)loc = id_loc(tid);
			report(preproc_loc, ERR_token_no_def(tid, loc));
		}
	} else {
		/* Ignore token definitions */
		ds |= dspec_done;
		ds &= ~dspec_pure;
	}
	COPY_dspec(id_storage(tid), ds);
	return;
}


/*
    This routine looks up the token id and performs the token operation
    i on it.  In addition to the values above i can be lex_undef indicating
    that the token should be undefined.
*/

void
token_interface(IDENTIFIER id, int i)
{
	int ok = 0;
	IDENTIFIER pid = id;
	while (!IS_NULL_id(pid)) {
		IDENTIFIER tid = find_token(pid);
		if (IS_id_token(tid)) {
			/* Token found */
			if (i == lex_undef) {
				if (do_dump) {
					dump_undefine(pid, &preproc_loc, 1);
				}
				remove_id(pid);
			} else {
				mark_interface(tid, i);
			}
			ok = 1;
		}
		if (!IS_id_function_etc(pid)) {
			break;
		}
		pid = DEREF_id(id_function_etc_over(pid));
	}
	if (!ok) {
		/* Token not found */
		report(preproc_loc, ERR_token_undecl(id));
	}
	return;
}
