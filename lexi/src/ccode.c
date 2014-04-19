/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>
#include <stdio.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>

#include <adt/instruction.h>
#include <adt/nametrans.h>

#include "ccode.h"

CcodeItemT *
ccodeitem_create(CcodeItemTypeT item_type)
{
	CcodeItemT *ccode_item;

	ccode_item = ALLOCATE(CcodeItemT);
	ccode_item->item_type=item_type;
	ccode_item->next=NULL;

	return ccode_item;
}

static NStringT *
ccodeitem_name(CcodeItemT *ccode_item)
{
	return &ccode_item->name;
}

static void
ccodeitem_destroy(CcodeItemT *ccode_item)
{
	switch (ccode_item->item_type) {
	case Ccode_identifier:
	case Ccode_string:
		nstring_destroy(ccodeitem_name(ccode_item));
		break;
	case Ccode_at:
		/* do nothing */
		;
	}

	DEALLOCATE(ccode_item);
}

void
ccode_init(CcodeT *c)
{
	c->head = NULL;
	c->tail = &c->head;
}

void ccode_assign(CcodeT* to, CcodeT* from)
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
ccode_append_ccodeitem(CcodeT *ccode, CcodeItemT *ccode_item)
{
	*(ccode->tail) = ccode_item;
	ccode->tail = &ccode_item->next;
}

void
ccode_append_at(CcodeT *ccode)
{
	CcodeItemT *ccode_item;

	ccode_item = ccodeitem_create(Ccode_at);
	ccode_append_ccodeitem(ccode, ccode_item);
}

void
ccode_append_identifier(CcodeT *ccode, NStringT *i)
{
	CcodeItemT *ccode_item;

	ccode_item = ccodeitem_create(Ccode_identifier);
	nstring_assign(ccodeitem_name(ccode_item), i);
	ccode_append_ccodeitem(ccode, ccode_item);
}

void
ccode_append_reference(CcodeT *ccode, NStringT *i)
{
	CcodeItemT *ccode_item;

	ccode_item = ccodeitem_create(Ccode_reference);
	nstring_assign(ccodeitem_name(ccode_item), i);
	ccode_append_ccodeitem(ccode, ccode_item);
}

void
ccode_append_string(CcodeT *ccode, NStringT *s)
{
	CcodeItemT *ccode_item;

	ccode_item = ccodeitem_create(Ccode_string);
	nstring_assign(ccodeitem_name(ccode_item), s);
	ccode_append_ccodeitem(ccode, ccode_item);
}

void ccode_destroy(CcodeT *c)
{
	CcodeItemT *it;

	it = c->head;
	for (it = c->head; it != NULL; it = it->next) {
		ccodeitem_destroy(it);
	}
}

static void
ccodeitem_output(FILE *file, CcodeItemT *ccode_item, struct NameTransT *trans, int d)
{
	char *s;
	arg *to;
	switch (ccode_item->item_type) {
		case Ccode_at:
			fputs("@", file);
			break;

		case Ccode_string:
			s = nstring_to_cstring(ccodeitem_name(ccode_item));
			fputs(s, file);
			DEALLOCATE(s)
			break;

		case Ccode_identifier:
			to = nametrans_translate(trans, ccodeitem_name(ccode_item));
			arg_output(to, false, d, file);
			break;

		case Ccode_reference:
			to = nametrans_translate(trans, ccodeitem_name(ccode_item));
			arg_output(to, true, d,file);
			break;
/* XXX:
			fprintf(file,"/" "* Not implemented yet: Identifier @s. Have to recover passing name. *" "/", s);
			DEALLOCATE(s)
*/
			break;
	}
}

void
ccode_output(FILE *file, CcodeT *ccode, struct NameTransT *trans, int d)
{
	CcodeItemT *it;
	for (it = ccode->head; it != NULL; it = it->next) {
		ccodeitem_output(file, it, trans, d);
	}
}

