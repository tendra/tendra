/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * unit-table.c - Unit set table ADT.
 *
 * This file implements the unit set table routines used by the TDF linker.
 */

#include <shared/bool.h>

#include "unit-table.h"
#include "solve-cycles.h"

UnitTableT *
unit_table_create(void)
{
    UnitTableT *table = ALLOCATE(UnitTableT);
    unsigned   i;

    for (i = 0; i < UNIT_TABLE_SIZE; i++) {
	table->contents[i] = NULL;
    }
    return table;
}

UnitEntryT *
unit_table_add(UnitTableT *table,			NStringT *  key ,
			unsigned   order)
{
    unsigned   hash_value = (nstring_hash_value(key)% UNIT_TABLE_SIZE);
    UnitEntryT *next       = (table->contents[hash_value]);
    UnitEntryT *entry      = unit_entry_create(key, next, order);

    table->contents[hash_value] = entry;
    return entry;
}

UnitEntryT *
unit_table_get(UnitTableT *table,			NStringT *  key)
{
    unsigned   hash_value = (nstring_hash_value(key)% UNIT_TABLE_SIZE);
    UnitEntryT *entry      = (table->contents[hash_value]);

    while (entry && (!nstring_equal(key, unit_entry_key(entry)))) {
	entry = unit_entry_next(entry);
    }
    return entry;
}

void
unit_table_iter(UnitTableT *table, void(*proc)(UnitEntryT *, void *),
		void * closure)
{
    unsigned i;

    for (i = 0; i < UNIT_TABLE_SIZE; i++) {
	UnitEntryT *entry = (table->contents[i]);

	while (entry) {
	   (*proc)(entry, closure);
	    entry = unit_entry_next(entry);
	}
    }
}
