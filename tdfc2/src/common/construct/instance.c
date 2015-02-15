/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include "config.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "exp_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "inst_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "allocate.h"
#include "basetype.h"
#include "check.h"
#include "chktype.h"
#include "class.h"
#include "compile.h"
#include "construct.h"
#include "copy.h"
#include "declare.h"
#include "derive.h"
#include "destroy.h"
#include "dump.h"
#include "file.h"
#include "function.h"
#include "hash.h"
#include "identifier.h"
#include "instance.h"
#include "namespace.h"
#include "operator.h"
#include "overload.h"
#include "predict.h"
#include "redeclare.h"
#include "template.h"
#include "tokdef.h"
#include "token.h"
static void copy_template(IDENTIFIER, int);


/*
    All template instances are formed into a linked list by their prev
    field (most recent first).
*/

INSTANCE all_instances = NULL_inst;


/*
    This routine copies the template arguments p to the start of the list q.
*/

static LIST(TOKEN)
add_template_args(LIST(TOKEN) p, LIST(TOKEN) q)
{
	if (!IS_NULL_list(p)) {
		TOKEN tok = DEREF_tok(HEAD_list(p));
		tok = expand_sort(tok, -1, 1);
		p = TAIL_list(p);
		q = add_template_args(p, q);
		CONS_tok(tok, q, q);
	}
	return q;
}


/*
    This routine is a special case of instance_func which allows for the
    case where some of the template arguments are given explicitly and
    others are deduced.  id gives the template with any explicit arguments
    already bound, and args gives the implicitly deduced arguments which
    are bound to the parameters pids.
*/

static IDENTIFIER
inst_func_deduce(IDENTIFIER id, LIST(IDENTIFIER) pids, LIST(TOKEN) args, int d)
{
	IDENTIFIER fid = DEREF_id(id_alias(id));
	TYPE form = DEREF_type(id_function_etc_form(fid));
	if (!IS_NULL_type(form) && IS_type_token(form)) {
		LIST(TOKEN)dargs;
		fid = DEREF_id(type_token_tok(form));
		dargs = DEREF_list(type_token_args(form));
		if (!IS_NULL_list(dargs)) {
			/* Partially specified template */
			TYPE s = DEREF_type(id_function_etc_type(fid));
			TOKEN sort = DEREF_tok(type_templ_sort(s));
			restore_token_args(pids, d);
			args = add_template_args(dargs, args);
			pids = DEREF_list(tok_templ_pids(sort));
			d = save_token_args(pids, args);
			fid = inst_func_deduce(fid, pids, args, d);
			return fid;
		}
	}
	fid = instance_func(fid, args, 1, 0);
	restore_token_args(pids, d);
	return fid;
}


/*
    This routine returns a list of all the base classes of gr which can
    be deduced to be equal to the class ct.
*/

static LIST(GRAPH)
deduce_graph(GRAPH gr, CLASS_TYPE ct, LIST(IDENTIFIER) pids)
{
	LIST(GRAPH) pr = NULL_list(GRAPH);
	CLASS_TYPE cr = DEREF_ctype(graph_head(gr));
	DECL_SPEC acc = DEREF_dspec(graph_access(gr));

	/* Check for equality */
	int d = save_token_args(pids, NULL_list(TOKEN));
	if (eq_ctype(cr, ct)) {
		CONS_graph(gr, pr, pr);
	}
	restore_token_args(pids, d);

	/* Examine base classes */
	if (acc & dspec_main) {
		LIST(GRAPH) br = DEREF_list(graph_tails(gr));
		while (!IS_NULL_list(br)) {
			GRAPH gs = DEREF_graph(HEAD_list(br));
			LIST(GRAPH) ps = deduce_graph(gs, ct, pids);
			while (!IS_NULL_list(ps)) {
				/* Add deduced graphs to list */
				LIST(GRAPH) pt = pr;
				DESTROY_CONS_graph(destroy, gs, ps, ps);
				while (!IS_NULL_list(pt)) {
					/* Search for previous deductions */
					GRAPH gt = DEREF_graph(HEAD_list(pt));
					if (eq_graph(gt, gs)) {
						break;
					}
					pt = TAIL_list(pt);
				}
				if (IS_NULL_list(pt)) {
					/* Not previously deduced */
					CONS_graph(gs, pr, pr);
				}
			}
			br = TAIL_list(br);
		}
	}
	return pr;
}


/*
    This routine attempts to deduce the function template parameter type t
    from the corresponding function argument type s in the case where both
    are classes.  s can be deduced to be a derived class of a template class
    rather than having to be equal to t.
*/

static int
deduce_derive(TYPE t, TYPE s, LIST(IDENTIFIER) pids)
{
	CLASS_TYPE cs = DEREF_ctype(type_compound_defn(s));
	CLASS_INFO ci = DEREF_cinfo(ctype_info(cs));
	if (ci & cinfo_templ_base) {
		/* Only check if s has a template base class */
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		GRAPH gs = DEREF_graph(ctype_base(cs));
		LIST(GRAPH) ps = deduce_graph(gs, ct, pids);
		if (!IS_NULL_list(ps)) {
			/* Deduction succeeded */
			DESTROY_CONS_graph(destroy, gs, ps, ps);
			if (IS_NULL_list(ps)) {
				/* Unambiguous deduction */
				TYPE fs;
				cs = DEREF_ctype(graph_head(gs));
				fs = DEREF_type(ctype_form(cs));
				if (!IS_NULL_type(fs) && IS_type_token(fs)) {
					IDENTIFIER fid =
					    DEREF_id(type_token_tok(fs));
					if (!IS_id_token(fid)) {
						/* cs is a template class */
						return eq_ctype(ct, cs);
					}
				}
				return 0;
			}
			DESTROY_list(ps, SIZE_graph);
		}
	}
	return 0;
}


/*
    This routine attempts to deduce the function template parameter type t
    from the corresponding function argument type s.  Qualification
    conversions and other inexact type conversions are allowed.  The
    routine returns true if the deduction was successful.
*/

static int
deduce_param(TYPE t, TYPE s, LIST(IDENTIFIER) pids)
{
	int go = 1;
	int depth = 0;
	int all_const = 1;
	do {
		unsigned nt = TAG_type(t);
		unsigned ns = TAG_type(s);
		CV_SPEC qt = find_cv_qual(t);
		CV_SPEC qs = find_cv_qual(s);
		qt &= cv_qual;
		qs &= cv_qual;
		if (qt != qs) {
			/* Allow for qualification conversions */
			if ((qs & ~qt) || !all_const) {
				return eq_type(t, s);
			}
		}
		if (depth && !(qt & cv_const)) {
			all_const = 0;
		}
		if (nt == ns) {
			switch (nt) {
			case type_ptr_tag:
			case type_ref_tag: {
				/* Continue checking pointer types */
				t = DEREF_type(type_ptr_etc_sub(t));
				s = DEREF_type(type_ptr_etc_sub(s));
				depth++;
				break;
			}
			case type_ptr_mem_tag: {
				/* Continue checking pointer to member types */
				CLASS_TYPE ct = DEREF_ctype(type_ptr_mem_of(t));
				CLASS_TYPE cs = DEREF_ctype(type_ptr_mem_of(s));
				if (!eq_ctype(ct, cs)) {
					return 0;
				}
				t = DEREF_type(type_ptr_mem_sub(t));
				s = DEREF_type(type_ptr_mem_sub(s));
				depth += 2;
				break;
			}
			case type_compound_tag: {
				/* Allow derived template classes */
				if (depth < 2 && deduce_derive(t, s, pids)) {
					return 1;
				}
				go = 0;
				break;
			}
			default:
				/* Now check for equality */
				go = 0;
				break;
			}
		} else {
			/* Now check for equality */
			go = 0;
		}
	} while (go);
	return eq_type_unqual(t, s);
}


/*
    This routine performs argument deduction for the call of the function
    template id with the arguments args.  Qualification conversions and
    other inexact deductions are allowed if qual is true.  The null
    identifier is returned to indicate that argument deduction fails.
    The instance corresponding to the deduced arguments is only created
    and returned if create is true.  If force is true then type deduction
    continues after a failure has occurred.
*/

IDENTIFIER
deduce_args(IDENTIFIER id, LIST(EXP) args, int qual, int force, int create,
	    ERROR *err)
{
	IDENTIFIER rid = NULL_id;
	TYPE s = DEREF_type(id_function_etc_type(id));
	TYPE r = DEREF_type(type_templ_defn(s));
	if (IS_type_func(r)) {
		int d;
		int ok = 2;
		int started = 0;
		ERROR err2 = NULL_err;
		TOKEN sort = DEREF_tok(type_templ_sort(s));
		LIST(TYPE) pars = DEREF_list(type_func_mtypes(r));
		LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(sort));
		if (err == KILL_err) {
			err = &err2;
		}
		force_template++;
		d = save_token_args(pids, NULL_list(TOKEN));

		/* Scan through arguments */
		while (!IS_NULL_list(pars) && !IS_NULL_list(args)) {
			int dep = 1;
			TYPE p = DEREF_type(HEAD_list(pars));
			EXP a = DEREF_exp(HEAD_list(args));
			if (qual) {
				dep = depends_on(p, pids);
			}
			if (!IS_NULL_exp(a) && dep) {
				int eq;
				TYPE q;
				int d2 = 0;
				ERROR ferr = NULL_err;
				if (started) {
					/* Each argument deduction is
					 * independent */
					d2 = save_token_args(pids,
							     NULL_list(TOKEN));
				}
				if (IS_type_ref(p)) {
					/* Use referenced type for type
					 * deduction */
					p = DEREF_type(type_ref_sub(p));
					a = resolve_cast(p, a, &ferr, 0, 0,
							 pids);
					if (IS_NULL_exp(a)) {
						q = redef_type;
					} else {
						q = DEREF_type(exp_type(a));
					}
				} else {
					/* Convert argument type */
					a = resolve_cast(p, a, &ferr, 0, 0,
							 pids);
					if (IS_NULL_exp(a)) {
						q = redef_type;
					} else {
						q = DEREF_type(exp_type(a));
						switch (TAG_type(q)) {
						case type_func_tag:
							/* Function to
							 * pointer */
							MAKE_type_ptr(cv_none,
								      q, q);
							break;
						case type_array_tag:
							/* Array to pointer */
							q = DEREF_type(type_array_sub(q));
							MAKE_type_ptr(cv_none,
								      q, q);
							break;
						case type_bitfield_tag:
							/* Promote bitfields */
							q = promote_type(q);
							break;
						default:
							/* Ignore type qualifiers */
							q = qualify_type(q, cv_none, 0);
							break;
						}
					}
				}
				if (qual) {
					/* Allow qualification conversions */
					eq = deduce_param(p, q, pids);
				} else {
					/* Require exact conversion */
					eq = eq_type(p, q);
				}
				if (!eq) {
					/* Type deduction should be identical */
					ok = force;
				}
				if (started) {
					/* Combine argument deductions */
					if (!merge_token_args(pids, d2, qual)) {
						ok = force;
					}
				}
				started = 1;
				if (!ok) {
					break;
				}
			}
			args = TAIL_list(args);
			pars = TAIL_list(pars);
		}

		/* Check the combined results */
		if (ok) {
			LIST(TOKEN) targs = make_token_args(id, pids, err);
			if (ok != 2) {
				/* Report unviable resolution */
				add_error(err, ERR_over_match_viable_none(id));
			}
			if (IS_NULL_err(*err) || force) {
				/* Successful deduction */
				if (create) {
					check_deduced_args(id, pids, targs);
					rid = inst_func_deduce(id, pids, targs,
							       d);
					force_template--;
					return rid;
				}
				rid = id;
			}
			DESTROY_list(targs, SIZE_tok);
		}
		restore_token_args(pids, d);
		force_template--;
	}
	UNUSED(qual);
	return rid;
}


/*
    This routine constructs checks whether an instance of the function
    template id of type t exists.  The null identifier is returned to
    indicate that no such instance exists.  peq is as in resolve_func.
*/

IDENTIFIER
deduce_func(IDENTIFIER id, TYPE t, int *peq)
{
	TYPE s = DEREF_type(id_function_etc_type(id));
	if (IS_type_templ(s)) {
		/* Template function */
		int d;
		int eq = 0;
		TYPE r = DEREF_type(type_templ_defn(s));
		TOKEN sort = DEREF_tok(type_templ_sort(s));
		LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(sort));
		force_template++;
		d = save_token_args(pids, NULL_list(TOKEN));
		if (IS_type_func(r) && IS_type_func(t)) {
			eq = eq_func_type(r, t, 1, 0);
		} else {
			int cmp = eq_type(r, t);
			if (cmp == 1 || cmp == 2)eq = 3;
		}
		if (eq >= 2) {
			/* Types match - form instance */
			ERROR err = NULL_err;
			LIST(TOKEN) args = make_token_args(id, pids, &err);
			if (IS_NULL_err(err)) {
				/* Successful deduction */
				IDENTIFIER rid;
				check_deduced_args(id, pids, args);
				rid = inst_func_deduce(id, pids, args, d);
				force_template--;
				*peq = eq;
				return rid;
			}
			destroy_error(err, 1);
		}
		restore_token_args(pids, d);
		force_template--;
	} else {
		/* Simple function */
		int eq = eq_func_type(s, t, 1, 0);
		if (eq >= 2) {
			*peq = eq;
			return id;
		}
	}
	*peq = 0;
	return NULL_id;
}


/*
    This routine is used to find the type of the specialisation of a
    template conversion function of type t which may be used for a
    conversion to type r.  If no such specialisation exists the null
    type is returned.
*/

TYPE
deduce_conv(TYPE t, TYPE r)
{
	if (IS_type_templ(t)) {
		int d;
		TOKEN sort = DEREF_tok(type_templ_sort(t));
		LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(sort));
		force_template++;
		d = save_token_args(pids, NULL_list(TOKEN));
		t = DEREF_type(type_templ_defn(t));
		t = deduce_conv(t, r);
		restore_token_args(pids, d);
		force_template--;
	} else {
		int eq;
		CV_SPEC cv;
		TYPE s = DEREF_type(type_func_ret(t));
		if (IS_type_ref(s) && !IS_type_ref(r)) {
			s = DEREF_type(type_ref_sub(s));
		}
		cv = DEREF_cv(type_qual(r));
		s = qualify_type(s, cv, 0);
		eq = eq_type(s, r);
		if (eq == 1 || eq == 2) {
			/* Match found */
			t = expand_type(t, 2);
		} else {
			/* No match found */
			t = NULL_type;
		}
	}
	return t;
}


/*
    This routine finds the underlying form for the template application id.
    If this is an undefined class then pi is set to true.
*/

TYPE
find_form(IDENTIFIER id, int *pi)
{
	TYPE t = NULL_type;
	if (!IS_NULL_id(id)) {
		switch (TAG_id(id)) {
		case id_class_name_tag: {
			/* Template classes */
			CLASS_TYPE ct;
			CLASS_INFO ci;
			t = DEREF_type(id_class_name_defn(id));
			while (IS_type_templ(t)) {
				t = DEREF_type(type_templ_defn(t));
			}
			ct = DEREF_ctype(type_compound_defn(t));
			ci = DEREF_cinfo(ctype_info(ct));
			if (!(ci & cinfo_defined)) {
				*pi = 1;
			}
			t = DEREF_type(ctype_form(ct));
			break;
		}
		case id_function_tag:
		case id_mem_func_tag:
		case id_stat_mem_func_tag:
			/* Template functions */
			t = DEREF_type(id_function_etc_form(id));
			break;
		case id_stat_member_tag: {
			/* Static data members of template classes */
			EXP d = DEREF_exp(id_stat_member_term(id));
			if (!IS_NULL_exp(d) && IS_exp_paren(d)) {
				t = DEREF_type(exp_type(d));
			}
			break;
		}
		}
	}
	return t;
}


/*
    This routine returns the list of all instances for the template tid.
*/

static INSTANCE
find_templ_apps(IDENTIFIER tid)
{
	TYPE s;
	TOKEN sort;
	INSTANCE apps;
	if (IS_id_class_name_etc(tid)) {
		s = DEREF_type(id_class_name_etc_defn(tid));
	} else {
		s = DEREF_type(id_function_etc_type(tid));
	}
	sort = DEREF_tok(type_templ_sort(s));
	apps = DEREF_inst(tok_templ_apps(sort));
	return apps;
}


/*
    This routine searches for a previous instance of the template tid
    of sort tok with the template arguments args.
*/

static IDENTIFIER
find_instance(IDENTIFIER tid, TOKEN tok, LIST(TOKEN) args, int def)
{
	INSTANCE apps;
	int fs = force_tokdef;
	int ft = force_template;
	force_tokdef = 0;
	force_template = 0;
	apps = DEREF_inst(tok_templ_apps(tok));
	while (!IS_NULL_inst(apps)) {
		DECL_SPEC acc = DEREF_dspec(inst_templ_access(apps));
		if (!(acc & dspec_alias)) {
			IDENTIFIER fid;
			LIST(TOKEN)fargs;
			TYPE form = DEREF_type(inst_form(apps));
			while (IS_type_templ(form)) {
				form = DEREF_type(type_templ_defn(form));
			}
			fid = DEREF_id(type_token_tok(form));
			fargs = DEREF_list(type_token_args(form));
			if (eq_token_args(tid, fid, args, fargs)) {
				/* Match found */
				IDENTIFIER id = DEREF_id(inst_templ_id(apps));
				if (def) {
					/* Mark instance as used */
					acc |= dspec_used;
					COPY_dspec(inst_templ_access(apps),
						   acc);
				}
				force_template = ft;
				force_tokdef = fs;
				return id;
			}
		}
		apps = DEREF_inst(inst_next(apps));
	}
	force_template = ft;
	force_tokdef = fs;
	return NULL_id;
}


/*
    This routine performs a final validation for the template arguments
    args for the template id of sort sort.
*/

static void
valid_template_args(IDENTIFIER id, TOKEN sort, LIST(TOKEN) args)
{
    LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(sort));
    while (!IS_NULL_list(pids) && !IS_NULL_list(args)) {
	TOKEN arg = DEREF_tok(HEAD_list(args));
	IDENTIFIER pid = DEREF_id(HEAD_list(pids));
	TOKEN par = DEREF_tok(id_token_sort(pid));
	unsigned kind = TAG_tok(par);
	if (!IS_NULL_tok(arg) && TAG_tok(arg) == kind) {
	    if (kind == tok_type_tag) {
		/* Check template types */
		TYPE t = DEREF_type(tok_type_value(arg));
		BASE_TYPE bt = DEREF_btype(tok_type_kind(par));
		bt &= btype_named;
		if (bt != btype_none) {
		    /* Check elaborated template type */
		    int ok = 0;
		    unsigned tag = TAG_type(t);
		    if (bt == btype_enum) {
			if (tag == type_enumerate_tag) {
				ok = 1;
			}
		    } else {
			if (tag == type_compound_tag) {
			    CLASS_TYPE ct;
			    BASE_TYPE key;
			    ct = DEREF_ctype(type_compound_defn(t));
			    key = find_class_key(ct);
			    ok = equal_key(bt, key);
			}
		    }
		    if (!ok && tag != type_error_tag) {
			/* Report type mismatch */
			ERROR err = ERR_temp_res_key(bt, pid, id, t);
			report(crt_loc, err);
		    }
		}
		break;
	    }
	}
	pids = TAIL_list(pids);
	args = TAIL_list(args);
    }
    return;
}


/*
    This routine forms the main body of body_match.  It runs a tournament
    to find the most specialised of the template specialisations apps.
    Note that the result is not necessarily more specialised than all
    the other elements of apps, but if there is such a most specialised
    element then it will be the winner of this tournament.
*/

static INSTANCE
best_match_aux(LIST(INSTANCE)apps)
{
	int cmp;
	TYPE t, s;
	INSTANCE a, b;
	if (IS_NULL_list(apps)) {
		return NULL_inst;
	}
	a = DEREF_inst(HEAD_list(apps));
	b = best_match_aux(TAIL_list(apps));
	if (IS_NULL_inst(b)) {
		return a;
	}
	t = DEREF_type(inst_form(a));
	s = DEREF_type(inst_form(b));
	cmp = eq_type(t, s);
	if (cmp == 2) {
		return b;
	}
	if (cmp == 3) {
		return a;
	}
	return NULL_inst;
}


/*
    This routine finds the most specialised of the template specialisations
    apps.  It returns the null instance if there is no match or the result
    is ambiguous.
*/

static INSTANCE
best_match(LIST(INSTANCE)apps)
{
	INSTANCE a = best_match_aux(apps);
	if (!IS_NULL_inst(a) && LENGTH_list(apps) > 2) {
		TYPE t = DEREF_type(inst_form(a));
		while (!IS_NULL_list(apps)) {
			INSTANCE b = DEREF_inst(HEAD_list(apps));
			if (!EQ_inst(b, a)) {
				TYPE s = DEREF_type(inst_form(b));
				int cmp = eq_type(t, s);
				if (cmp != 3) {
					/* a is not more specialised than b */
					a = NULL_inst;
					break;
				}
			}
			apps = TAIL_list(apps);
		}
	}
	return a;
}


/*
    This routine checks whether the template class instance app contains
    a specialisation of the member mid.
*/

static int
specialise_member(INSTANCE app, IDENTIFIER mid)
{
	if (!IS_NULL_id(mid)) {
		LIST(IDENTIFIER) mems = DEREF_list(inst_templ_mems(app));
		while (!IS_NULL_list(mems)) {
			IDENTIFIER nid = DEREF_id(HEAD_list(mems));
			if (EQ_id(nid, mid)) {
				return 1;
			}
			mems = TAIL_list(mems);
		}
	}
	return 0;
}


/*
    This routine returns the most specialised template specialisation
    from the list apps which contains a specialisation of the member mid
    and matches the instance form.  If there is no such specialisation
    or the result is ambiguous then the null instance is returned.
*/

static INSTANCE
match_form(INSTANCE app, TYPE form, IDENTIFIER mid)
{
	INSTANCE best = NULL_inst;
	LIST(INSTANCE) match = NULL_list(INSTANCE);
	force_template++;
	while (!IS_NULL_inst(app)) {
		DECL_SPEC acc = DEREF_dspec(inst_templ_access(app));
		if (!(acc & (dspec_alias | dspec_main))) {
			if ((acc & dspec_extern) ||
			    specialise_member(app, mid)) {
				TYPE prev = DEREF_type(inst_form(app));
				int cmp = eq_type(prev, form);
				if (cmp == 1 || cmp == 2) {
					/* Matches specialisation */
					CONS_inst(app, match, match);
				}
			}
		}
		app = DEREF_inst(inst_next(app));
	}
	if (!IS_NULL_list(match)) {
		/* Determine most specialised match */
		best = best_match(match);
		if (IS_NULL_inst(best)) {
			/* Ambiguous specialisation */
			report(crt_loc, ERR_temp_class_spec_ambig(form));
		} else {
			/* Unambiguous specialisation */
			IDENTIFIER bid = DEREF_id(inst_templ_id(best));
			report(crt_loc, ERR_temp_class_spec_match(bid));
		}
		DESTROY_list(match, SIZE_inst);
	}
	force_template--;
	return best;
}


/*
    This routine deduces the arguments required for the template
    specialisation spec to instantiate the matching instance form.
*/

static TYPE
specialise_args(INSTANCE spec, TYPE form)
{
	TYPE s = DEREF_type(inst_form(spec));
	if (IS_type_templ(s)) {
		int d;
		int eq;
		TYPE r = DEREF_type(type_templ_defn(s));
		TOKEN sort = DEREF_tok(type_templ_sort(s));
		LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(sort));
		force_template++;
		d = save_token_args(pids, NULL_list(TOKEN));
		eq = eq_type(r, form);
		if (eq == 1 || eq == 2) {
			/* Argument deduction successful */
			ERROR err = NULL_err;
			IDENTIFIER id = DEREF_id(inst_templ_id(spec));
			LIST(TOKEN) args = make_token_args(id, pids, &err);
			if (IS_NULL_err(err)) {
				/* Successful deduction */
				MAKE_type_token(cv_none, id, args, form);
				COPY_inst(type_token_app(form), spec);
			} else {
				destroy_error(err, 1);
			}
		}
		restore_token_args(pids, d);
		force_template--;
	} else {
		IDENTIFIER id = DEREF_id(inst_templ_id(spec));
		MAKE_type_token(cv_none, id, NULL_list(TOKEN), form);
	}
	return form;
}


/*
    This routine finds the template specialisation which best matches the
    template instance given by form.  If mid is the null identifier then
    only explicit specialisations are considered.  Otherwise any
    specialisation which specialises the member mid is considered.
*/

static TYPE
specialise_form(TYPE form, IDENTIFIER mid)
{
    if (!IS_NULL_type(form) && IS_type_token(form)) {
	IDENTIFIER tid = DEREF_id(type_token_tok(form));
	INSTANCE app = DEREF_inst(type_token_app(form));
	if (!IS_NULL_inst(app)) {
	    TYPE spec = DEREF_type(inst_templ_spec(app));
	    if (IS_NULL_type(spec) || !IS_NULL_id(mid)) {
		/* Not previously determined */
		DECL_SPEC acc = DEREF_dspec(inst_templ_access(app));
		if (acc & dspec_explicit) {
		    /* Explicit specialisation */
		    IDENTIFIER id = DEREF_id(inst_templ_id(app));
		    LIST(TOKEN)args = NULL_list(TOKEN);
		    MAKE_type_token(cv_none, id, args, spec);
		    COPY_inst(type_token_app(spec), app);
		} else if (acc & dspec_instance) {
		    /* Find matching partial specialisations */
		    INSTANCE best = find_templ_apps(tid);
		    best = match_form(best, form, mid);
		    if (!IS_NULL_inst(best)) {
			/* Use matching specialisation */
			spec = specialise_args(best, form);
		    } else {
			/* Use primary form */
			spec = form;
		    }
		}
		if (IS_NULL_id(mid)) {
		    /* Record best explicit match */
		    COPY_type(inst_templ_spec(app), spec);
		}
	    }
	    if (!IS_NULL_type(spec)) {
		    form = spec;
	    }
	}
    }
    return form;
}


/*
    This routine is identical to find_copied except that it allows for
    template instances when type is not 2.
*/

static IDENTIFIER
find_copied_member(IDENTIFIER cid, IDENTIFIER id, int res, int type)
{
	if (type != 2) {
		int undef = 0;
		TYPE form = find_form(id, &undef);
		if (!IS_NULL_type(form) && IS_type_token(form)) {
			/* Template instance */
			IDENTIFIER tid = DEREF_id(type_token_tok(form));
			LIST(TOKEN)args = DEREF_list(type_token_args(form));
			tid = find_copied(cid, tid, 1);
			id = apply_template(tid, args, 0, 0);
			return id;
		}
	}
	id = find_copied(cid, id, res);
	return id;
}


/*
    This routine finds the specialisation best matching the template instance
    or class template member id and specialising the member pid.
*/

static IDENTIFIER
match_specialise(IDENTIFIER id, IDENTIFIER pid)
{
	int undef = 0;
	IDENTIFIER tid = NULL_id;
	TYPE form = find_form(id, &undef);
	if (!IS_NULL_type(form)) {
		if (IS_type_token(form)) {
			/* Template instance */
			TYPE spec = specialise_form(form, pid);
			tid = DEREF_id(type_token_tok(spec));
		} else if (IS_type_instance(form)) {
			/* Member of template class */
			NAMESPACE cns;
			tid = DEREF_id(type_instance_id(form));
			cns = DEREF_nspace(id_parent(id));
			if (!IS_NULL_nspace(cns)) {
				IDENTIFIER cid = DEREF_id(nspace_name(cns));
				IDENTIFIER rid = match_specialise(cid, tid);
				if (!IS_NULL_id(rid)) {
					if (EQ_id(rid, cid)) {
						tid = id;
					} else {
						tid = find_copied_member(rid,
									 tid,
									 1, 2);
					}
				}
			}
		}
	}
	return tid;
}


/*
    This routine sets the template parameters for the instance form.
*/

static int
set_templ_args(TYPE form)
{
	int d = 0;
	INSTANCE app = DEREF_inst(type_token_app(form));
	TYPE spec = DEREF_type(inst_form(app));
	if (IS_type_templ(spec)) {
		TOKEN sort = DEREF_tok(type_templ_sort(spec));
		LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(sort));
		LIST(TOKEN) args = DEREF_list(type_token_args(form));
		d = save_token_args(pids, args);
	}
	return d;
}


/*
    This routine restores the template parameters for the instance form.
    d is the value returned from the corresponding call to set_templ_args.
*/

static void
restore_templ_args(TYPE form, int d)
{
	INSTANCE app = DEREF_inst(type_token_app(form));
	TYPE spec = DEREF_type(inst_form(app));
	if (IS_type_templ(spec)) {
		TOKEN sort = DEREF_tok(type_templ_sort(spec));
		LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(sort));
		restore_token_args(pids, d);
	}
	return;
}


/*
    This routine reports the instantiation of the template with the
    given form.
*/

static void
report_instance(TYPE form)
{
	ERROR err = ERR_temp_inst_def(form);
	if (!IS_NULL_err(err)) {
		if (is_templ_depend(form)) {
			destroy_error(err, 1);
		} else {
			report(crt_loc, err);
		}
	}
	return;
}


/*
    This routine creates an instance of the function template id with
    the template arguments args.
*/

IDENTIFIER
instance_func(IDENTIFIER id, LIST(TOKEN) args, int func, int def)
{
	int d = 0;
	IDENTIFIER tid;
	IDENTIFIER rid = DEREF_id(id_alias(id));
	TYPE s = DEREF_type(id_function_etc_type(rid));
	TOKEN sort = DEREF_tok(type_templ_sort(s));
	LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(sort));
	if (func) {
		/* Arguments already bound */
		/* EMPTY */
	} else {
		/* Bind arguments to parameters */
		d = save_token_args(pids, args);
	}

	/* Find template instance */
	tid = find_instance(rid, sort, args, def);
	if (IS_NULL_id(tid)) {
		/* Create a new instance */
		TYPE form;
		ERROR perr;
		PTR(LOCATION) ploc;
		valid_template_args(rid, sort, args);
		MAKE_type_token(cv_none, rid, args, form);
		dump_template++;
		ploc = MAKE_ptr(SIZE_loc);
		COPY_loc(ploc, crt_loc);
		perr = set_prefix(ERR_temp_inst_comment(form, ploc));
		if (incr_value(OPT_VAL_instance_depth)) {
			DECL_SPEC ds;
			INSTANCE apps ;
			HASHID nm = DEREF_hashid(id_name(rid));

			/* Create new instance */
			tid = copy_id(rid, 2);
			nm = expand_name(nm, NULL_ctype);
			COPY_hashid(id_name(tid), nm);
			ds = DEREF_dspec(id_storage(tid));
			ds &= ~(dspec_used | dspec_called | dspec_done |
				dspec_defn);
			ds &= ~dspec_template;
			ds |= dspec_instance;
			COPY_dspec(id_storage(tid), ds);
			COPY_exp(id_function_etc_defn(tid), NULL_exp);
			COPY_id(id_function_etc_over(tid), NULL_id);
			COPY_type(id_function_etc_form(tid), form);

			/* Check operator type */
			s = DEREF_type(id_function_etc_type(tid));
#if LANGUAGE_CPP
			if (IS_hashid_op(nm)) {
				int mem = 1;
				int alloc = 0;
				if (IS_id_function(tid)) {
					mem = 0;
				}
				s = check_operator(s, tid, mem, &alloc);
				if (alloc) {
					recheck_allocator(tid, alloc);
				}
			}
#endif

			/* Add new template application */
			if (IS_type_func(s)) {
				/* Full specialisation */
				ds = dspec_instance;
			} else {
				/* Partial specialisation */
				ds = dspec_implicit;
			}
			if (def) {
				ds |= dspec_used;
			}
			if (is_templ_depend(form)) {
				ds |= dspec_mutable;
			}
			apps = DEREF_inst(tok_templ_apps(sort));
			MAKE_inst_templ(form, apps, tid, ds, all_instances,
					apps);
			COPY_inst(type_token_app(form), apps);
			COPY_inst(tok_templ_apps(sort), apps);
			all_instances = apps;
			if (do_dump) {
				/* Dump template instance information */
				dump_declare(tid, &crt_loc, 0);
				dump_instance(tid, form, form);
			}
		} else {
			/* Instantiation depth too great */
			tid = rid;
		}
		decr_value(OPT_VAL_instance_depth);
		restore_prefix(perr);
		DESTROY_ptr(ploc, SIZE_loc);
		dump_template--;
	}
	if (func) {
		/* Check for templates */
		s = DEREF_type(id_function_etc_type(tid));
		if (IS_type_templ(s)) {
			tid = NULL_id;
		}
	} else {
		restore_token_args(pids, d);
	}
	return tid;
}


/*
    This routine creates an instance of the class template id with the
    template arguments args.  def is true if the class should be
    defined.
*/

IDENTIFIER
instance_type(IDENTIFIER id, LIST(TOKEN) args, int type, int def)
{
	int d = 0;
	int undef = 0;
	CLASS_TYPE cs;
	IDENTIFIER tid;
	TYPE form = NULL_type;
	IDENTIFIER rid = DEREF_id(id_alias(id));
	TYPE s = DEREF_type(id_class_name_defn(rid));
	TOKEN sort = DEREF_tok(type_templ_sort(s));
	LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(sort));
	if (type) {
		/* Arguments already bound */
		/* EMPTY */
	} else {
		/* Bind arguments to parameters */
		d = save_token_args(pids, args);
	}

	/* Check template class */
	while (IS_type_templ(s)) {
		s = DEREF_type(type_templ_defn(s));
	}
	cs = DEREF_ctype(type_compound_defn(s));

	/* Find template instance */
	tid = find_instance(rid, sort, args, def);
	if (!IS_NULL_id(tid) && def) {
		form = find_form(tid, &undef);
	}
	if (IS_NULL_id(tid) || (def && undef)) {
		/* Create a new instance or define an existing one */
		ERROR perr;
		PTR(LOCATION)ploc;
		if (IS_NULL_type(form)) {
			valid_template_args(rid, sort, args);
			MAKE_type_token(cv_none, rid, args, form);
		}
		dump_template++;
		if (def) {
			report_instance(form);
		}
		ploc = MAKE_ptr(SIZE_loc);
		COPY_loc(ploc, crt_loc);
		perr = set_prefix(ERR_temp_inst_comment(form, ploc));
		if (incr_value(OPT_VAL_instance_depth)) {
			TYPE t;
			int d2 = 0;
			DECL_SPEC ds;
			CLASS_TYPE ct;
			int created = 0;
			TYPE spec = form;
			CLASS_INFO ci = cinfo_templ_base;

			/* Create new instance if necessary */
			if (IS_NULL_id(tid)) {
				INSTANCE apps;
				tid = copy_id(rid, 2);
				ds = DEREF_dspec(id_storage(tid));
				ds &= ~(dspec_used | dspec_done | dspec_defn);
				ds &= ~dspec_template;
				ds |= dspec_instance;
				COPY_dspec(id_storage(tid), ds);

				/* Add new template application */
				ds = dspec_instance;
				if (def)ds |= dspec_used;
				if (is_templ_depend(form))ds |= dspec_mutable;
				apps = DEREF_inst(tok_templ_apps(sort));
				MAKE_inst_templ(form, apps, tid, ds,
						all_instances, apps);
				COPY_inst(type_token_app(form), apps);
				COPY_inst(tok_templ_apps(sort), apps);
				all_instances = apps;
				created = 1;
			}

			/* Check for matching specialisations */
			if (def) {
				spec = specialise_form(form, NULL_id);
				if (!EQ_type(spec, form)) {
					/* Specialisation found */
					d2 = set_templ_args(spec);
					rid = DEREF_id(type_token_tok(spec));
					s = DEREF_type(id_class_name_defn(rid));
					while (IS_type_templ(s)) {
						s = DEREF_type(type_templ_defn(s));
					}
					cs = DEREF_ctype(type_compound_defn(s));
					if (!created) {
						if (do_dump) {
							dump_instance(tid,
								      form,
								      spec);
						}
					}
				}
			}

			/* Instantiate class members */
			t = DEREF_type(id_class_name_defn(tid));
			s = DEREF_type(ctype_form(cs));
			COPY_type(ctype_form(cs), t);
			while (IS_type_templ(t)) {
				ci = cinfo_template;
				t = DEREF_type(type_templ_defn(t));
			}
			ct = DEREF_ctype(type_compound_defn(t));
			COPY_type(ctype_form(ct), form);
			if (do_dump && created) {
				/* Dump template instance information */
				dump_declare(tid, &crt_loc, 0);
				dump_instance(tid, form, spec);
			}
			copy_members(ct, cs, ci, def);
			COPY_type(ctype_form(cs), s);
			if (!EQ_type(spec, form)) {
				/* Reset specialisation parameters */
				restore_templ_args(spec, d2);
			}
		} else {
			/* Instantiation depth too great */
			if (IS_NULL_id(tid)) {
				tid = rid;
			}
		}
		decr_value(OPT_VAL_instance_depth);
		restore_prefix(perr);
		DESTROY_ptr(ploc, SIZE_loc);
		dump_template--;
	}
	if (type) {
		/* Check for templates */
		TYPE t = DEREF_type(id_class_name_defn(tid));
		if (IS_type_templ(t)) {
			tid = NULL_id;
		}
	} else {
		restore_token_args(pids, d);
	}
	return tid;
}


/*
    This routine is called with def true whenever a class type is
    encountered which is complete but not defined in a context where a
    complete type is required.  If ct is a template class instance then
    the definition is provided.  If def is false then ct is marked as
    complete if possible.
*/

void
complete_class(CLASS_TYPE ct, int def)
{
    CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
    if (!(ci & cinfo_defined)) {
	IDENTIFIER cid = DEREF_id(ctype_name(ct));
	IDENTIFIER sid = match_specialise(cid, NULL_id);
	if (!IS_NULL_id(sid) && IS_id_class_name(sid)) {
	    /* Template class instance */
	    CLASS_TYPE cs;
	    CLASS_INFO cj;
	    TYPE s = DEREF_type(id_class_name_defn(sid));
	    while (IS_type_templ(s)) {
		s = DEREF_type(type_templ_defn(s));
	    }
	    cs = DEREF_ctype(type_compound_defn(s));
	    if (!EQ_ctype(cs, ct)) {
		/* Allow for nested template classes */
		complete_class(cs, def);
	    }
	    cj = DEREF_cinfo(ctype_info(cs));
	    if (cj & cinfo_complete) {
		/* Template class is complete */
		ci |= cinfo_complete;
		COPY_cinfo(ctype_info(ct), ci);
		if (def) {
		    /* Define template class */
		    TYPE form = DEREF_type(ctype_form(ct));
		    if (!IS_NULL_type(form)) {
			if (IS_type_token(form)) {
			    /* Template instance */
			    IDENTIFIER tid;
			    LIST(TOKEN) args;
			    tid = DEREF_id(type_token_tok(form));
			    args = DEREF_list(type_token_args(form));
			    IGNORE instance_type(tid, args, 0, 1);
			} else {
			    /* Nested template class */
			    EXP e;
			    MAKE_exp_value(s, e);
			    IGNORE define_templ_member(cid, sid, form, e);
			}
		    }
		}
	    }
	}
    }
    return;
}


/*
    This routine checks the template specialisation declared with
    parameters pids and arguments form.
*/

static void
check_spec_args(LIST(IDENTIFIER) pids, TYPE form)
{
	LIST(TOKEN) args = DEREF_list(type_token_args(form));
	while (!IS_NULL_list(args)) {
		TOKEN a = DEREF_tok(HEAD_list(args));
		if (IS_tok_exp(a)) {
			/* Non-type argument */
			EXP e = DEREF_exp(tok_exp_value(a));
			if (depends_on_exp(e, pids, 0) == 1) {
				report(crt_loc,
				       ERR_temp_class_spec_depend(form));
			}
		}
		args = TAIL_list(args);
	}
	return;
}


/*
    This routine checks the specialisation spec of the template tid.
    It identifies spec with any previous matching specialisation and
    returns this previous version.  If no such match is found the
    original instance is returned.
*/

static INSTANCE
check_specialise(IDENTIFIER tid, INSTANCE spec, int type)
{
    INSTANCE apps;
    ERROR merr = NULL_err;
    INSTANCE eq = NULL_inst;
    TYPE form = DEREF_type(inst_form(spec));

    /* Scan through previous instances */
    force_template++;
    apps = find_templ_apps(tid);
    while (!IS_NULL_inst(apps)) {
	if (!EQ_inst(spec, apps)) {
	    DECL_SPEC acc = DEREF_dspec(inst_templ_access(apps));
	    if (!(acc & dspec_alias)) {
		/* Compare with previous instance */
		TYPE prev = DEREF_type(inst_form(apps));
		int cmp = eq_type(form, prev);
		if (acc & dspec_main) {
		    /* Comparison with primary template */
		    if (cmp == 1 && (type < 2 && crt_templ_qualifier)) {
			ERROR err = ERR_temp_class_spec_primary(form);
			report(crt_loc, err);
			crt_templ_qualifier = 0;
		    } else if (cmp == 2 || cmp == 4) {
			ERROR err = ERR_temp_class_spec_primary(form);
			report(crt_loc, err);
		    }
		}
		if (cmp == 2 && (acc & dspec_instance)) {
		    if (!(acc & dspec_explicit) && type < 3) {
			/* Specialisation matches previous use */
			ERROR err = ERR_temp_spec_post(form, prev);
			merr = concat_error(merr, err);
		    }
		}
		if (cmp == 1) {
		    /* Equality of template specialisations */
		    eq = apps;
		    break;
		}
	    }
	}
	apps = DEREF_inst(inst_next(apps));
    }
    force_template--;

    /* Identify equal specialisations */
    if (!IS_NULL_inst(eq)) {
	TYPE prev = DEREF_type(inst_form(eq));
	DECL_SPEC acc = DEREF_dspec(inst_templ_access(spec));
	acc |= dspec_alias;
	COPY_dspec(inst_templ_access(spec), acc);
	COPY_inst(inst_alias(spec), eq);
	if (!IS_NULL_err(merr)) {
		destroy_error(merr, 1);
	}

	/* Identify template parameters */
	if (IS_type_templ(form) && IS_type_templ(prev)) {
	    TOKEN as = DEREF_tok(type_templ_sort(form));
	    TOKEN at = DEREF_tok(type_templ_sort(prev));
	    LIST(IDENTIFIER) ps = DEREF_list(tok_templ_pids(as));
	    LIST(IDENTIFIER) pt = DEREF_list(tok_templ_pids(at));
	    IGNORE eq_templ_params(ps, pt);

	    /* Re-check more recent instances */
	    apps = all_instances;
	    while (!EQ_inst(apps, spec)) {
		acc = DEREF_dspec(inst_templ_access(apps));
		if (!(acc & dspec_alias)) {
		    IDENTIFIER pid;
		    prev = DEREF_type(inst_form(apps));
		    while (IS_type_templ(prev)) {
			prev = DEREF_type(type_templ_defn(prev));
		    }
		    pid = DEREF_id(type_token_tok(prev));
		    IGNORE check_specialise(pid, apps, 3);
		}
		apps = DEREF_inst(inst_templ_prev(apps));
	    }
	}
    } else {
	/* Report matching instances */
	if (!IS_NULL_err(merr)) {
		report(crt_loc, merr);
	}
	eq = spec;
    }
    return eq;
}


/*
    A specialisation of a template function is inline only if it is
    explicitly declared to be, independently of whether its function
    template is.  However no storage class specifiers may be given for
    a specialisation.  This routine adjusts the linkage of the template
    function id of form form declared with declaration specifiers ds.
*/

static void
adjust_func_templ(IDENTIFIER id, DECL_SPEC ds, TYPE form)
{
	if (!IS_NULL_type(form)) {
		DECL_SPEC pds;
		int redecl = 0;
		if (IS_type_token(form)) {
			INSTANCE app = DEREF_inst(type_token_app(form));
			if (!IS_NULL_inst(app)) {
				/* Check for redeclarations */
				DECL_SPEC acc =
				    DEREF_dspec(inst_templ_access(app));
				if (acc & dspec_static) {
					redecl = 1;
				}
				acc |= dspec_static;
				COPY_dspec(inst_templ_access(app), acc);
			}
		} else if (IS_type_instance(form)) {
			/* Check for redeclarations */
			DECL_SPEC acc = DEREF_dspec(type_instance_access(form));
			if (acc & dspec_static) {
				redecl = 1;
			}
			acc |= dspec_static;
			COPY_dspec(type_instance_access(form), acc);
		}
		if (!redecl && !IS_NULL_id(id) && IS_id_function_etc(id)) {
			/* Adjust inline specifier */
			pds = DEREF_dspec(id_storage(id));
			pds &= ~dspec_inline;
			if (ds & dspec_inline) {
				/* Mark inline functions */
				pds |= dspec_inline;
			}
			COPY_dspec(id_storage(id), pds);
		}
		pds = (ds & dspec_storage);
		if (pds != dspec_none) {
			/* Check for storage class specifiers */
			report(decl_loc, ERR_dcl_stc_expl_spec(pds));
		}
		if (crt_linkage == dspec_c) {
			/* Check for C linkage */
			report(decl_loc, ERR_temp_decl_linkage());
		}
	}
	return;
}


/*
    This routine examines the template specialisation t of the given form.
    expl is true for an explicit specialisation and false for a simple
    redeclaration.  The routine returns 2 if t represents an explicit
    instantiation, 1 if it represents an explicit specialisation, and 0
    otherwise.
*/

static int
bind_templ_spec(IDENTIFIER *pid, TYPE t, TYPE form, int type, int expl)
{
    int def = 0;
    if (expl) {
	DECL_SPEC acc;
	TOKEN sort = NULL_tok;
	NAMESPACE ns = crt_namespace;
	LIST(IDENTIFIER) pids = NULL_list(IDENTIFIER);
	INSTANCE spec = DEREF_inst(type_token_app(form));
	IDENTIFIER tid = DEREF_id(type_token_tok(form));
	if (IS_type_templ(t)) {
	    /* Find template information */
	    sort = DEREF_tok(type_templ_sort(t));
	    pids = DEREF_list(tok_templ_pids(sort));
	    ns = DEREF_nspace(tok_templ_pars(sort));
	}
	if (IS_NULL_list(pids)) {
	    if (IS_NULL_nspace(ns)) {
		/* Explicit instantiation */
		acc = DEREF_dspec(inst_templ_access(spec));
		if (acc & dspec_register) {
		    report(decl_loc, ERR_temp_spec_reinst(form));
		} else if (acc & dspec_explicit) {
		    report(decl_loc, ERR_temp_spec_redecl(form));
		}
		acc |= dspec_register;
		COPY_dspec(inst_templ_access(spec), acc);
		def = (type == 2 ? 3 : 2);
	    } else {
		/* Explicit specialisation */
		spec = check_specialise(tid, spec, type);
		if (type != 2) {
		    acc = DEREF_dspec(inst_templ_access(spec));
		    if (acc & dspec_register) {
			report(decl_loc, ERR_temp_spec_redecl(form));
		    } else if (acc & dspec_explicit) {
			report(decl_loc, ERR_temp_spec_respec(form));
		    } else if (acc & (dspec_used | dspec_called)) {
			report(decl_loc, ERR_temp_spec_used(form));
		    }
		    acc |= dspec_explicit;
		    COPY_dspec(inst_templ_access(spec), acc);
		}
		*pid = DEREF_id(inst_templ_id(spec));
		def = 1;
	    }
	} else {
	    /* Partial specialisation */
	    check_spec_args(pids, form);
	    if (check_templ_dargs(t)) {
		/* Check template default arguments */
		report(decl_loc, ERR_temp_class_spec_darg());
	    }
	    MAKE_type_templ(cv_none, sort, form, 1, form);
	    COPY_type(inst_form(spec), form);
	    spec = check_specialise(tid, spec, type);
	    acc = DEREF_dspec(inst_templ_access(spec));
	    acc &= ~dspec_instance;
	    acc |= dspec_template;
	    if (type == 0 && !(acc & dspec_main)) {
		/* Can't partially specialise functions */
		report(decl_loc, ERR_temp_decl_func());
	    }
	    if (type != 2) {
		if (acc & dspec_called) {
		    /* Have specialised members */
		    report(decl_loc, ERR_temp_spec_used(form));
		}
		acc |= dspec_extern;
	    }
	    COPY_dspec(inst_templ_access(spec), acc);
	    *pid = DEREF_id(inst_templ_id(spec));
	}
	if (type == 0 && check_func_dargs(t, 0, 0)) {
	    /* Check function default arguments */
	    report(decl_loc, ERR_temp_class_spec_darg());
	}
    }
    return def;
}


/*
    This flag is set by bind_specialise to indicate the type of template
    declaration encountered.  The values are as in bind_templ_spec.
*/

int bound_specialise = 0;


/*
    This routine binds any template parameters in the template
    specialisation given by the declarator id of type t and declaration
    specifiers ds.  It returns those components of t which bind to the
    underlying object.  For example in 'template < class T > int A < T >::a'
    the component of the type which binds to 'a' is 'int'.  The
    'template < class T >' component binds to the 'A < T >::' qualifier.
    Note that this analysis may be done prior to any replacement of
    inferred types in t.
*/

TYPE
bind_specialise(IDENTIFIER *pid, TYPE t, DECL_SPEC ds, int type, int force,
		int init)
{
    IDENTIFIER id = *pid;
    if (!IS_NULL_id(id)) {
	DECL_SPEC pds = DEREF_dspec(id_storage(id));
	if (pds & dspec_instance) {
	    /* Template instance */
	    TYPE f;
	    int def = 0;
	    int undef = 0;
	    INSTANCE spec = NULL_inst;

	    /* Examine enclosing class */
	    NAMESPACE ns = DEREF_nspace(id_parent(id));
	    if (!IS_NULL_nspace(ns) && IS_nspace_ctype(ns)) {
		IDENTIFIER cid = DEREF_id(nspace_name(ns));
		IDENTIFIER sid = cid;
		t = bind_specialise(&sid, t, ds, 2, 0, init);
		if (!EQ_id(sid, cid)) {
		    /* Changed specialisation */
		    IDENTIFIER qid = id;
		    id = find_copied_member(sid, qid, 0, type);
		    if (type != 2) {
			/* Update namespace stacks */
			QUALIFIER q = qual_nested;
			end_declarator(qid, 1);
			begin_declarator(id, q, NULL_nspace, 1);
		    }
		    *pid = id;
		}
		f = find_form(sid, &undef);
		if (!IS_NULL_type(f) && IS_type_token(f)) {
		    spec = DEREF_inst(type_token_app(f));
		}
	    }

	    /* Select overloaded function */
	    if (type == 0 && IS_id_function_etc(id)) {
		TYPE fn = t;
		if (!IS_NULL_type(fn)) {
		    TYPE ret;
		    int eq = 0;
		    IDENTIFIER fid;
		    LIST(IDENTIFIER) pids = NULL_list(IDENTIFIER);
		    if (IS_type_templ(fn)) {
			fn = DEREF_type(type_templ_defn(fn));
		    }
		    ret = inferred_return(fn, id);
		    fid = resolve_func(id, fn, 1, 0, pids, &eq);
		    if (IS_NULL_id(fid)) {
			/* No match found */
			report(decl_loc, ERR_temp_spec_type(fn, id));
		    } else if (IS_id_ambig(fid)) {
			/* More than one match found */
			IGNORE report_ambiguous(fid, 0, 0, 0);
			fid = NULL_id;
		    }
		    if (!IS_NULL_type(ret)) {
			/* Restore return type */
			COPY_type(type_func_ret(fn), ret);
		    }
		    *pid = fid;
		    id = fid;
		}
	    }

	    /* Examine template instance */
	    f = find_form(id, &undef);
	    if (!IS_NULL_type(f) && IS_type_token(f)) {
		IDENTIFIER tid = DEREF_id(type_token_tok(f));
		unsigned tag = TAG_id(tid);
		if (tag != id_token_tag) {
		    /* Examine template qualifiers */
		    if (!IS_NULL_type(t) && IS_type_templ(t)) {
			def = bind_templ_spec(&id, t, f, type, 1);
			if (def == 1 || def == 2) {
			    /* Explicit specialisations */
			    t = DEREF_type(type_templ_defn(t));
			} else if (def == 0) {
			    /* Partial specialisations */
			    if (type == 2 || crt_templ_qualifier) {
				t = DEREF_type(type_templ_defn(t));
			    }
			}
		    } else {
			int expl = 0;
			TYPE s = type_error;
			if (!(ds & dspec_friend)) {
			    /* A friend declaration is allowed */
			    report(decl_loc, ERR_temp_spec_prefix());
			    expl = 1;
			}
			def = bind_templ_spec(&id, s, f, type, expl);
		    }
		    if (tag == id_class_name_tag) {
			if (type == 0) {
			    report(decl_loc, ERR_temp_spec_bad(f));
			    id = NULL_id;
			}
		    } else {
			if (type) {
			    report(decl_loc, ERR_temp_spec_bad(f));
			    id = NULL_id;
			} else {
			}
		    }
		    bound_specialise = def;
		    *pid = id;
		}
	    } else {
		/* Check for explicit instantiations */
		if (!IS_NULL_type(t) && IS_type_templ(t)) {
		    TOKEN sort = DEREF_tok(type_templ_sort(t));
		    NAMESPACE pns = DEREF_nspace(tok_templ_pars(sort));
		    if (IS_NULL_nspace(pns)) {
			if (!IS_NULL_type(f) && IS_type_instance(f)) {
			    def = (type == 2 ? 3 : 2);
			} else {
			    report(decl_loc, ERR_temp_explicit_templ());
			}
			t = DEREF_type(type_templ_defn(t));
			bound_specialise = def;
		    }
		}
	    }

	    /* Adjust function linkage */
	    if (!type) {
		    adjust_func_templ(id, ds, f);
	    }

	    /* Record member specialisations */
	    if (!IS_NULL_inst(spec)) {
		DECL_SPEC acc;
		LIST(IDENTIFIER)mems;
		if (def == 0 || def == 1) {
		    if (!IS_NULL_type(f) && IS_type_instance(f)) {
			IDENTIFIER mid = DEREF_id(type_instance_id(f));
			mems = DEREF_list(inst_templ_mems(spec));
			CONS_id(mid, mems, mems);
			COPY_list(inst_templ_mems(spec), mems);
		    }
		}
		acc = DEREF_dspec(inst_templ_access(spec));
		acc |= dspec_called;
		COPY_dspec(inst_templ_access(spec), acc);
	    }

	    /* Mark explicit specialisations */
	    if (def == 1 && !IS_NULL_id(id)) {
		if (type != 2) {
		    /* Explicit specialisations are exported */
		    export_template(id, 1);
		}
	    }

	    /* Mark explicit instantiations */
	    if (def == 2 && !IS_NULL_id(id)) {
		if (force == 2) {
		    /* template-id required in instantiation */
		    ERROR err = ERR_temp_explicit_id(id);
		    report(decl_loc, err);
		}
		if (init) {
		    /* Can't have definition as well */
		    report(decl_loc, ERR_temp_explicit_def());
		}
		define_template(id, 1);
	    }

	} else if (force) {
	    /* Not a template instance */
	    if (pds & dspec_template) {
		if (IS_id_function_etc(id)) {
		    /* Template function */
		    allow_templ_dargs = 0;
		    *pid = parse_id_template(id, NIL(PPTOKEN), 0);
		    allow_templ_dargs = 1;
		    crt_templ_qualifier = 1;
		    t = bind_specialise(pid, t, ds, type, 2, init);
		} else {
		    /* Template class */
		    report(decl_loc, ERR_temp_param_none(id));
		    *pid = NULL_id;
		}
	    } else {
		NAMESPACE ns = DEREF_nspace(id_parent(id));
		if (!IS_NULL_nspace(ns) && IS_nspace_ctype(ns)) {
		    IDENTIFIER cid = DEREF_id(nspace_name(ns));
		    IDENTIFIER sid = cid;
		    t = bind_specialise(&sid, t, ds, 2, 0, init);
		    if (!EQ_id(sid, cid)) {
			/* Changed specialisation */
			IDENTIFIER qid = id;
			id = find_copied_member(sid, qid, 0, type);
			if (type != 2) {
			    /* Update namespace stacks */
			    QUALIFIER q = qual_nested;
			    end_declarator(qid, 1);
			    begin_declarator(id, q, NULL_nspace, 1);
			}
			*pid = id;
		    }
		}
		if (IS_type_templ(t)) {
		    /* Invalid template declaration */
		    id = underlying_id(id);
		    report(decl_loc, ERR_temp_param_none(id));
		    *pid = NULL_id;
		}
	    }
	}
    }
    return t;
}


/*
    This routine synthesises a list of dummy arguments for the function
    template id.
*/

static LIST(EXP)
synthesise_args(IDENTIFIER id)
{
	LIST(TYPE) pars;
	LIST(EXP) args = NULL_list(EXP);
	TYPE fn = DEREF_type(id_function_etc_type(id));
	while (IS_type_templ(fn)) {
		fn = DEREF_type(type_templ_defn(fn));
	}
	pars = DEREF_list(type_func_mtypes(fn));
	while (!IS_NULL_list(pars)) {
		EXP a;
		TYPE t = DEREF_type(HEAD_list(pars));
		if (IS_type_ref(t)) {
			/* Do reference conversions */
			t = DEREF_type(type_ref_sub(t));
		}
		MAKE_exp_value(t, a);
		CONS_exp(a, args, args);
		pars = TAIL_list(pars);
	}
	return REVERSE_list(args);
}


/*
    This routine compares the function templates tid and sid.  It returns
    1 if tid is more specialised than sid, 2 if sid is more specialised,
    and 0 otherwise.
*/

int
compare_specs(IDENTIFIER tid, IDENTIFIER sid)
{
	if (!EQ_id(tid, sid)) {
		IDENTIFIER ds, dt;
		LIST(EXP) args;
		ERROR err = NULL_err;
		args = synthesise_args(sid);
		ds = deduce_args(tid, args, 0, 0, 0, &err);
		free_exp_list(args, 1);
		args = synthesise_args(tid);
		dt = deduce_args(sid, args, 0, 0, 0, &err);
		free_exp_list(args, 1);
		if (!IS_NULL_err(err)) {
			destroy_error(err, 1);
		}
		if (!IS_NULL_id(ds)) {
			if (IS_NULL_id(dt)) {
				return 2;
			}
		} else {
			if (!IS_NULL_id(dt)) {
				return 1;
			}
		}
	}
	return 0;
}


/*
    This routine checks the declaration of the function id which is
    either a template function itself or overloads a template function.
*/

void
templ_func_decl(IDENTIFIER id)
{
	while (!IS_NULL_id(id)) {
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		ds |= dspec_template;
		COPY_dspec(id_storage(id), ds);
		id = DEREF_id(id_function_etc_over(id));
	}
	return;
}


/*
    The variable pending_templates holds a list of all the template
    instances which should be defined at the next available opportunity.
    The variable still_pending_templates holds a list of all those
    instances which should be defined if the corresponding template
    is defined at some later stage.
*/

LIST(IDENTIFIER) pending_templates = NULL_list(IDENTIFIER);
LIST(IDENTIFIER) still_pending_templates = NULL_list(IDENTIFIER);


/*
    This routine adds all members of the template class ct to the list of
    templates to be defined.
*/

static void
define_members(CLASS_TYPE ct)
{
	TYPE form = DEREF_type(ctype_form(ct));
	if (!IS_NULL_type(form)) {
		NAMESPACE ns = DEREF_nspace(ctype_member(ct));
		MEMBER mem = DEREF_member(nspace_ctype_first(ns));
		GRAPH gr = DEREF_graph(ctype_base(ct));
		LIST(GRAPH) br = DEREF_list(graph_tails(gr));
		while (!IS_NULL_list(br)) {
			/* Scan through base classes */
			GRAPH gs = DEREF_graph(HEAD_list(br));
			CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
			define_members(cs);
			br = TAIL_list(br);
		}
		while (!IS_NULL_member(mem)) {
			/* Scan through class members */
			IDENTIFIER id = DEREF_id(member_id(mem));
			IDENTIFIER alt = DEREF_id(member_alt(mem));
			if (!IS_NULL_id(id)) {
				define_template(id, 1);
			}
			if (!IS_NULL_id(alt) && !EQ_id(id, alt)) {
				define_template(alt, 2);
			}
			mem = DEREF_member(member_next(mem));
		}
	}
	return;
}


/*
    This routine adds the template instance id to the list of templates
    to be defined.  The identifier is marked as defined even though the
    actual definition occurs later.  Explicit instantiations are indicated
    by expl being true.
*/

void
define_template(IDENTIFIER id, int expl)
{
    DECL_SPEC ds = DEREF_dspec(id_storage(id));
    if (ds & dspec_inherit) {
	/* Inherited functions */
	id = DEREF_id(id_alias(id));
	ds = DEREF_dspec(id_storage(id));
    }
    if ((ds & dspec_instance) && !(ds & dspec_implicit)) {
	if (dependent_id(id)) {
	    /* Ignore template dependent instantiations */
	    return;
	}
	switch (TAG_id(id)) {
	    case id_class_name_tag:
	    case id_class_alias_tag: {
		if (expl) {
		    TYPE t = DEREF_type(id_class_name_etc_defn(id));
		    if (IS_type_compound(t)) {
			/* Define all template members */
			ERROR err = check_incomplete(t);
			if (IS_NULL_err(err)) {
			    CLASS_TYPE ct;
			    NAMESPACE ns = DEREF_nspace(id_parent(id));
			    check_decl_nspace(id, ns, 1, crt_namespace);
			    ct = DEREF_ctype(type_compound_defn(t));
			    define_members(ct);
			} else {
			    ERROR err2 = ERR_temp_explicit_incompl();
			    err = concat_error(err, err2);
			    report(crt_loc, err);
			}
		    }
		}
		break;
	    }
	    case id_function_tag:
	    case id_mem_func_tag:
	    case id_stat_mem_func_tag:
		/* Template functions */
		if (!(ds & dspec_defn)) {
		    CONS_id(id, pending_templates, pending_templates);
		    COPY_dspec(id_storage(id), (ds | dspec_defn));
		    COPY_loc(id_loc(id), crt_loc);
		}
		if (expl == 2) {
		    /* Allow for overloaded functions */
		    id = DEREF_id(id_function_etc_over(id));
		    if (!IS_NULL_id(id)) {
			    define_template(id, 2);
		    }
		}
		break;
	    case id_stat_member_tag: {
		/* Static data members of class templates */
		if (!(ds & dspec_defn)) {
		    TYPE t = DEREF_type(id_stat_member_type(id));
		    CV_SPEC cv = DEREF_cv(type_qual(t));
		    COPY_dspec(id_storage(id), (ds | dspec_defn));
		    COPY_loc(id_loc(id), crt_loc);
		    CONS_id(id, pending_templates, pending_templates);
		    if (cv == (cv_lvalue | cv_const)) {
			copy_template(id, 2);
		    }
		}
		break;
	    }
	}
    }
    return;
}


/*
    This routine binds the template arguments for the identifier tid to
    the specialisation sid and then defines id to be e.  It returns false
    if any template argument depends on an unbound template parameter.
*/

static int
bind_template(IDENTIFIER tid, IDENTIFIER id, IDENTIFIER sid, EXP e, int bound)
{
    if (IS_NULL_id(tid)) {
	/* Binding complete - copy definition */
	if (!bound) {
	    /* Suppress output of object definition */
	    DECL_SPEC ds = DEREF_dspec(id_storage(id));
	    COPY_dspec(id_storage(id), (ds | dspec_done));
	}
	copy_object(id, e);
    } else {
	/* Examine parent namespace */
	TYPE p, q;
	int undef = 0;
	IDENTIFIER pid = NULL_id;
	IDENTIFIER qid = NULL_id;
	NAMESPACE pns = DEREF_nspace(id_parent(tid));
	NAMESPACE qns = DEREF_nspace(id_parent(sid));
	if (!IS_NULL_nspace(pns)) {
	    switch (TAG_nspace(pns)) {
		case nspace_block_tag:
		case nspace_param_tag:
		case nspace_dummy_tag:
		case nspace_ctype_tag:
		    /* Find enclosing class or function */
		    pid = DEREF_id(nspace_name(pns));
		    qid = DEREF_id(nspace_name(qns));
		    break;
	    }
	}

	/* Bind template arguments */
	p = find_form(tid, &undef);
	q = find_form(sid, &undef);
	if (!IS_NULL_type(p) && IS_type_token(p)) {
	    /* Template application found */
	    TYPE s = NULL_type;
	    IDENTIFIER rid = NULL_id;
	    DECL_SPEC acc = dspec_none;
	    if (!IS_NULL_type(q) && IS_type_token(q)) {
		/* Check for specialised template */
		INSTANCE spec = DEREF_inst(type_token_app(q));
		s = DEREF_type(inst_form(spec));
		rid = DEREF_id(inst_templ_id(spec));
		acc = DEREF_dspec(inst_templ_access(spec));
	    }
	    if (!(acc & dspec_template)) {
		/* Not specialised - use primary template */
		rid = DEREF_id(type_token_tok(p));
		if (IS_id_class_name(rid)) {
		    s = DEREF_type(id_class_name_defn(rid));
		} else {
		    s = DEREF_type(id_function_etc_type(rid));
		}
		acc = dspec_main;
	    }
	    if (IS_type_templ(s)) {
		/* Bind template parameters */
		int d;
		LIST(TOKEN) args;
		LIST(IDENTIFIER) pids;
		TOKEN sort = DEREF_tok(type_templ_sort(s));
		pids = DEREF_list(tok_templ_pids(sort));
		if (acc & dspec_main) {
		    /* Bound to primary template */
		    args = DEREF_list(type_token_args(p));
		} else {
		    /* Bound to template specialisation */
		    args = NULL_list(TOKEN);
		}
		d = save_token_args(pids, args);
		if (IS_NULL_list(args)) {
		    force_template++;
		    s = DEREF_type(type_templ_defn(s));
		    if (!eq_type(s, p)) {
			error(ERR_INTERNAL, "bind_template failed");
			bound = 0;
		    }
		    force_template--;
		}

		/* Bind parent templates */
		if (is_templ_depend(p)) {
			bound = 0;
		}
		if (IS_id_class_name(rid)) {
		    TYPE t;
		    CLASS_TYPE cs;
		    s = DEREF_type(id_class_name_defn(rid));
		    while (IS_type_templ(s)) {
			s = DEREF_type(type_templ_defn(s));
		    }
		    cs = DEREF_ctype(type_compound_defn(s));
		    s = DEREF_type(ctype_form(cs));
		    t = DEREF_type(id_class_name_defn(tid));
		    COPY_type(ctype_form(cs), t);
		    bound = bind_template(pid, id, qid, e, bound);
		    COPY_type(ctype_form(cs), s);
		} else {
		    bound = bind_template(pid, id, qid, e, bound);
		}
		restore_token_args(pids, d);
	    } else {
		/* Explicit specialisation */
		bound = 0;
	    }
	} else {
	    /* Bind parent templates */
	    bound = bind_template(pid, id, qid, e, bound);
	}
    }
    return bound;
}


/*
    This routine defines the template member id given by form to be the
    specialisation tid of value e.  It returns the declaration specifiers
    of the result.
*/

DECL_SPEC
define_templ_member(IDENTIFIER id, IDENTIFIER tid, TYPE form, EXP e)
{
	ERROR perr;
	DECL_SPEC ds;
	PTR(LOCATION) ploc;
	dump_template++;
	report_instance(form);
	ploc = MAKE_ptr(SIZE_loc);
	COPY_loc(ploc, crt_loc);
	perr = set_prefix(ERR_temp_inst_comment(form, ploc));
	if (incr_value(OPT_VAL_instance_depth)) {
		/* Bind template arguments and copy function */
		LOCATION loc;
		loc = crt_loc;
		bad_crt_loc++;
		DEREF_loc(id_loc(tid), crt_loc);
		IGNORE bind_template(id, id, tid, e, 1);
		ds = DEREF_dspec(id_storage(id));
		clear_templates(0);
		crt_loc = loc;
		bad_crt_loc--;
	} else {
		/* Instantiation depth too great */
		ds = DEREF_dspec(id_storage(id));
	}
	decr_value(OPT_VAL_instance_depth);
	restore_prefix(perr);
	DESTROY_ptr(ploc, SIZE_loc);
	dump_template--;
	return ds;
}


/*
    This routine defines the template application id.  force is true to
    indicate the end of the translation unit when a non-exported template
    should have been defined.
*/

static void
copy_template(IDENTIFIER id, int force)
{
	/* Find the template information */
	EXP e = NULL_exp;
	TYPE form = NULL_type;
	IDENTIFIER tid = NULL_id;
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	switch (TAG_id(id)) {
	case id_function_tag:
	case id_mem_func_tag:
	case id_stat_mem_func_tag: {
		/* Template functions */
		e = DEREF_exp(id_function_etc_defn(id));
		if (!IS_NULL_exp(e)) {
			/* Template already defined */
			return;
		}
		form = DEREF_type(id_function_etc_form(id));
		tid = match_specialise(id, NULL_id);
		if (!IS_NULL_id(tid)) {
			/* Find function definition */
			DECL_SPEC tds = DEREF_dspec(id_storage(tid));
			if ((tds & dspec_instance) && !(tds & dspec_defn)) {
				/* This is itself a template */
				if (!EQ_id(tid, id)) {
					copy_template(tid, force);
				}
			}
			e = DEREF_exp(id_function_etc_defn(tid));
		}
		break;
	}
	case id_stat_member_tag: {
		/* Static data members */
		int undef = 0;
		e = DEREF_exp(id_stat_member_init(id));
		if (!IS_NULL_exp(e)) {
			/* Template member already defined */
			return;
		}
		form = find_form(id, &undef);
		tid = match_specialise(id, NULL_id);
		if (!IS_NULL_id(tid)) {
			/* Find static member definition */
			DECL_SPEC tds = DEREF_dspec(id_storage(tid));
			if ((tds & dspec_instance) && !(tds & dspec_defn)) {
				/* This is itself a template */
				if (!EQ_id(tid, id)) {
					copy_template(tid, force);
				}
			}
			e = DEREF_exp(id_stat_member_init(tid));
		}
		if (force == 2) {
			/* Check for constants only */
			if (IS_NULL_exp(e)) {
				return;
			}
			switch (TAG_exp(e)) {
			case exp_int_lit_tag:
				break;
			case exp_null_tag:
				break;
			default:
				return;
			}
		}
		break;
	}
	}

	/* Check for exported templates */
	if (is_exported(tid)) {
		export_template(id, 0);
		ds = DEREF_dspec(id_storage(id));
	}

	/* Define the object */
	if (IS_NULL_exp(e)) {
		if (force && !is_exported(id)) {
			/* Check for non-exported templates */
			if (!(ds & dspec_inline)) {
				report(crt_loc, ERR_temp_decl_undef(id));
				export_template(id, 0);
				ds = DEREF_dspec(id_storage(id));
			}
		}
		CONS_id(id, still_pending_templates, still_pending_templates);
		ds &= ~dspec_defn;
	} else {
		ds = define_templ_member(id, tid, form, e);
		ds |= dspec_defn;
	}
	COPY_dspec(id_storage(id), ds);
	return;
}


/*
    This routine calls copy_template for each element of the list p.
*/

static void
copy_template_list(LIST(IDENTIFIER) p, int force)
{
	if (!IS_NULL_list(p)) {
		IDENTIFIER id;
		DESTROY_CONS_id(destroy, id, p, p);
		copy_template_list(p, force);
		DEREF_loc(id_loc(id), crt_loc);
		copy_template(id, force);
	}
	return;
}


/*
    This routine defines all the template instances in the list of pending
    templates.  The list of still pending templates is only checked if
    templ is nonzero.  A templ value of 2 is used to indicate the end of
    the file.
*/

void
clear_templates(int templ)
{
	if (!in_function_defn && !in_class_defn) {
		LIST(IDENTIFIER) p = pending_templates;
		if (templ) {
			/* Include still pending templates */
			p = APPEND_list(still_pending_templates, p);
			still_pending_templates = NULL_list(IDENTIFIER);
		}
		if (!IS_NULL_list(p)) {
			LOCATION loc;
			loc = crt_loc;
			bad_crt_loc++;
			while (!IS_NULL_list(p)) {
				/* Scan through pending templates */
				pending_templates = NULL_list(IDENTIFIER);
				copy_template_list(p, 0);
				p = pending_templates;
			}
			if (templ == 2) {
				/* Check for exported templates */
				p = still_pending_templates;
				if (!IS_NULL_list(p)) {
					still_pending_templates =
					    NULL_list(IDENTIFIER);
					copy_template_list(p, 1);
				}
			}
			crt_loc = loc;
			bad_crt_loc--;
		}
	}
	return;
}
