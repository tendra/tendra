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


/**** arg-data.c --- Command line argument data ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the ADT that stores the information on the various
 * command line options that were given to the TDF linker.
 *
 **** Change Log:*/

/****************************************************************************/

#include "arg-data.h"
#include "capsule.h"
#include "msgcat.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

static void
shape_control_init(ShapeControlP control)
{
    control->head = NIL (ShapeControlEntryP);
}

static ShapeControlEntryP
shape_control_find(ShapeControlP control,
				   char *shape)
{
    NStringT           nstring;
    ShapeControlEntryP entry;

    nstring_copy_cstring (&nstring, shape);
    for (entry = control->head; entry; entry = entry->next) {
		if (nstring_equal (&nstring, &(entry->shape))) {
			nstring_destroy (&nstring);
			return (entry);
		}
    }
    entry             = ALLOCATE (ShapeControlEntryT);
    entry->next       = control->head;
    nstring_assign (&(entry->shape), &nstring);
    entry->all        = FALSE;
    name_key_list_init (&(entry->names));
    control->head     = entry;
    return (entry);
}

static void
shape_control_entry_add_name(ShapeControlEntryP entry,
							 char *name)
{
    NameKeyT key;

    if (name_key_parse_cstring (&key, name)) {
		name_key_list_add (&(entry->names), &key);
    } else {
		MSG_illegal_external_name (name);
    }
}

static void
shape_control_entry_set(ShapeControlEntryP entry)
{
    entry->all = TRUE;
}

/*--------------------------------------------------------------------------*/

static void
rename_control_init(RenameControlP control)
{
    control->head = NIL (RenameControlEntryP);
}

static RenameControlEntryP
rename_control_find(RenameControlP control,
					NStringP shape)
{
    RenameControlEntryP entry;

    for (entry = control->head; entry; entry = entry->next) {
		if (nstring_equal (shape, &(entry->shape))) {
			return (entry);
		}
    }
    entry             = ALLOCATE (RenameControlEntryT);
    entry->next       = control->head;
    nstring_copy (&(entry->shape), shape);
    name_key_pair_list_init (&(entry->names));
    control->head     = entry;
    return (entry);
}

static NameKeyPairListP
rename_control_entry_names(RenameControlEntryP entry)
{
    return (&(entry->names));
}

static void
rename_control_entry_parse_pair(RenameControlEntryP entry,
								char *from,
								char *to)
{
    NStringP shape = &(entry->shape);
    NameKeyT from_key;
    NameKeyT to_key;

    if (!name_key_parse_cstring (&from_key, from)) {
		MSG_illegal_external_name (from);
    } else if (!name_key_parse_cstring (&to_key, to)) {
		MSG_illegal_external_name (to);
    } else if (!name_key_pair_list_add (&(entry->names), &from_key, &to_key)) {
		MSG_multiply_renamed_name (shape, &from_key);
		name_key_destroy (&from_key);
		name_key_destroy (&to_key);
    }
}

/*--------------------------------------------------------------------------*/

void
shape_control_iter(ShapeControlP control,
				   void (*proc)(NStringP, BoolT, NameKeyListP, GenericP),
				   GenericP closure)
{
    ShapeControlEntryP entry;

    for (entry = control->head; entry; entry = entry->next) {
		(*proc) (&(entry->shape), entry->all, &(entry->names), closure);
    }
}

void
rename_control_iter(RenameControlP control,
					void (*proc)(NStringP, NameKeyPairListP, GenericP),
					GenericP closure)
{
    RenameControlEntryP entry;

    for (entry = control->head; entry; entry = entry->next) {
		(*proc) (&(entry->shape), &(entry->names), closure);
    }
}

/*--------------------------------------------------------------------------*/

void
arg_data_init(ArgDataP arg_data, char *default_output_file)
{
    arg_data->all_hide_defined    = FALSE;
    arg_data->suppress_mult       = FALSE;
    shape_control_init (&(arg_data->hides));
    shape_control_init (&(arg_data->keeps));
    shape_control_init (&(arg_data->suppresses));
    rename_control_init (&(arg_data->renames));
    arg_data->extract_all         = FALSE;
    arg_data->extract_basename    = FALSE;
    arg_data->extract_match_base  = FALSE;
    arg_data->content_index       = FALSE;
    arg_data->content_size        = FALSE;
    arg_data->content_version     = FALSE;
    ostream_init (&(arg_data->debug_file));
    arg_data->default_output_file = default_output_file;
    arg_data->output_file         = NULL;
    arg_data->num_library_files   = 0;
    arg_data->num_library_paths   = 0;
    cstring_list_init (&arg_data->library.list.file);
    cstring_list_init (&(arg_data->library.list.path));
    arg_data->unit_file           = NULL;
    arg_data->num_files           = 0;
}

void
arg_data_set_all_hide_defd(ArgDataP arg_data,
						   BoolT enable)
{
    arg_data->all_hide_defined = enable;
}

BoolT
arg_data_get_all_hide_defd(ArgDataP arg_data)
{
    return (arg_data->all_hide_defined);
}

void
arg_data_set_suppress_mult(ArgDataP arg_data,
						   BoolT enable)
{
    arg_data->suppress_mult = enable;
}

BoolT
arg_data_get_suppress_mult(ArgDataP arg_data)
{
    return (arg_data->suppress_mult);
}

void
arg_data_add_hide(ArgDataP arg_data, char *shape,
				  char *name)
{
    ShapeControlEntryP entry = shape_control_find (&(arg_data->hides), shape);

    shape_control_entry_add_name (entry, name);
}

void
arg_data_add_hide_defined(ArgDataP arg_data,
						  char *shape)
{
    ShapeControlEntryP entry = shape_control_find (&(arg_data->hides), shape);

    shape_control_entry_set (entry);
}

ShapeControlP
arg_data_get_hides(ArgDataP arg_data)
{
    return (&(arg_data->hides));
}

void
arg_data_add_keep(ArgDataP arg_data, char *shape,
				  char *name)
{
    ShapeControlEntryP entry = shape_control_find (&(arg_data->keeps), shape);

    shape_control_entry_add_name (entry, name);
}

void
arg_data_add_keep_all(ArgDataP arg_data, char *shape)
{
    ShapeControlEntryP entry = shape_control_find (&(arg_data->keeps), shape);

    shape_control_entry_set (entry);
}

ShapeControlP
arg_data_get_keeps(ArgDataP arg_data)
{
    return (&(arg_data->keeps));
}

void
arg_data_add_suppress(ArgDataP arg_data, char *shape,
					  char *name)
{
    ShapeControlEntryP entry = shape_control_find (&(arg_data->suppresses),
												   shape);

    shape_control_entry_add_name (entry, name);
}

void
arg_data_add_suppress_all(ArgDataP arg_data,
						  char *shape)
{
    ShapeControlEntryP entry = shape_control_find (&(arg_data->suppresses),
												   shape);

    shape_control_entry_set (entry);
}

ShapeControlP
arg_data_get_suppresses(ArgDataP arg_data)
{
    return (&(arg_data->suppresses));
}

void
arg_data_add_rename(ArgDataP arg_data, NStringP shape,
					NameKeyP from, NameKeyP to)
{
    RenameControlEntryP entry;
    NameKeyPairListP    names;

    entry = rename_control_find (&(arg_data->renames), shape);
    names = rename_control_entry_names (entry);
    if (!name_key_pair_list_add (names, from, to)) {
		MSG_multiply_renamed_name (shape, from);
		name_key_destroy (from);
		name_key_destroy (to);
    }
}

void
arg_data_parse_rename(ArgDataP arg_data, char *shape,
					  char *from, char *to)
{
    NStringT            nstring;
    RenameControlEntryP entry;

    nstring_copy_cstring (&nstring, shape);
    entry = rename_control_find (&(arg_data->renames), &nstring);
    nstring_destroy (&nstring);
    rename_control_entry_parse_pair (entry, from, to);
}

RenameControlP
arg_data_get_renames(ArgDataP arg_data)
{
    return (&(arg_data->renames));
}

void
arg_data_set_extract_all(ArgDataP arg_data,
						 BoolT enable)
{
    arg_data->extract_all = enable;
}

BoolT
arg_data_get_extract_all(ArgDataP arg_data)
{
    return (arg_data->extract_all);
}

void
arg_data_set_extract_basename(ArgDataP arg_data,
							  BoolT enable)
{
    arg_data->extract_basename = enable;
}

BoolT
arg_data_get_extract_basename(ArgDataP arg_data)
{
    return (arg_data->extract_basename);
}

void
arg_data_set_extract_match_base(ArgDataP arg_data,
								BoolT enable)
{
    arg_data->extract_match_base = enable;
}

BoolT
arg_data_get_extract_match_base(ArgDataP arg_data)
{
    return (arg_data->extract_match_base);
}

void
arg_data_set_content_index(ArgDataP arg_data,
						   BoolT enable)
{
    arg_data->content_index = enable;
}

BoolT
arg_data_get_content_index(ArgDataP arg_data)
{
    return (arg_data->content_index);
}

void
arg_data_set_content_size(ArgDataP arg_data,
						  BoolT enable)
{
    arg_data->content_size = enable;
}

BoolT
arg_data_get_content_size(ArgDataP arg_data)
{
    return (arg_data->content_size);
}

void
arg_data_set_content_version(ArgDataP arg_data,
							 BoolT enable)
{
    arg_data->content_version = enable;
}

BoolT
arg_data_get_content_version(ArgDataP arg_data)
{
    return (arg_data->content_version);
}

void
arg_data_set_debug_file(ArgDataP arg_data,
						char *debug_file)
{
    if (ostream_is_open (&(arg_data->debug_file))) {
		MSG_tld_multiple_debug_files ();
		UNREACHED;
    }
    if (!ostream_open (&(arg_data->debug_file), debug_file)) {
		MSG_tld_cannot_open_debug_file (debug_file);
		UNREACHED;
    }
}

OStreamP
arg_data_get_debug_file(ArgDataP arg_data)
{
    return (&(arg_data->debug_file));
}

void
arg_data_set_output_file(ArgDataP arg_data,
						 char *output_file)
{
    if (arg_data->output_file) {
		MSG_tld_multiple_output_files ();
		UNREACHED;
    }
    arg_data->output_file = output_file;
}

char *
arg_data_get_output_file(ArgDataP arg_data)
{
    if (arg_data->output_file) {
		return (arg_data->output_file);
    } else {
		return (arg_data->default_output_file);
    }
}

void
arg_data_add_library_file(ArgDataP arg_data,
						  char *library_file)
{
    CStringListP libraries = &(arg_data->library.list.file);
    if (!cstring_list_contains (libraries, library_file)) {
		arg_data->num_library_files ++;
		cstring_list_append (libraries, library_file);
    }
}

void
arg_data_add_library_path(ArgDataP arg_data,
						  char *directory)
{
    arg_data->num_library_paths ++;
    cstring_list_append (&(arg_data->library.list.path), directory);
}

void
arg_data_vector_libraries(ArgDataP arg_data)
{
    unsigned          num_files = arg_data->num_library_files;
    unsigned          num_paths = arg_data->num_library_paths;
    char *        *files     = ALLOCATE_VECTOR (char *, num_files);
    char *        *paths     = ALLOCATE_VECTOR (char *, num_paths);
    CStringListEntryP entry;
    unsigned          i;

    for (i = 0, entry = cstring_list_head (&(arg_data->library.list.file));
		 i < num_files; i ++, entry = cstring_list_entry_deallocate (entry)) {
		files [i] = cstring_list_entry_string (entry);
    }
    for (i = 0, entry = cstring_list_head (&(arg_data->library.list.path));
		 i < num_paths; i ++, entry = cstring_list_entry_deallocate (entry)) {
		paths [i] = cstring_list_entry_string (entry);
    }
    arg_data->library.vector.file = files;
    arg_data->library.vector.path = paths;
}

unsigned
arg_data_num_library_files(ArgDataP arg_data)
{
    return (arg_data->num_library_files);
}

unsigned
arg_data_num_library_paths(ArgDataP arg_data)
{
    return (arg_data->num_library_paths);
}

char **
arg_data_library_files(ArgDataP arg_data)
{
    return (arg_data->library.vector.file);
}

char **
arg_data_library_paths(ArgDataP arg_data)
{
    return (arg_data->library.vector.path);
}

void
arg_data_set_unit_file(ArgDataP arg_data,
					   char *unit_file)
{
    if (arg_data->unit_file) {
		MSG_tld_multiple_unit_files ();
		UNREACHED;
    }
    arg_data->unit_file = unit_file;
    capsule_read_unit_set_file (unit_file);
}

void
arg_data_set_files(ArgDataP arg_data, int num_files,
				   char **files)
{
    arg_data->num_files = (unsigned) num_files;
    arg_data->files     = files;
}

unsigned
arg_data_get_num_files(ArgDataP arg_data)
{
    return (arg_data->num_files);
}

char **
arg_data_get_files(ArgDataP arg_data)
{
    return (arg_data->files);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library" "../tdf")
 * eval: (include::add-path-entry "../generated")
 * End:
 **/
