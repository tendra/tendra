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
 *Revision 1.1.1.1  1997/10/13 12:43:02  ma
 *First version.
 *
 *Revision 1.1.1.1  1997/03/14 07:50:23  ma
 *Imported from DRA
 
 * Revision 1.1.1.1  1996/09/20  10:57:02  john
 *
 * Revision 1.2  1996/07/05  14:36:42  john
 * Fix to diagnostics
 *
 * Revision 1.1  95/03/08  16:46:33  ra
 * Added missing files.
 *
 * Revision 1.4  94/02/21  16:09:42  16:09:42  ra (Robert Andrews)
 * Put in a number of explicit casts.
 *
 * Revision 1.3  93/11/19  16:25:34  16:25:34  ra (Robert Andrews)
 * Bitfields should have the correct size, not 32.
 *
 * Revision 1.2  93/04/19  13:40:05  13:40:05  ra (Robert Andrews)
 * struct_fields and union_fields have been renamed diag_field.
 *
 * Revision 1.1  93/02/22  17:17:29  17:17:29  ra (Robert Andrews)
 * Initial revision
 *
 *--------------------------------------------------------------------------
 */


#include "config.h"
#include <time.h>
#include "common_types.h"
#include "expmacs.h"
#include "externs.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "output.h"
#include "shapemacs.h"
#include "utility.h"
#include "xdb_output.h"
#include "xdb_types.h"
#ifndef SEEK_SET
#define SEEK_SET 0
#endif


/*
 *    GENERATE A UNIQUE IDENTIFIER
 */

static unsigned
unique_id()
{
    static unsigned u = 0;
    if (u == 0) {
		time_t t = time ((time_t *) NULL);
		u = (unsigned) t;
    }
    return (u);
}


/*
 *    CURRENT POSITIONS IN DIAGNOSTIC NAME TABLES
 */

static posn_t dtposn_local = LOCAL_POSN;
static posn_t dtposn_globl = GLOBL_POSN;


/*
 *    OUTPUT A DIAGNOSTIC DIRECTIVE
 */

posn_t
out_dd(FILE *file, int n, int loc)
{
    diag_directive *d = dd + n;
    long sz = (diag_format == DIAG_XDB_NEW ? d->new_size : d->old_size);
    posn_t p = (loc ? dtposn_local : dtposn_globl);
    fprintf (file, "%s", instr_names [ d->instr ]);
    if (loc) {
		dtposn_local = p + sz;
    } else {
		dtposn_globl = p + sz;
    }
    return (p);
}


/*
 *     CREATE A NEW TABLE POSITION
 */

static table_posn
*new_table_posn(posn_t n, long sz)
{
    table_posn *p;
    static int no_tp_free = 0;
    static table_posn *tp_free;
    if (no_tp_free == 0) {
		no_tp_free = 20;
		tp_free = alloc_nof (table_posn, no_tp_free);
    }
    p = tp_free++;
    no_tp_free--;
    p->is_lab = 0;
    p->posn = n;
    p->size = sz;
    return (p);
}


/*
 *    OUTPUT A TABLE POSITION
 */

void
out_posn(FILE *file, table_posn *p, int comma)
{
    if (p->is_lab) {
		fprintf (file, "LD%d", (int) p->posn);
    } else {
		fprintf (file, "0x%x", (unsigned int) p->posn);
    }
    fputc ((comma ? ',' : '\n'), file);
    return;
}


/*
 *    GO TO A POSITION IN A FILE AND PRINT A TABLE POSITION
 */

void
fill_gap(FILE *file, long fp, posn_t t)
{
    long fp_old = ftell (file);
    if (fseek (file, fp, SEEK_SET) == -1) {
		error ("Internal file seek error");
		return;
    }
    fprintf (file, "0x%x", (unsigned int) t);
    if (fseek (file, fp_old, SEEK_SET) == -1) {
		error ("Internal file seek error");
    }
    return;
}


/*
 *    CURRENT DIAGNOSTICS LABEL NUMBER
 */

static long diag_lab = 0;


/*
 *    FIND THE TABLE POSITION OF A TDF SHAPE
 */

static table_posn
*analyse_diag_shape(FILE *file, shape sha)
{
    posn_t t = NULL_POSN;
    long sz = shape_size (sha);
    switch (name (sha)) {
	case scharhd : t = CHAR_POSN + sz ; break;
	case swordhd :
	case slonghd : t = SIGNED_POSN + sz ; break;
	case ucharhd :
	case uwordhd :
	case ulonghd : t = UNSIGNED_POSN + sz ; break;
	case shrealhd :
	case realhd :
	case doublehd : t = FLOATING_POSN + sz ; break;
    }
    return (new_table_posn (t, sz));
}


/*
 *    FIND THE TABLE POSITION OF A DIAGNOSTIC TYPE
 */

table_posn
*analyse_diag_type(FILE *file, diag_type dt,
				   int loc)
{
    table_posn *res;
    if (dt->been_outed) return ((table_posn *) dt->been_outed);
	
    switch (dt->key) {
		
	case DIAG_TYPE_ARRAY : {
	    diag_type dtl = dt->data.array.element_type;
	    long lo = no (dt->data.array.lower_b);
	    long hi = no (dt->data.array.upper_b);
		
	    table_posn *p = analyse_diag_type (file, dtl, loc);
	    long sz = (hi - lo + 1) * (p->size);
	    posn_t s, t = out_dd (file, xdb_subrange, loc);
		
	    if (diag_format == DIAG_XDB_NEW) fprintf (file, "0,0,");
	    fprintf (file, "%ld,%ld,0x%x,32\n", lo, hi,
				 (unsigned int) (SIGNED_POSN + 32));
	    s = out_dd (file, xdb_array, loc);
	    if (diag_format == DIAG_XDB_NEW) {
			fprintf (file, "0,0,0,0,0,0,");
	    }
	    fprintf (file, "0,%ld,0x%x,", sz, (unsigned int) t);
	    if (diag_format == DIAG_XDB_NEW) {
			out_posn (file, p, 1);
			fprintf (file, "%ld\n", p->size);
	    } else {
			out_posn (file, p, 0);
	    }
	    res = new_table_posn (s, sz);
	    break;
	}
		
	case DIAG_TYPE_BITFIELD : {
	    long sz = dt->data.bitfield.no_of_bits.nat_val.small_nat;
	    res = new_table_posn (SIGNED_POSN + 32, sz);
	    break;
	}
		
	case DIAG_TYPE_ENUM : {
	    char *nm = dt->data.t_enum.nme.ints.chars;
	    enum_values *fld = dt->data.t_enum.values->array;
	    long i, n = (long) dt->data.t_enum.values->lastused;
		
	    /* Initialize enumeration information */
	    long fp;
	    posn_t t;
	    t = out_dd (file, xdb_enum, loc);
	    fp = ftell (file);
	    fprintf (file, "%s,32\n", NULL_POSN_STR);
	    res = new_table_posn (t, L32);
		
	    /* Deal with enumeration members */
	    for (i = n - 1 ; i >= 0 ; i--) {
			char *fnm = fld [i]->nme.ints.chars;
			long v = no (fld [i]->val);
			posn_t s = out_dd (file, xdb_memenum, loc);
			fill_gap (file, fp, s);
			if (diag_format == DIAG_XDB_NEW) fprintf (file, "0,");
			if (*fnm) {
				diag_string (file, fnm);
			} else {
				diag_string (file, "__unknown");
			}
			fprintf (file, ",%ld,", v);
			fp = ftell (file);
			fprintf (file, "%s\n", NULL_POSN_STR);
	    }
		
	    /* Round off enumeration definition */
	    if (*nm) {
			(void) out_dd (file, xdb_tagdef, loc);
			fprintf (file, "0,");
			if (diag_format == DIAG_XDB_NEW) fprintf (file, "1,");
			diag_string (file, nm);
			fprintf (file, ",");
			out_posn (file, res, 0);
	    }
	    break;
	}
		
	case DIAG_TYPE_FLOAT : {
	    shape sha = f_floating (dt->data.f_var);
	    res = analyse_diag_shape (file, sha);
	    break;
	}
		
	case DIAG_TYPE_LOC : {
	    diag_type dtl = dt->data.loc.object;
	    res = analyse_diag_type (file, dtl, loc);
	    break;
	}
		
	case DIAG_TYPE_NULL : {
	    res = new_table_posn (NULL_POSN, L0);
	    break;
	}
		
	case DIAG_TYPE_PROC : {
	    diag_type dtl = dt->data.proc.result_type;
	    table_posn *p = analyse_diag_type (file, dtl, loc);
	    posn_t t = out_dd (file, xdb_functype, loc);
	    if (diag_format == DIAG_XDB_NEW) fprintf (file, "0,0,");
	    fprintf (file, "32,");
	    out_posn (file, p, 1);
	    fprintf (file, "%s\n", NULL_POSN_STR);
	    res = new_table_posn (t, L32);
	    break;
	}
		
	case DIAG_TYPE_PTR : {
	    diag_type dtl = dt->data.ptr.object;
	    table_posn *p = analyse_diag_type (file, dtl, loc);
	    posn_t t = out_dd (file, xdb_pointer, loc);
	    out_posn (file, p, 1);
	    fprintf (file, "32\n");
	    res = new_table_posn (t, L32);
	    break;
	}
		
	case DIAG_TYPE_STRUCT : {
	    shape sha = dt->data.t_struct.tdf_shape;
	    long sz = shape_size (sha);
	    char *nm = dt->data.t_struct.nme.ints.chars;
#if 0
	    struct_fields *fld = dt->data.t_struct.fields->array;
#else
	    diag_field *fld = dt->data.t_struct.fields->array;
#endif
	    long i, n = (long) dt->data.t_struct.fields->lastused;
		
	    /* Initialize structure information */
	    long fp;
	    posn_t t;
	    int taglab = 0;
	    char nmbuff [50];
	    long dlab = diag_lab++;
	    if (diag_format == DIAG_XDB_NEW) {
			if (*nm == 0) {
				unsigned u = unique_id ();
				nm = nmbuff;
				sprintf (nm, "(%u.%ld)", u, dlab);
			}
			taglab = 1;
	    }
	    if (!taglab) fprintf (file, "LD%ld:", dlab);
	    t = out_dd (file, xdb_struct, loc);
	    fprintf (file, "0,");
	    fp = ftell (file);
	    fprintf (file, "%s,%s,%s,%ld\n", NULL_POSN_STR, NULL_POSN_STR,
				 NULL_POSN_STR, sz);
	    res = new_table_posn (t, sz);
		
	    /* Print tag information */
	    if (*nm) {
			posn_t tt;
			if (taglab) fprintf (file, "LD%ld:", dlab);
			tt = out_dd (file, xdb_tagdef, loc);
			fprintf (file, "0,");
			if (diag_format == DIAG_XDB_NEW) fprintf (file, "1,");
			diag_string (file, nm);
			fprintf (file, ",");
			out_posn (file, res, 0);
			if (taglab) t = tt;
	    }
		
	    /* Set up structure label */
	    res->is_lab = 1;
	    res->posn = (posn_t) dlab;
	    dt->been_outed = (OUTPUT_REC) res;
		
	    /* Deal with structure fields */
	    for (i = n - 1 ; i >= 0 ; i--) {
			char *fnm = fld [i]->field_name.ints.chars;
			long off = no (fld [i]->where);
			diag_type dtl = fld [i]->field_type;
			table_posn *q = analyse_diag_type (file, dtl, loc);
			posn_t s = out_dd (file, xdb_field, loc);
			fill_gap (file, fp, s);
			if (diag_format == DIAG_XDB_NEW) fprintf (file, "0,0,");
			if (*fnm) {
				diag_string (file, fnm);
			} else {
				diag_string (file, "__unknown");
			}
			fprintf (file, ",%ld,", off);
			out_posn (file, q, 1);
			fprintf (file, "%ld,", q->size);
			fp = ftell (file);
			fprintf (file, "%s\n", NULL_POSN_STR);
	    }
		
	    /* Round off structure definition */
	    res->is_lab = 0;
	    res->posn = t;
	    break;
	}
		
	case DIAG_TYPE_UNION : {
	    shape sha = dt->data.t_union.tdf_shape;
	    long sz = shape_size (sha);
	    char *nm = dt->data.t_union.nme.ints.chars;
#if 0
	    union_fields *fld = dt->data.t_union.fields->array;
#else
	    diag_field *fld = dt->data.t_union.fields->array;
#endif
	    long i, n = (long) dt->data.t_union.fields->lastused;
		
	    /* Initialize union information */
	    long fp;
	    posn_t t;
	    int taglab = 0;
	    long dlab = diag_lab++;
	    char nmbuff [50];
	    if (diag_format == DIAG_XDB_NEW) {
			if (*nm == 0) {
				unsigned u = unique_id ();
				nm = nmbuff;
				sprintf (nm, "(%u.%ld)", u, dlab);
			}
			taglab = 1;
	    }
	    if (!taglab) fprintf (file, "LD%ld:", dlab);
	    t = out_dd (file, xdb_union, loc);
	    fp = ftell (file);
	    fprintf (file, "%s,%ld\n", NULL_POSN_STR, sz);
	    res = new_table_posn (t, sz);
		
	    /* Print tag information */
	    if (*nm) {
			posn_t tt;
			if (taglab) fprintf (file, "LD%ld:", dlab);
			tt = out_dd (file, xdb_tagdef, loc);
			fprintf (file, "0,");
			if (diag_format == DIAG_XDB_NEW) fprintf (file, "1,");
			diag_string (file, nm);
			fprintf (file, ",");
			out_posn (file, res, 0);
			if (taglab) t = tt;
	    }
		
	    /* Set up union label */
	    res->is_lab = 1;
	    res->posn = (posn_t) dlab;
	    dt->been_outed = (OUTPUT_REC) res;
		
	    /* Deal with union fields */
	    for (i = n - 1 ; i >= 0 ; i--) {
			char *fnm = fld [i]->field_name.ints.chars;
			long off = no (fld [i]->where);
			diag_type dtl = fld [i]->field_type;
			table_posn *q = analyse_diag_type (file, dtl, loc);
			posn_t s = out_dd (file, xdb_field, loc);
			fill_gap (file, fp, s);
			if (diag_format == DIAG_XDB_NEW) fprintf (file, "0,0,");
			if (*fnm) {
				diag_string (file, fnm);
			} else {
				diag_string (file, "__unknown");
			}
			fprintf (file, ",%ld,", off);
			out_posn (file, q, 1);
			fprintf (file, "%ld,", q->size);
			fp = ftell (file);
			fprintf (file, "%s\n", NULL_POSN_STR);
	    }
		
	    /* Round off union definition */
	    res->is_lab = 0;
	    res->posn = t;
	    break;
	}
		
	case DIAG_TYPE_VARIETY : {
	    shape sha = f_integer (dt->data.var);
	    res = analyse_diag_shape (file, sha);
	    break;
	}
		
	default : {
	    res = new_table_posn (NULL_POSN, L0);
	    break;
	}
    }
	
    dt->been_outed = (OUTPUT_REC) res;
    return (res);
}


/*
 *    DIAGNOSTIC SCOPE STACK
 */

static dscope *dscope_stack = null;
static int no_dscope = 0;
static int dscope_stk_size = 0;


/*
 *    PUSH A DIAGNOSTICS SCOPE
 */

void
push_dscope(posn_t p, int t)
{
    int n = no_dscope++;
    if (n >= dscope_stk_size) {
		dscope_stk_size += 20;
		dscope_stack = realloc_nof (dscope_stack, dscope, dscope_stk_size);
    }
    dscope_stack [n].posn = p;
    dscope_stack [n].dscope_type = t;
    return;
}


/*
 *    POP A DIAGNOSTICS SCOPE
 */

dscope
*pop_dscope()
{
    int n = no_dscope;
    if (n == 0) return (null);
    no_dscope = (--n);
    return (dscope_stack + n);
}
