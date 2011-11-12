/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"

#include "exptypes.h"
#include "tags.h"
#include "externs.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "exp.h"
#include "basicread.h"
#include "flags.h"
#include "table_fns.h"
#include "installglob.h"
#include "check.h"
#include "spec.h"


speci special_fn(exp a1, exp a2, shape s)
{				/* look for special functions */
  speci spr;
  dec* dp = brog (son (a1));
  char *id = dp -> dec_u.dec_val.dec_id;
  spr.is_special = 0;
  if (id == (char *) 0)
    return spr;
  /* at present the detection of special cases is done on the identifiers,
     but it really ought to be on special tokens, as for diagnostics */

  if (!strcmp (id, "setjmp"))
    has_setjmp = 1;

  if (!strcmp (id, "longjmp"))
    has_setjmp = 1;

     /* we must always set has_setjmp if it is longjmp,
        otherwise registers are not reset.
        so don't do do_special_fns test until after longjmp test. */
  if (!do_special_fns)
    return spr;

  if (do_alloca &&
      (!strcmp (id, "alloca") || !strcmp (id, "__builtin_alloca"))) {
    exp r = getexp (s, nilexp, 0, a2, nilexp, 0,
	(long) 0, alloca_tag);
    setfather(r, son(r));
    has_alloca = 1;
    spr.is_special = 1;
    spr.special_exp = r;
    kill_exp (a1, a1);
    return spr;
  };

  return spr;
}
