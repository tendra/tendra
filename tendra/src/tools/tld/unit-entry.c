/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


/*** unit-entry.c --- Unit set table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the unit set table entry routines used by the TDF
 * linker.
 *
 *** Change Log:*/

/****************************************************************************/

#include "unit-entry.h"
#include "debug.h"
#include "shape-entry.h"
#include "tdf.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

static void
unit_write(UnitP unit, ShapeTableP shapes,
		   unsigned num_shapes, TDFWriterP writer)
{
    unsigned  length = nstring_length (&(unit->contents));
    MapTableP table;

    if ((table = unit->map_table) != NIL (MapTableP)) {
		ShapeClosureT shape_closure;

		shape_closure.table  = table;
		shape_closure.writer = writer;
		debug_info_w_start_counts (num_shapes);
		tdf_write_int (writer, num_shapes);
		shape_table_iter (shapes, shape_entry_write_count,
						  (GenericP) &shape_closure);
		debug_info_w_start_maps (num_shapes);
		tdf_write_int (writer, num_shapes);
		shape_table_iter (shapes, shape_entry_write_links,
						  (GenericP) &shape_closure);
    } else {
		debug_info_w_start_counts ((unsigned) 0);
		tdf_write_int (writer, (unsigned) 0);
		debug_info_w_start_maps ((unsigned) 0);
		tdf_write_int (writer, (unsigned) 0);
    }
    debug_info_w_unit_body (length);
    tdf_write_int (writer, length);
    tdf_write_bytes (writer, &(unit->contents));
}

/*--------------------------------------------------------------------------*/

void
unit_set_contents(UnitP unit, NStringP nstring)
{
    nstring_assign (&(unit->contents), nstring);
}

MapTableP
unit_map_table(UnitP unit)
{
    return (unit->map_table);
}

UnitEntryP
unit_entry_create(NStringP key, UnitEntryP next,
				  unsigned order)
{
    UnitEntryP entry = ALLOCATE (UnitEntryT);

    entry->next  = next;
    entry->order = order;
    nstring_copy (&(entry->key), key);
    entry->head  = NIL (UnitP);
    entry->tail  = &(entry->head);
    return (entry);
}

UnitEntryP
unit_entry_next(UnitEntryP entry)
{
    return (entry->next);
}

NStringP
unit_entry_key(UnitEntryP entry)
{
    return (&(entry->key));
}

unsigned
unit_entry_order(UnitEntryP entry)
{
    return (entry->order);
}

UnitP
unit_entry_add_unit(UnitEntryP entry, unsigned num_counts)
{
    UnitP unit = ALLOCATE (UnitT);

    unit->next      = NIL (UnitP);
    unit->map_table = ((num_counts != 0) ?
					   map_table_create () : NIL (MapTableP));
    *(entry->tail)  = unit;
    entry->tail     = &(unit->next);
    return (unit);
}

/*--------------------------------------------------------------------------*/

void
unit_entry_do_count(UnitEntryP entry, GenericP gclosure)
{
    UnitSetClosureP closure = (UnitSetClosureP) gclosure;
    UnitP           unit;

    if ((unit = entry->head) != NIL (UnitP)) {
		while (unit) {
			MapTableP table;

			if ((table = unit->map_table) != NIL (MapTableP)) {
				map_table_iter (table, map_entry_check_non_empty,
								(GenericP) closure->shapes);
			}
			unit = unit->next;
		}
		closure->num_unit_sets ++;
    }
}

void
unit_entry_write_unit_set(UnitEntryP entry,
						  UnitEntryP tld_entry,
						  TDFWriterP writer)
{
    if ((entry->head) || (entry == tld_entry)) {
		NStringP key = unit_entry_key (entry);

		debug_info_w_unit_dec (key);
		tdf_write_string (writer, key);
    }
}

void
unit_entry_write_tld_unit(UnitEntryP entry,
						  ShapeTableP shapes,
						  TDFWriterP writer)
{
    unsigned size = (tdf_int_size ((unsigned) 1) + 1);
    NStringP key  = unit_entry_key (entry);

    debug_info_w_start_units (key, (unsigned) 1);
    tdf_write_int (writer, (unsigned) 1);
    debug_info_w_start_unit (key, (unsigned) 1, (unsigned) 1);
    debug_info_w_start_counts ((unsigned) 0);
    tdf_write_int (writer, (unsigned) 0);
    debug_info_w_start_maps ((unsigned) 0);
    tdf_write_int (writer, (unsigned) 0);
    shape_table_iter (shapes, shape_entry_compute_tld_size, (GenericP) &size);
    size /= 2;
    debug_info_w_unit_body (size);
    tdf_write_int (writer, size);
    tdf_write_align (writer);
    debug_info_w_tld_version ((unsigned) 1);
    tdf_write_int (writer, (unsigned) 1);
    shape_table_iter (shapes, shape_entry_write_tld, (GenericP) writer);
    tdf_write_align (writer);
}

void
unit_entry_write_units(UnitEntryP entry, ShapeTableP shapes,
					   unsigned num_shapes,
					   TDFWriterP writer)
{
    unsigned num_units = 0;
    NStringP key       = unit_entry_key (entry);
    UnitP    unit;

    for (unit = entry->head; unit; unit = unit->next) {
		num_units ++;
    }
    if (num_units > 0) {
		unsigned i;

		debug_info_w_start_units (key, num_units);
		tdf_write_int (writer, num_units);
		for (unit = entry->head, i = 1; unit; unit = unit->next, i ++) {
			debug_info_w_start_unit (key, i, num_units);
			unit_write (unit, shapes, num_shapes, writer);
		}
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
 **/
