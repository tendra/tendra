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
 *Revision 1.1.1.1  1997/10/13 12:43:01  ma
 *First version.
 *
 *Revision 1.1.1.1  1997/03/14 07:50:22  ma
 *Imported from DRA
 
 * Revision 1.1.1.1  1996/09/20  10:57:01  john
 *
 * Revision 1.2  1996/07/05  14:31:36  john
 * Removed copyright message
 *
 * Revision 1.1  95/03/08  16:46:11  ra
 * Added missing files.
 *
 * Revision 1.3  94/02/21  16:08:10  16:08:10  ra (Robert Andrews)
 * Clear up a couple of long-int confusions.
 *
 * Revision 1.2  93/04/19  13:38:52  13:38:52  ra (Robert Andrews)
 * struct_fields and union_fields have been renamed diag_field.
 *
 * Revision 1.1  93/02/22  17:17:11  17:17:11  ra (Robert Andrews)
 * Initial revision
 *
 *--------------------------------------------------------------------------
 */


#include "config.h"
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
#include "stab_types.h"


/*
 *    CREATE A STABS INSTRUCTION
 */

void
make_stabs(char *s, int a, long b, mach_op *op)
{
    mach_op *p = make_extern_data (s, 0);
    p->of = make_int_data ((long) a);
    p->of->of = make_int_data (0);
    p->of->of->of = make_int_data (b);
    p->of->of->of->of = (op ? op : make_int_data (0));
    make_instr (m_stabs, p, null, 0);
    return;
}


/*
 *    CREATE A STABN INSTRUCTION
 */

void
make_stabn(int a, long lab)
{
    mach_op *p = make_int_data ((long) a);
    p->of = make_int_data (0);
    p->of->of = make_int_data (0);
    p->of->of->of = make_lab_data (lab, 0);
    make_instr (m_stabn, p, null, 0);
    return;
}


/*
 *    TYPE USED FOR BUILDING STAB TYPES
 */

#define TSIZE 100

typedef struct page_tag {
    int index;
    char text [ TSIZE ];
    struct page_tag *next;
} page;


/*
 *    LIST OF FREE PAGES
 */

static page *free_pages = null;


/*
 *    CREATE A NEW PAGE
 */

static page
*new_page()
{
    page *p = free_pages;
    if (p == null) {
		p = alloc_nof (page, 1);
    } else {
		free_pages = p->next;
    }
    p->index = 0;
    p->next = null;
    return (p);
}


/*
 *    ADD A STRING TO A PAGE
 */

static page
*sprint_string(page *p, char *s)
{
    int i = p->index;
    for (; *s ; s++) {
		if (i >= TSIZE) {
			p->index = TSIZE;
			p->next = new_page ();
			p = p->next;
			i = 0;
		}
		p->text [i] = *s;
		i++;
    }
    p->index = i;
    return (p);
}


/*
 *    ADD A NUMBER TO A PAGE
 */

static page
*sprint_number(page *p, long n)
{
    char buff [100];
    (void) sprintf (buff, "%ld", n);
    return (sprint_string (p, buff));
}


/*
 *    CREATE A NEW STAB TYPE
 */

static char
*new_stab_type(diag_type dt)
{
    static long next_stab_type = 16;
    char *res = alloc_nof (char, 8);
    sprintf (res, "%ld", next_stab_type++);
    if (dt) dt->been_outed = (OUTPUT_REC) res;
    return (res);
}


/*
 *    SIZE OF LAST TYPE ANALYSED
 */

static long last_type_sz = 0;


/*
 *    INDEX TO SIMPLE STAB TYPES
 */

#define STAB_SCHAR	0
#define STAB_UCHAR	1
#define STAB_SWORD	2
#define STAB_UWORD	3
#define STAB_SLONG	4
#define STAB_ULONG	5
#define STAB_FLOAT	6
#define STAB_DOUBLE	7
#define STAB_LDOUBLE	8
#define STAB_VOID	9
#define STAB_PTR	10
#define STAB_COMPLEX	-1


/*
 *    TABLE OF SIMPLE STAB TYPES
 */

static char *stab_tab [] = {
    "2", "11", "6", "8", "1", "4", "12", "13", "14", "15",
    null, null, null, null, null, null, null, null, null, null
};


/*
 *    TEST IF A TYPE IS SIMPLE
 */

static int
test_type(diag_type dt)
{
    switch (dt->key) {
		
	case DIAG_TYPE_FLOAT : {
	    shape sha = f_floating (dt->data.f_var);
	    last_type_sz = shape_size (sha);
	    if (name (sha) == shrealhd) return (STAB_FLOAT);
	    if (name (sha) == realhd) return (STAB_DOUBLE);
	    return (STAB_LDOUBLE);
	}
		
	case DIAG_TYPE_VARIETY : {
	    shape sha = f_integer (dt->data.var);
	    last_type_sz = shape_size (sha);
	    switch (name (sha)) {
		case scharhd : return (STAB_SCHAR);
		case swordhd : return (STAB_SWORD);
		case slonghd : return (STAB_SLONG);
		case ucharhd : return (STAB_UCHAR);
		case uwordhd : return (STAB_UWORD);
		case ulonghd : return (STAB_ULONG);
	    }
	    break;
	}
		
	case DIAG_TYPE_NULL : {
	    last_type_sz = 0;
	    return (STAB_VOID);
	}
		
	default : {
	    break;
	}
    }
    return (STAB_COMPLEX);
}


/*
 *    BUILD UP A STAB TYPE IN A BUFFER
 */

static page
*build_stab_type(diag_type dt, page *ptr)
{
    switch (dt->key) {
		
	case DIAG_TYPE_FLOAT :
	case DIAG_TYPE_NULL :
	case DIAG_TYPE_VARIETY : {
	    /* Simple types */
	    int t = test_type (dt);
	    ptr = sprint_string (ptr, stab_tab [t]);
	    break;
	}
		
	case DIAG_TYPE_ARRAY : {
	    diag_type dtl = dt->data.array.element_type;
	    long lo = no (dt->data.array.lower_b);
	    long hi = no (dt->data.array.upper_b);
	    char *stl = analyse_stab_type (dtl, null, null);
	    ptr = sprint_string (ptr, new_stab_type (dt));
	    ptr = sprint_string (ptr, "=ar1;");
	    ptr = sprint_number (ptr, lo);
	    ptr = sprint_string (ptr, ";");
	    ptr = sprint_number (ptr, hi);
	    ptr = sprint_string (ptr, ";");
	    ptr = sprint_string (ptr, stl);
	    last_type_sz *= (hi - lo + 1);
	    break;
	}
		
	case DIAG_TYPE_BITFIELD : {
	    long sz = dt->data.bitfield.no_of_bits.nat_val.small_nat;
	    ptr = sprint_string (ptr, "1");
	    last_type_sz = sz;
	    break;
	}
		
	case DIAG_TYPE_ENUM : {
	    /* Not yet supported */
	    ptr = sprint_string (ptr, "1");
	    last_type_sz = 32;
	    break;
	}
		
	case DIAG_TYPE_LOC : {
	    diag_type dtl = dt->data.loc.object;
	    ptr = build_stab_type (dtl, ptr);
	    break;
	}
		
	case DIAG_TYPE_PROC : {
	    diag_type dtl = dt->data.proc.result_type;
	    char *stl = analyse_stab_type (dtl, null, null);
	    ptr = sprint_string (ptr, new_stab_type (dt));
	    ptr = sprint_string (ptr, "=*");
	    ptr = sprint_string (ptr, new_stab_type (null));
	    ptr = sprint_string (ptr, "=f");
	    ptr = sprint_string (ptr, stl);
	    last_type_sz = 32;
	    break;
	}
		
	case DIAG_TYPE_PTR : {
	    diag_type dtl = dt->data.ptr.object;
	    int t = test_type (dtl);
	    if (t != STAB_COMPLEX) {
			char *st = stab_tab [ STAB_PTR + t ];
			if (st) {
				ptr = sprint_string (ptr, st);
			} else {
				st = new_stab_type (null);
				stab_tab [ STAB_PTR + t ] = st;
				ptr = sprint_string (ptr, st);
				ptr = sprint_string (ptr, "=*");
				ptr = sprint_string (ptr, stab_tab [t]);
			}
	    } else {
			char *stl = analyse_stab_type (dtl, null, null);
			ptr = sprint_string (ptr, new_stab_type (dt));
			ptr = sprint_string (ptr, "=*");
			ptr = sprint_string (ptr, stl);
	    }
	    last_type_sz = 32;
	    break;
	}
		
	case DIAG_TYPE_STRUCT : {
	    char *nm = dt->data.t_struct.nme.ints.chars;
	    if (*nm) {
			char *res;
			dt->data.t_struct.nme.ints.chars = "";
			res = analyse_stab_type (dt, nm, "T");
			dt->data.t_struct.nme.ints.chars = nm;
			make_stabs (res, 128, L0, null);
			res = (char *) dt->been_outed;
			ptr = sprint_string (ptr, res);
	    } else {
			shape sha = dt->data.t_struct.tdf_shape;
			long sz = shape_size (sha);
#if 0
			struct_fields *fld = dt->data.t_struct.fields->array;
#else
			diag_field *fld = dt->data.t_struct.fields->array;
#endif
			long i, n = (long) dt->data.t_struct.fields->lastused;
			
			ptr = sprint_string (ptr, new_stab_type (dt));
			ptr = sprint_string (ptr, "=s");
			ptr = sprint_number (ptr, sz / 8);
			
			/* Deal with structure fields */
			for (i = n - 1 ; i >= 0 ; i--) {
				char *fnm = fld [i]->field_name.ints.chars;
				long off = no (fld [i]->where);
				diag_type dtl = fld [i]->field_type;
				char *q = analyse_stab_type (dtl, null, null);
				ptr = sprint_string (ptr, fnm);
				ptr = sprint_string (ptr, ":");
				ptr = sprint_string (ptr, q);
				ptr = sprint_string (ptr, ",");
				ptr = sprint_number (ptr, off);
				ptr = sprint_string (ptr, ",");
				ptr = sprint_number (ptr, last_type_sz);
				ptr = sprint_string (ptr, ";");
			}
			ptr = sprint_string (ptr, ";");
			last_type_sz = sz;
	    }
	    break;
	}
		
	case DIAG_TYPE_UNION : {
	    char *nm = dt->data.t_union.nme.ints.chars;
	    if (*nm) {
			char *res;
			dt->data.t_struct.nme.ints.chars = "";
			res = analyse_stab_type (dt, nm, "T");
			dt->data.t_struct.nme.ints.chars = nm;
			make_stabs (res, 128, L0, null);
			res = (char *) dt->been_outed;
			ptr = sprint_string (ptr, res);
	    } else {
			shape sha = dt->data.t_union.tdf_shape;
			long sz = shape_size (sha);
#if 0
			union_fields *fld = dt->data.t_union.fields->array;
#else
			diag_field *fld = dt->data.t_union.fields->array;
#endif
			long i, n = (long) dt->data.t_union.fields->lastused;
			
			ptr = sprint_string (ptr, new_stab_type (dt));
			ptr = sprint_string (ptr, "=u");
			ptr = sprint_number (ptr, sz / 8);
			
			/* Deal with union fields */
			for (i = n - 1 ; i >= 0 ; i--) {
				char *fnm = fld [i]->field_name.ints.chars;
				diag_type dtl = fld [i]->field_type;
				char *q = analyse_stab_type (dtl, null, null);
				ptr = sprint_string (ptr, fnm);
				ptr = sprint_string (ptr, ":");
				ptr = sprint_string (ptr, q);
				ptr = sprint_string (ptr, ",0,");
				ptr = sprint_number (ptr, last_type_sz);
				ptr = sprint_string (ptr, ";");
			}
			ptr = sprint_string (ptr, ";");
			last_type_sz = sz;
	    }
	    break;
	}
		
	default : {
	    ptr = sprint_string (ptr, "15");
	    last_type_sz = 0;
	    break;
	}
    }
    return (ptr);
}


/*
 *    FIND A STAB TYPE
 */

char
*analyse_stab_type(diag_type dt, char *nm,
				   char *cl)
{
    int n = 0;
    page *ptr, *p;
    char *res = (char *) dt->been_outed;
    if (res && nm == null && cl == null) return (res);
    p = ptr = new_page ();
    if (nm) {
		p = sprint_string (p, "\"");
		p = sprint_string (p, nm);
    }
    if (cl) {
		p = sprint_string (p, ":");
		p = sprint_string (p, cl);
    }
    if (res) {
		p = sprint_string (p, res);
    } else {
		p = build_stab_type (dt, p);
    }
    if (nm) p = sprint_string (p, "\"");
	
    /* Copy accumulated string */
    for (p = ptr ; p ; p = p->next) n += p->index;
    res = alloc_nof (char, n + 1);
    n = 0;
    for (p = ptr ; p ; p = p->next) {
		strncpy (res + n, p->text, p->index);
		n += p->index;
    }
    res [n] = 0;
	
    /* Free pages */
    p =  ptr;
    while (p->next) p = p->next;
    p->next = free_pages;
    free_pages = ptr;
    return (res);
}


/*
 *    INITIALIZE BASIC STAB TYPES
 */

void
init_stab_types()
{
    static char *stab_types [] = {
		"\"int:t1=r1;-2147483648;2147483647;\"",
		"\"char:t2=r2;0;127;\"",
		"\"long int:t3=r1;-2147483648;2147483647;\"",
		"\"unsigned int:t4=r1;0;-1;\"",
		"\"long unsigned int:t5=r1;0;-1;\"",
		"\"short int:t6=r1;-32768;32767;\"",
		"\"long long int:t7=r1;0;-1;\"",
		"\"short unsigned int:t8=r1;0;65535;\"",
		"\"long long unsigned int:t9=r1;0;-1;\"",
		"\"signed char:t10=r1;-128;127;\"",
		"\"unsigned char:t11=r1;0;255;\"",
		"\"float:t12=r1;4;0;\"",
		"\"double:t13=r1;8;0;\"",
		"\"long double:t14=r1;8;0;\"",
		"\"void:t15=15\""
    };
    int i;
    for (i = 0 ; i < 15 ; i++) {
		make_stabs (stab_types [i], 128, L0, null);
    }
    return;
}
