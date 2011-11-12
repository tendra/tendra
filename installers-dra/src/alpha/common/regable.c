/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef lint
static char vcid[] = "$Id: regable.c,v 1.1.1.1 1998/01/17 15:56:01 release Exp $";
#endif /* lint */


/*
   regable.c
*/

/*
$Log: regable.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:01  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1996/01/17  09:30:47  john
 * Change for new caller access method
 *
 * Revision 1.3  1995/09/29  09:45:41  john
 * Added outpar
 *
 * Revision 1.2  1995/05/16  10:54:51  john
 * Cosmetic changes
 *
 * Revision 1.1.1.1  1995/03/23  10:39:19  john
 * Entered into CVS
 *
 * Revision 1.3  1995/03/17  10:12:11  john
 * Changed valregable, so bitfields can now be put into registers.
 *
*/



#include "config.h"

#include "expmacs.h"
#include "shapemacs.h"
#include "regable.h"
#include "tags.h"
#include "localtypes.h"


bool
valregable(shape s)
{
  int n = name(s);
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
  register. Uses macros isvis, isglob from expmacs.h which examine 
  the props field. 
*/

bool
fixregable(exp e)
{
  if (!isvis (e) && !isglob (e) && !isoutpar(e) && 
      name(son(e))!=caller_name_tag) {
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
      name(son(e))!=caller_name_tag) {
    shape s = sh (son (e));
    if (is_floating(name (s))) {
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



