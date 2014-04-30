/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/xalloc.h>
#include <shared/error.h>

#include <adt/arg.h>

static struct arg *
new_arg(void)
{
	struct arg *p;

	p = xmalloc(sizeof *p);
	p->next   = NULL;
	p->is_ref = 0;

	return p;
}

struct arg *
add_arg(enum arg_kind kind, unsigned int d)
{
	struct arg *p;

	p = new_arg();
	p->kind    = kind;
	p->u.digit = d;

	return p;
}

struct arg *
add_ident(char *s)
{
	struct arg *p;

	p = new_arg();
	p->kind      = ARG_IDENT;
	p->u.literal = s;

	return p;
}

struct arg *
add_ref(char *s)
{
	struct arg *p;

	p = new_arg();
	p->kind      = ARG_IDENT;
	p->u.literal = s;
	p->is_ref    = 1;

	return p;
}

struct arg *
add_terminal(char * s)
{
	struct arg *p;

	p = new_arg();
	p->kind      = ARG_TERMINAL;
	p->u.literal = s;

	return p;
}

void
arg_out(struct arg *p, bool is_ref, int d, FILE *file)
{
	switch (p->kind) {
	case ARG_CHARP:
		error(ERROR_SERIOUS, "#* is not implemented yet at output level");
		break;

	case ARG_CHAR_NUM:
		/* TODO: assert(p->u.digit < nb_of_chars); */
		fprintf(file, "c%d", p->u.digit);
		break;

	case ARG_CHAR_COUNT:
		fprintf(file, "%d", d);
		break;

	case ARG_IDENT:
		if (p->is_ref) {
			/* TODO: assert(is_ref); */
			fprintf(file, "%s", p->u.literal);
		} else {
			if (is_ref) {
				fprintf(file, "(*%s)", p->u.literal);
			} else {
				fprintf(file, "%s", p->u.literal);
			}
		}
		break;

	case ARG_TERMINAL:
		fprintf(file, "%s", p->u.literal);
		break;

	case ARG_IGNORE:
		error(ERROR_SERIOUS, "Ignore symbol ! is not implemented yet at output level");
		/* TODO: implement */
		break;

	case ARG_RETURN:
		fprintf(file, "ZT1"); /* TODO: make prefixes option controllable or lct file controllable */
		break;

	default:
		UNREACHED;
		break;
	}
}

struct arg *
arg_index(struct arg *args, int index)
{
	struct arg *p;
	int i;

	for (p = args, i = 0; p != NULL; p = p->next, i++) {
		if (i == index) {
			return p;
		}
	}

	return NULL;
}

char *
arg_first_duplicate_ident(struct arg *args)
{
	struct arg *p, *q;

	for (p = args; p != NULL; p = p->next) {
		if (p->kind != ARG_IDENT) {
			continue;
		}

		for (q = p->next; q != NULL; q = q->next) {
			if (q->kind != ARG_IDENT) {
				continue;
			}

			if (0 == strcmp(p->u.literal, q->u.literal)) {
				return p->u.literal;
			}
		}
	}

	return NULL;
}

unsigned
arg_return_count(struct arg *args)
{
	struct arg *p;
	unsigned n;

	n = 0;

	for (p = args; p != NULL; p = p->next) {
		if (p->kind == ARG_RETURN) {
			n++;
		}
	}

	return n;
}

