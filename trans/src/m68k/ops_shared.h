/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPS_SHARED_INCLUDED
#define OPS_SHARED_INCLUDED


/*
    KEY TO OVERFLOW JUMPS

    The argument to jump_overflow is one of the following.
*/

typedef enum {
   UNCONDITIONAL,
   ON_OVERFLOW,
   ON_CARRY,
   ON_FP_OVERFLOW,
   ON_FP_CARRY,
   ON_FP_OPERAND_ERROR
} overflow_type;

#define ON_SHAPE(s)	(is_signed(s)? ON_OVERFLOW : ON_CARRY)


/*
    PROTOTYPES

    This file is a relic of the old operations.c which was split into
    the four ops_*.c files.  These routines were previously static but
    now must be external.
*/

extern void branch(long, exp, int, int, int);
extern int branch_ins(long, int, int, int);
extern void jump_overflow(int);
extern void test_overflow(overflow_type);
extern void test_overflow2(int);
extern void push(shape, long, where);
extern void push_float(long, where);
extern void pop(shape, long, where);
extern void shift_aux(shape, where, where, where, int, int);
extern void checkalloc_stack(where, int);
extern int set_overflow(exp);
extern int have_overflow(void);
extern void clear_overflow(int);
extern void reset_round_mode(void);
extern void cmp_zero(shape, long, where);


/*
    CONDITION CODES

    These condition codes are used to eliminate unnecessary comparison
    instructions.
*/

extern where last_cond;
extern long last_cond_sz;


/*
    SET CONDITION CODES

    This macro is used to set the condition codes for the where X of
    size Y.
*/

#define  set_cond(X, Y)		\
    {					\
	have_cond = 1; \
	last_cond = (X);		\
	last_cond_sz = (Y);		\
    }


/*
    SET ALTERNATIVE CONDITION CODES

    This macro is used to set the alterative last condition to X.
*/

#define  set_cond_alt(X)		\
    {					\
	have_cond = 3; \
	last_cond_alt = (X);		\
    }


/*
    OUTPUT A COMPARISON INSTRUCTION

    Some assemblers (e.g. HP) reverse the order of the operands in
    comparison instructions.  This macro handles this fact.
*/

#define ins2_cmp(I, S1, S2, X1, X2, M) \
    if (asm_cmp_reversed) {            \
        ins2(I, S2, S1, X2, X1, M);    \
    } else {                           \
        ins2(I, S1, S2, X1, X2, M);    \
    }


#endif
