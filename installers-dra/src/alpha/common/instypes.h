/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
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

