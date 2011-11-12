/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include "config.h"

#include "installglob.h"
#include "exp.h"
#include "expmacs.h"
#include "tags.h"
#include "check.h"
#include "flags.h"
#include "check_id.h"
#include "const.h"
#include "foralls.h"
#include "shapemacs.h"
#include "glopt.h"
#include "inline.h"
#include "global_opt.h"
#include "inl_norm.h"
#include "unroll.h"


/* PROCEDURES */


/***********************************************************************
  checkext examines the external definition e to see if it can be
  improved. It returns 1 if it makes a change, 0 otherwise.
 ***********************************************************************/

void
rec_inl(exp p)
{
	if (pt(p) != nilexp) {
		rec_inl(pt(p));
	}

	inline_exp(father(p));
	return;
}


void
checkext(exp e)
{
	exp def = son(e);

	/* if it is not used or there is no definition here, do nothing */
	if (no(e) == 0 || def == nilexp) {
		return;
	}

	if ((!PIC_code || brog(e)->dec_u.dec_val.dec_var == 0) && !isvar(e) &&
	    (name(def) == val_tag || name(def) == real_tag ||
	     name(def) == null_tag)) {
		while (pt(e) != nilexp) {
			/* substitute constants in */
			exp q = pt(e);
			if (bro(q) != nilexp) {
				/* can be nilexp for diags */
				exp d = copy(def);
				replace(q, d, nilexp);
				kill_exp(q, q);
			} else {
				pt(e) = pt(q);
			}
		}
		return;
	}

	return;
}


void
opt_all_exps(void)
{
	dec *my_def;

#if 0
	/* take constant expression out of loops */
	if (do_loopconsts)
		repeat_consts();
#endif

	if (do_unroll) {
		unroller();
	}

	my_def = top_def;
	while (my_def != (dec *)0) {
		exp crt_exp = my_def->dec_u.dec_val.dec_exp;
		checkext(crt_exp);
		glopt(my_def);
		my_def = my_def -> def_next;
	}

	normalised_inlining();

#if 1
	/* take constant expression out of loops */
	if (do_loopconsts) {
		repeat_consts();
	}
#endif

	/* replace indexing on loop variable by incremented pointer access */
	if (do_foralls) {
		forall_opt();
	}

	return;
}
