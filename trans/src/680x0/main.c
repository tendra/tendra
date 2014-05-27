/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/getopt.h>

#include <local/szs_als.h>
#include <local/localflags.h>

#include <reader/basicread.h>
#include <reader/main_reads.h>
#include <reader/externs.h>

#include <construct/flpt.h>
#include <construct/installglob.h>
#include <construct/exp.h>
#include <construct/flags.h>

#include <utility/version.h>

#include "assembler.h"
#include "weights.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "codex.h"
#include "output.h"
#include "peephole.h"
#include "tests.h"
#include "utility.h"
#include "where.h"
#include "evaluate.h"
#include "68k_globals.h"

#include "xdb_basics.h"
#include "xdb_output.h"

extern int errors;
extern int max_errors;

extern char *optarg;


/*
    PROGRAM NAME AND VERSION NUMBER
*/

static char *version_str = "0.6";
int normal_version = 1;


/*
    EXTRA COMPILATION FLAGS
*/

int do_pic = 0;
static int do_quit = 0;
static int do_sep_units = 0;
static int ignore_errors = 0;
static int report_trans_version = 0;
static int report_tdf_versions = 0;


/*
    VARIABLE SIZES AND ALIGNMENTS
*/

alignment MAX_BF_SIZE;


int main
(int argc, char **argv)
{
	int a;
	char *input = NULL;
	char *output = NULL;

	diag = DIAG_NONE;
	endian = ENDIAN_BIG;
	assembler = ASM_GAS;
	format = FORMAT_AOUT;

	/*
	 * HP cc has different conventions to gcc on certain points, most
	 * noticably on the alignment of bitfields.  Both conventions are
	 * supported, but the cc conventions are default on the HPUX. NeXT
	 * cc is gcc.
	 */
	abi = ABI_SUNOS;
	cconv = CCONV_SUN;

	load_ptr_pars = 1;
	trap_on_nil_contents = 0;
	target_dbl_maxexp = 1024;
	use_long_double = 0;

	set_progname(argv[0], version_str);

	{
		int c;

		while ((c = getopt(argc, argv,
			"A:B:C:DE:F:G:H:K:MO:PQRS:VWX:YZ" "aefiou")) != -1) {
			switch (c) {
			case 'A': abi = switch_abi(optarg,
				ABI_HPUX | ABI_NEXT | ABI_SUNOS); break;
			case 'C': cconv = switch_cconv(optarg,
				CCONV_HP | CCONV_GCC | CCONV_SUN); break;
			case 'E': endian = switch_endian(optarg, ENDIAN_BIG); break;
			case 'F': format = switch_format(optarg, FORMAT_AOUT); break;
			case 'G': diag = switch_diag(optarg,
				DIAG_NONE | DIAG_STABS | DIAG_XDB_OLD | DIAG_XDB_NEW); break;
			case 'S': assembler = switch_assembler(optarg,
				ASM_HP | ASM_GAS ); break;

			case 'B': builtin = flags_builtin(builtin, optarg); break;
			case 'O': optim   = flags_optim(optim, optarg);     break;
			case 'H': has     = flags_has(has, optarg);         break;
			case 'X': check   = flags_check(check, optarg);     break;

			case 'D': do_pic = 1;                      break;
			case 'K':                                  break;
			case 'M': strict_fl_div = 1;               break;
			case 'N':                                  break;
			case 'J':                                  break;
			case 'P': do_profile = 1;                  break;
			case 'Q': do_quit = 1;                     break;
			case 'R': round_after_flop = 1;            break;
			case 'V': report_trans_version = 1;        break;
			case 'W':                                  break;
			case 'Y': dyn_init = 1;                    break;
			case 'Z': report_tdf_versions = 1;         break;

			case 'a': no_align_directives = 1;         break;
			case 'e': ignore_errors = 1;               break;
			case 'f': convert_floats = 0;              break;
			case 'i': output_immediately = 1;          break;
			case 'u': do_sep_units = 1;                break;

			case '?':
			default:
				error(ERROR_WARNING, "Unrecognised option, %s", "'unknown option'");
			}
		}

		argc -= optind;
		argv += optind;
	}

    /* Report version if required */
    if (report_trans_version) {
		trans_version();
		return 0;
    }
    if (report_tdf_versions) {
	    report_versions = 1;
    }

	if (argc != 2) {
		error(ERROR_FATAL, "Input and output file expected");
	}

	input  = argv[0];
	output = argv[1];

	switch (assembler) {
	case ASM_GAS:
		asm_dotty_instrs   = 0;
		asm_percent_regs   = 0;
		asm_data_first     = 0;
		asm_does_jump_lens = 1;
		asm_uses_equals    = 1;
		asm_uses_lcomm     = 1;
		asm_no_btst_suffix = 1;
		asm_cmp_reversed   = 0;
		break;

	case ASM_HP:
		asm_dotty_instrs   = 1;
		asm_percent_regs   = 1;
		asm_data_first     = 1;
		asm_does_jump_lens = 0;
		asm_uses_equals    = 0;
		asm_uses_lcomm     = 0;
		asm_no_btst_suffix = 0;
		asm_cmp_reversed   = 1;
		break;
	}

    /* Things trans.680x0 does not "has" */
    has &= ~HAS_NEGSHIFT;
    has &= ~HAS_ROTATE;
    has &= ~HAS_MAXMIN;
    has &= ~HAS_SETCC;
    has &= ~HAS_COMPLEX;
    has &= ~HAS_64_BIT;

    /* Careful with procedure results */
    optim &= ~OPTIM_UNPAD_APPLY;

    if (abi == ABI_SUNOS) {
	promote_pars = 0;
    }

    /* Switch off optimizations if required */
    if (diag != DIAG_NONE
#ifdef EBUG
    || 1
#endif
    ) {
	optim = 0;
    }

    /* Check on separate units */
    if (do_sep_units) {
	separate_units = 1;
#if 0
	current_alloc_size = first_alloc_size;
#endif
    }

    do_pic = 0 ; /* TODO */

    /* Other options */
    if (do_pic) {
	    PIC_code = 1;
    }
    
    if (~check & CHECK_EXTRA) {
	    target_dbl_maxexp = 16384;
    }

    if (do_quit) {
	    exit(EXIT_SUCCESS);
    }

    if (!initreader(input)) {
	exit(EXIT_FAILURE);
    }
    /* open_input(input);*/

    /* Set up alignment rules */
    double_align = DBL_ALIGN;
    param_align = PARAM_ALIGN;
    stack_align = STACK_ALIGN;

    diagnose_registers = 0;

    MAX_BF_SIZE = (cconv != CCONV_HP ? MAX_BF_SIZE_CC : MAX_BF_SIZE_GCC);

    /* Call initialization routines */
    top_def = NULL;
    init_flpt();
    init_instructions();
#include <reader/inits.h>
    init_weights();
    init_wheres();

    /* Decode, optimize and process the input TDF */
    open_output(output);
    init_output();
    area(ptext);

    if (diag != DIAG_NONE) {
	    diag_prologue();
    }

    d_capsule();

    if (diag != DIAG_NONE) {
	    diag_epilogue();
    }

#ifdef asm_version
    if (normal_version) {
	asm_version;
    } else {
	asm_version_aux;
    }
    fputc('\n', fpout);
#endif
    if (number_errors != 0 && !ignore_errors) {
	    exit(EXIT_FAILURE);
    }
    return 0;
}
