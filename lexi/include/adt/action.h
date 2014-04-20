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

#include "typetuple.h" /* XXX */

struct code;

struct action {
	struct TypeTupleT in;
	struct TypeTupleT out;
	struct code *code;
	BoolT defined;
};

struct action *action_create(void);
void action_set_inputs(struct action *act, struct TypeTupleT *tuple);
void action_set_outputs(struct action *act, struct TypeTupleT *tuple);
struct TypeTupleT *action_get_inputs(struct action *act);
struct TypeTupleT *action_get_outputs(struct action *act);
struct code *action_get_code(struct action *act);
void action_set_code(struct action *act, struct code *);
int action_is_defined(struct action *act);
void action_set_define(struct action *act);

#endif

