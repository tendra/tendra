/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * shape-entry.c - Shape table entry ADT.
 *
 * This file implements the shape table entry routines used by the TDF
 * linker.
 */

#include <limits.h>

#include <shared/bool.h>
#include <shared/error.h>
#include <shared/check.h>

#include "shape-entry.h"
#include "unit-table.h"
#include "solve-cycles.h"
#include "debug.h"

ShapeEntryT *
shape_entry_create(NStringT *key)
{
    ShapeEntryT *entry = ALLOCATE(ShapeEntryT);

    entry->next      = NULL;
    nstring_copy(shape_entry_key(entry), key);
    entry->names     = name_table_create();
    entry->id_count  = 0;
    entry->non_empty = false;
    entry->head      = NULL;
    entry->tail      = & (entry->head);
    return entry;
}

ShapeEntryT *
shape_entry_next(ShapeEntryT *entry)
{
    return entry->next;
}

ShapeEntryT **
shape_entry_next_ref(ShapeEntryT *entry)
{
    return &entry->next;
}

NStringT *
shape_entry_key(ShapeEntryT *entry)
{
    return &entry->key;
}

NameTableT *
shape_entry_name_table(ShapeEntryT *entry)
{
    return entry->names;
}

unsigned
shape_entry_next_id(ShapeEntryT *entry)
{
    if (entry->id_count == UINT_MAX) {
	error(ERR_FATAL,"too many identifiers for this implementation");
    }
    return entry->id_count++;
}

void
shape_entry_set_non_empty(ShapeEntryT *entry)
{
    entry->non_empty = true;
}

bool
shape_entry_get_non_empty(ShapeEntryT *entry)
{
    return entry->non_empty;
}

void
shape_entry_add_to_list(ShapeEntryT *entry,				 NameEntryT * name_entry)
{
    *(entry->tail) = name_entry;
    entry->tail    = name_entry_list_next_ref(name_entry);
}

NameEntryT *
shape_entry_get_from_list(ShapeEntryT *entry)
{
    NameEntryT *name_entry;

    if ((name_entry = entry->head) != NULL) {
	entry->head = name_entry_list_next(name_entry);
	if (entry->head == NULL) {
	    entry->tail = (&entry->head);
	}
    }
    return name_entry;
}

ShapeEntryT *
shape_entry_deallocate(ShapeEntryT *entry)
{
    ShapeEntryT *next = shape_entry_next(entry);

    nstring_destroy(shape_entry_key(entry));
    name_table_deallocate(shape_entry_name_table(entry));
    DEALLOCATE(entry);
    return next;
}

void
shape_entry_do_count(ShapeEntryT *entry,			      void *    gclosure)
{
    unsigned *count_ref = (unsigned *)gclosure;

    if ((entry->id_count > 0) || (shape_entry_get_non_empty(entry))) {
	shape_entry_set_non_empty(entry);
	(*count_ref)++;
    }
}

void
shape_entry_write_shape(ShapeEntryT *entry,				 void *    gclosure)
{
    if (shape_entry_get_non_empty(entry)) {
	TDFWriterT *writer  = (TDFWriterT *)gclosure;
	NStringT *  key     = shape_entry_key(entry);
	unsigned   num_ids = entry->id_count;

	debug_info_w_shape(key, num_ids);
	tdf_write_string(writer, key);
	tdf_write_int(writer, num_ids);
    }
}

void
shape_entry_write_externs(ShapeEntryT *entry,				   void *    gclosure)
{
    if (shape_entry_get_non_empty(entry)) {
	TDFWriterT *writer      = (TDFWriterT *)gclosure;
	unsigned   num_externs = 0;
	NameTableT *table       = entry->names;
	NStringT *  key         = shape_entry_key(entry);

	name_table_iter(table, name_entry_do_count,(void *) &num_externs);
	debug_info_w_start_shape_names(key, num_externs);
	tdf_write_int(writer, num_externs);
	name_table_iter(table, name_entry_write_name,(void *)writer);
    }
}

void
shape_entry_compute_tld_size(ShapeEntryT *entry,				      void *    gclosure)
{
    if (shape_entry_get_non_empty(entry)) {
	name_table_iter(entry->names, name_entry_compute_tld_size, gclosure);
    }
}

void
shape_entry_write_tld(ShapeEntryT *entry,			       void *    gclosure)
{
    if (shape_entry_get_non_empty(entry)) {
	debug_info_w_start_usages(shape_entry_key(entry));
	name_table_iter(entry->names, name_entry_write_tld, gclosure);
    }
}

void
shape_entry_write_count(ShapeEntryT *entry,				 void *    gclosure)
{
    ShapeClosureT *closure = (ShapeClosureT *)gclosure;

    if (shape_entry_get_non_empty(entry)) {
	MapTableT * table     = closure->table;
	TDFWriterT *writer    = closure->writer;
	MapEntryT * map_entry = map_table_get(table, shape_entry_key(entry));
	unsigned   count     = (map_entry ? map_entry_get_count(map_entry):
				0);
	NStringT *  key       = shape_entry_key(entry);

	debug_info_w_count(count, key);
	tdf_write_int(writer, count);
    }
}

void
shape_entry_write_links(ShapeEntryT *entry,				 void *    gclosure)
{
    ShapeClosureT *closure = (ShapeClosureT *)gclosure;

    if (shape_entry_get_non_empty(entry)) {
	MapTableT * table     = closure->table;
	TDFWriterT *writer    = closure->writer;
	MapEntryT * map_entry = map_table_get(table, shape_entry_key(entry));
	NStringT *  key       = shape_entry_key(entry);

	if (map_entry) {
	    unsigned num_links = map_entry_get_num_links(map_entry);
	    unsigned i;

	    debug_info_w_start_shape_maps(key, num_links);
	    tdf_write_int(writer, num_links);
	    for (i = 0; i < num_links; i++) {
		unsigned internal;
		unsigned external;

		map_entry_get_link(map_entry, i , &internal, &external);
		debug_info_w_map(internal, external);
		tdf_write_int(writer, internal);
		tdf_write_int(writer, external);
	    }
	} else {
	    debug_info_w_start_shape_maps(key,(unsigned)0);
	    tdf_write_int(writer,(unsigned)0);
	}
    }
}

void
shape_entry_check_multi_defs(ShapeEntryT *entry,				      void *    gclosure)
{
    NameTableT *table = shape_entry_name_table(entry);
    NStringT *  key   = shape_entry_key(entry);

    UNUSED(gclosure);
    name_table_iter(table, name_entry_check_multi_defs,(void *)key);
}

void
shape_entry_do_lib_count(ShapeEntryT *entry,				  void *    gclosure)
{
    NameTableT *table     = shape_entry_name_table(entry);
    unsigned   num_names = 0;

    name_table_iter(table, name_entry_do_lib_count,(void *) &num_names);
    if (num_names > 0) {
	unsigned *num_shapes_ref = (unsigned *)gclosure;

	(*num_shapes_ref)++;
    }
    entry->num_lib_names = num_names;
}

void
shape_entry_do_lib_write(ShapeEntryT *entry,				  void *    gclosure)
{
    unsigned num_names = entry->num_lib_names;

    if (num_names > 0) {
	TDFWriterT *writer = (TDFWriterT *)gclosure;
	NameTableT *table  = shape_entry_name_table(entry);
	NStringT *  key    = shape_entry_key(entry);

	debug_info_w_start_shape_index(key, num_names);
	tdf_write_string(writer, shape_entry_key(entry));
	tdf_write_int(writer, num_names);
	name_table_iter(table, name_entry_do_lib_write, gclosure);
    }
}

void
shape_entry_resolve_undefined(ShapeEntryT *entry,				       void *    gclosure)
{
    ShapeLibClosureT *closure   = (ShapeLibClosureT *)gclosure;
    NStringT *        key       = shape_entry_key(entry);
    ShapeEntryT *     lib_entry = shape_table_get(closure->lib_shapes, key);
    NameTableT *      table     = ((lib_entry != NULL)?
				  shape_entry_name_table(lib_entry):
				  NULL);
    NameEntryT *      name_entry;

    while ((name_entry = shape_entry_get_from_list(entry)) !=
	   NULL) {
	if (name_entry_resolve_undefined(name_entry, table, closure->units,
					  closure->shapes, key, closure->missing_definitions)) {
	    closure->did_define = true;
	}
    }
}

void
shape_entry_hide_all_defd(ShapeEntryT *entry,				   void *    gclosure)
{
    NameTableT *table = shape_entry_name_table(entry);
    NStringT *  shape = shape_entry_key(entry);

    UNUSED(gclosure);
    name_table_iter(table, name_entry_hide_defd,(void *)shape);
}

void
shape_entry_suppress_mult(ShapeEntryT *entry,				   void *    gclosure)
{
    NameTableT *table = shape_entry_name_table(entry);
    NStringT *  shape = shape_entry_key(entry);

    UNUSED(gclosure);
    name_table_iter(table, name_entry_suppress_mult,(void *)shape);
}

void
shape_entry_lib_suppress_mult(ShapeEntryT *entry,				       void *    gclosure)
{
    NameTableT *table = shape_entry_name_table(entry);
    NStringT *  shape = shape_entry_key(entry);

    UNUSED(gclosure);
    name_table_iter(table, name_entry_lib_suppress_mult,(void *)shape);
}

void
shape_entry_show_content(ShapeEntryT *entry,				  void *    gclosure)
{
    UNUSED(gclosure);
    write_nstring(ostream_output, shape_entry_key(entry));
    write_char(ostream_output, ':');
    write_newline(ostream_output);
    name_table_iter(shape_entry_name_table(entry), name_entry_show_content,
		     NULL);
}
