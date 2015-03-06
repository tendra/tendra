/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Routines for choosing temporary registers. The next free register
 * is chosen cyclically from available t regs.
 *
 * The parameter is usually taken from a value of type space (which has
 * bits for fixed and floating regs).  A clear bit indicates that the
 * corresponding register is free for use.
 */

#include <assert.h>

#include <shared/check.h>
#include <shared/error.h>

#include <reader/exp.h>

#include <construct/exp.h>
#include <construct/tags.h>

#include <main/print.h>

#include "regmacs.h"
#include "proctypes.h"
#include "procrec.h"
#include "addrtypes.h"
#include "regexps.h"
#include "bitsmacs.h"
#include "getregs.h"


/* next fixed reg to be allocated */
static int currentfix = R_FIRST;
static long choosefix = RMASK(R_FIRST);

/* next float reg to be allocated */
static int currentfloat = R_FLT_FIRST;
static long choosefloat = RMASK(R_FLT_FIRST);


/* reset getreg() and getfreg() back to start of sequence for proc 'tg' */
/* (help register numbers be backward compatible). */
void
settempregs(exp tg)
{
  UNUSED(tg);

  /*ARGSUSED*/
  currentfix = GR2;
  choosefix = RMASK(currentfix);

  currentfloat = 1;
  choosefloat = RMASK(currentfloat);

}

/* get a free temporary fixed pt reg */
int
getreg(long fixed)
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

    assert(reg != GR0); 	/* hard wired to 0, shouldn't be in set */
    assert(reg != GR1);	       /* ad-hoc temporary                     */
    assert(reg != DP);        /* %dp must not be changed              */
    assert(reg != SP);       /* %sp must not be changed              */

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
       return GR0;
    }
  }

  UNREACHED;
}


int
getfreg(long fl) /* get a free temporary floating reg */
{

  /*
   * Choose reg from set 'fl'. Chosen in a cyclic order, to give good chance
   * for peep-hole optimiser finding something useful lying around. Bit set in
   * set 'float' means it is unavailable, we search for 0 bit.
   */
  int reg = -1;
  long start = choosefloat;

  asm_comment("getfreg: from %#lx, choosefloat=%#lx currentfloat=%d", fl, choosefloat, currentfloat);

  /*
   * currentfloat and choosefloat are in step, one the reg number, one the
   * mask
   */
  assert(choosefloat == RMASK(currentfloat));

  for (;;)
  {
    if (((choosefloat & fl) == 0) && IS_FLT_TREG(currentfloat))
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
      error(ERR_SERIOUS, "getfreg: too many floating point regs required");
      return 0;
    }
  }
}

