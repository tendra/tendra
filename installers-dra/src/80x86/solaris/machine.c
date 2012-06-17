/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"

#include "expmacs.h"
#include <construct/exp.h>
#include <construct/shapemacs.h>
#include "out.h"
#include "localflags.h"
#include "szs_als.h"

/* VARIABLES */
/* All variables are initialised, jmf */

char *local_prefix = ".L";
char *name_prefix = "";


/* PROCEDURES */

/* is the result of a procedure delivering
   this shape produced in registers. */
int
reg_result(shape sha)
{
  unsigned char  n = name(sha);
  if (gcc_compatible) {
    int sz = shape_size(sha);
    if (n == nofhd) {
      return 0;
    }
    if (n == cpdhd && sz > 32 && sz != 64) {
      return 0;
    }
    return 1;
  }
  if (n == cpdhd || n == nofhd) {
    return 0;
  }
  return 1;
}
