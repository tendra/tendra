/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

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
$Date: 1998/03/27 09:47:57 $
$Revision: 1.3 $
$Log: powertrans.c,v $
 * Revision 1.3  1998/03/27  09:47:57  release
 * Changes for 4.1.2 release.
 *
 * Revision 1.2  1998/02/04  15:48:35  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:58  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:03:26  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "config.h"
#include "release.h"
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

int main PROTO_N ((argc,argv)) PROTO_T (int argc X char **argv)
{
  bool errflg = 0;
  int a=1;
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
  
  do_alloca = 1;		/* Use builtin alloca */
  do_inlining = 1;		/* Do inlining of functions */
  do_special_fns = 1;		/* Builtin procs used */
  do_loopconsts = 1;		/* Take constant expression out of loops */
  do_foralls = 1;		/* Replace indexing on loop variable by
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
  
  /* 
   * Process program args 
   * 
   * Only advertise options in manual page, other debugging 
   * options available as well 
   */
#define GET_0_1 ((arg[2] == '1') ? 1 : 0)
  while (a<argc&&(arg=argv[a], arg[0]=='-')) 
  {
    switch ( arg [1] ) 
    {
     case 'A' : do_alloca = GET_0_1 ; break ;
     case 'B' : flpt_const_overflow_fail = GET_0_1; break;	
     case 'C' : do_loopconsts = GET_0_1; break ;
     case 'E' : extra_checks = 0 ; break ;
     case 'F' : do_foralls = GET_0_1 ; break ;
     case 'H' : diagnose = 1 ; break ;
     case 'I' : do_inlining = GET_0_1 ; break ;
     case 'K' : 
       if (arg[2]=='R')
       {
	 architecture = RS6000_CODE;
       }
       else if (arg[2]=='P')
       {
	 architecture = POWERPC_CODE;
       }
       else 
       {
	 fprintf(stderr,"Unknown architecture: -K should be followed by R for rs6000 or P for powerpc\n");
       }
      break; 
     case 'M' : strict_fl_div = GET_0_1 ; break ;
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
     case 'U' : do_unroll = GET_0_1; break;
      
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
      IGNORE fprintf(stderr, "installer compilation : %s\n", __DATE__);
#endif
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
      
      /* undocumented power specific flags below here */
     case 'c' : do_comment = 1 ; break ;
      
     default : {
       fprintf ( stderr, "%s : unknown option, %s\n",
		powertrans, arg ) ;
       break ;
     }
    }
    a++ ;
  }
  
  /* we expect two further filename arguments */
  if ( argc == a + 2 ) {
    infname = argv [a] ;
    outfname = argv [ a + 1 ] ;
  } else if ( argc == a + 1 ) {
    infname = argv [a] ;
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
