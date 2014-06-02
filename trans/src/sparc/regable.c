/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <reader/expmacs.h>
#include <local/localtypes.h>

#include <construct/shapemacs.h>
#include <construct/tags.h>

#include <main/flags.h>

#include "regable.h"

/*
  DOES A VALUE OF SHAPE s FIT INTO A FIXED REGISTER?
*/

bool 
valregable ( shape s ){
  if ( is_floating ( name ( s ) ) ) {
    /* Floating point values don't go in fixed registers */
    return 0;
  } 
  else {
    ash a ;
    a = ashof ( s ) ;
    if ( a.ashsize > 32 ) {
      /* Reject anything too big */
      return 0;
    } 
    else if ( name ( s ) == cpdhd || name (s) == nofhd) {
      /* Compound shapes are not put in registers */
      return 0;
    } 
    else if ( /*a.ashsize == a.ashalign && a.ashalign !=*/ 1 ) {
      /* Bitfields are put in registers */
      return 1;
    }
  }
  return 0;
}


/*
  DOES THE EXPRESSION e FIT INTO A FIXED REGISTER?
*/

bool 
fixregable ( exp e ){
  if ( !isvis ( e ) && !isoutpar ( e) && !isglob ( e ) && !isenvoff(e) &&
       name(son(e)) != caller_name_tag) {
    shape s = sh ( son ( e ) ) ;
    return valregable ( s ) ;
  }
  return 0;
}


/*
  DOES THE EXPRESSION e FIT INTO A FLOATING POINT REGISTER?
*/

bool 
floatregable ( exp e ){
  if ( !isvis ( e ) && !isoutpar ( e) && !isglob ( e ) && !isenvoff(e) &&
       name(son(e)) != caller_name_tag) {
    shape s = sh ( son ( e ) ) ;
    if ( is_floating ( name ( s ) ) ) {
      if ( use_long_double && shape_size ( s ) > 64 ) return 0;
      return 1;
    } 
    else {
      return 0;
    }
  }
  return 0;
}

