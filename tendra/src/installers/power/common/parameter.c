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
 * Revision 1.2  1998/02/04  15:49:02  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:03:18  pwe
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
#include "mem_copy.h"
#include "xalloc.h"
#include "parameter.h"
bool suspected_varargs = 0;
int saved_varargs_register=0;
int saved_varargs_offset = 0;

typedef struct
{
	exp par;
	int dest;
	int copied;
} TREG;

static int spare_fixed;/* The spare t-reg used in case of looping copy i.e if 3-->4 and 4-->3
						*			  replace with 3-->spare_fixed 4-->3 spare_fixed-->4  */
static int spare_float;

static int copying_fixed;
static int copying_float;
bool remember;
long fixedfree;
long floatfree;


TREG fixed_array[13];
TREG float_array[14];

static void do_fixed_params(void);
static void do_float_params(void);
static void copy_fixed(int);
static void copy_float(int);
static void clear_fixed(void);
static void clear_float(void);
static void set_fixed(exp,int,int);
static void set_float(exp,int,int);
static int getspare(long);
void track_fixed(int,exp);
void track_float(int,exp);
static int end_param;

void
output_parameters(exp e)
{
	exp par;
	
	if (name(e)==general_proc_tag)
	{
		end_param = GENERAL_PROC_PARAM_REGS + R_FIRST_PARAM - 1;
	}
	else
	{
		end_param = PROC_PARAM_REGS + R_FIRST_PARAM - 1;
	}
	
	/* Outputs the code for the parameters */
	fixedfree = PROC_TREGS;
	floatfree = PROC_FLT_TREGS;
	clear_fixed();
	clear_float();
	
	par = son(e);
	
	for (;;)
	{
		int param_reg;
		exp init_exp;
		int param_size;
		int param_align;
		int param_offset;
		bool is_float;
		bool src_in_reg;
		bool dest_in_reg;
		baseoff stackpos;
		where dest;
		
		if ((!isparam(par)) ||
			(name(par)!=ident_tag) ||
			(name(son(par))==formal_callee_tag))
			break;
		
		init_exp = son(par);
		is_float = is_floating(name(sh(init_exp)));
		param_reg = props(init_exp);
		param_size = shape_size(sh(init_exp));
		param_align = shape_align(sh(init_exp));
		param_offset = no(init_exp)>>3;
		src_in_reg = param_reg !=0;
		dest_in_reg = (props(par) & inanyreg)!=0;
		
		
		if (src_in_reg==1)
		{
			if (is_float)
			{
				p_float_params++;
			}
			else
			{
				p_fixed_params++;
			}
		}
		
		stackpos=boff_location(ENCODE_FOR_BOFF(param_offset,INPUT_CALLER_PARAMETER));    
		
		
		clearvarargparam(par);
		
		if (dest_in_reg==0 
			&& !p_has_no_vcallers 
			&& isvis(par)
			&& props(init_exp)!=0 
			&& last_caller_param(par))
		{
			/* VARARGS */
			int last_size;
			int pr;
			baseoff v;
			v = stackpos;
			
			setvarargparam(par);
			
			if (param_size == 0)
			{
				/* void from <varargs.h> */
				param_size = 32;
				param_align = 32;
			}
			
			last_size = param_size;
			pr = R_FIRST_PARAM + ALIGNNEXT(no(init_exp) + last_size, 32) / 32;
			
			v.offset += ALIGNNEXT(last_size, 32) / 8;
			/* now word align to allow for non word aligned last param */
			v.offset &= ~3;
			suspected_varargs = 1;
			saved_varargs_offset = v.offset;
			saved_varargs_register = pr;
			while (pr <= end_param)
			{
				st_ro_ins(i_st, pr, v);comment("varargs save all param regs");
				pr++;
				v.offset += 4;
			}
		}    
		/* Set up dest */
		if (dest_in_reg==1)
		{
			setregalt(dest.answhere,no(par));
		}
		else
		{
			instore is;
			is.b = stackpos;
			is.adval = 1;
			setinsalt(dest.answhere,is);
		}
		dest.ashwhere.ashsize  = param_size;
		dest.ashwhere.ashalign = param_align;
		
		
		/* Work out how the parameter is passed and where it will live */
		if (src_in_reg==0 && dest_in_reg==1) 
		{
			/* STACK  --->  REGISTER */
			/* Use move for consistency */
			ans a;
			instore is;
			is.b = stackpos;
			is.adval = 0;
			setinsalt(a,is);
			move(a, dest, PROC_TREGS | PARAM_TREGS, is_signed(sh(init_exp)));
		}
		else if (src_in_reg==1 && dest_in_reg ==0)
		{
			/* REGISTER  --->  STACK */
			bool is_aggregate =IS_AGGREGATE(sh(init_exp));
			if (is_aggregate)
			{
				/* Whole or part of struct passed in param t-regs */
				int last_st_reg;
				int r;
				
				last_st_reg = param_reg + (ALIGNNEXT(param_size, 32)/32) - 1;
				if (last_st_reg > end_param)
				{
					last_st_reg = end_param;
				}
				for (r = param_reg; r <= last_st_reg; r++)
				{
					st_ro_ins(i_st, r, stackpos);comment("copy param struct onto stack");
					stackpos.offset += 4;
				}
				p_fixed_params +=(last_st_reg - param_reg);
			}
			else
			{
				ans a;
				freg fr;
				
				if (is_float)
				{
					fr.dble = is_double_precision((sh(init_exp)));
					fr.fr = param_reg;
					setfregalt(a,fr);
				}
				else
				{
					setregalt(a, param_reg);
				}
				move(a,dest,PROC_TREGS|PARAM_TREGS,0);
			}
		}
		else if (src_in_reg==1 && dest_in_reg==1)
		{
			/* REGISTER  --->  REGISTER */
			int dest_reg = no(par);
			ASSERT(dest_reg!=0);/* This is now set up in needscan*/
			if ((props(par) & inreg_bits)!=0)
			{
				if (IS_SREG(dest_reg))
				{
					/* FIXED REGISTER --> FIXED S-REG */
					mov_rr_ins(param_reg , dest_reg);comment("copy param into an s-reg");
					track_fixed(param_reg,par);
				}
				else
				{
					/* FIXED REGISTER --> FIXED T-REG */
					set_fixed(par,param_reg ,  dest_reg);
				}
			}
			else
			{
				if (IS_FLT_SREG(dest_reg))
				{
					/* FLOAT REGISTER --> FLOAT S-REG */
					rrf_ins(i_fmr,param_reg , dest_reg);
					track_float(param_reg,par);
				}
				else
				{
					/* FLOAT REGISTER --> FLOAT T-REG */
					set_float(par,param_reg , dest_reg);
				}
			}
		}
		else
		{
			/* LIVES IN PLACE ON STACK */
		}
		
		par = bro(son(par));
	}
	do_fixed_params();
	do_float_params();
	return;
}


static void
do_fixed_params()
{
	int r;
	
	spare_fixed = getspare(fixedfree);
	copying_fixed = spare_fixed;
	copy_fixed(spare_fixed);
	
	for (r=R_FIRST_PARAM;r<=end_param;r++)
	{
		remember = 0;
		copying_fixed = r;
		copy_fixed(r);
		if (remember==1)
		{
			mov_rr_ins(spare_fixed , copying_fixed);comment("move param to its new reg");
			track_fixed(spare_fixed , fixed_array[copying_fixed].par);
		}
	}
	return;
}  
static void
do_float_params()
{
	int r;
	
	spare_float = getspare(floatfree);
	copying_float = spare_float;
	copy_float(spare_float);
	
	for (r=FR_FIRST_PARAM;r<=FR_LAST_PARAM;r++)
	{
		remember = 0;
		copying_float = r;
		copy_float(r);
		if (remember==1)
		{
			rrf_ins(i_fmr,spare_float,copying_float);
			track_float(spare_float,float_array[copying_float].par);
		}
	}
	return;
} 
static void
copy_fixed(int reg)
{
	if (fixed_array[reg].copied==1)
	{
		return;
	}
	if (fixed_array[reg].dest==reg)
	{
		fixed_array[reg].copied=1;
		return;
	}
	if (fixed_array[reg].dest==copying_fixed)
	{
		/* We have gone round in a loop */
		remember = 1;
		mov_rr_ins(reg,spare_fixed);comment("copy param reg to new location");
		fixed_array[reg].copied=1;
		return;
	}
	copy_fixed(fixed_array[reg].dest);
	mov_rr_ins(reg,fixed_array[reg].dest);comment("copy param reg to new reg");
	track_fixed(reg,fixed_array[reg].par);
	fixed_array[reg].copied=1;
	return;
}
static void
copy_float(int reg)
{
	if (float_array[reg].copied==1)
	{
		return;
	}
	if (float_array[reg].dest==reg)
	{
		float_array[reg].copied=1;
		return;
	}
	if (float_array[reg].dest==copying_float)
	{
		/* We have gone round in a loop */
		remember = 1;
		rrf_ins(i_fmr,reg,spare_float);
		float_array[reg].copied=1;
		return;
	}
	copy_float(float_array[reg].dest);
	rrf_ins(i_fmr,reg,float_array[reg].dest);
	track_float(reg,float_array[reg].par);
	float_array[reg].copied=1;
	return;
} 



static void
clear_fixed()
{
	int r;
	for (r=0;r<=12;r++)
	{
		fixed_array[r].par = nilexp;
		fixed_array[r].dest = 0;
		fixed_array[r].copied = 1;
	}
	return;
}
static void
clear_float()
{
	int r;
	for (r=0;r<=13;r++)
	{
		float_array[r].par = nilexp;
		float_array[r].dest = 0;
		float_array[r].copied = 1;
	}
	return;
}

static void
set_fixed(exp p, int from, int to)
{
	ASSERT(IS_PARAM_REG(from));
	ASSERT(IS_TREG(to));
	ASSERT(to!=R_TMP0);
	fixed_array[from].par = p;
	fixed_array[from].dest = to;
	fixed_array[from].copied = 0;
	fixedfree |= RMASK(to);
}
static void
set_float(exp p, int from, int to)
{
	ASSERT(IS_FLT_PARAM_REG(from));
	ASSERT(IS_FLT_TREG(to));
	float_array[from].par = p;
	float_array[from].dest = to;
	float_array[from].copied = 0;
	floatfree |= RMASK(to);
}
static int
getspare(long s)
{
	int r;
	for (r=0;r<=31;r++)
	{
		if ((s & RMASK(r))==0)
		{
			return r;
		}
	}
	fail("getspare failed");
	return 100;
}

void
track_fixed(int reg, exp id)
{
	exp def = son(id);
	
	if (pt(id)!=nilexp && keep_eq_size(sh(def),sh(pt(id))))
	{
		if (isvar(id))
		{
			keepcont(pt(id),reg);
		} 
		else
		{
			keepreg(pt(id),reg);
		}
	}
	return;
}

void
track_float(int reg, exp id)
{
	return;
}
