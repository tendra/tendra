/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_PARAM_H
#define LEXI_PARAM_H

#include <stdbool.h>

#include <exds/common.h>
#include <exds/dstring.h>

struct param {
	struct entry *et;
	NStringT local_name; /* The type NSTringT* will probably not be the final type */
	bool is_ref;
	struct param *next;
};

void param_append(struct param **, NStringT *, struct entry *, bool);
struct param *param_name_is_in(struct param *, NStringT *);
unsigned int param_length(struct param *);
int param_assign_names(struct param *, struct param *);
int param_match(struct param *, struct param *);
void param_destroy(struct param *);

#endif

