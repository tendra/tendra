/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* 80x86/is_worth.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: is_worth.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/01/30  12:56:29  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.5  1994/07/15  13:58:07  jmf
 * Admit global real consts. Safeguard father.
 *
 * Revision 1.4  1994/07/12  15:13:07  jmf
 * protected father for test_tag
 *
 * Revision 1.3  1994/07/12  15:12:11  jmf
 * Replaced keywords
 *
 * Revision 1.1  1994/07/12  14:35:40  jmf
 * Initial revision
 *
**********************************************************************/


#include "config.h"
#include "tags.h"
#include "expmacs.h"
#include "exp.h"
#include "shapemacs.h"
#include "is_worth.h"

/* PROCEDURES */

int is_worth
(exp c)
{
				/* decide if constant c is worth declaring
				   separately */
  unsigned char cnam = name(c);

  if (name(sh(c)) == realhd && cnam == cont_tag &&
	name(son(c)) == name_tag && isvar(son(son(c))) &&
	isglob(son(son(c))))
    return 1;

  if (cnam == cont_tag && name(son(c)) == name_tag &&
       !isvar(son(son(c)))) {
    return 1;
  }

  return((!is_o(cnam) && cnam != clear_tag &&
	   cnam != int_to_bitf_tag && cnam != bitf_to_int_tag) ||
  /* ignore simple things unless ... */
     (cnam == cont_tag && name(son(c)) == cont_tag &&
	name(son(son(c))) == name_tag)
      || (cnam == name_tag &&
         (isloadparam(son(c)) || isparam(son(c))) &&
          !isvar(son(c)) &&
          shape_size(sh(c)) <= 32

          && name(sh(c))!= shrealhd

        )
      || (cnam == cont_tag && name(son(c)) == name_tag &&
	   isvar(son(son(c))) && isglob(son(son(c))) &&
	  ((last(c) && bro(c)!= nilexp) ||
		(!last(c) && last(bro(c)) && bro(bro(c))!= nilexp)) &&
	   name(father(c)) == test_tag)
   );
}
