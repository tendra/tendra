/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * shape-table.c - Shape table ADT.
 *
 * This file implements the shape table routines used by the TDF linker.
 */

#include <shared/bool.h>
#include <shared/check.h>

#include "shape-table.h"
#include "solve-cycles.h"

ShapeTableT *
shape_table_create(void)
{
    ShapeTableT *table = ALLOCATE(ShapeTableT);
    unsigned    i;

    for (i = 0; i < SHAPE_TABLE_SIZE; i++) {
	table->contents[i] = NULL;
    }
    table->token_entry = NULL;
    table->tag_entry   = NULL;
    return table;
}

ShapeEntryT *
shape_table_add(ShapeTableT *table,			 NStringT *   key)
{
    unsigned     hash_value = (nstring_hash_value(key)% SHAPE_TABLE_SIZE);
    ShapeEntryT **entryp     = & (table->contents[hash_value]);
    ShapeEntryT * entry;

    while ((entry = *entryp) != NULL) {
	if (nstring_equal(key, shape_entry_key(entry))) {
	    return entry;
	}
	entryp = shape_entry_next_ref(entry);
    }
    entry   = shape_entry_create(key);
    *entryp = entry;
    return entry;
}

ShapeEntryT *
shape_table_get(ShapeTableT *table,			 NStringT *   key)
{
    unsigned    hash_value = (nstring_hash_value(key)% SHAPE_TABLE_SIZE);
    ShapeEntryT *entry      = (table->contents[hash_value]);

    while (entry) {
	if (nstring_equal(key, shape_entry_key(entry))) {
	    return entry;
	}
	entry = shape_entry_next(entry);
    }
    return NULL;
}

ShapeEntryT *
shape_table_get_token_entry(ShapeTableT *table)
{
    if (table->token_entry == NULL) {
	NStringT nstring;

	nstring_copy_cstring(&nstring, "token");
	table->token_entry = shape_table_get(table, &nstring);
	nstring_destroy(&nstring);
    }
    return table->token_entry;
}

ShapeEntryT *
shape_table_get_tag_entry(ShapeTableT *table)
{
    if (table->tag_entry == NULL) {
	NStringT nstring;

	nstring_copy_cstring(&nstring, "tag");
	table->tag_entry = shape_table_get(table, &nstring);
	nstring_destroy(&nstring);
    }
    return table->tag_entry;
}

void
shape_table_iter(ShapeTableT *table, void (*proc)(ShapeEntryT *, void *),
		 void * closure)
{
    unsigned i;

    for (i = 0; i < SHAPE_TABLE_SIZE; i++) {
	ShapeEntryT *entry = (table->contents[i]);

	while (entry) {
	   (*proc)(entry, closure);
	    entry = shape_entry_next(entry);
	}
    }
}

void
shape_table_deallocate(ShapeTableT *table)
{
    unsigned i;

    for (i = 0; i < SHAPE_TABLE_SIZE; i++) {
	ShapeEntryT *entry = (table->contents[i]);

	while (entry) {
	    entry = shape_entry_deallocate(entry);
	}
    }
}
