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




/*
 *			    VERSION INFORMATION
 *			    ===================
 *
 *--------------------------------------------------------------------------
 *$Header$
 *--------------------------------------------------------------------------
 *$Log$
 *Revision 1.2  2002/11/21 22:31:14  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.8  1997/08/23  13:54:10  pwe
 * initial ANDF-DE
 *
 * Revision 1.7  1996/10/03  08:51:12  pwe
 * PIC global/large offset, and PIC case guardregs
 *
 * Revision 1.6  1996/08/22  16:47:05  pwe
 * correct accessing for double params
 *
 * Revision 1.5  1996/02/29  17:39:30  john
 * Fix to double load
 *
 * Revision 1.4  1996/02/27  11:20:28  john
 * *** empty log message ***
 *
 * Revision 1.3  1996/01/24  18:11:05  john
 * Removed assertion
 *
 * Revision 1.2  1995/05/26  12:59:39  john
 * Reformatting
 *
 * Revision 1.1.1.1  1995/03/13  10:18:44  john
 * Entered into CVS
 *
 * Revision 1.7  1994/12/01  13:35:24  djch
 * va_alist can generate 4byte aligned doubles on the stack... Always indexed by
 * -8, so generated 2 loads for these..
 *
 * Revision 1.6  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.5  1994/06/22  09:52:52  djch
 * temporary fix to put temporary bitfields in the bottom of the word - one day
 * much of the code could go
 *
 * Revision 1.4  1994/05/25  14:13:03  djch
 * Added CREATE_instore_bits to shut up tcc
 *
 * Revision 1.3  1994/05/19  08:59:05  djch
 * added empty {} to pacify tcc
 *
 * Revision 1.2  1994/05/13  12:39:32  djch
 * Incorporates improvements from expt version
 * use new macros from addrtypes.h, added defaults to switchs
 *
 * Revision 1.1  1994/05/03  14:49:44  djch
 * Initial revision
 *
 * Revision 1.4  93/08/27  11:31:58  11:31:58  ra (Robert Andrews)
 * Added a couple of explicit integer casts.
 * 
 * Revision 1.3  93/07/15  12:32:46  12:32:46  ra (Robert Andrews)
 * Reformatted.  Changed critical value for introducing a loop for a large
 * move from 8 to 12.
 * 
 * Revision 1.2  93/07/05  18:22:05  18:22:05  ra (Robert Andrews)
 * Reformatted slightly.
 * 
 * Revision 1.1  93/06/24  14:58:45  14:58:45  ra (Robert Andrews)
 * Initial revision
 * 
 *--------------------------------------------------------------------------
 */


#define SPARCTRANS_CODE

/*
 *  The procedure move produces code to move a value from a to the
 *  destination dest.  This takes the form of a switch test on the
 *  parameter a (type ans) which is either a reg, freg instore or
 *  bitad value.  In each of the three cases the ans field of the
 *  dest is similarly dealt with to determine the necessary
 *  instructions for the move.  Sizes and alignment are taken from
 *  the ash field of the destination.  The routine returns the
 *  register used if a single word destination is instore, and
 *  NOREG otherwise.
 */

#include "config.h"
#include "common_types.h"
#include "myassert.h"
#include "sparcins.h"
#include "inst_fmt.h"
#include "addrtypes.h"
#include "proctypes.h"
#include "proc.h"
#include "getregs.h"
#include "labels.h"
#include "comment.h"
#include "bitsmacs.h"
#include "regmacs.h"
#include "maxminmacs.h"
#include "makecode.h"
#include "flags.h"
#include "move.h"


/*
 *  MAXIMUM SIZE FOR INLINED MOVES
 */

#define MAX_STEPS_INLINE_MOVE	12


/*
 *  BITMASK : NBITMASK (n) GIVES n 1'S
 */

#define NBITMASK(n)  ((unsigned long)((n)==32 ?~0L:((1<<(n))-1)))


/*
 *  TYPE REPRESENTING INSTRUCTION PAIRS
 *  Unsigned version, signed version.
 */

typedef ins_p ins_sgn_pair [2];


/*
 *  ARRAY OF LOAD INSTRUCTIONS
 */

static CONST ins_sgn_pair ld_ins_sz [] = {
	{ I_NIL, I_NIL },
	{ i_ldub, i_ldsb },
	{ i_lduh, i_ldsh },
	{ I_NIL, I_NIL },
	{ i_ld, i_ld },
	{ I_NIL, I_NIL },
	{ I_NIL, I_NIL },
	{ I_NIL, I_NIL },
	{ i_ldd, i_ldd }
};


/*
 *  ARRAY OF STORE INSTRUCTIONS
 */

static CONST ins_sgn_pair st_ins_sz [] = {
	{ I_NIL, I_NIL },
	{ i_stb, i_stb },
	{ i_sth, i_sth },
	{ I_NIL, I_NIL },
	{ i_st, i_st },
	{ I_NIL, I_NIL },
	{ I_NIL, I_NIL },
	{ I_NIL, I_NIL },
	{ i_std, i_std }
};


/*
 *  FIND THE LOAD INSTRUCTION FOR SIZE bits, SIGNEDNESS sgned
 */

ins_p
i_ld_sz(int bits, int sgned)
{
	return (ld_ins_sz [ bits / 8 ] [ sgned ]);
}


/*
 *  FIND THE STORE INSTRUCTION FOR SIZE bits (UNSIGNED)
 */

ins_p
i_st_sz(int bits)
{
	return (st_ins_sz [ bits / 8 ] [0]);
}


/*
 *  LOAD THE ADDRESS REPRESENTED BY is INTO reg
 */

void
ld_addr(instore is, int reg)
{
	if (is.adval) {
		if (IS_FIXREG (is.b.base)) {
			rir_ins (i_add, is.b.base, is.b.offset, reg);
		} else {
			set_ins (is.b, reg);
		}
	} else {
		ld_ins (i_ld, is.b, reg);
	}
	return;
}


/*
 *  LOAD THE ADDRESS REPRESENTED BY is INTO A REGISTER
 *  The register number is returned.  regs gives the registers to 
 *  choose from.
 */
int
addr_reg(instore is, long regs)
{
	int r;
	if (is.adval && IS_FIXREG (is.b.base) && is.b.offset == 0) {
		return (is.b.base);
	}
	r = getreg (regs);
	ld_addr (is, r);
	return (r);
}


/*
 *  MOVE a INTO dest
 *  regs gives the free registers, sgned gives the signedness.
 */

int
move(ans a, where dest, long regs, bool sgned)
{
	int al = (int) dest.ashwhere.ashalign;
	if (dest.ashwhere.ashsize == 0) return (NOREG);
	
	if (PIC_code && discrim (dest.answhere) == notinreg) {
		instore iss;
		iss = insalt (dest.answhere);
		if (!IS_FIXREG (iss.b.base) && !SIMM13_SIZE (iss.b.offset)) {
			/* global with large offset: we have to avoid double use of R_TMP */
			int ofs = iss.b.offset;
			int r = getreg (regs);
			regs |= RMASK (r);
			iss.b.offset = 0;
			set_ins (iss.b, r);
			iss.b.offset = ofs;
			iss.b.base = r;
			setinsalt (dest.answhere, iss);
		}
	}
	
	start : switch (discrim (a)) {
		
	case insomereg :
	case insomefreg : {
		/* Source is in some register */
		fail ("move : source register not specified");
		return (NOREG);
	}
	case inreg : {
		/* Source in fixed point register */
		int r = regalt (a);
		
		switch (discrim (dest.answhere)) {
			
		case inreg : {
			/* Register to register move */
			int rd = regalt (dest.answhere);
			if (rd != R_G0 && rd != r) {
				rr_ins (i_mov, r, rd);
			}
			return (NOREG);
		}
			
		case insomereg : {
			/* Register to some register move */
			int *sr = someregalt (dest.answhere);
			if (*sr != -1) fail ("Illegal register");
			*sr = r;
			return (NOREG);
		}
			
		case infreg : {
			/* Register to floating register move */
			freg fr;
			fr = fregalt (dest.answhere);
			st_ro_ins (i_st, r, mem_temp (0));
			ldf_ro_ins (i_ld, mem_temp (0), fr.fr << 1);
			if (fr.dble) {
				st_ro_ins (i_st, r + 1, mem_temp (4));
				ldf_ro_ins (i_ld, mem_temp (4),
							(fr.fr << 1) + 1);
			}
			return (NOREG);
		}
			
		case notinreg : {
			/* Register to store move */
			instore is;
			ins_p st = i_st_sz (al);
			
			if (al == 1) {
				st = i_st_sz ((int) dest.ashwhere.ashsize);
			} else {
				/*assert (al == dest.ashwhere.ashsize) ;*/
				st = i_st_sz (al);
			}
			
			is = insalt (dest.answhere);
			if (is.adval) {
				st_ins (st, r, is.b);
			} else {
				baseoff b;
				b.base = R_TMP;
				b.offset = 0;
				ld_ins (i_ld, is.b, b.base);
				st_ins (st, r, b);
			}
			return (r);
		}
		default:
			fail("fixed -> wrong dest");
		}
		/* NOT REACHED */
	}
	case infreg : {
		/* Source in floating point register */
		freg fr;
		fr = fregalt (a);
		
		switch (discrim (dest.answhere)) {
		case inreg : {
			/* Floating register to register move */
			int rd = regalt (dest.answhere);
			
			if (rd != 0) {
				/* store and load to move to fixed reg */
				stf_ins (i_st, fr.fr<<1, mem_temp (0));
				ld_ro_ins (i_ld, mem_temp (0), rd);
				if (fr.dble) {
					stf_ins (i_st, (fr.fr << 1) + 1,
							 mem_temp (4));
					ld_ro_ins (i_ld, mem_temp (4), rd + 1);
				}
			}
			return (NOREG);
		}
		case insomereg : {
			/* Floating register to some register move */
			int *sr = someregalt (dest.answhere);
			if (*sr != -1) fail ("Illegal register");
			*sr = getreg (regs);
			regs |= RMASK (*sr);
			setregalt (dest.answhere, *sr);
			goto start;
		}
		case infreg : {
			/* Floating register to floating register move */
			freg frd;
			frd = fregalt (dest.answhere);
			
			if (fr.fr != frd.fr) {
				rrf_ins (i_fmovs, fr.fr << 1, frd.fr << 1);
				if (frd.dble) {
					rrf_ins (i_fmovs, (fr.fr << 1) + 1,
							 (frd.fr << 1) + 1);
				}
			}
			return (NOREG);
		}
		case notinreg : {
			/* Floating register to store move */
			instore is;
			ins_p st = (fr.dble ? i_std : i_st);
			
			if ((dest.ashwhere.ashsize == 64 && !fr.dble) ||
				(dest.ashwhere.ashsize == 32 && fr.dble)) {
				fail ("Inconsistent sizes in move");
			}
			
			is = insalt (dest.answhere);
			if (is.adval) {
				if (fr.dble) {
					if (((is.b.offset & 7) == 0) && 
						((is.b.base == R_FP) || (is.b.base == R_SP))) {
						/* double aligned */
						stf_ins (i_std, fr.fr << 1, is.b);
					} else {
						/* not double aligned */
						stf_ins (i_st, fr.fr << 1, is.b);
						is.b.offset += 4;
						stf_ins (i_st, (fr.fr << 1) + 1, is.b);
					}
				} else {
					stf_ins (i_st, fr.fr << 1, is.b);
				}
			} else {
				baseoff b;
				b.base = getreg (regs);
				b.offset = 0;
				ld_ins (i_ld, is.b, b.base);
				stf_ro_ins (st, fr.fr << 1, b);
			}
			
			return (fr.dble ? -(fr.fr + 32) : (fr.fr + 32));
		}
		default:
			fail("Float to wrong dest");
		}
		/* NOT REACHED */
	}
	case notinreg : {
		/* Source in store */
		instore iss;
		int size = dest.ashwhere.ashsize;
		iss = insalt (a);
		
		if (PIC_code && !IS_FIXREG (iss.b.base) && !SIMM13_SIZE (iss.b.offset)) {
			/* global with large offset: we have to avoid double use of R_TMP */
			int ofs = iss.b.offset;
			int r = getreg (regs);
			regs |= RMASK (r);
			iss.b.offset = 0;
			set_ins (iss.b, r);
			iss.b.offset = ofs;
			iss.b.base = r;
		}
	    
		if (iss.adval && iss.b.offset == 0 && IS_FIXREG (iss.b.base)) {
			/* address of [ base_reg + 0 ] is base_reg */
			setregalt (a, iss.b.base);
			goto start;
		}
		if (al == 1){
			al = (size<=8)?9: ((size<=16)?16:32);
		}
		if (al == 64) al = 32;
		
		/* determine which load instruction to use from al and adval */
		switch (discrim (dest.answhere)) {
		case insomereg : {
			/* Move store to some register */
			int *sr = someregalt (dest.answhere);
			if (*sr != -1) fail ("Illegal register");
			*sr = getreg (regs);
			regs |= RMASK (*sr);
			setregalt (dest.answhere, *sr);
			/* FALL THROUGH */
		}
		case inreg : {
			/* Move store to register */
			int rd = regalt (dest.answhere);
			if (rd != R_G0) {
				if (iss.adval) {
					/* generate address of source */
					if (IS_FIXREG (iss.b.base)) {
						rir_ins (i_add, iss.b.base,
								 iss.b.offset, rd);
					} else {
						set_ins (iss.b, rd);
					}
				} else {
					/* load source */
					ld_ins (i_ld_sz (al, sgned), iss.b, rd);
				}
			}
			return (NOREG);
		}
		case infreg : {
			/* Move store to floating register */
			freg frd;
			frd = fregalt (dest.answhere);
			assert (!iss.adval);
			if (frd.dble) {
				/* double precision */
				if (((iss.b.offset & 7) == 0) && (iss.b.offset != -8) && 
					((iss.b.base == R_FP) || (iss.b.base == R_SP))) {
					/* source is double aligned */
					ldf_ins (i_ldd, iss.b, frd.fr << 1);
				} else {
					/* source is not double aligned */
					ldf_ins (i_ld, iss.b, frd.fr << 1);
					iss.b.offset += 4;
					ldf_ins (i_ld, iss.b, (frd.fr << 1) + 1);
				}
			} else {
				/* single precision */
				ldf_ins (i_ld, iss.b, frd.fr << 1);
			}
			return (NOREG);
		}
		case notinreg : {
			/* Move store to store address */
			int bits;
			int no_steps;
			int bits_per_step;
			int bytes_per_step;
			instore isd;
			ins_p st, ld;
			bool unalign = (bool) (al < 32);
			
			/* we are limited by 32 bit regs */
			bits_per_step = MIN_OF (al, 32);
			bytes_per_step = bits_per_step / 8;
			
			/* round up number of bits to be moved */
			bits = (int) ((dest.ashwhere.ashsize +
						   bits_per_step - 1) &
						  ~(bits_per_step - 1));
			
			no_steps = (bits + bits_per_step - 1) / bits_per_step;
			
			if ((al % 8) != 0 || (bits % 8) != 0) {
				fail ("move : misaligned store");
				return (NOREG);
			}
			assert ((bits % al) == 0);
			assert (bytes_per_step > 0 && bytes_per_step <= 4);
			assert (no_steps > 0);
			assert ((no_steps * bytes_per_step) == (bits / 8));
			
			ld = i_ld_sz (bits_per_step, sgned);
			st = i_st_sz (bits_per_step);
			
			isd = insalt (dest.answhere);
			if (no_steps <= MAX_STEPS_INLINE_MOVE) {
				/* expand to a number of loads and stores */
				if (no_steps == 1) {
					/* move can be done in one step */
					int r = getreg (regs);
					regs |= RMASK (r);
					if (iss.adval) {
						/* generate address of source */
						if (IS_FIXREG (iss.b.base)) {
							if (iss.b.offset == 0) {
								r = iss.b.base;
							} else {
								rir_ins (i_add, iss.b.base,
										 iss.b.offset, r);
							}
						} else {
							set_ins (iss.b, r);
						}
					} else {
						/* load source */
						ld_ins (ld, iss.b, r);
					}
					
					if (!isd.adval) {
						ld_ins (i_ld, isd.b, R_TMP);
						isd.b.base = R_TMP;
						isd.b.offset = 0;
					}
					st_ins (st, r, isd.b);
					return (unalign ? NOREG : r);
				} else {
					/* use two registers, ensuring load delay
					 *	     slot is not occupied */
					int r1, r2;
					int ld_steps = no_steps;
					int st_steps = no_steps;
					
					assert (ld_steps >= 2);
					/*assert (!iss.adval) ;*/
					assert (bits_per_step <= 32);
					
					/* find the registers to be used */
					r1 = getreg (regs);
					regs |= RMASK (r1);
					r2 = getreg (regs);
					regs |= RMASK (r2);
					
					if (!IS_FIXREG (iss.b.base)) {
						/* load source ptr in reg */
						int pr = getreg (regs);
						regs |= RMASK (pr);
						set_ins (iss.b, pr);
						iss.b.base = pr;
						iss.b.offset = 0;
					}
					
					if (!isd.adval) {
						int pr = getreg (regs);
						regs |= RMASK (pr);
						ld_ins (i_ld, isd.b, pr);
						isd.b.base = pr;
						isd.b.offset = 0;
					} else if (!IS_FIXREG (isd.b.base)) {
						int pr = getreg (regs);
						regs |= RMASK (pr);
						set_ins (isd.b, pr);
						isd.b.base = pr;
						isd.b.offset = 0;
					}
					
					/* first pre-load both registers */
					ld_ro_ins (ld, iss.b, r1);
					ld_steps--;
					iss.b.offset += bytes_per_step;
					
					ld_ro_ins (ld, iss.b, r2);
					ld_steps--;
					iss.b.offset += bytes_per_step;
					
					/* now generate a sequence of instructions
					 *	     of the form :
					 *
					 *	     st r1
					 *	     ld r1
					 *	     st r2
					 *	     ld r2
					 */
					while (st_steps > 0) {
						/* st r1 */
						st_ro_ins (st, r1, isd.b);
						st_steps--;
						isd.b.offset += bytes_per_step;
						
						/* ld r1 */
						if (ld_steps > 0) {
							ld_ro_ins (ld, iss.b, r1);
							ld_steps--;
							iss.b.offset += bytes_per_step;
						}
						
						/* st r2 */
						if (st_steps > 0) {
							st_ro_ins (st, r2, isd.b);
							st_steps--;
							isd.b.offset += bytes_per_step;
						}
						
						/* ld r2 */
						if (ld_steps > 0) {
							ld_ro_ins (ld, iss.b, r2);
							ld_steps--;
							iss.b.offset += bytes_per_step;
						}
					}
					assert (ld_steps == 0);
					return (NOREG);
				}
			} else {
				/* large number of steps - use a loop */
				int cnt_reg;
				int copy_reg;
				int srcptr_reg;
				int destptr_reg;
				int loop = new_label ();
				
				assert (!iss.adval);
				assert (bytes_per_step <= 4);
				
				/* find control register */
				cnt_reg = getreg (regs);
				regs |= RMASK (cnt_reg);
				
				/* find source register */
				assert (!iss.adval);
				iss.adval = 1;
				srcptr_reg = addr_reg (iss, regs);
				regs |= RMASK (srcptr_reg);
				
				/* find destination register */
				destptr_reg = addr_reg (isd, regs);
				regs |= RMASK (destptr_reg);
				
				/* find copy register */
				copy_reg = R_TMP;
				
				/* main loop */
				ir_ins (i_mov, (long) (bytes_per_step * no_steps),
						cnt_reg);
				set_label (loop);
				rir_ins (i_subcc, cnt_reg, (long) bytes_per_step,
						 cnt_reg);
				ld_rr_ins (ld, srcptr_reg, cnt_reg, copy_reg);
				st_rr_ins (st, copy_reg, destptr_reg, cnt_reg);
				br_ins (i_bne, loop);
				return (NOREG);
			}
		}
		default:
		{
			/* fall through to fail */
		}
		}
	}
	}
	fail ("Illegal move");
	return (NOREG);
}

