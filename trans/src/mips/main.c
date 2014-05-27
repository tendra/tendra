/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This is the main routine.
 * It constructs .G (binasm) and .T (symbol table) files from the input .t
 * files. If -S is given it will also construct a .s (assembler) file in as_file.
 */

#include <stdio.h>

#include <shared/check.h>
#include <shared/getopt.h>
#include <shared/error.h>

#include <reader/basicread.h>
#include <reader/main_reads.h>
#include <reader/externs.h>

#include <construct/flags.h>
#include <construct/flpt.h>
#include <construct/installglob.h>
#include <construct/machine.h>
#include <construct/exp.h>

#include "dump_distr.h"

extern void output_symtab(char*);

#define mipstrans_version   "4.49"

/* extern int bytes_allocated; */

void out_rename
(char * oldid, char * newid)
{
	/* ??? this may be wrong with diagnostics */
	return;
}

extern int good_trans;
bool do_extern_adds;
FILE * as_file;
FILE * ba_file;

int   majorno = 3;
int   minorno = 18;

long  currentfile = -1;		/* our source fileno 0.. */
long  mainfile = 0;		/* would be best if it actually contained main ! */

bool opt
(char c)
{ if (c == '0' || c == 0) return 0;
  else return 1;
}

int
main(int argc, char **argv)
{
	char *nm;
	char *aname;
	char *dname;
	bool produce_binasm = 0;
	PIC_code = 0;
	keep_PIC_vars = 1;
	diagnose_registers = 0;
	target_dbl_maxexp = 308;
	use_long_double = 0;

	as_file = NULL;
	redo_structfns = 0;
	do_extern_adds = 0;
	do_alloca = 0;

	endian = ENDIAN_BIG;
	assembler = ASM_GAS;
	format = FORMAT_ELF;
	diag = DIAG_NONE;
	cconv = CCONV_O32; /* TODO: confirm this is what we generate */
	abi = ABI_MIPS;

	set_progname(argv[0], mipstrans_version);

	{
		int c;

		while ((c = getopt(argc, argv,
			"A:B:DE:F:G:H:K:MO:PQRS:VWX:YZ"
			"es")) != -1) {
			switch (c) {
			case 'B': builtin = flags_builtin(builtin, optarg); break;
			case 'H': has     = flags_has(has, optarg);         break;
			case 'O': optim   = flags_optim(optim, optarg);     break;
			case 'X': check   = flags_check(check, optarg);     break;

			case 'A':
				abi = switch_cconv(optarg, ABI_MIPS);
				break;
			case 'C':
				cconv = switch_cconv(optarg, CCONV_O32);
				break;
			case 'E':
				endian = switch_endian(optarg, ENDIAN_BIG | ENDIAN_LITTLE);
				break;
			case 'F':
				format = switch_format(optarg, FORMAT_ELF);
				break;
			case 'G':
				diag = switch_diag(optarg, DIAG_NONE | DIAG_STABS);
				break;
			case 'S':
				assembler = switch_assembler(optarg, ASM_GAS | ASM_SGI | ASM_ULTRIX);
				break;

			case 'D': PIC_code = 1;                 break;
			case 'K': /* only MIPS */               break;
			case 'M': strict_fl_div = 1;            break;
			case 'P': do_profile = 1;               break;
			case 'Q': exit(EXIT_FAILURE);
			case 'R': round_after_flop = 1;         break;

			case 'V':
				trans_version();
				exit(EXIT_SUCCESS);

			case 'W': writable_strings = 1;        break;
			case 'Y': dyn_init = 1;                break;

			case 'Z': /* prints on stderr the versions of all the capsules
				from which this capsule was made */
				report_versions = 1;
				break;

			case 'e': do_extern_adds = 1; break;
			case 's': produce_binasm = 1; break;

			default:
				failer("Illegal flag");
				break;
			}
		}

		argc -= optind;
		argv += optind;
	}

	if (diag != DIAG_NONE) {
		do_alloca = 0; /* dbx does not understand variable frame sizes */
	}

	if (do_alloca && PIC_code) {
		failer("Can't do inline alloca with PIC code at the moment");
		exit(EXIT_FAILURE);
	}

	/* Things trans.mips does not "has" */
	has &= ~HAS_BYTEOPS;
	has &= ~HAS_BYTEREGS;
	has &= ~HAS_NEGSHIFT;
	has &= ~HAS_ROTATE;
	has &= ~HAS_MAXMIN;
	has &= ~HAS_SETCC;
	has &= ~HAS_COMPLEX;
	has &= ~HAS_64_BIT;

	/* line numbering goes to hell with optimisations */
	if (diag != DIAG_NONE) {
		optim = 0;
 	}

	if (produce_binasm) {
		dname = argv[1]; /* the .T file */
		nm    = argv[2]; /* the .G file */

		ba_file = fopen(nm, "w");
		if (ba_file == NULL) {
			printf("install: can't open output file %s\n", nm);
			return 1;
		}
	} else {
		aname = argv[1];

		as_file = fopen(aname, "w");
		if (as_file == NULL) {
			failer("can't open .s file");
			return 1;
		}
	}

	if (!initreader(argv[0])) {
		failer("cant read .t file");
		return 1;
	}

	init_flpt();

#include <reader/inits.h>

	top_def = NULL;

	local_prefix = "$$";
	name_prefix = "";

	d_capsule();

	if (produce_binasm) {
		fclose(ba_file);
		output_symtab(dname);
	} else {
		fclose(as_file);
	}

	return good_trans;
}

