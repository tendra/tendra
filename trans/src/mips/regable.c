/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <local/ash.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>

#include "regable.h"

bool
valregable(shape s)
{
	ash a;
	int n;

	n = s->tag;
	if (is_floating (n)) {	/* check shape to see if floating point */
		return 0;
	}

	a = ashof (s); /* get ash corresponding to shape of e */

	return a.ashsize <= 32  && n != cpdhd && n != nofhd && n != tophd;
}

/*
 * determines whether the exp e can fit in a single fixed point register.
 * Uses macros isvis, isglob, iscaonly from <reader/exp.h> which examine the
 * props field. The iscaonly bit is set by proc independent if the tag is only
 * used by the contents operator or as the left hand side of an assignment.
 *
 * The procedure also uses the macro is_floating from shapemacs.h which checks
 * the shape number is in the range for floating point shapes.
 */
bool
fixregable(exp e)
{
	if (!isvis(e) && !isoutpar(e) && !isglob(e)
	    && child(e)->tag != caller_name_tag) {
		shape s = sh (child (e));	/* child of ident exp is def */
		return valregable(s);
	}

	return 0;
}

/*
 * Determines whether the exp e can fit in a floating point register,
 * single or double.
 */
bool
floatregable(exp e)
{
	if (!isvis (e) && !isoutpar(e) && !isglob (e)
	    && child(e)->tag != caller_name_tag)
	{
		shape s = sh(child(e));

		return is_floating(s->tag);
	}

	return 0;
}

