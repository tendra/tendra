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
 * Revision 1.3  1995/09/12  10:59:30  currie
 * gcc pedanttry
 *
 * Revision 1.2  1995/08/16  16:06:50  currie
 * Shortened some .h names
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
 ***********************************************************************/
/* locate.c
 *     discovers "where" an "exp" is;
 *     The where coding of an address tells one whether the result of
 *      evaluating an exp is in a register or directly or literally in store,
 */


#include "config.h"
#include "addrtypes.h"
#include "expmacs.h"
#include "tags.h"
#include "inst_fmt.h"
#include "mips_ins.h"
#include "bitsmacs.h"
#include "exp.h"
#include "procrectypes.h"
#include "guard.h"
#include "eval.h"
#include "regexps.h"
#include "shapemacs.h"
#include "psu_ops.h"
#include "getregs.h"
#include "move.h"
#include "handle_sregs.h"
#include "common_types.h"
#include "frames.h"
#include "code_here.h"
#include "locate.h"
#include "basicread.h"

extern  FILE * as_file;

long  locals_offset;		/* the offset in bits of start of current
							 *				   locals */
long  frame_size;		/* the size of the current stack frame in
						 *				   bits */


baseoff
boff(exp id)
{		/* decodes id to give a baseoff suitable
		 *				   for ls_ins etc */
	baseoff an;
	if (isglob (id)) {		/* globals */
		dec * gl = brog(id);
		long sno = gl->dec_u.dec_val.sym_number;
		an.base = -(sno + 1);
		an.offset = 0;
	}
	else {
		int   x = no (id);
		int   b = x & 0x3f;
		if (name(son(id))==caller_name_tag) {
			an.base = 29;
			an.offset = (x-b)>>4;
			/* caller tags */
		}
		else
			if (b == 29) {
				an.base = 29;
				an.offset = ((x - b) >> 4) + (locals_offset >> 3);
				/* locally declared things accessed by sp*/
			}
			else
				if ((b==30 && Has_fp)) {
					an.base = b;
					an.offset = (((x - b)) >> 4) + (locals_offset >> 3)
						- ((frame_size+callee_size)>>3);
					/* locally declared things accessed by fp  */
				}
				else
					if ((b == local_reg && Has_vcallees)) {
						an.base = b;
						an.offset = (((x - b)) >> 4) + (locals_offset >> 3)
							- (frame_size>>3);
						/* locally declared things accessed by local_reg */
					}
					else
						if (b <= 31) {
							an.base = b;
							an.offset = ((x - b) >> 4);
							/* other base offsets */
						}
						else
							if (b == 32) {
								an.base = -((x - b) >> 6);
								an.offset = 0;
								/* global names  */
							}
							else
								if (b == 33) {
									an.base = (x - b) >> 6;
									an.offset = 0;
									/* global anonymous */
								}
								else {
									failer ("not a baseoff in boff ");
								}
	}
	return an;
}

where locate(exp e, space sp, shape s, int dreg);
/* locate differs from locate1 only in that it looks to see e has already
 *    been evaluated somehow */

where
locate1(exp e, space sp, shape s, int dreg)
{
	/* finds the address of e using shape s;
	 *				   sp gives available t-regs for any inner
	 *				   evaluation. dreg is historical. */
	ash a;
	ans aa;
	where wans;
	a = ashof (s);
	
/*  while (name (e) == diag_tag || name (e) == fscope_tag
 *      || name (e) == cscope_tag) {
 *    e = son (e);
 *  }
 */
	switch (name (e)) {
    case name_tag:
	{
		exp decx = son (e);
		bool var = isvar (decx);
		/* this a locally declared name ... */
		if (props (decx) & defer_bit) {
			/* ... it has been identified with a
			 *				   simple expression which is better
			 *				   evaluated every time */
			where w;
			w = locate (son (decx), sp, sh (son (decx)), dreg);
			
			if (no (e) == 0) {
				aa = w.answhere;
			}
			else {
				instore is;
				switch (w.answhere.discrim) {
				case notinreg:
				{
					is = insalt (w.answhere);
					is.b.offset += (no (e) / 8);
					break;
				}
				default:
					failer ("NOT deferable");
				}
				
				setinsalt (aa, is);
			}
		}
		else
			if (props (decx) & inreg_bits) {
				/* ... it has been allocated in a fixed
				 *				   point reg */
				if (var) {
					setregalt (aa, no (decx));
				}
				else {
					instore b;
					b.b.base = no (decx);
					b.b.offset = 0;
					b.adval = 1;
					setinsalt (aa, b);
				}
			}
			else
				if (props (decx) & infreg_bits) {
					/* ... it has been allocated in a floating
					 *				   point reg */
					freg fr;
					fr.fr = no (decx);
					fr.dble = (a.ashsize == 64) ? 1 : 0;
					setfregalt (aa, fr);
				}
				else {		/* ... it is in memory */
					instore is;
					if (var || (name (sh (e)) == prokhd &&
								(son (decx) == nilexp || name (son (decx)) == proc_tag
								 || name (son (decx)) == general_proc_tag))) {
						is.adval = 1;
					}
					else {
						is.adval = 0;
					}
					is.b = boff (decx);
					is.b.offset += (no (e) / 8);
					setinsalt (aa, is);
				}
		wans.answhere = aa;
		wans.ashwhere = a;
		return wans;
	}
	
    case addptr_tag:
	{
		exp sum = son (e);
		where wsum;
		int   addend;
		space nsp;
		int   reg;
		int   ind;
		instore is;
		ans asum;
		wsum = locate (sum, sp, sh (sum), 0);
		asum = wsum.answhere;
		/* answer is going to be wsum displaced by integer result of
		 *	   evaluating bro(sum) */
		
		switch (asum.discrim) {
		case notinreg:
	    {
			is = insalt (asum);
			if (is.adval) {	/* wsum is a literal address in store ...
							 */
				baseoff b;
				b = is.b;
				if (b.base < 0 || b.base > 31) {
					/* ... it is not a base-offset , so make
					 *				   it one */
					reg = getreg (sp.fixed);
					ls_ins (i_la, reg, b);
					keepreg (sum, reg);
					b.base = reg;
					b.offset = 0;
				}
				nsp = guardreg (b.base, sp);
				
				addend = reg_operand (bro (sum), nsp);
				/* evaluate the displacement ... */
				if (dreg == 0)
					dreg = getreg (nsp.fixed);
				rrr_ins (i_addu, dreg, b.base, addend);
				/* ... add it to the base register into new reg */
				b.base = dreg;
				is.b = b;
				setinsalt (aa, is);
				wans.answhere = aa;
				wans.ashwhere = a;
				/* ...and use it as base a literal base-offset result */
				keepexp (e, aa);
				return wans;
			}
			else {		/* wsum represents an actual pointer in
						 *				   store... */
				ind = getreg (sp.fixed);
				ls_ins (i_lw, ind, is.b);
				/* ... so load it into a good register */
			}
			goto breakpt;
			/* should be break - thought there was cc error */
			
	    }			/* end notinreg */
		
		case inreg:
			/* wsum is already in reg */
	    {
			ind = regalt (asum);
			goto breakpt;
	    }
		
		default: {
			failer ("Locate ? reg");
	    }
		}			/* end case */
		
	  breakpt: 			/* register ind contains the evaluation of
						 *				   1st operand of addptr */
		nsp = guardreg (ind, sp);
		if (name(bro(sum)) == env_offset_tag
			|| name(bro(sum)) == general_env_offset_tag) {
			is.b.base = ind;
			is.b.offset = frame_offset(son(bro(sum)));
		}
		else {
			addend = reg_operand (bro (sum), nsp);
			/* evaluate displacement .... */
			if (dreg == 0)
				dreg = getreg (nsp.fixed);
			rrr_ins (i_addu, dreg, ind, addend);
			/* ... add it to ind in new reg */
			is.b.base = dreg;
			is.b.offset = 0;
        }
		is.adval = 1;
		setinsalt (aa, is);
		wans.answhere = aa;
		wans.ashwhere = a;
		/* ... and deliver literal base_offset */
		keepexp (e, aa);
		return wans;
	}				/* end add_ptr */
	
    case subptr_tag: 		/* this is nugatory - previous transforms
							 *				   make it into addptr or reff */
	{
		exp sum = son (e);
		int   ind = reg_operand (sum, sp);
		instore isa;
		isa.adval = 1;
		sum = bro (sum);
		if (name (sum) == val_tag) {
			instore isa;
			isa.b.base = ind;
			isa.b.offset = -no (e);
			setinsalt (aa, isa);
		}
		else {
			if (dreg == 0)
				dreg = getreg (sp.fixed);
			rrr_ins (i_subu, dreg, ind,
					 reg_operand (sum, guardreg (ind, sp)));
			isa.b.base = dreg;
			isa.b.offset = 0;
		}
		setinsalt (aa, isa);
		wans.answhere = aa;
		wans.ashwhere = a;
		keepexp (e, aa);
		return wans;
	}				/* end subptr */
	
    case reff_tag: {
		instore isa;
		
		wans = locate (son (e), sp, sh (son (e)), 0);
		/* answer is going to be wans displaced by no(e) */
		
		switch (wans.answhere.discrim) {
		case notinreg: {
			
			isa = insalt (wans.answhere);
			if (!isa.adval) {
				/* wans is an actual pointer  in store, so make it into a
				 *		   literal address.... */
				int   reg = getreg (sp.fixed);
				ls_ins (i_lw, reg, isa.b);
				isa.b.offset = 0;
				isa.b.base = reg;
				isa.adval = 1;
			}
			/* ... and add appropriate displacement to give result */
			isa.b.offset += no (e) / 8;
			setinsalt (wans.answhere, isa);
			keepexp (e, wans.answhere);
			break;
	    }
		case inreg: {
			/* wans is a pointer in a register */
			isa.b.base = regalt (wans.answhere);
			isa.adval = 1;
			isa.b.offset = no (e) / 8;
			setinsalt (wans.answhere, isa);
			break;
	    }
		default: {
			failer ("Locate ? reg ");
	    }
		}
		wans.ashwhere = a;
		return wans;
		
	}				/* end reff */
		
    case cont_tag:
    case contvol_tag:
	{
		exp s = son (e);
		ans ason;
		instore isa;
		int   reg;
		where fc;
		fc = locate (s, sp, sh (e), 0);
		ason = fc.answhere;
		/* answer is going to be the contents of address represented by fc
		 */
		
		switch (ason.discrim) {
		case notinreg:
	    {
			isa = insalt (ason);
			if (isa.adval) {	/* fc is a literal store address, so make
								 *				   it into a direct one */
				isa.adval = 0;
				setinsalt (aa, isa);
			}
			else {		/* fc is an actual pointer in store ....
						 */
				reg = getreg (sp.fixed);
				ls_ins (i_lw, reg, isa.b);
				/* .... so load it into reg and deliver direct base-offset
				 *		   (reg,0) */
				isa.b.base = reg;
				isa.b.offset = 0;
				setinsalt (aa, isa);
				if (name (e) != contvol_tag && fc.ashwhere.ashalign != 1)
					keepexp (e, aa);
			}
			goto breakson;
			
	    }			/* end notinrg */
		
		case inreg:
			/* this one is fraught - it depends on only being used in
			 *	       lh-value positions from vars- take care */
	    {
			isa.b.base = regalt (ason);
			isa.b.offset = 0;
			isa.adval = 1;
			setinsalt (aa, isa);
			/* fc is in register, so deliver literal(!?) base-offset */
			goto breakson;
	    }
		
		case infreg: 		/* ditto caveat above */
	    {
			aa = ason;
			goto breakson;
	    }
		
		default: {
			failer ("Locate ? reg");
	    }
		}
	  breakson:
		wans.answhere = aa;
		wans.ashwhere = a;
		return wans;
		
	}				/* end cont */
	
    case top_tag: 		/* does this ever happen ? */
	{
		setregalt (aa, 0);
		wans.answhere = aa;
		wans.ashwhere = a;
		return wans;
	}				/* end top */
	
	
	
    case field_tag: {
		instore isa;
		wans = locate (son (e), sp, sh (son (e)), 0);
		/* answer is wans displace literally by no(e); it should always be
		 *	   a literal store adress */
		
		switch (wans.answhere.discrim) {
		case notinreg: {
			
			isa = insalt (wans.answhere);
			isa.b.offset += no (e) / 8;
			setinsalt (wans.answhere, isa);
			break;
	    }
		default:
			failer (" field should be transformed ");
		}
		wans.ashwhere = a;
		return wans;
	}				/* end field */
		
		
		
		
		
		
		
    default:
		/* general catch all; evaluate e into register and deliver it as a
		 *         literal store address */
	{
		int   r = reg_operand (e, sp);
		instore is;
		if (r == 2) {		/* guard possible result from proc - can
							 *				   do better */
			r = getreg (sp.fixed);
			mon_ins (i_move, r, 2);
		}
		is.b.base = r;
		is.b.offset = 0;
		is.adval = 1;
		setinsalt (aa, is);
		wans.answhere = aa;
		wans.ashwhere = a;
		return wans;
	}
	
	}
}

where
locate(exp e, space sp, shape s, int dreg)
{
	ans ak;
	where w;
	ak = iskept (e);
	if (ak.discrim == inreg && (regalt (ak) == 0)) {
		where w;
		w = locate1 (e, sp, s, dreg);
		return w;
	}
	else {			/* e has been evaluated into a register */
		w.answhere = ak;
		w.ashwhere = ashof (s);
	}
	return w;
}
