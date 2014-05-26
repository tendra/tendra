/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * These routines protect registers from future use. The type involved
 * is space which consists of two long ints with bit patterns taken to
 * represent usage of temporary fixed and floating point registers.
 * These bits are used in the procedure getregs which understands a
 * clear bit to mean that the corresponding register is free for use.
 *
 * The procedures are widely used in make_code which may use getreg to
 * choose a register to contain the result of an expression.
 *
 * If this expression is the first operand of a binary operation (say)
 * then the register is guarded, producing another space which will be
 * used by make_code for the second operand.
 */

#include <reader/basicread.h>

#include "procrectypes.h"
#include "addrtypes.h"
#include "guard.h"

/*
 * The integer parameter to procedures guardreg and guardfreg is taken to be
 * a register which needs to be protected. For floating point registers a
 * factor of 2 is involved. The corresponding bit in the appropriate field of the
 * space i.e fixed or float, is therefore set.
 */
space
guardreg(int r, space sp)
{
  if ((r >= 2 && r <= 15) || (r >= 24 && r <= 25) || r==31) {
				/* r is a fixed point t reg */
    sp.fixed |= (1 << r);
  }				/* set bit in the fixed field of sp */
  return sp;
}

space
guardfreg(int r, space sp)
{
  if (r<=9) {
				/* r is a floating point t reg */
    sp.flt |= (1 << r);
  }				/* set bit in the flt field of sp */
  return sp;
}

/*
 * The procedure guard may also protect a register involved in addressing
 * depending on the value of the parameter of type where. This is a union
 * of a fixpnt reg , a float reg and an instore value. In the latter case the
 * register involved in the addressing can be deduced from the base field of the
 * instore value. These types are defined in addressingtypes.h.
 */
space
guard(where w, space sp)
{
  switch (w.answhere.discrim) {
    case inreg:
      {
	int   r = regalt (w.answhere);
	if ((r >= 2 && r <= 15) || (r >= 24 && r <= 25) || r==31) {
	  sp.fixed |= (1 << r);
	}			/* guard reg */
	return sp;
      }
    case infreg:
      {
	int   r = fregalt (w.answhere).fr;
	if (r<=9) {
	  sp.flt |= (1 << r);
	}			/* guard freg */
	return sp;
      }
    case notinreg:
      {
	int   r = insalt (w.answhere).b.base;
	if ((r >= 2 && r <= 15) || (r >= 24 && r <= 25) || r==31) {
	  sp.fixed |= (1 << r);
	}
	/* guard fixed point t reg used as base of address */
	return sp;
      }
    default: {
	failer ("Guard ? reg ");
      }
  }
  return sp;
}
