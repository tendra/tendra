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
 *			    VERSION INFORMATION
 *			    ===================
 *
 *--------------------------------------------------------------------------
 *$Header$
 *--------------------------------------------------------------------------
 *$Log$
 *Revision 1.2  2002/11/21 22:31:14  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.12  1997/11/06  09:28:50  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.11  1997/10/10  18:32:25  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.10  1997/08/23  13:53:49  pwe
 * initial ANDF-DE
 *
 * Revision 1.9  1997/04/17  11:59:39  pwe
 * dwarf2 support
 *
 * Revision 1.8  1996/09/18  12:03:38  pwe
 * fixed PIC_code
 *
 * Revision 1.7  1995/12/15  10:12:47  john
 * Minor change
 *
 * Revision 1.6  1995/08/31  15:55:06  john
 * Added function for calculation of floating_max
 *
 * Revision 1.5  1995/07/18  09:38:37  john
 * New functions for return_to_label
 *
 * Revision 1.4  1995/07/14  16:30:59  john
 * Minor fix
 *
 * Revision 1.3  1995/06/14  15:33:09  john
 * Reformatting
 *
 * Revision 1.2  1995/05/26  12:58:38  john
 * Reformatting
 *
 * Revision 1.1.1.1  1995/03/13  10:18:39  john
 * Entered into CVS
 *
 * Revision 1.7  1995/01/24  16:56:34  john
 * Added special regs to the register set
 *
 * Revision 1.6  1994/12/21  12:11:38  djch
 * Added maxmin functions for int max/min. Uses the delay slot...
 *
 * Revision 1.5  1994/12/01  13:16:01  djch
 * Added lr_ins to load a label address to a register
 * Added lngjmp to code the long jump construct
 * Added br_abs to get efficient jump in abs (except with SunOS as)
 *
 * Revision 1.4  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.3  1994/07/04  08:20:45  djch
 * added asserts to spot uninitialized labels
 *
 * Revision 1.2  1994/05/13  12:31:14  djch
 * Incorporates improvements from expt version
 * Fixed printf strings to remove long, added CONST to extj_special_ins
 *
 * Revision 1.1  1994/05/03  14:49:38  djch
 * Initial revision
 *
 * Revision 1.7  93/09/27  14:45:39  14:45:39  ra (Robert Andrews)
 * The label prefix is now given by lab_prefix rather than by being
 * hardwired in.
 * 
 * Revision 1.6  93/08/27  11:27:19  11:27:19  ra (Robert Andrews)
 * Added a couple of explicit integer casts, ext_name now takes a long.
 * 
 * Revision 1.5  93/07/12  15:14:20  15:14:20  ra (Robert Andrews)
 * A couple of things should have been CONST.
 * 
 * Revision 1.4  93/07/08  18:21:11  18:21:11  ra (Robert Andrews)
 * Reformatted.
 * 
 * Revision 1.3  93/07/05  18:19:49  18:19:49  ra (Robert Andrews)
 * Reformatted a couple of routines.  Added support for Position Independent
 * Code (PIC) in set_ins.
 * 
 * Revision 1.2  93/06/29  14:26:39  14:26:39  ra (Robert Andrews)
 * Included a couple of explicit casts.
 * 
 * Revision 1.1  93/06/24  14:58:28  14:58:28  ra (Robert Andrews)
 * Initial revision
 * 
 *--------------------------------------------------------------------------
 */


#define SPARCTRANS_CODE

/*
 *    This file contains procedures for outputting various SPARC instruction
 *    formats to the external file - as_file.  Each procedure produces
 *    assembler instructions for a family of SPARC operations, the actual
 *    instruction being passed as the string understood by the assembler.
 */

#include "config.h"
#include "common_types.h"
#include "myassert.h"
#include "xalloc.h"
#include "addrtypes.h"
#include "regexps.h"
#include "regmacs.h"
#include "sparcins.h"
#include "maxminmacs.h"
#include "comment.h"
#include "translat.h"
#include "inst_fmt.h"
#include "out.h"
#include "flags.h"
#include "labels.h"
#ifdef NEWDWARF
#include "dw2_config.h"
#endif


/*
 *     IS c A POWER OF 2?
 */

#define IS_POW2(c)	((c) != 0 && ((c) & ((c) - 1)) == 0)


/*
 *    ARRAY OF REGISTER NAMES
 */

static CONST char reg_name_tab [66][5] = {
    "%g0", "%g1", "%g2", "%g3", "%g4", "%g5", "%g6", "%g7",
    "%o0", "%o1", "%o2", "%o3", "%o4", "%o5", "%sp", "%o7",
    "%l0", "%l1", "%l2", "%l3", "%l4", "%l5", "%l6", "%l7",
    "%i0", "%i1", "%i2", "%i3", "%i4", "%i5", "%fp", "%i7",
    "%f0", "%f1", "%f2", "%f3", "%f4", "%f5", "%f6", "%f7",
    "%f8", "%f9", "%f10","%f11","%f12","%f13","%f14","%f15",
    "%f16","%f17","%f18","%f19","%f20","%f21","%f22","%f23",
    "%f24","%f25","%f26","%f27","%f28","%f29","%f30","%f31",
    "%fsr","%y"
};


/*
 *    MACRO FOR ACCESSING REGISTER NAMES
 *
 *    This converts a register number into the corresponding register
 *    name.
 */

#define RN(reg)	reg_name_tab [ reg ]
#define FRN(reg)	reg_name_tab [ reg + 32 ]

/*
 *    FIND AN EXTERNAL NAME
 */

char
*ext_name(int id)
{
    if (id < 0) {
		/* Negative numbers refer to globals */
		char *ext = main_globals [ -id - 1 ]->dec_u.dec_val.dec_id;
		return (ext);
    } else {
		/* Positive numbers refer to labels */
		static char space [64];
		sprintf (space, "%sD%d", lab_prefix, id);
		return (space);
    }
}


/*
 *    OUTPUT A LOAD REGISTER-OFFSET INSTRUCTION
 */

void
ld_ro_ins(ins_p ins, baseoff a, int dest)
{
    long off = a.offset;
    assert (IS_FIXREG (a.base));
    clear_reg (dest);
    if (SIMM13_SIZE (off)) {
		/* Small offset */
		CONST char *ra = RN (a.base);
		CONST char *rd = RN (dest);
		if (off == 0) {
			fprintf (as_file, "\t%s\t[%s],%s\n", ins, ra, rd);
		} else if (off > 0) {
			fprintf (as_file, "\t%s\t[%s+%ld],%s\n", ins, ra, off, rd);
		} else /* if (off < 0) */ {
			fprintf (as_file, "\t%s\t[%s-%ld],%s\n", ins, ra, -off, rd);
		}
#ifdef NEWDWARF
		count_ins(1);
#endif
    } else {
		/* Large offset */
		if (a.base != dest) {
			/* Is this really a saving? */
			ir_ins (i_set, off, dest);
			ld_rr_ins (ins, a.base, dest, dest);
		} else {
			assert (a.base != R_TMP);
			ir_ins (i_set, off, R_TMP);
			ld_rr_ins (ins, a.base, R_TMP, dest);
		}
#ifdef NEWDWARF
		lost_count_ins();
#endif
    }
    return;
}


/*
 *    OUTPUT A LOAD REGISTER-REGISTER INSTRUCTION
 */

void
ld_rr_ins(ins_p ins, int reg1, int reg2, int dest)
{
    clear_reg (dest);
    fprintf (as_file, "\t%s\t[%s+%s],%s\n", ins,
			 RN (reg1), RN (reg2), RN (dest));
#ifdef NEWDWARF
    count_ins(1);
#endif
    return;
}


/*
 *    OUTPUT A SET INSTRUCTION
 */

void
set_ins(baseoff a, int dest)
{
    char *extname = ext_name (a.base);
    long d = a.offset;
    clear_reg (dest);
	
    if (d == 0 || PIC_code) {
		fprintf (as_file, "\tset\t%s,%s\n", extname, RN (dest));
    } else if (d > 0) {
		fprintf (as_file, "\tset\t%s+%ld,%s\n", extname, d, RN (dest));
    } else {
		fprintf (as_file, "\tset\t%s-%ld,%s\n", extname, -d, RN (dest));
    }
#ifdef NEWDWARF
    lost_count_ins();
#endif
	
    if (PIC_code) {
		ld_rr_ins (i_ld, R_L7, dest, dest);
		if (d) rir_ins (i_add, dest, d, dest);
    }
    return;
}


/*
 *    OUTPUT A LOAD INSTRUCTION
 *
 *    If baseoff is a global this may be two instructions and involve
 *    a temporary register.
 */


void
ld_ins(ins_p ins, baseoff a, int dest)
{
    if (!IS_FIXREG (a.base)) {
		/* global */
		baseoff tmp_off;
		tmp_off.base = R_TMP;
		tmp_off.offset = 0;
		set_ins (a, R_TMP);
		ld_ro_ins (ins, tmp_off, dest);
    } else {
		ld_ro_ins (ins, a, dest);
    }
    return;
}


/*
 *    OUTPUT A STORE REGISTER-OFFSET INSTRUCTION
 */

void
st_ro_ins(ins_p ins, int src, baseoff a)
{
    long off = a.offset;
    assert (IS_FIXREG (a.base));
	
    /* in general we cannot cope with store using temp reg, catch it always */
    if ((src == R_TMP || a.base == R_TMP)
		&& ABS_OF (off) > (16 + 1 + 6) * 4 /* leeway for mem_temp */) {
		fail ("Temporary register problem in st_ro_ins");
    }
	
    if (SIMM13_SIZE (off)) {
		/* Small offset */
		CONST char *rs = RN (src);
		CONST char *ra = RN (a.base);
		if (off == 0) {
			fprintf (as_file, "\t%s\t%s,[%s]\n", ins, rs, ra);
		} else if (off > 0) {
			fprintf (as_file, "\t%s\t%s,[%s+%ld]\n", ins, rs, ra, off);
		} else /* if (off < 0) */ {
			fprintf (as_file, "\t%s\t%s,[%s-%ld]\n", ins, rs, ra, -off);
		}
#ifdef NEWDWARF
		count_ins(1);
#endif
    } else {
		/* Large offset */
		assert (a.base != R_TMP);
		ir_ins (i_set, off, R_TMP);
#ifdef NEWDWARF
		lost_count_ins();
#endif
		st_rr_ins (ins, src, a.base, R_TMP);
    }
    return;
}


/*
 *    OUTPUT A STORE REGISTER-REGISTER INSTRUCTION
 */

void
st_rr_ins(ins_p ins, int src, int reg1, int reg2)
{
    fprintf (as_file, "\t%s\t%s,[%s+%s]\n", ins,
			 RN (src), RN (reg1), RN (reg2));
#ifdef NEWDWARF
    count_ins(1);
#endif
    return;
}


/*
 *    OUTPUT A STORE INSTRUCTION
 *
 *    If baseoff is a global this may be two instructions and involve
 *    a temporary register.
 */

void
st_ins(ins_p ins, int src, baseoff a)
{
    if (!IS_FIXREG (a.base)) {
		/* global */
		baseoff tmp_off;
		if (src == R_TMP) {
			fail ("Temporary register problem in st_ins");
		}
		tmp_off.base = R_TMP;
		tmp_off.offset = 0;
		set_ins (a, R_TMP);
		st_ro_ins (ins, src, tmp_off);
    } else {
		st_ro_ins (ins, src, a);
    }
    return;
}


/*
 *    OUTPUT A THREE REGISTER INSTRUCTION
 */

void
rrr_ins(ins_p ins, int src1, int src2, int dest)
{
    clear_reg (dest);
    fprintf (as_file, "\t%s\t%s,%s,%s\n", ins,
			 RN (src1), RN (src2), RN (dest));
#ifdef NEWDWARF
    count_ins(1);
#endif
    return;
}


/*
 *    OUTPUT A REGISTER, IMMEDIATE, REGISTER INSTRUCTION
 */

void
rir_ins(ins_p ins, int src1, long imm, int dest)
{
    clear_reg (dest);
	
    if (SIMM13_SIZE (imm)) {
		/* Small data */
		fprintf (as_file, "\t%s\t%s,%ld,%s\n", ins,
				 RN (src1), imm, RN (dest));
#ifdef NEWDWARF
		count_ins(1);
#endif
    } else if (SIMM13_SIZE (~imm) &&
			   (ins == i_and || ins == i_or || ins == i_xor)) {
		/* Small data complemented */
		ins_p n_ins;
		if (ins == i_and) {
			n_ins = i_andn;
		} else if (ins == i_or) {
			n_ins = i_orn;
		} else /* if (ins == i_xor) */ {
			n_ins = i_xnor;
		}
		fprintf (as_file, "\t%s\t%s,%ld,%s\n", n_ins,
				 RN (src1), ~imm, RN (dest));
#ifdef NEWDWARF
		count_ins(1);
#endif
    } else if (ins == i_and && IS_POW2 (imm + 1)) {
		/* Can be done by shift left, shift right */
		int nbits = 0, shift;
		unsigned long uimm = (unsigned long) imm;
		while (uimm != 0) {
			nbits++;
			uimm = uimm >> 1;
		}
		shift = 32 - nbits;
		rir_ins (i_sll, src1, (long) shift, dest);
		rir_ins (i_srl, dest, (long) shift, dest);
    } else if ((ins == i_add || ins == i_sub) &&
			   SIMM13_SIZE (imm / 2) && dest != R_SP) {
		if (imm == 4096) {
			/* add 4096 => sub -4096 etc */
			rir_ins ((ins == i_add ? i_sub : i_add), src1, -imm, dest);
		} else {
			/* use two adds or subs */
			long half = imm / 2;
			rir_ins (ins, src1, half, dest);
			rir_ins (ins, dest, (long) (imm - half), dest);
		}
    } else {
		/* use temporary register for large constant */
		if (src1 == R_TMP) {
			fail ("Temporary register problem in rir_ins");
		} else {
			fprintf (as_file, "\tset\t%ld,%s\n", imm, RN (R_TMP));
#ifdef NEWDWARF
			lost_count_ins();
#endif
			rrr_ins (ins, src1, R_TMP, dest);
		}
    }
    return;
}


/*
 *    OUTPUT A REGISTER TO REGISTER PSEUDO INSTRUCTION
 */

void
rr_ins(ins_p ins, int src, int dest)
{
    clear_reg (dest);
    fprintf (as_file, "\t%s\t%s,%s\n", ins, RN (src), RN (dest));
#ifdef NEWDWARF
    count_ins(1);
#endif
    return;
}


/*
 *    OUTPUT AN IMMEDIATE TO REGISTER PSEUDO INSTRUCTION
 */

void
ir_ins(ins_p ins, long imm, int dest)
{
    clear_reg (dest);
	
    if (SIMM13_SIZE (imm) || ins == i_set) {
		fprintf (as_file, "\t%s\t%ld,%s\n", ins, imm, RN (dest));
#ifdef NEWDWARF
		count_ins(1);
#endif
    } else if (ins == i_mov) {
		/* use a set instruction for move */
		fprintf (as_file, "\tset\t%ld,%s\n", imm, RN (dest));
#ifdef NEWDWARF
		lost_count_ins();
#endif
    } else {
		/* use temporary register for large constant */
		fprintf (as_file, "\tset\t%ld,%s\n", imm, RN (R_TMP));
#ifdef NEWDWARF
		lost_count_ins();
#endif
		rr_ins (ins, R_TMP, dest);
    }
    return;
}

/*
 *    OUTPUT A LABEL TO REGISTER PSEUDO INSTRUCTION
 */

void
lr_ins(int imm, int dest)
{
    clear_reg (dest);
	
    /* use a set instruction to load the label */
    fprintf (as_file, "\tset\t%s%d,%s\n", lab_prefix, imm, RN (dest));
#ifdef NEWDWARF
    lost_count_ins();
#endif
	
    if (PIC_code) {
		ld_rr_ins (i_ld, R_L7, dest, dest);
    }
    return;
}


/*
 *    OUTPUT A ZEROADIC INSTRUCTION
 */

void
z_ins(ins_p ins)
{
    fprintf (as_file, "\t%s\n", ins);
#ifdef NEWDWARF
    count_ins(1);
#endif
    return;
}


/*
 *    OUTPUT AN UNCONDITIONAL BRANCH
 */

void
uncond_ins(ins_p ins, int lab)
{
    fprintf (as_file, "\t%s\t%s%d\n", ins, lab_prefix, lab);
    assert (lab > 100);
    outs ("\tnop\n") ;	/* delay slot */
#ifdef NEWDWARF
    count_ins(2);
#endif
    return;
}


/*
 *    OUTPUT A RETURN INSTRUCTION
 */

void
ret_ins(ins_p ins)
{
    fprintf (as_file, "\t%s\n", ins);
    outs ("\tnop\n") ;	/* delay slot */
#ifdef NEWDWARF
    count_ins(2);
#endif
    return;
}


/*
 *    OUTPUT A RETURN AND RESTORE INSTRUCTION
 */

void
ret_restore_ins()
{
    fprintf (as_file, "\t%s\n", i_ret);
    fprintf (as_file, "\t%s\n", i_restore) ;	/* delay slot */
#ifdef NEWDWARF
    count_ins(2);
#endif
    return;
}

/*
 *   OUTPUT A LONGJMP (old sp, pc)
 */
/* offset from fp to saved i6 in the 16 word
 *				 reg save area. See rw_fp in <machine/reg.h> */
#define FP_OFFSET_IN_FRAME (8*4 + 6*4)

void
lngjmp(int o_fp_reg, int pc_reg, int r_new_sp)
{
	int lab = new_label();
	baseoff frm;
	
	frm.offset = FP_OFFSET_IN_FRAME;
    
#ifdef NOT_SUN_BUGGY_ASM
	fprintf (as_file, "\tta\t3\n");
#else
	fprintf (as_file, "\t.word\t0x91d02003\n") ; /* ta 3, but SunOS as may
												  *						    get ta wrong I'm told */
#endif
#ifdef NEWDWARF
	lost_count_ins();
#endif
	rr_ins (i_mov, R_SP, r_new_sp);
	rir_ins(i_sub, R_SP, 0x40, R_SP);
	
	frm.base = r_new_sp;
	
	set_label (lab);
	ld_ro_ins (i_ld, frm,   R_TMP);
	fprintf (as_file, "\tcmp\t%s,%s\n", RN (R_TMP), RN(o_fp_reg));
	fprintf (as_file, "\tbne,a\t%s%d\n", lab_prefix, lab);
#ifdef NEWDWARF
	count_ins(2);
#endif
	rr_ins (i_mov, R_TMP, r_new_sp);
	/* now r_new_sp holds the sp to a reg
	 *				 save area whose fp is the fp we want...*/
	rr_ins (i_mov, r_new_sp, R_FP);
	
	fprintf (as_file, "\tjmpl\t %s + 0, %%g0\n", RN(pc_reg));
	fprintf (as_file, "\t%s\n", i_restore) ;	/* delay slot */
#ifdef NEWDWARF
	count_ins(2);
#endif
}

/*
 *    OUTPUT A STRUCTURE RESULT RETURN AND RESTORE INSTRUCTION
 *
 *    See section D.4 of the SPARC architecture manual.
 */

void
stret_restore_ins()
{
    fprintf (as_file, "\tjmp\t%%i7+12\n");
    fprintf (as_file, "\t%s\n", i_restore) ;	/* delay slot */
#ifdef NEWDWARF
    count_ins(2);
#endif
    return;
}


/*
 *    OUTPUT AN EXTERNAL JUMP OR CALL INSTRUCTION
 */

void
extj_ins(ins_p ins, baseoff b, int param_regs_used)
{
	char *ext = ext_name (b.base);
	if (param_regs_used >= 0) {
		/* print number of parameter registers if known */
		assert (param_regs_used <= 6) ;	/* %o0..%o5 */
		if (b.offset) {
			fprintf(as_file,"\t%s\t%s+%ld,%d\n",ins,ext,b.offset,param_regs_used);
		}
		else {
			fprintf (as_file, "\t%s\t%s,%d\n", ins, ext, param_regs_used);
		}
		
	} 
	else {
		/* param_regs_used = -1 means it is not known */
		if (b.offset) {
			fprintf(as_file,"\t%s\t%s+%ld\n",ins,ext,b.offset);
		}
		else {
			fprintf (as_file, "\t%s\t%s\n", ins, ext);
		}
	}
	outs ("\tnop\n") ;	/* delay slot */
#ifdef NEWDWARF
	count_ins(2);
#endif
	return;
}	

/* 
 *   don't fill up the delay slot: the caller of this functions must
 *   provide its own delay slot filler 
 */
void
extj_ins_without_delay(ins_p ins, baseoff b,
					   int param_regs_used)
{
	char *ext = ext_name (b.base);
	if (param_regs_used >= 0) {
		/* print number of parameter registers if known */
		assert (param_regs_used <= 6) ;	/* %o0..%o5 */
		fprintf (as_file, "\t%s\t%s,%d\n", ins, ext, param_regs_used);
	} 
	else {
		/* param_regs_used = -1 means it is not known */
		fprintf (as_file, "\t%s\t%s\n", ins, ext);
	}
#ifdef NEWDWARF
	count_ins(1);
#endif
	return;
}



/*
 *  OUTPUT AN EXTERNAL JUMP OR CALL INSTRUCTION (SPECIAL CASE)
 *  
 *  This case is used to handle special calls like .muls where the
 *  name is given by a string.
 */

void
extj_special_ins(ins_p ins, CONST char * CONST ext,
				 int param_regs_used)
{
	if (param_regs_used >= 0) {
		/* print number of parameter registers if known */
		assert (param_regs_used <= 6) ;	/* %o0..%o5 */
		fprintf (as_file, "\t%s\t%s,%d\n", ins, ext, param_regs_used);
	} 
	else {
		/* param_regs_used = -1 means it is not known */
		fprintf (as_file, "\t%s\t%s\n", ins, ext);
	}
	outs ("\tnop\n") ;	/* delay slot */
#ifdef NEWDWARF
	count_ins(2);
#endif
	return;
}


/* as above, but with allowing the calling function to fill in the
 *   delay slot. */
void
extj_special_ins_no_delay(ins_p ins, CONST char * CONST ext,
						  int param_regs_used)
{
	if (param_regs_used >= 0) {
		/* print number of parameter registers if known */
		assert (param_regs_used <= 6) ;	/* %o0..%o5 */
		fprintf (as_file, "\t%s\t%s,%d\n", ins, ext, param_regs_used);
	} 
	else {
		/* param_regs_used = -1 means it is not known */
		fprintf (as_file, "\t%s\t%s\n", ins, ext);
	}
#ifdef NEWDWARF
	count_ins(1);
#endif
  	/* delay slot */
	return;
}




/*
 *  OUTPUT AN EXTERNAL JUMP TO REGISTER INSTRUCTION
 */

void
extj_reg_ins(ins_p ins, int reg, int param_regs_used)
{
	assert (IS_FIXREG (reg));
	if (sysV_assembler) {
		/* The SysV assembler likes reg to be R_G1 for calls */
		if (ins == i_call && reg != R_G1) {
			rr_ins (i_mov, reg, R_G1);
			reg = R_G1;
		}
	}	
	extj_special_ins (ins, RN (reg), param_regs_used);
	return;
}	


void
extj_reg_ins_no_delay(ins_p ins, int reg,
					  int param_regs_used)
{
	assert (IS_FIXREG (reg));
	if (sysV_assembler) {
		/* The SysV assembler likes reg to be R_G1 for calls */
		if (ins == i_call && reg != R_G1) {
			rr_ins (i_mov, reg, R_G1);
			reg = R_G1;
		}
	}	
	extj_special_ins_no_delay (ins, RN (reg), param_regs_used);
	return;
}	



/*
 *  OUTPUT AN UNIMP INSTRUCTION
 */

void
unimp_ins(long imm)
{
    fprintf (as_file, "\tunimp\t%ld\n", imm);
#ifdef NEWDWARF
    count_ins(1);
#endif
    return;
}


/*
 *  OUTPUT A CONDITIONAL INTEGER TEST JUMP
 */

void
br_ins(ins_p ins, int dest)
{
	fprintf (as_file, "\t%s\t%s%d\n", ins, lab_prefix, dest);
	assert (dest > 100);
	outs ("\tnop\n") ;	/* delay slot */
#ifdef NEWDWARF
	count_ins(2);
#endif
	return;
}

/*
 *  OUTPUT int branch for abs
 */

void
br_abs(int lab)
{
#ifdef NOT_SUN_BUGGY_ASM
	fprintf (as_file, "\t%s\t%s%s\n", "bpos,a", lab_prefix, lab);
#ifdef NEWDWARF
	count_ins(1);
#endif
	/* No nop, delay slot used!!! */
#else
	fprintf (as_file, "\t%s\t%s%d\n", "bneg", lab_prefix, lab);
	fprintf (as_file, "\tnop\n");
#ifdef NEWDWARF
	count_ins(2);
#endif
#endif
	return;
}


/*
 *  OUTPUT A CONDITIONAL FLOATING POINT TEST JUMP
 *
 *  The instruction before a floating point test jump instruction 
 *  cannot be another floating point instruction.
 */

void
fbr_ins(ins_p ins, int dest)
{
	outs ("\tnop\n");
	fprintf (as_file, "\t%s\t%s%d\n", ins, lab_prefix, dest);
	assert (dest > 100);
	outs ("\tnop\n") ;	/* delay slot */
#ifdef NEWDWARF
	count_ins(2);
#endif
	return;
}


/*
 *  OUTPUT A REGISTER, REGISTER COMPARISON
 */

void
condrr_ins(ins_p ins, int src1, int src2,
		   int lab)
{
	if (src2 == R_G0){
		fprintf (as_file, "\ttst\t%s\n",RN(src1));
	}
	else{
		fprintf (as_file, "\tcmp\t%s,%s\n", RN (src1), RN (src2));
	}
#ifdef NEWDWARF
	count_ins(1);
#endif
	br_ins (ins, lab);
	return;
}


/*
 *  OUTPUT A REGISTER, IMMEDIATE COMPARISON
 */

void
condri_ins(ins_p ins, int src1, long imm,
		   int lab)
{
	if (SIMM13_SIZE(imm)) {
		/* Small constant */
		fprintf (as_file, "\tcmp\t%s,%ld\n", RN (src1), imm);
#ifdef NEWDWARF
		count_ins(1);
#endif
		br_ins (ins, lab);
    } 
	else {
		/* Large constant */
		if (src1 == R_TMP) {
			fail ("Temporary register problem in condri_ins");
		}
		fprintf (as_file, "\tset\t%ld,%s\n", imm, RN (R_TMP));
#ifdef NEWDWARF
		lost_count_ins();
#endif
		condrr_ins (ins, src1, R_TMP, lab);
	}
	return;
}

/*
 *    OUTPUT A REGISTER, REGISTER MAX/MIN
 */

void
fmaxminrr_ins(ins_p ins, int src1, int src2,
			  int dest, int ftype)
{
	ins_p fcmp_ins;
	int lab = new_label();
	fcmp_ins = i_fcmps;
	fprintf (as_file, "\t%s\t%s,%s\n", fcmp_ins,RN (src1), RN (src2));
	fprintf (as_file, "\t%s\t%s%d\n", ins, lab_prefix, lab);
	/* USE the delay slot */
	fprintf (as_file, "\tfmovs %s, %s\n", RN(src1), RN(dest));
	fprintf (as_file, "\tfmovs %s, %s\n", RN(src2), RN(dest));
#ifdef NEWDWARF
	count_ins(4);
#endif
	
	set_label(lab);
	return;
}




void
maxminrr_ins(ins_p ins, int src1, int src2,
			 int dest)
{
	int lab = new_label();
	
	fprintf (as_file, "\tcmp\t%s,%s\n", RN (src1), RN (src2));
	fprintf (as_file, "\t%s\t%s%d\n", ins, lab_prefix, lab);
	/* USE the delay slot */
	fprintf (as_file, "\tmov %s, %s\n", RN(src1), RN(dest));
	fprintf (as_file, "\tmov %s, %s\n", RN(src2), RN(dest));
#ifdef NEWDWARF
	count_ins(4);
#endif
	
	set_label(lab);
	return;
}

/*
 *  OUTPUT A REGISTER, IMMEDIATE MAX/MIN
 */

void
maxminri_ins(ins_p ins, int src1, long val,
			 int dest)
{
	int lab = new_label();
	
	if (!SIMM13_SIZE (val))  {
		fprintf (as_file, "\tset\t%ld,%s\n", val, RN (R_TMP));
		fprintf (as_file, "\tcmp\t%s,%s\n", RN (src1), RN (R_TMP));
		fprintf (as_file, "\t%s\t%s%d\n", ins, lab_prefix, lab);
		/* USE the delay slot */
		fprintf (as_file, "\tmov %s, %s\n", RN(src1), RN(dest));
		/* note set is two instruction, and
		 *	       	        must not go in the delay slot... */
		fprintf (as_file, "\tset %ld, %s\n", val, RN(dest));
#ifdef NEWDWARF
		lost_count_ins();
#endif
	} 
	else{
		fprintf (as_file, "\tcmp\t%s,%ld\n", RN (src1), val);
		fprintf (as_file, "\t%s\t%s%d\n", ins, lab_prefix, lab);
		/* USE the delay slot */
		fprintf (as_file, "\tmov %s, %s\n", RN(src1), RN(dest));
		fprintf (as_file, "\tmov %ld, %s\n", val, RN(dest));
#ifdef NEWDWARF
		count_ins(4);
#endif
		
	}
	set_label(lab);
	return;
}


/*
 *  OUTPUT A LOAD FLOATING REGISTER-OFFSET INSTRUCTION
 */

void
ldf_ro_ins(ins_p ins, baseoff a, int dest)
{
	long off = a.offset;
	assert (IS_FIXREG (a.base));
	clear_freg (dest);
	if (SIMM13_SIZE (off)) {
		/* Small offset */
		CONST char *rn = RN (a.base);
		if (off == 0) {
			fprintf (as_file, "\t%s\t[%s],%s\n", ins, rn, FRN(dest));
		} 
		else if (off > 0) {
			fprintf (as_file, "\t%s\t[%s+%ld],%s\n", ins, rn, off, FRN(dest));
		} 
		else /* if (off < 0) */ {
			fprintf (as_file, "\t%s\t[%s-%ld],%s\n", ins, rn, -off, FRN(dest));
		}
#ifdef NEWDWARF
		count_ins(1);
#endif
	} 
	else {
		/* Large offset */
		assert (a.base != R_TMP);
		ir_ins (i_set, off, R_TMP);
#ifdef NEWDWARF
		lost_count_ins();
#endif
		ldf_rr_ins (ins, a.base, R_TMP, dest);
	}
	return;
}


/*
 *  OUTPUT A LOAD FLOATING REGISTER-REGISTER INSTRUCTION
 */

void
ldf_rr_ins(ins_p ins, int reg1, int reg2,
		   int dest)
{
	clear_freg (dest);
	fprintf (as_file, "\t%s\t[%s+%s],%s\n", ins,
			 RN (reg1), RN (reg2), FRN(dest));
#ifdef NEWDWARF
	count_ins(1);
#endif
	return;
}


/*
 *  OUTPUT A LOAD FLOATING INSTRUCTION
 *
 *  If baseoff is a global this may be two instructions and involve
 *  a temporary register.
 */

void
ldf_ins(ins_p ins, baseoff a, int dest)
{
	if (!IS_FIXREG (a.base)) {
		/* global */
		baseoff tmp_off;
		tmp_off.base = R_TMP;
		tmp_off.offset = 0;
		set_ins (a, R_TMP);
		ldf_ro_ins (ins, tmp_off, dest);
	} 
	else {
		ldf_ro_ins (ins, a, dest);
	}
	return;
}


/*
 *  OUTPUT A STORE FLOATING REGISTER-OFFSET INSTRUCTION
 */

void
stf_ro_ins(ins_p ins, int src, baseoff a)
{
	long off = a.offset;
	assert (IS_FIXREG (a.base));
	if (a.base == R_TMP && ABS_OF (off)  > (16 + 1 + 6) * 4) {
		fail ("Temporary register problem in stf_ro_ins");
	}
	if (SIMM13_SIZE (off)) {
		/* Small offset */
		CONST char *rn = RN (a.base);
		if (off == 0) {
			fprintf (as_file, "\t%s\t%s,[%s]\n", ins, FRN(src), rn);
		} 
		else if (off > 0) {
			fprintf (as_file, "\t%s\t%s,[%s+%ld]\n", ins, FRN(src), rn, off);
		} 
		else /* if (off < 0) */ {
			fprintf (as_file, "\t%s\t%s,[%s-%ld]\n", ins, FRN(src), rn, -off);
		}
#ifdef NEWDWARF
		count_ins(1);
#endif
	} 
	else {
		/* Large offset */
		assert (a.base != R_TMP);
		ir_ins (i_set, off, R_TMP);
#ifdef NEWDWARF
		lost_count_ins();
#endif
		stf_rr_ins (ins, src, a.base, R_TMP);
	}
	return;
}


/*
 *  OUTPUT A STORE FLOATING REGISTER-REGISTER INSTRUCTION
 */

void
stf_rr_ins(ins_p ins, int src, int reg1, int reg2)
{
	fprintf (as_file, "\t%s\t%s,[%s+%s]\n", ins, FRN(src), 
			 RN (reg1), RN (reg2));
#ifdef NEWDWARF
	count_ins(1);
#endif
	return;
}


/*
 *  OUTPUT A STORE FLOATING INSTRUCTION
 *  
 *  If baseoff is a global this may be two instructions and involve
 *  a temporary register.
 */

void
stf_ins(ins_p ins, int src, baseoff a)
{
	if (!IS_FIXREG (a.base)) {
		/* global */
		baseoff tmp_off;
		tmp_off.base = R_TMP;
		tmp_off.offset = 0;
		set_ins (a, R_TMP);
		stf_ro_ins (ins, src, tmp_off);
	} 
	else {
		stf_ro_ins (ins, src, a);
	}
	return;
}


/*
 *  OUTPUT A FLOATING REGISTER, FLOATING REGISTER COMPARISON
 */

void
rrf_cmp_ins(ins_p ins, int src1, int src2)
{
	fprintf (as_file, "\t%s\t%s,%s\n", ins, FRN(src1), FRN(src2));
#ifdef NEWDWARF
	count_ins(1);
#endif
	return;
}


/*
 *  OUTPUT A FLOATING REGISTER, FLOATING REGISTER INSTRUCTION
 */

void
rrf_ins(ins_p ins, int src, int dest)
{
	clear_freg (dest);
	fprintf (as_file, "\t%s\t%s,%s\n", ins, FRN(src), FRN(dest));
#ifdef NEWDWARF
	count_ins(1);
#endif
	return;
}


/*
 *  OUTPUT A THREE FLOATING REGISTER INSTRUCTION
 */

void
rrrf_ins(ins_p ins, int src1, int src2, int dest)
{
	clear_freg (dest);
	fprintf (as_file, "\t%s\t%s,%s,%s\n", ins, FRN(src1), 
			 FRN(src2), FRN(dest));
#ifdef NEWDWARF
	count_ins(1);
#endif
	return;
}



/*
 *  OUTPUT AN OPERAND, AS PART OF AN ASM SEQUENCE
 */

void
out_asm_reg(int r, int fp)
{
	outs ((fp ? FRN(r) : RN(r)));
	return;
}

void
out_asm_boff(baseoff b, long o2)
{
	long off = b.offset + o2;
	if (off == 0)
		fprintf (as_file, "[%s]", RN(b.base));
	else if (off > 0)
		fprintf (as_file, "[%s+%ld]", RN(b.base), off);
	else /* if (off < 0) */
		fprintf (as_file, "[%s-%ld]", RN(b.base), -off);
	return;
}
