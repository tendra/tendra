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
 * Revision 1.4  1997/06/02  08:28:44  pwe
 * correction re NEWDIAGS
 *
 * Revision 1.3  1997/02/19  12:53:41  pwe
 * NEWDIAGS for debugging optimised code
 *
 * Revision 1.2  1995/09/28  12:39:37  pwe
 * dwarf.h via import, and type changes for tcc checks
 *
 * Revision 1.1.1.1  1995/08/14  14:30:21  pwe
 * transferred from DJCH
 *
 **********************************************************************/

/* LOG 4 July 1994 added dwarf_types.h to unify with sparc version */
/* LOG 6/9/93 changes for sparc/ICL port of SVR4.2 djch
 * comment char is not #... introduced COMMENT_2 macros */

/* LOG 25/11/93 removed redundant expr_buf djch */

#include "config.h"
#include "common_types.h"
#include "readglob.h"
#include "table_fns.h"
#include "basicread.h"
#include "sortmacs.h"

/* machine dep headers */
#include "out.h"
#include "expmacs.h"

#include "tags.h"

#include "main_reads.h"
#include "check.h"
#include "main_reads.h"

#include "dwarf_types.h"
#include "dwarf_type.h"
#include "dwarf_out.h"
#include "diag_fns.h"
#include "dwarf_loc.h"
#include "dwarf_queue.h"
#include "dwarf_mc.h"
#include "mark_scope.h"
#include "cross_config.h"

#ifdef NEWDIAGS
#include "tags.h"
#endif

#ifndef CROSS_INCLUDE
#include <dwarf.h>
#else
#include CROSS_INCLUDE/dwarf.h>
#endif

int continue_decs;

static long lex_blk_stk_ptr = -1;

static dwarf_label lex_blk_stk[100];

#define PUSH_LEX_BLK (&lex_blk_stk[++lex_blk_stk_ptr])
#define POP_LEX_BLK  (&lex_blk_stk[lex_blk_stk_ptr--])
#define TOS_LEX_BLK  (&lex_blk_stk[lex_blk_stk_ptr])
#define CHK_LEX_STK  if (lex_blk_stk_ptr < -1) failer("lex stk underflow")

static void
out_dwarf_start_scope(dwarf_label *l)
{
	char expr_buf[100];
	
	if (lex_blk_stk_ptr == -1)
		return;
	
	sprintf(expr_buf,"%s - %s",LAB2CHAR(l->beg), LAB2CHAR(TOS_LEX_BLK->beg));
	OUT_DWARF_ATTR(AT_start_scope);
	dwarf4(expr_buf);
}

#ifdef NEWDIAGS

static void
comment_end_scope(diag_info * d)
{
	char expr_buf[100];
	sprintf(expr_buf,COMMENT_2("\t","\tEND diag_info key %d"),d->key);
	outs(expr_buf);
	outs("\n");	/* avoid 80x86 outnl which has side effect */
}

void
code_diag_info(diag_info * d, int proc_no,
			   void (*mcode)(void *), void * args)
{
	if (d == nildiag) {
		(*mcode)(args);
		return;
	}
	switch (d->key) {
    case DIAG_INFO_SCOPE: {
		next_dwarf_lab(PUSH_LEX_BLK);
		OUT_DWARF_BEG(TOS_LEX_BLK);
		cont_sib_chain(TAG_lexical_block);
		OUT_DWARF_ATTR(AT_low_pc);
		dwarf4(LAB2CHAR(TOS_LEX_BLK->beg));
		OUT_DWARF_ATTR(AT_high_pc);
		dwarf4(LAB2CHAR(TOS_LEX_BLK->end));
		leave_dwarf_blk();
		make_next_new_chain();
		code_diag_info (d->more, proc_no, mcode, args);
		OUT_DWARF_END(POP_LEX_BLK);
		CHK_LEX_STK;
		end_sib_chain();
		return;
    }
    case DIAG_INFO_SOURCE: {
		out_dwarf_sourcemark(&(d->data.source.beg));
		code_diag_info (d->more, proc_no, mcode, args);
		comment_end_scope (d);
		return;
    }
    case DIAG_INFO_ID: {
		exp x = d->data.id_scope.access;
		dwarf_label tlab;
		next_dwarf_lab(&tlab);
		OUT_DWARF_BEG(&tlab);	/* always needed for start_scope */
		while (1) {
			if (name(x) != hold_tag)
			{
				failer("access should be in hold");
				break;
			};
			x = son(x);
			if (name(x) == cont_tag && name(son(x)) == name_tag && isvar(son(son(x))))
				x = son(x);
			if ((name(x) != name_tag || isdiscarded(x))
				&& name(x) != val_tag && name(x) != null_tag)
			{
				break;	/* should do better ! */
			};
			
			if ((base_type(d->data.id_scope.typ))->key == DIAG_TYPE_INITED)
			{
				fprintf(stderr,"ERROR: %s has no diagtype... omitting\n",
						TDFSTRING2CHAR(d->data.id_scope.nme));
				break;
			}
			if (name(x) == name_tag && isglob(son(x)))
			{
				if (brog(son(x))->dec_u.dec_val.extnamed)
					break;
				else			/* static; goes out as local */
				{
					cont_sib_chain(TAG_local_variable);
					out_dwarf_start_scope(&tlab); /* only for local vars */
				}
			}
			else
				if (name(x) == name_tag && isparam(son(x)))
					cont_sib_chain(TAG_formal_parameter);
				else
				{
					cont_sib_chain(TAG_local_variable);
					out_dwarf_start_scope(&tlab);	/* only for local vars */
				};
			
			out_dwarf_name_attr(TDFSTRING2CHAR(d->data.id_scope.nme));
			out_dwarf_type_attr(d->data.id_scope.typ);
			if (!out_dwarf_loc_attr(x,proc_no))
				fprintf(stderr,"Unable to generate location info for variable '%s'\n",
						TDFSTRING2CHAR(d->data.id_scope.nme));
			leave_dwarf_blk();
			dump_type_q();
			break;
		}
		code_diag_info (d->more, proc_no, mcode, args);
		comment_end_scope (d);
		return;
    }
    case DIAG_INFO_TYPE: {
		dwarf_label tlab;
		next_dwarf_lab(&tlab);
		OUT_DWARF_BEG(&tlab);	/* always needed for start_scope */
		cont_sib_chain(TAG_typedef);
		out_dwarf_start_scope(&tlab);
		out_dwarf_name_attr(TDFSTRING2CHAR(d->data.type_scope.nme));
		out_dwarf_type_attr(d->data.type_scope.typ);
		leave_dwarf_blk();
		code_diag_info (d->more, proc_no, mcode, args);
		comment_end_scope (d);
		return;
    }
		failer("Illegal key in output_diag");
		fprintf(stderr,"key was %d\n",d->key);
		code_diag_info (d->more, proc_no, mcode, args);
	}
}

#else

void
output_diag(diag_info * d, int proc_no, exp e)
{
	if (d->key == DIAG_INFO_SOURCE)
	{
		out_dwarf_sourcemark(&(d->data.source.beg));
		return;
	}
	{
		dwarf_label tlab;
		
		mark_scope(e);
		
		if (props(e) & 0x80)
		{
			next_dwarf_lab(PUSH_LEX_BLK);
			OUT_DWARF_BEG(TOS_LEX_BLK);
			cont_sib_chain(TAG_lexical_block);
			OUT_DWARF_ATTR(AT_low_pc);
			dwarf4(LAB2CHAR(TOS_LEX_BLK->beg));
			OUT_DWARF_ATTR(AT_high_pc);
			dwarf4(LAB2CHAR(TOS_LEX_BLK->end));
			leave_dwarf_blk();
			make_next_new_chain();
		};
		
		next_dwarf_lab(&tlab);
		OUT_DWARF_BEG(&tlab);	/* always needed for start_scope */
		switch (d->key)
		{
		case DIAG_INFO_ID:
		{
			exp x = d->data.id_scope.access;
			
			if (name(x) != name_tag)
			{
				failer("diagnosing non-identifier");
				return;
			};
			
			if ((base_type(d->data.id_scope.typ))->key == DIAG_TYPE_INITED)
			{
				fprintf(stderr,"ERROR: %s %s has no diagtype... omitting\n",
						isparam(son(x)) ? "Formal parameter" : "Local variable",
						TDFSTRING2CHAR(d->data.id_scope.nme));
				break;
			}
			if (isglob(son(x)))
			{
				if (brog(son(x))->dec_u.dec_val.extnamed)
					break;
				else			/* static; goes out as local */
				{
					cont_sib_chain(TAG_local_variable);
					out_dwarf_start_scope(&tlab); /* only for local vars */
				}
			}
			else
				if (isparam(son(x)))
					cont_sib_chain(TAG_formal_parameter);
				else
				{
					cont_sib_chain(TAG_local_variable);
					out_dwarf_start_scope(&tlab);	/* only for local vars */
				};
			
			out_dwarf_name_attr(TDFSTRING2CHAR(d->data.id_scope.nme));
			out_dwarf_type_attr(d->data.id_scope.typ);
			if (!out_dwarf_loc_attr(x,proc_no))
				fprintf(stderr,"Unable to generate location info for variable '%s'\n",
						TDFSTRING2CHAR(d->data.id_scope.nme));
			leave_dwarf_blk();
			dump_type_q();
		}
		break;
		case DIAG_INFO_TYPE:
			cont_sib_chain(TAG_typedef);
			out_dwarf_start_scope(&tlab);
			out_dwarf_name_attr(TDFSTRING2CHAR(d->data.type_scope.nme));
			out_dwarf_type_attr(d->data.type_scope.typ);
			leave_dwarf_blk();
			break;
		case DIAG_INFO_TAG:
			fprintf(stderr,"diag_info_tag named %s\n",
					TDFSTRING2CHAR(d->data.tag_scope.nme));
			if (!strcmp(TDFSTRING2CHAR(d->data.tag_scope.nme),
						TDFSTRING2CHAR(d->data.tag_scope.typ->data.t_struct.nme)))
			{
				fprintf(stderr,"diag type gives name as %s\n",
						TDFSTRING2CHAR(d->data.tag_scope.typ->data.t_struct.nme));
				failer("different names in output_diag");
			}
			out_dwarf_user_type(d->data.tag_scope.typ);
			break;
		default:
			failer("Illegal key in output_diag");
			fprintf(stderr,"key was %d\n",d->key);
		}
	}
}

void
output_end_scope(diag_info * d, exp e)
{
	char expr_buf[100];
	
	sprintf(expr_buf,COMMENT_2("\t","\tEND diag_info key %d"),d->key);
	outs(expr_buf);
	outnl();
	
	if (d -> key != DIAG_INFO_SOURCE && props(e) & 0x80)
	{
		OUT_DWARF_END(POP_LEX_BLK);
		CHK_LEX_STK;
		end_sib_chain();
	}
}

#endif


