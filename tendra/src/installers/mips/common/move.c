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
 *Revision 1.2  2002/11/21 22:31:09  nonce
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
 * Revision 1.3  1995/09/12  10:59:35  currie
 * gcc pedanttry
 *
 * Revision 1.2  1995/08/16  16:06:55  currie
 * Shortened some .h names
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
 ***********************************************************************/
/**********************************************************************
 *		move.c
 *
 *	The procedure move produces code to move a value from a to the
 *destination dest. This takes the form of a switch test on the parameter a (type
 *ans) which is either a reg, freg or instore value. In each of the three cases the
 *ans field of the dest is similarly dealt with to determine the necessary
 *instructions for the move. Sizes and alignment are taken from the ash field of
 *the destination.
 *Delivers register used if 1-word destination is instore; otherwise NOREG.

**********************************************************************/

#include "config.h"
#include "mips_ins.h"
#include "inst_fmt.h"
#include "addrtypes.h"
#include "procrectypes.h"
#include "getregs.h"
#include "labels.h"
#include "psu_ops.h"
#include "bitsmacs.h"
#include "common_types.h"
#include "main.h"
#include "guard.h"
#include "maxminmacs.h"
#include "basicread.h"
#include "move.h"


int
move(ans a, where dest, space freeregs, bool sgned)
{
	long regs = freeregs.fixed;
	long fregs = freeregs.flt;
	int   al = dest.ashwhere.ashalign;
	int size = dest.ashwhere.ashsize;
	
	if (size==0) return NOREG;
	
  start:
	switch (a.discrim) {
    case insomereg:
    case insomefreg: {
		failer ("Source reg not specified");
	}
		
    case inreg:
/***************** source in fixed point register ********************/
	{
		int   r = regalt (a);
		switch (dest.answhere.discrim) {
		case inreg:
			/* ******* source and dest in fixed register ************ */
	    {
			int   rd = regalt (dest.answhere);
			if (rd != 0 /* nowhere */ && rd != r) {
				/* move reg r to reg rd */
				mon_ins (i_move, rd, r);
			}
			return NOREG;
	    }			/* end inreg dest */
		
		case insomereg:
			/* **** can choose dest register to be source reg **** */
	    {
			int  *sr = someregalt (dest.answhere);
			if (*sr != -1) {
				failer ("Somereg *2");
			}
			*sr = r;
			return NOREG;
	    }
		
		case infreg:
			/* ***source in fix reg,  dest in floating point register **********
			 */
	    {
			freg fr;
			fr = fregalt (dest.answhere);
			cop_ins (i_mtc1, r, fr.fr << 1);
			if (fr.dble) {
				cop_ins (i_mtc1, r + 1, (fr.fr << 1) + 1);
			};
			return NOREG;
	    }			/* end infreg dest */
		
		case insomefreg: {
			/* source in fixed, can choose flt dest */
			somefreg sfr;
			freg fr;
			sfr = somefregalt(dest.answhere);
			if (*sfr.fr != -1) { failer ("Somefreg *2"); }
			*sfr.fr = getfreg(fregs);
			fr.fr = *sfr.fr;
			fr.dble = sfr.dble;
			setfregalt(dest.answhere, fr);
			goto start;
		}
		case notinreg:
			/* **source in fix reg, dest instore ******************* */
	    {
			char *st = (size==al) ?(
	           	(size <= 8) ? i_sb : ((size <= 16) ? i_sh : i_sw)):
	           	((size<=8)? i_sb : ((size <= 16) ? i_ush : i_usw));
			instore is;
			is = insalt (dest.answhere);
			if (is.adval) {
				ls_ins (st, r, is.b);
			}			/* is the value an address? */
			else {
				baseoff b;
				b.base = getreg(regs);
				b.offset = 0;
				ls_ins (i_lw, b.base, is.b);
				ls_ins (st, r, b);
			};
			
			return r;
	    }			/* end notinreg dest */
		
		
		}			/* end switch dest */
	}				/* end inreg a */
    case infreg:
/****************** source in floating point register ******************/
	{
		freg fr;
		fr = fregalt (a);
		switch (dest.answhere.discrim) {
		case inreg:
			/* *source in float reg, dest in fixed point register ********
			 */
	    {
			int   rd = regalt (dest.answhere);
			if (rd != 0) {
				if (BIGEND) {
					if (fr.dble) {
						cop_ins (i_mfc1, rd, (fr.fr << 1) + 1);
					}
					cop_ins (i_mfc1, rd+1, fr.fr << 1);
				}
				else {
					cop_ins (i_mfc1, rd, fr.fr << 1);
					if (fr.dble) {
						cop_ins (i_mfc1, rd + 1, (fr.fr << 1) + 1);
					}
				}
			};
			return NOREG;
	    }			/* end inreg dest */
		case insomereg:
			/* *** source in flt reg, can choose dest reg ***** */
	    {
			int  *sr = someregalt (dest.answhere);
			if (*sr != -1) {
				failer ("Somereg *2");
			}
			*sr = getreg (regs);
			setregalt (dest.answhere, *sr);
			goto start;
	    }
		case insomefreg: {
			/* can choose dest reg to be source reg */
			somefreg sfr;
			sfr = somefregalt(dest.answhere);
			if (*(sfr.fr) !=-1) failer("some freg * 2");
			*(sfr.fr) = fr.fr;
	        return NOREG;
		}
		case infreg:
			/* ******* source and dest in floating point registers *******
			 */
	    {
			freg frd;
			frd = fregalt (dest.answhere);
			if (fr.fr != frd.fr) {
				rrfp_ins ((frd.dble) ? i_mov_d : i_mov_s, frd.fr << 1, fr.fr << 1);
			};
			return NOREG;
	    }			/* end infreg dest */
		case notinreg:
			/* ********** source in flt reg, dest instore ******************
			 */
	    {
			char *st = (fr.dble) ? i_s_d : i_s_s;
			instore is;
			
			if ((dest.ashwhere.ashsize == 64 && !fr.dble) ||
				(dest.ashwhere.ashsize == 32 && fr.dble)) {
				st = (dest.ashwhere.ashsize==64) ? i_s_d:i_s_s;
				/* failer ("INCONSISTENT SIZES"); */
			}
			
			is = insalt (dest.answhere);
			if (is.adval) {
				lsfp_ins (st, fr.fr << 1, is.b);
			}
			else {
				baseoff b;
				b.base = getreg (regs);
				b.offset = 0;
				ls_ins (i_lw, b.base, is.b);
				lsfp_ins (st, fr.fr << 1, b);
			};
			
			return ((fr.dble) ? -(fr.fr + 32) : (fr.fr + 32));
	    }			/* end notinreg dest */
		}			/* end switch dest */
	}				/* end infreg a */
	
	
	
    case notinreg:
/*********************** source instore *************************/
	{
		instore iss;
		char *ld;
		iss = insalt (a);
		if (iss.adval && iss.b.offset == 0 && iss.b.base > 0 && iss.b.base <= 31) {
			setregalt (a, iss.b.base);
			goto start;
		}
		
		if (al==1) { /* contained size for naked bitfields */
			al = (size<=8)? 8: ((size<=16)? 16:32);
		}
		ld = (iss.adval) ? i_la : ((al <= 8) ? ((sgned) ? i_lb : i_lbu) :
								   ((al <= 16) ? ((sgned) ? i_lh : i_lhu) : i_lw));
		/* determine which load instruction to use from al and adval */
		
		switch (dest.answhere.discrim) {
		case insomefreg: {
			/* source in store can choose dest freg */
			somefreg sfr;
			freg fr;
			sfr = somefregalt(dest.answhere);
			if (*sfr.fr != -1) { failer ("Somefreg *2"); }
			*sfr.fr = getfreg(fregs);
			fr.fr = *sfr.fr;
			fr.dble = sfr.dble;
			setfregalt(dest.answhere, fr);
			goto start;
		}
		case insomereg:
			/* **** source instore, can choose dest reg ***** */
	    {
			int  *sr = someregalt (dest.answhere);
			if (*sr != -1) {
				failer ("Somereg *2");
			}
			*sr = getreg (regs);
			setregalt (dest.answhere, *sr);
			/* and continue to next case */
	    }
		case inreg:
			/* ********** source and dest in fixpnt reg ************* */
	    {
			int   rd = regalt (dest.answhere);
			if (rd != 0 /* nowhere */) {
				ls_ins (ld, rd, iss.b);
			};
			return NOREG;
	    }			/* end inreg dest */
		
		
		case infreg:
			/* *********** source instore, dest in floating pnt reg ********
			 */
	    {
			freg frd;
			frd = fregalt (dest.answhere);
			if (iss.b.base == 0 && iss.b.offset == 0) {
				cop_ins (i_mtc1, 0, frd.fr << 1);
				if (frd.dble) {
					cop_ins (i_mtc1, 0, (frd.fr << 1) + 1);
				};
				return NOREG;
			}
			lsfp_ins ((frd.dble) ? i_l_d : i_l_s, frd.fr << 1, iss.b);
			return NOREG;
	    }			/* end infreg dest */
		
		
		case notinreg:
			/* *********** source and dest  instore ************* */
	    {
			char *st = (al <= 8) ? i_sb : ((al <= 16) ? i_sh : i_sw);
			/* determine which store instruction from al (align from
			 *	         dest) */
			instore isd;
			int   sunit = min (al, 32);
			int   step = sunit >> 3;
			int   s = (dest.ashwhere.ashsize + sunit - 1) / sunit;
			bool unalign = 0;
			isd = insalt (dest.answhere);
			if (al == 8 && s >= 4) {
				int   r = getreg (regs);
				freeregs = guardreg(r,freeregs);
				/* register for holding values transferred */
				unalign = 1;
				if (s <= 16) {	/* in line unalligned move */
					if (!isd.adval) {
						int r3 = getreg(freeregs.fixed);
						ls_ins (i_lw, r3, isd.b);
						isd.b.base = r3;
						isd.b.offset = 0;
						isd.adval = 1;
					}
					for (; s >= 4; s -= 4) {
						ls_ins (i_ulw, r, iss.b);
						ls_ins (i_usw, r, isd.b);
						iss.b.offset += 4;
						isd.b.offset += 4;
					}
					
				}
				else {		/* unaligned loop move *//* copy with
													  *				   loop, length in r1, to in 2, from in 3
													  */
					int   l = new_label ();
					int   r1 = getreg (freeregs.fixed);
					int r3, r2;
					baseoff src;
					baseoff dst;
					freeregs = guardreg(r1,freeregs);
					r3 = getreg(freeregs.fixed);
					r2 = getreg(guardreg(r3,freeregs).fixed);
					
					src.base = r3; src.offset = 0;
					dst.base = r2; dst.offset = 0;
					
					ls_ins ((isd.adval) ? i_la : i_lw, r2, isd.b);
					isd.adval = 1;
					ls_ins (i_la, r3, iss.b);
					
					
					rri_ins (i_addu, r1, r3, (s & ~3));
					/* output instruction to initialise counter */
					set_label (l);
					ls_ins (i_ulw, r, src);
					rri_ins (i_addu, r3, r3, 4);
					ls_ins (i_usw, r, dst);
					rri_ins (i_addu, r2, r2, 4);
					condrr_ins (i_bne, r1, r3, l);
					/* instruction to test end of loop */
					
					s = s & 3;
					iss.b = src;
					isd.b = dst;
				}
				
				for (; s>0; s--) {
					ls_ins(i_lb, r, iss.b);
					ls_ins(i_sb, r, isd.b);
					iss.b.offset += 1;
					isd.b.offset += 1;
				};
				return NOREG;
			}
			
			if (s <= inlineassign) {/* move in line */
				int   r = getreg (regs);
				/* register for holding values transferred */
				
				if (!isd.adval) {
					int r3 = getreg(guardreg(r,freeregs).fixed);
					freeregs = guardreg(r3,freeregs);
					ls_ins (i_lw, r3, isd.b);
					isd.b.base = r3;
					isd.b.offset = 0;
				}
				if (s == 1) {
					ls_ins (ld, r, iss.b);
					ls_ins (st, r, isd.b);
					
					return (unalign) ? NOREG : r;
				}
				else {
					int   er = getreg (freeregs.fixed);
					int   nr = r;
					for (; s > 0; --s) {
						ls_ins (ld, nr, iss.b);
						ls_ins (st, nr, isd.b);
						iss.b.offset += step;
						isd.b.offset += step;
						if (nr == r) {
							nr = er;
						}
						else {
							nr = r;
						}
					}
					return NOREG;
				}
			}			/* inline end */
			else {		/* copy with loop, length in r1, to in r2,
						 *				   from in r3 */
				int   a = getreg (regs);
				/* get register for transferring values */
				int   l = new_label ();
				int   r1, r2, r3;
				baseoff src;
				baseoff dst;
				freeregs = guardreg(a,freeregs);
				r1 = getreg(freeregs.fixed);
				freeregs = guardreg(r1,freeregs);
				r2 = getreg(freeregs.fixed);
				freeregs = guardreg(r2,freeregs);
				r3 = getreg(freeregs.fixed);
				src.base = r3; src.offset = 0;
				dst.base = r2; dst.offset = 0;
				
				
				ls_ins ((isd.adval) ? i_la : i_lw, r2, isd.b);
				ls_ins (i_la, r3, iss.b);
				
				ri_ins (i_li, r1, s);
				/* output instruction to initialise counter */
				set_label (l);
				ls_ins (ld, a, src);
				rri_ins (i_addu, r3, r3, step);
				ls_ins (st, a, dst);
				rri_ins (i_addu, r2, r2, step);
				rri_ins (i_subu, r1, r1, 1);
				/* instruction to decrement counter */
				condr_ins (i_bgtz, r1, l);
				/* instruction to test end of loop */
				
				return NOREG;
			}			/* loop assign */
	    }			/* end notinreg dest */
		}			/* end switch dest */
	}				/* end notinreg a */
	}				/* end switch a */
}
