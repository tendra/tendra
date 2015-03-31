/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>

#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/complex_eq.h>
#include <construct/misc_c.h>

static int
invariant_to_apply(exp e);

static int
invar_list(exp e)
{
	while (1) {
		if (e==NULL) {
			return 1;
		}
		if (!invariant_to_apply(e)) {
			return 0;
		}
		if (last(e)) {
			return 1;
		}
		e = bro(e);
	}
}


/* determines if e has no side effects and the same value
   if evaluated immediately before and after any procedure
   call (including a recursive one). The evaluation of the
   procedure arguments is assumed to to affect the value of e.
   e will not be NULL.
*/
static int
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
		return 0;
	}

	return 1;
}


int
is_tester(exp e, int eq)
{
	if (e->tag == test_tag || e->tag == testbit_tag) {
		if (!eq || test_number(e) == f_equal) {
			return 1;
		}
	}
	return 0;
}


int
take_out_of_line(exp first, exp alt, int in_repeat, double scale)
{
	int extract;
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
		extract = 1;
	}

	if (!extract && first->tag == seq_tag && no(son(alt)) == 1 &&
	    ((is_tester(son(son(first)), 1) && pt(son(son(first))) == alt &&
	      bro(son(son(son(first))))->tag == null_tag) ||
	     (son(son(first))->tag == ident_tag &&
	      is_tester(bro(son(son(son(first)))), 1) &&
	      pt(bro(son(son(son(first))))) == alt &&
	      bro(son(bro(son(son(son(first))))))->tag == null_tag))) {
		extract = 1;
	}
	if (!extract && first->tag == seq_tag && no(son(alt)) == 1 &&
	    son(son(first))->tag == ident_tag &&
	    is_tester(bro(son(son(son(first)))), 0) &&
	    pt(bro(son(son(son(first))))) == alt &&
	    no(bro(son(son(son(first))))) < 29) {
		extract = 1;
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
			extract = 1;
		}
	}
	return extract;
}


int
take_out_by_prob(exp first, exp alt)
{
	int extract = 0;
	if (!extract && first->tag == seq_tag && no(son(alt)) == 1 &&
	    (is_tester(son(son(first)), 0) && pt(son(son(first))) == alt &&
	     no(son(son(first))) < 29)) {
		extract = 1;
	}
	if (!extract && first->tag == seq_tag && no(son(alt)) == 1 &&
	    son(son(first))->tag == ident_tag &&
	    is_tester(bro(son(son(son(first)))), 0) &&
	    pt(bro(son(son(son(first))))) == alt &&
	    no(bro(son(son(son(first))))) < 29) {
		extract = 1;
	}
	return extract;
}


/* looks for things like
	(a ~ b) ? a : b
	puts test in t - can make use of delay-slot
*/
int
is_maxop(exp x, exp *t)
{
	exp op1, op2, z, l, w;
	if (x->tag != cond_tag) {
		goto flab0;
	}
	{
		exp xC = son(x);
		if (xC->tag != seq_tag) {
			goto flab0;
		}
		{
			exp xCC = son(xC);
			{
				exp xCCC = son(xCC);
				*t = xCCC;
				if (xCCC->tag != test_tag) {
					goto flab0;
				}
				l=pt(*t);
				{
					exp xCCCC = son(xCCC);
					op1 = xCCCC;
					if (!(!is_floating(sh(op1)->tag))) {
						goto flab0;
					}
					if (last(xCCCC)) {
						goto flab0;
					}
					xCCCC = bro(xCCCC);
					op2 = xCCCC;
					if (!last(xCCCC)) {
						goto flab0;
					}
				}
				if (!last(xCCC)) {
					goto flab0;
				}
			}
			if (last(xCC)) {
				goto flab0;
			}
			xCC = bro(xCC);
			z = xCC;
			if (!(complex_eq_exp(z, op1, NULL,NULL))) {
				goto flab0;
			}
			if (!last(xCC)) {
				goto flab0;
			}
		}
		if (last(xC)) {
			goto flab0;
		}
		xC = bro(xC);
		if (l != xC) {
			goto flab0;
		}
		{
			exp xCC = son(xC);
			z = xCC;
			if (!(no(z) == 1)) {
				goto flab0;
			}
			if (last(xCC)) {
				goto flab0;
			}
			xCC = bro(xCC);
			w = xCC;
			if (!(complex_eq_exp(w, op2, NULL, NULL))) {
				goto flab0;
			}
			if (!last(xCC)) {
				goto flab0;
			}
		}
		if (!last(xC)) {
			goto flab0;
		}
	}
	return 1;
flab0:
	return 0;
}


/* looks for things like
	(a ~ b) ? b : a
	puts test in t - can make use of delay-slot
*/
int
is_minop(exp x, exp *t)
{
	exp op1, op2, z, l, w;
	if (x->tag != cond_tag) {
		goto flab0;
	}
	{
		exp xC = son(x);
		if (xC->tag != seq_tag) {
			goto flab0;
		}
		{
			exp xCC = son(xC);
			{
				exp xCCC = son(xCC);
				*t = xCCC;
				if (xCCC->tag != test_tag) {
					goto flab0;
				}
				l=pt(*t);
				{
					exp xCCCC = son(xCCC);
					op1 = xCCCC;
					if (!(!is_floating(sh(op1)->tag))) {
						goto flab0;
					}
					if (last(xCCCC)) {
						goto flab0;
					}
					xCCCC = bro(xCCCC);
					op2 = xCCCC;
					if (!last(xCCCC)) {
						goto flab0;
					}
				}
				if (!last(xCCC)) {
					goto flab0;
				}
			}
			if (last(xCC)) {
				goto flab0;
			}
			xCC = bro(xCC);
			z = xCC;
			if (!(complex_eq_exp(z, op2,NULL,NULL))) {
				goto flab0;
			}
			if (!last(xCC)) {
				goto flab0;
			}
		}
		if (last(xC)) {
			goto flab0;
		}
		xC = bro(xC);
		if (l != xC) {
			goto flab0;
		}
		{
			exp xCC = son(xC);
			z = xCC;
			if (!(no(z) == 1)) {
				goto flab0;
			}
			if (last(xCC)) {
				goto flab0;
			}
			xCC = bro(xCC);
			w = xCC;
			if (!(complex_eq_exp(w, op1,NULL,NULL))) {
				goto flab0;
			}
			if (!last(xCC)) {
				goto flab0;
			}
		}
		if (!last(xC)) {
			goto flab0;
		}
	}
	return 1;
flab0:
	return 0;
}


int
is_condassign(exp e, exp *to_test, exp *to_ass)
{
	exp arg1 = son(e);
	exp arg2 = bro(arg1);
	exp z;
	exp st;
	exp ass;
	exp val;
	if (arg1->tag != seq_tag) {
		return 0;
	}

	z = son(arg1);
	st = son(z);
	ass = bro(z);

	if (no(son(arg2)) != 1 || bro(son(arg2))->tag != top_tag) {
		return 0;
	}
	if (st->tag != test_tag && st->tag != testbit_tag) {
		return 0;
	}
	if (!last(st)) {
		return 0;
	}
	if (ass->tag != ass_tag) {
		return 0;
	}
	if (son(ass)->tag != name_tag || !isvar(son(son(ass)))) {
		return 0;
	}

	val = bro(son(ass));
	*to_test = st;
	*to_ass = ass;
	if (val->tag == val_tag) {
		return 1;
	}

	return 0;
}

