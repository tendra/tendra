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
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1996/10/29  10:10:51  currie
 * 512 bit alignment for hppa
 *
 * Revision 1.3  1995/07/05  09:26:35  currie
 * continue wrong
 *
 * Revision 1.2  1995/05/05  08:10:56  currie
 * initial_value + signtures
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
 ***********************************************************************/




#include "config.h"
#include "common_types.h"
#include "exp.h"
#include "expmacs.h"
#include "table_fns.h"
#include "externs.h"
#include "installglob.h"
#include "tags.h"
#include "install_fns.h"
#include "check.h"
#include "messages_c.h"
#include "shapemacs.h"
#include "basicread.h"
#include "natmacs.h"
#include "me_fns.h"

/* a collection of useful procedures for makeing up exps */

/* PROCEDURES */

exp
me_obtain(exp id)
{
	shape sha = (son(id)==nilexp)?sh(id):sh(son(id));
	exp n;
	n = getexp((isvar(id)) ? f_pointer(align_of(sha)) : sha,
			   nilexp, 0, id, pt(id), 0, 0, name_tag);
	++no(id);
	pt(id) = n;
	return n;
}

exp
me_startid(shape sha, exp def, int isv)
{
	exp r = getexp(sha, nilexp, 0, def, nilexp, 0, 0, ident_tag);
	if (isv)
		setvar(r);
	return r;
}

exp
me_start_clearvar(shape sha, shape shb)
{
	exp init = getexp(shb, nilexp, 0, nilexp, nilexp, 0, 0, clear_tag);
	exp var = getexp(sha, nilexp, 0, init, nilexp, 0, 0, ident_tag);
	setvar(var);
	return var;
}

exp
me_complete_id(exp id, exp body)
{
	clearlast(son(id));
	bro(son(id)) = body;
	setlast(body);
	bro(body) = id;
	sh(id) = sh(body);
	return hold_check(id);
}

exp
me_u1(error_treatment ov_err, exp arg1, unsigned char nm)
{
	exp r = getexp (sh (arg1), nilexp, 0, arg1, nilexp,
					0, 0, nm);
	seterrhandle(r, ov_err.err_code);
	if (isov(r))
		setjmp_dest(r, get_lab(ov_err.jmp_dest));
	setfather (r, arg1);
	return r;
}

exp
me_u2(exp arg1, unsigned char nm)
{
	exp r = getexp (sh (arg1), nilexp, 0, arg1, nilexp, 0, 0, nm);
	setfather (r, arg1);
	return r;
}

exp
me_u3(shape sha, exp arg1, unsigned char nm)
{
	exp r = getexp (sha, nilexp, 0, arg1, nilexp, 0, 0, nm);
	setfather (r, arg1);
	return r;
}

exp
me_b1(error_treatment ov_err, exp arg1, exp arg2,
	  unsigned char nm)
{
	exp r = getexp (sh (arg1), nilexp, 0, arg1, nilexp,
					0, 0, nm);
	seterrhandle(r, ov_err.err_code);
	setbro(arg1, arg2);
	clearlast(arg1);
	if (isov(r))
		setjmp_dest(r, get_lab(ov_err.jmp_dest));
	setfather (r, arg2);
	return r;
}

exp
me_b2(exp arg1, exp arg2, unsigned char nm)
{
	exp r = getexp (sh (arg1), nilexp, 0, arg1, nilexp, 0, 0, nm);
	setbro(arg1, arg2);
	clearlast(arg1);
	setfather (r, arg2);
	return r;
}

exp
me_b3(shape sha, exp arg1, exp arg2, unsigned char nm)
{
	exp r = getexp (sha, nilexp, 0, arg1, nilexp, 0, 0, nm);
	setbro(arg1, arg2);
	clearlast(arg1);
	setfather (r, arg2);
	return r;
}

exp
me_c1(shape sha, error_treatment ov_err, exp arg1,
	  unsigned char nm)
{
	exp r = getexp (sha, nilexp, 0, arg1, nilexp,
					0, 0, nm);
	seterrhandle(r, ov_err.err_code);
	if (isov(r))
		setjmp_dest(r, get_lab(ov_err.jmp_dest));
	setfather (r, arg1);
	return r;
}

exp
me_c2(shape sha, exp arg1, unsigned char nm)
{
	exp r = getexp (sha, nilexp, 0, arg1, nilexp, 0, 0, nm);
	setfather (r, arg1);
	return r;
}

exp
me_l1(shape s, unsigned char nm)
{
	exp r = getexp (s, nilexp, 0, nilexp, nilexp, 0, 0, nm);
	return r;
}



exp
me_q1_aux(nat_option prob, ntest nt, exp lab,
		  exp arg1, exp arg2, unsigned char nm)
{
	exp r;
	r = getexp (f_top, nilexp, 0, arg1, lab, 0, 0, nm);
	no(r) = (prob.present) ? natint(prob.val) : 1000;
	settest_number(r, nt);
	setbro(arg1, arg2);
	clearlast(arg1);
	++no(son(lab));
	setfather (r, arg2);
	return r;
}

exp
me_q1(nat_option prob, ntest nt, label dest,
	  exp arg1, exp arg2, unsigned char nm)
{
	return me_q1_aux(prob, nt, get_lab(dest), arg1, arg2, nm);
}

exp
me_q2_aux(nat_option prob, error_treatment err,
		  ntest nt, exp lab, exp arg1, exp arg2,
		  unsigned char nm)
{
	exp r;
	UNUSED(err);
	r = getexp (f_top, nilexp, 0, arg1, lab, 0, 0, nm);
	no(r) = (prob.present) ? natint(prob.val) : 1000;
	settest_number(r, nt);
	setbro(arg1, arg2);
	clearlast(arg1);
	++no(son(lab));
	setfather (r, arg2);
	
	return r;
}

exp
me_q2(nat_option prob, error_treatment err,
	  ntest nt, label dest, exp arg1, exp arg2,
	  unsigned char nm)
{
	return me_q2_aux(prob, err, nt, get_lab(dest), arg1, arg2, nm);
}

exp
me_shint(shape sha, int i)
{
	return getexp(sha, nilexp, 0, nilexp, nilexp, 0, i, val_tag);
}

exp
me_null(shape sha, int i, unsigned char nm)
{
	return getexp(sha, nilexp, 0, nilexp, nilexp, 0, i, nm);
}

exp
me_b4(error_treatment div0_err, error_treatment ov_err,
	  exp arg1, exp arg2, unsigned char nm)
{
	exp id, tst, divexp, seq;
	
	if (div0_err.err_code != 4)
		return me_b1(ov_err, arg1, arg2, nm);
	
	id = me_startid(sh(arg1), arg2, 0);
	divexp = me_b1(ov_err, arg1, me_obtain(id), nm);
	tst = me_q1(no_nat_option, f_not_equal, div0_err.jmp_dest,
				me_obtain(id), me_shint(sh(arg1), 0), test_tag);
	seq = me_b2(me_u2(tst, 0), divexp, seq_tag);
	return me_complete_id(id, seq);
}

void
note_repeat(exp r)
{
	if (crt_repeat != nilexp)
		++no (crt_repeat);
	repeat_list = getexp (f_top, crt_repeat, 0, nilexp,
						  repeat_list, 1, 0, 0);
	crt_repeat = repeat_list;
	
	pt(r) = crt_repeat;
	
	son (crt_repeat) = r;
	crt_repeat = bro(crt_repeat);
	return;
}

/* the result is an alignment for something of which the
 *     addresses must be divisible by n bits */
alignment
long_to_al(int n)
{
	switch (n) {
    case 0:
    case 1: return const_al1;
    case 8: return const_al8;
    case 16: return const_al16;
    case 32: return const_al32;
    case 64: return const_al64;
    case 512: return const_al512;
    default: failer(BAD_LONG_AL);
		return const_al32;
	};
}

/* the shape describes an integer */
int
is_integer(shape s)
{
	return name(s) >= scharhd && name(s) <= u64hd;
}

/* the shape describes a floating point number */
int
is_float(shape s)
{
	return name(s) >= shrealhd && name(s) <= doublehd;
}

int
is_complex(shape s)
{
#if substitute_complex
	return (name(s) == cpdhd);
#else
	return name(s) >= shcomplexhd && name(s) <= complexdoublehd;
#endif
}

floating_variety
float_to_complex_var(floating_variety f)
{
	return f+3;
}

floating_variety
complex_to_float_var(floating_variety f)
{
	return f-3;
}
