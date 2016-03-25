/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * alt.c - Alternative ADT.
 *
 * This file implements the alternative manipulation routines.  They are
 * specified in the file "rule.h".
 */

#include <shared/bool.h>
#include <shared/check.h>

#include "rule.h"
#include "action.h"
#include "basic.h"
#include "name.h"
#include "type.h"

AltT *
alt_create(void)
{
	AltT *alt = ALLOCATE(AltT);

	alt->next      = NULL;
	types_init(alt_names(alt));
	bitvec_init(alt_first_set(alt));
	alt->item_head = NULL;
	alt->item_tail = &alt->item_head;

	return alt;
}

AltT *
alt_create_merge(ItemT *initial_item, ItemT *trailing_item,
	TypeTransT *translator, TableT *table)
{
	AltT *alt = alt_create();

	for ( ; initial_item; initial_item = item_next(initial_item)) {
		ItemT *new_item;

		new_item = item_duplicate_and_translate(initial_item, translator, table);
		alt_add_item(alt, new_item);
	}

	for ( ; trailing_item; trailing_item = item_next(trailing_item)) {
		ItemT *new_item;

		new_item = item_duplicate(trailing_item);
		alt_add_item(alt, new_item);
	}

	return alt;
}

AltT *
alt_duplicate(AltT *alt)
{
	AltT  *new_alt = alt_create();
	ItemT *item;

	for (item = alt_item_head(alt); item; item = item_next(item)) {
		ItemT *new_item;

		new_item = item_duplicate(item);
		alt_add_item(new_alt, new_item);
	}

	return new_alt;
}

bool
alt_less_than(AltT *alt1, AltT *alt2)
{
	ItemT      *item1 = alt_item_head(alt1);
	ItemT      *item2 = alt_item_head(alt2);
	KeyT       *key1;
	KeyT       *key2;
	TypeTupleT *type1;
	TypeTupleT *type2;

	if (item_type(item1) < item_type(item2)) {
		return true;
	} else if (item_type(item1) > item_type(item2)) {
		return false;
	}

	key1 = entry_key(item_entry(item1));
	key2 = entry_key(item_entry(item2));
	switch (key_compare(key1, key2)) EXHAUSTIVE {
	case CMP_LT:
		return true;
	case CMP_GT:
		return false;
	case CMP_EQ:
		break;
	}

	type1 = item_param(item1);
	type2 = item_param(item2);
	switch (types_compare(type1, type2)) EXHAUSTIVE {
	case CMP_LT:
		return true;
	case CMP_GT:
		return false;
	case CMP_EQ:
		break;
	}

	type1 = item_result(item1);
	type2 = item_result(item2);
	switch (types_compare(type1, type2)) EXHAUSTIVE {
	case CMP_LT:
		return true;
	case CMP_GT:
		return false;
	case CMP_EQ:
		break;
	}

	UNREACHED;
}

bool
alt_equal(AltT *alt1, AltT *alt2)
{
	ItemT *item1;
	ItemT *item2;

	if (alt1 == NULL && alt2 == NULL) {
		return true;
	} else if (alt1 == NULL || alt2 == NULL) {
		return false;
	}

	item1 = alt_item_head(alt1);
	item2 = alt_item_head(alt2);
	while (item1 && item2) {
		if (item_entry(item1) == item_entry(item2)
			&& types_equal_numbers(item_param(item1), item_param(item2))
			&& types_equal_numbers(item_result(item1), item_result(item2))) {
			item1 = item_next(item1);
			item2 = item_next(item2);
		} else {
			return false;
		}
	}

	return item1 == item2;
}

AltT *
alt_next(AltT *alt)
{
	return alt->next;
}

AltT **
alt_next_ref(AltT *alt)
{
	return &alt->next;
}

void
alt_set_next(AltT *alt1, AltT *alt2)
{
	alt1->next = alt2;
}

TypeTupleT *
alt_names(AltT *alt)
{
	return &alt->names;
}

BitVecT *
alt_first_set(AltT *alt)
{
	return &alt->first_set;
}

ItemT *
alt_item_head(AltT *alt)
{
	return alt->item_head;
}

ItemT *
alt_unlink_item_head(AltT *alt)
{
	ItemT *item = alt_item_head(alt);

	alt->item_head = item_next(item);
	item_set_next(item, NULL);
	if (alt->item_tail == item_next_ref(item)) {
		alt->item_tail = &alt->item_head;
	}

	return item;
}

void
alt_add_item(AltT *alt, ItemT *item)
{
	*alt->item_tail = item;
	alt->item_tail  = item_next_ref(item);
}

AltT *
alt_deallocate(AltT *alt)
{
	AltT  *next = alt_next(alt);
	ItemT *item;

	for (item = alt_item_head(alt); item; item = item_deallocate(item)) {
		/* NOTHING */
	}

	types_destroy(alt_names(alt));
	bitvec_destroy(alt_first_set(alt));
	DEALLOCATE(alt);

	return next;
}

void
write_alt(OStreamT *ostream, AltT *alt)
{
	ItemT *item;

	for (item = alt_item_head(alt); item; item = item_next(item)) {
		write_tab(ostream);
		write_item(ostream, item);
		write_newline(ostream);
	}
}

void
write_alt_highlighting(OStreamT *ostream, AltT *alt, ItemT *highlight)
{
	ItemT *item;

	for (item = alt_item_head(alt); item; item = item_next(item)) {
		if (item == highlight) {
			write_cstring(ostream, "==>>");
		}

		write_tab(ostream);
		write_item(ostream, item);
		write_newline(ostream);
	}
}
