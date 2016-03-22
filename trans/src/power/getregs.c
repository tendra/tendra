/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <main/print.h>

#include "regmacs.h"
#include "getregs.h"



/* next fixed reg to be allocated */
static int currentfix;
static long choosefix;

/* next float reg to be allocated */
static int currentfloat;
static long choosefloat;


/* reset getreg() and getfreg() back to start of sequence for proc 'tag' */
void settempregs(exp tag)
{
  UNUSED(tag);

  currentfix = R_LAST_PARAM+1;/* R_11 it must be for parameters*/
  choosefix = RMASK(currentfix);

  currentfloat = FR_1;

  choosefloat = RMASK(currentfloat);
}


/* count how many free regs there are */
int freeregs(long rmask)
{
  /* Free reg marked by 0 bit, count them */
  unsigned long bit = 1;
  int n = 0;

  while (bit != 0)
  {
    if ((rmask & bit) == 0)
      n++;
    bit <<= 1;
  }
  return n;
}


/* get a free temporary fixed pt reg */
int getreg(long fixed)
{
  /*
   * Choose reg from set 'fixed'. Chosen in a cyclic order, to give good
   * chance for peep-hole optimiser finding something useful lying around. Bit
   * set in set 'fixed' means it is unavailable, we search for 0 bit.
   */
  int reg = -1;
  long start = choosefix;

  asm_comment("getreg: from %#lx, choosefix=%#lx currentfix=%d", (unsigned long) fixed, (unsigned long) choosefix, currentfix);

  /* currentfix and choosefix are in step, one the reg number, one the mask */
  assert(choosefix == RMASK(currentfix));

  for (;;)
  {
    if ((choosefix & fixed) == 0)
      reg = currentfix;

    assert(reg != R_0);		/* R_0 not a fully functional reg, should never be in set */
    assert(!IS_R_TMP(reg));	/* +++ R_TMP currently used as ad-hoc temp in
				 * various places */

    if (currentfix == R_LAST)
    {
      /* back to start */
      currentfix = R_FIRST;
      choosefix = RMASK(R_FIRST);
    }
    else
    {
      /* next reg */
      currentfix++;
      choosefix = choosefix << 1;
    }

    if (reg != -1)
    {
      asm_comment("getreg: allocating %d", reg);
      assert(IS_TREG(reg));
      return reg;
    }

    if (choosefix == start)
    {
      error(ERR_SERIOUS, "getreg: too many regs required");
      return R_0;
    }
  }
}



/* get a free temporary floating reg */
int getfreg(long fl)
{
  /*
   * Choose reg from set 'fl'. Chosen in a cyclic order, to give good chance
   * for peep-hole optimiser finding something useful lying around. Bit set in
   * set 'float' means it is unavailable, we search for 0 bit.
   */
  int reg = -1;
  long start = choosefloat;

  asm_comment("getfreg: from %#lx, choosefloat=%#lx currentfloat=%d", fl, (unsigned long) choosefloat, currentfloat);

  /*
   * currentfloat and choosefloat are in step, one the reg number, one the
   * mask
   */
  assert(choosefloat == RMASK(currentfloat));

  for (;;)
  {
    if ((choosefloat & fl) == 0)
      reg = currentfloat;

    if (currentfloat == R_FLT_LAST)
    {
      /* back to start */
      currentfloat = R_FLT_FIRST;
      choosefloat = RMASK(R_FLT_FIRST);
    }
    else
    {
      /* next reg */
      currentfloat++;
      choosefloat = choosefloat << 1;
    }

    if (reg != -1)
    {
      asm_comment("getfreg: allocating %d", reg);
      assert(IS_FLT_TREG(reg));
      return reg;
    }

    if (choosefloat == start)
    {
      error(ERR_SERIOUS, "getfreg: too many float regs required");
      return 0;
    }
  }
}



/* return next branch unit cr reg to use */
int next_creg(void)
{
  /*
   * Cycle around cr 0,1,6,7.	+++ allocate as regs
   * cr3 & cr4 would require proc to save them.
   * cr4 & cr5 reserved for system use.
   */
  static int creg = 7;

  creg++;

  if (creg == 8)
    creg = 0;
  else if (creg == 2)
    creg = 6;

  return creg;
}
