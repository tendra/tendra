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


typedef struct{
  char *ins;
  int val;
} instruction;


/*#define ins_equal(insa,insb) (streq(insa.ins,insb.ins))*/
#define ins_equal(insa,insb) (insa.val == insb.val)
#define ins_symbolic_name(inst) (inst.ins)
#define ins_binid(ins) (ins.val)

#endif /* INST_TYPES */

