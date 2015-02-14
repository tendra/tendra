/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <main/driver.h>
#include <main/print.h>

#include "addrtypes.h"
#include "regexps.h"
#include "labels.h"


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
  asm_label("%s%d", lab_prefix, l);
  assert (l > 100);
}
