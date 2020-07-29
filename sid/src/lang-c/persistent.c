/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * persistent.h - Persistent variables
 */

#include <shared/bool.h>
#include <shared/check.h>

#include "persistent.h"

PersistentT *
persistent_create(NStringT *name, NStringT *ctype)
{
	PersistentT *persistent = ALLOCATE(PersistentT);

	nstring_assign(&persistent->name, name);
	nstring_assign(&persistent->ctype, ctype);
	persistent -> next = NULL;

	return persistent;
}

void
persistent_list_init(PersistentListT *persistent_list)
{
	persistent_list->head = NULL;
	persistent_list->tail = &persistent_list->head;
}

void
persistent_list_append(PersistentListT *persistent_list, PersistentT *persistent)
{
	*persistent_list->tail = persistent;
	persistent_list->tail = &persistent->next;
}

PersistentT *
persistent_list_find(PersistentListT *list, NStringT *name)
{
	PersistentT *p;

	for (p = list->head; p; p = p->next) {
		if (nstring_equal(&p->name, name)) {
			return p;
		}
	}

	return NULL;
}

