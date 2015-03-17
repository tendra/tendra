/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * builder.c - Front end to library construction mode of TDF linker.
 *
 * This file provides the front end to the library construction mode of the
 * TDF linker.
 */

#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <exds/common.h>
#include <exds/error.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>

#include "adt/library.h"
#include "adt/shape-table.h"
#include "adt/unit-table.h"
#include "adt/solve-cycles.h"
#include "adt/capsule.h"
#include "adt/arg-data.h"

#include "debug.h"

static LibraryT **
builder_read_libraries(ArgDataT * arg_data,				unsigned *num_libs_ref ,
				unsigned *num_capsules_ref)
{
    unsigned  num_lib_files   = arg_data_num_library_files(arg_data);
    const char * *lib_files       = arg_data_library_files(arg_data);
    LibraryT **libraries       = ALLOCATE_VECTOR(LibraryT *, num_lib_files);
    unsigned  num_capsules    = 0;
    unsigned  i;

    for (i = 0; i < num_lib_files; i++) {
	LibraryT *library = library_create_stream_input(lib_files[i]);

	if (library != NULL) {
	    ShapeTableT *lib_shapes = shape_table_create();

	    library_read(library, lib_shapes);
	    library_close(library);
	    libraries[i] = library;
	    num_capsules += library_num_capsules(library);
	    shape_table_deallocate(lib_shapes);
	} else {
	    libraries[i] = NULL;
		error(ERR_SERIOUS, "cannot open input file '%s': %s", 
			lib_files[i], strerror(errno));
	}
    }
    *num_libs_ref = num_lib_files;
    *num_capsules_ref = num_capsules;
    return libraries;
}

static void
builder_read_capsule(CapsuleT *capsule, CapsuleT **capsules,
		     unsigned capsule_index, UnitTableT *units,
		     ShapeTableT *shapes)
{
    char * name = capsule_name(capsule);
    unsigned i;

    for (i = 0; i < capsule_index; i++) {
	if (streq(name, capsule_name(capsules[i]))) {
	    error(ERR_SERIOUS, "capsule name '%s' occurs more than "
		"once in input capsule list", 
		name);
	}
    }
    capsule_set_index(capsule, capsule_index);
    capsule_read(capsule, units, shapes);
    capsule_store_contents(capsule);
    capsule_close(capsule);
    capsules[capsule_index] = capsule;
}

static CapsuleT **
builder_read_capsules(ArgDataT *   arg_data,			       UnitTableT * units ,
			       ShapeTableT *shapes ,
			       unsigned   *num_capsules_ref)
{
    unsigned  num_input_files = arg_data_get_num_files(arg_data);
    char * *input_files     = arg_data_get_files(arg_data);
    unsigned  capsule_index   = 0;
    unsigned  num_libraries;
    LibraryT **libraries;
    unsigned  num_capsules;
    CapsuleT **capsules;
    unsigned  i;

    libraries     = builder_read_libraries(arg_data, &num_libraries,
					    &num_capsules);
    num_capsules += num_input_files;
    capsules      = ALLOCATE_VECTOR(CapsuleT *, num_capsules);
    for (i = 0; i < num_libraries; i++) {
	LibraryT *library = libraries[i];

	if (library != NULL) {
	    unsigned num_lib_capsules = library_num_capsules(library);
	    unsigned j;

	    for (j = 0; j < num_lib_capsules; j++) {
		LibCapsuleT *lib_capsule = library_get_capsule(library, j);
		char *    name        = lib_capsule_name(lib_capsule);
		NStringT *   contents    = lib_capsule_contents(lib_capsule);
		CapsuleT *   capsule;

		capsule = capsule_create_string_input(name, contents);
		builder_read_capsule(capsule, capsules, capsule_index,
				      units, shapes);
		capsule_index++;
	    }
	}
    }
    DEALLOCATE(libraries);
    for (i = 0; i < num_input_files; i++) {
	CapsuleT *capsule;

	if ((capsule = capsule_create_stream_input(input_files[i])) !=
	    NULL) {
	    builder_read_capsule(capsule, capsules, capsule_index, units,
				  shapes);
	    capsule_index++;
	} else {
		error(ERR_SERIOUS, "cannot open input file '%s': %s", 
			input_files[i], strerror(errno));
	}
    }
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
    *num_capsules_ref = num_capsules;
    return capsules;
}

static void
builder_check_multi_defs(ShapeTableT *shapes)
{
    shape_table_iter(shapes, shape_entry_check_multi_defs, NULL);
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}

static void
builder_suppress_1(NStringT *    shape,			    BoolT        all ,
			    NameKeyListT *names ,
			    void *     gclosure)
{
    ShapeTableT *lib_shapes = (ShapeTableT *)gclosure;
    ShapeEntryT *entry      = shape_table_get(lib_shapes, shape);

    if (entry) {
	NameTableT *       table = shape_entry_name_table(entry);
	NameKeyListEntryT *name  = name_key_list_head(names);

	if (all) {
	    name_table_iter(table, name_entry_builder_suppress,
			    (void *)shape);
	}
	for (; name; name = name_key_list_entry_next(name)) {
	    NameKeyT *  key        = name_key_list_entry_key(name);
	    NameEntryT *name_entry = name_table_get(table, key);

	    if (name_entry) {
		debug_info_l_suppress(shape, key);
		name_entry_set_definition(name_entry, NULL);
	    }
	}
    }
}

static void
builder_suppress(ArgDataT *   arg_data,			  ShapeTableT *lib_shapes)
{
    if (arg_data_get_suppress_mult(arg_data)) {
	shape_table_iter(lib_shapes, shape_entry_suppress_mult,
			  NULL);
    }
    shape_control_iter(arg_data_get_suppresses(arg_data), builder_suppress_1,
			(void *)lib_shapes);
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}

static void
builder_write_library(ArgDataT *   arg_data,			       ShapeTableT *shapes ,
			       unsigned    num_capsules ,
			       CapsuleT *  *capsules)
{
    char * output_file = arg_data_get_output_file(arg_data);
    LibraryT *library;

    if ((library = library_create_stream_output(output_file)) !=
	NULL) {
	library_write(library, shapes, num_capsules, capsules);
	library_close(library);
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
builder_main(ArgDataT *arg_data)
{
    UnitTableT * units  = unit_table_create();
    ShapeTableT *shapes = shape_table_create();
    unsigned    num_capsules;
    CapsuleT *  *capsules;

    capsules = builder_read_capsules(arg_data, units, shapes, &num_capsules);
    builder_check_multi_defs(shapes);
    builder_suppress(arg_data, shapes);
    builder_write_library(arg_data, shapes, num_capsules, capsules);
}
