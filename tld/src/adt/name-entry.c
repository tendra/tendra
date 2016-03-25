/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * name-entry.c - Name table entry ADT.
 *
 * This file implements the name table entry routines used by the TDF
 * linker.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/error.h>
#include <shared/check.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/ostream.h>

#include "name-entry.h"
#include "capsule.h"
#include "library.h"
#include "name-table.h"
#include "unit-table.h"
#include "solve-cycles.h"
#include "shape-entry.h"
#include "shape-table.h"
#include "tdf.h"
#include "debug.h"


NameEntryT *
name_entry_create_direct(NameKeyT *   key,				  ShapeEntryT *shape_entry)
{
    NameEntryT *entry = ALLOCATE(NameEntryT);

    entry->next                    = NULL;
    name_key_copy(& (entry->key), key);
    entry->type                    = NT_DIRECT;
    entry->u.direct.id             = shape_entry_next_id(shape_entry);
    entry->u.direct.use            = 0;
    entry->u.direct.definition     = NULL;
    entry->u.direct.lib_definition = NULL;
    shape_entry_add_to_list(shape_entry, entry);
    return entry;
}

NameEntryT *
name_entry_create_indirect(NameKeyT *  key,				    NameEntryT *indirect)
{
    NameEntryT *entry = ALLOCATE(NameEntryT);

    entry->next       = NULL;
    name_key_copy(& (entry->key), key);
    entry->type       = NT_INDIRECT;
    entry->u.indirect = indirect;
    return entry;
}

NameEntryT *
name_entry_create_place(NameKeyT *key)
{
    NameEntryT *entry = ALLOCATE(NameEntryT);

    entry->next       = NULL;
    name_key_copy(& (entry->key), key);
    entry->type       = NT_PLACEHOLDER;
    return entry;
}

void
name_entry_make_direct(NameEntryT * entry,				ShapeEntryT *shape_entry)
{
    assert(name_entry_is_place(entry));
    entry->type                    = NT_DIRECT;
    entry->u.direct.id             = shape_entry_next_id(shape_entry);
    entry->u.direct.use            = 0;
    entry->u.direct.definition     = NULL;
    entry->u.direct.lib_definition = NULL;
    shape_entry_add_to_list(shape_entry, entry);
}

void
name_entry_make_indirect(NameEntryT *entry,				  NameEntryT *indirect)
{
    assert(name_entry_is_place(entry));
    entry->type       = NT_INDIRECT;
    entry->u.indirect = indirect;
}

NameEntryT *
name_entry_resolve_renames(NameEntryT *entry,				    NStringT *  shape, 
				    bool      report)
{
    switch (entry->type) {
      case NT_PLACEHOLDER:
      case NT_DIRECT:
	return entry;
      case NT_INDIRECT_DONE:
	return name_entry_get_indirect(entry);
      case NT_INDIRECT_CYCLING:
	if (report) {
		error(ERR_SERIOUS,"cycle in %S renaming including name '%K'",
			(void *) shape, (void *) name_entry_key(entry));
	}
	return NULL;
      case NT_INDIRECT:
	entry->type = NT_INDIRECT_CYCLING;
	entry->u.indirect = name_entry_resolve_renames(entry->u.indirect,
							shape, report);
	entry->type = NT_INDIRECT_DONE;
	return name_entry_get_indirect(entry);
    }
    UNREACHED;
}

NameKeyT *
name_entry_key(NameEntryT *entry)
{
    return &entry->key;
}

NameEntryT *
name_entry_next(NameEntryT *entry)
{
    return entry->next;
}

NameEntryT **
name_entry_next_ref(NameEntryT *entry)
{
    return &entry->next;
}

bool
name_entry_is_direct(NameEntryT *entry)
{
    return entry->type == NT_DIRECT;
}

bool
name_entry_is_indirect(NameEntryT *entry)
{
    return entry->type == NT_INDIRECT ||
	   entry->type == NT_INDIRECT_CYCLING ||
	   entry->type == NT_INDIRECT_DONE;
}

bool
name_entry_is_place(NameEntryT *entry)
{
    return entry->type == NT_PLACEHOLDER;
}

unsigned
name_entry_id(NameEntryT *entry)
{
    assert(name_entry_is_direct(entry));
    return entry->u.direct.id;
}

void
name_entry_merge_use(NameEntryT *entry,			      unsigned   use)
{
    assert(name_entry_is_direct(entry));
    entry->u.direct.use |= use;
}

unsigned
name_entry_get_use(NameEntryT *entry)
{
    assert(name_entry_is_direct(entry));
    return entry->u.direct.use & (U_DEFD | U_DECD | U_MULT | U_USED);
}

void
name_entry_hide(NameEntryT *entry)
{
    assert(name_entry_is_direct(entry));
    entry->u.direct.use |= U_HIDE;
}

void
name_entry_unhide(NameEntryT *entry)
{
    assert(name_entry_is_direct(entry));
    entry->u.direct.use &= ~U_HIDE;
}

bool
name_entry_is_hidden(NameEntryT *entry)
{
    assert(name_entry_is_direct(entry));
    return (entry->u.direct.use & U_HIDE) == U_HIDE;
}

void
name_entry_set_definition(NameEntryT *entry,				   CapsuleT *  capsule)
{
    assert(name_entry_is_direct(entry));
    entry->u.direct.definition = capsule;
}

CapsuleT *
name_entry_get_definition(NameEntryT *entry)
{
    assert(name_entry_is_direct(entry));
    return entry->u.direct.definition;
}

void
name_entry_set_lib_definition(NameEntryT * entry,				       LibCapsuleT *capsule)
{
    assert(name_entry_is_direct(entry));
    entry->u.direct.lib_definition = capsule;
}

LibCapsuleT *
name_entry_get_lib_definition(NameEntryT *entry)
{
    assert(name_entry_is_direct(entry));
    return entry->u.direct.lib_definition;
}

NameEntryT *
name_entry_list_next(NameEntryT *entry)
{
    assert(name_entry_is_direct(entry));
    return entry->u.direct.list_next;
}

NameEntryT **
name_entry_list_next_ref(NameEntryT *entry)
{
    assert(name_entry_is_direct(entry));
    return &entry->u.direct.list_next;
}

NameEntryT *
name_entry_get_indirect(NameEntryT *entry)
{
    assert(name_entry_is_indirect(entry));
    return entry->u.indirect;
}

NameEntryT *
name_entry_deallocate(NameEntryT *entry)
{
    NameEntryT *next = name_entry_next(entry);

    name_key_destroy(name_entry_key(entry));
    DEALLOCATE(entry);
    return next;
}

void
name_entry_do_count(NameEntryT *entry,			     void *   gclosure)
{
    unsigned *count_ref = (unsigned *)gclosure;

    if (!(name_entry_is_hidden(entry))) {
	(*count_ref)++;
    }
}

void
name_entry_write_name(NameEntryT *entry,			       void *   gclosure)
{
    if (!(name_entry_is_hidden(entry))) {
	TDFWriterT *writer = (TDFWriterT *)gclosure;
	NameKeyT *  key    = name_entry_key(entry);
	unsigned   id     = name_entry_id(entry);

	debug_info_w_name(key, id);
	tdf_write_int(writer, id);
	tdf_write_name(writer, key);
    }
}

void
name_entry_compute_tld_size(NameEntryT *entry,				     void *   gclosure)
{
    size_t *size_ref = gclosure;

    if (!name_entry_is_hidden(entry)) {
	unsigned use = name_entry_get_use(entry);

	(*size_ref) += tdf_int_size(use);
    }
}

void
name_entry_write_tld(NameEntryT *entry,			      void *   gclosure)
{
    TDFWriterT *writer = (TDFWriterT *)gclosure;

    if (!(name_entry_is_hidden(entry))) {
	unsigned use = name_entry_get_use(entry);

	debug_info_w_usage(use, name_entry_key(entry));
	tdf_write_int(writer, use);
    }
}

void
name_entry_check_multi_defs(NameEntryT *entry,				     void *   gclosure)
{
    NStringT *shape_name = (NStringT *)gclosure;

    if ((name_entry_get_use(entry) & U_MULT) &&
	(name_entry_get_definition(entry) == NULL)) {
	error(ERR_SERIOUS,"no single definition for %S '%K'",
		(void *) shape_name, (void *) name_entry_key(entry));
    }
}

void
name_entry_do_lib_count(NameEntryT *entry,				 void *   gclosure)
{
    if (name_entry_get_definition(entry)) {
	unsigned *num_names_ref = (unsigned *)gclosure;

	(*num_names_ref)++;
    }
}

void
name_entry_do_lib_write(NameEntryT *entry,				 void *   gclosure)
{
    CapsuleT *definition = name_entry_get_definition(entry);

    if (definition) {
	TDFWriterT *writer        = (TDFWriterT *)gclosure;
	NameKeyT *  key           = name_entry_key(entry);
	unsigned   use           = name_entry_get_use(entry);
	unsigned   capsule_index = capsule_get_index(definition);

	debug_info_w_index_entry(key, use, capsule_name(definition),
				  capsule_index);
	tdf_write_name(writer, key);
	tdf_write_int(writer, use);
	tdf_write_int(writer, capsule_index);
    }
}

void
name_entry_suppress(NameEntryT *entry,			     void *   gclosure)
{
    NStringT *shape = (NStringT *)gclosure;

    debug_info_l_suppress(shape, name_entry_key(entry));
    name_entry_set_lib_definition(entry, NULL);
}

void
name_entry_builder_suppress(NameEntryT *entry,				     void *   gclosure)
{
    NStringT *shape = (NStringT *)gclosure;

    debug_info_l_suppress(shape, name_entry_key(entry));
    name_entry_set_definition(entry, NULL);
}

bool
name_entry_resolve_undefined(NameEntryT * entry,				      NameTableT * table, 
				      UnitTableT * units, 
				      ShapeTableT *shapes, 
				      NStringT *   shape_key,
				      bool     missing_definitions)
{
    unsigned use = name_entry_get_use(entry);
    NameKeyT *key = name_entry_key(entry);

    if ((use & U_DEFD) || (!(use & U_USED))) {
	debug_info_l_not_needed(key, shape_key, use);
	return false;
    } else if (table) {
	NameEntryT *lib_entry = name_table_get(table, key);

	if (lib_entry) {
	    LibCapsuleT *lib_def = name_entry_get_lib_definition(lib_entry);
	    unsigned    lib_use = name_entry_get_use(lib_entry);

	    if (lib_def && (!lib_capsule_is_loaded(lib_def)) &&
		((!(use & U_MULT)) || (lib_use & U_DEFD))) {
		char * name     = lib_capsule_full_name(lib_def);
		NStringT *contents = lib_capsule_contents(lib_def);
		CapsuleT *capsule;

		debug_info_l_found(key, shape_key, use, name);
		capsule = capsule_create_string_input(name, contents);
		capsule_read(capsule, units, shapes);
		capsule_close(capsule);
		lib_capsule_loaded(lib_def);
		return true;
	    }
	}
    }
    if (missing_definitions) {
	error(ERR_WARN,"no definition found for %S '%K'",
		(void *) shape_key,(void *) key);
    }
    debug_info_l_not_found(key, shape_key, use);
    return false;
}

void
name_entry_hide_defd(NameEntryT *entry,			      void *   gclosure)
{
    if (name_entry_get_use(entry) & U_DEFD) {
	NStringT *shape = (NStringT *)gclosure;

	debug_info_l_hide(shape, name_entry_key(entry));
	name_entry_hide(entry);
    }
}

void
name_entry_keep(NameEntryT *entry,			 void *   gclosure)
{
    NStringT *shape = (NStringT *)gclosure;

    debug_info_l_keep(shape, name_entry_key(entry));
    name_entry_unhide(entry);
}

void
name_entry_suppress_mult(NameEntryT *entry,				  void *   gclosure)
{
    if ((name_entry_get_use(entry) & (U_DEFD | U_MULT)) == U_MULT) {
	NStringT *shape = (NStringT *)gclosure;

	debug_info_l_suppress(shape, name_entry_key(entry));
	name_entry_set_definition(entry, NULL);
    }
}

void
name_entry_lib_suppress_mult(NameEntryT *entry,				      void *   gclosure)
{
    if ((name_entry_get_use(entry) & (U_DEFD | U_MULT)) == U_MULT) {
	NStringT *shape = (NStringT *)gclosure;

	debug_info_l_suppress(shape, name_entry_key(entry));
	name_entry_set_lib_definition(entry, NULL);
    }
}

void
name_entry_show_content(NameEntryT *entry,				 void *   gclosure)
{
    LibCapsuleT *capsule = name_entry_get_lib_definition(entry);

    UNUSED(gclosure);
    write_cstring(ostream_output, "  ");
    write_name_key(ostream_output, name_entry_key(entry));
    write_char(ostream_output, ' ');
    write_usage(ostream_output, name_entry_get_use(entry));
    write_cstring(ostream_output, " '");
    write_cstring(ostream_output, lib_capsule_name(capsule));
    write_char(ostream_output, '\'');
    write_newline(ostream_output);
}
