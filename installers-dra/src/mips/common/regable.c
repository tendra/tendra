/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */







/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:06 $
$Revision: 1.1.1.1 $
$Log: regable.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/12/12  09:02:19  currie
 * out_pars not regable
 *
 * Revision 1.2  1995/09/22  15:49:17  currie
 * added outpar
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/******************************************************************
		regable.c

******************************************************************/


#include "config.h"

#include "localtypes.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "tags.h"
#include "regable.h"

/***************************************************************
	fixregable

determines whether the exp e can fit in a single fixed point register. Uses
macros isvis, isglob, iscaonly from expmacs.h which examine the props
field. The iscaonly bit is set by proc independent if the tag is only used
by the contents operator or as the left hand side of an assignment. The
procedure also uses the macro is_floating from shapemacs.h which checks
the shape number is in the range for floating point shapes.
****************************************************************/


bool
valregable(shape s)
{
  int n = name(s);
  if (is_floating (n)) {	/* check shape to see if floating point */
    return 0;
  }
  else {
    ash a;
    a = ashof (s);		/* get ash corresponding to shape of e */

/* ALTERATION #1 */
    return a.ashsize <=32  && n!=cpdhd && n!= nofhd && n!=tophd;

  }
}

bool
fixregable(exp e)
{
  if (!isvis (e) && !isoutpar(e) && !isglob (e)
		&& name(son(e)) != caller_name_tag) {
    shape s = sh (son (e));	/* son of ident exp is def */
    return valregable (s);
  }
  else {
    return 0;
  }
}

/***************************************************************
	floatregable

determines whether the exp e can fit in a floating point register, single
or double.
***************************************************************/

bool
floatregable(exp e)
{
  if (!isvis (e) && !isoutpar(e) && !isglob (e)
	&& name(son(e)) != caller_name_tag) {
    shape s = sh (son (e));
    if is_floating
      (name (s)) {
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
