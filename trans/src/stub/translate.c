/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <construct/installtypes.h>
#include <construct/installglob.h>

#include <refactor/optimise.h>

void 
translate_capsule(void)
{
	dec *d;

	opt_all_exps();

	for (d = top_def; d != NULL; d = d->def_next) {
		const char *id;

		if (d->dec_u.dec_val.processed) {
			continue;
		}

		id = d->dec_u.dec_val.dec_id;

		fprintf(stderr, "dec: %s\n", id);
	}
}

