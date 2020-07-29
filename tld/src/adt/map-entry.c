/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * map-entry.c - Mapping table entry ADT.
 *
 * This file implements the mapping table entry routines used by the TDF
 * linker.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>

#include "map-entry.h"
#include "shape-table.h"
#include "solve-cycles.h"

MapEntryT *
map_entry_create(NStringT * key,			  MapEntryT *next, 
			  unsigned  count)
{
    MapEntryT *entry = ALLOCATE(MapEntryT);

    entry->next  = next;
    nstring_copy(& (entry->key), key);
    entry->count = count;
    return entry;
}

MapEntryT *
map_entry_next(MapEntryT *entry)
{
    return entry->next;
}

NStringT *
map_entry_key(MapEntryT *entry)
{
    return &entry->key;
}

void
map_entry_set_num_links(MapEntryT *entry,				 unsigned  num_links)
{
    entry->num_links = num_links;
    entry->links     = ALLOCATE_VECTOR(MapLinkT, num_links);
}

void
map_entry_set_link(MapEntryT *entry,			    unsigned  link, 
			    unsigned  internal, 
			    unsigned  external)
{
    assert(link < entry->num_links);
    entry->links[link].internal = internal;
    entry->links[link].external = external;
}

unsigned
map_entry_get_count(MapEntryT *entry)
{
    return entry->count;
}

unsigned
map_entry_get_num_links(MapEntryT *entry)
{
    return entry->num_links;
}

void
map_entry_get_link(MapEntryT *entry,			    unsigned  link, 
			    unsigned *internal_ref, 
			    unsigned *external_ref)
{
    assert(link < entry->num_links);
    *internal_ref = entry->links[link].internal;
    *external_ref = entry->links[link].external;
}

void
map_entry_check_non_empty(MapEntryT *entry,				   void *  gclosure)
{
    ShapeTableT *table = (ShapeTableT *)gclosure;

    if (entry->count > 0) {
	NStringT *   key         = map_entry_key(entry);
	ShapeEntryT *shape_entry = shape_table_get(table, key);

	shape_entry_set_non_empty(shape_entry);
    }
}
