/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/installglob.h>
#include <construct/exp.h>

#include <utility/complexity.h>

#include <main/flags.h>

#include <refactor/optimise.h>

#define crit_inline	    50
#define decs_allowed	4
#define decs_with_apply	0
#define apply_cost      1

/*
 * This delivers 0 if no uses of the procedure can be inlined,
 * 1 if this use cannot be inlined and 2 if this use can be inlined.
 */
int
inlinechoice(exp t, exp def, int total_uses)
{
	exp apars;
	exp fpars;
	int newdecs = 0;

	UNUSED(total_uses);

	/* only uses are applications */
	apars = bro(t);
	fpars = son(def);

	for (;;) {
		if (fpars->tag != ident_tag || !isparam(fpars)) {
			if (apars->tag != top_tag) {
				newdecs = 10;
			}
			break;
		}

		switch (apars->tag) {
		case val_tag:
		case real_tag:
		case string_tag:
		case name_tag:
			break;

		case cont_tag:
			if (son(apars)->tag == name_tag &&
			    isvar(son(son(apars))) &&
			    !isvar(fpars)) {
				break;
			}

			FALL_THROUGH;

		default:
			newdecs++;
		}

		fpars = bro(son(fpars));
		if (apars->last) {
			break;
		}

		apars = bro(apars);
	}

	/*
	 * newdecs is now the number of declarations (which will not be
	 * optimised out) arising from actual parameters
	 */
	if (complexity(fpars, crit_inline, newdecs, decs_allowed, decs_with_apply, apply_cost) >= 0) {
		return 2;
	} else if (newdecs == 0) {
		return 0;
	}

	return 1;
}

