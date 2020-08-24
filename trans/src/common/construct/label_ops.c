/*
 * Copyright 2002-2012, The TenDRA Project.
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

#include <construct/label_ops.h>
#include <construct/exp.h>
#include <construct/installglob.h>

#include <main/flags.h>

#include <refactor/refactor.h>


/* label_is_next returns 1 if lab is a labst which immediately
   follows e, otherwise 0. e will not be NULL
*/
int
label_is_next(exp lab, exp e)
{
	if (~optim & OPTIM_JUMPS) {
		return 0;
	}
	while (e->last) {
		e = next(e);
		if (e == NULL || e->tag >= ass_tag || sh(e)->tag != bothd) {
			return 0;
		}
	}
	if (next(e)->tag == labst_tag) {
		return next(e) == lab;
	}
	return 0;
}


static exp
is_jumper(exp e)
{
	if (e->tag == test_tag || e->tag == goto_tag ||
	    e->tag == testbit_tag || e->tag == res_tag) {
		return e;
	}
	return NULL;
}


static exp
down(exp e)
{
	if (e->tag == seq_tag) {
		return down(child(child(e)));
	}
	if (e->tag == cond_tag) {
		return down(child(e));
	}
	return e;
}


/* next_jump delivers a goto, res, test or testbit exp if this
   is certain to be the next thing obeyed after e. NULL
   otherwise.
*/
static exp
next_jump(exp e)
{
	if (~optim & OPTIM_JUMPS) {
		return NULL;
	}

	do {
		while (e->last) {
			e = next(e);
			if (e == NULL || e->tag >= goto_tag) {
				return NULL;
			}
		}
		e = next(e);
	} while (e->tag == labst_tag && (e = father(e), e->tag !=rep_tag));

	if (is_jumper(e)) {
		return e;
	}
	if (e->tag == seq_tag || e->tag == cond_tag) {
		return is_jumper(down(e));
	}
	if (e->tag == top_tag) {
		return next_jump(e);
	}
	return NULL;
}


/* next_jump delivers a goto, res, test or testbit exp if this
   is certain to be the next thing obeyed after e and there is no
   other route to the goto (etc.). NULL otherwise.
*/
exp
short_next_jump(exp e)
{
	if (~optim & OPTIM_JUMPS) {
		return NULL;
	}

	while (e->last) {
		e = next(e);
		if (e == NULL || e->tag >= cond_tag) {
			return NULL;
		}
	}
	e = next(e);

	if (is_jumper(e)) {
		return e;
	}
	if (e->tag == seq_tag || e->tag == cond_tag) {
		return is_jumper(down(e));
	}
	if (e->tag == top_tag) {
		return short_next_jump(e);
	}
	return NULL;
}


static exp
jump_dest(exp lab)
{
	return next_jump(child(lab));
}


exp
final_dest(exp lab)
{
	exp final = lab;
	exp temp, ll;
	while (final->tag == labst_tag) {
		temp = jump_dest(final);
		if (temp != NULL && temp->tag == goto_tag &&
		    pt(temp) != final) {
			ll = lab;
			while (ll != final) {
				if (pt(temp) == ll) {
					/* pathological loop */
					return final;
				}
				ll = pt(jump_dest(ll));
			}
			final = pt(temp);
		} else {
			break;
		}
	}
	return final;
}


/* delivers 1 iff when a jumps, b also jumps
   a and b will be test or testbit */
static int
subsumes(exp a, exp b)
{
	if (a->tag == b->tag && test_number(a) == test_number(b) &&
	    eq_exp(child(a), child(b)) && eq_exp(next(child(a)), next(child(b)))) {
		return 1;
	}
	return 0;
}


exp
final_dest_test(exp lab, exp e)
{
	exp final = lab;
	exp temp, ll;
	while (final->tag == labst_tag) {
		temp = jump_dest(final);
		if (temp == NULL || final == pt(temp)) {
			return final;
		}
		if (temp->tag == goto_tag ||
		    (temp->tag == e->tag && subsumes(e, temp))) {
			ll = lab;
			while (ll != final) {
				if (pt(temp) == ll) {
					/* pathological loop */
					return final;
				}
				ll = pt(jump_dest(ll));
			}
			final = pt(temp);
		} else {
			break;
		}
	}
	return final;
}
