/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <reader/exp.h>
#include <reader/read_fns.h>

#include <construct/installtypes.h>
#include <construct/installglob.h>

#include <main/flags.h>

/*
 * Translate a single TDF unit
 */
void
translate_unit(void)
{
	dec *d;

	if (!separate_units) {
		return;
	}

	translate_capsule();

	for (d = top_def; d != NULL; d->def_next) {
		exp c = d->dec_u.dec_val.dec_exp;
		no(c) = 0;
		pt(c) = NULL;
	}

	crt_repeat  = NULL;
	repeat_list = NULL;
}

