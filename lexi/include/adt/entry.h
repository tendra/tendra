/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_ENTRY_H
#define LEXI_ENTRY_H

#include <exds/common.h>
#include <exds/dstring.h>

struct action;
struct param;

enum entry_kind {
	ENTRY_ACTION,
	ENTRY_TYPE,
	ENTRY_LOCAL
};

struct entry {
	NStringT key;
	enum entry_kind kind;
	union {
		struct action *act;
	} u;
	struct entry *next;
};

struct entry *table_get_entry(struct entry **, NStringT *);
struct entry *table_add_local_name(struct entry **, NStringT *);
struct entry *table_get_type(struct entry **, NStringT *);
struct entry *table_add_type(struct entry **, NStringT *);
struct entry *table_add_action(struct entry **, NStringT *, struct param *, struct param *);

#endif

