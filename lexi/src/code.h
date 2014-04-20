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

struct NameTransT;

enum code_kind {
	CODE_STRING,
	CODE_IDENT,
	CODE_REF,
	CODE_AT
};

struct code_item {
	enum code_kind kind;
	NStringT name;
	struct code_item *next;
};

struct code {
	struct code_item *head;
	struct code_item **tail;
};

void code_init(struct code *);
void code_assign(struct code *, struct code *);
void code_append_at(struct code *);
void code_append_ident(struct code *, NStringT *);
void code_append_ref(struct code *code, NStringT *i);
void code_append_string(struct code *, NStringT *);
void code_destroy(struct code *c);
void code_out(FILE *, struct code *, struct NameTransT *, int);

#endif

