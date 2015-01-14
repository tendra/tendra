/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>

#include <construct/installtypes.h>
#include <construct/reg_result.h>

#include "memtdf.h"
#include "localexpmacs.h"

bool
reg_result(shape sha)
{
  return is_floating(name(sha) ||
    (shape_size(sha) <= 32 && !IS_AGGREGATE(sha)));
}
