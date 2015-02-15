/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * arg-data.c - Command line argument data ADT.
 *
 * This file implements the ADT that stores the information on the various
 * command line options that were given to the TDF linker.
 */

#include <errno.h>
#include <string.h>

#include <shared/error.h>
#include <shared/check.h>

#include "arg-data.h"
#include "capsule.h"
#include "solve-cycles.h"


static void
shape_control_init(ShapeControlT *control)
{
    control->head = NULL;
}

static ShapeControlEntryT *
shape_control_find(ShapeControlT *control,			    char *      shape)
{
    NStringT           nstring;
    ShapeControlEntryT *entry;

    nstring_copy_cstring(&nstring, shape);
    for (entry = control->head; entry; entry = entry->next) {
	if (nstring_equal(&nstring, & (entry->shape))) {
	    nstring_destroy(&nstring);
	    return entry;
	}
    }
    entry             = ALLOCATE(ShapeControlEntryT);
    entry->next       = control->head;
    nstring_assign(& (entry->shape), &nstring);
    entry->all        = FALSE;
    name_key_list_init(& (entry->names));
    control->head     = entry;
    return entry;
}

static void
shape_control_entry_add_name(ShapeControlEntryT *entry,				      char *           name)
{
    NameKeyT key;

    if (name_key_parse_cstring(&key, name)) {
	name_key_list_add(& (entry->names), &key);
    } else {
	error(ERR_SERIOUS, "illegal external name '%s'", name);
    }
}

static void
shape_control_entry_set(ShapeControlEntryT *entry)
{
    entry->all = TRUE;
}

static void
rename_control_init(RenameControlT *control)
{
    control->head = NULL;
}

static RenameControlEntryT *
rename_control_find(RenameControlT *control,			     NStringT *      shape)
{
    RenameControlEntryT *entry;

    for (entry = control->head; entry; entry = entry->next) {
	if (nstring_equal(shape, & (entry->shape))) {
	    return entry;
	}
    }
    entry             = ALLOCATE(RenameControlEntryT);
    entry->next       = control->head;
    nstring_copy(& (entry->shape), shape);
    name_key_pair_list_init(& (entry->names));
    control->head     = entry;
    return entry;
}

static NameKeyPairListT *
rename_control_entry_names(RenameControlEntryT *entry)
{
    return &entry->names;
}

static void
rename_control_entry_parse_pair(RenameControlEntryT *entry,					 char *            from ,
					 char *            to)
{
    NStringT *shape = & (entry->shape);
    NameKeyT from_key;
    NameKeyT to_key;

    if (!name_key_parse_cstring(&from_key, from)) {
	error(ERR_SERIOUS, "illegal external name '%s'", from);
    } else if (!name_key_parse_cstring(&to_key, to)) {
	error(ERR_SERIOUS, "illegal external name '%s'", to);
    } else if (!name_key_pair_list_add(& (entry->names), &from_key, &to_key)) {
	error(ERR_SERIOUS, "%S '%K' is renamed multiple times",
		(void *) shape, (void *) &from_key);
	
	name_key_destroy(&from_key);
	name_key_destroy(&to_key);
    }
}

void
shape_control_iter(ShapeControlT *control,			    void       (*proc)(NStringT *, BoolT,
							  NameKeyListT *,
							  void *),
			    void *      closure)
{
    ShapeControlEntryT *entry;

    for (entry = control->head; entry; entry = entry->next) {
	(*proc)(& (entry->shape), entry->all, & (entry->names), closure);
    }
}

void
rename_control_iter(RenameControlT *control,			     void        (*proc)(NStringT *,
							    NameKeyPairListT *,
							    void *),
			     void *       closure)
{
    RenameControlEntryT *entry;

    for (entry = control->head; entry; entry = entry->next) {
	(*proc)(& (entry->shape), & (entry->names), closure);
    }
}

void
arg_data_init(ArgDataT *arg_data,		       char * default_output_file)
{
    arg_data->all_hide_defined    = FALSE;
    arg_data->suppress_mult       = FALSE;
    shape_control_init(& (arg_data->hides));
    shape_control_init(& (arg_data->keeps));
    shape_control_init(& (arg_data->suppresses));
    rename_control_init(& (arg_data->renames));
    arg_data->extract_all         = FALSE;
    arg_data->extract_basename    = FALSE;
    arg_data->extract_match_base  = FALSE;
    arg_data->content_index       = FALSE;
    arg_data->content_size        = FALSE;
    arg_data->content_version     = FALSE;
    arg_data->missing_definitions = FALSE;
    ostream_init(& (arg_data->debug_file));
    arg_data->default_output_file = default_output_file;
    arg_data->output_file         = NULL;
    arg_data->num_library_files   = 0;
    arg_data->num_library_paths   = 0;
    cstring_list_init(&arg_data->library.list.file);
    cstring_list_init(& (arg_data->library.list.path));
    arg_data->unit_file           = NULL;
    arg_data->num_files           = 0;
}

void
arg_data_set_all_hide_defd(ArgDataT *arg_data,				    BoolT    enable)
{
    arg_data->all_hide_defined = enable;
}

BoolT
arg_data_get_all_hide_defd(ArgDataT *arg_data)
{
    return arg_data->all_hide_defined;
}

void
arg_data_set_suppress_mult(ArgDataT *arg_data,				    BoolT    enable)
{
    arg_data->suppress_mult = enable;
}

BoolT
arg_data_get_suppress_mult(ArgDataT *arg_data)
{
    return arg_data->suppress_mult;
}

void
arg_data_add_hide(ArgDataT *arg_data,			   char * shape ,
			   char * name)
{
    ShapeControlEntryT *entry = shape_control_find(& (arg_data->hides), shape);

    shape_control_entry_add_name(entry, name);
}

void
arg_data_add_hide_defined(ArgDataT *arg_data,				   char * shape)
{
    ShapeControlEntryT *entry = shape_control_find(& (arg_data->hides), shape);

    shape_control_entry_set(entry);
}

ShapeControlT *
arg_data_get_hides(ArgDataT *arg_data)
{
    return &arg_data->hides;
}

void
arg_data_add_keep(ArgDataT *arg_data,			   char * shape ,
			   char * name)
{
    ShapeControlEntryT *entry = shape_control_find(& (arg_data->keeps), shape);

    shape_control_entry_add_name(entry, name);
}

void
arg_data_add_keep_all(ArgDataT *arg_data,			       char * shape)
{
    ShapeControlEntryT *entry = shape_control_find(& (arg_data->keeps), shape);

    shape_control_entry_set(entry);
}

ShapeControlT *
arg_data_get_keeps(ArgDataT *arg_data)
{
    return &arg_data->keeps;
}

void
arg_data_add_suppress(ArgDataT *arg_data,			       char * shape ,
			       char * name)
{
    ShapeControlEntryT *entry = shape_control_find(& (arg_data->suppresses),
						   shape);

    shape_control_entry_add_name(entry, name);
}

void
arg_data_add_suppress_all(ArgDataT *arg_data,				   char * shape)
{
    ShapeControlEntryT *entry = shape_control_find(& (arg_data->suppresses),
						   shape);

    shape_control_entry_set(entry);
}

ShapeControlT *
arg_data_get_suppresses(ArgDataT *arg_data)
{
    return &arg_data->suppresses;
}

void
arg_data_add_rename(ArgDataT *arg_data,			     NStringT *shape ,
			     NameKeyT *from ,
			     NameKeyT *to)
{
    RenameControlEntryT *entry;
    NameKeyPairListT *   names;

    entry = rename_control_find(& (arg_data->renames), shape);
    names = rename_control_entry_names(entry);
    if (!name_key_pair_list_add(names, from, to)) {
	error(ERR_SERIOUS, "%S '%K' is renamed multiple times",
		(void *) shape, (void *) from);
	name_key_destroy(from);
	name_key_destroy(to);
    }
}

void
arg_data_parse_rename(ArgDataT *arg_data,			       char * shape ,
			       char * from ,
			       char * to)
{
    NStringT            nstring;
    RenameControlEntryT *entry;

    nstring_copy_cstring(&nstring, shape);
    entry = rename_control_find(& (arg_data->renames), &nstring);
    nstring_destroy(&nstring);
    rename_control_entry_parse_pair(entry, from, to);
}

RenameControlT *
arg_data_get_renames(ArgDataT *arg_data)
{
    return &arg_data->renames;
}

void
arg_data_set_extract_all(ArgDataT *arg_data,				  BoolT    enable)
{
    arg_data->extract_all = enable;
}

BoolT
arg_data_get_extract_all(ArgDataT *arg_data)
{
    return arg_data->extract_all;
}

void
arg_data_set_extract_basename(ArgDataT *arg_data,				       BoolT    enable)
{
    arg_data->extract_basename = enable;
}

BoolT
arg_data_get_extract_basename(ArgDataT *arg_data)
{
    return arg_data->extract_basename;
}

void
arg_data_set_extract_match_base(ArgDataT *arg_data,					 BoolT    enable)
{
    arg_data->extract_match_base = enable;
}

BoolT
arg_data_get_extract_match_base(ArgDataT *arg_data)
{
    return arg_data->extract_match_base;
}

void
arg_data_set_content_index(ArgDataT *arg_data,				    BoolT    enable)
{
    arg_data->content_index = enable;
}

BoolT
arg_data_get_content_index(ArgDataT *arg_data)
{
    return arg_data->content_index;
}

void
arg_data_set_content_size(ArgDataT *arg_data,				   BoolT    enable)
{
    arg_data->content_size = enable;
}

BoolT
arg_data_get_content_size(ArgDataT *arg_data)
{
    return arg_data->content_size;
}

void
arg_data_set_content_version(ArgDataT *arg_data,				      BoolT    enable)
{
    arg_data->content_version = enable;
}

BoolT
arg_data_get_content_version(ArgDataT *arg_data)
{
    return arg_data->content_version;
}

void
arg_data_set_missing_definitions(ArgDataT *arg_data,				  BoolT    enable)
{
    arg_data->missing_definitions = enable;
}

BoolT
arg_data_get_missing_definitions(ArgDataT *arg_data)
{
    return arg_data->missing_definitions;
}

void
arg_data_set_debug_file(ArgDataT *arg_data,				 char * debug_file)
{
    if (ostream_is_open(& (arg_data->debug_file))) {
	error(ERR_FATAL, "more than one debug file specified");
	UNREACHED;
    }
    if (!ostream_open(& (arg_data->debug_file), debug_file)) {
	error(ERR_FATAL, "cannot open debug file '%s': %s", 
		debug_file, strerror(errno));
	UNREACHED;
    }
}

OStreamT *
arg_data_get_debug_file(ArgDataT *arg_data)
{
    return &arg_data->debug_file;
}

void
arg_data_set_output_file(ArgDataT *arg_data,				  char * output_file)
{
    if (arg_data->output_file) {
	error(ERR_FATAL, "more than one output file specified");
	UNREACHED;
    }
    arg_data->output_file = output_file;
}

char *
arg_data_get_output_file(ArgDataT *arg_data)
{
    if (arg_data->output_file) {
	return arg_data->output_file;
    } else {
	return arg_data->default_output_file;
    }
}

void
arg_data_add_library_file(ArgDataT *arg_data,				   char * library_file)
{
    CStringListT *libraries = & (arg_data->library.list.file);
    if (!cstring_list_contains(libraries, library_file)) {
	arg_data->num_library_files++;
	cstring_list_append(libraries, library_file);
    }
}

void
arg_data_add_library_path(ArgDataT *arg_data,				   char * directory)
{
    arg_data->num_library_paths++;
    cstring_list_append(& (arg_data->library.list.path), directory);
}

void
arg_data_vector_libraries(ArgDataT *arg_data)
{
    unsigned          num_files = arg_data->num_library_files;
    unsigned          num_paths = arg_data->num_library_paths;
    const char *     *files     = ALLOCATE_VECTOR(const char *, num_files);
    const char *     *paths     = ALLOCATE_VECTOR(const char *, num_paths);
    CStringListEntryT *entry;
    unsigned          i;

    for (i = 0, entry = cstring_list_head(& (arg_data->library.list.file));
	 i < num_files; i++, entry = cstring_list_entry_deallocate(entry)) {
	files[i] = cstring_list_entry_string(entry);
    }
    for (i = 0, entry = cstring_list_head(& (arg_data->library.list.path));
	 i < num_paths; i++, entry = cstring_list_entry_deallocate(entry)) {
	paths[i] = cstring_list_entry_string(entry);
    }
    arg_data->library.vector.file = files;
    arg_data->library.vector.path = paths;
}

unsigned
arg_data_num_library_files(ArgDataT *arg_data)
{
    return arg_data->num_library_files;
}

unsigned
arg_data_num_library_paths(ArgDataT *arg_data)
{
    return arg_data->num_library_paths;
}

const char * *
arg_data_library_files(ArgDataT *arg_data)
{
    return arg_data->library.vector.file;
}

const char * *
arg_data_library_paths(ArgDataT *arg_data)
{
    return arg_data->library.vector.path;
}

void
arg_data_set_unit_file(ArgDataT *arg_data,				char * unit_file)
{
    if (arg_data->unit_file) {
	error(ERR_FATAL, "more than one unit set file specified");
	UNREACHED;
    }
    arg_data->unit_file = unit_file;
    capsule_read_unit_set_file(unit_file);
}

void
arg_data_set_files(ArgDataT * arg_data,			    int       num_files ,
			    char * *files)
{
    arg_data->num_files = (unsigned)num_files;
    arg_data->files     = files;
}

unsigned
arg_data_get_num_files(ArgDataT *arg_data)
{
    return arg_data->num_files;
}

char * *
arg_data_get_files(ArgDataT *arg_data)
{
    return arg_data->files;
}
