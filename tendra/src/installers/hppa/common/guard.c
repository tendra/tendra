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


/*
$Log: guard.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:11:26  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  09:31:40  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  09:31:40  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:26:36  16:26:36  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:17:16  11:17:16  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:27:04  15:27:04  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:08:43  13:08:43  wfs (William Simmonds)
 * Initial revision
 * 
*/


#define  HPPATRANS_CODE
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
If this expression is the first operand of a binary operation (say)
then the register is guarded, producing another space which will be
used by make_code for the second operand.

******************************************************************/


#include "config.h"
#include "regmacs.h"
#include "procrec.h"
#include "addrtypes.h"
#include "tempdecs.h"
#include "comment.h"
#include "guard.h"


/*******************************************************************
The integer parameter to procedures guardreg and guardfreg
is taken to be a register which needs to be protected. For floating point
registers a factor of 2 is involved. The corresponding bit in the appropriate field of the
space i.e fixed or float, is therefore set.
********************************************************************/

space guardreg 
    PROTO_N ( ( r, sp ) )
    PROTO_T ( int r X space sp )
{
  if (IS_TREG(r))
  {
    sp.fixed |= RMASK(r);
  }				/* set bit in the fixed field of sp */
  return sp;
}

space guardfreg 
    PROTO_N ( ( r, sp ) )
    PROTO_T ( int r X space sp )
{
  if (IS_FLT_TREG(r))		/* r is a floating point t reg */
  {
    sp.flt |= RMASK(r);
  }				/* set bit in the flt field of sp */
  return sp;
}


/*
 * needreg & needfreg are like guardreg & guardfreg,
 * except it is an error if the reg is alread in use.
 * Used, eg, when claiming regs that will be damaged, as in a call.
 */

space needreg 
    PROTO_N ( ( r, sp ) )
    PROTO_T ( int r X space sp )
{
  /* tempdec() can allocate t regs if dead over calls, so dont fail */
#if 0 /* !!!! */
  if (!(tempdecopt && IS_TREG(r)) && (sp.fixed & RMASK(r)) != 0)
  {
    comment1("needreg: %d", r);
    fail("needreg: fixed reg already in use");
  }
#endif
  return guardreg(r, sp);
}

space needfreg 
    PROTO_N ( ( r, sp ) )
    PROTO_T ( int r X space sp )
{
#if 0 /* !!!! */
  /* tempdec() can allocate t regs if dead over calls, so dont fail */
  if (!(tempdecopt && IS_FLT_TREG(r)) && (sp.flt & RMASK(r)) != 0)
  {
    comment1("needfreg: %d", r);
    fail("needfreg: float reg already in use");
  }
#endif
  return guardreg(r, sp);
}


/********************************************************************
The procedure guard may also protect a register involved in
addressing depending on the value of the parameter of type where. This is a
union of a fixpnt reg , a float reg and an instore value. In the latter case the
register involved in the addressing can be deduced from the base field of the
instore value. These types are defined in addrtypes.h.
*********************************************************************/

space guard 
    PROTO_N ( ( w, sp ) )
    PROTO_T ( where w X space sp )
{
  switch (discrim ( w.answhere ) )
  {
    case inreg:
    {
      int r = regalt(w.answhere);

      if (IS_TREG(r))
      {
	sp.fixed |= RMASK(r);
      }				/* guard reg */
      return sp;
    }
  case infreg:
    {
      int r = fregalt(w.answhere).fr;

      if (IS_FLT_TREG(r))
      {
	sp.flt |= RMASK(r);
      }				/* guard freg */
      return sp;
    }
#if USE_BITAD
  case bitad:
#endif
  case notinreg:
    {
      int r = insalt(w.answhere).b.base;

      if (IS_TREG(r))
      {
	sp.fixed |= RMASK(r);
      }
      /* guard fixed point t reg used as base of address */
      return sp;
    }
  case insomereg:
  case insomefreg:
    {
      comment1("guard: BAD discrim %d", discrim ( w.answhere ) );
      fail("guard: Guard ? reg");
      return sp;
    }
  default:
    {
      comment1("guard: BAD discrim %d", discrim ( w.answhere ) );
      fail("guard: not in switch");
      return sp;
    }
  }
}



