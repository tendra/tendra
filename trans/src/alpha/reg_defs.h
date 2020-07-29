/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This file identifies the special registers and makes some
 * other useful definitions.
 */

#ifndef REG_DEFS_H
#define REG_DEFS_H

#define RESULT_REG 0

#define FP 15 /* frame pointer */
#define RA 26 /* return address */
#define PV 27 /* proc value */
#define AT 28 /* reserved by assembler */
#define GP 29 /* global pointer */
#define SP 30 /* stack pointer */

#define FIRST_INT_ARG   16
#define LAST_INT_ARG    21 /* 1st 6 integer arguments */
#define NUM_PARAM_REGS   6
#define FIRST_FLOAT_ARG	16
#define LAST_FLOAT_ARG	21
#define FIRST_S_REG	     9
#define PARAM_REGS	0x3f0000 /* bitmask of parameter regs */
#define NO_REG          32 /* not a register */

#define REG_SIZE    64 /* size of register in bits */
#define FLOAT_REG_0 32

#define is_param_reg(r) ((r >= FIRST_INT_ARG) && (r <= LAST_INT_ARG))

#endif

