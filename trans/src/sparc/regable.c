/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>

#include <local/ash.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>

#include <main/flags.h>

#include "regable.h"

/*
 * Does a value of shape s fit into a fixed register?
 */
bool
valregable(shape s)
{
	ash a ;

	if (is_floating(s->tag)) {
		/* Floating point values don't go in fixed registers */
		return 0;
	}

	a = ashof(s);
	if (a.ashsize > 32) {
		/* Reject anything too big */
		return 0;
	} else if (s->tag == cpdhd || s->tag == nofhd) {
		/* Compound shapes are not put in registers */
		return 0;
	} else if (/* a.ashsize == a.ashalign && a.ashalign != */ 1) {
		/* Bitfields are put in registers */
		return 1;
	}

	return 0;
}

/*
 * Does the expression e fit into a fixed register?
 */
bool
fixregable(exp e)
{
	if (!isvis(e) && !isoutpar(e) && !isglob(e) && !isenvoff(e) &&
	     child(e)->tag != caller_name_tag)
	{
		shape s = sh(child(e));
		return valregable(s);
	}

	return 0;
}

/*
 * Does the expression e fit into a floating point register?
 */
bool
floatregable(exp e)
{
	if (!isvis(e) && !isoutpar(e) && !isglob(e) && !isenvoff(e) &&
	     child(e)->tag != caller_name_tag)
	{
		shape s = sh(child(e));

		if (!is_floating(s->tag)) {
			return 0;
		}

		if ((has & HAS_LONG_DOUBLE) && shape_size(s) > 64) {
			return 0;
		}

		return 1;
	}

	return 0;
}

