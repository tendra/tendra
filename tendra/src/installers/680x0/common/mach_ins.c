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
 *Revision 1.4  1997/11/13 08:27:13  ma
 *All avs test passed (except add_to_ptr).
 *
 *Revision 1.3  1997/11/10 15:38:06  ma
 *.
 *
 *Revision 1.2  1997/11/09 14:13:58  ma
 *comment.
 *
 *Revision 1.1.1.1  1997/10/13 12:42:55  ma
 *First version.
 *
 *Revision 1.5  1997/10/13 08:49:35  ma
 *Made all pl_tests for general proc & exception handling pass.
 *
 *Revision 1.4  1997/06/18 10:09:36  ma
 *Checking in before merging with Input Baseline changes.
 *
 *Revision 1.3  1997/05/13 11:30:34  ma
 *Introduced make_comment for debug.
 *
 *Revision 1.2  1997/04/20 11:30:31  ma
 *Introduced gcproc.c & general_proc.[ch].
 *Added cases for apply_general_proc next to apply_proc in all files.
 *
 *Revision 1.1.1.1  1997/03/14 07:50:14  ma
 *Imported from DRA
 
 * Revision 1.1.1.1  1996/09/20  10:56:55  john
 *
 * Revision 1.2  1996/07/05  14:22:21  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:14  john
 *
 * Revision 1.2  94/02/21  15:59:49  15:59:49  ra (Robert Andrews)
 * Add a couple of explicit casts.  Some flags which used to be bool are
 * now int.
 *
 * Revision 1.1  93/02/22  17:16:02  17:16:02  ra (Robert Andrews)
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
extern bool have_cond;

#ifdef EBUG
extern bool seek_label;
extern bool seek_extern;
extern int seek_label_no;
extern char *seek_extern_id;
#endif


/*
 *    OUTPUT FLAG
 *
 *    If this is true, all instructions are output immediately.  This
 *    effectively switches off all peephole optimizations.
 */

int output_immediately = 0;

/*
 *    LIST OF ALL INSTRUCTIONS
 *
 *    A list of all instructions in maintained.  The current instruction is
 *    given by current_ins.
 */

mach_ins *all_mach_ins = null;
mach_ins *current_ins = null;


/*
 *    RECORD OF LAST JUMP AND REGISTERS CHANGED SINCE
 *
 *    This is used to help get a more accurate idea of which registers
 *    are known during the peephole optimizations.
 */

long last_jump = -1;
bitpattern last_jump_regs = 0;


/*
 *    LIST OF FREE INSTRUCTIONS
 *
 *    A list of free mach_ins's, linked by their next field, is maintained.
 */

static mach_ins *mach_ins_list = null;


/*
 *    FREE A SINGLE INSTRUCTION AND ITS OPERANDS
 *
 *    The operands of the instruction are freed and the instruction
 *    itself is added to the list of all free instructions.
 */

void
reclaim_ins(mach_ins *p)
{
    if (p->op1) free_mach_op (p->op1);
    if (p->op2) free_mach_op (p->op2);
    p->next = mach_ins_list;
    mach_ins_list = p;
    return;
}


/*
 *    FREE ALL INSTRUCTIONS AND THEIR OPERANDS
 *
 *    All the instructions in the list of all instructions are freed and
 *    the list is reset to zero length.
 */

void
free_all_ins()
{
    mach_ins *p = all_mach_ins, *q = null;
    if (p == null) return;
    while (p != null) {
		if (p->op1) free_mach_op (p->op1);
		if (p->op2) free_mach_op (p->op2);
		q = p;
		p = p->next;
    }
    q->next = mach_ins_list;
    mach_ins_list = all_mach_ins;
    all_mach_ins = null;
    current_ins = null;
    last_jump = -1;
    last_jump_regs = 0;
    return;
}


/*
 *    CREATE A NEW INSTRUCTION
 *
 *    A new instruction, with instruction number insno and operands op1 and
 *    op2 is added to the list of all instructions.  ch gives the mask of
 *    all registers changed by the instruction.  If susp is true then
 *    this instruction is never output immediately.  This only occurs in
 *    tmp_reg.
 *
 *    This routine is usual called via the macro make_instr which has the
 *    same first four arguments, but has susp always false.
 */

#ifdef EBUG
static int next_id = 0;
#endif

void
make_instr_aux(int insno, mach_op *op1, mach_op *op2,
			   bitpattern ch, int susp)
{
    mach_ins *p;
    if (insno != m_comment) {
		if (stack_change) update_stack ();
    }
    if (mach_ins_list == null) {
		int i, n = 1000;
		mach_ins_list = alloc_nof (mach_ins, n);
		for (i = 0 ; i < n - 1 ; i++) {
			(mach_ins_list + i)->next = mach_ins_list + (i + 1);
		}
		(mach_ins_list + (n - 1))->next = null;
    }
    p = mach_ins_list;
    mach_ins_list = p->next;
#ifdef EBUG
    p->id = ++ next_id;
#if 1
    if (p->id == 4803) {
		int found = 1;
    }
#endif
#endif
    p->ins_no = insno;
    p->op1 = op1;
    p->op2 = op2;
    p->changed = ch;
    last_jump_regs |= ch;
    if (current_ins == null) {
		p->next = all_mach_ins;
		all_mach_ins = p;
    } else {
		p->next = current_ins->next;
		current_ins->next = p;
    }
    current_ins = p;
	
    if (insno != m_comment) {
		/* Clear the temporary register status */
		tmp_reg_status = 0;
		tmp_reg_prefer = 0;
    }
	
    if (output_immediately && !susp) {
		output_all ();
		free_all_ins ();
    }
    return;
}


/*
 *    CREATE A LABEL
 *
 *    A label is added to the list of all instructions.  This has the effect
 *    of marking all registers as changed.
 */

void
make_label(long n)
{
    mach_op *p = new_mach_op ();
    p->type = MACH_LABQ;
    p->def.num = n;
    make_instr_aux (m_label_ins, p, null, (bitpattern) 0xffff, 0);
    have_cond = 0;
#ifdef EBUG
    if (seek_label && n == (long) seek_label_no) {
		warning ("Label %ld used", n);
		breakpoint ();
    }
#endif
    return;
}

#ifdef EBUG

void
make_comment(char* comment)
{
    mach_op *p;
	
    p = new_mach_op ();
    p->type = MACH_COMMENT;
    p->def.str = comment;
    make_instr_aux (m_comment, p, null, (bitpattern) 0x0000, 0);
	
    return;
}
#endif

/*
 *    CREATE AN EXTERNAL LABEL
 *
 *    An external label is added to the list of all instructions.  This has
 *    the effect of marking all registers as changed.
 */

void
make_external_label(char *nm)
{
    mach_op *p = new_mach_op ();
    p->type = MACH_EXTQ;
    p->def.str = nm;
    make_instr_aux (m_extern_ins, p, null, (bitpattern) 0xffff, 0);
    have_cond = 0;
#ifdef EBUG
    if (seek_extern && eq (nm, seek_extern_id)) {
		warning ("Label %s used", nm);
		breakpoint ();
    }
#endif
    return;
}


/*
 *    CREATE A JUMP
 *
 *    A jump, instruction number insno, to label n, is added to the list
 *    of all instructions.
 */

void
make_jump(int insno, long n)
{
    mach_op *p = new_mach_op ();
    p->type = MACH_LABQ;
    p->def.num = n;
    make_instr_aux (insno, p, null, (bitpattern) 0, 0);
    if (n != last_jump) {
		last_jump = n;
		last_jump_regs = 0;
    }
    return;
}


/*
 *    SET A SPECIAL LABEL VALUE
 *
 *    The special label with identifier nm is set equal to the given value.
 */

void
set_special(char *nm, mach_op *op)
{
    mach_op *op1 = make_special_data (nm);
    make_instr_aux (m_as_assign, op1, op, (bitpattern) 0, 0);
    return;
}


/*
 *    OUTPUT AN IDENTIFICATION OF TWO NAMES
 *
 *    This is not required, since all link information is known by the
 *    time I get round to code production.
 */

void
out_rename(char *old_nm, char *nm)
{
#if 0
    mach_op *op1 = make_extern_data (old_nm, 0);
    mach_op *op2 = make_extern_data (nm, 0);
    make_instr_aux (m_as_assign, op1, op2, 0, 0);
#endif
    return;
}
