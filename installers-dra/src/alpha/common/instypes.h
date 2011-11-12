/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  instypes.h
  Provides the definition of the instruction type, and some associted
  macros.
*/

#ifndef INST_TYPES
#define INST_TYPES
#if DO_SCHEDULE
#include "scheduler.h"
#endif


typedef struct{
  char *ins;
  int val;
#if DO_SCHEDULE
  Class class;
#endif
} instruction;


/*#define ins_equal(insa,insb) (!strcmp(insa.ins,insb.ins))*/
#define ins_equal(insa,insb) (insa.val == insb.val)
#define ins_symbolic_name(inst) (inst.ins)
#define ins_binid(ins) (ins.val)

#if DO_SCHEDULE
#define ins_class(ins)	(ins.class)
#endif

#endif /* INST_TYPES */

