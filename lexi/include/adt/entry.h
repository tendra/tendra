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

enum entry_kind {
	entry_action,
	entry_type,
	entry_local_name
};

struct EntryT {
	NStringT key;
	enum entry_kind entry_kind;
	union {
	      struct ActionT *action;
	      struct TypeT *type;
	} u;
	struct EntryT *next;
};

struct EntryT *entry_create(NStringT *);
int entry_is_type(struct EntryT *);
int entry_is_action(struct EntryT *);
int entry_is_localname(struct EntryT *);
NStringT *entry_key(struct EntryT *);
void entry_set_type(struct EntryT *, struct TypeT *);
void entry_set_action(struct EntryT *, struct ActionT *);
struct TypeT *entry_get_type(struct EntryT *);
struct ActionT *entry_get_action(struct EntryT *);

struct EntryT *table_get_entry(struct EntryT **, NStringT *);
struct EntryT *table_add_local_name(struct EntryT **, NStringT *);
struct EntryT *table_get_type(struct EntryT **, NStringT *);
struct EntryT *table_add_type(struct EntryT **, NStringT *, bool);
struct EntryT *table_add_action(struct EntryT **, NStringT *, struct TypeTupleT *, struct TypeTupleT *);

#endif

