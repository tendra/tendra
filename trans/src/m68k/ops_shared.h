/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPS_SHARED_INCLUDED
#define OPS_SHARED_INCLUDED

/*
 * The argument to jump_overflow is one of the following.
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
 * This file is a relic of the old ops.c which was split into
 * the four ops_*.c files. These routines were previously static but
 * now must be external.
 */
void branch(long, exp, int, int, int);
int branch_ins(long, int, int, int);
void jump_overflow(int);
void test_overflow(overflow_type);
void test_overflow2(int);
void push(shape, long, where);
void push_float(long, where);
void pop(shape, long, where);
void shift_aux(shape, where, where, where, int, int);
void checkalloc_stack(where, int);
int set_overflow(exp);
int have_overflow(void);
void clear_overflow(int);
void reset_round_mode(void);
void cmp_zero(shape, long, where);

/*
 * These condition codes are used to eliminate unnecessary comparison
 * instructions.
 */
extern where last_cond;
extern long last_cond_sz;

/*
 * This macro is used to set the condition codes for the where X of size Y.
 */
#define set_cond(X, Y)      \
    {                       \
        have_cond = 1;      \
        last_cond = (X);    \
        last_cond_sz = (Y); \
    }

/*
 * This macro is used to set the alterative last condition to X.
 */
#define set_cond_alt(X)      \
    {                        \
        have_cond = 3;       \
        last_cond_alt = (X); \
    }

/*
 * Output a comparison instruction
 *
 * Some assemblers (e.g. HP) reverse the order of the operands in
 * comparison instructions.  This macro handles this fact.
 */
#define ins2_cmp(I, S1, S2, X1, X2, M) \
    if (asm_cmp_reversed) {            \
        ins2(I, S2, S1, X2, X1, M);    \
    } else {                           \
        ins2(I, S1, S2, X1, X2, M);    \
    }

#endif

