/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <adt/arg.h>
#include <adt/trans.h>
#include <adt/typetuple.h>

static void
trans_append(struct trans **p, NStringT *from, struct arg *to)
{
	struct trans *t;

	assert(p != NULL);

	/* XXX: suspicious. why isn't this a set? */
	while (*p != NULL) {
		p = &(*p)->next;
	}

	t = xmalloc(sizeof *t);
	t->to   = to;
	t->next = *p;

	nstring_assign(&t->from, from);

	*p = t;
}

void
trans_add(struct trans **t, struct TypeTupleT *tuple, struct args_list *l)
{
	struct TypeTupleEntryT *p;
	struct arg *q;

	assert(t != NULL);

	for (p = tuple->head, q = l->head; p != NULL && q != NULL; p = p->next, q = q->next) {
		trans_append(t, &p->local_name, q);
	}

	/* TODO: assert(!p&&!q) */
}

void
trans_destroy(struct trans *t)
{
	struct trans *p, *next;

	for (p = t; p != NULL; p = p->next) {
		next = p->next;

		xfree(p);
	}
}

struct arg *
trans_find(struct trans *t, NStringT *key)
{
	struct trans *p;

	for (p = t; p != NULL; p = p->next) {
		if (nstring_compare(&p->from, key)) {
			return p->to;
		}
	}

	return NULL;
}

