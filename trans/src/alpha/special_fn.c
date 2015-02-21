/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Defines special_fn which recognises and replaces some special function calls.
 */

#include <string.h>

#include <shared/check.h>

#include <reader/exp.h>

#include <reader/externs.h>
#include <reader/basicread.h>
#include <reader/table_fns.h>

#include <construct/tags.h>
#include <construct/shape.h>
#include <construct/exp.h>
#include <construct/installglob.h>
#include <construct/installtypes.h>
#include <construct/special_fn.h>

#include <main/flags.h>

bool
special_fn(exp a1, exp a2, shape s, exp *e)
{
	UNUSED(a1);
	UNUSED(a2);
	UNUSED(s);
	UNUSED(e);

#if 0
	dec *dp;
	char *id;

	dp = brog(son (a1));
	id = dp->dec_id;

	if (id == NULL) {
		return 0;
	}

	/*
	 * At present the detection of special cases is done on the identifiers,
	 * but it really ought to be on special tokens, as for diagnostics.
	 */

	if (!strcmp (id, "setjmp")) {
		has_setjmp = 1;
	}

	if (a2 != NULL && last(a2) && ((do_alloca && !strcmp (id, "alloca"))
	                                || !strcmp (id, "__builtin_alloca"))) {
		exp r = getexp (s, NULL, 0, a2, NULL, 0, 0, alloca_tag);
		setfather(r, son(r));
		has_alloca = 1;
		*e = r;
		kill_exp (a1, a1);
		return 1;
	};
#endif

	return 0;
}

