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

#include "config.h"

#include "regexps.h"
#include "ibinasm.h"
#include "out_ba.h"
#if DO_SCHEDULE
#include "scheduler.h"
#endif
#include "inst_fmt.h"
#include "labels.h"

extern  FILE * as_file;

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
#if DO_SCHEDULE
  Instruction new_ins = getinst();
  Instruction_data ins_dat  = get_new_ins_data();
#endif
  char * binasm_data;
#if DO_SCHEDULE
  char * outline = (char*)xcalloc(80,sizeof(char));
  setclass(new_ins,class_null);
  setlabel(new_ins,l);
  setsets_pc(new_ins,true);
#endif
  clear_all ();
  if (as_file){
#if !DO_SCHEDULE    
    fprintf (as_file, "$%d:\n", l);
#else
    sprintf(outline,"$%d:\n",l);
#endif
  }
  
/*  setdata(new_ins,outline);*/
  binasm_data = out_common(-l,ilabel);
#if DO_SCHEDULE
  set_instruction_text(ins_dat,outline);
  set_instruction_binasm(ins_dat,binasm_data);
  setdata(new_ins,ins_dat);
/*
  setbase_label(new_ins,l);
  setoffset_label(new_ins,0);
  setsize_label(new_ins,0);*/
  process_instruction(new_ins);
#endif
  /*add_instruction(new_ins);*/
  return;
}

void
set_label_no_clear(int l)
{
  if (as_file)
    fprintf (as_file, "$%d:\n", l);
  out_common(-l,ilabel);
}
