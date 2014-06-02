/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>

#include <reader/exptypes.h>
#include <reader/expmacs.h>

#include <construct/installglob.h>
#include <construct/exp.h>
#include <construct/tags.h>
#include <construct/shapemacs.h>

#include <main/flags.h>

#include <refactor/optimise.h>

#include <utility/complexity.h>

#define crit_inline 100
#define decs_allowed 4
#define decs_with_apply 0
#define apply_cost 1

/*
 * delivers 0 if no uses of this proc can be inlined.
 * delivers 1 if this use cannot be inlined
 * delivers 2 if this use can be inlined.
 */
int inlinechoice(exp t, exp def, int total)
{
  exp apars;
  exp fpars;
  int newdecs = 0;
  shape shdef = pt(def);
  UNUSED(total);

  if (!eq_shape(sh(father(t)), shdef))
  {
    /* shape required by application is different from definition */
    return 1;
  }
  apars = t; /* only uses are applications */
  fpars = son(def);

  for (;;) {
     if (name(fpars)!=ident_tag || !isparam(fpars)) {
	if (!last(apars)) return 1;
      	break;
     }

     if (last(apars)) return 1;
     apars = bro(apars);

     switch (name(apars)) {
      case val_tag: case real_tag: case string_tag: case name_tag:
      	   break;
      case cont_tag: {
      	   if (name(son(apars)) ==name_tag && isvar(son(son(apars))) &&
      	        		!isvar(fpars))break;
      	   } /* ... else continue */
      default: newdecs++;
     }
     fpars = bro(son(fpars));
  }
        /* newdecs is now the number of declarations (which will not be
      	     optimised out) arising from actual parameters */

  if (complexity(fpars, crit_inline, newdecs, decs_allowed, decs_with_apply, apply_cost) >= 0)
    return 2;
  else if (newdecs == 0)
    return 0;
  return 1;
}
