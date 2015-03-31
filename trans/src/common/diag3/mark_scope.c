/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/bool.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/externs.h>

#include "dg_aux.h"
#include "mark_scope.h"
#include "diaginfo1.h"

static exp
previous_scope(exp e)
{
	if (!last(e) || bro(e) == NULL) {
		return NULL;
	}

	if (bro(e)->tag == diagnose_tag && (props(bro(e)) & 0x7) == 1) {
		return previous_scope(bro(e));
	}

	if (bro(e)->tag == diagnose_tag) {
		return bro(e);
	}

	if (bro(e)->tag == ident_tag && last(bro(e))) {
		if (bro(bro(e)) == NULL) {
			return NULL;
		}

		if (bro(bro(e))->tag == diagnose_tag &&
		    (props(bro(bro(e))) & 0x7) == 1) {
			return previous_scope(bro(bro(e)));
		}

		if (bro(bro(e))->tag == diagnose_tag) {
			return bro(bro(e));
		}

		return NULL;
	}

	return NULL;
}

static int
param_scope(exp e)
{
	diag_info *d = dno(e);
	if (d->key == DIAG_INFO_ID) {
		return isparam(son(d->data.id_scope.access));
	}

	return 0;
}

static int
needs_hiding(exp a, exp b)
{
	diag_info *da = dno(a);
	diag_info *db = dno(b);

	if (da->key != db->key) {
		return 0;
	}

	switch (da->key) {
	case DIAG_INFO_ID:
		return streq(da->data.id_scope.nme.ints.chars,
		               db->data.id_scope.nme.ints.chars);

	case DIAG_INFO_TYPE:
		return streq(da->data.type_scope.nme.ints.chars,
		               db->data.type_scope.nme.ints.chars);

	case DIAG_INFO_TAG:
		return streq(da->data.tag_scope.nme.ints.chars,
		               db->data.tag_scope.nme.ints.chars);

	default:
		return 0;
	}
}

void
mark_scope(exp e)
{
	exp scope = e;

	if (param_scope(e)) {
		return;
	}

	for (;;) {
		scope = previous_scope(scope);

		if (scope == NULL || param_scope(scope) ||
		    needs_hiding(e, scope)) {
			props(e) = (prop) (props(e) | 0x80);
			return;
		}

		if (props(scope) & 0x80) {
			return;
		}
	}
}

