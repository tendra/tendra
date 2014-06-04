/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>


#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/is_worth.h>

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
	  ((last(c) && bro(c)!= NULL) ||
		(!last(c) && last(bro(c)) && bro(bro(c))!= NULL)) &&
	   name(father(c)) == test_tag)
   );
}
