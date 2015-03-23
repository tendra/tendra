/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Discovers "where" an "exp" is;
 * The where coding of an address tells one whether the result of
 * evaluating an exp is in a register or directly or literally in store,
 */

#include <assert.h>

#include <shared/check.h>
#include <shared/error.h>

#include <local/ash.h>

#include <construct/installtypes.h>
#include <construct/tags.h>
#include <construct/dec.h>
#include <construct/ash.h>

#include <main/print.h>

#include "codegen.h"
#include "geninst.h"
#include "proc.h"
#include "stack.h"
#include "locate.h"
#include "frames.h"
#include "localexpmacs.h"

/*
 * For non globals, boff encodes things in the following way:
 *
 * The number of bytes gives a displacement from different positions on
 * the stack depending on whether it is relative to R_SP R_FP or R_TP
 *
 * The stack below gives the worst case of the stack i.e a general_proc with
 * alloca:
 *
 *   |           |
 *   |           | #
 *   |           | |  x relative to R_TP i.e caller parameters
 *   |-----------| |                     in input caller parameter area
 *   | STACK     | |
 *   | LINK      | | STACK_ARG_AREA
 *   | AREA      | |
 *   |-----------|<--------R_TP
 *   | Input     |
 *   | Callees   |
 *   |           |
 *   |           |
 *   |           |
 *   |           |
 *   |-----------|<--------R_FP
 *   |           | |
 *   |           | |
 *   |           | |                          #
 *   |           | |                          | displacement x relative to R_FP
 *   |           | |                          | coded like this in regalloc
 *   |           | | p_frame_size             #
 *   |           | |                          |
 *   |           | |                          | p_locals_offset
 *   |           | |                          |
 *   |           | |                          |
 *   |           | # <--initial R_SP was here
 *   |-----------|
 *   |           | #
 *   |           | | x relative to R_SP i.e output caller parameter construction
 *   |-----------| |
 *   | STACK     | |
 *   | LINK      | | STACK_ARG_AREA
 *   | AREA      | |
 *   |-----------|<--------R_SP
 *
 */

/* decodes e to give a baseoff suitable for xxx_ins functions */
baseoff boff(exp e)
{
  baseoff an;

  if (isglob(e))
  {
    dec *gl = brog(e);
    long sno = gl->sym_number;

    /* an.base is negated global sym number, positive used for base reg number */
    an.base = - (sno + 1);
    an.offset = 0;
  }
  else
  {
    return boff_location(no(e));
  }
  return an;
}
baseoff boff_location(int n)
{
  baseoff an;
  int br = n & 0x3f;		/* base reg in bottom 6 bits */
  long off = (n>>6);		/* offset in bytes from br in rest */

  assert((n<0)==(off<0));	/* any sign propagated */
  if (br<0)
    br = -br;

  /*
   * There are three possiblilities for br
   * i.e R_TP R_FP R_SP
   *
   *   R_TP|
   *   -----
   *   if something is relative to R_TP it is a caller of the previous proc
   *   since R_TP is the top of the frame
   *
   *   R_FP|
   *   -----
   *   This is all locals to the current procedure
   *
   *   R_SP|
   *   -----
   *   This is used for constructing argument lists for calling parameters
   *
   * It is possible that all three are the same i.e they are all calculated
   * from the stack pointer. However in a general_proc things get nasty
   * and all three will point to different places
   */
  if (br == R_SP)
  {
    an.base = R_SP;
    an.offset = off;
    assert(off >= 0);
  }
  else if (br == R_FP)
  {
    if (p_has_fp)
    {
      an.base = R_FP;
      an.offset = p_locals_offset + off - p_frame_size;
    }
    else
    {
      an.base = R_SP;
      an.offset = p_locals_offset + off;
    }
  }
  else if (br == R_TP)
  {
    if (p_has_tp)
    {
      an.base = R_TP;
      an.offset = off;
    }
    else if (p_has_fp)
    {
      an.base = R_FP;
      an.offset = off;
    }
    else
    {
      an.base = R_SP;
      an.offset = off + p_frame_size;
    }
  }
  else
  {
    error(ERR_SERIOUS, "Error:boff_location: Unknown base");
  }
  return an;
}

/*
 * type is either:
 * INPUT_CALLER_PARAMETER, INPUT_CALLEE_PARAMETER, OUTPUT_CALLER_PARAMETER
 * offset shoulb be in bytes
 */
int ENCODE_FOR_BOFF(int off, int type)
{
  int encode_offset;
  int encode_base;

  switch (type)
  {
   case INPUT_CALLER_PARAMETER:
    {
      encode_base = R_TP;
      encode_offset = off + STACK_ARG_AREA;
      break;
    }
   case INPUT_CALLEE_PARAMETER:
    {
      encode_base = R_FP;
      encode_offset = p_frame_size - p_locals_offset + EXTRA_CALLEE_BYTES + off;
      break;
    }
   case OUTPUT_CALLER_PARAMETER:
    {
      encode_base = R_SP;
      encode_offset = STACK_ARG_AREA + off;
      break;
    }
   default:
    error(ERR_SERIOUS, "Unknown encodeing for ENCODE_FOR_BOFF");
  }
  return (encode_offset<<6) + encode_base;
}

/* mutual recursion between locate1() and locate() */
where locate(exp, space, shape, int);

/*
 * finds the address of e using shape s; sp gives available t-regs for any
 * inner evaluation. dreg is historical.
 */
static where locate1(exp e, space sp, shape s, int dreg)
{
  ash a;
  ans aa;
  where wans;

  asm_comment("locate1: name(e) =%d, name(s) =%d, dreg=%d", name(e), name(s), dreg);

  a = ashof(s);

  switch (name(e))
  {
   case name_tag:
    {
      /* NAME_TAG */
      exp dc = son(e);
      bool var = isvar(dc);

      asm_comment("locate1 name_tag: name(dc) =%d, var=%d", name(dc), var);

      if (props(dc) & defer_bit)
      {
	/*
	 * ... it has been identified with a simple expression which is
	 * better evaluated every time
	 */
	where w;

	w = locate(son(dc), sp, sh(son(dc)), dreg);

	if (no(e) == 0)
	{
	  aa = w.answhere;
	}
	else
	{
	  instore is;

	  switch (w.answhere.discrim)
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

	fr.fr = no(dc);
	fr.dble = (a.ashsize == 64)? 1 : 0;
	setfregalt(aa, fr);
      }
      else
      {
	/* ... it is in memory */
	instore is;

	if (var|| (name(sh(e)) == prokhd &&
		     (son(dc) == NULL || IS_A_PROC(son(dc)))))
	{
	  is.adval = 1;
	  /* If it is a var tag you can get address of it */
	}
	else
	{
	  is.adval = 0;
	}
	is.b = boff(dc);

	is.b.offset += (no(e) / 8);

#if 1
	if (var && name(sh(e))!= prokhd && !IS_FIXREG(is.b.base) && is.b.offset == 0)
	{
	  /*
	   * A global which has to be accessed via TOC.
	   *
	   * We load it explicitly into reg here so we can use the reg contents
	   * tracking mechanism for addresses found in the TOC.
	   *
	   * If we did not do this, we would still generate correct code,
	   * but needlessly reload from TOC.
	   * +++ offset != 0 -> keepglob for 0 offset & keepreg for offset
	   */
	  if (dreg == 0)
	    dreg = getreg(sp.fixed);

	  set_ins(is.b, dreg);
	  keepreg(e, dreg);
	  asm_comment("locate1 name_tag: keepreg glob adval=%d bo={%d,%ld}", is.adval, is.b.base, is.b.offset);
	  is.b.base = dreg;
	  is.b.offset = 0;
	}
#endif
	setinsalt(aa, is);

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

      wsum = locate(sum, sp, sh(sum), 0);
      asum = wsum.answhere;

      /*
       * answer is going to be wsum displaced by integer result of evaluating
       * bro(sum)
       */

      switch (asum.discrim)
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
	      /* ... it is not a base-offset, so make it one */
	      reg = getreg(sp.fixed);
	      set_ins(b, reg);
	      keepreg(sum, reg);
	      b.base = reg;
	      b.offset = 0;
	    }
	    nsp = guardreg(b.base, sp);

	    addend = reg_operand(bro(sum), nsp);

	    /* evaluate the displacement ... */
	    if (dreg == 0)
	      dreg = getreg(nsp.fixed);
	    rrr_ins(i_a, b.base, addend, dreg);

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
	    ld_ins(i_l, is.b, ind);
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

      if (name(bro(sum)) == env_offset_tag || name(bro(sum)) ==general_env_offset_tag)
      {
	is.b.base = ind;
	is.b.offset = frame_offset(son(bro(sum)));
      }
      else
      {
	addend = reg_operand(bro(sum), nsp);

	/* evaluate displacement, add it to ind in new reg */
	if (dreg == 0)
	  dreg = getreg(nsp.fixed);
	rrr_ins(i_a, ind, addend, dreg);

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

  case subptr_tag:
	/*
	 * This is nugatory - previous transforms make it into addptr or reff
	 */
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
	rrr_ins(i_s, ind, reg_operand(sum, guardreg(ind, sp)), dreg);
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

      /* answer is going to be wans displaced by no(e) */

      wans = locate(son(e), sp, sh(son(e)), 0);

      switch (wans.answhere.discrim)
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

	    ld_ins(i_l, isa.b, reg);
	    isa.b.offset = 0;
	    isa.b.base = reg;
	    isa.adval = 1;
	  }

	  /*
	   * ... and add appropriate displacement to give result
	   */

	  isa.b.offset += no(e) / 8;
	  setinsalt(wans.answhere, isa);
	  keepexp(e, wans.answhere);
	  break;
	}
      case inreg:
	{
	  /* wans is a pointer in a register */
	  isa.b.base = regalt(wans.answhere);
	  isa.adval = 1;

	  isa.b.offset = no(e) / 8;
	  setinsalt(wans.answhere, isa);
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
      exp p = son(e);
      ans ason;
      instore isa;
      int reg;
      where fc;

      fc = locate(p, sp, sh(e), 0);
      ason = fc.answhere;

      /*
       * answer is going to be the contents of address represented by fc
       */

      switch (ason.discrim)
      {
       case notinreg:
	{
	  isa = insalt(ason);
	  asm_comment("locate1 cont_tag: adval=%d bo={%d,%ld}", isa.adval, isa.b.base, isa.b.offset);
	  if (isa.adval)
	  {
	    /* literal store address, so make it into a direct one */
	    isa.adval = 0;
	    setinsalt(aa, isa);
	  }
	  else
	  {
	    /*
	     * actual pointer in store
	     * so load it into reg and deliver direct base-offset (reg,0)
	     */
	    reg = getreg(sp.fixed);
	    ld_ins(i_l, isa.b, reg);
	    isa.b.base = reg;
	    isa.b.offset = 0;
	    setinsalt(aa, isa);
	    if (name(e)!= contvol_tag && fc.ashwhere.ashalign != 1)
	      keepexp(e, aa);
	  }
	  goto breakson;

	}			/* end notinrg */

      case inreg:

	/*
	 * this one is fraught
	 * - it depends on only being used in lh-value positions from vars
	 * - take care
	 */
	{
	  isa.b.base = regalt(ason);
	  isa.b.offset = 0;
	  isa.adval = 1;
	  setinsalt(aa, isa);
	  /* fc is in register, so deliver literal(!? ) base-offset */
	  goto breakson;
	}

      case infreg:		/* ditto caveat above */
	{
	  aa = ason;
	  goto breakson;
	}
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
       * answer is wans displace literally by no(e);
       * it should always be a literal store address
       */

      switch (wans.answhere.discrim)
      {
      case notinreg:
	{
	  isa = insalt(wans.answhere);
	  isa.b.offset += no(e) / 8;
	  setinsalt(wans.answhere, isa);
	  asm_comment("locate field_tag: adjusting byte offset to %ld", isa.b.offset);
	  break;
	}
       default:
	error(ERR_SERIOUS, "field should be transformed");
      }
      wans.ashwhere = a;
      return wans;
    }				/* end field */

  default:
    {
      /*
       * general catch all;
       * evaluate e into register and deliver it as a literal
       * store address
       */
      int r = reg_operand(e, sp);
      instore is;

      if (r == R_RESULT)
      {
	/* guard possible result from proc - can do better +++ */
	asm_comment("guarding possible result");
	r = getreg(sp.fixed);
	if (r != R_RESULT)
	{
	  mov_rr_ins(R_RESULT, r);asm_comment("move R_RESULT to reg");
	}
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

/*
 * locate differs from locate1 only in that it looks to see if e has already
 * been evaluated and remembered by register contents tracking scheme
 */
where locate(exp e, space sp, shape s, int dreg)
{
  ans ak;
  where w;

  /* Check to see if e has already been evaluated and remembered */
  if (!IS_R_NO_REG(dreg))
  {
    /* first try for exact reg */
    ak = iskept_inreg(e, dreg);
    if (ak.discrim == inreg && (regalt(ak) == 0))
      ak = iskept(e);			/* no luck, try anywhere */
  }
  else
  {
    ak = iskept(e);
  }

  if (ak.discrim == inreg && (regalt(ak) == 0))	/* See if we found a register */
  {
    w = locate1(e, sp, s, dreg);/* No register found so we must use locate1 */
  }
  else
  {
    asm_comment("locate: iskept() found value inreg=%d [reg=%d]", ak.discrim == inreg, regalt(ak));
    w.answhere = ak;
    w.ashwhere = ashof(s);
  }
  return w;
}
