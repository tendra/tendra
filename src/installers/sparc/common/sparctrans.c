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




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/sparctrans.c,v 1.4 1998/03/11 11:03:59 pwe Exp $
--------------------------------------------------------------------------
$Log: sparctrans.c,v $
 * Revision 1.4  1998/03/11  11:03:59  pwe
 * DWARF optimisation info
 *
 * Revision 1.3  1998/02/06  17:04:37  release
 * Last minute pre-release polishing.
 *
 * Revision 1.2  1998/01/21  10:30:12  pwe
 * labdiff change
 *
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.15  1997/12/05  10:38:59  pwe
 * system identification
 *
 * Revision 1.14  1997/10/28  10:19:10  pwe
 * extra diags
 *
 * Revision 1.13  1997/10/10  18:33:02  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.12  1997/08/23  13:54:36  pwe
 * initial ANDF-DE
 *
 * Revision 1.11  1997/06/02  08:42:37  pwe
 * diags visibility
 *
 * Revision 1.10  1997/04/17  11:59:59  pwe
 * dwarf2 support
 *
 * Revision 1.9  1997/02/18  11:48:27  pwe
 * NEWDIAGS for debugging optimised code
 *
 * Revision 1.8  1996/08/15  15:34:54  pwe
 * mod for PWE ownership
 *
 * Revision 1.7  1996/03/18  09:02:17  john
 * Changed dynamic init default.
 *
 * Revision 1.6  1996/02/21  15:10:38  john
 * dynamic initialisations turned on by default
 *
 * Revision 1.5  1995/12/15  10:27:46  john
 * Added dynamic initialisations on SunOS
 *
 * Revision 1.4  1995/11/24  11:41:53  john
 * Fix for postludes
 *
 * Revision 1.3  1995/06/27  09:12:17  john
 * Reformatting
 *
 * Revision 1.2  1995/03/14  17:54:41  john
 * Changed default optimisation level
 *
 * Revision 1.1.1.1  1995/03/13  10:18:57  john
 * Entered into CVS
 *
 * Revision 1.7  1994/10/26  13:44:06  djch
 * added switches -i[idas] to give runtime control of inlining choices
 *
 * Revision 1.6  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.5  1994/07/04  08:30:49  djch
 * Changes to argument values and names, in conformance to new man page for all
 * installers.
 *
 * Revision 1.4  1994/05/24  13:13:53  djch
 * hacked -O to provide flpt overflow off, and -O? to be optimization
 *
 * Revision 1.3  1994/05/13  13:11:23  djch
 * Incorporates improvements from expt version
 * included debug.h to get enums to suport printing tag and shape names
 * changed default to do inlining and foralls, made their switches toggle...
 *
 * Revision 1.2  1994/05/03  15:13:39  djch
 * removed the -R flag (inner procs now in the common section)
 *
 * Revision 1.10  94/02/21  16:13:24  16:13:24  ra (Robert Andrews)
 * A couple of flags have changed.
 * 
 * Revision 1.9  93/11/19  16:31:27  16:31:27  ra (Robert Andrews)
 * Changed version number to 0.10.
 * 
 * Revision 1.8  93/09/27  14:55:41  14:55:41  ra (Robert Andrews)
 * The values of name_prefix, local_prefix and lab_prefix (which is new)
 * vary according to the target machine.
 * 
 * Revision 1.7  93/08/27  11:38:14  11:38:14  ra (Robert Andrews)
 * A couple of lint-like changes.  The definitions of local_prefix and
 * name_prefix are now not duplicated (see machine.c).
 * 
 * Revision 1.6  93/08/18  11:17:03  11:17:03  ra (Robert Andrews)
 * Changed method of specifying target machine (see config.h).
 * 
 * Revision 1.5  93/08/13  14:46:34  14:46:34  ra (Robert Andrews)
 * Removed a couple of comments.
 * 
 * Revision 1.4  93/07/14  11:22:15  11:22:15  ra (Robert Andrews)
 * Add options to set library_key.
 * 
 * Revision 1.3  93/07/05  18:28:24  18:28:24  ra (Robert Andrews)
 * Made distinction between the System V assembler and the System V ABI.
 * Added support for PIC (switched on using the -D option).
 * 
 * Revision 1.2  93/06/29  14:34:22  14:34:22  ra (Robert Andrews)
 * Slight reorganisation.  Error messages now use sparctrans (the variable).
 * The version number has also changed.
 * 
 * Revision 1.1  93/06/24  14:59:26  14:59:26  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE
#include "config.h"
#include "release.h"
#include "flags.h"
#include "tempdecs.h"
#include "comment.h"
#include "translat.h"
#include "main_reads.h"	
#include "basicread.h"
#include "addrtypes.h"
#include "makecode.h"
#include "flpt.h"
#include "exptypes.h"
#include "exp.h"
#include "installglob.h"
#include "out.h"
#include "externs.h"
#include "special.h"
#include "labels.h"

#include "target_v.h"
#include "reader_v.h"
#include "construct_v.h"
#ifdef NEWDIAGS
#include "diag_v.h"
#include "dg_version.h"
#endif
#ifdef NEWDWARF
#include "dw2_iface.h"
#include "dw2_vsn.h"
#include "dw2_abbrev.h"
#include "dw2_common.h"
static bool dump_abbrev = 0 ;
#endif

#if DWARF
#include "dwarf_mc.h"
#endif

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
bool do_tlrecursion = 0 ;
#if 0
bool do_innerprocs = 0 ;
#endif

extern int crit_inline;
extern int crit_decs;
extern int crit_decsatapp;
extern int show_inlining;

int do_dynamic_init=1;    /* Only applies to SunOS */

/*
  OPEN INPUT AND OUTPUT FILES
*/

static void open_files 
    PROTO_N ( ( infname, outfname ) )
    PROTO_T ( char * infname X char * outfname ){

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

int main 
    PROTO_N ( ( argc, argv ) )
    PROTO_T ( int argc X char ** argv )
{
  int a = 1 ;
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
  do_inlining = 1 ;			/* do inline */
  do_special_fns = 1 ;			/* do special functions */
  do_loopconsts = 1 ;			/* do loop constant extraction */
  do_foralls = 1;			/* do do foralls optimisation */
  do_unroll = 1;			/* do unroll loops */
  
  redo_structfns = 0 ;			/* structure results are normal */
  redo_structparams = 1 ;		/* structure parameters are odd */
  diagnose = 0 ;			/* not in diagnostics mode */
#ifdef NEWDIAGS
  diag_visible = 0;
  extra_diags = 0;
#endif
#ifdef NEWDWARF
  dwarf2 = 0;
#endif
  do_profile = 0 ;			/* not in profiling mode */
  PIC_code = 0 ;			/* don't do PIC */
  do_alloca = 1 ;			/* inline alloca */
  tempdecopt = 1 ;			/* do the tempdec optimisation */
  sysV_abi = SYSV_ABI ;			/* SYSV version */
  sysV_assembler = SYSV_AS ;		/* SYSV version */
  optim_level = 2 ;			/* default, equivalent to -O2 */
  g_reg_max = ( sysV_abi ? 4 : 7 ) ;	/* number of G registers */

    
  flpt_const_overflow_fail = 1;		/* constant floating point arithmetic
					   fails installation, if overflow */
  strict_fl_div = 1;			/* don't mult by 1/constant */
  round_after_flop = 0;			/* don't round every time */
  do_dynamic_init = 1;                  /* Only applies to SunOS*/
  
#define GET_0_1 ((arg[2] == '1') ? 1 : 0)
    /* process program arguments */
    while ( a < argc && ( arg = argv [a], arg [0] == '-' ) ) {
      switch ( arg [1] ) {
	case 'A' : do_alloca = GET_0_1 ; break ;
	case 'B' : flpt_const_overflow_fail = GET_0_1; break;	
	case 'C' : do_loopconsts = GET_0_1; break ;
	case 'D' : PIC_code = GET_0_1 ; break ;
	case 'E' : extra_checks = 0 ; break ;
	case 'F' : do_foralls = GET_0_1 ; break ;
	case 'H' : {
	  diagnose = 1 ;
#ifdef NEWDIAGS
	  if (arg[2] != 'O')
	    diag_visible = 1;
#endif
	  break ;
	}
	case 'I' : do_inlining = GET_0_1 ; break ;
#ifdef NEWDWARF
        case 'J' : 
	  diagnose = 1;
	  extra_diags = 1;
	  dwarf2 = 1;
	  break;
#endif
	case 'K' : break;
	case 'M' : strict_fl_div = GET_0_1 ; break ;
	case 'N' : do_prom = 1 ; break ;
	case 'O' : {
	  /* optimisation level */
	  optim_level = atoi ( arg + 2 ) ;
	  if ( optim_level < 0 ) optim_level = 0 ;
	  if ( optim_level > 4 ) optim_level = 4 ;
	  break ;
	}
	
	case 'P' : do_profile = 1 ; break ;	      
	case 'Q' : exit(EXIT_SUCCESS); break;
	case 'R' : round_after_flop = GET_0_1; break;
#ifdef NEWDWARF
	case 'T' :
	  dump_abbrev = 1;
	  diagnose = 1;
	  extra_diags = 1;
	  dwarf2 = 1;
	  break;
#endif
	case 'U' : do_unroll = GET_0_1; break;
	
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
	IGNORE fprintf(stderr, "system %s: ", target_system);
#ifdef __DATE__
	IGNORE fprintf(stderr, "installer compilation %s", __DATE__);
#endif
	IGNORE fprintf(stderr, "\n");
#ifdef RELEASE
	IGNORE fprintf(stderr, "release: %s\n",RELEASE);
#endif
	break;
	     
	case 'W' : break;
	case 'X' : {
	  /* disable all optimisations */
	  optim_level = 0 ;
	  tempdecopt = 0 ;
	  do_inlining = 0 ;
	  do_loopconsts = 0 ;
	  do_foralls = 0 ;
	  do_tlrecursion = 0 ;
	  do_unroll = 0;
	  break ;
	}
	case 'Z' : report_versions = 1 ; break ;

/* undocumented sparc specific flags below here */

	case 'a' : sysV_abi = 1 ; g_reg_max = 4 ; break ;
	case 'c' : do_comment = 1 ; break ;
	case 'g' : library_key = 2 ; break ;
	case 'l' : library_key = 1 ; break ;
	case 'i':
	switch (arg[2]) {
	  case 'i':
	  crit_inline = atoi(arg+3);
	  break;
	  case 'd':
	  crit_decs = atoi(arg+3);
	  break;
	  case 'a':
	  crit_decsatapp = atoi(arg+3);
	  break;
	  case 's':
	  fprintf(stderr,"count %d decs %d decs@app %d\n",
		  crit_inline, crit_decs, crit_decsatapp);
	  show_inlining = 1;
	  break;
	  default:
	  fprintf(stderr,"Incorrect inline option %c\n",arg[2]);
	}
	break;
	case 'r' : {
	  /* number of G registers */
	  g_reg_max = atoi ( arg + 2 ) ;
	  if ( g_reg_max < 4 ) g_reg_max = 4 ;
	  if ( g_reg_max > 7 ) g_reg_max = 7 ;
	  break ;
	}
	case 't' : tempdecopt = 0 ; break ;
	
	case 'u' : {
	  separate_units = 1 ;
#if 0	
	  current_alloc_size = first_alloc_size ;
#endif	
	  case 'n': {
	    do_dynamic_init = GET_0_1;
	  }
	  break ;
	}

	default : {
	  fprintf ( stderr, "%s : unknown option, %s\n",
		    sparctrans, arg ) ;
	  break ;
	}
      }
      a++ ;
    }

    /* we expect two further filename arguments */
    if ( argc == a + 2 ) {
      infname = argv [a] ;
      outfname = argv [ a + 1 ] ;
    } 
    else if ( argc == a + 1 ) {
      infname = argv [a] ;
      outfname = "-" ;
    } 
    else {
      if ( argc == a )
	fprintf ( stderr, "%s : input file missing\n", sparctrans );
      errflg = 1 ;
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
      tempdecopt = 0 ;
      do_inlining = 0 ;
      do_loopconsts = 0 ;
      do_foralls = 0 ;
      all_variables_visible = 1;	/* set vis flag for all declarations */
    }	

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
#include "inits.h"
    top_def = null ;

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
    return ( 0 ) ;
#endif
}
