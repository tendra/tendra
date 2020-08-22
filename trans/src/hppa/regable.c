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
 * Does a value of a shape s fit into a fixed register?
 */
bool
valregable(shape s)
{
	int n;
	ash a;

	n = s->tag;
	if (is_floating(n)) {
		return false; /* floats don't go in fixed point registers */
	}

	a = ashof(s) ;
	if (a.ashsize > 32) {
		/* too big for a 32 bit register */
		return false;
	}

	if (n == cpdhd || n == nofhd) {
		/* Compound shapes are not put in registers */
		return false;
	}

	if (n == tophd) {
		return false;
	}

	return true;
}

/*
 * Does the expression e fit into a fixed register?
 */
bool
fixregable(exp e)
{
	if (!isvis(e) && !isoutpar(e) && !isglob(e) && !isenvoff(e)
	     && (child(e)->tag != caller_name_tag))
	{
		shape s = sh(child(e));
		return valregable(s);
	}

	return false;
}

/*
 * Does the expression e fit into a floating point register?
 */
bool
floatregable(exp e)
{
	if (!isvis(e) && !isoutpar(e) && !isglob(e) && !isenvoff(e)
	     && (child(e)->tag != caller_name_tag))
	{
		shape s = sh(child(e));
		if (!is_floating(s->tag)) {
			return false;
		}

		if ((has & HAS_LONG_DOUBLE) && shape_size(s) > 64) {
			return false;
		}

		return true;
	}

	return false;
}

