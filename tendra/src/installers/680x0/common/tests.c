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
 *    		 Crown Copyright (c) 1996
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
/*
 *			    VERSION INFORMATION
 *			    ===================
 *
 *--------------------------------------------------------------------------
 *$Header$
 *--------------------------------------------------------------------------
 *$Log$
 *Revision 1.2  2002/11/21 22:30:45  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
 *Revision 1.2  1997/11/09 14:15:09  ma
 *Removed issigned. Use is_signed instead.
 *
 *Revision 1.1.1.1  1997/10/13 12:42:59  ma
 *First version.
 *
 *Revision 1.5  1997/10/13 08:50:11  ma
 *Made all pl_tests for general proc & exception handling pass.
 *
 *Revision 1.4  1997/09/25 06:45:35  ma
 *All general_proc tests passed
 *
 *Revision 1.3  1997/04/20 11:30:39  ma
 *Introduced gcproc.c & general_proc.[ch].
 *Added cases for apply_general_proc next to apply_proc in all files.
 *
 *Revision 1.2  1997/03/20 12:46:24  ma
 *Now tag ids are kept in unsigned chars (MAX tag id > 127).
 *
 *Revision 1.1.1.1  1997/03/14 07:50:18  ma
 *Imported from DRA
 
 * Revision 1.1.1.1  1996/09/20  10:56:59  john
 *
 * Revision 1.2  1996/07/05  14:26:52  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:17  john
 *
 * Revision 1.3  94/02/21  16:04:20  16:04:20  ra (Robert Andrews)
 * A number of values which were previously bool are now int.
 *
 * Revision 1.2  93/05/24  16:00:03  16:00:03  ra (Robert Andrews)
 * The optimisation which check_anyway is designed to test for has
 * returned.  Some tuning is required.
 *
 * Revision 1.1  93/02/22  17:16:44  17:16:44  ra (Robert Andrews)
 * Initial revision
 *
 *--------------------------------------------------------------------------
 */


#include "config.h"
#include "common_types.h"
#include "assembler.h"
#include "exp.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "tags.h"
#include "tests.h"
#include "is_worth.h"
#ifndef tdf3
#include "68k_globals.h"
#endif


/*
 *    CC CONVENTIONS
 *
 *    HP cc has different conventions to gcc on certain points, most
 *    noticably on the alignment of bitfields.  Both conventions are
 *    supported, but the cc conventions are default on the HP.  NeXT
 *    cc is gcc.
 */

#ifdef hp_cc_conventions
int cc_conventions = 1;
#else
int cc_conventions = 0;
#endif

bool
reused_parameter(exp e)
{
	bool reused = 0;
	exp def, ident_exp;
	def = son (e);
	if (name (def) == name_tag) {
		ident_exp = son (def);
		if (! isvar (ident_exp)) {
			/* This an obtain_tag of a parameter */
			if (name(son(ident_exp)) == formal_callee_tag) {
				reused = cur_proc_use_same_callees;
			}
			else {
				/* caller parameter */
				reused = cur_proc_has_tail_call;
			}
		}
	}
	return reused;
}

/*
 *    CAN THE VALUE OF AN EXPRESSION BE PUT INTO A REGISTER?
 *
 *    This routine returns 1 if the expression e can be put into a register.
 *    It has to have its visible flag false, and to be of a suitable shape.
 */

bool
regable(exp e)
{
    shape sha;
    char n;
    long sz;
	
    if (isvis (e)) return (0);
	
    sha = sh (son (e));
    n = name (sha);
    if (n == realhd || n == doublehd) return (1);
	
    sz = shape_size (sha);
	
    return (n != cpdhd && n != nofhd && sz <= 32);
}


/*
 *    DOES AN EXP HAVE NO SIDE EFFECTS?
 *
 *    This routine returns 1 if e has no side effects.
 */

bool
no_side(exp e)
{
    int n = name (e);
    if (n == ident_tag) {
		return (no_side (son (e)) && (no_side (bro (son (e)))));
    }
    return (is_a (n) || n == test_tag ||
			n == ass_tag || n == testbit_tag);
}

char n;

/*
 *    IS AN EXP A PUSHABLE PROCEDURE ARGUMENT?
 *
 *    Can the expression e be pushed directly onto the stack when it is
 *    the parameter of a procedure?
 */

bool
push_arg(exp e)
{
    unsigned char n = name (e);
	
    if (is_a (n)) return (1);
    if (n == apply_tag || n == apply_general_tag) return (reg_result (sh (e)));
    if (n == ident_tag) {
		return (push_arg (son (e)) && push_arg (bro (son (e))));
    }
    return (0);
}


#if 0

/*
 *    IS A UNION ACTUALLY POINTER VOID?
 *
 *    No longer used.
 */


#ifndef PTR_VOID_MIN
#define PTR_VOID_MIN	10
#endif

bool
is_ptr_void(shape sha)
{
    bool go;
    int ptrs = 0;
    exp t = son (sha);
    if (t == nilexp) return (0);
    do {
		go = (last (t) ? 0 : 1);
		if (name (sh (t)) != ptrhd) return (0);
		ptrs++;
		t = bro (t);
    } while (go);
    if (ptrs < PTR_VOID_MIN) return (0);
#ifdef PTR_VOID_MAX
    if (ptrs > PTR_VOID_MAX) return (0);
#endif
    return (1);
}

#endif


/*
 *    IS A SHAPE COMPOUND?
 *
 *    This routine is designed to test whether a given shape is compound,
 *    and thus likely to cause problems when it is the parameter of a
 *    procedure.
 */

bool
cpd_param(shape sha)
{
    char n = name (sha);
    if (!cc_conventions || n == bitfhd) {
		long sz = shape_size (sha);
		if (sz <= 32) return (0);
    }
    return (n == cpdhd || n == nofhd || n == bitfhd
			
            || n == s64hd || n == u64hd
			
		);
}


/*
 *    DOES A PROCEDURE RETURN A RESULT OF A GIVEN SHAPE IN A REGISTER?
 *
 *    cc has two ways of getting results from procedures.  Firstly in the
 *    register D0 (or D0 and D1 in certain cases) and secondly in a section
 *    of memory the address of which is passed in at the start of the
 *    procedure in the A1 register and returned at the end in the D0
 *    register.  This routine works out whether or not a procedure
 *    delivering a result of shape sha will use the first method.
 */


int
reg_result(shape sha)
{
    char n = name (sha);
    if (cc_conventions) {
		/* HP cc doesn't return any tuples, unions etc in a register */
		return (n != cpdhd && n != nofhd);
    } else {
		/* Return anything of size <= 32 or 64 in a register */
		long sz = shape_size (sha);
		return (sz <= 32 || sz == 64);
    }
}


/*
 *    IS A SHAPE OF VARIABLE SIZE?
 *
 *    This routine returns 1 if sha involves an array.
 */

bool
varsize(shape sha)
{
    return (name (sha) == nofhd ? 1 : 0);
}

#if 0
Use is_signed macro instead

/*
 *    IS A SHAPE SIGNED?
 *
 *    This routine returns 1 if the integer variety shape sha is signed
 *    and 0 otherwise.
 */

bool
issigned(shape sha)
{
    char n = name (sha);
    if (n == ucharhd || n == uwordhd || n == ulonghd) return (0);
    return (1);
}
#endif

/*
 *    CHECK ON DECLARATION FOR PARAMETER SUBSTITUTION
 *
 *    This routine checks if the declaration e should be substituted
 *    for all its uses or not.
 */

int do_sub_params = 1;

int
check_anyway(exp e)
{
#ifndef tdf3
	return 0;
#else
    if (do_sub_params) {
		setmarked (e);
		if (no (e) > 2) return (1);
    }
    return (0);
#endif
}


/*
 *    IS IT WORTH EXTRACTING A CONSTANT?
 */

int
is_worth(exp c)
{
	unsigned char cnam = name (c);
	return ((!is_o (cnam) && cnam != clear_tag) ||
			/* ignore simple things unless ... */
			(cnam == cont_tag && name (son (c)) == cont_tag &&
			 name (son (son (c)))  == name_tag) ||
			(cnam == name_tag && isparam (son (c)) && !isvar (son (c)) &&
			 shape_size (sh (c)) <= 32 && name (sh (c)) != shrealhd));
}
