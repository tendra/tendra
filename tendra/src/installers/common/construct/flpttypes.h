/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:47 $
$Revision: 1.1.1.1 $
$Log: flpttypes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/
#ifndef flpttypekey
#define flpttypekey 1



#include <limits.h>

#include "fbase.h"



#if FBASE == 10

/* FBASE 10 is obsolete */

# define MANT_SIZE 40

#define Fdig unsigned char

# define FNUM_SIZE 65		/* max size required by flt2str */
/* MANT_SIZE + 1(sign) + 1(point) + 2(E+sign) + log(MAX_LONG) + 1(null) */

#define E_MIN	(-1000000)	/* (LONG_MIN/10) doesnt work on 80386 cc 
				*/
#define E_MAX	(LONG_MAX/10)

/* Function status values:   */
# define OKAY		0
# define EXP2BIG	(-1)
# define SYNTAX		(-2)
# define DIVBY0		(-3)

/* Rounding types:   */
# define R2ZERO	0
# define R2PINF	1
# define R2NINF	2
# define R2NEAR	3

typedef struct _flt {
  Fdig  mant[MANT_SIZE];
				/* mantissa digit values [0-9] (NOT '0' to
				   '9') */
  /* point is between 1st and 2nd digits */
  int   sign;			/* -1: negative; +1: positive; 0: value is
				   zero */
  int  exp;			/* signed exponent; in range E_MIN..E_MAX 
				*/
}                   flt;	/* floating point representation */


#else

/* all installers should use this definition */

#ifndef MANT_SIZE
#define MANT_SIZE 8
#endif

	/* MANT_SIZE is the number of mantissa array elements */

#define Fdig unsigned short
#define FBITS 16
	/* FBITS is the number of bits in one array element */

#define E_MIN	(-16384)
#define E_MAX	(LONG_MAX/FBASE)

/* Function status values:   */
# define OKAY		0
# define EXP2BIG	(-1)
# define SYNTAX		(-2)
# define DIVBY0		(-3)

/* Rounding types:   */
# define R2ZERO	3
# define R2PINF	2
# define R2NINF	1
# define R2NEAR	0

typedef struct _flt {
  Fdig  mant[MANT_SIZE];
  /* point is between 1st and 2nd digits */
  int   sign;			/* -1: negative; +1: positive; 0: value is
				   zero */
  int  exp;			/* signed exponent; in range E_MIN..E_MAX 
				*/
}                   flt;	/* floating point representation */


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
	/* used to convert flpt number which are integers into a
	   64 bit representation */


#endif
