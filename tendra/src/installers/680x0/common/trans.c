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
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
 *Revision 1.2  1997/10/29 10:22:31  ma
 *Replaced use_alloca with has_alloca.
 *
 *Revision 1.1.1.1  1997/10/13 12:43:00  ma
 *First version.
 *
 *Revision 1.6  1997/10/13 08:50:13  ma
 *Made all pl_tests for general proc & exception handling pass.
 *
 *Revision 1.5  1997/09/25 06:45:36  ma
 *All general_proc tests passed
 *
 *Revision 1.4  1997/06/18 12:04:59  ma
 *Merged with Input Baseline changes.
 *
 *Revision 1.3  1997/06/18 10:09:45  ma
 *Checking in before merging with Input Baseline changes.
 *
 *Revision 1.2  1997/04/20 11:30:40  ma
 *Introduced gcproc.c & general_proc.[ch].
 *Added cases for apply_general_proc next to apply_proc in all files.
 *
 *Revision 1.1.1.1  1997/03/14 07:50:19  ma
 *Imported from DRA
 
 * Revision 1.1.1.1  1996/09/20  10:56:59  john
 *
 * Revision 1.2  1996/07/05  14:28:02  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:18  john
 *
 * Revision 1.3  94/02/21  16:05:07  16:05:07  ra (Robert Andrews)
 * Just declare scan2 traditionally.
 *
 * Revision 1.2  93/11/19  16:23:34  16:23:34  ra (Robert Andrews)
 * Reformatted mark_unaliased.
 *
 * Revision 1.1  93/02/22  17:16:50  17:16:50  ra (Robert Andrews)
 * Initial revision
 *
 *--------------------------------------------------------------------------
 */


#include "config.h"
#include "common_types.h"
#include "expmacs.h"
#include "exp.h"
#include "flags.h"
#include "instrs.h"
#include "installglob.h"
#include "shapemacs.h"
#include "evaluate.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "weights.h"
#include "mach.h"
#include "where.h"
#include "coder.h"
#include "codex.h"
#include "optimise.h"
#include "output.h"
#include "tests.h"
#include "tags.h"
#include "utility.h"
#if have_diagnostics
#include "xdb_basics.h"
#endif
extern dec *sort_decs(dec *) ;
static void output_all_exps(void) ;

/*
 *    INCLUDE DEBUGGING ROUTINES
 *
 *    These are used to aid in debugging.
 
*/
#ifdef EBUG
/*
 *#include <misc/debug>
 */
void
breakpoint() {}
#endif

#ifndef tdf3
#include "general_proc.h"
#include "68k_globals.h"
int need_dummy_double = 0;
#endif

/*
 *    LOCAL AND GLOBAL NAME PREFIXES
 */

char *local_prefix = "L";
char *name_prefix = "_";


/*
 *    EXTERNAL POSITIONS
 */

static long crt_ext_off = 64;
static long crt_ext_pt = 10;


/*
 *    MARK AN EXPRESSION AS BEING STATIC AND UNALIASED
 */

static void
mark_unaliased(exp e)
{
    exp p = pt (e);
    bool ca = 1;
    while (p != nilexp && ca) {
		exp q = bro (p);
		if (q == nilexp) {
			ca = 0;
		} else if (!(last (p) && name (q) == cont_tag) &&
				   !(!last (p) && last (q) &&
					 name (bro (q)) == ass_tag)) {
			ca = 0;
		}
		p = pt (p);
    }
    if (ca) setcaonly (e);
    return;
}


/*
 *    PROCESS THE TDF
 *
 *    This routine gets all the TDF read into the correct operand form
 *    and applies the dead variable and register allocation analysis.
 */

void
translate_capsule()
{
    dec *d;
	
    /* Fix procedure handling (copied from trans386) */
    d = top_def;
#if 0
    while (d != (dec *) 0) {
		exp crt_exp = d -> dec_u.dec_val.dec_exp;
		exp idval;
		if (!(d -> dec_u.dec_val.dec_var) && (name(sh(crt_exp)) != prokhd ||
											  (idval = son(crt_exp) ,
											   idval != nilexp && name(idval) != null_tag &&
											   name(idval) != proc_tag && name(idval) != general_proc_tag))){
			/* make variable, and change all uses to contents */
			exp p = pt(crt_exp);
			if (d -> dec_u.dec_val.extnamed)
				sh(crt_exp) = f_pointer(f_alignment(sh(crt_exp)));
			else
				setvar(crt_exp);
			while (p != nilexp) {
				exp np = pt(p);
				exp* ptr = refto (father(p), p);
				exp c = getexp (sh(p), bro(p), last(p), p, nilexp, 0, 0, cont_tag);
				setfather (c, p);
				if (no(p) != 0) {
					exp r = getexp (sh(p), c, 1, p, nilexp, 0, no(p), reff_tag);
					no(p) = 0;
					son(c) = r;
					setfather (r, p);
				}
				*ptr = c;
				p = np;
			}
		}
		d = d->def_next;
    }
#endif
	
	
    make_transformations ();
	
#ifndef EBUG
    opt_all_exps ();
#endif
	
    /* Mark static unaliases declarations */
    if (!separate_units) {
		for (d = top_def ; d ; d = d->def_next) {
			exp c = d->dec_u.dec_val.dec_exp;
			if (son (c) != nilexp &&
				!(d->dec_u.dec_val.extnamed) && isvar (c)) {
				mark_unaliased (c);
			}
		}
    }
	
    /* Mark locations for all globals */
    for (d = top_def ; d ; d = d->def_next) {
		if (d->dec_u.dec_val.processed) {
			exp c = d->dec_u.dec_val.dec_exp;
			ptno (c) = crt_ext_pt++;
			no (c) = crt_ext_off;
			crt_ext_off += shape_size (d->dec_u.dec_val.dec_shape);
		}
    }
	
    /* Output all code */
    output_all_exps ();
	
    return;
}


/*
 *    TRANSLATE A SINGLE TAG DEFINITION
 */

void
translate_tagdef()
{
    return;
}


/*
 *    TRANSLATE A SINGLE UNIT
 */

void
translate_unit()
{
    if (separate_units) {
		dec *d;
		translate_capsule ();
		d = top_def;
		while (d) {
			exp c = d->dec_u.dec_val.dec_exp;
			no (c) = 0;
			pt (c) = nilexp;
			d = d->def_next;
		}
		crt_repeat = nilexp;
		repeat_list = nilexp;
    }
    return;
}


/*
 *    ENCODE A PROCEDURE
 *
 *    The procedure with declaration d, name id, definition c and body s
 *    is encoded.
 */

static void
code_proc(dec *d, char *id, exp c, exp s)
{
    diag_global *di = d->dec_u.dec_val.diag_info;
    int reg_res = (has_struct_res (s) ? 0 : 1);
    int is_ext = (d->dec_u.dec_val.extnamed ? 1 : 0);
	
    area (ptext);
	
    cur_proc_dec = d;
    cur_proc_callees_size = 0;
    cur_proc_has_vcallees = 0;
	
    /* Code procedure body */
#if 0
    if (name (s) == proc_tag)
		cproc (s, id, -1, is_ext, reg_res, di);
    else
#endif
		gcproc (s, id, -1, is_ext, reg_res, di);
	
	
    d -> dec_u.dec_val.index = cur_proc_env_size ; /* for use in constant evaluation */
	
    output_env_size(d, cur_proc_env_size);
}


/*
 *    ENCODE A CONSTANT
 *
 *    The constant with declaration d, name id, definition c and body s
 *    is encoded.
 */

static void
code_const(dec *d)
{
	exp c = d->dec_u.dec_val.dec_exp;
	exp s = son (c);
	char *id = d->dec_u.dec_val.dec_id;
	
	diag_global *di = d->dec_u.dec_val.diag_info;
	area (isvar (c) ? pdata : ptext);
#ifndef no_align_directives
	make_instr (m_as_align4, null, null, 0);
#endif
	evaluate (s, L_1 , id, !isvar (c), 1, di);
}


/*
 *    ENCODE THE CONSTANTS IN const_list
 *
 *    All auxiliary constants are formed into a list, const_list.  This
 *    routine applies evaluate to each element of this list.
 */

static void
code_const_list()
{
    while (const_list != nilexp) {
		exp t = const_list;
		exp s = son (t);
		bool b = (name (s) != res_tag);
		const_list = bro (const_list);
		if (name (s) == proc_tag || name (s) == general_proc_tag) {
			char *id = alloc_nof (char, 30);
			sprintf (id, "%s%ld", local_prefix, no (t));
			gcproc (s, null, no (t), 0, 1, null);
		} else {
			area (b ? pdata : ptext);
			evaluate (s, no (t), null, b, 0, null);
		}
    }
    return;
}

/*
 *   CONST_READY
 *
 *   Returns TRUE if it is possible to evaluate the value of the constant now
 */

static int
const_ready(exp e)
{
	unsigned char  n = name (e);
	if (n == env_size_tag)
		return (brog(son(son(e))) -> dec_u.dec_val.processed);
	if (n == env_offset_tag)
		return (ismarked(son(e)));
	if (n == name_tag || son(e) == nilexp)
		return 1;
	e = son(e);
	while (!last(e)) {
		if (!const_ready(e))
			return 0;
		e = bro(e);
	}
	return (const_ready(e));
}

typedef struct delayedconst{
	dec* This;
	struct delayedconst* next;
} delayed_const;

static delayed_const* delayed_const_list = 0;

static void
eval_if_ready(dec *d)
{
	exp c = d->dec_u.dec_val.dec_exp;
	if (const_ready(c)) {
		code_const (d);
	}
	else {
		delayed_const* p = (delayed_const*)xmalloc (sizeof(delayed_const));
		p->This = d;
		p->next = delayed_const_list;
		delayed_const_list = p;
	}
}

void
eval_delayed_const_list()
{
	delayed_const* p;
	bool done = 0;
	while (! done) {
		done = 1;
		for (p = delayed_const_list; p; p = p->next) {
			dec* d = p->This;
			if (!d->dec_u.dec_val.processed) {
				exp c = d->dec_u.dec_val.dec_exp;
				if (const_ready(c)) {
					code_const (d);
					d->dec_u.dec_val.processed = 1;
				}
				done = 0;
			}
		}
	}
}


/*
 *    OUTPUT ALL THE ENCODED EXPRESSIONS
 *
 *    This routine scans through all the declarations encoding suitably.
 */

static void
output_all_exps()
{
    dec *d = top_def;
    if (diagnose) d = sort_decs (d);
	
    area (ptext);
	
    /* Clear any existing output */
    output_all ();
    free_all_ins ();
	
    /* Scan through the declarations */
    while (d) {
		
		if (!d->dec_u.dec_val.processed) {
			exp c = d->dec_u.dec_val.dec_exp;
			exp s = son (c);
			char *id = d->dec_u.dec_val.dec_id;
			
			init_output ();
			
			if (s != nilexp) {
				if (name (s) == proc_tag ||
                    name (s) == general_proc_tag) {
					code_proc (d, id, c, s);
					code_const_list ();
                    d->dec_u.dec_val.processed = 1;
				} else {
					eval_if_ready (d);
					code_const_list ();
				}
			} else {
				shape sha = d->dec_u.dec_val.dec_shape;
				long sz = round (shape_size (sha) / 8, 4);
				area (ptext);
				if (!is_local (id) && isvar (c) &&
					varsize (sha) && !reserved (id)) {
					if (sz) {
						mach_op *op1 = make_extern_data (id, 0);
						mach_op *op2 = make_int_data (sz);
						make_instr (m_as_common, op1, op2, 0);
					}
				} else {
					if (is_local (id) && no (c)) {
						mach_op *op1 = make_extern_data (id, 0);
						mach_op *op2 = make_int_data (sz);
						make_instr (m_as_local, op1, op2, 0);
					}
				}
                d->dec_u.dec_val.processed = 1;
			}
			
			output_all ();
			free_all_ins ();
		}
		d = d->def_next;
    }
	
    eval_delayed_const_list();
    output_all ();
    free_all_ins ();
	
    /* Add final touches */
    init_output ();
    if (need_dummy_double)  {
		mach_op *op1 = make_extern_data ("___m68k_dummy_double", 0);
		mach_op *op2 = make_int_data (8);
		make_instr (m_as_common, op1, op2, 0);
    }
	
    if (do_profile) profile_hack ();
	
    area (pdata);
    output_all ();
    free_all_ins ();
    return;
}
