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
 *    Copyright (c) 1993 Open Software Foundation, Inc.
 *
 *
 *    All Rights Reserved
 *
 *
 *    Permission to use, copy, modify, and distribute this software
 *    and its documentation for any purpose and without fee is hereby
 *    granted, provided that the above copyright notice appears in all
 *    copies and that both the copyright notice and this permission
 *    notice appear in supporting documentation.
 *
 *
 *    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
 *    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *    PARTICULAR PURPOSE.
 *
 *
 *    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
 *    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 *    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
 *    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 *    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $TenDRA$
 */

/*
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
 */



/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$
 *$Log$
 *Revision 1.2  2002/11/21 22:31:12  nonce
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
 * Revision 1.2  1998/02/04  15:49:08  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:58  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:04:15  pwe
 * add banners and mod for PWE ownership
 *
 **********************************************************************/


#ifndef REGMACS_H
#define REGMACS_H


/* fixed point regs */
#define R_0	0
#define R_SP	1
#define R_TOC	2
#define R_3	3
#define R_4	4
#define R_5	5
#define R_6	6
#define R_7	7
#define R_8	8
#define R_9	9
#define R_10	10
#define R_11	11
#define R_12	12
#define R_13	13
#define R_14	14
#define R_15	15
#define R_16	16
#define R_17	17
#define R_18	18
#define R_19	19
#define R_20	20
#define R_21	21
#define R_22	22
#define R_23	23
#define R_24	24
#define R_25	25
#define R_26	26
#define R_27	27
#define R_28	28
#define R_29	29
#define R_30	30
#define R_31	31



/* float point regs */
#define FR_0	0
#define FR_1	1
#define FR_2	2
#define FR_3	3
#define FR_4	4
#define FR_5	5
#define FR_6	6
#define FR_7	7
#define FR_8	8
#define FR_9	9
#define FR_10	10
#define FR_11	11
#define FR_12	12
#define FR_13	13
#define FR_14	14
#define FR_15	15
#define FR_16	16
#define FR_17	17
#define FR_18	18
#define FR_19	19
#define FR_20	20
#define FR_21	21
#define FR_22	22
#define FR_23	23
#define FR_24	24
#define FR_25	25
#define FR_26	26
#define FR_27	27
#define FR_28	28
#define FR_29	29
#define FR_30	30
#define FR_31	31

/* frame pointer */
#define R_FP    R_31
/* top of frame pointer */
#define R_TP    R_30

/* temp scratch register than can be used without allocation */
#define R_TMP0		R_0		/* reg 0, which is not totally general */

#define IS_R_TMP(r)	((r) == R_TMP0)


/* registers used for proc paramaters */
#define R_FIRST_PARAM		R_3
#define R_LAST_PARAM		R_10
#define FR_FIRST_PARAM		FR_1
#define FR_LAST_PARAM		FR_13

#define IS_PARAM_REG(r)    ((r) >= R_FIRST_PARAM && (r)<= R_LAST_PARAM)
#define IS_FLT_PARAM_REG(r)    ((r) >= FR_FIRST_PARAM && (r)<= FR_LAST_PARAM)

/* registers used for proc results */
#define R_RESULT		R_3
#define FR_RESULT		FR_1


/* range R_FIRST..R_LAST to loop over fixed regs */
#define R_FIRST			R_0
#define R_LAST			R_31

/* range FR_FIRST..FR_LAST to loop over float regs */
#define FR_FIRST		FR_0
#define FR_LAST			FR_31



/*
 * POWER floating point registers
 *
 * Two representations are used in sparctrans,
 * 0..15 to represent 16 reg-pairs for doubles at the higher (eg fregalloc)
 * levels,
 * and 0..31 at the lower (assembler) levels.
 * This is somewhat confusing, conversion is one way using a 'frg<<1' like
 * expression, often in the parameter position of a XXX_ins() function call.
 */

/* range R_FLT_FIRST..R_FLT_LAST to loop over float regs */
#define R_FLT_FIRST	0
#define R_FLT_LAST	31



/* Codes, which can be used where register number is usual */
#define R_NO_REG	100	/* code for no reg allocated */
#define R_USE_RES_REG	101	/* code to indicate result reg to be used */

#define FR_NO_REG	R_NO_REG /* code for no reg allocated */
#define FR_DEFER_RESULT	34	/* code to indicate FR_RESULT to be used */


#define IS_R_NO_REG(r)		((r) == R_NO_REG || (r) == R_0)		/* +++ R_0 historical */
#define IS_FR_NO_REG(r)		((r) == FR_NO_REG)


/*
 * Register masks, a bit per reg, as used in 'space' etc.
 * A set bit indicates reg is not available for allocation.
 */

#define	RMASK(r)	(((unsigned long)1)<<(r))


/*
 * Register sets.
 */


#define IS_FIXREG(r)	((r) >= R_FIRST && (r) <= R_LAST )


/* s reg, for local variables, preserved over calls: R_13..R_31  */
#define IS_SREG(r)	((r) >= R_13 && (r) <= R_31)

/* t reg, for temp use, not preserved over calls: R_3..R_12 */
#define IS_TREG(r)	((r) >= R_3 && (r) <= R_12)	/* R_0-2 special */

#define MAXFIX_SREGS	(R_31-R_13+1)
/* maxfix_tregs calculated in translat.c to permit differing reg conventions */


/* output parameter t fixed regs: R_3..R_10 */
#define PARAM_TREGS \
			(RMASK(R_3)|RMASK(R_4)|RMASK(R_5)|RMASK(R_6)| \
			RMASK(R_7)|RMASK(R_8)|RMASK(R_9)|RMASK(R_10))


/* output parameter t float regs: FR_1..FR_13 */
#define PARAM_FLT_TREGS \
			(RMASK(FR_1)|RMASK(FR_2)|RMASK(FR_3)|RMASK(FR_4)| \
			RMASK(FR_5)|RMASK(FR_6)|RMASK(FR_7)|RMASK(FR_8)| \
			RMASK(FR_9)|RMASK(FR_10)|RMASK(FR_11)|RMASK(FR_12)| \
			RMASK(FR_13))

/*
 * t regs mask available in proc
 *
 *	PROC_TREGS	fixed point regs: R_3..R_12
 *	PROC_FLT_TREGS	float point regs: FR_0..FR_13
 *
 * Note this mask sets a bit for those registers that are NOT a t reg.
 */
#define PROC_TREGS	(~0 - (PARAM_TREGS|RMASK(R_11)|RMASK(R_12)))

#define PROC_FLT_TREGS	(~0 - (RMASK(FR_0)|PARAM_FLT_TREGS))


/* float s reg, for local variables, preserved over calls: FR_14..FR_31  */
#define IS_FLT_SREG(r)	((r) >= FR_14 && (r) <= FR_LAST)

/* float t reg, for temp use, not preserved over calls: FR_0..FR_13 */
#define IS_FLT_TREG(r)	((r) >= FR_0 && (r) <= FR_13)

#define MAXFLT_SREGS	(FR_LAST-FR_14+1)
#define MAXFLT_TREGS	(FR_13-FR_0+1)



/* map fixreg s number 1..n onto real s-reg R_13..R_31 */
#define SREG_TO_REALREG(n)	((n) - 1 + R_13)

/* map floatreg s number 1..n onto real s-reg FR_14..FR_31 */
#define SFREG_TO_REALFREG(n)	((n) - 1 + FR_14)



/* Needed to restore s-regs in tail_call */

#define R_TEMP_FP    R_11
#define R_TEMP_TP    R_12
#define ALIGNNEXT(bitposn, bitalign)	(((bitposn)+(bitalign)-1) & ~((bitalign)-1))
#endif /* regmacs.h */


