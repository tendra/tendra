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
 *Revision 1.2  2002/11/21 22:31:03  nonce
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
 * Revision 1.4  1998/03/11  11:03:24  pwe
 * DWARF optimisation info
 *
 * Revision 1.3  1998/02/18  11:22:11  pwe
 * test corrections
 *
 * Revision 1.2  1998/01/20  17:14:23  release
 * Parameter named 'formal' confused SCO cc.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1997/10/23  09:24:25  pwe
 * extra diags
 *
 * Revision 1.4  1997/08/23  13:24:09  pwe
 * no invert order, and NEWDIAGS inlining
 *
 *Revision 1.3  1997/03/20 17:05:12  currie
 *Dwarf2 diags
 *
 *Revision 1.2  1997/02/18 12:56:28  currie
 *NEW DIAG STRUCTURE
 *
 *Revision 1.1  1995/04/06 10:44:05  currie
 *Initial revision

***********************************************************************/




#include "config.h"
#include "common_types.h"
#include "exp.h"
#include "expmacs.h"
#include "check.h"
#include "tags.h"
#include "shapemacs.h"
#include "me_fns.h"
#include "externs.h"
#include "flags.h"
#ifdef NEWDIAGS
#include "dg_globs.h"
#include "dg_aux.h"
#endif

#include "inline.h"

/* PROCEDURES */

static exp
last_action(exp e)
{
	if (e == nilexp)
		return e;
	
	if (name(e) == ident_tag || name(e) == seq_tag) {
		return last_action(bro(son(e)));
	}
	
	return e;
}

static void
change_last_shapes(exp e, shape sha)
{
	if (e == nilexp)
		return;
	
	if (name(e) == ident_tag || name(e) == seq_tag) {
		sh(e) = sha;
		change_last_shapes(bro(son(e)), sha);
	}
	
	return;
}

/* replaces a formal paramter by an actual parameter */
static void
replace_pars(exp actual, exp formal_par)
{
	exp def;
	if (!last(actual))
		replace_pars(bro(actual), bro(son(formal_par)));
	
	clearparam(formal_par);
	def = son(formal_par);
	if (no(formal_par) == 1 &&
		shape_size(sh(pt(formal_par))) == 8)
		setvis(formal_par);
	replace(def, actual, formal_par);
	
	retcell(def);
	return;
}

/* inlines the procedure application e */
void
inline_exp(exp e)
{
	exp fn = son(e);	/* the name_tag for the function */
	exp pars = bro(fn);	/* the first actual parameter */
	exp body = son(son(son(fn)));	/* the proc_tag exp */
	exp bc, t, q;
	exp lab;
	exp var;		/* the destination to which the result is to
					 *  			   be assigned */
	exp new_var = nilexp;
	exp new_dec;	/* a new variable declaration if we make one */
	shape sha = sh(e);	/* the shape delivered by the application */
	exp cond_alt;
	exp res;
	exp last_act;
	
	if (name(sha) == tophd) {	/* not returning a result, no ass needed */
		var = nilexp;
		cond_alt = f_make_top();
	}
	else {
		if (last(e) && name(bro(e)) == ass_tag &&
			name(son(bro(e))) == name_tag) {
			/* the result of the application is being assigned to
			 *		   a name_tag */
			var = son(bro(e));/* the destination of the ass */
			cond_alt = f_make_top();	/* the result is being assigned in the
										 *      				   body - no need for a delivered result */
			e = bro(e); /* NOTE e CHANGED to ass_tag */
#ifdef NEWDIAGS
			if (diagnose) {	/* bro(son(e)) is now the call */
				dg_whole_comp (e, bro(son(e)));
				dgf(e) = dgf(bro(son(e)));
			}
#endif
		}
		else {
			new_dec = me_start_clearvar(sha, sha);
			/* make a new variable to assign to at each res_tag */
			setinlined(new_dec);	/* mark the declaration */
			new_var = me_obtain(new_dec);
			var = new_var;	/* the destination of assignments
							 *      			   new_var is killed at end */
			cond_alt = f_contents(sha, copy(new_var));
			/* delivers the contents of the variable - hence the value */
		};
	};
	
	lab = me_b3(sh(cond_alt), me_shint(sha, 0), cond_alt, labst_tag);
  	/* the labst for the new cond_tag we are making up */
	name(son(lab)) = clear_tag;
	
	t = fn; /* start t so that its bro is the first actual parameter */
	q = body;	/* start q so that its son is the first formal parameter */
	
	while (!last(t))	/* check actual and formal shapes */
    {
		if (name(q) != ident_tag || !isparam(q))
			return;  /* no inline if more actuals than formals */
		if (shape_size(sh(bro(t))) != shape_size(sh(son(q))))
			return;	/* no inlining if shapes do not match. */
		t = bro(t);	/* next actual */
		q = bro(son(q));	/* next formal */
    };
	
	if (name(q) == ident_tag && isparam(q))
		return;  /* no inline if more formals than actuals */
	
#ifdef NEWDIAGS
	doing_inlining = 1;
#endif
	bc = copy_res(body, var, lab);
  	/* copy the body, making res_tag into assignment to var and
	 *	   jump to lab */
#ifdef NEWDIAGS
	doing_inlining = 0;
#endif
	bc = hold(bc);
	
	if (!last(fn)) {	/* if there are any parameters */
		replace_pars(pars, son(bc)); /* replace formals by actuals */
	}
	
	IGNORE check(son(bc), son(bc));	/* check the result (proc_tag ?)*/
	res = son(bc); /* remove the proc_tag */
	retcell(bc);	/* and retcell it */
	
	last_act = last_action(res);
	if (no(son(lab)) == 1 && name(last_act) == goto_tag &&
        pt(last_act) == lab) {
		/* there is only one (final) goto replacement for return */
		if (name(res) == goto_tag) {
			res = (name(sha)==tophd)?f_make_top():f_make_value(sha);
		}
		else {
			change_last_shapes(res, sh(bro(son(lab))));
#ifdef NEWDIAGS
			if (diagnose)
				dg_whole_comp (last_act, bro(son(lab)));
#endif
			replace(last_act, bro(son(lab)), res);
		}
	}
	else
		res = me_b3(sh(lab), res, lab, cond_tag);
  	/* make up the cond out of the substituted exp and lab */
	
	if (var != nilexp)
		kill_exp(var, var);
	
	if (new_var != nilexp) { /* we made up a new variable */
		SET(new_dec);
		if (no(new_dec) != 1) {
			res = me_complete_id(new_dec, res);	/* complete the variable def */
		}
		else {
			exp r = f_make_top();
#ifdef NEWDIAGS
			if (diagnose)
				dgf(r) = dgf(bro(son(lab)));
#endif
			replace(bro(son(lab)), r, r);
		}
	};
	
	
#ifdef NEWDIAGS
	if (diagnose)
		dg_complete_inline (e, res);
#endif
	replace(e, res, nilexp);	/* replace the call by the inlined stuff */
	kill_exp(fn, fn);	/* kill off the function name_tag */
	
	return;
}
