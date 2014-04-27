/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <adt/action.h>
#include <adt/entry.h>

struct entry *
table_get_entry(struct entry **table, char *key)
{
	struct entry *e;

	assert(table != NULL);

	for (e = *table; e != NULL; e = e->next) {
		if (0 == strcmp(e->key, key)) {
			return e;
		}
	}

	return NULL;
}

struct entry *
table_get_type(struct entry **table, char *key)
{
	struct entry *et;

	assert(table != NULL);

	et = table_get_entry(table, key);

	if (et->kind != ENTRY_TYPE) {
		return NULL;
	}

	return et;
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

static struct entry *
entry_create(char *name, enum entry_kind kind)
{
	struct entry *e;

	e = xmalloc(sizeof *e);
	e->kind = kind;
	e->key  = name;
	e->next = NULL;

	return e;
}

struct entry *
table_add_type(struct entry **table, char *name)
{
	struct entry *et;

	et = entry_create(name, ENTRY_TYPE);
	table_add_entry(table, et);

	return et;
}

struct entry *
table_add_action(struct entry **table, char *name,
	struct param *in, struct param *out)
{
	struct entry *ea;

	ea = entry_create(name, ENTRY_ACTION);
	table_add_entry(table, ea);

	ea->u.act = action_create();
	ea->u.act->in  = in;
	ea->u.act->out = out;

	return ea;
}

struct entry *
table_add_local_name(struct entry **table, char *name)
{
	struct entry *en;

	en = entry_create(name, ENTRY_LOCAL);
	table_add_entry(table, en);

	return en;
}

