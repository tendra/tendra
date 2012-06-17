/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* dragonfly/machine.c */

#include "config.h"
#include "expmacs.h"
#include <construct/exp.h>
#include <construct/shapemacs.h>
#include "out.h"
#include "localflags.h"
#include "szs_als.h"

/* VARIABLES */

int dragonfly_elf = 1;

char *local_prefix = ".L";
char *name_prefix = "";



/* PROCEDURES */

void
set_dragonfly_format(int elf)
{
        dragonfly_elf = elf;
        if (elf == 1) {
                local_prefix = ".L";
                name_prefix = "";
        } else {
                local_prefix = "L";
                name_prefix = "_";
        }
}

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
    if (n == cpdhd && sz != 8 && sz != 16 && sz != 32 && sz != 64) {
      return 0;
    }
    return 1;
  }
  if (n == cpdhd || n == nofhd) {
    return 0;
  }
  return 1;
}
