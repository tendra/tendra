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
 *		regalloc.c
 *
 *	The main procedure defined here is reg_alloc which
 *allocates registers and stack space for a proc exp. After the application of
 *weights to the body reg_alloc re-codes the number field of each ident within it.
 *Paralloc in paralloc.c does the corresponding work for the parameters.
 *	At the end of reg_alloc:-
 *1) props of ident contains inreg_bits or infreg_bits and number = 0
 *then the value will be in a t reg to be chosen in make_code
 *2) if props contains the reg bits then number of ident is fixpt s reg
 *or floatpnt s reg (divided by 2)
 *3) value is on the stack and:
 *number of ident = (word displacement in locals)*64 + R_SP

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
 *	maxspace
 *
 *Procedure to find the total spacereq of two spacereqs. The bit
 *representations of the s regs used are simply 'or'ed so that the
 *resulting dump fields contain all the regs of the parameters.
 *The largest of the two stack sizes is returned as the stack of the result.

*****************************************************************/

spacereq
maxspace(spacereq a, spacereq b)
{
	a.fixdump |= b.fixdump;
	a.fltdump |= b.fltdump;
	a.stack = max(a.stack, b.stack);
	a.obtain = nilexp;
	return a;
}

/* maxspace2 is used by seq tags and ident_tags since the result of these tags
 *   could be the result of one of the brothers */
spacereq
maxspace2(spacereq a, spacereq b)
{
	a.fixdump |= b.fixdump;
	a.fltdump |= b.fltdump;
	a.stack = max(a.stack, b.stack);
	a.obtain = b.obtain;
	return a;
} 

/******************************************************************
 *	reg_alloc
 *
 *Delivers a spacereq which gives the local stack bit requirement in the
 *stack field and the s regs used as bit positions in the fixdump and
 *fltdump fields for fixed and float regs.

******************************************************************/

spacereq
regalloc(exp e, int freefixed, int freefloat,
		 long stack) /* * e is a proc body. * freefixed and freefloat are the number of fixed and floating s regs * available. These are initialised at the outer level but may be reduced * by usage in paralloc. */
{
	int n = name(e);
	exp s = son(e);
	spacereq def;
	
	switch (n)
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
				name(s) == concatnof_tag)
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
					 *	       calculated in make_ident_tag_code
					 *	       Caller parameters identified in postludes are
					 *	       also done in make_ident_tag_code
					 *	       
					 *	       It is essential that caller parameters identified
					 *	       in postludes are not allocated into s-regs
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
		
		if (name(s)==ident_tag &&
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
		if (s == nilexp)
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
