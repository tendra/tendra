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

#include <reader/reader_v.h>		/* for reader_revison */

#include <construct/flags.h>		/* for option flags */
#include <construct/installglob.h>
#include <construct/construct_v.h>	/* for construct_revision */

#include "comment.h"		/* for do_comment */
#include "target_v.h"		/* for comiple_date */
#include "macro.h"

int architecture=COMMON_CODE;	

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
  
  redo_structfns = 1;		/* procs delivering structs 
				 * recast to extra param
				 * for call struct/union return convention 
				 */
  diagnose = 0;			/* Produce diagnosics */
  do_profile = 0;		/* Produce profiling info */
  separate_units = 0;		/* Translate units separately */
  all_variables_visible = 0;	/* Set vis flag for all declarations */
  strict_fl_div = 1;		/* Don't mult by 1/constant */
  round_after_flop = 1;		/* Round every time */
  do_comment = 0;		/* (see comment.c) */
  endian = ENDIAN_BIG;
  assembler = ASM_IBM;
  format = FORMAT_XCOFF;
  diag = DIAG_STABX;
  
	{
		int c;

		while ((c = getopt(argc, argv,
			"B:C:E:F:G:H:IK:MO:PQRVWX:YZ" "c")) != -1) {
			switch (c) {
			case 'B': builtin = flags_builtin(optarg); break;
			case 'C':
				diag = switch_diag(optarg, DIAG_STABX | DIAG_XDB_OLD | DIAG_XDB_NEW);
				break;
			case 'E':
				endian = switch_endian(optarg, ENDIAN_BIG | ENDIAN_LITTLE);
				break;
			case 'F':
				format = switch_format(optarg, FORMAT_XCOFF);
				break;
			case 'G':
				assembler = switch_assembler(optarg, ASM_IBM);
				break;
			case 'I': diagnose = 1;                    break;

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

			case 'H': has = flags_has(optarg);     break;
			case 'O': optim = flags_optim(optarg); break;
			case 'P': do_profile = 1;              break;	      
			case 'Q': exit(EXIT_SUCCESS);          break;
			case 'R': round_after_flop = 1;        break;
      
			case 'V':
				fprintf(stderr, "DERA TDF translator (TDF version %d.%d)\n",
				MAJOR_VERSION, MINOR_VERSION);
				fprintf(stderr, "reader %d.%d: \n", reader_version,
					reader_revision);
				fprintf(stderr, "construct %d.%d: \n", construct_version,
					construct_revision);
				fprintf(stderr, "translator %d.%d: \n", target_version, target_revision);
#ifdef __DATE__
				fprintf(stderr, "installer compilation : %s\n", __DATE__);
#endif
				break;
      
			case 'W': break;
			case 'X': check = flags_check(optarg); break;
			case 'Y': dyn_init = 1;                break;
			case 'Z': report_versions = 1;         break;

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
  
  /* Things trans.power does not "has" */
  has &= ~HAS_BYTEOPS;
  has &= ~HAS_BYTEREGS;

  /* switch off certain optimisations in diagnostics mode */
  if ( diagnose ) {
    all_variables_visible = 1;	/* set vis flag for all declarations */
    optim = 0;
  }
  return translate(infname, outfname);
}
