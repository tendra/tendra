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


/*** map-table.c --- Mapping table ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the mapping table routines used by the TDF linker.
 *
 *** Change Log:
 * $Log: map-table.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:19  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:23  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:46:31  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:33  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "map-table.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

MapTableP
map_table_create PROTO_Z ()
{
    MapTableP table = ALLOCATE (MapTableT);
    unsigned  i;

    for (i = 0; i < MAP_TABLE_SIZE; i ++) {
	table->contents [i] = NIL (MapEntryP);
    }
    return (table);
}

MapEntryP
map_table_add PROTO_N ((table, key, count))
	      PROTO_T (MapTableP table X
		       NStringP  key X
		       unsigned  count)
{
    unsigned  hash_value = (nstring_hash_value (key) % MAP_TABLE_SIZE);
    MapEntryP next       = (table->contents [hash_value]);
    MapEntryP entry      = map_entry_create (key, next, count);

    table->contents [hash_value] = entry;
    return (entry);
}

MapEntryP
map_table_get PROTO_N ((table, key))
	      PROTO_T (MapTableP table X
		       NStringP  key)
{
    unsigned  hash_value = (nstring_hash_value (key) % MAP_TABLE_SIZE);
    MapEntryP entry      = (table->contents [hash_value]);

    while (entry) {
	if (nstring_equal (key, map_entry_key (entry))) {
	    return (entry);
	}
	entry = map_entry_next (entry);
    }
    return (NIL (MapEntryP));
}

void
map_table_iter PROTO_N ((table, proc, closure))
	       PROTO_T (MapTableP table X
			void    (*proc) PROTO_S ((MapEntryP, GenericP)) X
			GenericP  closure)
{
    unsigned i;

    for (i = 0; i < MAP_TABLE_SIZE; i ++) {
	MapEntryP entry = (table->contents [i]);

	while (entry) {
	    (*proc) (entry, closure);
	    entry = map_entry_next (entry);
	}
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
