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
$Log: regalloc.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:12:27  wfs
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
 * Revision 3.4  1995/08/25  10:27:07  wfs
 * Fairly major revision - register allocation is more like the "mips"
 * and more suited to the hppa. Register synonyms changed.
 *
 * Revision 3.4  1995/08/25  10:27:07  wfs
 * Fairly major revision - register allocation is more like the "mips"
 * and more suited to the hppa. Register synonyms changed.
 *
 * Revision 3.1  95/04/10  16:27:59  16:27:59  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:18:50  11:18:50  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:28:40  15:28:40  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:15:26  13:15:26  wfs (William Simmonds)
 * Initial revision
 * 
*/


#define HPPATRANS_CODE
/****************************************************************
		regalloc.c

	The main procedure defined here is reg_alloc which
allocates registers and stack space for a proc exp. After the application of
weights to the body reg_alloc re-codes the number field of each ident within it.
	At the end of reg_alloc:-
1) props of ident contains inreg_bits or infreg_bits and number = 0
then the value will be in a t reg to be chosen in make_code
2) if props contains the reg bits then number of ident is fixpt s reg
or floatpnt s reg (divided by 2)
3) value is on the stack and:
number of ident = (word displacement in locals)*64 + GR17

*****************************************************************/



#include "config.h"
#include "expmacs.h"
#include "tags.h"
#include "proctypes.h"
#include "procrec.h"
#include "bitsmacs.h"
#include "maxminmacs.h"
#include "regable.h"
#include "regmacs.h"
#include "comment.h"
#include "myassert.h"
#include "frames.h"
#include "regalloc.h"

/* map fixreg s number 16,..,1 onto real callee-saves registers GR3,...,GR18 */
#define SREG_TO_REALREG(n) real_reg[16-(n)];

int real_reg[16] =
{ GR3,
  0,
  0,
  GR6,
  GR7,
  GR8,
  GR9,
  GR10,
  GR11,
  GR12,
  GR13,
  GR14,
  GR15,
  GR16,
  GR17,
  GR18 };



#define ALIGNNEXT(bitposn, bitalign)	(((bitposn)+(bitalign)-1) & ~((bitalign)-1))

spacereq zerospace = {0, 0, 0};

/*****************************************************************
	maxspace

Procedure to find the total spacereq of two spacereqs. The bit
representations of the s regs used are simply 'or'ed so that the
resulting dump fields contain all the regs of the parameters.
The largest of the two stack sizes is returned as the stack of the result.

*****************************************************************/

spacereq maxspace 
    PROTO_N ( ( a, b ) )
    PROTO_T ( spacereq a X spacereq b )
{
  a.fixdump |= b.fixdump;
  a.fltdump |= b.fltdump;
  a.stack = MAX_OF(a.stack, b.stack);
  return a;
}


/******************************************************************
	reg_alloc

Delivers a spacereq which gives the local stack bit requirement in the
stack field and the s regs used as bit positions in the fixdump, sdump and
ddump fields for fixed point, single and double floats respectively.

******************************************************************/

spacereq regalloc 
    PROTO_N ( ( e, freefixed, freefloat, stack ) )
    PROTO_T ( exp e X int freefixed X int freefloat X long stack )
/*
 * e is a proc body.
 * freefixed and freefloat are the number of fixed and floating s regs
 * available. These are initialised at the outer level but may be reduced
 * by usage in paralloc.
 */
{
  int n = name(e);
  exp s = son(e);
  spacereq def;
  if (n == ident_tag)
  {
    int ffix = freefixed;
    int ffloat = freefloat;
    long st = stack;
    spacereq body;
    ash a;

    FULLCOMMENT4("regalloc ident_tag(%d):	freefixed,freefloat,stack = %d %d %ld",
		 EXP_NUM(e), freefixed, freefloat, stack);

    assert(freefixed >= 0);
    assert(freefloat >= 0);

    if (props(e) & defer_bit)
    {
      /* the tag declared is transparent to code production */
      def = zerospace;
    }
    else
    if (
	  !isvar(e) && !isparam(e)
	  && name(s) == name_tag
	  && !isvar(son(s))
	  && !isvis(son(s))
	  && !isparam(son(s))
	  && (props(son(s)) & inreg_bits)
       )
    {
      /*
       * dont take space for this constant dec,
       * initialiser is another simple constant ident
       * (eg from double nested loop optimisation)
       */
      props(e) |= defer_bit;
      def = zerospace;
    }
    else
    {
      a = ashof(sh(s));

      if (name(s) == compound_tag || name(s) == nof_tag || name(s) == concatnof_tag )
      {
	/*
	 * elements of tuples are done separately so evaluate above dec
	 * using stack space
	 * stack - bit address for current allocation
	 * st - bit address for next allocation
	 */

	assert((stack&31)==0);	/* we expect stack to be word aligned */

	st = ALIGNNEXT(stack, a.ashalign);
	st = ALIGNNEXT(st+a.ashsize, 32);	/* maintain word alignment */

	assert(st-stack>=a.ashsize);
	assert((st&31)==0);

	def = regalloc (s, freefixed, freefloat, st);
      }
      else
      {
	def = regalloc(s, freefixed, freefloat, stack);
      }

      FULLCOMMENT4("regalloc ident_tag:	props=%#x,fixregable=%d,no(e)=%d,ffix=%d",
		   props(e), fixregable(e), no(e), ffix);


      if ((props(e) & inreg_bits) == 0 && fixregable(e) && no(e) < ffix)
      {
	/* suitable for s reg, no(e) has been set up by weights */
	props(e) |= inreg_bits;
	no(e) = SREG_TO_REALREG(ffix);	/* will be an s reg */
	ffix -= 1;
	def.fixdump |= RMASK(no(e));
	FULLCOMMENT1("regalloc suitable for reg no %ld", no(e));
	assert(ffix >= 0);
	assert(IS_SREG(no(e)));
	assert(a.ashsize <= 32);
      }
      else if ((props(e) & infreg_bits) == 0 && floatregable(e) && no(e) < ffloat)
      {
	/* suitable for float s reg , no(e) has been set up by weights */
	fail("regalloc: no float point s regs acknowledged");
      }
      else if ((props(e) & inanyreg) == 0)
      {

	/*
	 * not suitable for reg allocation
	 */
	if (name(son(e)) == val_tag && !isvar(e) && !isenvoff(e))
	{

	  /*
	   * must have been forced by const optimisation - replace uses by the
	   * value
	   */
	  exp t = pt(e);

	  for (; t != nilexp;)
	  {
	    exp p = pt(t);

	    setname(t, val_tag);
	    son(t) = nilexp;
	    no(t) = no(son(e));
	    props(t) = 0;
	    pt(t) = nilexp;
	    t = p;
	  }
	  pt(e) = nilexp;

	  FULLCOMMENT("regalloc heavily used const: no spare regs - replace use by value");
	  props(e) |= defer_bit;
	  def = zerospace;
	}
	else if (name(son(e)) == name_tag && !isvar(e) && !isenvoff(e))
	{
	  /* must have been forced  - defer it */
	  FULLCOMMENT("regalloc heavily used address: no spare regs - replace use by value");
	  props(e) |= defer_bit;
	  def = zerospace;
	}
	else if (isparam(e))
	{
	  /* don't know framesize yet; displacement in no(son(e)) */
	  no(e) = 0;		/* set correctly in make_code ident_tag */
	}
	else
	{

	  /*
	   * allocate on stack stack - bit address for current allocation st -
	   * bit address for next allocation
	   */

	  assert((stack & 31) == 0);	/* we expect stack to be word aligned */

	  stack = ALIGNNEXT(stack, a.ashalign);
	  st = ALIGNNEXT(stack + a.ashsize, 32);	/* maintain word
							 * alignment */

	  assert(st - stack >= a.ashsize);
	  assert((stack & 31) == 0);

	  def.stack = MAX_OF(def.stack, st);
	  no(e) = stack * 2 + GR17;
	  FULLCOMMENT3("regalloc allocate on stack:	stack,st=%ld,%ld	no(e)=%ld", stack, st, no(e));
	}
      }
      else if (no(e) == R_USE_RES_REG)
      {

	/*
	 * optimisation: use result reg for ident_tag to avoid reg move
	 */
	assert (!isenvoff(e));
	FULLCOMMENT2("regalloc no(e)==R_USE_RES_REG:	no(e)=%ld, inreg_bits=%d", no(e), (props(e) & inreg_bits) != 0);
	no(e) = ((props(e) & inreg_bits) != 0) ? RET0 : R_DEFER_FR4;
	/* set up result of proc as declared id ( R_DEFER_FR4 = %fr4 later) */
      }
      else
      {
	/* allocation of stack like regs in make_code */
	assert (!isenvoff(e));
	FULLCOMMENT1("regalloc no(e)==%d: allocation of stack like regs in make_code", no(e));
      }
    }
    body = regalloc(bro(s), ffix, ffloat, st);
    FULLCOMMENT3("regalloc return:	ffix,ffloat,st = %d %d %ld", ffix, ffloat, st);
    return maxspace(body, def);
  }
  else if (n == case_tag)
  {
    /* recurse on all expressions in tree */
    return regalloc(s, freefixed, freefloat, stack);
  }
  else
  if (n != name_tag && n != env_offset_tag && n!=general_env_offset_tag                            && s != nilexp)
  {
    /* recurse on all expressions in tree */
    def = regalloc(s, freefixed, freefloat, stack);
    while (!last(s))
    {
      s = bro(s);
      def = maxspace(def, regalloc(s, freefixed, freefloat, stack));
    }
    return def;
  }
  else
  {
    def = zerospace;
    def.stack = stack;
    return def;
  }
}






