/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* locate.c
     discovers "where" an "exp" is;
     The where coding of an address tells one whether the result of
      evaluating an exp is in a register or directly or literally in store,
*/

#include <assert.h>

#include <shared/error.h>

#include <local/ash.h>

#include <tdf/tag.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>
#include <construct/exp.h>
#include <construct/shape.h>

#include <main/print.h>

#include "addrtypes.h"
#include "inst_fmt.h"
#include "regmacs.h"
#include "hppains.h"
#include "bitsmacs.h"
#include "procrec.h"
#include "guard.h"
#include "eval.h"
#include "regexps.h"
#include "getregs.h"
#include "move.h"
#include "regable.h"
#include "code_here.h"
#include "proc.h"
#include "frames.h"
#include "locate.h"
#include "localexpmacs.h"


/* decodes x to give a baseoff suitable for xxxx_ins functions */
baseoff boff
(exp e)
{

  int n = no(e);
  int b = n & 0x3f;
  baseoff an;

  if (isglob(e))
  {
    /* bro() is index in main_globals */
    dec *gl = brog(e);
    long sno = gl->sym_number;
    an.base = - (sno + 1);
    an.offset = 0;
  }
  else if (name(son(e)) ==caller_name_tag)
  {
     int n = no(e);
     an.base = SP;
     an.offset = - (n>>3);
  }
  else if (isparam(e))
  {
     /* parameter */
     assert(name(son(e)) == clear_tag);
     if (Has_vcallees)
     {
	an.base = FP;
     }
     else
     {
	an.base = EP;
     }
     if (name(son(e)) ==formal_callee_tag)
     {
	an.offset=(no(son(e))-callees_offset)>>3;/* outermost ()'s for gcc */
     }
     else
     {
	an.offset=(-no(son(e))-params_offset)>>3;/* outermost ()'s for gcc */
     }
  }
  else if (b == GR17)
  {
     /* locally declared */
     an.base = EP;
     an.offset = ((n-b) >>4) - (locals_offset>>3);
  }
  else if (b == EP)
  {
    /* on stack temps (should not happen) */
    an.base = EP;
    an.offset = (n - b) >> 4;
  }
  else if (b <= 31)
  {
    /* other base reg and offset */
    an.base = b;
    an.offset = ((n - b) >> 4);
  }
#if 1
  /* +++ obsolete */
  else if (b == 32)
  {
    /* global names */
    an.base = - ((n - b) >> 6);
    an.offset = 0;
  }
  else if (b == 33)
  {
    /* local data label: LDNNNN */
    an.base = (n - b) >> 6;
    an.offset = 0;
  }
#endif
  else
  {
    asm_comment("baseoff: n=%x, b=%d, n>>4=%d", n, b, n >> 4);
    error(ERR_SERIOUS, "not a baseoff in boff");
  }
  asm_comment("baseoff: base=%d off=%ld", an.base, an.offset);
  return an;
}


 /*
  * locate differs from locate1 only in that it looks to see e has already
  * been evaluated somehow
  */
where locate(exp, space, shape, int);


 /*
  * finds the address of e using shape s; sp gives available t-regs for any
  * inner evaluation. dreg is historical.
  */
where locate1
(exp e, space sp, shape s, int dreg)
{
  ash a;
  ans aa;
  where wans;
#if 0				/* causes core dump spec/espresso/set.c */
  asm_comment("locate1: %s, %s, dreg=%d",(int)tag_name(name(e)), (int)sh_name(name(s)), dreg);
  asm_comment("        space= (%ld,%ld) no(e) =%d no(son(e)) =%d", sp.fixed, sp.flt, no(e), no(son(e)));
#endif

  a = ashof(s);

/*
  while (name(e) == diag_tag || name(e) == fscope_tag || name(e) == cscope_tag)
  {
    e = son(e);
  }
*/
  switch (name(e))
  {
  case name_tag:
    {
      exp dc = son(e);
      bool var = isvar(dc);

      /* this a locally declared name ... */
      if (props(dc) & defer_bit)
      {

	/*
	 * ... it has been identified with a simple expression which is better
	 * evaluated every time
	 */
	where w;

	asm_comment("locate1: name_tag: defer_bit");

	w = locate(son(dc), sp, sh(son(dc)), dreg);

	if (no(e) == 0)
	{
	  aa = w.answhere;
	}
	else
	{
	  instore is;

	  switch (discrim(w.answhere))
	  {
	  case notinreg:
	    {
	      is = insalt(w.answhere);
	      is.b.offset += (no(e) / 8);
	      break;
	    }
	  default:
	    error(ERR_SERIOUS, "name not deferable");
	  }

	  setinsalt(aa, is);
	}
      }
      else if (props(dc) & inreg_bits)
      {
	/* ... it has been allocated in a fixed point reg */

	asm_comment("locate1: name_tag: fixed point reg%s", var ? " var" : "");

	if (var)
	{
	  setregalt(aa, no(dc));
	}
	else
	{
	  instore b;

	  b.b.base = no(dc);
	  b.b.offset = 0;
	  b.adval = 1;
	  setinsalt(aa, b);
	}
      }
      else if (props(dc) & infreg_bits)
      {
	/* ... it has been allocated in a floating point reg */

	freg fr;

	asm_comment("locate1: name_tag: fixed point reg");

	fr.fr = no(dc);
	fr.dble = (a.ashsize==64 ? 1 : 0);
	setfregalt(aa, fr);
      }
      else
      {
	/* ... it is in memory */
	instore is;

	if (var || (name(sh(e)) == prokhd &&
		   (son(dc) == NULL || IS_A_PROC(son(dc)))))
	{
	  is.adval = 1;
	}
	else
	{
	  is.adval = 0;
	}
	is.b = boff(dc);
#if USE_BITAD
	if (a.ashalign == 1 && (var || name(sh(e))!= ptrhd))
	  /* some bit field */
	{
	  is.b.offset = (is.b.offset << 3) + no(e);
	  setbitadalt(aa, is);
	}
	else
#endif
	{
	  is.b.offset += (no(e) / 8);
	  setinsalt(aa, is);
	}
      }
      wans.answhere = aa;
      wans.ashwhere = a;
      return wans;
    }

  case addptr_tag:
    {
      exp sum = son(e);
      where wsum;
      int addend;
      space nsp;
      int reg;
      int ind = R_NO_REG;
      instore is;
      ans asum;
      int shift;

      wsum = locate(sum, sp, sh(sum), 0);
      asum = wsum.answhere;

      /*
       * answer is going to be wsum displaced by integer result of evaluating
       * bro(sum)
       */

      switch (discrim(asum))
      {
      case notinreg:
	{
	  is = insalt(asum);
	  if (is.adval)
	  {
	    /* wsum is a literal address in store ... */
	    baseoff b;

	    b = is.b;
	    if (!IS_FIXREG(b.base))
	    {
	      /* ... it is not a base-offset , so make it one */

	      reg = getreg(sp.fixed);
	      set_ins("",b, reg);
	      keepreg(sum, reg);
	      b.base = reg;
	      b.offset = 0;

	    }

	    nsp = guardreg(b.base, sp);

	    shift=no(bro(son(bro(sum))));
	    if (name(bro(sum)) ==offset_mult_tag && name(bro(son(bro(sum)))) ==val_tag && (shift==0 || shift==2 || shift==4))
	    {
	       addend=reg_operand(son(bro(sum)),nsp);
	       if (dreg == 0)
		  dreg = getreg(nsp.fixed);
	       rrr_ins(shift==0 ? i_add :(shift==2 ? i_sh1add : i_sh2add),                           c_,addend,b.base,dreg);
	    }
	    else
	    {
	       addend = reg_operand(bro(sum), nsp);
	       /* evaluate the displacement ... */
	       if (dreg == 0)
		  dreg = getreg(nsp.fixed);
	       rrr_ins(i_add,c_,b.base,addend,dreg);
	    }

	    clear_reg(dreg);

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
	  else
	  {
	     /* wsum represents an actual pointer in store... */
	     /* ... so load it into a good register */
	     ind = getreg(sp.fixed);
	     ld_ins(i_lw,1,is.b,ind);
	  }
	  break;
	}			/* end notinreg */

      case inreg:
	{
	  /* wsum is already in reg */
	  ind = regalt(asum);
	  break;
	}

      default:
	{
	  error(ERR_SERIOUS, "locate ? reg");
	}
      }				/* end case */

      /* register ind contains the evaluation of 1st operand of addptr */
      nsp = guardreg(ind, sp);
      /* evaluate displacement, add it to ind in new reg */
      if (name(bro(sum)) == env_offset_tag ||
	  name(bro(sum)) == general_env_offset_tag)
      {
	  is.b.base = ind;
	  is.b.offset = frame_offset(son(bro(sum)));
      }
      else
      {
	 shift=no(bro(son(bro(sum))));
	 if (name(bro(sum)) ==offset_mult_tag && name(bro(son(bro(sum)))) ==val_tag && (shift==0 || shift==2 || shift==4))
	 {
	    addend=reg_operand(son(bro(sum)),nsp);
	    if (dreg == 0)
	       dreg = getreg(nsp.fixed);
	    rrr_ins(shift==0 ? i_add :(shift==2 ? i_sh1add : i_sh2add),                           c_,addend,ind,dreg);
	 }
	 else
	 {
	    addend = reg_operand(bro(sum), nsp);

	    if (dreg == 0)
	       dreg = getreg(nsp.fixed);
	    rrr_ins(i_add,c_,ind,addend,dreg);
	 }
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

  case subptr_tag:		/* this is nugatory - previous transforms make
				 * it into addptr or reff */
    {
      exp sum = son(e);
      int ind = reg_operand(sum, sp);
      instore isa;

      isa.adval = 1;
      sum = bro(sum);
      if (name(sum) == val_tag)
      {
	instore isa;

	isa.b.base = ind;
	isa.b.offset = -no(e);
	setinsalt(aa, isa);
      }
      else
      {
	if (dreg == 0)
	   dreg = getreg(sp.fixed);
	rrr_ins(i_sub,c_,ind,reg_operand(sum,guardreg(ind,sp)),dreg);
	isa.b.base = dreg;
	isa.b.offset = 0;
      }
      setinsalt(aa, isa);
      wans.answhere = aa;
      wans.ashwhere = a;
      keepexp(e, aa);
      return wans;
    }				/* end subptr */

  case reff_tag:
    {
      instore isa;
#if USE_BITAD
      bool bitfield = 0;
#endif

      /* answer is going to be wans displaced by no(e) */
      wans = locate(son(e), sp, sh(son(e)), 0);

#if USE_BITAD
      bitfield = ((name(sh(e)) == ptrhd) && (al1(sh(e)) == 1));
#endif
      switch (discrim(wans.answhere))
      {
      case notinreg:
	{
	  isa = insalt(wans.answhere);
	  if (!isa.adval)
	  {

	    /*
	     * wans is an actual pointer  in store, so make it into a literal
	     * address....
	     */
	    int reg = getreg(sp.fixed);

	    ld_ins(i_lw,0,isa.b,reg);
	    isa.b.offset = 0;
	    isa.b.base = reg;
	    isa.adval = 1;
	  }

	  /*  ... and add appropriate displacement to give result  */

#if USE_BITAD
	  if (bitfield)
	  {
	    isa.b.offset <<= 3;
	    isa.b.offset += no(e);
	    setbitadalt(wans.answhere, isa);
	  }
	  else
#endif
	  {
	    isa.b.offset += no(e) / 8;
	    setinsalt(wans.answhere, isa);
	    keepexp(e, wans.answhere);
	  }
       	  break;
	}
#if USE_BITAD
      case bitad:
	{
	  isa = bitadalt(wans.answhere);
	  if (!isa.adval)
	  {
	    error(ERR_SERIOUS, "no var bit selection");
	  }
	  /* wans is a literal bit address */
	  isa.b.offset += no(e);
	  setbitadalt(wans.answhere, isa);
	  break;
	}
#endif
      case inreg:
	{
	  /* wans is a pointer in a register */
	  isa.b.base = regalt(wans.answhere);
	  isa.adval = 1;
#if USE_BITAD
	  if (bitfield)
	  {
	    isa.b.offset = no(e);
	    setbitadalt(wans.answhere, isa);
	  }
	  else
#endif
	  {
	    isa.b.offset = BITS2BYTES(no(e));
	    setinsalt(wans.answhere, isa);
	  }
	  break;
	}
      default:
	{
	  error(ERR_SERIOUS, "locate ? reg ");
	}
      }
      wans.ashwhere = a;
      return wans;
    }				/* end reff */

  case cont_tag:
  case contvol_tag:
    {
      exp s = son(e);
      ans ason;
      instore isa;
      int reg;
      where fc;

      fc = locate(s, sp, sh(e), 0);
      ason = fc.answhere;

      /*
       * answer is going to be the contents of address represented by fc
       */

      asm_comment("locate1: cont[vol]_tag: %d", (int) discrim(ason));

      switch (discrim(ason))
      {
      case notinreg:
	{
	  isa = insalt(ason);
	  if (isa.adval)
	  {
	    /* literal store address, so make it into a direct one */
	    asm_comment("locate1: cont[vol]_tag: literal store address");
	    isa.adval = 0;
	    setinsalt(aa, isa);
	  }
	  else
	  {

	    /*
	     * actual pointer in store so load it into reg and deliver direct
	     * base-offset (reg,0)
	     */
	    asm_comment("locate1: cont[vol]_tag: ptr in store");
	    reg = getreg(sp.fixed);
	    ld_ins(i_lw,1,isa.b,reg);
	    isa.b.base = reg;
	    isa.b.offset = 0;
	    setinsalt(aa, isa);
	    if (name(e)!= contvol_tag && fc.ashwhere.ashalign != 1)
	      keepexp(e, aa);
	  }
#if USE_BITAD
	  if (fc.ashwhere.ashalign == 1)	/* ... adjust for bit contents */
	  {
	    isa.b.offset <<= 3;
	    setbitadalt(aa, isa);
	  }
#endif
	  goto breakson;

	}			/* end notinrg */

      case inreg:

	/*
	 * this one is fraught - it depends on only being used in lh-value
	 * positions from vars - take care
	 */
	{
	  isa.b.base = regalt(ason);
	  isa.b.offset = 0;
	  isa.adval = 1;
#if USE_BITAD
	  if (a.ashalign == 1)
	  {
	    setbitadalt(aa, isa);
	  }
	  else
#endif
	  {
	    setinsalt(aa, isa);
	  }
	  /* fc is in register, so deliver literal(!? ) base-offset */
	  goto breakson;
	}

      case infreg:		/* ditto caveat above */
	{
	  aa = ason;
	  goto breakson;
	}

#if USE_BITAD
      case bitad:
	{
	  isa = bitadalt(ason);
	  if (!isa.adval)
	  {
	    error(ERR_SERIOUS, "no ptr bits");
	  }
	  /* fc is a literal address of bits, so make it direct */
	  isa.adval = 0;
	  setbitadalt(aa, isa);
	  goto breakson;
	}
#endif
      default:
	{
	  error(ERR_SERIOUS, "locate ? reg");
	}
      }
  breakson:
      wans.answhere = aa;
      wans.ashwhere = a;
      return wans;

    }				/* end cont */

  case top_tag:		/* does this ever happen ? */
    {
      setregalt(aa, 0);
      wans.answhere = aa;
      wans.ashwhere = a;
      return wans;
    }				/* end top */

  case field_tag:
    {
      instore isa;

      wans = locate(son(e), sp, sh(son(e)), 0);

      /*
       * answer is wans displace literally by no(e); it should always be a
       * literal store address
       */

      switch (discrim(wans.answhere))
      {
      case notinreg:
	{
	  isa = insalt(wans.answhere);
#if USE_BITAD
	  if (a.ashalign == 1)
	  {
	    isa.b.offset += no(e);
	    setbitadalt(wans.answhere, isa);
	  }
	  else
#endif
	  {
	    isa.b.offset += no(e) / 8;
	    setinsalt(wans.answhere, isa);
	  }
	  break;
	}
#if USE_BITAD
      case bitad:
	{
	  wans.answhere.val.instoreans.b.offset += no(e);
	  asm_comment("locate field_tag: adjusting bitad offset to %d", wans.answhere.val.instoreans.b.offset);
	  break;
	}
#endif
      default:
	error(ERR_SERIOUS, "field should be transformed");
      }
      wans.ashwhere = a;
      return wans;
    }				/* end field */
  default:
    {

      /*
       * general catch all; evaluate e into register and deliver it as a
       * literal store address
       */
      int r = reg_operand(e, sp);
      instore is;

      if (r == RET0)		/* guard possible result from proc - can do
				 * better */
      {
	asm_comment("guarding possible result");	/* +++ remove */
	r = getreg(sp.fixed);
	if (r != RET0)
	  rr_ins(i_copy,RET0,r);
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
  if (discrim(ak) == inreg && (regalt(ak) == 0))
  {
    w = locate1(e, sp, s, dreg);
  }
  else
  {
    asm_comment("locate: iskept() found value");
    w.answhere = ak;
    w.ashwhere = ashof(s);
  }
  return w;
}












