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


/*** unit-entry.h --- Unit set table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "unit-entry.c" for more information.
 *
 *** Change Log:
 * $Log: unit-entry.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:20  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:47:07  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:40  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_UNIT_ENTRY
#define H_UNIT_ENTRY

#include "os-interface.h"
#include "dalloc.h"
#include "dstring.h"
#include "map-table.h"
#include "shape-table.h"
#include "tdf-write.h"

/*--------------------------------------------------------------------------*/

typedef struct UnitT {
    struct UnitT	       *next;
    MapTableP			map_table;
    NStringT			contents;
} UnitT, *UnitP;

typedef struct UnitEntryT {
    struct UnitEntryT	       *next;
    NStringT			key;
    unsigned			order;
    UnitP			head;
    UnitP		       *tail;
} UnitEntryT, *UnitEntryP;

typedef struct UnitSetClosureT {
    unsigned			num_unit_sets;
    ShapeTableP			shapes;
} UnitSetClosureT, *UnitSetClosureP;

/*--------------------------------------------------------------------------*/

extern void			unit_set_contents
	PROTO_S ((UnitP, NStringP));
extern MapTableP		unit_map_table
	PROTO_S ((UnitP));

extern UnitEntryP		unit_entry_create
	PROTO_S ((NStringP, UnitEntryP, unsigned));
extern UnitEntryP		unit_entry_next
	PROTO_S ((UnitEntryP));
extern NStringP			unit_entry_key
	PROTO_S ((UnitEntryP));
extern unsigned			unit_entry_order
	PROTO_S ((UnitEntryP));
extern UnitP			unit_entry_add_unit
	PROTO_S ((UnitEntryP, unsigned));

extern void			unit_entry_do_count
	PROTO_S ((UnitEntryP, GenericP));
extern void			unit_entry_write_unit_set
	PROTO_S ((UnitEntryP, UnitEntryP, TDFWriterP));
extern void			unit_entry_write_tld_unit
	PROTO_S ((UnitEntryP, ShapeTableP, TDFWriterP));
extern void			unit_entry_write_units
	PROTO_S ((UnitEntryP, ShapeTableP, unsigned, TDFWriterP));

#endif /* !defined (H_UNIT_ENTRY) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
