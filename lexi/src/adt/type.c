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

TypeT *
type_create(bool predefined)
{
	TypeT *type;

	type = xmalloc_nof(TypeT, 1);

	nstring_init(&type->mapping);

	type->mapped     = false;
	type->predefined = predefined;

	return type;
}

void
type_map(TypeT *t, NStringT *mapping)
{
	nstring_assign(&t->mapping, mapping);
	t->mapped = true;
}

