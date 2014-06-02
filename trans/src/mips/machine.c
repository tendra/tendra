/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <reader/expmacs.h>

#include <construct/shapemacs.h>
#include <construct/installtypes.h>

/* is the result of a procedure delivering
   this shape produced in registers. */
bool
reg_result(shape sha)
{
  return ( is_floating(name(sha)) ||
    (shape_size(sha) <= 32 && name (sha) != cpdhd && name(sha) != nofhd));

}

char * local_prefix;
char * name_prefix;
