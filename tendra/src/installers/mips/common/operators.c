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
 * Revision 1.4  1995/09/21  15:42:55  currie
 * silly reordering by as again
 *
 * Revision 1.3  1995/09/20  14:23:06  currie
 * callee-list blunder + fix for silliness in ultrix assembler
 *
 * Revision 1.2  1995/08/16  16:07:04  currie
 * Shortened some .h names
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
 ***********************************************************************/
/* operators.c
 *	produces code for common operations
 */


#include "config.h"
#include "code_here.h"
#include "expmacs.h"
#include "addrtypes.h"
#include "inst_fmt.h"
#include "move.h"
#include "maxminmacs.h"
#include "getregs.h"
#include "guard.h"
#include "tags.h"
#include "shapemacs.h"
#include "bitsmacs.h"
#include "common_types.h"
#include "mips_ins.h"
#include "operators.h"
#include "psu_ops.h"

bool testover = 0;		/* always 0 for C */

static void
tidyshort(int r, shape s, char* ins)
{/* corrects possible overflows of chars
  *				   and shorts in reg r */
	int sz = shape_size(s);
	if (sz == 32) return;
	if (!is_signed(s)) {
		rri_ins(i_and, r, r, (1<<sz)-1);
	}
	else
		if (ins == i_not || ins == i_nor) {
			rri_ins(i_sll, r, r, 32-sz);
			rri_ins(i_sra, r, r, 32-sz);
		}
}

bool
regremoved(exp * seq, int reg)
{
	/* given a list of expressions seq which
	 *				   contains one whose value is in
	 *				   register reg, removes that exp from seq
	 *				   and delivers 1; otherwise delivers 0 */
	exp s = *seq;
	exp t = bro (s);
	if (abs (regofval (s)) == reg) {
		(*seq) = t;
		return 1;
	}
	for (;;) {
		if (abs (regofval (t)) == reg) {
			bro (s) = bro (t);
			if (last (t))
				setlast (s);
			return 1;
		}
		if (last (t)) {
			return 0;
		}
		s = t;
		t = bro (t);
	}
}

void
do_comm(exp seq, space sp, int final, char *rins)
{
	/* evaluates the fixed operation seq1 rins
	 *				   seq 2 rins...., into reg final, using
	 *				   sp as free t-regs */
	int   r = 0;
	space nsp;
	int   a1;
	int   a2;
	
	a1 = reg_operand (seq, sp);
	/* evaluate 1st operand into a1 */
	for (;;) {
		nsp = guardreg (a1, sp);
		seq = bro (seq);
		if (name (seq) == val_tag) {/* next operand is a constant */
			if (last (seq)) {
				rri_ins (rins, final, a1, no (seq));
				return;
			}
			else {
				if (r == 0)
					r = getreg (sp.fixed);
				rri_ins (rins, r, a1, no (seq));
			}
		}
		else {
			exp sq = seq;
			char *ins = rins;
			a2 = reg_operand (sq, nsp);
			/* evaluate next operand */
			if (last (seq)) {
				rrr_ins (ins, final, a1, a2);
				return;
			}
			else {
				if (r == 0)
					r = getreg (sp.fixed);
				rrr_ins (ins, r, a1, a2);
			}
		}
		a1 = r;
	}
}


int
comm_op(exp e, space sp, where d, char *rrins)
{
	/* evaluate commutative operation rrins
	 *				   given by e into d, using sp to get
	 *				   t-regs */
	char *rins = rrins;
	
	
	switch (d.answhere.discrim) {
    case inreg:
	{
		int   dest = regalt (d.answhere);
		bool usesdest = regremoved (&son (e), dest);
		exp seq = son (e);
		/* the destination is in a register; take care that we dont alter
		 *	   it before possible use as an operand .... */
		if (usesdest && last (seq)) {
			/* ...it was used, but there is only one
			 *				   other operand */
			if (name (seq) == val_tag) {
				rri_ins (rins, dest, dest, no (seq));
			}
			else {
				rrr_ins (rins, dest, dest, reg_operand (seq, sp));
			}
			tidyshort (dest, sh (e), rins);
			return dest;
		}
		else
			if (usesdest) {	/* ... it was used so ... */
				int   r = getreg (sp.fixed);
				do_comm (seq, sp, r, rins);
				/* ... evaluate the remainder of the expression into r... */
				rrr_ins (rins, dest, dest, r);
				/* ... and do dest = dest rins r */
				tidyshort (dest, sh (e), rins);
				return dest;
			}
			else {		/* ... it wasn't used */
				do_comm (seq, sp, dest, rins);
				tidyshort (dest, sh (e), rins);
				return dest;
			}
	}				/* end inreg */
	
    default:
	{
		ans a;
		int   r = getreg (sp.fixed);
		space nsp;
        bool rok =1;
		setregalt (a, r);
		do_comm (son (e), sp, r, rins);
		/* evaluate the expression into r ... */
		if (d.answhere.discrim != notinreg) {
			tidyshort (r, sh (e), rins);
        } else rok = shape_size(sh(e))==32;
		nsp = guardreg (r, sp);
		move (a, d, nsp, 1);
		/* ... and move into a */
		return ((rok)?r:NOREG);
	}				/* notinreg */
	}				/* end switch */
}

int
non_comm_op(exp e, space sp, where dest, char *rins)
{
	/* evalate binary operation e with rins
	 *				   into dest */
	exp l = son (e);
	exp r = bro (l);
	int   a1 = reg_operand (l, sp);
	space nsp;
	int   a2;
	char *ins = rins;
	
	
	nsp = guardreg (a1, sp);
	a2 = reg_operand (r, nsp);
	/* regs a1 and a2 contain the operands */
	switch (dest.answhere.discrim) {
    case inreg: 		/* destination in register */
	{
		int   d = regalt (dest.answhere);
		rrr_ins (ins, d, a1, a2);
		tidyshort (d, sh (e), rins);
		return d;
	}
	
    default: 			/* destination elsewhere */
	{
		ans a;
		int   r1 = getreg (nsp.fixed);
        int rok = 1;
		setregalt (a, r1);
		rrr_ins (ins, r1, a1, a2);
		if (dest.answhere.discrim != notinreg){
			tidyshort (r1, sh (e), rins);
		} else rok = shape_size(sh(e))==32;
		nsp = guardreg (r1, sp);
		move (a, dest, nsp, 1);
		return (rok)?r1:NOREG;
	}
	}
}

int
monop(exp e, space sp, where dest, char *ins)
{
	/* evaluate fixed monadic operation e
	 *				   using ins into dest */
	int   r1 = getreg (sp.fixed);
	int   a1 = reg_operand (son (e), sp);
	/* operand in reg a1 */
	space nsp;
	switch (dest.answhere.discrim) {
    case inreg: 		/* destination in register */
	{
		int   d = regalt (dest.answhere);
		mon_ins (ins, d, a1);
		tidyshort (d, sh (e), ins);
		return d;
	}
	
    default: 			/* destination elsewhere */
	{
		ans a;
		int rok = 1;
		setregalt (a, r1);
		mon_ins (ins, r1, a1);
		if (dest.answhere.discrim != notinreg){
			tidyshort (r1, sh (e), ins);
		} else rok = shape_size(sh(e))==32;
		nsp = guardreg (r1, sp);
		move (a, dest, nsp, 1);
		return ((rok)?r1:NOREG);
	}
	}
}

int
fop(exp e, space sp, where dest, char *ins)
{
	/* evaluate floating dyadic operation e
	 *				   using ins into dest */
	exp l = son (e);
	exp r = bro (l);
	int   a1;
	space nsp;
	int   a2;
	freg fr;
	
	if (IsRev(e)) {
		a2 = freg_operand (r, sp);
		nsp = guardfreg (a2, sp);
		a1 = freg_operand(l, nsp);
	}
	else {
		a1 = freg_operand (l, sp);
		nsp = guardfreg (a1, sp);
		a2 = freg_operand(r, nsp);
	}
	
	if (!optop(e)) setnoreorder();
	
	switch (dest.answhere.discrim) {
    case infreg: 		/* dest in register */
	{
		fr = fregalt (dest.answhere);
		rrrfp_ins (ins, fr.fr << 1, a1 << 1, a2 << 1);
        break;
	}
    default: 			/* destinationelsewhere */
	{
		ans a;
		int   r1 = getfreg (nsp.flt);
		fr.fr = r1;
		fr.dble = (dest.ashwhere.ashsize == 64) ? 1 : 0;
		setfregalt (a, fr);
		rrrfp_ins (ins, r1 << 1, a1 << 1, a2 << 1);
		move (a, dest, sp, 1);
	}
	}
	if (!optop(e)) setreorder();
	return ((fr.dble) ? -(fr.fr + 32) : (fr.fr + 32));
}

int
fmop(exp e, space sp, where dest, char *ins)
{
	/* evaluate floating monadic operation e
	 *				   using ins into dest */
	int   a1 = freg_operand (son (e), sp);
	freg fr;
	if (!optop(e)) setnoreorder();
	switch (dest.answhere.discrim) {
    case infreg:
	{
		fr = fregalt (dest.answhere);
		rrfp_ins (ins, fr.fr << 1, a1 << 1);
        break;
	}
	
    default:
	{
		ans a;
		fr.fr = getfreg(sp.flt);
		fr.dble = (dest.ashwhere.ashsize == 64) ? 1 : 0;
		setfregalt (a, fr);
		rrfp_ins (ins, fr.fr << 1, a1 << 1);
		move (a, dest, sp, 1);
	}
	}
	if (!optop(e)) setreorder();
	return ((fr.dble) ? -(fr.fr + 32) : (fr.fr + 32));
}
