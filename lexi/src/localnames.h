/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_LOCALNAMES_H
#define LEXI_LOCALNAMES_H

struct EntryT;

/*
 * This is a trie of chars, the leaves point to a type represented by an EntryT *, see adt.h
 * This structure stores the types of the local names used in actions so we can type check
 * during parsing.
 */
typedef struct LocalNamesEntryT {
	char c;
	struct LocalNamesEntryT *next;
	struct LocalNamesEntryT *opt;
	struct LocalNamesEntryT *up;
	struct EntryT *type;
} LocalNamesEntryT;

typedef struct LocalNamesT {
	LocalNamesEntryT *top;
	unsigned int max_depth;
} LocalNamesT;

typedef struct LocalNamesIteratorT {
	LocalNamesEntryT *p;
	int depth;
} LocalNamesIteratorT;

void localnames_init(LocalNamesT *);
int localnames_add_nstring(LocalNamesT *, NStringT *, struct EntryT *);
struct EntryT *localnames_get_type(LocalNamesT *, NStringT *);
void localnames_begin(LocalNamesIteratorT *, LocalNamesT *);
void localnamesiterator_next(LocalNamesIteratorT *);

#endif

