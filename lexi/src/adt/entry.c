/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include "action.h"
#include "entry.h"
#include "type.h"

NStringT *
entry_key(EntryT *entry)
{
	return &entry->key;
}

int
entry_is_type(EntryT *entry)
{
	return entry->entry_kind == entry_type;
}

int
entry_is_action(EntryT *entry)
{
	return entry->entry_kind == entry_action;
}

int
entry_is_localname(EntryT *entry)
{
	return entry->entry_kind == entry_local_name;
}

static void
entry_set_kind_type(EntryT *entry)
{
	entry->entry_kind = entry_type;
}

static void
entry_set_kind_action(EntryT *entry)
{
	entry->entry_kind = entry_action;
}

static void
entry_set_kind_local_name(EntryT *entry)
{
	entry->entry_kind = entry_local_name;
}

struct ActionT *
entry_get_action(EntryT *entry)
{
	/* TODO: assert entry_is_action */
	return entry->u.action;
}

void
entry_set_type(EntryT *entry, struct TypeT *type)
{
	/* TODO: assert entry_is_type */
	entry->u.type = type;
}

void
entry_set_action(EntryT *entry, struct ActionT *action)
{
	/* TODO: assert entry_is_action */
	entry->u.action = action;
}

struct TypeT *
entry_get_type(EntryT *entry)
{
	/* TODO: assert entry_is_type */
	return entry->u.type;
}

EntryT *
table_get_entry(EntryT **table, NStringT* key)
{
	EntryT *entry;

	assert(table != NULL);

	for (entry = *table; entry != NULL; entry = entry->next) {
		if (nstring_equal(&entry->key, key)) {
			return entry;
		}
	}

	return NULL;
}

EntryT *table_get_type(EntryT **table, NStringT *key)
{
	EntryT *entry;

	assert(table != NULL);

	entry = table_get_entry(table, key);

	if (entry_is_type(entry)) {
		return entry;
	}

	return NULL;
}

static void
table_add_entry(EntryT **table, EntryT *entry)
{
	assert(table != NULL);
	assert(entry != NULL);
	assert(entry->next == NULL);

	entry->next = *table;
	*table = entry;
}

EntryT *
entry_create(NStringT *name)
{
	EntryT *entry;

	entry = xmalloc_nof(EntryT, 1);

	nstring_assign(entry_key(entry), name);
	entry->next = NULL;

	return entry;
}

EntryT *
table_add_type(EntryT **table, NStringT *type_name, bool predefined)
{
	EntryT *entry;

	entry = entry_create(type_name);

	entry_set_kind_type(entry);
	entry_set_type(entry, type_create(predefined));
	table_add_entry(table, entry);

	return entry;
}

EntryT *
table_add_action(EntryT **table, NStringT *name, struct TypeTupleT *inputs, struct TypeTupleT *outputs)
{
	EntryT *entry;

	entry = entry_create(name);

	entry_set_kind_action(entry);
	table_add_entry(table, entry);

	entry_set_action(entry, action_create());
	action_set_inputs (entry_get_action(entry),  inputs);
	action_set_outputs(entry_get_action(entry), outputs);

	return entry;
}

EntryT*
table_add_local_name(EntryT **table, NStringT *name)
{
	EntryT *entry;

	entry = entry_create(name);

	entry_set_kind_local_name(entry);
	table_add_entry(table, entry);

	return entry;
}

