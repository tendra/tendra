/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

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
#include "reader_v.h"
#include "construct_v.h"
#include "operand.h"
#ifdef NEWDIAGS
#include "diag_v.h"
#include "dg_version.h"
#endif /* NEWDIAGS */
#ifdef NEWDWARF
#include "dw2_iface.h"
#include "dw2_vsn.h"
#include "dw2_abbrev.h"
#include "dw2_common.h"
static bool dump_abbrev = 0;
#endif /* NEWDWARF */

#if DWARF
#include "dwarf_mc.h"
#endif

static void init_all(void);
static void print_version(void);

extern int print_inlines;

static void
init_all(void)
{
	init_flpt();
#include "inits.h" /* XXX: not nice */
	good_trans = 0;
	capsule_freelist = NULL;
	old_proc_props = NULL;

	/* 80x86 specific */
	extra_stack = 0;
	top_def = NULL;
	init_weights();
	initzeros();
	const_list = nilexp;
}

int
main(int argc, char **argv)
{
	int ch;
	char *outfname;
	const char *optstring;

	extern char *optarg;
	extern int optind;

	/*
	 * defaults
	 */
	do_inlining = 1;	/* inline */
	redo_structfns = 1;	/* replace fns delivering structs */
	redo_structparams = 0;	/* no change to struct params */
	is80486 = 1;		/* (at least) 80486 */
	is80586 = 1;		/* Pentium */
	separate_units = 0;	/* combine units */
	do_foralls = 1;		/* do forall optimisations */
	extra_checks = 1;	/* perform the extra checks */
	always_use_frame = 0;	/* avoid using frame pointer */
	do_loopconsts = 1;	/* extract constants from loops */
	diagnose = 0;		/* diagnostics off */
#ifdef NEWDIAGS
	diag_visible = 0;
	extra_diags = 0;
#endif /* NEWDIAGS */
#ifdef NEWDWARF
	dwarf2 = 0;
#endif /* NEWDWARF */
	do_profile = 0;		/* no profiling code */
	writable_strings = 0;	/* strings are read only */
	PIC_code = 0;		/* do not produce PIC code */
	all_variables_visible = 0; /* use registers */
	do_alloca = 1;		/* inline calls of alloca */
	round_after_flop = 0;	/* do not round after each floating point
				   operation */
	/* do not replace divisions by multiplication by the inverse */
	strict_fl_div = 1;
	/* constant floating point arithmetic fails installation, if overflow */
	flpt_const_overflow_fail = 1;
	flpt_always_comparable = 0; /* this is the default for SVR4.2 */
	report_versions = 0;	/* do not print version numbers */
	permit_8byte_align = 1;	/* allow 8byte alignment for local doubles */
	do_unroll = 1;		/* perform loop unrolling */
	replace_arith_type = 1;	/* use the C definitions of promote etc. */
	indirect_jumps = 1;	/* follow gotos and tests to final dest */
	no_bss = 0;		/* use .comm */


	ptr_null = 0;		/* null value for pointer */
	proc_null = 0;		/* null value for proc */
	lv_null = 0;		/* null value for label_value*/

	/*
	 * When using NEWDIAGS, -H takes an undocumented argument.
	 */
#ifdef NEWDIAGS
#define DEBUG_OPTSTRING "H:"
#else
#define DEBUG_OPTSTRING "H"
#endif

	/*
	 * XXX: Some arguments are undocumented in trans.1, check
	 */
#ifdef NEWDWARF
	optstring = "A:B:C:D:EF:G:" DEBUG_OPTSTRING "I:" "J" "K:M:NPQR:" "T" \
	    "U:VW:XZabcdefghik:s";
#else
	optstring = "A:B:C:D:EF:G:" DEBUG_OPTSTRING "I:"     "K:M:NPQR:" \
	    "U:VW:XZabcdefghik:s";
#endif

#undef DEBUG_OPTSTRING

	while ((ch = getopt(argc, argv, optstring)) != -1) {
		switch (ch) {
		case 'A':
			do_alloca = (*optarg == '1');
			break;
		case 'B':
			flpt_const_overflow_fail = (*optarg == '1');
			break;
		case 'C':
			do_loopconsts = (*optarg == '1');
			break;
		case 'D':
			PIC_code = (*optarg == '1');
			break;
		case 'E':
			extra_checks = 0;
			break;
		case 'F':
			do_foralls = (*optarg == '1');
			break;
		case 'G':
			gcc_compatible = (*optarg == '1');
			break;
		case 'H':
			/* XXX: takes an undocumented optarg */
			diagnose = 1;
#ifdef NEWDIAGS
			if (*optarg != 'O') {
				/*
				 * XXX: why Oh and not zero?
				 * kate suggested that O stands for optimised
				 */
				diag_visible = 1;
				always_use_frame = 1;
				do_inlining = 0;
				do_loopconsts = 0;
				do_foralls = 0;
				all_variables_visible = 1;
			}
#else
			always_use_frame = 1;
			do_inlining = 0;
			do_loopconsts = 0;
			do_foralls = 0;
			all_variables_visible = 1;
#endif /* NEWDIAGS */
			break;
		case 'I':
			do_inlining = (*optarg == '1');
			break;
#ifdef NEWDWARF
		case 'J':
			diagnose = 1;
			extra_diags = 1;
			dwarf2 = 1;
			break;
#endif
		case 'K':
			switch (*optarg) {
			case '3':
				is80486 = 0;
				is80586 = 0;
				break;
			case '4':
				is80486 = 1;
				is80586 = 0;
				break;
			case '5':
				is80486 = 1;
				is80586 = 1;
				break;
			default:
				/* XXX: proper error handling */
				(void) fprintf(stderr,
				    "trans: invalid argument for -K\n");
				exit(EXIT_FAILURE);
			}
			break;
		case 'M':
			strict_fl_div = (*optarg == '1');
			break;
		case 'N':
			do_prom = 1;
			break;
		case 'P':
			do_profile = 1;
			break;
		case 'Q':
			exit(EXIT_SUCCESS);
			break;
		case 'R':
			round_after_flop = (*optarg == '1');
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
			do_unroll = (*optarg == '1');
			break;
		case 'V':
			print_version();
			break;
		case 'W':
			writable_strings = (*optarg == '1');
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
			/* XXX: undocumented */
			/* null value for pointer */
			ptr_null = 0x55555555;
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
#if isdragonfly
		case 'k':
			set_dragonfly_format(*optarg == '1');
			break;
#elif isfreebsd
		case 'k':
			set_freebsd_format(*optarg == '1');
			break;
#elif islinux
		case 'k':
			set_linux_format(*optarg == '1');
			break;
#else
		case 'k':
			/* XXX: proper error handling */
			(void) fprintf(stderr,
			    "trans: warning: -k is a no-op on this system\n");
			break;
#endif
#if issco
		case 's':
			sco_gas = 1;
			break;
#endif
		default:
			/* getopt will print an errormessage */
			exit(EXIT_FAILURE);
			break;
		}
	}

	argc -= optind;
	argv += optind;

#if isdragonfly
	if (gcc_compatible < 0)
		gcc_compatible = !dragonfly_elf;
#elif isfreebsd
	if (gcc_compatible < 0)
		gcc_compatible = !freebsd_elf;
#elif islinux
	if (gcc_compatible < 0)
		gcc_compatible = !linux_elf;
#elif isopenbsd || isnetbsd
	if (gcc_compatible < 0)
		gcc_compatible = 0; /* always ELF */
#endif
	if (argc == 0 || (argc % 2) != 0) {
		failer(BAD_COMMAND1);
		exit(EXIT_FAILURE);
	}

	while (*argv) {
		outfname = argv[1];

		/* initiate the output file */
		if (!outinit(outfname)) {
			failer(CANT_OPEN);
			exit(EXIT_FAILURE);
		}

		if (!initreader(argv[0])) {
			failer(CANT_READ);
			exit(EXIT_FAILURE);
		}

		init_all();

#ifdef NEWDWARF
		if (dwarf2)
			init_dwarf2();
		else
#endif
			if (diagnose)
				out_diagnose_prelude();

#ifdef NEWDWARF
		if (dump_abbrev) {
			outs(".text\n");
			do_abbreviations();
			dwarf2_prelude();
			make_dwarf_common();
			dwarf2_postlude();
		} else
#endif

		(void) d_capsule();

		while (weak_list) {
			outs(".set ");
			outs(weak_list->weak_id);
			outs(",");
			outs(weak_list->val_id);
			outnl();
			weak_list = weak_list->next;
		}

#ifdef NEWDWARF
		if (dwarf2)
			end_dwarf2();
		else
#endif
			if (diagnose)
				out_diagnose_postlude();

		outend(); /* close the .s file */
		endreader();

		if (good_trans)
			exit(EXIT_FAILURE);

		argv += 2; /* next pair of input/output files */
	}

	exit(EXIT_SUCCESS);
}

static void
print_version(void)
{
	(void) fprintf(stderr, "DERA ANDF 80x86/Pentium translator (TDF version %d.%d)\n",
	    MAJOR_VERSION, MINOR_VERSION);
	(void) fprintf(stderr, "reader %d.%d: ", reader_version,
	    reader_revision);
	(void) fprintf(stderr, "construct %d.%d: ", construct_version,
	    construct_revision);
	(void) fprintf(stderr, "target %d.%d: ", target_version,
	    target_revision);
#if DWARF
	(void) fprintf(stderr, "dwarf1 %d.%d: ", DWARF_MAJOR,
	    DWARF_MINOR);
#endif
#ifdef NEWDIAGS
	(void) fprintf(stderr, "diag_info %d.%d:\n%s   ", diag_version,
	    diag_revision, DG_VERSION);
#endif
#ifdef NEWDWARF
	(void) fprintf(stderr, "dwarf2 %d.%d: ", DWARF2_MAJOR,
	    DWARF2_MINOR);
#endif
	(void) fprintf(stderr, "\n");
	(void) fprintf(stderr, "system %s: ", target_system);
#ifdef __DATE__
	(void) fprintf(stderr, "installer compilation %s", __DATE__);
#endif
	(void) fprintf(stderr, "\n");
#ifdef RELEASE
	(void) fprintf(stderr, "release: %s\n", RELEASE);
#endif
}
