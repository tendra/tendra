/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <local/ash.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>


ash
ashof(shape s)
{
	ash a;

	a.ashsize  = shape_size(s);
	a.ashalign = shape_align(s);

	return a;
}

