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


/*** unit-table.c --- Unit set table ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the unit set table routines used by the TDF linker.
 *
 *** Change Log:
 * $Log: unit-table.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:20  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:45  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:47:09  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:40  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "unit-table.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

UnitTableP
unit_table_create PROTO_Z ()
{
    UnitTableP table = ALLOCATE (UnitTableT);
    unsigned   i;

    for (i = 0; i < UNIT_TABLE_SIZE; i ++) {
	table->contents [i] = NIL (UnitEntryP);
    }
    return (table);
}

UnitEntryP
unit_table_add PROTO_N ((table, key, order))
	       PROTO_T (UnitTableP table X
			NStringP   key X
			unsigned   order)
{
    unsigned   hash_value = (nstring_hash_value (key) % UNIT_TABLE_SIZE);
    UnitEntryP next       = (table->contents [hash_value]);
    UnitEntryP entry      = unit_entry_create (key, next, order);

    table->contents [hash_value] = entry;
    return (entry);
}

UnitEntryP
unit_table_get PROTO_N ((table, key))
	       PROTO_T (UnitTableP table X
			NStringP   key)
{
    unsigned   hash_value = (nstring_hash_value (key) % UNIT_TABLE_SIZE);
    UnitEntryP entry      = (table->contents [hash_value]);

    while (entry && (!nstring_equal (key, unit_entry_key (entry)))) {
	entry = unit_entry_next (entry);
    }
    return (entry);
}

void
unit_table_iter PROTO_N ((table, proc, closure))
		PROTO_T (UnitTableP table X
			 void     (*proc) PROTO_S ((UnitEntryP, GenericP)) X
			 GenericP   closure)
{
    unsigned i;

    for (i = 0; i < UNIT_TABLE_SIZE; i ++) {
	UnitEntryP entry = (table->contents [i]);

	while (entry) {
	    (*proc) (entry, closure);
	    entry = unit_entry_next (entry);
	}
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
