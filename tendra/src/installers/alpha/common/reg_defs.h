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


/* 	$Id: reg_defs.h,v 1.1.1.1 1998/01/17 15:56:01 release Exp $	 */

/*
   reg_defs.h

   This file identifies the special registers and makes some 
   other useful definitions.
*/

/*
$Log: reg_defs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:01  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/10/27  16:22:12  john
 * Change to general procs
 *
 * Revision 1.2  1995/05/23  13:25:20  john
 * Added new register definition
 *
 * Revision 1.1.1.1  1995/03/23  10:39:18  john
 * Entered into CVS
 *
 * Revision 1.7  1995/03/23  10:12:38  john
 * Added definition of FLOAT_REG_0
 *
*/

#ifndef REG_DEFS_H
#define REG_DEFS_H

#define RESULT_REG 0
#define FP 15			/* frame pointer */
#define RA 26			/* return address */
#define PV 27			/* proc value */
#define AT 28			/* reserved by assembler */
#define GP 29			/* global pointer */
#define SP 30			/* stack pointer */
#define FIRST_INT_ARG     16
#define LAST_INT_ARG      21	/* 1st 6 integer arguments */
#define NUM_PARAM_REGS 6
#define FIRST_FLOAT_ARG	  16
#define LAST_FLOAT_ARG	  21
#define FIRST_S_REG	9
#define PARAM_REGS	0x3f0000	/* bitmask of parameter regs */
#define NO_REG 32		/* not a register */

#define REG_SIZE 64		/* size of register in bits */
#define FLOAT_REG_0	32	 

#define is_param_reg(X) ((X>=FIRST_INT_ARG) && (X<= LAST_INT_ARG))
#endif


