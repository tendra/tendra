/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include "config.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "assign.h"
#include "basetype.h"
#include "cast.h"
#include "chktype.h"
#include "class.h"
#include "construct.h"
#include "convert.h"
#include "copy.h"
#include "declare.h"
#include "derive.h"
#include "destroy.h"
#include "dump.h"
#include "exception.h"
#include "expression.h"
#include "function.h"
#include "hash.h"
#include "identifier.h"
#include "initialise.h"
#include "instance.h"
#include "namespace.h"
#include "operator.h"
#include "option.h"
#include "overload.h"
#include "predict.h"
#include "syntax.h"
#include "template.h"
#include "tokdef.h"
#include "token.h"
#include "ustring.h"
#include "xalloc.h"


/*
    CANDIDATE LIST

    This variable gives the main candidate list used in overload resolution.
*/

CANDIDATE_LIST candidates = { NULL, 0, 0, NULL, 0 };


/*
    ADD A CANDIDATE TO A LIST

    This routine adds the candidate given by id, bid and kind to the
    candidate list p.
*/

static void
add_candidate(CANDIDATE_LIST *p, IDENTIFIER id, IDENTIFIER bid, int kind)
{
	CANDIDATE *q = p->elem;
	unsigned n = p->size;
	unsigned m = p->max_size;
	if (n >= m) {
		/* Increase size if necessary */
		m += 200;
		q = xrealloc_nof(q, CANDIDATE, m);
		p->elem = q;
		p->max_size = m;
	}
	q[n].func = id;
	q[n].base = bid;
	q[n].kind = kind;
	q[n].rank = RANK_NONE;
	q[n].convs = NULL;
	q[n].cond = NULL_exp;
	p->size = n + 1;
	return;
}


/*
    ADD AN IDENTIFIER TO A CANDIDATE LIST

    This routine adds the overloaded function identifier id to the candidate
    list given by p.  The kind argument is stored in the kind field of each
    candidate.  The table of candidate functions may need extending.  Note
    that the candidates are added in the reverse order in which they were
    declared.
*/

void
add_candidates(CANDIDATE_LIST *p, IDENTIFIER id, int over, int kind)
{
	unsigned tag = TAG_id(id);
	switch (tag) {
	case id_function_tag:
	case id_mem_func_tag:
	case id_stat_mem_func_tag:
		/* Functions */
		while (!IS_NULL_id(id)) {
			IDENTIFIER bid = DEREF_id(id_alias(id));
			add_candidate(p, id, bid, kind);
			if (!over) {
				break;
			}
			id = DEREF_id(id_function_etc_over(id));
		}
		break;
	case id_builtin_tag:
		/* Built-in operators */
		add_candidate(p, id, id, kind);
		break;
	case id_ambig_tag: {
		/* Ambiguous functions */
		LIST(IDENTIFIER) r = DEREF_list(id_ambig_ids(id));
		if (over) {
			over = DEREF_int(id_ambig_over(id));
		}
		while (!IS_NULL_list(r)) {
			IDENTIFIER rid = DEREF_id(HEAD_list(r));
			add_candidates(p, rid, over, kind);
			r = TAIL_list(r);
		}
		break;
	}
	}
	return;
}


/*
    LOOK UP A FUNCTION IN AN ARGUMENT NAMESPACE

    This routine looks up the function id in the namespace containing the
    type name cid.  Any functions found are added to the candidate list p.
*/

static IDENTIFIER
koenig_id(CANDIDATE_LIST *p, IDENTIFIER id, IDENTIFIER cid, int kind)
{
	if (!IS_NULL_id(cid)) {
		NAMESPACE cns = DEREF_nspace(id_parent(cid));
		if (!IS_NULL_nspace(cns)) {
			switch (TAG_nspace(cns)) {
			case nspace_named_tag:
			case nspace_unnamed_tag:
			case nspace_global_tag: {
				/* Look up identifier in parent class */
				HASHID nm = DEREF_hashid(id_name(id));
				MEMBER mem = search_member(cns, nm, 0);
				if (!IS_NULL_member(mem)) {
					IDENTIFIER fid =
					    DEREF_id(member_id(mem));
					if (!IS_NULL_id(fid) &&
					    !EQ_id(fid, id)) {
						add_candidates(p, fid, 1, kind);
						id = fid;
					}
				}
				break;
			}
			case nspace_ctype_tag: {
				/* Allow for nested classes */
				IDENTIFIER pid = DEREF_id(nspace_name(cns));
				id = koenig_id(p, id, pid, kind);
				break;
			}
			}
		}
	}
	return id;
}


/*
    PERFORM ARGUMENT DEPENDENT NAME LOOK-UP FOR A CLASS

    This routine performs argument dependent name look-up for the function
    id and the argument class type ct.
*/

static IDENTIFIER
koenig_class(CANDIDATE_LIST *p, IDENTIFIER id, CLASS_TYPE ct, int kind)
{
	TYPE form = DEREF_type(ctype_form(ct));
	if (IS_NULL_type(form)) {
		IDENTIFIER cid = DEREF_id(ctype_name(ct));
		GRAPH gr = DEREF_graph(ctype_base(ct));
		LIST(GRAPH) br = DEREF_list(graph_tails(gr));
		id = koenig_id(p, id, cid, kind);
		while (!IS_NULL_list(br)) {
			GRAPH gs = DEREF_graph(HEAD_list(br));
			CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
			id = koenig_class(p, id, cs, kind);
			br = TAIL_list(br);
		}
	} else {
		id = koenig_candidates(p, id, form, kind);
	}
	return id;
}


/*
    PERFORM ARGUMENT DEPENDENT NAME LOOK-UP FOR A TOKEN ARGUMENT

    This routine performs argument dependent name look-up for the function
    id and the token argument tok.
*/

static IDENTIFIER
koenig_token(CANDIDATE_LIST *p, IDENTIFIER id, TOKEN tok, int kind)
{
	if (!IS_NULL_tok(tok)) {
		ASSERT(ORDER_tok == 10);
		switch (TAG_tok(tok)) {
		case tok_type_tag: {
			TYPE t = DEREF_type(tok_type_value(tok));
			id = koenig_candidates(p, id, t, kind);
			break;
		}
		case tok_class_tag: {
			IDENTIFIER tid = DEREF_id(tok_class_value(tok));
			id = koenig_id(p, id, tid, kind);
			break;
		}
		}
	}
	return id;
}


/*
    PERFORM ARGUMENT DEPENDENT NAME LOOK-UP

    This routine performs argument dependent name look-up for the function
    id and the argument type t, adding any candidates found to the list p.
*/

IDENTIFIER
koenig_candidates(CANDIDATE_LIST *p, IDENTIFIER id, TYPE t, int kind)
{
	if (!IS_NULL_type(t)) {
		ASSERT(ORDER_type == 18);
		switch (TAG_type(t)) {
		case type_ptr_tag:
		case type_ref_tag: {
			TYPE s = DEREF_type(type_ptr_etc_sub(t));
			id = koenig_candidates(p, id, s, kind);
			break;
		}
		case type_ptr_mem_tag: {
			CLASS_TYPE cs = DEREF_ctype(type_ptr_mem_of(t));
			TYPE s = DEREF_type(type_ptr_mem_sub(t));
			id = koenig_class(p, id, cs, kind);
			id = koenig_candidates(p, id, s, kind);
			break;
		}
		case type_func_tag: {
			TYPE r = DEREF_type(type_func_ret(t));
			LIST(TYPE) q = DEREF_list(type_func_ptypes(t));
			id = koenig_candidates(p, id, r, kind);
			while (!IS_NULL_list(q)) {
				TYPE s = DEREF_type(HEAD_list(q));
				id = koenig_candidates(p, id, s, kind);
				q = TAIL_list(q);
			}
			break;
		}
		case type_array_tag: {
			TYPE s = DEREF_type(type_array_sub(t));
			id = koenig_candidates(p, id, s, kind);
			break;
		}
		case type_compound_tag: {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			id = koenig_class(p, id, ct, kind);
			break;
		}
		case type_enumerate_tag: {
			ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
			IDENTIFIER eid = DEREF_id(etype_name(et));
			id = koenig_id(p, id, eid, kind);
			break;
		}
		case type_token_tag: {
			IDENTIFIER tid = DEREF_id(type_token_tok(t));
			LIST(TOKEN) args = DEREF_list(type_token_args(t));
			if (IS_id_token(tid)) {
				tid = DEREF_id(id_token_alt(tid));
			}
			id = koenig_id(p, id, tid, kind);
			while (!IS_NULL_list(args)) {
				TOKEN arg = DEREF_tok(HEAD_list(args));
				id = koenig_token(p, id, arg, kind);
				args = TAIL_list(args);
			}
			break;
		}
		case type_templ_tag: {
			TYPE s = DEREF_type(type_templ_defn(t));
			id = koenig_candidates(p, id, s, kind);
			break;
		}
		}
	}
	return id;
}


/*
    FREE A LIST OF CANDIDATES

    This routine frees the elements of the candidate list p.
*/

void
free_candidates(CANDIDATE_LIST *p)
{
	xfree_nof(p->elem);
	xfree_nof(p->convs);
	p->elem = NULL;
	p->size = 0;
	p->max_size = 0;
	p->convs = NULL;
	p->nconvs = 0;
	return;
}


/*
    SWAP PARAMETER TYPE FIELDS FOR A FUNCTION

    Overload resolution is based on the mtypes field of the function type.
    This routine can be used to force resolution on the ptypes field by
    swapping the two fields for the overloaded function identifier id.
    Note that after overload resolution the fields should be swapped back.
*/

void
swap_ptypes(IDENTIFIER id)
{
	LIST(TYPE) ptypes;
	LIST(TYPE) mtypes;
	TYPE fn = DEREF_type(id_function_etc_type(id));
	while (IS_type_templ(fn)) {
		/* Allow for template functions */
		fn = DEREF_type(type_templ_defn(fn));
	}
	ptypes = DEREF_list(type_func_ptypes(fn));
	mtypes = DEREF_list(type_func_mtypes(fn));
	if (!EQ_list(ptypes, mtypes)) {
		COPY_list(type_func_ptypes(fn), mtypes);
		COPY_list(type_func_mtypes(fn), ptypes);
	}
	return;
}


/*
    SWAP PARAMETER TYPE FIELDS FOR CANDIDATES FUNCTIONS

    This routine swaps the parameter type fields for all the constructor
    candidates in p, starting with the nth entry.
*/

void
swap_candidates(CANDIDATE_LIST *p, unsigned n)
{
	unsigned i, m = p->size;
	for (i = n; i < m; i++) {
		CANDIDATE *r = p->elem + i;
		if (r->kind == KIND_CONSTR) {
			swap_ptypes(r->base);
		}
	}
	return;
}


/*
    LIST CANDIDATES FOR ERROR REPORTING

    This routine appends messages listing all the candidates from the list
    p of rank at least rank to the end of the error message err.  No action
    is taken if err is the null error.
*/

ERROR
list_candidates(ERROR err, CANDIDATE_LIST *p, unsigned rank)
{
	if (!IS_NULL_err(err)) {
		ERROR err2 = ERR_over_match_viable_list();
		if (!IS_NULL_err(err2)) {
			unsigned m = 0;
			CANDIDATE *q = p->elem;
			unsigned n = p->size;
			err = concat_error(err, err2);
			while (n) {
				CANDIDATE *r = q + (--n);
				if (r->rank >= rank) {
					/* List viable candidates */
					IDENTIFIER bid = r->base;
					DECL_SPEC ds =
					    DEREF_dspec(id_storage(bid));
					if (!(ds & dspec_register)) {
						IDENTIFIER id = r->func;
						if (IS_id_builtin(id)) {
							/* Dump dummy built-in
							 * operators */
							if (do_dump) {
								dump_builtin(id);
							}
						}
						m++;
						err2 = ERR_fail_list_item(m, id, id_loc(id));
						err = concat_error(err, err2);
						ds |= dspec_register;
						COPY_dspec(id_storage(bid), ds);
					}
				}
			}
			if (m) {
				n = p->size;
				while (n) {
					/* Clear marks */
					CANDIDATE *r = q + (--n);
					IDENTIFIER bid = r->base;
					DECL_SPEC ds =
					    DEREF_dspec(id_storage(bid));
					if (ds & dspec_register) {
						ds &= ~dspec_register;
						COPY_dspec(id_storage(bid), ds);
					}
				}
			}
			err = concat_error(err, ERR_fail_list_end(m));
		}
	}
	return err;
}


/*
    OVERLOAD MATCHING INFORMATION

    These variables are used to store information gained during overload
    resolution.  If match_no_args is nonzero it gives the number of
    candidates which take the right number of arguments, otherwise if it
    is zero it indicates that either there are no such functions or there
    is only one candidate.  Similarly match_no_viable gives the number of
    viable candidates (counting viable templates twice).
*/

unsigned match_no_args = 0;
unsigned match_no_viable = 0;
static unsigned viable_templates = 0;
int resolved_kind = KIND_FUNC;


/*
    IS A CANDIDATE FUNCTION PLAUSIBLE?

    A candidate function is plausible for a list of arguments if it accepts
    that number of arguments.  This routine tests whether the candidate r
    is plausible.  It returns the absolute difference between the number
    of arguments and the number of parameters (i.e. zero for a plausible
    candidate).
*/

static unsigned
plausible_candidate(CANDIDATE *r, unsigned nargs)
{
	IDENTIFIER id = r->base;
	if (IS_id_builtin(id)) {
		/* Built-in candidates */
		LIST(TYPE) mtypes = DEREF_list(id_builtin_ptypes(id));
		unsigned npars = LENGTH_list(mtypes);
		if (nargs == npars) {
			/* Equal numbers of arguments and parameters */
			return 0;
		} else if (nargs > npars) {
			/* More arguments than parameters */
			return nargs - npars;
		} else {
			/* Less arguments than parameters */
			return npars - nargs;
		}
	} else {
		/* Function candidates */
		unsigned npars;
		LIST(TYPE) mtypes;
		TYPE fn = DEREF_type(id_function_etc_type(id));
		while (IS_type_templ(fn)) {
			/* Allow for template functions */
			fn = DEREF_type(type_templ_defn(fn));
		}
		mtypes = DEREF_list(type_func_mtypes(fn));
		npars = LENGTH_list(mtypes);
		if (nargs == npars) {
			/* Equal numbers of arguments and parameters */
			return 0;
		} else if (nargs > npars) {
			/* More arguments than parameters */
			int ell = DEREF_int(type_func_ellipsis(fn));
			if (ell) {
				/* Match with ellipsis */
				return 0;
			}
			return nargs - npars;
		} else {
			/* Less arguments than parameters */
			unsigned margs = min_no_args(fn);
			if (nargs >= margs) {
				/* Match with default arguments */
				return 0;
			}
			return margs - nargs;
		}
	}
	/* NOTREACHED */
}


/*
    INHERITANCE MATCHING FLAG

    This flag may be set to true to make the match for the implicit
    this parameter for an inherited function as good as a match for
    a non-inherited function from the point of view of function
    overloading.
*/

int match_this = 0;


/*
    IS A PLAUSIBLE CANDIDATE FUNCTION VIABLE?

    A plausible candidate function is viable for a list of arguments if
    there is an implicit conversion sequence for each argument to the
    corresponding parameter type.  This routine tests whether the plausible
    candidate r is viable, building up the corresponding list of conversions.
    It returns the number of arguments for which a sequence exists, plus
    one.
*/

static unsigned
viable_candidate(CANDIDATE *r, LIST(EXP) args, TYPE ret)
{
	TYPE rtype;
	int bind = 0;
	unsigned conv;
	unsigned match = 1;
	LIST(TYPE) mtypes;
	IDENTIFIER id = r->base;
	CONVERSION *convs = r->convs;
	HASHID nm = DEREF_hashid(id_name(id));

	/* Extract type information */
	if (IS_id_builtin(id)) {
		if (IS_hashid_op(nm)) {
			int op = DEREF_int(hashid_op_lex(nm));
			if (op == lex_assign) {
				bind = 1;
			}
		}
		mtypes = DEREF_list(id_builtin_ptypes(id));
		rtype = DEREF_type(id_builtin_ret(id));
	} else {
		LIST(TYPE) ptypes;
		TYPE fn = DEREF_type(id_function_etc_type(id));
		if (IS_type_templ(fn)) {
			/* Allow for template functions */
			ERROR err = NULL_err;
			if (r->kind == KIND_CONSTR) {
				/* Deal with swapped candidates */
				IDENTIFIER tid;
				EXP a = NULL_exp;
				LIST(EXP) dargs;
				swap_ptypes(id);
				CONS_exp(a, args, dargs);
				tid = deduce_args(id, dargs, 2, 0, 1, &err);
				DESTROY_CONS_exp(destroy, a, args, dargs);
				UNUSED(a);
				if (IS_NULL_id(tid)) {
					swap_ptypes(id);
					return 0;
				}
				swap_ptypes(tid);
				id = tid;
			} else {
				/* Deal with normal candidates */
				id = deduce_args(id, args, 2, 0, 1, &err);
				if (IS_NULL_id(id)) {
					return 0;
				}
			}
			fn = DEREF_type(id_function_etc_type(id));
			if (!IS_type_func(fn)) {
				return 0;
			}
			viable_templates++;
			r->func = id;
			r->base = id;
		}
		mtypes = DEREF_list(type_func_mtypes(fn));
		ptypes = DEREF_list(type_func_ptypes(fn));
		if (IS_hashid_constr(nm)) {
			rtype = DEREF_type(hashid_constr_type(nm));
		} else {
			rtype = DEREF_type(type_func_ret(fn));
		}
		if (!EQ_list(mtypes, ptypes)) {
			/* Member function */
			if (!IS_NULL_list(ptypes)) {
				ptypes = TAIL_list(ptypes);
			}
			if (EQ_list(mtypes, ptypes)) {
				/* Parameter types have been swapped */
				/* EMPTY */
			} else {
				/* Matching implicit this parameter */
				if (match_this) {
					/* Force exact match */
					bind = 2;
				} else {
					IDENTIFIER fid = r->func;
					DECL_SPEC ds =
					    DEREF_dspec(id_storage(fid));
					if ((ds & dspec_inherit) &&
					    !(ds & dspec_alias)) {
						/* Inherited member function */
						bind = 3;
					} else {
						bind = 2;
					}
				}
			}
		}
	}

	/* Check for implicit conversion sequences */
	while (!IS_NULL_list(mtypes) && !IS_NULL_list(args)) {
		conv = convs->rank;
		if (conv == CONV_NONE) {
			/* Recalculate if necessary */
			EXP a = DEREF_exp(HEAD_list(args));
			TYPE t = DEREF_type(HEAD_list(mtypes));
			convs->to = t;
			if (IS_NULL_exp(a)) {
				/* A null expression counts as an exact match */
				convs->from = t;
				conv = CONV_EXACT;
			} else {
				/* Calculate conversion sequence */
				TYPE s = DEREF_type(exp_type(a));
				convs->from = s;
				if (IS_NULL_type(ret)) {
					conv = convert_seq(convs, a, bind, 0);
				} else {
					conv =
					    std_convert_seq(convs, a, bind, 0);
				}
				convs->from = s;
				convs->to = t;
			}
		}
		if (conv != CONV_NONE) {
			match++;
		}
		convs->rank = conv;
		convs++;
		args = TAIL_list(args);
		mtypes = TAIL_list(mtypes);
		bind = 0;
	}

	/* Remaining arguments match with ellipsis */
	while (!IS_NULL_list(args)) {
		convs->rank = CONV_ELLIPSIS;
		convs++;
		match++;
		args = TAIL_list(args);
	}

	/* Check for return conversion sequences */
	if (!IS_NULL_type(ret)) {
		conv = convs->rank;
		if (conv == CONV_NONE) {
			convs->to = ret;
			convs->from = rtype;
			conv = std_convert_seq(convs, NULL_exp, 0, 0);
			convs->from = rtype;
			convs->to = ret;
		}
	} else {
		conv = CONV_ELLIPSIS;
	}
	convs->rank = conv;
	return match;
}


/*
    COMPARE TWO FUNCTIONS

    This routine compares the candidate functions rid and sid to determine
    which is better under the template specialisation rules.  It returns
    1 if rid is better than sid, 2 if sid is better than rid, and 0 otherwise.
*/

static int
compare_funcs(IDENTIFIER rid, IDENTIFIER sid)
{
	int res = 0;
	if (EQ_id(rid, sid)) {
		/* Select first if equal */
		res = 1;
	} else {
		if (IS_NULL_id(rid)) {
			res = 2;
		} else if (IS_NULL_id(sid)) {
			res = 1;
		} else {
			rid = find_template(rid, 0);
			sid = find_template(sid, 0);
			if (!IS_NULL_id(rid)) {
				if (!IS_NULL_id(sid)) {
					/* Both template functions */
					res = compare_specs(rid, sid);
				} else {
					/* rid is a template function */
					res = 2;
				}
			} else if (!IS_NULL_id(sid)) {
				/* sid is a template function */
				res = 1;
			}
		}
	}
	return res;
}


/*
    COMPARE TWO CANDIDATE FUNCTIONS

    This routine compares the candidate functions r and s for the argument
    list args and return type ret.  It returns 1 if r is better than s, 2 if
    s is better than r, and some other value otherwise.  Better in this
    sense means at least as good for all arguments, plus strictly better
    in at least one argument or the return type.
*/

static int
compare_candidates(CANDIDATE *r, CANDIDATE *s, LIST(EXP) args, TYPE ret)
{
	int res = 0;
	CONVERSION *cr = r->convs;
	CONVERSION *cs = s->convs;

	/* Compare each argument in turn */
	while (!IS_NULL_list(args)) {
		int cmp = compare_seq(cr, cs);
		if (cmp == 1) {
			/* r better in this argument */
			if (res == 2) {
				return 0;
			}
			res = 1;
		} else if (cmp == 2) {
			/* s better in this argument */
			if (res == 1) {
				return 0;
			}
			res = 2;
		}
		cr++;
		cs++;
		args = TAIL_list(args);
	}

	/* Tie breakers */
	if (res == 0) {
		res = compare_funcs(r->base, s->base);
		if (res == 0 && !IS_NULL_type(ret)) {
			/* Resolve on return type */
			res = compare_seq(cr, cs);
		}
	}
	return res;
}


/*
    OVERLOADED FUNCTION RESOLUTION

    This routine selects the best match from the list of overloaded function
    given by p based on the argument list args and the return type ret (which
    may be the null type).  The list of candidate functions will not be empty.
    If replay is true then the conversion sequences have already been
    calculated and only the final tournament to select the best viable
    candidate is necessary.
*/

CANDIDATE *
resolve_overload(CANDIDATE_LIST *p, LIST(EXP) args, TYPE ret, int replay)
{
	unsigned round;
	unsigned match = 0;
	CANDIDATE *q = p->elem;
	CANDIDATE *best = q;
	CANDIDATE *beat = NULL;
	unsigned i, n = p->size;

	if (!replay) {
		/* Eliminate all non-viable candidates */
		unsigned nargs;
		unsigned margs;
		unsigned mconvs;
		unsigned best_margs;
		unsigned nconvs = p->nconvs;
		CONVERSION *convs = p->convs;

		/* Check for plausible candidates */
		nargs = LENGTH_list(args);
		best_margs = nargs + 1;
		for (i = 0; i < n; i++) {
			CANDIDATE *r = q + i;
			if (r->rank != RANK_IGNORE) {
				margs = plausible_candidate(r, nargs);
				if (margs == 0) {
					/* Plausible candidate */
					r->rank = RANK_ARGS;
					best = r;
					match++;
				} else if (match == 0 && margs <= best_margs) {
					/* Most nearly plausible candidate so
					 * far */
					best_margs = margs;
					best = r;
				}
			}
		}
		match_no_args = match;
		if (match == 0) {
			/* No plausible candidates - return most nearly
			 * plausible */
			match_no_viable = 0;
			return best;
		}

		/* Allocate room for conversion ranks */
		nargs++;
		mconvs = match * nargs;
		if (mconvs >= nconvs) {
			nconvs = mconvs + 200;
			convs = xrealloc_nof(convs, CONVERSION, nconvs);
			p->nconvs = nconvs;
			p->convs = convs;
		}

		/* Check for viable candidates */
		match = 0;
		best_margs = 0;
		viable_templates = 0;
		for (i = 0; i < n; i++) {
			CANDIDATE *r = q + i;
			if (r->rank == RANK_ARGS) {
				/* Only check plausible candidates */
				unsigned m;
				r->convs = convs;
				for (m = 0; m < nargs; m++) {
					convs->rank = CONV_NONE;
					convs++;
				}
				margs = viable_candidate(r, args, ret);
				if (margs == nargs) {
					/* Viable candidate */
					r->rank = RANK_VIABLE;
					best = r;
					match++;
				} else if (match == 0 && margs >= best_margs) {
					/* Most nearly viable candidate so
					 * far */
					best_margs = margs;
					best = r;
				}
			}
		}
		match_no_viable = match + viable_templates;
		if (match == 0) {
			/* No viable candidates - return most nearly viable */
			return best;
		}
		if (match == 1) {
			/* Exactly one viable candidate - must be the winner */
			best->rank = RANK_BEST;
			return best;
		}
	} else {
		/* Replay - pick a viable candidate */
		for (i = 0; i < n; i++) {
			CANDIDATE *r = q + i;
			if (r->rank >= RANK_VIABLE) {
				r->rank = RANK_VIABLE;
				best = r;
				match++;
			}
		}
	}

	/* Play tournament among viable candidates */
	round = RANK_VIABLE;
	while (match > 1) {
		CANDIDATE *s = NULL;
		match = 0;
		for (i = 0; i < n; i++) {
			CANDIDATE *r = q + i;
			if (r->rank == round) {
				/* Only check those through to this round */
				if (s == NULL) {
					/* r is first candidate in contest */
					s = r;
				} else {
					/* r is second candidate in contest */
					int cmp =
					    compare_candidates(s, r, args, ret);
					if (cmp == 1) {
						/* s wins */
						s->rank = round + 1;
						r->rank = RANK_VIABLE;
						best = s;
						beat = r;
						match++;
					} else if (cmp == 2) {
						/* r wins */
						r->rank = round + 1;
						s->rank = RANK_VIABLE;
						best = r;
						beat = s;
						match++;
					} else {
						/* Draw - both eliminated */
						s->rank = RANK_VIABLE;
						r->rank = RANK_VIABLE;
					}
					s = NULL;
				}
			}
		}
		if (s != NULL) {
			/* Bye - s goes through */
			s->rank = round + 1;
			best = s;
			match++;
		}
		round++;
	}

	/* Examine the tournament winner */
	if (match == 1) {
		/* Tournament winner must now beat all the others */
		best->rank = RANK_BEST;
		for (i = 0; i < n; i++) {
			CANDIDATE *r = q + i;
			if (r->rank >= RANK_VIABLE) {
				if (r == best) {
					/* Don't compare against self */
					/* EMPTY */
				} else if (r == beat) {
					/* This has already been beaten */
					/* EMPTY */
				} else {
					int cmp =
					    compare_candidates(best, r, args,
							       ret);
					if (cmp != 1) {
						/* r is at least as good as
						 * best */
						best->rank = RANK_VIABLE;
						break;
					}
				}
			}
		}
	} else {
		/* No clear tournament winner */
		if (best->rank >= RANK_VIABLE) {
			best->rank = RANK_VIABLE;
		}
	}
	return best;
}


/*
    FIND A LIST OF POSSIBLE TYPE VALUES

    This routine constructs a list of the possible resolutions for the
    target dependent type t or its promotion.  In the latter case prom
    is set to true.  If neither t or its promotion is target dependent
    then the empty list is returned.
*/

static LIST(TYPE)
possible_types(TYPE t, int *prom)
{
	LIST(TYPE) r = NULL_list(TYPE);
	switch (TAG_type(t)) {
	case type_integer_tag: {
		/* Integral type */
		INT_TYPE it = DEREF_itype(type_integer_rep(t));
		r = DEREF_list(itype_cases(it));
		if (LENGTH_list(r) == 1) {
			/* Type is not target dependent */
			t = DEREF_type(itype_prom(it));
			it = DEREF_itype(type_integer_rep(t));
			r = DEREF_list(itype_cases(it));
			if (LENGTH_list(r) == 1) {
				/* Promoted type is not target dependent */
				r = NULL_list(TYPE);
			} else {
				*prom = 1;
			}
		}
		break;
	}
	case type_bitfield_tag:
	case type_enumerate_tag:
		/* Enumeration and bitfield types */
		t = promote_type(t);
		r = possible_types(t, prom);
		*prom = 1;
		break;
	}
	return r;
}


/*
    CHECK FOR TARGET DEPENDENT OVERLOADED FUNCTION RESOLUTIONS

    This routine is called when an ambiguous overload resolution is
    detected to determine which of the viable candidates to proceed with.
    The parameters are as in resolve_overload.
*/

CANDIDATE *
resolve_ambiguous(CANDIDATE_LIST *p, LIST(EXP) args, TYPE ret, int depth)
{
    CANDIDATE *q = p->elem;
    CANDIDATE *best = q;
    unsigned i, n = p->size;
    unsigned overall_rank = RANK_VIABLE;

    /* Check for arguments of error type */
    if (depth == 0) {
	LIST(EXP) a = args;
	while (!IS_NULL_list(a)) {
	    EXP e = DEREF_exp(HEAD_list(a));
	    if (!IS_NULL_exp(e)) {
		TYPE t = DEREF_type(exp_type(e));
		if (IS_type_error(t)) {
		    /* Error types are ignored */
		    overall_rank = RANK_BEST;
		    break;
		}
	    }
	    a = TAIL_list(a);
	}
    }

    /* Check for target dependent resolutions */
    if (overall_rank != RANK_BEST) {
	unsigned na = 0;
	LIST(EXP) a = args;
	EXP saved[100];
	EXP *save = saved;
	if (n >= 100) {
		save = xmalloc_nof(EXP, n);
	}
	for (i = 0; i < n; i++)save[i] = NULL_exp;
	while (!IS_NULL_list(a)) {
	    EXP e = DEREF_exp(HEAD_list(a));
	    if (!IS_NULL_exp(e)) {
		int prom = 0;
		int have_match = 0;
		TYPE t = DEREF_type(exp_type(e));
		LIST(TYPE) pt = possible_types(t, &prom);
		if (!IS_NULL_list(pt)) {
		    CANDIDATE *r;
		    LIST(TYPE) ps = pt;
		    unsigned new_rank = RANK_TARGET;
		    if (prom) {
			/* Only use promoted types if no exact match */
			for (i = 0; i < n; i++) {
			    r = q + i;
			    if (r->rank >= RANK_VIABLE) {
				if (r->convs[na].rank == CONV_EXACT) {
				    ps = NULL_list(TYPE);
				    new_rank = overall_rank;
				    break;
				}
			    }
			}
		    }
		    overall_rank = new_rank;
		    while (!IS_NULL_list(ps)) {
			TYPE u = t;
			TYPE s = DEREF_type(HEAD_list(ps));
			COPY_type(exp_type(e), s);
			for (i = 0; i < n; i++) {
			    r = q + i;
			    if (r->rank >= RANK_VIABLE) {
				/* Recalculate conversions */
				r->convs[na].rank = CONV_NONE;
				IGNORE viable_candidate(r, args, ret);
				r->rank = RANK_VIABLE;
			    }
			}
			r = resolve_overload(p, args, ret, 1);
			if (r->rank == RANK_VIABLE) {
			    /* Check further arguments */
			    for (i = 0; i < n; i++) {
				/* Save conditions */
				save[i] = q[i].cond;
				q[i].cond = NULL_exp;
			    }
			    r = resolve_ambiguous(p, args, ret, 1);
			    for (i = 0; i < n; i++) {
				/* Restore conditions */
				EXP c = q[i].cond;
				q[i].cond = save[i];
				save[i] = c;
			    }
			}
			COPY_type(exp_type(e), t);
			if (r->rank >= RANK_TARGET) {
			    /* Create condition for resolution */
			    if (prom) {
				    u = promote_type(u);
			    }
			    for (i = 0; i < n; i++) {
				r = q + i;
				if (r->rank >= RANK_TARGET) {
				    EXP c1, c2;
				    TYPE ti = type_sint;
				    TYPE tb = type_bool;
				    NTEST nt = ntest_eq;
				    MAKE_exp_rtti_no(ti, u, c1);
				    MAKE_exp_rtti_no(ti, s, c2);
				    MAKE_exp_compare(tb, nt, c1, c2, c1);
				    c2 = save[i];
				    if (!IS_NULL_exp(c2)) {
					MAKE_exp_log_and(tb, c1, c2, c1);
				    }
				    c2 = r->cond;
				    if (!IS_NULL_exp(c2)) {
					MAKE_exp_log_or(tb, c1, c2, c1);
				    }
				    r->cond = c1;
				    have_match = 1;
				}
				save[i] = NULL_exp;
			    }
			} else if (option(OPT_overload_strict)) {
			    /* Don't have match in all cases */
			    have_match = 0;
			    break;
			}
			ps = TAIL_list(ps);
		    }
		    if (!have_match) {
			overall_rank = RANK_VIABLE;
			break;
		    }
		}
	    }
	    a = TAIL_list(a);
	    na++;
	}
	if (save != saved) {
		xfree_nof(save);
	}
    }

    /* Select last viable candidate */
    for (i = 0; i < n; i++) {
	CANDIDATE *r = q + i;
	if (r->rank >= RANK_VIABLE) {
	    if (overall_rank == RANK_TARGET) {
		if (IS_NULL_exp(r->cond)) {
		    if (depth == 0)r->rank = RANK_ARGS;
		} else {
		    r->rank = overall_rank;
		    best = r;
		}
	    } else {
		r->rank = overall_rank;
		best = r;
	    }
	}
    }
    return best;
}


/*
    LIST OF ALL AMBIGUOUS OVERLOADED FUNCTIONS

    This list is used to hold all the dummy tokenised functions constructed
    to represent target dependent overload resolutions.  The functions are
    determined by the list of candidates, the list of argument types and
    the qualifier used.
*/

typedef struct ambig_func_tag {
	IDENTIFIER id;
	LIST(IDENTIFIER) funcs;
	LIST(TYPE) types;
	QUALIFIER qual;
	struct ambig_func_tag *next;
} AMBIG_FUNCTION;

static AMBIG_FUNCTION *all_ambig_funcs = NULL;


/*
    FIND A PREVIOUS AMBIGUOUS OVERLOADED FUNCTION

    This routine searches the list of all ambiguous overloaded functions
    for one which candidate functions p, argument types q and qualifier
    qual.
*/

static IDENTIFIER
previous_ambig_func(LIST(IDENTIFIER) p, LIST(TYPE) q, QUALIFIER qual)
{
	AMBIG_FUNCTION *f = all_ambig_funcs;
	if (f) {
		unsigned np = LENGTH_list(p);
		unsigned nq = LENGTH_list(q);
		while (f != NULL) {
			if (f->qual == qual) {
				int ok = 1;
				LIST(IDENTIFIER) pf = f->funcs;
				LIST(TYPE) qf = f->types;
				if (LENGTH_list(pf) == np) {
					LIST(IDENTIFIER) pg = p;
					while (!IS_NULL_list(pg)) {
						IDENTIFIER nf =
						    DEREF_id(HEAD_list(pf));
						IDENTIFIER ng =
						    DEREF_id(HEAD_list(pg));
						if (!EQ_id(nf, ng)) {
							ok = 0;
							break;
						}
						pf = TAIL_list(pf);
						pg = TAIL_list(pg);
					}
				}
				if (ok && LENGTH_list(qf) == nq) {
					LIST(TYPE) qg = q;
					while (!IS_NULL_list(qg)) {
						TYPE tf =
						    DEREF_type(HEAD_list(qf));
						TYPE tg =
						    DEREF_type(HEAD_list(qg));
						if (!eq_type(tf, tg)) {
							ok = 0;
							break;
						}
						qf = TAIL_list(qf);
						qg = TAIL_list(qg);
					}
				}
				if (ok) {
					return f->id;
				}
			}
			f = f->next;
		}
	}
	return NULL_id;
}


/*
    CONSTRUCT AN AMBIGUOUS OVERLOADED FUNCTION

    This routine constructs a dummy tokenised function to represent the
    target dependent overload resolution given by the candidates p for
    the function call 'id ( args )' detected by the previous call to
    resolve_ambiguous.  Any errors arising are added to err.
*/

IDENTIFIER
make_ambig_func(CANDIDATE_LIST *p, IDENTIFIER id, LIST(EXP) args,
		QUALIFIER qual, ERROR *err)
{
	EXP res;
	TYPE fn;
	TOKEN tok;
	TYPE form;
	MEMBER mem;
	DECL_SPEC ds;
	IDENTIFIER tid;
	LIST(TYPE) mt;
	AMBIG_FUNCTION *all;
	TYPE ret = NULL_type;
	TYPE et = type_error;
	CANDIDATE *q = p->elem;
	unsigned i, n = p->size;
	NAMESPACE ns = crt_namespace;
	QUALIFIER cq = crt_id_qualifier;
	int tq = crt_templ_qualifier;
	int td = have_type_declaration;
	unsigned tag = id_function_tag;
	HASHID nm = DEREF_hashid(id_name(id));

	/* List of viable candidates */
	LIST(EXP) conds = NULL_list(EXP);
	LIST(TYPE) types = NULL_list(TYPE);
	LIST(IDENTIFIER) funcs = NULL_list(IDENTIFIER);

	/* Check function return types */
	for (i = 0; i < n; i++) {
		CANDIDATE *r = q + i;
		if (r->rank >= RANK_VIABLE) {
			int suspect = 0;
			TYPE ta = NULL_type;
			IDENTIFIER fid = r->base;
			switch (TAG_id(fid)) {
			case id_builtin_tag: {
				ta = DEREF_type(id_builtin_ret(fid));
				break;
			}
			case id_function_tag: {
				TYPE fa = DEREF_type(id_function_type(fid));
				if (IS_type_func(fa)) {
					ta = DEREF_type(type_func_ret(fa));
				}
				break;
			}
			case id_mem_func_tag: {
				TYPE fa = DEREF_type(id_mem_func_type(fid));
				if (IS_type_func(fa)) {
					HASHID fnm = DEREF_hashid(id_name(fid));
					mt = DEREF_list(type_func_mtypes(fa));
					et = DEREF_type(HEAD_list(mt));
					if (IS_hashid_constr(fnm)) {
						ta = DEREF_type(hashid_constr_type(fnm));
					} else {
						ta = DEREF_type(type_func_ret(fa));
						tag = id_mem_func_tag;
					}
				}
				break;
			}
			case id_stat_mem_func_tag: {
				TYPE fa =
				    DEREF_type(id_stat_mem_func_type(fid));
				if (IS_type_func(fa)) {
					mt = DEREF_list(type_func_mtypes(fa));
					et = DEREF_type(HEAD_list(mt));
					ta = DEREF_type(type_func_ret(fa));
					if (tag != id_mem_func_tag) {
						tag = id_stat_mem_func_tag;
					}
				}
				break;
			}
			}
			ret = common_type(ret, ta, &suspect);
			if (suspect) {
				ret = NULL_type;
			}
			CONS_exp(r->cond, conds, conds);
			CONS_id(fid, funcs, funcs);
		}
	}
	if (IS_NULL_type(ret)) {
		/* Couldn't bring return types to common type */
		ERROR err2 = ERR_over_match_best_common();
		add_error(err, err2);
		ret = type_error;
	}
	if (err != KILL_err) {
		*err = list_candidates(*err, p, RANK_VIABLE);
	}

	/* Create list of argument types */
	while (!IS_NULL_list(args)) {
		TYPE t;
		EXP e = DEREF_exp(HEAD_list(args));
		if (IS_NULL_exp(e)) {
			t = et;
			et = type_error;
		} else {
			t = DEREF_type(exp_type(e));
			if (IS_type_bitfield(t)) {
				t = promote_type(t);
			} else {
				CV_SPEC cv = DEREF_cv(type_qual(t));
				if (cv & cv_lvalue) {
					MAKE_type_ref(cv_none, t, t);
				}
			}
		}
		CONS_type(t, types, types);
		args = TAIL_list(args);
	}
	types = REVERSE_list(types);

	/* Check for previous instance */
	tid = previous_ambig_func(funcs, types, qual);
	if (!IS_NULL_id(tid)) {
		DESTROY_list(funcs, SIZE_id);
		DESTROY_list(types, SIZE_type);
		free_exp_list(conds, 1);
		return tid;
	}

	/* Create new instance */
	all = xmalloc_one(AMBIG_FUNCTION);
	all->id = NULL_id;
	all->funcs = funcs;
	all->types = types;
	all->qual = qual;
	all->next = all_ambig_funcs;
	all_ambig_funcs = all;

	/* Scan through argument types */
	crt_id_qualifier = qual_none;
	crt_templ_qualifier = 0;
	have_type_declaration = TYPE_DECL_NONE;
	decl_loc = crt_loc;
	begin_param(id);
	mt = types;
	while (!IS_NULL_list(mt)) {
		HASHID pnm = lookup_anon();
		IDENTIFIER pid = DEREF_id(hashid_id(pnm));
		TYPE t = DEREF_type(HEAD_list(mt));
		pid = make_param_decl(dspec_none, t, pid, CONTEXT_PARAMETER);
		init_param(pid, NULL_exp);
		mt = TAIL_list(mt);
	}
	fn = make_func_type(ret, FUNC_NONE, cv_none, empty_type_set);
	if (tag != id_function_tag) {
		mt = DEREF_list(type_func_ptypes(fn));
		mt = TAIL_list(mt);
		COPY_list(type_func_ptypes(fn), mt);
	}
	end_param();

	/* Create a function identifier */
	ds = (dspec_static | dspec_token | dspec_reserve);
	MAKE_id_function_etc(tag, nm, ds, ns, crt_loc, fn, NULL_id, id);

	/* Create token identifier */
	ns = token_namespace;
	nm = lookup_anon();
	mem = search_member(ns, nm, 1);
	MAKE_tok_func(fn, tok);
	MAKE_id_token(nm, ds, ns, crt_loc, tok, id, tid);
	MAKE_type_token(cv_none, tid, NULL_list(TOKEN), form);
	COPY_type(id_function_etc_form(id), form);
	set_member(mem, tid);
	tok = func_proc_token(tok);

	/* Define token */
	res = install_error(&crt_loc, ERR_over_match_best_install());
	while (!IS_NULL_list(funcs)) {
		EXP c, f;
		LIST(EXP) fargs = NULL_list(EXP);
		LIST(IDENTIFIER) pids = DEREF_list(tok_proc_bids(tok));
		IDENTIFIER fid = DEREF_id(HEAD_list(funcs));
		DESTROY_CONS_exp(destroy, c, conds, conds);
		while (!IS_NULL_list(pids)) {
			/* Build up argument list */
			TYPE t;
			int prom = 0;
			LIST(TYPE) pt;
			IDENTIFIER pid = DEREF_id(HEAD_list(pids));
			EXP e = apply_exp_token(pid, NULL_list(TOKEN), 0);
			e = convert_reference(e, REF_NORMAL);
			t = DEREF_type(exp_type(e));
			pt = possible_types(t, &prom);
			if (!IS_NULL_list(pt)) {
				/* Mark target dependent arguments */
				MAKE_exp_paren(t, e, e);
			}
			CONS_exp(e, fargs, fargs);
			pids = TAIL_list(pids);
		}
		fargs = REVERSE_list(fargs);
		if (IS_id_builtin(fid)) {
			f = apply_builtin(fid, fargs);
		} else {
			HASHID fnm = DEREF_hashid(id_name(fid));
			use_func_id(fid, 1, 0);
			if (IS_hashid_constr(fnm)) {
				f = apply_constr(fid, fargs);
			} else {
				f = apply_func_id(fid, qual, NULL_graph, fargs);
			}
		}
		if (!IS_type_top_etc(ret)) {
			/* Convert to common return type */
			ERROR err2 = NULL_err;
			f = convert_reference(f, REF_ASSIGN);
			f = cast_exp(ret, f, &err2, CAST_IMPLICIT);
			if (!IS_NULL_err(err2)) {
				report(crt_loc, err2);
			}
		}
		if (IS_NULL_exp(res)) {
			free_exp(c, 1);
			res = f;
		} else {
			MAKE_exp_hash_if (ret, c, f, res, res);
		}
		funcs = TAIL_list(funcs);
	}
	IGNORE define_exp_token(tid, res, 1);

	/* Restore previous state */
	have_type_declaration = td;
	crt_templ_qualifier = tq;
	crt_id_qualifier = cq;
	all->id = id;
	return id;
}


/*
    IS AN IDENTIFIER A FUNCTION TEMPLATE?

    This routine returns true if id is a function template.  In this case
    overload resolution is always done even if id is not overloaded.
*/

static int
is_template_func(IDENTIFIER id)
{
	if (IS_id_function_etc(id)) {
		TYPE fn = DEREF_type(id_function_etc_type(id));
		if (IS_type_templ(fn)) {
			return 1;
		}
	}
	return 0;
}


/*
    RESOLVE AN OVERLOADED FUNCTION CALL

    This routine resolves the overloaded function call 'id ( args )' where
    id is an identifier expression.  dep is true when id is a simple
    unqualified function name.  It returns the identifier for id which
    provides the best match for the given arguments.  For ambiguities the
    identifier returned is the first of the viable functions to be declared
    (this is a side effect of the algorithm in resolve_overload and the
    way in which overloaded functions are represented).
*/

IDENTIFIER
resolve_call(IDENTIFIER id, LIST(EXP) args, QUALIFIER qual, int dep)
{
	/* Build up candidate list */
	unsigned sz;
	IDENTIFIER fid = id;
	CANDIDATE_LIST *p = &candidates;
	p->size = 0;
	if (dep) {
		/* Allow for argument dependent look-up */
		LIST(EXP) q = args;
		while (!IS_NULL_list(q)) {
			EXP a = DEREF_exp(HEAD_list(q));
			if (!IS_NULL_exp(a)) {
				TYPE t = DEREF_type(exp_type(a));
				IGNORE koenig_candidates(p, fid, t, KIND_FUNC);
			}
			q = TAIL_list(q);
		}
	}
	add_candidates(p, fid, 1, KIND_FUNC);
	sz = p->size;
	if (sz == 0) {
		/* No candidates */
		EXP a;
		int fn = 2;
		QUALIFIER cq = crt_id_qualifier;
		crt_id_qualifier = (qual & qual_explicit);
		if (qual & qual_mark) {
			fn = 1;
		}
		a = implicit_id_exp(fid, fn);
		if (IS_exp_identifier_etc(a)) {
			fid = DEREF_id(exp_identifier_etc_id(a));
			add_candidates(p, fid, 1, KIND_FUNC);
			sz = p->size;
			if (sz != 0) {
				fid = p->elem[0].func;
			}
		}
		crt_id_qualifier = cq;
	} else {
		fid = p->elem[0].func;
	}

	/* Resolve overloaded functions */
	if (sz > 1) {
		CANDIDATE *q = resolve_overload(p, args, NULL_type, 0);
		IDENTIFIER qid = q->func;
		unsigned rank = q->rank;
		int kind = q->kind;
		if (rank == RANK_BEST) {
			/* Unambiguous resolution */
			if (match_no_viable > 1) {
				ERROR err = ERR_over_match_call_ok(qid);
				if (!IS_NULL_err(err)) {
					report(crt_loc, err);
				}
			}
		} else if (rank == RANK_VIABLE) {
			/* Ambiguous resolution */
			q = resolve_ambiguous(p, args, NULL_type, 0);
			qid = q->func;
			rank = q->rank;
			if (rank == RANK_TARGET) {
				ERROR err = ERR_over_match_call_target(id);
				qid = make_ambig_func(p, qid, args, qual, &err);
				kind = KIND_FUNC;
				report(crt_loc, err);
			} else if (rank == RANK_VIABLE) {
				ERROR err = ERR_over_match_call_ambig(id);
				err = list_candidates(err, p, RANK_VIABLE);
				report(crt_loc, err);
			}
		} else {
			/* Unviable resolution */
			report(crt_loc, ERR_over_match_viable_none(id));
		}
		resolved_kind = kind;
		return qid;
	}

	/* Check template functions */
	if (is_template_func(fid)) {
		ERROR err = NULL_err;
		IDENTIFIER qid = deduce_args(fid, args, 2, 0, 1, &err);
		if (IS_NULL_id(qid)) {
			/* No viable resolution */
			err = concat_error(err, ERR_over_match_viable_none(id));
			qid = fid;
		}
		if (!IS_NULL_err(err)) {
			/* Report any argument deduction errors */
			err = concat_error(err, ERR_temp_deduct_fail(id));
			report(crt_loc, err);
		} else {
			/* Successful argument deduction */
			report(crt_loc, ERR_over_match_call_ok(qid));
		}
		fid = qid;
	}

	/* Don't check non-overloaded functions */
	match_no_args = 0;
	match_no_viable = 0;
	resolved_kind = KIND_FUNC;
	return fid;
}


/*
    RESOLVE AN AMBIGUOUS FUNCTION ADDRESS

    This routine resolves the list of functions ids to see which is the
    best under the template specialisation rules.  If no one best candidate
    is found the null identifier is returned.  This rule is not actually
    in ISO C++, but it could have been.
*/

static IDENTIFIER
resolve_ambig_func(LIST(IDENTIFIER) ids, int depth)
{
	if (!IS_NULL_list(ids)) {
		int cmp;
		IDENTIFIER rid, sid;
		LIST(IDENTIFIER) pids = ids;

		/* Find the first two functions */
		rid = DEREF_id(HEAD_list(pids));
		pids = TAIL_list(pids);
		if (IS_NULL_list(pids)) {
			return rid;
		}
		sid = DEREF_id(HEAD_list(pids));
		pids = TAIL_list(pids);

		/* Compare them */
		cmp = compare_funcs(rid, sid);
		if (cmp == 2) {
			rid = sid;
		} else if (cmp != 1) {
			rid = NULL_id;
		}

		/* Compare the winner against the best of the rest */
		sid = resolve_ambig_func(pids, depth + 1);
		cmp = compare_funcs(rid, sid);
		if (cmp == 2) {
			rid = sid;
		} else if (cmp != 1) {
			rid = NULL_id;
		}

		/* Check overall winner */
		if (depth == 0 && !IS_NULL_id(rid)) {
			pids = ids;
			while (!IS_NULL_list(pids)) {
				sid = DEREF_id(HEAD_list(pids));
				if (!EQ_id(rid, sid)) {
					cmp = compare_funcs(rid, sid);
					if (cmp != 1) {
						return NULL_id;
					}
				}
				pids = TAIL_list(pids);
			}
		}
		return rid;
	}
	return NULL_id;
}


/*
    FIND AN OVERLOADED FUNCTION OF A GIVEN TYPE

    This routine returns whichever of the set of overloaded or ambiguous
    functions id has type t.  Type deduction is allowed for the template
    parameters pids if templ is true. The null identifier is returned if
    none has the correct type, an ambiguous identifier is returned if
    more than one has the correct type (although overload resolution
    occurs if res is true).  If there is a match ignoring linkage
    specifiers then this is returned, the value of eq_func_type for the
    result is assigned to peq.
*/

IDENTIFIER
resolve_func(IDENTIFIER id, TYPE t, int templ, int res, LIST(IDENTIFIER) pids,
	     int *peq)
{
	int best = 2;
	IDENTIFIER rid = NULL_id;
	switch (TAG_id(id)) {
	case id_function_tag:
	case id_mem_func_tag:
	case id_stat_mem_func_tag: {
		/* Check overloaded functions */
		IDENTIFIER fid = id;
		int have_templates = 0;
		LIST(IDENTIFIER) rids = NULL_list(IDENTIFIER);
		while (!IS_NULL_id(fid)) {
			TYPE s;
			int d = 0;
			int eq = 0;
			IDENTIFIER tid = fid;
			if (!IS_NULL_list(pids)) {
				/* Save template parameter values */
				d = save_token_args(pids, NULL_list(TOKEN));
			}
			s = DEREF_type(id_function_etc_type(fid));
			if (IS_type_templ(s) && templ) {
				/* Template functions */
				tid = deduce_func(tid, t, &eq);
				if (!IS_NULL_id(tid)) {
					have_templates = 1;
				}
			} else {
				/* Simple functions */
#if LANGUAGE_CPP
				eq = eq_func_type(s, t, 1, 0);
#else
				TYPE r = type_composite(s, t, 1, 0, KILL_err,
							0);
				if (!IS_NULL_type(r)) {
					eq = 3;
				}
#endif
			}
			if (eq >= best) {
				if (eq > best) {
					/* Better match than previous */
					if (!IS_NULL_list(rids)) {
						DESTROY_list(rids, SIZE_id);
						rids = NULL_list(IDENTIFIER);
					}
					rid = NULL_id;
					best = eq;
				}
				if (!IS_NULL_id(rid)) {
					CONS_id(rid, rids, rids);
				}
				rid = tid;
			}
			if (!IS_NULL_list(pids)) {
				/* Restore template parameters */
				restore_token_args(pids, d);
			}
			fid = DEREF_id(id_function_etc_over(fid));
		}
		if (!IS_NULL_list(rids)) {
			/* Construct ambiguous result */
			HASHID nm;
			NAMESPACE ns;
			DECL_SPEC ds;
			CONS_id(rid, rids, rids);
			if (have_templates && res) {
				/* Perform overload resolution */
				rid = resolve_ambig_func(rids, 0);
				if (!IS_NULL_id(rid)) {
					DESTROY_list(rids, SIZE_id);
					break;
				}
			}
			nm = DEREF_hashid(id_name(id));
			ns = DEREF_nspace(id_parent(id));
			ds = find_ambig_dspec(rids);
			MAKE_id_ambig(nm, ds, ns, crt_loc, rids, 0, rid);
		}
		break;
	}

	case id_ambig_tag: {
		/* Check ambiguous functions */
		LIST(IDENTIFIER) rids = NULL_list(IDENTIFIER);
		LIST(IDENTIFIER) p = DEREF_list(id_ambig_ids(id));
		while (!IS_NULL_list(p)) {
			int eq = 0;
			IDENTIFIER pid = DEREF_id(HEAD_list(p));
			pid = resolve_func(pid, t, templ, 0, pids, &eq);
			if (!IS_NULL_id(pid) && eq >= best) {
				if (eq > best) {
					/* Better match than previous */
					if (!IS_NULL_list(rids)) {
						DESTROY_list(rids, SIZE_id);
						rids = NULL_list(IDENTIFIER);
					}
					rid = NULL_id;
					best = eq;
				}
				if (IS_id_ambig(pid)) {
					LIST(IDENTIFIER) q;
					q = DEREF_list(id_ambig_ids(pid));
					while (!IS_NULL_list(q)) {
						pid = DEREF_id(HEAD_list(q));
						if (!IS_NULL_id(rid)) {
							CONS_id(rid, rids, rids);
						}
						rid = pid;
						q = TAIL_list(q);
					}
				} else {
					if (!IS_NULL_id(rid)) {
						CONS_id(rid, rids, rids);
					}
					rid = pid;
				}
			}
			p = TAIL_list(p);
		}
		if (!IS_NULL_list(rids)) {
			HASHID nm;
			NAMESPACE ns;
			DECL_SPEC ds;
			CONS_id(rid, rids, rids);
			if (res) {
				/* Perform overload resolution */
				rid = resolve_ambig_func(rids, 0);
				if (!IS_NULL_id(rid)) {
					DESTROY_list(rids, SIZE_id);
					break;
				}
			}
			nm = DEREF_hashid(id_name(id));
			ns = DEREF_nspace(id_parent(id));
			ds = find_ambig_dspec(rids);
			MAKE_id_ambig(nm, ds, ns, crt_loc, rids, 0, rid);
		}
		break;
	}
	}
	if (IS_NULL_id(rid)) {
		best = 0;
	}
	*peq = best;
	return rid;
}


/*
    CREATE A RESOLVED OVERLOADED FUNCTION EXPRESSION

    This routine creates a resolved overloaded function expression for
    the function id.
*/

static EXP
make_resolved_exp(IDENTIFIER id, QUALIFIER q, EXP b, int addr, int paren)
{
	EXP e;
	TYPE fn = DEREF_type(id_function_etc_type(id));
	if (IS_id_mem_func(id)) {
		if (!IS_NULL_exp(b)) {
			report(crt_loc, ERR_expr_ref_call());
			q = qual_nested;
		}
		MAKE_exp_member(fn, id, q, e);
	} else {
		MAKE_exp_identifier(fn, id, q, e);
		if (!IS_NULL_exp(b)) {
			e = join_exp(b, e);
		}
	}
	if (addr) {
		if (paren) {
			e = make_paren_exp(e);
		}
		e = make_ref_exp(e, 1);
	}
	return e;
}


/*
    RESOLVE THE ADDRESS OF AN OVERLOADED FUNCTION

    This routine checks the conversion of the expression e to type t.  If
    e is an overloaded function identifier expression and t is a function
    type, or pointer to function type, or pointer to member function type,
    then the various versions of e are checked for the one which matches
    the function type underlying t in the context of the template
    parameters pids.  An error is added to err if this does not exist.
    The result is the appropriate version of e.  Note that member
    expressions which resolve to static function members are replaced
    by identifier expressions at this stage (see make_id_exp).
*/

EXP
resolve_cast(TYPE t, EXP e, ERROR *err, int use, int rescan,
	     LIST(IDENTIFIER) pids)
{
	/* Check for identifier expressions */
	EXP a = e;
	QUALIFIER q;
	int addr = 0;
	int paren = 0;
	IDENTIFIER id;
	EXP b = NULL_exp;
	unsigned tag = TAG_exp(a);
	while (tag == exp_paren_tag) {
		a = DEREF_exp(exp_paren_arg(a));
		tag = TAG_exp(a);
	}
	if (tag == exp_address_tag) {
		/* Address expression */
		a = DEREF_exp(exp_address_arg(a));
		tag = TAG_exp(a);
		addr = 1;
	} else if (tag == exp_address_mem_tag) {
		/* Address of member expression */
		paren = DEREF_int(exp_address_mem_paren(a));
		a = DEREF_exp(exp_address_mem_arg(a));
		tag = TAG_exp(a);
		addr = 1;
	} else if (tag == exp_op_tag) {
		/* Check for undetermined address expressions */
		int op = DEREF_int(exp_op_lex(a));
		EXP c = DEREF_exp(exp_op_arg2(a));
		if (op == lex_and_H1 && IS_NULL_exp(c)) {
			a = DEREF_exp(exp_op_arg1(a));
			tag = TAG_exp(a);
			addr = 1;
		}
	}
	while (tag == exp_paren_tag) {
		a = DEREF_exp(exp_paren_arg(a));
		paren = 1;
		tag = TAG_exp(a);
	}
	if (tag == exp_call_tag) {
		/* Member reference expression */
		b = DEREF_exp(exp_call_arg(a));
		a = DEREF_exp(exp_call_ptr(a));
	}
	if (!IS_exp_identifier_etc(a)) {
		/* Not an identifier expression */
		return e;
	}

	/* Mark identifiers as resolved */
	id = DEREF_id(exp_identifier_etc_id(a));
	q = DEREF_qual(exp_identifier_etc_qual(a));
	if (q & qual_mark) {
		return e;
	}
	if (rescan) {
		/* Rescan function name if necessary */
		id = rescan_func_id(id, q);
	}
	q |= qual_mark;

	/* Check for overloaded functions */
	tag = TAG_id(id);
	switch (tag) {
	case id_function_tag:
	case id_mem_func_tag:
	case id_stat_mem_func_tag:
function_lab: {
		       /* Check functions for overloading */
		       TYPE s;
		       IDENTIFIER over;
		       if (rescan) {
			       goto overload_lab;
		       }
		       if (dependent_cast(id, t)) {
			       /* Allow for template parameters */
			       if (!IS_type_func(t)) {
				       t = rvalue_type(t);
			       }
			       MAKE_exp_op(t, lex_function, e, NULL_exp, e);
			       return e;
		       }
		       over = DEREF_id(id_function_etc_over(id));
		       if (!IS_NULL_id(over)) {
			       goto overload_lab;
		       }
		       s = DEREF_type(id_function_etc_type(id));
		       if (IS_type_templ(s)) {
			       goto overload_lab;
		       }
		       if (tag == id_mem_func_tag) {
			       if (!IS_NULL_exp(b) || addr) {
				       /* Force error in this case */
				       e = make_resolved_exp(id, q, b, addr,
							     paren);
			       }
		       }
		       if (use) {
			       COPY_qual(exp_identifier_etc_qual(a), q);
			       use_id(id, suppress_usage);
		       }
		       break;
	       }

	case id_ambig_tag:
	case id_undef_tag:
overload_lab: {
		      /* Overloaded and ambiguous functions */
		      TYPE fn = find_func_type(t);
		      if (!IS_NULL_type(fn)) {
			      /* Overload resolution */
			      int eq = 0;
			      IDENTIFIER rid;
			      if (dependent_cast(id, t)) {
				      /* Allow for template parameters */
				      if (!IS_type_func(t)) {
					      t = rvalue_type(t);
				      }
				      MAKE_exp_op(t, lex_function, e, NULL_exp,
						  e);
				      return e;
			      }
			      if (tag == id_undef_tag) {
				      goto default_lab;
			      }
			      rid = resolve_func(id, fn, 1, 0, pids, &eq);
			      if (!IS_NULL_id(rid)) {
				      if (IS_id_ambig(rid)) {
					      /* Ambiguous resolution */
					      if (use) {
						      /* Select one function */
						      LIST(IDENTIFIER) ids;
						      IGNORE report_ambiguous(rid, 0, 0, 0);
						      ids = DEREF_list(id_ambig_ids(rid));
						      rid = resolve_ambig_func(ids, 0);
						      if (IS_NULL_id(rid)) {
							      rid = DEREF_id(HEAD_list(ids));
						      }
					      } else {
						      e = NULL_exp;
						      rid = NULL_id;
					      }
				      }
				      if (!IS_NULL_id(rid)) {
					      /* Unique resolution */
					      report(crt_loc, ERR_over_over_ok(rid));
					      e = make_resolved_exp(rid, q, b, addr, paren);
					      if (use) {
						      use_id(rid, suppress_usage);
					      }
				      }
			      } else {
				      /* Unsuccessful resolution */
				      if (use) {
					      add_error(err, ERR_over_over_none(id, fn));
					      e = make_error_exp(0);
				      } else {
					      e = NULL_exp;
				      }
			      }
		      } else {
			      /* No context for resolution */
			      if (tag == id_undef_tag) {
				      goto default_lab;
			      }
			      if (use) {
				      add_error(err, ERR_over_over_context(id));
				      e = make_error_exp(0);
			      } else {
				      e = NULL_exp;
			      }
		      }
		      break;
	      }

	default:
default_lab:
	      /* Other identifiers */
	      if (rescan) {
		      if (use) {
			      EXP c = implicit_id_exp(id, 1);
			      if (IS_exp_identifier_etc(c)) {
				      id = DEREF_id(exp_identifier_etc_id(a));
				      if (IS_id_function_etc(id)) {
					      goto function_lab;
				      }
			      }
		      } else {
			      e = NULL_exp;
		      }
	      }
	      break;
	}
	return e;
}
