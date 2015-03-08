/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef READER_SPECIAL_H
#define READER_SPECIAL_H

#include <construct/installtypes.h>

struct special_fn {
	const char *name;
	int mask;
	bool (*f)(exp a1, exp a2, shape s, exp *e);
};

bool
special_fn(exp a1, exp a2, shape s, exp *e);

extern struct special_fn special_fns[];
extern size_t special_fns_count;

#endif

