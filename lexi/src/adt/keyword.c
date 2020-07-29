/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <string.h>

#include <shared/xalloc.h>
#include <shared/error.h>

#include <adt/keyword.h>
#include <adt/zone.h>
#include <adt/cmd.h>

void
add_keyword(struct zone *z, const char *name, struct cmd *cmd)
{
	struct keyword *p, *q;

	assert(name != NULL);
	assert(strlen(name) > 0);

	p = z->keywords;
	q = NULL;

	while (p) {
		int c;

		c = strcmp(name, p->name);

		if (c == 0) {
			error(ERR_SERIOUS, "Keyword '%s' already defined", name);
			return;
		}

		if (c < 0) {
			break;
		}

		q = p;
		p = p->next;
	}

	p = xmalloc(sizeof *p);
	p->name  = name;
	p->cmd   = cmd;

	if (q == NULL) {
		p->next = z->keywords;
		z->keywords = p;
	} else {
		p->next = q->next;
		q->next = p;
	}
}

void
keywords_iterate(struct keyword *kw, void (*f)(struct keyword *, void *), void *opaque)
{
	struct keyword *k;

	assert(kw != NULL);
	assert(f != NULL);

	for (k = kw; k; k = k->next) {
		f(k, opaque);
	}
}

