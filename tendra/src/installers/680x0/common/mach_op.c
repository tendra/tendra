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
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
 *Revision 1.2  1997/10/29 10:22:21  ma
 *Replaced use_alloca with has_alloca.
 *
 *Revision 1.1.1.1  1997/10/13 12:42:55  ma
 *First version.
 *
 *Revision 1.3  1997/09/25 06:45:15  ma
 *All general_proc tests passed
 *
 *Revision 1.2  1997/06/18 10:09:37  ma
 *Checking in before merging with Input Baseline changes.
 *
 *Revision 1.1.1.1  1997/03/14 07:50:15  ma
 *Imported from DRA
 
 * Revision 1.2  1996/09/20  13:51:39  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:55  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:14  john
 *
 * Revision 1.1  93/02/22  17:16:07  17:16:07  ra (Robert Andrews)
 * Initial revision
 *
 *--------------------------------------------------------------------------
 */


#include "config.h"
#include "common_types.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "codex.h"
#include "output.h"
#include "utility.h"

#ifndef tdf3
#define  par2_pl        4       /* procedure argument accessed by use of A5 */
#define  par3_pl        5       /* procedure argument accessed by use of SP */
#endif


/*
 *    LIST OF FREE OPERANDS
 *
 *    A list of free mach_op's, linked by the plus field.
 */

static mach_op *mach_op_list = null;


/*
 *    ALLOCATE A NEW OPERAND
 *
 *    This routine returns a pointer to a mach_op.  This is taken from the
 *    list of free mach_op's.
 */
#ifndef tdf3
#ifdef EBUG
static int next_id = 0;
#endif
#endif

mach_op
*new_mach_op()
{
    mach_op *p;
    if (mach_op_list == null) {
		int i, n = 1000;
		p = alloc_nof (mach_op, n);
		for (i = 0 ; i < n - 1 ; i++) {
			(p + i)->plus = p + (i + 1);
			(p + i)->of = null;
		}
		(p + (n - 1))->plus = null;
		(p + (n - 1))->of = null;
		mach_op_list = p;
    }
    p = mach_op_list;
    if (p->of) {
		mach_op *q = p->of;
		mach_op_list = q;
		while (q->plus) q = q->plus;
		q->plus = p->plus;
    } else {
		mach_op_list = p->plus;
    }
    p->def.num = 0;
    p->plus = null;
    p->of = null;
#ifndef tdf3
#ifdef EBUG
    if (next_id == 70) {
		int dummy = next_id;
    }
	
    p->id = next_id ++;
#endif
#endif
    return (p);
}


/*
 *    FREE AN OPERAND
 *
 *    A mach_op is freed by adding it to the list of free mach_op's.
 */

void
free_mach_op(mach_op *ptr)
{
    mach_op *p = ptr;
    if (p == null) return;
    while (p->plus) p = p->plus;
    p->plus = mach_op_list;
    mach_op_list = ptr;
    return;
}


/*
 *    SPECIAL LABELS INFORMATION
 *
 *    A special label consists of the label prefix, "L", followed by the
 *    special label identifier, followed by the value of special_no for
 *    the current procedure.  A particular special label is that with
 *    identifier special_str.
 */

long special_no = 0;
char *special_str = "S";


/*
 *    TEMPORARY REGISTER STATUS
 *
 *    This records the number of temporary registers which have been allocated
 *    at any given moment, any temporary register preferences and the last
 *    temporary register used.
 */

int tmp_reg_status = 0;
int tmp_reg_prefer = 0;
static int last_reg = 0;


/*
 *    FIND THE NUMBER OF THE NEXT TEMPORARY REGISTER
 *
 *    This is a look-ahead routine to find what the next temporary register
 *    allocated will be.  Let X denote the prefered temporary register
 *    (if specified) and Y denote any A-register used in the procedure
 *    but not currently active.
 *
 *    If X is specified, it will always be the first temporary register
 *    returned.  The second will be Y, if that exists, or A1, unless
 *    this equals X, if which case A0 is used.
 *
 *    If X is not specified, the first temporary register will be Y,
 *    if that exists, or A1.  The second will be A1 if Y exists, or
 *    A0 otherwise.
 *
 *    Under very rare conditions a third temporary register is required.
 *    In these cases D0 always suffices.
 */

int
next_tmp_reg()
{
    int r;
    int t = tmp_reg_status;
    if (t > 1) {
		debug_warning ("Temporary D-register used");
		r = REG_D0;
    } else if (tmp_reg_prefer) {
		if (t == 0) {
			r = tmp_reg_prefer;
			last_reg = r;
		} else {
			bitpattern na = (regsinuse | reuseables | regsindec);
			bitpattern a = regsinproc & ~na & 0x3c00;
			r = (a ? reg (a) : REG_A1);
			if (r == last_reg) r = REG_A0;
		}
    } else {
		bitpattern na = (regsinuse | reuseables | regsindec);
		bitpattern a = regsinproc & ~na & 0x3c00;
		if (t == 0) {
			r = (a ? reg (a) : REG_A1);
			last_reg = r;
		} else {
			r = (a ? REG_A1 : REG_A0);
			if (r == last_reg) r = (r == REG_A0 ? REG_A1 : REG_A0);
		}
    }
    return (r);
}


/*
 *    AVOID A GIVEN TEMPORARY REGISTER
 *
 *    This marks the given register number as to be avoided by pretending
 *    that it was the previous temporary register.
 */

void
avoid_tmp_reg(int r)
{
    last_reg = r;
    tmp_reg_status++;
    return;
}


/*
 *    MOVE AN OPERAND INTO A TEMPORARY REGISTER
 *
 *    It is sometimes necessary to move an operand into a temporary address
 *    register.  A move instruction (given by instr) is output, and the
 *    number of the temporary register is returned.
 */

int
tmp_reg(int instr, mach_op *ptr)
{
    int t = tmp_reg_status;
    int r = next_tmp_reg ();
    mach_op *p = new_mach_op ();
    p->type = MACH_REG;
    p->def.num = (long) r;
    make_instr_aux (instr, ptr, p, regmsk (r), 1);
    regsinproc |= regmsk (r);
    tmp_reg_status = t + 1;
    return (r);
}


/*
 *    TEST IF A REGISTER IS USED IN AN OPERAND
 *
 *    This routine returns 1 if register r is used in the operand op.
 */

bool
check_op(mach_op *op, int r)
{
    if (op == null) return (0);
    switch (op->type) {
		
	case MACH_CONT : return ((op->def.num) & regmsk (r) ? 1 : 0);
		
	case MACH_REG :
	case MACH_DEC :
	case MACH_INC : return (op->def.num == r ? 1 : 0);
		
	case MACH_BF : return (check_op (op->of, r));
		
	case MACH_RPAIR : {
	    if (op->def.num == r) return (1);
	    return (op->plus->def.num == r ? 1 : 0);
	}
    }
    return (0);
}


/*
 *    TEST IF TWO OPERANDS ARE EQUAL
 *
 *    This returns 1 if the two operands have equal effect.  Note that,
 *    for example, consecutive uses of the same pre-decremented register,
 *    although having the same representation, are not equal in this
 *    context.
 */

bool
equal_op(mach_op *op1, mach_op *op2)
{
    mach_op *p1 = op1, *p2 = op2;
    while (p1 && p2) {
		if (p1->type != p2->type) return (0);
		if (p1->type == MACH_DEC || p1->type == MACH_INC) return (0);
		if (p1->def.num != p2->def.num) return (0);
		if (p1->plus) {
			if (p2->plus == null) return (0);
			if (!equal_op (p1->plus, p2->plus)) return (0);
		} else {
			if (p2->plus) return (0);
		}
		p1 = p1->of;
		p2 = p2->of;
    }
    return (p1 == p2 ? 1 : 0);
}


/*
 *    MAKE AN INTEGER CONSTANT OPERAND
 *
 *    This and the subsequent routines are used to allocate machine operands.
 *    The constructions are simple applications of the descriptions given
 *    in mach.h.  They need very little other comment.
 */

mach_op
*make_value(long n)
{
    mach_op *p = new_mach_op ();
    p->type = MACH_VAL;
    p->def.num = n;
    return (p);
}


/*
 *    MAKE AN INTEGER DATA OPERAND
 */

mach_op
*make_int_data(long n)
{
    mach_op *p = new_mach_op ();
    p->type = MACH_VALQ;
    p->def.num = n;
    return (p);
}


/*
 *    MAKE A HEXADECIMAL INTEGER CONSTANT OPERAND
 */

mach_op
*make_hex_value(long n)
{
    mach_op *p = new_mach_op ();
    p->type = MACH_HEX;
    p->def.num = n;
    return (p);
}


/*
 *    MAKE A HEXADECIMAL INTEGER CONSTANT DATA OPERAND
 */

mach_op
*make_hex_data(long n)
{
    mach_op *p = new_mach_op ();
    p->type = MACH_HEXQ;
    p->def.num = n;
    return (p);
}


/*
 *    MAKE A FLOATING POINT DATA OPERAND
 */

mach_op
*make_float_data(flt *f)
{
    mach_op *p = new_mach_op ();
    p->type = MACH_FLOATQ;
    p->def.fp = f;
    return (p);
}


/*
 *    MAKE A LABEL OPERAND
 */

mach_op
*make_lab(long n, long d)
{
    mach_op *p1 = new_mach_op ();
    p1->type = MACH_LAB;
    p1->def.num = n;
    if (d) {
		mach_op *p2 = new_mach_op ();
		p2->type = MACH_VAL;
		p2->def.num = d;
		p1->plus = p2;
    }
    return (p1);
}


/*
 *    MAKE A LABEL DATA OPERAND
 */

mach_op
*make_lab_data(long n, long d)
{
    mach_op *p1 = new_mach_op ();
    p1->type = MACH_LABQ;
    p1->def.num = n;
    if (d) {
		mach_op *p2 = new_mach_op ();
		p2->type = MACH_VAL;
		p2->def.num = d;
		p1->plus = p2;
    }
    return (p1);
}


/*
 *    MAKE AN OPERAND CORRESPONDING TO THE DIFFERENCE OF TWO LABELS
 */

mach_op
*make_lab_diff(long a, long b)
{
    mach_op *p1 = new_mach_op ();
    mach_op *p2 = new_mach_op ();
    mach_op *p3 = new_mach_op ();
    p1->type = MACH_LABQ;
    p1->def.num = a;
    p1->plus = p2;
    p2->type = MACH_NEG;
    p2->plus = p3;
    p3->type = MACH_LABQ;
    p3->def.num = b;
    return (p1);
}


/*
 *    MAKE AN EXTERNAL OPERAND
 */

mach_op
*make_extern(char *nm, long d)
{
    mach_op *p1 = new_mach_op ();
    p1->type = MACH_EXT;
    p1->def.str = nm;
    if (d) {
		mach_op *p2 = new_mach_op ();
		p2->type = MACH_VAL;
		p2->def.num = d;
		p1->plus = p2;
    }
    return (p1);
}


/*
 *    MAKE AN EXTERNAL DATA OPERAND
 */

mach_op
*make_extern_data(char *nm, long d)
{
    mach_op *p1 = new_mach_op ();
    p1->type = MACH_EXTQ;
    p1->def.str = nm;
    if (d) {
		mach_op *p2 = new_mach_op ();
		p2->type = MACH_VAL;
		p2->def.num = d;
		p1->plus = p2;
    }
    return (p1);
}


/*
 *    MAKE A SPECIAL LABEL OPERAND
 */

mach_op
*make_special(char *nm)
{
    mach_op *p = new_mach_op ();
    p->type = MACH_SPEC;
    p->def.str = nm;
    return (p);
}


/*
 *    MAKE A SPECIAL LABEL DATA OPERAND
 */

mach_op
*make_special_data(char *nm)
{
    mach_op *p = new_mach_op ();
    p->type = MACH_SPECQ;
    p->def.str = nm;
    return (p);
}


/*
 *    MAKE A LABEL INDIRECT OPERAND
 */

mach_op
*make_lab_ind(long n, long d)
{
    mach_op *p1 = new_mach_op ();
    mach_op *p2 = new_mach_op ();
    p1->type = MACH_CONT;
    p1->def.num = 0;
    p1->of = p2;
    p2->type = MACH_LAB;
    p2->def.num = n;
    if (d) {
		mach_op *p3 = new_mach_op ();
		p3->type = MACH_VAL;
		p3->def.num = d;
		p2->plus = p3;
    }
    return (p1);
}


/*
 *    MAKE AN EXTERNAL INDIRECT OPERAND
 */

mach_op
*make_extern_ind(char *nm, long d)
{
    mach_op *p1 = new_mach_op ();
    mach_op *p2 = new_mach_op ();
    p1->type = MACH_CONT;
    p1->def.num = 0;
    p1->of = p2;
    p2->type = MACH_EXT;
    p2->def.str = nm;
    if (d) {
		mach_op *p3 = new_mach_op ();
		p3->type = MACH_VAL;
		p3->def.num = d;
		p2->plus = p3;
    }
    return (p1);
}


/*
 *    MAKE A REGISTER DIRECT OPERAND
 */

mach_op
*make_register(int r)
{
    mach_op *p = new_mach_op ();
    p->type = MACH_REG;
    p->def.num = (long) r;
    return (p);
}

/*
 *    MAKE PSEUDO OPERAND REPRESENTING LDISP
 *    (the space between sp and the parameters at procedure entry)
 */

mach_op
*make_ldisp(long offset)
{
    mach_op *p1 = new_mach_op ();
    p1->type = MACH_SPEC;
    p1->def.str = special_str;
    if (offset) {
		p1->plus = new_mach_op ();
		p1->plus->type = MACH_VAL;
		p1->plus->def.num = offset;
    }
    return (p1);
}


/*
 *    MAKE A REGISTER INDIRECT WITH DISPLACEMENT OPERAND
 *
 *    This is the first example where a temporary register may be required.
 *    Under very rare circumstances, we may be trying to address relative
 *    to a D-register, if which case we need to use a temporary A-register
 *    instead.
 */

mach_op
*make_indirect(int r, long d)
{
    mach_op *p1 = new_mach_op ();
    mach_op *p2 = new_mach_op ();
    p1->type = MACH_CONT;
    p1->def.num = regmsk (r);
    p2->type = MACH_REG;
    p2->def.num = (long) r;
    if (is_dreg (r)) {
		int t = tmp_reg (m_movl, p2);
		p2 = new_mach_op ();
		p2->type = MACH_REG;
		p2->def.num = (long) t;
		p1->def.num = regmsk (t);
    }
    p1->of = p2;
    if (d) {
		mach_op *p3 = new_mach_op ();
		p3->type = MACH_VAL;
		p3->def.num = d;
		p2->plus = p3;
    }
    return (p1);
}


/*
 *    MAKE A APPLICATION POINTER INDIRECT WITH DISPLACEMENT OPERAND
 *
 *    Since we don't want to use an applications pointer unless absolutely
 *    necessary, this is often changed into a stack pointer indirect
 *    with displacement operand.
 */

mach_op
*make_rel_ap(long d)
{
    mach_op *p1 = new_mach_op ();
    mach_op *p2 = new_mach_op ();
    p1->type = MACH_CONT;
    p1->def.num = 0;
    p2->type = MACH_REG;
    p1->of = p2;
    if (d > 0) {
		if (!used_stack) {
			/* Use stack pointer instead of application pointer */
			long s = stack_size + stack_change;
			mach_op *p3 = new_mach_op ();
			mach_op *p4 = new_mach_op ();
			p2->def.num = (long) REG_SP;
			p3->type = MACH_SPEC;
			p3->def.str = special_str;
			p2->plus = p3;
			p4->type = MACH_VAL;
			p4->def.num = d - s / 8;
			p3->plus = p4;
			used_ldisp = 1;
			return (p1);
		}
		d += 4;
    }
    p2->def.num = (long) REG_AP;
    if (d) {
		mach_op *p3 = new_mach_op ();
		p3->type = MACH_VAL;
		p3->def.num = d;
		p2->plus = p3;
    }
    used_stack = 1;
    return (p1);
}

#ifndef tdf3
/*
 *    MAKE A 2. APPLICATION POINTER INDIRECT WITH DISPLACEMENT OPERAND
 *
 *    This application pointer A5 is used by general proc. to access
 *    the caller parameters, when there are a dynamic number of callees.
 */

mach_op
*make_rel_ap2(long d)
{
    mach_op *p1 = new_mach_op ();
    mach_op *p2 = new_mach_op ();
    mach_op *p3 = new_mach_op ();
	
    p1->type = MACH_CONT;
    p1->def.num = 0;
    p2->type = MACH_REG;
    p1->of = p2;
    p2->def.num = (long) REG_A5;
	
    p3->type = MACH_VAL;
    p3->def.num = d;
    p2->plus = p3;
	
    used_stack = 1;
    return (p1);
}
/*
 *   Used to access caller parrameters in the postlude.
 */

mach_op
*make_rel_sp(long d)
{
    mach_op *p1 = new_mach_op ();
    mach_op *p2 = new_mach_op ();
    mach_op *p3 = new_mach_op ();
    long s = stack_size + stack_change;
	
    p1->type = MACH_CONT;
    p1->def.num = 0;
    p1->of = p2;
	
    p2->type = MACH_REG;
    p2->def.num = (long) REG_SP;
    p2->plus = p3;
	
    p3->type = MACH_VAL;
    p3->def.num = d - s / 8;
	
    return (p1);
}

#endif

/*
 *    MAKE A REGISTER INDIRECT WITH INDEX OPERAND
 *
 *    Again we have to be careful, in case r1 is a D-register.
 */

mach_op
*make_reg_index(int r1, int r2, long d, int sf)
{
    mach_op *p1 = new_mach_op ();
    mach_op *p2 = new_mach_op ();
    mach_op *p3 = new_mach_op ();
    mach_op *p4 = new_mach_op ();
    p1->type = MACH_CONT;
    p2->type = MACH_REG;
    p2->def.num = (long) r1;
    if (is_dreg (r1)) {
		int t = tmp_reg (m_movl, p2);
		p2 = new_mach_op ();
		p2->type = MACH_REG;
		p2->def.num = (long) t;
		p1->def.num = (regmsk (t) | regmsk (r2));
    } else {
		p1->def.num = (regmsk (r1) | regmsk (r2));
    }
    p1->of = p2;
    p2->plus = p3;
    p3->type = MACH_SCALE;
    p3->def.num = (long) sf;
    p3->of = p4;
    p4->type = MACH_REG;
    p4->def.num = (long) r2;
    if (d) {
		mach_op *p5 = new_mach_op ();
		p5->type = MACH_VAL;
		p5->def.num = d;
		p3->plus = p5;
    }
    return (p1);
}


/*
 *    MAKE A APPLICATION POINTER INDEXED WITH DISPLACEMENT OPERAND
 *
 *    It is always quicker to do this using a temporary register rather
 *    than using the complex addressing mode.  However we do use the
 *    latter course when temporary registers are short.
 *
 *    Typ determines the type of the application pointer.
 */

mach_op
*_make_ind_rel_ap(long d, long e, int typ)
{
    mach_op *p1, *p2;
	
    switch (typ) {
    case par2_pl :
		p2 = make_rel_ap2 (d);
		break;
    case par3_pl :
		p2 = make_rel_sp (d);
		break;
    default :
		p2 = make_rel_ap (d);
    }
	
    if (tmp_reg_status < 2) {
		int t = tmp_reg (m_movl, p2);
		return (make_indirect (t, e));
    }
	
    debug_warning ("Complex operand");
	
    p1 = new_mach_op ();
    p1->type = MACH_CONT;
    p1->def.num = 0;
    p1->of = p2;
    if (e) {
		mach_op *p3 = new_mach_op ();
		p3->type = MACH_VAL;
		p3->def.num = e;
		p2->plus = p3;
    }
    return (p1);
}

mach_op
*make_ind_rel_ap(long d, long e)
{
	return _make_ind_rel_ap (d, e, 0);
}

mach_op
*make_ind_rel_ap2(long d, long e)
{
	return _make_ind_rel_ap (d, e, par2_pl);
}
mach_op
*make_ind_rel_ap3(long d, long e)
{
	return _make_ind_rel_ap (d, e, par3_pl);
}



/*
 *    MAKE A PRE-DECREMENT STACK POINTER OPERAND
 */

mach_op
*make_dec_sp()
{
    mach_op *p = new_mach_op ();
    p->type = MACH_DEC;
    p->def.num = (long) REG_SP;
    return (p);
}


/*
 *    MAKE A POST-INCREMENT STACK POINTER OPERAND
 */

mach_op
*make_inc_sp()
{
    mach_op *p = new_mach_op ();
    p->type = MACH_INC;
    p->def.num = (long) REG_SP;
    return (p);
}

#ifndef tdf3
/*
 *    MAKE A PRE-DECREMENT REGISTER OPERAND
 */

mach_op
*make_predec(int r)
{
    mach_op *p = new_mach_op ();
    p->type = MACH_DEC;
    p->def.num = (long) r;
    return (p);
}
#endif

/*
 *    MAKE A POSTINCREMENT REGISTER OPERAND
 */

mach_op
*make_postinc(int r)
{
    mach_op *p = new_mach_op ();
    p->type = MACH_INC;
    p->def.num = (long) r;
    return (p);
}


/*
 *    MAKE A REGISTER PAIR
 */

mach_op
*make_reg_pair(int r1, int r2)
{
    mach_op *p1 = new_mach_op ();
    mach_op *p2 = new_mach_op ();
    p1->type = MACH_RPAIR;
    p1->def.num = (long) r1;
    p1->plus = p2;
    p2->type = MACH_REG;
    p2->def.num = (long) r2;
    return (p1);
}


/*
 *    MAKE AN INDEX OPERAND
 *
 *    The machine operands op1 and op2 are turned into an index operand
 *    with scale factor sf.  Unless op1 is very simple or temporary
 *    registers are short, it is always quicker to move the contents of
 *    op1 into a temporary register.  A temporary register may also be
 *    required for op2, but hopefully not too often.
 */

mach_op
*make_index_op(mach_op *op1, mach_op *op2,
			   int sf)
{
    bitpattern u;
    bool use_tmp = 1;
    mach_op *p1, *p2 = new_mach_op ();
	
    if (op1->type != MACH_CONT) {
		error ("Illegal indexing operand");
		return (null);
    }
	
    p1 = op1->of;
    u = op1->def.num;
    if (p1->type == MACH_REG) {
		use_tmp = is_dreg (p1->def.num);
    } else if (tmp_reg_status && op2->type != MACH_REG) {
		if (p1->type == MACH_EXT && p1->plus == null) {
			p1->type = MACH_EXTQ;
			use_tmp = 0;
		} else if (p1->type == MACH_CONT) {
			mach_op *q = p1->of;
			if (q->type == MACH_REG) {
				q = q->plus;
				if (q == null || q->type != MACH_SCALE) use_tmp = 0;
			}
		}
    }
	
    if (use_tmp) {
		int t = tmp_reg (m_movl, p1);
		p1 = new_mach_op ();
		p1->type = MACH_REG;
		p1->def.num = (long) t;
		u = regmsk (t);
    }
    op1->of = p1;
    p2->type = MACH_SCALE;
    p2->def.num = (long) sf;
    p2->plus = p1->plus;
    p1->plus = p2;
    if (op2->type == MACH_REG) {
		u |= regmsk (op2->def.num);
    } else {
		int t = tmp_reg (m_movl, op2);
		op2 = new_mach_op ();
		op2->type = MACH_REG;
		op2->def.num = (long) t;
		u |= regmsk (t);
    }
    p2->of = op2;
    op1->def.num = u;
    return (op1);
}


/*
 *    MAKE A BITFIELD OPERAND
 *
 *    The machine operand op is turned into the corresponding bitfield
 *    operand.
 */

mach_op
*make_bitfield_op(mach_op *op, int bf_off,
				  int bf_bits)
{
    mach_op *p1 = new_mach_op ();
    mach_op *p2 = new_mach_op ();
    p1->type = MACH_BF;
    p1->def.num = (long) bf_off;
    p1->plus = p2;
    p1->of = op;
    p2->type = MACH_VAL;
    p2->def.num = (long) bf_bits;
    return (p1);
}
