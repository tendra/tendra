/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

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
$Date: 1998/02/04 15:49:07 $
$Revision: 1.2 $
$Log: regalloc.c,v $
 * Revision 1.2  1998/02/04  15:49:07  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:04:01  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


/****************************************************************
		regalloc.c

	The main procedure defined here is reg_alloc which
allocates registers and stack space for a proc exp. After the application of
weights to the body reg_alloc re-codes the number field of each ident within it.
Paralloc in paralloc.c does the corresponding work for the parameters.
	At the end of reg_alloc:-
1) props of ident contains inreg_bits or infreg_bits and number = 0
then the value will be in a t reg to be chosen in make_code
2) if props contains the reg bits then number of ident is fixpt s reg
or floatpnt s reg (divided by 2)
3) value is on the stack and:
number of ident = (word displacement in locals)*64 + R_SP

*****************************************************************/
#include "config.h"
#include "memtdf.h"
#include "codegen.h"

#include "myassert.h"
#include "maxminmacs.h"
#include "comment.h"

#include "regalloc.h"



#define ALIGNNEXT(bitposn, bitalign)	(((bitposn)+(bitalign)-1) & ~((bitalign)-1))


spacereq zerospace = {0, 0, 0, 0x0};

/*****************************************************************
	maxspace

Procedure to find the total spacereq of two spacereqs. The bit
representations of the s regs used are simply 'or'ed so that the
resulting dump fields contain all the regs of the parameters.
The largest of the two stack sizes is returned as the stack of the result.

*****************************************************************/

spacereq maxspace PROTO_N ((a,b)) PROTO_T (spacereq a X spacereq b)
{
  a.fixdump |= b.fixdump;
  a.fltdump |= b.fltdump;
  a.stack = max(a.stack, b.stack);
  a.obtain = nilexp;
  return a;
}

/* maxspace2 is used by seq tags and ident_tags since the result of these tags
   could be the result of one of the brothers */
spacereq maxspace2 PROTO_N ((a,b)) PROTO_T (spacereq a X spacereq b)
{
  a.fixdump |= b.fixdump;
  a.fltdump |= b.fltdump;
  a.stack = max(a.stack, b.stack);
  a.obtain = b.obtain;
  return a;
} 

/******************************************************************
	reg_alloc

Delivers a spacereq which gives the local stack bit requirement in the
stack field and the s regs used as bit positions in the fixdump and
fltdump fields for fixed and float regs.

******************************************************************/

spacereq regalloc PROTO_N ((e,freefixed,freefloat,stack)) PROTO_T (exp e X int freefixed X int freefloat X long stack)
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

  switch(n)
  {
   case ident_tag:
    {
      int ffix = freefixed;
      int ffloat = freefloat;
      long st = stack;
      bool caller_in_postlude = (name(s)==caller_name_tag);
      spacereq body;
      
      FULLCOMMENT4("regalloc ident_tag:	vis=%d	freefixed,freefloat,stack = %d %d %ld", isvis(e)!=0, freefixed, freefloat, stack);
      
      ASSERT(freefixed >= 0);
      ASSERT(freefloat >= 0);
      
      if (props(e) & defer_bit)
      {
	/* the tag declared is transparent to code production */
	def = zerospace;
      }
      else if (
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
	ash a;
	a = ashof(sh(s));
	
	if (name(s) == compound_tag || 
	    name(s) == nof_tag || 
	    name(s) == concatnof_tag )
	{
	  /*
	   * elements of tuples are done separately so evaluate above dec
	   * using stack space
	   * stack - bit address for current allocation
	   * st - bit address for next allocation
	   */
	  
	  ASSERT((stack&31)==0);	/* we expect stack to be word aligned */
	  
	  st = ALIGNNEXT(stack, a.ashalign);
	  st = ALIGNNEXT(st+a.ashsize, 32);	/* maintain word alignment */
	  
	  ASSERT(st-stack>=a.ashsize);
	  ASSERT((st&31)==0);
	  
	  def = regalloc (s, freefixed, freefloat, st);
	}
	else
	{
	  def = regalloc(s, freefixed, freefloat, stack);
	}
	
	FULLCOMMENT4("regalloc ident_tag:	props=%#x fixregable=%d no(e)=%d ffix=%d", props(e), fixregable(e), no(e), ffix);
	
	if ((props(e) & inreg_bits) == 0 && 
	    fixregable(e) && no(e) < ffix
	    && !caller_in_postlude)
	{
	  /* suitable for s reg, no(e) has been set up by weights */
	  props(e) |= inreg_bits;
	  no(e) = SREG_TO_REALREG(ffix);	/* will be in s reg */
	  def.fixdump |= RMASK(no(e));
	  ffix--;
	  FULLCOMMENT1("regalloc suitable for s reg:	no(e)=%ld", no(e));
	  ASSERT(ffix >= 0);
	  ASSERT(IS_SREG(no(e)));
	  ASSERT(a.ashsize <= 32);
	}
	else if ((props(e) & infreg_bits) == 0 && 
		 floatregable(e) && no(e) < ffloat
		 && !caller_in_postlude)
	{
	  /* suitable for float s reg , no(e) has been set up by weights */
	  props(e) |= infreg_bits;
	  no(e) = SFREG_TO_REALFREG(ffloat);	/* will be in s reg */
	  def.fltdump |= RMASK(no(e));
	  ffloat--;
	  FULLCOMMENT1("regalloc suitable for s freg:	no(e)=%ld", no(e));
	  ASSERT(ffloat >= 0);
	  ASSERT(IS_FLT_SREG(no(e)));
	  ASSERT(a.ashsize <= 64);
	}
	else if ((props(e) & inanyreg) == 0)
	{
	  /*
	   * not suitable for reg allocation
	   */
	  if (name(son(e)) == val_tag && !isvar(e) && !isenvoff(e))
	  {
	    /*
	     * must have been forced by const optimisation
	     * - replace uses by the value
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
	  else if (isparam(e) || caller_in_postlude)
	  {
	    /* Caller parameters and callee parameters are
	       calculated in make_ident_tag_code
	       Caller parameters identified in postludes are
	       also done in make_ident_tag_code
	       
	       It is essential that caller parameters identified
	       in postludes are not allocated into s-regs
	       */
	    no(e) = 0;
	  }
	  else
	  {
	    /*
	     * allocate on stack
	     * stack - bit address for current allocation
	     * st - bit address for next allocation
	     */
	    
	    ASSERT((stack&31)==0);	/* we expect stack to be word aligned */
	    
	    stack = ALIGNNEXT(stack, a.ashalign);
	    st = ALIGNNEXT(stack+a.ashsize, 32);	/* maintain word alignment */
	    
	    ASSERT(st-stack>=a.ashsize);
	    ASSERT((stack&31)==0);
	    
	    def.stack = max(def.stack, st);
	    no(e) = (stack<<3) + R_FP;		/* no() decoded by boff() */
	    ASSERT((stack&7)==0);			/* must be byte aligned */
	    FULLCOMMENT3("regalloc allocate on stack:	stack,st=%ld,%ld	no(e)=%ld", stack,st,no(e));
	  }
	}
	else 
	{
	  FULLCOMMENT1("regalloc no(e)==%d:/* allocation of stack like regs in make_code */", no(e));
	}
      }
      body = regalloc(bro(s), ffix, ffloat, st);

      FULLCOMMENT3("regalloc return:	ffix,ffloat,st = %d %d %ld", ffix, ffloat, st);
      return maxspace2(def, body);
    }
    
   case case_tag:
    {
      /* We do not wish to recurse down the bro(son(e)) */
      def = regalloc(s, freefixed, freefloat, stack);
      def.obtain = nilexp;/* A case returns nothing */
      return def;
    }
   case cont_tag:
    if (name(s)==name_tag &&
	name(son(s))==ident_tag &&
	isvar(son(s)) &&
	(
	(((props(son(s)) & inreg_bits)!=0) && IS_SREG(no(son(s))))  ||
	  (((props(son(s)) & infreg_bits)!=0) && IS_FLT_SREG(no(son(s))))
	 )
	)
    {
      def = zerospace;
      def.stack = stack;
      def.obtain = son(s);
      return def;
    }
    else
    {
      goto label_default;
    }
   case name_tag:
    {
      def = zerospace;
      def.stack = stack;
      
      if( name(s)==ident_tag &&
	 !isvar(s) &&
	 (
	 (((props(s) & inreg_bits)!=0) && IS_SREG(no(s))) ||
	 (((props(s) & infreg_bits)!=0) && IS_FLT_SREG(no(s)))
	  )
	 )
      {
	/* This could be the last one */
	def.obtain = s;
      }
      return def;
    }
   case env_offset_tag:
   case general_env_offset_tag:
   case caller_name_tag:
    {
      /* We do not wish to recurse down these tags */
      def = zerospace;
      def.stack = stack;
      def.obtain = nilexp;
      return def;
    }
   case seq_tag:
    {      
      def = regalloc(s, freefixed, freefloat, stack);
      s = bro(s);
      def = maxspace2(def,regalloc(s, freefixed, freefloat, stack));
      return def;	
    }
   label_default:
   default:
    {
      if(s == nilexp)
      {
	def = zerospace;
	def.stack = stack;
	def.obtain = nilexp;
	return def;
      }
      else
      {
	def = regalloc(s, freefixed, freefloat, stack);
	if (def.obtain == s)
	{
	  if (props(def.obtain)&inreg_bits !=0)
	  {
	    freefixed--;
	  }
	  else
	  {
	    freefloat--;
	  }
	}
	
	while (!last(s))
	{
	  s = bro(s);
	  def = maxspace(def, regalloc(s, freefixed, freefloat, stack));
	  if (def.obtain==s)
	  {
	    if (props(def.obtain)&inreg_bits !=0)
	    {
	      freefixed--;
	    }
	    else
	    {
	      freefloat--;
	    }
	  }
	}
	return def;	
      }
    }
  }
}
