/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CONSTANT_INCLUDED
#define CONSTANT_INCLUDED


/*
    CONSTANT EVALUATION MACROS

    All the calculation routines are based on lists of unsigned int's
    holding values in the range [0, 0xffff].  The type unsigned long is
    guaranteed to contain at least the range [0, 0xffffffff].  All
    calculations are performed in this double precision type to allow for
    overflows.  The macros LO_HALF, HI_HALF, EXTEND_VALUE and COMBINE_VALUES
    are used for converting to and from the extended type.
*/

#define NAT_DIGITS		16
#define NAT_MASK		((unsigned)0xffff)

#define LO_HALF(A)		((unsigned)((A) & NAT_MASK))
#define HI_HALF(A)		(LO_HALF((A) >> NAT_DIGITS))

#define EXTEND_VALUE(A)		((unsigned long)(A))
#define COMBINE_VALUES(A, B)	(EXTEND_VALUE(A) +\
				 (EXTEND_VALUE(B) << NAT_DIGITS))
#define EXTENDED_MAX		COMBINE_VALUES(NAT_MASK, NAT_MASK)


/*
    CONSTANT EVALUATION DECLARATIONS

    The routines in this module are concerned with constructing and
    performing calculations with integer constant expressions.
*/

extern void init_constant(void);
extern void init_float(FLOAT_TYPE);
extern FLOAT get_float(TYPE, int);

extern NAT make_nat_literal(NAT, unsigned, unsigned);
extern NAT make_large_nat(LIST(unsigned));
extern NAT make_nat_value(unsigned long);
extern NAT make_small_nat(int);
extern unsigned long get_nat_value(NAT);
extern NAT negate_nat(NAT);
extern NAT binary_nat_op(unsigned, NAT, NAT);
extern int compare_nat(NAT, NAT);
extern int eq_nat(NAT, NAT);

extern int check_nat_range(TYPE, NAT);
extern int check_type_size(TYPE, NAT);
extern NAT czero_type_value(TYPE);
extern NAT max_type_value(TYPE, int);
extern void check_bounds(int, TYPE, EXP);
extern unsigned eval_const_cond(EXP);
extern unsigned no_bits(unsigned);
extern int divides_nat(EXP, EXP);
extern int is_zero_nat(NAT);
extern int is_negative_nat(NAT);
extern int is_error_nat(NAT);
extern int is_calc_nat(NAT);
extern int is_zero_exp(EXP);
extern int is_literal(EXP);


/*
    CONSTANT EVALUATION ROUTINES

    These routines are concerned with the evaluation of integer constant
    expressions.  They are so designed that the int_lit expressions are
    precisely the constant-expressions from the grammar.
*/

extern EXP make_test_nat(EXP);
extern EXP make_unary_nat(unsigned, EXP);
extern EXP make_binary_nat(unsigned, EXP, EXP);
extern EXP make_compare_nat(NTEST, EXP, EXP);
extern EXP make_cond_nat(EXP, EXP, EXP);
extern EXP make_cast_nat(TYPE, EXP, ERROR *, unsigned);
extern EXP make_int_exp(TYPE, unsigned, NAT);
extern NAT make_nat_exp(EXP, ERROR *);
extern EXP calc_nat_value(NAT, TYPE);

#define SMALL_NAT_SIZE		257
#define SMALL_NAT_ALLOC		17
#define SMALL_FLT_SIZE		2

extern NAT small_neg_nat[SMALL_NAT_SIZE];
extern NAT small_nat[SMALL_NAT_SIZE];
extern string small_number[SMALL_FLT_SIZE];


#endif
