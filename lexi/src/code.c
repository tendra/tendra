/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>
#include <stdio.h>

#include <shared/xalloc.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>

#include <adt/nametrans.h>

#include "code.h"

struct code_item *
codeitem_create(enum code_kind kind)
{
	struct code_item *c;

	c = xmalloc(sizeof *c);
	c ->kind=kind;
	c ->next=NULL;

	return c;
}

static NStringT *
codeitem_name(struct code_item *c)
{
	return &c->name;
}

static void
codeitem_destroy(struct code_item *c)
{
	switch (c->kind) {
	case CODE_IDENT:
	case CODE_STRING:
		nstring_destroy(codeitem_name(c));
		break;

	case CODE_AT:
		/* do nothing */
		break;
	}

	xfree(c);
}

void
code_init(struct code *c)
{
	c->head = NULL;
	c->tail = &c->head;
}

void
code_assign(struct code* to, struct code* from)
{
	if (from->head == NULL) {
		to->head = NULL;
		to->tail = &to->head;
	} else {
		to->head = from->head;
		to->tail = from->tail;
	}
}

static void
code_append_codeitem(struct code *code, struct code_item *c)
{
	*code->tail = c;
	code->tail = &c->next;
}

void
code_append_at(struct code *code)
{
	struct code_item *c;

	c = codeitem_create(CODE_AT);
	code_append_codeitem(code, c);
}

void
code_append_ident(struct code *code, NStringT *i)
{
	struct code_item *c;

	c = codeitem_create(CODE_IDENT);
	nstring_assign(codeitem_name(c), i);
	code_append_codeitem(code, c);
}

void
code_append_ref(struct code *code, NStringT *i)
{
	struct code_item *c;

	c = codeitem_create(CODE_REF);
	nstring_assign(codeitem_name(c), i);
	code_append_codeitem(code, c);
}

void
code_append_string(struct code *code, NStringT *s)
{
	struct code_item *c;

	c = codeitem_create(CODE_STRING);
	nstring_assign(codeitem_name(c), s);
	code_append_codeitem(code, c);
}

void code_destroy(struct code *c)
{
	struct code_item *it;

	it = c->head;
	for (it = c->head; it != NULL; it = it->next) {
		codeitem_destroy(it);
	}
}

static void
codeitem_out(FILE *file, struct code_item *c, struct NameTransT *trans, int d)
{
	char *s;
	struct arg *to;

	switch (c->kind) {
		case CODE_AT:
			fputs("@", file);
			break;

		case CODE_STRING:
			s = nstring_to_cstring(codeitem_name(c));
			fputs(s, file);
			xfree(s);
			break;

		case CODE_IDENT:
			to = nametrans_translate(trans, codeitem_name(c));
			arg_out(to, false, d, file);
			break;

		case CODE_REF:
			to = nametrans_translate(trans, codeitem_name(c));
			arg_out(to, true, d,file);
			break;
/* XXX:
			fprintf(file,"/" "* Not implemented yet: Identifier @s. Have to recover passing name. *" "/", s);
			xfree(s)
*/
			break;
	}
}

void
code_out(FILE *file, struct code *code, struct NameTransT *trans, int d)
{
	struct code_item *it;

	for (it = code->head; it != NULL; it = it->next) {
		codeitem_out(file, it, trans, d);
	}
}

