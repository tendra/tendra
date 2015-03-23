/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/error.h>

#include <construct/installtypes.h>
#include <construct/dec.h>

#include <main/driver.h>
#include <main/print.h>

#include "translate.h"
#include "labels.h"


static int last_label = 50;	/* >32 to avoid possible confusion with regs */


void seed_label(void)
{
  /*
   * Round label numbering up to next 100. Normally called at function start.
   * Purpose is to make assembler output more human-readable, and to make
   * minor code changes less likely to affect next function, so diff output
   * more compact.
   */
  int old_last_label = last_label;

  last_label = ((last_label + 100) / 100) * 100;

  UNUSED(old_last_label);
  assert(last_label >= old_last_label);
}


int new_label(void)
{
  last_label++;
  return last_label;
}


void set_label(int l)
{
  asm_label( "L.%d", l);
}
