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
#include "../src/ccode.h" /* XXX */

struct ActionT {
	struct TypeTupleT inputs;
	struct TypeTupleT outputs;
	struct CcodeT code;
	BoolT defined;
};

struct ActionT *action_create(void);
void action_set_inputs(struct ActionT *action, struct TypeTupleT *tuple);
void action_set_outputs(struct ActionT *action, struct TypeTupleT *tuple);
struct TypeTupleT *action_get_inputs(struct ActionT *);
struct TypeTupleT *action_get_outputs(struct ActionT *);
struct CcodeT *action_get_code(struct ActionT *);
void action_set_code(struct ActionT *, struct CcodeT *);
int action_is_defined(struct ActionT *);
void action_set_define(struct ActionT *);

#endif

