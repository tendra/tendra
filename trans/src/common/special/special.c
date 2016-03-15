/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/string.h>

#include <reader/exp.h>
#include <reader/token.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/machine.h>

#include <special/special_call.h>
#include <special/special_fn.h>
#include <special/special_tok.h>

#include <main/flags.h>

bool
special_call(const struct special_call a[], size_t count,
	dec *dp)
{
	size_t i;

	for (i = 0; i < count; i++) {
		if (a[i].mask && (builtin & ~a[i].mask)) {
			continue;
		}

		if (streq(a[i].name, dp->name)) {
			return a[i].f(dp);
		}
	}

	return false;
}


bool
special_fn(const struct special_fn a[], size_t count,
	exp a1, exp a2, shape s, exp *e)
{
	dec *dp;
	char *name;
	size_t i;

	dp = brog(son(a1));
	name = dp->name;

	if (name == NULL) {
		return false;
	}

	name += strlen(name_prefix);

	/*
	 * At present the detection of special cases is done on the identifiers,
	 * but it really ought to be on special tokens, as for diagnostics
	 */

	for (i = 0; i < count; i++) {
		if (a[i].mask && (builtin & ~a[i].mask)) {
			continue;
		}

		if (streq(a[i].name, name)) {
			return a[i].f(a1, a2, s, e);
		}
	}

	return false;
}

bool
special_token(const struct special_tok a[], size_t count,
	tokval *tkv, token t, bitstream pars, int sortcode)
{
	size_t i;

	UNUSED(sortcode);

	if (t->tok_name == NULL) {
		return false;
	}

	for (i = 0; i < count; i++) {
		if (a[i].mask && (builtin & ~a[i].mask)) {
			continue;
		}

		if (streq(a[i].name, t->tok_name)) {
			return a[i].f(tkv, t, pars);
		}
	}

	return false;
}

