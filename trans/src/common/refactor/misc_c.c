/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/externs.h>

#include <refactor/misc_c.h>
#include <refactor/query.h>

static bool
invariant_to_apply(exp e);

static bool
invar_list(exp e)
{
	for (;;) {
		if (e == NULL) {
			return true;
		}

		if (!invariant_to_apply(e)) {
			return false;
		}

		if (e->last) {
			return true;
		}

		e = next(e);
	}
}

/*
 * Determine if e has no side effects and the same value
 * if evaluated immediately before and after any procedure
 * call (including a recursive one). The evaluation of the
 * procedure arguments is assumed to to affect the value of e.
 * e will not be NULL.
 */
static bool
invariant_to_apply(exp e)
{
	if (e->tag == cont_tag) {
		return child(e)->tag == name_tag && isvar(child(child(e))) &&
		       iscaonly(child(child(e))) && !isglob(child(child(e)));
	}

	if (e->tag == seq_tag || e->tag == ident_tag ||
	    (e->tag >= plus_tag && e->tag < cont_tag) ||
	    e->tag == field_tag || e->tag == reff_tag) {
		return invar_list(child(e));
	}

	if (e->tag == contvol_tag) {
		return false;
	}

	return true;
}

bool
take_out_of_line(exp first, exp alt, int in_repeat, double scale)
{
	bool extract;

	extract = in_repeat && first->tag == seq_tag &&
	          sh(first)->tag == bothd && no(child(alt)) == 1 &&
	          ((is_tester(child(child(first)), 0) && pt(child(child(first))) == alt) ||
	           (child(child(first))->tag == ident_tag &&
	            is_tester(next(child(child(child(first)))), 0) &&
	            pt(next(child(child(child(first))))) == alt));
	if (!extract && first->tag == seq_tag && no(child(alt)) == 1 &&
	    next(child(first))->tag == apply_tag &&
	    ((is_tester(child(child(first)), 0) && pt(child(child(first))) == alt) ||
	     (child(child(first))->tag == ident_tag &&
	      is_tester(next(child(child(child(first)))), 0) &&
	      pt(next(child(child(child(first))))) == alt))) {
		extract = true;
	}

	if (!extract && first->tag == seq_tag && no(child(alt)) == 1 &&
	    ((is_tester(child(child(first)), 1) && pt(child(child(first))) == alt &&
	      next(child(child(child(first))))->tag == null_tag) ||
	     (child(child(first))->tag == ident_tag &&
	      is_tester(next(child(child(child(first)))), 1) &&
	      pt(next(child(child(child(first))))) == alt &&
	      next(child(next(child(child(child(first))))))->tag == null_tag))) {
		extract = true;
	}

	if (!extract && first->tag == seq_tag && no(child(alt)) == 1 &&
	    child(child(first))->tag == ident_tag &&
	    is_tester(next(child(child(child(first)))), 0) &&
	    pt(next(child(child(child(first))))) == alt &&
	    no(next(child(child(child(first))))) < 29) {
		extract = true;
	}

	if (!extract && first->tag == seq_tag && no(child(alt)) == 1 &&
	    (is_tester(child(child(first)), 0) && pt(child(child(first))) == alt)) {
		exp q = next(child(child(first)));
		exp p = NULL;

		if (q->tag == prof_tag) {
			p = q;
		}

		if (q->tag == 0 && next(q)->tag == seq_tag &&
		    child(child(next(q)))->tag == prof_tag) {
			p = child(child(next(q)));
		}

		if (p != NULL && (double)(no(p)) < (0.29 * scale)) {
			extract = true;
		}
	}

	return extract;
}

bool
take_out_by_prob(exp first, exp alt)
{
	bool extract = false;

	if (!extract && first->tag == seq_tag && no(child(alt)) == 1 &&
	    (is_tester(child(child(first)), 0) && pt(child(child(first))) == alt &&
	     no(child(child(first))) < 29)) {
		extract = true;
	}

	if (!extract && first->tag == seq_tag && no(child(alt)) == 1 &&
	    child(child(first))->tag == ident_tag &&
	    is_tester(next(child(child(child(first)))), 0) &&
	    pt(next(child(child(child(first))))) == alt &&
	    no(next(child(child(child(first))))) < 29) {
		extract = true;
	}

	return extract;
}

