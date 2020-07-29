/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * unit-table.h - Unit set table ADT.
 *
 * See the file "unit-table.c" for more information.
 */

#ifndef H_UNIT_TABLE
#define H_UNIT_TABLE

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>
#include "unit-entry.h"

#define UNIT_TABLE_SIZE	(11)

typedef struct UnitTableT {
    UnitEntryT *		contents[UNIT_TABLE_SIZE];
} UnitTableT;

extern UnitTableT *	unit_table_create
(void);
extern UnitEntryT *	unit_table_add
(UnitTableT *, NStringT *, unsigned);
extern UnitEntryT *	unit_table_get
(UnitTableT *, NStringT *);
extern void			unit_table_iter
(UnitTableT *, void(*)(UnitEntryT *, void *), void *);

#endif /* !defined (H_UNIT_TABLE) */
