/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

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
	const char *id;
	exp c, s;

	assert(d != NULL);

	id = d->dec_id;

	c = d->dec_exp;
	s = son(c);

	if (s == NULL) {
		shape sha;

		sha = d->dec_shape;

		fprintf(stderr, "shape %u: %s\n", sha->tag, id);
	} else {
		switch (s->tag) {
		case proc_tag:
		case general_proc_tag:
			fprintf(stderr, "proc: %s\n", id);
			break;

		case string_tag:
			fprintf(stderr, "string: %s = \"%s\"\n", id, nostr(s));
			break;

		default:
			fprintf(stderr, "tag %d: %s\n", s->tag, id);
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

	for (d = top_def; d != NULL; d = d->def_next) {
		if (d->processed) {
			continue;
		}

		something(d);
	}
}

