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


/**** debug.h --- Debugging routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * See the file "debug.c" for more information.
 *
 **** Change Log:
 * $Log: debug.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/07/07  15:32:23  smf
 * Updated to support TDF specification 4.0.
 *
 * Revision 1.2  1994/12/12  11:46:21  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:31  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_DEBUG
#define H_DEBUG

#include "os-interface.h"
#include "cstring.h"
#include "dstring.h"
#include "name-key.h"
#include "ostream.h"

/*--------------------------------------------------------------------------*/

extern void			debug_set_file
	PROTO_S ((OStreamP));

extern void			debug_info_u_name
	PROTO_S ((NStringP));

extern void			debug_info_r_start_capsule
	PROTO_S ((CStringP));
extern void			debug_info_r_versions
	PROTO_S ((unsigned, unsigned));
extern void			debug_info_r_start_unit_decs
	PROTO_S ((unsigned));
extern void			debug_info_r_unit_dec
	PROTO_S ((NStringP));
extern void			debug_info_r_start_shapes
	PROTO_S ((unsigned));
extern void			debug_info_r_shape
	PROTO_S ((NStringP, unsigned));
extern void			debug_info_r_start_names
	PROTO_S ((unsigned));
extern void			debug_info_r_start_shape_names
	PROTO_S ((NStringP, unsigned));
extern void			debug_info_r_name
	PROTO_S ((NameKeyP, unsigned, unsigned, NameKeyP));
extern void			debug_info_r_start_unit_sets
	PROTO_S ((unsigned));
extern void			debug_info_r_start_units
	PROTO_S ((NStringP, unsigned));
extern void			debug_info_r_start_unit
	PROTO_S ((NStringP, unsigned, unsigned));
extern void			debug_info_r_start_counts
	PROTO_S ((unsigned));
extern void			debug_info_r_count
	PROTO_S ((unsigned, NStringP));
extern void			debug_info_r_start_maps
	PROTO_S ((unsigned));
extern void			debug_info_r_start_shape_maps
	PROTO_S ((NStringP, unsigned));
extern void			debug_info_r_map
	PROTO_S ((unsigned, unsigned, unsigned));
extern void			debug_info_r_unit_body
	PROTO_S ((unsigned));
extern void			debug_info_r_tld_version
	PROTO_S ((unsigned));
extern void			debug_info_r_start_usages
	PROTO_S ((NStringP, unsigned));
extern void			debug_info_r_usage
	PROTO_S ((unsigned, unsigned, NameKeyP));
extern void			debug_info_r_end_capsule
	PROTO_S ((void));
extern void			debug_info_r_abort_capsule
	PROTO_S ((void));

extern void			debug_info_w_start_capsule
	PROTO_S ((CStringP));
extern void			debug_info_w_versions
	PROTO_S ((unsigned, unsigned));
extern void			debug_info_w_start_unit_decs
	PROTO_S ((unsigned));
extern void			debug_info_w_unit_dec
	PROTO_S ((NStringP));
extern void			debug_info_w_start_shapes
	PROTO_S ((unsigned));
extern void			debug_info_w_shape
	PROTO_S ((NStringP, unsigned));
extern void			debug_info_w_start_names
	PROTO_S ((unsigned));
extern void			debug_info_w_start_shape_names
	PROTO_S ((NStringP, unsigned));
extern void			debug_info_w_name
	PROTO_S ((NameKeyP, unsigned));
extern void			debug_info_w_start_unit_sets
	PROTO_S ((unsigned));
extern void			debug_info_w_start_units
	PROTO_S ((NStringP, unsigned));
extern void			debug_info_w_start_unit
	PROTO_S ((NStringP, unsigned, unsigned));
extern void			debug_info_w_start_counts
	PROTO_S ((unsigned));
extern void			debug_info_w_count
	PROTO_S ((unsigned, NStringP));
extern void			debug_info_w_start_maps
	PROTO_S ((unsigned));
extern void			debug_info_w_start_shape_maps
	PROTO_S ((NStringP, unsigned));
extern void			debug_info_w_map
	PROTO_S ((unsigned, unsigned));
extern void			debug_info_w_unit_body
	PROTO_S ((unsigned));
extern void			debug_info_w_tld_version
	PROTO_S ((unsigned));
extern void			debug_info_w_start_usages
	PROTO_S ((NStringP));
extern void			debug_info_w_usage
	PROTO_S ((unsigned, NameKeyP));
extern void			debug_info_w_end_capsule
	PROTO_S ((void));

extern void			debug_info_r_start_library
	PROTO_S ((CStringP));
extern void			debug_info_r_lib_versions
	PROTO_S ((unsigned, unsigned));
extern void			debug_info_r_library_version
	PROTO_S ((unsigned));
extern void			debug_info_r_start_capsules
	PROTO_S ((unsigned));
extern void			debug_info_r_capsule
	PROTO_S ((NStringP, unsigned));
extern void			debug_info_r_start_index
	PROTO_S ((unsigned));
extern void			debug_info_r_start_shape_index
	PROTO_S ((NStringP, unsigned));
extern void			debug_info_r_index_entry
	PROTO_S ((NameKeyP, unsigned, unsigned, NameKeyP, CStringP));
extern void			debug_info_r_end_library
	PROTO_S ((void));
extern void			debug_info_r_abort_library
	PROTO_S ((void));

extern void			debug_info_w_start_library
	PROTO_S ((CStringP));
extern void			debug_info_w_lib_versions
	PROTO_S ((unsigned, unsigned));
extern void			debug_info_w_library_version
	PROTO_S ((unsigned));
extern void			debug_info_w_start_capsules
	PROTO_S ((unsigned));
extern void			debug_info_w_capsule
	PROTO_S ((CStringP, unsigned));
extern void			debug_info_w_start_index
	PROTO_S ((unsigned));
extern void			debug_info_w_start_shape_index
	PROTO_S ((NStringP, unsigned));
extern void			debug_info_w_index_entry
	PROTO_S ((NameKeyP, unsigned, CStringP, unsigned));
extern void			debug_info_w_end_library
	PROTO_S ((void));

extern void			debug_info_l_not_needed
	PROTO_S ((NameKeyP, NStringP, unsigned));
extern void			debug_info_l_not_found
	PROTO_S ((NameKeyP, NStringP, unsigned));
extern void			debug_info_l_found
	PROTO_S ((NameKeyP, NStringP, unsigned, CStringP));
extern void			debug_info_l_hide
	PROTO_S ((NStringP, NameKeyP));
extern void			debug_info_l_keep
	PROTO_S ((NStringP, NameKeyP));
extern void			debug_info_l_suppress
	PROTO_S ((NStringP, NameKeyP));
extern void			debug_info_l_rename
	PROTO_S ((NStringP, NameKeyP, NameKeyP));

#endif /* !defined (H_DEBUG) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "os-interface" "library" "generated")
 * End:
**/
