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

typedef struct TypeTupleEntryT {
	struct EntryT *type;
	NStringT local_name; /* The type NSTringT* will probably not be the final type */
	bool is_reference;
	struct TypeTupleEntryT *next;
} TypeTupleEntryT;

typedef struct TypeTupleT {
	TypeTupleEntryT *head;
	TypeTupleEntryT **tail;
	unsigned int length;
} TypeTupleT;

TypeTupleEntryT *typetupleentry_create(NStringT *, struct EntryT *, bool);
void typetupleentry_destroy(TypeTupleEntryT *);

void typetuple_init(TypeTupleT *);
TypeTupleEntryT *typetuple_name_is_in(TypeTupleT *, NStringT *);
void typetuple_append(TypeTupleT *, TypeTupleEntryT *);
void typetuple_assign(TypeTupleT *, TypeTupleT *);
int typetuple_length(TypeTupleT *);
int typetuple_assign_names(TypeTupleT *, TypeTupleT *);
int typetuple_match(TypeTupleT *, TypeTupleT *);
void typetuple_destroy(TypeTupleT *);

#endif

