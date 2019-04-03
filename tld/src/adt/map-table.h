/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * map-table.h - Mapping table ADT.
 *
 * See the file "map-table.c" for more information.
 */

/* Mapping tables only exist as part of entries in a unit set table. */

#ifndef H_MAP_TABLE
#define H_MAP_TABLE

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>
#include "map-entry.h"

#define MAP_TABLE_SIZE	(11)

typedef struct MapTableT {
    MapEntryT *		contents[MAP_TABLE_SIZE];
} MapTableT;

extern MapTableT *	map_table_create
(void);
extern MapEntryT *	map_table_add
(MapTableT *, NStringT *, unsigned);
extern MapEntryT *	map_table_get
(MapTableT *, NStringT *);
extern void			map_table_iter
(MapTableT *, void(*)(MapEntryT *, void *), void *);

#endif /* !defined (H_MAP_TABLE) */
