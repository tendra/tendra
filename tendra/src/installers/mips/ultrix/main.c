/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:04 $
$Revision: 1.1.1.1 $
$Log: main.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:04  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/09/12  11:00:34  currie
 * gcc pedanttry
 *
 * Revision 1.1  1995/04/13  09:33:41  currie
 * Initial revision
 *
***********************************************************************/

/*********************************************************************
                     main.c

   This is the main routine.
    It constructs .G (binasm) and .T (symbol table) files from the input .t
    files. If -S is given it will also construct a .s (assembler) file in as_file.

 *********************************************************************/




#include "config.h"
#include "version.h"
#include "common_types.h"
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
extern void output_symtab PROTO_S (( char* ));


/* extern int bytes_allocated; */

void out_rename
    PROTO_N ( (oldid, newid) )
    PROTO_T ( char * oldid X char * newid )
{
	/* ??? this may be wrong with diagnostics */
	return;
}

extern int good_trans;
bool do_extern_adds;
FILE * as_file;

FILE * ba_file;

int   majorno = 3;
int   minorno = 0;

long  currentfile = -1;		/* our source fileno 0.. */
long  mainfile = 0;		/* would be best if it  actually contained
				   main ! */
bool BIGEND = (little_end == 0);

bool do_tlrecursion = 1;

bool opt
    PROTO_N ( (c) )
    PROTO_T ( char c )
{ if (c == '0' || c == 0) return 0;
  else return 1;
}

int   main
    PROTO_N ( (argc, argv) )
    PROTO_T ( int argc X char **argv )
{
  long  i;
  char *nm;
  char *aname;
  char *dname;
  bool withs = 0;
  bool no_opts = 0;
  bool override_diags = 0;
/*  bool show_size = 0; */

  as_file = (FILE *) 0;
  do_inlining = 1;
  redo_structfns = 1;
  do_unroll = 1;
  do_extern_adds = 0;


  flpt_const_overflow_fail = 1; /* HUGEVAL requires 0 for Ysystem */

  do_foralls = 1;
  do_alloca = 1;
  for (i = 1; argv[i][0] == '-'; ++i) {/* read flags */
    char *s = argv[i];
    switch (s[1]) {
/*      case '?':
	show_size = 1;
	break;
*/
      case 'A':
	do_alloca = opt(s[2]);
	break;
      case 'B':
	flpt_const_overflow_fail = opt(s[2]);
	break;
      case 'C':
	do_loopconsts = opt(s[2]);
	break;
      case 'D':
	failer("No PIC code available");
	exit(EXIT_FAILURE);
      case 'E':
        extra_checks = 0;
        break;
      case 'e':
	do_extern_adds = opt(s[2]);
	break;
      case 'F':
        do_foralls = opt(s[2]);
        break;
      case '-':
      	override_diags = 1;
      	break;
      case 'H':
	diagnose = 1;
	do_alloca = 0; /* dbx does not understand variable frame sizes */
	break;
      case 'I':
	do_inlining = opt(s[2]);
        break;
      case 'K':
	/* only MIPS ultrix */
	break;
      case 'M':
	strict_fl_div = (opt(s[2]) == 0);
	break;
      case 'P':
	do_profile = 1;
	break;
      case 'Q':
	exit(EXIT_FAILURE);
      case 'R':
	round_after_flop = opt(s[2]);
	break;
      case 'S':
	withs =1;
	break;
      case 'U':
        do_unroll = opt(s[2]);
        break;
      case 'V': {
		int   ind = 2;
		int maj = 0;
		minorno = 0;
		for (;; ind++) {
		  char  si = s[ind];
		  if (si != ' ') {
		    if (si >= '0' && si <= '9') {
		      maj = maj * 10 + si - '0';
		    }
		    else
		      break;
		  }
		}

		if (s[ind] != '.') {
		  fprintf(stderr,
                "DRA TDF Mips Ultrix (as:3.x) translator %d.%d: (TDF version %d.%d)\n",
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
		  char  si = s[ind];
		  if (si >= '0' && si <= '9') {
		    minorno = minorno * 10 + si - '0';
		  }
		  else
		    break;
		}

	      }
      case 'W':
        writable_strings = opt(s[2]);
        break;
      case 'X':
        no_opts = 1;
        break;
      case 'd':
        do_dump_opt = 0;
        break;
      case 'l':
        do_tlrecursion = opt(s[2]);
        break;
      case 'Z': /* prints on stderr the versions of all the capsules
                   from which this capsule was made */
        report_versions = 1;
        break;
      default:
	failer ("Illegal flag");
	break;
    };
  };

#ifdef V210
	if (majorno != 2) {
		printf("This translator is only for ULTRIX versions 2.x\n");
		exit(EXIT_FAILURE);
	}
#else
	if (majorno == 2) {
		printf("This translator is not for ULTRIX versions 2.x\n");
		exit(EXIT_FAILURE);
	}
#endif

  if (override_diags) diagnose = 0;
  if (diagnose || no_opts) {		/* line numbering goes to hell with
				   optimisations */

        do_inlining = 0;
        do_loopconsts = 0;
        do_foralls = 0;
        do_dump_opt = 0;
        do_unroll = 0;
	do_tlrecursion = 0;
  };


  if (withs) {			/* requires assembler text */
    aname = argv[argc - 1];
    as_file = fopen (aname, "w");
    if (as_file == (FILE *) 0) {
      failer ("can't find .s file");
      return 1;
    }
    argc--;
  }


  dname = argv[argc - 1];	/* the .T file */
  nm = argv[argc - 2];		/* the .G file */
  ba_file = fopen (nm, "w");
  if (ba_file == (FILE *) 0) {
    printf ("install: can't open output file %s\n", nm);
    return (1);
  }


  if (!initreader (argv[argc - 3])) {
    failer ("cant read .t file");
    return (1);
  };

  init_flpt();
#include "inits.h"
  top_def = (dec*)0;





  local_prefix = "$$";
  name_prefix = "";


  d_capsule();
/*
  if (show_size) {
	printf("bytes allocated = %d\n", bytes_allocated);
  }
*/



  if (as_file)
    fclose (as_file);		/* close the .s file */
  fclose (ba_file);		/* close the .G file */
  output_symtab (dname);	/* construct the .T file */
  return (good_trans);		/* return 1 for error, 0 for good */
}

