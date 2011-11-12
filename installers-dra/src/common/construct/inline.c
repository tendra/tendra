/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: pwe $
$Date: 1998/03/11 11:03:24 $
$Revision: 1.4 $
$Log: inline.c,v $
 * Revision 1.4  1998/03/11  11:03:24  pwe
 * DWARF optimisation info
 *
 * Revision 1.3  1998/02/18  11:22:11  pwe
 * test corrections
 *
 * Revision 1.2  1998/01/20  17:14:23  release
 * Parameter named 'formal' confused SCO cc.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1997/10/23  09:24:25  pwe
 * extra diags
 *
 * Revision 1.4  1997/08/23  13:24:09  pwe
 * no invert order, and NEWDIAGS inlining
 *
Revision 1.3  1997/03/20 17:05:12  currie
Dwarf2 diags

Revision 1.2  1997/02/18 12:56:28  currie
NEW DIAG STRUCTURE

Revision 1.1  1995/04/06 10:44:05  currie
Initial revision

***********************************************************************/

#include <stddef.h>

#include "config.h"

#include "exptypes.h"
#include "exp.h"
#include "expmacs.h"
#include "check.h"
#include "tags.h"
#include "shapemacs.h"
#include "me_fns.h"
#include "externs.h"
#include "flags.h"
#ifdef NEWDIAGS
#include "dg_globs.h"
#include "dg_aux.h"
#endif

#include "inline.h"

/* PROCEDURES */

static exp
last_action(exp e)
{
	if (e == nilexp) {
		return e;
	}

	if (name(e) == ident_tag || name(e) == seq_tag) {
		return last_action(bro(son(e)));
	}

	return e;
}


static void
change_last_shapes(exp e, shape sha)
{
	if (e == nilexp) {
		return;
	}

	if (name(e) == ident_tag || name(e) == seq_tag) {
		sh(e) = sha;
		change_last_shapes(bro(son(e)), sha);
	}

	return;
}


/* replaces a formal paramter by an actual parameter */
static void
replace_pars(exp actual, exp formal_par)
{
	exp def;
	if (!last(actual)) {
		replace_pars(bro(actual), bro(son(formal_par)));
	}

	clearparam(formal_par);
	def = son(formal_par);
	if (no(formal_par) == 1 && shape_size(sh(pt(formal_par))) == 8) {
		setvis(formal_par);
	}
	replace(def, actual, formal_par);

	retcell(def);
	return;
}


/* inlines the procedure application e */
void
inline_exp(exp e)
{
	exp fn = son(e);	/* the name_tag for the function */
	exp pars = bro(fn);	/* the first actual parameter */
	exp body = son(son(son(fn)));	/* the proc_tag exp */
	exp bc, t, q;
	exp lab;
	exp var;		/* the destination to which the result is to be
				   assigned */
	exp new_var = nilexp;
	exp new_dec;		/* a new variable declaration if we make one */
	shape sha = sh(e);	/* the shape delivered by the application */
	exp cond_alt;
	exp res;
	exp last_act;

	if (name(sha) == tophd) {
		/* not returning a result, no ass needed */
		var = nilexp;
		cond_alt = f_make_top();
	} else {
		if (last(e) && name(bro(e)) == ass_tag &&
		    name(son(bro(e))) == name_tag) {
			/* the result of the application is being assigned to
			   a name_tag */
			var = son(bro(e));	/* the destination of the ass */
			cond_alt = f_make_top();	/* the result is being
							   assigned in the body
							   - no need for a
							   delivered result */
			e = bro(e); /* NOTE e CHANGED to ass_tag */
#ifdef NEWDIAGS
			if (diagnose) {
				/* bro(son(e)) is now the call */
				dg_whole_comp(e, bro(son(e)));
				dgf(e) = dgf(bro(son(e)));
			}
#endif
		} else {
			new_dec = me_start_clearvar(sha, sha);
			/* make a new variable to assign to at each res_tag */
			setinlined(new_dec);	/* mark the declaration */
			new_var = me_obtain(new_dec);
			var = new_var;	/* the destination of assignments
					   new_var is killed at end */
			cond_alt = f_contents(sha, copy(new_var));
			/* delivers the contents of the variable - hence the
			 * value */
		}
	}

	lab = me_b3(sh(cond_alt), me_shint(sha, 0), cond_alt, labst_tag);
	/* the labst for the new cond_tag we are making up */
	name(son(lab)) = clear_tag;

	t = fn;	  /* start t so that its bro is the first actual parameter */
	q = body; /* start q so that its son is the first formal parameter */

	while (!last(t)) {
		/* check actual and formal shapes */
		if (name(q) != ident_tag || !isparam(q)) {
			return;  /* no inline if more actuals than formals */
		}
		if (shape_size(sh(bro(t))) != shape_size(sh(son(q)))) {
			return;	/* no inlining if shapes do not match. */
		}
		t = bro(t);		/* next actual */
		q = bro(son(q));	/* next formal */
	}

	if (name(q) == ident_tag && isparam(q)) {
		return;  /* no inline if more formals than actuals */
	}

#ifdef NEWDIAGS
	doing_inlining = 1;
#endif
	bc = copy_res(body, var, lab);
	/* copy the body, making res_tag into assignment to var and
	   jump to lab */
#ifdef NEWDIAGS
	doing_inlining = 0;
#endif
	bc = hold(bc);

	/* if there are any parameters */
	if (!last(fn)) {
		/* replace formals by actuals */
		replace_pars(pars, son(bc));
	}

	IGNORE check(son(bc), son(bc));	/* check the result (proc_tag ?)*/
	res = son(bc); /* remove the proc_tag */
	retcell(bc);	/* and retcell it */

	last_act = last_action(res);
	if (no(son(lab)) == 1 && name(last_act) == goto_tag &&
	    pt(last_act) == lab) {
		/* there is only one (final) goto replacement for return */
		if (name(res) == goto_tag) {
			res = (name(sha) == tophd) ? f_make_top() :
				f_make_value(sha);
		} else {
			change_last_shapes(res, sh(bro(son(lab))));
#ifdef NEWDIAGS
			if (diagnose) {
				dg_whole_comp(last_act, bro(son(lab)));
			}
#endif
			replace(last_act, bro(son(lab)), res);
		}
	} else {
		res = me_b3(sh(lab), res, lab, cond_tag);
	}
	/* make up the cond out of the substituted exp and lab */

	if (var != nilexp) {
		kill_exp(var, var);
	}

	if (new_var != nilexp) { /* we made up a new variable */
		SET(new_dec);
		if (no(new_dec) != 1) {
			/* complete the variable def */
			res = me_complete_id(new_dec, res);
		} else {
			exp r = f_make_top();
#ifdef NEWDIAGS
			if (diagnose) {
				dgf(r) = dgf(bro(son(lab)));
			}
#endif
			replace(bro(son(lab)), r, r);
		}
	}


#ifdef NEWDIAGS
	if (diagnose) {
		dg_complete_inline(e, res);
	}
#endif
	replace(e, res, nilexp); /* replace the call by the inlined stuff */
	kill_exp(fn, fn);	 /* kill off the function name_tag */

	return;
}
