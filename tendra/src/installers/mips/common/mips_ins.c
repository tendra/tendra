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
 *Revision 1.2  2002/11/21 22:31:09  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
 ***********************************************************************/
/*****************************************************************
 *		mips_ins.c
 *
 *This file defines the MIPS instruction set as C strings for use by assembler
 *producing routines such as make_code.
 *Each MIPS instruction is a unique string starting with  i_ using MIPS
 * names  with . replaced by _
 *The first character of each string is  (binasm coding +1) for the instruction

*****************************************************************/

#include "config.h"
#include "mips_ins.h"

char *i_la = "\45la";
char *i_lb = "\46lb";
char *i_lbu = "\47lbu";
char *i_lh = "\50lh";
char *i_lhu = "\51lhu";
char *i_lw = "\53lw";
char *i_lwc1 = "\55lwc1";
char *i_lwl = "\134lwl";
char *i_sb = "\107sb";
char *i_sh = "\115sh";
char *i_sw = "\130sw";
char *i_swc1 = "\64swc1";
char *i_swl = "\136swl";
char *i_swr = "\137swr";
char *i_ulh = "\320ulh";
char *i_ulhu = "\321ulhu";
char *i_ulw = "\317ulw";
char *i_ush = "\323ush";
char *i_usw = "\322usw";
char *i_rfe = "\104rfe";
char *i_syscall = "\131syscall";
char *i_break = "\34break";
char *i_nop = "\77nop";
char *i_li = "\52li";
char *i_lui = "\316lui";
char *i_abs = "\1abs";
char *i_neg = "\76neg";
char *i_negu = "\334negu";
char *i_not = "\133not";
char *i_add = "\2add";
char *i_addu = "\3addu";
char *i_and = "\4and";
char *i_div = "\41div";
char *i_divu = "\42divu";
char *i_xor = "\132xor";
char *i_mul = "\71mul";
char *i_mulo = "\72mulo";
char *i_mulou = "\73mulou";
char *i_nor = "\100nor";
char *i_or = "\101or";
char *i_rem = "\102rem";
char *i_remu = "\103remu";
char *i_rol = "\105rol";
char *i_ror = "\106ror";
char *i_seq = "\110seq";
char *i_slt = "\121slt";
char *i_sltu = "\122sltu";
char *i_sle = "\116sle";
char *i_sleu = "\117sleu";
char *i_sgt = "\113sgt";
char *i_sgtu = "\114sgtu";
char *i_sge = "\111sge";
char *i_sgeu = "\112sgeu";
char *i_sne = "\123sne";
char *i_sll = "\120sll";
char *i_sra = "\124sra";
char *i_srl = "\125srl";
char *i_sub = "\126sub";
char *i_subu = "\127subu";
char *i_mult = "\74mult";
char *i_multu = "\75multu";
char *i_b = "\5b";
char *i_bc1t = "\11bc1t";
char *i_bc1f = "\10bc1f";
char *i_beq = "\16beq";
char *i_bgt = "\22bgt";
char *i_bge = "\17bge";
char *i_bgeu = "\20bgeu";
char *i_bgtu = "\23bgtu";
char *i_blt = "\30blt";
char *i_bltu = "\31bltu";
char *i_ble = "\25ble";
char *i_bleu = "\26bleu";
char *i_bne = "\33bne";
char *i_bal = "\344bal";
char *i_beqz = "\335beqz";
char *i_bgez = "\21bgez";
char *i_bgezal = "\345bgezal";
char *i_bgtz = "\24bgtz";
char *i_blez = "\27blez";
char *i_bltz = "\32bltz";
char *i_bltzal = "\346bltzal";
char *i_bnez = "\336bnez";
char *i_j = "\43j";
char *i_jal = "\44jal";
char *i_move = "\62move";
char *i_mfhi = "\60mfhi";
char *i_mthi = "\67mthi";
char *i_mflo = "\61mflo";
char *i_mfc1 = "\142mfc1";
char *i_mtc1 = "\146mtc1";
char *i_cfc1 = "\342cfc1";
char *i_ctc1 = "\343ctc1";
char *i_l_d = "\170l.d";
char *i_l_s = "\167l.s";
char *i_s_d = "\173s.d";
char *i_s_s = "\172s.s";
char *i_mov_s = "\214mov.s";
char *i_mov_d = "\215mov.d";
char *i_abs_d = "\220abs.d";
char *i_abs_s = "\217abs.s";
char *i_add_d = "\176add.d";
char *i_add_s = "\175add.s";
char *i_div_s = "\206div.s";
char *i_div_d = "\207div.d";
char *i_mul_d = "\204mul.d";
char *i_mul_s = "\203mul.s";
char *i_sub_d = "\201sub.d";
char *i_sub_s = "\200sub.s";
char *i_cvt_s_d = "\222cvt.s.d";
char *i_cvt_d_s = "\225cvt.d.s";
char *i_cvt_s_w = "\224cvt.s.w";
char *i_cvt_d_w = "\227cvt.d.w";
char *i_cvt_w_d = "\234cvt.w.d";
char *i_cvt_w_s = "\233cvt.w.s";
char *i_neg_d = "\340neg.d";
char *i_neg_s = "\337neg.s";
char *i_c_eq_s = "\244c.eq.s";
char *i_c_eq_d = "\245c.eq.d";
char *i_c_lt_s = "\302c.lt.s";
char *i_c_lt_d = "\303c.lt.d";
char *i_c_le_s = "\310c.le.s";
char *i_c_le_d = "\311c.le.d";

char *i_trunc_w_s = "\351trunc.w.s";
char *i_trunc_w_d = "\352trunc.w.d";
char *i_round_w_s = "\354round.w.s";
char *i_round_w_d = "\355round.w.d";
