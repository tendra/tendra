/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef LEXI_CODE_H
#define LEXI_CODE_H

#include "exds/common.h"
#include "exds/dstring.h"

struct param;
struct arg;

enum code_kind {
	CODE_STRING,
	CODE_IDENT,
	CODE_REF,
	CODE_AT
};

struct code {
	enum code_kind kind;
	NStringT name;
	struct code *next;
};

void code_append_at(struct code **);
void code_append_ident(struct code **, NStringT *);
void code_append_ref(struct code **, NStringT *i);
void code_append_string(struct code **, NStringT *);
void code_destroy(struct code *);
void code_out(FILE *, struct code *,
	struct arg *rhs, struct param *in,
	struct arg *lhs, struct param *out,
	int);

#endif

