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

#include "../ccode.h"
#include "typetuple.h" /* XXX */

struct arg_tag;
struct args_list_tag;

struct TypeTupleT;

typedef struct ActionT {
	struct TypeTupleT inputs;
	struct TypeTupleT outputs;
	CcodeT code;
	BoolT defined;
} ActionT;

ActionT *action_create(void);
void action_set_inputs(ActionT *action, struct TypeTupleT *tuple);
void action_set_outputs(ActionT *action, struct TypeTupleT *tuple);
TypeTupleT *action_get_inputs(ActionT *);
TypeTupleT *action_get_outputs(ActionT *);
CcodeT *action_get_code(ActionT *);
void action_set_code(ActionT *, CcodeT *);
int action_is_defined(ActionT *);
void action_set_define(ActionT *);

#endif

