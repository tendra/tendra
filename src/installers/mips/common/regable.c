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
#include "expmacs.h"
#include "common_types.h"
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


bool valregable
    PROTO_N ( (s) )
    PROTO_T ( shape s )
{
  int n = name(s);
  if (is_floating (n)) {	/* check shape to see if floating point */
    return 0;
  }
  else {
    ash a;
    a = ashof (s);		/* get ash corresponding to shape of e */

/* ALTERATION #1 */
    return (a.ashsize <=32  && n!=cpdhd && n!= nofhd && n!=tophd);

  }
}

bool fixregable
    PROTO_N ( (e) )
    PROTO_T ( exp e )
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

bool floatregable
    PROTO_N ( (e) )
    PROTO_T ( exp e )
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
