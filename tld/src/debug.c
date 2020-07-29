/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * debug.c - Debugging routines.
 *
 * This file implements the tracing routines for use with the TDF linker.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>

#include "debug.h"
#include "tdf.h"

#include "adt/solve-cycles.h"

static OStreamT *debug_file   = NULL;

void
debug_set_file(OStreamT *file)
{
    if (ostream_is_open(file)) {
	debug_file = file;
    } else {
	debug_file = NULL;
    }
}

void
debug_info_u_name(NStringT *name)
{
    if (debug_file) {
	write_cstring(debug_file, "Using unit set name '");
	write_nstring(debug_file, name);
	write_char(debug_file, '\'');
	write_newline(debug_file);
    }
}

void
debug_info_r_start_capsule(char * name)
{
    if (debug_file) {
	write_cstring(debug_file, "Reading capsule '");
	write_cstring(debug_file, name);
	write_cstring(debug_file, "':");
	write_newline(debug_file);
    }
}

void
debug_info_r_versions(unsigned major, unsigned minor)
{
    if (debug_file) {
	write_cstring (debug_file, "  Read major version: ");
	write_unsigned(debug_file, major);
	write_cstring (debug_file, "; minor version:");
	write_unsigned(debug_file, minor);
	write_newline (debug_file);
    }
}

void
debug_info_r_start_unit_decs(unsigned num_unit_sets)
{
    if (debug_file) {
	write_cstring(debug_file, "  Reading ");
	write_unsigned(debug_file, num_unit_sets);
	write_cstring(debug_file, " unit set names:");
	write_newline(debug_file);
    }
}

void
debug_info_r_unit_dec(NStringT *name)
{
    if (debug_file) {
	write_cstring(debug_file, "    ");
	write_nstring(debug_file, name);
	write_newline(debug_file);
    }
}

void
debug_info_r_start_shapes(unsigned num_shapes)
{
    if (debug_file) {
	write_cstring(debug_file, "  Reading ");
	write_unsigned(debug_file, num_shapes);
	write_cstring(debug_file, " shape names:");
	write_newline(debug_file);
    }
}

void
debug_info_r_shape(NStringT *name,			    unsigned num_ids)
{
    if (debug_file) {
	write_cstring(debug_file, "    ");
	write_nstring(debug_file, name);
	write_cstring(debug_file, ", ");
	write_unsigned(debug_file, num_ids);
	write_newline(debug_file);
    }
}

void
debug_info_r_start_names(unsigned num_names)
{
    if (debug_file) {
	write_cstring(debug_file, "  Reading ");
	write_unsigned(debug_file, num_names);
	write_cstring(debug_file, " external name categories:");
	write_newline(debug_file);
    }
}

void
debug_info_r_start_shape_names(NStringT *shape,					unsigned num_names)
{
    if (debug_file) {
	write_cstring(debug_file, "    Reading ");
	write_unsigned(debug_file, num_names);
	write_cstring(debug_file, " external ");
	write_nstring(debug_file, shape);
	write_cstring(debug_file, " names:");
	write_newline(debug_file);
    }
}

void
debug_info_r_name(NameKeyT *name,			   unsigned old_id, 
			   unsigned new_id, 
			   NameKeyT *key)
{
    if (debug_file) {
	write_cstring(debug_file, "      ");
	write_name_key(debug_file, name);
	write_cstring(debug_file, ", ");
	write_unsigned(debug_file, old_id);
	write_cstring(debug_file, " -> ");
	write_unsigned(debug_file, new_id);
	write_cstring(debug_file, " (");
	write_name_key(debug_file, key);
	write_char(debug_file, ')');
	write_newline(debug_file);
    }
}

void
debug_info_r_start_unit_sets(unsigned num_unit_sets)
{
    if (debug_file) {
	write_cstring(debug_file, "  Reading ");
	write_unsigned(debug_file, num_unit_sets);
	write_cstring(debug_file, " unit sets:");
	write_newline(debug_file);
    }
}

void
debug_info_r_start_units(NStringT *unit_set,				  unsigned num_units)
{
    if (debug_file) {
	write_cstring(debug_file, "    Reading ");
	write_unsigned(debug_file, num_units);
	write_char(debug_file, ' ');
	write_nstring(debug_file, unit_set);
	write_cstring(debug_file, " units:");
	write_newline(debug_file);
    }
}

void
debug_info_r_start_unit(NStringT *unit_set,				 unsigned unit, 
				 unsigned num_units)
{
    if (debug_file) {
	write_cstring(debug_file, "      Reading ");
	write_nstring(debug_file, unit_set);
	write_cstring(debug_file, " unit ");
	write_unsigned(debug_file, unit);
	write_cstring(debug_file, " of ");
	write_unsigned(debug_file, num_units);
	write_char(debug_file, ':');
	write_newline(debug_file);
    }
}

void
debug_info_r_start_counts(unsigned num_counts)
{
    if (debug_file) {
	write_cstring(debug_file, "        Reading ");
	write_unsigned(debug_file, num_counts);
	write_cstring(debug_file, " counts:");
	write_newline(debug_file);
    }
}

void
debug_info_r_count(unsigned count,			    NStringT *shape)
{
    if (debug_file) {
	write_cstring(debug_file, "          ");
	write_unsigned(debug_file, count);
	write_cstring(debug_file, " (");
	write_nstring(debug_file, shape);
	write_char(debug_file, ')');
	write_newline(debug_file);
    }
}

void
debug_info_r_start_maps(unsigned num_maps)
{
    if (debug_file) {
	write_cstring(debug_file, "        Reading ");
	write_unsigned(debug_file, num_maps);
	write_cstring(debug_file, " mapping categories:");
	write_newline(debug_file);
    }
}

void
debug_info_r_start_shape_maps(NStringT *shape,				       unsigned num_maps)
{
    if (debug_file) {
	write_cstring(debug_file, "          Reading ");
	write_unsigned(debug_file, num_maps);
	write_char(debug_file, ' ');
	write_nstring(debug_file, shape);
	write_cstring(debug_file, " mappings:");
	write_newline(debug_file);
    }
}

void
debug_info_r_map(unsigned internal,			  unsigned old_external, 
			  unsigned new_external)
{
    if (debug_file) {
	write_cstring(debug_file, "            ");
	write_unsigned(debug_file, internal);
	write_cstring(debug_file, ", ");
	write_unsigned(debug_file, old_external);
	write_cstring(debug_file, " -> ");
	write_unsigned(debug_file, new_external);
	write_newline(debug_file);
    }
}

void
debug_info_r_unit_body(size_t size)
{
    if (debug_file) {
	write_cstring(debug_file, "        Reading ");
	write_unsigned(debug_file, (unsigned) size);
	write_cstring(debug_file, " bytes of unit body");
	write_newline(debug_file);
    }
}

void
debug_info_r_tld_version(unsigned version)
{
    if (debug_file) {
	write_cstring(debug_file, "          Reading version ");
	write_unsigned(debug_file, version);
	write_cstring(debug_file, " linker information unit:");
	write_newline(debug_file);
    }
}

void
debug_info_r_start_usages(NStringT *shape,				   unsigned num_names)
{
    if (debug_file) {
	write_cstring(debug_file, "            Reading ");
	write_unsigned(debug_file, num_names);
	write_cstring(debug_file, " external ");
	write_nstring(debug_file, shape);
	write_cstring(debug_file, " name usages:");
	write_newline(debug_file);
    }
}

void
debug_info_r_usage(unsigned use,			    unsigned name_use, 
			    NameKeyT *key)
{
    if (debug_file) {
	write_cstring(debug_file, "              ");
	write_usage(debug_file, use);
	write_cstring(debug_file, " (");
	write_name_key(debug_file, key);
	write_cstring(debug_file, ", ");
	write_usage(debug_file, name_use);
	write_char(debug_file, ')');
	write_newline(debug_file);
    }
}

void
debug_info_r_end_capsule(void)
{
    if (debug_file) {
	write_cstring(debug_file, "Finished reading capsule");
	write_newline(debug_file);
    }
}

void
debug_info_r_abort_capsule(void)
{
    if (debug_file) {
	write_cstring(debug_file, "Aborted reading capsule");
	write_newline(debug_file);
    }
}

void
debug_info_w_start_capsule(char * name)
{
    if (debug_file) {
	write_cstring(debug_file, "Writing capsule '");
	write_cstring(debug_file, name);
	write_cstring(debug_file, "':");
	write_newline(debug_file);
    }
}

void
debug_info_w_versions(unsigned major, unsigned minor)
{
    if (debug_file) {
	write_cstring (debug_file, "  Writing major version: ");
	write_unsigned(debug_file, major);
	write_cstring (debug_file, "; minor version:");
	write_unsigned(debug_file, minor);
	write_newline (debug_file);
    }
}

void
debug_info_w_start_unit_decs(unsigned num_unit_sets)
{
    if (debug_file) {
	write_cstring(debug_file, "  Writing ");
	write_unsigned(debug_file, num_unit_sets);
	write_cstring(debug_file, " unit set names:");
	write_newline(debug_file);
    }
}

void
debug_info_w_unit_dec(NStringT *name)
{
    if (debug_file) {
	write_cstring(debug_file, "    ");
	write_nstring(debug_file, name);
	write_newline(debug_file);
    }
}

void
debug_info_w_start_shapes(unsigned num_shapes)
{
    if (debug_file) {
	write_cstring(debug_file, "  Writing ");
	write_unsigned(debug_file, num_shapes);
	write_cstring(debug_file, " shape names:");
	write_newline(debug_file);
    }
}

void
debug_info_w_shape(NStringT *name,			    unsigned num_ids)
{
    if (debug_file) {
	write_cstring(debug_file, "    ");
	write_nstring(debug_file, name);
	write_cstring(debug_file, ", ");
	write_unsigned(debug_file, num_ids);
	write_newline(debug_file);
    }
}

void
debug_info_w_start_names(unsigned num_names)
{
    if (debug_file) {
	write_cstring(debug_file, "  Writing ");
	write_unsigned(debug_file, num_names);
	write_cstring(debug_file, " external name categories:");
	write_newline(debug_file);
    }
}

void
debug_info_w_start_shape_names(NStringT *shape,					unsigned num_names)
{
    if (debug_file) {
	write_cstring(debug_file, "    Writing ");
	write_unsigned(debug_file, num_names);
	write_cstring(debug_file, " external ");
	write_nstring(debug_file, shape);
	write_cstring(debug_file, " names:");
	write_newline(debug_file);
    }
}

void
debug_info_w_name(NameKeyT *name,			   unsigned id)
{
    if (debug_file) {
	write_cstring(debug_file, "      ");
	write_name_key(debug_file, name);
	write_cstring(debug_file, ", ");
	write_unsigned(debug_file, id);
	write_newline(debug_file);
    }
}

void
debug_info_w_start_unit_sets(unsigned num_unit_sets)
{
    if (debug_file) {
	write_cstring(debug_file, "  Writing ");
	write_unsigned(debug_file, num_unit_sets);
	write_cstring(debug_file, " unit sets:");
	write_newline(debug_file);
    }
}

void
debug_info_w_start_units(NStringT *unit_set,				  unsigned num_units)
{
    if (debug_file) {
	write_cstring(debug_file, "    Writing ");
	write_unsigned(debug_file, num_units);
	write_char(debug_file, ' ');
	write_nstring(debug_file, unit_set);
	write_cstring(debug_file, " units:");
	write_newline(debug_file);
    }
}

void
debug_info_w_start_unit(NStringT *unit_set,				 unsigned unit, 
				 unsigned num_units)
{
    if (debug_file) {
	write_cstring(debug_file, "      Writing ");
	write_nstring(debug_file, unit_set);
	write_cstring(debug_file, " unit ");
	write_unsigned(debug_file, unit);
	write_cstring(debug_file, " of ");
	write_unsigned(debug_file, num_units);
	write_char(debug_file, ':');
	write_newline(debug_file);
    }
}

void
debug_info_w_start_counts(unsigned num_counts)
{
    if (debug_file) {
	write_cstring(debug_file, "        Writing ");
	write_unsigned(debug_file, num_counts);
	write_cstring(debug_file, " counts:");
	write_newline(debug_file);
    }
}

void
debug_info_w_count(unsigned count,			    NStringT *shape)
{
    if (debug_file) {
	write_cstring(debug_file, "          ");
	write_unsigned(debug_file, count);
	write_cstring(debug_file, " (");
	write_nstring(debug_file, shape);
	write_char(debug_file, ')');
	write_newline(debug_file);
    }
}

void
debug_info_w_start_maps(unsigned num_maps)
{
    if (debug_file) {
	write_cstring(debug_file, "        Writing ");
	write_unsigned(debug_file, num_maps);
	write_cstring(debug_file, " mapping categories:");
	write_newline(debug_file);
    }
}

void
debug_info_w_start_shape_maps(NStringT *shape,				       unsigned num_maps)
{
    if (debug_file) {
	write_cstring(debug_file, "          Writing ");
	write_unsigned(debug_file, num_maps);
	write_char(debug_file, ' ');
	write_nstring(debug_file, shape);
	write_cstring(debug_file, " mappings:");
	write_newline(debug_file);
    }
}

void
debug_info_w_map(unsigned internal,			  unsigned external)
{
    if (debug_file) {
	write_cstring(debug_file, "            ");
	write_unsigned(debug_file, internal);
	write_cstring(debug_file, ", ");
	write_unsigned(debug_file, external);
	write_newline(debug_file);
    }
}

void
debug_info_w_unit_body(size_t size)
{
    if (debug_file) {
	write_cstring(debug_file, "        Writing ");
	write_unsigned(debug_file, (unsigned) size);
	write_cstring(debug_file, " bytes of unit body");
	write_newline(debug_file);
    }
}

void
debug_info_w_tld_version(unsigned version)
{
    if (debug_file) {
	write_cstring(debug_file, "          Writing version ");
	write_unsigned(debug_file, version);
	write_cstring(debug_file, " linker information unit:");
	write_newline(debug_file);
    }
}

void
debug_info_w_start_usages(NStringT *shape)
{
    if (debug_file) {
	write_cstring(debug_file, "            Writing external ");
	write_nstring(debug_file, shape);
	write_cstring(debug_file, " name usages:");
	write_newline(debug_file);
    }
}

void
debug_info_w_usage(unsigned use,			    NameKeyT *key)
{
    if (debug_file) {
	write_cstring(debug_file, "              ");
	write_usage(debug_file, use);
	write_cstring(debug_file, " (");
	write_name_key(debug_file, key);
	write_char(debug_file, ')');
	write_newline(debug_file);
    }
}

void
debug_info_w_end_capsule(void)
{
    if (debug_file) {
	write_cstring(debug_file, "Finished writing capsule");
	write_newline(debug_file);
    }
}

void
debug_info_r_start_library(const char * name)
{
    if (debug_file) {
	write_cstring(debug_file, "Reading library '");
	write_cstring(debug_file, name);
	write_cstring(debug_file, "':");
	write_newline(debug_file);
    }
}

void
debug_info_r_lib_versions(unsigned major, unsigned minor)
{
    if (debug_file) {
	write_cstring (debug_file, "  Reading major version: ");
	write_unsigned(debug_file, major);
	write_cstring (debug_file, "; minor version: ");
	write_unsigned(debug_file, minor);
	write_newline (debug_file);
    }
}

void
debug_info_r_library_version(unsigned version)
{
    if (debug_file) {
	write_cstring(debug_file, "  Reading type ");
	write_unsigned(debug_file, version);
	write_cstring(debug_file, " library:");
	write_newline(debug_file);
    }
}

void
debug_info_r_start_capsules(unsigned num_capsules)
{
    if (debug_file) {
	write_cstring(debug_file, "    Reading ");
	write_unsigned(debug_file, num_capsules);
	write_cstring(debug_file, " capsules:");
	write_newline(debug_file);
    }
}

void
debug_info_r_capsule(NStringT *name,			      size_t length)
{
    if (debug_file) {
	write_cstring(debug_file, "      Loaded '");
	write_nstring(debug_file, name);
	write_cstring(debug_file, "', ");
	write_unsigned(debug_file, (unsigned) length);
	write_cstring(debug_file, " bytes");
	write_newline(debug_file);
    }
}

void
debug_info_r_start_index(unsigned num_shapes)
{
    if (debug_file) {
	write_cstring(debug_file, "    Reading ");
	write_unsigned(debug_file, num_shapes);
	write_cstring(debug_file, " shape indices:");
	write_newline(debug_file);
    }
}

void
debug_info_r_start_shape_index(NStringT *shape,					unsigned num_names)
{
    if (debug_file) {
	write_cstring(debug_file, "      Reading ");
	write_unsigned(debug_file, num_names);
	write_cstring(debug_file, " entries in ");
	write_nstring(debug_file, shape);
	write_cstring(debug_file, " external name index:");
	write_newline(debug_file);
    }
}

void
debug_info_r_index_entry(NameKeyT *name,				  unsigned use, 
				  unsigned name_use, 
				  NameKeyT *key, 
				  char * cap_name)
{
    if (debug_file) {
	write_cstring(debug_file, "        ");
	write_name_key(debug_file, name);
	write_cstring(debug_file, ", ");
	write_usage(debug_file, use);
	write_cstring(debug_file, ", '");
	write_cstring(debug_file, cap_name);
	write_cstring(debug_file, "' (");
	write_name_key(debug_file, key);
	write_cstring(debug_file, ", ");
	write_usage(debug_file, name_use);
	write_char(debug_file, ')');
	write_newline(debug_file);
    }
}

void
debug_info_r_end_library(void)
{
    if (debug_file) {
	write_cstring(debug_file, "Finished reading library");
	write_newline(debug_file);
    }
}

void
debug_info_r_abort_library(void)
{
    if (debug_file) {
	write_cstring(debug_file, "Aborted reading library");
	write_newline(debug_file);
    }
}

void
debug_info_w_start_library(const char * name)
{
    if (debug_file) {
	write_cstring(debug_file, "Writing library '");
	write_cstring(debug_file, name);
	write_cstring(debug_file, "':");
	write_newline(debug_file);
    }
}

void
debug_info_w_lib_versions(unsigned major, unsigned minor)
{
    if (debug_file) {
	write_cstring (debug_file, "  Writing major version: ");
	write_unsigned(debug_file, major);
	write_cstring (debug_file, "; minor version: ");
	write_unsigned(debug_file, minor);
	write_newline (debug_file);
    }
}

void
debug_info_w_library_version(unsigned version)
{
    if (debug_file) {
	write_cstring(debug_file, "  Writing type ");
	write_unsigned(debug_file, version);
	write_cstring(debug_file, " library:");
	write_newline(debug_file);
    }
}

void
debug_info_w_start_capsules(unsigned num_capsules)
{
    if (debug_file) {
	write_cstring(debug_file, "    Writing ");
	write_unsigned(debug_file, num_capsules);
	write_cstring(debug_file, " capsules:");
	write_newline(debug_file);
    }
}

void
debug_info_w_capsule(char * name,			      size_t length)
{
    if (debug_file) {
	write_cstring(debug_file, "      Saved '");
	write_cstring(debug_file, name);
	write_cstring(debug_file, "', ");
	write_unsigned(debug_file, (unsigned) length);
	write_cstring(debug_file, " bytes");
	write_newline(debug_file);
    }
}

void
debug_info_w_start_index(unsigned num_shapes)
{
    if (debug_file) {
	write_cstring(debug_file, "    Writing ");
	write_unsigned(debug_file, num_shapes);
	write_cstring(debug_file, " shape indices:");
	write_newline(debug_file);
    }
}

void
debug_info_w_start_shape_index(NStringT *shape,					unsigned num_names)
{
    if (debug_file) {
	write_cstring(debug_file, "      Writing ");
	write_unsigned(debug_file, num_names);
	write_cstring(debug_file, " entries in ");
	write_nstring(debug_file, shape);
	write_cstring(debug_file, " external name index:");
	write_newline(debug_file);
    }
}

void
debug_info_w_index_entry(NameKeyT *key,				  unsigned use, 
				  char * cap_name, 
				  unsigned cap_index)
{
    if (debug_file) {
	write_cstring(debug_file, "        ");
	write_name_key(debug_file, key);
	write_cstring(debug_file, ", ");
	write_usage(debug_file, use);
	write_cstring(debug_file, ", '");
	write_cstring(debug_file, cap_name);
	write_cstring(debug_file, "' (");
	write_unsigned(debug_file, cap_index);
	write_char(debug_file, ')');
	write_newline(debug_file);
    }
}

void
debug_info_w_end_library(void)
{
    if (debug_file) {
	write_cstring(debug_file, "Finished writing library");
	write_newline(debug_file);
    }
}

void
debug_info_l_not_needed(NameKeyT *key,				 NStringT *shape_key, 
				 unsigned use)
{
    if (debug_file) {
	write_cstring(debug_file, "No definition needed for ");
	write_nstring(debug_file, shape_key);
	write_cstring(debug_file, " '");
	write_name_key(debug_file, key);
	write_cstring(debug_file, "' (");
	write_usage(debug_file, use);
	write_char(debug_file, ')');
	write_newline(debug_file);
    }
}

void
debug_info_l_not_found(NameKeyT *key,				NStringT *shape_key, 
				unsigned use)
{
    if (debug_file) {
	write_cstring(debug_file, "No definition found for ");
	write_nstring(debug_file, shape_key);
	write_cstring(debug_file, " '");
	write_name_key(debug_file, key);
	write_cstring(debug_file, "' (");
	write_usage(debug_file, use);
	write_char(debug_file, ')');
	write_newline(debug_file);
    }
}

void
debug_info_l_found(NameKeyT *key,			    NStringT *shape_key, 
			    unsigned use, 
			    char * name)
{
    if (debug_file) {
	write_cstring(debug_file, "Definition found for ");
	write_nstring(debug_file, shape_key);
	write_cstring(debug_file, " '");
	write_name_key(debug_file, key);
	write_cstring(debug_file, "' (");
	write_usage(debug_file, use);
	write_cstring(debug_file, ") in file '");
	write_cstring(debug_file, name);
	write_char(debug_file, '\'');
	write_newline(debug_file);
    }
}

void
debug_info_l_hide(NStringT *shape,			   NameKeyT *key)
{
    if (debug_file) {
	write_cstring(debug_file, "Hid external ");
	write_nstring(debug_file, shape);
	write_cstring(debug_file, " '");
	write_name_key(debug_file, key);
	write_char(debug_file, '\'');
	write_newline(debug_file);
    }
}

void
debug_info_l_keep(NStringT *shape,			   NameKeyT *key)
{
    if (debug_file) {
	write_cstring(debug_file, "Kept external ");
	write_nstring(debug_file, shape);
	write_cstring(debug_file, " '");
	write_name_key(debug_file, key);
	write_char(debug_file, '\'');
	write_newline(debug_file);
    }
}

void
debug_info_l_suppress(NStringT *shape,			       NameKeyT *key)
{
    if (debug_file) {
	write_cstring(debug_file, "Suppressed external ");
	write_nstring(debug_file, shape);
	write_cstring(debug_file, " '");
	write_name_key(debug_file, key);
	write_char(debug_file, '\'');
	write_newline(debug_file);
    }
}

void
debug_info_l_rename(NStringT *shape,			     NameKeyT *from, 
			     NameKeyT *to)
{
    if (debug_file) {
	write_cstring(debug_file, "Renamed external ");
	write_nstring(debug_file, shape);
	write_cstring(debug_file, " '");
	write_name_key(debug_file, from);
	write_cstring(debug_file, "' to '");
	write_name_key(debug_file, to);
	write_char(debug_file, '\'');
	write_newline(debug_file);
    }
}
