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


/* 80x86/overlap.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: overlap.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/01/30  12:56:41  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:39:22  jmf
 * Initial revision
 *
**********************************************************************/


#include "config.h"
#include "common_types.h"
#include "tags.h"
#include "expmacs.h"
#include "exp.h"

#include "overlap.h"

/* PROCEDURES */

/* false if a value of shape sha at
   w1 cannot overlap with one at w2.
   true if it does or might overlap.
   only used by move, so we can assume
   that w1 and w2 are addressable.
*/
int might_overlap
    PROTO_N ( (sha, w1, w2) )
    PROTO_T ( shape sha X where w1 X where w2 )
{
  exp e1 = w1.where_exp;
  exp e2 = w2.where_exp;
  exp i1, i2;
  int off1, off2, sz;

  if (name(e1) != name_tag) {
    if (name(e2) == name_tag && iscaonly(son(e2)))
      return 0;
    return 1;
  };

  if (name(e2) != name_tag) {
    if (name(e1) == name_tag && iscaonly(son(e1)))
      return 0;
    return 1;
  };

	/* both are name_tags */
  i1 = son(e1);
  i2 = son(e2);
  if (isglob(i1)) {
    if (i1 != i2)
      return 0;
    sz = shape_size(sha);
    off1 = no(e1) + w1.where_off;
    off2 = no(e2) + w2.where_off;
    if (off1 <= off2 && (off1 + sz) > off2)
      return 1;
    if (off2 <= off1 && (off2 + sz) > off1)
      return 1;
    return 0;
  };
  if (isglob(i2))
    return 0;

	/* both are local */
  if (ptno(i1) != ptno(i2))
    return 0;

  sz = shape_size(sha);
  off1 = no(e1) + no(i1) + w1.where_off;
  off2 = no(e2) + no(i2) + w2.where_off;
  if (off1 <= off2 && (off1 + sz) > off2)
    return 1;
  if (off2 <= off1 && (off2 + sz) > off1)
    return 1;
  return 0;

}
