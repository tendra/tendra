/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_NAMETRANS_H
#define LEXI_NAMETRANS_H

#include <stdbool.h>

#include <exds/common.h>
#include <exds/dstring.h>

struct arg;
struct args_list;
struct TypeTupleT;

struct NameTransEntryT {
	NStringT from;
	struct arg *to;
};

struct NameTransT {
	struct NameTransEntryT *tab;
	unsigned int size;
	unsigned int capacity;
};

void nametrans_init(struct NameTransT *, unsigned int);
void nametrans_destroy(struct NameTransT *);
void nametrans_sort(struct NameTransT *);
void nametrans_append_tuple(struct NameTransT *, struct TypeTupleT *, struct args_list *);
struct arg *nametrans_translate(struct NameTransT *, NStringT *);

#endif

