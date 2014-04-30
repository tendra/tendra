/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/xalloc.h>

#include <adt/param.h>

void
param_append(struct param **params, char *str, struct entry *et, bool isref)
{
	struct param *p;

	p = xmalloc(sizeof *p);

	p->et         = et;
	p->is_ref     = isref;
	p->local_name = str;
	p->next       = *params;

	while (*params != NULL) {
		params = &(*params)->next;
	}

	*params = p;
}

struct param *
param_name_is_in(struct param *params, const char *id)
{
	struct param *p;

	for (p = params; p != NULL; p = p->next) {
		if (0 == strcmp(p->local_name, id)) {
			return p;
		}
	}

	return NULL;
}

unsigned int
param_length(struct param *params)
{
	struct param *p;
	unsigned int n;

	n = 0;
	for (p = params; p != NULL; p = p->next) {
		n++;
	}

	return n;
}

int
param_match(struct param *a, struct param *b)
{
	struct param *p, *q;

	for (p = a, q = b; p != NULL && q != NULL; p = p->next, q = q->next) {
		if (p->et != q->et || p->is_ref != q->is_ref) {
			return 0;
		}
	}

	return p == NULL && q == NULL;
}

int
param_assign_names(struct param *to, struct param *from)
{
	struct param *p, *q;
	int allhavenames;

	allhavenames = 1;

	for (p = from, q = to; p != NULL && q != NULL; p = p->next, q = q->next) {
		if (p->local_name == NULL) {
			allhavenames = 0;
		} else {
			q->local_name = p->local_name;
			p->local_name = NULL;
		}
	}

	/* TODO: assert(!(p||q))*/

	return allhavenames;
}

void param_destroy(struct param *params)
{
	struct param *p, *next;

	for (p = params; p != NULL; p = next) {
		next = p->next;

		xfree(p->local_name);
		xfree(p);
	}
}

/*
 * This helper function returns true if all names in params and results
 * are unique. It returns false otherewise.
 */
int
param_unique_names(struct param *params, struct param *results)
{
	struct param *p;
	int i;

	for (p = params;  p != NULL; p = p->next, i++) {
		if (param_name_is_in(results, p->local_name)) {
			return 0;
		}
	}

	return 1;
}

int
param_findindex(struct param *params, const char *key)
{
	struct param *p;
	int i;

	for (p = params, i = 0; p != NULL; p = p->next, i++) {
		if (0 == strcmp(p->local_name, key)) {
			return i;
		}
	}

	return -1;
}

