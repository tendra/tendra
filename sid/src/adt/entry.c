/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * entry.c - Identifier table entry ADT.
 *
 * This file implements the identifier table routines used by SID.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>

#include "entry.h"
#include "action.h"
#include "basic.h"
#include "name.h"
#include "rule.h"
#include "type.h"

static void
entry_traced(EntryT * entry)
{
    entry->traced = true;
}

/*
 * Externally visible functions
 */

EntryT *
entry_create_from_string(NStringT *key, unsigned number, EntryTypeT type)
{
	EntryT *entry = ALLOCATE(EntryT);

	entry->next   = NULL;
	key_init_from_string(entry_key(entry), key, number);
	entry->mapped = false;
	nstring_init(&entry->mapping);
	entry->type   = type;
	entry->name   = name_create();
	entry->traced = false;

	return entry;
}

EntryT *
entry_create_from_number(unsigned key, EntryTypeT type, bool traced, EntryT *next)
{
	EntryT *entry = ALLOCATE(EntryT);

	entry->next   = next;
	key_init_from_number(entry_key(entry), key);
	entry->mapped = false;
	nstring_init(&entry->mapping);
	entry->type   = type;
	entry->name   = name_create();
	entry->traced = traced;

	return entry;
}

void
entry_set_basic(EntryT *entry, BasicT *basic)
{
	assert(entry_is_basic(entry));
	entry->u.basic = basic;
}

void
entry_set_rule(EntryT *entry, RuleT *rule)
{
	assert(entry_is_rule(entry));
	entry->u.rule = rule;
}

void
entry_set_action(EntryT *entry, ActionT *action)
{
	assert(entry_is_action(entry));
	entry->u.action = action;
}

void
entry_set_type(EntryT *entry, TypeT *type)
{
	assert(entry_is_type(entry));
	entry->u.type = type;
}

void
entry_set_non_local(EntryT *entry, EntryT *type)
{
	assert(entry_is_non_local(entry));
	entry->u.non_local = type;
}

EntryT *
entry_next(EntryT *entry)
{
	return entry->next;
}

EntryT **
entry_next_ref(EntryT *entry)
{
	return &entry->next;
}

KeyT *
entry_key(EntryT *entry)
{
	return &entry->key;
}

EntryTypeT
entry_type(EntryT *entry)
{
	return entry->type;
}

void
entry_change_type(EntryT *entry, EntryTypeT type)
{
	entry->type = type;
}

bool
entry_is_basic(EntryT *entry)
{
	return entry->type == ET_BASIC;
}

bool
entry_is_action(EntryT *entry)
{
	return entry->type == ET_ACTION;
}

bool
entry_is_rule(EntryT *entry)
{
	return entry->type == ET_RULE;
}

bool
entry_is_type(EntryT *entry)
{
	return entry->type == ET_TYPE;
}

bool
entry_is_non_local(EntryT *entry)
{
	return entry->type == ET_NON_LOCAL;
}

BasicT *
entry_get_basic(EntryT *entry)
{
	assert(entry_is_basic(entry));
	return entry->u.basic;
}

ActionT *
entry_get_action(EntryT *entry)
{
	assert(entry_is_action(entry));
	return entry->u.action;
}

RuleT *
entry_get_rule(EntryT *entry)
{
	assert(entry_is_rule(entry));
	return entry->u.rule;
}

NameT *
entry_get_name(EntryT *entry)
{
	return entry->name;
}

TypeT *
entry_get_type(EntryT *entry)
{
	assert(entry_is_type(entry));
	return entry->u.type;
}

EntryT *
entry_get_non_local(EntryT *entry)
{
	assert(entry_is_non_local(entry));
	return entry->u.non_local;
}

void
entry_set_mapping(EntryT *entry, NStringT *mapping)
{
	if (entry->mapped) {
		nstring_destroy(&entry->mapping);
	}

	nstring_assign(&entry->mapping, mapping);
	entry->mapped = true;
}

NStringT *
entry_get_mapping(EntryT *entry)
{
	if (entry->mapped) {
		return &entry->mapping;
	}

	return NULL;
}

void
entry_iter(EntryT *entry, bool full, void (*proc)(EntryT *, void *), void *closure)
{
	if (entry_is_traced(entry)) {
		return;
	}

	entry_traced(entry);
	if (proc) {
		proc(entry, closure);
	}

	switch (entry_type(entry))EXHAUSTIVE {
	case ET_RULE: {
			RuleT *rule = entry_get_rule(entry);

			rule_iter_for_table(rule, full, proc, closure);
		}
		break;

	case ET_ACTION: {
			ActionT *action = entry_get_action(entry);

			action_iter_for_table(action, full, proc, closure);
		}
		break;

	case ET_BASIC: {
			BasicT *basic = entry_get_basic(entry);

			basic_iter_for_table(basic, full, proc, closure);
		}
		break;

	case ET_NON_LOCAL:
		if (full) {
			entry_iter(entry_get_non_local(entry), true, proc, closure);
		}
		break;

	case ET_NAME:
	case ET_TYPE:
	case ET_RENAME:
		/* NOTHING */
		break;

	case ET_PREDICATE:
		UNREACHED;
	}
}

void
entry_not_traced(EntryT *entry)
{
	entry->traced = false;
}

bool
entry_is_traced(EntryT *entry)
{
	return entry->traced;
}
