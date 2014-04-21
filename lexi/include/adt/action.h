/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_ACTION_H
#define LEXI_ACTION_H

#include <stdbool.h>

#include <exds/common.h>

struct code;
struct param;

struct action {
	struct param *in;
	struct param *out;
	struct code *code;
	BoolT defined;
};

struct action *action_create(void);
void action_set_inputs(struct action *, struct param *);
void action_set_outputs(struct action *, struct param *);
struct param *action_get_inputs(struct action *);
struct param *action_get_outputs(struct action *);
struct code *action_get_code(struct action *);
void action_set_code(struct action *, struct code *);
int action_is_defined(struct action *);
void action_set_define(struct action *);

#endif

