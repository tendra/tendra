/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <shared/xalloc.h>

#include <adt/arg.h>
#include <adt/param.h>

#include "code.h"

struct code *
code_create(enum code_kind kind)
{
	struct code *c;

	c = xmalloc(sizeof *c);
	c->kind = kind;
	c->next = NULL;

	return c;
}

static void
code_append(struct code **p, struct code *new)
{
	assert(p != NULL);

	while (*p != NULL) {
		p = &(*p)->next;
	}

	*p = new;
}

void
code_append_ident(struct code **c, char *ident)
{
	struct code *new;

	new = code_create(CODE_IDENT);
	new->name = ident;
	code_append(c, new);
}

void
code_append_ref(struct code **c, char *ident)
{
	struct code *new;

	new = code_create(CODE_REF);
	new->name = ident;
	code_append(c, new);
}

void
code_append_string(struct code **c, char *s)
{
	struct code *new;

	new = code_create(CODE_STRING);
	new->name = s;
	code_append(c, new);
}

void
code_destroy(struct code *c)
{
	struct code *p, *next;

	for (p = c; p != NULL; p = next) {
		next = p->next;

		switch (p->kind) {
		case CODE_IDENT:
		case CODE_STRING:
		case CODE_REF:
			free(p->name);
			break;
		}

		xfree(p);
	}
}

void
code_out(FILE *file, struct code *c,
	struct arg *rhs, struct param *in,
	struct arg *lhs, struct param *out,
	int d)
{
	struct code *p;

	for (p = c; p != NULL; p = p->next) {
		switch (p->kind) {
		case CODE_IDENT: {
			struct arg *to;

			/* TODO: do (and store these) replacements before calling code_out */
			(to = arg_index(rhs, param_findindex(in,  p->name))) ||
			(to = arg_index(lhs, param_findindex(out, p->name)));
			assert(to != NULL);

			arg_out(to, false, d, file);
			break;
		}

		case CODE_REF: {
			struct arg *to;

			/* TODO: do (and store these) replacements before calling code_out */
			(to = arg_index(rhs, param_findindex(in,  p->name))) ||
			(to = arg_index(lhs, param_findindex(out, p->name)));
			assert(to != NULL);

			arg_out(to, true, d, file);
			break;
		}

		case CODE_STRING:
			fputs(p->name, file);
			break;
		}
	}
}

