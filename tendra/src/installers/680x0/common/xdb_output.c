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
 *Revision 1.1.1.1  1997/03/14 07:50:23  ma
 *Imported from DRA
 
 * Revision 1.1.1.1  1996/09/20  10:57:01  john
 *
 * Revision 1.2  1996/07/05  14:35:40  john
 * Fix to diagnostics
 *
 * Revision 1.1  95/03/08  16:46:25  ra
 * Added missing files.
 *
 * Revision 1.3  94/02/21  16:09:13  16:09:13  ra (Robert Andrews)
 * Put in a number of explicit casts.
 *
 * Revision 1.2  93/04/19  13:39:31  13:39:31  ra (Robert Andrews)
 * crt_fname and crt_line_num are no longer static.
 *
 * Revision 1.1  93/02/22  17:17:25  17:17:25  ra (Robert Andrews)
 * Initial revision
 *
 *--------------------------------------------------------------------------
 */


#include "config.h"
#include "common_types.h"
#include "assembler.h"
#include "codex.h"
#include "exp.h"
#include "expmacs.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "output.h"
#include "tags.h"
#include "utility.h"
#include "xdb_types.h"
#include "xdb_output.h"
#include "stab_types.h"
extern int diag_override;


/*
 *    WORK OUT WHETHER TO DO A DYNAMIC TEST FOR DIAGNOSTIC FORMAT
 */

#if (default_diag == DIAG_UNKNOWN)
#define dynamic_test
extern double atof(CONST char *) ;
#include <sys/utsname.h>
#else
#undef dynamic_test
#endif


/*
 *    WHICH DIAGNOSTIC FORMAT SHOULD BE USED?
 */

bool diag_format = default_diag;


/*
 *    ARRAY OF DIAGNOSTIC DIRECTIVES
 *
 *    This array gives information on all the available diagnostic directives,
 *    included those which are unused.
 */

diag_directive dd [] = {
    { m_dd_array, 2, 2 },
    { m_dd_begin, 1, 1 },
    { m_dd_const, 0, 0 },	/* unknown */
    { m_dd_dvar, 2, 2 },
    { m_dd_end, 1, 1 },
    { m_dd_entry, 0, 0 },	/* unknown */
    { m_dd_enum, 1, 1 },
    { m_dd_field, 2, 2 },
    { m_dd_file, 0, 0 },	/* unknown */
    { m_dd_fparam, 2, 2 },
    { m_dd_function, 3, 3 },
    { m_dd_functype, 2, 2 },
    { m_dd_import, 0, 0 },	/* unknown */
    { m_dd_label, 0, 0 },	/* unknown */
    { m_dd_memenum, 2, 2 },
    { m_dd_module, 1, 2 },
    { m_dd_pointer, 1, 1 },
    { m_dd_set, 0, 0 },		/* unknown */
    { m_dd_srcfile, 1, 1 },
    { m_dd_struct, 2, 2 },
    { m_dd_subrange, 2, 2 },
    { m_dd_svar, 2, 2 },
    { m_dd_tagdef, 1, 1 },
    { m_dd_typedef, 1, 1 },
    { m_dd_union, 1, 1 },
    { m_dd_variant, 0, 0 }	/* unknown */
};


/*
 *    DIAGNOSTICS FILES
 *
 *    There are three sections of diagnostic information in the new
 *    diagnostics mode (the vt, lntt and gntt sections).  One temporary
 *    file is used for each.  In the old diagnosics mode there is
 *    only one section (the dntt section), and only one file, diagfp2,
 *    is used.
 */

static FILE *diagfp1;
static FILE *diagfp2;
static FILE *diagfp3;


/*
 *    INITIALIZE DIAGNOSTICS FILES
 *
 *    The temporary files are opened, and the headings of the various
 *    sections are printed.
 */

void
init_diag()
{
    double vs = (diag_format == DIAG_XDB_NEW ? 7.40 : 7.05);
	
#ifdef dynamic_test
    struct utsname u;
    char *os = "HP-UX";
    uname (&u);
    os = u.sysname;
    vs = atof (u.release);
    if (strcmp (os, "HP-UX") == 0) {
		diag_format = (vs >= 7.40 ? DIAG_XDB_NEW : DIAG_XDB_OLD);
    } else {
		diag_format = DIAG_UNKNOWN;
	}
#endif
	
    if (diag_override != DIAG_UNKNOWN) {
		diag_format = diag_override;
		vs = (diag_format == DIAG_XDB_NEW ? 7.40 : 7.05);
    }
    switch (diag_format) {
		
	case DIAG_STAB : {
	    /* Temporary files not used */
	    break;
	}
		
	case DIAG_UNKNOWN : {
	    warning ("Unknown diagnostics format");
	    diag_format = DIAG_XDB_NEW;
	    /* Fall through */
	}
		
	case DIAG_XDB_NEW : {
	    diagfp1 = tmpfile ();
	    diagfp2 = tmpfile ();
	    diagfp3 = tmpfile ();
	    if (diagfp1 == null || diagfp2 == null || diagfp3 == null) {
			error ("Can't open temporary diagnostics file");
			exit (EXIT_FAILURE);
	    }
	    fprintf (diagfp1, "%s\n", instr_names [ m_as_data ]);
	    fprintf (diagfp1, "%s\n", instr_names [ m_dd_vt ]);
	    fprintf (diagfp2, "%s\n", instr_names [ m_dd_lntt ]);
	    fprintf (diagfp3, "%s\n", instr_names [ m_dd_gntt ]);
	    break;
	}
		
	case DIAG_XDB_OLD : {
	    diagfp2 = tmpfile ();
	    if (diagfp2 == null) {
			error ("Can't open temporary diagnostics file");
			exit (EXIT_FAILURE);
	    }
	    fprintf (diagfp2, "%s\n", instr_names [ m_as_data ]);
	    fprintf (diagfp2, "%s\n", instr_names [ m_dd_start ]);
	    break;
	}
    }
    return;
}


/*
 *    COPY A FILE
 *
 *    The the file is copied to the main output file, fpout.
 */

static void
copy_diag_file(FILE *file)
{
    int c;
    rewind (file);
    while (c = getc (file), c != EOF) putc (c, fpout);
    fclose (file);
    return;
}


/*
 *    VT AREA NEWLINE FLAG
 *
 *    This flag is true if a newline has just been output in the vt area.
 */

static int vt_newline = 1;


/*
 *    COPY DIAGNOSTICS FILES
 *
 *    All the diagnostic files are copied to the main output file.
 */

void
copy_diag()
{
    if (diag_format == DIAG_XDB_NEW) {
		if (vt_newline) {
			fprintf (diagfp1, "%s0\n", instr_names [ m_dd_vtbytes ]);
		} else {
			fprintf (diagfp1, ",0\n");
		}
		copy_diag_file (diagfp1);
		copy_diag_file (diagfp2);
		copy_diag_file (diagfp3);
    } else if (diag_format == DIAG_XDB_OLD) {
		copy_diag_file (diagfp2);
    }
    return;
}


/*
 *    OUTPUT A DIAGNOSTICS STRING
 *
 *    Diagnostic strings (eg. procedure and variable names) are dealt with
 *    differently in the two formats.  In the old format they are output
 *    direct, in the new they are added to the vt table and the offset
 *    from the start of the table is used.
 */

void
diag_string(FILE *file, char *s)
{
    if (diag_format == DIAG_XDB_NEW) {
		static int vtposn = 0;
		static int vtwidth = 0;
		if (vt_newline) {
			fprintf (diagfp1, "%s0", instr_names [ m_dd_vtbytes ]);
			vt_newline = 0;
		} else {
			fprintf (diagfp1, ",0");
		}
		vtposn++;
		vtwidth++;
		fprintf (file, "%d", vtposn);
		for (; *s ; s++) {
			if (vt_newline) {
				fprintf (diagfp1, "%s%d", instr_names [ m_dd_vtbytes ], *s);
				vt_newline = 0;
			} else {
				fprintf (diagfp1, ",%d", *s);
			}
			vtposn++;
			vtwidth++;
			if (vtwidth > 12) {
				fprintf (diagfp1, "\n");
				vt_newline = 1;
				vtwidth = 0;
			}
		}
    } else {
		fprintf (file, "\"%s\"", s);
    }
    return;
}


/*
 *    CURRENT FILE INDEX AND LINE NUMBER
 *
 *    These variables record the current position in the source file.
 */

char *crt_fname = "";
long crt_line_num = -1;


/*
 *    NUMBER OF SLT INSTRUCTIONS
 *
 *    A count of the number of slt instructions is maintained.
 */

static int slt_num = 0;


/*
 *    PRINT AN SLT SPECIAL INSTRUCTION
 *
 *    An sltspecial instruction is output.  This goes straight into the
 *    main output file.
 */

static void
slt_special(int t, posn_t p)
{
    mach_op *op1, *op2, *op3;
    area (ptext);
    op1 = make_int_data (t);
    op2 = make_int_data (crt_line_num);
    op3 = make_hex_data (p);
    op1->of = op2;
    op2->of = op3;
    make_instr (m_dd_special, op1, null, 0);
    area (plast);
    slt_num++;
    return;
}


/*
 *    OUTPUT A SLT NORMAL INSTRUCTION
 *
 *    An sltnormal instruction is output.  This goes straight into the
 *    main output file.
 */

static void
slt_normal()
{
    mach_op *op;
    area (ptext);
    op = make_int_data (crt_line_num);
    if (diag_format == DIAG_STAB) {
		mach_op *op1 = make_int_data (68);
		op1->of = make_int_data (0);
		op1->of->of = op;
		make_instr (m_stabd, op1, null, 0);
    } else {
		make_instr (m_dd_normal, op, null, 0);
    }
    area (plast);
    slt_num++;
    return;
}


/*
 *    OUTPUT A SLT EXIT INSTRUCTION
 *
 *    An sltexit instruction is output (new format only).
 */

void
slt_exit()
{
    mach_op *op;
    area (ptext);
    op = make_int_data (crt_line_num);
    make_instr (m_dd_exit, op, null, 0);
    area (plast);
    slt_num++;
    return;
}


/*
 *    OUTPUT A DNT BEGIN INSTRUCTION
 */

void
dnt_begin()
{
    if (diag_format == DIAG_STAB) {
		long lab = next_lab ();
		make_label (lab);
		push_dscope ((posn_t) lab, 0);
    } else {
		posn_t p = out_dd (diagfp2, xdb_begin, 1);
		push_dscope (p, 4);
		if (diag_format == DIAG_XDB_NEW) fprintf (diagfp2, "0,");
		fprintf (diagfp2, "%d\n", slt_num);
		slt_special (5, p);
    }
    return;
}


/*
 *    OUTPUT A DNT END INSTRUCTION
 */

int
dnt_end()
{
    dscope *d = pop_dscope ();
    if (d == null) return (0);
    if (diag_format == DIAG_STAB) {
		long lab1 = (long) d->posn;
		long lab2 = next_lab ();
		make_label (lab2);
		make_stabn (192, lab1);
		make_stabn (224, lab2);
    } else {
		posn_t p = out_dd (diagfp2, xdb_end, 1);
		if (diag_format == DIAG_XDB_NEW) {
			fprintf (diagfp2, "%d,0,", d->dscope_type);
		}
		fprintf (diagfp2, "%d,0x%x\n", slt_num,
				 (unsigned int) d->posn);
		slt_special (6, p);
    }
    return (1);
}


/*
 *    FLAG FOR MODULE NAME
 */

static bool have_module = 0;


/*
 *    DIAGNOSTICS FOR FILE NAME
 *
 *    This routine output the necessary instructions to indicate a change
 *    of source file.
 */

void
diag_source_file(char *nm, long ln)
{
    if (diag_format == DIAG_STAB) {
		int n = strlen (nm) + 3;
		char *qnm = alloc_nof (char, n);
		mach_op *op = make_extern_data ("Ltext", 0);
		sprintf (qnm, "\"%s\"", nm);
		make_stabs (qnm, (have_module ? 132 : 100), L0, op);
		if (!have_module) {
			make_external_label ("Ltext");
			init_stab_types ();
			have_module = 1;
		}
		crt_fname = nm;
		crt_line_num = ln;
    } else {
		posn_t x = out_dd (diagfp2, xdb_srcfile, 1);
		fprintf (diagfp2, "1,");
		diag_string (diagfp2, nm);
		fprintf (diagfp2, ",%d\n", slt_num);
		crt_fname = nm;
		crt_line_num = ln;
		make_instr (m_dd_align, null, null, 0);
		slt_special (1, x);
		if (!have_module) {
			x = out_dd (diagfp2, xdb_module, 1);
			if (diag_format == DIAG_XDB_NEW) {
				fprintf (diagfp2, "0,0");
			} else {
				diag_string (diagfp2, nm);
			}
			fprintf (diagfp2, ",%d\n", slt_num);
			push_dscope (x, 1);
			slt_special (2, x);
			have_module = 1;
		}
    }
    return;
}


/*
 *    DIAGNOSTICS FOR LINE NUMBER
 *
 *    This routine outputs an instruction indicating the position within
 *    the source file.
 */

void
diag_source(char *nm, long ln, int d)
{
    if (have_module && d == 0) return;
    if (!eq (nm, crt_fname)) diag_source_file (nm, ln);
    crt_line_num = ln;
    if (d) slt_normal ();
    return;
}


/*
 *    CURRENT DIAGNOSTICS PROCEDURE LABEL
 */

long crt_diag_proc_lab;


/*
 *    DIAGNOSTICS FOR A PROCEDURE
 */

void
diag_proc_main(diag_type dt, exp e, char *id,
			   int is_glob, char *val)
{
    exp a;
    posn_t t;
    long fp;
    table_posn *p;
    diag_type dtl;
	
    /* Analyse result sort */
    if (dt->key != DIAG_TYPE_PROC) {
		error ("Illegal procedure type");
		return;
    }
    dtl = dt->data.proc.result_type;
	
    if (diag_format == DIAG_STAB) {
		mach_op *op = make_extern_data (val, 0);
		char *st = analyse_stab_type (dtl, id, (is_glob ? "F" : "f"));
		make_stabs (st, 36, crt_line_num, op);
		dnt_begin ();
    } else {
		p = analyse_diag_type (diagfp2, dtl, 1);
		
		/* Create diagnostics procedure label */
		crt_diag_proc_lab = next_lab ();
		
		/* Output function diagnostic directive */
		t = out_dd (diagfp2, xdb_function, 1);
		fprintf (diagfp2, "%d,1,", is_glob);
		if (diag_format == DIAG_XDB_NEW) fprintf (diagfp2, "0,0,0,0,0,");
		diag_string (diagfp2, id);
		if (strcmp (id, "main") == 0) {
			fputc (',', diagfp2);
			diag_string (diagfp2, "_MAIN_");
			fputc (',', diagfp2);
		} else {
			fprintf (diagfp2, ",0,");
		}
		fp = ftell (diagfp2);
		fprintf (diagfp2, "%s,%d,%s,", NULL_POSN_STR, slt_num, val);
		out_posn (diagfp2, p, 1);
		if (diag_format == DIAG_XDB_NEW) fprintf (diagfp2, "%s,", val);
		fprintf (diagfp2, "L%ld\n", crt_diag_proc_lab);
		
		/* Start new diagnostic scope */
		push_dscope (t, 2);
		slt_special (3, t);
    }
	
    /* Step over actual procedure arguments */
    a = son (e);
    while (name (a) == ident_tag /* && isparam (a) */) {
		a = bro (son (a));
    }
	
    /* Read procedure argument definitions */
    while (name (a) == diagnose_tag) {
		diag_info *di = dno (a);
		if (di->key == DIAG_INFO_ID) {
			exp ps = di->data.id_scope.access;
			if (isparam (son (ps))) {
				diag_type pdt = di->data.id_scope.typ;
				char *pnm = di->data.id_scope.nme.ints.chars;
				long off = 8 + (no (ps) + no (son (ps))) / 8;
				if (diag_format == DIAG_STAB) {
					mach_op *op = make_int_data (off);
					char *st = analyse_stab_type (pdt, pnm, "p");
					make_stabs (st, 160, L0, op);
				} else {
					p = analyse_diag_type (diagfp2, pdt, 1);
					t = out_dd (diagfp2, xdb_fparam, 1);
					fill_gap (diagfp2, fp, t);
					if (diag_format == DIAG_XDB_NEW) {
						fprintf (diagfp2, "0,0,0,0,0,");
					} else {
						fprintf (diagfp2, "0,0,");
					}
					if (*pnm) {
						diag_string (diagfp2, pnm);
					} else {
						diag_string (diagfp2, "__unknown");
					}
					fprintf (diagfp2, ",%ld,", off);
					out_posn (diagfp2, p, 1);
					fp = ftell (diagfp2);
					if (diag_format == DIAG_XDB_NEW) {
						fprintf (diagfp2, "%s,0\n", NULL_POSN_STR);
					} else {
						fprintf (diagfp2, "%s\n", NULL_POSN_STR);
					}
				}
			}
		}
		a = son (a);
    }
    return;
}


/*
 *    DIAGNOSTICS FOR A GLOBAL IDENTIFIER
 */

void
diag_globl_variable(diag_type dt, char *id,
					int is_glob, char *val,
					int has_def)
{
    if (diag_format == DIAG_STAB) {
		if (is_glob) {
			char *st = analyse_stab_type (dt, id, "G");
			make_stabs (st, 32, crt_line_num, null);
		} else {
			mach_op *op = make_extern_data (val, 0);
			char *st = analyse_stab_type (dt, id, "S");
			make_stabs (st, 38, crt_line_num, op);
		}
    } else {
		int loc;
		FILE *file;
		table_posn *x;
		if (diag_format == DIAG_XDB_NEW) {
			loc = (is_glob ? 0 : 1);
			file = (is_glob ? diagfp3 : diagfp2);
		} else {
			loc = 1;
			file = diagfp2;
		}
		x = analyse_diag_type (file, dt, loc);
		(void) out_dd (file, xdb_svar, loc);
		if (diag_format == DIAG_XDB_NEW) {
			fprintf (file, "%d,0,0,0,0,", is_glob);
		} else {
			fprintf (file, "%d,0,", is_glob);
		}
		diag_string (file, id);
		if (has_def) {
			fprintf (file, ",%s,", val);
		} else {
			fprintf (file, ",-1,");
		}
		out_posn (file, x, 1);
		fprintf (file, "0,0\n");
    }
    return;
}


/*
 *    DIAGNOSTICS FOR A LOCAL IDENTIFIER
 */

void
diag_local_variable(diag_type dt, char *id,
					long fp)
{
    if (diag_format == DIAG_STAB) {
		mach_op *op = make_int_data (-fp);
		char *st = analyse_stab_type (dt, id, "l");
		make_stabs (st, 128, crt_line_num, op);
    } else {
		table_posn *x = analyse_diag_type (diagfp2, dt, 1);
		(void) out_dd (diagfp2, xdb_dvar, 1);
		if (diag_format == DIAG_XDB_NEW) {
			fprintf (diagfp2, "0,0,0,0,");
		} else {
			fprintf (diagfp2, "0,0,0,");
		}
		diag_string (diagfp2, id);
		fprintf (diagfp2, ",%ld,", -fp);
		if (diag_format == DIAG_XDB_NEW) {
			out_posn (diagfp2, x, 1);
			fprintf (diagfp2, "0\n");
		} else {
			out_posn (diagfp2, x, 0);
		}
    }
    return;
}


/*
 *    DIAGNOSTICS FOR A TYPE DEFINITION
 */

void
diag_type_defn(char *nm, diag_type dt)
{
    switch (dt->key) {
		
	case DIAG_TYPE_UNINIT :
	case DIAG_TYPE_INITED : {
	    /* Ignore unused types */
	    break;
	}
		
	default : {
	    if (diag_format == DIAG_STAB) {
			char *st = analyse_stab_type (dt, nm, "t");
			make_stabs (st, 128, L1, null);
	    } else {
			int loc = (diag_format == DIAG_XDB_NEW ? 0 : 1);
			FILE *file = (loc ? diagfp2 : diagfp3);
			table_posn *p = analyse_diag_type (file, dt, loc);
			(void) out_dd (file, xdb_typedef, loc);
			fprintf (file, "0,");
			diag_string (file, nm);
			fprintf (file, ",");
			out_posn (file, p, 0);
	    }
	    break;
	}
    }
    return;
}
