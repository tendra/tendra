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


#define SPARCTRANS_CODE
#include "config.h"
#include "common_types.h"
#include "myassert.h"
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

void seed_label 
    PROTO_Z (){
  int old_last_label = last_label ;
  last_label = ( ( last_label + 100 ) / 100 ) * 100 ;
  assert ( last_label >= old_last_label ) ;
  return ;
}


/*
    CALCULATE NEXT LABEL NUMBER
*/

int new_label 
    PROTO_Z (){
  last_label++ ;
  return ( last_label ) ;
}	


/*
  PRINT A LABEL
*/
void set_label 
    PROTO_N ( ( l ) )
    PROTO_T ( int l ){
  outs ( lab_prefix ) ;
  outn ( l ) ;
  outs ( ":\n" ) ;
  assert (l > 100);
  return ;
}
