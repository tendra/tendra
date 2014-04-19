/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_LOCALNAMES_H
#define LEXI_LOCALNAMES_H

#include <exds/common.h>
#include <exds/dstring.h>

struct entry;

/*
 * This is a trie of chars, the leaves point to a type represented by an entry *, see adt.h
 * This structure stores the types of the local names used in actions so we can type check
 * during parsing.
 */
struct LocalNamesEntryT {
	char c;
	struct LocalNamesEntryT *next;
	struct LocalNamesEntryT *opt;
	struct LocalNamesEntryT *up;
	struct entry *et;
};

struct LocalNamesT {
	struct LocalNamesEntryT *top;
	unsigned int max_depth;
};

struct LocalNamesIteratorT {
	struct LocalNamesEntryT *p;
	int depth;
};

void localnames_init(struct LocalNamesT *);
int localnames_add_nstring(struct LocalNamesT *, NStringT *, struct entry *);
struct entry *localnames_get_type(struct LocalNamesT *, NStringT *);
void localnames_begin(struct LocalNamesIteratorT *, struct LocalNamesT *);
void localnamesiterator_next(struct LocalNamesIteratorT *);

#endif

