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


/**** linker.c --- Front end to linking mode of TDF linker.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file provides the front end to the linking mode of the TDF linker.
 *
 **** Change Log:
 * $Log: linker.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:16  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:37:11  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 *
 * Revision 1.2  1994/12/12  11:44:06  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:26  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "linker.h"
#include "capsule.h"
#include "debug.h"
#include "error.h"
#include "file-name.h"
#include "gen-errors.h"
#include "library.h"
#include "shape-table.h"
#include "tdf.h"
#include "unit-table.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

typedef struct RenameClosureT {
    ShapeTableP			shapes;
    ShapeTableP			lib_shapes;
} RenameClosureT, *RenameClosureP;

/*--------------------------------------------------------------------------*/

static void
linker_rename_1 PROTO_N ((shape, names, gclosure))
		PROTO_T (NStringP         shape X
			 NameKeyPairListP names X
			 GenericP         gclosure)
{
    RenameClosureP        closure    = (RenameClosureP) gclosure;
    ShapeTableP           shapes     = closure->shapes;
    ShapeTableP           lib_shapes = closure->lib_shapes;
    ShapeEntryP           entry      = shape_table_add (shapes, shape);
    ShapeEntryP           lib_entry  = shape_table_add (lib_shapes, shape);
    NameTableP            table      = shape_entry_name_table (entry);
    NameTableP            lib_table  = shape_entry_name_table (lib_entry);
    NameKeyPairListEntryP name       = name_key_pair_list_head (names);

    for (; name; name = name_key_pair_list_entry_next (name)) {
	NameKeyP from = name_key_pair_list_entry_from (name);
	NameKeyP to   = name_key_pair_list_entry_to (name);

	debug_info_l_rename (shape, from, to);
	name_table_add_rename (table, from, to);
	name_table_add_rename (lib_table, from, to);
    }
    name_table_resolve_renames (table, shape, TRUE);
    name_table_resolve_renames (lib_table, shape, FALSE);
}

static void
linker_rename PROTO_N ((arg_data, shapes, lib_shapes))
	      PROTO_T (ArgDataP    arg_data X
		       ShapeTableP shapes X
		       ShapeTableP lib_shapes)
{
    RenameClosureT closure;

    closure.shapes     = shapes;
    closure.lib_shapes = lib_shapes;
    rename_control_iter (arg_data_get_renames (arg_data), linker_rename_1,
			 (GenericP) &closure);
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
	exit (EXIT_FAILURE);
	UNREACHED;
    }
}

static void
linker_read_capsules PROTO_N ((arg_data, units, shapes))
		     PROTO_T (ArgDataP    arg_data X
			      UnitTableP  units X
			      ShapeTableP shapes)
{
    unsigned  num_input_files = arg_data_get_num_files (arg_data);
    CStringP *input_files     = arg_data_get_files (arg_data);
    unsigned  i;

    for (i = 0; i < num_input_files; i ++) {
	CapsuleP capsule;

	if ((capsule = capsule_create_stream_input (input_files [i])) !=
	    NIL (CapsuleP)) {
	    capsule_read (capsule, units, shapes);
	    capsule_close (capsule);
	} else {
	    E_cannot_open_input_file (input_files [i]);
	}
    }
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
	exit (EXIT_FAILURE);
	UNREACHED;
    }
}

static void
linker_load_libraries PROTO_N ((arg_data, lib_shapes))
		      PROTO_T (ArgDataP    arg_data X
			       ShapeTableP lib_shapes)
{
    CStringP   *files     = arg_data_library_files (arg_data);
    CStringP   *paths     = arg_data_library_paths (arg_data);
    unsigned    num_files = arg_data_num_library_files (arg_data);
    unsigned    num_paths = arg_data_num_library_paths (arg_data);
    unsigned    i;

    for (i = 0; i < num_files; i ++) {
	LibraryP library = NIL (LibraryP);

	if (file_name_is_basename (files [i])) {
	    unsigned j;

	    for (j = 0; j < num_paths; j ++) {
		CStringP name = file_name_expand (paths [j], files [i], "tl");

		if ((library = library_create_stream_input (name)) !=
		    NIL (LibraryP)) {
		    goto found;
		} else {
		    DEALLOCATE (name);
		}
	    }
	    E_cannot_open_library_file (files [i]);
	} else {
	    if ((library = library_create_stream_input (files [i])) ==
		NIL (LibraryP)) {
		E_cannot_open_library_file (files [i]);
	    }
	}
      found:
	if (library) {
	    library_read (library, lib_shapes);
	    library_close (library);
	}
    }
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
	exit (EXIT_FAILURE);
	UNREACHED;
    }
}

static void
linker_suppress_1 PROTO_N ((shape, all, names, gclosure))
		  PROTO_T (NStringP     shape X
			   BoolT        all X
			   NameKeyListP names X
			   GenericP     gclosure)
{
    ShapeTableP lib_shapes = (ShapeTableP) gclosure;
    ShapeEntryP entry      = shape_table_get (lib_shapes, shape);

    if (entry) {
	NameTableP        table = shape_entry_name_table (entry);
	NameKeyListEntryP name  = name_key_list_head (names);

	if (all) {
	    name_table_iter (table, name_entry_suppress, (GenericP) shape);
	}
	for (; name; name = name_key_list_entry_next (name)) {
	    NameKeyP   key        = name_key_list_entry_key (name);
	    NameEntryP name_entry = name_table_get (table, key);

	    if (name_entry) {
		debug_info_l_suppress (shape, key);
		name_entry_set_lib_definition (name_entry, NIL (LibCapsuleP));
	    }
	}
    }
}

static void
linker_suppress PROTO_N ((arg_data, lib_shapes))
		PROTO_T (ArgDataP    arg_data X
			 ShapeTableP lib_shapes)
{
    if (arg_data_get_suppress_mult (arg_data)) {
	shape_table_iter (lib_shapes, shape_entry_lib_suppress_mult,
			  NIL (GenericP));
    }
    shape_control_iter (arg_data_get_suppresses (arg_data), linker_suppress_1,
			(GenericP) lib_shapes);
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
	exit (EXIT_FAILURE);
	UNREACHED;
    }
}

static void
linker_resolve_undefined PROTO_N ((units, shapes, lib_shapes))
			 PROTO_T (UnitTableP  units X
				  ShapeTableP shapes X
				  ShapeTableP lib_shapes)
{
    ShapeLibClosureT closure;

    closure.lib_shapes = lib_shapes;
    closure.units      = units;
    closure.shapes     = shapes;
    do {
	closure.did_define = FALSE;
	shape_table_iter (shapes, shape_entry_resolve_undefined,
			  (GenericP) &closure);
    } while (closure.did_define);
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
	exit (EXIT_FAILURE);
	UNREACHED;
    }
}

static void
linker_hide PROTO_N ((shape, all, names, gclosure))
	    PROTO_T (NStringP     shape X
		     BoolT        all X
		     NameKeyListP names X
		     GenericP     gclosure)
{
    ShapeTableP shapes = (ShapeTableP) gclosure;
    ShapeEntryP entry  = shape_table_get (shapes, shape);

    if (entry == NIL (ShapeEntryP)) {
	E_cannot_hide_shape (shape);
    } else {
	NameTableP        table = shape_entry_name_table (entry);
	NameKeyListEntryP name  = name_key_list_head (names);

	if (all) {
	    name_table_iter (table, name_entry_hide_defd, (GenericP) shape);
	}
	for (; name; name = name_key_list_entry_next (name)) {
	    NameKeyP   key        = name_key_list_entry_key (name);
	    NameEntryP name_entry = name_table_get (table, key);

	    if (name_entry == NIL (NameEntryP)) {
		E_cannot_hide (shape, key);
	    } else if (name_entry_get_use (name_entry) & U_DEFD) {
		debug_info_l_hide (shape, key);
		name_entry_hide (name_entry);
	    } else {
		E_cannot_hide_undefined (shape, key);
	    }
	}
    }
}

static void
linker_keep PROTO_N ((shape, all, names, gclosure))
	    PROTO_T (NStringP     shape X
		     BoolT        all X
		     NameKeyListP names X
		     GenericP     gclosure)
{
    ShapeTableP shapes = (ShapeTableP) gclosure;
    ShapeEntryP entry  = shape_table_get (shapes, shape);

    if (entry == NIL (ShapeEntryP)) {
	E_cannot_keep_shape (shape);
    } else {
	NameTableP        table = shape_entry_name_table (entry);
	NameKeyListEntryP name  = name_key_list_head (names);

	if (all) {
	    name_table_iter (table, name_entry_keep, (GenericP) shape);
	}
	for (; name; name = name_key_list_entry_next (name)) {
	    NameKeyP   key        = name_key_list_entry_key (name);
	    NameEntryP name_entry = name_table_get (table, key);

	    if (name_entry == NIL (NameEntryP)) {
		E_cannot_keep (shape, key);
	    } else {
		debug_info_l_keep (shape, key);
		name_entry_unhide (name_entry);
	    }
	}
    }
}

static void
linker_hide_and_keep PROTO_N ((arg_data, shapes))
		     PROTO_T (ArgDataP    arg_data X
			      ShapeTableP shapes)
{
    if (arg_data_get_all_hide_defd (arg_data)) {
	shape_table_iter (shapes, shape_entry_hide_all_defd, NIL (GenericP));
    }
    shape_control_iter (arg_data_get_hides (arg_data), linker_hide,
			(GenericP) shapes);
    shape_control_iter (arg_data_get_keeps (arg_data), linker_keep,
			(GenericP) shapes);
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
	exit (EXIT_FAILURE);
	UNREACHED;
    }
}

static void
linker_write_capsule PROTO_N ((arg_data, units, shapes))
		     PROTO_T (ArgDataP    arg_data X
			      UnitTableP  units X
			      ShapeTableP shapes)
{
    CStringP output_file = arg_data_get_output_file (arg_data);
    CapsuleP capsule;

    if ((capsule = capsule_create_stream_output (output_file)) !=
	NIL (CapsuleP)) {
	capsule_write (capsule, units, shapes);
	capsule_close (capsule);
    } else {
	E_cannot_open_output_file (output_file);
	UNREACHED;
    }
    if (error_max_reported_severity () >= ERROR_SEVERITY_ERROR) {
	exit (EXIT_FAILURE);
	UNREACHED;
    }
}

/*--------------------------------------------------------------------------*/

void
linker_main PROTO_N ((arg_data))
	    PROTO_T (ArgDataP arg_data)
{
    UnitTableP  units      = unit_table_create ();
    ShapeTableP shapes     = shape_table_create ();
    ShapeTableP lib_shapes = shape_table_create ();

    linker_rename (arg_data, shapes, lib_shapes);
    linker_read_capsules (arg_data, units, shapes);
    linker_load_libraries (arg_data, lib_shapes);
    linker_suppress (arg_data, lib_shapes);
    linker_resolve_undefined (units, shapes, lib_shapes);
    linker_hide_and_keep (arg_data, shapes);
    linker_write_capsule (arg_data, units, shapes);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library" "../tdf")
 * eval: (include::add-path-entry "../generated")
 * End:
**/
