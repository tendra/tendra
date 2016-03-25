/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * name-table.h - Name table ADT.
 *
 * See the file "name-table.c" for more information.
 */

#ifndef H_NAME_TABLE
#define H_NAME_TABLE

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>
#include "name-entry.h"
#include "name-key.h"

struct ShapeEntryT;

#define NAME_TABLE_SIZE	(31)

typedef struct NameTableT {
    NameEntryT *		contents[NAME_TABLE_SIZE];
} NameTableT;

extern NameTableT *	name_table_create
(void);
extern void			name_table_add_rename
(NameTableT *, NameKeyT *, NameKeyT *);
extern void			name_table_resolve_renames
(NameTableT *, NStringT *, bool);
extern NameEntryT *	name_table_add
(NameTableT *, NameKeyT *, struct ShapeEntryT *);
extern NameEntryT *	name_table_get
(NameTableT *, NameKeyT *);
extern void			name_table_iter
(NameTableT *, void(*)(NameEntryT *, void *), void *);
extern void			name_table_deallocate
(NameTableT *);

#endif /* !defined (H_NAME_TABLE) */
