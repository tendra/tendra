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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/comment.c,v 1.1.1.1 1998/01/17 15:55:53 release Exp $
--------------------------------------------------------------------------
$Log: comment.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/05/26  12:56:43  john
 * Reformatting
 *
 * Revision 1.1.1.1  1995/03/13  10:18:29  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.2  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.1  1994/05/03  14:49:32  djch
 * Initial revision
 *
 * Revision 1.4  93/08/27  11:23:07  11:23:07  ra (Robert Andrews)
 * Need to include common_types.h to shut lint up.
 * 
 * Revision 1.3  93/08/13  14:35:24  14:35:24  ra (Robert Andrews)
 * Got rid of the comment routines.
 * 
 * Revision 1.2  93/06/29  14:22:54  14:22:54  ra (Robert Andrews)
 * Added new variable, sparctrans, giving the executable name for use in
 * error messages.
 * 
 * Revision 1.1  93/06/24  14:58:03  14:58:03  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE
#include "config.h"
#include "common_types.h"
#include "comment.h"
#include "const.h"
#include "out.h"


/*
  PROGRAM NAME
*/

char *sparctrans = "sparctrans" ;


/*
  COMMENT FAILURES
*/

bool do_comment = 0 ;


/*
  ERROR REPORTING ROUTINE
*/

void fail 
    PROTO_N ( ( mess ) )
    PROTO_T ( char * mess ){
  if ( do_comment ) {
    outs ( "!! TRANSLATION FAILED : " ) ;
    outs ( mess ) ;
    outnl () ;
    fflush ( as_file ) ;
  }
  fprintf ( stderr, "%s : error : %s\n", sparctrans, mess ) ;
  if ( !do_comment ) exit ( EXIT_FAILURE ) ;
  /* generate more code to give the error context when commenting */
  return ;
}
