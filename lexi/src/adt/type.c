/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdbool.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <exds/common.h>
#include <exds/dstring.h>

#include <adt/type.h>

struct type *
type_create(bool predefined)
{
	struct type *t;

	t = xmalloc(sizeof *t);

	nstring_init(&t->mapping);

	t->mapped     = false;
	t->predefined = predefined;

	return t;
}

void
type_map(struct type *t, NStringT *mapping)
{
	nstring_assign(&t->mapping, mapping);
	t->mapped = true;
}

