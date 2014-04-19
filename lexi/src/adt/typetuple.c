/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>
#include <stdbool.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <exds/common.h>
#include <exds/dstring.h>

#include <adt/typetuple.h>

struct TypeTupleEntryT *
typetupleentry_create(NStringT *str, struct EntryT *type, bool isref)
{
	struct TypeTupleEntryT *p;

	p = xmalloc_nof(struct TypeTupleEntryT, 1);

	nstring_assign(&p->local_name, str);

	p->type = type;
	p->is_reference = isref;
	p->next = NULL;

	return p;
}

void
typetupleentry_destroy(struct TypeTupleEntryT *p)
{
	if (p != NULL) {
		nstring_destroy(&p->local_name);
	}

	xfree(p);
}

void typetuple_init(struct TypeTupleT *ttlist)
{
	ttlist->head   = NULL;
	ttlist->tail   = &ttlist->head;
	ttlist->length = 0;
}

struct TypeTupleEntryT *
typetuple_name_is_in(struct TypeTupleT *tt, NStringT *id)
{
	struct TypeTupleEntryT *it;

	for (it = tt->head; it != NULL; it = it->next) {
		if (nstring_equal(&it->local_name, id)) {
			return it;
		}
	}

	return NULL;
}

void typetuple_append(struct TypeTupleT *ttlist, struct TypeTupleEntryT *tt)
{
	*ttlist->tail = tt;
	ttlist->tail = &tt->next;
	++ttlist->length;
}

void
typetuple_assign(struct TypeTupleT* to, struct TypeTupleT* from)
{
	to->length = from->length;
	if ((to->head = from->head) == NULL) {
		to->tail = &(to->head);
	} else {
		to->tail = from->tail;
	}
}

int
typetuple_length(struct TypeTupleT *tuple)
{
	return tuple->length;
}

int
typetuple_match(struct TypeTupleT *t1, struct TypeTupleT *t2)
{
	struct TypeTupleEntryT *p, *q;

	for (p = t1->head, q = t2->head; p != NULL && q != NULL; p = p->next, q = q->next) {
		if ((p->type != q->type) || (p->is_reference != q->is_reference)) {
			return 0;
		}
	}

	return p == NULL && q == NULL;
}

int
typetuple_assign_names(struct TypeTupleT *to, struct TypeTupleT *from)
{
	struct TypeTupleEntryT *p, *q;
	int allhavenames;

	allhavenames = 1;

	for (p = from->head, q = to->head; p != NULL && q != NULL; p = p->next, q = q->next) {
		if (nstring_length(&p->local_name) == 0) {
			allhavenames = 0;
		} else {
			nstring_assign(&q->local_name, &p->local_name);
			nstring_init(&p->local_name);
		}
	}

	/* TODO: assert(!(p||q))*/

	return allhavenames;
}

void typetuple_destroy(struct TypeTupleT *tuple)
{
	struct TypeTupleEntryT *p;

	for(p = tuple->head; p != NULL; p = p->next) {
		typetupleentry_destroy(p);
	}
}

static int
cmp_tuples_names(void const *p, void const *q)
{
	switch (nstring_compare((NStringT *) p, (NStringT *) q)) EXHAUSTIVE {
	case CMP_LT: return -1;
	case CMP_EQ: return  0;
	case CMP_GT: return  1;
	}

	UNREACHED;
}

/*
 * This helper function returns true if all names in params and results
 * are unique. It returns false otherewise.
 */
int
typetuple_unique_names(struct TypeTupleT *params, struct TypeTupleT *results)
{
	struct TypeTupleEntryT *p;
	NStringT **tab;
	int total_length;
	int i;

	total_length = typetuple_length(params) + typetuple_length(results);
	tab = xmalloc_nof(NStringT*, typetuple_length(params) + typetuple_length(results));

	i = 0;

	for (p = params->head;  p != NULL; p = p->next, i++) {
		tab[i] = &p->local_name;
	}
	for (p = results->head; p != NULL; p = p->next, i++) {
		tab[i] = &p->local_name;
	}

	qsort(tab, total_length, sizeof(NStringT**), &cmp_tuples_names);

	for (i = 0; i < total_length - 1; i++) {
		if (nstring_equal(tab[i], tab[i + 1])) {
			xfree(tab);
			return false;
		}
	}

	xfree(tab);

	return true;
}

