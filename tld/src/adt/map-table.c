/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * map-table.c - Mapping table ADT.
 *
 * This file implements the mapping table routines used by the TDF linker.
 */

#include <shared/bool.h>
#include <shared/check.h>

#include "map-table.h"
#include "solve-cycles.h"

MapTableT *
map_table_create(void)
{
    MapTableT *table = ALLOCATE(MapTableT);
    unsigned  i;

    for (i = 0; i < MAP_TABLE_SIZE; i++) {
	table->contents[i] = NULL;
    }
    return table;
}

MapEntryT *
map_table_add(MapTableT *table,		       NStringT * key, 
		       unsigned  count)
{
    unsigned  hash_value = (nstring_hash_value(key)% MAP_TABLE_SIZE);
    MapEntryT *next       = (table->contents[hash_value]);
    MapEntryT *entry      = map_entry_create(key, next, count);

    table->contents[hash_value] = entry;
    return entry;
}

MapEntryT *
map_table_get(MapTableT *table,		       NStringT * key)
{
    unsigned  hash_value = (nstring_hash_value(key)% MAP_TABLE_SIZE);
    MapEntryT *entry      = (table->contents[hash_value]);

    while (entry) {
	if (nstring_equal(key, map_entry_key(entry))) {
	    return entry;
	}
	entry = map_entry_next(entry);
    }
    return NULL;
}

void
map_table_iter(MapTableT *table,			void   (*proc)(MapEntryT *, void *),
			void *  closure)
{
    unsigned i;

    for (i = 0; i < MAP_TABLE_SIZE; i++) {
	MapEntryT *entry = (table->contents[i]);

	while (entry) {
	   (*proc)(entry, closure);
	    entry = map_entry_next(entry);
	}
    }
}
