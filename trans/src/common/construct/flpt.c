/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Routines for handling the internal floating point representation.
 */

#include <limits.h>
#include <stdlib.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <local/szs_als.h>

#include <reader/basicread.h>

#include <construct/flpttypes.h>
#include <construct/exp.h>
#include <construct/messages_c.h>
#include <construct/installglob.h>
#include <construct/flpt.h>

#include <main/flags.h>

#define MAX_USEFUL_DECEXP 10000
/* plenty big enough for IEEE and VAX */
#define initial_flpts 50
#define extra_flpts 50

/*
 * Floating point emulator code
 *
 * Lines which assume the use of an ASCII character set are accompanied
 * by the comment "ASCII"
 */

typedef struct _dbl {
  /* Double precision type - used for internal working */
  Fdig mant[2 * 10];
  int  sign;
  int  exp;
} dbl;

/*
 * The current rounding rule. This may be one of the following :
 *
 *   R2ZERO - round towards zero.
 *   R2PINF - round towards positive infinity.
 *   R2NINF - round towards negative infinity.
 *   R2NEAR - round to nearest integer.
 *
 * It should be set using the "set_round" function.
 */

static Fdig bitround[16] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80,
			     0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000,
			     0x4000, 0x8000};
static Fdig bitmask[17] = {0xffff, 0xfffe, 0xfffc, 0xfff8,
			    0xfff0, 0xffe0, 0xffc0, 0xff80,
			    0xff00, 0xfe00, 0xfc00, 0xf800,
			    0xf000, 0xe000, 0xc000, 0x8000, 0x0};

static flt powers[16] = {
	{{10, 0, 0, 0, 0, 0, 0, 0},1, 0},
	{{100, 0, 0, 0, 0, 0, 0, 0},1, 0},
	{{1000, 0, 0, 0, 0, 0, 0, 0},1, 0},
	{{10000, 0, 0, 0, 0, 0, 0, 0},1, 0},
	{{1, 34464, 0, 0, 0, 0, 0, 0},1, 1},
	{{15, 16960, 0, 0, 0, 0, 0, 0},1, 1},
	{{152, 38528, 0, 0, 0, 0, 0, 0},1, 1},
	{{1525, 57600, 0, 0, 0, 0, 0, 0},1, 1},
	{{15258, 51712, 0, 0, 0, 0, 0, 0},1, 1},
	{{2, 21515, 58368, 0, 0, 0, 0, 0},1, 2},
	{{23, 18550, 59392, 0, 0, 0, 0, 0},1, 2},
	{{232, 54437, 4096, 0, 0, 0, 0, 0},1, 2},
	{{2328, 20082, 40960, 0, 0, 0, 0, 0},1, 2},
	{{23283, 4218, 16384, 0, 0, 0, 0, 0},1, 2},
	{{3, 36222, 42182, 32768, 0, 0, 0, 0},1, 3},
	{{35, 34546, 28609, 0, 0, 0, 0, 0},1, 3}
};

static int two_powers[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
			    2048, 4096, 8192, 16384, 32768};
static int round_type = R2NEAR;

/* All variables initialised */

int tot_flpts;		/* total number of floating point numbers */
int flptfree;		/* floating point free list */
int flpt_left;		/* number of floating point numbers left */

flt *flptnos;		/* the extendable array of floating point numbers */

int fzero_no;
int fone_no;

flpt new_flpt(void);

/*
 * Internal functions
 */

/*
 * "f1" and "f2" are two legal single precision numbers.
 *
 * The result is -1, 0 or +1 depending on whether the magnitude of "f1"
 * is less than, equal to or greater than that of "f2"
 */
static int
mag_cmp(flt f1, flt f2)
{
  int i;
  if (f1.sign == 0) {
    if (f2.sign == 0) {
      return 0;
    }
    return -1;
  }
  if (f2.sign == 0) {
    return 1;
  }
  if (f1.exp != f2.exp) {
    return (f1.exp < f2.exp) ? -1 : 1;
  }
  for (i = 0; i < MANT_SIZE; i++) {
    if ((f1.mant[i]) != (f2.mant[i])) {
      return ((f1.mant[i]) < (f2.mant[i])) ? -1 : 1;
    }
  }
  return 0;
}

/*
 * "d1" and "d2" are two legal double precision numbers.
 *
 * The result is -1, 0 or +1 depending on whether the magnitude of "d1"
 * is less than, equal to or greater than that of "d2"
 */
static int
dbl_mag_cmp (dbl d1, dbl d2)
{
  int i;
  if (d1.sign == 0) {
    if (d2.sign == 0) {
      return 0;
    }
    return -1;
  }
  if (d2.sign == 0) {
    return 1;
  }
  if (d1.exp != d2.exp) {
    return (d1.exp < d2.exp) ? -1 : 1;
  }
  for (i = 0; i < (2 * MANT_SIZE); i++) {
    if ((d1.mant[i]) != (d2.mant[i])) {
      return ((d1.mant[i]) < (d2.mant[i]))? -1 : 1;
    }
  }
  return 0;
}

/*
 * "f" is a pointer to a legal single precision number. "c" is a character
 * value from 0 to FBASE-1.
 *
 * On return, the single precision number pointed to by "f" will have been
 * modified as if "c" were the digit following the least significant digit
 * of the number pointed to by "f" and the number has been rounded according
 * to the current rounding rule.
 */
static void
flt_int_round(flt *f, unsigned int ic)
{
  int i;
  switch (round_type) {
  default:
  case R2ZERO:
    return;
  case R2PINF:
    if (((f->sign) != 1) || (ic == 0))
      return;
    break;
  case R2NINF:
    if (((f->sign) != -1) || (ic == 0))
      return;
    break;
  case R2NEAR:
    if (ic < (unsigned int)(FBASE / 2)) {
      return;
    }
    break;
  }
  ic = 1;
  for (i = (MANT_SIZE - 1); i >= 0; i--) {
    (f->mant)[i] = (unsigned short)((ic += (unsigned int)((f->mant)[i])) % FBASE);
    /* CAST:jmf: unsigned short since FBASE <= MAX_USHORT+1 */
    if ((ic /= FBASE) == 0) {
      return;
    }
  }
  (f->exp)++;
  (f->mant)[0] = 1;
  for (i = 1; i < MANT_SIZE; i++) {
    (f->mant)[i] = 0;
  }
}

/*
 * "d" is a legal double precision number. "f" is a pointer to a single
 * precision number.
 *
 * On return, the number pointed to by "f" contains the value of "d"
 * but to less precision. The current rounding rule is used to truncate
 * the mantissa.
 */
static void
dbl2float(dbl d, flt *f)
{
  int i;
  (f->sign) = d.sign;
  (f->exp) = d.exp;
  for (i = 0; i < MANT_SIZE; i++) {
    (f->mant)[i] = d.mant[i];
  }
  flt_int_round(f, (unsigned int)d.mant[MANT_SIZE]);
}

/*
 * "f" is a legal single precision number. "d" is a pointer to a double
 * precision number.
 *
 * On return, the number pointed to by "d" will contain the value of "f"
 */
static void
flt2double(flt f, dbl *d)
{
  int i;
  (d->sign) = f.sign;
  (d->exp) = f.exp;
  for (i = 0; i < MANT_SIZE; i++) {
    (d->mant)[i] = f.mant[i];
  }
  for (i = MANT_SIZE; i < (2 * MANT_SIZE); i++) {
    (d->mant)[i] = 0;
  }
}

/*
 * "d" is a pointer to a legal double precision number. "dist" is a int with
 * value greater than zero.
 *
 * On return, the number pointed to by "d" keeps the same value (although some
 * loss of precision may occur) but is no longer in normalised form.
 * The mantissa is shifted right "dist" places, and the exponent is adjusted
 * to keep the value the same
 */
static void
shift_right(dbl *d, int dist)
{
  int i;
  int j = (2 * MANT_SIZE) - 1 - dist;
  for (i = (2 * MANT_SIZE) - 1; i >= 0; i--, j--) {
    (d->mant)[i] = (unsigned short)((j >= 0) ? ((d->mant)[j]) : 0);
  }
  (d->exp) += dist;
}

/*
 * "d1" and "d2" are double precision numbers, with the same exponent and
 * opposite (non-zero) signs. "res" is a pointer to a single precision number,
 * whose exponent has been set to the same value as "d1" and "d2".
 *
 * On return, the number pointed to by "res" is the result of adding
 * "d1" to "d2" and rounding it by the current rounding rule.
 * The return value is either OKAY or EXP2BIG (in which case the value of
 * the number pointed to by "res" is undefined)
 */
static int
sub_mantissas(dbl d1, dbl d2, flt *res)
{
  dbl *dp1 = &d1, *dp2 = &d2, rdbl;
  unsigned int  c = 0;
  int i, cmp = dbl_mag_cmp(d1, d2);
  if (cmp == 0) {
    (res->sign) = 0;
    (res->exp) = 0;
    for (i = 0; i < MANT_SIZE; i++) {
      (res->mant)[i] = 0;
    }
    return OKAY;
  } else if (cmp == -1) {
    dp1 = &d2;
    dp2 = &d1;
  }
  rdbl.exp = (res->exp);
  for (i = (2 * MANT_SIZE) - 1; i >= 0; i--) {
    int s = (int)(((dp1->mant)[i]) - ((dp2->mant)[i]) - c);
    c = 0;
    if (s < 0) {
      c = 1;
      s += FBASE;
    }
    rdbl.mant[i] = (unsigned short)s;	/* CAST:jmf: */
  }
  rdbl.sign = (dp1->sign);
  while ((rdbl.mant[0]) == 0) {
    for (i = 1; i < (2 * MANT_SIZE); i++) {
      rdbl.mant[i - 1] = rdbl.mant[i];
    }
    rdbl.mant[(2 * MANT_SIZE) - 1] = 0;
    if ((--rdbl.exp) < E_MIN) {
      return EXP2BIG;
    }
  }
  dbl2float(rdbl, res);
  return OKAY;
}

/*
 * "d1" and "d2" are double precision numbers, with the same exponent and
 * non-zero signs. "res" is a pointer to a single precision number which has
 * the same exponent as "d1" and "d2".
 *
 * On return, the number pointed to by "res" will be the result of adding
 * "d1" to "d2" and rounding it according to the current rounding rule.
 * The return value will be either OKAY or EXP2BIG (in which case the value
 * of the number pointed to by "res" is undefined)
 */
static int
add_mantissas(dbl d1, dbl d2, flt * res)
{
  int i;
  unsigned int c;
  if (d1.sign == d2.sign) {
    dbl rdbl;
    (res->sign) = d1.sign;
    flt2double(*res, &rdbl);
    c = 0;
    for (i = (2 * MANT_SIZE) - 1; i >= 0; i--) {
      c += (unsigned int)(d1.mant[i] + d2.mant[i]);
      rdbl.mant[i] = (unsigned short)(c % FBASE);	/* CAST:jmf: */
      c /= FBASE;
    }
    if (c) {
      for (i = (2 * MANT_SIZE) - 1; i > 0; i--) {
	rdbl.mant[i] = rdbl.mant[i - 1];
      }
      rdbl.mant[0] = (unsigned short)c;	/* CAST:jmf: */
      if (((++rdbl.exp) >= E_MAX) || (rdbl.exp <= E_MIN)) {
	return EXP2BIG;
      }
    }
    dbl2float(rdbl, res);
    return OKAY;
  }
  return sub_mantissas(d1, d2, res);
}

/*
 * "public" emulator functions
 */

/*
 * "f" is a pointer to a single precision number.
 *
 * On return, the number pointed to by "f" will have the value zero
 */
void
flt_zero(flt *f)
{
  int i;
  (f->sign) = 0;
  (f->exp) = 0;
  for (i = 0; i < MANT_SIZE; i++) {
    (f->mant)[i] = 0;
  }
}

/*
 * "f" is a legal single precision number. "res" is a pointer to a single
 * precision number.
 *
 * On return, the number pointed to by "res" is the same as "f"
 */
void
flt_copy(flt f, flt *res)
{
  int i;
  (res->sign) = f.sign;
  (res->exp) = f.exp;
  for (i = 0; i < MANT_SIZE; i++) {
    (res->mant)[i] = f.mant[i];
  }
  return;
}

/*
 * "f1" and "f2" are legal single precision numbers. "res" is a pointer to a
 * single precision number.
 *
 * On return, if the result is OKAY, then the number pointed to by "res" will
 * contain the value of adding "f1" to "f2". If the result is EXP2BIG,
 * then the value of the number pointed to by "res" is undefined.
 */
int
flt_add(flt f1, flt f2, flt *res)
{
  dbl d1, d2;
  if (f1.sign == 0) {
    flt_copy(f2, res);
    return OKAY;
  } else if (f2.sign == 0) {
    flt_copy(f1, res);
    return OKAY;
  }
  flt2double(f1, &d1);
  flt2double(f2, &d2);
  if (d1.exp < d2.exp) {
    shift_right(&d1, d2.exp - d1.exp);
  } else if (d1.exp > d2.exp) {
    shift_right(&d2, d1.exp - d2.exp);
  }
  (res->exp) = d1.exp;
  return add_mantissas(d1, d2, res);
}

/*
 * "f1" and "f2" are legal single precision numbers. "res" is a pointer to a
 * single precision number.
 *
 * On return, if the result is OKAY, then the number pointed to by "res" will
 * contain the value of subtracting "f2" from "f1". If the result is EXP2BIG,
 * then the value of the number pointed to by "res" is undefined.
 */
int
flt_sub(flt f1, flt f2, flt *res)
{
  f2.sign = -f2.sign;
  return flt_add(f1, f2, res);
}


#if FBASE == 10

/*
 * "f1" and "f2" are legal single precision numbers. "res" is a pointer to a
 * single precision number.
 *
 * On return, if the result is OKAY, then the number pointed to by "res" will
 * contain the value of multiplying "f1" by "f2". If the result is EXP2BIG,
 * then the value of the number pointed to by "res" is undefined.
 */
int
flt_mul(flt f1, flt f2, flt *res)
{
  dbl rdbl;
  int i, j;
  unsigned int c = 0;
  unsigned int acc[2 * MANT_SIZE];
  if ((f1.sign == 0) || (f2.sign == 0)) {
    flt_zero(res);
    return OKAY;
  }
  rdbl.sign = ((f1.sign == f2.sign)? 1 : -1);
  rdbl.exp = (f1.exp + f2.exp + 1);
  if ((rdbl.exp >= E_MAX) || (rdbl.exp <= E_MIN)) {
    return EXP2BIG;
  }
  for (i = 0; i < (2 * MANT_SIZE); i++) {
    acc[i] = 0;
  }
  for (i = MANT_SIZE - 1; i >= 0; i--) {
    for (j = MANT_SIZE - 1; j >= 0; j--) {
      acc[i + j + 1] += (f1.mant[i] * f2.mant[j]);
    }
  }
  for (i = (2 * MANT_SIZE) - 1; i >= 0; i--) {
    c += acc[i];
    rdbl.mant[i] = (c % FBASE);
    c /= FBASE;
  }
  while (rdbl.mant[0] == 0) {
    for (i = 1; i < (2 * MANT_SIZE); i++) {
      rdbl.mant[i - 1] = rdbl.mant[i];
    }
    rdbl.mant[(2 * MANT_SIZE) - 1] = 0;
    if ((--rdbl.exp) <= E_MIN) {
      return EXP2BIG;
    }
  }
  dbl2float(rdbl, res);
  return OKAY;
}

#else

/*
 * "f1" and "f2" are legal single precision numbers. "res" is a pointer to a
 * single precision number.
 *
 * On return, if the result is OKAY, then the number pointed to by "res" will
 * contain the value of multiplying "f1" by "f2". If the result is EXP2BIG,
 * then the value of the number pointed to by "res" is undefined.
 */
int
flt_mul(flt f1, flt f2, flt *res)
{
  dbl rdbl;
  int i, j, k;
  unsigned int acc[2 * MANT_SIZE];
  if ((f1.sign == 0) || (f2.sign == 0)) {
    flt_zero(res);
    return OKAY;
  }
  rdbl.sign = ((f1.sign == f2.sign)? 1 : -1);
  rdbl.exp = (f1.exp + f2.exp + 1);
  if ((rdbl.exp >= E_MAX) || (rdbl.exp <= E_MIN)) {
    return EXP2BIG;
  }
  for (i = 0; i < (2 * MANT_SIZE); i++) {
    acc[i] = 0;
  }
  SET(acc);

  for (i = MANT_SIZE - 1; i >= 0; i--) {
    for (j = MANT_SIZE - 1; j >= 0; j--) {
      unsigned int temp = (unsigned int)(f1.mant[i] * f2.mant[j]);
      unsigned int atl;
      for (k = i + j + 1; temp != 0; --k) {
	atl = acc[k] + (temp & 0xffff);
	acc[k] = atl & 0xffff;
	temp = (atl >> 16) + (temp >> 16);
      }
    }
  }

  for (i = (2 * MANT_SIZE) - 1; i >= 0; i--) {
    rdbl.mant[i] = (unsigned short)(acc[i]);	/* CAST:jmf: */
  }

  while (rdbl.mant[0] == 0) {
    for (i = 1; i < (2 * MANT_SIZE); i++) {
      rdbl.mant[i - 1] = rdbl.mant[i];
    }
    rdbl.mant[(2 * MANT_SIZE) - 1] = 0;
    if ((--rdbl.exp) <= E_MIN) {
      return EXP2BIG;
    }
  }

  dbl2float(rdbl, res);
  return OKAY;
}
#endif


#if FBASE == 10

/*
 * "f1" and "f2" are legal single precision numbers, and "f2" is non-zero.
 * "res" is a pointer to a single precision number.
 *
 * On return, if the result is OKAY, then the number pointed to by "res"
 * contains the result of dividing "f1" by "f2". If the result is EXP2BIG
 * or DIVBY0 then the contents of the number pointed to by "res" are undefined.
 */
int
flt_div(flt f1, flt f2, flt *res)
{
  dbl rdbl;
  int i = 0;
  flt f3;
  if (f2.sign == 0) {
    return DIVBY0;
  }
  if (f1.sign == 0) {
    flt_zero(res);
    return OKAY;
  }
  rdbl.sign = ((f1.sign == f2.sign) ? 1 : -1);
  rdbl.exp = (f1.exp - f2.exp);
  if ((rdbl.exp >= E_MAX) || (rdbl.exp <= E_MIN)) {
    return EXP2BIG;
  }
  f1.sign = 1;
  f2.sign = 1;
  f1.exp = 0;
  f2.exp = 0;
  flt_copy(f1, &f3);
  while (i < (2 * MANT_SIZE)) {
    int count = -1;
    while (f3.sign != -1) {
      if (flt_sub(f3, f2, &f3) != OKAY) {
	return EXP2BIG;
      }
      count++;
    }
    if (flt_add(f3, f2, &f3) != OKAY) {
      return EXP2BIG;
    }
    rdbl.mant[i++] = count;
    if (f3.sign == 0) {
      break;
    }
    if ((--f2.exp) <= E_MIN) {
      return EXP2BIG;
    }
  }
  while (i < (2 * MANT_SIZE)) {
    rdbl.mant[i++] = 0;
  }
  while (rdbl.mant[0] == 0) {
    for (i = 1; i < (2 * MANT_SIZE); i++) {
      rdbl.mant[i - 1] = rdbl.mant[i];
    }
    rdbl.mant[(2 * MANT_SIZE) - 1] = 0;
    if ((--rdbl.exp) <= E_MIN) {
      return EXP2BIG;
    }
  }
  dbl2float(rdbl, res);
  return OKAY;
}

#else

int
flt_div(flt f1, flt f2, flt *res)
{
  Fdig a1[MANT_SIZE+1];
  Fdig a2[MANT_SIZE+1];
  Fdig r[MANT_SIZE+1];
  int bit_diff = 0;
  int i;
  int t, s;
  unsigned int c = 0;
  int bit, bitpos;
  int sg;
  int keep_on;
  int final_expt = f1.exp - f2.exp;
  int final_shift = 0;
  unsigned int k;

  if (f2.sign == 0) {
    return DIVBY0;
  }

  if (f1.sign == 0) {
    flt_zero(res);
    return OKAY;
  }

  for (i = 0; i < MANT_SIZE; ++i) {
    a1[i] = f1.mant[i];
    a2[i] = f2.mant[i];
    r[i] = 0;
  }
  a1[MANT_SIZE] = 0;
  a2[MANT_SIZE] = 0;
  r[MANT_SIZE] = 0;

  /*
   * Shift first digit of a1 or a2 right until a1[0] < a2[0] and a1[0] >= 2*a2[0]
   * Count the places in bit_diff.
   */
  t = (int)(a1[0]);
  s = (int)(a2[0]);
  if (t >= s) {
    for (; t >= s; ++bit_diff) {
      t >>= 1;
    }
  } else {
    for (; t < s; --bit_diff) {
      s >>= 1;
    }
    ++bit_diff;
  }


  /*
   * Shift a1  bit_diff places right if bit_diff positive.
   * Shift a2 -bit_diff places right if bit_diff negative.
   */
  if (bit_diff > 0) {
    for (i = 0; i < (MANT_SIZE + 1); ++i) {
      c = (unsigned int)(a1[i] + (c << 16));
      a1[i] = (unsigned short)(c >> bit_diff);	/* CAST:jmf: */
      c &= (unsigned int)((1 << (bit_diff + 1)) -1);
    }
  } else if (bit_diff < 0) {
    for (i = 0; i < (MANT_SIZE + 1); ++i) {
      c = (unsigned int)(a2[i] + (c << 16));
      a2[i] = (unsigned short)(c >> -bit_diff);	/* CAST:jmf: */
      c &= (unsigned int)((1 << (-bit_diff + 1)) -1);
    }
  }

  /* do the division */
  bit = 0;	/* current bit of result */
  bitpos = 0;	/* current digit of result */
  sg = 1;	/* 1 means subtract, 0 means add */
  keep_on = 1;
  while (keep_on) {
    c = 0;
    /* subtract or add */
    if (sg) {
      for (i = MANT_SIZE; i >= 0; --i) {
	c = (unsigned int)(a1[i] - a2[i] + c);
	a1[i] = (unsigned short)(c & 0xffff);	/* CAST:jmf: */
	if (c & 0x10000) {
	  c = (unsigned int)(-1);
	} else {
	  c = 0;
	}
      }
      sg = (c)? 0 : 1;
    } else {
      for (i = MANT_SIZE; i >= 0; --i) {
	c = (unsigned int)(a1[i] + a2[i] + c);
	a1[i] = (unsigned short)(c & 0xffff);	/* CAST:jmf: */
	if (c & 0x10000) {
	  c = 1;
	} else {
	  c = 0;
	}
      }
      sg = (c)? 1 : 0;
    }
    if (sg) {
      r[bitpos] = (unsigned short)((int)r[bitpos] | (1 << bit));
      /* CAST:jmf: */
    }
    if (bit == 0) {
      bit = 15;
      ++bitpos;
    } else {
      --bit;
    }
    keep_on = 0;
    /* shift f2 right one place, if zero keep_on = 0 */
    c = 0;
    for (i = 0; i < (MANT_SIZE + 1); ++i) {
      c = (unsigned int)(a2[i] + (c << 16));
      if (c) {
	keep_on = 1;
      }
      a2[i] = (unsigned short)(c >> 1);	/* CAST:jmf: */
      c &= 1;
    }
  }

  /* correct line-up of r */
  if (bit_diff > 0) {
    final_shift = bit_diff;
  } else {
    --final_expt;
    if (bit_diff > -16) {
      final_shift = 16 + bit_diff;
    }
  }
  k = (unsigned int)((((int)r[MANT_SIZE] << final_shift) & 0x8000) >> 15);
  /* (int) coercion OK because r is shorter */
  k = (unsigned int)(k + (r[MANT_SIZE] >> (16 - final_shift)));
  for (i = MANT_SIZE-1; i >= 0; --i) {
    k = (unsigned int)((r[i] << final_shift) + k);
    res ->mant[i] = (unsigned short)(k & 0xffff);;	/* CAST:jmf: */
    k >>= 16;
  }

  if (res->mant[0] == 0) {
    for (i = 0; i < MANT_SIZE - 1; ++i) {
      res->mant[i] = res->mant[i + 1];
    }
    res->mant[MANT_SIZE - 1] = 0;
    --final_expt;
  }

  res->exp = final_expt;
  res->sign = (f1.sign == f2.sign) ? 1 : -1;
  return OKAY;
}

#endif

/*
 * "f1" and "f2" are legal single precision numbers.
 *
 * The return value will be -1, 0 or 1 depending whether "f1" is
 * less than, equal to or greater than "f2"
 */
int
flt_cmp(flt f1, flt f2)
{
  int ret;
  if (f1.sign < f2.sign) {
    return -1;
  }
  if (f1.sign > f2.sign) {
    return 1;
  }
  ret = mag_cmp(f1, f2);
  return (f1.sign == -1) ? -ret : ret;
}

/*
 * "f" is a legal single precision number. "res" is a pointer to a single
 * precision number.
 *
 * On return, the number pointed to by "res" will be the integer value of
 * "f" rounded using the current rounding rule.
 */
void
flt_round(flt f, flt *res)
{
  int i;
  unsigned int ex;
  if (f.exp < -1) {
    flt_zero(res);
    return;
  }
  flt_copy(f, res);
  if ((f.exp + 1) >= MANT_SIZE) {
    return;
  }
  ex = ((res->mant)[f.exp + 1]);
  for (i = f.exp + 1; i < MANT_SIZE; i++) {
    (res->mant)[i] = 0;
  }
  if (f.exp == -1) {
    (res->sign) = 0;
    (res->exp) = 0;
  }
  switch (round_type) {
  default:
  case R2ZERO:
    return;
  case R2PINF:
    if ((f.sign != 1) || (ex == 0)) {
      return;
    }
    break;
  case R2NINF:
    if ((f.sign != -1) || (ex == 0)) {
      return;
    }
    break;
  case R2NEAR:
    if (ex < (unsigned int)(FBASE/2)) {
      return;
    }
    break;
  }
  ex = 1;
  for (i = f.exp; i >= 0; i--) {
    (res->mant)[i] =
	(unsigned short)((ex = ex + (unsigned int)((res->mant)[i])) % FBASE);
    /* CAST:jmf */
    if ((ex /= FBASE) == 0) {
      return;
    }
  }
  if (f.exp != -1) {
    (res->exp) ++;
  } else {
    (res->sign) = f.sign;
  }
  (res->mant)[0] = 1;
  for (i = 1; i < MANT_SIZE; i++) {
    (res->mant)[i] = 0;
  }
}

/*
 * "f" is a legal single precision number. "res" is a pointer to a single
 * precision number.
 *
 * On return, the number pointed to by "res" will be the integer value of
 * "f" rounded towards zero.
 */
void
flt_trunc(flt f, flt *res)
{
  int i;
  if (f.exp < 0) {
    flt_zero(res);
    return;
  }
  flt_copy(f, res);
  for (i = f.exp + 1; i < MANT_SIZE; i++) {
   (res->mant)[i] = 0;
  }
}

/*
 * "s" is a pointer to an array of characters. "f" is a pointer to a single
 * precision number. "ret" is NULL, or a pointer to a pointer to a character.
 *
 * On return, if the return value is OKAY, then the number pointed to by
 * "f" is the floating point number represented in the string "s".
 *
 * If "ret" was not NULL, then it will point to a pointer to the next character
 * in "s" not used in the number. If the return value is SYNTAX or EXP2BIG,
 * then the value of the number pointed to by "f" is undefined. In this case,
 * if "ret" was not NULL, then it will point to a pointer to the start of the
 * string. Leading white space in the string will be ignored.
 *
 * Numbers have the following form:
 * [+-]?(([0-9]+(\.[0-9]*)?)|([0-9]*\.[0-9]+))([Ee][+-]?[0-9]+)?
 */

#if FBASE == 10

int
str2flt(char *s, flt *f, char **r)
{
  int i = 0, ids = -1, rounded = 0, mant_empty = 1, zero = 1;
  (f->sign) = 1;
  (f->exp) = 0;
  if (r) {
    *r = s;
  }
  while ((*s) && (' ' == (*s))) {
    s++;
  }
  if (*s == '-') {
    (f->sign) = -1;
    s++;
  } else if (*s == '+') {
    s++;
  }
  while (*s == '0') {
    mant_empty = 0;
    s++;
  }
  while (*s >= '0' && *s <= '9') {
    mant_empty = 0;
    zero = 0;
    if (i < MANT_SIZE) {
      (f->mant)[i++] = ((*s) - '0');/* ASCII */
    } else if (!rounded) {
      flt_int_round(f,(*s) - '0');
      rounded = 1;		/* ASCII */
    }
    if (ids >= E_MAX) {
      return EXP2BIG;
    }
    ids++;
    s++;
  }
  if (*s == '.') {
    s++;
    if (zero) {
      while (*s == '0') {
	if (ids <= E_MIN) {
	  return EXP2BIG;
	}
	ids--;
	s++;
	mant_empty = 0;
      }
    }
    while (*s >= '0' && *s <= '9') {
      if (i < MANT_SIZE) {
	(f->mant)[i++] = ((*s) - '0');/* ASCII */
      } else if (!rounded) {
	flt_int_round(f,(*s) - '0');
	rounded = 1;		/* ASCII */
      }
      s++;
      zero = 0;
      mant_empty = 0;
    }
  }
  while (i < MANT_SIZE) {
    (f->mant)[i++] = 0;
  }
  if ((*s == 'E') || (*s == 'e')) {
    int e_sign = 1, exp_empty = 1;
    int e = 0;
    if (*++s == '-') {
      e_sign = -1;
      s++;
    } else if (*s == '+') {
      s++;
    }
    while ((*s) && (*s >= '0' && *s <= '9')) {
      if (e >= (E_MAX / 10)) {
	return EXP2BIG;
      }
      e = e * 10 + ((*s++) - '0');
      exp_empty = 0;		/* ASCII */
    }
    if (exp_empty) {
      return SYNTAX;
    }
    e *= e_sign;
    (f->exp) += (e + ids);
  } else {
    (f->exp) += ids;
  }
  if (((f->exp) >= E_MAX) || ((f->exp) <= E_MIN)) {
    return EXP2BIG;
  }
  if (zero) {
    (f->sign) = 0;
    (f->exp) = 0;
  }
  if (mant_empty) {
    return SYNTAX;
  }
  if (r) {
    *r = s;
  }
  return OKAY;
}

#endif

/*
 * Interface to  TDF translator
 */

/*
 * Memory allocation
 */
void
init_flpt(void)
{
  /* initialise */
  int i;
  flt *fzr;
  flt *forf;
  if (initial_flpts == 0) {
    flptnos = NULL;
  } else {
    flptnos = (flt *)xcalloc(initial_flpts, sizeof(flt));
  }
  tot_flpts = initial_flpts;
  for (i = 1; i < tot_flpts; ++i) {
    flptnos[i].exp = i - 1;
  }
  flptfree = tot_flpts - 1;
  flpt_left = tot_flpts;

  fzero_no = new_flpt();
  fone_no = new_flpt();
  fzr = &flptnos[fzero_no];
  fzr->sign = 0;
  fzr->exp = 0;
  forf = &flptnos[fone_no];
  forf->sign = 1;
  forf->exp = 0;
  for (i = 0; i < MANT_SIZE; i++) {
    (fzr->mant)[i] = 0;
    (forf->mant)[i] = 0;
  }
  (forf->mant)[0] = 1;

  return;
}

void
more_flpts(void)
{
  /* extend the floating point array */
  int i;
  tot_flpts += extra_flpts;
  flptnos = xrealloc(flptnos, tot_flpts * sizeof *flptnos);
  for (i = tot_flpts - extra_flpts + 1; i < tot_flpts; ++i) {
    flptnos[i].exp = i - 1;
  }
  flptfree = tot_flpts - 1;
  flpt_left = extra_flpts;
  return;
}

flpt
new_flpt(void)
{
  /* allocate space for a new floating point number */
  flpt r = flptfree;
  flptfree = flptnos[r].exp;
  if (--flpt_left == 0) {
    more_flpts();
  }
  return r;
}

void
flpt_ret(flpt f)
{
  /* return a floating point number to free */
  flptnos[f].exp = flptfree;
  flptfree = f;
  ++flpt_left;
  return;
}

/*
 * Do the test testno on and and b deliver 1 if true, 0 otherwise.
 */
int
cmpflpt(flpt a, flpt b, int testno)
{
  int res = flt_cmp(flptnos[a], flptnos[b]);

  switch (testno) {
  case 1:  return res ==  1;
  case 2:  return res != -1;
  case 3:  return res == -1;
  case 4:  return res !=  1;
  case 5:  return res ==  0;
  default: return res !=  0;
  }
}

#if FBASE == 10

flpt
floatrep(int n)
{
  flpt res = new_flpt();
  char *pr = intchars(n);
  /* this is wrong for unsigned integers */
  flt fr;
  IGNORE str2flt(pr, &fr,(char **)0);
  flptnos[res] = fr;
  return res;
}

flpt
floatrep_unsigned(unsigned int n)
{
  failer("floatrep_unsigned not used");
  return 0;
}

int
flpt_bits(floating_variety fv)
{
  return 0;
}

void
flpt_round(int round_t, int posn, flt *res)
{
  return;
}

#else

static flpt
floatrep_aux(int n, int sign)
{
  flpt res = new_flpt();
  flt fr;
  unsigned int mask = 0xffff;
  int i;
  int supp = 1;
  int index = 0;

  flt_zero(&fr);
  if (n == 0) {
    flptnos[res] = fr;
    return res;
  }

  fr.sign = sign;

  for (i = 1; i >= 0; --i) {
    int t = (int)((n >> (i * 16)) & (int)mask);
    if (supp && t) {
      supp = 0;
      fr.exp = i;
    }
    if (!supp) {
      fr.mant[index++] = (unsigned short)t;	/* CAST:jmf: */
    }
  }

  flptnos[res] = fr;
  return res;
}

flpt
floatrep(int n)
{
  if (n < 0) {
    return floatrep_aux(-n, -1);
  }
  return floatrep_aux(n, 1);
}

flpt
floatrep_unsigned(unsigned int n)
{
  return floatrep_aux((int)n, 1);
}

/*
 * Prepend a new digit to the MSB end of the current mantissa.
 * Sign and exponent are adjusted accordingly.
 *
 * The incoming digit may be in an arbitary base (unrelated to FBASE),
 * given by the base parameter.
 *
 * The result is normalised such that the mantissa has no leading zeroes.
 */
void
flpt_newdig(unsigned int dig, flt *res, int base)
{
	int i;
	unsigned int c = 0;

	if (dig != 0)
		res->sign = 1;


	i = MANT_SIZE - 1;

	for (; i >= 0; --i) {
		c = (unsigned int)(((int)res->mant[i] * base) + (int)c);
		res->mant[i] = (unsigned short)(c % FBASE);
		c = c / FBASE;
	}

	if (c) {
		++res->exp;
		i = res->exp;

		if (i >= MANT_SIZE)
			i = MANT_SIZE - 1;

		for (; i >= 1; --i)
			res->mant[i] = res->mant[i-1];

		res->mant[0] = (unsigned short)c;
	}

	if (res->exp >= MANT_SIZE)
		return;

	c = dig;
	for (i = res->exp; c && i >= 0; --i) {
		c = (unsigned int)(res->mant[i] + c);
		res->mant[i] = (unsigned short)(c % FBASE);
		c = c / FBASE;
	}

	if (c) {
		++res->exp;
		i = res->exp;

		if (i >= MANT_SIZE)
			i = MANT_SIZE - 1;

		for (; i >= 1; --i)
			res->mant[i] = res->mant[i-1];

		res->mant[0] = (unsigned short)c;
	}
}

void
flpt_scale(int expt, flt *res, int base)
{
  flt ft;

  if (base == 10) {
    if (expt > 0) {
      if (expt > MAX_USEFUL_DECEXP) {
	failer(BIG_FLPT);
	exit(EXIT_FAILURE);
	/* UNREACHED */
      }
      while (expt > 16) {
	IGNORE flt_mul(*res, powers[15], &ft); /* cannot fail */
	flt_copy(ft, res);
	expt -= 16;
      }
      IGNORE flt_mul(*res, powers[expt - 1], &ft); /* cannot fail */
      flt_copy(ft, res);
    } else if (expt < 0) {
      if (expt < - MAX_USEFUL_DECEXP) {
	flt_zero(res);
	return;
      }
      while (expt < -16) {
	IGNORE flt_div(*res, powers[15], &ft); /* cannot fail */
	flt_copy(ft, res);
	expt += 16;
      }
      IGNORE flt_div(*res, powers[-1 - expt], &ft); /* cannot fail */
      flt_copy(ft, res);
    }
  } else {
    if (base == 4) {
      expt += expt;
    }
    if (base == 8) {
      expt *= 3;
    }
    if (base == 16) {
      expt *= 4;
    }

    if (expt > 0) {
      res->exp += (expt / 16);
      expt = expt % 16;
      if (expt != 0) {
	flpt_newdig((unsigned int)0, res, two_powers[expt]);
      }
      return;
    } else if (expt < 0) {
      int temp = ((-expt) / 16);
      expt = (-expt)% 16;
      if (expt == 0) {
	res->exp -= temp;
      } else {
	flpt_newdig((unsigned int)0, res, two_powers[16 - expt]);
	res->exp -= (temp+1);
      }
    }
  }
  return;
}

/*
 * posn is the number of bits to be left correct after the rounding operation.
 */
void
flpt_round(int round_t, int posn, flt * res)
{
  unsigned int c = res->mant[0];
  unsigned int mask;
  int ndig0 = 0;
  int i, bitpos;
  int digpos = 0;
  int bits_discarded = 0;

  if (res->sign == 0) {
    return;
  }

  for (mask = FBASE - 1; mask & c; mask <<= 1) {
    ++ndig0;
  }

  bitpos = ndig0 - posn;

  while (bitpos < 1) {
    bitpos += FBITS;
    ++digpos;
  };

  --bitpos;

  /*
   * digpos holds the number of the FBASE digit to be rounded,
   * bitpos holds the number of the bit within that digit to have one added.
   */

  for (i = digpos + 1; i < MANT_SIZE; ++i) {
    if (res->mant[i]) {
      bits_discarded = 1;
      res->mant[i] = 0;
    }
  }

  switch (round_t) {
  default:
  case R2ZERO:
    res->mant[digpos] =
	(unsigned short)(res->mant[digpos] & bitmask[bitpos + 1]);
    return;
  case R2PINF:
    if (res->sign != 1 ||
	(!bits_discarded && ((res->mant[digpos] & bitmask[bitpos + 1]) ==
			     (int)res->mant[digpos]))) {
      res->mant[digpos] =
	  (unsigned short)(res->mant[digpos] & bitmask[bitpos + 1]);

      return;
    }
    res->mant[digpos] = (unsigned short)(res->mant[digpos] | bitround[bitpos]);
    break;
  case R2NINF:
    if (res->sign == 1 ||
	(!bits_discarded && ((res->mant[digpos] & bitmask[bitpos + 1]) ==
			     (int)res->mant[digpos]))) {
      res->mant[digpos] = (unsigned short)((int)res->mant[digpos] &
					   (int)bitmask[bitpos + 1]);

      return;
    }
    res->mant[digpos] = (unsigned short)((int)res->mant[digpos] |
					 (int)bitround[bitpos]);
    break;
  case R2NEAR:
    break;
  }

  res->mant[digpos] = (unsigned short)((int)res->mant[digpos] &
				       (int)bitmask[bitpos]);

  c = bitround[bitpos];
  for (i = digpos; c && i >= 0; --i) {
    c = (unsigned int)((int)res->mant[i] + (int)c);
    res->mant[i] = (unsigned short)(c % FBASE);	/* CAST:jmf: */
    c = c / FBASE;
  }
  if (c) {
    ++res->exp;
    i = res->exp;
    if (i >= MANT_SIZE) {
      i = MANT_SIZE - 1;
    }
    for (; i >= 1; --i) {
      res->mant[i] = res->mant[i-1];
    }
    res-> mant[0] = (unsigned short)c;
  }
  res->mant[digpos+ (int)c] = (unsigned short)((int)res->mant[digpos + (int)c] &
					       (int)bitmask[bitpos + 1]);
  return;
}

int
flpt_bits(floating_variety fv)
{
  switch (fv) {
  case 0: return FLOAT_BITS;
  case 1: return DOUBLE_BITS;
  case 2: return LDOUBLE_BITS;
  }

  return 0;
}

int
flpt_round_to_integer(int rndmd, flt *f)
{
  unsigned int c = f->mant[0];
  unsigned int mask;
  int ndig0 = 0;
  int intbits;
  int res;

  if (f->sign == 0) {
    return 0;
  }

  for (mask = FBASE - 1; mask & c; mask <<= 1)
    ++ndig0;
  intbits = ndig0 + (f->exp * FBITS);

  if (intbits >= 0) {
    flpt_round(rndmd, intbits, f);
  } else {
    switch (rndmd)EXHAUSTIVE {
    case R2ZERO:
      break;
    case R2PINF:
      if (f->sign == 1) {
	flt_copy(flptnos[fone_no], f);
      } else {
	flt_zero(f);
      }
      break;
    case R2NINF:
      if (f->sign == -1) {
	flt_copy(flptnos[fone_no], f);
	f->sign = -1;
      } else {
	flt_zero(f);
      }
      break;
    case R2NEAR:
      break;
    }
  }

  /*
  if (has & HAS_64_BIT) {
    if (f->exp > 3) {
      int ij;
      f->mant[0] = f->mant[f->exp - 3];
      f->mant[1] = f->mant[f->exp - 2];
      f->mant[2] = f->mant[f->exp - 1];
      f->mant[3] = f->mant[f->exp];
      for (ij = 4; ij <= f->exp; ++ij) {
        f->mant[ij] = 0;
      }
      f->exp = 3;
    }
  } else {
    if (f->exp > 1) {
      f->mant[0] = f->mant[f->exp - 1];
      f->mant[1] = f->mant[f->exp];
      f->exp = 1;
    }
  }
   */

  if (f->exp == 1) {
    res = ((int)f->mant[1] + ((int)f->mant[0] << 16));
  } else {
    res = (int)(f->mant[0]);
  }
  return res * f->sign;  /* this is only valid for 32-bit results */
}

/*
 * Convert flt * to IEEE representation in ints.
 * sw is 0 for single, 1 for double, 2 for extended.
 */
r2l
real2longs_IEEE(flt *fp, int sw)
{
  r2l res;
  flt f;
  unsigned int c = fp->mant[0];
  unsigned int mask;
  int ndig0 = 0;
  int expt;
  int bias, expt_size, precision;
  unsigned int sig1, sig2 = 0, sig3 = 0, sig4 = 0;
  int i, index;
  res.i1 = 0;
  res.i2 = 0;
  res.i3 = 0;
  res.i4 = 0;

  if (fp->sign == 0) {
    return res;
  }

  f = *fp;

  switch (sw)EXHAUSTIVE {
  case 0:
    bias = 127;
    expt_size = 8;
    precision = 24;
    break;
  case 1:
    bias = 1023;
    expt_size = 11;
    precision = 53;
    break;
  case 2:
    bias = 16383;
    expt_size = 15;
    precision = LDOUBLE_BITS;
    break;
  }

  for (mask = FBASE - 1; mask & c; mask <<= 1) {
    ++ndig0;
  }
  expt = ndig0 + (f.exp * FBITS) - 1;

  if (expt < (1-bias-precision)) {
    /* 0 - underflowed */
    return res;
  }

  if (expt > bias) {
    if (check & CHECK_FLPT_OVERFLOW) {
      failer(BIG_FLPT);
      exit(EXIT_FAILURE);
    }
    switch (sw) {
    case 0:
      if (f.sign == -1) {
	res.i1 = 0x80000000;
      }
      res.i1 += 0x7f800000;
      return res;
    case 1:
      if (f.sign == -1) {
	res.i2 = 0x80000000;
      }
      res.i2 += 0x7ff00000;
      return res;
    case 2:
#if TRANS_80x86
      if (f.sign == -1) {
	res.i3 = 0x8000;
      }
      res.i3 += 0x7fff;
      res.i2 = 0x80000000;
      return res;
#else
#if TRANS_SPARC || TRANS_HPPA
      if (f.sign == -1) {
	res.i4 = 0x8000;
      }
      res.i4 += 0x7fff;
      return res;
#else
      failer("long double not implemented");
      return res;
#endif
#endif
    }
  }

  expt += bias;
  i = precision - ndig0;;
  sig1 = f.mant[0];
  index = 1;
  while (i >= 16) {
    sig4 <<= 16;
    sig4 += (sig3 >> 16);
    sig3 <<= 16;
    sig3 += (sig2 >> 16);
    sig2 <<= 16;
    sig2 += (sig1 >> 16);
    sig1 <<= 16;
    sig1 = (unsigned int)(sig1 + f.mant[index++]);
    i -= 16;
  }
  if (i != 0) {
    sig4 <<= i;
    sig4 += (sig3 >> (32-i));
    sig3 <<= i;
    sig3 += (sig2 >> (32-i));
    sig2 <<= i;
    sig2 += (sig1 >> (32-i));
    sig1 <<= i;
    sig1 = (unsigned int)(sig1 + (f.mant[index] >> (16 - i)));
  }

  if (expt < 1) {
    int places = 1 - expt;
    while (places >= 32) {
      sig1 = sig2;
      sig2 = sig3;
      sig3 = sig4;
      sig4 = 0;
      places -= 32;
    }
    if (places > 0) {
      sig1 = (sig1 >> places) + (sig2 << (32 - places));
      sig2 = (sig2 >> places) + (sig3 << (32 - places));
      sig3 = (sig3 >> places) + (sig4 << (32 - places));
      sig4 >>= places;
    }
    expt = 0;
  } else {
    expt &= ((1 << (expt_size+1)) -1);
  }

  switch (sw) {
  case 0:
    if (f.sign == -1) {
      res.i1 = 0x80000000;
    }
    res.i1 += (expt << 23);
    res.i1 += (int)(sig1 & 0x007fffff);
    break;
  case 1:
    if (f.sign == -1) {
      res.i2 = 0x80000000;
    }
    res.i2 += (expt << 20);
    res.i2 += (int)(sig2 & 0xfffff);
    res.i1 = (int)sig1;
    break;
  case 2:
#if defined(TRANS_80x86)
    res.i1 = (int)sig1;
    res.i2 = (int)sig2;
    if (f.sign == -1) {
      res.i3 = 0x8000;
    }
    res.i3 += expt;
    UNUSED(sig3);
    UNUSED(sig4);
    break;
#elif defined(TRANS_SPARC) || defined(TRANS_HPPA)
    if (f.sign == -1) {
      res.i4 = 0x80000000;
    }
    res.i4 += (expt << 16);
    res.i4 += (int)(sig4 & 0xffff);
    res.i3 = (int)sig3;
    res.i2 = (int)sig2;
    res.i1 = (int)sig1;
    break;
#else
    failer("long double not implemented");
    return res;
#endif
  }

  return res;
}

#endif
