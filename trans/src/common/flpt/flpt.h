/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef COMMON_FLPT_H
#define COMMON_FLPT_H

#include <limits.h>

#include <tdf/nat.h>

#include <construct/installtypes.h>

#include <main/flags.h>

#include <local/fbase.h>

/* Function status values: */
enum {
	OKAY    =  0,
	EXP2BIG = -1,
	SYNTAX  = -2,
	DIVBY0  = -3
};

/* MANT_SIZE is the number of mantissa array elements */
#ifndef MANT_SIZE
#define MANT_SIZE 8
#endif

/*
 * MANT_SIZE_MAX is the number of mantissas array elements that
 * supported by the platform's largest floating point type (double or
 * long double)
 */
#ifndef MANT_SIZE_MAX
#define MANT_SIZE_MAX 8
#endif

#define Fdig unsigned short

/* FBITS is the number of bits in one array element */
#define FBITS 16

#define E_MIN (-16384)
#define E_MAX (LONG_MAX / FBASE)

/* Rounding types: */
enum {
	R2ZERO = 3,
	R2PINF = 2,
	R2NINF = 1,
	R2NEAR = 0
};

/* floating point representation */
typedef struct {
	Fdig mant[10];
	/* point is between 1st and 2nd digits */
	int sign; /* -1: negative; +1: positive; 0: value is zero */
	int exp;  /* signed exponent; in range E_MIN..E_MAX */
} flt;

/* type for result of conversion of reals to ints */
typedef struct r2l_t {
	int i1; /* least significant */
	int i2;
	int i3;
	int i4;	/* most significant */
} r2l;

/*
 * used to convert flpt number which are integers into a 64 bit
 * representation
 */
typedef struct flt64_t {
	int big;            /* more significant 32 bits */
	unsigned int small; /* less significant 32 bits */
} flt64;

extern void init_flpt(void);
extern flpt new_flpt(void);
extern void flpt_ret(flpt f);
extern int cmpflpt(flpt a, flpt b, int testno);
extern flpt floatrep(int n);
extern flpt floatrep_unsigned(unsigned int n);
extern flt *flptnos;

/* floatingpoint functions - are these needed externally??? */
extern void flt_zero(flt *f);
extern void flt_copy(flt f, flt *res);
extern int  flt_add(flt f1, flt f2, flt *res);
extern int  flt_sub(flt f1, flt f2, flt *res);
extern int  flt_mul(flt f1, flt f2, flt *res);
extern int  flt_div(flt f1, flt f2, flt *res);
extern int  flt_cmp(flt f1, flt f2);
extern void flt_round(flt f, flt *res);
extern void flpt_newdig(unsigned int dig, flt *res, int base);
extern void flpt_scale(int decexp, flt *res, int base);
extern void flpt_round(int rdnmd, int pos, flt *res);
extern int flpt_bits(floating_variety fv);
extern int flpt_round_to_integer(int rndmd, flt *f);
extern r2l real2longs_IEEE(flt *f, int sw);

extern int fzero_no;
extern int fone_no;

extern flt64 flt_to_f64(flpt fp, int sg, int *ov);
extern flpt f64_to_flt(flt64 a, int sg);
extern int f64_to_flpt(flt64 a, int sg, int *pr, int sz);
extern flt64 int_to_f64(int i, int sg);
extern flt64 exp_to_f64(exp e);


#endif

