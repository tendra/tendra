/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <stdlib.h>

#include <refactor/const.h>

#include "comment.h"
#include <local/out.h>


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

void 
fail ( char * mess ){
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
