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
 *Revision 1.1.1.1  1997/10/13 12:43:02  ma
 *First version.
 *
 *Revision 1.2  1997/03/20 12:53:13  ma
 *Removed warning.
 *
 *Revision 1.1.1.1  1997/03/14 07:50:22  ma
 *Imported from DRA
 
 * Revision 1.1.1.1  1996/09/20  10:57:01  john
 *
 * Revision 1.2  1996/07/05  14:33:46  john
 * Fix to diagnostics
 *
 * Revision 1.1  95/03/08  16:46:19  ra
 * Added missing files.
 *
 * Revision 1.1  93/02/22  17:17:20  17:17:20  ra (Robert Andrews)
 * Initial revision
 *
 *--------------------------------------------------------------------------
 */


#include "config.h"
#include "common_types.h"
#include "codex.h"
#include "diag_fns.h"
#include "diagglob.h"
#include "expmacs.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "mark_scope.h"
#include "output.h"
#include "xdb_types.h"
#include "xdb_basics.h"
#include "xdb_output.h"
#include "stab_types.h"


/*
 *    DIAGNOSTICS INITIALIZATION ROUTINE
 */

void
diag_prologue()
{
    init_diag ();
    return;
}


/*
 *    DIAGNOSTICS TERMINATION ROUTINE
 */

void
diag_epilogue()
{
    while (dnt_end ()) /* empty */;
    if (diag_format == DIAG_STAB) {
		mach_op *op = make_extern_data ("Letext", 0);
		area (ptext);
		make_stabs ("\"\"", 100, 0, op);
		make_external_label ("Letext");
    }
    output_all ();
    copy_diag ();
    return;
}


/*
 *    OUTPUT A DIAGNOSTICS SOURCE MARK
 */

static void
diag_mark(sourcemark *sm)
{
    char *nm = sm->file->file.ints.chars;
    long ln = sm->line_no.nat_val.small_nat;
    diag_source (nm, ln, 1);
    return;
}


/*
 *    DIAGNOSTICS FOR A LOCAL VARIABLE
 */

static void
diag_variable(diag_info *di, exp e)
{
    exp s = di->data.id_scope.access;
    diag_type t = di->data.id_scope.typ;
    char *nm = di->data.id_scope.nme.ints.chars;
    long p = (no (s) + no (son (s))) / 8;
    if (!isparam (son (s))) {
		diag_local_variable (t, nm, p);
    }
    return;
}


/*
 *    START OF A DIAGNOSTICS ITEM
 */

void
diag_start(diag_info *di, exp e)
{
    switch (di->key) {
		
	case DIAG_INFO_SOURCE : {
	    sourcemark *sm = &(di->data.source.beg);
	    diag_mark (sm);
	    break;
	}
		
	case DIAG_INFO_ID : {
	    mark_scope (e);
	    if (props (e) & 0x80) dnt_begin ();
	    if (diag_format != DIAG_XDB_NEW) diag_variable (di, e);
	    break;
	}
		
	default : {
	    break;
	}
    }
    return;
}


/*
 *    END OF A DIAGNOSTICS ITEM
 */

void
diag_end(diag_info *di, exp e)
{
    if (di->key == DIAG_INFO_ID) {
		if (diag_format == DIAG_XDB_NEW) diag_variable (di, e);
		if (props (e) & 0x80) dnt_end ();
    }
    return;
}


/*
 *    DIAGNOSTICS FOR THE START OF A PROCEDURE
 */

void
xdb_diag_proc_begin(diag_global *di, exp p,
					char *pname, long cname,
					int is_ext)
{
    char *nm = di->data.id.nme.ints.chars;
    diag_type t = di->data.id.new_type;
    sourcemark *sm = &(di->data.id.whence);
    diag_proc_main (t, p, nm, !is_local (pname), pname);
    diag_mark (sm);
    return;
}


/*
 *    DIAGNOSTICS FOR THE RETURN STATEMENT OF A PROCEDURE
 */

void
xdb_diag_proc_return ()
{
    if (diag_format == DIAG_XDB_NEW) slt_exit ();
    return;
}


/*
 *    DIAGNOSTICS FOR THE END OF A PROCEDURE
 */

void
xdb_diag_proc_end(diag_global *di)
{
    area (ptext);
    if (diag_format == DIAG_XDB_NEW) {
		mach_op *op1 = make_lab_data (crt_diag_proc_lab, 0);
		mach_op *op2 = make_extern_data (".-1", 0);
		make_instr (m_as_assign, op1, op2, 0);
    } else if (diag_format == DIAG_XDB_OLD) {
		make_label (crt_diag_proc_lab);
    }
    dnt_end ();
    area (plast);
    return;
}


/*
 *    DIAGNOSTICS FOR THE START OF A VALUE
 */

void
xdb_diag_val_begin(diag_global *di, char *pname,
				   long cname, int is_ext)
{
    char *nm = di->data.id.nme.ints.chars;
    diag_type t = di->data.id.new_type;
    diag_globl_variable (t, nm, !is_local (pname), pname, 1);
    return;
}


/*
 *    OUTPUT GLOBAL TABLE
 */

void
OUTPUT_GLOBALS_TAB()
{
    diag_descriptor *di = unit_diagvar_tab.array;
    unsigned long i, n = unit_diagvar_tab.lastused;
    for (i = 0 ; i < n ; i++) {
		if (di [i].key == DIAG_TYPEDEF_KEY) {
			diag_type d = di [i].data.typ.new_type;
			char *nm = di [i].data.typ.nme.ints.chars;
			diag_type_defn (nm, d);
		}
    }
    return;
}


/*
 *    OUTPUT ALL DIAGNOSTIC TAGS
 */

void
OUTPUT_DIAG_TAGS()
{
    return;
}


/*
 *    INSPECT FILENAME
 */

void
INSPECT_FILENAME(filename fn)
{
    char *nm = fn->file.ints.chars;
    diag_source (nm, 1, 0);
    return;
}


/*
 *    COMPARE TWO DECLARATIONS
 */

static bool
cmp_dec(dec *x, dec *y)
{
    int c;
    long lx, ly;
    char *fx, *fy;
    sourcemark *sx, *sy;
    diag_global *dx = x->dec_u.dec_val.diag_info;
    diag_global *dy = y->dec_u.dec_val.diag_info;
    if (dy == null || dy->key != DIAG_ID_KEY) return (0);
    if (dx == null || dx->key != DIAG_ID_KEY) return (1);
    sx = &(dx->data.id.whence);
    fx = sx->file->file.ints.chars;
    lx = sx->line_no.nat_val.small_nat;
    sy = &(dy->data.id.whence);
    fy = sy->file->file.ints.chars;
    ly = sy->line_no.nat_val.small_nat;
    c = strcmp ((char*)sx, (char*)sy);
    if (c < 0) return (0);
    if (c > 0) return (1);
    return (lx > ly ? 1 : 0);
}


/*
 *    SORT DECLARATION INTO ORDER
 */

dec
*sort_decs(dec *p)
{
    dec *res = null;
    dec *x = p, *y;
    while (x != null) {
		dec *nextx = x->def_next;
		dec *before = null;
		for (y = res ; y != null ; y = y->def_next) {
			if (!cmp_dec (x, y)) break;
			before = y;
		}
		if (before == null) {
			x->def_next = res;
			res = x;
		} else {
			x->def_next = before->def_next;
			before->def_next = x;
		}
		x = nextx;
    }
    return (res);
}
