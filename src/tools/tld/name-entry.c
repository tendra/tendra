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


/*** name-entry.c --- Name table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the name table entry routines used by the TDF
 * linker.
 *
 *** Change Log:
 * $Log: name-entry.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:19  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:24  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:46:35  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:34  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "name-entry.h"
#include "capsule.h"
#include "debug.h"
#include "gen-errors.h"
#include "library.h"
#include "name-table.h"
#include "ostream.h"
#include "shape-entry.h"
#include "shape-table.h"
#include "tdf.h"
#include "unit-table.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

NameEntryP
name_entry_create_direct PROTO_N ((key, shape_entry))
			 PROTO_T (NameKeyP    key X
				  ShapeEntryP shape_entry)
{
    NameEntryP entry = ALLOCATE (NameEntryT);

    entry->next                    = NIL (NameEntryP);
    name_key_copy (&(entry->key), key);
    entry->type                    = NT_DIRECT;
    entry->u.direct.id             = shape_entry_next_id (shape_entry);
    entry->u.direct.use            = 0;
    entry->u.direct.definition     = NIL (CapsuleP);
    entry->u.direct.lib_definition = NIL (LibCapsuleP);
    shape_entry_add_to_list (shape_entry, entry);
    return (entry);
}

NameEntryP
name_entry_create_indirect PROTO_N ((key, indirect))
			   PROTO_T (NameKeyP   key X
				    NameEntryP indirect)
{
    NameEntryP entry = ALLOCATE (NameEntryT);

    entry->next       = NIL (NameEntryP);
    name_key_copy (&(entry->key), key);
    entry->type       = NT_INDIRECT;
    entry->u.indirect = indirect;
    return (entry);
}

NameEntryP
name_entry_create_place PROTO_N ((key))
			PROTO_T (NameKeyP key)
{
    NameEntryP entry = ALLOCATE (NameEntryT);

    entry->next       = NIL (NameEntryP);
    name_key_copy (&(entry->key), key);
    entry->type       = NT_PLACEHOLDER;
    return (entry);
}

void
name_entry_make_direct PROTO_N ((entry, shape_entry))
		       PROTO_T (NameEntryP  entry X
				ShapeEntryP shape_entry)
{
    ASSERT (name_entry_is_place (entry));
    entry->type                    = NT_DIRECT;
    entry->u.direct.id             = shape_entry_next_id (shape_entry);
    entry->u.direct.use            = 0;
    entry->u.direct.definition     = NIL (CapsuleP);
    entry->u.direct.lib_definition = NIL (LibCapsuleP);
    shape_entry_add_to_list (shape_entry, entry);
}

void
name_entry_make_indirect PROTO_N ((entry, indirect))
			 PROTO_T (NameEntryP entry X
				  NameEntryP indirect)
{
    ASSERT (name_entry_is_place (entry));
    entry->type       = NT_INDIRECT;
    entry->u.indirect = indirect;
}

NameEntryP
name_entry_resolve_renames PROTO_N ((entry, shape, report))
			   PROTO_T (NameEntryP entry X
				    NStringP   shape X
				    BoolT      report)
{
    switch (entry->type) EXHAUSTIVE {
      case NT_PLACEHOLDER:
      case NT_DIRECT:
	return (entry);
      case NT_INDIRECT_DONE:
	return (name_entry_get_indirect (entry));
      case NT_INDIRECT_CYCLING:
	if (report) {
	    E_rename_cycle (shape, name_entry_key (entry));
	}
	return (NIL (NameEntryP));
      case NT_INDIRECT:
	entry->type = NT_INDIRECT_CYCLING;
	entry->u.indirect = name_entry_resolve_renames (entry->u.indirect,
							shape, report);
	entry->type = NT_INDIRECT_DONE;
	return (name_entry_get_indirect (entry));
    }
    UNREACHED;
}

NameKeyP
name_entry_key PROTO_N ((entry))
	       PROTO_T (NameEntryP entry)
{
    return (&(entry->key));
}

NameEntryP
name_entry_next PROTO_N ((entry))
		PROTO_T (NameEntryP entry)
{
    return (entry->next);
}

NameEntryP *
name_entry_next_ref PROTO_N ((entry))
		    PROTO_T (NameEntryP entry)
{
    return (&(entry->next));
}

BoolT
name_entry_is_direct PROTO_N ((entry))
		     PROTO_T (NameEntryP entry)
{
    return (entry->type == NT_DIRECT);
}

BoolT
name_entry_is_indirect PROTO_N ((entry))
		       PROTO_T (NameEntryP entry)
{
    return ((entry->type == NT_INDIRECT) ||
	    (entry->type == NT_INDIRECT_CYCLING) ||
	    (entry->type == NT_INDIRECT_DONE));
}

BoolT
name_entry_is_place PROTO_N ((entry))
		    PROTO_T (NameEntryP entry)
{
    return (entry->type == NT_PLACEHOLDER);
}

unsigned
name_entry_id PROTO_N ((entry))
	      PROTO_T (NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    return (entry->u.direct.id);
}

void
name_entry_merge_use PROTO_N ((entry, use))
		     PROTO_T (NameEntryP entry X
			      unsigned   use)
{
    ASSERT (name_entry_is_direct (entry));
    entry->u.direct.use |= use;
}

unsigned
name_entry_get_use PROTO_N ((entry))
		   PROTO_T (NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    return (entry->u.direct.use & (U_DEFD | U_DECD | U_MULT | U_USED));
}

void
name_entry_hide PROTO_N ((entry))
		PROTO_T (NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    entry->u.direct.use |= U_HIDE;
}

void
name_entry_unhide PROTO_N ((entry))
		  PROTO_T (NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    entry->u.direct.use &= ~U_HIDE;
}

BoolT
name_entry_is_hidden PROTO_N ((entry))
		     PROTO_T (NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    return ((entry->u.direct.use & U_HIDE) == U_HIDE);
}

void
name_entry_set_definition PROTO_N ((entry, capsule))
			  PROTO_T (NameEntryP entry X
				   CapsuleP   capsule)
{
    ASSERT (name_entry_is_direct (entry));
    entry->u.direct.definition = capsule;
}

CapsuleP
name_entry_get_definition PROTO_N ((entry))
			  PROTO_T (NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    return (entry->u.direct.definition);
}

void
name_entry_set_lib_definition PROTO_N ((entry, capsule))
			      PROTO_T (NameEntryP  entry X
				       LibCapsuleP capsule)
{
    ASSERT (name_entry_is_direct (entry));
    entry->u.direct.lib_definition = capsule;
}

LibCapsuleP
name_entry_get_lib_definition PROTO_N ((entry))
			      PROTO_T (NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    return (entry->u.direct.lib_definition);
}

NameEntryP
name_entry_list_next PROTO_N ((entry))
		     PROTO_T (NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    return (entry->u.direct.list_next);
}

NameEntryP *
name_entry_list_next_ref PROTO_N ((entry))
			 PROTO_T (NameEntryP entry)
{
    ASSERT (name_entry_is_direct (entry));
    return (&(entry->u.direct.list_next));
}

NameEntryP
name_entry_get_indirect PROTO_N ((entry))
			PROTO_T (NameEntryP entry)
{
    ASSERT (name_entry_is_indirect (entry));
    return (entry->u.indirect);
}

NameEntryP
name_entry_deallocate PROTO_N ((entry))
		      PROTO_T (NameEntryP entry)
{
    NameEntryP next = name_entry_next (entry);

    name_key_destroy (name_entry_key (entry));
    DEALLOCATE (entry);
    return (next);
}

/*--------------------------------------------------------------------------*/

void
name_entry_do_count PROTO_N ((entry, gclosure))
		    PROTO_T (NameEntryP entry X
			     GenericP   gclosure)
{
    unsigned *count_ref = (unsigned *) gclosure;

    if (!(name_entry_is_hidden (entry))) {
	(*count_ref) ++;
    }
}

void
name_entry_write_name PROTO_N ((entry, gclosure))
		      PROTO_T (NameEntryP entry X
			       GenericP   gclosure)
{
    if (!(name_entry_is_hidden (entry))) {
	TDFWriterP writer = (TDFWriterP) gclosure;
	NameKeyP   key    = name_entry_key (entry);
	unsigned   id     = name_entry_id (entry);

	debug_info_w_name (key, id);
	tdf_write_int (writer, id);
	tdf_write_name (writer, key);
    }
}

void
name_entry_compute_tld_size PROTO_N ((entry, gclosure))
			    PROTO_T (NameEntryP entry X
				     GenericP   gclosure)
{
    unsigned *size_ref = (unsigned *) gclosure;

    if (!name_entry_is_hidden (entry)) {
	unsigned use = name_entry_get_use (entry);

	(*size_ref) += tdf_int_size (use);
    }
}

void
name_entry_write_tld PROTO_N ((entry, gclosure))
		     PROTO_T (NameEntryP entry X
			      GenericP   gclosure)
{
    TDFWriterP writer = (TDFWriterP) gclosure;

    if (!(name_entry_is_hidden (entry))) {
	unsigned use = name_entry_get_use (entry);

	debug_info_w_usage (use, name_entry_key (entry));
	tdf_write_int (writer, use);
    }
}

void
name_entry_check_multi_defs PROTO_N ((entry, gclosure))
			    PROTO_T (NameEntryP entry X
				     GenericP   gclosure)
{
    NStringP shape_name = (NStringP) gclosure;

    if ((name_entry_get_use (entry) & U_MULT) &&
	(name_entry_get_definition (entry) == NIL (CapsuleP))) {
	E_no_single_definition (shape_name, name_entry_key (entry));
    }
}

void
name_entry_do_lib_count PROTO_N ((entry, gclosure))
			PROTO_T (NameEntryP entry X
				 GenericP   gclosure)
{
    if (name_entry_get_definition (entry)) {
	unsigned *num_names_ref = (unsigned *) gclosure;

	(*num_names_ref) ++;
    }
}

void
name_entry_do_lib_write PROTO_N ((entry, gclosure))
			PROTO_T (NameEntryP entry X
				 GenericP   gclosure)
{
    CapsuleP definition = name_entry_get_definition (entry);

    if (definition) {
	TDFWriterP writer        = (TDFWriterP) gclosure;
	NameKeyP   key           = name_entry_key (entry);
	unsigned   use           = name_entry_get_use (entry);
	unsigned   capsule_index = capsule_get_index (definition);

	debug_info_w_index_entry (key, use, capsule_name (definition),
				  capsule_index);
	tdf_write_name (writer, key);
	tdf_write_int (writer, use);
	tdf_write_int (writer, capsule_index);
    }
}

void
name_entry_suppress PROTO_N ((entry, gclosure))
		    PROTO_T (NameEntryP entry X
			     GenericP   gclosure)
{
    NStringP shape = (NStringP) gclosure;

    debug_info_l_suppress (shape, name_entry_key (entry));
    name_entry_set_lib_definition (entry, NIL (LibCapsuleP));
}

void
name_entry_builder_suppress PROTO_N ((entry, gclosure))
			    PROTO_T (NameEntryP entry X
				     GenericP   gclosure)
{
    NStringP shape = (NStringP) gclosure;

    debug_info_l_suppress (shape, name_entry_key (entry));
    name_entry_set_definition (entry, NIL (CapsuleP));
}

BoolT
name_entry_resolve_undefined PROTO_N ((entry, table, units, shapes, shape_key))
			     PROTO_T (NameEntryP  entry X
				      NameTableP  table X
				      UnitTableP  units X
				      ShapeTableP shapes X
				      NStringP    shape_key)
{
    unsigned use = name_entry_get_use (entry);
    NameKeyP key = name_entry_key (entry);

    if ((use & U_DEFD) || (!(use & U_USED))) {
	debug_info_l_not_needed (key, shape_key, use);
	return (FALSE);
    } else if (table) {
	NameEntryP lib_entry = name_table_get (table, key);

	if (lib_entry) {
	    LibCapsuleP lib_def = name_entry_get_lib_definition (lib_entry);
	    unsigned    lib_use = name_entry_get_use (lib_entry);

	    if (lib_def && (!lib_capsule_is_loaded (lib_def)) &&
		((!(use & U_MULT)) || (lib_use & U_DEFD))) {
		CStringP name     = lib_capsule_full_name (lib_def);
		NStringP contents = lib_capsule_contents (lib_def);
		CapsuleP capsule;

		debug_info_l_found (key, shape_key, use, name);
		capsule = capsule_create_string_input (name, contents);
		capsule_read (capsule, units, shapes);
		capsule_close (capsule);
		lib_capsule_loaded (lib_def);
		return (TRUE);
	    }
	}
    }
    E_no_definition_found (shape_key, key);
    debug_info_l_not_found (key, shape_key, use);
    return (FALSE);
}

void
name_entry_hide_defd PROTO_N ((entry, gclosure))
		     PROTO_T (NameEntryP entry X
			      GenericP   gclosure)
{
    if (name_entry_get_use (entry) & U_DEFD) {
	NStringP shape = (NStringP) gclosure;

	debug_info_l_hide (shape, name_entry_key (entry));
	name_entry_hide (entry);
    }
}

void
name_entry_keep PROTO_N ((entry, gclosure))
		PROTO_T (NameEntryP entry X
			 GenericP   gclosure)
{
    NStringP shape = (NStringP) gclosure;

    debug_info_l_keep (shape, name_entry_key (entry));
    name_entry_unhide (entry);
}

void
name_entry_suppress_mult PROTO_N ((entry, gclosure))
			 PROTO_T (NameEntryP entry X
				  GenericP   gclosure)
{
    if ((name_entry_get_use (entry) & (U_DEFD | U_MULT)) == U_MULT) {
	NStringP shape = (NStringP) gclosure;

	debug_info_l_suppress (shape, name_entry_key (entry));
	name_entry_set_definition (entry, NIL (CapsuleP));
    }
}

void
name_entry_lib_suppress_mult PROTO_N ((entry, gclosure))
			     PROTO_T (NameEntryP entry X
				      GenericP   gclosure)
{
    if ((name_entry_get_use (entry) & (U_DEFD | U_MULT)) == U_MULT) {
	NStringP shape = (NStringP) gclosure;

	debug_info_l_suppress (shape, name_entry_key (entry));
	name_entry_set_lib_definition (entry, NIL (LibCapsuleP));
    }
}

void
name_entry_show_content PROTO_N ((entry, gclosure))
			PROTO_T (NameEntryP entry X
				 GenericP   gclosure)
{
    LibCapsuleP capsule = name_entry_get_lib_definition (entry);

    UNUSED (gclosure);
    write_cstring (ostream_output, "  ");
    write_name_key (ostream_output, name_entry_key (entry));
    write_char (ostream_output, ' ');
    write_usage (ostream_output, name_entry_get_use (entry));
    write_cstring (ostream_output, " '");
    write_cstring (ostream_output, lib_capsule_name (capsule));
    write_char (ostream_output, '\'');
    write_newline (ostream_output);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
