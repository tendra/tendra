/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*   
  labels.c
  create and set program labels;
  The setting of a label clears all memory of the contents of
  the registers - see regexps.c
*/

#include <stdio.h>

#include <shared/xalloc.h>

#include <main/driver.h>

#include "regexps.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "inst_fmt.h"
#include "labels.h"

int   last_label = 31;

int
new_label(void)
{
        last_label++;
  return last_label;
}

void
set_label(int l)
{
  char * binasm_data;
  clear_all ();
  if (as_file){
    fprintf (as_file, "$%d:\n", l);
  }
  
  binasm_data = out_common(-l,ilabel);
  return;
}

void
set_label_no_clear(int l)
{
  if (as_file)
    fprintf (as_file, "$%d:\n", l);
  out_common(-l,ilabel);
}
