/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:05 $
$Revision: 1.1.1.1 $
$Log: guard.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/12  10:59:23  currie
 * gcc pedanttry
 *
 * Revision 1.2  1995/08/16  16:06:42  currie
 * Shortened some .h names
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/****************************************************************
		 guard.c

	These routines protect registers from future use. The type
involved is space which consists of two long ints with bit patterns
taken to represent usage of temporary fixed and floating
point registers. These bits are used in the procedure
getregs which understands a clear bit to mean that the corresponding
register is free for use.
	The procedures are widely used in make_code which may use
getreg to choose a register to contain the result of an expression.
If this expression is the first operand of a binary operation (say) then the register
is guarded, producing another space which will be used by make_code for the
second operand.

******************************************************************/


#include "config.h"
#include "procrectypes.h"
#include "addrtypes.h"
#include "basicread.h"
#include "guard.h"


/*******************************************************************
The integer parameter to procedures guardreg and guardfreg
is taken to be a register which needs to be protected. For floating point
registers a factor of 2 is involved. The corresponding bit in the appropriate field of the
space i.e fixed or float, is therefore set.
********************************************************************/

space guardreg
    PROTO_N ( (r, sp) )
    PROTO_T ( int r X space sp )
{
  if ((r >= 2 && r <= 15) || (r >= 24 && r <= 25) || r==31) {
				/* r is a fixed point t reg */
    sp.fixed |= (1 << r);
  }				/* set bit in the fixed field of sp */
  return sp;
}

space guardfreg
    PROTO_N ( (r, sp) )
    PROTO_T ( int r X space sp )
{
  if (r<=9) {
				/* r is a floating point t reg */
    sp.flt |= (1 << r);
  }				/* set bit in the flt field of sp */
  return sp;
}


/********************************************************************
The procedure guard may also protect a register involved in
addressing depending on the value of the parameter of type where. This is a
union of a fixpnt reg , a float reg and an instore value. In the latter case the
register involved in the addressing can be deduced from the base field of the
instore value. These types are defined in addressingtypes.h.
*********************************************************************/

space guard
    PROTO_N ( (w, sp) )
    PROTO_T ( where w X space sp )
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
