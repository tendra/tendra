/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef flpttypekey
#define flpttypekey 1

#include <limits.h>

#include <local/fbase.h>

#if FBASE == 10

/* FBASE 10 is obsolete */

#define MANT_SIZE 40
#define MANT_SIZE_MAX 40

#define Fdig unsigned char

#define FNUM_SIZE 65		/* max size required by flt2str */
/* MANT_SIZE + 1(sign) + 1(point) + 2(E+sign) + log(MAX_LONG) + 1(NULL) */

#define E_MIN	(-1000000)	/* (LONG_MIN/10) doesnt work on 80386 cc
				*/
#define E_MAX	(LONG_MAX / 10)

/* Function status values:   */
#define OKAY		0
#define EXP2BIG	(-1)
#define SYNTAX		(-2)
#define DIVBY0		(-3)

/* Rounding types:   */
#define R2ZERO	0
#define R2PINF	1
#define R2NINF	2
#define R2NEAR	3

/* floating point representation */
typedef struct _flt {
  Fdig mant[MANT_SIZE]; /* mantissa digit values [0-9] (NOT '0' to '9') */
  /* point is between 1st and 2nd digits */
  int sign;		/* -1: negative; +1: positive; 0: value is zero */
  int exp;		/* signed exponent; in range E_MIN..E_MAX */
} flt;

#else

/* all installers should use this definition */

/* MANT_SIZE is the number of mantissa array elements */
#ifndef MANT_SIZE
#define MANT_SIZE 8
#endif

/* MANT_SIZE_MAX is the number of mantissas array elements that
 * supported by the platform's largest floating point type (double or
 * long double)
 */
#ifndef MANT_SIZE_MAX
#define MANT_SIZE_MAX 8
#endif

#define Fdig unsigned short
/* FBITS is the number of bits in one array element */
#define FBITS 16

#define E_MIN	(-16384)
#define E_MAX	(LONG_MAX / FBASE)

/* Function status values:   */
#define OKAY		0
#define EXP2BIG	(-1)
#define SYNTAX		(-2)
#define DIVBY0		(-3)

/* Rounding types:   */
#define R2ZERO	3
#define R2PINF	2
#define R2NINF	1
#define R2NEAR	0

typedef struct _flt {
  Fdig mant[10];
  /* point is between 1st and 2nd digits */
  int sign;		/* -1: negative; +1: positive; 0: value is zero */
  int exp;		/* signed exponent; in range E_MIN..E_MAX */
} flt;	/* floating point representation */


/* type for result of conversion of reals to ints */
typedef struct r2l_t {
	int i1; /* least significant */
	int i2;
	int i3;
	int i4;	/* most significant */
} r2l;

#endif

typedef struct flt64_t {
  int big;		/* more significant 32 bits */
  unsigned int small;	/* less significant 32 bits */
} flt64;
/* used to convert flpt number which are integers into a 64 bit
 * representation */

#endif /* flpttypekey */
