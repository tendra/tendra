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


/*
 *$Log$
 *Revision 1.2  2002/11/21 22:31:07  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1996/01/10  17:18:57  wfs
 * Corrected definition of "IS_TREG" macro + cosmetic changes to needscan.c
 *
 * Revision 1.2  1995/12/18  13:12:32  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.0  1995/08/25  14:00:27  wfs
 * Preperation for August 95 Glue release
 *
 * Revision 4.0  1995/08/25  13:34:00  wfs
 * ..
 *
 * Revision 4.0  1995/08/25  13:34:00  wfs
 * ..
 *
 * Revision 3.4  1995/08/25  11:05:02  wfs
 * Major revision of internal register synonym's
 *
 * Revision 3.4  1995/08/25  11:05:02  wfs
 * Major revision of internal register synonym's
 *
 * Revision 3.1  95/04/10  16:28:07  16:28:07  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:18:56  11:18:56  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:28:46  15:28:46  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:43:36  13:43:36  wfs (William Simmonds)
 * Initial revision
 * 
 */


#ifndef REGMACS_INCLUDED
#define REGMACS_INCLUDED


/****************************/
/*   HP_PA FIXED REGISTERS  */
/****************************/

#define GR0             0       /* Hard wired to 0           */
#define GR1             1      /* First temporary register  */
#define GR2             2     
#define GR3		16   /*  C  */   
#define GR4		17   /*  a  */
#define GR5		18   /*  l  */
#define GR6		19   /*  l  */
#define GR7		20   /*  e  */
#define GR8		21   /*  e  */
#define GR9		22   /*     */
#define GR10		23   /*     */
#define GR11		24   /*     */
#define GR12		25   /*     */
#define GR13		26   /*     */
#define GR14		27   /*  S  */
#define GR15		28   /*  a  */
#define GR16		29   /*  v  */
#define GR17		30   /*  e  */
#define GR18		31   /*  s  */
#define GR19            3
#define GR20            4
#define GR21            5
#define GR22            6
#define GR23            10            
#define GR24            9
#define GR25            8
#define GR26            7
#define GR27            11
#define GR28            12
#define GR29            13
#define GR30            14
#define GR31            15

/****************************/
/*   HP_PA SPACE REGISTERS  */
/****************************/

#define SR0             0
#define SR1             1
#define SR2             2
#define SR3             3
#define SR4             4
#define SR5             5
#define SR6             6
#define SR7             7

/**************/
/*  Synonyms  */
/**************/

#define SP	   GR30               /*  Stack Pointer              */
#define DP         GR27              /*  Global Data Pointer        */
#define RP         GR2              /*  Return Pointer             */
#define T4         GR19            /*  Fourth Temporary Register  */
#define T3         GR20           /*  Third Temporary Register   */
#define T2         GR21          /*  Second Temporary Register  */
#define T1         GR22         /*  First Temporary Register   */
#define MRP        GR31        /*  Millicode Return Pointer   */
#define ARG3       GR23       /*  Argument Word 3            */
#define ARG2       GR24      /*  Argument Word 2            */
#define ARG1       GR25     /*  Argument Word 1            */
#define ARG0       GR26    /*  Argument Word 0            */
#define RET0       GR28   /*  Return value               */
#define RET1       GR29  /*  Return Value               */


#define FP         GR3  /* Frame Pointer. GR3 is reserved for use as a
						 *                           frame pointer iff Has_fp==1 (cf. frames.c).  */

int EP;  /*  EP is a register which holds the frames original stack pointer.
		  *             EP=GR3, if has_vsp==1, or SP otherwise (c.f. frames.c).  */


/* Range of all fixed registers */
#define R_FIRST		0
#define R_LAST		31


/*
 *    HP_PA FLOATING POINT REGISTERS
 *
 *    Two representations are used in hppatrans, 0...15 to represent 16
 *    register-pairs for doubles at the higher (e.g. fregalloc) levels, and
 *    0...31 at the lower (assembler) levels.  This is somewhat confusing,
 *    conversion is one way using a 'frg << 1'-like expression, often in
 *    the parameter position of a ???_ins () function call.
 */

/* Floating point registers */
#define R_FR0		0	/* floating point zero */
#define R_FR4		4	/* procedure float result register */

/* Range of all floating point registers */
#define R_FLT_FIRST	0
#define R_FLT_LAST	31


/*
 *    PSEUDO-REGISTER CODES
 */

#define R_NO_REG	100	/* code for no register allocated */
#define R_USE_RES_REG	101	/* code to indicate result register */
#define R_DEFER_FR4	16	/* code to indicate %fr4 to be used */


/*
 *    REGISTER MASKS
 *    A register mask, with one bit per register, is used in 'space' etc.
 *    A set bit indicates that the register is not available for allocation.
 */

#define	RMASK(r)	(((long) 1) << (r))


/*
 *    REGISTER SETS
 *
 *    IS_FIXREG tests for fixed registers, IS_SREG for s-registers (those
 *    preserved over procedure calls), and IS_TREG for t-registers (those
 *    not so preserved).  PARAM_TREGS gives all the procedure parameter
 *    registers (ARG0-ARG3)
 */

#define IS_FIXREG(r)  ((r)>=R_FIRST && (r)<=R_LAST)
#define IS_SREG(r)    ((r)>=GR3 && (r)<=GR18)
#define IS_TREG(r)    (((r)>GR0 && (r)<=GR2) || ((r)>=GR19 && (r)<= GR31))

#define PARAM_TREGS   RMASK(ARG0)|RMASK(ARG1)|RMASK(ARG2)|RMASK(ARG3)
#define PROC_TREGS    -65536 /*  i.e. 11111111111111110000000000000000  */

#define IS_FLT_SREG(r)	0
/*#define IS_FLT_TREG(r)	((r) >= 0 && (r) <= 15)  */
#define IS_FLT_TREG(r)	(((r)>7 && (r)<12) || ((r)>21 && (r)<32))
#define PARAM_FLT_TREGS		0x0000
#define PROC_FLT_TREGS		0x0000
#define MAXFLOAT_TREGS		14


#endif /* REGMACS_INCLUDED */






















