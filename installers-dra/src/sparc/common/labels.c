/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */



/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/labels.c,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: labels.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1997/08/23  13:53:52  pwe
 * initial ANDF-DE
 *
 * Revision 1.2  1995/05/26  12:59:00  john
 * Reformatting
 *
 * Revision 1.1.1.1  1995/03/13  10:18:41  john
 * Entered into CVS
 *
 * Revision 1.3  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.3  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.2  1994/06/13  12:55:11  djch
 * added assert to spot uninitialized labels
 *
 * Revision 1.1  1994/05/03  14:49:40  djch
 * Initial revision
 *
 * Revision 1.2  93/09/27  14:46:44  14:46:44  ra (Robert Andrews)
 * Introduce the variable lab_prefix to stand for the label prefix.
 * 
 * Revision 1.1  93/06/24  14:58:34  14:58:34  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#include <assert.h>

#define SPARCTRANS_CODE
#include "config.h"
#include "addrtypes.h"
#include "regexps.h"
#include "labels.h"
#include "out.h"


/*
  LABEL PREFIX
*/

char *lab_prefix = "" ;


/*
  CURRENT LABEL NUMBER
  The count starts at 50 to avoid confusion with registers.
*/

static int last_label = 50 ;


/*
  ROUND UP CURRENT LABEL NUMBER
  This rounds the current label number up to the next multiple of 
  100.  It is called at the start of each procedure to aid 
  readability.
*/

void 
seed_label (void){
  int old_last_label = last_label ;
  last_label = ( ( last_label + 100 ) / 100 ) * 100 ;
  assert ( last_label >= old_last_label ) ;
  return ;
}


/*
    CALCULATE NEXT LABEL NUMBER
*/

int 
new_label (void) {
  last_label++ ;
  return last_label;
}	


/*
  PRINT A LABEL
*/
void 
set_label ( int l ){
  outs ( lab_prefix ) ;
  outn ( l ) ;
  outs ( ":\n" ) ;
  assert (l > 100);
  return ;
}
