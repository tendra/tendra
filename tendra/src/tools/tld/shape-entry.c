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


/*** shape-entry.c --- Shape table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the shape table entry routines used by the TDF
 * linker.
 *
 *** Change Log:
 * $Log: shape-entry.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:20  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:31  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:46:46  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:37  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "shape-entry.h"
#include "debug.h"
#include "gen-errors.h"
#include "unit-table.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

ShapeEntryP
shape_entry_create PROTO_N ((key))
		   PROTO_T (NStringP key)
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
shape_entry_next PROTO_N ((entry))
		 PROTO_T (ShapeEntryP entry)
{
    return (entry->next);
}

ShapeEntryP *
shape_entry_next_ref PROTO_N ((entry))
		     PROTO_T (ShapeEntryP entry)
{
    return (&(entry->next));
}

NStringP
shape_entry_key PROTO_N ((entry))
		PROTO_T (ShapeEntryP entry)
{
    return (&(entry->key));
}

NameTableP
shape_entry_name_table PROTO_N ((entry))
		       PROTO_T (ShapeEntryP entry)
{
    return (entry->names);
}

unsigned
shape_entry_next_id PROTO_N ((entry))
		    PROTO_T (ShapeEntryP entry)
{
    if (entry->id_count == UINT_MAX) {
	E_too_many_ids ();
    }
    return (entry->id_count ++);
}

void
shape_entry_set_non_empty PROTO_N ((entry))
			  PROTO_T (ShapeEntryP entry)
{
    entry->non_empty = TRUE;
}

BoolT
shape_entry_get_non_empty PROTO_N ((entry))
			  PROTO_T (ShapeEntryP entry)
{
    return (entry->non_empty);
}

void
shape_entry_add_to_list PROTO_N ((entry, name_entry))
			PROTO_T (ShapeEntryP entry X
				 NameEntryP  name_entry)
{
    *(entry->tail) = name_entry;
    entry->tail    = name_entry_list_next_ref (name_entry);
}

NameEntryP
shape_entry_get_from_list PROTO_N ((entry))
			  PROTO_T (ShapeEntryP entry)
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
shape_entry_deallocate PROTO_N ((entry))
		       PROTO_T (ShapeEntryP entry)
{
    ShapeEntryP next = shape_entry_next (entry);

    nstring_destroy (shape_entry_key (entry));
    name_table_deallocate (shape_entry_name_table (entry));
    DEALLOCATE (entry);
    return (next);
}

/*--------------------------------------------------------------------------*/

void
shape_entry_do_count PROTO_N ((entry, gclosure))
		     PROTO_T (ShapeEntryP entry X
			      GenericP    gclosure)
{
    unsigned *count_ref = (unsigned *) gclosure;

    if ((entry->id_count > 0) || (shape_entry_get_non_empty (entry))) {
	shape_entry_set_non_empty (entry);
	(*count_ref) ++;
    }
}

void
shape_entry_write_shape PROTO_N ((entry, gclosure))
			PROTO_T (ShapeEntryP entry X
				 GenericP    gclosure)
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
shape_entry_write_externs PROTO_N ((entry, gclosure))
			  PROTO_T (ShapeEntryP entry X
				   GenericP    gclosure)
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
shape_entry_compute_tld_size PROTO_N ((entry, gclosure))
			     PROTO_T (ShapeEntryP entry X
				      GenericP    gclosure)
{
    if (shape_entry_get_non_empty (entry)) {
	name_table_iter (entry->names, name_entry_compute_tld_size, gclosure);
    }
}

void
shape_entry_write_tld PROTO_N ((entry, gclosure))
		      PROTO_T (ShapeEntryP entry X
			       GenericP    gclosure)
{
    if (shape_entry_get_non_empty (entry)) {
	debug_info_w_start_usages (shape_entry_key (entry));
	name_table_iter (entry->names, name_entry_write_tld, gclosure);
    }
}

void
shape_entry_write_count PROTO_N ((entry, gclosure))
			PROTO_T (ShapeEntryP entry X
				 GenericP    gclosure)
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
shape_entry_write_links PROTO_N ((entry, gclosure))
			PROTO_T (ShapeEntryP entry X
				 GenericP    gclosure)
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
shape_entry_check_multi_defs PROTO_N ((entry, gclosure))
			     PROTO_T (ShapeEntryP entry X
				      GenericP    gclosure)
{
    NameTableP table = shape_entry_name_table (entry);
    NStringP   key   = shape_entry_key (entry);

    UNUSED (gclosure);
    name_table_iter (table, name_entry_check_multi_defs, (GenericP) key);
}

void
shape_entry_do_lib_count PROTO_N ((entry, gclosure))
			 PROTO_T (ShapeEntryP entry X
				  GenericP    gclosure)
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
shape_entry_do_lib_write PROTO_N ((entry, gclosure))
			 PROTO_T (ShapeEntryP entry X
				  GenericP    gclosure)
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
shape_entry_resolve_undefined PROTO_N ((entry, gclosure))
			      PROTO_T (ShapeEntryP entry X
				       GenericP    gclosure)
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
shape_entry_hide_all_defd PROTO_N ((entry, gclosure))
			  PROTO_T (ShapeEntryP entry X
				   GenericP    gclosure)
{
    NameTableP table = shape_entry_name_table (entry);
    NStringP   shape = shape_entry_key (entry);

    UNUSED (gclosure);
    name_table_iter (table, name_entry_hide_defd, (GenericP) shape);
}

void
shape_entry_suppress_mult PROTO_N ((entry, gclosure))
			  PROTO_T (ShapeEntryP entry X
				   GenericP    gclosure)
{
    NameTableP table = shape_entry_name_table (entry);
    NStringP   shape = shape_entry_key (entry);

    UNUSED (gclosure);
    name_table_iter (table, name_entry_suppress_mult, (GenericP) shape);
}

void
shape_entry_lib_suppress_mult PROTO_N ((entry, gclosure))
			      PROTO_T (ShapeEntryP entry X
				       GenericP    gclosure)
{
    NameTableP table = shape_entry_name_table (entry);
    NStringP   shape = shape_entry_key (entry);

    UNUSED (gclosure);
    name_table_iter (table, name_entry_lib_suppress_mult, (GenericP) shape);
}

void
shape_entry_show_content PROTO_N ((entry, gclosure))
			 PROTO_T (ShapeEntryP entry X
				  GenericP    gclosure)
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
