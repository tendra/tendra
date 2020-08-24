/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/externs.h>
#include <reader/basicread.h>
#include <reader/table_fns.h>

#include <construct/exp.h>
#include <construct/installglob.h>
#include <construct/installtypes.h>
#include <construct/dec.h>

#include <special/special_fn.h>

#include <main/flags.h>

static bool
special_setjmp(exp a1, exp a2, shape s, exp *e)
{
	UNUSED(a1);
	UNUSED(a2);
	UNUSED(s);
	UNUSED(e);

	has_setjmp = true;

	return false;
}

static bool
special_alloca(exp a1, exp a2, shape s, exp *e)
{
	exp r;

	r = getexp(s, NULL, 0, a2, NULL, 0, 0, alloca_tag);
	setfather(r, child(r));
	has_alloca = true;
	kill_exp(a1, a1);

	*e = r;

	return true;
}

const struct special_fn special_fns[] = {
	{ "setjmp",           BUILTIN_LONGJMP, special_setjmp },
	{ "alloca",           BUILTIN_ALLOCA,  special_alloca },
	{ "__builtin_alloca", BUILTIN_ALLOCA,  special_alloca }
};

size_t special_fns_count = sizeof special_fns / sizeof * special_fns;

