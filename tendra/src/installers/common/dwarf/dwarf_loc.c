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
 * Revision 1.2  1998/02/04  10:43:37  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/02/19  12:53:44  pwe
 * NEWDIAGS for debugging optimised code
 *
 * Revision 1.2  1995/09/28  12:39:42  pwe
 * dwarf.h via import, and type changes for tcc checks
 *
 * Revision 1.1.1.1  1995/08/14  14:30:21  pwe
 * transferred from DJCH
 *
 **********************************************************************/

/* LOG 6/9/93 changes for sparc/ICL port of SVR4.2 djch
 *   new stuff for sparc registers  added by ra 8/9/93 */

/* LOG 27/9/93 removing the blocks aroung locations djch */
/* LOG 26/11/93 proc_no long -> int to shut up tdfc djch */

#include "config.h"
#include "common_types.h"
#include "installtypes.h"

/* machine dependent */
#include "machine.h"
#include "codermacs.h"

#include "tags.h"

/* machine dependent */
#include "out.h"

#include "shapemacs.h"

/* machine dependent */
#include "expmacs.h"

#include "basicread.h"

#include "dwarf_types.h"
#include "dwarf_out.h"
#include "dwarf_queue.h"
#include "dwarf_type.h"

#include "dwarf_loc.h"
#include "cross_config.h"

#ifndef CROSS_INCLUDE
#include <dwarf.h>
#else
#include CROSS_INCLUDE/dwarf.h>
#endif

void
out_dwarf_const4(exp x)
{
	if (name(x) != val_tag && name(x) != null_tag)
	{
		failer("non const exp in out_dwarf_const4");
		return;
	}
	dwarf4n(no(x));
}

void
out_dwarf_const_by8(exp x)
{
	if (name(x) != val_tag)
	{
		failer("non const exp in out_dwarf_const_by8");
		return;
	}
	dwarf4n((no(x)/8));
}

void
out_dwarf_member_loc_attr(exp e)
{
	int o;
	
	OUT_DWARF_ATTR(AT_location);
	if (name(e) != val_tag)
		failer("out_mem_loc_attr");
	
#ifdef LOCS_IN_BLKS
	new_dwarf_blk2();
#else
	OUT_DWARF_LOC_BLK(6);
#endif
	o = no(e)/8;
	dwarf1(OP_CONST);
	dwarf4n(o);
	dwarf1(OP_ADD);
#ifdef LOCS_IN_BLKS
	leave_dwarf_blk2();
#endif
}

/* given the bit offset to base of anon object */
void
out_dwarf_bit_member_loc_attr(int u)
{
	OUT_DWARF_ATTR(AT_location);
	
#ifdef LOCS_IN_BLKS
	new_dwarf_blk2();
#else
	OUT_DWARF_LOC_BLK(6);
#endif
	dwarf1(OP_CONST);
	dwarf4n(u/8);
	dwarf1(OP_ADD);
#ifdef LOCS_IN_BLKS
	leave_dwarf_blk2();
#endif
}

#if (is80x86)
static int
ok_reg_no(int x)
{
	switch (x)
	{
	case 1:
	case 2:
	case 4:
	case 8:
	case 16:
	case 0x20:
	case 0x40:
		return 1;
	default:
		return 0;
	}
}

static char
*dwarf_reg_str(int x)
{
	switch (x)
	{
	case 1:
		return ("0\t#\teax");
	case 2:
		return ("2\t#\tedx");
	case 4:
		return ("1\t#\tecx");
	case 8:
		return ("3\t#\tebx");	/* 4 is esp */
	case 0x10:
		return ("7\t#\tedi");
	case 0x20:
		return ("6\t#\tesi");
	case 0x40:
		return ("5\t#\tebp");
		/* 8 eip 9 eflags 10 fpsw 11 fpcw
		 *				 12 fpip 13 fpdp 14 st0....*/
	default:
		failer("Illegal reg no in dwarf_reg_str");
		exit(EXIT_FAILURE);
	}
}

#define DWARF_FP "5\t# ebp"

#else
#if (issparc)

static char
*dwarf_reg_str(long x)
{
    int i;
    for (i = 0 ; i < 32 ; i++) {
		if (x & 1) {
			static char buff [10];
			sprintf (buff, "%d", i);
		}
		x >>= 1;
    }
    failer ("Illegal register number in dwarf_reg_str");
    return ("???");
}

#else
error need internal to dwarf register number routines
#endif
#endif

int
out_dwarf_loc_attr(exp t, int proc_no)
{
	int rval = 1;
	
	if (name(t) != name_tag) {
		OUT_DWARF_ATTR(AT_const_value);
		out_dwarf_const4(t);
		return rval;
	}
	
#ifdef NEWDIAGS
	if (isdiscarded(t))
		return rval;	/* no location */
#endif
	
	
	OUT_DWARF_ATTR(AT_location);
#ifdef LOCS_IN_BLKS
	new_dwarf_blk2();
#endif
	{
		exp s = son(t);
		
		if (isglob(s))
		{
#ifndef LOCS_IN_BLKS
			OUT_DWARF_LOC_BLK(5);
#endif
			dwarf1(OP_ADDR);
			dwarf4(brog(s) -> dec_u.dec_val.dec_id);
		}
		else
#if (is80x86)
		{
			int p = ptno(s);
			switch (p)
			{
			case local_pl:
			{
				char expr_buf[100];
				
				sprintf(expr_buf,"%d - %sdisp%d # local var",(no(s)+no(t))/8,
						local_prefix,proc_no);
#ifndef LOCS_IN_BLKS
				OUT_DWARF_LOC_BLK(11);
#endif
				dwarf1(OP_CONST);
				dwarf4(expr_buf);
			}
			dwarf1(OP_BASEREG);
			dwarf4(DWARF_FP);
			dwarf1(OP_ADD);
			break;
			case par_pl:
#ifndef LOCS_IN_BLKS
				OUT_DWARF_LOC_BLK(11);
#endif
				dwarf1(OP_CONST);
				dwarf4n((no(s)+no(t))/8 + 8);
				dwarf1(OP_BASEREG);
				dwarf4(DWARF_FP);
				dwarf1(OP_ADD);
				break;
			case reg_pl:
				if (!ok_reg_no(no(s)))	/* fails for fp regs, so put out no atoms */
					rval = 0;
				else
				{
#ifndef LOCS_IN_BLKS
					OUT_DWARF_LOC_BLK(5);
#endif
					dwarf1(OP_REG);
					dwarf4(dwarf_reg_str(no(s)));
				}
				break;
			default:
				failer("illegal ptno in out_loc_attr");
				exit(EXIT_FAILURE);
			}
		}
#else
#if (issparc)
		{
			if (props (s) & defer_bit) {
				failer ("Deferred expression in out_loc_attr");
				rval = 0;
			} else if (props (s) & inreg_bits) {
#ifndef LOCS_IN_BLKS
				OUT_DWARF_LOC_BLK(5);
#endif
				dwarf1 (OP_REG);
				dwarf4n (no (s));
			} else if (props (s) & infreg_bits) {
				failer ("Floating register expression in out_loc_attr");
				rval = 0;
			} else {
				baseoff b;
				b = boff (s);
#ifndef LOCS_IN_BLKS
				OUT_DWARF_LOC_BLK(11);
#endif
				dwarf1 (OP_CONST);
				dwarf4n ((int) b.offset);
				dwarf1 (OP_BASEREG);
				dwarf4n ((int) b.base);
				dwarf1 (OP_ADD);
			}
		}
#else
		error need machine specific non-global location description code
#endif
#endif
			}
#ifdef LOCS_IN_BLKS
	leave_dwarf_blk2();
#endif
	return rval;
}

