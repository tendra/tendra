/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>

#include <tdf/shape.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/reg_result.h>

bool
reg_result(shape sha)
{
	return sha->tag != cpdhd && sha->tag != nofhd;
}

