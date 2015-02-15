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

#include <reader/basicread.h>
#include <reader/main_reads.h>
#include <reader/externs.h>
#include <reader/readglob.h>

#include <construct/flpt.h>
#include <construct/installglob.h>
#include <construct/exp.h>

#include <diag3/diag_reform.h>

#include <main/flags.h>
#include <main/driver.h>

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

#define VERSION_STR "0.6"
int normal_version = 1;


/*
    EXTRA COMPILATION FLAGS
*/

int do_pic = 0;
static int do_sep_units = 0;


/*
    VARIABLE SIZES AND ALIGNMENTS
*/

alignment MAX_BF_SIZE;


static void
init(void)
{
	/* TODO: have no defaults; pass all explicitly from tcc */
	diag      = DIAG_NONE;
	endian    = ENDIAN_BIG;
	assembler = ASM_GAS;
	format    = FORMAT_AOUT;

	/*
	 * HP cc has different conventions to gcc on certain points, most
	 * noticably on the alignment of bitfields. Both conventions are
	 * supported, but the cc conventions are default on the HPUX.
	 * NeXT cc is gcc.
	 */
	abi   = ABI_SUNOS;
	cconv = CCONV_SUN;

	load_ptr_pars        = 1;
	trap_on_nil_contents = 0;
	target_dbl_maxexp    = 1024;
	use_long_double      = 0;
}

static int
option(char c, const char *optarg)
{
	switch (c) {
	case 'a': no_align_directives = 1; break;
	case 'f': convert_floats      = 0; break;
	case 'i': output_immediately  = 1; break;
	case 'u': do_sep_units        = 1; break;

	default:
		return -1;
	}

	return 0;
}

static void
unhas(void)
{
    /* Things trans.m68k does not "has" */
    has &= ~HAS_NEGSHIFT;
    has &= ~HAS_ROTATE;
    has &= ~HAS_MAXMIN;
    has &= ~HAS_SETCC;
    has &= ~HAS_COMPLEX;
    has &= ~HAS_64_BIT;

    /* Careful with procedure results */
    optim &= ~OPTIM_UNPAD_APPLY;

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

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}

	if (abi == ABI_SUNOS) {
		promote_pars = 0;
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
}

static void
cleanup(void)
{
	if (diag != DIAG_NONE) {
		diag3_driver->out_diagnose_postlude();
	}

#ifdef asm_version
	if (normal_version) {
		asm_version;
	} else {
		asm_version_aux;
	}
	asm_printf("\n");
#endif
}

struct driver driver = {
	VERSION_STR,

	init,
	unhas,
	NULL,
	NULL,
	cleanup,

	"afiou",
	option,
	NULL,

	ABI_HPUX | ABI_NEXT | ABI_SUNOS,
	CCONV_HP | CCONV_GCC | CCONV_SUN,
	ENDIAN_BIG,
	FORMAT_AOUT,
	DIAG_NONE | DIAG_STABS | DIAG_XDB_OLD | DIAG_XDB_NEW,
	ASM_HP | ASM_GAS
};

