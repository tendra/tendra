/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * table.c - Identifier table ADT.
 *
 * This file implements the identifier table routines used by SID.
 */

#include <limits.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include "table.h"
#include "action.h"
#include "basic.h"
#include "../grammar.h"
#include "name.h"
#include "rule.h"
#include "type.h"

static unsigned
table_next_generated_key(void)
{
	static unsigned sequence = 0;

	if (sequence == UINT_MAX) {
		error(ERR_FATAL, "too many automatically generated identifiers required");
		UNREACHED;
	}

	return sequence++;
}

static EntryT *
table_add_entry(TableT *table, NStringT *key, EntryTypeT type, bool *found_ref)
{
	unsigned hash   = nstring_hash_value(key) % TABLE_SIZE;
	EntryT **entryp = &table->contents[hash];
	EntryT *entry;
	unsigned number;

	*found_ref = false;
	while ((entry = *entryp) != NULL) {
		KeyT *ent_key = entry_key(entry);

		if (key_is_string(ent_key) && nstring_equal(key_get_string(ent_key), key)) {
			if (type == ET_NAME) {
				nstring_destroy(key);
				return entry;
			} else if (entry_type(entry) == ET_NAME) {
				nstring_destroy(key);
				entry_change_type(entry, type);
				return entry;
			} else if (entry_type(entry) == type
				&& (type == ET_ACTION || type == ET_RULE)) {
				*found_ref = true;
				nstring_destroy(key);
				return entry;
			} else {
				return NULL;
			}
		}

		entryp = entry_next_ref(entry);
	}

	number  = table_next_generated_key();
	entry   = entry_create_from_string(key, number, type);
	*entryp = entry;

	return entry;
}


/*
 * Externally visible functions
 */

void
table_init(TableT *table)
{
	unsigned i;

	for (i = 0; i < TABLE_SIZE; i++) {
		table->contents[i] = NULL;
	}
}

EntryT *
table_add_type(TableT *table, NStringT *key, bool ignored)
{
	bool  found;
	EntryT *entry = table_add_entry(table, key, ET_TYPE, &found);

	if (entry) {
		entry_set_type(entry, type_create(ignored));
	}

	return entry;
}

EntryT *
table_add_basic(TableT *table, NStringT *key, GrammarT *grammar, bool ignored)
{
	bool   found;
	EntryT *entry = table_add_entry(table, key, ET_BASIC, &found);

	if (entry) {
		entry_set_basic(entry, basic_create(grammar, ignored));
	}

	return entry;
}

EntryT *
table_add_action(TableT *table, NStringT *key, bool ignored)
{
	bool   found;
	EntryT *entry = table_add_entry(table, key, ET_ACTION, &found);

	if (entry != NULL && !found) {
		entry_set_action(entry, action_create(ignored));
	}

	return entry;
}

EntryT *
table_add_rule(TableT *table, NStringT *key)
{
	bool   found;
	EntryT *entry = table_add_entry(table, key, ET_RULE, &found);

	if (entry != NULL && !found) {
		entry_set_rule(entry, rule_create(entry));
	}

	return entry;
}

EntryT *
table_add_generated_rule(TableT *table, bool traced)
{
	unsigned sequence = table_next_generated_key();
	unsigned hash     = sequence % TABLE_SIZE;
	EntryT **entryp   = &table->contents[hash];
	EntryT *entry;

	entry = entry_create_from_number(sequence, ET_RULE, traced, *entryp);
	entry_set_rule(entry, rule_create(entry));
	*entryp = entry;

	return entry;
}

EntryT *
table_add_name(TableT *table, NStringT *key)
{
	bool found;

	return table_add_entry(table, key, ET_NAME, &found);
}

EntryT *
table_add_generated_name(TableT *table)
{
	unsigned sequence = table_next_generated_key();
	unsigned hash     = sequence % TABLE_SIZE;
	EntryT **entryp   = &table->contents[hash];
	EntryT *entry;

	entry = entry_create_from_number(sequence, ET_NAME, false, *entryp);
	*entryp = entry;

	return entry;
}

EntryT *
table_add_rename(TableT *table)
{
	unsigned sequence = table_next_generated_key();
	unsigned hash     = sequence % TABLE_SIZE;
	EntryT **entryp   = &table->contents[hash];
	EntryT *entry;

	entry = entry_create_from_number(sequence, ET_RENAME, true, *entryp);
	*entryp = entry;

	return entry;
}

EntryT *
table_add_non_local(TableT *table, NStringT *key, EntryT *type)
{
	bool   found;
	EntryT *entry;

	entry = table_add_entry(table, key, ET_NON_LOCAL, &found);
	if (entry) {
		entry_set_non_local(entry, type);
	}

	return entry;
}

EntryT *
table_get_entry(TableT *table, NStringT *key)
{
	unsigned  hash  = nstring_hash_value(key) % TABLE_SIZE;
	EntryT   *entry;

	for(entry = table->contents[hash]; entry; entry = entry->next) {
		KeyT *ent_key = entry_key(entry);

		if (key_is_string(ent_key) &&
			nstring_equal(key_get_string(ent_key), key)) {
			return entry;
		}
	}

	return NULL;
}

EntryT *
table_get_type(TableT *table, NStringT *key)
{
	EntryT *entry;

	entry = table_get_entry(table, key);
	if (entry && entry_is_type(entry)) {
		return entry;
	} else {
		return NULL;
	}
}

EntryT *
table_get_basic(TableT *table, NStringT *key)
{
	EntryT *entry;

	entry = table_get_entry(table, key);
	if (entry && entry_is_basic(entry)) {
		return entry;
	} else {
		return NULL;
	}
}

EntryT *
table_get_basic_by_number(TableT *table, unsigned number)
{
	unsigned i;

	for (i = 0; i < TABLE_SIZE; i++) {
		EntryT *entry;

		for (entry = table->contents[i]; entry; entry = entry_next(entry)) {
			BasicT *basic;

			if (!entry_is_basic(entry)) {
				continue;
			}

			basic = entry_get_basic(entry);
			if (basic_terminal(basic) == number) {
				return entry;
			}
		}
	}

	return NULL;
}

EntryT *
table_get_action(TableT *table, NStringT *key)
{
	EntryT *entry;

	entry = table_get_entry(table, key);
	if (entry && entry_is_action(entry)) {
		return entry;
	} else {
		return NULL;
	}
}

EntryT *
table_get_rule(TableT *table, NStringT *key)
{
	EntryT *entry;

	entry = table_get_entry(table, key);
	if (entry && entry_is_rule(entry)) {
		return entry;
	} else {
		return NULL;
	}
}

void
table_iter(TableT *table, void (*proc)(EntryT *, void *), void *closure)
{
	unsigned i;

	for (i = 0; i < TABLE_SIZE; i++) {
		EntryT *entry;

		for (entry = table->contents[i]; entry; entry = entry_next(entry)) {
			proc(entry, closure);
		}
	}
}

void
table_untrace(TableT *table)
{
	unsigned i;

	for (i = 0; i < TABLE_SIZE; i++) {
		EntryT *entry;

		for (entry = table->contents[i]; entry; entry = entry_next(entry)) {
			entry_not_traced(entry);
		}
	}
}

void
table_unlink_untraced_rules(TableT * table)
{
	unsigned i;

	for (i = 0; i < TABLE_SIZE; i++) {
		EntryT *entry;

		for (entry = table->contents[i]; entry; entry = entry_next(entry)) {
			if (entry_is_rule(entry) && !entry_is_traced(entry)) {
				rule_deallocate(entry_get_rule(entry));
				entry_change_type(entry, ET_NAME);
			}
		}
	}
}
