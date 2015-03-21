/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>
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
#include <construct/dec.h>
#include <construct/me_fns.h>
#include <construct/machine.h>

#include <special/special_fn.h>

#include <main/flags.h>

#include "localexpmacs.h"

static bool
special_trans386(exp a1, exp a2, shape s, exp *e)
{
	exp r;

	if (a2 == NULL || !last(a2)) {
		return false;
	}

	r = me_b3(s, a1, a2, apply_tag);
	setbuiltin(r);	/* dummy proc, so ignore state of builtin */

	*e = r;

	return true;
}

static bool
special_setjmp(exp a1, exp a2, shape s, exp *e)
{
	UNUSED(a1);
	UNUSED(a2);
	UNUSED(s);
	UNUSED(e);

	has_setjmp = 1;

	return false;
}

static bool
special_longjmp(exp a1, exp a2, shape s, exp *e)
{
	exp r;

	if (last(a2) || bro(a2) == NULL) {
		return 0;
	}

	r = getexp(f_bottom, NULL, 0, a1, NULL, 0, 0, apply_tag);
	has_setjmp = 1;

	bro(a1) = a2;
	clearlast(a1);
	parked(a2) = 0;
	clearlast(a2);

	a2 = bro(a2);
	setlast(a2);
	parked(a2) = 0;
	bro(a2) = r;

	*e = r;

	return true;
}

static bool
special_alloca(exp a1, exp a2, shape s, exp *e)
{
	exp r;

	if (a2 == NULL || !last(a2)) {
		return false;
	}

	r = getexp(s, NULL, 0, a2, NULL, 0, 0, alloca_tag);
	setfather(r, son(r));
	has_alloca = 1;
	kill_exp(a1, a1);

	*e = r;

	return true;
}

static bool
special_exit(exp a1, exp a2, shape s, exp *e)
{
	if (a2 == NULL || !last(a2)) {
		return false;
	}

	*e = me_b3(f_bottom, a1, a2, apply_tag);

	return true;
}

static bool
special_abort(exp a1, exp a2, shape s, exp *e)
{
	if (a2 == NULL || !last(a2)) {
		return false;
	}

	*e = me_u3(f_bottom, a1, apply_tag);

	return true;
}

const struct special_fn special_fns[] = {
	{ "__trans386_special", 0,               special_trans386 },
	{ "setjmp",             BUILTIN_LONGJMP, special_setjmp   },
	{ "longjmp",            BUILTIN_LONGJMP, special_longjmp  },
	{ "__builtin_alloca",   BUILTIN_ALLOCA,  special_alloca   },
	{ "exit",               BUILTIN_API,     special_exit     },
	{ "abort",              BUILTIN_API,     special_abort    }
};

size_t special_fns_count = sizeof special_fns / sizeof *special_fns;

