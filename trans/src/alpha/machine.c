/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <local/expmacs.h>
#include <local/localtypes.h>

#include <construct/shapemacs.h>
#include <construct/installtypes.h>

int
reg_result(shape sha)
{
  /* is the result of a procedure delivering
     this shape produced in registers. */
  return name(sha) != cpdhd && name(sha) != nofhd;
}

char * local_prefix;
char * name_prefix;
