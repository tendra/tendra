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
 * Revision 1.2  1998/02/04  15:49:11  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:58  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:04:47  pwe
 * add banners and mod for PWE ownership
 *
 **********************************************************************/


#include "config.h"
#include "tags.h"
#include "common_types.h"
#include "exp.h"
#include "const.h"
#include "expmacs.h"
#include "bitsmacs.h"
#include "regable.h"
#include "tempdecs.h"
#include "regmacs.h"
#include "myassert.h"

/* to go in a switch as in case CASE_APPLYLIKE: */
#define	CASE_APPLYLIKE	apply_tag: case round_tag:case apply_general_tag


bool tempdecopt;	/* flag to allow this optimisation, set in main() */
static int nouses;
static bool useinpar;
static int param_uses(exp);
static int locate_param(exp);

bool
APPLYLIKE(exp e)
{
	if (name(e)==apply_tag)
		return 1;
	if (name(e)==apply_general_tag)
		return 1;
	if (name(e)==round_tag)
		if (name(sh(e))==ulonghd||architecture!=POWERPC_CODE)
			return 1;
	return 0;
}
/* RETURNS_R_RESULT returns 1 if the exp returns R_RESULT when evaluated */
bool
RETURNS_R_RESULT(exp e)
{
	if (name(e)==apply_tag && valregable(sh(e)))
	{
		return 1;
	}
	if (name(e)==apply_general_tag && valregable(sh(e)))
	{
		return 1;
	}
	if (name(e)==round_tag)
	{
		if (name(sh(e))==ulonghd||architecture!=POWERPC_CODE)
			return 1;
	}
	return 0;
}
/* RETURNS_FR_RESULT returns 1 if the exp returns FR_RESULT when evaluated */
bool
RETURNS_FR_RESULT(exp e)
{
	if (name(e)==apply_tag && is_floating(name(sh(e))))
	{
		return 1;
	}
	if (name(e)==apply_general_tag && is_floating(name(sh(e))))
	{
		return 1;
	}
	return 0;
}


int
trace_uses(exp e, exp id)
{
	/*
	 * reduces nouses for each non-assignment use of id encountered in e; sets
	 * useinpar if use in actual parameter (or function) posn terminates with 0 on
	 * applications or jumps terminates with 2 on assignment to id otherwise
	 * delivers 1
	 * 0 is returned if trace_uses runs into a dead end 
	 * 2 is returned if trace_uses runs into another assignment
	 * 1 is returned if still searching ok so as soon as 0 or 2 is returned 
	 * the recursion ends quickly
	 */
	
	if (APPLYLIKE(e))
	{
		/* u is nouses before we start to scan the parameters */
		int u = nouses;
		int p = 1;
		exp l = son(e);
		
		while (p == 1)
		{
			p = trace_uses(l, id);
			if (u != nouses || p == 2)
			{
				/* We found a use of the ident or we found an assignment to it */
				useinpar = 1;
			}
			
			if (p == 0)
				nouses = u;
			if (last(l))
				break;
			l = bro(l);
		}
		return 0;
	}
	
	switch (name(e))
	{
	case caller_name_tag:
	case env_offset_tag:
	case general_env_offset_tag:
		/* Don't want to look at sons of these tags */
		return 1;
	case name_tag:
    {
		nouses -= (son(e) == id);
		return (1);
    }
	
	case ident_tag:
    {
		exp f = son(e);
		exp s = bro(f);
		int a;
		
		if ((props(e) & defer_bit) != 0)
		{
			exp t = f;
			
			f = s;
			s = t;
		}
		a = trace_uses(f, id);
		if (a != 1)
			return a;
		return trace_uses(s, id);
    }
	case case_tag:
    {
		trace_uses(son(e), id);
		return 0;
    }
	
	case labst_tag:
		return 0;
		
	case cond_tag:
    {
		int el;
		
		/* Cond tags are not treated like the default since we know 
		 *	 that the first argument will be coded first */
		el = trace_uses(son(e),id);
		if (el != 1)
		{
			return el;
		}
		return 0;
    }
	case seq_tag:
    {
		exp s = son(son(e));
		
		for (;;)
		{
			int el = trace_uses(s, id);
			
			if (el != 1)
				return el;
			if (last(s))
				return trace_uses(bro(son(e)), id);
			s = bro(s);
		}
    }
    
	case ass_tag:
    {
		if (isvar(id) && name(son(e)) == name_tag && son(son(e)) == id)
		{
			trace_uses(bro(son(e)), id);
			return 2;
		}
		else if (APPLYLIKE(bro(son(e))))
		{
			return trace_uses(bro(son(e)), id);
		}
		/* else cont to next case */
    }
	default:
    {
		exp s = son(e);
		int nu = nouses;
		int bad_arguments = 0; 
		/* A bad argument is one which contains an assignment or something to stop flow */
		int good_arguments = 0;
		/* A good_argument is one which contains one or more uses of id, but doesn't have
		 *	 any assignments or things to stop flow */
		int ret_value = 0;
		
		if (s==nilexp)
		{
			/*no arguments */
			return 1;
		}
		for (;;)
		{
			int monitor_uses;
			int el; 
			monitor_uses = nouses;
			el = trace_uses(s, id);
			if (el==1  && nouses < monitor_uses)
			{
				/* argument with uses of ident*/
				good_arguments ++;
			}
			if (el != 1)
			{	
				/* An argument corrupts the flow */
				bad_arguments++;
				ret_value = el;
			}
			if (last(s))
				break;
			s = bro(s);
		}
		if (bad_arguments==0)
		{
			return 1;
			/* No problems */
		}
		
		if (bad_arguments==1 && good_arguments==0)
		{
			/* one bad one */
			/* all the rest don't use it */
			return ret_value;
		}
		nouses = nu;
		return ret_value;
    }
	}
}


void
after_a(exp a, exp id)
{
	/* apply trace_uses to dynamic successors of a */
	exp dad;
	exp l;
	
  tailrecurse:
	dad = father(a);
	if (nouses == 0)
		return;
	if (name(dad) == cond_tag || name(dad) == rep_tag
		|| name(dad) == solve_tag || name(dad) == labst_tag
		|| name(dad) == case_tag || name(dad) == goto_tag
		|| name(dad) == test_tag || APPLYLIKE(dad))
	{
		/* dont try too hard ! */
		while (APPLYLIKE(dad) && dad != id)
			dad = father(dad);
		if (APPLYLIKE(dad))
		{
			useinpar = 1;
		}
		return;
	}
	
	
	for (l = a; !last(l); l = bro(l))
	{
		int u = trace_uses(bro(l), id);
		
		if (u != 1 || nouses == 0)
			return;
	}
	a = dad;
	if (dad != id)
		goto tailrecurse;
}
bool
simple_seq(exp e, exp id)
{
#if 0
	exp dad = father(e);
	
	for (;;)
	{
		if (dad == id)
			return 1;
		if (name(dad) == seq_tag || name(dad) == 0
			|| name(dad) == ident_tag)
		{
			dad = father(dad);
		}
		else
			return 0;
	}
#else
	return 1;
#endif
}

int
tempdec(exp e, bool enoughs)
{
	/*
	 * e is a local declaration; 'enoughs' is a misnomer to say whether there
	 * are t-regs available delivers 1 if e can be allocated into t-reg or par
	 * reg
	 */
	exp p;
	
	if (!tempdecopt)
		return 0;
	
	nouses = 0;
	useinpar = 0;
	
	if (isvar(e))
	{
		for (p = pt(e); p != nilexp; p = pt(p))
		{
			/* find no of uses which are not assignments to id ... */
			if (!last(p) && last(bro(p))
				&& name(bro(bro(p))) == ass_tag)
			{
				if (!simple_seq(bro(bro(p)), e))
					return 0;
				continue;
			}
			nouses++;
		}
	}
	else
		nouses = no(e);
	
	/*
	 * trace simple successors to assignmnts or init to id to find if all uses
	 * occur before unpredictable change of control (or another assignment to
	 * id)
	 */
	
	if (name(son(e)) != clear_tag || isparam(e))
	{
		after_a(son(e), e);
	}
	
	if (isvar(e))
	{
		for (p = pt(e); p != nilexp; p = pt(p))
		{
			if (!last(p) && last(bro(p))
				&& name(bro(bro(p))) == ass_tag)
			{
				after_a(bro(bro(p)), e);
			}
		}
	}
	
	if (nouses == 0 && (enoughs || !useinpar))
	{
		if (useinpar)
		{
			/* See if it can be allocated into a parameter register */
			props(e) |= notparreg;
			if (isparam(e))
			{
				return param_uses(e);
			}
			else 
				return 100;
		}
		return 100;
	}
	return 0;
}
static int
param_uses(exp id)
{
	exp p;
	ASSERT(isparam(id));
	ASSERT(useinpar);
	ASSERT(nouses==0);
	/* We found all the uses of the ident and we found one of them in a parameter list */
	
	for (p=pt(id) ; p!=nilexp;p = pt(p))
	{
		if (APPLYLIKE(father(p)))
		{
			return locate_param(p);
		}
	}
	/* not a simple use in a parameter list */
	return 100;
}
static int
locate_param(exp e)
{
	exp f = father(e);
	bool is_float = is_floating(name(sh(e)));
	exp par;
	
	
	ASSERT(APPLYLIKE(f));
	switch (name(f))
	{
	case apply_general_tag:
		par =  son(bro(son(f))); 
		break;
	case apply_tag:
		par = bro(son(f));
		break;
	case round_tag:
		par = son(f);
		break;
	default:
		return 0;
	}
	{
		int fxparam = R_FIRST_PARAM;
		int flparam = FR_FIRST_PARAM;
		int stparam = 0;
		
		for (;;)
		{
			int par_size = shape_size(sh(par));
			
			if (par==e)
			{
				/* We have found it */
				if (is_float)
				{
					if (flparam>FR_LAST_PARAM)
						return 0;
					else
						return flparam;
				}
				else
				{
					if (fxparam>end_param)
						return 0;
					else
						return fxparam;
				}
			}
			stparam = ALIGNNEXT(stparam + par_size,32);
			fxparam = (stparam/32) + R_FIRST_PARAM;
			if (is_floating(name(sh(par))))
			{
				flparam++;
			}
			if (last(par))
				break;
			par = bro(par);
		}
		return 0;
	}
}  






