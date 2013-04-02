/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/error.h>

#include "expmacs.h"
#include "glopt.h"

#include <construct/installglob.h>
#include <construct/exp.h>
#include <construct/tags.h>
#include <construct/flags.h>
#include <construct/shapemacs.h>

#include <refactor/const.h>
#include <refactor/optimise.h>
#include <refactor/refactor_ext.h>

/* PROCEDURES */


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
opt_all_exps(void)
{
	dec *my_def;

#if 0
	/* take constant expression out of loops */
	if (optim & OPTIM_LOOPCONSTS)
		repeat_consts();
#endif

	if (optim & OPTIM_UNROLL) {
		unroller();
	}

	my_def = top_def;
	while (my_def != (dec *)0) {
		exp crt_exp = my_def->dec_u.dec_val.dec_exp;
		refactor_ext(crt_exp);
		glopt(my_def);
		my_def = my_def -> def_next;
	}

	normalised_inlining();

#if 1
	/* take constant expression out of loops */
	if (optim & OPTIM_LOOPCONSTS) {
		repeat_consts();
	}
#endif

	/* replace indexing on loop variable by incremented pointer access */
	if (optim & OPTIM_FORALLS) {
		forall_opt();
	}

	return;
}

