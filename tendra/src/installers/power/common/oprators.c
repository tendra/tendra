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
 * Revision 1.2  1998/02/04  15:49:01  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1996/11/18  15:50:25  pwe
 * correct alias with bitfields, and case odds
 *
 * Revision 1.2  1996/10/04  16:03:10  pwe
 * add banners and mod for PWE ownership
 *
 **********************************************************************/


#include "config.h"
#include "myassert.h"
#include "memtdf.h"
#include "codegen.h"
#include "geninst.h"
#include "maxminmacs.h"		/* for absval() */
#include "flags.h"
#include "instruct.h"
#include "proc.h"
#include "oprators.h"
#include "comment.h"
#include "makecode.h"
#include "error.h"

void
tidyshort(int r, exp e)
{
	shape s = sh(e);
	switch (name(e))
	{
	case and_tag:
    {
		exp r = bro(son(e));/* could be a val_tag */
		if (name(s)==ucharhd && name(r)==val_tag && ((no(r) & 0xff) == no(r)))
		{
			return;
		}
		if (name(s)==uwordhd && name(r)==val_tag && ((no(r) & 0xffff) == no(r)))
		{
			return;
		}
    }
	}
	
	if (name(s) == ucharhd)
	{
		rir_ins(i_and, r, 255, r);
	}
	else if (name(s) == uwordhd)
	{
		rir_ins(i_and, r, 0xffff, r);
	}
}


/*
 * given a list of expressions seq which contains one whose value is in
 * register reg, removes that exp from seq and delivers 1; otherwise delivers 0
 */
bool
regremoved(exp * seq, int reg)
{
	exp s = *seq;
	exp t = bro(s);
	
	if (absval(regofval(s)) == reg)
	{
		(*seq) = t;
		return 1;
	}
	for (;;)
	{
		if (absval(regofval(t)) == reg)
		{
			bro(s) = bro(t);
			if (last(t))
				setlast(s);
			return 1;
		}
		if (last(t))
		{
			return 0;
		}
		s = t;
		t = bro(t);
	}
}


/*
 * evaluates the fixed operation seq1 rins seq 2 rins...., into reg final,
 * using sp as free t-regs
 */
void
do_comm(exp seq, space sp, int final, Instruction_P rins)
{
	int r = 0;
	space nsp;
	int a1;
	int a2;
	
	/* should have been optimised in scan... */
	ASSERT(!(rins == i_a && name(seq) == neg_tag && name(bro(seq)) != val_tag));
	
	/* evaluate 1st operand into a1 */
	a1 = reg_operand(seq, sp);
	
	for (;;)
	{
		nsp = guardreg(a1, sp);
		seq = bro(seq);
		if (name(seq) == val_tag)	/* next operand is a constant */
		{
			if (last(seq))
			{
				rir_ins(rins, a1, no(seq), final);
				return;
			}
			else
			{
				if (r == 0)
					r = getreg(sp.fixed);
				rir_ins(rins, a1, no(seq), r);
			}
		}
		else
		{
			exp sq = seq;
			Instruction_P ins = rins;
			
			a2 = reg_operand(sq, nsp);
			/* evaluate next operand */
			if (last(seq))
			{
				rrr_ins(ins, a1, a2, final);
				return;
			}
			else
			{
				if (r == 0)
					r = getreg(sp.fixed);
				rrr_ins(ins, a1, a2, r);
			}
		}
		a1 = r;
	}
}


/*
 * Evaluate commutative operation rrins given by e into d,
 * using sp to get t-regs 
 */
int
comm_op(exp e, space sp, where d, Instruction_P rrins)
{
	Instruction_P rins = rrins;
	
	switch (d.answhere.discrim)
	{
	case inreg:
    {
		int dest = regalt(d.answhere);
		bool usesdest = regremoved(&son(e), dest);
		exp seq = son(e);
		
		/*
		 * the destination is in a register; take care that we don't alter it
		 * before possible use as an operand ....
		 */
		if (usesdest && last(seq))
		{
			/* used, but there is only one other operand */
			if (name(seq) == val_tag)
			{
				rir_ins(rins, dest, no(seq), dest);
			}
			else
			{
				rrr_ins(rins, dest, reg_operand(seq, sp), dest);
			}
			tidyshort(dest, e);
			return dest;
		}
		else if (usesdest)
		{
			/* dest used, use temp */
			int r = getreg(sp.fixed);
			
			do_comm(seq, sp, r, rins);
			rrr_ins(rins, dest, r, dest);
			tidyshort(dest, e);
			return dest;
		}
		else
		{
			/* dest not used, evaluate into dest */
			do_comm(seq, sp, dest, rins);
			tidyshort(dest, e);
			return dest;
		}
    }				/* end inreg */
	default:
    {
		ans a;
		int r = getreg(sp.fixed);
		space nsp;
		bool rok =1;
		setregalt(a, r);
		do_comm(son(e), sp, r, rins);
		/* evaluate the expression into r ... */
		if (d.answhere.discrim != notinreg) { 
			tidyshort (r, e);
		} 
		else 
			rok = shape_size(sh(e))==32;
		nsp = guardreg(r, sp);
		move(a, d, nsp.fixed, 1);
		/* ... and move into a */
		return ((rok)?r:NOREG);
    }				/* notinreg */
	}				/* end switch */
}

/* evalate binary operation e with ins into dest */
int
non_comm_op(exp e, space sp, where dest, Instruction_P ins)
{
	exp l = son(e);
	exp r = bro(l);
	bool sf_imm = name(l) == val_tag && ins == i_s && IMM_SIZE(no(l));
	/* we can use sfi instruction */
	int a1;
	int a2;
	space nsp;
	
	switch (dest.answhere.discrim)
	{
	case inreg:
    {
		int d = regalt(dest.answhere);
		
		if (sf_imm)
		{
			rir_ins(i_sf, reg_operand(r, sp), no(l), d);
		}
		else
		{
			a1 = reg_operand(l, sp);
			nsp = guardreg(a1, sp);
			a2 = reg_operand(r, nsp);
			rrr_ins(ins, a1, a2, d);
		}
		
		tidyshort(d, e);
		return d;
    }
	
	default:			/* destination elsewhere */
    {
		ans a;
		int r1 = getreg(sp.fixed);
		
		setregalt(a, r1);
		
		if (sf_imm)
		{
			rir_ins(i_sf, reg_operand(r, sp), no(l), r1);
		}
		else
		{
			a1 = reg_operand(l, sp);
			nsp = guardreg(a1, sp);
			a2 = reg_operand(r, nsp);
			rrr_ins(ins, a1, a2, r1);
		}
		
		tidyshort(r1, e);
		nsp = guardreg(r1, sp);
		move(a, dest, nsp.fixed, 1);
		return r1;
    }
	}
}

/* evaluate floating dyadic operation e using ins into dest */
int
fop(exp e, space sp, where dest, Instruction_P ins)
{
	exp l = son(e);
	exp r = bro(l);
	int a1;
	int a2;
	space nsp;
	
	if (IsRev(e))
	{
		a2 = freg_operand(r, sp, getfreg(sp.flt));
		nsp = guardfreg(a2, sp);
		a1 = freg_operand(l, nsp, getfreg(nsp.flt));
	}
	else
	{
		a1 = freg_operand(l, sp, getfreg(sp.flt));
		nsp = guardfreg(a1, sp);
		a2 = freg_operand(r, nsp, getfreg(nsp.flt));
	}
	
	switch (dest.answhere.discrim)
	{
	case infreg:			/* dest in register */
    {
		freg fr;
		
		fr = fregalt(dest.answhere);
		if (ERROR_TREATMENT(e))
		{
			do_fop_error_jump(e,a1,a2,fr.fr);/* Floating point error jump */
		}
		else
		{
			rrrf_ins(ins, a1, a2, fr.fr);
		}
		if (fr.dble==0 && round_after_flop)
		{
			rrf_ins(i_frsp,fr.fr,fr.fr);
		}   
		return ((fr.dble) ? -(fr.fr + 32) : (fr.fr + 32));
    }
	default:			/* destination elsewhere */
    {
		ans a;
		freg fr;
		int r1 = getfreg(nsp.flt);
		
		fr.fr = r1;
		fr.dble = (dest.ashwhere.ashsize == 64) ? 1 : 0;
		setfregalt(a, fr);
		if (ERROR_TREATMENT(e))
		{
			do_fop_error_jump(e,a1,a2,fr.fr);/* Floating point error jump */
		}
		else
		{
			rrrf_ins(ins, a1, a2, r1);
		}
		if (fr.dble==0 && round_after_flop)
		{
			rrf_ins(i_frsp,r1,r1);
		}   
		move(a, dest, sp.fixed, 1);
		return ((fr.dble) ? -(fr.fr + 32) : (fr.fr + 32));
    }
	}
}

/* evaluate floating monadic operation e using ins into dest */
int
fmop(exp e, space sp, where dest, Instruction_P ins)
{
	int a1 = freg_operand(son(e), sp, getfreg(sp.flt));
	
	switch (dest.answhere.discrim)
	{
	case infreg:
    {
		freg fr;
		
		fr = fregalt(dest.answhere);
		if (ERROR_TREATMENT(e))
		{
			do_fmop_error_jump(e,a1,fr.fr);
		}
		else
		{
			rrf_ins(ins, a1, fr.fr);
		}
		if (fr.dble==0 && round_after_flop)
		{
			rrf_ins(i_frsp,fr.fr,fr.fr);
		}
		return ((fr.dble) ? -(fr.fr + 32) : (fr.fr + 32));
    }
	
	default:
    {
		ans a;
		freg fr;
		
		fr.fr = getfreg(sp.flt);
		fr.dble = (dest.ashwhere.ashsize == 64) ? 1 : 0;
		setfregalt(a, fr);
		if (ERROR_TREATMENT(e))
		{
			do_fmop_error_jump(e,a1,fr.fr);
		}
		else
		{
			rrf_ins(ins, a1, fr.fr);      
		}
		if (fr.dble==0 && round_after_flop)
		{
			rrf_ins(i_frsp,fr.fr,fr.fr);
		}      
		move(a, dest, sp.fixed, 1);
		return ((fr.dble) ? -(fr.fr + 32) : (fr.fr + 32));
    }
	}
}
