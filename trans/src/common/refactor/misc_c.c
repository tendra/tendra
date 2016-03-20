/* $Id$ */

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

		e = bro(e);
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
		return son(e)->tag == name_tag && isvar(son(son(e))) &&
		       iscaonly(son(son(e))) && !isglob(son(son(e)));
	}

	if (e->tag == seq_tag || e->tag == ident_tag ||
	    (e->tag >= plus_tag && e->tag < cont_tag) ||
	    e->tag == field_tag || e->tag == reff_tag) {
		return invar_list(son(e));
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
	          sh(first)->tag == bothd && no(son(alt)) == 1 &&
	          ((is_tester(son(son(first)), 0) && pt(son(son(first))) == alt) ||
	           (son(son(first))->tag == ident_tag &&
	            is_tester(bro(son(son(son(first)))), 0) &&
	            pt(bro(son(son(son(first))))) == alt));
	if (!extract && first->tag == seq_tag && no(son(alt)) == 1 &&
	    bro(son(first))->tag == apply_tag &&
	    ((is_tester(son(son(first)), 0) && pt(son(son(first))) == alt) ||
	     (son(son(first))->tag == ident_tag &&
	      is_tester(bro(son(son(son(first)))), 0) &&
	      pt(bro(son(son(son(first))))) == alt))) {
		extract = true;
	}

	if (!extract && first->tag == seq_tag && no(son(alt)) == 1 &&
	    ((is_tester(son(son(first)), 1) && pt(son(son(first))) == alt &&
	      bro(son(son(son(first))))->tag == null_tag) ||
	     (son(son(first))->tag == ident_tag &&
	      is_tester(bro(son(son(son(first)))), 1) &&
	      pt(bro(son(son(son(first))))) == alt &&
	      bro(son(bro(son(son(son(first))))))->tag == null_tag))) {
		extract = true;
	}

	if (!extract && first->tag == seq_tag && no(son(alt)) == 1 &&
	    son(son(first))->tag == ident_tag &&
	    is_tester(bro(son(son(son(first)))), 0) &&
	    pt(bro(son(son(son(first))))) == alt &&
	    no(bro(son(son(son(first))))) < 29) {
		extract = true;
	}

	if (!extract && first->tag == seq_tag && no(son(alt)) == 1 &&
	    (is_tester(son(son(first)), 0) && pt(son(son(first))) == alt)) {
		exp q = bro(son(son(first)));
		exp p = NULL;

		if (q->tag == prof_tag) {
			p = q;
		}

		if (q->tag == 0 && bro(q)->tag == seq_tag &&
		    son(son(bro(q)))->tag == prof_tag) {
			p = son(son(bro(q)));
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

	if (!extract && first->tag == seq_tag && no(son(alt)) == 1 &&
	    (is_tester(son(son(first)), 0) && pt(son(son(first))) == alt &&
	     no(son(son(first))) < 29)) {
		extract = true;
	}

	if (!extract && first->tag == seq_tag && no(son(alt)) == 1 &&
	    son(son(first))->tag == ident_tag &&
	    is_tester(bro(son(son(son(first)))), 0) &&
	    pt(bro(son(son(son(first))))) == alt &&
	    no(bro(son(son(son(first))))) < 29) {
		extract = true;
	}

	return extract;
}

