/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This file contains code to allow 64 bit arithmetic to be handled portably.
 */

#include <stdio.h>

#include <shared/bool.h>

#include <construct/flpt.h>
#include <construct/dec.h>

#include <main/print.h>

#include "cross.h"
#include "main.h"

#if BLDARCHBITS == 64

INT64
flt64_to_INT64(flt64 arg)
{
  INT64 res;
  res = arg.small+((long)arg.big<<32);
  return res;
}


INT64
exp_to_INT64(exp e)
{
  if(isbigval(e)){
    return flt64_to_INT64(exp_to_f64(e));
  }
  else{
    return no(e);
  }
}

#else /* BLDARCHBITS */

/*
 * This function outputs a literal 64 bit int value to the assembler file.
 * If the value of the argument exceeds the integer range of the machine
 * it is output in hexadecimal representation; otherwise it is output
 * as a decimal.
 */
void
out_INT64(INT64 val)
{
  if(isquad(val)){
	asm_printf( "0x%08x%08x", high_INT64(val), low_INT64(val));
  } else{
	asm_printf( "%d", low_INT64(val));
  }
}

/*
 * The following functions implement the basic arithmetic operations
 * for the INT64 type.
 *
 * In each case the procedure is to convert the arguments into the internal
 * floating point representation and then use the floating point arithmetic
 * and conversion functions provided by the common installer code to
 * calculate the result.
 *
 * In the event of an error in evaluation the functions will each print an error
 * message and execution will halt; otherwise the result will be returned
 * as an INT64.
 *
 * Note: As the f64_to_flt function can change the base address of flptnos,
 * all references to the flptnos array should be made _after_ this function
 * has been called.
 */

INT64
INT64_mult(INT64 arg1, INT64 arg2, bool sgned)
{
  int ov;
  flpt farg1;
  flpt	farg2;
  flt64 res;
  flpt fresno=new_flpt();
  flt *fres;
  farg1 = f64_to_flt(arg1,sgned);
  farg2 = f64_to_flt(arg2,sgned);
  fres= &flptnos[fresno];
  if(flt_mul(flptnos[farg1],flptnos[farg2],fres)==EXP2BIG){
    error(ERR_SERIOUS, "Overflow: 64 bit multiplication failed");
  }
  res = flt_to_f64(fresno,sgned,&ov);
  flpt_ret(fresno);
  flpt_ret(farg1);
  flpt_ret(farg2);
  return flt64_to_INT64(res);
}


INT64
INT64_divide(INT64 arg1, INT64 arg2, bool sgned)
{
  flpt farg1;
  flpt farg2;
  flt64 res;
  flpt fresno = new_flpt();
  flt  *fres;
  int ov;
  int divexit;
  farg1 = f64_to_flt(arg1,sgned);
  farg2 = f64_to_flt(arg2,sgned);
  fres = &flptnos[fresno];
  divexit = flt_div(flptnos[farg1],flptnos[farg2],fres);
  if((divexit == EXP2BIG)||(divexit == DIVBY0)){
    error(ERR_SERIOUS, "Overflow: 64 bit division failed");
  }
  res = flt_to_f64(fresno,sgned,&ov);
  flpt_ret(fresno);
  flpt_ret(farg1);
  flpt_ret(farg2);
  return flt64_to_INT64(res);
}


INT64
INT64_add(INT64 arg1, INT64 arg2, bool sgned)
{
  flpt farg1;
  flpt farg2;
  flpt fresno = new_flpt();	
  flt  *fres;
  flt64 res;
  int ov;
  farg1 = f64_to_flt(arg1,sgned);
  farg2 = f64_to_flt(arg2,sgned);
  fres  = &flptnos[fresno];
  if(flt_add(flptnos[farg1],flptnos[farg2],fres) == EXP2BIG){
    error(ERR_SERIOUS, "Overflow: 64 bit addition failed");
  }
  res = flt_to_f64(fresno,sgned,&ov);
  flpt_ret(fresno);
  flpt_ret(farg1);
  flpt_ret(farg2);
  return flt64_to_INT64(res);
}


INT64
INT64_subtract(INT64 arg1, INT64 arg2, bool sgned)
{
  flpt farg1;
  flpt farg2;
  flpt fresno = new_flpt();
  flt *fres;
  flt64 res;
  int ov;
  farg1 = f64_to_flt(arg1,sgned);
  farg2 = f64_to_flt(arg2,sgned); 
  fres = &flptnos[fresno];
  if(flt_sub(flptnos[farg1],flptnos[farg2],fres) == EXP2BIG){
    error(ERR_SERIOUS, "Overflow: 64 bit subtraction failed");
  }
  res = flt_to_f64(fresno,sgned,&ov);
  flpt_ret(fresno);
  flpt_ret(farg1);
  flpt_ret(farg2);
  return flt64_to_INT64(res);
}  


INT64
INT64_increment(INT64 arg)
{
  INT64 inc_64=make_INT64(0U,1);
  return INT64_add(arg,inc_64,1);
}

INT64
INT64_decrement(INT64 arg)
{
  INT64 dec_64=make_INT64(0U,1);
  return INT64_subtract(arg,dec_64,1);
}

/*
 * The following functions implement bitwise logical operations
 * for the INT64 type.
 */

INT64
INT64_or(INT64 arg1, INT64 arg2)
{
  INT64 res;
  low_INT64(res)=low_INT64(arg1)|low_INT64(arg2);
  high_INT64(res)=high_INT64(arg1)|high_INT64(arg2);
  return res;
}

INT64
INT64_and(INT64 arg1, INT64 arg2)
{
  INT64 res;
  low_INT64(res)=low_INT64(arg1)&low_INT64(arg2);
  high_INT64(res)=high_INT64(arg1)&high_INT64(arg2);
  return res;
}

INT64
INT64_not(INT64 arg)
{
  INT64 res;
  low_INT64(res) = ~low_INT64(arg);
  high_INT64(res) = ~high_INT64(arg);
  return res;
}

/*
 * The following functions implement left and right shift operations
 * for the INT64 type.
 */

INT64
INT64_shift_left(INT64 arg, int shift, int sgned)
{
  INT64 multiplier;
  if(shift<=31){
    low_INT64(multiplier)=(1<<shift);
    high_INT64(multiplier)=0;
  }
  else{
    high_INT64(multiplier)=(1<<(shift-32));
    low_INT64(multiplier)=0;
  }
  return INT64_mult(arg,multiplier,sgned);
}



INT64
INT64_shift_right(INT64 arg, int shift, int sgned)
{
  INT64 divisor;
  if(shift<=31){
    low_INT64(divisor)=(1<<shift);
    high_INT64(divisor)=0;
  }
  else{
    low_INT64(divisor)=0;
    high_INT64(divisor)=(1<<(shift-32));
  }
  return INT64_divide(arg,divisor,sgned);
}

/*
 * The following functions implement the comparison operations
 * >, >= and = for the INT64 type.
 */

bool
INT64_eq(INT64 arg1, INT64 arg2)
{
  return low_INT64(arg1)==low_INT64(arg2))&&
    (high_INT64(arg1)==high_INT64(arg2);
}

bool
INT64_leq(INT64 arg1, INT64 arg2)
{
  /* test arg1<arg2 */
  return (high_INT64(arg1)<high_INT64(arg2))||
	  ((high_INT64(arg1)==high_INT64(arg2))&&
	   (low_INT64(arg1)<=low_INT64(arg2)));
}

bool
INT64_lt(INT64 arg1, INT64 arg2)
{
  return (high_INT64(arg1)<high_INT64(arg2))||
	  ((high_INT64(arg1)==high_INT64(arg2))&&
	   (low_INT64(arg1)<low_INT64(arg2)));
}

/*
 * This function constructs an INT64 variable from two INT32
 */
INT64
make_INT64(INT32 big, UINT32 small)
{
  INT64 res;
  high_INT64(res)=big;
  low_INT64(res)=small;
  return res;
}

#endif /* BLDARCHBITS */
