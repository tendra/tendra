/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <local/ash.h>

#include <tdf/tag.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>
#include <construct/shape.h>

#include "regable.h"

bool
valregable(shape s)
{
  int n = s->tag;
  if (is_floating (n)) {	
    /* check shape to see if floating point */
    return 0;
  }		
  else {
    ash a;
    a = ashof (s);		/* get ash corresponding to shape of e */
    return a.ashsize <=64 && n!=cpdhd && n!= nofhd;
  }
}


/*
  fixregable
  
  determines whether the exp e can fit in a single fixed point 
  register. Uses macros isvis, isglob from <reader/exp.h> which examine 
  the props field. 
*/

bool
fixregable(exp e)
{
  if (!isvis (e) && !isglob (e) && !isoutpar(e) && 
      son(e)->tag!=caller_name_tag) {
    shape s = sh (son (e));	/* son of ident exp is def */
    return valregable (s);
  }		
  else {
    return 0;
  }
}


/*
  floatregable
  
  determines whether the exp e can fit in a floating point 
  register, single or double.
*/
bool
floatregable(exp e)
{
  if (!isvis (e) && !isglob (e) && !isoutpar(e) &&
      son(e)->tag!=caller_name_tag) {
    shape s = sh (son (e));
    if (is_floating(s->tag)) {
      return 1;
    }
    else {
      return 0;
    }	
  }	
  else {
    return 0;
  }	
}

