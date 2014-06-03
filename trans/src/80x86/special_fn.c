/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
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
#include <construct/me_fns.h>
#include <construct/special_fn.h>

#include <main/flags.h>

#include "localexpmacs.h"
#include "prefix.h"

special special_fn
(exp a1, exp a2, shape s)
{
		/* look for special functions */
  special spr;
  dec* dp = brog(son(a1));
  char *id = dp -> dec_u.dec_val.dec_id;
  spr.is_special = 0;
  if (id == (char *)0) {
    return spr;
  }
  id += prefix_length;

  if (a2 != NULL && last(a2) && !strcmp(id, "__trans386_special")) {
    exp r = me_b3(s, a1, a2, apply_tag);
    setbuiltin(r);	/* dummy proc, so ignore state of builtin */
    spr.is_special = 1;
    spr.special_exp = r;
    return spr;
  };

  if (builtin & BUILTIN_LONGJMP) {
    if (!strcmp(id, "setjmp")) {
      has_setjmp = 1;
    };
  
    if (!strcmp(id, "longjmp")) {
      exp r = getexp(f_bottom, NULL, 0, a1, NULL, 0, 0,apply_tag);
      has_setjmp = 1;
      if (last(a2) || bro(a2) == NULL)
        return spr;
      bro(a1) = a2;
      clearlast(a1);
      parked(a2) = 0;
      clearlast(a2);
      a2 = bro(a2);
      setlast(a2);
      parked(a2) = 0;
      bro(a2) = r;
      spr.is_special = 1;
      spr.special_exp = r;
    };
  }

  if (builtin & BUILTIN_ALLOCA) {
    if (a2 != NULL && last(a2) && !strcmp(id, "__builtin_alloca")) {
      exp r = getexp(s, NULL, 0, a2, NULL, 0,
  	0, alloca_tag);
      setfather(r, son(r));
      has_alloca = 1;
      spr.is_special = 1;
      spr.special_exp = r;
      kill_exp(a1, a1);
      return spr;
    };
  }

  if (builtin & BUILTIN_API) {
    if (a2 != NULL && last(a2) && !strcmp(id, "exit")) {
      exp r = me_b3(f_bottom, a1, a2, apply_tag);
      spr.is_special = 1;
      spr.special_exp = r;
      return spr;
    };
  
    if (a2 == NULL && !strcmp(id, "abort")) {
      exp r = me_u3(f_bottom, a1, apply_tag);
      spr.is_special = 1;
      spr.special_exp = r;
      return spr;
    };
  }

  return spr;
}
