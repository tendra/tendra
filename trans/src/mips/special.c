/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*special.c
    inlines some of the simpler standard library functions
*/

#include <string.h>

#include <shared/error.h>

#include <local/ash.h>

#include <reader/exp.h>
#include <reader/basicread.h>

#include <construct/installtypes.h>
#include <construct/ash.h>
#include <construct/shape.h>
#include <construct/tags.h>

#include "addrtypes.h"
#include "move.h"
#include "pseudo.h"
#include "getregs.h"
#include "guard.h"
#include "code_here.h"
#include "inst_fmt.h"
#include "mips_ins.h"
#include "labels.h"
#include "procrectypes.h"
#include "bitsmacs.h"
#include "special.h"


static int
specno(char *n)
{	/* these are the procs I could do
				   something about */
  if    (strcmp (n, "strcpy") == 0)
          return - 1;
  if (strcmp (n, "strlen") == 0)
    return 2;
  if (strcmp (n, "strcmp") == 0)
    return - 3;
  return 0;
}

static  needs strcpyneeds = {
  0, 0, 0, 0
};
static  needs strlenneeds = {
  3, 0, uses2_bit, 0
};
static  needs strcmpneeds = {
  2, 0, 0, 0
};

needs
specialneeds(int i)
{	/* these are the needs for their expansion
				   */
  switch (i) {
    case 1:
      return strcpyneeds;
    case 2:
      return strlenneeds;
    case 3:
      return strcmpneeds;
    default:
      error(ERR_INTERNAL, "not special fn");
  }
  return strcpyneeds;
}

int
specialfn(exp fn)
{	/* could I treat this function load
				   specially ? */
  if (name (fn) == name_tag && name (son (fn)) == ident_tag &&
      isglob (son (fn)) && son (son (fn)) == NULL) {
    char *extname = brog(son (fn)) -> dec_u.dec_val.dec_id;
    return specno (extname);
  }
  return 0;
}





int
specialmake(int n, exp par, space sp, where dest, int exitlab)
{
  switch (n) {
    case  2:			/* translate strlen in the obvious manner
				*/
      {
	where w;
	ans aa;
	int   lstart = new_label ();
	int   r;
	int   r1;
	baseoff ind3;
	int r3;
	r = (dest.answhere.discrim == inreg) ? regalt (dest.answhere)
	  : getreg (sp.fixed);
	if (r == 0) r = 2; /* can be called like proc on lhs of ass */
	sp = guardreg(r,sp);
	r3 = getreg(sp.fixed);
	ind3.base = r3; ind3.offset = 0;
	setregalt (w.answhere, r3);
	w.ashwhere = ashof (sh (par));
	code_here (par, sp, w);

	r1 = getreg (guardreg (r3, sp).fixed);

	rri_ins (i_add, r, r3, 1);
	set_label (lstart);

	ls_ins (i_lb, r1, ind3);
	rri_ins (i_add, r3, r3, 1);
	condr_ins (i_bnez, r1, lstart);

	rrr_ins (i_sub, r, r3, r);
	setregalt (aa, r);
	move (aa, dest, sp, 1);
	return exitlab;
      }
    default:
      error(ERR_INTERNAL, "not special");
  }
  return exitlab;
}
