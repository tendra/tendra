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
 *Revision 1.1.1.1  1997/10/13 12:43:00  ma
 *First version.
 *
 *Revision 1.3  1997/09/25 06:45:40  ma
 *All general_proc tests passed
 *
 *Revision 1.2  1997/04/20 11:30:41  ma
 *Introduced gcproc.c & general_proc.[ch].
 *Added cases for apply_general_proc next to apply_proc in all files.
 *
 *Revision 1.1.1.1  1997/03/14 07:50:20  ma
 *Imported from DRA
 
 * Revision 1.1.1.1  1996/09/20  10:57:00  john
 *
 * Revision 1.2  1996/07/05  14:29:51  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:19  john
 *
 * Revision 1.2  94/02/21  16:06:14  16:06:14  ra (Robert Andrews)
 * Put in an explicit cast.
 *
 * Revision 1.1  93/02/22  17:16:59  17:16:59  ra (Robert Andrews)
 * Initial revision
 *
 *--------------------------------------------------------------------------
 */


#include "config.h"
#include "common_types.h"
#include "exp.h"
#include "expmacs.h"
#include "externs.h"
#include "shapemacs.h"
#include "tags.h"
#include "tests.h"
#include "utility.h"
#include "mach.h"
#include "where.h"
#include "translate.h"
#include "weights.h"


/*
 *    CONTROL MACROS
 */

#define  AVERAGE_LOOP_LENGTH	10


/*
 *    MAXIMUM AND MINIMUM WEIGHTS
 */

#define  cant_use		((float) -1.0e10)


/*
 *    NUMBERS OF AVAILABLE REGISTERS
 */

#define  wdno		16
#define  wano		16
#define  wfno		6
#define  wno		(wdno + wano + wfno)


/*
 *    STRUCTURE DEFINITIONS OF weights, wp, explist
 */

typedef struct {
    float wts [ wno ];
    long d_used;
    long a_used;
    long f_used;
} weights;

typedef struct {
    weights wt;
    long bkpt;
} wp;

typedef struct elt {
    exp member;
    struct elt *next;
} explist ;


/*
 *    BASIC WEIGHTS
 */

static weights zeros;
static weights weightsv(exp, explist *) ;


/*
 *    CURRENT WEIGHTS SCALE FACTOR
 */

static float scale;


/*
 *    ADD TWO WEIGHT VECTORS
 */

static weights
add_weights(weights w1, weights w2)
{
    long i;
    weights r;
    float wa, wb;
    for (i = 0 ; i < wno ; i++) {
		wa = (w1.wts)[i];
		wb = (w2.wts)[i];
		if (wa == cant_use || wb == cant_use) {
			(r.wts)[i] = cant_use;
		} else {
			(r.wts)[i] = wa + wb;
		}
    }
    r.d_used = maximum (w1.d_used, w2.d_used);
    r.a_used = maximum (w1.a_used, w2.a_used);
    r.f_used = maximum (w1.f_used, w2.f_used);
    return (r);
}


/*
 *    INITIALIZE BASIC WEIGHTS
 */

void
init_weights()
{
    long i;
    for (i = 0 ; i < wno ; i++) (zeros.wts)[i] = (float) 0.0;
    zeros.d_used = -1;
    zeros.a_used = -1;
    zeros.f_used = -1;
    return;
}


/*
 *    MARK A LIST OF EXPS
 */

static void
markcall(explist *el, bitpattern b)
{
    explist *t;
    for (t = el ; t != null ; t = t->next) props (t->member) |= b;
    return;
}


/*
 *    WORK OUT WEIGHTS FOR A DECLARATION
 */

static wp
max_weights(long s, float locp, weights ws,
			int rtype)
{
    wp res;
    bool bkset = 0;
    long i, n;
    long sz = (s + 31) / 32, bk = 1;
    long q = 0;
    float *w, *pw;
    long used, total, offset;
	
    /* Find values for this register type */
    switch (rtype) {
		
	case Dreg : {
	    offset = 0;
	    total = wdno;
	    used = ws.d_used;
	    break;
	}
		
	case Areg : {
	    offset = wdno;
	    total = wano;
	    used = ws.a_used;
	    break;
	}
		
	case Freg : {
	    offset = wdno + wano;
	    total = wfno;
	    used = ws.f_used;
	    break;
	}
		
	default : {
	    error ("Illegal register type");
	    exit (EXIT_FAILURE);
	}
    }
    w = &(ws.wts)[ offset ];
    pw = &((res.wt).wts)[ offset ];
    n = used + sz + 1;
    if (n > total) n = total;
	
    /* Copy ws to res.wt */
    for (i = 0 ; i < wno ; i++) ((res.wt).wts)[i] = (ws.wts)[i];
    res.wt.d_used = ws.d_used;
    res.wt.a_used = ws.a_used;
    res.wt.f_used = ws.f_used;
	
    if (locp == cant_use) {
		for (i = 0 ; i < n ; i++) pw [i] = cant_use;
		for (i = n ; i < total ; i++) pw [i] = w [i];
		switch (rtype) {
	    case Dreg : res.wt.d_used = ws.d_used + sz ; break;
	    case Areg : res.wt.a_used = ws.a_used + sz ; break;
	    case Freg : res.wt.f_used = ws.f_used + sz ; break;
		}
		bk = 0;
    } else {
		float loc = locp * ((float) sz);
		q = -1;
		for (i = 0 ; i < total ; i++) {
			if (w [i] == cant_use) {
				pw [i] = cant_use;
				q = i;
			} else {
				if (i < (sz + q)) {
					pw [i] = w [i];
				} else {
					if (i == (sz + q)) {
						if (loc >= w [i] && used <= q) {
							pw [i] = loc;
							bk = i + 1;
							bkset = 1;
						} else {
							pw [i] = w [i];
						}
					} else {
						float z = loc + w [ i - sz ];
						if (z >= w [i]) {
							pw [i] = z;
							if (!bkset) { bk = i + 1 ; bkset = 1 ; }
						} else {
							pw [i] = w [i];
						}
					}
				}
			}
		}
    }
    /* Set the breakpoint */
    res.bkpt = bk;
    return (res);
}


/*
 *    WORK OUT WEIGHTS FOR A LIST OF EXPS
 */

static weights
add_wlist(exp re, explist *el)
{
    weights wl1, wl2;
    if (re == nilexp) return (zeros);
	
    wl1 = weightsv (re, el);
	
    while (!last (re)) {
		re = bro (re);
		wl2 = weightsv (re, el);
		wl1 = add_weights (wl1, wl2);
    }
    return (wl1);
}


/*
 *    IS X AN ASSIGNMENT?
 */

#define  ass(X)	(name (X) == ass_tag || name (X) == assvol_tag)


/*
 *    WORK OUT WEIGHTS FOR e SCALED BY scale AND SET BREAK POINTS
 */

static weights
weightsv(exp e, explist *el)
{
    unsigned char n = name (e);
    switch (n) {
		
	case name_tag : {
	    if (!isglob (son (e))) fno (son (e)) += scale;
	    /* Add value to the no field of the declaration */
	    return (zeros);
	}
		
	case make_lv_tag : {
	    return (zeros);
	}
		
	case ident_tag : {
	    wp p;
	    long sz;
	    shape sha;
		
	    /* Starting point for pt list */
	    exp t = pt (e);
	    exp d = son (e);
		
	    /* Add e to the list of exps */
	    explist nel;
	    nel.member = e;
	    nel.next = el;
		
	    while (isvar (e) && !isvis (e) && t != nilexp) {
			/* Scan along pt list */
			if (!(last (t) && name (bro (t)) == cont_tag) &&
				!(last (bro (t)) &&
				  ass (bro (bro (t)))))
				/* Make sure it will not go in register */
				setvis (e);
			t = pt (t);
	    }
		
	    if (d != nilexp) {
			int sht;
			weights wdef, wbody;
			fno (e) = (float) 0.0;
			
			/* Work out weights for the body */
			wbody = weightsv (bro (d), &nel);
			
			/* Work out weights for the definition */
			if (name (d) == clear_tag) {
				wdef = zeros;
			} else {
				float old_scale = scale;
				if (name (d) == name_tag) scale = fno (e);
				wdef = weightsv (d, el);
				scale = old_scale;
			}
			
			/* Shape information */
			sha = sh (d);
			sz = shape_size (sha);
			sht = shtype (sha);
			
#if 0
			/* Correct producer bug */
			if (name (sha) == slonghd && name (d) == val_tag &&
				no (d) == 0) {
				bool fix = 0;
				t = pt (e);
				while (t != nilexp) {
					exp f = father (t);
					if (name (f) == cont_tag &&
						name (sh (f)) == ptrhd) fix = 1;
					t = (last (t) ? nilexp : pt (t));
				}
				if (fix) {
					sh (d) = ptr_shape (sha);
					sht = Areg;
				}
			}
#endif
			
			if (isusereg (e)) {
				/* Work out breakpoint */
				p = max_weights (sz, cant_use, wbody, sht);
				no (e) = p.bkpt;
				if (no (e) == 13) error ("Bad breakpoint");
				return (add_weights (wdef, p.wt));
			}
			
			if (regable (e)) {
				/* Work out breakpoint */
				float loc = fno (e);
				if (name (d) == name_tag && isusereg (e)) {
					loc = (float) 1.0;
				}
				p = max_weights (sz, loc, wbody, sht);
				no (e) = p.bkpt;
				return (add_weights (wdef, p.wt));
			}
			
			no (e) = 16;
			return (add_weights (wdef, wbody));
	    }
	    return (zeros);
	}
		
	case labst_tag : {
	    /* Add e to list of exps */
	    explist nel;
	    nel.member = e;
	    nel.next = el;
	    if (regable (e)) {
			weights wbody;
			float old_scale = scale;
			scale = fno (e);
			wbody = weightsv (bro (son (e)), &nel);
			scale = old_scale;
			return (wbody);
	    } else {
			return (add_wlist (bro (son (e)), &nel));
	    }
	}
		
	case rep_tag : {
	    weights swl, bwl;
	    swl = weightsv (son (e), el);
	    bwl = weightsv (bro (son (e)), el);
	    return (add_weights (swl, bwl));
	}
		
	case compound_tag : {
	    return (add_wlist (son (e), el));
	}
		
	case untidy_return_tag :
	case case_tag :
	case res_tag : {
	    return (weightsv (son (e), el));
	}
	case apply_general_tag :
	case apply_tag :
	case round_tag :
	case float_tag : {
	    markcall (el, (bitpattern) 0x80);
	    return (add_wlist (son (e), el));
	}
		
	case ass_tag :
	case assvol_tag : {
	    weights swl, bwl;
	    swl = weightsv (son (e), el);
	    bwl = weightsv (bro (son (e)), el);
	    return (add_weights (swl, bwl));
	}
		
	case general_proc_tag :
	case proc_tag : {
	    weightsv (son (e), null);
	    return (zeros);
	}
		
	case env_offset_tag : {
	    return (zeros);
	}
		
	case val_tag :
	case real_tag : {
	    return (zeros);
	}
		
	case test_tag : {
	    weights twl;
	    twl = add_wlist (son (e), el);
	    /* scale = scale * (((float) 1.0) - fno (e)) ; */
	    return (twl);
	}
		
	default : {
	    return (add_wlist (son (e), el));
	}
    }
}


/*
 *    COMPUTE WEIGHTS
 */

void
comp_weights(exp e)
{
    scale = (float) 1.0;
    weightsv (e, null);
    return;
}
