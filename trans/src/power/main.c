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

#include <shared/check.h>
#include <shared/getopt.h>

#include <local/localflags.h>

#include <reader/reader_v.h>		/* for reader_revison */

#include <construct/flags.h>		/* for option flags */
#include <construct/installglob.h>
#include <construct/construct_v.h>	/* for construct_revision */

#include "comment.h"		/* for do_comment */
#include "target_v.h"		/* for comiple_date */
#include "macro.h"
#include "dynamic_init.h"

enum cpu cpu;
int no_error_jump;

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
  do_profile = 0;		/* Produce profiling info */
  separate_units = 0;		/* Translate units separately */
  all_variables_visible = 0;	/* Set vis flag for all declarations */
  strict_fl_div = 1;		/* Don't mult by 1/constant */
  round_after_flop = 1;		/* Round every time */
  do_comment = 0;		/* (see comment.c) */
  trap_on_nil_contents = 0;
  target_dbl_maxexp = 308;
  use_long_double = 0;

  cpu = CPU_COMMON;
  endian = ENDIAN_BIG;
  assembler = ASM_IBM;
  format = FORMAT_XCOFF;
  diag = DIAG_NONE;
  cconv = CCONV_XLC;
  abi = ABI_POWER;
  
	{
		int c;

		while ((c = getopt(argc, argv,
			"A:B:C:E:F:G:H:K:MO:PQRS:VWX:YZ" "cen")) != -1) {
			switch (c) {
			case 'B': builtin = flags_builtin(builtin, optarg); break;
			case 'H': has     = flags_has(has, optarg);         break;
			case 'O': optim   = flags_optim(optim, optarg);     break;
			case 'X': check   = flags_check(check, optarg);     break;

			case 'A':
				abi = switch_abi(optarg, ABI_POWER);
				break;
			case 'C':
				cconv = switch_assembler(optarg, CCONV_XLC);
				break;
			case 'E':
				endian = switch_endian(optarg, ENDIAN_BIG | ENDIAN_LITTLE);
				break;
			case 'F':
				format = switch_format(optarg, FORMAT_XCOFF);
				break;
			case 'G':
				diag = switch_diag(optarg, DIAG_NONE | DIAG_STABX | DIAG_XDB_OLD | DIAG_XDB_NEW);
				break;
			case 'S':
				assembler = switch_assembler(optarg, ASM_IBM);
				break;

			case 'K': 
				switch (*optarg) {
				case 'C': cpu = CPU_COMMON;  break;
				case 'R': cpu = CPU_RS6000;  break;
				case 'P': cpu = CPU_POWERPC; break;

				default:
					fprintf(stderr,"Unknown architecture: "
						"-K should be followed by R for rs6000 or P for powerpc\n");
				}
				break; 

			case 'M': strict_fl_div = 1; break ;

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
				break;
      
			case 'W': break;
			case 'Y': dyn_init = 1;                break;
			case 'Z': report_versions = 1;         break;

			case 'c': do_comment = 1;      break;
			case 'e': no_error_jump = 1;   break;
			case 'n': do_dynamic_init = 1; break;
      
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
  has &= ~HAS_NEGSHIFT;
  has &= ~HAS_ROTATE;
  has &= ~HAS_MAXMIN;
  has &= ~HAS_SETCC;
  has &= ~HAS_COMPLEX;
  has &= ~HAS_64_BIT;

  /* switch off certain optimisations in diagnostics mode */
  if ( diag != DIAG_NONE ) {
    all_variables_visible = 1;	/* set vis flag for all declarations */
    optim = 0;
  }
  return translate(infname, outfname);
}
