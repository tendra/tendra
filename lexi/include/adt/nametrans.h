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

struct TypeTupleT;

struct arg_tag;
struct args_list_tag;

typedef struct NameTransEntryT {
	NStringT from;
	struct arg_tag *to;
} NameTransEntryT;

typedef struct NameTransT {
	NameTransEntryT *tab;
	unsigned int size;
	unsigned int capacity;
} NameTransT;

void nametrans_init(NameTransT *, unsigned int);
void nametrans_destroy(NameTransT *);
void nametrans_sort(NameTransT *);
void nametrans_append_tuple(NameTransT *, struct TypeTupleT *, struct args_list_tag *);
struct arg_tag *nametrans_translate(NameTransT *, NStringT *);

#endif

