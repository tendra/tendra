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


/* 80x86/inlinechoice.c */

/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$
 *$Log$
 *Revision 1.2  2002/11/21 22:31:02  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.8  1996/12/04  17:58:36  pwe
 * correct to allow inlining at >1 location
 *
 * Revision 1.7  1995/09/28  12:45:17  pwe
 * tidy for tcc
 *
 * Revision 1.6  1995/08/04  08:29:20  pwe
 * 4.0 general procs implemented
 *
 * Revision 1.5  1995/02/22  13:34:31  pwe
 * no inline if application shape differs from return shape of proc
 *
 * Revision 1.4  1995/01/30  12:56:15  pwe
 * Ownership -> PWE, tidy banners
 *
 **********************************************************************/


#include "config.h"
#include "common_types.h"
#include "installglob.h"
#include "exp.h"
#include "expmacs.h"
#include "tags.h"
#include "flags.h"
#include "shapemacs.h"
#include "inl_norm.h"

#define crit_inline	300
#define crit_decs	5
#define crit_decsatapp	5
#define apply_cost      3

static int complexity(exp e, int count, int newdecs);
static last_new_decs = -999;

/*
 *    APPLY COMPLEXITY TO A LIST OF EXPRESSIONS
 */

int
sbl(exp e, int count, int newdecs)
{
    int c = complexity (e, count, newdecs);
    if (c < 0) return (c);
    if (last (e)) return (c);
    return (sbl (bro (e), c, newdecs));
}


/*
 *    FIND THE COMPLEXITY OF AN EXPRESSION
 *
 *    This routine examines the structure of e to see if its complexity
 *    (roughly the number of nodes) is greater than count.  As soon as the
 *    complexity exceeds this value it stops.  It returns the difference
 *    between count and the calculated complexity.
 */

static int
complexity(exp e, int count, int newdecs)
{
    unsigned char n = name (e);
	
    last_new_decs = newdecs;
	
    if (count < 0)
		return (-1);
    if (newdecs > crit_decs)
		return (-2);
    if (son (e) == nilexp)
		return (count);
	
    switch (n) {
		
	case apply_tag : {
	    if (newdecs > crit_decsatapp)
			return (-3);
	    return (sbl (son (e),  (count - apply_cost),
					 (newdecs + 1)));
	}
		
	case rep_tag : {
	    return (complexity (bro (son (e)),  (count - 1),
							(newdecs + 1)
					));
	}
		
	case res_tag : {
	    return (complexity (son (e),  (count + 1),
							newdecs));
	}
		
	case ident_tag : {
	    return (sbl (son (e),  (count - 1),
					 (newdecs + 1)));
	}
		
	case top_tag :
	case clear_tag :
	case val_tag : {
	    return (count);
	}
		
	case case_tag : {
	    return (complexity (son (e),  (count - 1),
							newdecs));
	}
		
	case name_tag :
	case string_tag :
	case env_offset_tag : {
	    return (count - 1);
	}
		
	case labst_tag : {
	    return (complexity (bro (son (e)), count, newdecs));
	}
		
	case solve_tag :
	case seq_tag :
	case cond_tag : {
	    return (sbl (son (e), count, newdecs));
	}
		
	default : {
	    return (sbl (son (e),  (count - 1), newdecs));
	}
    }
    /* NOT REACHED */
}


/* delivers 0 if no uses of this proc can be inlined.
 *   delivers 1 if this use cannot be inlined
 *   delivers 2 if this use can be inlined.
 */
int
inlinechoice(exp t, exp def, int total_uses)
{
	int res;
	
	exp apars;
	exp fpars;
	
	int newdecs = 0;
	int no_actuals;
	int max_complexity;
	
	int nparam;
	CONST  int CONST_BONUS_UNIT = 16;
	int const_param_bonus;
	int adjusted_max_complexity;
	
	shape shdef = pt(def) /* Oh, yes it is! */;
	
	if (!eq_shape(sh(father(t)), shdef)) {
		/* shape required by application is different from definition */
		return 1;
	}
	
	nparam = 0;
	const_param_bonus = 0;
	
	
	max_complexity = (crit_inline / total_uses);
	
#if issparc
	{
#define QQQ 2
		int i;
		if (total_uses >=(1<<QQQ))
		{
			for (i= total_uses >> QQQ ; i>0; i >>=1)
			{
				max_complexity *= 3;
				max_complexity /= 2;
			}
		}
#undef QQQ
	}
#endif
	
	if (max_complexity < 15) {
		max_complexity = 15;
	} else if (max_complexity > 120) {
		max_complexity = 120;
	}
	
	apars = bro(t); /* only uses are applications */
	no_actuals = last(t);		/* if so then apars is apply_tag... */
	fpars = son(def);
	
	for (;;) {
		if (name(fpars)!=ident_tag || !isparam(fpars)) {
			/* first beyond formals */
			if (!no_actuals)
				newdecs = 10;
			/* more actuals than formals, since last(apars)->break */
			break;
		}
		nparam++;
		
		switch (name(apars)) {
		case val_tag: case real_tag: case string_tag: case name_tag:
			break;
		case cont_tag: {
			if (name(son(apars))==name_tag && isvar(son(son(apars))) &&
				!isvar(fpars)) break;
		} /* ... else continue */
		default: newdecs++;
		}
		switch (name (apars))
		{
		case val_tag : {
			int n = no (apars);
			if (isbigval(apars)) break;
			
			/* Simple constant param. Increase desire to
			 *	   inline since a constant may cause further
			 *	   optimisation, eg strength reduction (mul
			 *	   to shift) or dead code savings */
			
#define IS_POW2(c)	((c) != 0 && ((c) & ((c) - 1)) == 0)
			
			if (0) {
				/* needs a register - poor */
				const_param_bonus += CONST_BONUS_UNIT / 4;
			} else if (n == 0 || (n > 0 && IS_POW2 (n))) {
				/* very good */
				const_param_bonus += CONST_BONUS_UNIT;
			} else {
				/* less good */
				const_param_bonus += CONST_BONUS_UNIT / 2;
			}
			break;
		}
			
#undef IS_POW2
			
		case real_tag :
			/* reals not that useful */
			const_param_bonus += CONST_BONUS_UNIT / 4;
			break;
			
		case string_tag :
		case name_tag :
			break;
			
		case cont_tag :
			if (name (son (apars)) == name_tag &&
				isvar (son (son (apars))) &&
				!isvar (fpars)) {
				break;
			}
			/* FALL THROUGH */
			
		default : {
			newdecs++;
			break;
		}
		}
		fpars = bro(son(fpars));
		if (last(apars)) break;
		apars = bro(apars);
	}
	
	adjusted_max_complexity = max_complexity;
	
	/* increase to up to 3 times (average around 2) according
	 *     to const params */
	if (nparam != 0) {
		adjusted_max_complexity +=
			(2 * max_complexity * const_param_bonus) /
			(CONST_BONUS_UNIT * nparam);
	}
	
	/* increase by number of instructions saved for call */
    adjusted_max_complexity += nparam - newdecs + 1;
	
	if ((complexity (fpars,  adjusted_max_complexity, newdecs)) >= 0)
		res = 2;
	else if (newdecs == 0)
		res = 0;
	else
		res = 1;
	
	
	return res;
	
}

