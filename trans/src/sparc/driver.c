/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <shared/check.h>
#include <shared/getopt.h>
#include <shared/error.h>

#include <local/ash.h>

#include <reader/exp.h>
#include <reader/main_reads.h>
#include <reader/basicread.h>
#include <reader/externs.h>

#include <construct/flpt.h>
#include <construct/exp.h>
#include <construct/installglob.h>
#include <construct/machine.h>

#include <main/driver.h>
#include <main/flags.h>

#include "translate.h"
#include "addrtypes.h"
#include "make_code.h"
#include "special.h"
#include "labels.h"

#ifdef DWARF2
#include <dwarf2/dw2_iface.h>
#include <dwarf2/dw2_abbrev.h>
#include <dwarf2/dw2_common.h>
#endif

extern int use_link_stuff;

#include "debug.h"

#define VERSION_STR "3.11"

extern int redo_structparams;
extern int crit_inline;
extern int crit_decs;
extern int crit_decsatapp;
extern int show_inlining;

int gencompat = 1;
int do_dynamic_init = 0;

static void
init(void)
{
	endian    = ENDIAN_BIG;
	assembler = ASM_SUN;
	format    = FORMAT_ELF;
	diag      = DIAG_NONE;
	cconv     = CCONV_SPARC;
	abi       = ABI_SYSV;

	/* set defaults for options */
	redo_structfns    = 0; /* structure results are normal */
	redo_structparams = 1; /* structure parameters are odd */
	do_profile        = 0; /* not in profiling mode */
	PIC_code          = 0; /* don't do PIC */
	keep_PIC_vars     = 1;
	do_alloca         = 0; /* inline alloca */
	g_reg_max         = (abi == ABI_SYSV ? 4 : 7); /* number of G registers */

	/*
	 * On DIV_SETS_CC:
	 *
	 * This shouldn't really be solaris specific.  It depends on whether or not
	 * the processor correctly implements the sdivcc and udivcc instructions.
	 * These are part of the SPARC v8 architecture but their implementation
	 * (via software) on some implementations does not meet the specification
	 * with respect to overflow detection.
	 */

	/*
	 * This appears to be a combination of assembler dialect and ABI for the sake
	 * of producing a.out vs. ELF assembly. I'm keeping it around for the moment
	 * until I can test exactly what needs to happen for a.out systems.
	 *
	 * TODO: split this into ABI and as(1) dialect things, or have a separate
	 * flag for executable format.
	 * TODO: actually I think this is just the assembler; there was a separate
	 * variable for the sysV ABI.
	 */
	sysV_assembler = 1; /* SYSV version */

	/*
	 * Note that this does not belong in common/construct/optimise.h as this is
	 * a concept specific to sparc; it controls the ".optim" pseudo-op.
	 */
	optim_level      = 2; /* default, equivalent to -O2 */

	strict_fl_div    = 0; /* don't mult by 1/constant */
	round_after_flop = 0; /* don't round every time */
	do_dynamic_init  = 0;
}

static int
option(char c, const char *optarg)
{
	switch (c) {
	case 'b': sysV_assembler = 0; break;
	case 'g': library_key    = 2; break;
	case 'l': library_key    = 1; break;
	case 'm': gencompat      = 0; break;
	case 'n': do_dynamic_init = 1; break;

	case 'i':
		switch (optarg[0]) {
		case 'i': crit_inline    = atoi(optarg + 1); break;
		case 'd': crit_decs      = atoi(optarg + 1); break;
		case 'a': crit_decsatapp = atoi(optarg + 1); break;

		case 's':
			fprintf(stderr, "count %d decs %d decs@app %d\n",
				crit_inline, crit_decs, crit_decsatapp);
			show_inlining = 1;
			break;

		default:
			error(ERR_FATAL, "Incorrect inline option: %c", optarg[2]);
		}
		break;

	case 'o':
		/* optimisation level */
		optim_level = atoi(optarg);
		if ( optim_level < 0 ) optim_level = 0 ;
		if ( optim_level > 4 ) optim_level = 4 ;
		break;

	case 'r':
		/* number of G registers */
		g_reg_max = atoi(optarg);
		if ( g_reg_max < 4 ) g_reg_max = 4 ;
		if ( g_reg_max > 7 ) g_reg_max = 7 ;
		break ;

	case 'u' :
		separate_units = 1;
#if 0
		current_alloc_size = first_alloc_size;
#endif
		break;

	default:
		return -1;
	}

	return 0;
}

static void
unhas(void)
{
	/* Things trans.sparc does not "has" */
	has &= ~HAS_BYTEOPS;
	has &= ~HAS_BYTEREGS;
	has &= ~HAS_NEGSHIFT;
	has &= ~HAS_ROTATE;
	has &= ~HAS_MAXMIN;
	has &= ~HAS_SETCC;
	has &= ~HAS_COMPLEX;
	has &= ~HAS_64_BIT;

	/* not implemented */
	optim &= ~OPTIM_TAIL;
	optim &= ~OPTIM_ZEROOFFSETS;
	optim &= ~OPTIM_SUBSTPARAMS;

	/* Careful with procedure results */
	optim &= ~OPTIM_UNPAD_APPLY;

	/*
	 * I am not sure that this really counts as an optimisation. Possibly it
	 * shouldn't be an OPTIM_ flag at all. Or: it could be perfectly okay for
	 * a user to set this for sparc, and thus this ought to be cleared by the
	 * tcc environment for sparc. Meanwhile I'm clearing it here just in case.
	 */
	optim &= ~OPTIM_COMPOUNDS;

	if (writable_strings) {
		/* TODO: either always on, or always off. error out accordingly */
	}

	if (sysV_assembler) {
		use_link_stuff = 1;
	}

	switch (abi) {
	case ABI_SYSV:
		use_long_double   = 1;
		target_dbl_maxexp = 16384;
		break;

	case ABI_SUNOS:
		use_long_double   = 0;
		target_dbl_maxexp = 308;
		break;

	default:
		error(ERR_SERIOUS, "unsupported ABI");
	}

	/* check ABI conformance */
	if ( abi == ABI_SYSV && ( g_reg_max > 4 ) ) {
		error(ERR_FATAL, "%s : -r%d conflicts with SYSV ABI",
			progname, g_reg_max ) ;
	}

	if (diag != DIAG_NONE) {
		optim_level = 0 ;
	}

	/* initialise nowhere */
	setregalt ( nowhere.answhere, 0 ) ;
	nowhere.ashwhere.ashsize = 0 ;
	nowhere.ashwhere.ashsize = 0 ;

	/* initialise name prefixes and label numbers */
	name_prefix  = ( sysV_assembler ? "" : "_" ) ;
	local_prefix = ( sysV_assembler ? ".." : "$$" ) ;
	lab_prefix   = ( sysV_assembler ? ".L" : "L." ) ;
	crt_labno = 101 ;
}

static void
cleanup(void)
{
	exit_translator () ;
}

struct driver driver = {
	VERSION_STR,

	init,
	unhas,
	NULL,
	NULL,
	cleanup,

	"bglmo:i:r:un",
	option,
	NULL,

	ABI_SUNOS | ABI_SYSV,
	CCONV_SPARC,
	ENDIAN_LITTLE,
	FORMAT_AOUT | FORMAT_ELF,
	DIAG_NONE | DIAG_STABS | DIAG_DWARF1 | DIAG_DWARF2,
	ASM_SUN
};

