/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 *  This file contains functions which perform 64-bit
 *  arithmetic on 32-bit machines.
 *
 *  The functions all use abstract types which refer
 *  to some characteristic of that type, so that INT32
 *  is a 32-bit signed integer, and UINT64 is a 32-bit
 *  unsigned integer.  These types are defined in the
 *  file 'INT64_types.h'.
 */

#ifndef NDEBUG
#include <stdio.h>
#endif

#ifndef NDEBUG
#include <shared/check.h>
#endif

#if defined(__TenDRA__)
#include "abstract.h"
#else
#include "concrete.h"
#endif

#undef STATIC
#ifdef NDEBUG
#define STATIC static
#else
#define STATIC
#endif

#define UINT32_const(X) ((UINT32) (X))

/*
 * Error Treatments handling
 */

int __TDFerror;

#define OVERFLOW_ERROR (__TDFerror = -1)
#if USE_SEPARATE_DIV_ZERO_ERROR
#define DIV_ZERO_ERROR (__TDFerror =  0)
#else
#define DIV_ZERO_ERROR OVERFLOW_ERROR
#endif
#define CLEAR_ERRORS   (__TDFerror =  1)

static TDF_INT64 TDFUplus(TDF_INT64, TDF_INT64);
static TDF_INT64 TDFUminus(TDF_INT64, TDF_INT64);
static TDF_INT64 TDFUmult(TDF_INT64, TDF_INT64);
static TDF_INT64 TDFUdiv_rem(TDF_INT64, TDF_INT64, UINT32);
static TDF_INT64 TDFUshr(TDF_INT64, UINT32);

#ifndef NDEBUG
INT64	make_INT64(INT32, UINT32);
UINT64	make_UINT64(UINT32, UINT32);
void 	INT64_print(char *,  INT64, char *);
void	UINT64_print(char *, UINT64, char *);
#endif

INT64 __TDFUs_plus(INT64, INT64);
INT64 __TDFUs_minus(INT64, INT64);
INT64 __TDFUs_mult(INT64, INT64);
INT64 __TDFUs_div1(INT64, INT64);
INT64 __TDFUs_div2(INT64, INT64);
INT64 __TDFUs_rem1(INT64, INT64);
INT64 __TDFUs_rem2(INT64, INT64);
INT64 __TDFUneg(INT64);
INT64 __TDFUabs(INT64);
INT64 __TDFUsswiden(INT32);
INT64 __TDFUuswiden(UINT32);
INT32 __TDFUssshorten(INT64);
INT32 __TDFUusshorten(UINT64);
INT64 __TDFUu642s64(UINT64);
INT64 __TDFUs_max(INT64, INT64);
INT64 __TDFUs_min(INT64, INT64);
int __TDFUs_test(INT64, INT64);

UINT64 __TDFUu_plus(UINT64, UINT64);
UINT64 __TDFUu_minus(UINT64, UINT64);
UINT64 __TDFUu_mult(UINT64, UINT64);
UINT64 __TDFUu_div2(UINT64, UINT64);
UINT64 __TDFUu_rem2(UINT64, UINT64);
UINT64 __TDFUu_shl(UINT64, UINT32);
UINT64 __TDFUu_shr(UINT64, UINT32);
UINT64 __TDFUuuwiden(UINT32);
UINT64 __TDFUsuwiden(INT32);
UINT32 __TDFUsushorten(INT64);
UINT32 __TDFUuushorten(UINT64);
UINT64 __TDFUs642u64(INT64);
UINT64 __TDFUu_max(UINT64, UINT64);
UINT64 __TDFUu_min(UINT64, UINT64);
int __TDFUu_test(UINT64, UINT64);
UINT64 __TDFUand(UINT64, UINT64);
UINT64 __TDFUor(UINT64, UINT64);
UINT64 __TDFUxor(UINT64, UINT64);
UINT64 __TDFUnot(UINT64);

#define TDFUis_positive(X) (hi_32(X) >= 0)
#define TDFUis_negative(X) (hi_32(X) <  0)
#define TDFUis_zero(X)     (hi_32(X) == 0 && lo_32(X) == 0)
#define TDFUis_nonzero(X)  (hi_32(X) != 0 || lo_32(X) != 0)

/*
 * TDFUshl simply masks out the necessary bits as appropriate
 * for shifts of less than 32 and those greater than 32.
 *
 * No error checking - should have already been done.
 *
 * Defined here as a macro, which is implemented as a TDF token.
 * This token is then used in the PL_TDF file which implements
 * the remaining functions in the 64-bit arithmetic library.
 *
 * The token must contain IF, but TDFC only allows this to be
 * done with "procedure tokens". If non-TenDRA compilation is
 * to be possible, this macro cannot be used directly since
 * constants will produce illegal shift values, so a function
 * has to be defined.
 *
 * A function cannot have the desired side-effect of updating
 * the first parameter (without making it into a pointer),
 * so another macro is used (which calls the function defined
 * using the macro which produces the definition of the TDF token.
 */
#define _TDFUshl(shifted_a, a, n) {                                   \
    if (n > 32) {                                                     \
        /* assuming n <= 64 */                                        \
        hi_u32(shifted_a) = lo_u32(a) << (n -32);                     \
        lo_u32(shifted_a) = (UINT32) 0x00000000;                      \
    } else {                                                          \
        /* (0 < n <= 32) */                                           \
        hi_u32(shifted_a) = (lo_u32(a) >> (32-n)) | (hi_u32(a) << n); \
        lo_u32(shifted_a) =  lo_u32(a) << n;                          \
    }                                                                 \
}

#ifdef __TenDRA__

/* Want to use this value in the .pl file */
#pragma token EXP rvalue : int : BIGEND_INT64 #
#ifndef BIGENDIAN_INT64
#define BIGEND_INT64 0
#else
#define BIGEND_INT64 BIGENDIAN_INT64
#endif

/* Use a "procedure token" to implement TDFUshl */
#pragma token PROC(EXP lvalue : TDF_INT64 : , \
        EXP rvalue : TDF_INT64 : ,            \
        EXP rvalue : UINT32 :)                \
    STATEMENT TDFUshl #

#define TDFUshl(shifted_a, a, n) _TDFUshl((shifted_a), (a), (n))

#else

/* Use a macro (which calls a function) to implement TDFUshl */
TDF_INT64 __TDFUshl(TDF_INT64, UINT32);
TDF_INT64
__TDFUshl(TDF_INT64 a, UINT32 n)
{
	TDF_INT64 tmp;

	_TDFUshl(tmp, a, n);

	return tmp;
}

#define TDFUshl(shifted_a, a, n) { shifted_a = __TDFUshl(a, n); }

#endif


/*
 * Generic function to add two 64-bit integers,
 * interpretting each as an unsigned value.
 */
static TDF_INT64
TDFUplus(TDF_INT64 a, TDF_INT64 b)
{
	TDF_INT64 sum;

	lo_u32(sum) = lo_u32(a) + lo_u32(b);

	if (lo_u32(sum) < lo_u32(a)) {
		hi_u32(sum) = hi_u32(a) + hi_u32(b) + 1;
	} else {
		hi_u32(sum) = hi_u32(a) + hi_u32(b);
	}

	return sum;
}

/*
 * Interpret signed numbers as unsigned, add them as unsigned numbers,
 * then reinterpret as signed.
 *
 * Error handling if two positives produce a negative or two negative
 * produce a positive, else alright.
 */
INT64
__TDFUs_plus(INT64 param_a, INT64 param_b)
{
	TDF_INT64 sum, a, b;

	PARAM(a) = param_a;
	PARAM(b) = param_b;

	CLEAR_ERRORS;

	sum = TDFUplus(a, b); /* add as unsigned numbers */

	if (TDFUis_positive(a)    /* a     >= 0 */
	&&  TDFUis_positive(b)    /* b     >= 0 */
	&&  TDFUis_negative(sum)) /* a + b <  0 */
	{
		OVERFLOW_ERROR;
	}

	if (TDFUis_negative(a)    /* a     <  0 */
	&&  TDFUis_negative(b)    /* b     <  0 */
	&&  TDFUis_positive(sum)) /* a + b >= 0 */
	{
		OVERFLOW_ERROR;
	}

	return PARAM(sum);
}

/*
 * Adds arguments, and tests to see if sum is less than the first
 * argument for error detection.
 */
UINT64
__TDFUu_plus(UINT64 param_a, UINT64 param_b)
{
	TDF_INT64 sum, a, b;

	UPARAM(a) = param_a;
	UPARAM(b) = param_b;

	CLEAR_ERRORS;

	sum = TDFUplus(a, b);

	if ((hi_u32(sum) <= hi_u32(a)) &&
	    (lo_u32(sum) <  lo_u32(a))) /* sum < a */
	{
		OVERFLOW_ERROR;
	}

	return UPARAM(sum);
}

/*
 * Generic function to subtract two 64-bit integers,
 * interpretting each as an unsigned value.
 */
static TDF_INT64
TDFUminus(TDF_INT64 a, TDF_INT64 b)
{
	TDF_INT64 sum;

	lo_u32(sum) = lo_u32(a) - lo_u32(b);

	if (lo_u32(sum) > lo_u32(a)) {
		hi_u32(sum) = hi_u32(a) - hi_u32(b) - 1;
	} else {
		hi_u32(sum) = hi_u32(a) - hi_u32(b);
	}

	return sum;
}

/*
 * Interpret signed numbers as unsigned, add them as unsigned numbers,
 * then reinterpret as signed.
 *
 * Error handling if two positives produce a negative or two negative
 * produce a positive, else alright.
 */
INT64
__TDFUs_minus(INT64 param_a, INT64 param_b)
{
	TDF_INT64 diff, a, b;

	PARAM(a) = param_a;
	PARAM(b) = param_b;

	CLEAR_ERRORS;

	diff = TDFUminus(a, b); /* subtract as unsigned numbers */

	if (TDFUis_positive(a)     /* a     >= 0 */
	&&  TDFUis_negative(b)     /* b     <  0 */
	&&  TDFUis_negative(diff)) /* a - b <  0 */
	{
		OVERFLOW_ERROR;
	}

	if (TDFUis_negative(a)     /* a     <  0 */
	&&  TDFUis_positive(b)     /* b     >= 0 */
	&&  TDFUis_positive(diff)) /* a - b >= 0 */
	{
		OVERFLOW_ERROR;
	}

	return PARAM(diff);
}

/*
 * Adds arguments, and tests to see if sum is less than
 * the first argument for error detection.
 */
UINT64
__TDFUu_minus(UINT64 param_a, UINT64 param_b)
{
	TDF_INT64 diff, a, b;

	UPARAM(a) = param_a;
	UPARAM(b) = param_b;

	CLEAR_ERRORS;

	diff = TDFUminus(a, b);

	if (hi_u32(diff) >= hi_u32(a) &&
	    lo_u32(diff) >  lo_u32(a)) /* diff > a */
	{
		OVERFLOW_ERROR;
	}

	return UPARAM(diff);
}

/*
 *           a3   a2   a1   a0
 *   x       b3   b2   b1   b0
 *  ----------------------------
 *                     a0 x b0    (stage 1)
 *
 *                a1 x b0         (stage 2)
 *                a0 x b1
 *
 *           a2 x b0              (stage 3)
 *           a1 x b1
 *           a0 x b2
 *
 *      a3 x b0                   (stage 4)
 *      a2 x b1
 *      a1 x b2
 *      a0 x b3
 *
 * These are the only terms necessary to produce the answer.
 * The other terms must all be used at error checking to ensure
 * that overflow does not occur.
 *
 * By adding the contributions in this order, it is possible to control
 * the size of the sum as each stage, i.e. only certain terms need
 * to be considered, reducing the number of steps in the addition.
 *
 * If the parameter 'error_check' is non-zero, error-checking is done:
 * its value is reset to zero if non occur.
 */

#define hi_u16(X)	((X) >> 16)
#define lo_u16(X)	((X) & ((UINT32)0xffff))

static TDF_INT64
TDFUmult(TDF_INT64 a, TDF_INT64 b)
{
	TDF_INT64 prod;

	UINT32 a0, a1, a2, a3;
	UINT32 b0, b1, b2, b3;
	UINT32 work1, work2;

	a0 = lo_u16(lo_u32(a));
	a1 = hi_u16(lo_u32(a));
	a2 = lo_u16(hi_u32(a));
	a3 = hi_u16(hi_u32(a));

	b0 = lo_u16(lo_u32(b));
	b1 = hi_u16(lo_u32(b));
	b2 = lo_u16(hi_u32(b));
	b3 = hi_u16(hi_u32(b));

	if (a1 == 0 && a2 == 0 && a3 == 0
	&&  b1 == 0 && b2 == 0 && b3 == 0)
	{
		/* result fits into 32 bits */
		hi_u32(prod) = 0;
		lo_u32(prod) = a0 * b0;
		return prod;
	}

/* stage 1 */

	lo_u32(prod) = a0 * b0;

/* stage 2 */

	work1 = a1 * b0;
	work2 = work1 + a0 * b1;
	if (work2 < work1) {
		hi_u32(prod) = (UINT32) 0x10000; /* set carry in result */
	} else {
		hi_u32(prod) = 0;  /* must initialise somewhere */
	}

	work1 = lo_u16(work2); /* lo-16 bits of sum */
	work2 = hi_u16(work2); /* hi-16 bits of sum */

	lo_u32(prod) += (work1 << 16);
	if ((work1 << 16) > lo_u32(prod)) {
		/* wrap */
		hi_u32(prod) += work2 + 1;
	} else {
		hi_u32(prod) += work2;
	}

/* stage 3 */

	work1 = a2 * b0;
	work2 = work1 + a1 * b1;

	if (work1 > work2) {
		OVERFLOW_ERROR;
	}

	work1 = work2 + a0 * b2;

	if (work2 > work1) {
		OVERFLOW_ERROR;
	}

	hi_u32(prod) += work1;

	if (work1 > hi_u32(prod)) {
		OVERFLOW_ERROR;
	}

/* stage 4 */

	work1 = a3 * b0;
	work2 = a2 * b1;

	if (work1 > ((UINT32) 0xffff) || work2 > ((UINT32) 0xffff)) {
		OVERFLOW_ERROR;
	}

	work1 = work1 + work2;
	work2 = a1 * b2;

	if (work2 > ((UINT32)0xffff)) {
		OVERFLOW_ERROR;
	}

	work1 = work1 + work2;
	work2 = a0 * b3;
	work1 = work1 + work2;

	if (work1 > ((UINT32) 0xffff) || work2 > ((UINT32) 0xffff)) {
		OVERFLOW_ERROR;
	}

	work2 = work1 << 16; /* we've made sure this will work */
	hi_u32(prod) += work2;

	if (work2 > hi_u32(prod) /* this mustn't overflow */
	||  a3 * b1 != 0 /* remaining contributions must all be zero */
	||  a2 * b2 != 0
	||  a1 * b3 != 0
	||  a3 * b2 != 0
	||  a2 * b3 != 0
	||  a3 * b3 != 0)
	{
		OVERFLOW_ERROR;
	}

	return prod;
}

/*
 * Implements long multiplication in binary,
 * checking for errors as it goes along.
 */
INT64
__TDFUs_mult(INT64 param_a, INT64 param_b)
{
	TDF_INT64 prod, a, b;
	int sign;

	PARAM(a) = param_a;
	PARAM(b) = param_b;

	CLEAR_ERRORS;

	sign = ((hi_32(a) ^ hi_32(b)) < 0); /* sign of result */

	PARAM(a) = __TDFUabs(param_a);
	PARAM(b) = __TDFUabs(param_b);

	prod = TDFUmult(a, b);
	/* any overflow will be flagged */

	if (hi_32(prod) < 0) { /* definitely okay if this is false */
		if (sign == 0 /* positive int too big for INT_64 */
		||  hi_u32(prod) > ((UINT32) 0x80000000) /* signed int too big for INT_64 */
		||  lo_u32(prod) > ((UINT32) 0x00000000))
		{
			OVERFLOW_ERROR;
		}
	}

	if (sign == 0 /* result is unsigned */
	|| (hi_u32(prod) == ((UINT32) 0x80000000)   /* - this number has the same     */
	&&  lo_u32(prod) != ((UINT32) 0x00000000))) /* representation as its negation */
	{
		return PARAM(prod);
	}

	return __TDFUneg(PARAM(prod));
}

/*
 * __TDFUu_mult implements long multiplication in binary,
 * checking for errors as it goes along.
 */

#if 0

UINT64
__TDFUu_mult(UINT64 param_a, UINT64 param_b)
{
	TDF_INT64 prod, a, b;

	if (__TDFUu_test(param_b, UPARAM(const_u0)) == 0) {
		return UPARAM(const_u0);
	}

	UPARAM(a) = param_a;
	UPARAM(b) = param_b;

	prod = const_u0;

	while (__TDFUu_test(UPARAM(b), UPARAM(const_u1)) != 0) {
		if ((lo_u32(b) & 1) != 0) {
			prod = __TDFUu_plus(UPARAM(prod), UPARAM(a));
			/* any overflow will be flagged */
		}

		PARAM(a) = __TDFUu_shl(UPARAM(a), (UINT32)1);
		PARAM(b) = __TDFUu_shr(UPARAM(b), (UINT32)1);
	}

	return UPARAM(__TDFUu_plus(prod, a));
}

#else

UINT64
__TDFUu_mult(UINT64 param_a, UINT64 param_b)
{
	TDF_INT64 prod, a, b;

	UPARAM(a) = param_a;
	UPARAM(b) = param_b;

	CLEAR_ERRORS;

	prod = TDFUmult(a, b);
	/* any overflow will be flagged */

	return UPARAM(prod);
}

#endif



/*
 * Implementation of div0, div1, rem0 and rem1:
 *
 * Clearly there are no problems for unsigned numbers.
 * I have written a generic function to divide two unsigned
 * 64-bit integers which produces both the result of
 * the divide and the remainder.
 *
 * For signed numbers, a and b, it is possible to work out
 * the values of m and n s.t.:
 *
 *   |a| = n * |b| + m,    (0 <= m < |b|)
 *
 * From this information, I believe the correct values
 * for the various functions can be deduced from the
 * following table:
 *
 *    a   b  class  |  div              rem
 *  ==================================================
 *    +   +    1    |   n                m
 *    +   +    2    |   n                m
 *    +   -    1    |  -n or -(n + 1)    0 or (b + m)
 *    +   -    2    |  -n                m
 *    -   +    1    |  -n or -(n + 1)    0 or (b - m)
 *    -   +    2    |  -n               -m
 *    -   -    1    |   n               -m
 *    -   -    2    |   n               -m
 *
 */

/*
 * TDFUdiv_rem:
 *
 * Generic function to divide two 64-bit integers, interpretting each
 * as an unsigned value. Implements the basic 'shift, compare and
 * subtract' algorithm.
 *
 * Since the one function produces both the result and the remainder,
 * it is passed a parameter which tells it which result is expected.
 * The S_DIV_0_1 flags is used for a signed-div0 call for which the
 * arguments represent integers of different signs; in this case,
 * it is the result depends on the remainder (and so is adjusted
 * accordingly while this information is still freely available.
 */

#define S_DIV1       ((UINT32) 0)
#define S_DIV2       ((UINT32) 2)
#define U_DIV2       ((UINT32) 3)
#define S_REM1       ((UINT32) 4)
#define S_REM2       ((UINT32) 6)
#define U_REM2       ((UINT32) 7)
#define S_DIV1_0_1   ((UINT32) 8)

#define is_signed(X) (((X) & 1) == 0)
#define is_class1(X) (((X) & 2) == 0)
#define is_div(X)    (((X) & 4) == 0)

static TDF_INT64
TDFUdiv_rem(TDF_INT64 a, TDF_INT64 b, UINT32 flags)
{
	TDF_INT64 new_int, a_upper;
	UINT32 i;

	new_int = const_u0;
	a_upper = const_u0;

	if (hi_u32(a) == 0) {
		if (hi_u32(b) == 0) {
			/* both a and b fit into 32 bits */
			lo_u32(new_int) = lo_u32(a) / lo_u32(b);
			lo_u32(a_upper) = lo_u32(a) % lo_u32(b);
		} else {
			/* b > a */
			lo_u32(new_int) = 0;
			a_upper = a;
		}
	} else {
		for (i = 64; i > 0; i--) {
			TDFUshl(new_int, new_int,(UINT32)1);

			TDFUshl(a_upper, a_upper,(UINT32)1);

			if ((hi_u32(a) >> 31) != 0) {
				hi_u32(a) &= ((UINT32) 0x7fffffff); /* mask out for shift */
				lo_u32(a_upper) |= 1; /* do carry */
			}

			TDFUshl(a, a,(UINT32)1);

			if (__TDFUu_test(UPARAM(a_upper), UPARAM(b)) >= 0) {
				UPARAM(a_upper) = __TDFUu_minus(UPARAM(a_upper), UPARAM(b));
				lo_u32(new_int) |= 1;
			}
		}

	}

	if (is_div(flags)) {
		if (flags == S_DIV1_0_1
		&& (lo_32(a_upper) != 0 || hi_32(a_upper) != 0))
		{
			PARAM(new_int) = __TDFUs_plus(PARAM(new_int), PARAM(const_1));
		}

		/* result of 'div' */
		return new_int;
	} else {
		/* result of 'rem' */
		return a_upper;
	}
}

/*
 * Division-by-zero is the only possible error.
 */
INT64
__TDFUs_div1(INT64 param_a, INT64 param_b)
{
	TDF_INT64 quot, a, b;
	int is_neg;

	PARAM(b) = param_b;
	if (TDFUis_zero(b)) {
		/* Stop now - return anything */
		DIV_ZERO_ERROR;
		return param_b;
	}

	PARAM(a) = param_a;

	/* is result negative? */
	is_neg = (hi_32(a) ^ hi_32(b)) < 0;

	PARAM(a) = __TDFUabs(param_a);
	PARAM(b) = __TDFUabs(param_b);

	if (is_neg) {
		quot = TDFUdiv_rem(a, b, S_DIV1_0_1);

		CLEAR_ERRORS; /* May have been set by __TDFUabs */

		/* Avoid errors, don't call __TDFUneg */
		hi_32(quot) = hi_32(quot) ^ ((INT32) ((UINT32) 0xffffffff));
		lo_32(quot) = lo_32(quot) ^ UINT32_const(0xffffffff);

		return PARAM(TDFUplus(quot, const_1));
	}

	quot = TDFUdiv_rem(a, b, S_DIV1);

	CLEAR_ERRORS; /* May have been set by __TDFUabs */

	if (TDFUis_negative(quot)) {
		/* Only happens for INT_MAX + 1 */
		OVERFLOW_ERROR;
	}

	return PARAM(quot);
}

/*
 * Division-by-zero is the only possible error.
 */
INT64
__TDFUs_div2(INT64 param_a, INT64 param_b)
{
	TDF_INT64 quot, a, b;
	int  is_neg;

	PARAM(b) = param_b;
	if (TDFUis_zero(b)) {
		/* Stop now - return anything */
		DIV_ZERO_ERROR;
		return param_b;
	}

	PARAM(a) = param_a;

	/* is result negative ? */
	is_neg = ((hi_32(a) ^ hi_32(b)) < 0);

	PARAM(a) = __TDFUabs(param_a);
	PARAM(b) = __TDFUabs(param_b);

	quot = TDFUdiv_rem(a, b, S_DIV2);

	CLEAR_ERRORS; /* May have been set by __TDFUabs */

	if (is_neg) {
		/* Avoid errors, don't call __TDFUneg */
		hi_32(quot) = hi_32(quot) ^ ((INT32) ((UINT32) 0xffffffff));
		lo_32(quot) = lo_32(quot) ^ ((UINT32) 0xffffffff);

		return PARAM(TDFUplus(quot, const_1));
	}

	if (TDFUis_negative(quot)) {
		/* Only happens for INT_MAX + 1 */
		OVERFLOW_ERROR;
	}

	return PARAM(quot);
}

/*
 * Division-by-zero is the only possible error.
 */
UINT64
__TDFUu_div2(UINT64 param_a, UINT64 param_b)
{
	TDF_INT64 a, b;

	CLEAR_ERRORS;

	UPARAM(b) = param_b;
	if (TDFUis_zero(b)) {
		/* Stop now - return anything */
		DIV_ZERO_ERROR;
		return param_b;
	}

	UPARAM(a) = param_a;

	return UPARAM(TDFUdiv_rem(a, b, U_DIV2));
}

/*
 * Modulo-zero is the only possible error.
 */
INT64
__TDFUs_rem1(INT64 param_a, INT64 param_b)
{
	TDF_INT64 rem, a, b, abs_a, abs_b;
	int is_neg;

	PARAM(b) = param_b;
	if (TDFUis_zero(b)) {
		/* Stop now - return anything */
		DIV_ZERO_ERROR;
		return param_b;
	}

	PARAM(a) = param_a;

	PARAM(abs_a) = __TDFUabs(param_a);
	PARAM(abs_b) = __TDFUabs(param_b);

	/* is result negative ? */
	is_neg = TDFUis_negative(b);

	rem = TDFUdiv_rem(abs_a, abs_b, S_REM1);

	CLEAR_ERRORS; /* May have been set by __TDFUabs */

	if (TDFUis_positive(a) && TDFUis_negative(b) && TDFUis_nonzero(rem)) {
		return __TDFUs_plus(param_b, PARAM(rem));
	}

	if (TDFUis_negative(a) && TDFUis_positive(b) && TDFUis_nonzero(rem)) {
		return __TDFUs_minus(param_b, PARAM(rem));
	}

	if (is_neg) {
		return __TDFUneg(PARAM(rem));
	}

	return PARAM(rem);
}

/*
 * Modulo-zero is the only possible error.
 */
INT64
__TDFUs_rem2(INT64 param_a, INT64 param_b)
{
	TDF_INT64 rem, a, b;
	int is_neg;

	PARAM(b) = param_b;
	if (TDFUis_zero(b)) {
		DIV_ZERO_ERROR; /* Stop now - return anything */
		return param_b;
	}

	PARAM(a) = param_a;

	is_neg = TDFUis_negative(a); /* is result negative ? */
	PARAM(a) = __TDFUabs(param_a);
	PARAM(b) = __TDFUabs(param_b);

	rem = TDFUdiv_rem(a, b, S_REM2);

	CLEAR_ERRORS; /* May have been set by __TDFUabs */

	if (is_neg) {
		return __TDFUneg(PARAM(rem));
	}

	return PARAM(rem);
}

/*
 * Modulo-zero is the only possible error.
 */
UINT64
__TDFUu_rem2(UINT64 param_a, UINT64 param_b)
{
	TDF_INT64 a, b;

	UPARAM(b) = param_b;

	if (TDFUis_zero(b)) {
		/* Stop now - return anything */
		DIV_ZERO_ERROR;
		return param_b;
	}

	UPARAM(a) = param_a;

	CLEAR_ERRORS;

	return UPARAM(TDFUdiv_rem(a, b, U_REM2));
}

/*
 * Flip all bits and add 1, as for 2's complement.
 * Overflow error if original value was INT64_MIN.
 */
INT64
__TDFUneg(INT64 param_a)
{
	TDF_INT64 a;

	PARAM(a) = param_a;

	hi_32(a) = hi_32(a) ^ ((INT32) ((UINT32) 0xffffffff));
	lo_32(a) = lo_32(a) ^ ((UINT32) 0xffffffff);

	return __TDFUs_plus(PARAM(a), PARAM(const_1)); /* Should handle any errors */
}

/*
 * Does error checking. If all is okay, returns the value.
 *
 */
UINT64
__TDFUu_shl(UINT64 param_a, UINT32 n)
{
	TDF_INT64 a;

	CLEAR_ERRORS;

	if (n > 63) {
		OVERFLOW_ERROR;
		return UPARAM(const_u0);
	}

	if (n == 0) {
		return param_a;
	}

	/* check that the result won't overflow */

	UPARAM(a) = param_a;
	if (n > 32) {
		if ((lo_u32(a) >> (64 - n)) != 0 || hi_u32(a) != 0) {
			OVERFLOW_ERROR;
		}
	} else if ((hi_u32(a) >> (32 - n)) != 0) {
		OVERFLOW_ERROR;
	}

	TDFUshl(a, a, n);

	return UPARAM(a);
}

/*
 * 2 cases:
 *   n  > 32 - copy high 32-bits across and shift.
 *   n <= 32 - mask out two contributions and OR together.
 */
static TDF_INT64
TDFUshr(TDF_INT64 a, UINT32 n)
{
	TDF_INT64 shifted_a;

	CLEAR_ERRORS;

	if (n >= 32) {
		/* 32 <= n < 64 */
		lo_u32(shifted_a) = hi_u32(a) >> (n -32);
		hi_u32(shifted_a) = (UINT32) 0x00000000;
	} else {
		/* 0 < n <= 32 */
		lo_u32(shifted_a) = (hi_u32(a) << (32-n)) | (lo_u32(a) >> n);
		hi_u32(shifted_a) =  hi_u32(a) >> n;
	}

	return shifted_a;
}

/*
 * Error occurs if n > 64 since the result is undefined.
 */
UINT64
__TDFUu_shr(UINT64 param_a, UINT32 n)
{
	TDF_INT64 a;

	CLEAR_ERRORS;

	if (n > 63) {
		/* This is undefined */
		OVERFLOW_ERROR;
		return UPARAM(const_u0);
	}

	if (n == 0) {
		return param_a;
	}

	UPARAM(a) = param_a;

	return UPARAM(TDFUshr(a, n));
}

/*
 * Checks for a negative quantity, for which it calls '__TDFUneg'.
 * Overflow for, as for __TDFUneg, occurs when the value is INT32_MIN.
 */
INT64
__TDFUabs(INT64 param_a)
{
	TDF_INT64 a;

	PARAM(a) = param_a;
	if (TDFUis_negative(a)) {
		return __TDFUneg(param_a); /* This handles any errors */
	}

	CLEAR_ERRORS;

	return param_a;
}

/*
 * Extends the sign bit, and returns the new int.
 */
INT64
__TDFUsswiden(INT32 a)
{
	TDF_INT64 ext_int;

	CLEAR_ERRORS;

	hi_32(ext_int) = (INT32) (a < 0 ? -1 : 0); /* sign-extend a */
	lo_32(ext_int) = (UINT32) a;

	return PARAM(ext_int);
}

/*
 * Error if a is negative.
 * Otherwise extends the sign bit (just to be safe)
 */
UINT64 __TDFUsuwiden(INT32 a)
{
	TDF_INT64 ext_int;

	CLEAR_ERRORS;
	if (a < 0) {
		OVERFLOW_ERROR;
	}

	hi_u32(ext_int) = (UINT32) (a < 0 ? 0xffffffff : 0);

	/* sign-extend a */
	lo_u32(ext_int) = (UINT32) a;

	return UPARAM(ext_int);
}

/*
 * Puts zero in bits 32-63 and returns
 */
UINT64
__TDFUuuwiden(UINT32 a)
{
	TDF_INT64 ext_int;

	CLEAR_ERRORS;

	hi_u32(ext_int) = 0;
	lo_u32(ext_int) = a;

	return UPARAM(ext_int);
}

/*
 * Same as __TDFUuuswiden.
 */
INT64
__TDFUuswiden(UINT32 a)
{
	TDF_INT64 ext_int;

	CLEAR_ERRORS;

	hi_32(ext_int) = 0;
	lo_32(ext_int) = a;

	return PARAM(ext_int);
}

/*
 * Check that bits 31-63 are all set/unset, otherwise signal overflow.
 * Mask sign bit into bit-31.
 */
INT32
__TDFUssshorten(INT64 param_a)
{
	TDF_INT64 a;

	PARAM(a) = param_a;

	CLEAR_ERRORS;

	switch ((int) hi_32(a)) {
	case 0:
		if ((lo_32(a) & ((UINT32) 0x80000000)) != 0) {
			OVERFLOW_ERROR;
		}
		break;

	case -1:
		if ((lo_32(a) & ((UINT32) 0x80000000)) == 0) {
			OVERFLOW_ERROR;
		}
		break;

	default: {
			OVERFLOW_ERROR;
		}
	}

	return (((INT32) lo_32(a)) & ((INT32) 0x7fffffff))
	               | (hi_32(a) & ((INT32) ((UINT32) 0x80000000)));
}

/*
 * Check that bits 32-63 are all zero otherwise signal overflow.
 * Answer is in bits 0-31.
 */
UINT32
__TDFUsushorten(INT64 param_a)
{
	TDF_INT64 a;

	PARAM(a) = param_a;

	CLEAR_ERRORS;

	if (hi_32(a) != 0) {
		OVERFLOW_ERROR;
	}

	return lo_32(a);
}

/*
 * Error if bits 32-63 are not all zero.
 * Return bits 0-31.
 */
UINT32
__TDFUuushorten(UINT64 param_a)
{
	TDF_INT64 a;

	UPARAM(a) = param_a;

	CLEAR_ERRORS;

	if (hi_u32(a) != 0) {
		OVERFLOW_ERROR;
	}

	return lo_u32(a);
}

/*
 * Error if bits 31-63 are not all zero.
 * Return bits 0-31.
 */
INT32
__TDFUusshorten(UINT64 param_a)
{
	TDF_INT64 a;

	UPARAM(a) = param_a;

	CLEAR_ERRORS;

	if (hi_u32(a) != 0 || ((INT32) lo_u32(a)) < 0) {
		/* Must be an error - started off unsigned */
		OVERFLOW_ERROR;
	}

	return (INT32) lo_u32(a);
}

/*
 * Error only if MSB of "a" is set.
 * Return bits 0-31.
 */
INT64
__TDFUu642s64(UINT64 param_a)
{
	TDF_INT64 a;

	UPARAM(a) = param_a;

	CLEAR_ERRORS;

	/* Cast and check */
	if (TDFUis_negative(a)) {
		OVERFLOW_ERROR;
	}

	return PARAM(a);
}

/*
 * Error only if "a" < 0.
 * Return bits 0-31.
 */
UINT64
__TDFUs642u64(INT64 param_a)
{
	TDF_INT64 a;

	PARAM(a) = param_a;

	CLEAR_ERRORS;

	/* Check and cast */
	if (TDFUis_negative(a)) {
		OVERFLOW_ERROR;
	}

	return UPARAM(a);
}

/*
 * Uses: (a > b) ? a : b
 * No errors.
 */
INT64
__TDFUs_max(INT64 param_a, INT64 param_b)
{
	CLEAR_ERRORS;

	if (__TDFUs_test(param_a, param_b) > 0) {
		return param_a; /* a == max(a,b) */
	} else {
		return param_b; /* b == max(a,b) */
	}
}

/*
 * Uses: (a > b) ? a : b
 * No errors.
 */
UINT64
__TDFUu_max(UINT64 param_a, UINT64 param_b)
{
	if (__TDFUu_test(param_a, param_b) > 0) {
		return param_a; /* a == max(a, b) */
	} else {
		return param_b; /* b == max(a, b) */
	}
}

/*
 * Uses: (a < b) ? a : b
 * No errors.
 */
INT64
__TDFUs_min(INT64 param_a, INT64 param_b)
{
	if (__TDFUs_test(param_a, param_b) < 0) {
		return param_a; /* a == min(a, b) */
	} else {
		return param_b; /* b == min(a, b) */
	}
}

/*
 * Uses: (a < b) ? a : b
 * No errors.
 */
UINT64
__TDFUu_min(UINT64 param_a, UINT64 param_b)
{
	if (__TDFUu_test(param_a, param_b) < 0) {
		return param_a; /* a == min(a, b) */
	} else {
		return param_b; /* b == min(a, b) */
	}
}

/*
 * Returns -1  if a < b;  This gives: a op b <=> TDFs_test(a, b) op 0
 *          0  if a = b;
 *          1  if a > b.
 */
int
__TDFUs_test(INT64 param_a, INT64 param_b)
{
	TDF_INT64 a, b;

	PARAM(a) = param_a;
	PARAM(b) = param_b;

	CLEAR_ERRORS;

	if (hi_32(a) < hi_32(b)) return -1;
	if (hi_32(a) > hi_32(b)) return  1;
	if (lo_32(a) < lo_32(b)) return -1;
	if (lo_32(a) > lo_32(b)) return  1;

	return 0;
}

/*
 *	__TDFUu_test:  as for __TDFUs_test, but for unsigned types.
 */
int
__TDFUu_test(UINT64 param_a, UINT64 param_b)
{
	TDF_INT64 a, b;

	UPARAM(a) = param_a;
	UPARAM(b) = param_b;

	CLEAR_ERRORS;

	if (hi_u32(a) < hi_u32(b)) return -1;
	if (hi_u32(a) > hi_u32(b)) return  1;
	if (lo_u32(a) < lo_u32(b)) return -1;
	if (lo_u32(a) > lo_u32(b)) return  1;

	return 0;
}

/*
 * AND the hi- and low-words together, and return.
 */
UINT64
__TDFUand(UINT64 param_a, UINT64 param_b)
{
	TDF_INT64 a, b;

	UPARAM(a) = param_a;
	UPARAM(b) = param_b;

	CLEAR_ERRORS;

	hi_u32(a) = (hi_u32(a) & hi_u32(b));
	lo_u32(a) = (lo_u32(a) & lo_u32(b));

	return UPARAM(a);
}

/*
 * OR the hi- and low-words together, and return.
 */
UINT64
__TDFUor(UINT64 param_a, UINT64 param_b)
{
	TDF_INT64 a, b;

	UPARAM(a) = param_a;
	UPARAM(b) = param_b;

	CLEAR_ERRORS;

	hi_u32(a) = (hi_u32(a) | hi_u32(b));
	lo_u32(a) = (lo_u32(a) | lo_u32(b));

	return UPARAM(a);
}

/*
 * OR the hi- and low-words together, and return.
 */
UINT64
__TDFUxor(UINT64 param_a, UINT64 param_b)
{
	TDF_INT64 a, b;

	UPARAM(a) = param_a;
	UPARAM(b) = param_b;

	CLEAR_ERRORS;

	hi_u32(a) = (hi_u32(a) ^ hi_u32(b));
	lo_u32(a) = (lo_u32(a) ^ lo_u32(b));

	return UPARAM(a);
}

/*
 * XOR the hi- and low-words each with 0xffffffff
 */
UINT64
__TDFUnot(UINT64 param_a)
{
	TDF_INT64	a;

	UPARAM(a) = param_a;

	CLEAR_ERRORS;

	hi_u32(a) = hi_u32(a) ^ ((UINT32) 0xffffffff);
	lo_u32(a) = lo_u32(a) ^ ((UINT32) 0xffffffff);

	return UPARAM(a);
}


#ifndef NDEBUG

INT64
make_INT64(INT32 new_hi, UINT32 new_lo)
{
	TDF_INT64 new_int;

	hi_32(new_int) = new_hi;
	lo_32(new_int) = new_lo;

	return PARAM(new_int);
}

UINT64
make_UINT64(UINT32 new_hi, UINT32 new_lo)
{
	TDF_INT64 new_int;

	hi_u32(new_int) = new_hi;
	lo_u32(new_int) = new_lo;

	return UPARAM(new_int);
}

#if !defined(__TenDRA__)

/*
 * We can't print these when using the abstract interface.
 */

void
INT64_print(char * t1, INT64 a, char *t2)
{
	IGNORE printf("%s(%d,%u)%s", t1, (int) a.hi32, (unsigned) a.lo32, t2);
}

void
UINT64_print(char * t1, UINT64 a, char * t2)
{
	IGNORE printf("%s(%u,%u)%s", t1, (unsigned) a.hi32, (unsigned) a.lo32, t2);
}

#endif

#endif  /* !NDEBUG */

