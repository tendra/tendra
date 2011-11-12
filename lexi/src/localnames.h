/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef _H_LEXI_LOCAL_NAMES 
#define _H_LEXI_LOCAL_NAMES 

struct EntryT;

/* 
	This is a trie of chars, the leaves point to a type represented by an EntryT*, see adt.h
	This structure stores the types of the local names used in actions so we can type check
	during parsing.
*/
typedef struct LocalNamesEntryT {
	char c;
	struct LocalNamesEntryT* next;
	struct LocalNamesEntryT* opt;
	struct LocalNamesEntryT* up;
	struct EntryT* type;
} LocalNamesEntryT;

typedef struct LocalNamesT {
	LocalNamesEntryT* top;
	unsigned int max_depth ;
} LocalNamesT;

typedef struct LocalNamesIteratorT {
	LocalNamesEntryT* p;
	int depth;
} LocalNamesIteratorT;

extern void localnames_init(LocalNamesT*);
extern int localnames_add_nstring(LocalNamesT*, NStringT*, struct EntryT*);
extern struct EntryT* localnames_get_type(LocalNamesT*, NStringT*);
extern void localnames_begin(LocalNamesIteratorT*, LocalNamesT*);
extern void localnamesiterator_next(LocalNamesIteratorT* );
#endif
