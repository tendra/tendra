/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_ACTION_H
#define LEXI_ACTION_H

#include <shared/bool.h>

struct code;
struct param;

struct action {
	struct param *in;
	struct param *out;
	struct code *code;
	bool defined;
};

struct action *action_create(struct param *in, struct param *out);

#endif

