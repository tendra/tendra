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
 *Revision 1.3  2002/11/21 22:31:07  nonce
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
 *Revision 1.1  2002/01/26 21:31:22  asmodai
 *Initial version of TenDRA 4.1.2.
 
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:12:46  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  10:41:19  wfs
 * A few refinements necessary for 3.1 and 4.0 compatibility.
 *
 * Revision 3.4  1995/08/25  10:41:19  wfs
 * A few refinements necessary for 3.1 and 4.0 compatibility.
 *
 * Revision 3.1  95/04/10  16:28:41  16:28:41  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:19:16  11:19:16  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:29:06  15:29:06  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:19:42  13:19:42  wfs (William Simmonds)
 * Initial revision
 * 
 */


#define HPPATRANS_CODE
/******************************************************************
 *		weights.c
 *
 *	The main procedure here is weightsv which determines
 *the allocation of s regs. It considers which of those tags not already
 *allocated to a t reg by scan, are best put in an s register. The same
 *conditions as for t regs apply as to the suitability of the tags for registers.
 *Weights estimates the usage of each tag and hence the amount that would
 *be saved if it were held in an s reg. Thus it computes break points for
 *register allocation for later use by reg_alloc.
 *	The type weights consists of two arrays of integers. In the first
 *array each integer corresponds to a fixpnt reg and the second arrays'
 *integers correspond to floating point regs.
 *	At the end of a call of weights on an ident exp the props field
 *of the ident may still contain inreg_bits or infreg_bits, set by scan, to
 *indicate that a t reg should be used. Otherwise number of ident is set up to
 *represent the break point for allocation. A similar process occurs for
 *proc parameters which have the break value in the forweights field
 *of the parapair of the corresponding procrec. This value has three
 *meanings:
 *	1) The ident (or parameter) defines a fixpnt value and number
 *of ident (forweights of parpair) is an integer brk with the interpretation
 *that if there are at least brk fixpt s registers unallocated at this point then
 *one will be used for this tag (parameter).
 *	2) As 1 but for floating point values.
 *	3) number of ident = 100 in which case allocate value on the
 *stack, (this is obviously always available for parameters).

******************************************************************/


#include "config.h"
#include "exptypes.h"
#include "expmacs.h"
#include "codetypes.h"
#include "installtypes.h"
#include "const.h"
#include "exp.h"
#include "tags.h"
#include "common_types.h"
#include "proctypes.h"
#include "procrec.h"
#include "bitsmacs.h"
#include "maxminmacs.h"
#include "regable.h"
#include "comment.h"
#include "shapemacs.h"
#include "special.h"
#include "weights.h"



weights zeroweights =
{{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
},
 {
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 }
};

/* NB scale, throughout,  should be a float but mips cc V2.10 compiles calls and
 *		proc body inconsistently !! */

weights weightsv(double, exp) ;

weights
add_weights(weights * w1, weights * w2)
{
	/* sum of weights */
	weights r;
	long i;
	
	for (i = 0; i < wfixno; ++i)
	{
		(r.fix)[i] = (w1->fix)[i] + (w2->fix)[i];
	};
	for (i = 0; i < wfloatno; ++i)
	{
		(r.floating)[i] = (w1->floating)[i] + (w2->floating)[i];
	};
	return (r);
}

wp
max_weights(double loc, weights * ws, bool fix)
{
	
	/*
	 * loc is the usage count of a tag, ws is the weights computed for the scope
	 * of the tag and fix distinguishes between fix and float. This computes the
	 * weights for the declaration and a break point for register allocation
	 * which gives the number of available regs for which it is worthwhile to
	 * allocate this tag into a reg ("regged"). This proc is the source of all
	 * non-zero weights. NB loc may be negative since using a s-reg will involve
	 * a dump and restore
	 */
	long bk = wfixno + 1;
	long i;
	float *w = (ws->fix);
	/* w[i] = greatest usage of (i+1) inner fixed tags  */
	wp res;
	float *pw = &(((res.wp_weights).fix)[0]);
	
	if (fix)
	{
		for (i = 0; i < wfixno; ++i)
		{
			if (i == 0)
			{
				if (loc > w[i])
				{
					/* this tag has higher usage than any inner one ... */
					pw[i] = loc;
					bk = i;		/* ... so it's regged in pref to others */
				}
				else
					pw[i] = w[i];
			}
			else
			{
				if ((loc + w[i - 1]) > w[i])
				{
					
					/*
					 * this tag and i inner ones have higher usage than any other (i+1)
					 * inner ones ...
					 */
					pw[i] = loc + w[i - 1];
					if (i < bk)
						bk = i;
					
					/*
					 * ... so it and i inner ones are regged in preference to any other
					 * (i+1) inner ones
					 */
				}
				else
					pw[i] = w[i];
			};
		};
		
		res.fix_break = bk;
	}
	else
	{
		for (i = 0; i < wfixno; ++i)
		{
			pw[i] = w[i];
		}
	}
	
#if NO_SREG
	res.fix_break = wfixno + 1;
#else
	res.fix_break = bk;
#endif
	
	bk = wfloatno + 1;
	w = (ws->floating);
	pw = &(((res.wp_weights).floating)[0]);
	if (!fix)
	{				/* same algorithm for float regs as fixed regs */
		for (i = 0; i < wfloatno; ++i)
		{
			if (i == 0)
			{
				if (loc > w[i])
				{
					pw[i] = loc;
					bk = i;
				}
				else
					pw[i] = w[i];
			}
			else
			{
				if ((loc + w[i - 1]) > w[i])
				{
					pw[i] = loc + w[i - 1];
					if (i < bk)
						bk = i;
				}
				else
					pw[i] = w[i];
			};
		};
	}
	else
	{
		for (i = 0; i < wfloatno; ++i)
		{
			pw[i] = w[i];
		}
	}
	
	res.float_break = bk;
	return res;
}

weights
mult_weights(double m, weights * ws)
{
	
	/*
	 * multiply weights by scalar - non overflowing
	 */
	weights res;
	float *r = &(res.fix)[0];
	float *w = ws->fix;
	long i;
	
	for (i = 0; i < wfixno; ++i)
	{
		r[i] = w[i] * m;
	};
	
	r = &(res.floating)[0];
	w = ws->floating;
	for (i = 0; i < wfloatno; ++i)
	{
		r[i] = w[i] * m;
	};
	return (res);
}

weights
add_wlist(double scale, exp re)
{				/* sum of  weights of list re */
	weights w, w1;
	exp r = re;
	
	if (r == nilexp)
	{
		return zeroweights;
	}
	else if (last(r))
	{
		return (weightsv(scale, r));
	}
	else
	{
		w = weightsv(scale, r);
		do
		{
			r = bro(r);
			w1 = weightsv(scale, r);
			w = add_weights(&w, &w1);
		} while (!last(r));
		return w;
	}
}



/*****************************************************************
 *	weightsv
 *
 *This procedure estimates the usage of tags and parameters to help
 *determine whether they can advantageously be placed in s registers.
 *The parameter scale allows more importance to be placed on usage
 *inside 'for' loops for example. The procedure reg_alloc in reg_alloc.c
 *finally determines the actual choice of s reg and recodes the number
 *field of an ident.

******************************************************************/
weights
weightsv(double scale, exp e)
{
	unsigned char n;
	
  tailrecurse:
	n = name(e);
	
	
	switch (n)
	{
	case name_tag:
    {
		exp s = son(e);
		
		if (name(s) == ident_tag && !isglob(s))
		{
			if (is_floating(name(sh(e))) && name(sh(e)) != shrealhd)
			{
				fno(s) += scale * 2.0;
			}
			else
				fno(s) += scale;
		}
		/* usage of tag stored in number of son of load_name (decl) */
		return zeroweights;
    };
	
	case ident_tag:
    {
		if (son(e) != nilexp)
		{
			weights wdef;
			bool wdef_set;
			weights wbody;
			long noe = no(e) /* set by scan */;
			
#if 1
			if (isparam(e))
			{
				/* initialising is a use */
				fno(e) = scale;
				wdef_set = 0;
			}
			else
#endif
				if (name(son(e)) == clear_tag || props(e) & defer_bit)
				{
					wdef = zeroweights;
					fno(e) = 0.0;
					wdef_set = 0;
				}
				else
				{
					/* maybe needs a store to initialise */
					if (is_floating(name(sh(son(e)))) && name(sh(son(e))) != shrealhd)
					{
						fno(e) = scale * 2.0;
					}
					else
						fno(e) = scale;
					wdef = weightsv(scale, son(e));
					wdef_set = 1;
				}
			/* weights for initialisation of dec */
			
			wbody = weightsv(scale, bro(son(e)));
			/* weights of body of scan */
			
			if (props(e) & defer_bit)
			{			/* declaration will be treated transparently
						 * in code production */
				exp t = son(e);
				exp s;
				
				if ((name(t) == val_tag) || (name(t) == real_tag)) /* +++ string_tag too */
				{
					return wbody;
				}
				while (name(t) != name_tag)
				{
					t = son(t);
				}
				
				s = son(t);
				if (name(s) == ident_tag && !isglob(t))
				{
					fno(s) += fno(e);
				}
				/* usage of tag stored in number of son of load_name (decl) */
				
				return wbody;
			}			/* end deferred */
			
			if ((props(e) & inreg_bits) == 0 && fixregable(e))
			{
				wp p;
				
				p = max_weights(fno(e) - 2.0 * scale, &wbody, 1);
				
				no(e) = p.fix_break;
				if (wdef_set)
					return add_weights(&wdef, &p.wp_weights);
				else
					return p.wp_weights;
			}
			else if ((props(e) & infreg_bits) == 0 && floatregable(e))
			{
				wp p;
				
				p = max_weights(fno(e) - 3.0 * scale, &wbody, 0);
				
				/*
				 * usage decreased by 3 because of dump and restore of double s-reg
				 */
				no(e) = p.float_break /* was noe */;
				if (wdef_set)
					return add_weights(&wdef, &p.wp_weights);
				else
					return p.wp_weights;
			}
			else
			{
				no(e) = noe;
				
				if (wdef_set)
					return add_weights(&wdef, &wbody);
				else
					return wbody;
			}
		}
		else
			return zeroweights;
    };
	case rep_tag:
    {
		e = bro(son(e));
		goto tailrecurse;
    }
	
	case case_tag:
    {
		e = son(e);
		goto tailrecurse;
    };
	
	case labst_tag:
    {
		scale = fno(e) * scale;
		e = bro(son(e));
		goto tailrecurse;
    }
	
	
	case val_tag:
    {
		return zeroweights;
    };
	
	case ncopies_tag:
    {
		scale = no(e) * scale;
		e = son(e);
		goto tailrecurse;
    }
	
	
	
	
	default:
    {
		if (son(e) == nilexp || n == env_offset_tag
			|| n == general_env_offset_tag)
		{
			return zeroweights;
		}
		if (last(son(e)))
		{
			e = son(e);
			goto tailrecurse;
		}
		return (add_wlist(scale, son(e)));
    }
	}
}














