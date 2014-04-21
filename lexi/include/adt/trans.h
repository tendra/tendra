/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_TRANS_H
#define LEXI_TRANS_H

#include <stdbool.h>

#include <exds/common.h>
#include <exds/dstring.h>

struct arg;
struct args_list;
struct param;

struct trans {
	NStringT from;
	struct arg *to;
	struct trans *next;
};

void trans_add(struct trans **, struct param *, struct args_list *);
void trans_destroy(struct trans *);
struct arg *trans_find(struct trans *, NStringT *);

#endif

