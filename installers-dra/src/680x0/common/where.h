/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef WHERE_INCLUDED
#define WHERE_INCLUDED

#include "config.h"

#include "exptypes.h"
#include <construct/installtypes.h>

#include "utility.h"

/*
    STRUCTURE REPRESENTING ALLOCATED EXPRESSIONS

    A where consists of an expression, wh_exp, and an offset wh_off.
    The wh_is field gives information on where the expression is
    stored (see below).  The wh_regs field gives the register mask
    of all the registers involved in storing the expression.
*/

typedef struct {
    exp wh_exp;
    long wh_off;
    int wh_is;
    bitpattern wh_regs;
} where;


/*
    POSSIBLE VALUES FOR THE wh_is FIELD OF A WHERE
*/


#define  Dreg		0	/* In a D-register */
#define  Areg		1	/* In an A-register */
#define  Freg		2	/* In an F-register */
#define  Value		3	/* Constant value */
#define  Parameter	4	/* On the stack (procedure argument) */
#define  Variable	5	/* On the stack (allocated variable) */
#define  RegInd		6	/* Indirect relative to a register */
#define  EffAddr	7	/* In a valid 68020 effective address */
#define  External	8	/* External data */
#define  RegPair	9	/* In a register pair */
#define  Other		10	/* All other cases */

/*
    PROCEDURES INVOLVING WHERE'S
*/

extern void init_wheres(void);
extern int shtype(shape);
extern where mw(exp, long);
extern where mnw(long);
extern bool eq_where_a(where, where, int);
extern where where_operand(mach_op*);


/*
    MACROS INVOLVING WHERE'S
*/

#define  whereis(X)		((X).wh_is)
#define  interfere(X, Y)	((X).wh_regs & (Y).wh_regs)
#define  last_use(X)		((X).wh_regs & reuseables)
#define  nw(X)		(no((X).wh_exp) + (X).wh_off)
#define  zw(X)		mw(X, 0L)
#define  eq_where(X, Y)	eq_where_a(X, Y, 1)


/*
    CONSTANT EXP'S AND WHERE'S
*/

extern exp zeroe;
extern where zero, fzero;
extern where A6_4, A0_p, A1_p, SP_p, A6_4_p, D0_D1;
extern where RW[];

extern where dummy_double_dest ; /* used to force floating-point overflow */
extern where firstlocal ; /* represents first local on the stack */

/*
    DEFINITION OF REGISTER WHERE'S
*/

#define  D0		(RW[REG_D0])
#define  D1		(RW[REG_D1])
#define  D2		(RW[REG_D2])
#define  D3		(RW[REG_D3])
#define  D4		(RW[REG_D4])
#define  D5		(RW[REG_D5])
#define  D6		(RW[REG_D6])
#define  D7		(RW[REG_D7])
#define  A0		(RW[REG_A0])
#define  A1		(RW[REG_A1])
#define  A2		(RW[REG_A2])
#define  A3		(RW[REG_A3])
#define  A4		(RW[REG_A4])
#define  A5		(RW[REG_A5])
#define  AP		(RW[REG_AP])
#define  SP		(RW[REG_SP])
#define  FP0		(RW[REG_FP0])
#define  FP1		(RW[REG_FP1])
#define  FP2		(RW[REG_FP2])
#define  FP3		(RW[REG_FP3])
#define  FP4		(RW[REG_FP4])
#define  FP5		(RW[REG_FP5])
#define  FP6		(RW[REG_FP6])
#define  FP7		(RW[REG_FP7])
#define  register(X)	(RW[(X)])

#endif
