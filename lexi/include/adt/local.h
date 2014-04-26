/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_LOCAL_H
#define LEXI_LOCAL_H

#include <exds/common.h>
#include <exds/dstring.h>

struct entry;

/*
 * Each entry here stores the types of the local names used in actions
 * so we can type check during parsing.
 */
struct local {
	NStringT name;
	struct entry *et;
	struct local *next;
};

void local_add(struct local **, NStringT *, struct entry *);
struct entry *local_find(struct local *, NStringT *);

#endif

