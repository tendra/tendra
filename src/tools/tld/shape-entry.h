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


/*** shape-entry.h --- Shape table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "shape-entry.c" for more information.
 *
 *** Change Log:
 * $Log: shape-entry.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:20  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:46:48  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:38  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_SHAPE_ENTRY
#define H_SHAPE_ENTRY

#include "os-interface.h"
#include "dalloc.h"
#include "dstring.h"
#include "map-table.h"
#include "name-entry.h"
#include "name-table.h"
#include "tdf-write.h"

struct ShapeTableT;
struct UnitTableT;

/*--------------------------------------------------------------------------*/

typedef struct ShapeEntryT {
    struct ShapeEntryT	       *next;
    NStringT			key;
    NameTableP			names;
    unsigned			id_count;
    BoolT			non_empty;
    unsigned			num_lib_names;
    NameEntryP			head;
    NameEntryP		       *tail;
} ShapeEntryT, *ShapeEntryP;

typedef struct ShapeClosureT {
    MapTableP			table;
    TDFWriterP			writer;
} ShapeClosureT, *ShapeClosureP;

typedef struct ShapeLibClosureT {
    BoolT			did_define;
    struct ShapeTableT	       *lib_shapes;
    struct UnitTableT	       *units;
    struct ShapeTableT	       *shapes;
} ShapeLibClosureT, *ShapeLibClosureP;

/*--------------------------------------------------------------------------*/

extern ShapeEntryP		shape_entry_create
	PROTO_S ((NStringP));
extern ShapeEntryP		shape_entry_next
	PROTO_S ((ShapeEntryP));
extern ShapeEntryP	       *shape_entry_next_ref
	PROTO_S ((ShapeEntryP));
extern NStringP			shape_entry_key
	PROTO_S ((ShapeEntryP));
extern NameTableP		shape_entry_name_table
	PROTO_S ((ShapeEntryP));
extern unsigned			shape_entry_next_id
	PROTO_S ((ShapeEntryP));
extern void			shape_entry_set_non_empty
	PROTO_S ((ShapeEntryP));
extern BoolT			shape_entry_get_non_empty
	PROTO_S ((ShapeEntryP));
extern void			shape_entry_add_to_list
	PROTO_S ((ShapeEntryP, NameEntryP));
extern NameEntryP		shape_entry_get_from_list
	PROTO_S ((ShapeEntryP));
extern ShapeEntryP		shape_entry_deallocate
	PROTO_S ((ShapeEntryP));

extern void			shape_entry_do_count
	PROTO_S ((ShapeEntryP, GenericP));
extern void			shape_entry_write_shape
	PROTO_S ((ShapeEntryP, GenericP));
extern void			shape_entry_write_externs
	PROTO_S ((ShapeEntryP, GenericP));
extern void			shape_entry_compute_tld_size
	PROTO_S ((ShapeEntryP, GenericP));
extern void			shape_entry_write_tld
	PROTO_S ((ShapeEntryP, GenericP));
extern void			shape_entry_write_count
	PROTO_S ((ShapeEntryP, GenericP));
extern void			shape_entry_write_links
	PROTO_S ((ShapeEntryP, GenericP));
extern void			shape_entry_check_multi_defs
	PROTO_S ((ShapeEntryP, GenericP));
extern void			shape_entry_do_lib_count
	PROTO_S ((ShapeEntryP, GenericP));
extern void			shape_entry_do_lib_write
	PROTO_S ((ShapeEntryP, GenericP));
extern void			shape_entry_resolve_undefined
	PROTO_S ((ShapeEntryP, GenericP));
extern void			shape_entry_hide_all_defd
	PROTO_S ((ShapeEntryP, GenericP));
extern void			shape_entry_suppress_mult
	PROTO_S ((ShapeEntryP, GenericP));
extern void			shape_entry_lib_suppress_mult
	PROTO_S ((ShapeEntryP, GenericP));
extern void			shape_entry_show_content
	PROTO_S ((ShapeEntryP, GenericP));

#endif /* !defined (H_SHAPE_ENTRY) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
