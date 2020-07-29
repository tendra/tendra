/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_ENTRY_H
#define LEXI_ENTRY_H

struct action;
struct param;

enum entry_kind {
	ENTRY_ACTION,
	ENTRY_TYPE,
	ENTRY_LOCAL
};

struct entry {
	char *key;
	enum entry_kind kind;
	union {
		struct action *act;
	} u;
	struct entry *next;
};

struct entry *table_get_entry(struct entry **, char *);
struct entry *table_add_local_name(struct entry **, char *);
struct entry *table_get_type(struct entry **, char *);
struct entry *table_add_type(struct entry **, char *);
struct entry *table_add_action(struct entry **, char *, struct param *, struct param *);

#endif

