/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
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
 *** Change Log:
 * $Log: unit-entry.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:20  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:43  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:47:05  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:40  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "unit-entry.h"
#include "debug.h"
#include "shape-entry.h"
#include "tdf.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

static void
unit_write PROTO_N ((unit, shapes, num_shapes, writer))
	   PROTO_T (UnitP       unit X
		    ShapeTableP shapes X
		    unsigned    num_shapes X
		    TDFWriterP  writer)
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
unit_set_contents PROTO_N ((unit, nstring))
		  PROTO_T (UnitP    unit X
			   NStringP nstring)
{
    nstring_assign (&(unit->contents), nstring);
}

MapTableP
unit_map_table PROTO_N ((unit))
	       PROTO_T (UnitP unit)
{
    return (unit->map_table);
}

UnitEntryP
unit_entry_create PROTO_N ((key, next, order))
		  PROTO_T (NStringP   key X
			   UnitEntryP next X
			   unsigned   order)
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
unit_entry_next PROTO_N ((entry))
		PROTO_T (UnitEntryP entry)
{
    return (entry->next);
}

NStringP
unit_entry_key PROTO_N ((entry))
	       PROTO_T (UnitEntryP entry)
{
    return (&(entry->key));
}

unsigned
unit_entry_order PROTO_N ((entry))
		 PROTO_T (UnitEntryP entry)
{
    return (entry->order);
}

UnitP
unit_entry_add_unit PROTO_N ((entry, num_counts))
		    PROTO_T (UnitEntryP entry X
			     unsigned   num_counts)
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
unit_entry_do_count PROTO_N ((entry, gclosure))
		    PROTO_T (UnitEntryP entry X
			     GenericP   gclosure)
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
unit_entry_write_unit_set PROTO_N ((entry, tld_entry, writer))
			  PROTO_T (UnitEntryP entry X
				   UnitEntryP tld_entry X
				   TDFWriterP writer)
{
    if ((entry->head) || (entry == tld_entry)) {
	NStringP key = unit_entry_key (entry);

	debug_info_w_unit_dec (key);
	tdf_write_string (writer, key);
    }
}

void
unit_entry_write_tld_unit PROTO_N ((entry, shapes, writer))
			  PROTO_T (UnitEntryP  entry X
				   ShapeTableP shapes X
				   TDFWriterP  writer)
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
unit_entry_write_units PROTO_N ((entry, shapes, num_shapes, writer))
		       PROTO_T (UnitEntryP  entry X
				ShapeTableP shapes X
				unsigned    num_shapes X
				TDFWriterP  writer)
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
