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
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.8  1998/01/09  09:30:07  pwe
 * prep restructure
 *
 * Revision 1.7  1997/10/28  10:12:38  pwe
 * local location support
 *
 * Revision 1.6  1997/10/23  09:21:26  pwe
 * ANDF-DE V1.7 and extra diags
 *
 * Revision 1.5  1997/08/23  13:27:24  pwe
 * initial ANDF-DE
 *
 * Revision 1.4  1997/04/02  12:55:05  currie
 * includes before ifdef
 *
 *Revision 1.3  1997/03/20 17:04:53  currie
 *Dwarf2 diags
 *
 *Revision 1.2  1997/02/18 12:55:52  currie
 *NEW DIAG STRUCTURE

 * Revision 1.1  1995/04/06  10:42:55  currie
 * Initial revision
 *
 ***********************************************************************/


#include "config.h"
#include "common_types.h"
#include "expmacs.h"
#include "tags.h"
#include "xalloc.h"
#include "externs.h"
#include "dg_aux.h"
#include "mark_scope.h"


#ifdef NEWDIAGS

int doing_mark_scope = 0;

void
mark_scope(exp e)
{
	/* called by read_diag_id_scope; dgf(e) holds DIAG_INFO_ID */
	dg_info d = dgf(e);
	dg_info * ptr;
	exp id;
	if (!d || d->key != DGA_NAME || d->data.i_nam.dnam->key != DGN_OBJECT)
		return;
	id = son(d->data.i_nam.dnam->data.n_obj.obtain_val);
	if (name(id) == cont_tag)
		id = son(id);
	if (name(id) != name_tag)
		return;
	id = son(id);
	if (isparam(id))
		return;
	ptr = &(d->more);
	d = nildiag;
	while (*ptr && (*ptr)->key != DGA_SCOPE)
		ptr = &((*ptr)->more);
	if (!*ptr && name(e) == seq_tag && name(son(son(e))) == ass_tag
		&& last(son(son(e))) && name(bro(son(e))) != ident_tag) {
		ptr = &dgf(bro(son(e)));
		while (*ptr && (*ptr)->key != DGA_SCOPE)
			ptr = &((*ptr)->more);
	}
	if (*ptr) {
		d = *ptr;
		*ptr = d->more;
	}
	else {
		d = f_lexical_block_dg (no_dg_idname_option, no_dg_sourcepos_option);
		d->data.i_scope.begin_st = (long)(-1);
		doing_mark_scope = 1;
	}
	/* if (isglob(id)) */ {
		d->more = dgf(e);
		dgf(e) = d;
	}
#if 0
	else {
		exp def = son(id);
		if (dgf(def) && dgf(def)->key == DGA_SRC)
			dgf(e)->data.i_nam.dnam->whence = dgf(def)->data.i_src.startpos;
		d->more = dgf(id);
		dgf(id) = d;
	}
#endif
	return;
}

void
mark_scope2(exp e)
{
	/* called by read_diag_type_scope; dgf(e) holds DIAG_INFO_ID */
	dg_info d = dgf(e);
	dg_info * ptr;
	if (!d || d->key != DGA_NAME || d->data.i_nam.dnam->key != DGN_TYPE)
		return;
	ptr = &(d->more);
	d = nildiag;
	while (*ptr && (*ptr)->key != DGA_SCOPE)
		ptr = &((*ptr)->more);
	if (*ptr) {
		d = *ptr;
		*ptr = d->more;
	}
	else {
		d = f_lexical_block_dg (no_dg_idname_option, no_dg_sourcepos_option);
		d->data.i_scope.begin_st = (long)(-1);
		doing_mark_scope = 1;
	}
	d->more = dgf(e);
	dgf(e) = d;
	return;
}

void
correct_mark_scope(exp e)
{
	dg_info d = nildiag;
	dg_info * ptr = &(dgf(bro(son(e))));
	while (*ptr && (*ptr)->key != DGA_SCOPE)
		ptr = &((*ptr)->more);
	if (*ptr) {
		d = *ptr;
		*ptr = d->more;
	}
	if (d) {
		d->more = dgf(e);
		dgf(e) = d;
	}
	return;
}


#else


/* PROCEDURES */

static exp
previous_scope(exp e)
{
	if (!last(e) || bro(e) == nilexp)
		return nilexp;
	
	if (name(bro(e)) == diagnose_tag && (props(bro(e)) & 0x7) == 1)
		return previous_scope(bro(e));
	
	if (name(bro(e)) == diagnose_tag)
		return bro(e);
	
	if (name(bro(e)) == ident_tag && last(bro(e)))
	{
		if (bro(bro(e)) == nilexp)
			return nilexp;
		
		if (name(bro(bro(e))) == diagnose_tag &&
			(props(bro(bro(e))) & 0x7) == 1)
			return previous_scope(bro(bro(e)));
		
		if (name(bro(bro(e))) == diagnose_tag)
			return bro(bro(e));
		
		return nilexp;
	};
	
	return nilexp;
}


static int
param_scope(exp e)
{
	diag_info * d = dno(e);
	if (d -> key == DIAG_INFO_ID)
		return isparam(son(d -> data.id_scope.access));
	return 0;
}

static int
needs_hiding(exp a, exp b)
{
	diag_info * da = dno(a);
	diag_info * db = dno(b);
	
	if (da -> key != db -> key)
		return 0;
	
	switch (da -> key)
    {
	case DIAG_INFO_ID:
		return !strcmp(da -> data.id_scope.nme.ints.chars,
					   db -> data.id_scope.nme.ints.chars);
	case DIAG_INFO_TYPE:
		return !strcmp(da -> data.type_scope.nme.ints.chars,
					   db -> data.type_scope.nme.ints.chars);
	case DIAG_INFO_TAG:
		return !strcmp(da -> data.tag_scope.nme.ints.chars,
					   db -> data.tag_scope.nme.ints.chars);
	default: return 0;
    };
}

void
mark_scope(exp e)
{
	exp scope = e;
	
	if (param_scope(e))
		return;
	
	while (1)
	{
		scope = previous_scope(scope);
		
		if (scope == nilexp || param_scope(scope) ||
			needs_hiding(e, scope))
		{
			props(e) = (prop)(props(e) | 0x80);
			return;
		};
		
		if (props(scope) & 0x80)
			return;
		
	};
}

#endif
