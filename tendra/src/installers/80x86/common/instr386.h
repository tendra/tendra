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


/* 80x86/instr386decs.h */

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
 * Revision 1.17  1997/10/10  18:25:22  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.16  1996/11/08  16:19:19  pwe
 * check_stack to check before modifying stack
 *
 * Revision 1.15  1996/07/31  12:57:19  pwe
 * restore alloca stack after longjump
 *
 * Revision 1.14  1996/05/20  14:30:33  pwe
 * improved 64-bit handling
 *
 * Revision 1.13  1996/05/13  12:51:59  pwe
 * undo premature commit
 *
 * Revision 1.11  1996/01/10  14:00:01  pwe
 * apply with varcallees within postlude
 *
 * Revision 1.10  1995/09/26  16:47:00  pwe
 * compare with zero to ignore previous overflow
 *
 * Revision 1.9  1995/09/13  14:25:17  pwe
 * tidy for gcc
 *
 * Revision 1.8  1995/09/08  12:51:22  pwe
 * exceptions improved
 *
 * Revision 1.7  1995/09/05  16:25:03  pwe
 * specials and exception changes
 *
 * Revision 1.6  1995/08/30  16:06:45  pwe
 * prepare exception trapping
 *
 * Revision 1.5  1995/08/23  09:42:53  pwe
 * track fpu control word for trap etc
 *
 * Revision 1.4  1995/08/14  13:53:51  pwe
 * several corrections, tail calls and error jumps
 *
 * Revision 1.3  1995/08/04  08:29:35  pwe
 * 4.0 general procs implemented
 *
 * Revision 1.2  1995/01/30  12:56:25  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:34:48  jmf
 * Initial revision
 *
 **********************************************************************/


/**********************************************************************
 *                        instr386decs.h
 *
 *   declares the higher level routines which output 80x86 instructions.

**********************************************************************/

#ifndef i386_key
#define i386_key 1


extern  void add(shape sha, where a1, where a2, where dest);
extern  void absop(shape sha, where a1, where dest);
extern  void maxop(shape sha, where a1, where a2, where dest);
extern  void minop(shape sha, where a1, where a2, where dest);
extern  void sub(shape sha, where min, where from, where dest);
extern  void mult(shape sha, where a1, where a2, where dest);
extern  void multiply(shape sha, where a1, where a2, where dest);
extern  void div0(shape sha, where bottom, where top, where dest);
extern  void div1(shape sha, where bottom, where top, where dest);
extern  void div2(shape sha, where bottom, where top, where dest);
extern  int cmp(shape sha, where from, where min, int nt, exp e);
extern  void negate(shape sha, where a, where dest);
extern  void move(shape sha, where from, where to);
extern  void mova(where from, where to);
extern  void and(shape sha, where a1, where a2, where dest);
extern  void or(shape sha, where a1, where a2, where dest);
extern  void xor(shape sha, where a1, where a2, where dest);
extern  void not(shape sha, where a, where dest);
extern  void change_var(shape sha, where from, where to);
extern  void change_var_check(shape sha, where from, where to);
extern  void change_var_sh(shape sha, shape fsh, where from, where to);
extern  void floater(shape sha, where from, where to);
extern  void frnd0(shape sha, where from, where to);
extern  void frnd1(shape sha, where from, where to);
extern  void frnd2(shape sha, where from, where to);
extern  void frnd3(shape sha, where from, where to);
extern  void frnd4(shape sha, where from, where to);
extern  void changefl(shape sha, where from, where to);
extern  void shiftl(shape sha, where wshift, where from, where to);
extern  void shiftr(shape sha, where wshift, where from, where to);
extern  void rotatel(shape sha, where wshift, where from, where to);
extern  void rotater(shape sha, where wshift, where from, where to);
extern  void mod(shape sha, where bottom, where top, where dest);
extern  void rem2(shape sha, where bottom, where top, where dest);
extern  void rem0(shape sha, where bottom, where top, where dest);
extern  void long_jump(exp e);
extern  void initzeros(void);
extern  where zero;
extern  where fzero;
extern  where dzero;
extern  exp zeroe;
extern  where ind_reg0;
extern  where ind_reg1;
extern  where ind_sp;
extern  where sp;
extern  where bp;
extern  where reg0;
extern  where reg1;
extern  where reg2;
extern  where reg3;
extern  where reg4;
extern  where reg5;
extern  where reg_wheres[7];
extern  where pushdest;
extern  where cond1;
extern  where cond2a;
extern  where cond2b;
extern  int cond1_set;
extern  int cond2_set;
extern  void decstack(int longs);
extern  void callins(int longs, exp ind, int ret_stack_dec);
extern  void jumpins(exp ind);
extern  void retins(void);
extern  int inmem(where w);
extern  void fl_binop(unsigned char op, shape sha, where arg1, where arg2,
					  where dest, exp last_arg);
extern  void fl_multop(unsigned char op, shape sha, exp arglist, where dest);
extern  void fl_neg(shape sha, where from, where to);
extern  void fl_abs(shape sha, where from, where to);
extern  void test(shape sha, where a, where b);
extern  void fl_comp(shape sha, where pos, where neg, exp e);
extern  where flstack;
extern  int in_fl_reg(exp e);
extern  int in_fstack(exp e);
extern  void movecont(where from, where to, where length, int nooverlap);
extern  void load_stack0(void);
extern  int in_reg(exp e);
extern  void end_contop(void);
extern  int top_regsinuse;
extern  int lsmask[33];
extern  int first_fl_reg;
extern  int fstack_pos;
extern  exp overflow_e;
extern  void stack_return (int longs);
extern  int bad_from_reg(where f);

extern  void bits_to_mem(exp e, exp d, ash stack);
extern  void mem_to_bits(exp e, shape sha, where dest, ash stack);

extern  void setup_fl_ovfl(exp e);
extern  void test_fl_ovfl(exp e, where dest);
extern void reset_fpucon(void);
extern exp find_stlim_var(void);
extern void checkalloc_stack(where sz, int b);	/* uses reg1 */
extern void special_ins(char * id, exp args, where dest);

extern exp ferrmem;
extern int ferrsize;
extern int fpucon;
extern int cmp_64hilab;

extern void save_stack(void);
extern void restore_stack(void);

extern void start_asm(void);
extern void end_asm(void);
extern void asm_ins(exp e);


#endif

