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


/*** map-entry.h --- Mapping table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "map-entry.c" for more information.
 *
 *** Change Log:
 * $Log: map-entry.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:19  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:46:29  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:33  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_MAP_ENTRY
#define H_MAP_ENTRY

#include "os-interface.h"
#include "dalloc.h"
#include "dstring.h"

/*--------------------------------------------------------------------------*/

typedef struct MapLinkT {
    unsigned			internal;
    unsigned			external;
} MapLinkT, *MapLinkP;

typedef struct MapEntryT {
    struct MapEntryT	       *next;
    NStringT			key;
    unsigned			count;
    unsigned			num_links;
    MapLinkP			links;
} MapEntryT, *MapEntryP;

/*--------------------------------------------------------------------------*/

extern MapEntryP		map_entry_create
	PROTO_S ((NStringP, MapEntryP, unsigned));
extern MapEntryP		map_entry_next
	PROTO_S ((MapEntryP));
extern NStringP			map_entry_key
	PROTO_S ((MapEntryP));
extern void			map_entry_set_num_links
	PROTO_S ((MapEntryP, unsigned));
extern void			map_entry_set_link
	PROTO_S ((MapEntryP, unsigned, unsigned, unsigned));
extern unsigned			map_entry_get_count
	PROTO_S ((MapEntryP));
extern unsigned			map_entry_get_num_links
	PROTO_S ((MapEntryP));
extern void			map_entry_get_link
	PROTO_S ((MapEntryP, unsigned, unsigned *, unsigned *));

extern void			map_entry_check_non_empty
	PROTO_S ((MapEntryP, GenericP));

#endif /* !defined (H_MAP_ENTRY) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
