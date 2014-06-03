/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>
#include <shared/error.h>

#include <local/cpu.h>

#include <reader/exptypes.h>

#include "localflags.h"
#include "memtdf.h"
#include "codegen.h"
#include "geninst.h"
#include "needscan.h"
#include "comment.h"
#include "muldvrem.h"
#include "translate.h"
#include "error.h"

#define BITS_PER_WORD		32

#define MAX_MUL_POW2_OFFSET	2	/* max permissable X in 2**n +- X for
					 * constant multiply */

#define NOT_MUL_CONST_SIMPLE	(MAX_MUL_POW2_OFFSET+1)
 /* any constant larger than permissable X offset in 2**n +- X */

#define IS_POW2(c)		((c)!= 0 && ((c) & ((c) -1)) == 0)




/*
 * Utility functions.
 */

/* return bit number 0..31 from right of word of 'c' which has one bit set */
static int bit_no(unsigned long c)
{
  int shift_const;
  unsigned long mask;

  ASSERT(IS_POW2(c));

  for (mask = 1, shift_const = 0; mask != c; mask = mask << 1)
  {
    shift_const++;
  }

  return shift_const;
}




/*
 * Multiply.
 */


/* is constval +ve const 2**n or 2**(n +- X) where abs(X) <= MAX_MUL_POW2_OFFSET */
static int offset_mul_const_simple(long constval, bool sgned)
{
  int i;

  FULLCOMMENT1("offset_mul_const_simple: %ld", constval);

  if (constval < 0)
  {
    if (sgned)
      constval = -constval;
    else
      return NOT_MUL_CONST_SIMPLE;	/* very rare case */
  }

  for (i = 0; i <= MAX_MUL_POW2_OFFSET; i++)
  {
    long c;			/* power of two close to constval */

    /* check for add offsets, avoiding overflow confusion */
    c = constval - i;
    if (IS_POW2(c) && c+i == constval)
      return i;

    /* check for sub offset of 1 only, avoiding overflow confusion */
    if (i == 1)
    {
      c = constval + i;
      if (IS_POW2(c) && c-i == constval)
	return -i;
    }
  }

  return NOT_MUL_CONST_SIMPLE;
}


/* generate code for multiply by constant */
static void mul_const_simple(int src, long constval, int dest, bool sgned)
{
  int shift_const;
  long c;			/* power of two close to constval */
  int add_sub;			/* difference from power of two: +N add, 0
				 * nop, -N sub */

  if (sgned && constval < 0)
  {
    if (constval == -1)
    {
      /* X * -1 => -X */
      rr_ins(i_neg, src, dest);
      return;
    }
    constval = -constval;
    rr_ins(i_neg, src, R_TMP0);	/* incorrect to modify source */
    src = R_TMP0;
  }

  if (constval == 0)
  {
    ld_const_ins(0, dest);	/* rare case not handled by mul_const_X() */
    return;
  }
  else if (constval == 1)
  {
    if (src != dest)
    {
      mov_rr_ins(src, dest);comment(NIL);
    }
    return;
  }
  else if (constval == 2)
  {
    /* use add, which can be peep-hole optimised to addcc later */
    rrr_ins(i_a, src, src, dest);
    return;
  }

  add_sub = offset_mul_const_simple(constval, sgned);
  c = constval - add_sub;

  ASSERT(constval == c + add_sub);

  shift_const = bit_no(c);

  FULLCOMMENT3("mul_const_simple: constval=%#lx shift_const=%d add_sub=%d", constval, shift_const, add_sub);
  ASSERT(constval == (1 << shift_const) + add_sub);

  if (add_sub == 0)
  {
    rir_ins(i_sl, src, shift_const, dest);
  }
  else
  {
    /* add_sub != 0 */
    Instruction_P i_add_sub;
    int n;			/* number of add_sub instructions */
    int inter_reg;		/* for partial result */
    int i;

    if (add_sub > 0)
    {
      i_add_sub = i_a;
      n = add_sub;
    }
    else
    {
      i_add_sub = i_s;
      n = -add_sub;
    }

    if (src == dest)
    {
      inter_reg = R_TMP0;	/* must preserve src for add/sub */
    }
    else
    {
      inter_reg = dest;
    }

    ASSERT(src != inter_reg);

    rir_ins(i_sl, src, shift_const, inter_reg);

    /* all but final add_sub */
    for (i = 1; i < n; i++)
    {
      rrr_ins(i_add_sub, inter_reg, src, inter_reg);
    }

    /* final add_sub to dest reg */
    rrr_ins(i_add_sub, inter_reg, src, dest);
  }
}



/* generate code for multiply using i_muls unless simple constant */
static int do_mul_comm_const(exp seq, space sp, int final_reg, bool sgned)
{
  exp arg2 = bro(seq);
  int lhs_reg = reg_operand(seq, sp);

  ASSERT(name(arg2) == val_tag && offset_mul_const_simple(no(arg2), sgned)!= NOT_MUL_CONST_SIMPLE);


  sp = guardreg(lhs_reg, sp);

  ASSERT(last(arg2));			/* refactor() & scan() should move const to last */

  if (final_reg == R_NO_REG)
    final_reg = getreg(sp.fixed);	/* better code from mul_const if src != dest reg */

  mul_const_simple(lhs_reg, no(arg2), final_reg, sgned);

  return final_reg;
}


/* generate code for divide using i_divs/i_div unless simple constant */
static int do_div(exp seq, space sp, int final_reg, bool sgned)
{
  exp lhs = seq;
  exp rhs = bro(lhs);
  exp e = bro(rhs);

  int div_type=name(bro(rhs));

  int lhs_reg = reg_operand(lhs, sp);
  int rhs_reg;

  sp = guardreg(lhs_reg, sp);

  if (final_reg == R_NO_REG)
  {
    final_reg = getreg(sp.fixed);
    sp = guardreg(final_reg, sp);
  }

  ASSERT(last(rhs));

  if (name(rhs) == val_tag && IS_POW2(no(rhs)))
  {
    /*
     * OPTIMISATION: Division by power of 2 can be done as a shift
     */
    long constval = no(rhs);
    if (!optop(e) && constval == 0)
    {
      /* division by zero goto error jump */
      uncond_ins(i_b,no(son(pt(e))));
      return final_reg;
    }
    if (constval>0 && IS_POW2(constval))
    {
      /* const optim, replace div by 2**n by shift right */

      int shift_const = bit_no(constval);

      if (constval==1)
      {
	/* result always lhs */
	mov_rr_ins(lhs_reg, final_reg);comment(NIL);
      }
      else if (sgned && div_type!=div1_tag)
      {
	/* signed, adjust lhs before shift */

	/* +++ the divide instructions rounds to zero, but the shift
	 * instruction sets the carry bit if the result is negative so a
	 * shift follwed by an add-with-carry instruction is equivalent to
	 * a round-to-zero divide.
	 */

	int tmp_reg = R_TMP0;

	ASSERT(shift_const>0);			/* assumed below */

	if (shift_const-1 != 0)
	{
	  rir_ins(i_sra, lhs_reg, shift_const-1, tmp_reg);
	  rir_ins(i_sr, tmp_reg, 32-shift_const, tmp_reg);
	}
	else
	{
	  rir_ins(i_sr, lhs_reg, 32-shift_const, tmp_reg);
	}
	rrr_ins(i_a, lhs_reg, tmp_reg, tmp_reg);
	rir_ins(i_sra, tmp_reg, shift_const, final_reg);
      }
      else
      {
	/* div1_tag and unsigned */
	if (sgned)
	{
	  rir_ins(i_sra, lhs_reg, shift_const, final_reg);
	}
	else
	{
	  rir_ins(i_sr, lhs_reg, shift_const, final_reg);
	}
      }
      return final_reg;
    }
  }

  rhs_reg = reg_operand(rhs,sp);
  if (ERROR_TREATMENT(e))
  {
    div_error_treatment(lhs_reg, rhs_reg, e);
  }

  if (cpu == CPU_POWERPC)
  {
    /* PowerPC has nicer divide instructions */
    if (div_type !=div1_tag || !sgned)
    {
      rrr_ins(sgned?i_divw:i_divwu,lhs_reg,rhs_reg,final_reg);
    }
    else
    {
      int creg = next_creg();
      int creg2 = next_creg();
      int lab =new_label();

      /* signed div1_tag needs special care */
      rrr_ins(i_xor,lhs_reg,rhs_reg,R_TMP0);
      rir_ins(i_and,R_TMP0,0x80000000,R_TMP0);
      cmp_ri_ins(i_cmp,R_TMP0,0,creg);
      rrr_ins(i_divw,lhs_reg,rhs_reg,final_reg);
      bc_ins(i_beq,creg,lab,LIKELY_TO_JUMP); /* both the same sign same as div2 so jump over*/
      rrr_ins(i_muls,rhs_reg,final_reg,R_TMP0);
      rrr_ins(i_sf,R_TMP0,lhs_reg,R_TMP0);
      cmp_ri_ins(i_cmp,R_TMP0,0,creg2);
      bc_ins(i_beq,creg2,lab,UNLIKELY_TO_JUMP); /* 0 remainder jump over */
      rir_ins(i_a,final_reg,-1,final_reg); /* subtract one from answer */
      set_label(lab);
    }

  }
  else
  {
    /* RS/6000 and Common code */
    if (sgned)
    {
      if (div_type==div1_tag)
      {
	int creg = next_creg();
	int creg2 = next_creg();
	int lab =new_label();

	/* signed div1_tag needs special care */
	rrr_ins(i_xor,lhs_reg,rhs_reg,R_TMP0);
	rir_ins(i_and,R_TMP0,0x80000000,R_TMP0);
	cmp_ri_ins(i_cmp,R_TMP0,0,creg);
	rrr_ins(i_divs,lhs_reg,rhs_reg,final_reg);
	bc_ins(i_beq,creg,lab,LIKELY_TO_JUMP); /* both the same sign same as div2 so jump over*/
	rrr_ins(i_muls,rhs_reg,final_reg,R_TMP0);
	rrr_ins(i_sf,R_TMP0,lhs_reg,R_TMP0);
	cmp_ri_ins(i_cmp,R_TMP0,0,creg2);
	bc_ins(i_beq,creg2,lab,UNLIKELY_TO_JUMP); /* 0 remainder jump over */
	rir_ins(i_a,final_reg,-1,final_reg); /* subtract one from answer */
	set_label(lab);
      }
      else
      {
	/* signed divide is easy */
	rrr_ins(i_divs, lhs_reg, rhs_reg, final_reg);
      }
    }
    else
    {
      /* unsigned divide */
      int safe_rhs_reg;
      int creg1 = next_creg();
      int creg2 = next_creg();
      int endlab = new_label();

      ASSERT(creg1 != creg2);

      if (final_reg != rhs_reg)
      {
	safe_rhs_reg = rhs_reg;
      }
      else
      {
	/* early setting of final_reg will clobber rhs_reg so make safe copy */
	safe_rhs_reg = getreg(sp.fixed);
	mov_rr_ins(rhs_reg, safe_rhs_reg);comment(NIL);
      }

      /* compares as early as possible to minimise cr def-use delay */
      cmp_rr_ins(i_cmpl, rhs_reg, lhs_reg, creg1);
      cmp_ri_ins(i_cmp, rhs_reg, 0, creg2);

      /* maximise cr def-use delay by loading mq early for following div */
      mt_ins(i_mtmq, lhs_reg);

      /* if rhs > lhs then result is 0 */
      ld_const_ins(0, final_reg);
      bc_ins(i_bgt, creg1, endlab,LIKELY_TO_JUMP);

      /* otherwise if rhs has top bit set then result is 1 */
      ld_const_ins(1, final_reg);
      bc_ins(i_blt, creg2, endlab,LIKELY_TO_JUMP);

      /* do the extended div */
      ld_const_ins(0, R_TMP0);
      rrr_ins(i_div, R_TMP0, safe_rhs_reg, final_reg);

      set_label(endlab);
    }
  }

  return final_reg;
}


/* generate code for rem using i_divs/i_div unless simple constant */
static int do_rem(exp seq, space sp, int final_reg, bool sgned)
{
  exp lhs = seq;
  exp rhs = bro(lhs);
  exp e = bro(rhs);
  int lhs_reg;
  int rem_type=name(bro(rhs));
  int rhs_reg;
  ASSERT(last(rhs));

  lhs_reg = reg_operand(lhs, sp);

  sp = guardreg(lhs_reg, sp);

  if (final_reg == R_NO_REG)
  {
    final_reg = getreg(sp.fixed);
  }

  if (name(rhs) == val_tag && IS_POW2(no(rhs)))
  {
    long constval = no(rhs);

    if (constval>0 && IS_POW2(constval))
    {
      /* const optim, replace rem by 2**n by and with mask */

      if (constval==1)
      {
	/* result always 0 */
	ld_const_ins(0, final_reg);
      }
      else if (sgned && rem_type!=mod_tag)
      {
	/*
	 * signed, need to allow for negative lhs.
	 * Treat l%c as l-(l/c)*c
	 */

	int tmp_reg = R_TMP0;
	int shift_const = bit_no(constval);

	ASSERT(shift_const>0);			/* assumed below */

	/* do the divide, as in do_div */
	if (shift_const-1 != 0)
	{
	  rir_ins(i_sra, lhs_reg, shift_const-1, tmp_reg);
	  rir_ins(i_sr, tmp_reg, 32-shift_const, tmp_reg);
	}
	else
	{
	  rir_ins(i_sr, lhs_reg, 32-shift_const, tmp_reg);
	}
	rrr_ins(i_a, lhs_reg, tmp_reg, tmp_reg);
	rir_ins(i_sra, tmp_reg, shift_const, tmp_reg);

	/* multiply */
	rir_ins(i_sl, tmp_reg, shift_const, tmp_reg);

	/* subtract */
	rrr_ins(i_s, lhs_reg, tmp_reg, final_reg);
      }
      else
      {
	/* mod_tag and unsigned */
	rir_ins(i_and, lhs_reg, constval-1, final_reg);
      }
      return final_reg;
    }
  }
  rhs_reg = reg_operand(rhs,sp);
  if (ERROR_TREATMENT(e))
  {
    rem_error_treatment(lhs_reg,rhs_reg,e);
  }
  if (cpu == CPU_POWERPC)
  {
    if (!sgned || rem_type !=mod_tag)
    {

      rrr_ins(sgned?i_divw:i_divwu,lhs_reg,rhs_reg,R_TMP0);
      rrr_ins(i_muls,R_TMP0,rhs_reg,R_TMP0);
      rrr_ins(i_sf,R_TMP0,lhs_reg,final_reg);
    }
    else
    {
      /* signed and rem1 */
      int creg = next_creg();
      int creg2 = next_creg();
      int lab =new_label();

      /* signed div1_tag needs special care */
      rrr_ins(i_xor,lhs_reg,rhs_reg,R_TMP0);
      rir_ins(i_and,R_TMP0,0x80000000,R_TMP0);
      cmp_ri_ins(i_cmp,R_TMP0,0,creg);
      rrr_ins(i_divw,lhs_reg,rhs_reg,R_TMP0);
      rrr_ins(i_muls,rhs_reg,R_TMP0,final_reg);
      rrr_ins(i_sf,final_reg,lhs_reg,final_reg);
      bc_ins(i_beq,creg,lab,LIKELY_TO_JUMP); /* both the same sign same as div2 so jump over*/
      cmp_ri_ins(i_cmp,final_reg,0,creg2);
      bc_ins(i_beq,creg2,lab,UNLIKELY_TO_JUMP); /* 0 remainder jump over */
      rrr_ins(i_a,final_reg,rhs_reg,final_reg); /* add quotinent to answer */
      set_label(lab);
    }
  }
  else
  {
    if (sgned)
    {
      if (rem_type==mod_tag)
      {
	int creg = next_creg();
	int creg2 = next_creg();
	int lab =new_label();

	/* signed div1_tag needs special care */
	rrr_ins(i_xor,lhs_reg,rhs_reg,R_TMP0);
	rir_ins(i_and,R_TMP0,0x80000000,R_TMP0);
	cmp_ri_ins(i_cmp,R_TMP0,0,creg);
	rrr_ins(i_divs,lhs_reg,rhs_reg,R_TMP0);
	rrr_ins(i_muls,rhs_reg,R_TMP0,final_reg);
	rrr_ins(i_sf,final_reg,lhs_reg,final_reg);
	bc_ins(i_beq,creg,lab,LIKELY_TO_JUMP); /* both the same sign same as div2 so jump over*/
	cmp_ri_ins(i_cmp,final_reg,0,creg2);
	bc_ins(i_beq,creg2,lab,UNLIKELY_TO_JUMP); /* 0 remainder jump over */
	rrr_ins(i_a,final_reg,rhs_reg,final_reg); /* add quotinent to answer */
	set_label(lab);
      }
      else
      {
	rrr_ins(i_divs, lhs_reg, rhs_reg, R_TMP0);
	mf_ins(i_mfmq, final_reg);
      }
    }
    else
    {
      int safe_rhs_reg;
      int creg1 = next_creg();
      int creg2 = next_creg();
      int endlab = new_label();

      ASSERT(creg1 != creg2);

      if (final_reg != rhs_reg)
      {
	safe_rhs_reg = rhs_reg;
      }
      else
      {
	/* early setting of final_reg will clobber rhs_reg so make safe copy */
	safe_rhs_reg = getreg(sp.fixed);
	mov_rr_ins(rhs_reg, safe_rhs_reg);comment(NIL);
      }

      /* compares as early as possible to minimise cr def-use delay */
      cmp_rr_ins(i_cmpl, rhs_reg, lhs_reg, creg1);
      cmp_ri_ins(i_cmp, rhs_reg, 0, creg2);

      /* maximise cr def-use delay by loading mq early for following div */
      mt_ins(i_mtmq, lhs_reg);

      /* if rhs > lhs then result is lhs */
      mov_rr_ins(lhs_reg, final_reg);comment(NIL);
      bc_ins(i_bgt, creg1, endlab,LIKELY_TO_JUMP);

      /* otherwise if rhs has top bit set then result is lhs - rhs */
      if (lhs_reg == final_reg)
      {
	/* lhs has been clobbered, recover from MQ */
	mf_ins(i_mfmq, lhs_reg);
      }
      rrr_ins(i_s, lhs_reg, safe_rhs_reg, final_reg);
      bc_ins(i_blt, creg2, endlab,LIKELY_TO_JUMP);

      /* do the extended div */
      ld_const_ins(0, R_TMP0);
      rrr_ins(i_div, R_TMP0, safe_rhs_reg, R_TMP0);
      mf_ins(i_mfmq, final_reg);

      set_label(endlab);
    }
  }

  return final_reg;
}



/* choose regs and generate code using do_fn */
static int find_reg_and_apply
(exp e, space sp, where dest, bool sgned,	     int(*do_fn)(exp, space, int, bool))
{
  exp seq = son(e);
  ans a;
  int dest_reg;

  switch (dest.answhere.discrim)
  {
  case inreg:
    dest_reg = (*do_fn)(seq, sp, regalt(dest.answhere), sgned);
    break;

  case insomereg:
    {
      int *dr = someregalt(dest.answhere);

      *dr = (*do_fn)(seq, sp, R_NO_REG, sgned);		/* leave (*do_fn)() to allocate reg */
      return *dr;		/* no need for move */
    }

  default:
    dest_reg = (*do_fn)(seq, sp, R_NO_REG, sgned);	/* leave (*do_fn)() to allocate reg */
  }

  ASSERT(dest_reg != R_NO_REG);

  setregalt(a, dest_reg);
  sp = guardreg(dest_reg, sp);
  move(a, dest, sp.fixed, sgned);

  return dest_reg;
}



/* choose regs and generate code for multiply */
int do_mul_comm_op(exp e, space sp, where dest, bool sgned)
{
  exp arg2 = bro(son(e));

  if (name(arg2) == val_tag &&
      offset_mul_const_simple(no(arg2), sgned)!= NOT_MUL_CONST_SIMPLE)
  {
    return find_reg_and_apply(e, sp, dest, sgned, do_mul_comm_const);
  }
  else
  {
    return comm_op(e, sp, dest, i_muls);
    /* i_muls for both signed and unsigned with no error treatment */
  }
}


/* choose regs and generate code for divide */
int do_div_op(exp e, space sp, where dest, bool sgned)
{
  return find_reg_and_apply(e, sp, dest, sgned, do_div);
}


/* choose regs and generate code for rem */
int do_rem_op(exp e, space sp, where dest, bool sgned)
{
  return find_reg_and_apply(e, sp, dest, sgned, do_rem);
}


#if 0
/*
 * Needs estimation
 */


needs multneeds(exp *e, exp **at)
{
  needs n = likeplus(e, at);	/* has had comm_ass() treatment */
  exp arg1 = son(*e);
  exp arg2 = bro(arg1);

  /* remember that mult may have more than two args after optimisation */

  if (last(arg2) && name(arg2) == val_tag)
  {
    /*
     * const optim, additional reg only needed where src and dest are same reg,
     * in which case it has already been allowed for.
     */
    return n;
  }

  return n;
}


needs divneeds(exp *e, exp **at)
{
  needs n = likeminus(e, at);
  exp lhs = son(*e);
  exp rhs = bro(lhs);
  bool sgned = name(sh(*e)) & 1;

  ASSERT(last(rhs));

  if (name(rhs) ==val_tag)
  {
    long constval = no(rhs);

    if (constval>0 && IS_POW2(constval))
    {
      /* const optim, replace div by positive, non-zero, 2**n by shift right */

      return n;
    }
  }

  /* need extra reg for unsigned div */
  if (!sgned && n.fixneeds < 2)
    n.fixneeds = 2;

  return n;
}


needs remneeds(exp *e, exp **at)
{
  needs n = likeminus(e, at);
  exp lhs = son(*e);
  exp rhs = bro(lhs);
  bool sgned = name(sh(*e)) & 1;

  ASSERT(last(rhs));

  if (name(rhs) ==val_tag)
  {
    long constval = no(rhs);

    if (constval>0 && IS_POW2(constval))
    {
      /* const optim of rem by positive, non-zero, 2**n */

      return n;
    }
  }

  /* need extra reg for unsigned rem */
  if (!sgned && n.fixneeds < 2)
    n.fixneeds = 2;

  return n;
}
#endif
