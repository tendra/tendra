/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <reader/exptypes.h>
#include <reader/expmacs.h>
#include <reader/codetypes.h>

#include <construct/installtypes.h>
#include <construct/exp.h>
#include <construct/special_fn.h>

special
special_fn(exp a1, exp a2, shape s)
{				/* look for special functions */
  special spr;

  /* +++ implement special fns handling */
  spr.is_special = 0;
  spr.special_exp = NULL;

  return spr;
}

