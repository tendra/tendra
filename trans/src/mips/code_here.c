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

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>
#include <construct/exp.h>

#include "addr.h"
#include "procrec.h"
#include "labels.h"
#include "bits.h"
#include "make_code.h"
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
        exp decx = child (e);
  if (e->tag == name_tag && decx->tag == ident_tag) {/* ident tag */
    if ((decx->props & defer_bit) != 0) {
      return regofval (child (decx));
    }
    if ((decx->props & inreg_bits) != 0) {
      return (isvar (decx)) ? (-no (decx)) : (no (decx));
    }
    return 100;
  }
  else
  if ((e->tag == val_tag && no (e) == 0) ||
		 e->tag == clear_tag || e->tag== top_tag) {
	return 0;
  }
  else {
	return 100;
  }
}

static int
fregofval(exp e)
{
        exp decx = child (e);
  if (e->tag == name_tag && decx->tag == ident_tag) {
    if ((decx->props & infreg_bits) != 0) {
      return no (decx);
    }
    return 100;
  }
  else
  if (e->tag==clear_tag || e->tag==top_tag) {
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

static ash ash0 = {
  0, 0
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
  if (e->tag == cont_tag) {
    x = regofval (child (e));
    if (x < 0) {
      return -x;
    }
  }
  else
    if (e->tag == apply_tag && specialfn (child (e)) == 0) {
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
  if (e->tag == cont_tag) {
    x = fregofval (child (e));
    if (x < 100) {
      return x;
    }
  }
  else
    if (e->tag == apply_tag) {
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
