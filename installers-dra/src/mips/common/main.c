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

#include "version.h"
#include "basicread.h"
#include "flags.h"
#include "main_reads.h"
#include "flpt.h"
#include "externs.h"
#include "installglob.h"
#include "machine.h"
#include "exp.h"
#include "dump_distr.h"
#include "construct_v.h"
#include "reader_v.h"
#include "optimise.h"

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
bool BIGEND = (little_end == 0);

bool opt
(char c)
{ if (c == '0' || c == 0) return 0;
  else return 1;
}

int   main
(int argc, char **argv)
{
  char *nm;
  char *aname;
  char *dname;
  bool withs = 0;
  bool override_diags = 0;
  PIC_code = 0;

  as_file = (FILE *)0;
  redo_structfns = 0;
  do_extern_adds = 0;


  flpt_const_overflow_fail = 0; /* HUGEVAL requires 0 for Ysystem */

  do_alloca = 0;

	{
		int c;

		while ((c = getopt(argc, argv,
			"ABDEG:HK:MO:PQRSVWZ"
			"ei")) != -1) {
			switch (c) {
			case 'A': do_alloca = 1;                break;
			case 'B': flpt_const_overflow_fail = 1; break;
			case 'D': PIC_code = 1;                 break;
			case 'E': extra_checks = 0;             break;
			case 'G':                               break;

			case 'H':
				diagnose = 1;
				do_alloca = 0; /* dbx does not understand variable frame sizes */
				break;

			case 'K': /* only MIPS */               break;
			case 'M': strict_fl_div = 1;            break;
			case 'O': optim = optim_flags(optarg);  break;
			case 'P': do_profile = 1;               break;
			case 'Q': exit(EXIT_FAILURE);
			case 'R': round_after_flop = 1;         break;
			case 'S': withs = 1;                    break;

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

			case 'W': writable_strings = 1; break;

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
	}

	if (do_alloca && PIC_code) {
		failer("Can't do inline alloca with PIC code at the moment");
		exit(EXIT_FAILURE);
	}

  if (override_diags)diagnose = 0;
  if (diagnose) {		/* line numbering goes to hell with
				   optimisations */

	optim = 0;
  };


  if (withs) {			/* requires assembler text */
    aname = argv[argc - 1];
    as_file = fopen(aname, "w");
    if (as_file == (FILE *)0) {
      failer("can't find .s file");
      return 1;
    }
    argc--;
  }


  dname = argv[argc - 1];	/* the .T file */
  nm = argv[argc - 2];		/* the .G file */
  ba_file = fopen(nm, "w");
  if (ba_file == (FILE *)0) {
    printf("install: can't open output file %s\n", nm);
    return 1;
  }


  if (!initreader(argv[argc - 3])) {
    failer("cant read .t file");
    return 1;
  };

  init_flpt();
#include "inits.h"
  top_def = (dec*)0;





  local_prefix = "$$";
  name_prefix = "";


  d_capsule();



  if (as_file)
    fclose (as_file);		/* close the .s file */
  fclose (ba_file);		/* close the .G file */
  output_symtab (dname);	/* construct the .T file */
  return good_trans;		/* return 1 for error, 0 for good */
}
