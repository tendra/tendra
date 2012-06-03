/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <stdlib.h>

#include <shared/getopt.h>

#include "config.h"

#include "flags.h"		/* for option flags */
#include "tempdecs.h"	/* for tempdecopt */
#include "comment.h"		/* for do_comment */
#include "translat.h"	/* for optim_level, translate() */
#include "installglob.h"
#include "reader_v.h"		/* for reader_revison */
#include "construct_v.h"	/* for construct_revision */
#include "target_v.h"		/* for comiple_date */
#include "macro.h"

int architecture=COMMON_CODE;	
bool do_tlrecursion;		/* expected by needscan.c */

int main(int argc, char **argv)
{
  bool errflg = 0;
  char *infname=(char*)0;
  char *outfname=(char*)0;
  char *arg;
  char *powertrans;

  /* 
   * Initialise executable name 
   */
  powertrans = argv [0] ;
  for ( arg = powertrans ; *arg ; arg++ ) 
  {
    if ( *arg == '/' ) 
    {
      powertrans = arg + 1 ;
    }
  }

  /* errors messages are output on stdout, ensure they get out */
  setbuf(stdout, NULL);
  
  /* 
   * Set defaults for options (see construct/flags.c)
   */
  do_macros = 0;                /* If you have compiled 
				   with -DDO_ASSEMBLER_MACROS this makes the 
				   output easier to read*/
  
  do_alloca = 0;		/* Use builtin alloca */
  do_inlining = 0;		/* Do inlining of functions */
  do_special_fns = 0;		/* Builtin procs used */
  do_loopconsts = 0;		/* Take constant expression out of loops */
  do_foralls = 0;		/* Replace indexing on loop variable by
				 * incremented pointer access.
				 */
  redo_structfns = 1;		/* procs delivering structs 
				 * recast to extra param
				 * for call struct/union return convention 
				 */
  diagnose = 0;			/* Produce diagnosics */
  do_profile = 0;		/* Produce profiling info */
  extra_checks = 1;		/* Do extra portability checks */
  separate_units = 0;		/* Translate units separately */
  all_variables_visible = 0;	/* Set vis flag for all declarations */
  do_unroll=1;                  /* Do unrolling of loops */
  flpt_const_overflow_fail = 1;	/* Constant floating point arithmetic
				 * fails installation, if overflow 
				 */
  strict_fl_div = 1;		/* Don't mult by 1/constant */
  round_after_flop = 1;		/* Round every time */
  
  do_tlrecursion = 0;		/* Do proc tail recursion optimisation 
				 * (see needscan.c)
				 */
  tempdecopt = 1;		/* (see tempdecs.c) */
  do_comment = 0;		/* (see comment.c) */
  optim_level = 2;		/* Optimize level */
  
	{
		int c;

		while ((c = getopt(argc, argv,
			"ABCEFGHIK:MO:PQRUVWXZ" "c")) != -1) {
			switch (c) {
			case 'A': do_alloca = 1;                break;
			case 'B': flpt_const_overflow_fail = 1; break;	
			case 'C': do_loopconsts = 1;            break;
			case 'E': extra_checks = 0;             break;
			case 'F': do_foralls = 1;               break;
			case 'G':                               break;
			case 'H': diagnose = 1;                 break;
			case 'I': do_inlining = 1;              break;

			case 'K': 
				if (optarg[0] == 'R') {
					architecture = RS6000_CODE;
				} else if (optarg[0] == 'P') {
					architecture = POWERPC_CODE;
				} else {
					fprintf(stderr,"Unknown architecture: "
						"-K should be followed by R for rs6000 or P for powerpc\n");
				}
				break; 

			case 'M': strict_fl_div = 1; break ;

			case 'O':
				/* optimisation level */
				optim_level = atoi(optarg) ;
				if ( optim_level < 0 ) optim_level = 0 ;
				if ( optim_level > 4 ) optim_level = 4 ;
				break;
      
			case 'P': do_profile = 1;       break;	      
			case 'Q': exit(EXIT_SUCCESS);   break;
			case 'R': round_after_flop = 1; break;
			case 'U': do_unroll = 1;        break;
      
			case 'V':
				fprintf(stderr, "DERA TDF translator (TDF version %d.%d)\n",
				MAJOR_VERSION, MINOR_VERSION);
				fprintf(stderr, "reader %d.%d: \n", reader_version,
					reader_revision);
				fprintf(stderr, "construct %d.%d: \n", construct_version,
					construct_revision);
				fprintf(stderr, "translator %d.%d: \n", target_version, target_revision);
				fprintf(stderr, "system %s: \n", target_system);
#ifdef __DATE__
				fprintf(stderr, "installer compilation : %s\n", __DATE__);
#endif
				break;
      
			case 'W': break;

			case 'X':
				/* disable all optimisations */
				optim_level = 0 ;
				tempdecopt = 0 ;
				do_inlining = 0 ;
				do_loopconsts = 0 ;
				do_foralls = 0 ;
				do_tlrecursion = 0 ;
				do_unroll = 0;
				break ;

			case 'Z': report_versions = 1 ; break ;

			case 'c': do_comment = 1 ; break ;
      
			case '?':
			default:
				fprintf ( stderr, "%s : unknown option, %s\n",
				powertrans, arg ) ;
				break ;
			}
		}

		argc -= optind;
		argv += optind;
	}
  
  /* we expect two further filename arguments */
  if ( argc == 2 ) {
    infname = argv[0] ;
    outfname = argv[1] ;
  } else if ( argc == 1 ) {
    infname = argv[0] ;
    outfname = "-" ;
  } else {
    errflg = 1 ;
  }
  
  /* quit if arguments were wrong */
  if ( errflg ) {
    exit ( EXIT_FAILURE ) ;
    }
  
  /* switch off certain optimisations in diagnostics mode */
  if ( diagnose ) {
    optim_level = 0 ;
    tempdecopt = 0 ;
    do_inlining = 0 ;
    do_loopconsts = 0 ;
    do_foralls = 0 ;
    do_unroll=0;
    do_tlrecursion = 0;
    do_special_fns = 0;		/* no builtins */
    all_variables_visible = 1;	/* set vis flag for all declarations */
  }
  return translate(infname, outfname);
}
