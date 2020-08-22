/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <shared/bool.h>

#include <tdf/tag.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/installglob.h>

#include <refactor/optimise.h>

#include <main/driver.h>
#include <main/flags.h>

static void
something(dec *d)
{
	const char *name;
	exp c, s;

	assert(d != NULL);

	name = d->name;

	c = d->exp;
	s = child(c);

	if (s == NULL) {
		shape sha;

		sha = d->shape;

		fprintf(stderr, "shape %u: %s\n", sha->tag, name);
	} else {
		switch (s->tag) {
		case proc_tag:
		case general_proc_tag:
			fprintf(stderr, "proc: %s\n", name);
			break;

		case string_tag:
			fprintf(stderr, "string: %s = \"%s\"\n", name, nostr(s));
			break;

		default:
			fprintf(stderr, "tag %d: %s\n", s->tag, name);
			return;
		}
	}

	d->processed = true;
}

void
local_translate_capsule(void)
{
	dec *d;

	if (diag == DIAG_NONE) {
		opt_all_exps();
	}

	for (d = top_def; d != NULL; d = d->next) {
		if (d->processed) {
			continue;
		}

		something(d);
	}
}

