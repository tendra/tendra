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
 * Revision 1.4  1998/03/15  16:00:32  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.3  1998/03/11  11:03:37  pwe
 * DWARF optimisation info
 *
 * Revision 1.2  1998/01/21  10:30:04  pwe
 * labdiff change
 *
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.11  1997/12/08  16:36:59  pwe
 * abbrev key & directory names
 *
 * Revision 1.10  1997/12/04  19:41:10  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.9  1997/11/06  09:21:57  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.8  1997/10/23  09:27:23  pwe
 * ANDF-DE v1.7, extra diags
 *
 * Revision 1.7  1997/10/10  18:18:19  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.6  1997/08/23  13:36:31  pwe
 * initial ANDF-DE
 *
 * Revision 1.5  1997/05/13  08:02:25  pwe
 * Signed LEB128 corrected
 *
 * Revision 1.4  1997/04/17  11:50:11  pwe
 * Sparc and 80x86 support
 *
 * Revision 1.3  1997/04/01  17:19:33  pwe
 * diagnose pl_tests and locate -> platform specific
 *
 * Revision 1.2  1997/03/24  11:10:17  pwe
 * struct bitfields
 *
 * Revision 1.1  1997/03/20  16:08:59  pwe
 * first version
 *
 **********************************************************************/

#include "config.h"
#include "common_types.h"
#include "dw2_config.h"
#include "dw2_basic.h"
#include "dw2_codes.h"
#include "dw2_iface.h"
#include "szs_als.h"
#include "expmacs.h"
#include "tags.h"
#include "basicread.h"
#include "dw2_abbrev_vn.h"


#define entry_names_wanted
#include "dw2_entries.h"
#undef entry_names_wanted


static char * sep = ", ";


void
uleb128(unsigned long value)
{
	int byt;
	for (;;) {
		byt = value & 127;
		value >>= 7;
		if (value == 0) {
			outn ((long)byt);
			return;
		}
		outn ((long)byt | 128);
		outs (sep);
	}
}

int
uleb128_length(unsigned long value)
{
	int op = 1;
	for (;;) {
		value >>= 7;
		if (value == 0) {
			return op;
		}
		op++;
	}
}

void
sleb128(long value)
{
	int negative = (value < 0);
	int byt;
	for (;;) {
		byt = (unsigned long) value & 127;
		value >>= 7;
		if (negative)
			/* sign extend, since C doesn't imply arithmetic shift */
			value |= - (1 << ((sizeof(value)*8) - 7));
		/* sign bit of byte is 2nd high order bit (0x40) */
		if (value == - (long) ((byt & 0x40) != 0)) {
			outn ((long)byt);
			return;
		}
		outn ((long)byt | 128);
		outs (sep);
	};
}

int
sleb128_length(long value)
{
	int op = 1;
	int negative = (value < 0);
	int byt;
	for (;;) {
		byt = (unsigned long) value & 127;
		value >>= 7;
		if (negative)
			/* sign extend, since C doesn't imply arithmetic shift */
			value |= - (1 << ((sizeof(value)*8) - 7));
		if (value == - (long) ((byt & 0x40) != 0)) {
			return op;
		}
		op++;
	};
}

void
set_attribute(int nm, int form)
{
	out8 (); uleb128 ((unsigned long)nm);
	if (form || !nm) {
		outs (sep); uleb128 ((unsigned long) form);
	}
	d_outnl ();
	return;
}

static long info_end;
static long pubnames_end;
static long aranges_end;


void
do_compunit_header()
{
	info_end = next_dwarf_label ();
	pubnames_end = next_dwarf_label ();
	aranges_end = next_dwarf_label ();
	enter_section ("debug_info");
	out_dwf_label (dw_info_start, 1);
	outnl_comment("Compilation Unit Header");
	out32 (); out_dwf_dist_to_label (info_end); d_outnl ();
	out16 (); outn ((long)DWARF_MOD_VERSION); d_outnl ();
	out32 (); outs (abbrev_name); d_outnl ();
	out8 (); outn ((long)PTR_SZ/8); d_outnl ();
	exit_section ();
	enter_section ("debug_pubnames");
	out32 (); out_dwf_dist_to_label (pubnames_end); d_outnl ();
	out16 (); outn ((long)DWARF_MOD_VERSION); d_outnl ();
	out32 (); out_dwf_label (dw_info_start, 0); d_outnl ();
	out32 (); out_dwf_labdiff (dw_info_start, info_end); d_outnl ();
	exit_section ();
	enter_section ("debug_aranges");
	out32 (); out_dwf_dist_to_label (aranges_end); d_outnl ();
	out16 (); outn ((long)DWARF_MOD_VERSION); d_outnl ();
	out32 (); out_dwf_label (dw_info_start, 0); d_outnl ();
	out8 (); outn ((long)PTR_SZ/8); d_outnl ();
	out8 (); outn ((long)0); d_outnl ();
	dot_align (PTR_SZ/4);
	exit_section ();
	return;
}

void
close_compunit_info()
{
	enter_section ("debug_info");
	out_dwf_label (info_end, 1);
#ifdef NEEDS_DEBUG_ALIGN
	dot_align (4);
#endif
	exit_section ();
	enter_section ("debug_pubnames");
	out32 (); outn ((long)0); d_outnl ();
	out_dwf_label (pubnames_end, 1);
#ifdef NEEDS_DEBUG_ALIGN
	dot_align (4);
#endif
	exit_section ();
	enter_section ("debug_aranges");
	out32 (); outn ((long)0); d_outnl ();
	out32 (); outn ((long)0); d_outnl ();
	out_dwf_label (aranges_end, 1);
	exit_section ();
}


void
dw_sibling_end()
{
	out8 (); uleb128 ((unsigned long)0); 
	outnl_comment ("sibling end");
	return;
}

void
dw_at_address(long lab)
{
	out32 (); out_dwf_label (lab, 0); d_outnl ();
	return;
}

void
dw_at_ext_lab(ext_lab lab)
{
	out32 ();
	switch (lab.k) {
    case LAB_STR:
		outs (lab.u.s);
		break;
    case LAB_CODE:
		out_code_label (lab.u.l);
		break;
    case LAB_D:
		out_dwf_label (lab.u.l, 0);
		break;
    default:
		failer ("unset label");
	}
	d_outnl ();
	return;
}

void
dw_set_ext_lab(ext_lab lab)
{
	switch (lab.k) {
    case LAB_STR:
		out_ext_label (lab.u.s);
		break;
    case LAB_D:
		out_dwf_label (lab.u.l, 1);
		break;
    default:
		failer ("unexpected set label");
	}
	return;
}

void
dw_at_ext_address(dg_tag dt)
{
	if (dt->outref.k == NO_LAB) {
		dt->outref.k = LAB_D;
		dt->outref.u.l = next_dwarf_label ();
	}
	dw_at_ext_lab (dt->outref);
	return;
}

void
set_ext_address(dg_tag dt)
{
	if (dt->outref.k == NO_LAB) {
		dt->outref.k = LAB_D;
		dt->outref.u.l = next_dwarf_label ();
	}
	dw_set_ext_lab (dt->outref);
	return;
}

void
dw_at_abstract_lab(dg_tag dt)
{
	if (!dt->abstract_lab)
		dt->abstract_lab = next_dwarf_label ();
	out32 ();
	out_dwf_label (dt->abstract_lab, 0);
	d_outnl ();
	return;
}

void
set_abstract_lab(dg_tag dt)
{
	if (!dt->abstract_lab)
		dt->abstract_lab = next_dwarf_label ();
	out_dwf_label (dt->abstract_lab, 1);
	return;
}

void
dw_at_string(char* s)
{
	if (!s) s = "";
	out_string (s);
	return;
}

void
dw_at_form(int f)
{
	out8 ();
	uleb128 ((unsigned long)f);
	return;
}

void
dw_at_data(int n, long d)
{
	switch (n) {
    case 1: {
		out8 ();
		break;
    }
    case 2: {
		out16 ();
		break;
    }
    case 4: {
		out32 ();
		break;
    }
    default:
		failer ("dwarf data size not supported");
	}
	outn (d); d_outnl ();
	return;
}

void
dw_at_udata(unsigned long n)
{
	out8 (); uleb128 (n); d_outnl ();
	return;
}

void
dw_at_sdata(long n)
{
	out8 (); sleb128 (n); d_outnl ();
	return;
}

void
dw_at_flag(int x)
{
	out8 (); outn ((long)x); d_outnl ();
	return;
}

void
dw_at_decl(short_sourcepos p)
{
	out8 (); uleb128 ((unsigned long)(p.file ? p.file->index : 0));
	outs(sep); uleb128 ((unsigned long)p.line);
	outs(sep); uleb128 ((unsigned long)p.column);
	d_outnl ();
	return;
}

void
dw_no_locate()
{
	out8 (); outn ((long)0);
	outnl_comment ("discarded variable");
	return;
}

void
dw_locate_offset(int n)
{
	out8(); outn ((long)(1 + uleb128_length((unsigned long)n))); outs(sep);
	outn ((long)DW_OP_plus_uconst); outs (sep);
	uleb128 ((unsigned long)n); d_outnl ();
	return;
}

static char* bad_refloc = "unimplemented relative location";

static int
refloc_length(exp e, exp id)
{
	switch (name(e)) {
    case name_tag: {
		if (son(e) != id)
			failer (bad_refloc);
		if (no(e) == 0)
			return (0);
		return (1 + uleb128_length((unsigned long)no(e)/8));
    }
    case cont_tag: {
		return (refloc_length (son(e), id) + 1);
    }
    case reff_tag: {
		if (no(e)<0)
			failer (bad_refloc);
		return (refloc_length (son(e), id) + 1 +
				uleb128_length((unsigned long)no(e)/8));
    }
    default: {
		failer (bad_refloc);
		return (0);
    }
	}
}

static void
out_refloc(exp e, exp id)
{
	switch (name(e)) {
    case name_tag: {
		if (son(e) != id)
			failer (bad_refloc);
		outs (sep); outn ((long)DW_OP_plus_uconst);
		outs (sep); uleb128 ((unsigned long)no(e)/8);
		return;
    }
    case cont_tag: {
		out_refloc (son(e), id);
		outs (sep); outn ((long)DW_OP_deref);
		return;
    }
    case reff_tag: {
		if (no(e)<0)
			failer (bad_refloc);
		out_refloc (son(e), id);
		outs (sep); outn ((long)DW_OP_plus_uconst);
		outs (sep); uleb128 ((unsigned long)no(e)/8);
		return;
    }
    default:
		failer (bad_refloc);
	}
}

void
dw_locate_reloffset(exp e)
{
	int length;
	if (name(e) != ident_tag) {
		failer (bad_refloc);
		return;
	}
	length = refloc_length (bro(son(e)), e);
	out8();
	if (length == 0) {
		outn ((long)1);
		outs(sep); outn ((long)DW_OP_nop);
	}
	else {
		outn ((long)length);
		out_refloc (bro(son(e)), e);
	}
	d_outnl ();
	return;
}

void
dw_at_distance(long lo, long hi)
{
	out16 (); out_dwf_labdiff (lo, hi); d_outnl ();
	return;
}

long last_text_label = 0;

long
set_dw_text_label()
{
	if (any_output) {
		last_text_label = next_dwarf_label ();
		out_dwf_label (last_text_label, 1);
		reset_any_output;
	}
	return last_text_label;
}

void
out_text_label(long n)
{
	out_dwf_label (n, 1);
	last_text_label = n;
	return;
}

void
out_loc_range(long start, long end, int inclusive)
{
	/* for location list */
	out32 (); out_dwf_labdiff (dw_text_start, start); d_outnl ();
	out32 (); out_dwf_labdiff (dw_text_start, end);
	if (inclusive) {
		outs (" + ");
		outn ((long)min_instr_size);
	}
	d_outnl ();
	return;
}
