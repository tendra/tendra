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


/*** shape-table.c --- Shape table ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the shape table routines used by the TDF linker.
 *
 *** Change Log:
 * $Log: shape-table.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:20  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:34  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:46:50  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:38  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "shape-table.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

ShapeTableP
shape_table_create PROTO_Z ()
{
    ShapeTableP table = ALLOCATE (ShapeTableT);
    unsigned    i;

    for (i = 0; i < SHAPE_TABLE_SIZE; i ++) {
	table->contents [i] = NIL (ShapeEntryP);
    }
    table->token_entry = NIL (ShapeEntryP);
    table->tag_entry   = NIL (ShapeEntryP);
    return (table);
}

ShapeEntryP
shape_table_add PROTO_N ((table, key))
		PROTO_T (ShapeTableP table X
			 NStringP    key)
{
    unsigned     hash_value = (nstring_hash_value (key) % SHAPE_TABLE_SIZE);
    ShapeEntryP *entryp     = &(table->contents [hash_value]);
    ShapeEntryP  entry;

    while ((entry = *entryp) != NIL (ShapeEntryP)) {
	if (nstring_equal (key, shape_entry_key (entry))) {
	    return (entry);
	}
	entryp = shape_entry_next_ref (entry);
    }
    entry   = shape_entry_create (key);
    *entryp = entry;
    return (entry);
}

ShapeEntryP
shape_table_get PROTO_N ((table, key))
		PROTO_T (ShapeTableP table X
			 NStringP    key)
{
    unsigned    hash_value = (nstring_hash_value (key) % SHAPE_TABLE_SIZE);
    ShapeEntryP entry      = (table->contents [hash_value]);

    while (entry) {
	if (nstring_equal (key, shape_entry_key (entry))) {
	    return (entry);
	}
	entry = shape_entry_next (entry);
    }
    return (NIL (ShapeEntryP));
}

ShapeEntryP
shape_table_get_token_entry PROTO_N ((table))
			    PROTO_T (ShapeTableP table)
{
    if (table->token_entry == NIL (ShapeEntryP)) {
	NStringT nstring;

	nstring_copy_cstring (&nstring, "token");
	table->token_entry = shape_table_get (table, &nstring);
	nstring_destroy (&nstring);
    }
    return (table->token_entry);
}

ShapeEntryP
shape_table_get_tag_entry PROTO_N ((table))
			  PROTO_T (ShapeTableP table)
{
    if (table->tag_entry == NIL (ShapeEntryP)) {
	NStringT nstring;

	nstring_copy_cstring (&nstring, "tag");
	table->tag_entry = shape_table_get (table, &nstring);
	nstring_destroy (&nstring);
    }
    return (table->tag_entry);
}

void
shape_table_iter PROTO_N ((table, proc, closure))
		 PROTO_T (ShapeTableP table X
			  void      (*proc) PROTO_S ((ShapeEntryP, GenericP)) X
			  GenericP    closure)
{
    unsigned i;

    for (i = 0; i < SHAPE_TABLE_SIZE; i ++) {
	ShapeEntryP entry = (table->contents [i]);

	while (entry) {
	    (*proc) (entry, closure);
	    entry = shape_entry_next (entry);
	}
    }
}

void
shape_table_deallocate PROTO_N ((table))
		       PROTO_T (ShapeTableP table)
{
    unsigned i;

    for (i = 0; i < SHAPE_TABLE_SIZE; i ++) {
	ShapeEntryP entry = (table->contents [i]);

	while (entry) {
	    entry = shape_entry_deallocate (entry);
	}
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
