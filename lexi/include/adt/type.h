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

struct TypeT {
	bool mapped;
	bool predefined;
	NStringT mapping;
};

struct TypeT *type_create(bool);
void type_map(struct TypeT *, NStringT *);

#endif

