/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"

#include <shared/check.h>

#include "exptypes.h"
#include "expmacs.h"

#include <construct/installglob.h>
#include <construct/exp.h>
#include <construct/tags.h>
#include <construct/flags.h>
#include <construct/shapemacs.h>

#include <refactor/optimise.h>

#define crit_inline 100
#define decs_allowed 4
#define decs_with_apply 0

static int  complexity(exp, int, int);

static int sbl(exp e, int count, int newdecs)
/* applies complexity to the members of a list */
{
  int  c = complexity(e, count,newdecs);
  if (c < 0)
    return c;
  if (last(e))
    return c;
  return sbl(bro(e), c, newdecs);
}

static int complexity(exp e, int count, int newdecs)
{
  unsigned char  n = name(e);
  if (count < 0 || newdecs >= decs_allowed)
    return -1;
  if (son(e) == nilexp) return count;
  switch (n) {
  	case apply_tag: {
  	   if (newdecs > decs_with_apply)
		 return -1;
  	   return sbl(son(e), count-1, newdecs);
  	}
  	case res_tag: return complexity(son(e), count-1, newdecs);
        case ident_tag:
	  if (isloadparam(son(e)))
	    return sbl(son(e), count-1, newdecs);
	  else
	    return sbl(son(e), count-1, newdecs+1);
        case top_tag: case clear_tag: case prof_tag: return count;
	case case_tag: return complexity(son(e), count - 1, newdecs);
	case name_tag: case string_tag: case env_offset_tag:
               return count - 1;
	case labst_tag: return complexity(bro(son(e)), count,
                        newdecs);
	case solve_tag: case seq_tag: return sbl(son(e), count, newdecs);
	default: return sbl(son(e), count - 1, newdecs);
  }
}

int inlinechoice(exp t, exp def, int total)
	/* delivers 0 if no uses of this proc can be inlined.
	   delivers 1 if this use cannot be inlined
	   delivers 2 if this use can be inlined.
	*/
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



  if (complexity(fpars, crit_inline, newdecs) >= 0)
    return 2;
  else if (newdecs == 0)
    return 0;
  return 1;
}
