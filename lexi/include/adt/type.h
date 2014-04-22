/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_TYPE_H
#define LEXI_TYPE_H

#include <stdbool.h>

struct type {
	bool predefined;
};

struct type *type_create(bool);

#endif

