/*
 * Copyright 2015, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>
#include <stdio.h>

#include <shared/bool.h>

#include <reader/exp.h>
#include <reader/reader.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/installglob.h>

#include <main/flags.h>
#include <main/driver.h>

/*
 * Translate a single TDF capsule
 *
 * This may be called from common/reader directly,
 * as well as by translate_unit() below.
 */
static void
translate_capsule(void)
{
	driver.translate_capsule();
}

/*
 * Translate a single TDF unit
 */
static void
translate_unit(void)
{
	dec *d;

	if (!separate_units) {
		return;
	}

	translate_capsule();

	for (d = top_def; d != NULL; d = d->next) {
		exp c = d->exp;
		no(c) = 0;
		pt(c) = NULL;
	}

	crt_repeat  = NULL;
	repeat_list = NULL;
}

struct reader_dispatch reader_dispatch = {
	translate_unit,
	translate_capsule
};

