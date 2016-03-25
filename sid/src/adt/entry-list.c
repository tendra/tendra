/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * entry-list.c - Identifier table entry list ADT.
 *
 * This file implements the SID table entry list routines.
 */

#include <shared/bool.h>
#include <shared/check.h>

#include "entry-list.h"
#include "action.h"
#include "basic.h"
#include "name.h"
#include "rule.h"
#include "type.h"

typedef struct EntrySortListT {
	EntryListEntryT *head;
	EntryListEntryT **tail;
} EntrySortListT;

static EntryListEntryT *
entry_list_find(EntryListT *list, EntryT *entry)
{
	EntryListEntryT *link;

	for (link = list->head; link; link = link->next) {
		if (link->entry == entry) {
			return link;
		}
	}

	return NULL;
}

/*
 * Externally visible functions
 */

void
entry_list_init(EntryListT *list)
{
	list->head = NULL;
	list->tail = &list->head;
}

void
entry_list_copy(EntryListT *to, EntryListT *from)
{
	EntryListEntryT *ptr;

	to->head = NULL;
	to->tail = &to->head;
	for (ptr = from->head; ptr; ptr = ptr->next) {
		entry_list_add(to, ptr->entry);
	}
}

void
entry_list_add(EntryListT *list, EntryT *entry)
{
	EntryListEntryT *link = ALLOCATE(EntryListEntryT);

	link->next  = NULL;
	link->entry = entry;
	*list->tail = link;
	list->tail  = &link->next;
}

void
entry_list_add_if_missing(EntryListT *list, EntryT *entry)
{
	if (entry_list_find(list, entry) == NULL) {
		entry_list_add(list, entry);
	}
}

bool
entry_list_contains(EntryListT *list, EntryT *entry)
{
	return entry_list_find(list, entry) != NULL;
}

bool
entry_list_includes(EntryListT *list1, EntryListT *list2)
{
	EntryListEntryT *ptr;

	for (ptr = list2->head; ptr; ptr = ptr->next) {
		if (entry_list_find(list1, ptr->entry) == NULL) {
			return false;
		}
	}

	return true;
}

void
entry_list_intersection(EntryListT *to, EntryListT *list1, EntryListT *list2)
{
	EntryListEntryT *ptr;

	entry_list_init(to);
	for (ptr = list1->head; ptr; ptr = ptr->next) {
		if (entry_list_find(list2, ptr->entry) != NULL) {
			entry_list_add_if_missing(to, ptr->entry);
		}
	}
}

void
entry_list_unlink_used(EntryListT *to, EntryListT *from)
{
	EntryListEntryT *ptr;

	to->tail = &to->head;
	while ((ptr = *to->tail) != NULL) {
		if (entry_list_find(from, ptr->entry) != NULL) {
			*to->tail = ptr->next;
			DEALLOCATE(ptr);
		} else {
			to->tail = &ptr->next;
		}
	}
}

void
entry_list_append(EntryListT *to, EntryListT *from)
{
	EntryListEntryT *ptr;

	for (ptr = from->head; ptr; ptr = ptr->next) {
		entry_list_add_if_missing(to, ptr->entry);
	}
}

bool
entry_list_is_empty(EntryListT *list)
{
	return list->head == NULL;
}

void
entry_list_save_state(EntryListT *list, SaveListT *state)
{
	state->last_ref = list->tail;
}

void
entry_list_restore_state(EntryListT *list, SaveListT *state)
{
	EntryListEntryT *ptr = *state->last_ref;

	*state->last_ref = NULL;
	list->tail       = state->last_ref;
	while (ptr) {
		EntryListEntryT *tmp = ptr;

		ptr = ptr->next;
		DEALLOCATE(tmp);
	}
}

void
entry_list_iter(EntryListT *list, void (*proc)(EntryT *, void *), void *closure)
{
	EntryListEntryT *ptr;

	for (ptr = list->head; ptr; ptr = ptr->next) {
		proc(ptr->entry, closure);
	}
}

void
entry_list_iter_table(EntryListT *list, bool full,
	void (*proc)(EntryT *, void *), void *closure)
{
	EntryListEntryT *ptr;

	for (ptr = list->head; ptr; ptr = ptr->next) {
		entry_iter(ptr->entry, full, proc, closure);
	}
}

void
entry_list_destroy(EntryListT *list)
{
	EntryListEntryT *ptr = list->head;

	while (ptr) {
		EntryListEntryT *tmp = ptr;

		ptr = ptr->next;
		DEALLOCATE(tmp);
	}
}

void
write_entry_list(OStreamT *ostream, EntryListT *list)
{
	EntryListEntryT *ptr = list->head;
	char            *sep = "";

	/* TODO for() */
	while (ptr) {
		write_cstring(ostream, sep);
		write_char(ostream, '\'');
		write_key(ostream, entry_key(ptr->entry));
		write_char(ostream, '\'');
		if ((ptr = ptr->next) && (ptr->next)) {
			sep = " & ";
		} else {
			sep = ", ";
		}
	}
}
