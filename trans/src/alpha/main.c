/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  driver.c
  Provides the driver function for the TDF->DEC Alpha translator.
*/

#include <stdio.h>
#include <stdlib.h>

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
#include "file.h"
#include "fail.h"
#include "symbol.h"
#include "bool.h"

FILE *as_file;		/* assembly file */
FILE *ba_file;

#define alphatrans_version "2.4.11"

#define SUCCESS 0
#define FAILURE 1

int use_umulh_for_div;
bool fail_with_denormal_constant = TRUE;
bool treat_denorm_specially = FALSE;
bool trap_all_fops = FALSE;
bool do_extern_adds = FALSE;

static int infoopt = FALSE;	/* set if the -V option has been invoked */
static bool produce_binasm = FALSE;

void
out_rename(char *oldid, char *newid)
{
  UNUSED(oldid);
  UNUSED(newid);
  return;
}

int currentfile = -1;
int mainfile=0;
int majorno = 3;
int minorno = 11;

int
main(int argc, char *argv[])
{
	int i;
	char *aname;	/* name of file for assembly output */
	char *dname;	/* name of file to hold symbol table */
	char *baname;
	char *tname;

	set_progname(argv[0], alphatrans_version);

	target_dbl_maxexp = 308;
	redo_structfns=1;
	promote_pars = 0;
	do_alloca=0;
#if DO_NEW_DIVISION 
	use_umulh_for_div = 1;
#else
	use_umulh_for_div = 0;
#endif

	endian = ENDIAN_LITTLE;
	assembler = ASM_GAS;
	format = FORMAT_ELF;
	diag = DIAG_NONE;
	cconv = CCONV_ALPHA;
	abi = ABI_OSF1;

	{
		int c;

		while ((c = getopt(argc, argv, "A:B:C:DE:F:G:H:K:MO:PQRS:VWX:YZ" "sud:")) != -1) {
			switch (c) {
			case 'B': builtin = flags_builtin(builtin, optarg); break;
			case 'O': optim   = flags_optim(optim, optarg);     break;
			case 'H': has     = flags_has(has, optarg);         break;
			case 'X': check   = flags_check(check, optarg);     break;

			case 'D': failer("no PIC code available"); exit(EXIT_FAILURE);

			case 'A':
				abi = switch_cconv(optarg, ABI_OSF1);
				break;
			case 'C':
				cconv = switch_cconv(optarg, CCONV_ALPHA);
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
				assembler = switch_assembler(optarg, ASM_OSF1 | ASM_GAS);
				break;

			case 'K':
				fprintf(stderr,"alphatrans: [-K..] -> only one kind of processor is supported\n");
				break;

			case 'M': strict_fl_div = 1;           break;
			case 'P': do_profile = 1;              break;
			case 'Q': exit(EXIT_SUCCESS);          break;
			case 'R': round_after_flop = 1;        break;
			case 'V': trans_version(); infoopt = TRUE; break;
			case 'W': writable_strings = 1;        break;
			case 'Y': dyn_init = 1;                break;
			case 'Z': report_versions = 1;         break;

			case 'u': use_umulh_for_div = 1;       break;

			case 's': produce_binasm = TRUE;       break;
			case 'd':	
				/* handle IEEE denormals */
				treat_denorm_specially = TRUE;

				switch (atoi(optarg)) {
				case 0:
					/* replace denormal const with 0.0 (don't do this) */
					alphawarn("Unsupported denormal switch");
					fail_with_denormal_constant = FALSE;
					break;

				case 1:
					/* error if denormal const is encountered */
					fail_with_denormal_constant = TRUE;
					break;

				case 2: 
					/* handle denormals properly (and slowly), by 
					 * stopping the interleaving of floating point 
					 * operations and using the OS exception handler */
					treat_denorm_specially = FALSE;
					trap_all_fops = TRUE;
					break;

				default:
					alphafail(ILLEGAL_FLAG, "-d");
					break;
				}
				break;

			default:
				exit(EXIT_FAILURE);
			}
		}

		argc -= optind;
		argv += optind;

		if (produce_binasm && argc != 3 || argc != 2) {
			if (infoopt) {
				exit(EXIT_SUCCESS);
			}

			alphafail(TOO_FEW_PARAMETERS);
		}
	}

	/* the files are passed in the order .t { .G .T | .s } */
	if (produce_binasm) {
		tname   = argv[0];
		baname  = argv[1];
		dname   = argv[2];
	} else {
		tname   = argv[0];
		aname   = argv[1];
		as_file = open_file(aname,WRITE);
	}

	/* Things trans.alpha does not "has" */
	has &= ~HAS_BYTEOPS;
	has &= ~HAS_BYTEREGS;
	has &= ~HAS_NEGSHIFT;
	has &= ~HAS_ROTATE;
	has &= ~HAS_MAXMIN;
	has &= ~HAS_CONDASSIGN;
	has &= ~HAS_DIV0;
	has &= ~HAS_SETCC;
	has &= ~HAS_COMPLEX;

	/* This does not work on the alpha */
	optim &= ~OPTIM_CASE;

	if (produce_binasm) {
		ba_file = open_file(baname,WRITE);
	} else {
		ba_file = NULL;
	}

	if (!initreader(tname)) {
		alphafail(OPENING_T_FILE, tname);
	}

	init_flpt();

#include <reader/inits.h>

	top_def = NULL;
	local_prefix = "$$";
	name_prefix  = "";

	(void) d_capsule();

	if (produce_binasm) {
		output_symtab(dname);
	}

	if (produce_binasm) {
		close_file(ba_file);
	} else {
		close_file(as_file);
	}

	return SUCCESS;
}

