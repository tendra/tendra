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
$Log: hppatrans.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:04  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1996/04/18  11:09:12  wfs
 * Fixed a bug in "needscan.c" where "locptr_tag" was being wrapped around
 * the wrong exps.
 *
 * Revision 1.5  1996/01/30  15:36:29  wfs
 * Added the dynamic initialization files "dyn_begin.s" and "dyn_end.s" to
 * the hppatrans repository. The bl_install and bl_update scripts were
 * expanded to deal with these new "initcode" files.
 *
 * Revision 1.4  1996/01/08  12:01:50  wfs
 * Cosmetic changes to usage message in "hppatrans.c". "issparc" set to 0 in
 * "config.h". Change to "scan()" regarding the passing of 64 bit int params.
 *
 * Revision 1.3  1995/12/20  12:11:18  wfs
 * "-v" option disabled. "ManualPages" put under cvs control.
 *
 * Revision 1.2  1995/12/18  13:11:35  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.5  1995/10/30  12:57:56  wfs
 * Standardized the format of the warning messages.
 *
 * Revision 5.4  1995/10/25  14:32:46  wfs
 * Removed a few commented out instructions.
 *
 * Revision 5.3  1995/10/20  13:55:38  wfs
 * Changes for gcc compilation.
 *
 * Revision 5.2  1995/09/25  10:17:42  wfs
 * Added "#ifdef _SYMTAB_INCLUDED" provisios around any code which refers
 * to "hpux-symtab.h". We cannot legally distribute this header file.
 *
 * Revision 5.1  1995/09/15  12:29:03  wfs
 * Minor changes made to stop gcc compiler from complaining + changed
 * messages citing "hppatrans" to "trans".
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  11:22:17  wfs
 * Name of installer occuring in messages changed from "hppatrans" to
 * "trans"
 *
 * Revision 3.4  1995/08/25  11:22:17  wfs
 * Name of installer occuring in messages changed from "hppatrans" to
 * "trans"
 *
 * Revision 3.3  1995/08/25  09:36:12  wfs
 * some superflous code removed ( includingincluding the SunOS "-G" option).
 * minor alterations for diagnostics stuff.
 *
 * Revision 3.1  95/04/10  16:26:49  16:26:49  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:17:27  11:17:27  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:27:34  15:27:34  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/17  13:58:43  13:58:43  wfs (William Simmonds)
 * Initial revision
 * 
*/



#define HPPATRANS_CODE
#include "config.h"		/* for PROTO_S () */
#include "flags.h"		/* for option flags */
#include "tempdecs.h"		/* for tempdecopt */
#include "comment.h"		/* for do_comment */
#include "translat.h"		/* for optim_level, translate () */
#include "main_reads.h"		/* for d_capsule */
#include "basicread.h"	/* for good_trans */
#include "addrtypes.h"		/* for where */
#include "makecode.h"		/* for nowhere */
#include "flpt.h"
#include "exptypes.h"
#include "exp.h"		/* for current_alloc_size */
#include "installglob.h"	/* for top_def */
#include "out.h"
#include "installtypes.h"
#include "version.h"
#include "reader_v.h"
#include "construct_v.h"
#include "externs.h"
#include "hppadiags.h"
#include "frames.h"

#ifdef __DATE__
#define compile_date __DATE__
#else
#define compile_date "unknown date"
#endif

extern int good_trans;
int OPTIM=1;
int gdb,xdb,gcc_assembler;

#define GET_0_1 ( (arg[2]=='0') ? 0 : 1 )

char *local_prefix, *name_prefix;

bool do_tlrecursion = 0;	/* eventually to be moved to flagsdescs.h */



/* only advertise options in manual page, other debugging options available as well */
static char usage_mess[] = "usage ( s = 0|1 ): trans [-As] [-Bs] [-Cs] [-D] [-d] [-Es] [-Fs] [-Gs] [-H] [-h] [-Is] [-K] [-Ms] [-O] [-P] [-Q] [-Rs] [-T] [-Us] [-V] [-v] [-W] [-X] [-Z] TDF-capsule output-as-file\n";

static int init_trans PROTO_S ( ( char *, char * ) ) ; /* forward reference */

int main 
    PROTO_N ( ( argc, argv ) )
    PROTO_T ( int argc X char ** argv )
{
  int a=1;
  char *arg;
  bool errflg = 0;
  bool versionflg = 0;
  char *infname=(char*)0;
  char *outfname=(char*)0;
 

  /* initialise output file */
  outf = stdout ;

  /* errors messages are output on stdout, ensure they get out */
  setbuf(stdout, NULL);

   /* set defaults for options */

   do_unroll = 1;                   /* do unroll loops */		
   do_inlining = 1;                /* do inline */		
   do_special_fns = 1;            /* do special functions */
   do_loopconsts = 1;	         /* remove constants from loops */
   do_foralls = 1;	        /* do foralls optimisation */
   gcc_assembler = 0; 
   xdb = 0;
   gdb = 0;
   OPTIM = 1;

  redo_structfns = 0;	  /* procs delivering structs recast to extra param */
  redo_structparams = 1; /* struct and union value parameters indirected   */
  diagnose = 0;		/* -H option for diagnostics */
  do_profile = 0;      /* -P option for profiling info */
  do_alloca = 1;      /* inline alloca       */
  PIC_code = 0;

  /* from tempdecs.c */
  tempdecopt = 1;		/* unset by -T option */

  /* from comment.c */
  do_comment = 0;		/* implement -C option */

  /* from translat.c */
  optim_level = 2;		/* default equiv to -O2 */


   /* process program args */
   while ( a < argc && ( arg = argv[a], arg[0] == '-' ) )
     {
       switch ( arg[1] )
	 {
	 case 'A' : do_alloca = GET_0_1; break;
	 case 'B' : flpt_const_overflow_fail = GET_0_1; break;
	 case 'C' : do_loopconsts = GET_0_1; break;
	 case 'D' :
           {
             /* -D emulates cc's +Z flag */
             PIC_code = GET_0_1;
             plusZ = 1;
             break;
	   }
	 case 'd' :
           {
             /* -d emulates cc's +z flag */
             PIC_code = GET_0_1;
             plusZ = 0;
             break;
	   }
	 case 'E' : extra_checks = 0; break;
	 case 'F' : do_foralls = GET_0_1; break;
	 case 'G' : gcc_assembler = GET_0_1; break;
	 case 'H' :
	   {
#ifdef _SYMTAB_INCLUDED
	        diagnose = 1;
                xdb = 1;  
#else
	        fprintf(stderr,"trans warning: XDB diagnostics not supported on this version of hppatrans, -H option ignored\n");
                xdb = 0;
                diagnose = 0;
#endif
	     break;
	   }
         case 'h':
	   {
              diagnose = 1;
              gdb = 1;
              gcc_assembler = 1;
	   }
	 case 'I': do_inlining = GET_0_1; break;
	 case 'K' : break;
	 case 'M' : strict_fl_div = GET_0_1; break;
	 case 'O' : /* optim_level not applicable to hp_pa */ break;
	 case 'P' :
           {
	     do_profile = 1;
	     break;
           }
	 case 'Q' : exit( EXIT_SUCCESS ); break;
	 case 'R' : round_after_flop = GET_0_1; break;
	 case 'T' : /* tempdecopt = 0, not applicable to hp_pa */ break;
	 case 'U' : do_unroll = GET_0_1; break;
	 case 'V' :
	   {
	     /* print version number */
	     fprintf(stderr,"DERA TDF->HP PA-RISC translator %d.%d: (TDF %d.%d)\nreader %d.%d:\nconstruct %d.%d:\ntranslator compilation date = %s\n ",
		    MAJOR,MINOR,MAJOR_VERSION,MINOR_VERSION,
		    reader_version,reader_revision,construct_version,
		    construct_revision,compile_date);
	     versionflg = 1;
	     break;
	   }
	 case 'W' : break;
	 case 'X' :
	   {
	     /* disable all optimisations */
	     tempdecopt = 0;
	     do_inlining = 0;
	     do_loopconsts = 0;
	     do_foralls = 0;
	     do_tlrecursion = 0;
	     do_unroll = 0;
	     break;
	   }
	 case 'Z' : report_versions = 1; break;
	 case '?' : default:
           {
    	     fprintf ( stderr, "%s : unknown option, \"%s\"\n", "trans", arg );
             errflg = 1; break;
           }
	 }  /* switch */
       a++;
     }
   
   /* we expect two further filename arguments */
   if ( argc == a+2 )
     {
       infname = argv[a] ;
       outfname = argv[a+1] ;
     }
   else if ( argc == a+1 )
     {
       infname = argv [a] ;
       outfname = "-" ;
     }
   else { errflg = 1; } ;
   
   if (errflg)
     {
       if (!versionflg)		/* no complaints for -v */
	 fprintf(stderr, usage_mess);
       exit ( EXIT_FAILURE ) ;
     }
   
   if (do_profile && PIC_code)
   {
      fprintf(stderr,"hppatrans warning: \"-P\" and \"-D\" are mutually exclusive. \"-P\" ignored.\n");
      do_profile = 0;
   }

   /* Switch off certain optimisations when in diagnostics mode. */
   if (diagnose)
   {
      optim_level = 0;
      tempdecopt = 0;
      do_inlining = 0;
      do_loopconsts = 0;
      do_foralls = 0;
      do_tlrecursion = 0;
      do_unroll = 0;
      OPTIM = 0;
      if (gdb)
         gcc_assembler = 1;
   }
   
   /* init nowhere */
  setregalt(nowhere.answhere, 0);
  nowhere.ashwhere.ashsize = 0;
  nowhere.ashwhere.ashsize = 0;

  local_prefix = "$";		/* Label prefix */
  crt_labno = 101;		/* First label; avoid conflict with reg nos */
				/* (and backward compatibility) */

   name_prefix = "";

  init_flpt();			/* initialise the floating point array */
#include "inits.h"		/* initialise common parts of translator */
  top_def = (dec *) 0;

  if ( diagnose )
  {
     init_stab();
  }

  if ( init_trans(infname,outfname) || d_capsule() || good_trans)
     exit ( EXIT_FAILURE ) ;

  exit_translator();

  /* check for output errors and close the .s file */
  if (ferror(outf) != 0 || fclose(outf) != 0)
  {
    fprintf(stderr, "hppatrans: error writing to output file %s\n", outfname);
    exit ( EXIT_FAILURE ) ;
  }

  exit ( EXIT_SUCCESS ) ;
}

/*
 * Open input and output files.
 */
static int init_trans 
    PROTO_N ( ( infname, outfname ) )
    PROTO_T ( char * infname X char * outfname )
{

  /*
   * Open files.
   */

  if (!initreader(infname))
  {
    fprintf(stderr, "hppatrans: cannot open input file %s\n", infname);
    return 3;
  }

  if (strcmp(outfname, "-") == 0)
  {
    /* "-" by convention means stdout */
    outf = stdout;
  }
  else
  {
    outf = fopen(outfname, "w+");
    if (outf == (FILE *) 0)
    {
      fprintf(stderr, "hppatrans: cannot open output file %s\n", outfname);
      return 3;
    }
  }

  return 0;			/* OK */
}

void out_rename 
    PROTO_N ( ( oldid, newid ) )
    PROTO_T ( char * oldid X char * newid )
{
    comment2 ( "renamed %s as %s", oldid, newid ) ;
    return ;
}
