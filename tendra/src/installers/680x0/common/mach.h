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
 *Revision 1.1.1.1  1997/10/13 12:42:55  ma
 *First version.
 *
 *Revision 1.2  1997/06/18 10:09:35  ma
 *Checking in before merging with Input Baseline changes.
 *
 *Revision 1.1.1.1  1997/03/14 07:50:14  ma
 *Imported from DRA
 
 * Revision 1.2  1996/09/20  13:51:37  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:55  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:14  john
 *
 * Revision 1.1  93/02/22  17:16:00  17:16:00  ra (Robert Andrews)
 * Initial revision
 * 
 *--------------------------------------------------------------------------
 */


#ifndef MACH_INCLUDED
#define MACH_INCLUDED

#include "flpttypes.h"


/*
 *    STRUCTURE REPRESENTING MACHINE OPERANDS
 *
 *    A machine operand consists of a type, the meaning of which is explained
 *    below, a value, which can be a number, a string or a floating-point
 *    number, and two pointers to further machine operands, plus and of.
 */

typedef struct tag_mach_op {
    char type;
    union {
		long num;
		char *str;
		flt *fp;
    } def;
    struct tag_mach_op *plus;
    struct tag_mach_op *of;
#ifndef tdf3
#ifdef EBUG
    int id;
#endif
#endif
} mach_op;


/*
 *    STRUCTURE REPRESENTING MACHINE INSTRUCTIONS
 *
 *    A machine instruction consists of an instruction number, which can
 *    take the values given in instrs.h, two machine operands, giving
 *    the operands of this instruction, a register mask, giving all the
 *    registers changed by this instruction, and a pointer to the next
 *    instruction.
 */

typedef struct tag_mach_ins {
    short ins_no;
    mach_op *op1;
    mach_op *op2;
    bitpattern changed;
    struct tag_mach_ins *next;
#ifndef tdf3
#ifdef EBUG
    int id;
#endif
#endif
} mach_ins;


/*
 *    OPERAND TYPES
 *
 *    These are the possible values for the type of a machine operand.
 *    The meanings are given below.
 */

#define  MACH_BF	0
#define  MACH_CONT	1
#define  MACH_DEC	2
#define  MACH_EXT	3
#define  MACH_EXTQ	4
#define  MACH_FLOATQ	5
#define  MACH_HEX	6
#define  MACH_HEXQ	7
#define  MACH_INC	8
#define  MACH_LAB	9
#define  MACH_LABQ	10
#define  MACH_NEG	11
#define  MACH_REG	12
#define  MACH_RPAIR	13
#define  MACH_SCALE	14
#define  MACH_SPEC	15
#define  MACH_SPECQ	16
#define  MACH_VAL	17
#define  MACH_VALQ	18

#ifndef tdf3
#ifdef EBUG
#define  MACH_COMMENT   19
#endif
#endif

/*
 *    REGISTER NUMBERS
 *
 *    Each register is identified by a register number.
 */

#define  REG_D0		0
#define  REG_D1		1
#define  REG_D2		2
#define  REG_D3		3
#define  REG_D4		4
#define  REG_D5		5
#define  REG_D6		6
#define  REG_D7		7
#define  REG_A0		8
#define  REG_A1		9
#define  REG_A2		10
#define  REG_A3		11
#define  REG_A4		12
#define  REG_A5		13
#define  REG_AP		14
#define  REG_SP		15
#define  REG_FP0	16
#define  REG_FP1	17
#define  REG_FP2	18
#define  REG_FP3	19
#define  REG_FP4	20
#define  REG_FP5	21
#define  REG_FP6	22
#define  REG_FP7	23
#define  REG_PC		24
#define  REG_CCR	25
#define  REG_FPCR	26
#define  REG_FPSR	27
#define  REG_FPIAR	28
#define  REG_ZA0	29


/*
 *    TESTS ON REGISTER NUMBERS
 *
 *    These test whether a given register number represents a D-register
 *    or an A-register.
 */

#define  is_dreg(X)	((X) < REG_A0)
#define  is_areg(X)	((X) >= REG_A0 && (X) < REG_FP0)


/*
 *    CONVERSION FROM REGISTER NUMBERS TO MASKS
 *
 *    Given a register mask, reg returns the smallest register number
 *    involved in that mask.  Given a register number, regmsk gives the
 *    corresponding register mask.
 */

#define  reg(X)	bit_one (X)
#define  regmsk(X)	(((bitpattern) 1) << (X))


/*
 *    USEFUL MASKS ETC.
 *
 *    dreg_msk gives all D-registers, areg_msk gives all A-registers,
 *    save_msk gives all registers preserved across procedure calls.
 *    regs extracts all the D- and A-registers from a mask.  fregs
 *    extracts all the F-registers.
 */

#define  dreg_msk	((bitpattern) 0x000000ff)
#define  areg_msk	((bitpattern) 0x0000ff00)
#define  save_msk	((bitpattern) 0xfffc3cfc)
#define  regs(X)	((X) & ((bitpattern) 0xffff))
#define  fregs(X)	((X) & ((bitpattern) 0xff0000))


/*
 *    MEANINGS OF OPERAND TYPES
 *
 *    MACH_BF is used to represent bitfield operands.  Its of field is
 *    the basic operand, the def field is a number, giving the bitfield
 *    offset, the plus field is a dummy operand whose def field is a
 *    number, giving the bitfield size.
 *
 *    MACH_CONT is used to represent contents operands.  The of field
 *    gives the operand the contents of which are meant.  The plus field
 *    may give another operand to be added.  The def field is a number
 *    giving all the registers used in this operand and all its sub-operands.
 *
 *    MACH_DEC is used to represent pre-decremented registers.  Its def
 *    field is the register number involved.
 *
 *    MACH_EXT and MACH_EXTQ are used to represent external names.  Their
 *    def field is a string giving the external name.
 *
 *    MACH_FLOATQ is used to represent floating-point numbers.  Its def
 *    field is a pointer to the internal representation of the number.
 *
 *    MACH_HEX, MACH_HEXQ, MACH_VAL and MACH_VALQ are used to represent
 *    integer constants.  Their def field gives the value.  The different
 *    types allow different numbers to be expressed in decimal or hex.
 *
 *    MACH_INC is used to represent post-incremented registers.  Its def
 *    field is the register number involved.
 *
 *    MACH_LAB and MACH_LABQ are used to represent labels.  Their def
 *    field is the label number.
 *
 *    MACH_NEG is used to indicate that an operand should be negated.
 *    The operand to be negated is given by the plus field.
 *
 *    MACH_REG is used to represent registers.  Its def field gives the
 *    register number.
 *
 *    MACH_RPAIR is used to represent register pairs.  Its def field
 *    gives the first register number, the plus field is a dummy operand
 *    whose def field gives the second register number.
 *
 *    MACH_SCALE is used to represent scaled operands.  Its def field
 *    is a number, giving the scaling factor, and its of field gives
 *    the operand being scaled.
 *
 *    MACH_SPEC and MACH_SPECQ are used to represent special labels.
 *    Their def field is a string giving the special identifier.
 *
 *    Most 680x0 operands and constants can be expressed by using the
 *    plus and of fields to connect the basic operands.  A special use
 *    of the of field is to string together a list of constants
 *    (which do not otherwise use it - see evaluate.c and output.c).
 *
 *    For example, the register indirect operand 4(%a0) is represented
 *    by the machine operand a given by :
 *
 *	    a = { MACH_CONT, regmsk (REG_A0), null, &b }
 *	    b = { MACH_REG, REG_A0, &c, null }
 *	    c = { MACH_VAL, 4, null, null }
 */

#endif
