/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_TYPETUPLE_H
#define LEXI_TYPETUPLE_H

#include <stdbool.h>

#include <exds/common.h>
#include <exds/dstring.h>

struct TypeTupleEntryT {
	struct entry *et;
	NStringT local_name; /* The type NSTringT* will probably not be the final type */
	bool is_ref;
	struct TypeTupleEntryT *next;
};

struct TypeTupleT {
	struct TypeTupleEntryT *head;
	struct TypeTupleEntryT **tail;
	unsigned int length;
};

struct TypeTupleEntryT *typetupleentry_create(NStringT *, struct entry *, bool);
void typetupleentry_destroy(struct TypeTupleEntryT *);

void typetuple_init(struct TypeTupleT *);
struct TypeTupleEntryT *typetuple_name_is_in(struct TypeTupleT *, NStringT *);
void typetuple_append(struct TypeTupleT *, struct TypeTupleEntryT *);
void typetuple_assign(struct TypeTupleT *, struct TypeTupleT *);
int typetuple_length(struct TypeTupleT *);
int typetuple_assign_names(struct TypeTupleT *, struct TypeTupleT *);
int typetuple_match(struct TypeTupleT *, struct TypeTupleT *);
void typetuple_destroy(struct TypeTupleT *);

#endif

