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


/**** debug.c --- Debugging routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the tracing routines for use with the TDF linker.
 *
 **** Change Log:
 * $Log: debug.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/09/22  08:39:15  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.3  1995/07/07  15:32:22  smf
 * Updated to support TDF specification 4.0.
 *
 * Revision 1.2  1994/12/12  11:46:18  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:31  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "debug.h"
#include "tdf.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

static OStreamP	debug_file   = NIL (OStreamP);

/*--------------------------------------------------------------------------*/

void
debug_set_file PROTO_N ((file))
	       PROTO_T (OStreamP file)
{
    if (ostream_is_open (file)) {
	debug_file = file;
    } else {
	debug_file = NIL (OStreamP);
    }
}

/*--------------------------------------------------------------------------*/

void
debug_info_u_name PROTO_N ((name))
		  PROTO_T (NStringP name)
{
    if (debug_file) {
	write_cstring (debug_file, "Using unit set name '");
	write_nstring (debug_file, name);
	write_char (debug_file, '\'');
	write_newline (debug_file);
    }
}

/*--------------------------------------------------------------------------*/

void
debug_info_r_start_capsule PROTO_N ((name))
			   PROTO_T (CStringP name)
{
    if (debug_file) {
	write_cstring (debug_file, "Reading capsule '");
	write_cstring (debug_file, name);
	write_cstring (debug_file, "':");
	write_newline (debug_file);
    }
}

void
debug_info_r_versions PROTO_N ((major, minor))
    		      PROTO_T (unsigned major X unsigned minor)
{
    if (debug_file) {
	write_cstring  (debug_file, "  Read major version: ");
	write_unsigned (debug_file, major);
	write_cstring  (debug_file, "; minor version:");
	write_unsigned (debug_file, minor);
	write_newline  (debug_file);
    }
}

void
debug_info_r_start_unit_decs PROTO_N ((num_unit_sets))
			     PROTO_T (unsigned num_unit_sets)
{
    if (debug_file) {
	write_cstring (debug_file, "  Reading ");
	write_unsigned (debug_file, num_unit_sets);
	write_cstring (debug_file, " unit set names:");
	write_newline (debug_file);
    }
}

void
debug_info_r_unit_dec PROTO_N ((name))
		      PROTO_T (NStringP name)
{
    if (debug_file) {
	write_cstring (debug_file, "    ");
	write_nstring (debug_file, name);
	write_newline (debug_file);
    }
}

void
debug_info_r_start_shapes PROTO_N ((num_shapes))
			  PROTO_T (unsigned num_shapes)
{
    if (debug_file) {
	write_cstring (debug_file, "  Reading ");
	write_unsigned (debug_file, num_shapes);
	write_cstring (debug_file, " shape names:");
	write_newline (debug_file);
    }
}

void
debug_info_r_shape PROTO_N ((name, num_ids))
		   PROTO_T (NStringP name X
			    unsigned num_ids)
{
    if (debug_file) {
	write_cstring (debug_file, "    ");
	write_nstring (debug_file, name);
	write_cstring (debug_file, ", ");
	write_unsigned (debug_file, num_ids);
	write_newline (debug_file);
    }
}

void
debug_info_r_start_names PROTO_N ((num_names))
			 PROTO_T (unsigned num_names)
{
    if (debug_file) {
	write_cstring (debug_file, "  Reading ");
	write_unsigned (debug_file, num_names);
	write_cstring (debug_file, " external name categories:");
	write_newline (debug_file);
    }
}

void
debug_info_r_start_shape_names PROTO_N ((shape, num_names))
			       PROTO_T (NStringP shape X
					unsigned num_names)
{
    if (debug_file) {
	write_cstring (debug_file, "    Reading ");
	write_unsigned (debug_file, num_names);
	write_cstring (debug_file, " external ");
	write_nstring (debug_file, shape);
	write_cstring (debug_file, " names:");
	write_newline (debug_file);
    }
}

void
debug_info_r_name PROTO_N ((name, old_id, new_id, key))
		  PROTO_T (NameKeyP name X
			   unsigned old_id X
			   unsigned new_id X
			   NameKeyP key)
{
    if (debug_file) {
	write_cstring (debug_file, "      ");
	write_name_key (debug_file, name);
	write_cstring (debug_file, ", ");
	write_unsigned (debug_file, old_id);
	write_cstring (debug_file, " -> ");
	write_unsigned (debug_file, new_id);
	write_cstring (debug_file, " (");
	write_name_key (debug_file, key);
	write_char (debug_file, ')');
	write_newline (debug_file);
    }
}

void
debug_info_r_start_unit_sets PROTO_N ((num_unit_sets))
			     PROTO_T (unsigned num_unit_sets)
{
    if (debug_file) {
	write_cstring (debug_file, "  Reading ");
	write_unsigned (debug_file, num_unit_sets);
	write_cstring (debug_file, " unit sets:");
	write_newline (debug_file);
    }
}

void
debug_info_r_start_units PROTO_N ((unit_set, num_units))
			 PROTO_T (NStringP unit_set X
				  unsigned num_units)
{
    if (debug_file) {
	write_cstring (debug_file, "    Reading ");
	write_unsigned (debug_file, num_units);
	write_char (debug_file, ' ');
	write_nstring (debug_file, unit_set);
	write_cstring (debug_file, " units:");
	write_newline (debug_file);
    }
}

void
debug_info_r_start_unit PROTO_N ((unit_set, unit, num_units))
			PROTO_T (NStringP unit_set X
				 unsigned unit X
				 unsigned num_units)
{
    if (debug_file) {
	write_cstring (debug_file, "      Reading ");
	write_nstring (debug_file, unit_set);
	write_cstring (debug_file, " unit ");
	write_unsigned (debug_file, unit);
	write_cstring (debug_file, " of ");
	write_unsigned (debug_file, num_units);
	write_char (debug_file, ':');
	write_newline (debug_file);
    }
}

void
debug_info_r_start_counts PROTO_N ((num_counts))
			  PROTO_T (unsigned num_counts)
{
    if (debug_file) {
	write_cstring (debug_file, "        Reading ");
	write_unsigned (debug_file, num_counts);
	write_cstring (debug_file, " counts:");
	write_newline (debug_file);
    }
}

void
debug_info_r_count PROTO_N ((count, shape))
		   PROTO_T (unsigned count X
			    NStringP shape)
{
    if (debug_file) {
	write_cstring (debug_file, "          ");
	write_unsigned (debug_file, count);
	write_cstring (debug_file, " (");
	write_nstring (debug_file, shape);
	write_char (debug_file, ')');
	write_newline (debug_file);
    }
}

void
debug_info_r_start_maps PROTO_N ((num_maps))
			PROTO_T (unsigned num_maps)
{
    if (debug_file) {
	write_cstring (debug_file, "        Reading ");
	write_unsigned (debug_file, num_maps);
	write_cstring (debug_file, " mapping categories:");
	write_newline (debug_file);
    }
}

void
debug_info_r_start_shape_maps PROTO_N ((shape, num_maps))
			      PROTO_T (NStringP shape X
				       unsigned num_maps)
{
    if (debug_file) {
	write_cstring (debug_file, "          Reading ");
	write_unsigned (debug_file, num_maps);
	write_char (debug_file, ' ');
	write_nstring (debug_file, shape);
	write_cstring (debug_file, " mappings:");
	write_newline (debug_file);
    }
}

void
debug_info_r_map PROTO_N ((internal, old_external, new_external))
		 PROTO_T (unsigned internal X
			  unsigned old_external X
			  unsigned new_external)
{
    if (debug_file) {
	write_cstring (debug_file, "            ");
	write_unsigned (debug_file, internal);
	write_cstring (debug_file, ", ");
	write_unsigned (debug_file, old_external);
	write_cstring (debug_file, " -> ");
	write_unsigned (debug_file, new_external);
	write_newline (debug_file);
    }
}

void
debug_info_r_unit_body PROTO_N ((size))
		       PROTO_T (unsigned size)
{
    if (debug_file) {
	write_cstring (debug_file, "        Reading ");
	write_unsigned (debug_file, size);
	write_cstring (debug_file, " bytes of unit body");
	write_newline (debug_file);
    }
}

void
debug_info_r_tld_version PROTO_N ((version))
			 PROTO_T (unsigned version)
{
    if (debug_file) {
	write_cstring (debug_file, "          Reading version ");
	write_unsigned (debug_file, version);
	write_cstring (debug_file, " linker information unit:");
	write_newline (debug_file);
    }
}

void
debug_info_r_start_usages PROTO_N ((shape, num_names))
			  PROTO_T (NStringP shape X
				   unsigned num_names)
{
    if (debug_file) {
	write_cstring (debug_file, "            Reading ");
	write_unsigned (debug_file, num_names);
	write_cstring (debug_file, " external ");
	write_nstring (debug_file, shape);
	write_cstring (debug_file, " name usages:");
	write_newline (debug_file);
    }
}

void
debug_info_r_usage PROTO_N ((use, name_use, key))
		   PROTO_T (unsigned use X
			    unsigned name_use X
			    NameKeyP key)
{
    if (debug_file) {
	write_cstring (debug_file, "              ");
	write_usage (debug_file, use);
	write_cstring (debug_file, " (");
	write_name_key (debug_file, key);
	write_cstring (debug_file, ", ");
	write_usage (debug_file, name_use);
	write_char (debug_file, ')');
	write_newline (debug_file);
    }
}

void
debug_info_r_end_capsule PROTO_Z ()
{
    if (debug_file) {
	write_cstring (debug_file, "Finished reading capsule");
	write_newline (debug_file);
    }
}

void
debug_info_r_abort_capsule PROTO_Z ()
{
    if (debug_file) {
	write_cstring (debug_file, "Aborted reading capsule");
	write_newline (debug_file);
    }
}

/*--------------------------------------------------------------------------*/

void
debug_info_w_start_capsule PROTO_N ((name))
			   PROTO_T (CStringP name)
{
    if (debug_file) {
	write_cstring (debug_file, "Writing capsule '");
	write_cstring (debug_file, name);
	write_cstring (debug_file, "':");
	write_newline (debug_file);
    }
}

void
debug_info_w_versions PROTO_N ((major, minor))
    		      PROTO_T (unsigned major X unsigned minor)
{
    if (debug_file) {
	write_cstring  (debug_file, "  Writing major version: ");
	write_unsigned (debug_file, major);
	write_cstring  (debug_file, "; minor version:");
	write_unsigned (debug_file, minor);
	write_newline  (debug_file);
    }
}

void
debug_info_w_start_unit_decs PROTO_N ((num_unit_sets))
			     PROTO_T (unsigned num_unit_sets)
{
    if (debug_file) {
	write_cstring (debug_file, "  Writing ");
	write_unsigned (debug_file, num_unit_sets);
	write_cstring (debug_file, " unit set names:");
	write_newline (debug_file);
    }
}

void
debug_info_w_unit_dec PROTO_N ((name))
		      PROTO_T (NStringP name)
{
    if (debug_file) {
	write_cstring (debug_file, "    ");
	write_nstring (debug_file, name);
	write_newline (debug_file);
    }
}

void
debug_info_w_start_shapes PROTO_N ((num_shapes))
			  PROTO_T (unsigned num_shapes)
{
    if (debug_file) {
	write_cstring (debug_file, "  Writing ");
	write_unsigned (debug_file, num_shapes);
	write_cstring (debug_file, " shape names:");
	write_newline (debug_file);
    }
}

void
debug_info_w_shape PROTO_N ((name, num_ids))
		   PROTO_T (NStringP name X
			    unsigned num_ids)
{
    if (debug_file) {
	write_cstring (debug_file, "    ");
	write_nstring (debug_file, name);
	write_cstring (debug_file, ", ");
	write_unsigned (debug_file, num_ids);
	write_newline (debug_file);
    }
}

void
debug_info_w_start_names PROTO_N ((num_names))
			 PROTO_T (unsigned num_names)
{
    if (debug_file) {
	write_cstring (debug_file, "  Writing ");
	write_unsigned (debug_file, num_names);
	write_cstring (debug_file, " external name categories:");
	write_newline (debug_file);
    }
}

void
debug_info_w_start_shape_names PROTO_N ((shape, num_names))
			       PROTO_T (NStringP shape X
					unsigned num_names)
{
    if (debug_file) {
	write_cstring (debug_file, "    Writing ");
	write_unsigned (debug_file, num_names);
	write_cstring (debug_file, " external ");
	write_nstring (debug_file, shape);
	write_cstring (debug_file, " names:");
	write_newline (debug_file);
    }
}

void
debug_info_w_name PROTO_N ((name, id))
		  PROTO_T (NameKeyP name X
			   unsigned id)
{
    if (debug_file) {
	write_cstring (debug_file, "      ");
	write_name_key (debug_file, name);
	write_cstring (debug_file, ", ");
	write_unsigned (debug_file, id);
	write_newline (debug_file);
    }
}

void
debug_info_w_start_unit_sets PROTO_N ((num_unit_sets))
			     PROTO_T (unsigned num_unit_sets)
{
    if (debug_file) {
	write_cstring (debug_file, "  Writing ");
	write_unsigned (debug_file, num_unit_sets);
	write_cstring (debug_file, " unit sets:");
	write_newline (debug_file);
    }
}

void
debug_info_w_start_units PROTO_N ((unit_set, num_units))
			 PROTO_T (NStringP unit_set X
				  unsigned num_units)
{
    if (debug_file) {
	write_cstring (debug_file, "    Writing ");
	write_unsigned (debug_file, num_units);
	write_char (debug_file, ' ');
	write_nstring (debug_file, unit_set);
	write_cstring (debug_file, " units:");
	write_newline (debug_file);
    }
}

void
debug_info_w_start_unit PROTO_N ((unit_set, unit, num_units))
			PROTO_T (NStringP unit_set X
				 unsigned unit X
				 unsigned num_units)
{
    if (debug_file) {
	write_cstring (debug_file, "      Writing ");
	write_nstring (debug_file, unit_set);
	write_cstring (debug_file, " unit ");
	write_unsigned (debug_file, unit);
	write_cstring (debug_file, " of ");
	write_unsigned (debug_file, num_units);
	write_char (debug_file, ':');
	write_newline (debug_file);
    }
}

void
debug_info_w_start_counts PROTO_N ((num_counts))
			  PROTO_T (unsigned num_counts)
{
    if (debug_file) {
	write_cstring (debug_file, "        Writing ");
	write_unsigned (debug_file, num_counts);
	write_cstring (debug_file, " counts:");
	write_newline (debug_file);
    }
}

void
debug_info_w_count PROTO_N ((count, shape))
		   PROTO_T (unsigned count X
			    NStringP shape)
{
    if (debug_file) {
	write_cstring (debug_file, "          ");
	write_unsigned (debug_file, count);
	write_cstring (debug_file, " (");
	write_nstring (debug_file, shape);
	write_char (debug_file, ')');
	write_newline (debug_file);
    }
}

void
debug_info_w_start_maps PROTO_N ((num_maps))
			PROTO_T (unsigned num_maps)
{
    if (debug_file) {
	write_cstring (debug_file, "        Writing ");
	write_unsigned (debug_file, num_maps);
	write_cstring (debug_file, " mapping categories:");
	write_newline (debug_file);
    }
}

void
debug_info_w_start_shape_maps PROTO_N ((shape, num_maps))
			      PROTO_T (NStringP shape X
				       unsigned num_maps)
{
    if (debug_file) {
	write_cstring (debug_file, "          Writing ");
	write_unsigned (debug_file, num_maps);
	write_char (debug_file, ' ');
	write_nstring (debug_file, shape);
	write_cstring (debug_file, " mappings:");
	write_newline (debug_file);
    }
}

void
debug_info_w_map PROTO_N ((internal, external))
		 PROTO_T (unsigned internal X
			  unsigned external)
{
    if (debug_file) {
	write_cstring (debug_file, "            ");
	write_unsigned (debug_file, internal);
	write_cstring (debug_file, ", ");
	write_unsigned (debug_file, external);
	write_newline (debug_file);
    }
}

void
debug_info_w_unit_body PROTO_N ((size))
		       PROTO_T (unsigned size)
{
    if (debug_file) {
	write_cstring (debug_file, "        Writing ");
	write_unsigned (debug_file, size);
	write_cstring (debug_file, " bytes of unit body");
	write_newline (debug_file);
    }
}

void
debug_info_w_tld_version PROTO_N ((version))
			 PROTO_T (unsigned version)
{
    if (debug_file) {
	write_cstring (debug_file, "          Writing version ");
	write_unsigned (debug_file, version);
	write_cstring (debug_file, " linker information unit:");
	write_newline (debug_file);
    }
}

void
debug_info_w_start_usages PROTO_N ((shape))
			  PROTO_T (NStringP shape)
{
    if (debug_file) {
	write_cstring (debug_file, "            Writing external ");
	write_nstring (debug_file, shape);
	write_cstring (debug_file, " name usages:");
	write_newline (debug_file);
    }
}

void
debug_info_w_usage PROTO_N ((use, key))
		   PROTO_T (unsigned use X
			    NameKeyP key)
{
    if (debug_file) {
	write_cstring (debug_file, "              ");
	write_usage (debug_file, use);
	write_cstring (debug_file, " (");
	write_name_key (debug_file, key);
	write_char (debug_file, ')');
	write_newline (debug_file);
    }
}

void
debug_info_w_end_capsule PROTO_Z ()
{
    if (debug_file) {
	write_cstring (debug_file, "Finished writing capsule");
	write_newline (debug_file);
    }
}

/*--------------------------------------------------------------------------*/

void
debug_info_r_start_library PROTO_N ((name))
			   PROTO_T (CStringP name)
{
    if (debug_file) {
	write_cstring (debug_file, "Reading library '");
	write_cstring (debug_file, name);
	write_cstring (debug_file, "':");
	write_newline (debug_file);
    }
}

void
debug_info_r_lib_versions PROTO_N ((major, minor))
    			  PROTO_T (unsigned major X unsigned minor)
{
    if (debug_file) {
	write_cstring  (debug_file, "  Reading major version: ");
	write_unsigned (debug_file, major);
	write_cstring  (debug_file, "; minor version: ");
	write_unsigned (debug_file, minor);
	write_newline  (debug_file);
    }
}

void
debug_info_r_library_version PROTO_N ((version))
			     PROTO_T (unsigned version)
{
    if (debug_file) {
	write_cstring (debug_file, "  Reading type ");
	write_unsigned (debug_file, version);
	write_cstring (debug_file, " library:");
	write_newline (debug_file);
    }
}

void
debug_info_r_start_capsules PROTO_N ((num_capsules))
			    PROTO_T (unsigned num_capsules)
{
    if (debug_file) {
	write_cstring (debug_file, "    Reading ");
	write_unsigned (debug_file, num_capsules);
	write_cstring (debug_file, " capsules:");
	write_newline (debug_file);
    }
}

void
debug_info_r_capsule PROTO_N ((name, length))
		     PROTO_T (NStringP name X
			      unsigned length)
{
    if (debug_file) {
	write_cstring (debug_file, "      Loaded '");
	write_nstring (debug_file, name);
	write_cstring (debug_file, "', ");
	write_unsigned (debug_file, length);
	write_cstring (debug_file, " bytes");
	write_newline (debug_file);
    }
}

void
debug_info_r_start_index PROTO_N ((num_shapes))
			 PROTO_T (unsigned num_shapes)
{
    if (debug_file) {
	write_cstring (debug_file, "    Reading ");
	write_unsigned (debug_file, num_shapes);
	write_cstring (debug_file, " shape indices:");
	write_newline (debug_file);
    }
}

void
debug_info_r_start_shape_index PROTO_N ((shape, num_names))
			       PROTO_T (NStringP shape X
					unsigned num_names)
{
    if (debug_file) {
	write_cstring (debug_file, "      Reading ");
	write_unsigned (debug_file, num_names);
	write_cstring (debug_file, " entries in ");
	write_nstring (debug_file, shape);
	write_cstring (debug_file, " external name index:");
	write_newline (debug_file);
    }
}

void
debug_info_r_index_entry PROTO_N ((name, use, name_use, key, cap_name))
			 PROTO_T (NameKeyP name X
				  unsigned use X
				  unsigned name_use X
				  NameKeyP key X
				  CStringP cap_name)
{
    if (debug_file) {
	write_cstring (debug_file, "        ");
	write_name_key (debug_file, name);
	write_cstring (debug_file, ", ");
	write_usage (debug_file, use);
	write_cstring (debug_file, ", '");
	write_cstring (debug_file, cap_name);
	write_cstring (debug_file, "' (");
	write_name_key (debug_file, key);
	write_cstring (debug_file, ", ");
	write_usage (debug_file, name_use);
	write_char (debug_file, ')');
	write_newline (debug_file);
    }
}

void
debug_info_r_end_library PROTO_Z ()
{
    if (debug_file) {
	write_cstring (debug_file, "Finished reading library");
	write_newline (debug_file);
    }
}

void
debug_info_r_abort_library PROTO_Z ()
{
    if (debug_file) {
	write_cstring (debug_file, "Aborted reading library");
	write_newline (debug_file);
    }
}

/*--------------------------------------------------------------------------*/

void
debug_info_w_start_library PROTO_N ((name))
			   PROTO_T (CStringP name)
{
    if (debug_file) {
	write_cstring (debug_file, "Writing library '");
	write_cstring (debug_file, name);
	write_cstring (debug_file, "':");
	write_newline (debug_file);
    }
}

void
debug_info_w_lib_versions PROTO_N ((major, minor))
    			  PROTO_T (unsigned major X unsigned minor)
{
    if (debug_file) {
	write_cstring  (debug_file, "  Writing major version: ");
	write_unsigned (debug_file, major);
	write_cstring  (debug_file, "; minor version: ");
	write_unsigned (debug_file, minor);
	write_newline  (debug_file);
    }
}

void
debug_info_w_library_version PROTO_N ((version))
			     PROTO_T (unsigned version)
{
    if (debug_file) {
	write_cstring (debug_file, "  Writing type ");
	write_unsigned (debug_file, version);
	write_cstring (debug_file, " library:");
	write_newline (debug_file);
    }
}

void
debug_info_w_start_capsules PROTO_N ((num_capsules))
			    PROTO_T (unsigned num_capsules)
{
    if (debug_file) {
	write_cstring (debug_file, "    Writing ");
	write_unsigned (debug_file, num_capsules);
	write_cstring (debug_file, " capsules:");
	write_newline (debug_file);
    }
}

void
debug_info_w_capsule PROTO_N ((name, length))
		     PROTO_T (CStringP name X
			      unsigned length)
{
    if (debug_file) {
	write_cstring (debug_file, "      Saved '");
	write_cstring (debug_file, name);
	write_cstring (debug_file, "', ");
	write_unsigned (debug_file, length);
	write_cstring (debug_file, " bytes");
	write_newline (debug_file);
    }
}

void
debug_info_w_start_index PROTO_N ((num_shapes))
			 PROTO_T (unsigned num_shapes)
{
    if (debug_file) {
	write_cstring (debug_file, "    Writing ");
	write_unsigned (debug_file, num_shapes);
	write_cstring (debug_file, " shape indices:");
	write_newline (debug_file);
    }
}

void
debug_info_w_start_shape_index PROTO_N ((shape, num_names))
			       PROTO_T (NStringP shape X
					unsigned num_names)
{
    if (debug_file) {
	write_cstring (debug_file, "      Writing ");
	write_unsigned (debug_file, num_names);
	write_cstring (debug_file, " entries in ");
	write_nstring (debug_file, shape);
	write_cstring (debug_file, " external name index:");
	write_newline (debug_file);
    }
}

void
debug_info_w_index_entry PROTO_N ((key, use, cap_name, cap_index))
			 PROTO_T (NameKeyP key X
				  unsigned use X
				  CStringP cap_name X
				  unsigned cap_index)
{
    if (debug_file) {
	write_cstring (debug_file, "        ");
	write_name_key (debug_file, key);
	write_cstring (debug_file, ", ");
	write_usage (debug_file, use);
	write_cstring (debug_file, ", '");
	write_cstring (debug_file, cap_name);
	write_cstring (debug_file, "' (");
	write_unsigned (debug_file, cap_index);
	write_char (debug_file, ')');
	write_newline (debug_file);
    }
}

void
debug_info_w_end_library PROTO_Z ()
{
    if (debug_file) {
	write_cstring (debug_file, "Finished writing library");
	write_newline (debug_file);
    }
}

/*--------------------------------------------------------------------------*/

void
debug_info_l_not_needed PROTO_N ((key, shape_key, use))
			PROTO_T (NameKeyP key X
				 NStringP shape_key X
				 unsigned use)
{
    if (debug_file) {
	write_cstring (debug_file, "No definition needed for ");
	write_nstring (debug_file, shape_key);
	write_cstring (debug_file, " '");
	write_name_key (debug_file, key);
	write_cstring (debug_file, "' (");
	write_usage (debug_file, use);
	write_char (debug_file, ')');
	write_newline (debug_file);
    }
}

void
debug_info_l_not_found PROTO_N ((key, shape_key, use))
		       PROTO_T (NameKeyP key X
				NStringP shape_key X
				unsigned use)
{
    if (debug_file) {
	write_cstring (debug_file, "No definition found for ");
	write_nstring (debug_file, shape_key);
	write_cstring (debug_file, " '");
	write_name_key (debug_file, key);
	write_cstring (debug_file, "' (");
	write_usage (debug_file, use);
	write_char (debug_file, ')');
	write_newline (debug_file);
    }
}

void
debug_info_l_found PROTO_N ((key, shape_key, use, name))
		   PROTO_T (NameKeyP key X
			    NStringP shape_key X
			    unsigned use X
			    CStringP name)
{
    if (debug_file) {
	write_cstring (debug_file, "Definition found for ");
	write_nstring (debug_file, shape_key);
	write_cstring (debug_file, " '");
	write_name_key (debug_file, key);
	write_cstring (debug_file, "' (");
	write_usage (debug_file, use);
	write_cstring (debug_file, ") in file '");
	write_cstring (debug_file, name);
	write_char (debug_file, '\'');
	write_newline (debug_file);
    }
}

void
debug_info_l_hide PROTO_N ((shape, key))
		  PROTO_T (NStringP shape X
			   NameKeyP key)
{
    if (debug_file) {
	write_cstring (debug_file, "Hid external ");
	write_nstring (debug_file, shape);
	write_cstring (debug_file, " '");
	write_name_key (debug_file, key);
	write_char (debug_file, '\'');
	write_newline (debug_file);
    }
}

void
debug_info_l_keep PROTO_N ((shape, key))
		  PROTO_T (NStringP shape X
			   NameKeyP key)
{
    if (debug_file) {
	write_cstring (debug_file, "Kept external ");
	write_nstring (debug_file, shape);
	write_cstring (debug_file, " '");
	write_name_key (debug_file, key);
	write_char (debug_file, '\'');
	write_newline (debug_file);
    }
}

void
debug_info_l_suppress PROTO_N ((shape, key))
		      PROTO_T (NStringP shape X
			       NameKeyP key)
{
    if (debug_file) {
	write_cstring (debug_file, "Suppressed external ");
	write_nstring (debug_file, shape);
	write_cstring (debug_file, " '");
	write_name_key (debug_file, key);
	write_char (debug_file, '\'');
	write_newline (debug_file);
    }
}

void
debug_info_l_rename PROTO_N ((shape, from, to))
		    PROTO_T (NStringP shape X
			     NameKeyP from X
			     NameKeyP to)
{
    if (debug_file) {
	write_cstring (debug_file, "Renamed external ");
	write_nstring (debug_file, shape);
	write_cstring (debug_file, " '");
	write_name_key (debug_file, from);
	write_cstring (debug_file, "' to '");
	write_name_key (debug_file, to);
	write_char (debug_file, '\'');
	write_newline (debug_file);
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "os-interface" "library" "generated")
 * End:
**/
