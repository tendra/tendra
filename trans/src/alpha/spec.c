/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Defines special_fn which recognises and replaces some special function calls.
 */

#include <string.h>

#include <reader/exptypes.h>
#include <reader/expmacs.h>

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
{
  /* look for special functions */
  speci spr;
#if 0
  dec* dp = brog (son (a1));
  char *id = dp -> dec_u.dec_val.dec_id;
  spr.is_special = 0;
  if (id == (char *) 0)
    return spr;
	/*
	 * At present the detection of special cases is done on the identifiers,
	 * but it really ought to be on special tokens, as for diagnostics.
	 */

  if (!strcmp (id, "setjmp"))
    has_setjmp = 1;

  if (a2 != NULL && last(a2) && ( (do_alloca && !strcmp (id, "alloca"))
  			 || !strcmp (id, "__builtin_alloca"))) {
    exp r = getexp (s, NULL, 0, a2, NULL, 0,
	(long) 0, alloca_tag);
    setfather(r, son(r));
    has_alloca = 1;
    spr.is_special = 1;
    spr.special_exp = r;
    kill_exp (a1, a1);
    return spr;
  };
  return spr;
#endif
  spr.is_special=0;
  return spr;
}
