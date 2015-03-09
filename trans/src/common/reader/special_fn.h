/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef READER_SPECIAL_FN_H
#define READER_SPECIAL_FN_H

#include <construct/installtypes.h>

struct special_fn {
	const char *name;
	int mask;
	bool (*f)(exp a1, exp a2, shape s, exp *e);
};

/*
 * a1 is the function, a2 is the arguments, s is the shape of the result.
 *
 * Returns true if a special case has been recognised,
 * in which case *e will be populated with the transformed exp.
 */
bool
special_fn(exp a1, exp a2, shape s, exp *e);

extern const struct special_fn special_fns[];
extern size_t special_fns_count;

#endif

