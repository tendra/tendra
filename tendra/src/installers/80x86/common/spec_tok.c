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


/* 80x86/spec_tok.c */

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
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.9  1997/10/10  18:25:29  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.8  1997/08/23  13:45:42  pwe
 * initial ANDF-DE
 *
 * Revision 1.7  1997/03/20  16:24:07  pwe
 * dwarf2
 *
 * Revision 1.6  1997/02/18  11:43:08  pwe
 * NEWDIAGS for debugging optimised code
 *
 * Revision 1.5  1996/12/13  14:39:33  pwe
 * prep NEWDIAGS
 *
 * Revision 1.4  1996/12/10  15:11:52  pwe
 * prep NEWDIAGS
 *
 * Revision 1.3  1996/10/29  14:04:49  pwe
 * remove inbuilt C promote etc, for inclusion of long long
 *
 * Revision 1.2  1995/01/30  12:56:52  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:41:50  jmf
 * Initial revision
 *
 **********************************************************************/


#include "config.h"
#include "common_types.h"
#include "basicread.h"
#include "tags.h"
#include "exp.h"
#include "expmacs.h"
#include "diag_fns.h"
#include "flags.h"
#include "check.h"
#include "me_fns.h"
#include "externs.h"
#include "installglob.h"
#include "messages_r.h"
#include "main_reads.h"
#include "install_fns.h"
#include "c_arith_type.h"
#include "natmacs.h"
#include "spec_tok.h"
#include "dg_fns.h"


/* intercepts specially defined tokens */

tokval
special_token(token t, bitstream pars, int sortcode,
			  int * done)
{
	tokval tkv;
	UNUSED(sortcode);
	
	if (t -> tok_name == (char*)0) {
		SET(tkv); /* call looks at done to see if result is meaningful */
		return tkv;
	};
	
	if (!strcmp(t -> tok_name, "JMFprofile"))  {
		nat n;
		place old_place;
		old_place = keep_place();
		set_place(pars);
		n = d_nat();
		
		set_place(old_place);
		tkv.tk_exp = f_profile(n);
		*done = 1;
		return tkv;
	};
	if (!strcmp(t -> tok_name, "JMFinline"))  {
		exp s;
		place old_place;
		old_place = keep_place();
		set_place(pars);
		IGNORE d_shape();
		s = d_exp();
		if (name(s) == apply_tag)
			settoinline(s);
		if (name(s) == ident_tag && name(son(s)) == clear_tag &&
			name(bro(son(s))) == seq_tag &&
			name(son(son(bro(son(s))))) == apply_tag)
			settoinline(son(son(bro(son(s)))));
		
		
		s = hold_check(s);
		
		set_place(old_place);
		tkv.tk_exp = s;
		*done = 1;
		return tkv;
	};
	if (!strcmp(t -> tok_name, "~div"))  {
		exp arg1, arg2;
		place old_place;
		old_place = keep_place();
		set_place(pars);
		arg1 = hold_check(d_exp());
		arg2 = hold_check(d_exp());
		
		set_place(old_place);
		tkv.tk_exp = me_b2(arg1, arg2, div0_tag);
		*done = 1;
		return tkv;
	};
	if (!strcmp(t -> tok_name, "~rem"))  {
		exp arg1, arg2;
		place old_place;
		old_place = keep_place();
		set_place(pars);
		arg1 = hold_check(d_exp());
		arg2 = hold_check(d_exp());
		
		set_place(old_place);
		tkv.tk_exp = me_b2(arg1, arg2, rem0_tag);
		*done = 1;
		return tkv;
	};
#ifdef INBUILT_PROMOTE
	if (!strcmp(t -> tok_name, "~arith_type")) {
		int a, b;
		place old_place;
		signed_nat sn;
		old_place = keep_place();
		set_place(pars);
		sn = d_signed_nat();
		a = snatint(sn);
		sn = d_signed_nat();
		b = snatint(sn);
		set_place(old_place);
		snatint(sn) = arith_type(a, b);
		tkv.tk_signed_nat = sn;
		*done = 1;
		return tkv;
	};
	if (!strcmp(t -> tok_name, "~promote")) {
		int a;
		place old_place;
		signed_nat sn;
		old_place = keep_place();
		set_place(pars);
		sn = d_signed_nat();
		a = snatint(sn);
		set_place(old_place);
		snatint(sn) = promote(a);
		tkv.tk_signed_nat = sn;
		*done = 1;
		return tkv;
	};
	if (!strcmp(t -> tok_name, "~sign_promote")) {
		int a;
		place old_place;
		signed_nat sn;
		old_place = keep_place();
		set_place(pars);
		sn = d_signed_nat();
		a = snatint(sn);
		set_place(old_place);
		snatint(sn) = sign_promote(a);
		tkv.tk_signed_nat = sn;
		*done = 1;
		return tkv;
	};
	if (!strcmp(t -> tok_name, "~convert")) {
		int a;
		place old_place;
		signed_nat sn;
		old_place = keep_place();
		set_place(pars);
		sn = d_signed_nat();
		a = snatint(sn);
		set_place(old_place);
		tkv.tk_variety = convert((unsigned)a);
		*done = 1;
		return tkv;
	};
#endif
	if (!strcmp(t -> tok_name, "~alloca"))  {
		exp arg1;
		place old_place;
		old_place = keep_place();
		set_place(pars);
		arg1 = hold_check(d_exp());
		set_place(old_place);
		tkv.tk_exp = hold_check(me_u3(f_pointer(long_to_al(8)),
									  arg1, alloca_tag));
		*done = 1;
		has_alloca = 1;
		return tkv;
	};
	
	if (!strcmp(t -> tok_name, "~exp_to_source") ||
		!strcmp(t -> tok_name, "~diag_id_scope") ||
		!strcmp(t -> tok_name, "~diag_type_scope") ||
		!strcmp(t -> tok_name, "~diag_tag_scope")
#ifdef NEWDIAGS
		|| !strcmp(t -> tok_name, "~dg_exp")
#endif
		)  {
		
		place old_place;
		old_place = keep_place();
		set_place(pars);
		tkv.tk_exp = hold_check(d_exp());
		*done = 1;
		
		if (!diagnose)
        {
			set_place(old_place);
			return tkv;
        };
		
		if (!strcmp(t -> tok_name, "~exp_to_source"))
		{
#ifdef NEWDIAGS
			tkv.tk_exp = read_exp_to_source (tkv.tk_exp);
#else
			diag_info * di = read_exp_to_source();
			exp r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
						   1, 0, diagnose_tag);
			setfather(r, tkv.tk_exp);
			dno(r) = di;
			tkv.tk_exp = r;
			crt_lno = natint(di -> data.source.end.line_no);
			crt_charno = natint(di -> data.source.end.char_off);
			crt_flnm = di -> data.source.beg.file->file.ints.chars;
#endif
			set_place(old_place);
			return tkv;
		};
		
		if (!strcmp(t -> tok_name, "~diag_id_scope"))
		{
#ifdef NEWDIAGS
			tkv.tk_exp = read_diag_id_scope (tkv.tk_exp);
#else
			diag_info * di = read_diag_id_scope();
			exp r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
						   2, 0, diagnose_tag);
			setfather(r, tkv.tk_exp);
			dno(r) = di;
			tkv.tk_exp = r;
#endif
			set_place(old_place);
			return tkv;
		};
		
		if (!strcmp(t -> tok_name, "~diag_type_scope"))
		{
#ifdef NEWDIAGS
			tkv.tk_exp = read_diag_type_scope (tkv.tk_exp);
#else
			diag_info * di = read_diag_type_scope();
			exp r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
						   3, 0, diagnose_tag);
			setfather(r, tkv.tk_exp);
			dno(r) = di;
			tkv.tk_exp = r;
#endif
			set_place(old_place);
			return tkv;
		};
		
		if (!strcmp(t -> tok_name, "~diag_tag_scope"))
		{
#ifndef NEWDIAGS
			diag_info * di = read_diag_tag_scope();
			exp r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
						   4, 0, diagnose_tag);
			setfather(r, tkv.tk_exp);
			dno(r) = di;
			tkv.tk_exp = r;
#endif
			set_place(old_place);
			return tkv;
		};
		
#ifdef NEWDIAGS
		if (!strcmp(t -> tok_name, "~dg_exp"))
		{
			tkv.tk_exp = read_dg_exp (tkv.tk_exp);
			set_place(old_place);
			return tkv;
		};
#endif
		
	};
	
	if (!strncmp(t -> tok_name, "~asm", 4)) {
		int prp;
		exp arg1;
		place old_place;
		old_place = keep_place();
		if (!strcmp(t -> tok_name, "~asm")) {
			set_place(pars);
			arg1 = hold_check (f_make_nof_int (ucharsh, d_string()));
			prp = 1;
		}
		else {
			if (!strcmp(t -> tok_name, "~asm_sequence"))
				prp = 0;
			else
				if (!strcmp(t -> tok_name, "~asm_exp_input"))
					prp = 2;
				else
					if (!strcmp(t -> tok_name, "~asm_exp_output"))
						prp = 4;
					else
						if (!strcmp(t -> tok_name, "~asm_exp_address"))
							prp = 8;
						else
							return tkv;
			set_place(pars);
			arg1 = hold_check (d_exp());
		}
		set_place(old_place);
		tkv.tk_exp = getexp (f_top, nilexp, 0, arg1, nilexp, prp, 0, asm_tag);
		setfather (tkv.tk_exp, arg1);
		*done = 1;
		return tkv;
	}
	
	SET(tkv); /* call looks at done to see if result is meaningful */
	return tkv;
}
