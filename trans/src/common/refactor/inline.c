/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/me_fns.h>

#include <main/flags.h>

#include <refactor/refactor.h>
#include <refactor/optimise.h>

#ifdef TDF_DIAG4
#include <diag4/dg_aux.h>
#include <diag4/diagglob.h>
#endif

static exp
last_action(exp e)
{
	if (e == NULL) {
		return e;
	}

	if (e->tag == ident_tag || e->tag == seq_tag) {
		return last_action(next(child(e)));
	}

	return e;
}

static void
change_last_shapes(exp e, shape sha)
{
	if (e == NULL) {
		return;
	}

	if (e->tag == ident_tag || e->tag == seq_tag) {
		sh(e) = sha;
		change_last_shapes(next(child(e)), sha);
	}
}

/* replaces a formal paramter by an actual parameter */
static void
replace_pars(exp actual, exp formal_par)
{
	exp def;

	if (!actual->last) {
		replace_pars(next(actual), next(child(formal_par)));
	}

	clearparam(formal_par);
	def = child(formal_par);
	if (no(formal_par) == 1 && shape_size(sh(pt(formal_par))) == 8) {
		setvis(formal_par);
	}

	replace(def, actual, formal_par);

	retcell(def);
}

/* inlines the procedure application e */
void
inline_exp(exp e)
{
	exp fn = child(e);	/* the name_tag for the function */
	exp pars = next(fn);	/* the first actual parameter */
	exp body = child(child(child(fn)));	/* the proc_tag exp */
	exp bc, t, q;
	exp lab;
	exp var; /* the destination to which the result is to be assigned */
	exp new_var = NULL;
	exp new_dec;		/* a new variable declaration if we make one */
	shape sha = sh(e);	/* the shape delivered by the application */
	exp cond_alt;
	exp res;
	exp last_act;

	if (sha->tag == tophd) {
		/* not returning a result, no ass needed */
		var = NULL;
		cond_alt = f_make_top();
	} else {
		if (e->last && next(e)->tag == ass_tag &&
		    child(next(e))->tag == name_tag) {

			/* the result of the application is being assigned to a name_tag */
			var = child(next(e));	/* the destination of the ass */

			/* the result is being assigned in the body - no need for a delivered result */
			cond_alt = f_make_top();

			e = next(e); /* NOTE e CHANGED to ass_tag */
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				/* next(child(e)) is now the call */
				dg_whole_comp(e, next(child(e)));
				dgf(e) = dgf(next(child(e)));
			}
#endif
		} else {
			/* make a new variable to assign to at each res_tag */
			new_dec = me_start_clearvar(sha, sha);

			setinlined(new_dec);	/* mark the declaration */
			new_var = me_obtain(new_dec);

			var = new_var;	/* the destination of assignments new_var is killed at end */
			/* delivers the contents of the variable - hence the * value */
			cond_alt = f_contents(sha, copy(new_var));
		}
	}

	lab = me_b3(sh(cond_alt), me_shint(sha, 0), cond_alt, labst_tag);
	/* the labst for the new cond_tag we are making up */
	child(lab)->tag = clear_tag;

	t = fn;	  /* start t so that its next is the first actual parameter */
	q = body; /* start q so that its child is the first formal parameter */

	while (!t->last) {
		/* check actual and formal shapes */
		if (q->tag != ident_tag || !isparam(q)) {
			return;  /* no inline if more actuals than formals */
		}
		if (shape_size(sh(next(t))) != shape_size(sh(child(q)))) {
			return;	/* no inlining if shapes do not match. */
		}
		t = next(t);		/* next actual */
		q = next(child(q));	/* next formal */
	}

	if (q->tag == ident_tag && isparam(q)) {
		return;  /* no inline if more formals than actuals */
	}

#ifdef TDF_DIAG4
	doing_inlining = true;
#endif

	/* copy the body, making res_tag into assignment to var and jump to lab */
	bc = copy_res(body, var, lab);
#ifdef TDF_DIAG4
	doing_inlining = false;
#endif
	bc = hold(bc);

	/* if there are any parameters */
	if (!fn->last) {
		/* replace formals by actuals */
		replace_pars(pars, child(bc));
	}

	IGNORE refactor(child(bc), child(bc));	/* check the result (proc_tag ?)*/
	res = child(bc); /* remove the proc_tag */
	retcell(bc);	/* and retcell it */

	last_act = last_action(res);
	if (no(child(lab)) == 1 && last_act->tag == goto_tag && pt(last_act) == lab) {
		/* there is only one (final) goto replacement for return */
		if (res->tag == goto_tag) {
			res = (sha->tag == tophd) ? f_make_top() :
			      f_make_value(sha);
		} else {
			change_last_shapes(res, sh(next(child(lab))));
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dg_whole_comp(last_act, next(child(lab)));
			}
#endif
			replace(last_act, next(child(lab)), res);
		}
	} else {
		res = me_b3(sh(lab), res, lab, cond_tag);
	}
	/* make up the cond out of the substituted exp and lab */

	if (var != NULL) {
		kill_exp(var, var);
	}

	if (new_var != NULL) { /* we made up a new variable */
		SET(new_dec);
		if (no(new_dec) != 1) {
			/* complete the variable def */
			res = me_complete_id(new_dec, res);
		} else {
			exp r = f_make_top();
#ifdef TDF_DIAG4
			if (diag != DIAG_NONE) {
				dgf(r) = dgf(next(child(lab)));
			}
#endif
			replace(next(child(lab)), r, r);
		}
	}

#ifdef TDF_DIAG4
	if (diag != DIAG_NONE) {
		dg_complete_inline(e, res);
	}
#endif

	replace(e, res, NULL); /* replace the call by the inlined stuff */
	kill_exp(fn, fn);	 /* kill off the function name_tag */
}

