/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <adt/action.h>
#include <adt/entry.h>
#include <adt/type.h>

NStringT *
entry_key(struct EntryT *entry)
{
	return &entry->key;
}

int
entry_is_type(struct EntryT *entry)
{
	return entry->entry_kind == entry_type;
}

int
entry_is_action(struct EntryT *entry)
{
	return entry->entry_kind == entry_action;
}

int
entry_is_localname(struct EntryT *entry)
{
	return entry->entry_kind == entry_local_name;
}

static void
entry_set_kind_type(struct EntryT *entry)
{
	entry->entry_kind = entry_type;
}

static void
entry_set_kind_action(struct EntryT *entry)
{
	entry->entry_kind = entry_action;
}

static void
entry_set_kind_local_name(struct EntryT *entry)
{
	entry->entry_kind = entry_local_name;
}

struct ActionT *
entry_get_action(struct EntryT *entry)
{
	/* TODO: assert entry_is_action */
	return entry->u.action;
}

void
entry_set_type(struct EntryT *entry, struct TypeT *type)
{
	/* TODO: assert entry_is_type */
	entry->u.type = type;
}

void
entry_set_action(struct EntryT *entry, struct ActionT *action)
{
	/* TODO: assert entry_is_action */
	entry->u.action = action;
}

struct TypeT *
entry_get_type(struct EntryT *entry)
{
	/* TODO: assert entry_is_type */
	return entry->u.type;
}

struct EntryT *
table_get_entry(struct EntryT **table, NStringT* key)
{
	struct EntryT *entry;

	assert(table != NULL);

	for (entry = *table; entry != NULL; entry = entry->next) {
		if (nstring_equal(&entry->key, key)) {
			return entry;
		}
	}

	return NULL;
}

struct EntryT *table_get_type(struct EntryT **table, NStringT *key)
{
	struct EntryT *entry;

	assert(table != NULL);

	entry = table_get_entry(table, key);

	if (entry_is_type(entry)) {
		return entry;
	}

	return NULL;
}

static void
table_add_entry(struct EntryT **table, struct EntryT *entry)
{
	assert(table != NULL);
	assert(entry != NULL);
	assert(entry->next == NULL);

	entry->next = *table;
	*table = entry;
}

struct EntryT *
entry_create(NStringT *name)
{
	struct EntryT *entry;

	entry = xmalloc(sizeof *entry);

	nstring_assign(entry_key(entry), name);
	entry->next = NULL;

	return entry;
}

struct EntryT *
table_add_type(struct EntryT **table, NStringT *type_name, bool predefined)
{
	struct EntryT *entry;

	entry = entry_create(type_name);

	entry_set_kind_type(entry);
	entry_set_type(entry, type_create(predefined));
	table_add_entry(table, entry);

	return entry;
}

struct EntryT *
table_add_action(struct EntryT **table, NStringT *name, struct TypeTupleT *inputs, struct TypeTupleT *outputs)
{
	struct EntryT *entry;

	entry = entry_create(name);

	entry_set_kind_action(entry);
	table_add_entry(table, entry);

	entry_set_action(entry, action_create());
	action_set_inputs (entry_get_action(entry),  inputs);
	action_set_outputs(entry_get_action(entry), outputs);

	return entry;
}

struct EntryT *
table_add_local_name(struct EntryT **table, NStringT *name)
{
	struct EntryT *entry;

	entry = entry_create(name);

	entry_set_kind_local_name(entry);
	table_add_entry(table, entry);

	return entry;
}

