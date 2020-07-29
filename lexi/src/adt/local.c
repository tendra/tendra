/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>
#include <string.h>

#include <shared/string.h>
#include <shared/xalloc.h>

#include <adt/local.h>

void
local_add(struct local **locals, char *name, struct entry *et)
{
	struct local *new;

	new = xmalloc(sizeof *new);
	new->et   = et;
	new->name = name;

	new->next = *locals;
	*locals = new;
}

struct entry *
local_find(struct local *locals, char *name)
{
	struct local *p;

	for (p = locals; p != NULL; p = p->next) {
		if (streq(p->name, name)) {
			return p->et;
		}
	}

	return NULL;
}

