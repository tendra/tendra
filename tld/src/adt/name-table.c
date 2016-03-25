/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * name-table.c - Name table ADT.
 *
 * This file implements the name table routines used by the TDF linker.
 */

#include <shared/bool.h>
#include <shared/check.h>

#include "name-table.h"
#include "shape-entry.h"
#include "solve-cycles.h"

NameTableT *
name_table_create(void)
{
    NameTableT *table = ALLOCATE(NameTableT);
    unsigned   i;

    for (i = 0; i < NAME_TABLE_SIZE; i++) {
	table->contents[i] = NULL;
    }
    return table;
}

void
name_table_add_rename(NameTableT *table,			       NameKeyT *  from, 
			       NameKeyT *  to)
{
    unsigned    to_hash_value = (name_key_hash_value(to)% NAME_TABLE_SIZE);
    NameEntryT **to_entryp     = & (table->contents[to_hash_value]);
    unsigned    hash_value    = (name_key_hash_value(from)% NAME_TABLE_SIZE);
    NameEntryT **from_entryp   = & (table->contents[hash_value]);
    NameEntryT * to_entry;
    NameEntryT * from_entry;

    while ((to_entry = *to_entryp) != NULL) {
	if (name_key_equal(to, name_entry_key(to_entry))) {
	    goto found;
	}
	to_entryp = name_entry_next_ref(to_entry);
    }
    to_entry   = name_entry_create_place(to);
    *to_entryp = to_entry;
  found:
    while ((from_entry = *from_entryp) != NULL) {
	if (name_key_equal(from, name_entry_key(from_entry))) {
	    name_entry_make_indirect(from_entry, to_entry);
	    return;
	}
	from_entryp = name_entry_next_ref(from_entry);
    }
    from_entry   = name_entry_create_indirect(from, to_entry);
    *from_entryp = from_entry;
}

void
name_table_resolve_renames(NameTableT *table,				    NStringT *  shape, 
				    bool      report)
{
    unsigned i;

    for (i = 0; i < NAME_TABLE_SIZE; i++) {
	NameEntryT *entry = (table->contents[i]);

	while (entry) {
	    IGNORE name_entry_resolve_renames(entry, shape, report);
	    entry = name_entry_next(entry);
	}
    }
}

NameEntryT *
name_table_add(NameTableT * table,			NameKeyT *   key, 
			ShapeEntryT *shape_entry)
{
    unsigned    hash_value = (name_key_hash_value(key)% NAME_TABLE_SIZE);
    NameEntryT **entryp     = & (table->contents[hash_value]);
    NameEntryT * entry;

    while ((entry = *entryp) != NULL) {
	if (name_key_equal(key, name_entry_key(entry))) {
	    if (name_entry_is_indirect(entry)) {
		entry = name_entry_get_indirect(entry);
	    }
	    if (name_entry_is_place(entry)) {
		name_entry_make_direct(entry, shape_entry);
	    }
	    return entry;
	}
	entryp = name_entry_next_ref(entry);
    }
    entry   = name_entry_create_direct(key, shape_entry);
    *entryp = entry;
    return entry;
}

NameEntryT *
name_table_get(NameTableT *table,			NameKeyT *  key)
{
    unsigned   hash_value = (name_key_hash_value(key)% NAME_TABLE_SIZE);
    NameEntryT *entry      = table->contents[hash_value];

    while (entry) {
	if (name_key_equal(key, name_entry_key(entry))) {
	    if (name_entry_is_indirect(entry)) {
		entry = name_entry_get_indirect(entry);
	    }
	    if (name_entry_is_place(entry)) {
		return NULL;
	    }
	    return entry;
	}
	entry = name_entry_next(entry);
    }
    return NULL;
}

void
name_table_iter(NameTableT *table, void(*proc)(NameEntryT *, void *),
		void * closure)
{
    unsigned i;

    for (i = 0; i < NAME_TABLE_SIZE; i++) {
	NameEntryT *entry = (table->contents[i]);

	while (entry) {
	    if (name_entry_is_direct(entry)) {
		(*proc)(entry, closure);
	    }
	    entry = name_entry_next(entry);
	}
    }
}

void
name_table_deallocate(NameTableT *table)
{
    unsigned i;

    for (i = 0; i < NAME_TABLE_SIZE; i++) {
	NameEntryT *entry = (table->contents[i]);

	while (entry) {
	    entry = name_entry_deallocate(entry);
	}
    }
}
