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

NStringT *
entry_key(struct entry *e)
{
	return &e->key;
}

int
entry_is_type(struct entry *e)
{
	return e->entry_kind == ENTRY_TYPE;
}

int
entry_is_action(struct entry *e)
{
	return e->entry_kind == ENTRY_ACTION;
}

int
entry_is_localname(struct entry *e)
{
	return e->entry_kind == ENTRY_LOCAL;
}

static void
entry_set_kind_type(struct entry *e)
{
	e->entry_kind = ENTRY_TYPE;
}

static void
entry_set_kind_action(struct entry *e)
{
	e->entry_kind = ENTRY_ACTION;
}

static void
entry_set_kind_local_name(struct entry *e)
{
	e->entry_kind = ENTRY_LOCAL;
}

struct action *
entry_get_action(struct entry *ea)
{
	/* TODO: assert entry_is_action */
	return ea->u.act;
}

void
entry_set_action(struct entry *ea, struct action *act)
{
	/* TODO: assert entry_is_action */
	ea->u.act = act;
}

struct entry *
table_get_entry(struct entry **table, NStringT* key)
{
	struct entry *entry;

	assert(table != NULL);

	for (entry = *table; entry != NULL; entry = entry->next) {
		if (nstring_equal(&entry->key, key)) {
			return entry;
		}
	}

	return NULL;
}

struct entry *table_get_type(struct entry **table, NStringT *key)
{
	struct entry *entry;

	assert(table != NULL);

	entry = table_get_entry(table, key);

	if (entry_is_type(entry)) {
		return entry;
	}

	return NULL;
}

static void
table_add_entry(struct entry **table, struct entry *entry)
{
	assert(table != NULL);
	assert(entry != NULL);
	assert(entry->next == NULL);

	entry->next = *table;
	*table = entry;
}

struct entry *
entry_create(NStringT *name)
{
	struct entry *e;

	e = xmalloc(sizeof *e);

	nstring_assign(entry_key(e), name);
	e->next = NULL;

	return e;
}

struct entry *
table_add_type(struct entry **table, NStringT *type_name)
{
	struct entry *et;

	et = entry_create(type_name);

	entry_set_kind_type(et);
	table_add_entry(table, et);

	return et;
}

struct entry *
table_add_action(struct entry **table, NStringT *name,
	struct param *in, struct param *out)
{
	struct entry *ea;

	ea = entry_create(name);

	entry_set_kind_action(ea);
	table_add_entry(table, ea);

	entry_set_action(ea, action_create());
	action_set_inputs (entry_get_action(ea),  in);
	action_set_outputs(entry_get_action(ea), out);

	return ea;
}

struct entry *
table_add_local_name(struct entry **table, NStringT *name)
{
	struct entry *en;

	en = entry_create(name);

	entry_set_kind_local_name(en);
	table_add_entry(table, en);

	return en;
}

