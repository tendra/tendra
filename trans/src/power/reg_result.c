/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>

#include <local/exp.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/reg_result.h>

bool
reg_result(shape sha)
{
	return is_floating(sha->tag ||
	                   (shape_size(sha) <= 32 && !IS_AGGREGATE(sha)));
}

