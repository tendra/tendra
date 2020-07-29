/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * table.h - Identifier table ADT.
 *
 * See the file "table.c" for more information.
 */

#ifndef H_TABLE
#define H_TABLE

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dstring.h>
#include "entry.h"
#include <exds/ostream.h>
#include "key.h"

/* To avoid cicularity: */
struct GrammarT;

#define TABLE_SIZE	(127)


/* 
 * TableT holds most of the information about a grammar, rules,
 * actions, terminals, non-local names, types and local names along
 * with their scopes.
 */

typedef struct TableT {
    EntryT *			contents[TABLE_SIZE];
} TableT;

void	table_init(TableT *);
EntryT *	table_add_type(TableT *, NStringT *, bool);
EntryT *	table_add_basic(TableT *, NStringT *, struct GrammarT *, bool);
EntryT *	table_add_action(TableT *, NStringT *, bool);
EntryT *	table_add_rule(TableT *, NStringT *);
EntryT *	table_add_generated_rule(TableT *, bool);
EntryT *	table_add_name(TableT *, NStringT *);
EntryT *	table_add_generated_name(TableT *);
EntryT *	table_add_rename(TableT *);
EntryT *	table_add_non_local(TableT *, NStringT *, EntryT *);
EntryT *	table_get_entry(TableT *, NStringT *);
EntryT *	table_get_type(TableT *, NStringT *);
EntryT *	table_get_basic(TableT *, NStringT *);
EntryT *	table_get_basic_by_number(TableT *, unsigned);
EntryT *	table_get_action(TableT *, NStringT *);
EntryT *	table_get_rule(TableT *, NStringT *);
void	table_iter(TableT *, void(*)(EntryT *, void *), void *);
void	table_untrace(TableT *);
void	table_unlink_untraced_rules(TableT *);

#endif /* !defined (H_TABLE) */
