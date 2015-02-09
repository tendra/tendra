/* $Id$ */

/*
 * Copyright 2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <reader/exp.h>

#include <reader/externs.h>
#include <reader/table_fns.h>
#include <reader/basicread.h>

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
	dec *dp = brog (son (a1));
	char *id = dp->dec_u.dec_val.dec_id;

	if (id == NULL) {
		return 0;
	}

	/*
	 * at present the detection of special cases is done on the identifiers,
	 * but it really ought to be on special tokens, as for diagnostics
	 */

	if (builtin & BUILTIN_LONGJMP) {
		if (!strcmp (id, "setjmp")) {
			has_setjmp = 1;
		}

		if (!strcmp (id, "longjmp")) {
			has_setjmp = 1;
		}
	}

	if (builtin & BUILTIN_ALLOCA) {
		if ((!strcmp (id, "alloca") || !strcmp (id, "__builtin_alloca"))) {
			exp r = getexp (s, NULL, 0, a2, NULL, 0, 0, alloca_tag);
			setfather(r, son(r));
			has_alloca = 1;
			*e = r;
			kill_exp (a1, a1);
			return 1;
		};
	}

	return 0;
}

