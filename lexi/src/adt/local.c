/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#include <shared/xalloc.h>

#include <exds/common.h>
#include <exds/dstring.h>

#include <adt/local.h>

void
local_add(struct local **locals, NStringT *name, struct entry *et)
{
	struct local *new;

	new = xmalloc(sizeof *new);
	new->et = et;

	nstring_assign(&new->name, name);

	new->next = *locals;
	*locals = new;
}

struct entry *
local_find(struct local *locals, NStringT *name)
{
	struct local *p;

	for (p = locals; p != NULL; p = p->next) {
		if (CMP_EQ == nstring_compare(&p->name, name)) {
			return p->et;
		}
	}

	return NULL;
}

