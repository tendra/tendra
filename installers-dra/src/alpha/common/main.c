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

#include "config.h"

#include <reader/basicread.h>
#include <reader/main_reads.h>
#include <reader/externs.h>
#include <reader/reader_v.h>

#include <construct/flags.h>
#include <construct/flpt.h>
#include <construct/installglob.h>
#include <construct/machine.h>
#include <construct/exp.h>
#include <construct/construct_v.h>

#include "dump_distr.h"
#include "file.h"
#include "fail.h"
#include "version.h"
#include "symbol.h"
#include "bool.h"

FILE *as_file;		/* assembly file */
FILE *ba_file;

#define SUCCESS 0
#define FAILURE 1
#ifndef compile_date
#ifdef __DATE__
#define compile_date __DATE__
#else
#error "compile_date is not set"
#define compile_date	"04/07/71"
#endif
#endif
int use_umulh_for_div;
bool fail_with_denormal_constant = TRUE;
bool treat_denorm_specially = FALSE;
bool trap_all_fops = FALSE;
bool do_extern_adds = FALSE;

static int infoopt = FALSE;	/* set if the -V option has been invoked */
static bool produce_binasm = FALSE;

void
printinfo(void)
{
  (void)fprintf(stderr,"DRA TDF DEC Alpha/OSF1 translator %d.%d.%d:(TDF version %d.%d)\n",
		target_version,target_revision,target_patchlevel,
		MAJOR_VERSION,MINOR_VERSION);
  (void)fprintf(stderr,"reader %d.%d: ",reader_version,reader_revision);
  (void)fprintf(stderr,"construct %d.%d: \n",construct_version,
		construct_revision);
  (void)fprintf(stderr,"installer compilation %s\n",compile_date);
  return;
}

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

	redo_structfns=1;
	promote_pars = 0;
	do_alloca=0;
#if DO_NEW_DIVISION 
	use_umulh_for_div = 1;
#else
	use_umulh_for_div = 0;
#endif

	endian = ENDIAN_LITTLE;
	assembler = ASM_OSF1;
	format = FORMAT_ELF;
	diag = DIAG_STABS;

	{
		int c;

		while ((c = getopt(argc, argv, "B:C:DE:F:G:H:IK:MO:PQRSVWX:YZ" "ud:")) != -1) {
			switch (c) {
			case 'B': builtin = flags_builtin(builtin, optarg); break;
			case 'O': optim   = flags_optim(optim, optarg);     break;
			case 'H': has     = flags_has(has, optarg);         break;
			case 'X': check   = flags_check(check, optarg);     break;

			case 'D': failer("no PIC code available"); exit(EXIT_FAILURE);
			case 'C':
				diag = switch_diag(optarg, DIAG_STABS);
				break;
			case 'E':
				endian = switch_endian(optarg, ENDIAN_BIG | ENDIAN_LITTLE);
				break;
			case 'F':
				format = switch_format(optarg, FORMAT_ELF);
				break;
			case 'G':
				assembler = switch_assembler(optarg, ASM_OSF1);
				break;

			case 'I':
				diagnose      = 1;

			case 'K':
				fprintf(stderr,"alphatrans: [-K..] -> only one kind of processor is supported\n");
				break;

			case 'M': strict_fl_div = 1;           break;
			case 'P': do_profile = 1;              break;
			case 'Q': exit(EXIT_SUCCESS);          break;
			case 'R': round_after_flop = 1;        break;
			case 'S': produce_binasm = TRUE;       break;
			case 'V': printinfo(); infoopt = TRUE; break;
			case 'W': writable_strings = 1;        break;
			case 'Y': dyn_init = 1;                break;
			case 'Z': report_versions = 1;         break;

			case 'u': use_umulh_for_div = 1;       break;

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

			argc -= optind;
			argv += optind;
		}

		if (produce_binasm && argc != 3 || argc != 2) {
			if (infoopt) {
				exit(EXIT_SUCCESS);
			}

			alphafail(TOO_FEW_PARAMETERS);
		}

		argc -= optind;
		argv += optind;
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

