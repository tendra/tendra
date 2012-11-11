/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/getopt.h>

#include "config.h"

#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/main_reads.h>
#include <reader/readglob.h>
#include <reader/reader_v.h>

#include <construct/flags.h>
#include <construct/flpt.h>
#include <construct/installglob.h>
#include <construct/machine.h>
#include <construct/exp.h>
#include <construct/construct_v.h>

#include "out.h"
#include "weights.h"
#include "instr.h"
#include "expmacs.h"
#include "instr386.h"
#include "localflags.h"
#include "messages_8.h"
#include "assembler.h"
#include "target_v.h"
#include "operand.h"

#ifdef NEWDIAGS
#include <newdiag/diag_fns.h>
#include <newdiag/diag_v.h>
#include <reader/dg_version.h>
#else
#include <diag/diag_fns.h>
#endif

#ifdef NEWDWARF
#include <dwarf2/dw2_iface.h>
#include <dwarf2/dw2_vsn.h>
#include <dwarf2/dw2_abbrev.h>
#include <dwarf2/dw2_common.h>
static bool dump_abbrev = 0;
#endif /* NEWDWARF */

#if DWARF
#include <dwarf/dwarf_mc.h>
#endif

static void init_all(void);
static void print_version(void);

extern int print_inlines;

extern int use_link_stuff;

static void
init_all(void)
{
	init_flpt();
#include <reader/inits.h> /* XXX: not nice */
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
	redo_structfns = 1;	/* replace fns delivering structs */
	redo_structparams = 0;	/* no change to struct params */
	is80486 = 1;		/* (at least) 80486 */
	is80586 = 1;		/* Pentium */
	separate_units = 0;	/* combine units */
	always_use_frame = 0;	/* avoid using frame pointer */
	diagnose = 0;		/* diagnostics off */
#ifdef NEWDIAGS
	diag_visible = 0;
	extra_diags = 0;
#endif /* NEWDIAGS */
	do_profile = 0;		/* no profiling code */
	writable_strings = 0;	/* strings are read only */
	PIC_code = 0;		/* do not produce PIC code */
	all_variables_visible = 0; /* use registers */
	do_alloca = 1;		/* inline calls of alloca */
	round_after_flop = 0;	/* do not round after each floating point
				   operation */
	/* do not replace divisions by multiplication by the inverse */
	strict_fl_div = 1;
	flpt_always_comparable = 0; /* this is the default for SVR4.2 */
	report_versions = 0;	/* do not print version numbers */
	permit_8byte_align = 1;	/* allow 8byte alignment for local doubles */
	replace_arith_type = 1;	/* use the C definitions of promote etc. */
	no_bss = 0;		/* use .comm */
	use_link_stuff = 1;
	endian = ENDIAN_LITTLE;
	assembler = ASM_GAS;
	format = FORMAT_ELF;
#ifdef NEWDWARF
	diag = DIAG_DWARF2;
#else
	diag = DIAG_DWARF;
#endif

	ptr_null = 0;		/* null value for pointer */
	proc_null = 0;		/* null value for proc */
	lv_null = 0;		/* null value for label_value*/

	/*
	 * XXX: Some arguments are undocumented in trans.1, check
	 */
#ifdef NEWDWARF
	optstring = "B:C:D:E:F:G:H:I:" "J" "K:M:NO:PQR:" "T" "VW:X:YZ" "abcdfghit:";
#else
	optstring = "B:C:D:E:F:G:H:I:"     "K:M:NO:PQR:"     "VW:X:YZ" "abcdfghit:";
#endif

	while ((ch = getopt(argc, argv, optstring)) != -1) {
		switch (ch) {
		case 'B':
			builtin = flags_builtin(optarg);
			break;
		case 'C':
			diag = switch_diag(optarg, DIAG_STABS | DIAG_DWARF | DIAG_DWARF2);
			break;
		case 'D':
			PIC_code = (*optarg == '1');
			break;
		case 'E':
			endian = switch_endian(optarg, ENDIAN_LITTLE);
			break;
		case 'F':
			format = switch_format(optarg, FORMAT_ELF | FORMAT_AOUT);
			break;
		case 'G':
			assembler = switch_assembler(optarg, ASM_GAS);
			break;
		case 'H':
			has = flags_has(optarg);
			break;
		case 'I':
			/* Add debug symbols to assembly */

			if (*optarg != 'O' && *optarg != 'N') {
				fprintf(stderr,
				    "trans: invalid argument for -I\n");
				exit(EXIT_FAILURE);
			}

			diagnose = 1;

#ifdef NEWDIAGS
			/*
			 * O: produce optimised assembly
			 * N: disable assembly optimisation
			 */
			if (*optarg == 'N') {
				diag_visible = 1;

				always_use_frame = 1;
				all_variables_visible = 1;
				optim = 0;
			}
#else /* At the moment every operating system but solaris */
			always_use_frame = 1;
			all_variables_visible = 1;
			optim = 0;
#endif /* NEWDIAGS */
			break;
#ifdef NEWDWARF
		case 'J':
			diagnose = 1;
			extra_diags = 1;
			diag = DIAG_DWARF2;
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
		case 'O':
			optim = flags_optim(optarg);
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
			diag = DIAG_DWARF2;
			break;
#endif
		case 'V':
			print_version();
			break;
		case 'W':
			writable_strings = (*optarg == '1');
			break;
		case 'X':
			check = flags_check(optarg);
			break;
		case 'Y':
			dyn_init = 1;
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
		case 't':
			/* TODO: I think it ought to be set by the ABI. But I'm putting
			 * it here for the moment to keep it out of the way.
			 * I think this is only relevant for a.out systems. */
			gcc_compatible = (*optarg == '1');
			break;
		default:
			/* getopt will print an errormessage */
			exit(EXIT_FAILURE);
			break;
		}
	}

	argc -= optind;
	argv += optind;

	if (argc == 0 || (argc % 2) != 0) {
		failer(BAD_COMMAND1);
		exit(EXIT_FAILURE);
	}

	/* TODO: unsure about this. I think it ought to be set by the ABI.
	 * It might not neccessarily always be the same as gcc_compatible,
	 * because those differed for Solaris x86. Or that was an a.out system,
	 * and this isn't relevant for ELF. */
	remove_struct_ref = gcc_compatible;

	/* Things trans.80x86 does not "has" */
	has &= ~HAS_NEGSHIFT;
	has &= ~HAS_CONDASSIGN;

	if (!is80586) {
		has &= ~HAS_SETCC;
	}

	/* XXX: invalid assembly is generated without this */
	optim |= OPTIM_CASE;

	set_format(format);

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
		if (diag == DIAG_DWARF2)
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
		if (diag == DIAG_DWARF2)
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
#ifdef __DATE__
	(void) fprintf(stderr, "installer compilation %s", __DATE__);
#endif
}
