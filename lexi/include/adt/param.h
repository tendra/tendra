/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_PARAM_H
#define LEXI_PARAM_H

#include <shared/bool.h>

struct param {
	struct entry *et;
	char *local_name;
	bool is_ref;
	struct param *next;
};

void param_append(struct param **, char *, struct entry *, bool);
struct param *param_name_is_in(struct param *, const char *);
unsigned int param_length(struct param *);
int param_assign_names(struct param *, struct param *);
int param_match(struct param *, struct param *);
void param_destroy(struct param *);
int param_findindex(struct param *, const char *);

#endif

