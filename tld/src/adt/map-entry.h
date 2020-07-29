/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * map-entry.h - Mapping table entry ADT.
 *
 * See the file "map-entry.c" for more information.
 */

#ifndef H_MAP_ENTRY
#define H_MAP_ENTRY

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>

typedef struct MapLinkT {
    unsigned			internal;
    unsigned			external;
} MapLinkT;

typedef struct MapEntryT {
    struct MapEntryT	       *next;
    NStringT			key; /* shape name */

    /* This contains the unit scope identifier limit for the shape in
       the unit that contains the table that the entry is an entry
       in. */
    unsigned			count;

    /* This contains the number of unit scope to capsule scope
       identifier mappings for the shape in the unit that contains the
       table that the entry is an entry in. */
    unsigned			num_links;

    /* This contains the unit scope to capsule scope identifier
       mappings for the shape in the unit that contains the table that
       the entry is an entry in. */
    MapLinkT *		links;
} MapEntryT;

extern MapEntryT *	map_entry_create
(NStringT *, MapEntryT *, unsigned);
extern MapEntryT *	map_entry_next
(MapEntryT *);
extern NStringT *		map_entry_key
(MapEntryT *);
extern void			map_entry_set_num_links
(MapEntryT *, unsigned);
extern void			map_entry_set_link
(MapEntryT *, unsigned, unsigned, unsigned);
extern unsigned			map_entry_get_count
(MapEntryT *);
extern unsigned			map_entry_get_num_links
(MapEntryT *);
extern void			map_entry_get_link
(MapEntryT *, unsigned, unsigned *, unsigned *);

extern void			map_entry_check_non_empty
(MapEntryT *, void *);

#endif /* !defined (H_MAP_ENTRY) */
