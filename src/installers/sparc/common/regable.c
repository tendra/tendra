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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/regable.c,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: regable.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1996/09/06  16:50:35  pwe
 * fix outpar doubles for postlude
 *
 * Revision 1.5  1995/12/15  10:26:39  john
 * Made caller_names non-regable
 *
 * Revision 1.4  1995/09/25  16:35:45  john
 * Fix for outpar
 *
 * Revision 1.3  1995/05/26  13:01:16  john
 * Reformatting
 *
 * Revision 1.2  1995/03/28  12:24:40  john
 * Stopped putting arrays in registers
 *
 * Revision 1.1.1.1  1995/03/13  10:18:53  john
 * Entered into CVS
 *
 * Revision 1.3  1994/12/01  13:36:27  djch
 * Fix fixregable and floatregable to avoid envoffset's
 *
 * Revision 1.2  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.1  1994/05/03  14:49:50  djch
 * Initial revision
 *
 * Revision 1.2  93/09/27  14:54:38  14:54:38  ra (Robert Andrews)
 * Long double values should not be put in registers (yet),
 * 
 * Revision 1.1  93/06/24  14:59:08  14:59:08  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE
#include "config.h"
#include "expmacs.h"
#include "common_types.h"
#include "shapemacs.h"
#include "tags.h"
#include "regable.h"

/*
  DOES A VALUE OF SHAPE s FIT INTO A FIXED REGISTER?
*/

bool valregable 
    PROTO_N ( ( s ) )
    PROTO_T ( shape s ){
  if ( is_floating ( name ( s ) ) ) {
    /* Floating point values don't go in fixed registers */
    return ( 0 ) ;
  } 
  else {
    ash a ;
    a = ashof ( s ) ;
    if ( a.ashsize > 32 ) {
      /* Reject anything too big */
      return ( 0 ) ;
    } 
    else if ( name ( s ) == cpdhd || name (s) == nofhd) {
      /* Compound shapes are not put in registers */
      return ( 0 ) ;
    } 
    else if ( /*a.ashsize == a.ashalign && a.ashalign !=*/ 1 ) {
      /* Bitfields are put in registers */
      return ( 1 ) ;
    }
  }
  return ( 0 ) ;
}


/*
  DOES THE EXPRESSION e FIT INTO A FIXED REGISTER?
*/

bool fixregable 
    PROTO_N ( ( e ) )
    PROTO_T ( exp e ){
  if ( !isvis ( e ) && !isoutpar ( e) && !isglob ( e ) && !isenvoff(e) &&
       name(son(e)) != caller_name_tag) {
    shape s = sh ( son ( e ) ) ;
    return ( valregable ( s ) ) ;
  }
  return ( 0 ) ;
}


/*
  DOES THE EXPRESSION e FIT INTO A FLOATING POINT REGISTER?
*/

bool floatregable 
    PROTO_N ( ( e ) )
    PROTO_T ( exp e ){
  if ( !isvis ( e ) && !isoutpar ( e) && !isglob ( e ) && !isenvoff(e) &&
       name(son(e)) != caller_name_tag) {
    shape s = sh ( son ( e ) ) ;
    if ( is_floating ( name ( s ) ) ) {
#if use_long_double
      if ( shape_size ( s ) > 64 ) return ( 0 ) ;
#endif
      return ( 1 ) ;
    } 
    else {
      return ( 0 ) ;
    }
  }
  return ( 0 ) ;
}

