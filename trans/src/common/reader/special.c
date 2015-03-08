/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/bool.h>

#include <reader/exp.h>
#include <reader/special_fn.h>

#include <construct/installtypes.h>
#include <construct/machine.h>

#include <main/flags.h>

bool
special_fn(exp a1, exp a2, shape s, exp *e)
{
	dec *dp;
	char *id;
	size_t i;

	dp = brog(son(a1));
	id = dp->dec_id;

	if (id == NULL) {
		return false;
	}

	id += strlen(name_prefix);

	/*
	 * At present the detection of special cases is done on the identifiers,
	 * but it really ought to be on special tokens, as for diagnostics
	 */

	for (i = 0; i < special_fns_count; i++) {
		if (special_fns[i].mask && (builtin & ~special_fns[i].mask)) {
			continue;
		}

		if (0 == strcmp(special_fns[i].name, id)) {
			return special_fns[i].f(a1, a2, s, e);
		}
	}

	return false;
}

