/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * shape-table.h - Shape table ADT.
 *
 * See the file "shape-table.c" for more information.
 */

#ifndef H_SHAPE_TABLE
#define H_SHAPE_TABLE

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>
#include "shape-entry.h"

#define SHAPE_TABLE_SIZE	(11)

typedef struct ShapeTableT {
    ShapeEntryT *		token_entry;
    ShapeEntryT *		tag_entry;
    ShapeEntryT *		contents[SHAPE_TABLE_SIZE];
} ShapeTableT;

extern ShapeTableT *	shape_table_create
(void);
extern ShapeEntryT *	shape_table_add
(ShapeTableT *, NStringT *);
extern ShapeEntryT *	shape_table_get
(ShapeTableT *, NStringT *);
extern ShapeEntryT *	shape_table_get_token_entry
(ShapeTableT *);
extern ShapeEntryT *	shape_table_get_tag_entry
(ShapeTableT *);
extern void			shape_table_iter
(ShapeTableT *, void(*)(ShapeEntryT *, void *), void *);
extern void			shape_table_deallocate
(ShapeTableT *);

#endif /* !defined (H_SHAPE_TABLE) */
