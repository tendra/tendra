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
 *Revision 1.2  2002/11/21 22:31:03  nonce
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
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1997/08/23  13:24:07  pwe
 * no invert order, and NEWDIAGS inlining
 *
 *Revision 1.3  1997/02/18 12:56:27  currie
 *NEW DIAG STRUCTURE

 * Revision 1.2  1995/08/02  13:17:59  currie
 * Various bugs reported
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
 ***********************************************************************/

/* normalised_inlining chooses the order in which inlining is to be
 *   done.
 */

#include "config.h"
#include "common_types.h"
#include "installglob.h"
#include "exp.h"
#include "expmacs.h"
#include "tags.h"
#include "check.h"
#include "flags.h"
#include "check_id.h"
#include "const.h"
#include "foralls.h"
#include "shapemacs.h"
#include "glopt.h"
#include "inline.h"
#include "xalloc.h"
#ifdef NEWDIAGS
#include "dg_aux.h"
#endif
#include "inl_norm.h"


int print_inlines = 0;

/* Procedures */

/*********************************************************************
 *  test a declaration to see that the identifier is only used as an
 *  applied procedure.
 *********************************************************************/


int
apply_only(exp e)
{
	exp t = pt (e);
	int ao = 1;
	exp f;
	while (ao && t != nilexp) {
#ifdef NEWDIAGS
		if (isdiaginfo(t))
			t = pt (t);
		else {
			f = father(t);
			if (name (f) == apply_tag && son(f) == t)
				t = pt (t);
			else
				ao = 0;
		};
#else
		f = father(t);
		if (name (f) == apply_tag && son(f) == t)
			t = pt (t);
		else
			ao = 0;
#endif
	};
	return (ao);
}


void
normalised_inlining()
{
	int proc_count = 0;
	dec * my_def;
	dec ** to_dec;
	exp def;
	int i;
	int j;
	char * consider;
	int * order;
	char * uses;
	int changed;
	int low;
	int high;
	int no_inlined =0;
	
	if (!do_inlining)
		return;
	
	/* count the defined procedures */
	
	my_def = top_def;
	while (my_def != (dec *) 0) {
		exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
		
		def = son(crt_exp);
		if (def != nilexp && !isvar (crt_exp) && name (def) == proc_tag &&
			!isrecursive(def) && apply_only (crt_exp) && !proc_has_setjmp(def) &&
			!proc_uses_crt_env(def) &&
			!proc_has_alloca(def) &&
			!proc_has_lv(def)) {
			proc_count++;
		}
		my_def = my_def -> def_next;
	}
	
	/* allocate
	 *     a matrix, uses, to hold uses[i, j] - i calls j
	 *     a vector, to_dec, to hold dec* (number -> dec)
	 *     a vector, consider, 1 if still considering.
	 *     a vector, order, of the procedure numbers (+1) ordered
	 */
	
	uses = (char*)xcalloc(proc_count * proc_count, sizeof(char));
	to_dec = (dec**)xcalloc(proc_count, sizeof(dec*));
	consider = (char*)xcalloc(proc_count, sizeof(char));
    /* assumes calloc clears consider */
	order = (int*)xcalloc(proc_count, sizeof(int));
    /* assumes calloc clears order */
	
	
	/* form the to_dec vector and set index in each proc dec.
	 *     set consider vector */
	
	my_def = top_def;
	i = 0;
	while (my_def != (dec *) 0) {
		exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
		
		def = son(crt_exp);
		if (def != nilexp && !isvar (crt_exp) && name (def) == proc_tag &&
			!isrecursive(def) && apply_only (crt_exp) && !proc_has_setjmp(def) &&
			!proc_uses_crt_env(def) &&
			!proc_has_alloca(def) &&
			!proc_has_lv(def)) {
			to_dec[i] = my_def;
			my_def -> dec_u.dec_val.index = i;
			consider[i] = 1;
			i++;
		}
		my_def = my_def -> def_next;
	}
	
	/* form uses matrix: uses[i, j] implies i calls j */
	
	for (i = 0; i < proc_count; i++) {
		exp crt_exp = to_dec[i] -> dec_u.dec_val.dec_exp;
		
		if (no(crt_exp) == 0 || son(crt_exp) == nilexp) {
			consider[i] = 0;
		}
		else {
			exp t = pt(crt_exp);
			
			while (t != nilexp) {
				exp k = t;
#ifdef NEWDIAGS
				if (isdiaginfo(t)) {
					t = pt (t);
					continue;
				}
#endif
				while (k != nilexp && name(k) != hold_tag && name(k) != 102
					   && name(k) != proc_tag && name(k) != general_proc_tag)
					k = bro(k);
				if (k != nilexp && name(k) == proc_tag) {
					int up = brog(bro(k)) -> dec_u.dec_val.index;
					if (up >=0 && up< proc_count) {
						uses[proc_count *up + i] = 1;
					}
				}
				t = pt(t);
			}
		}
	}
	
	/* form the order list from uses */
	
	low = 0;
	high = proc_count-1;
	changed = 1;
	while (changed) {
		changed = 0;
		
		for (i = 0; i < proc_count; i++) {
			if (consider[i]) {
				int good = 1;
				for (j = 0; good && j < proc_count; j++) {
					if (consider[j] && uses[i*proc_count+j] == 1)
						good = 0;
				}
				if (good) {
					consider[i] = 0;
					order[low++] = i+1;
					changed = 1;
				}
			}
		}
		
		for (i = 0; i < proc_count; i++) {
			if (consider[i]) {
				int good = 1;
				for (j = 0; good && j < proc_count; j++) {
					if (consider[j] && uses[j*proc_count+i] == 1)
						good = 0;
				}
				if (good) {
					consider[i] = 0;
					order[high--] = i+1;
					changed = 1;
				}
			}
		}
	}
	
	/* permit inlining of static recursive functions */
	
	for (i = 0; i < proc_count; i++) {
		if (consider[i]) {
			order[low++] = i+1;
		}
	}
	
	/* try to inline in given order */
	
	for (i = proc_count-1; i >= 0; i--) {
		if (order[i] > 0) {
			exp crt_exp;
			exp t;
			exp k;
			int total_uses;
			int crt_uses;
			int this_changed = 1;
			my_def = to_dec[order[i] - 1];
			crt_exp = my_def -> dec_u.dec_val.dec_exp;
			def = son(crt_exp);
			total_uses = no(crt_exp);
#ifdef NEWDIAGS
			if (diagnose)
				start_diag_inlining (def, my_def->dec_u.dec_val.diag_info);
#endif
			
			while (this_changed) {
				this_changed = 0;
				t = pt(crt_exp);
				crt_uses = no(crt_exp);
				while (t!=nilexp) {
					exp nextt = pt(t);
					exp dad;
#ifdef NEWDIAGS
					if (isdiaginfo(t)) {
						t = pt (t);
						continue;
					}
#endif
					dad = father(t);
					if (istoinline(dad)) {
						inline_exp(dad);
						
						k = t;
						while (k != nilexp && name(k) != hold_tag && name(k) != proc_tag)
							k = bro(k);
						if (print_inlines)
							IGNORE fprintf(stderr, "%s inlined in %s\n",
										   my_def -> dec_u.dec_val.dec_id,
										   brog(bro(k)) -> dec_u.dec_val.dec_id);
						
						this_changed = 1;
						break;
					}
					else
						if (no_inlined > 10000) {
							break; /* pathological expansion in AVS */
						}
						else {
							int ch = inlinechoice(t, def, total_uses);
							if (ch == 0)
								break;
							if (ch == 2) {
								inline_exp(dad);
								no_inlined++;
								
								k = t;
								while (k != nilexp && name(k) != hold_tag && name(k) != proc_tag)
									k = bro(k);
								if (print_inlines)
									IGNORE fprintf(stderr, "%s inlined in %s\n",
												   my_def -> dec_u.dec_val.dec_id,
												   brog(bro(k)) -> dec_u.dec_val.dec_id);
								
								this_changed = 1;
								break;
							}
						};
					t = nextt;
				}
				if (crt_uses <= no(crt_exp))
					break;
			}
#ifdef NEWDIAGS
			if (diagnose)
				end_diag_inlining (def, my_def->dec_u.dec_val.diag_info);
#endif
		}
	}
	
	xfree((void*)to_dec);
	xfree((void*)uses);
	xfree((void*)consider);
	xfree((void*)order);
	
	return;
}
