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

struct action;
struct type;
struct TypeTupleT;

enum entry_kind {
	ENTRY_ACTION,
	ENTRY_TYPE,
	ENTRY_LOCAL
};

struct entry {
	NStringT key;
	enum entry_kind entry_kind;
	union {
	      struct action *act;
	      struct type *type;
	} u;
	struct entry *next;
};

struct entry *entry_create(NStringT *);
int entry_is_type(struct entry *);
int entry_is_action(struct entry *);
int entry_is_localname(struct entry *);
NStringT *entry_key(struct entry *);
void entry_set_type(struct entry *, struct type *);
void entry_set_action(struct entry *, struct action *act);
struct type *entry_get_type(struct entry *);
struct action *entry_get_action(struct entry *);

struct entry *table_get_entry(struct entry **, NStringT *);
struct entry *table_add_local_name(struct entry **, NStringT *);
struct entry *table_get_type(struct entry **, NStringT *);
struct entry *table_add_type(struct entry **, NStringT *, bool);
struct entry *table_add_action(struct entry **, NStringT *, struct TypeTupleT *, struct TypeTupleT *);

#endif

