/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <local/ash.h>

#include <construct/installtypes.h>
#include <construct/ash.h>

#include <reader/expmacs.h>

ash
ashof(shape s)
{
	ash a;

	a.ashsize  = shape_size(s);
	a.ashalign = shape_align(s);

	return a;
}

