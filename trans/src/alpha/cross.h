/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  cross.h

  This file contains a set of macros & function declarations
  to process the 64 bit integer type INT64.  If compiling on a
  platform with 64 bit longs, INT64 can be represented as a
  long and the operations can be implemented by macros expanding
  to the simple arithmetic operations.  If, however, a 64 bit
  integral type is not available, then INT64 is represented
  by the flt64 type (see flpt.h) and the operations are
  represented by a set of functions, defined in cross.c
*/

#ifndef CROSS_H
#define CROSS_H

#include <limits.h>

#include <reader/exp.h>

#include <construct/installtypes.h>

#include <flpt/flpt.h>

extern flt64 exp_to_f64(exp);
typedef int INT32;
typedef unsigned int UINT32;
#define int8 char
#define int16 short
#define int32 int

#define is64(X)	((X->tag ==u64hd) || (X->tag ==s64hd) || (X->tag ==ptrhd))
#define is32(X)((X->tag ==slonghd) || (X->tag ==ulonghd))

/* some macros to access the fields of the flt64/INT64 type */
#if BLDARCHBITS == 64 /* 64 bit ints can be represented as longs */
typedef long INT64;
#define clear_INT64(x)	((x) =0)
#define low_INT64(x)	(x)
#define isquad(x)	((unsigned long)(x) >UINT_MAX)

#define INT64_assign(x,y)((x) = (y))
#define out_INT64(x)(void)asm_printf("%ld", (x))
#define INT64_mult(x,y,z)((z)?((x)*(y)):((unsigned long)((x)*(y))))
#if 0
#define INT64_divide(x,y,z)((z)?((x) / (y)):(unsigned long)((x) / (y)))
#else
#define INT64_divide(x,y,z)((x) / (y))
#endif
#define INT64_mod(x,y,z)((x)%(y))
#define INT64_add(x,y,z)((z)?((x) + (y)):(unsigned long)((x) + (y)))
#if 0
#define INT64_subtract(x,y,z)((z)?((x) - (y)):(unsigned long)((x) - (y)))
#else
#define INT64_subtract(x,y,z)((x) - (y))
#endif
#define INT64_increment(x)((x) +1)
#define INT64_decrement(x)((x) -1)
#define INT64_or(x,y)((x) | (y))
#define INT64_and(x,y)((x) & (y))
#define INT64_not(x)(~(x))
#define INT64_xor(x,y)((x)^(y))
#define INT64_shift_left(x,y,z)((x) << (y))
#define INT64_shift_right(x,y,z)((x) >> (y))
#define INT64_eq(x,y)((x) == (y))
#define INT64_leq(x,y)((x) <= (y))
#define INT64_lt(x,y)((x) < (y))
#define INT64_abs(x)(((x) >0)?(x):- (x))
#define make_INT64(big,small)	((small) + (((long)(big)) <<32))
#define umax 0xffffffffffffffffUL
#define smin 0x8000000000000000L
#define zero_int64 0L

#else	/* no 64 bit integral type available, use a struct of 2 32s */
typedef flt64 INT64;
#define clear_INT64(x)	{(x).big=0;(x).small=0;}
#define low_INT64(x)	(x).small
#define high_INT64(x)	(x).big
#define isquad(x)	((x).big!=0)
#define flt64_to_INT64(x) (x)		/* the types are identical */

#define INT64_assign(x,y)((x) = (y))
void out_INT64(INT64);
INT64 INT64_mult(INT64,INT64,bool);
INT64 INT64_divide(INT64,INT64,bool);
INT64 INT64_add(INT64,INT64,bool);
INT64 INT64_subtract(INT64,INT64,bool);
INT64 INT64_mod(INT64,INT64,bool);

INT64 INT64_increment(INT64);
INT64 INT64_decrement(INT64);

INT64 INT64_or(INT64,INT64);
INT64 INT64_and(INT64,INT64);
INT64 INT64_not(INT64);
INT64 INT64_xor(INT64,INT64);

INT64 INT64_shift_left(INT64,int,int);
INT64 INT64_shift_right(INT64,int,int);

bool INT64_eq(INT64,INT64);
bool INT64_leq(INT64,INT64);
bool INT64_lt(INT64,INT64);

INT64 make_INT64(INT32,UINT32);

#define umax {0xffffffff,0xffffffff}
#define smin {0x80000000,0x00000000}
#define zero_int64 make_INT64(0,0)
/*#define zero_int64 {0,0}*/
#endif 	/* #if alpha */

INT64  flt64_to_INT64(flt64);
INT64  exp_to_INT64(exp);


#endif	/* #ifndef CROSS_H */




