/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This contains procedures:
 *
 * regofval, fregofval:    to see if an exp is a load_tag that has been
 *                         allocated to a register.
 * regoperand, freoperand: to evaluate an exp into a register using make_code
 * code_here:              calls make_code and ensures that any internal
 *                         exit labels are tied up after the call
 *
 * The procedures regoperand and fregoperand evaluate their exp parameter
 * into a single register using make_code. This register is returned.
 * An initial test with regofval checks to see if the exp is already
 * in a register.
 */

#include <local/ash.h>


#include <construct/installtypes.h>
#include <construct/ash.h>
#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shape.h>

#include "addrtypes.h"
#include "procrectypes.h"
#include "labels.h"
#include "new_code.h"
#include "bitsmacs.h"
#include "locate.h"
#include "regexps.h"
#include "inst_fmt.h"
#include "mips_ins.h"
#include "special.h"
#include "handle_sregs.h"
#include "code_here.h"

/*
 * The procedure regofval checks to see if an exp is a load_tag that has been
 * allocated into a fixpnt register and if so return it or else 100.
 */
int
regofval(exp e)
{
        exp decx = son (e);
  if (name (e) == name_tag && name (decx) == ident_tag) {/* ident tag */
    if ((props (decx) & defer_bit) != 0) {
      return regofval (son (decx));
    }
    if ((props (decx) & inreg_bits) != 0) {
      return (isvar (decx)) ? (-no (decx)) : (no (decx));
    }
    return 100;
  }
  else
  if ((name (e) == val_tag && no (e) == 0) ||
		 name(e) == clear_tag || name(e)== top_tag) {
	return 0;
  }
  else {
	return 100;
  }
}

int
fregofval(exp e)
{
        exp decx = son (e);
  if (name (e) == name_tag && name (decx) == ident_tag) {
    if ((props (decx) & infreg_bits) != 0) {
      return no (decx);
    }
    return 100;
  }
  else
  if (name(e)==clear_tag || name(e)==top_tag) {
	return 0;
  }
  else {
      return 100;
  }
}

/*
 * The procedure code_here calls make_code and ensures that any internal
 * exit labels are tied up after the call.
 */
int
code_here(exp e, space sp, where dest)
{
        makeans mka;
  mka = make_code (e, sp, dest, 0);
  if (mka.lab != 0) {
    set_label (mka.lab);
  }
  return mka.regmove;
}

ash ash0 = {
  0, 0
};
ash ash32 = {
  32, 32
};


int
reg_operand(exp e, space sp)
{
  int   x = regofval (e);
  ans aa;
  where w;
  if (x >= 0 && x < 100) {
    return x;
  }				/* x is a register for e */
  if (name (e) == cont_tag) {
    x = regofval (son (e));
    if (x < 0) {
      return -x;
    }
  }
  else
    if (name (e) == apply_tag && specialfn (son (e)) == 0) {
				/* apply proc */
      setregalt (aa, 0);
      w.answhere = aa;
      w.ashwhere = ash0;
      make_code (e, sp, w, 0);
      return 2;			/* simple proc calls give result in reg 2 */
    }

  aa = iskept (e);
  if (aa.discrim == inreg && regalt (aa) != 0) {
		/* the same expression has already been evaluated into a reg */
    return regalt (aa);
  }
  if (aa.discrim == notinreg) {
    instore is;
    is = insalt (aa);
    if (is.adval && is.b.offset == 0) {
      int   r = is.b.base;
      /* the same expression has already been evaluated into a reg */
      return r;
    }
  }

  {
    int   reg = -1;
    setsomeregalt (aa, &reg);
    /* allow code_here to evaluate e into reg of its choice */
    w.answhere = aa;
    w.ashwhere = ashof (sh (e));
    code_here (e, sp, w);
    keepreg (e, reg);
    return reg;
  }
}

int
freg_operand(exp e, space sp)
{
  int   x = fregofval (e);
  ans aa;
  where w;
  freg fr;
  w.ashwhere = ashof (sh (e));
  if (x >= 0 && x < 100) {
    return x;
  }
  if (name (e) == cont_tag) {
    x = fregofval (son (e));
    if (x < 100) {
      return x;
    }
  }
  else
    if (name (e) == apply_tag) {
      setregalt (aa, 0);
      w.answhere = aa;
      w.ashwhere = ash0;
      make_code (e, sp, w, 0);
      return 0;
    }

  aa = iskept (e);
  if (aa.discrim == infreg) {	/* e already evaluated in fl reg */
    return regalt (aa) /* cheat */ ;
  }

 { int reg = -1;
   somefreg sfr;
   sfr.fr = &reg;
   sfr.dble = fr.dble = (w.ashwhere.ashsize == 64) ? 1 : 0;
  setsomefregalt (aa, sfr);
  w.answhere = aa;
  /* evaluate e into reg ... */
  code_here (e, sp, w);
  fr.fr = reg;
  setfregalt(aa, fr);
  keepexp (e, aa);
  return reg;
 }
}
