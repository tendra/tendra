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
 * Revision 1.2  1998/02/04  15:49:09  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:58  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:04:27  pwe
 * add banners and mod for PWE ownership
 *
 **********************************************************************/


#include "config.h"
#include "memtdf.h"
#include "codegen.h"
#include "geninst.h"
#include "translat.h"
#include "makecode.h"
#include "machine.h"
#include "flags.h"
#include "myassert.h"
#include "comment.h"
#include "proc.h"
#include "stack.h"
/* All measurements in bytes */
long p_frame_size=0;		/* total size of frame */  
long p_locals_offset=0;	/* where the locals live  */
long p_maxargbytes=0;	/* the largest size of the param area */
long p_args_and_link_size=0;	/* used by alloca */
bool p_has_fp=0;

bool p_leaf=0;
bool p_has_back_chain=0;
bool p_save_all_sregs=0;
bool p_has_alloca=0;
bool p_has_vcallees=0;
bool p_has_no_vcallers=0;

long p_fixed_params=0;
long p_float_params=0;
long p_sreg_first_save=0;
long p_sfreg_first_save=0;

bool p_has_saved_sp=0;
long p_saved_sp_offset=0;
int p_return_label=0; /* the number of the label which contains the return */
ans p_result;
long p_callee_size;

bool p_has_tp;

exp p_current;
long p_no_of_returns =0;

/*
 * The function of this file is to keep a lot of the stack controlling 
 * functions in the same place, so that they can be easily and consistently
 * maintained. I have introduced several new variables to make things easier
 * to follow.
 *
 *	|              |
 *	|              |
 *------->|--------------|<======R_FP                v
 *	|   Saved      |                           |
 *	|    FPR       |                           |
 *	|              |                           |
 *	|--------------|                           |
 *	|   Saved      |                           |< p_frame_size(bytes)
 *	|    GPR       |                           |
 *	|              |                           |
 *	|--------------|                           |
 *	| Possible word|for 8 byte alignment       |
 *	|--------------|                           |
 *	|              |                           |
 *	|--------------|                           |
 *	|  Saved SP    |<-- If have saved_sp       |
 *	|--------------|  this is where it lives   |
 *	|              |                           | 
 *	|              |                           | 
 *	|              |                           | 
 *	|              |                           |
 *    >56 |--------------|         v                 | 
 *	|    Pn        |         |                 |                 
 *	|     .        |         |                 |       
 *	|     .        |         |                 |                 
 *	|     .        |         |                 |  
 *	|     .        |         |                 |     
 *	|    P1        |         |< PROC_ARGS_AND_ |                 
 *      24|--------------|         |     LINK_SIZE   |                 
 *	|   Saved TOC  |         |     (bytes)     |                 
 *      20|--------------|         |                 |                 
 *	|   Reserved2  |         |                 |                 
 *      16|--------------|         |                 |                 
 *	|   Reserved1  |         |                 |                 
 *      12|--------------|         |                 |                 
 *	|   Saved LR   |         |                 |                 
 *       8|--------------|         |                 |                 
 *	|   Saved CR   |         |                 |                 
 *       4|--------------|         |                 |                 
 *	|  Back Chain  |         |                 |                 
 *-----> 0|--------------|<=====R_SP                 ^
 *          STACK_TEMP
 */
void
initialise_procedure(procrec *pr)
{
	p_sreg_first_save= pr->sreg_first_save;
	p_sfreg_first_save = pr->sfreg_first_save;
	p_has_alloca = pr->alloca_proc;
	p_save_all_sregs = pr->save_all_sregs;
	p_frame_size = pr->frame_size>>3; /* in bytes */
	p_locals_offset = pr->locals_offset>>3; /* in bytes */
	p_maxargbytes = pr->maxargs>>3; /* in bytes */
	p_has_fp = pr->has_fp;
	p_has_tp = pr->has_tp;
	p_has_saved_sp = pr->has_saved_sp;
	p_leaf = pr->leaf_proc;
	p_callee_size = pr->callee_size>>3;
	p_has_vcallees = pr->has_vcallees;
	p_has_no_vcallers = pr->has_no_vcallers;
	p_no_of_returns = pr->no_of_returns;
	
	p_fixed_params = 0;		/* Updated in make_ident_tag_code */
	p_float_params = 0;		/* Updated in make_ident_tag_code */
	p_has_back_chain = p_leaf ? 0 : diagnose;
	p_args_and_link_size = p_leaf ? 0 : STACK_LINK_AREA_SIZE + p_maxargbytes;
	ASSERT(pr->frame_size>=0 && (pr->frame_size&63) == 0);
	ASSERT(pr->frame_size>=pr->maxargs);
	return;
}


void
generate_procedure_prologue()
{
	int r;
	baseoff stackpos;
	
	stackpos.base = R_SP;
	stackpos.offset = 0;
	
	/* Get LR for non leaf */
	if (!p_leaf)
	{
		mf_ins(i_mflr,R_0);
	}
	/* 
	 * Save floating point s-regs
	 */
	if (p_sfreg_first_save != FR_NO_REG)
	{
		for (r = p_sfreg_first_save; r <= FR_LAST; r++)
		{
			if (IS_FLT_SREG(r))
			{
				stackpos.offset -= 8;
				stf_ro_ins(i_stfd, r, stackpos);
			}
		}
		ASSERT(stackpos.offset >= -STACK_FLOAT_REG_DUMP_AREA_SIZE);
	}
	/*
	 * Save fixed point s-regs
	 */
	if (p_sreg_first_save != R_NO_REG)
	{
		if (p_sreg_first_save < R_28)
		{
			/* Use the stm instruction */
			stackpos.offset -= 4*(R_31+1-p_sreg_first_save);
			st_ro_ins(i_stm, p_sreg_first_save, stackpos);comment("save fixed point s-regs");
		}
		else
		{ 
			/* Less than or 4 stores so do individually */
			for (r=R_31;r>=p_sreg_first_save;r--)
			{ 
				stackpos.offset -= 4;
				st_ro_ins(i_st,r,stackpos);comment("save fixed point s-reg");
			}
		}
		ASSERT(stackpos.offset >= -STACK_REG_DUMP_AREA_SIZE);
	}
	/* Align to next 8 byte boundary */
	stackpos.offset= -ALIGNNEXT(-stackpos.offset,8);
	/*
	 * Make room for saved sp if we have one
	 */
	if (p_has_saved_sp)
	{
		stackpos.offset -= 8;
		p_saved_sp_offset = stackpos.offset;
	}
	/* 
	 * Initialise the top pointer if needed 
	 */
	if (p_has_tp)
	{
		baseoff a;
		
		/* This is where the backward pointing chain is held */
		a.base = R_SP;
		a.offset = 0;
		ld_ro_ins(i_l,a,R_TP);comment("set up TP");
	}
	
	/* 
	 * Initialize the frame pointer if needed
	 */
	if (p_has_fp)
	{
		mov_rr_ins(R_SP, R_FP);comment("set up FP");
	}
	
	
	/*
	 * Save the Link Register
	 */
	if (! p_leaf)
	{
		if (p_has_tp)
		{
			stackpos.base = R_TP;
		}
		else
		{
			stackpos.base = R_SP;
		}
		
		stackpos.offset = STACK_SAVED_LR;
		st_ro_ins(i_st, R_0, stackpos);comment("save LR");
	}
	
	/* 
	 * Decrease the stack pointer
	 */
	
	stackpos.base = R_SP;
	
	if (p_has_back_chain)
	{
		stackpos.offset = - p_frame_size;
		st_ro_ins(i_stu , R_SP , stackpos);comment("pull stack down with back chain");
	}
	else
	{
		if (p_frame_size !=0)
		{
			rir_ins(i_a, R_SP, -p_frame_size ,R_SP);
		}
	}
	/* Save sp on stack if necessary */
	if (p_has_saved_sp)
	{
		save_sp_on_stack();
	}
	
	return;
}


void
generate_procedure_epilogue()
{
	baseoff saved_lr;
	
	if (p_frame_size !=0)
	{
		if (p_has_fp)
		{
			/* Use frame pointer to collapse stack frame */
			mov_rr_ins(R_FP, R_SP);comment("collapse frame using FP");
		}
		else if (p_has_back_chain)
		{
			/* Use back chain to collapse stack frame */
			baseoff back_chain;
			back_chain.base=R_SP;
			back_chain.offset=0;
			ld_ro_ins(i_l, back_chain, R_SP);comment("collapse stack frame");
		}
		else
		{
			/* Use frame size to collapse stack frame */
			rir_ins(i_a, R_SP, p_frame_size , R_SP);
		}
	}
	/* At this point the stack pointer is collapsed to where the s-regs 
	 *     are stored */
	if (p_has_tp)
	{
		mov_rr_ins(R_TP,R_TEMP_TP);comment("copy TP to TEMP_TP");
		restore_sregs(R_SP,0);
		mov_rr_ins(R_TEMP_TP,R_SP);comment("collapse frame using TEMP_TP");
	}
	else
	{
		restore_sregs(R_SP,0);
	}
	/* At this point the stack pointer is in its return position */
	if (!p_leaf)
	{
		saved_lr.base = R_SP;
		saved_lr.offset = STACK_SAVED_LR;
		ld_ro_ins(i_l, saved_lr , R_TMP0);comment("restore LR");
		mt_ins(i_mtlr, R_TMP0);
	}	
	z_ins(i_br);
	return;
}
void
generate_untidy_procedure_epilogue()
{
	baseoff saved_lr;
	
	/* The stack pointer is not collapsed at all */
	if (p_has_tp && !p_leaf)/*We need R_TP later for the link */
	{
		mov_rr_ins(R_TP,R_TEMP_TP);comment("copy TP to TEMP_TP");
	}
	/* load up R_TEMP_FP with the value of where the s-regs are stored */
	if (p_has_fp)
	{
		mov_rr_ins(R_FP,R_TEMP_FP);comment("copy FP ro TEMP_FP");
		restore_sregs(R_TEMP_FP,0);
	}
	else if (p_has_back_chain)
	{
		baseoff back_chain;
		back_chain.base = R_SP;
		back_chain.offset = 0;
		ld_ro_ins(i_l,back_chain,R_TEMP_FP);comment(NIL);
		restore_sregs(R_TEMP_FP,0);
	}
	else
	{
		restore_sregs(R_SP,p_frame_size);
	}
	/* s-regs are restored */
	if (!p_leaf)
	{
		if (p_has_tp)
		{
			saved_lr.base = R_TEMP_TP;
			saved_lr.offset = STACK_SAVED_LR;
		}
		else if (p_has_fp)
		{
			saved_lr.base = R_TEMP_FP;
			saved_lr.base = STACK_SAVED_LR;
		}
		else
		{
			saved_lr.base = R_SP;
			saved_lr.offset = STACK_SAVED_LR + p_frame_size;
		}
		ld_ro_ins(i_l,saved_lr,R_TMP0);comment("restore LR");
		mt_ins(i_mtlr,R_TMP0);
	}
	z_ins(i_br);
	return;
}



void
save_sp_on_stack()
{
	baseoff saved_sp;
	
	/* Saves the value of the stack pointer on stack */
	ASSERT(p_has_saved_sp);
	ASSERT(p_has_fp);
	saved_sp.base = R_FP;
	saved_sp.offset = p_saved_sp_offset;
	st_ro_ins(i_st,R_SP,saved_sp);comment("save sp on stack");
	return;
}
void
get_sp_from_stack()
{
	baseoff saved_sp;
	
	/* Restores the stack pointer from the stack */
	ASSERT(p_has_saved_sp);
	ASSERT(p_has_fp);
	saved_sp.base = R_FP;
	saved_sp.offset = p_saved_sp_offset;
	ld_ro_ins(i_l,saved_sp,R_SP);comment("get SP of stack");
	return;
}
void
save_back_chain_using_frame_pointer()
{
	/* saves back chain using frame pointer */
	baseoff back_chain;
	back_chain.base = R_SP;
	back_chain.offset = 0;
	ASSERT(p_has_fp);
	st_ro_ins(i_st,R_FP,back_chain);comment("save back chain");
	return;
}

void
restore_sregs(int start_base, int start_offset)
{
	baseoff stackpos;
	int r;
	
	ASSERT(IS_TREG(start_base) || start_base == R_SP);
	ASSERT(start_base!=R_TMP0);
	stackpos.base = start_base;
	stackpos.offset = start_offset;
	COMMENT2("restore s-regs using %d offset %d bytes",start_base,start_offset);
	
	
	if (p_sfreg_first_save != FR_NO_REG)
	{
		for (r = p_sfreg_first_save; r <= FR_LAST; r++)
		{
			if (IS_FLT_SREG(r))
			{
				stackpos.offset -= 8;
				ldf_ro_ins(i_lfd, stackpos, r);
			}
		}
	}
	
	/* 
	 * Restore fixed point s-regs 
	 */
	if (p_sreg_first_save != R_NO_REG)
	{
		if (p_sreg_first_save < R_28)
		{
			/* Use lm instruction */
			stackpos.offset -= 4*(R_31+1-p_sreg_first_save);
			ld_ro_ins(i_lm, stackpos, p_sreg_first_save);comment("restore fixed s-regs");
		}
		else
		{
			/* Less than or 4 loads so do individually */ 
			for (r=R_31;r>=p_sreg_first_save;r--)
			{
				stackpos.offset -=4;
				ld_ro_ins(i_l,stackpos,r);comment("restore fixed s-reg");
			}
		}
	}
	return;
}
void
restore_link_register()
{
	/* this function is only used by tail_call */
	baseoff saved_lr;
	COMMENT("restore link register");
	if (!p_leaf)
	{
		if (p_has_tp)
		{
			saved_lr.base = R_TP;
			saved_lr.offset = STACK_SAVED_LR;
		}
		else if (p_has_fp)
		{
			saved_lr.base = R_FP;
			saved_lr.offset = STACK_SAVED_LR;
		}
		else 
		{
			fail("Shouldn't be calling this function without R_TP or R_FP");
		}
		ld_ro_ins(i_l,saved_lr,R_TMP0);comment("restore LR");
		mt_ins(i_mtlr,R_TMP0);
	}
}

