/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_TYPE_H
#define LEXI_TYPE_H

#include <stdbool.h>

#include <exds/common.h>
#include <exds/dstring.h>

struct type {
	bool mapped;
	bool predefined;
	NStringT mapping;
};

struct type *type_create(bool);
void type_map(struct type *, NStringT *);

#endif

