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


/*** map-entry.c --- Mapping table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the mapping table entry routines used by the TDF
 * linker.
 *
 *** Change Log:
 * $Log: map-entry.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:21  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:46:27  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:32  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "map-entry.h"
#include "shape-table.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

MapEntryP
map_entry_create PROTO_N ((key, next, count))
		 PROTO_T (NStringP  key X
			  MapEntryP next X
			  unsigned  count)
{
    MapEntryP entry = ALLOCATE (MapEntryT);

    entry->next  = next;
    nstring_copy (&(entry->key), key);
    entry->count = count;
    return (entry);
}

MapEntryP
map_entry_next PROTO_N ((entry))
	       PROTO_T (MapEntryP entry)
{
    return (entry->next);
}

NStringP
map_entry_key PROTO_N ((entry))
	      PROTO_T (MapEntryP entry)
{
    return (&(entry->key));
}

void
map_entry_set_num_links PROTO_N ((entry, num_links))
			PROTO_T (MapEntryP entry X
				 unsigned  num_links)
{
    entry->num_links = num_links;
    entry->links     = ALLOCATE_VECTOR (MapLinkT, num_links);
}

void
map_entry_set_link PROTO_N ((entry, link, internal, external))
		   PROTO_T (MapEntryP entry X
			    unsigned  link X
			    unsigned  internal X
			    unsigned  external)
{
    ASSERT (link < entry->num_links);
    entry->links [link].internal = internal;
    entry->links [link].external = external;
}

unsigned
map_entry_get_count PROTO_N ((entry))
		    PROTO_T (MapEntryP entry)
{
    return (entry->count);
}

unsigned
map_entry_get_num_links PROTO_N ((entry))
			PROTO_T (MapEntryP entry)
{
    return (entry->num_links);
}

void
map_entry_get_link PROTO_N ((entry, link, internal_ref, external_ref))
		   PROTO_T (MapEntryP entry X
			    unsigned  link X
			    unsigned *internal_ref X
			    unsigned *external_ref)
{
    ASSERT (link < entry->num_links);
    *internal_ref = entry->links [link].internal;
    *external_ref = entry->links [link].external;
}

/*--------------------------------------------------------------------------*/

void
map_entry_check_non_empty PROTO_N ((entry, gclosure))
			  PROTO_T (MapEntryP entry X
				   GenericP  gclosure)
{
    ShapeTableP table = (ShapeTableP) gclosure;

    if (entry->count > 0) {
	NStringP    key         = map_entry_key (entry);
	ShapeEntryP shape_entry = shape_table_get (table, key);

	shape_entry_set_non_empty (shape_entry);
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
