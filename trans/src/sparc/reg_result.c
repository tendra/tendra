/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>

#include <tdf/shape.h>

#include <construct/reg_result.h>

#include <main/flags.h>

#include "regable.h"

bool
reg_result(shape sha)
{
	if (valregable(sha)) {
		return 1;
	}

	if (is_floating(sha->tag)) {
		if ((has & HAS_LONG_DOUBLE) && shape_size(sha) > 64) {
			return 0;
		}

		return 1;
	}

	return 0;
}

