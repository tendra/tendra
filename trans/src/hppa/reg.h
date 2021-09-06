/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef REGMACS_H
#define REGMACS_H

/*
 * HP_PA fixed registers
 */
#define GR0   0  /* Hard wired to 0           */
#define GR1   1  /* First temporary register  */
#define GR2   2
#define GR3  16  /*  C  */
#define GR4  17  /*  a  */
#define GR5  18  /*  l  */
#define GR6  19  /*  l  */
#define GR7  20  /*  e  */
#define GR8  21  /*  e  */
#define GR9  22  /*     */
#define GR10 23  /*     */
#define GR11 24  /*     */
#define GR12 25  /*     */
#define GR13 26  /*     */
#define GR14 27  /*  S  */
#define GR15 28  /*  a  */
#define GR16 29  /*  v  */
#define GR17 30  /*  e  */
#define GR18 31  /*  s  */
#define GR19  3
#define GR20  4
#define GR21  5
#define GR22  6
#define GR23 10
#define GR24  9
#define GR25  8
#define GR26  7
#define GR27 11
#define GR28 12
#define GR29 13
#define GR30 14
#define GR31 15

/*
 * HP_PA space registers
 */
#define SR0 0
#define SR1 1
#define SR2 2
#define SR3 3
#define SR4 4
#define SR5 5
#define SR6 6
#define SR7 7

/*
 * Synonyms
 */
#define SP	       GR30  /*  Stack Pointer              */
#define DP         GR27  /*  Global Data Pointer        */
#define RP         GR2   /*  Return Pointer             */
#define T4         GR19  /*  Fourth Temporary Register  */
#define T3         GR20  /*  Third Temporary Register   */
#define T2         GR21  /*  Second Temporary Register  */
#define T1         GR22  /*  First Temporary Register   */
#define MRP        GR31  /*  Millicode Return Pointer   */
#define ARG3       GR23  /*  Argument Word 3            */
#define ARG2       GR24  /*  Argument Word 2            */
#define ARG1       GR25  /*  Argument Word 1            */
#define ARG0       GR26  /*  Argument Word 0            */
#define RET0       GR28  /*  Return value               */
#define RET1       GR29  /*  Return Value               */


/*
 * Frame Pointer. GR3 is reserved for use as a
 * frame pointer iff Has_fp==1 (cf. frames.c).
 */
#define FP         GR3

/*
 * EP is a register which holds the frames original stack pointer.
 * EP=GR3, if has_vsp==1, or SP otherwise (c.f. frames.c).
 */
extern int EP;

/* Range of all fixed registers */
#define R_FIRST  0
#define R_LAST   31


/*
 * HPPA Floating Point Registers
 *
 * Two representations are used in hppatrans, 0...15 to represent 16
 * register-pairs for doubles at the higher (e.g. fregalloc) levels, and
 * 0...31 at the lower (assembler) levels.  This is somewhat confusing,
 * conversion is one way using a 'frg << 1'-like expression, often in
 * the parameter position of a ???_ins () function call.
 */

/* Floating point registers */
#define R_FR0  0 /* floating point zero */
#define R_FR4  4 /* procedure float result register */

/* Range of all floating point registers */
#define R_FLT_FIRST	0
#define R_FLT_LAST	31

/*
 * Pseudo-register codes
 */
#define R_NO_REG      100 /* code for no register allocated   */
#define R_USE_RES_REG 101 /* code to indicate result register */
#define R_DEFER_FR4    16 /* code to indicate %fr4 to be used */

/*
 * Register masks
 *
 * A register mask, with one bit per register, is used in 'space' etc.
 * A set bit indicates that the register is not available for allocation.
 */

#define	RMASK(r) (((long) 1) << (r))


/*
 * Register sets
 *
 * IS_FIXREG tests for fixed registers, IS_SREG for s-registers
 * (those preserved over procedure calls), and IS_TREG for t-registers
 * (those not so preserved). PARAM_TREGS gives all the procedure parameter
 * registers (ARG0-ARG3)
 */

#define IS_FIXREG(r)  ((r) >= R_FIRST && (r) <= R_LAST)
#define IS_SREG(r)    ((r) >= GR3 && (r) <= GR18)
#define IS_TREG(r)    (((r) > GR0 && (r) <= GR2) || ((r) >= GR19 && (r) <= GR31))

#define PARAM_TREGS   RMASK(ARG0) | RMASK(ARG1) | RMASK(ARG2) | RMASK(ARG3)
#define PROC_TREGS    -65536 /*  i.e. 11111111111111110000000000000000  */

#define IS_FLT_SREG(r)   0
/*#define IS_FLT_TREG(r) ((r)  >= 0 && (r) <= 15) */
#define IS_FLT_TREG(r)   (((r) >  7 && (r) <  12) || ((r) > 21 && (r) < 32))
#define PARAM_FLT_TREGS  0x0000
#define PROC_FLT_TREGS   0x0000
#define MAXFLOAT_TREGS   14

#endif

