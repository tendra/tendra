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


/* 	cross.h,v 1.3 1995/05/23 10:54:50 john Exp	 */

/*
  cross.h

  This file contains a set of macros & function declarations 
  to process the 64 bit integer type INT64.  If compiling on a 
  platform with 64 bit longs, INT64 can be represented as a 
  long and the operations can be implemented by macros expanding 
  to the simple arithmetic operations.  If, however, a 64 bit 
  integral type is not available, then INT64 is represented 
  by the flt64 type (see flpttypes.h) and the operations are 
  represented by a set of functions, defined in cross.c
*/

/*
  cross.h,v
 * Revision 1.3  1995/05/23  10:54:50  john
 * Minor fixes to 64 bit support
 *
 * Revision 1.2  1995/05/16  10:46:21  john
 * Cosmetic change
 *
 * Revision 1.1.1.1  1995/03/23  10:39:05  john
 * Entered into CVS
 *
 * Revision 1.11  1995/03/23  10:03:18  john
 * Corrected some definitions
 *
 * Revision 1.10  1995/01/26  13:32:13  john
 * Corrected a few macro definitions
 *
*/

#ifndef CROSS_H
#define CROSS_H
#include <limits.h>
/*typedef char bool;*/
#include "output.h"
#include "flpttypes.h"
#include "exptypes.h"
#include "common_types.h"
extern flt64 exp_to_f64 PROTO_S ((exp));
typedef int INT32;
typedef unsigned int UINT32;
#define int8 char
#define int16 short
#define int32 int

#define is64(X)	((name(X)==u64hd)||(name(X)==s64hd)||(name(X)==ptrhd))
#define is32(X) ((name(X)==slonghd)||(name(X)==ulonghd))

/* some macros to access the fields of the flt64/INT64 type */
#if FS_64_BIT /* 64 bit ints can be represented as longs */
typedef long INT64;
#define clear_INT64(x)	((x)=0)
#define low_INT64(x)	(x)
#define isquad(x)	((unsigned long)(x)>UINT_MAX)

#define INT64_assign(x,y) ((x) = (y))
#define out_INT64(x) (void)outlong((x))
#define INT64_mult(x,y,z) ((z)?((x)*(y)):((unsigned long)((x)*(y))))
#if 0
#define INT64_divide(x,y,z) ((z)?((x)/(y)):(unsigned long)((x)/(y)))
#else
#define INT64_divide(x,y,z) ((x)/(y))
#endif
#define INT64_mod(x,y,z) ((x)%(y))
#define INT64_add(x,y,z) ((z)?((x)+(y)):(unsigned long)((x)+(y)))
#if 0
#define INT64_subtract(x,y,z) ((z)?((x)-(y)):(unsigned long)((x)-(y)))
#else
#define INT64_subtract(x,y,z) ((x)-(y))
#endif
#define INT64_increment(x) ((x)+1)
#define INT64_decrement(x) ((x)-1)
#define INT64_or(x,y) ((x)|(y))
#define INT64_and(x,y) ((x)&(y))
#define INT64_not(x) (~(x))
#define INT64_xor(x,y) ((x)^(y))
#define INT64_shift_left(x,y,z) ((x)<<(y))
#define INT64_shift_right(x,y,z) ((x)>>(y))
#define INT64_eq(x,y) ((x)==(y))
#define INT64_leq(x,y) ((x)<=(y))
#define INT64_lt(x,y) ((x)<(y))
#define INT64_abs(x) (((x)>0)?(x):-(x))
#define make_INT64(big,small)	((small)+(((long)(big))<<32))
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

#define INT64_assign(x,y) ((x) = (y))
void out_INT64 PROTO_S ((INT64));
INT64 INT64_mult PROTO_S ((INT64,INT64,bool));
INT64 INT64_divide PROTO_S ((INT64,INT64,bool));
INT64 INT64_add PROTO_S ((INT64,INT64,bool));
INT64 INT64_subtract PROTO_S ((INT64,INT64,bool));
INT64 INT64_mod PROTO_S ((INT64,INT64,bool));

INT64 INT64_increment PROTO_S ((INT64));
INT64 INT64_decrement PROTO_S ((INT64));

INT64 INT64_or PROTO_S ((INT64,INT64));
INT64 INT64_and PROTO_S ((INT64,INT64));
INT64 INT64_not PROTO_S ((INT64));
INT64 INT64_xor PROTO_S ((INT64,INT64));

INT64 INT64_shift_left PROTO_S ((INT64,int,int));
INT64 INT64_shift_right PROTO_S ((INT64,int,int));

bool INT64_eq  PROTO_S ((INT64,INT64));
bool INT64_leq PROTO_S ((INT64,INT64));
bool INT64_lt  PROTO_S ((INT64,INT64));

INT64 make_INT64 PROTO_S ((INT32,UINT32));

#define umax {0xffffffff,0xffffffff}
#define smin {0x80000000,0x00000000}
#define zero_int64 make_INT64(0,0)
/*#define zero_int64 {0,0}*/
#endif 	/* #if alpha */

INT64  flt64_to_INT64 PROTO_S ((flt64));
INT64  exp_to_INT64 PROTO_S ((exp));


#endif	/* #ifndef CROSS_H */

			 

			   
  
   
