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
 *
 * $TenDRA$
 */


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$
 *$Log$
 *Revision 1.2  2002/11/21 22:31:10  nonce
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
 *		regalloc.c
 *
 *	The main procedure defined here is reg_alloc which
 *allocates registers and stack space for a proc exp. After the application of
 *weights to the body reg_alloc re-codes the number field of each ident within it. Paralloc in paralloc.c does the corresponding work for the
 *parameters.
 *	At the end of reg_alloc:-
 *1) props of ident contains inreg_bits or infreg_bits and number = 0
 *then the value will be in a t reg to be chosen in make_code
 *2) if props contains the reg bits then number of ident is fixpt s reg
 *or floatpnt s reg (divided by 2)
 *3) value is on the stack and:
 *number of ident = (word displacement in locals)*64 + 29

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
	a.stack = max (a.stack, b.stack);
	return a;
}

static int spareparregs = 0;

/******************************************************************
 *	reg_alloc
 *
 *Delivers a spacereq which gives the local stack bit requirement in the
 *stack field and the s regs used as bit positions in the fixdump, sdump and
 *ddump fields for fixed point, single and double floats respectively.

******************************************************************/

spacereq
regalloc(exp e, int freefixed, int freefloat,
		 long stack)
{
	/* e is a proc body . freefixed and
	 *				   freefloat are the number of fixed and
	 *				   floating s regs available. These are
	 *				   initialised at the outer level but may
	 *				   be reduced by usage in paralloc */
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
									 *				   production */
			def = zerospace;
		}
		else {
			a = ashof (sh (s));
			if (name(s) != compound_tag && name(s) != nof_tag
				&& name(s) != concatnof_tag) {
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
				 *				   up by weights */
				props (e) |= inreg_bits;
				if (ffix == 9) {
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
					 *				   been set up by weights */
					props (e) |= infreg_bits;
					
					no (e) = ffloat + 9;	/* will be in s reg , note start from $f20      */
					ffloat -= 1;
					def.fltdump |= (3 << (ffloat << 1));
				}
				else
					if ((props (e) & inanyreg) == 0) {
						if (fixregable(e) && PossParReg(e) && spareparregs > 0) {
							props(e) |= inreg_bits;
							no(e) = 0;
							spareparregs--;
						}
						else
							/* not suitable for reg allocation */
							if (name (son (e)) == val_tag && !isvar (e) && !isvis(e)) {
								/* must have been forced by const- replace
								 *				   uses by the value */
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
