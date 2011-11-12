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

/*
$Log: instypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:00  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/05/16  10:52:49  john
 * Cosmetic change
 *
 * Revision 1.1.1.1  1995/03/23  10:39:36  john
 * Entered into CVS
 *
 * Revision 1.2  1995/03/23  10:08:00  john
 * Changed instruction type to include class information.
 *
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

