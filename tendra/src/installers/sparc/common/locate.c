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
 * Revision 1.11  1997/08/23  13:53:55  pwe
 * initial ANDF-DE
 *
 * Revision 1.10  1997/02/18  11:47:54  pwe
 * NEWDIAGS for debugging optimised code
 *
 * Revision 1.9  1996/03/20  16:13:56  john
 * Reformatting
 *
 * Revision 1.8  1996/01/23  10:31:13  john
 * Fix to handle env_offset in locate
 *
 * Revision 1.7  1995/12/15  10:24:59  john
 * Changed env_offset calculation
 *
 * Revision 1.6  1995/11/24  11:41:22  john
 * Change to caller location
 *
 * Revision 1.5  1995/11/02  18:03:43  john
 * Stopped using local reg to access data
 *
 * Revision 1.4  1995/07/14  16:31:26  john
 * Minor change
 *
 * Revision 1.3  1995/06/14  15:34:08  john
 * Fixed error in calculating offset for local_reg based address.
 *
 * Revision 1.2  1995/05/26  12:59:16  john
 * Changes for new spec (3.1)
 *
 * Revision 1.1.1.1  1995/03/13  10:18:42  john
 * Entered into CVS
 *
 * Revision 1.5  1994/12/01  13:47:39  djch
 * Create boff_env_offset to get the stack offset of an ident. Needs to trace the
 * parent proc.
 *
 * Revision 1.4  1994/07/04  10:48:58  djch
 * Jun94 tape version
 *
 * Revision 1.3  1994/05/25  14:15:07  djch
 * Added CREATE_instore_bits to shut up tcc
 *
 * Revision 1.2  1994/05/13  12:34:45  djch
 * Incorporates improvements from expt version
 * Use of new macros in addrtypes.h
 *
 * Revision 1.1  1994/05/03  14:49:41  djch
 * Initial revision
 *
 * Revision 1.5  93/08/27  11:29:36  11:29:36  ra (Robert Andrews)
 * Added a couple of explicit integer casts.
 * 
 * Revision 1.4  93/08/13  14:38:14  14:38:14  ra (Robert Andrews)
 * Reformatted.
 * 
 * 
 * Revision 1.3  93/07/05  18:20:37  18:20:37  ra (Robert Andrews)
 * Reordered include files.
 * 
 * Revision 1.2  93/06/29  14:27:11  14:27:11  ra (Robert Andrews)
 * Changed failer to fail.
 * 
 * Revision 1.1  93/06/24  14:58:37  14:58:37  ra (Robert Andrews)
 * Initial revision
 * 
 *--------------------------------------------------------------------------
 */

#define SPARCTRANS_CODE
#include "config.h"
#include "common_types.h"
#include "myassert.h"
#include "addrtypes.h"
#include "expmacs.h"
#include "tags.h"
#include "inst_fmt.h"
#include "regmacs.h"
#include "sparcins.h"
#include "bitsmacs.h"
#include "exp.h"
#include "procrec.h"
#include "guard.h"
#include "eval.h"
#include "regexps.h"
#include "shapemacs.h"
#include "comment.h"
#include "getregs.h"
#include "move.h"
#include "regable.h"
#include "codehere.h"
#include "proc.h"
#include "locate.h"
#include "flags.h"
#include "translat.h"

int call_base_reg = R_SP;

/*
 *  DECODE x INTO A BASE REGISTER PLUS OFFSET
 */

baseoff
boff(exp e)
{
	int n = no (e);
	int b = REG_PART(n);
	baseoff an;
	if (isglob (e)) {
		/* bro is index in main_globals */
		dec *gl = brog (e);
		long sno = gl->dec_u.dec_val.sym_number;
		an.base = (int) (-(sno + 1));
		an.offset = 0;
	} 
	else if (isparam (e) && name(son(e)) != formal_callee_tag) {
		/* parameter, positive offset from %fp */
		/* assert (name (son (e)) == clear_tag) ;*/
		an.base = R_FP;
		an.offset = BITS2BYTES(no (son (e)) + proc_state.params_offset);
		assert (an.offset >= BITS2BYTES(proc_state.params_offset));
	} 
	else if (isparam(e) && name(son(e)) == formal_callee_tag){
		an.base = R_SP;
		an.offset = BITS2BYTES(no(son(e)));
#if 1
		if (Has_vcallees){
			an.base = local_reg;
			an.base = callee_start_reg;
			an.offset = BITS2BYTES(no(son(e)));
		}
		else{
/*
 *      an.base = R_FP;
 *      an.offset = BITS2BYTES(no(son(e)) - proc_state.callee_size);
 */
			an.base = callee_start_reg;
			an.offset = BITS2BYTES(no(son(e)));
		}
#endif
	}
	else if (name(son(e)) == caller_name_tag){
		/* caller name tag is located at [%sp+paramsoffset] */
		an.base = R_SP;
		an.base = call_base_reg;
		an.offset = BYTE_OFFSET_PART(n) + BITS2BYTES(PARAMS_OFFSET);
		
	}	
	else if (b == R_FP) {
		/* locally declared things, negative offset from %fp */
		an.base = R_FP;
		an.offset = -(BITS2BYTES(proc_state.locals_space)) +
			BYTE_OFFSET_PART(n) + BITS2BYTES(proc_state.locals_offset) /*-
																		*      BITS2BYTES(proc_state.callee_size)*/;
		assert (an.offset <= 0);
		assert (an.offset >= -(BITS2BYTES(proc_state.locals_space /*+ 
																   *				       proc_state.callee_size*/)));
	} 
	else if (b == R_SP) {
		/* on stack temps */
		an.base = R_SP;
		an.offset = BYTE_OFFSET_PART(n);
	} 
#if 0
	else if (b == local_reg && Has_vcallees){
		an.base = b;
		an.offset = -(BITS2BYTES(proc_state.locals_space)) +
			BYTE_OFFSET_PART(n) + BITS2BYTES(proc_state.locals_offset);
	}	
#endif
	else if (b <= 31) {
		/* other base register and offset */
		an.base = b;
		an.offset = BYTE_OFFSET_PART(n);
	}	
	
#if 1
	/* obsolete */
	else if (b == 32) {
		/* global names */
		an.base = - ADDR_PART(n);
		an.offset = 0;
	} 
	else if (b == 33) {
		/* local data label : LDNNNN */
		an.base = ADDR_PART(n);
		an.offset = 0;
	}
#endif
	else {
		fail ("not a baseoff in boff");
	}
	return (an);
}

int
boff_env_offset(exp e)
{
	/* used ONLY for envoffsets as init values for globals. 
	 *   cf make_proc_tag_code */
	int n = no (e);
	/*int b = REG_PART(n);*/
	int offset = 0x7fffffff;/* if not set should be outside stack seg */
	/*int this_callee_size = 0;*/
	exp x = e;
	assert (! isglob (e));
	/*assert (b == R_FP);*/
	
#define VAL_params_offset ((16 + 1) * 32)
#define VAL_locals_offset (0)
	while (name(x) != proc_tag && name(x)!=general_proc_tag){
		x = father(x);
		assert (x != nilexp);
	}
	if (isparam (e)) {
		/* parameter, positive offset from %fp */
		/*    assert (name (son (e)) == clear_tag) ;*/
		if (name(son(e)) == formal_callee_tag) {
			offset =  no(son(e))>>3;
		}
		else {
			offset = BITS2BYTES(no (son (e)) + VAL_params_offset);
			assert (offset >= BITS2BYTES(VAL_params_offset));
		}
	} 
	else {
		/* locally declared things, negative offset from %fp */
		/* Now we need the stack size from the procrec, so find the proc */
		long locals_space;
		
		locals_space = procrecs[no(x)].spacereqproc.stack;
		locals_space = (locals_space +63) &~63; /* 8 byte aligned */
		offset = -(BITS2BYTES(locals_space)) +
			BYTE_OFFSET_PART(n) + BITS2BYTES(VAL_locals_offset);
		assert (offset < 0);
		assert (offset >= -(BITS2BYTES(locals_space)));
	}
	return (offset);
}	


/*
 *  AUXILLIARY LOCATION ROUTINE
 *
 *  Finds the address of the expression e using shape s.  sp gives the
 *  available t-registers for any inner evaluation.  dreg is 
 *  historical.
 */

where
locate1(exp e, space sp, shape s, int dreg)
{
	ash a;
	ans aa;
	where wans;
	a = ashof (s);
	
	switch (name (e)) {
    case name_tag : {
		/* this a locally declared name ... */
		exp dc = son (e);
		bool var = (bool) isvar (dc);
		if (props (dc) & defer_bit) {
			/* ... it has been identified with a simple expression
			 *	   which is better evaluated every time */
			where w;
			w = locate (son (dc), sp, sh (son (dc)), dreg);
			if (no (e) == 0) {
				aa = w.answhere;
			} 
			else {
				instore is;
				switch (discrim (w.answhere)) {
				case notinreg : {
					is = insalt (w.answhere);
					is.b.offset += (no (e) / 8);
					break;
				}
				default : {
					fail ("name not deferable");
				}
				}
				setinsalt (aa, is);
			}
		} 
		else if (props (dc) & inreg_bits) {
			/* ... it has been allocated in a fixed point register */
			if (var) {
				setregalt (aa, no (dc));
			} 
			else {
				instore b;
				b.b.base = no (dc);
				b.b.offset = 0;
				b.adval = 1;
				setinsalt (aa, b);
			}
		} 
		else if (props (dc) & infreg_bits) {
			/* ... it has been allocated in a floating point register */
			freg fr;
			fr.fr = no (dc);
			fr.dble = (bool) ((a.ashsize == 64) ? 1 : 0);
			setfregalt (aa, fr);
		} 
		else {
			/* ... it is in memory */
			instore is;
			if (var || (name (sh (e)) == prokhd &&
						(son (dc) == nilexp ||
						 name (son (dc)) == proc_tag ||
						 name(son(dc)) == general_proc_tag))) {
				is.adval = 1;
			} 
			else {
				is.adval = 0;
			}
			is.b = boff (dc);
			is.b.offset += BITS2BYTES(no(e));
			setinsalt(aa,is);
		}
		wans.answhere = aa;
		wans.ashwhere = a;
		return (wans);
    }
    case addptr_tag : {
		exp sum = son (e);
		where wsum;
		int addend;
		space nsp;
		int reg;
		int ind = R_NO_REG;
		instore is;
		ans asum;
		
		wsum = locate (sum, sp, sh (sum), 0);
		asum = wsum.answhere;
		
		/* answer is going to be wsum displaced by integer result of
		 *       evaluating bro (sum) */
		switch (discrim (asum)) {
		case notinreg : {
			is = insalt (asum);
			if (is.adval) {
				/* wsum is a literal address in store ... */
				baseoff b;
				b = is.b;
				if (!IS_FIXREG (b.base)) {
					/* ... it is not a base-offset, so make it one */
					reg = getreg (sp.fixed);
					set_ins (b, reg);
					keepreg (sum, reg);
					b.base = reg;
					b.offset = 0;
				}
				nsp = guardreg (b.base, sp);
				addend = reg_operand (bro (sum), nsp);
				
				/* evaluate the displacement ... */
				if (dreg == 0) dreg = getreg (nsp.fixed);
				rrr_ins (i_add, b.base, addend, dreg);
				clear_reg (dreg);
				
				/* ... add it to the base register into new reg */
				b.base = dreg;
				is.b = b;
				setinsalt (aa, is);
				wans.answhere = aa;
				wans.ashwhere = a;
				
				/* ...and use it as base a literal base-offset result */
				keepexp (e, aa);
				return (wans);
			} 
			else {
				/* wsum represents an actual pointer in store ... */
				/* ... so load it into a good register */
				ind = getreg (sp.fixed);
				ld_ins (i_ld, is.b, ind);
			}
			break;
		}
		case inreg : {
			/* wsum is already in reg */
			ind = regalt (asum);
			break;
		}
		default : {
			fail ("locate ? reg");
		}
		}
		/*register ind contains the evaluation of 1st operand of addptr*/
		if (name (bro (sum)) == env_offset_tag || 
			name (bro(sum)) == general_env_offset_tag) {
			is.b.base = ind;
			is.b.offset = boff_env_offset(son(bro(sum)));
		}
		nsp = guardreg (ind, sp);
		addend = reg_operand (bro (sum), nsp);
		/* evaluate displacement, add it to ind in new reg */
		if (dreg == 0) dreg = getreg (nsp.fixed);
		rrr_ins (i_add, ind, addend, dreg);
		clear_reg (dreg);
		is.b.base = dreg;
		is.b.offset = 0;
		is.adval = 1;
		setinsalt (aa, is);
		wans.answhere = aa;
		wans.ashwhere = a;
		/* ... and deliver literal base_offset */
		keepexp (e, aa);
		return (wans);
    }
    case subptr_tag : {
		/* shouldn't occur */
		exp sum = son (e);
		int ind = reg_operand (sum, sp);
		instore isa;
		isa.adval = 1;
		sum = bro (sum);
		if (name (sum) == val_tag) {
			isa.b.base = ind;
			isa.b.offset = -no (e);
			setinsalt (aa, isa);
		} 
		else {
			if (dreg == 0) dreg = getreg (sp.fixed);
			rrr_ins (i_sub, ind,
					 reg_operand (sum, guardreg (ind, sp)), dreg);
			isa.b.base = dreg;
			isa.b.offset = 0;
		}
		setinsalt (aa, isa);
		wans.answhere = aa;
		wans.ashwhere = a;
		keepexp (e, aa);
		return (wans);
    }
    case reff_tag : {
		/* answer is going to be wans displaced by no (e) */
		wans = locate (son (e), sp, sh (son (e)), 0);
		switch (discrim (wans.answhere)) {
		case notinreg : {
			instore isa;
			isa = insalt (wans.answhere);
			if (!isa.adval) {
				/* wans is an actual pointer in store, so make it
				 *	       into a literal address ...  */
				int reg = getreg (sp.fixed);
				ld_ins (i_ld, isa.b, reg);
				isa.b.offset = 0;
				isa.b.base = reg;
				isa.adval = 1;
			}
			/* ... and add appropriate displacement to give result */
			isa.b.offset += BITS2BYTES(no (e));
			setinsalt (wans.answhere, isa);
			keepexp (e, wans.answhere);
			break;
		}
		case inreg : {
			/* wans is a pointer in a register */
			instore isa;
			
			isa.b.base = regalt (wans.answhere);
			isa.adval = 1;
			isa.b.offset = BITS2BYTES(no (e));
			setinsalt (wans.answhere, isa);
			break;
		}
		default : {
			fail ("locate ? reg ");
		}
		}
		wans.ashwhere = a;
		return (wans);
    }
    case cont_tag :
    case contvol_tag : {
		exp se = son (e);
		ans ason;
		instore isa;
		int reg;
		where fc;
		/* answer is contents of address represented by fc */
		fc = locate (se, sp, sh (e), 0);
		ason = fc.answhere;
		switch (discrim (ason)) {
		case notinreg : {
			isa = insalt (ason);
			if (isa.adval) {
				/* literal store address, make it a direct one */
				isa.adval = 0;
				setinsalt (aa, isa);
			} 
			else {
				/* actual pointer in store so load it into reg and
				 *	       deliver direct base-offset (reg, 0) */
				reg = getreg (sp.fixed);
				ld_ins (i_ld, isa.b, reg);
				isa.b.base = reg;
				isa.b.offset = 0;
				setinsalt (aa, isa);
				if (name (e) != contvol_tag &&
					fc.ashwhere.ashalign != 1) {
					keepexp (e, aa);
				}
			}
			goto breakson;
		}
		case inreg : {
			/* this one is fraught - it depends on only being used
			 *	     in lh-value positions from vars - take care */
			isa.b.base = regalt (ason);
			isa.b.offset = 0;
			isa.adval = 1;
			setinsalt (aa, isa);
			/* fc is in register, so deliver literal base-offset */
			goto breakson;
		}
		case infreg : {
			/* ditto caveat above */
			aa = ason;
			goto breakson;
		}
		default : {
			fail ("locate ? reg");
		}
		}
		breakson :
			wans.answhere = aa;
		wans.ashwhere = a;
		return (wans);
    }
    case top_tag : {
		/* does this ever happen? */
		setregalt (aa, 0);
		wans.answhere = aa;
		wans.ashwhere = a;
		return (wans);
    }
    case field_tag : {
		/* answer is wans displace literally by no (e) ; it should
		 *	 always be a literal store address */
		wans = locate (son (e), sp, sh (son (e)), 0);
		switch (discrim (wans.answhere)) {
		case notinreg : {
			instore isa;
			isa = insalt (wans.answhere);
			isa.b.offset += BITS2BYTES(no (e));
			setinsalt(wans.answhere,isa);
			break;
		}
		default : {
			fail ("field should be transformed");
		}
		}
		wans.ashwhere = a;
		return (wans);
    }
    default : {
		/* general catch all ; evaluate e into register and deliver
		 *	 it as a literal store address */
		int r = reg_operand (e, sp);
		instore is;
		/* Is this needed on SPARC??? */
		if (r == R_O0) {
			/* guard possible result from proc - can do better */
			r = getreg (sp.fixed);
			if (r != R_O0) rr_ins (i_mov, R_O0, r);
		}
		is.b.base = r;
		is.b.offset = 0;
		is.adval = 1;
		setinsalt (aa, is);
		wans.answhere = aa;
		wans.ashwhere = a;
		return (wans);
    }
	}
}


/*
 *  MAIN LOCATION ROUTINE
 *
 *  This is similar to locate1, but firstly checks if e is kept in a
 *  register.
 */

where
locate(exp e, space sp, shape s, int dreg)
{
	ans ak;
	where w;
	ak = iskept (e);
	if (discrim (ak) == inreg && regalt (ak) == 0) {
		w = locate1 (e, sp, s, dreg);
	} 
	else {
		w.answhere = ak;
		w.ashwhere = ashof (s);
	}
	return (w);
}




