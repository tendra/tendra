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
 *	(1) Its Recipients shall ensure that this Notice is
 *	reproduced upon any copies or amended versions of it;
 *    
 *	(2) Any amended version of it shall be clearly marked to
 *	show both the nature of and the organisation responsible
 *	for the relevant amendment or amendments;
 *    
 *	(3) Its onward transfer from a recipient to another
 *	party shall be deemed to be that party's acceptance of
 *	these conditions;
 *    
 *	(4) DERA gives no warranty or assurance as to its
 *	quality or suitability for any purpose and DERA accepts
 *	no liability whatsoever in relation to any use to which
 *	it may be put.
 *
 * $TenDRA$
 */


/*
 *$Log$
 *Revision 1.2  2002/11/21 22:31:07  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:10:58  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.2  1995/10/09  13:06:48  wfs
 * Cosmetic changes.
 *
 * Revision 5.1  1995/09/25  09:44:17  wfs
 * *** empty log message ***
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.5  1995/08/25  09:10:21  wfs
 * *** empty log message ***
 *
 * Revision 3.5  1995/08/25  09:10:21  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  09:04:24  wfs
 * internal register synonyms changed to be closer to the hppa's
 * register names
 *
 * Revision 3.1  95/04/10  16:25:50  16:25:50  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:14:28  11:14:28  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:25:17  15:25:17  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.2  95/01/17  17:20:33  17:20:33  wfs (William Simmonds)
 * Changed name of an included header file.
 * 
 * Revision 1.1  95/01/11  13:02:40  13:02:40  wfs (William Simmonds)
 * Initial revision
 * 
 */


#define HPPATRANS_CODE
/******************************************************************
 *		code_here
 *
 *This contains procedures :-
 *
 *regofval, fregofval : to see if an exp is a load_tag that has been allocated to a register.
 *
 *regoperand, freoperand : to evaluate an exp into a register using make_code
 *
 *code_here :  calls make_code and ensures that any internal exit labels are tied up after the call
 *
 *
 *	The procedures regoperand and fregoperand evaluate their
 *exp parameter into a single register using make_code. This register is
 *returned. An initial test with regofval checks to see if the exp is already
 *in a register.

******************************************************************/


#include "config.h"
#include "myassert.h"
#include "common_types.h"
#include "addrtypes.h"
#include "proctypes.h"
#include "labels.h"
#include "expmacs.h"
#include "tags.h"
#include "makecode.h"
#include "exp.h"
#include "bitsmacs.h"
#include "locate.h"
#include "regexps.h"
#include "regmacs.h"
#include "inst_fmt.h"
#include "hppains.h"
#include "shapemacs.h"
#include "special.h"
#include "regable.h"
#include "guard.h"
#include "move.h"
#include "comment.h"

#include "codehere.h"


/*********************************************************************
 *regofval
 *The procedure regofval checks to see if an exp is a load_tag
 *that has been allocated into a fixpnt register and if so return it or else R_NO_REG.
 *********************************************************************/
int
regofval(exp e)
{
	exp dc = son(e);
	
	if (name(e) == name_tag && name(dc) == ident_tag)	/* ident tag */
	{
		if ((props(dc) & defer_bit) != 0)
		{
			return regofval(son(dc));
		}
		if ((props(dc) & inreg_bits) != 0)
		{
			return ((isvar(dc)) ? (-no(dc)) : (no(dc)));
		}
		return R_NO_REG;
	}
	else if ((name(e) == val_tag && no(e) == 0) 
#if 0
			 || name(e) == clear_tag || name(e)== top_tag 
#endif
		)
	{
		return 0;
	}
	else
	{
		return R_NO_REG;
	}
}

int
fregofval(exp e)
{
	exp dc = son(e);
	
	if (name(e) == name_tag && name(dc) == ident_tag)
	{
		if ((props(dc) & infreg_bits) != 0)
		{
			return no(dc);
		}
		return R_NO_REG;
	}
	else
	{
		return R_NO_REG;
	}
}


/* calls make_code and tie up any internal exit labels */
static int
make_code_here(exp e, space sp, where dest)
{
	makeans mka;
	
	mka = make_code(e, sp, dest, 0);
	if (mka.lab != 0)
	{
		clear_all();
		outlab("L$$",mka.lab);
	}
	return mka.regmove;
}


/* return reg if 'e' e can easily go to one reg only */
static int
is_reg_operand(exp e, space sp)
{
	int x = regofval(e);
	ans aa;
	
	if (x >= 0 && x < R_NO_REG)
		return x;			/* x is a register for e */
	
	if (name(e) == cont_tag)
	{
		x = regofval(son(e));
		if (x < 0)
			return (-x);
	}
	
	aa = iskept(e);
	
	if (discrim (aa) == inreg && regalt(aa) != 0)
	{				/* the same expression has already been
					 * evaluated into a reg */
		return regalt(aa);
	}
	
	if (discrim (aa) == notinreg)
	{
		instore is;
		
		is = insalt(aa);
		if (is.adval && is.b.offset == 0)
		{
			int r = is.b.base;
			
			/* the same expression has already been evaluated into a reg */
			return r;
		}
	}
	
	return R_NO_REG;		/* exprssion can go to many regs just as
							 * easily */
}


int
reg_operand(exp e, space sp)
{
	int reg;
	
	reg = is_reg_operand(e, sp);
	
	if (reg == R_NO_REG || reg == GR0)
	{
		/* allow make_code_here to evaluate e into reg of its choice */
		ans aa;
		where w;
		
		reg = -1;
		setsomeregalt(aa, &reg);
		w.answhere = aa;
		w.ashwhere = ashof(sh(e));
		make_code_here(e, sp, w);
		assert(reg!=-1);
		keepreg(e, reg);
		return reg;
	}
	else
	{
		/* e was found easily in a reg */
		assert(IS_FIXREG(reg));
		return reg;
	}
}

/* like reg_operand(), but to specified reg */
void
reg_operand_here(exp e, space sp, int this_reg)
{
	int reg;
	
	assert(IS_FIXREG(this_reg) && this_reg != GR0);	/* variable fix reg */
	
	
	reg = is_reg_operand(e, sp);
	
	if (reg == R_NO_REG || reg == GR0)
	{
		/* evaluate to this_reg */
		
		where w;
		
		w.ashwhere = ashof(sh(e));
		setregalt(w.answhere, this_reg);
		make_code_here(e, sp, w);
	}
	else
	{
		/* e was found easily in a reg, move to this_reg if needed */
		assert(IS_FIXREG(reg));
		
		if (reg != this_reg)
			rr_ins(i_copy,reg,this_reg);
	}
	
	keepreg(e, this_reg);
}


int
freg_operand(exp e, space sp, int reg)
{
	int x = fregofval(e);
	ans aa;
	where w;
	freg fr;
	
	w.ashwhere = ashof(sh(e));
	fr.dble = (w.ashwhere.ashsize == 64) ? 1 : 0;
	
	if (x >= 0 && x < R_NO_REG)
	{
		return x;
	}
	
	if (name(e) == cont_tag)
	{
		x = fregofval(son(e));
		if (x < R_NO_REG)
		{
			return (x);
		}
	}
	else if (name(e) == apply_tag)
	{
		fr.fr = R_FR4;
		setfregalt(aa, fr);
		comment("freg_operand: call of float point result proc");
		w.answhere = aa;
		/* w.ashwhere already correctly set up above */
		make_code(e, sp, w, 0);
		return R_FR4;   /* float point proc calls give result in %fr4 */
	}
	
	aa = iskept(e);
	if (discrim (aa) == infreg)
	{
		/* e already evaluated in fl reg */
		return regalt(aa) /* cheat */;
	}
	
	fr.fr = reg;
	setfregalt(aa, fr);
	w.answhere = aa;
	make_code_here(e, sp, w);
	keepexp(e, aa);
	return reg;
}



/*
 * The procedure code_here calls make_code and ensures that
 * any internal exit labels are tied up after the call.
 * Optimises the case where the value of 'e' is in a register.
 */
int
code_here(exp e, space sp, where dest)
{
	int reg;
	
	
	reg = is_reg_operand(e, sp);
	
	
	if (reg == R_NO_REG || reg == GR0)
	{
		return make_code_here(e, sp, dest);
	}
	else
	{
		/* +++ do in make_code maybe */
		/* +++ for reals as well */
		/* e was found easily in a reg */
		ans aa;
		
		assert(IS_FIXREG(reg));
		assert(ashof(sh(e)).ashsize <= 32);
		
		setregalt(aa, reg);
		move(aa, dest, guardreg(reg, sp).fixed, 1);
		
		return reg;
	}
}


















