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
$Date: 1998/01/17 15:56:06 $
$Revision: 1.1.1.1 $
$Log: regalloc.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/09/22  15:49:18  currie
 * added outpar
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/****************************************************************
		regalloc.c

	The main procedure defined here is reg_alloc which
allocates registers and stack space for a proc exp. After the application of
weights to the body reg_alloc re-codes the number field of each ident within it. Paralloc in paralloc.c does the corresponding work for the
parameters.
	At the end of reg_alloc:-
1) props of ident contains inreg_bits or infreg_bits and number = 0
then the value will be in a t reg to be chosen in make_code
2) if props contains the reg bits then number of ident is fixpt s reg
or floatpnt s reg (divided by 2)
3) value is on the stack and:
number of ident = (word displacement in locals)*64 + 29

*****************************************************************/



#include "config.h"
#include "expmacs.h"
#include "tags.h"
#include "procrectypes.h"
#include "bitsmacs.h"
#include "maxminmacs.h"
#include "regable.h"
#include "regmacs.h"
#include "common_types.h"
#include "frames.h"
#include "flags.h"
#include "regalloc.h"

spacereq zerospace = {
  0, 0, 0
};

/*****************************************************************
	maxspace

Procedure to find the total spacereq of two spacereqs. The bit
representations of the s regs used are simply 'or'ed so that the
resulting dump fields contain all the regs of the parameters.
The largest of the two stack sizes is returned as the stack of the result.

*****************************************************************/

spacereq maxspace
    PROTO_N ( (a,b) )
    PROTO_T ( spacereq a X spacereq b )
{
  a.fixdump |= b.fixdump;
  a.fltdump |= b.fltdump;
  a.stack = max (a.stack, b.stack);
  return a;
}

static int spareparregs = 0;

/******************************************************************
	reg_alloc

Delivers a spacereq which gives the local stack bit requirement in the
stack field and the s regs used as bit positions in the fixdump, sdump and
ddump fields for fixed point, single and double floats respectively.

******************************************************************/

spacereq regalloc
    PROTO_N ( ( e, freefixed, freefloat, stack) )
    PROTO_T ( exp e X int freefixed X int freefloat X long stack )
{
				/* e is a proc body . freefixed and
				   freefloat are the number of fixed and
				   floating s regs available. These are
				   initialised at the outer level but may
				   be reduced by usage in paralloc */
  int   n = name (e);
  exp s = son (e);
  spacereq def;

  if (n == ident_tag) {
    int   ffix = freefixed;
    int   ffloat = freefloat;
    long  st = stack;
    int old_spareparregs = spareparregs;

    spacereq body;
    ash a;
    if (props (e) & defer_bit) {/* the tag declared is transparent to code
				   production */
      def = zerospace;
    }
    else {
      a = ashof (sh (s));
      if (name(s) != compound_tag && name(s) != nof_tag
         	&& name(s) != concatnof_tag ) {
      	def = regalloc (s, freefixed, freefloat, stack);
      }
      else  { /* elements of tuples are done separately so evaluate above dec */
          if (a.ashalign <= 32 || (stack & 0x20) == 0) {
              st = stack + ((a.ashsize + 31) & ~31);
          }
          else {
              st = stack + 32 + ((a.ashsize + 31) & ~31);
          }
         def = regalloc (s, freefixed, freefloat, st);
      }
      if ((props (e) & inreg_bits) == 0 && fixregable (e) && no (e) < ffix) {
				/* suitable for s reg , no(e) has been set
				   up by weights */
	props (e) |= inreg_bits;
        if( ffix == 9) {
		no(e)=30;
		def.fixdump |= (1 << 14);
        }
        else {
		no (e) = ffix + 15;	/* will be in s reg , note s0 = $16 */
		def.fixdump |= (1 << (ffix-1));
        }
	ffix -= 1;

      }
      else
	if ((props (e) & infreg_bits) == 0
	    && floatregable (e) && no (e) < ffloat) {
				/* suitable for float s reg , no(e) has
				   been set up by weights */
	  props (e) |= infreg_bits;

	  no (e) = ffloat + 9;	/* will be in s reg , note start from $f20      */
	  ffloat -= 1;
	  def.fltdump |= (3 << (ffloat << 1));
	}
	else
	  if ((props (e) & inanyreg) == 0) {
	    if( fixregable(e) && PossParReg(e) && spareparregs > 0) {
		props(e) |= inreg_bits;
		no(e) = 0;
		spareparregs--;
	    }
	    else
				/* not suitable for reg allocation */
	    if (name (son (e)) == val_tag && !isvar (e) && !isvis(e)) {
				/* must have been forced by const- replace
				   uses by the value */
	      exp t = pt (e);
	      for (; t != nilexp;) {
		exp p = pt (t);
		setname (t, val_tag);
		son (t) = nilexp;
		no (t) = no (son (e));
		props (t) = 0;
		pt (t) = nilexp;
		t = p;
	      }
	      pt (e) = nilexp;
	      props (e) |= defer_bit;
	      def = zerospace;
	    }
	    else
	      if (name (son (e)) == name_tag && !isvar (e) && !isvis(e)) {
				/* must have been forced  - defer it */
		props (e) |= defer_bit;
		def = zerospace;
	      }
	      else
	      if (isparam(e)) {
		if (props(son(e)) != 0)  {
			spareparregs++;  /* can use this reg in PossParReg */
		}
	      	no(e) = 0;
	      	/* don't know framesize yet; displacement in no(son(e)) */

	      }
	      else {		/* allocate on stack */
		int basereg = (Has_vcallees)?local_reg:((Has_fp)?30:29);
		if (a.ashalign <= 32 || (stack & 0x20) == 0) {
		  st = stack + ((a.ashsize + 31) & ~31);
		}
		else {
		  stack += 32;
		  st = stack + ((a.ashsize + 31) & ~31);
		}
		def.stack = max (def.stack, st);
		no (e) = stack * 2 + basereg;
	      }
	  }
	  else
	    if (no (e) == 101) {
	      no (e) = ((props (e) & inreg_bits) != 0) ? 2 : 16;
	      /* set up result of proc as declared id ($f16 = $f0 later)
	      */
	    }
      /* else  allocation of stack like regs in make_code */
    }
    body = regalloc (bro (s), ffix, ffloat, st);
    spareparregs = old_spareparregs;
    return maxspace (body, def);
  }
  else				/* recurse on all expressions in tree */
    if (n == case_tag) {
      return regalloc (s, freefixed, freefloat, stack);
    }
    else
      if (n != name_tag && n!= env_offset_tag
	    && n!= general_env_offset_tag && s != nilexp) {
	def = regalloc (s, freefixed, freefloat, stack);
	while (!last (s)) {
	  s = bro (s);
	  def = maxspace (def, regalloc (s, freefixed, freefloat, stack));
	}
	return def;
      }
      else {
      	def = zerospace;
      	def.stack = stack;
	return def;
      }
}
