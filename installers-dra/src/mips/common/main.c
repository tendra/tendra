/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*********************************************************************
                     main.c

   This is the main routine.
    It constructs .G (binasm) and .T (symbol table) files from the input .t
    files. If -S is given it will also construct a .s (assembler) file in as_file.

 *********************************************************************/

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
#include "version.h"

extern void output_symtab(char*);


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
long  mainfile = 0;		/* would be best if it  actually contained
				   main ! */

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
	bool override_diags = 0;
	PIC_code = 0;

	as_file = NULL;
	redo_structfns = 0;
	do_extern_adds = 0;
	do_alloca = 0;
	endian = ENDIAN_BIG;
	assembler = ASM_GAS;
	format = FORMAT_ELF;
	diag = DIAG_STABS;

	{
		int c;

		while ((c = getopt(argc, argv,
			"B:C:DE:F:G:H:IK:MO:PQRSV:WX:YZ"
			"ei")) != -1) {
			switch (c) {
			case 'B': builtin = flags_builtin(optarg); break;
			case 'D': PIC_code = 1;                    break;
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
				assembler = switch_assembler(optarg, ASM_GAS | ASM_SGI | ASM_ULTRIX);
				break;

			case 'I':
				diagnose = 1;
				do_alloca = 0; /* dbx does not understand variable frame sizes */
				break;

			case 'K': /* only MIPS */               break;
			case 'M': strict_fl_div = 1;            break;
			case 'H': has   = flags_has(optarg);    break;
			case 'O': optim = flags_optim(optarg);  break;
			case 'P': do_profile = 1;               break;
			case 'Q': exit(EXIT_FAILURE);
			case 'R': round_after_flop = 1;         break;
			case 'S': produce_binasm = 1;           break;

			case 'V':
				{
					int ind = 2;
					int maj = 0;

					minorno = 0;
					for (;; ind++) {
						char si = optarg[ind];
						if (si != ' ') {
							if (si >= '0' && si <= '9') {
								maj = maj * 10 + si - '0';
							}
							else
								break;
						}
					}

					if (optarg[ind]!= '.') {
						fprintf(stderr,
							"DRA TDF Mips (as:3.x) translator %d.%d: (TDF version %d.%d); 30th June 1994\n",
							mipstrans_version,mipstrans_revision, MAJOR_VERSION, MINOR_VERSION);
						fprintf(stderr, "reader %d.%d: \n", reader_version,
							reader_revision);
						fprintf(stderr, "construct %d.%d: \n", construct_version,
							construct_revision);
						break;
					}

					majorno = maj;
					minorno = 0;

					for (ind++;; ind++) {
						char  si = optarg[ind];
						if (si >= '0' && si <= '9') {
							minorno = minorno * 10 + si - '0';
						}
						else
							break;
					}
				}

			case 'W': writable_strings = 1;        break;
			case 'X': check = flags_check(optarg); break;
			case 'Y': dyn_init = 1;                break;

			case 'Z': /* prints on stderr the versions of all the capsules
				from which this capsule was made */
				report_versions = 1;
				break;

			case 'e': do_extern_adds = 1; break;
			case 'i': override_diags = 1; break;

			default:
				failer("Illegal flag");
				break;
			}
		}

		argc -= optind;
		argv += optind;
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

	if (override_diags) {
		diagnose = 0;
	}

	/* line numbering goes to hell with optimisations */
	if (diagnose) {
		optim = 0;
 	}

	if (produce_binasm) {
		dname = argv[1];	/* the .T file */
		nm    = argv[2];		/* the .G file */

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

