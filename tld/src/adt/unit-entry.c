/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * unit-entry.c - Unit set table entry ADT.
 *
 * This file implements the unit set table entry routines used by the TDF
 * linker.
 */

#include <shared/bool.h>
#include <shared/check.h>

#include "unit-entry.h"
#include "shape-entry.h"
#include "solve-cycles.h"
#include "debug.h"
#include "tdf.h"


static void
unit_write(UnitT *      unit,		    ShapeTableT *shapes ,
		    unsigned    num_shapes ,
		    TDFWriterT * writer)
{
    size_t length = nstring_length(& (unit->contents));
    MapTableT *table;

    if ((table = unit->map_table) != NULL) {
	ShapeClosureT shape_closure;

	shape_closure.table  = table;
	shape_closure.writer = writer;
	debug_info_w_start_counts(num_shapes);
	tdf_write_int(writer, num_shapes);
	shape_table_iter(shapes, shape_entry_write_count,
			 (void *) &shape_closure);
	debug_info_w_start_maps(num_shapes);
	tdf_write_int(writer, num_shapes);
	shape_table_iter(shapes, shape_entry_write_links,
			 (void *) &shape_closure);
    } else {
	debug_info_w_start_counts((unsigned)0);
	tdf_write_int(writer,(unsigned)0);
	debug_info_w_start_maps((unsigned)0);
	tdf_write_int(writer,(unsigned)0);
    }
    debug_info_w_unit_body(length);
    tdf_write_int(writer, (unsigned) length);
    tdf_write_bytes(writer, & (unit->contents));
}

void
unit_set_contents(UnitT *   unit,			   NStringT *nstring)
{
    nstring_assign(& (unit->contents), nstring);
}

MapTableT *
unit_map_table(UnitT *unit)
{
    return unit->map_table;
}

UnitEntryT *
unit_entry_create(NStringT *  key,			   UnitEntryT *next ,
			   unsigned   order)
{
    UnitEntryT *entry = ALLOCATE(UnitEntryT);

    entry->next  = next;
    entry->order = order;
    nstring_copy(& (entry->key), key);
    entry->head  = NULL;
    entry->tail  = & (entry->head);
    return entry;
}

UnitEntryT *
unit_entry_next(UnitEntryT *entry)
{
    return entry->next;
}

NStringT *
unit_entry_key(UnitEntryT *entry)
{
    return &entry->key;
}

unsigned
unit_entry_order(UnitEntryT *entry)
{
    return entry->order;
}

UnitT *
unit_entry_add_unit(UnitEntryT *entry,			     unsigned   num_counts)
{
    UnitT *unit = ALLOCATE(UnitT);

    unit->next      = NULL;
    unit->map_table = ((num_counts != 0)?
		       map_table_create(): NULL);
    *(entry->tail) = unit;
    entry->tail     = & (unit->next);
    return unit;
}

void
unit_entry_do_count(UnitEntryT *entry,			     void *   gclosure)
{
    UnitSetClosureT *closure = (UnitSetClosureT *)gclosure;
    UnitT *          unit;

    if ((unit = entry->head) != NULL) {
	while (unit) {
	    MapTableT *table;

	    if ((table = unit->map_table) != NULL) {
		map_table_iter(table, map_entry_check_non_empty,
				(void *)closure->shapes);
	    }
	    unit = unit->next;
	}
	closure->num_unit_sets++;
    }
}

void
unit_entry_write_unit_set(UnitEntryT *entry,				   UnitEntryT *tld_entry ,
				   TDFWriterT *writer)
{
    if ((entry->head) || (entry == tld_entry)) {
	NStringT *key = unit_entry_key(entry);

	debug_info_w_unit_dec(key);
	tdf_write_string(writer, key);
    }
}

void
unit_entry_write_tld_unit(UnitEntryT * entry,				   ShapeTableT *shapes ,
				   TDFWriterT * writer)
{
    size_t size = (tdf_int_size((unsigned)1) + 1);
    NStringT *key  = unit_entry_key(entry);

    debug_info_w_start_units(key,(unsigned)1);
    tdf_write_int(writer,(unsigned)1);
    debug_info_w_start_unit(key,(unsigned)1,(unsigned)1);
    debug_info_w_start_counts((unsigned)0);
    tdf_write_int(writer,(unsigned)0);
    debug_info_w_start_maps((unsigned)0);
    tdf_write_int(writer,(unsigned)0);
    shape_table_iter(shapes, shape_entry_compute_tld_size, &size);
    size /= 2;
    debug_info_w_unit_body(size);
    tdf_write_int(writer, (unsigned) size);
    tdf_write_align(writer);
    debug_info_w_tld_version((unsigned)1);
    tdf_write_int(writer,(unsigned)1);
    shape_table_iter(shapes, shape_entry_write_tld,(void *)writer);
    tdf_write_align(writer);
}

void
unit_entry_write_units(UnitEntryT * entry,				ShapeTableT *shapes ,
				unsigned    num_shapes ,
				TDFWriterT * writer)
{
    unsigned num_units = 0;
    NStringT *key       = unit_entry_key(entry);
    UnitT *   unit;

    for (unit = entry->head; unit; unit = unit->next) {
	num_units++;
    }
    if (num_units > 0) {
	unsigned i;

	debug_info_w_start_units(key, num_units);
	tdf_write_int(writer, num_units);
	for (unit = entry->head, i = 1; unit; unit = unit->next, i++) {
	    debug_info_w_start_unit(key, i, num_units);
	    unit_write(unit, shapes, num_shapes, writer);
	}
    }
}
