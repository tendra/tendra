/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    Copyright (c) 1993 Open Software Foundation, Inc.
 *
 *
 *    All Rights Reserved
 *
 *
 *    Permission to use, copy, modify, and distribute this software
 *    and its documentation for any purpose and without fee is hereby
 *    granted, provided that the above copyright notice appears in all
 *    copies and that both the copyright notice and this permission
 *    notice appear in supporting documentation.
 *
 *
 *    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
 *    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *    PARTICULAR PURPOSE.
 *
 *
 *    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
 *    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 *    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
 *    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 *    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $TenDRA$
 */

/*
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 */



/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$
 *$Log$
 *Revision 1.2  2002/11/21 22:31:12  nonce
 *Remove ossg prototypes.  This commit is largely whitespace changes,
 *but is nonetheless important.  Here's why.
 *
 *I.  Background
 *=========================
 *
 *    The current TenDRA-4.1.2 source tree uses "ossg" prototype
 *conventions, based on the Open Systems Software Group publication "C
 *Coding Standards", DRA/CIS(SE2)/WI/94/57/2.0 (OSSG internal document).
 *The goal behind ossg prototypes remains admirable: TenDRA should
 *support platforms that lack ANSI compliant compilers.  The explicit
 *nature of ossg's prototypes makes macro substition easy.
 *
 *    Here's an example of one function:
 *
 *    static void uop
 *	PROTO_N ( ( op, sha, a, dest, stack ) )
 *	PROTO_T ( void ( *op ) PROTO_S ( ( shape, where, where ) ) X
 *		  shape sha X exp a X where dest X ash stack )
 *    {
 *
 *tendra/src/installers/680x0/common/codec.c
 *
 *  The reasons for removing ossg are several, including:
 *
 *  0) Variables called 'X' present a problem (besides being a poor
 *variable name).
 *
 *  1) Few platforms lack ANSI-compliant compilers.  ISO-compliant
 *prototypes are easily handled by most every compiler these days.
 *
 *  2) Although TenDRA emphasizes portability, standards compliance is
 *the primary goal of the current project.  We should expect no less
 *from the compiler source code.
 *
 *  3) The benefits of complex prototypes are few, given parameter
 *promotion rules.  (Additionally, packing more types into int-sized
 *spaces tends to diminish type safety, and greatly complicates
 *debugging and testing.)
 *
 *  4) It would prove impractical to use an OSSG internal style document
 *in an open source project.
 *
 *  5) Quite frankly, ossg prototypes are difficult to read, but that's
 *certainly a matter of taste and conditioning.
 *
 *II.  Changes
 *=========================
 *
 *   This commit touches most every .h and .c file in the tendra source
 *tree.  An emacs lisp script (http://www.tendra.org/~nonce/tendra/rmossg.el)
 *was used to automate the following changes:
 *
 *   A.  Prototype Conversions.
 *   --------------------------------------------------
 *
 *   The PROTO_S, PROTO_Z, PROTO_N, PROTO_T, and PROTO_V macros were
 *rewritten to ISO-compliant form.  Not every file was touched.  The
 *files named ossg.h, ossg_api.h, code.c, coder.c and ossg_std.h were
 *left for hand editing.  These files provide header generation, or have
 *non-ossg compliant headers to start with.  Scripting around these
 *would take too much time; a separate hand edit will fix them.
 *
 *   B.  Statement Spacing
 *   --------------------------------------------------
 *
 *   Most of the code in the TenDRA-4.1.2 used extra spaces to separate
 *parenthetical lexemes.  (See the quoted example above.)  A simple
 *text substitution was made for:
 *
 *     Before            After
 *===================================
 *
 *   if ( x )            if (x)
 *   if(x)               if (x)
 *   x = 5 ;             x = 5;
 *   ... x) )            ... x))
 *
 *All of these changes are suggested by style(9).  Additional, statement
 *spacing considerations were made for all of the style(9) keywords:
 *"if" "while" "for" "return" "switch".
 *
 *A few files seem to have too few spaces around operators, e.g.:
 *
 *      arg1*arg2
 *
 *instead of
 *
 *      arg1 * arg2
 *
 *These were left for hand edits and later commits, since few files
 *needed these changes.  (At present, the rmossg.el script takes 1 hour
 *to run on a 2GHz P4, using a ramdisk.  Screening for the 1% that
 *needed change would take too much time.)
 *
 *   C.  License Information
 *   --------------------------------------------------
 *
 *After useful discussion on IRC, the following license changes were
 *made:
 *
 *   1) Absent support for $License::BSD$ in the repository, license
 *and copyright information was added to each file.
 *
 *   2) Each file begins with:
 *
 *   Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 *   All rights reserved.
 *
 *   Usually, copyright stays with the author of the code; however, I
 *feel very strongly that this is a group effort, and so the tendra
 *project should claim any new (c) interest.
 *
 *   3) The comment field then shows the bsd license and warranty
 *
 *   4) The comment field then shows the Crown Copyright, since our
 *changes are not yet extensive enough to claim any different.
 *
 *   5) The comment field then closes with the $TenDRA$ tag.
 *
 *   D.  Comment Formatting
 *   --------------------------------------------------
 *
 *The TenDRA-4.1.2 code base tended to use comment in this form:
 *
 *    /*
 *       Statement statement
 *       statement
 *     */
 *
 *while style(9) suggests:
 *
 *    /*
 *     * Statement statement
 *     * statement
 *     */
 *
 *Not every comment in -4.1.2 needed changing.  A parser was written to
 *identify non-compliant comments.  Note that a few comments do not
 *follow either the TenDRA-4.1.2 style or style(9), or any style I can
 *recognize.  These need hand fixing.
 *
 *   E.  Indentation
 *   --------------------------------------------------
 *
 *   A elisp tendra-c-mode was created to define how code should be
 *indented.  The structure follows style(9) in the following regards:
 *
 *  (c-set-offset 'substatement-open 0)
 *  (setq c-indent-tabs-mode t
 *	c-indent-level 4
 *	c-argdecl-indent t
 *	c-tab-always-indent t
 *	backward-delete-function nil
 *	c-basic-offset 4
 *	tab-width 4))
 *
 *This means that substatement opening are not indented.  E.g.:
 *
 *   if (condition)
 *   {
 *
 *instead of
 *
 *   if (condition)
 *     {
 *
 *or even
 *
 *   if (condition) {
 *
 *Each statement is indented by a tab instead of a spaces.  Set your tab
 *stop to comply with style(9); see the vim resources in the tendra
 *tree.  I'll add the emacs mode support shortly.
 *
 *No doubt, a function or two escaped change because of unusual
 *circumstances.  These must be hand fixed as well.
 *
 *III.  Things Not Changed
 *=========================
 *
 *    A large number of style(9) deficiencies remain.  These will
 *require a separate effort.  I decided to stop with the changes noted
 *above because:
 *
 *   0)  The script currently takes hours to run to completion even on
 *high-end consumer machines.
 *
 *   1)  We need to move on and fix other substantive problems.
 *
 *   2) The goal of this commit was *just* ossg removal; I took the
 *opportunity to get other major white-space issues out of the way.
 *
 *    I'll also note that despite this commit, a few ossg issues remain.
 *These include:
 *
 *   0) The ossg headers remain.  They contain useful flags needed by
 *other operations.  Additionally, the BUILD_ERRORS perl script still
 *generates ossg-compliant headers.  (This is being removed as we change
 *the build process.)
 *
 *   1) A few patches of code check for ossg flags: "if (ossg) etc."
 *These can be hand removed as well.
 *
 *   2) No doubt, a few ossg headers escaped the elisp script.  We can
 *address these seriatim.
 *
 *IV.  Testing
 *=========================
 *
 *    Without a complete build or test suite, it's difficult to
 *determine if these changes have introduced any bugs.  I've identified
 *several situations where removal of ossg caused bugs in sid and
 *calculus operations.  The elisp script avoids these situations; we
 *will hand edit a few files.
 *
 *    As is, the changes should behave properly; the source base builds
 *the same before and after the rmossg.el script is run.  Nonetheless,
 *please note that this commit changes over 23,000 PROTO declarations,
 *and countless line changes.  I'll work closely with any developers
 *affected by this change.
 *
 * Revision 1.2  1998/02/04  15:49:00  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:02:52  pwe
 * add banners and mod for PWE ownership
 *
 **********************************************************************/


#include "config.h"
#include "memtdf.h"
#include "codegen.h"
#include "geninst.h"

#include "myassert.h"
#include "needscan.h"
#include "comment.h"

#include "muldvrem.h"
#include "translat.h"
#include "error.h"
#define BITS_PER_WORD		32

#define MAX_MUL_POW2_OFFSET	2	/* max permissable X in 2**n +- X for
								 * constant multiply */

#define NOT_MUL_CONST_SIMPLE	(MAX_MUL_POW2_OFFSET+1)
/* any constant larger than permissable X offset in 2**n +- X */

#define IS_POW2(c)		((c) != 0 && ((c) & ((c)-1)) == 0)




/*
 * Utility functions.
 */

/* return bit number 0..31 from right of word of 'c' which has one bit set */
static int
bit_no(unsigned long c)
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
static int
offset_mul_const_simple(long constval, bool sgned)
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
static void
mul_const_simple(int src, long constval, int dest,
				 bool sgned)
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
static int
do_mul_comm_const(exp seq, space sp, int final_reg,
				  bool sgned)
{
	exp arg2 = bro(seq);
	int lhs_reg = reg_operand(seq, sp);
	
	ASSERT(name(arg2) == val_tag && offset_mul_const_simple(no(arg2), sgned) != NOT_MUL_CONST_SIMPLE);
	
	
	sp = guardreg(lhs_reg, sp);
	
	ASSERT(last(arg2));			/* check() & scan() should move const to last */
	
	if (final_reg == R_NO_REG)
		final_reg = getreg(sp.fixed);	/* better code from mul_const if src != dest reg */
	
	mul_const_simple(lhs_reg, no(arg2), final_reg, sgned);
	
	return final_reg;
}


/* generate code for divide using i_divs/i_div unless simple constant */
static int
do_div(exp seq, space sp, int final_reg, bool sgned)
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
	
	if (architecture==POWERPC_CODE)
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
static int
do_rem(exp seq, space sp, int final_reg, bool sgned)
{
	exp lhs = seq;
	exp rhs = bro(lhs);
	exp e = bro(rhs);
	int lhs_reg;
	int rem_type=name(bro(rhs));
	int rhs_reg ;  
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
	if (architecture==POWERPC_CODE)
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
static int
find_reg_and_apply(exp e, space sp, where dest,
				   bool sgned, int (*do_fn)(exp, space, int, bool))
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
int
do_mul_comm_op(exp e, space sp, where dest,
			   bool sgned)
{
	exp arg2 = bro(son(e));
	
	if (name(arg2) == val_tag &&
		offset_mul_const_simple(no(arg2), sgned) != NOT_MUL_CONST_SIMPLE)
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
int
do_div_op(exp e, space sp, where dest, bool sgned)
{
	return find_reg_and_apply(e, sp, dest, sgned, do_div);
}


/* choose regs and generate code for rem */
int
do_rem_op(exp e, space sp, where dest, bool sgned)
{
	return find_reg_and_apply(e, sp, dest, sgned, do_rem);
}


#if 0
/*
 * Needs estimation
 */


needs
multneeds(exp *e, exp **at)
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


needs
divneeds(exp *e, exp **at)
{
	needs n = likeminus(e, at);
	exp lhs = son(*e);
	exp rhs = bro(lhs);
	bool sgned = name(sh(*e)) & 1;
	
	ASSERT(last(rhs));
	
	if (name(rhs)==val_tag)
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


needs
remneeds(exp *e, exp **at)
{
	needs n = likeminus(e, at);
	exp lhs = son(*e);
	exp rhs = bro(lhs);
	bool sgned = name(sh(*e)) & 1;
	
	ASSERT(last(rhs));
	
	if (name(rhs)==val_tag)
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
