/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
   locate.c
   This file provides functions to locate an exp.
*/

#include <stdio.h>

#include <shared/error.h>

#include <local/ash.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>
#include <construct/exp.h>

#include <flpt/flpt.h>

#include "addr.h"
#include "inst_fmt.h"
#include "alpha_ins.h"
#include "bits.h"
#include "procrec.h"
#include "guard.h"
#include "eval.h"
#include "regexps.h"
#include "pseudo.h"
#include "getregs.h"
#include "move.h"
#include "handle_sregs.h"
#include "frames.h"
#include "code_here.h"
#include "reg_defs.h"
#include "locate.h"

int locals_offset; /* the offset in bits of start of current locals */
int frame_size;	/* the size of the current stack frame in bits */


baseoff boff
(exp id)
{
  baseoff an;
  if (isglob (id)) {		/* globals */
    dec * gl = nextg(id);
    long sno = gl->sym_number;
    an.base = - (sno + 1);
    an.offset = 0;
  }
  else {
    int   x = no(id);
    int   b = x & 0x3f;
    if (child(id)->tag == caller_name_tag) {
      an.base = SP;
      an.offset = (x-b) >>4;
    }
    else if (b == SP) {
      an.base = SP;
      an.offset = ((x - b) >> 4) + (locals_offset >> 3);
      /* locally declared things accessed by sp*/
    }
    else if (b==FP && Has_fp) {
      an.base = FP;
      an.offset = ((x - b) >> 4) + ((locals_offset-callee_size-frame_size) >>3);
      /* locally declared things accessed by fp */
    }
    else if ((b == local_reg && Has_vcallees)) {
      an.base = b;
      an.offset = (((x-b))>>4)+ ((locals_offset-frame_size/*-callee_size*/)>>3);
    }
    else if (b <= 31) {
	an.base = b;
	an.offset = ((x - b) >> 4);
	/* other base offsets */
    }
    else if (b == 32) {
      an.base = - ((x - b) >> 6);
      an.offset = 0;
	  /* global names  */
    }
    else if (b == 33) {
      an.base = (x - b) >> 6;
      an.offset = 0;
      /* global anonymous */
    }
    else {
      error(ERR_INTERNAL, "not a baseoff in boff");
    }
  }
  return an;
}

 /*
    locate differs from locate1 only in that it looks to
    see if e has already been evaluated somehow
*/
where locate(exp e, space sp, shape s, int dreg);

static where
locate1(exp e, space sp, shape s, int dreg)
{
  /* finds the address of e using shape s;
     sp gives available t-regs for any inner
     evaluation. dreg is historical (carried over from mipstrans). */
  ash a;
  ans aa;
  where wans;
  source src;

  a = ashof(s);

  switch (e->tag) {
   case name_tag:
    {
      exp decx = child(e);
      bool var = isvar(decx);
      /* this a locally declared name ... */
      if (props(decx) & defer_bit) {
	/* ... it has been identified with a
	   simple expression which is better
	   evaluated every time */
	where w;
	w = locate(child(decx), sp, sh(child(decx)), dreg);

	if (no(e) == 0) {
	  aa = w.answhere;
	}
	else {
	  instore is;
	  switch (w.answhere.discrim) {
	    case notinreg: {
	      is = insalt(w.answhere);
	      is.b.offset += (no(e) / 8);
	      break;
	    }
	    default:
	    error(ERR_INTERNAL, "NOT deferable");
	  }

	  setinsalt(aa, is);
	}
      }
      else if (props(decx) & inreg_bits) {
	/* ... it has been allocated in a fixed
	   point reg */
	if (var) {
	  setregalt(aa, no(decx));
	}
	else {
	  instore b;
	  b.b.base = no(decx);
	  b.b.offset = 0;
	  b.adval = 1;
	  setinsalt(aa, b);
	}
      }
      else if (props(decx) & infreg_bits) {
	/* ... it has been allocated in a floating
	   point reg */
	freg fr;
	fr.fr = no(decx);
	if (a.ashsize==64)
	  fr.type = IEEE_double;
	else
	  fr.type = IEEE_single;
	setfregalt(aa, fr);
      }
      else {		/* ... it is in memory */
	instore is;
	if (var || (sh(e)->tag == prokhd &&
		   (child(decx) == NULL || child(decx)->tag == proc_tag
		     || child(decx)->tag == general_proc_tag))) {
	  is.adval = 1;
	}
	else {
	  is.adval = 0;
	}
	is.b = boff(decx);
	is.b.offset += (no(e) / 8);
	setinsalt(aa, is);
      }
      wans.answhere = aa;
      wans.ashwhere = a;
      return wans;
    }

    case addptr_tag:
    {
      exp sum = child(e);
      where wsum;
      int   addend;
      space nsp;
      int   reg;
      int   ind;
      instore is;
      ans asum;
      int multiplier;
      wsum = locate(sum, sp, sh(sum), NO_REG);
      asum = wsum.answhere;
      /* answer is going to be wsum displaced by integer result of
	   evaluating next(sum) */

      switch (asum.discrim) {
      case notinreg:
      {
	instruction scale_ins;
	is = insalt(asum);
	if (is.adval) {	/* wsum is a literal address in store ...
			 */
	  baseoff b;
	  b = is.b;
	  if (b.base < 0 || b.base > 31) {
	    /* ... it is not a base-offset , so make
	       it one */
	    reg = getreg(sp.fixed);
	    load_store(i_lda, reg, b);
	    keepreg(sum, reg);
	    b.base = reg;
	    b.offset = 0;
	  }
	  nsp = guardreg(b.base, sp);

	  /* choose the appropriate instruction based on the
	     multiplier.  Not shure if this is any faster than
	     using two instructions : mult & add.
	     */
	  if (next(sum)->tag == offset_mult_tag) {
	    multiplier = no(next(child(next(sum))));
	    switch (multiplier) {
	    case 4:
	      scale_ins=i_s4addq;
	      addend = reg_operand(child(next(sum)),nsp);
	      break;
	    case 8:
	      scale_ins=i_s8addq;
	      addend = reg_operand(child(next(sum)),nsp);
	      break;
	    default:
	      scale_ins=i_addq;
	      addend = reg_operand(next(sum),nsp);
	    }
	  }
	  else{
	    scale_ins=i_addq;
	    addend = reg_operand(next(sum), nsp);
	  }

	  /* evaluate the displacement ... */
	  if (dreg == NO_REG)
	    dreg = getreg(nsp.fixed);
	  src.reg=0;
	  src.value=addend;
	  operate_fmt(scale_ins,src.value,b.base,dreg);
	  /* ... add it to the base register into new reg */
	  b.base = dreg;
	  is.b = b;
	  setinsalt(aa, is);
	  wans.answhere = aa;
	  wans.ashwhere = a;
	  /* ...and use it as base a literal base-offset result */
	  keepexp(e, aa);
	  return wans;
	}
	else {		/* wsum represents an actual pointer in
			   store... */
	  ind = getreg(sp.fixed);
	  load_store(i_ldq,ind,is.b);
	  /* ... so load it into a good register */
	}
	goto breakpt;
	/* should be break - thought there was cc error */

      }			/* end notinreg */

      case inreg:
	/* wsum is already in reg */
      {
	ind = regalt(asum);
	goto breakpt;
      }

      default: {
	error(ERR_INTERNAL, "Locate ? reg");
      }
      }			/* end case */

    breakpt: 		/* register ind contains the evaluation of
		        1st operand of addptr */
      nsp = guardreg(ind, sp);
      if (next(sum)->tag == env_offset_tag ||
	  next(sum)->tag ==general_env_offset_tag) {
	is.b.base = ind;
	is.b.offset = frame_offset(child(next(sum)));
      }
      else {
	instruction ins=i_addq;
	if (next(sum)->tag == offset_mult_tag &&
	   next(child(next(sum)))->tag ==val_tag) {
	  switch (no(next(child(next(sum))))) {
	  case 4:
	    ins=i_s4addq;
	    addend = reg_operand(child(next(sum)),nsp);
	    break;
	  case 8:
	    ins=i_s8addq;
	    addend = reg_operand(child(next(sum)),nsp);
	    break;
	  default:
	    addend = reg_operand(next(sum),nsp);
	    break;
	  }
	}
	else{
	  addend = reg_operand(next(sum),nsp);
	}
	/*addend = reg_operand (next (sum), nsp);*/
	/* evaluate displacement .... */
	if (dreg == NO_REG)
	  dreg = getreg(nsp.fixed);
	src.reg=0;
	src.value=addend;
	operate_fmt(ins,src.value,ind,dreg);
          /* ... add it to ind in new reg */
	is.b.base = dreg;
	is.b.offset = 0;
      }
      is.adval = 1;
      setinsalt(aa, is);
      wans.answhere = aa;
      wans.ashwhere = a;
      /* ... and deliver literal base_offset */
      keepexp(e, aa);
      return wans;
    }				/* end add_ptr */

    case subptr_tag: 		/* this is nugatory - previous transforms
			       make it into addptr or reff */
    {
      exp sum = child(e);
      int   ind = reg_operand(sum, sp);
      instore isa;
      isa.adval = 1;
      sum = next(sum);
      if (sum->tag == val_tag) {
	instore isa;
	isa.b.base = ind;
	isa.b.offset = -no(e);
	setinsalt(aa, isa);
      }
      else {
	if (dreg == 0)
	  dreg = getreg(sp.fixed);
	src.reg=0;
	src.value=ind;
	operate_fmt(i_subq,reg_operand(sum,guardreg(ind,sp)),src.value,dreg);
	isa.b.base = dreg;
	isa.b.offset = 0;
      }
      setinsalt(aa, isa);
      wans.answhere = aa;
      wans.ashwhere = a;
      keepexp(e, aa);
      return wans;
    }				/* end subptr */

    case reff_tag: {
	instore isa;
	wans = locate(child(e), sp, sh(child(e)), NO_REG);
	/* answer is going to be wans displaced by no(e) */

	switch (wans.answhere.discrim) {
	  case notinreg: {

	    isa = insalt(wans.answhere);
	    if (!isa.adval) {
	      /* wans is an actual pointer  in store, so make it into a
		 literal address.... */
	      int   reg = getreg(sp.fixed);
	      load_store(i_ldq,reg,isa.b);
	      isa.b.offset = 0;
	      isa.b.base = reg;
	      isa.adval = 1;
	    }
	      /* ... and add appropriate displacement to
		 give result */

	      /* make sure that alignment is correct.
	       64 bit data needs to be placed on 64 bit boundaries */
	    isa.b.offset += no(e) / 8;
	    setinsalt(wans.answhere, isa);
	    keepexp(e, wans.answhere);
	    break;
	  }
	  case inreg: {
	    /* wans is a pointer in a register */
	    isa.b.base = regalt(wans.answhere);
	    isa.adval = 1;
	    isa.b.offset = no(e) / 8;
	    setinsalt(wans.answhere, isa);
	    break;
	  }
	  default: {
	    error(ERR_INTERNAL, "Locate ? reg ");
	  }
	}
	wans.ashwhere = a;
	return wans;
      }				/* end reff */

   case cont_tag:
   case contvol_tag:
    {
      exp s = child(e);
      ans ason;
      instore isa;
      int   reg;
      where fc;
      fc = locate(s, sp, sh(e), NO_REG);
      ason = fc.answhere;
      /* answer is going to be the contents of address represented by fc
       */

      switch (ason.discrim) {
       case notinreg:
	{
	  isa = insalt(ason);
	  if (isa.adval) {	/* fc is a literal store address, so make
				   it into a direct one */
	    isa.adval = 0;
	    setinsalt(aa, isa);
	  }
	  else {		/* fc is an actual pointer in store ....
				 */
	    reg = getreg(sp.fixed);
	    load_store(i_ldq,reg,isa.b);
	    /*load_store(i_lda,reg,isa.b);*/
	    /* .... so load it into reg and deliver direct base-offset
	       (reg,0) */
	    isa.b.base = reg;
	    isa.b.offset = 0;
	    setinsalt(aa, isa);
	    if (e->tag!= contvol_tag && fc.ashwhere.ashalign != 1)
	      keepexp(e, aa);
	  }
	  goto breakson;

	}			/* end notinrg */

       case inreg:
	/* this one is fraught - it depends on only being used in
	   lh-value positions from vars- take care */
	{	/* This is very dubious indeed */
	  isa.b.base = regalt(ason);
	  isa.b.offset = 0;
	  isa.adval = 1;
	  aa = ason;
	  setinsalt(aa, isa);
	  /* fc is in register, so deliver literal(!? ) base-offset */
	  goto breakson;
	}

       case infreg: 		/* ditto caveat above */
	{
	  aa = ason;
	  goto breakson;
	}

       default: {
	 error(ERR_INTERNAL, "Locate ? reg");
       }
      }
     breakson:
      wans.answhere = aa;
      wans.ashwhere = a;
      return wans;

    }				/* end cont */

   case top_tag: 		/* does this ever happen ? */
    {
      setregalt(aa, 0);
      wans.answhere = aa;
      wans.ashwhere = a;
      return wans;
    }				/* end top */



   case field_tag: {
     instore isa;
     wans = locate(child(e), sp, sh(child(e)), NO_REG);
     /* answer is wans displace literally by no(e); it should always be
	a literal store adress */

     switch (wans.answhere.discrim) {
      case notinreg: {

	isa = insalt(wans.answhere);
	isa.b.offset += no(e) / 8;
	setinsalt(wans.answhere, isa);
	break;
      }
      default:
       error(ERR_INTERNAL, "field should be transformed");
     }
     wans.ashwhere = a;
     return wans;
   }				/* end field */







   default:
    /* general catch all; evaluate e into register and deliver it as a
       literal store address */
    {
      int   r = reg_operand(e, sp);
      instore is;
      if (r == 0) {		/* guard possible result from proc - can
				   do better */
	r = getreg(sp.fixed);
	operate_fmt(i_bis,0,0,r);
      }
      is.b.base = r;
      is.b.offset = 0;
      is.adval = 1;
      setinsalt(aa, is);
      wans.answhere = aa;
      wans.ashwhere = a;
      return wans;
    }

  }
}

where locate
(exp e, space sp, shape s, int dreg)
{
  ans ak;
  where w;
  ak = iskept(e);
  if (ak.discrim == inreg && (regalt(ak) == NO_REG)) {
    where w;
    w = locate1(e, sp, s, dreg);
    return w;
  }
  else {			/* e has been evaluated into a register */
    w.answhere = ak;
    w.ashwhere = ashof(s);
  }
  return w;
}
