/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/*** shape-entry.c --- Shape table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the shape table entry routines used by the TDF
 * linker.
 *
 *** Change Log:*/

/****************************************************************************/

#include "shape-entry.h"
#include "debug.h"
#include "gen-errors.h"
#include "unit-table.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

ShapeEntryP
shape_entry_create(NStringP key)
{
    ShapeEntryP entry = ALLOCATE (ShapeEntryT);
	
    entry->next      = NIL (ShapeEntryP);
    nstring_copy (shape_entry_key (entry), key);
    entry->names     = name_table_create ();
    entry->id_count  = 0;
    entry->non_empty = FALSE;
    entry->head      = NIL (NameEntryP);
    entry->tail      = &(entry->head);
    return (entry);
}

ShapeEntryP
shape_entry_next(ShapeEntryP entry)
{
    return (entry->next);
}

ShapeEntryP *
shape_entry_next_ref(ShapeEntryP entry)
{
    return (&(entry->next));
}

NStringP
shape_entry_key(ShapeEntryP entry)
{
    return (&(entry->key));
}

NameTableP
shape_entry_name_table(ShapeEntryP entry)
{
    return (entry->names);
}

unsigned
shape_entry_next_id(ShapeEntryP entry)
{
    if (entry->id_count == UINT_MAX) {
		E_too_many_ids ();
    }
    return (entry->id_count ++);
}

void
shape_entry_set_non_empty(ShapeEntryP entry)
{
    entry->non_empty = TRUE;
}

BoolT
shape_entry_get_non_empty(ShapeEntryP entry)
{
    return (entry->non_empty);
}

void
shape_entry_add_to_list(ShapeEntryP entry,
						NameEntryP name_entry)
{
    *(entry->tail) = name_entry;
    entry->tail    = name_entry_list_next_ref (name_entry);
}

NameEntryP
shape_entry_get_from_list(ShapeEntryP entry)
{
    NameEntryP name_entry;
	
    if ((name_entry = entry->head) != NIL (NameEntryP)) {
		entry->head = name_entry_list_next (name_entry);
		if (entry->head == NIL (NameEntryP)) {
			entry->tail = (&entry->head);
		}
    }
    return (name_entry);
}

ShapeEntryP
shape_entry_deallocate(ShapeEntryP entry)
{
    ShapeEntryP next = shape_entry_next (entry);
	
    nstring_destroy (shape_entry_key (entry));
    name_table_deallocate (shape_entry_name_table (entry));
    DEALLOCATE (entry);
    return (next);
}

/*--------------------------------------------------------------------------*/

void
shape_entry_do_count(ShapeEntryP entry, GenericP gclosure)
{
    unsigned *count_ref = (unsigned *) gclosure;
	
    if ((entry->id_count > 0) || (shape_entry_get_non_empty (entry))) {
		shape_entry_set_non_empty (entry);
		(*count_ref) ++;
    }
}

void
shape_entry_write_shape(ShapeEntryP entry,
						GenericP gclosure)
{
    if (shape_entry_get_non_empty (entry)) {
		TDFWriterP writer  = (TDFWriterP) gclosure;
		NStringP   key     = shape_entry_key (entry);
		unsigned   num_ids = entry->id_count;
		
		debug_info_w_shape (key, num_ids);
		tdf_write_string (writer, key);
		tdf_write_int (writer, num_ids);
    }
}

void
shape_entry_write_externs(ShapeEntryP entry,
						  GenericP gclosure)
{
    if (shape_entry_get_non_empty (entry)) {
		TDFWriterP writer      = (TDFWriterP) gclosure;
		unsigned   num_externs = 0;
		NameTableP table       = entry->names;
		NStringP   key         = shape_entry_key (entry);
		
		name_table_iter (table, name_entry_do_count, (GenericP) &num_externs);
		debug_info_w_start_shape_names (key, num_externs);
		tdf_write_int (writer, num_externs);
		name_table_iter (table, name_entry_write_name, (GenericP) writer);
    }
}

void
shape_entry_compute_tld_size(ShapeEntryP entry,
							 GenericP gclosure)
{
    if (shape_entry_get_non_empty (entry)) {
		name_table_iter (entry->names, name_entry_compute_tld_size, gclosure);
    }
}

void
shape_entry_write_tld(ShapeEntryP entry, GenericP gclosure)
{
    if (shape_entry_get_non_empty (entry)) {
		debug_info_w_start_usages (shape_entry_key (entry));
		name_table_iter (entry->names, name_entry_write_tld, gclosure);
    }
}

void
shape_entry_write_count(ShapeEntryP entry,
						GenericP gclosure)
{
    ShapeClosureP closure = (ShapeClosureP) gclosure;
	
    if (shape_entry_get_non_empty (entry)) {
		MapTableP  table     = closure->table;
		TDFWriterP writer    = closure->writer;
		MapEntryP  map_entry = map_table_get (table, shape_entry_key (entry));
		unsigned   count     = (map_entry ? map_entry_get_count (map_entry) :
								0);
		NStringP   key       = shape_entry_key (entry);
		
		debug_info_w_count (count, key);
		tdf_write_int (writer, count);
    }
}

void
shape_entry_write_links(ShapeEntryP entry,
						GenericP gclosure)
{
    ShapeClosureP closure = (ShapeClosureP) gclosure;
	
    if (shape_entry_get_non_empty (entry)) {
		MapTableP  table     = closure->table;
		TDFWriterP writer    = closure->writer;
		MapEntryP  map_entry = map_table_get (table, shape_entry_key (entry));
		NStringP   key       = shape_entry_key (entry);
		
		if (map_entry) {
			unsigned num_links = map_entry_get_num_links (map_entry);
			unsigned i;
			
			debug_info_w_start_shape_maps (key, num_links);
			tdf_write_int (writer, num_links);
			for (i = 0; i < num_links; i ++) {
				unsigned internal;
				unsigned external;
				
				map_entry_get_link (map_entry, i , &internal, &external);
				debug_info_w_map (internal, external);
				tdf_write_int (writer, internal);
				tdf_write_int (writer, external);
			}
		} else {
			debug_info_w_start_shape_maps (key, (unsigned) 0);
			tdf_write_int (writer, (unsigned) 0);
		}
    }
}

void
shape_entry_check_multi_defs(ShapeEntryP entry,
							 GenericP gclosure)
{
    NameTableP table = shape_entry_name_table (entry);
    NStringP   key   = shape_entry_key (entry);
	
    UNUSED (gclosure);
    name_table_iter (table, name_entry_check_multi_defs, (GenericP) key);
}

void
shape_entry_do_lib_count(ShapeEntryP entry,
						 GenericP gclosure)
{
    NameTableP table     = shape_entry_name_table (entry);
    unsigned   num_names = 0;
	
    name_table_iter (table, name_entry_do_lib_count, (GenericP) &num_names);
    if (num_names > 0) {
		unsigned *num_shapes_ref = (unsigned *) gclosure;
		
		(*num_shapes_ref) ++;
    }
    entry->num_lib_names = num_names;
}

void
shape_entry_do_lib_write(ShapeEntryP entry,
						 GenericP gclosure)
{
    unsigned num_names = entry->num_lib_names;
	
    if (num_names > 0) {
		TDFWriterP writer = (TDFWriterP) gclosure;
		NameTableP table  = shape_entry_name_table (entry);
		NStringP   key    = shape_entry_key (entry);
		
		debug_info_w_start_shape_index (key, num_names);
		tdf_write_string (writer, shape_entry_key (entry));
		tdf_write_int (writer, num_names);
		name_table_iter (table, name_entry_do_lib_write, gclosure);
    }
}

void
shape_entry_resolve_undefined(ShapeEntryP entry,
							  GenericP gclosure)
{
    ShapeLibClosureP closure   = (ShapeLibClosureP) gclosure;
    NStringP         key       = shape_entry_key (entry);
    ShapeEntryP      lib_entry = shape_table_get (closure->lib_shapes, key);
    NameTableP       table     = ((lib_entry != NIL (ShapeEntryP)) ?
								  shape_entry_name_table (lib_entry) :
								  NIL (NameTableP));
    NameEntryP       name_entry;
	
    while ((name_entry = shape_entry_get_from_list (entry)) !=
		   NIL (NameEntryP)) {
		if (name_entry_resolve_undefined (name_entry, table, closure->units,
										  closure->shapes, key)) {
			closure->did_define = TRUE;
		}
    }
}

void
shape_entry_hide_all_defd(ShapeEntryP entry,
						  GenericP gclosure)
{
    NameTableP table = shape_entry_name_table (entry);
    NStringP   shape = shape_entry_key (entry);
	
    UNUSED (gclosure);
    name_table_iter (table, name_entry_hide_defd, (GenericP) shape);
}

void
shape_entry_suppress_mult(ShapeEntryP entry,
						  GenericP gclosure)
{
    NameTableP table = shape_entry_name_table (entry);
    NStringP   shape = shape_entry_key (entry);
	
    UNUSED (gclosure);
    name_table_iter (table, name_entry_suppress_mult, (GenericP) shape);
}

void
shape_entry_lib_suppress_mult(ShapeEntryP entry,
							  GenericP gclosure)
{
    NameTableP table = shape_entry_name_table (entry);
    NStringP   shape = shape_entry_key (entry);
	
    UNUSED (gclosure);
    name_table_iter (table, name_entry_lib_suppress_mult, (GenericP) shape);
}

void
shape_entry_show_content(ShapeEntryP entry,
						 GenericP gclosure)
{
    UNUSED (gclosure);
    write_nstring (ostream_output, shape_entry_key (entry));
    write_char (ostream_output, ':');
    write_newline (ostream_output);
    name_table_iter (shape_entry_name_table (entry), name_entry_show_content,
					 NIL (GenericP));
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
 **/
