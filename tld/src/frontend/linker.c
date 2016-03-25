/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * linker.c - Front end to linking mode of TDF linker.
 *
 * This file provides the front end to the linking mode of the TDF linker.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <exds/common.h>
#include <exds/error.h>

#include "adt/capsule.h"
#include "adt/library.h"
#include "adt/shape-table.h"
#include "adt/unit-table.h"
#include "adt/solve-cycles.h"
#include "adt/arg-data.h"

#include "debug.h"
#include "file-name.h"
#include "tdf.h"


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
    name_table_resolve_renames(table, shape, true);
    name_table_resolve_renames(lib_table, shape, false);
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
	    NULL) {
	    capsule_read(capsule, units, shapes);
	    capsule_close(capsule);
	} else {
		error(ERR_SERIOUS, "cannot open input file '%s': %s", 
			input_files[i], strerror(errno));
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
    const char *   *files     = arg_data_library_files(arg_data);
    const char *   *paths     = arg_data_library_paths(arg_data);
    unsigned    num_files = arg_data_num_library_files(arg_data);
    unsigned    num_paths = arg_data_num_library_paths(arg_data);
    unsigned    i;

    for (i = 0; i < num_files; i++) {
	LibraryT *library = NULL;

	if (file_name_is_basename(files[i])) {
	    unsigned j;

	    for (j = 0; j < num_paths; j++) {
		char * name = file_name_expand(paths[j], files[i], "tl");

		if ((library = library_create_stream_input(name)) !=
		    NULL) {
		    goto found;
		} else {
		    DEALLOCATE(name);
		}
	    }
		error(ERR_SERIOUS, "cannot open library file '%s': %s", 
			files[i], strerror(errno));
	} else {
	    if ((library = library_create_stream_input(files[i])) ==
		NULL) {
		error(ERR_SERIOUS, "cannot open library file '%s': %s", 
			files[i], strerror(errno));
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
linker_suppress_1(NStringT *    shape,			   bool        all, 
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
		name_entry_set_lib_definition(name_entry, NULL);
	    }
	}
    }
}

static void
linker_suppress(ArgDataT *   arg_data,			 ShapeTableT *lib_shapes)
{
    if (arg_data_get_suppress_mult(arg_data)) {
	shape_table_iter(lib_shapes, shape_entry_lib_suppress_mult,
			  NULL);
    }
    shape_control_iter(arg_data_get_suppresses(arg_data), linker_suppress_1,
			(void *)lib_shapes);
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}

static void
linker_resolve_undefined(ArgDataT *   arg_data,
				  UnitTableT * units,				  ShapeTableT *shapes, 
				  ShapeTableT *lib_shapes)
{
    ShapeLibClosureT closure;

    closure.lib_shapes          = lib_shapes;
    closure.units               = units;
    closure.shapes              = shapes;
    closure.missing_definitions = arg_data_get_missing_definitions(arg_data);
    do {
	closure.did_define = false;
	shape_table_iter(shapes, shape_entry_resolve_undefined,
			 (void *) &closure);
    } while (closure.did_define);
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}

static void
linker_hide(NStringT *    shape,		     bool        all, 
		     NameKeyListT *names, 
		     void *     gclosure)
{
    ShapeTableT *shapes = (ShapeTableT *)gclosure;
    ShapeEntryT *entry  = shape_table_get(shapes, shape);

    if (entry == NULL) {
	error(ERR_SERIOUS,"there are no external %S names to hide", (void *) shape);
    } else {
	NameTableT *       table = shape_entry_name_table(entry);
	NameKeyListEntryT *name  = name_key_list_head(names);

	if (all) {
	    name_table_iter(table, name_entry_hide_defd,(void *)shape);
	}
	for (; name; name = name_key_list_entry_next(name)) {
	    NameKeyT *  key        = name_key_list_entry_key(name);
	    NameEntryT *name_entry = name_table_get(table, key);

	    if (name_entry == NULL) {
		error(ERR_SERIOUS,"there is no external %S named "
		"'%K' to hide", (void *) shape, (void *) key);
	    } else if (name_entry_get_use(name_entry) & U_DEFD) {
		debug_info_l_hide(shape, key);
		name_entry_hide(name_entry);
	    } else {
		error(ERR_SERIOUS,"cannot hide undefined external %S named "
			"'%K'", (void *) shape, (void *) key);
	    }
	}
    }
}

static void
linker_keep(NStringT *    shape,		     bool        all, 
		     NameKeyListT *names, 
		     void *     gclosure)
{
    ShapeTableT *shapes = (ShapeTableT *)gclosure;
    ShapeEntryT *entry  = shape_table_get(shapes, shape);

    if (entry == NULL) {
	error(ERR_SERIOUS,"there are no external %S names to keep",
		(void *) shape);
    } else {
	NameTableT *       table = shape_entry_name_table(entry);
	NameKeyListEntryT *name  = name_key_list_head(names);

	if (all) {
	    name_table_iter(table, name_entry_keep,(void *)shape);
	}
	for (; name; name = name_key_list_entry_next(name)) {
	    NameKeyT *  key        = name_key_list_entry_key(name);
	    NameEntryT *name_entry = name_table_get(table, key);

	    if (name_entry == NULL) {
		error(ERR_SERIOUS,"there is no external %S named "
			"'%K' to keep",
			(void *) shape, (void *) key);
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
	shape_table_iter(shapes, shape_entry_hide_all_defd, NULL);
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
	NULL) {
	capsule_write(capsule, units, shapes);
	capsule_close(capsule);
    } else {
	error(ERR_FATAL, "cannot open output file '%s': %s", 
		output_file, strerror(errno));
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
    linker_resolve_undefined(arg_data, units, shapes, lib_shapes);
    linker_hide_and_keep(arg_data, shapes);
    linker_write_capsule(arg_data, units, shapes);
}
