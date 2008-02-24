/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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


/*
 * linker.c - Front end to linking mode of TDF linker.
 *
 * This file provides the front end to the linking mode of the TDF linker.
 */

#include <stdlib.h>

#include "linker.h"
#include "../adt/capsule.h"
#include "../debug.h"
#include <exds/common.h>
#include <exds/error.h>
#include "../file-name.h"
#include "../gen-errors.h"
#include "../adt/library.h"
#include "../adt/shape-table.h"
#include "../tdf.h"
#include "../adt/unit-table.h"

#include "../adt/solve-cycles.h"

typedef struct RenameClosureT {
    ShapeTableT *		shapes;
    ShapeTableT *		lib_shapes;
} RenameClosureT;

static void
linker_rename_1(NStringT *        shape,			 NameKeyPairListT *names, 
			 void *         gclosure)
{
    RenameClosureT *       closure    = (RenameClosureT *)gclosure;
    ShapeTableT *          shapes     = closure->shapes;
    ShapeTableT *          lib_shapes = closure->lib_shapes;
    ShapeEntryT *          entry      = shape_table_add(shapes, shape);
    ShapeEntryT *          lib_entry  = shape_table_add(lib_shapes, shape);
    NameTableT *           table      = shape_entry_name_table(entry);
    NameTableT *           lib_table  = shape_entry_name_table(lib_entry);
    NameKeyPairListEntryT *name       = name_key_pair_list_head(names);

    for (; name; name = name_key_pair_list_entry_next(name)) {
	NameKeyT *from = name_key_pair_list_entry_from(name);
	NameKeyT *to   = name_key_pair_list_entry_to(name);

	debug_info_l_rename(shape, from, to);
	name_table_add_rename(table, from, to);
	name_table_add_rename(lib_table, from, to);
    }
    name_table_resolve_renames(table, shape, TRUE);
    name_table_resolve_renames(lib_table, shape, FALSE);
}

static void
linker_rename(ArgDataT *   arg_data,		       ShapeTableT *shapes, 
		       ShapeTableT *lib_shapes)
{
    RenameClosureT closure;

    closure.shapes     = shapes;
    closure.lib_shapes = lib_shapes;
    rename_control_iter(arg_data_get_renames(arg_data), linker_rename_1,
			(void *) &closure);
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}

static void
linker_read_capsules(ArgDataT *   arg_data,			      UnitTableT * units, 
			      ShapeTableT *shapes)
{
    unsigned  num_input_files = arg_data_get_num_files(arg_data);
    char * *input_files     = arg_data_get_files(arg_data);
    unsigned  i;

    for (i = 0; i < num_input_files; i++) {
	CapsuleT *capsule;

	if ((capsule = capsule_create_stream_input(input_files[i])) !=
	    NIL(CapsuleT *)) {
	    capsule_read(capsule, units, shapes);
	    capsule_close(capsule);
	} else {
	    E_cannot_open_input_file(input_files[i]);
	}
    }
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}

static void
linker_load_libraries(ArgDataT *   arg_data,			       ShapeTableT *lib_shapes)
{
    char *   *files     = arg_data_library_files(arg_data);
    char *   *paths     = arg_data_library_paths(arg_data);
    unsigned    num_files = arg_data_num_library_files(arg_data);
    unsigned    num_paths = arg_data_num_library_paths(arg_data);
    unsigned    i;

    for (i = 0; i < num_files; i++) {
	LibraryT *library = NIL(LibraryT *);

	if (file_name_is_basename(files[i])) {
	    unsigned j;

	    for (j = 0; j < num_paths; j++) {
		char * name = file_name_expand(paths[j], files[i], "tl");

		if ((library = library_create_stream_input(name)) !=
		    NIL(LibraryT *)) {
		    goto found;
		} else {
		    DEALLOCATE(name);
		}
	    }
	    E_cannot_open_library_file(files[i]);
	} else {
	    if ((library = library_create_stream_input(files[i])) ==
		NIL(LibraryT *)) {
		E_cannot_open_library_file(files[i]);
	    }
	}
      found:
	if (library) {
	    library_read(library, lib_shapes);
	    library_close(library);
	}
    }
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}

static void
linker_suppress_1(NStringT *    shape,			   BoolT        all, 
			   NameKeyListT *names, 
			   void *     gclosure)
{
    ShapeTableT *lib_shapes = (ShapeTableT *)gclosure;
    ShapeEntryT *entry      = shape_table_get(lib_shapes, shape);

    if (entry) {
	NameTableT *       table = shape_entry_name_table(entry);
	NameKeyListEntryT *name  = name_key_list_head(names);

	if (all) {
	    name_table_iter(table, name_entry_suppress,(void *)shape);
	}
	for (; name; name = name_key_list_entry_next(name)) {
	    NameKeyT *  key        = name_key_list_entry_key(name);
	    NameEntryT *name_entry = name_table_get(table, key);

	    if (name_entry) {
		debug_info_l_suppress(shape, key);
		name_entry_set_lib_definition(name_entry, NIL(LibCapsuleT *));
	    }
	}
    }
}

static void
linker_suppress(ArgDataT *   arg_data,			 ShapeTableT *lib_shapes)
{
    if (arg_data_get_suppress_mult(arg_data)) {
	shape_table_iter(lib_shapes, shape_entry_lib_suppress_mult,
			  NIL(void *));
    }
    shape_control_iter(arg_data_get_suppresses(arg_data), linker_suppress_1,
			(void *)lib_shapes);
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}

static void
linker_resolve_undefined(UnitTableT * units,				  ShapeTableT *shapes, 
				  ShapeTableT *lib_shapes)
{
    ShapeLibClosureT closure;

    closure.lib_shapes = lib_shapes;
    closure.units      = units;
    closure.shapes     = shapes;
    do {
	closure.did_define = FALSE;
	shape_table_iter(shapes, shape_entry_resolve_undefined,
			 (void *) &closure);
    } while (closure.did_define);
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}

static void
linker_hide(NStringT *    shape,		     BoolT        all, 
		     NameKeyListT *names, 
		     void *     gclosure)
{
    ShapeTableT *shapes = (ShapeTableT *)gclosure;
    ShapeEntryT *entry  = shape_table_get(shapes, shape);

    if (entry == NIL(ShapeEntryT *)) {
	E_cannot_hide_shape(shape);
    } else {
	NameTableT *       table = shape_entry_name_table(entry);
	NameKeyListEntryT *name  = name_key_list_head(names);

	if (all) {
	    name_table_iter(table, name_entry_hide_defd,(void *)shape);
	}
	for (; name; name = name_key_list_entry_next(name)) {
	    NameKeyT *  key        = name_key_list_entry_key(name);
	    NameEntryT *name_entry = name_table_get(table, key);

	    if (name_entry == NIL(NameEntryT *)) {
		E_cannot_hide(shape, key);
	    } else if (name_entry_get_use(name_entry) & U_DEFD) {
		debug_info_l_hide(shape, key);
		name_entry_hide(name_entry);
	    } else {
		E_cannot_hide_undefined(shape, key);
	    }
	}
    }
}

static void
linker_keep(NStringT *    shape,		     BoolT        all, 
		     NameKeyListT *names, 
		     void *     gclosure)
{
    ShapeTableT *shapes = (ShapeTableT *)gclosure;
    ShapeEntryT *entry  = shape_table_get(shapes, shape);

    if (entry == NIL(ShapeEntryT *)) {
	E_cannot_keep_shape(shape);
    } else {
	NameTableT *       table = shape_entry_name_table(entry);
	NameKeyListEntryT *name  = name_key_list_head(names);

	if (all) {
	    name_table_iter(table, name_entry_keep,(void *)shape);
	}
	for (; name; name = name_key_list_entry_next(name)) {
	    NameKeyT *  key        = name_key_list_entry_key(name);
	    NameEntryT *name_entry = name_table_get(table, key);

	    if (name_entry == NIL(NameEntryT *)) {
		E_cannot_keep(shape, key);
	    } else {
		debug_info_l_keep(shape, key);
		name_entry_unhide(name_entry);
	    }
	}
    }
}

static void
linker_hide_and_keep(ArgDataT *   arg_data,			      ShapeTableT *shapes)
{
    if (arg_data_get_all_hide_defd(arg_data)) {
	shape_table_iter(shapes, shape_entry_hide_all_defd, NIL(void *));
    }
    shape_control_iter(arg_data_get_hides(arg_data), linker_hide,
			(void *)shapes);
    shape_control_iter(arg_data_get_keeps(arg_data), linker_keep,
			(void *)shapes);
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}

static void
linker_write_capsule(ArgDataT *   arg_data,			      UnitTableT * units, 
			      ShapeTableT *shapes)
{
    char * output_file = arg_data_get_output_file(arg_data);
    CapsuleT *capsule;

    if ((capsule = capsule_create_stream_output(output_file)) !=
	NIL(CapsuleT *)) {
	capsule_write(capsule, units, shapes);
	capsule_close(capsule);
    } else {
	E_cannot_open_output_file(output_file);
	UNREACHED;
    }
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}

void
linker_main(ArgDataT *arg_data)
{
    UnitTableT * units      = unit_table_create();
    ShapeTableT *shapes     = shape_table_create();
    ShapeTableT *lib_shapes = shape_table_create();

    linker_rename(arg_data, shapes, lib_shapes);
    linker_read_capsules(arg_data, units, shapes);
    linker_load_libraries(arg_data, lib_shapes);
    linker_suppress(arg_data, lib_shapes);
    linker_resolve_undefined(units, shapes, lib_shapes);
    linker_hide_and_keep(arg_data, shapes);
    linker_write_capsule(arg_data, units, shapes);
}

