/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/check.h>

#include <local/ash.h>
#include <local/exp.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>
#include <construct/exp.h>

#include <flpt/flpt.h>

#include "addr.h"
#include "procrec.h"
#include "labels.h"
#include "make_code.h"
#include "bits.h"
#include "locate.h"
#include "inst_fmt.h"
#include "alpha_ins.h"
#include "special.h"
#include "handle_sregs.h"
#include "regexps.h"
#include "code_here.h"
#include "reg_defs.h"


/*
  regofval
  The procedure regofval checks to see if an exp is a load_tag
  that has been allocated into a fixpnt register and if so return 
  it or else 100.
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
      return isvar(decx) ? (-no (decx)) : (no (decx));
    }
    return 100;
  }
  else
  if ((e->tag == val_tag && no (e) == 0) || e->tag == clear_tag ||
    e->tag == top_tag) {
	return 31;
  }
  else {
	return 100;
  }
}

/*
  add code to return 31 if fval is 0.0
*/
static int
fregofval(exp e)
{
  exp decx = child (e);
  if (e->tag == name_tag && decx->tag == ident_tag) {
    if ((decx->props & infreg_bits) != 0) {
      return no (decx);
    }
#if 0
    if((decx->props & infreg_bits) != 0){
      return isvar(decx) ? (-no(decx)) : (no(decx));
    }
#endif
    return 100;
  }
  else
    if(e->tag == clear_tag || e->tag == top_tag){
      return 0;
    }
    else {
      return 100;
    }
}
  
  
  

/*
  code_here
  The procedure code_here calls make_code and ensures that
  any internal exit labels are tied up after the call.
*/
int
code_here(exp e, space sp, where dest)
{
  makeans mka;
  mka = make_code (e, sp, dest, 0);
  if (mka.lab != 0) {
    IGNORE set_label(mka.lab);
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
    if (e->tag == apply_tag || (e->tag == apply_general_tag && 
	specialfn (child (e)) == 0)) {
				/* apply proc */
      setregalt (aa, RESULT_REG);
      w.answhere = aa;
      w.ashwhere = ash0;
      IGNORE make_code(e, sp, w, 0);
      return RESULT_REG;	/* simple proc calls give result in reg 0
				*/
    }

  aa = iskept (e);
  if (aa.discrim == inreg && regalt (aa) != NO_REG) {
				/* the same expression has already been
				   evaluated into a reg */
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
    IGNORE code_here(e, sp, w);	
    assert(reg!=-1);
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
    if (e->tag == apply_tag || e->tag == apply_general_tag) {
      if(is_floating(sh(e)->tag)) {
	freg fr;
	fr.fr = 0;
	fr.type = (e->tag==realhd)?IEEE_double:IEEE_single;
	setfregalt(aa,fr);
      }
      else{
	setregalt (aa, 0);
      }
      w.answhere = aa;
      w.ashwhere = ash0;
      IGNORE make_code(e, sp, w, 0);
      return 0;
    }

  aa = iskept (e);
  if (aa.discrim == infreg) {	/* e already evaluated in fl reg */
    return regalt (aa) /* cheat */ ;
  }

 { int reg = -1;
   somefreg sfr;
   sfr.fr = &reg;
   if(w.ashwhere.ashsize==64)
     fr.type = IEEE_double;
   else
     fr.type = IEEE_single;
   sfr.type = fr.type;
   setsomefregalt (aa, sfr);
   w.answhere = aa;
  /* evaluate e into reg ... */
  IGNORE code_here(e, sp, w);
   fr.fr = reg;
   setfregalt(aa, fr);
   keepexp (e, aa);
   return reg;
 }
}
