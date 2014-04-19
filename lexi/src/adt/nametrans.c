/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <adt/arg.h>
#include <adt/typetuple.h>
#include <adt/nametrans.h>

void
nametrans_init(struct NameTransT *p, unsigned int s)
{
	p->tab = s == 0 ? NULL : xmalloc_nof(struct NameTransT, s);
	p->size = 0;
	p->capacity = s;
}

void
nametrans_destroy(struct NameTransT* p)
{
	xfree(p->tab);
}

static int
nametrans_cmp(const void *p, const void *q)
{
	struct NameTransEntryT *a = (struct NameTransEntryT *) p;
	struct NameTransEntryT *b = (struct NameTransEntryT *) q;

	switch (nstring_compare(&a->from, &b->from)) EXHAUSTIVE {
	case CMP_LT: return -1;
	case CMP_EQ: return  0;
	case CMP_GT: return  1;
	}

	UNREACHED;
}

void
nametrans_sort(struct NameTransT *p)
{
	qsort(p->tab, p->size, sizeof (struct NameTransEntryT), nametrans_cmp);
}

static void
nametrans_append(struct NameTransT *tr, NStringT *from, struct arg *to)
{
	/* TODO when debugging: Checking tr->size < tr->capacity */
	nstring_assign(&tr->tab[tr->size].from, from);
	tr->tab[tr->size].to = to;
	tr->size++;
}

void
nametrans_append_tuple(struct NameTransT *tr, struct TypeTupleT *tuple, struct args_list *l)
{
	struct TypeTupleEntryT *p;
	struct arg *q;

	for (p = tuple->head, q = l->head; p != NULL && q != NULL; p = p->next, q = q->next) {
		nametrans_append(tr, &p->local_name, q);
	}

	/* TODO: assert(!p&&!q) */
}

struct arg *
nametrans_translate(struct NameTransT *trans, NStringT *key)
{
	int i, j;
	int mid;

	i = 0;
	j = trans->size - 1;

	/* TODO: assert(i < j) */
	mid = (i + j) / 2;

	while (i < j) {
		switch (nstring_compare(&trans->tab[mid].from, key)) {
		case CMP_LT: i = mid + 1; mid = (i + j + 0) / 2; break;
		case CMP_GT: j = mid - 1; mid = (i + j + 1) / 2; break;
		case CMP_EQ:
			return trans->tab[mid].to;
			break;
		}
	}

	if (nstring_compare(&trans->tab[i].from, key) == CMP_EQ) {
		return trans->tab[i].to;
	} else {
		return NULL;
	}
}

