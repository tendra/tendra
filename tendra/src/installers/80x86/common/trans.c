/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


#include "config.h"
#include "argparse.h"
#include "catstdn.h"
#include "msgcat.h"
#include "tenapp.h"

#include "release.h"
#include "common_types.h"
#include "basicread.h"
#include "flags.h"
#include "out.h"
#include "main_reads.h"
#include "flpt.h"
#include "externs.h"
#include "weights.h"
#include "inl_norm.h"
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


/* PROCEDURES */

static void opt_help(char *option, void *closure);

#define	AP_OPT_BINSW(name, snm, lnm, value) \
	AP_OPTION((snm), (lnm), AT_EITHER, opt_bin_switch, (value), MID_description_of_##name)

static void
opt_bin_switch(char *option, void *closure, char *value)
{
	int *optval = closure;

	UNUSED(option);

	switch (*value) {
	  case '0':
		*optval = 0;
		break;
	  case '1':
		*optval = 1;
		break;
	  default:
		MSG_getopt_invalid_argument(option, value);
	}
}

static void
opt_diag(char *option, void *closure)
{
	UNUSED(closure);

	diagnose = 1;

#ifdef NEWDIAGS1
	if (option[1] == 'O') {
		return;
	} else if (option[1])
		MSG_arg_parse_unknown_option(option);
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
}

#ifdef NEWDWARF
static void
opt_dwarf2(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	diagnose = 1;
	extra_diags = 1;
	dwarf2 = 1;
}

static void
opt_dwarf2abbrev(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	dump_abbrev = 1;
	diagnose = 1;
	extra_diags = 1;
	dwarf2 = 1;
}
#endif

static void
opt_proctype(char *option, void *closure)
{
	UNUSED(closure);

	switch (option[1]) {
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
		MSG_arg_parse_unknown_option(option);
	}
}

static void
opt_quit(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	tenapp_exit2(0);
}

static void
opt_versions(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	tenapp_report_version();
	IGNORE fprintf(stderr, "TDF version %d.%d:",  MAJOR_VERSION, MINOR_VERSION);
	IGNORE fprintf(stderr, "reader %d.%d: ", reader_version, reader_revision);
	IGNORE fprintf(stderr, "construct %d.%d: ", construct_version,
				   construct_revision);
	IGNORE fprintf(stderr, "target %d.%d: ", target_version, target_revision);
#if DWARF
	IGNORE fprintf(stderr, "dwarf1 %d.%d: ", DWARF_MAJOR, DWARF_MINOR);
#endif
#ifdef NEWDIAGS
	IGNORE fprintf(stderr, "diag_info %d.%d:\n%s   ", diag_version,
				   diag_revision, DG_VERSION);
#endif
#ifdef NEWDWARF
	IGNORE fprintf(stderr, "dwarf2 %d.%d: ", DWARF2_MAJOR, DWARF2_MINOR);
#endif
	IGNORE fprintf(stderr, "\n");
	IGNORE fprintf(stderr, "system %s\n", target_system);
}

static void
opt_disableopts(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	do_unroll = 0;
	do_inlining = 0;
	do_loopconsts = 0;
	do_special_fns = 0;
	do_foralls = 0;
	indirect_jumps = 0;
	all_variables_visible = 1;
}

static void
opt_outformat(char *option, void *closure, char *value)
{
	int fmt = 0;

	UNUSED(option);
	UNUSED(closure);

	switch (*value) {
	  case '0':
		break;
	  case '1':
		fmt = 1;
		break;
	  default:
		MSG_getopt_invalid_argument(option, value);
	}
#if islinux
	set_linux_format (fmt);
#endif
#if isfreebsd
	set_freebsd_format (fmt);
#endif
}

static void
opt_ptrnull(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	ptr_null = 0x55555555;		/* null value for pointer */
}

static ArgListT cmdl_opts[] = {
	AP_OPT_BINSW	(do_alloca,		'A', NULL, &do_alloca),
	AP_OPT_BINSW	(flptc_range,	'B', NULL, &flpt_const_overflow_fail),
	AP_OPT_BINSW	(do_loopconsts,	'C', NULL, &do_loopconsts),
	AP_OPT_BINSW	(PIC_code,		'D', NULL, &PIC_code),
	AP_OPT_RESET	(no_constchk,	'E', NULL, &extra_checks),
	AP_OPT_BINSW	(do_foralls,	'F', NULL, &do_foralls),
	AP_OPT_BINSW	(gcc_compat,	'G', NULL, &gcc_compatible),
#ifdef NEWDIAGS
	AP_OPT_IMMEDIATE(diag_o,		'H', NULL, opt_diag),	/* -HO form */
#endif
	AP_OPT_EMPTY	(diag,			'H', NULL, opt_diag),
	AP_OPT_BINSW	(do_inlining,	'I', NULL, &do_inlining),
#ifdef NEWDWARF
	AP_OPT_EMPTY	(dwarf2,		'J', NULL, opt_dwarf2),
#endif
	AP_OPT_EITHER	(proctype,		'K', NULL, opt_proctype),
	AP_OPT_BINSW	(strict_fl_div,	'M', NULL, &strict_fl_div),
	AP_OPT_SET		(do_prom,		'N', NULL, &do_prom),
	AP_OPT_SET		(do_profile,	'P', NULL, &do_profile),
	AP_OPT_EMPTY	(quit,			'Q', NULL, opt_quit),
	AP_OPT_BINSW	(round_flop,	'R', NULL, &round_after_flop),
#ifdef NEWDWARF
	AP_OPT_EMPTY	(dwarf2abbrev,	'T', NULL, opt_dwarf2abbrev),
#endif
	AP_OPT_BINSW	(do_unroll,		'U', NULL, &do_unroll),
	AP_OPT_EMPTY	(versions,		'V', "version", opt_versions),
	AP_OPT_BINSW	(writable_strs,	'W', NULL, &writable_strings),
	AP_OPT_EMPTY	(disableopts,	'X', NULL, opt_disableopts),
	AP_OPT_SET		(reportcapver,	'Z', NULL, &report_versions),
	AP_OPT_SET		(useframe,		'a', NULL, &always_use_frame),
	AP_OPT_SET		(visvars,		'b', NULL, &all_variables_visible),
	AP_OPT_RESET	(todoc,			'c', NULL, &replace_arith_type),
	AP_OPT_RESET	(retbyref,		'd', NULL, &redo_structfns),
	AP_OPT_RESET	(todoc,			'e', NULL, &indirect_jumps),
	AP_OPT_EMPTY	(nullptr,		'f', NULL, opt_ptrnull),
	AP_OPT_SET		(todoc,			'g', NULL, &flpt_always_comparable),
	AP_OPT_EMPTY	(help,			'h', "help", opt_help),
	AP_OPT_SET		(print_inlines,	'i', NULL, &print_inlines),
	AP_OPT_SET		(no_bss,		'j', NULL, &no_bss),
	AP_OPT_EITHER	(outformat,		'k', NULL, opt_outformat),
#if issco
	AP_OPT_SET		(sco_gas,		's', NULL, &sco_gas),
#endif
	AP_OPT_EOL
};

static void
opt_help(char *option, void *closure)
{
	UNUSED(option);
	UNUSED(closure);

	MSG_usage ();
	arg_print_usage (cmdl_opts);
	msg_append_newline ();
}


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
	int optcnt;
	char *outfname;

	tenapp_init(argc, argv, "TDF to 80x86/Pentium translator", "1.0");
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

	optcnt = arg_parse_arguments (cmdl_opts, --argc, ++argv);
	argc -= optcnt;
	argv += optcnt;

#if islinux
	if (gcc_compatible < 0)
		gcc_compatible = ! linux_elf;
#endif
#if isfreebsd
	if (gcc_compatible < 0)
		gcc_compatible = ! freebsd_elf;
#endif

	if (argc < 2)
		MSG_getopt_not_enough_arguments();

	for (; argc ; argc -=2, argv += 2) {
		if (argc < 2)
			MSG_getopt_not_enough_arguments();

		outfname = argv[1];

		/* initiate the output file */
		if (!outinit (outfname))
			MSG_cant_open_output_file(outfname);

		if (!initreader (argv[0]))
			MSG_file_read_error(argv[0]);

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
		}

#ifdef NEWDWARF
		if (dwarf2) {
			end_dwarf2 ();
		} else
#endif
			if (diagnose) out_diagnose_postlude();

		outend ();			/* close the .s file */
		endreader();

		if (good_trans)
			tenapp_exit2(EXIT_FAILURE);
	}
	return 0;
}
