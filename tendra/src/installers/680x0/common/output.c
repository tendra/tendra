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
 *Revision 1.4  1997/11/13 08:27:18  ma
 *All avs test passed (except add_to_ptr).
 *
 *Revision 1.3  1997/11/10 15:38:10  ma
 *.
 *
 *Revision 1.2  1997/11/09 14:21:00  ma
 *.
 *
 *Revision 1.1.1.1  1997/10/13 12:42:57  ma
 *First version.
 *
 *Revision 1.3  1997/06/18 12:04:56  ma
 *Merged with Input Baseline changes.
 *
 *Revision 1.2  1997/05/13 11:30:38  ma
 *Introduced make_comment for debug.
 *
 *Revision 1.1.1.1  1997/03/14 07:50:16  ma
 *Imported from DRA
 
 * Revision 1.2  1996/09/20  13:51:41  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:58  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:16  john
 *
 * Revision 1.2  94/02/21  16:02:42  16:02:42  ra (Robert Andrews)
 * Put in an explicit cast.
 *
 * Revision 1.1  93/02/22  17:16:29  17:16:29  ra (Robert Andrews)
 * Initial revision
 *
 *--------------------------------------------------------------------------
 */


#include "config.h"
#include "common_types.h"
#include "assembler.h"
#include "instrs.h"
#include "fbase.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "output.h"
#include "codex.h"


/*
 *    OUTPUT FILE
 */

FILE *fpout;


/*
 *    OPEN OUTPUT FILE
 *
 *    This routine opens the file with the given name for output.  If the
 *    name is null, the standard output is used.
 */

void
open_output(char *nm)
{
    if (nm == null) {
		fpout = stdout;
    } else {
		fpout = fopen (nm, "w");
		if (fpout == null) {
			error ("Can't open output file, %s", nm);
			exit (EXIT_FAILURE);
		}
    }
    return;
}


/*
 *    ARRAY OF INSTRUCTION NAMES
 *
 *    This table gives the mapping between instruction numbers and the
 *    corresponding names.
 */

#ifdef asm_dotty_instrs
#define INSTR_SET_0
#endif /* asm_dotty_instrs */

#ifdef asm_simple_instrs
#define INSTR_SET_1
#endif /* asm_simple_instrs */

char *instr_names [] = {
#include "instr_aux.h"
};


/*
 *    ARRAY OF GLOBAL REGISTER NAMES
 *
 *    This table gives the mapping between register numbers and register
 *    names.
 */

#ifdef asm_percent_regs
#define REGISTER_SET_0
#endif /* asm_percent_regs */

#ifdef asm_simple_regs
#define REGISTER_SET_1
#endif /* asm_simple_regs */

static char *glob_reg_names [] = {
#include "instr_aux.h"
};


/*
 *    ARRAY OF LOCAL REGISTER NAMES
 *
 *    This table gives the local mapping between register numbers and
 *    register names.  It is initialized from the table of global register
 *    names, but may be changed thereafter.
 */

char *reg_names [ NO_OF_REGS ];


/*
 *    OUTPUT A REGISTER NAME
 *
 *    This routine outputs the register name corresponding to a given
 *    register number.
 */

#define  out_reg_name(X)	outs (reg_names [ (X) ])


/*
 *    OUTPUT A SUM OF DATA, EXTERNALS AND LABELS
 *
 *    This routine prints the sum of all data, external and labels, starting
 *    with ptr, and moving down the plus-chain.
 */

static void
out_data(mach_op *ptr)
{
    mach_op *p;
    bool neg_next = 0;
    bool need_plus = 0;
    for (p = ptr ; p ; p = p->plus) {
		switch (p->type) {
			
	    case MACH_EXT :
	    case MACH_EXTQ : {
			if (need_plus || neg_next) outc (neg_next ? '-' : '+');
			outs (p->def.str);
			need_plus = 1;
			neg_next = 0;
			break;
	    }
			
	    case MACH_LAB :
	    case MACH_LABQ : {
			if (need_plus || neg_next) outc (neg_next ? '-' : '+');
			outc (LPREFIX);
			outn (p->def.num);
			need_plus = 1;
			neg_next = 0;
			break;
	    }
			
	    case MACH_SPEC :
	    case MACH_SPECQ : {
			if (!output_immediately && p->def.str == special_str) {
				/* The value of LSx is known, so use it */
				long n = ldisp;
				if (neg_next) n = (-n);
				if (p->plus && p->plus->type == MACH_VAL) {
					p->plus->def.num += n;
				} else {
					if (need_plus && n >= 0) outc ('+');
					outn (n);
					need_plus = 1;
				}
			} else {
				if (need_plus || neg_next) outc (neg_next ? '-' : '+');
				outc (LPREFIX);
				outs (p->def.str);
				outn ((long) special_no);
				need_plus = 1;
			}
			neg_next = 0;
			break;
	    }
			
	    case MACH_VAL :
	    case MACH_VALQ : {
			long n = p->def.num;
			if (neg_next) n = (-n);
			if (need_plus && n >= 0) outc ('+');
			outn (n);
			need_plus = 1;
			neg_next = 0;
			break;
	    }
			
	    case MACH_HEX :
	    case MACH_HEXQ : {
			long n = p->def.num;
			if (neg_next) n = (-n);
			if (need_plus && n >= 0) outc ('+');
			outh (n);
			need_plus = 1;
			neg_next = 0;
			break;
	    }
			
	    case MACH_NEG : {
			neg_next = 1;
			break;
	    }
			
	    default : return;
		}
    }
    return;
}


/*
 *    OUTPUT A SCALED OPERAND
 *
 *    This routine outputs a scaled register operand.
 */

static void
out_scaled(mach_op *ptr)
{
    long sf = ptr->def.num;
    asm_scale_before;
    out_reg_name (ptr->of->def.num);
    if (sf == 1) {
		asm_scale_1;
    } else {
		asm_scale;
		outn (sf);
    }
    return;
}


/*
 *    OUTPUT A FLOATING POINT NUMBER
 *
 *    This routine outputs a floating point number.
 */

static void
out_float(flt *f)
{
#if (FBASE == 10)
    int i;
    asm_fprefix;
    if (f->sign < 0) outc ('-');
    outc ('0' + f->mant [0]);
    outc ('.');
    for (i = 1 ; i < MANT_SIZE ; i++) outc ('0' + f->mant [i]);
    outc ('e');
    if (f->exp >= 0) outc ('+');
    outn (f->exp);
#else
    error ("Illegal floating point constant");
#endif
    return;
}


/*
 *    MACROS FOR CONSTRUCTS DEPENDING ON asm_data_first
 */

#ifdef asm_data_first

#define  out_data_1(X)	if (X) out_data (X)
#define  out_data_1a(X)	if (X) { out_data (X) ; outc (',') ; }
#define  out_data_1b(X)	if (X) { outc (',') ; out_data (X) ; }
#define  out_sf_data(X, Y)	if (Y) out_scaled (Y)

#else /* asm_data_first */

#define  out_data_1(X)	/* empty */
#define  out_data_1a(X)	/* empty */
#define  out_data_1b(X)	/* empty */
#define  out_sf_data(X, Y)	\
    if (X) {			\
	outc ('(') ;		\
	out_data (X) ;	\
	if (Y) {		\
	    outc (',') ;	\
	    out_scaled (Y) ;	\
	}			\
	outc (')') ;		\
    } else {			\
	if (Y) {		\
	    outc ('(') ;	\
	    out_scaled (Y) ;	\
	    outc (')') ;	\
	}			\
    }

#endif /* asm_data_first */


/*
 *    OUTPUT A MACHINE OPERAND
 *
 *    This routine prints a machine operand.
 */

static void
out_mach_op(mach_op *ptr)
{
    mach_op *p = ptr;
    switch (p->type) {
		
	case MACH_BF : {
	    /* Bitfield operands */
	    long bf_off = p->def.num;
	    long bf_bits = p->plus->def.num;
	    out_mach_op (p->of);
	    asm_bf_before;
	    asm_nprefix;
	    outn (bf_off);
	    asm_bf_middle;
	    asm_nprefix;
	    outn (bf_bits);
	    asm_bf_after;
	    return;
	}
		
	case MACH_CONT : {
	    p = p->of;
	    switch (p->type) {
			
		case MACH_CONT : {
		    /* Memory indirect (post- or pre-indexed) */
		    mach_op *p1 = p->plus;
		    mach_op *p2 = null;
		    mach_op *q = p->of;
		    mach_op *q1 = q->plus;
		    mach_op *q2 = null;
		    if (p1 && p1->type == MACH_SCALE) {
				p2 = p1;
				p1 = p2->plus;
		    }
		    if (q1 && q1->type == MACH_SCALE) {
				if (p2) {
					error ("Illegal addressing mode");
					outs ("error");
					return;
				}
				q2 = q1;
				q1 = q2->plus;
		    }
		    asm_mem_before;
		    out_data_1a (q1);
		    out_reg_name (q->def.num);
		    asm_mem_second;
		    out_sf_data (q1, q2);
		    asm_mem_third;
		    out_sf_data (p1, p2);
		    if (p2) out_scaled (p2);
		    out_data_1b (p1);
		    asm_mem_after;
		    return;
		}
			
		case MACH_REG : {
		    /* Register indirect (with displacement or index) */
		    mach_op *p1 = p->plus;
		    mach_op *p2 = null;
		    if (p1) {
				if (p1->type == MACH_SCALE) {
					p2 = p1;
					p1 = p2->plus;
				}
				out_data_1 (p1);
		    }
		    asm_ind_before;
		    out_reg_name (p->def.num);
		    asm_ind_middle;
		    out_sf_data (p1, p2);
		    asm_ind_after;
		    return;
		}
			
		case MACH_EXTQ : {
		    /* External indirect (with displacement or index) */
		    mach_op *p1 = p->plus;
		    mach_op *p2 = null;
		    if (p1) {
				if (p1->type == MACH_SCALE) {
					p2 = p1;
					p1 = p2->plus;
				}
				out_data_1 (p1);
		    }
		    asm_ind_before;
		    outs (p->def.str);
		    asm_ind_middle;
		    out_sf_data (p1, p2);
		    asm_ind_after;
		    return;
		}
			
		case MACH_EXT :
		case MACH_LAB :
		case MACH_SPEC :
		case MACH_VAL :
		case MACH_HEX :
		case MACH_NEG : {
		    /* Contents of immediate data, externals, labels */
		    out_data (p);
		    return;
		}
	    }
	    error ("Illegal addressing mode");
	    outs ("error");
	    return;
	}
		
	case MACH_DEC : {
	    /* Register indirect with predecrement */
	    asm_predec_before;
	    out_reg_name (p->def.num);
	    asm_predec_after;
	    return;
	}
		
	case MACH_INC : {
	    /* Register indirect with postincrement */
	    asm_postinc_before;
	    out_reg_name (p->def.num);
	    asm_postinc_after;
	    return;
	}
		
	case MACH_REG : {
	    /* Register direct */
	    out_reg_name (p->def.num);
	    return;
	}
		
	case MACH_RPAIR : {
	    /* Register pair */
	    out_reg_name (p->def.num);
	    asm_rpair_sep;
	    out_reg_name (p->plus->def.num);
	    return;
	}
		
	case MACH_EXT :
	case MACH_LAB :
	case MACH_SPEC :
	case MACH_VAL :
	case MACH_HEX : {
	    /* Immediate data, externals, labels */
	    asm_nprefix;
	    out_data (p);
	    return;
	}
		
	case MACH_EXTQ :
	case MACH_LABQ :
	case MACH_SPECQ : {
	    /* Contents of externals, labels */
	    out_data (p);
	    return;
	}
		
	case MACH_FLOATQ : {
	    /* Floating-point data */
	    out_float (p->def.fp);
	    return;
	}
		
	case MACH_VALQ : {
	    /* Integer data */
	    outn (p->def.num);
	    return;
	}
		
	case MACH_HEXQ : {
	    /* Integer data */
	    outh (p->def.num);
	    return;
	}
    }
    error ("Illegal addressing mode");
    outs ("error");
    return;
}


/*
 *    OUTPUT ALL MACHINE INSTRUCTIONS
 *
 *    This routine outputs all the machine instructions, together with their
 *    operands (if any).
 */

void
output_all()
{
    int n;
    mach_ins *p;
    for (p = all_mach_ins ; p ; p = p->next) {
		n = p->ins_no;
#ifdef EBUG
#if 1
        if (n != m_comment) {
			outs ("#inst");
			outn (p->id);
			outnl ();
        }
        if (p->id == 4921) {
			int found = 1;
        }
#endif
#endif
		switch (n) {
#ifdef EBUG
		case m_comment : {
			outs ("#");
			outs (p->op1->def.str);
			outnl ();
			break;
		}
#endif
			
#ifdef m_ignore_ins
	    case m_ignore_ins : {
			/* Ignore */
			break;
	    }
#endif /* m_ignore_ins */
			
	    case m_label_ins : {
			/* Labels */
			outc (LPREFIX);
			outn (p->op1->def.num);
			outc (':');
			outnl ();
			break;
	    }
			
	    case m_extern_ins : {
			/* Externals */
			out_data (p->op1);
			outc (':');
			outnl ();
			break;
	    }
			
#ifdef asm_uses_equals
	    case m_as_assign : {
			out_mach_op (p->op1);
			outc ('=');
			out_mach_op (p->op2);
			outnl ();
			break;
	    }
#endif /* asm_uses_equals */
			
	    case m_as_byte :
	    case m_as_short :
	    case m_as_long :
	    case m_stabs :
	    case m_stabd :
	    case m_stabn :
	    case m_dd_special : {
			/* Data */
			mach_op *q;
			bool started = 0;
			int c = 0;
			for (q = p->op1 ; q ; q = q->of) {
				if (c == 0) {
					if (started) outnl ();
					outs (instr_names [n]);
				} else {
					outc (',');
				}
				out_data (q);
				started = 1;
				if (++c == 8) c = 0;
			}
			outnl ();
			break;
	    }
			
	    default : {
			if (is_jump (n)) {
				/* Jumps */
#ifndef asm_does_jump_lens
				if (is_unsized (n)) n += long_jump;
#endif /* !asm_does_jump_lens */
				outs (instr_names [n]);
				outc (LPREFIX);
				outn (p->op1->def.num);
				if (n == m_bra || n == m_brab ||
					n == m_braw || n == m_bral) {
					/* Align after unconditional jumps */
					outnl ();
#ifndef no_align_directives
					outs (instr_names [ m_as_align4 ]);
#endif
				}
			} else {
				/* Simple instructions */
				outs (instr_names [n]);
				if (p->op1) out_mach_op (p->op1);
				if (p->op2) {
					outc (',');
#ifdef EBUG
					outc (' ');
#endif /* EBUG */
					out_mach_op (p->op2);
				}
			}
			outnl ();
			break;
	    }
		}
    }
    return;
}


/*
 *    INITIALIZE INSTRUCTIONS
 *
 *    Apply a couple of patches for odd instruction quirks.
 */

void
init_instructions()
{
#ifdef asm_no_btst_suffix
    instr_names [ m_btstb ] = instr_names [ m_btst ];
    instr_names [ m_btstl ] = instr_names [ m_btst ];
#endif /* asm_no_btst_suffix */
    return;
}


/*
 *    INITIALIZE OUTPUT ROUTINES
 *
 *    This routine copies the table of global register names into the
 *    table of global register names and
 */

void
init_output()
{
    memcpy (reg_names, glob_reg_names, sizeof (glob_reg_names));
#ifdef SYSV_ABI
    {
		char *r = reg_names [ REG_A0 ];
		reg_names [ REG_A0 ] = reg_names [ REG_A1 ];
		reg_names [ REG_A1 ] = r;
    }
#endif /* SYS_ABI */
    all_mach_ins = null;
    current_ins = null;
    return;
}


#ifdef EBUG

extern bool seek_line;
extern int seek_line_no;


/*
 *    OUTPUT NEW LINE (DEBUG MODE ONLY)
 *
 *    In debug mode a count is keep of the current line number in the
 *    output file to allow stopping the debugger at a given line.  Normally
 *    outnl is a macro which just outputs a newline character.
 */

void
outnl()
{
    static int line_no = 0;
    outc ('\n');
    line_no++;
    if (seek_line && line_no == seek_line_no) {
		warning ("Line %d reached", line_no);
		breakpoint ();
    }
    return;
}

#endif /* EBUG */
