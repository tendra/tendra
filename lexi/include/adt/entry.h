/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_ENTRY_H
#define LEXI_ENTRY_H

#include <stdbool.h>

#include <exds/common.h>
#include <exds/dstring.h>

struct ActionT;
struct TypeT;
struct TypeTupleT;

typedef struct EntryT {
	NStringT key;
	enum { entry_action, entry_type, entry_local_name } entry_kind;
	union {
	      struct ActionT *action;
	      struct TypeT *type;
	} u;
	struct EntryT *next;
} EntryT;

EntryT *entry_create(NStringT *);
int entry_is_type(EntryT *);
int entry_is_action(EntryT *);
int entry_is_localname(EntryT *);
NStringT *entry_key(EntryT *);
void entry_set_type(EntryT *, struct TypeT *);
void entry_set_action(EntryT *, struct ActionT *);
struct TypeT *entry_get_type(EntryT *);
struct ActionT *entry_get_action(EntryT *);

EntryT *table_get_entry(EntryT **, NStringT *);
EntryT *table_add_local_name(EntryT **, NStringT *);
EntryT *table_get_type(EntryT **, NStringT *);
EntryT *table_add_type(EntryT **, NStringT *, bool);
EntryT *table_add_action(EntryT **, NStringT *, struct TypeTupleT *, struct TypeTupleT *);

#endif

