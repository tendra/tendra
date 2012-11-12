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

#include "config.h"

#include <reader/main_reads.h>	
#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/reader_v.h>

#include <construct/flags.h>
#include <construct/flpt.h>
#include <construct/exp.h>
#include <construct/installglob.h>
#include <construct/construct_v.h>

#include "comment.h"
#include "translat.h"
#include "addrtypes.h"
#include "makecode.h"
#include "exptypes.h"
#include "out.h"
#include "special.h"
#include "labels.h"

#include "target_v.h"

#ifdef NEWDIAGS
#include <newdiag/diag_v.h>
#include <reader/dg_version.h>
#endif

#ifdef NEWDWARF
#include <dwarf2/dw2_iface.h>
#include <dwarf2/dw2_vsn.h>
#include <dwarf2/dw2_abbrev.h>
#include <dwarf2/dw2_common.h>
static bool dump_abbrev = 0 ;
#endif

#if DWARF
#include <dwarf/dwarf_mc.h>
#endif

extern int use_link_stuff;

extern int good_trans ;

#include "debug.h"
/*
  IDENTIFIER PREFIXES
*/

char *local_prefix = "", *name_prefix = "" ;


/*
  LOCAL FLAGS
*/

extern int redo_structparams ;
extern int crit_inline;
extern int crit_decs;
extern int crit_decsatapp;
extern int show_inlining;

int do_dynamic_init=1;    /* Only applies to SunOS */

/*
  OPEN INPUT AND OUTPUT FILES
*/

static void 
open_files ( char * infname, char * outfname ){

  if ( !initreader ( infname ) ) {
    fprintf ( stderr, "%s : cannot open input file %s\n",
	      sparctrans, infname ) ;
    exit ( EXIT_FAILURE ) ;
  }

  if ( strcmp ( outfname, "-" ) == 0 ) {
    /* "-" by convention means stdout */
    as_file = stdout ;
  } 
  else {
    as_file = fopen ( outfname, "w" ) ;
    if ( as_file == NULL ) {
      fprintf ( stderr, "%s : cannot open output file %s\n",
		sparctrans, outfname ) ;
      exit ( EXIT_FAILURE ) ;
    }
  }
  return ;
}


/*
  MAIN ROUTINE
*/

int 
main ( int argc, char ** argv )
{
  char *arg ;
  char *infname ;
  char *outfname ;
  bool errflg = 0 ;
  
  /* initialise executable name */
  sparctrans = argv [0] ;
  for ( arg = sparctrans ; *arg ; arg++ ) {
    if ( *arg == '/' ) sparctrans = arg + 1 ;
  }
  
  /* initialise output file */
  as_file = stdout ;
  
  /* errors messages are output on stdout, ensure they get out */
  setbuf ( stdout, NULL ) ;
  setbuf ( stderr, NULL ) ;

  /* set defaults for options */
  redo_structfns = 0 ;			/* structure results are normal */
  redo_structparams = 1 ;		/* structure parameters are odd */
  diagnose = 0 ;			/* not in diagnostics mode */
#ifdef NEWDIAGS
  diag_visible = 0;
  extra_diags = 0;
#endif
  do_profile = 0 ;			/* not in profiling mode */
  PIC_code = 0 ;			/* don't do PIC */
  do_alloca = 0 ;			/* inline alloca */
  sysV_abi = SYSV_ABI ;			/* SYSV version */
  g_reg_max = ( sysV_abi ? 4 : 7 ) ;	/* number of G registers */

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
   * TODO: split this into ABI and as(1) dialect things, or have a seperate
   * flag for executable format.
   */
  sysV_assembler = 1 ;		/* SYSV version */

  /*
   * Note that this does not belong in common/construct/optimise.h as this is
   * a concept specific to sparc; it controls the ".optim" pseudo-op.
   */
  optim_level = 2 ;			/* default, equivalent to -O2 */

  strict_fl_div = 0;			/* don't mult by 1/constant */
  round_after_flop = 0;			/* don't round every time */
  do_dynamic_init = 1;                  /* Only applies to SunOS*/
  
  endian = ENDIAN_BIG;
  assembler = ASM_SUN;
  format = FORMAT_ELF;
#ifdef NEWDWARF
  diag = DIAG_DWARF;
#else
  diag = DIAG_STABS;
#endif

	{
		int c;

		while ((c = getopt(argc, argv,
			"B:C:DE:F:G:H:I:JK:MNO:PQRTVWX:YZ"
			"abcglo:i:r:un")) != -1) {
			switch (c) {
			case 'B': builtin = flags_builtin(optarg); break;
			case 'D': PIC_code = 1;                    break;
			case 'C':
				diag = switch_diag(optarg, DIAG_STABS | DIAG_DWARF | DIAG_DWARF2);
				break;
			case 'E':
				endian = switch_endian(optarg, ENDIAN_LITTLE);
				break;
			case 'F':
				format = switch_format(optarg, FORMAT_AOUT | FORMAT_ELF);
				break;
			case 'G':
				assembler = switch_assembler(optarg, ASM_SUN);
				break;

			case 'I':
				diagnose = 1 ;
#ifdef NEWDIAGS
				if (arg[2] != 'O')
					diag_visible = 1;
#endif
				break;

#ifdef NEWDWARF
			case 'J':
				diagnose = 1;
				extra_diags = 1;
				diag = DIAG_DWARF2;
				break;
#endif

			case 'K':                              break;
			case 'M': strict_fl_div = 1;           break;
			case 'N': do_prom = 1;                 break;
			case 'H': has = flags_has(optarg);     break;
			case 'O': optim = flags_optim(optarg); break;
			case 'P': do_profile = 1;              break;	      
			case 'Q': exit(EXIT_SUCCESS);          break;
			case 'R': round_after_flop = 1;        break;

#ifdef NEWDWARF
			case 'T':
				dump_abbrev = 1;
				diagnose = 1;
				extra_diags = 1;
				diag = DIAG_DWARF2;
				break;
#endif

			case 'V':
				IGNORE fprintf(stderr, "DERA ANDF Sparc translator (TDF version %d.%d)\n",
		    			MAJOR_VERSION, MINOR_VERSION);
				IGNORE fprintf(stderr, "reader %d.%d: ", reader_version,
					reader_revision);
				IGNORE fprintf(stderr, "construct %d.%d: ", construct_version,
					construct_revision);
				IGNORE fprintf(stderr, "target %d.%d: ", target_version,
					target_revision);
#if (DWARF == 1)
				IGNORE fprintf(stderr, "dwarf %d.%d: ", DWARF_MAJOR,
					DWARF_MINOR);
#endif
#ifdef NEWDIAGS
				IGNORE fprintf(stderr, "diag_info %d.%d:\n%s   ", diag_version,
					diag_revision, DG_VERSION);
#endif
#ifdef NEWDWARF
				IGNORE fprintf(stderr, "dwarf2 %d.%d: ", DWARF2_MAJOR,
					DWARF2_MINOR);
#endif
				IGNORE fprintf(stderr, "\n");
#ifdef __DATE__
				IGNORE fprintf(stderr, "installer compilation %s", __DATE__);
#endif
				break;
	     
			case 'W': break;
			case 'X': check = flags_check(optarg);  break;
			case 'Y': dyn_init = 1;                 break;
			case 'Z': report_versions = 1;          break;

			case 'a' : sysV_abi = 1; g_reg_max = 4; break;
			case 'b' : sysV_assembler = 0; break;
			case 'c' : do_comment = 1; break;
			case 'g' : library_key = 2; break;
			case 'l' : library_key = 1; break;
			case 'i':
				switch (optarg[0]) {
				case 'i': crit_inline    = atoi(&optarg[1]); break;
				case 'd': crit_decs      = atoi(&optarg[1]); break;
				case 'a': crit_decsatapp = atoi(&optarg[1]); break;
				case 's':
					fprintf(stderr,"count %d decs %d decs@app %d\n",
						crit_inline, crit_decs, crit_decsatapp);
					show_inlining = 1;
					break;
				default:
					fprintf(stderr,"Incorrect inline option %c\n",arg[2]);
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

			case 'n':
				do_dynamic_init = 1;
				break;

			default:
				fprintf ( stderr, "%s : unknown option, %s\n",
					sparctrans, arg ) ;
				break ;
			}
		}

		argc -= optind;
		argv += optind;
	}

    /* we expect two further filename arguments */
    if ( argc ==  2 ) {
      infname  = argv[0] ;
      outfname = argv[1] ;
    } 
    else if ( argc == 1 ) {
      infname = argv[0] ;
      outfname = "-" ;
    } 
    else {
      if ( argc == 0 )
	fprintf ( stderr, "%s : input file missing\n", sparctrans );
      errflg = 1 ;
    }

    if (sysV_assembler) {
      use_link_stuff = 1;
    }

    /* check ABI conformance */
    if ( sysV_abi && ( g_reg_max > 4 ) ) {
      fprintf ( stderr, "%s : -r%d conflicts with SYSV ABI\n",
		sparctrans, g_reg_max ) ;
    }

    /* quit if arguments were wrong */
    if ( errflg ) {
      exit ( EXIT_FAILURE ) ;
    }

    /* switch off certain optimisations in diagnostics mode */
#ifdef NEWDIAGS
    if ( diag_visible ) {
#else
    if ( diagnose ) {
#endif
      optim_level = 0 ;
      all_variables_visible = 1;	/* set vis flag for all declarations */
      optim = 0;
    }	

    /* Things trans.sparc does not "has" */
    has &= ~HAS_BYTEOPS;
    has &= ~HAS_BYTEREGS;
    has &= ~HAS_NEGSHIFT;
    has &= ~HAS_ROTATE;
    has &= ~HAS_MAXMIN;
    has &= ~HAS_SETCC;

    /* not implemented */
    optim &= ~OPTIM_TAIL;
    optim &= ~OPTIM_ZEROOFFSETS;
    optim &= ~OPTIM_SUBSTPARAMS;

    /* initialise nowhere */
    setregalt ( nowhere.answhere, 0 ) ;
    nowhere.ashwhere.ashsize = 0 ;
    nowhere.ashwhere.ashsize = 0 ;

    /* initialise name prefixes and label numbers */
    name_prefix = ( sysV_assembler ? "" : "_" ) ;
    local_prefix = ( sysV_assembler ? ".." : "$$" ) ;
    lab_prefix = ( sysV_assembler ? ".L" : "L." ) ;
    crt_labno = 101 ;

    /* other initialisation routines */
    init_flpt () ;
#include <reader/inits.h>
    top_def = NULL ;

    /* main decoding routines */
    open_files ( infname, outfname ) ;
    init_translator () ;
#ifdef NEWDWARF
    if ( dump_abbrev ) {
	/* Dump abbreviations table */
	do_abbreviations () ;
	dwarf2_prelude () ;
	make_dwarf_common () ;
	dwarf2_postlude () ;
    } else
#endif
    d_capsule () ;
    exit_translator () ;
    if ( good_trans ) exit ( EXIT_FAILURE ) ;

    /* check for output errors and close the output file */
    if ( ferror ( as_file ) != 0 || fclose ( as_file ) != 0 ) {
      fprintf ( stderr, "%s : output file error, %s\n",
		sparctrans, outfname ) ;
      exit ( EXIT_FAILURE ) ;
    }

    /* success */
    exit ( EXIT_SUCCESS ) ;
#ifdef lint
    return 0;
#endif
}
