/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * item.c - Item ADT.
 *
 * This file implements the item manipulation routines.  These are specified
 * in the file "rule.h".
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>

#include "rule.h"
#include "action.h"
#include "basic.h"
#include "name.h"
#include "type.h"

ItemT *
item_create(EntryT *entry)
{
	ItemT *item = ALLOCATE(ItemT);

	item->next         = NULL;
	types_init(item_param(item));
	types_init(item_result(item));
	item->type         = entry_type(entry);
	item->entry        = entry;
	item->inlinable    = false;
	item->tail_call    = false;

	return item;
}

ItemT *
item_duplicate(ItemT *item)
{
	ItemT *new_item = ALLOCATE(ItemT);

	new_item->next         = NULL;
	types_copy(item_param(new_item), item_param(item));
	types_copy(item_result(new_item), item_result(item));
	new_item->type         = item->type;
	new_item->entry        = item->entry;
	new_item->inlinable    = item->inlinable;
	new_item->tail_call    = item->tail_call;

	return new_item;
}

ItemT *
item_duplicate_and_translate(ItemT *item, TypeTransT *translator, TableT *table)
{
	ItemT *new_item = ALLOCATE(ItemT);

	new_item->next         = NULL;
	types_copy_and_translate(item_param(new_item), item_param(item), translator, table);
	types_copy_and_translate(item_result(new_item), item_result(item), translator, table);
	new_item->type         = item->type;
	new_item->entry        = item->entry;
	new_item->inlinable    = item->inlinable;
	new_item->tail_call    = item->tail_call;

	return new_item;
}

void
item_translate_list(ItemT *item, TypeBTransT *translator)
{
	for ( ; item; item = item_next(item)) {
		types_translate(item_param(item), translator);
		types_translate(item_result(item), translator);
	}
}

void
item_to_predicate(ItemT *item)
{
	assert(item_is_action(item));
	item->type = ET_PREDICATE;
}

ItemT *
item_next(ItemT *item)
{
	return item->next;
}

ItemT **
item_next_ref(ItemT * item)
{
	return &item->next;
}

void
item_set_next(ItemT *item1, ItemT *item2)
{
	item1->next = item2;
}

EntryT *
item_entry(ItemT *item)
{
	return item->entry;
}

void
item_set_entry(ItemT *item, EntryT *entry)
{
	item->entry = entry;
}

EntryTypeT
item_type(ItemT *item)
{
	return item->type;
}

bool
item_is_rule(ItemT *item)
{
	return item->type == ET_RULE;
}

bool
item_is_action(ItemT *item)
{
	return item->type == ET_ACTION;
}

bool
item_is_predicate(ItemT *item)
{
	return item->type == ET_PREDICATE;
}

bool
item_is_basic(ItemT *item)
{
	return item->type == ET_BASIC;
}

bool
item_is_rename(ItemT *item)
{
	return item->type == ET_RENAME;
}

TypeTupleT *
item_param(ItemT *item)
{
	return &item->param;
}

void
item_add_param(ItemT *item, TypeTupleT *param)
{
	types_assign(item_param(item), param);
}

TypeTupleT *
item_result(ItemT *item)
{
	return &item->result;
}

void
item_add_result(ItemT *item, TypeTupleT *result)
{
	types_assign(item_result(item), result);
}

bool
item_is_inlinable(ItemT *item)
{
	return item->inlinable;
}

void
item_inlinable(ItemT *item)
{
	item->inlinable = true;
}

bool
item_is_tail_call(ItemT *item)
{
	return item->tail_call;
}

void
item_tail_call(ItemT *item)
{
	item->tail_call = true;
}

bool
item_names_used_in_list(ItemT *item, TypeTupleT *names)
{
	for ( ; item; item = item_next(item)) {
		if (types_intersect(item_param(item), names)
			|| types_intersect(item_result(item), names)) {
			return true;
		}
	}

	return false;
}

void
item_compute_minimal_dataflow(ItemT *item, TypeTupleT *used)
{
	ItemT *next;

	if (!item) {
		return;
	}

	next = item_next(item);

	if (next) {
		item_compute_minimal_dataflow(next, used);
	}

	if (item_is_inlinable(item)) {
		RuleT *rule = entry_get_rule(item_entry(item));

		types_inplace_intersection(item_result(item), used);
		types_inplace_intersection(rule_result(rule), used);
		rule_compute_minimal_dataflow(rule, item_param(item));
	}

	types_add_new_names(used, item_param(item), NULL);
}

ItemT *
item_deallocate(ItemT *item)
{
	ItemT *next = item_next(item);

	types_destroy(item_param(item));
	types_destroy(item_result(item));
	DEALLOCATE(item);

	return next;
}

void
write_item(OStreamT *ostream, ItemT *item)
{
	EntryT *entry = item_entry(item);

	write_type_names(ostream, item_result(item), true);
	if (item_is_predicate(item)) {
		write_cstring(ostream, " ?");
	}

	write_cstring(ostream, " = ");
	switch (item_type(item)) EXHAUSTIVE {
	case ET_ACTION:
	case ET_PREDICATE:
		write_char(ostream, '<');
		write_key(ostream, entry_key(entry));
		write_cstring(ostream, "> ");
		break;

	case ET_RULE:
		if (item_is_inlinable(item)) {
			if (item_is_tail_call(item)) {
				write_char(ostream, '*');
			} else {
				write_char(ostream, '+');
			}
		}
		FALL_THROUGH;

	case ET_BASIC:
		write_key(ostream, entry_key(item_entry(item)));
		write_char(ostream, ' ');
		break;

	case ET_RENAME:
		break;

	case ET_NON_LOCAL:
	case ET_NAME:
	case ET_TYPE:
		UNREACHED;
	}

	write_type_names(ostream, item_param(item), true);
	write_char(ostream, ';');
}
