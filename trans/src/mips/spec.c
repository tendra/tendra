/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Defines special_fn which recognises and replaces some special
 * function calls.
 */

#include <stddef.h>
#include <string.h>

#include <local/exptypes.h>
#include <local/expmacs.h>

#include <reader/externs.h>
#include <reader/basicread.h>
#include <reader/table_fns.h>

#include <construct/tags.h>
#include <construct/shapemacs.h>
#include <construct/exp.h>
#include <construct/installglob.h>
#include <construct/spec.h>

#include <main/flags.h>

speci
special_fn(exp a1, exp a2, shape s)
{				/* look for special functions */
  speci spr;
  dec* dp = brog (son (a1));
  char *id = dp -> dec_u.dec_val.dec_id;
  spr.is_special = 0;
  if (id == (char *) 0)
    return spr;
  /*
   * At present the detection of special cases is done on the identifiers,
   * but it really ought to be on special tokens, as for diagnostics.
   */

  if (builtin & BUILTIN_LONGJMP) {
    if (!strcmp (id, "setjmp"))
      has_setjmp = 1;
  }

  if (builtin & BUILTIN_ALLOCA) {
    if (a2 != nilexp && last(a2) && ( (do_alloca && !strcmp (id, "alloca"))
    			 || !strcmp (id, "__builtin_alloca"))) {
      exp r = getexp (s, nilexp, 0, a2, nilexp, 0,
  	(long) 0, alloca_tag);
      setfather(r, son(r));
      has_alloca = 1;
      spr.is_special = 1;
      spr.special_exp = r;
      kill_exp (a1, a1);
      return spr;
    };
  }

  return spr;
}
