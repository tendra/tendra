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


/* 80x86/trans.c */

/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$
 *$Log$
 *Revision 1.2  2002/11/21 22:31:02  nonce
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
 * Revision 1.4  1998/03/11  11:03:06  pwe
 * DWARF optimisation info
 *
 * Revision 1.3  1998/02/06  17:04:21  release
 * Last minute pre-release polishing.
 *
 * Revision 1.2  1998/01/21  10:30:01  pwe
 * labdiff change
 *
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.14  1997/12/05  10:32:38  pwe
 * system identification
 *
 * Revision 1.13  1997/10/23  09:37:15  pwe
 * extra_diags
 *
 * Revision 1.12  1997/10/10  18:25:33  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.11  1997/08/23  13:45:46  pwe
 * initial ANDF-DE
 *
 * Revision 1.10  1997/06/02  08:36:00  pwe
 * diags visibility
 *
 * Revision 1.9  1997/03/24  11:15:36  pwe
 * dwarf2 option/default
 *
 * Revision 1.8  1997/03/20  16:24:10  pwe
 * dwarf2
 *
 * Revision 1.7  1996/12/13  14:39:36  pwe
 * prep NEWDIAGS
 *
 * Revision 1.6  1996/02/16  10:10:44  pwe
 * Linux/ELF struct result and PIC jump table
 *
 * Revision 1.5  1996/02/08  13:45:15  pwe
 * Linux elf v aout option
 *
 * Revision 1.4  1995/03/16  09:13:35  pwe
 * sco_gas now install time option
 *
 * Revision 1.3  1995/02/17  13:21:17  pwe
 * rationalise compilation info
 *
 * Revision 1.2  1995/01/30  12:56:56  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.2  1994/07/13  07:39:57  jmf
 * Remove prefix initialising, do it in machine.c
 *
 * Revision 1.1  1994/07/12  14:42:47  jmf
 * Initial revision
 *
 **********************************************************************/


#include "config.h"
#include "release.h"
#include "common_types.h"
#include "basicread.h"
#include "flags.h"
#include "out.h"
#include "main_reads.h"
#include "flpt.h"
#include "externs.h"
#include "weights.h"
#include "installglob.h"
#include "instr.h"
#include "machine.h"
#include "exp.h"
#include "expmacs.h"
#include "instr386.h"
#include "localflags.h"
#include "messages_8.h"
#include "diag_fns.h"
#include "readglob.h"
#include "assembler.h"
#include "target_v.h"
#include "system_v.h"
#include "reader_v.h"
#include "construct_v.h"
#include "operand.h"
#ifdef NEWDIAGS
#include "diag_v.h"
#include "dg_version.h"
#endif
#ifdef NEWDWARF
#include "dw2_iface.h"
#include "dw2_vsn.h"
#include "dw2_abbrev.h"
#include "dw2_common.h"
static bool dump_abbrev = 0;
#endif

#if DWARF
#include "dwarf_mc.h"
#endif

extern int print_inlines;

/* PROCEDURES */

static void
init_all()
{
	init_flpt();
#include "inits.h"
	good_trans = 0;
	capsule_freelist = (capsule_frees*)0;
	old_proc_props = (proc_props *)0;
	
/* 80x86 specific */
	extra_stack = 0;
	top_def = (dec*)0;
	init_weights();
	initzeros ();
	const_list = nilexp;
	return;
}

int
main(int argc, char **argv)
{
	int i;
	char *outfname;
	
	/* defaults */
	do_inlining = 1;		/* inline */
	redo_structfns = 1;		/* replace fns delivering structs */
	redo_structparams = 0;	/* no change to struct params */
	is80486 = 1;			/* (at least) 80486 */
	is80586 = 1;			/* Pentium */
	separate_units = 0;		/* combine units */
	do_foralls = 1;		/* do forall optimisations */
	extra_checks = 1;		/* perform the extra checks */
	always_use_frame = 0;		/* avoid using frame pointer */
	do_loopconsts = 1;		/* extract constants from loops */
	diagnose = 0;			/* diagnostics off */
#ifdef NEWDIAGS
	diag_visible = 0;
	extra_diags = 0;
#endif
#ifdef NEWDWARF
	dwarf2 = 0;
#endif
	do_profile = 0;		/* no profiling code */
	writable_strings = 0;		/* strings are read only */
	PIC_code = 0;			/* do not produce PIC code */
	all_variables_visible = 0;	/* use registers */
	do_alloca = 1;		/* inline calls of alloca */
	round_after_flop = 0;		/* do not round after each floating point
								 *				   operation */
	strict_fl_div = 1;		/* do not replace divisions by
							 *				   multiplication by the inverse */
	flpt_const_overflow_fail = 1;	/* constant floating point arithmetic
									 *				   fails installation, if overflow */
	flpt_always_comparable = 0;	/* this is the default for SVR4.2 */
	report_versions = 0;		/* do not print version numbers */
	permit_8byte_align = 1;	/* allow 8byte alignment for local doubles
							 */
	do_unroll = 1;		/* perform loop unrolling */
	replace_arith_type = 1;	/* use the C definitions of promote etc.
							 */
	indirect_jumps = 1;		/* follow gotos and tests to final dest */
	no_bss = 0;			/* use .comm */
	
	
	ptr_null = 0;			/* null value for pointer */
	proc_null = 0;		/* null value for proc */
	lv_null = 0;			/* null value for label_value*/
	
	
	for (i = 1; i != argc && argv[i][0] == '-'; ++i) {/* read flags */
		char *s = argv[i];
		
		switch (s[1]) {
		case 'A':
			do_alloca = (s[2] == '1');
			break;
		case 'B':
			flpt_const_overflow_fail = (s[2] == '1');
			break;
		case 'C':
			do_loopconsts = (s[2] == '1');
			break;
		case 'D':
			PIC_code = (s[2] == '1');
			break;
		case 'E':
			extra_checks = 0;
			break;
		case 'F':
			do_foralls = (s[2] == '1');
			break;
		case 'G':
			gcc_compatible = (s[2] == '1');
			break;
		case 'H':
			diagnose = 1;
#ifdef NEWDIAGS
			if (s[2] != 'O')
#endif
			{
#ifdef NEWDIAGS
				diag_visible = 1;
#endif
				always_use_frame = 1;
				do_inlining = 0;
				do_loopconsts = 0;
				do_foralls = 0;
				all_variables_visible = 1;
			}
			break;
		case 'I':
			do_inlining = (s[2] == '1');
			break;
#ifdef NEWDWARF
		case 'J':
			diagnose = 1;
			extra_diags = 1;
			dwarf2 = 1;
			break;
#endif
		case 'K':
			if (s[2] == '3')
			{
				is80486 = 0;
				is80586 = 0;
			};
			if (s[2] == '4')
			{
				is80486 = 1;
				is80586 = 0;
			};
			if (s[2] == '5')
			{
				is80486 = 1;
				is80586 = 1;
			};
			break;
		case 'M':
			strict_fl_div = (s[2] == '1');
			break;
		case 'N':
			do_prom = 1;
			break;
		case 'P':
			do_profile = 1;
			break;
		case 'Q':
			return 0;
		case 'R':
			round_after_flop = (s[2] == '1');
			break;
#ifdef NEWDWARF
		case 'T':
			dump_abbrev = 1;
			diagnose = 1;
			extra_diags = 1;
			dwarf2 = 1;
			break;
#endif
		case 'U':
			do_unroll = (s[2] == '1');
			break;
		case 'V':
			IGNORE fprintf(stderr, "DERA ANDF 80x86/Pentium translator (TDF version %d.%d)\n",
						   MAJOR_VERSION, MINOR_VERSION);
			IGNORE fprintf(stderr, "reader %d.%d: ", reader_version,
						   reader_revision);
			IGNORE fprintf(stderr, "construct %d.%d: ", construct_version,
						   construct_revision);
			IGNORE fprintf(stderr, "target %d.%d: ", target_version,
						   target_revision);
#if DWARF
			IGNORE fprintf(stderr, "dwarf1 %d.%d: ", DWARF_MAJOR,
						   DWARF_MINOR);
#endif
#ifdef NEWDIAGS
			IGNORE fprintf(stderr, "diag_info %d.%d:\n%s   ", diag_version,
						   diag_revision, DG_VERSION);
#endif
#ifdef NEWDWARF
			IGNORE fprintf(stderr, "dwarf2 %d.%d: ", DWARF2_MAJOR,
						   DWARF2_MINOR);
#endif
			IGNORE fprintf(stderr, "\n");
			IGNORE fprintf(stderr, "system %s: ", target_system);
#ifdef __DATE__
			IGNORE fprintf(stderr, "installer compilation %s", __DATE__);
#endif
			IGNORE fprintf(stderr, "\n");
#ifdef RELEASE
			IGNORE fprintf(stderr, "release: %s\n",RELEASE);
#endif
			break;
		case 'W':
			writable_strings = (s[2] == '1');
			break;
		case 'X':
			do_unroll = 0;
			do_inlining = 0;
			do_loopconsts = 0;
			do_special_fns = 0;
			do_foralls = 0;
			indirect_jumps = 0;
			all_variables_visible = 1;
			break;
		case 'Z':
			report_versions = 1;
			break;
			
		case 'a':
			always_use_frame = 1;
			break;
		case 'b':
			all_variables_visible = 1;
			break;
		case 'c':
			replace_arith_type = 0;
			break;
		case 'd':
			redo_structfns = 0;
			break;
		case 'e':
			indirect_jumps = 0;
			break;
		case 'f':
			ptr_null = 0x55555555;		/* null value for pointer */
			break;
		case 'g':
			flpt_always_comparable = 1;
			break;
		case 'h':
			no_bss = 1;
			break;
		case 'i':
			print_inlines = 1;
			break;
#if islinux
		case 'k':
			set_linux_format (s[2] == '1');
			break;
#endif
#if issco
		case 's':
			sco_gas = 1;
			break;
#endif
			
		default:
			failer (BAD_FLAG);
			break;
		};
	};
	
#if islinux
	if (gcc_compatible < 0)
		gcc_compatible = ! linux_elf;
#endif
	
	if (i == argc)
		i--;	/* BAD_COMMAND1 */
	
	for (; i < argc ; i += 2) {
		if (i == (argc-1))
		{
			failer (BAD_COMMAND1);
			return (1);
		};
		
		
		outfname = argv[i+1];
		
		/* initiate the output file */
		if (!outinit (outfname)) {
			failer (CANT_OPEN);
			return (1);
		};
		
		if (!initreader (argv[i])) {
			failer (CANT_READ);
			return (1);
		};
		
		init_all();
		
#ifdef NEWDWARF
		if (dwarf2) {
			init_dwarf2 ();
		} else
#endif
			if (diagnose) out_diagnose_prelude();
		
#ifdef NEWDWARF
		if (dump_abbrev) {
			outs (".text\n");
			do_abbreviations ();
			dwarf2_prelude ();
			make_dwarf_common ();
			dwarf2_postlude ();
		} else
#endif
			
			IGNORE d_capsule();
		
		while (weak_list)
		{
			outs(".set ");
			outs(weak_list -> weak_id);
			outs(",");
			outs(weak_list -> val_id);
			outnl();
			weak_list = weak_list -> next;
		};
		
#ifdef NEWDWARF
		if (dwarf2) {
			end_dwarf2 ();
		} else
#endif
			if (diagnose) out_diagnose_postlude();
		
		outend ();			/* close the .s file */
		endreader();
		
		if (good_trans)
			exit(EXIT_FAILURE);
	}
	return 0;
}
