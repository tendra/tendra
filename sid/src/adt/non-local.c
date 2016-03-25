/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * non-local.c - Non local name ADT.
 *
 * This file implements the non local name list manipulation routines.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>

#include "non-local.h"

void
non_local_list_init(NonLocalListT *non_locals)
{
	non_locals->head = NULL;
	non_locals->tail = &non_locals->head;
}

NonLocalEntryT *
non_local_list_add(NonLocalListT *non_locals, EntryT *name, EntryT *type)
{
	NonLocalEntryT *entry = ALLOCATE(NonLocalEntryT);

	entry->next        = NULL;
	entry->name        = name;
	entry->type        = type;
	entry->initialiser = NULL;
	*non_locals->tail  = entry;
	non_locals->tail   = &entry->next;

	return entry;
}

bool
non_local_list_is_empty(NonLocalListT *non_locals)
{
	return non_locals->head == NULL;
}

void
non_local_list_iter_for_table(NonLocalListT *non_locals,
	void (*proc)(EntryT *, void *), void *closure)
{
	NonLocalEntryT *non_local;

	for (non_local = non_locals->head; non_local; non_local = non_local->next) {
		entry_iter(non_local->type, true, proc, closure);
		if (non_local->initialiser) {
			entry_iter(non_local->initialiser, true, proc, closure);
		}
	}
}

void
non_local_list_destroy(NonLocalListT *non_locals)
{
	NonLocalEntryT *entry;
	NonLocalEntryT *next;

	for (entry = non_locals->head; entry; entry = next) {
		next = entry->next;
		DEALLOCATE(entry);
	}
}

void
write_non_locals(OStreamT *ostream, NonLocalListT *non_locals)
{
	NonLocalEntryT *non_local;

	for (non_local = non_locals->head; non_local; non_local = non_local->next) {
		assert(non_local->type);
		assert(non_local->name);

		write_tab(ostream);
		write_key(ostream, entry_key(non_local->name));
		write_cstring(ostream, ": ");
		write_key(ostream, entry_key(non_local->type));

		if (non_local->initialiser) {
			write_cstring(ostream, " = <");
			write_key(ostream, entry_key(non_local->initialiser));
			write_char(ostream, '>');
		}

		write_char(ostream, ';');
		write_newline(ostream);
	}
}

void
non_local_entry_set_initialiser(NonLocalEntryT *non_local, EntryT *init)
{
	non_local->initialiser = init;
}

EntryT *
non_local_entry_get_initialiser(NonLocalEntryT *non_local)
{
	return non_local->initialiser;
}

EntryT *
non_local_entry_get_name(NonLocalEntryT *non_local)
{
	return non_local->name;
}

EntryT *
non_local_entry_get_type(NonLocalEntryT *non_local)
{
	return non_local->type;
}
