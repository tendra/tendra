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


/**** builder.c --- Front end to library construction mode of TDF linker.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file provides the front end to the library construction mode of the
 * TDF linker.
 *
 **** Change Log:
 * $Log: builder.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:16  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:37:01  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 *
 * Revision 1.2  1994/12/12  11:43:56  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:23  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include <string.h>

#include "builder.h"
#include "capsule.h"
#include "debug.h"
#include <exds/common.h>
#include <exds/error.h>
#include "gen-errors.h"
#include "library.h"
#include "shape-table.h"
#include "unit-table.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

static LibraryT **
builder_read_libraries(ArgDataT * arg_data,				unsigned *num_libs_ref ,
				unsigned *num_capsules_ref)
{
    unsigned  num_lib_files   = arg_data_num_library_files(arg_data);
    char * *lib_files       = arg_data_library_files(arg_data);
    LibraryT **libraries       = ALLOCATE_VECTOR(LibraryT *, num_lib_files);
    unsigned  num_capsules    = 0;
    unsigned  i;

    for (i = 0; i < num_lib_files; i++) {
	LibraryT *library = library_create_stream_input(lib_files[i]);

	if (library != NIL(LibraryT *)) {
	    ShapeTableT *lib_shapes = shape_table_create();

	    library_read(library, lib_shapes);
	    library_close(library);
	    libraries[i] = library;
	    num_capsules += library_num_capsules(library);
	    shape_table_deallocate(lib_shapes);
	} else {
	    libraries[i] = NIL(LibraryT *);
	    E_cannot_open_input_file(lib_files[i]);
	}
    }
    *num_libs_ref = num_lib_files;
    *num_capsules_ref = num_capsules;
    return(libraries);
}

static void
builder_read_capsule(CapsuleT *capsule, CapsuleT **capsules,
		     unsigned capsule_index, UnitTableT *units,
		     ShapeTableT *shapes)
{
    char * name = capsule_name(capsule);
    unsigned i;

    for (i = 0; i < capsule_index; i++) {
	if (!strcmp(name, capsule_name(capsules[i]))) {
	    E_duplicate_capsule_name(name);
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

	if (library != NIL(LibraryT *)) {
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
	    NIL(CapsuleT *)) {
	    builder_read_capsule(capsule, capsules, capsule_index, units,
				  shapes);
	    capsule_index++;
	} else {
	    E_cannot_open_input_file(input_files[i]);
	}
    }
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
    *num_capsules_ref = num_capsules;
    return(capsules);
}

static void
builder_check_multi_defs(ShapeTableT *shapes)
{
    shape_table_iter(shapes, shape_entry_check_multi_defs, NIL(void *));
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
		name_entry_set_definition(name_entry, NIL(CapsuleT *));
	    }
	}
    }
}

static void
builder_suppress(ArgDataT *   arg_data,			  ShapeTableT *lib_shapes)
{
    if (arg_data_get_suppress_mult(arg_data)) {
	shape_table_iter(lib_shapes, shape_entry_suppress_mult,
			  NIL(void *));
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
	NIL(LibraryT *)) {
	library_write(library, shapes, num_capsules, capsules);
	library_close(library);
    } else {
	E_cannot_open_output_file(output_file);
	UNREACHED;
    }
    if (error_max_reported_severity() >= ERROR_SEVERITY_ERROR) {
	exit(EXIT_FAILURE);
	UNREACHED;
    }
}

/*--------------------------------------------------------------------------*/

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

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library" "../tdf")
 * eval: (include::add-path-entry "../generated")
 * End:
**/
