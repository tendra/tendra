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
 *Revision 1.2  2002/11/21 22:31:05  nonce
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
 * Revision 1.3  1998/03/11  11:03:40  pwe
 * DWARF optimisation info
 *
 * Revision 1.2  1998/02/18  11:22:18  pwe
 * test corrections
 *
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 **********************************************************************/


#include "config.h"
#include "dw2_entries.h"
#include "dw2_config.h"
#include "dw2_basic.h"
#include "basicread.h"

static long empty[] = { -1 };

static long x_variable[] = {
	H_AO | H_SS | H_LC,
	H_AO | H_SS | H_LL,
	H_AO | H_SS | H_LL | H_LE,
	H_AO | H_SS | H_CV,
	H_NM | H_XY | H_EX | H_TP | H_LC,
	H_NM | H_XY | H_EX | H_TP | H_LL,
	H_NM | H_XY | H_EX | H_TP | H_LL | H_LE,
	H_NM | H_XY | H_TP | H_SS | H_LC,
	H_NM | H_XY | H_TP | H_SS | H_LL,
	H_NM | H_XY | H_TP | H_SS | H_LL | H_LE,
	H_NM | H_XY | H_TP | H_SS | H_CV,
	H_NM | H_XY | H_TP | H_CV,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_TP | H_LC,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_TP | H_LL,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_TP | H_LL | H_LE,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_TP | H_CV,
	H_DC | H_NM | H_XY | H_AT | H_TP | H_SS | H_LC,
	H_DC | H_NM | H_XY | H_AT | H_TP | H_SS | H_LL,
	H_DC | H_NM | H_XY | H_AT | H_TP | H_SS | H_LL | H_LE,
	H_DC | H_NM | H_XY | H_AT | H_TP | H_SS | H_CV,
	H_DC | H_NM | H_XY | H_TP,
	H_DC | H_NM | H_XY | H_EX | H_TP,
	H_SP | H_XY | H_EX | H_LC,
	H_SP | H_XY | H_EX | H_LL,
	H_SP | H_XY | H_EX | H_LL | H_LE,
	H_SP | H_XY | H_EX | H_CV,
	H_SP | H_XY | H_SS | H_LC,
	H_SP | H_XY | H_SS | H_LL,
	H_SP | H_XY | H_SS | H_LL | H_LE,
	H_SP | H_XY | H_SS | H_CV,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_AC | H_TP | H_LC,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_AC | H_TP | H_LL,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_AC | H_TP | H_LL | H_LE,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_AC | H_TP | H_CV,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_TP | H_SS | H_LC,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_TP | H_SS | H_LL,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_TP | H_SS | H_LL | H_LE,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_TP | H_SS | H_CV,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_TP | H_LC | H_RP,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_TP | H_LL | H_RP,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_TP | H_LL | H_LE | H_RP,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_TP | H_CV | H_RP,
	H_DC | H_NM | H_XY | H_AT | H_TP | H_SS | H_LC | H_RP,
	H_DC | H_NM | H_XY | H_AT | H_TP | H_SS | H_LL | H_RP,
	H_DC | H_NM | H_XY | H_AT | H_TP | H_SS | H_LL | H_LE | H_RP,
	H_DC | H_NM | H_XY | H_AT | H_TP | H_SS | H_CV | H_RP,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_AC | H_TP | H_LC | H_RP,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_AC | H_TP | H_LL | H_RP,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_AC | H_TP | H_LL | H_LE | H_RP,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_AC | H_TP | H_CV | H_RP,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_TP | H_SS | H_LC | H_RP,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_TP | H_SS | H_LL | H_RP,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_TP | H_SS | H_LL | H_LE | H_RP,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_TP | H_SS | H_CV | H_RP,
	0 };

#define y_variable (H_DC|H_NM|H_XY|H_EX|H_AT)

static long x_constant[] = {
	H_NM | H_XY | H_TP | H_EX | H_CV,
	H_NM | H_XY | H_TP | H_SS | H_CV,
	0 };

#define y_constant (H_DC|H_NM|H_XY|H_EX|H_AT|H_VP)

static long x_param[] = {
	H_AO | H_LC,
	H_AO | H_CV,
	H_TP,
	H_NM | H_XY | H_TP,
	H_NM | H_XY | H_TP | H_VP,
	H_NM | H_XY | H_TP | H_VP | H_LL,
	H_NM | H_XY | H_TP | H_VP | H_LL | H_LE,
	H_NM | H_XY | H_TP | H_AT | H_VP,
	H_NM | H_XY | H_TP | H_AT | H_VP | H_LL,
	H_NM | H_XY | H_TP | H_AT | H_VP | H_LL | H_LE,
	H_NM | H_XY | H_TP | H_AC | H_VP,
	H_NM | H_XY | H_TP | H_AC | H_VP | H_LL,
	H_NM | H_XY | H_TP | H_AC | H_VP | H_LL | H_LE,
	H_NM | H_XY | H_TP | H_AT | H_AC | H_VP,
	H_NM | H_XY | H_TP | H_AT | H_AC | H_VP | H_LL,
	H_NM | H_XY | H_TP | H_AT | H_AC | H_VP | H_LL | H_LE,
	H_AO | H_LL,
	H_AO | H_LL | H_LE,
	H_TP | H_DF,
	H_NM | H_XY | H_TP | H_DF,
	H_NM | H_XY | H_TP | H_VP | H_DF,
	H_NM | H_XY | H_TP | H_VP | H_LL | H_DF,
	H_NM | H_XY | H_TP | H_VP | H_LL | H_LE | H_DF,
	H_NM | H_XY | H_TP | H_AT | H_VP | H_DF,
	H_NM | H_XY | H_TP | H_AT | H_VP | H_LL | H_DF,
	H_NM | H_XY | H_TP | H_AT | H_VP | H_LL | H_LE | H_DF,
	H_NM | H_XY | H_TP | H_AC | H_VP | H_DF,
	H_NM | H_XY | H_TP | H_AC | H_VP | H_LL | H_DF,
	H_NM | H_XY | H_TP | H_AC | H_VP | H_LL | H_LE | H_DF,
	H_NM | H_XY | H_TP | H_AT | H_AC | H_VP | H_DF,
	H_NM | H_XY | H_TP | H_AT | H_AC | H_VP | H_LL | H_DF,
	H_NM | H_XY | H_TP | H_AT | H_AC | H_VP | H_LL | H_LE | H_DF,
#ifdef H_DX
	H_TP | H_DX,
	H_NM | H_XY | H_TP | H_DX,
	H_NM | H_XY | H_TP | H_VP | H_DX,
	H_NM | H_XY | H_TP | H_VP | H_LL | H_DX,
	H_NM | H_XY | H_TP | H_VP | H_LL | H_LE | H_DX,
	H_NM | H_XY | H_TP | H_AT | H_VP | H_DX,
	H_NM | H_XY | H_TP | H_AT | H_VP | H_LL | H_DX,
	H_NM | H_XY | H_TP | H_AT | H_VP | H_LL | H_LE | H_DX,
	H_NM | H_XY | H_TP | H_AC | H_VP | H_DX,
	H_NM | H_XY | H_TP | H_AC | H_VP | H_LL | H_DX,
	H_NM | H_XY | H_TP | H_AC | H_VP | H_LL | H_LE | H_DX,
	H_NM | H_XY | H_TP | H_AT | H_AC | H_VP | H_DX,
	H_NM | H_XY | H_TP | H_AT | H_AC | H_VP | H_LL | H_DX,
	H_NM | H_XY | H_TP | H_AT | H_AC | H_VP | H_LL | H_LE | H_DX,
#endif
	0 };

#define y_param (H_DC|H_NM|H_XY|H_AT|H_VP)

static long x_proc[] = {
	H_AO | H_PC,
	H_AO | H_PC | H_SL,
	H_AO | H_PC | H_EXTN,
	H_AO | H_PC | H_SL | H_EXTN,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_CC,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_CC | H_TP,
	H_NM | H_XY | H_EX | H_AT | H_CC | H_PC,
	H_NM | H_XY | H_EX | H_AT | H_CC | H_TP | H_PC,
	H_NM | H_XY | H_EX | H_AT | H_CC | H_IL,
	H_NM | H_XY | H_EX | H_AT | H_CC | H_TP | H_IL,
	H_DC | H_SP | H_XY | H_EX | H_CC,
	H_SP | H_XY | H_EX | H_CC | H_PC,
	H_SP | H_XY | H_EX | H_CC | H_IL,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_AC | H_CC,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_AC | H_CC | H_TP,
	H_NM | H_XY | H_EX | H_AT | H_AC | H_CC | H_PC,
	H_NM | H_XY | H_EX | H_AT | H_AC | H_CC | H_TP | H_PC,
	H_NM | H_XY | H_EX | H_AT | H_AC | H_CC | H_IL,
	H_NM | H_XY | H_EX | H_AT | H_AC | H_CC | H_TP | H_IL,
	H_DC | H_SP | H_XY | H_EX | H_AC | H_CC,
	H_SP | H_XY | H_EX | H_AC | H_CC | H_PC,
	H_SP | H_XY | H_EX | H_AC | H_CC | H_IL,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_CC | H_PT,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_CC | H_TP | H_PT,
	H_NM | H_XY | H_EX | H_AT | H_CC | H_PT | H_PC,
	H_NM | H_XY | H_EX | H_AT | H_CC | H_TP | H_PT | H_PC,
	H_NM | H_XY | H_EX | H_AT | H_CC | H_PT | H_IL,
	H_NM | H_XY | H_EX | H_AT | H_CC | H_TP | H_PT | H_IL,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_AC | H_CC | H_PT,
	H_DC | H_NM | H_XY | H_EX | H_AT | H_AC | H_CC | H_TP | H_PT,
	H_NM | H_XY | H_EX | H_AT | H_AC | H_CC | H_PT | H_PC,
	H_NM | H_XY | H_EX | H_AT | H_AC | H_CC | H_TP | H_PT | H_PC,
	H_NM | H_XY | H_EX | H_AT | H_AC | H_CC | H_PT | H_IL,
	H_NM | H_XY | H_EX | H_AT | H_AC | H_CC | H_TP | H_PT | H_IL,
	
	H_DC|H_NM|H_XY|H_EX|H_AT|H_CC|H_VT|H_EXTN,
	H_DC|H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_PC|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_PC|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_IL|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_IL|H_VT|H_EXTN,
	H_DC|H_SP|H_XY|H_EX|H_CC|H_VT|H_EXTN,
	H_SP|H_XY|H_EX|H_CC|H_PC|H_VT|H_EXTN,
	H_SP|H_XY|H_EX|H_CC|H_IL|H_VT|H_EXTN,
	H_DC|H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_VT|H_EXTN,
	H_DC|H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_PC|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_PC|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_IL|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_IL|H_VT|H_EXTN,
	H_DC|H_SP|H_XY|H_EX|H_AC|H_CC|H_VT|H_EXTN,
	H_SP|H_XY|H_EX|H_AC|H_CC|H_PC|H_VT|H_EXTN,
	H_SP|H_XY|H_EX|H_AC|H_CC|H_IL|H_VT|H_EXTN,
	H_DC|H_NM|H_XY|H_EX|H_AT|H_CC|H_PT|H_VT|H_EXTN,
	H_DC|H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_PT|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_PT|H_PC|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_PT|H_PC|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_PT|H_IL|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_PT|H_IL|H_VT|H_EXTN,
	H_DC|H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_PT|H_VT|H_EXTN,
	H_DC|H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_PT|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_PT|H_PC|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_PT|H_PC|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_PT|H_IL|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_PT|H_IL|H_VT|H_EXTN,
	
	H_DC|H_NM|H_XY|H_EX|H_AT|H_CC|H_VT|H_VL|H_EXTN,
	H_DC|H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_PC|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_PC|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_IL|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_IL|H_VT|H_VL|H_EXTN,
	H_DC|H_SP|H_XY|H_EX|H_CC|H_VT|H_VL|H_EXTN,
	H_SP|H_XY|H_EX|H_CC|H_PC|H_VT|H_VL|H_EXTN,
	H_SP|H_XY|H_EX|H_CC|H_IL|H_VT|H_VL|H_EXTN,
	H_DC|H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_VT|H_VL|H_EXTN,
	H_DC|H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_PC|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_PC|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_IL|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_IL|H_VT|H_VL|H_EXTN,
	H_DC|H_SP|H_XY|H_EX|H_AC|H_CC|H_VT|H_VL|H_EXTN,
	H_SP|H_XY|H_EX|H_AC|H_CC|H_PC|H_VT|H_VL|H_EXTN,
	H_SP|H_XY|H_EX|H_AC|H_CC|H_IL|H_VT|H_VL|H_EXTN,
	H_DC|H_NM|H_XY|H_EX|H_AT|H_CC|H_PT|H_VT|H_VL|H_EXTN,
	H_DC|H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_PT|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_PT|H_PC|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_PT|H_PC|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_PT|H_IL|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_PT|H_IL|H_VT|H_VL|H_EXTN,
	H_DC|H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_PT|H_VT|H_VL|H_EXTN,
	H_DC|H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_PT|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_PT|H_PC|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_PT|H_PC|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_PT|H_IL|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_PT|H_IL|H_VT|H_VL|H_EXTN,
	
	H_NM|H_XY|H_EX|H_AT|H_CC|H_PC|H_SL|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_PC|H_SL|H_VT|H_EXTN,
	H_SP|H_XY|H_EX|H_CC|H_PC|H_SL|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_PC|H_SL|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_PC|H_SL|H_VT|H_EXTN,
	H_SP|H_XY|H_EX|H_AC|H_CC|H_PC|H_SL|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_PT|H_PC|H_SL|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_PT|H_PC|H_SL|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_PT|H_PC|H_SL|H_VT|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_PT|H_PC|H_SL|H_VT|H_EXTN,
	
	H_NM|H_XY|H_EX|H_AT|H_CC|H_PC|H_SL|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_PC|H_SL|H_VT|H_VL|H_EXTN,
	H_SP|H_XY|H_EX|H_CC|H_PC|H_SL|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_PC|H_SL|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_PC|H_SL|H_VT|H_VL|H_EXTN,
	H_SP|H_XY|H_EX|H_AC|H_CC|H_PC|H_SL|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_PT|H_PC|H_SL|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_CC|H_TP|H_PT|H_PC|H_SL|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_PT|H_PC|H_SL|H_VT|H_VL|H_EXTN,
	H_NM|H_XY|H_EX|H_AT|H_AC|H_CC|H_TP|H_PT|H_PC|H_SL|H_VT|H_VL|H_EXTN,
	
	0 };

#define y_proc (H_DC|H_NM|H_XY|H_EX|H_AT|H_CC|H_VT|H_EXTN)
#define z_proc (H_EL|H_GN|H_RP|H_LN)

static long x_entry[] = {
	H_NM | H_XY,
	H_NM | H_XY | H_AC,
	H_NM | H_XY | H_TP,
	H_NM | H_XY | H_AC | H_TP,
	H_NM | H_XY | H_RP,
	H_NM | H_XY | H_AC | H_RP,
	H_NM | H_XY | H_TP | H_RP,
	H_NM | H_XY | H_AC | H_TP | H_RP,
	0 };

#define y_entry (H_NM|H_XY)

static long x_module[] = {
	H_AO,
	H_AO | H_PC,
	H_AO | H_EL,
	H_DC | H_NM | H_XY | H_AT,
	H_DC | H_NM | H_XY | H_AT | H_EXTN,
	H_DC | H_SP | H_XY,
	H_DC | H_NM | H_XY | H_AT | H_AC,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_EXTN,
	H_DC | H_SP | H_XY | H_AC,
	H_DC | H_NM | H_XY | H_AT | H_PC,
	H_DC | H_NM | H_XY | H_AT | H_PC | H_EXTN,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_PC,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_PC | H_EXTN,
	H_DC | H_NM | H_XY | H_AT | H_SP | H_EXTN,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_SP | H_EXTN,
	H_DC | H_NM | H_XY | H_AT | H_PC | H_SP | H_EXTN,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_PC | H_SP | H_EXTN,
	0 };

#define y_module (H_DC|H_NM|H_XY|H_AT)

static long x_namespace[] = {
	H_AO,
	H_DC | H_NM | H_XY | H_AT,
	H_DC | H_NM | H_XY | H_AT | H_EXTN,
	H_DC | H_SP | H_XY,
	H_DC | H_NM | H_XY | H_AT | H_AC,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_EXTN,
	H_DC | H_SP | H_XY | H_AC,
	0 };

#define y_namespace (H_DC|H_NM|H_XY|H_AT)

static long x_import[] = {
	0,
	H_NM | H_XY,
	H_AC,
	H_NM | H_XY | H_AC,
	H_SS,
	H_NM | H_XY | H_SS,
	H_AC | H_SS,
	H_NM | H_XY | H_AC | H_SS,
	0 };

#define y_import (H_NM|H_XY)

static long x_lexscope[] = {
	0,
	H_PC,
	H_NM | H_XY | H_PC,
	H_PC | H_BG,
	H_NM | H_XY | H_PC | H_BG,
	0 };

#define y_lexscope (H_NM|H_XY)

static long x_typedef[] = {
	0,
	H_TP,
	H_DC | H_NM | H_XY,
	H_NM | H_XY | H_TP,
	H_DC | H_NM | H_XY | H_TP,
	H_SP | H_NM | H_XY | H_TP,
	H_SP | H_NM | H_XY | H_TP | H_NW,
	H_DC | H_NM | H_XY | H_AT | H_TP | H_NW,
	H_SP | H_DC | H_NM | H_XY | H_AT | H_TP | H_NW,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_TP | H_NW,
	H_SP | H_DC | H_NM | H_XY | H_AT | H_AC | H_TP | H_NW,
	H_SP | H_NM | H_XY | H_TP | H_AD,
	H_DC | H_NM | H_XY | H_AT | H_TP | H_AD,
	H_SP | H_DC | H_NM | H_XY | H_AT | H_TP | H_AD,
	H_DC | H_NM | H_XY | H_AT | H_AC | H_TP | H_AD,
	H_SP | H_DC | H_NM | H_XY | H_AT | H_AC | H_TP | H_AD,
	H_AO,
	0 };

#define y_typedef (H_DC|H_NM|H_XY|H_AT|H_NW)

static long x_struct[] = {
	H_NM | H_SZ,
	H_SZ,
	H_DC | H_SZ,
	H_DC | H_NM | H_SZ,
	H_SP | H_SZ,
	H_SP | H_NM | H_SZ,
	H_DC | H_NM | H_XY | H_NW,
	H_DC | H_NM | H_XY | H_SZ | H_NW,
	H_SP | H_DC | H_NM | H_XY | H_NW,
	H_SP | H_DC | H_NM | H_XY | H_SZ | H_NW,
	0 };

#define y_struct (H_DC|H_NM|H_XY|H_NW)

static long x_class[] = {
	H_NM | H_SZ,
	H_SZ,
	H_DC | H_SZ,
	H_DC | H_NM | H_SZ,
	H_SP | H_SZ,
	H_SP | H_NM | H_SZ,
	H_DC | H_NM | H_XY | H_EXTN,
	H_DC | H_NM | H_XY | H_SZ | H_EXTN,
	H_SP | H_DC | H_NM | H_XY | H_EXTN,
	H_SP | H_DC | H_NM | H_XY | H_SZ | H_EXTN,
	0 };

#define y_class (H_DC|H_NM|H_XY|H_GN|H_EXTN)
#define z_class (H_NW|H_EL|H_VS|H_VD|H_RS|H_RD|H_CB|H_ID)

static long x_member[] = {
	H_NM | H_TP,
	H_NM | H_TP | H_LC,
	H_NM | H_TP | H_BF,
	H_NM | H_TP | H_LC | H_BF,
	H_NM | H_XY | H_TP,
	H_NM | H_XY | H_TP | H_LC,
	H_NM | H_XY | H_TP | H_BF,
	H_NM | H_XY | H_TP | H_LC | H_BF,
	H_NM | H_XY | H_AC | H_TP,
	H_NM | H_XY | H_AC | H_TP | H_LC,
	H_NM | H_XY | H_AC | H_TP | H_BF,
	H_NM | H_XY | H_AC | H_TP | H_LC | H_BF,
	H_NM | H_XY | H_TP | H_DS,
	H_NM | H_XY | H_TP | H_LC | H_DS,
	H_NM | H_XY | H_TP | H_BF | H_DS,
	H_NM | H_XY | H_TP | H_LC | H_BF | H_DS,
	H_NM | H_XY | H_AC | H_TP | H_DS,
	H_NM | H_XY | H_AC | H_TP | H_LC | H_DS,
	H_NM | H_XY | H_AC | H_TP | H_BF | H_DS,
	H_NM | H_XY | H_AC | H_TP | H_LC | H_BF | H_DS,
	H_NM | H_XY | H_TP | H_DS | H_DF,
	H_NM | H_XY | H_TP | H_LC | H_DS | H_DF,
	H_NM | H_XY | H_TP | H_BF | H_DS | H_DF,
	H_NM | H_XY | H_TP | H_LC | H_BF | H_DS | H_DF,
	H_NM | H_XY | H_AC | H_TP | H_DS | H_DF,
	H_NM | H_XY | H_AC | H_TP | H_LC | H_DS | H_DF,
	H_NM | H_XY | H_AC | H_TP | H_BF | H_DS | H_DF,
	H_NM | H_XY | H_AC | H_TP | H_LC | H_BF | H_DS | H_DF,
#ifdef H_DX
	H_NM | H_XY | H_TP | H_DS | H_DX,
	H_NM | H_XY | H_TP | H_LC | H_DS | H_DX,
	H_NM | H_XY | H_TP | H_BF | H_DS | H_DX,
	H_NM | H_XY | H_TP | H_LC | H_BF | H_DS | H_DX,
	H_NM | H_XY | H_AC | H_TP | H_DS | H_DX,
	H_NM | H_XY | H_AC | H_TP | H_LC | H_DS | H_DX,
	H_NM | H_XY | H_AC | H_TP | H_BF | H_DS | H_DX,
	H_NM | H_XY | H_AC | H_TP | H_LC | H_BF | H_DS | H_DX,
#endif
	0 };

#define y_member (H_NM|H_XY)

static long x_ind_mem[] = {
	H_NM | H_TP | H_LC,
	H_NM | H_XY | H_TP | H_LC,
	0 };

#define y_ind_mem (H_NM|H_XY)

static long x_inherit[] = {
	H_TP | H_LC,
	H_XY | H_TP | H_LC | H_VT,
	H_XY | H_TP | H_LC | H_AC | H_VT,
	0 };

#define y_inherit (H_XY|H_VT)

static long x_procret[] = {
	H_XY,
	H_XY | H_PC,
	H_XY | H_PC | H_LC,
	0 };

static long x_throw[] = {
	H_XY,
	H_XY | H_TP,
	H_XY | H_TP | H_LC,
	H_XY | H_TP | H_CV,
	0 };

static long x_destruct[] = {
	0,
	H_TP | H_LC,
	H_TP | H_CV,
	0 };

static long x_enum[] = {
	H_NM | H_SZ,
	H_NM | H_XY | H_SZ,
	H_SP | H_NM | H_XY | H_SZ,
	H_DC | H_NM | H_XY | H_SZ | H_NW,
	H_SP | H_DC | H_NM | H_XY | H_SZ | H_NW,
	0 };

#define y_enum (H_DC|H_NM|H_XY|H_NW)

static long x_cons_t[] = {
	H_DC | H_TP | H_SZ,
	H_DC | H_SP | H_TP | H_SZ,
	0 };

#define y_cons_t (H_DC)

static long x_subr[] = {
	0,
	H_TP | H_SZ,
	H_TP | H_SZ | H_LB,
	H_TP | H_SZ | H_LB | H_UB,
	H_TP | H_SZ | H_LB | H_CN,
	H_TP | H_SZ | H_UB,
	0 };

static long x_constraint[] = {
	H_CV,
	H_TP,
	H_RM | H_CV,
	H_RM | H_TP,
	0 };

static long x_fixpt[] = {
	0,
	H_DF,
	H_DS,
	H_DF | H_DS,
	0 };



#if 1
#define Z(a,b,c,d)	{0, a, (long)b, (long)c, d}
#else
#define Z(a,b,c,d)	{0, a, (long)b, (long)c}
#endif


abbrev_entry
dwe_comp_unit	= Z (empty, 0, 0, "compilation unit"),
	dwe_cmac_unit	= Z (empty, 0, 0, "compilation unit with macros"),
	dwe_module	= Z (x_module, y_module, 0, "module"),
	dwe_namespace	= Z (x_namespace, y_namespace, 0, "namespace"),
	dwe_subunit	= Z (empty, 0, 0, "subunit"),
	dwe_childunit	= Z (empty, 0, 0, "child unit"),
	dwe_child_acc	= Z (empty, 0, 0, "child unit_a"),
	dwe_import	= Z (x_import, y_import, 0, "import"),
	dwe_import_p	= Z (x_import, y_import, 0, "import_p"),
	dwe_entrypt	= Z (empty, 0, 0, "entry point"),
	dwe_param	= Z (x_param, y_param, 0, "formal parameter"),
	dwe_formal	= Z (empty, 0, 0, "formal parameter type"),
	dwe_opt_par	= Z (empty, 0, 0, "unspecified parameters"),
	dwe_thrown_t	= Z (empty, 0, 0, "thrown type"),
	dwe_inl_call	= Z (empty, 0, 0, "inlined call"),
	dwe_inl_opnd	= Z (empty, 0, 0, "inlined call is operand"),
	dwe_scope	= Z (x_lexscope, y_lexscope, 0, "lexical block"),
	dwe_fragment	= Z (empty, 0, 0, "lexical fragment"),
	dwe_label	= Z (empty, 0, 0, "labelled statement"),
	dwe_with	= Z (empty, 0, 0, "with statement"),
	dwe_try	= Z (empty, 0, 0, "try block"),
	dwe_catch	= Z (empty, 0, 0, "catch block"),
	dwe_variable	= Z (x_variable, y_variable, 0, "variable"),
	dwe_constant	= Z (x_constant, y_constant, 0, "constant"),
	dwe_tmpl_type	= Z (empty, 0, 0, "template type"),
	dwe_tmpl_val	= Z (empty, 0, 0, "template value"),
	dwe_tmpl_proc	= Z (empty, 0, 0, "template proc"),
	dwe_tmpl_mod	= Z (empty, 0, 0, "template module"),
	dwe_typedef	= Z (x_typedef, y_typedef, 0, "type definition"),
	dwe_typecon	= Z (x_typedef, y_typedef, 0, "type definition with constraints"),
	dwe_cnstraint	= Z (x_constraint, 0, 0, "constraint"),
	dwe_base_type	= Z (empty, 0, 0, "base type"),
	dwe_cnst_type	= Z (empty, 0, 0, "const type"),
	dwe_vol_type	= Z (empty, 0, 0, "volatile type"),
	dwe_clwd_type	= Z (empty, 0, 0, "class wide type"),
	dwe_als_type	= Z (empty, 0, 0, "aliased type"),
	dwe_lim_type	= Z (empty, 0, 0, "limited type"),
	dwe_ptr_type	= Z (empty, 0, 0, "pointer type"),
	dwe_hpptr_t	= Z (empty, 0, 0, "heap-only pointer"),
	dwe_ref_type	= Z (empty, 0, 0, "reference type"),
	dwe_pack_type	= Z (empty, 0, 0, "packed type"),
	dwe_arr_type	= Z (empty, 0, 0, "array type"),
	dwe_arr_dyn	= Z (empty, 0, 0, "array type"),
	dwe_subr_type	= Z (x_subr, 0, 0, "subrange type"),
	dwe_enum_type	= Z (x_enum, y_enum, 0, "enumeration type"),
	dwe_enum_tor	= Z (empty, 0, 0, "enumerator"),
	dwe_enum_char	= Z (empty, 0, 0, "enumerator"),
	dwe_struct_t	= Z (x_struct, y_struct, 0, "struct type"),
	dwe_member	= Z (x_member, y_member, 0, "member"),
	dwe_varpart	= Z (empty, 0, 0, "variant part discr"),
	dwe_varpart_t	= Z (empty, 0, 0, "variant part type"),
	dwe_variant_0	= Z (empty, 0, 0, "variant def"),
	dwe_variant_1	= Z (empty, 0, 0, "variant val"),
	dwe_variant_n	= Z (empty, 0, 0, "variant list"),
	dwe_union_t	= Z (x_struct, y_struct, 0, "union type"),
	dwe_class_t	= Z (x_class, y_class, z_class, "class type"),
	dwe_inheritce	= Z (x_inherit, y_inherit, 0, "inheritance"),
	dwe_friend	= Z (empty, 0, 0, "friend"),
	dwe_ptrmem_t	= Z (empty, 0, 0, "ptr to member type"),
	dwe_ind_mem	= Z (x_ind_mem, y_ind_mem, 0, "indirect member"),
	dwe_proc_type	= Z (empty, 0, 0, "subroutine type"),
	dwe_procv_t	= Z (empty, 0, 0, "subroutine type void"),
	dwe_string_t	= Z (empty, 0, 0, "string type"),
	dwe_stringc_t	= Z (empty, 0, 0, "string type, constant length"),
	dwe_file_t	= Z (x_cons_t, y_cons_t, 0, "file type"),
	dwe_set_t	= Z (x_cons_t, y_cons_t, 0, "set type"),
	dwe_fixpt_t	= Z (x_fixpt, 0, 0, "fixed point type"),
	dwe_fldg_t	= Z (empty, 0, 0, "floating digits"),
	dwe_modular_t	= Z (empty, 0, 0, "modular type"),
	dwe_task_t	= Z (x_class, y_class, z_class, "task type"),
	dwe_synch_t	= Z (x_class, y_class, z_class, "synchronous type"),
	dwe_entry	= Z (x_entry, y_entry, 0, "entry"),
	dwe_for_unit	= Z (empty, 0, 0, "foreign compunit"),
	dwe_for_lang	= Z (empty, 0, 0, "foreign language"),
	dwe_call	= Z (empty, 0, 0, "subroutine call"),
	dwe_return	= Z (x_procret, 0, 0, "subroutine return"),
	dwe_destruct	= Z (x_destruct, 0, 0, "destruct"),
	dwe_branch	= Z (empty, 0, 0, "branch"),
	dwe_branch_0	= Z (empty, 0, 0, "optimised branch"),
	dwe_break	= Z (empty, 0, 0, "breakpoint"),
	dwe_test	= Z (empty, 0, 0, "test"),
	dwe_test_0	= Z (empty, 0, 0, "optimised test"),
	dwe_jump	= Z (empty, 0, 0, "jump"),
	dwe_jump_0	= Z (empty, 0, 0, "optimised jump"),
	dwe_lj	= Z (empty, 0, 0, "long jump"),
	dwe_lj_0	= Z (empty, 0, 0, "optimised long jump"),
	dwe_throw	= Z (x_throw, 0, 0, "throw"),
	dwe_barrier	= Z (empty, 0, 0, "entry barrier"),
	dwe_select	= Z (empty, 0, 0, "select"),
	dwe_accept	= Z (empty, 0, 0, "accept"),
	dwe_accept_c	= Z (empty, 0, 0, "accept_c"),
	dwe_rts	= Z (empty, 0, 0, "rts call"),
	dwe_rts_en	= Z (empty, 0, 0, "rts entry call"),
	dwe_sel_alt	= Z (empty, 0, 0, "select alternative"),
	dwe_sel_alt_c	= Z (empty, 0, 0, "select alternative_c"),
	dwe_sel_guard	= Z (empty, 0, 0, "select guard"),
	dwe_asynchsel	= Z (empty, 0, 0, "asynchronous select"),
	dwe_trigger	= Z (empty, 0, 0, "triggering alternate"),
	dwe_trigger_c	= Z (empty, 0, 0, "triggering alternate_c"),
	dwe_abort_pt	= Z (empty, 0, 0, "abortable part"),
	dwe_abort_ptc	= Z (empty, 0, 0, "abortable part_c"),
	dwe_requeue	= Z (empty, 0, 0, "requeue"),
	dwe_unknown_t	= Z (empty, 0, 0, "unknown type"),
	dwe_span	= Z (empty, 0, 0, "source span"),
	dwe_span_strt	= Z (empty, 0, 0, "span start"),
	dwe_span_end	= Z (empty, 0, 0, "span end"),
	dwe_absent	= Z (empty, 0, 0, "absent"),
	dwe_absent_r	= Z (empty, 0, 0, "absent with ref"),
	dwe_absent_x	= Z (empty, 0, 0, "absent statement"),
	dwe_absent_xr	= Z (empty, 0, 0, "absent statement with ref"),
	dwe_displaced	= Z (empty, 0, 0, "movement source"),
	dwe_displ_x	= Z (empty, 0, 0, "moved statement source"),
	dwe_moved	= Z (empty, 0, 0, "movement dest"),
	dwe_moved_r	= Z (empty, 0, 0, "movement dest with ref"),
	dwe_moved_x	= Z (empty, 0, 0, "trivial movement dest"),
	dwe_moved_xr	= Z (empty, 0, 0, "trivial movement dest with ref"),
	dwe_optim	= Z (empty, 0, 0, "optimisation block"),
	dwe_proc	= Z (x_proc, y_proc, z_proc, "subroutine");


static int
count(long * attr)
{
	int c = 0;
	if (*attr == -1)
		return 1;
	do c++;
	while (*(++attr));
	return c;
}

void
init_dw_entries()
{
#define CT(x)	x.index = c; c+= count(x.attr)
	int c = 1;
	CT (dwe_comp_unit);
	CT (dwe_cmac_unit);
	CT (dwe_module);
	CT (dwe_namespace);
	CT (dwe_subunit);
	CT (dwe_childunit);
	CT (dwe_child_acc);
	CT (dwe_import);
	CT (dwe_import_p);
	CT (dwe_entrypt);
	CT (dwe_param);
	CT (dwe_formal);
	CT (dwe_opt_par);
	CT (dwe_thrown_t);
	CT (dwe_inl_call);
	CT (dwe_inl_opnd);
	CT (dwe_scope);
	CT (dwe_fragment);
	CT (dwe_label);
	CT (dwe_with);
	CT (dwe_try);
	CT (dwe_catch);
	CT (dwe_variable);
	CT (dwe_constant);
	CT (dwe_tmpl_type);
	CT (dwe_tmpl_val);
	CT (dwe_tmpl_proc);
	CT (dwe_tmpl_mod);
	CT (dwe_typedef);
	CT (dwe_typecon);
	CT (dwe_cnstraint);
	CT (dwe_base_type);
	CT (dwe_cnst_type);
	CT (dwe_vol_type);
	CT (dwe_clwd_type);
	CT (dwe_als_type);
	CT (dwe_lim_type);
	CT (dwe_ptr_type);
	CT (dwe_hpptr_t);
	CT (dwe_ref_type);
	CT (dwe_pack_type);
	CT (dwe_arr_type);
	CT (dwe_arr_dyn);
	CT (dwe_subr_type);
	CT (dwe_enum_type);
	CT (dwe_enum_tor);
	CT (dwe_enum_char);
	CT (dwe_struct_t);
	CT (dwe_member);
	CT (dwe_varpart);
	CT (dwe_varpart_t);
	CT (dwe_variant_0);
	CT (dwe_variant_1);
	CT (dwe_variant_n);
	CT (dwe_union_t);
	CT (dwe_class_t);
	CT (dwe_inheritce);
	CT (dwe_friend);
	CT (dwe_ptrmem_t);
	CT (dwe_ind_mem);
	CT (dwe_proc_type);
	CT (dwe_procv_t);
	CT (dwe_string_t);
	CT (dwe_stringc_t);
	CT (dwe_file_t);
	CT (dwe_set_t);
	CT (dwe_fixpt_t);
	CT (dwe_fldg_t);
	CT (dwe_modular_t);
	CT (dwe_task_t);
	CT (dwe_synch_t);
	CT (dwe_entry);
	CT (dwe_for_unit);
	CT (dwe_for_lang);
	CT (dwe_call);
	CT (dwe_return);
	CT (dwe_destruct);
	CT (dwe_branch);
	CT (dwe_branch_0);
	CT (dwe_break);
	CT (dwe_test);
	CT (dwe_test_0);
	CT (dwe_jump);
	CT (dwe_jump_0);
	CT (dwe_lj);
	CT (dwe_lj_0);
	CT (dwe_throw);
	CT (dwe_barrier);
	CT (dwe_select);
	CT (dwe_accept);
	CT (dwe_accept_c);
	CT (dwe_rts);
	CT (dwe_rts_en);
	CT (dwe_sel_alt);
	CT (dwe_sel_alt_c);
	CT (dwe_sel_guard);
	CT (dwe_asynchsel);
	CT (dwe_trigger);
	CT (dwe_trigger_c);
	CT (dwe_abort_pt);
	CT (dwe_abort_ptc);
	CT (dwe_requeue);
	CT (dwe_unknown_t);
	CT (dwe_span);
	CT (dwe_span_strt);
	CT (dwe_span_end);
	CT (dwe_absent);
	CT (dwe_absent_r);
	CT (dwe_absent_x);
	CT (dwe_absent_xr);
	CT (dwe_displaced);
	CT (dwe_displ_x);
	CT (dwe_moved);
	CT (dwe_moved_r);
	CT (dwe_moved_x);
	CT (dwe_moved_xr);
	CT (dwe_optim);
	CT (dwe_proc);
	UNUSED (c);
	return;
}


long
dw_entry(abbrev_entry en, long attr)
{
	int d_tag = en.index;
	long * comb = en.attr;
	if (*comb != -1) {
		for (;;) {
			long extra = *comb & ~attr;
			long missing = attr & ~*comb & ~(en.special);
			if (!(extra & ~(en.valid)) && !missing)
				break;
			if (!*(++comb))
				failer ("unsupported attribute combination");
			d_tag++;
		}
	}
	out8 (); uleb128 ((unsigned long)d_tag);
#if 1
	outnl_comment_i (en.aname, (long)(d_tag - en.index));
#else
	d_outnl ();
#endif
	return *comb;
}

