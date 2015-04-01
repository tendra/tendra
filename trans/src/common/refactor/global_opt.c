/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/error.h>
#include <shared/string.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/externs.h>
#include <reader/table_fns.h>
#include <reader/basicread.h>

#include <construct/installglob.h>
#include <construct/exp.h>

#include <special/special_call.h>

#include <main/flags.h>

#include <refactor/const.h>
#include <refactor/optimise.h>
#include <refactor/refactor_ext.h>

void
opt_all_exps(void)
{
	dec *d;

#if 0
	/* take constant expression out of loops */
	if (optim & OPTIM_LOOPCONSTS)
		repeat_consts();
#endif

	if (optim & OPTIM_UNROLL) {
		unroller();
	}

	for (d = top_def; d != NULL; d = d->def_next) {
		exp crt_exp = d->dec_exp;
		refactor_ext(crt_exp);
		(void) special_call(special_calls, special_calls_count, d);
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
}

