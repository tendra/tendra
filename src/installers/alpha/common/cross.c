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


/* 	$Id: cross.c,v 1.1.1.1 1998/01/17 15:55:59 release Exp $	 */

#ifndef lint
static char vcid[] = "$Id: cross.c,v 1.1.1.1 1998/01/17 15:55:59 release Exp $";
#endif /* lint */

/*
$Log: cross.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:59  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/05/23  10:54:34  john
 * Cosmetic changes
 *
 * Revision 1.1.1.1  1995/03/23  10:39:05  john
 * Entered into CVS
 *
 * Revision 1.8  1995/01/12  15:03:36  john
 * Minor Fix
 *
*/

/*
  cross.c

  This file contains code to allow 64 bit arithmetic to be handled 
  portably.
*/

#include "output.h"
#include "config.h"
#include "flpttypes.h"
#include "cross.h"
#include "main.h"
#include "config.h"
#include "fail.h"
#include "flpt.h"
#include "f64.h"
#include "expmacs.h"

#if FS_64_BIT

INT64 flt64_to_INT64
    PROTO_N ( ( arg ) )
    PROTO_T ( flt64 arg )
{
  INT64 res;
  res = arg.small+((long)arg.big<<32);
  return res;
}


INT64 exp_to_INT64
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
  if(isbigval(e)){
    return flt64_to_INT64(exp_to_f64(e));
  }
  else{
    return no(e);
  }
}




#else /* FS_64_BIT */

/*
  This function outputs a literal 64 bit int value to the 
  assembler file.  If the value of the argument exceeds the integer
  range of the machine it is output in hexadecimal representation;
  otherwise it is output as a decimal.
*/
void out_INT64
    PROTO_N ( ( val ) )
    PROTO_T ( INT64 val )
{
  if(isquad(val)){
    outhex(high_INT64(val));
    outhigh(low_INT64(val));
  }
  else{
    outint(low_INT64(val));
  }
}



/*
  The following functions implement the basic arithmetic 
  operations for the INT64 type.  In each case the procedure 
  is to convert the arguments into the internal floating point 
  representation and then use the floating point arithmetic and 
  conversion functions provided by the common installer code to 
  calculate the result.  In the event of an error in evaluation 
  the functions will each print an error message and execution 
  will halt; otherwise the result will be returned as an INT64.
  note: as the f64_to_flt function can change the base address 
  of flptnos, all references to the flptnos array should be made 
  _after_ this function has been called.
*/

/*******************************************************************/

INT64 INT64_mult
    PROTO_N ( ( arg1,arg2,sgned ) )
    PROTO_T ( INT64 arg1 X INT64 arg2 X bool sgned )
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
    alphafail(BIG_MULTIPLICATION);
    abort();
  }
  res = flt_to_f64(fresno,sgned,&ov);
  flpt_ret(fresno);
  flpt_ret(farg1);
  flpt_ret(farg2);
  return flt64_to_INT64(res);
}


INT64 INT64_divide
    PROTO_N ( ( arg1,arg2,sgned ) )
    PROTO_T ( INT64 arg1 X INT64 arg2 X bool sgned )
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
    alphafail(BIG_DIVISION);
    abort();
  }
  res = flt_to_f64(fresno,sgned,&ov);
  flpt_ret(fresno);
  flpt_ret(farg1);
  flpt_ret(farg2);
  return flt64_to_INT64(res);
}


INT64 INT64_add
    PROTO_N ( ( arg1,arg2,sgned ) )
    PROTO_T ( INT64 arg1 X INT64 arg2 X bool sgned )
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
    alphafail(BIG_ADDITION);
    abort();
  }
  res = flt_to_f64(fresno,sgned,&ov);
  flpt_ret(fresno);
  flpt_ret(farg1);
  flpt_ret(farg2);
  return flt64_to_INT64(res);
}


INT64 INT64_subtract
    PROTO_N ( ( arg1,arg2,sgned ) )
    PROTO_T ( INT64 arg1 X INT64 arg2 X bool sgned )
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
    alphafail(BIG_SUBTRACTION);
    abort();
  }
  res = flt_to_f64(fresno,sgned,&ov);
  flpt_ret(fresno);
  flpt_ret(farg1);
  flpt_ret(farg2);
  return flt64_to_INT64(res);
}  


INT64 INT64_increment
    PROTO_N ( ( arg ) )
    PROTO_T ( INT64 arg )
{
  INT64 inc_64=make_INT64(0U,1);
  return INT64_add(arg,inc_64,1);
}

INT64 INT64_decrement
    PROTO_N ( ( arg ) )
    PROTO_T ( INT64 arg )
{
  INT64 dec_64=make_INT64(0U,1);
  return INT64_subtract(arg,dec_64,1);
}

  

/*******************************************************************/
  


/*
   The following functions implement bitwise logical operations 
   for the INT64 type.  
*/

/*******************************************************************/

INT64 INT64_or
    PROTO_N ( ( arg1,arg2 ) )
    PROTO_T ( INT64 arg1 X INT64 arg2 )
{
  INT64 res;
  low_INT64(res)=low_INT64(arg1)|low_INT64(arg2);
  high_INT64(res)=high_INT64(arg1)|high_INT64(arg2);
  return res;
}

INT64 INT64_and
    PROTO_N ( ( arg1,arg2 ) )
    PROTO_T ( INT64 arg1 X INT64 arg2 )
{
  INT64 res;
  low_INT64(res)=low_INT64(arg1)&low_INT64(arg2);
  high_INT64(res)=high_INT64(arg1)&high_INT64(arg2);
  return res;
}

INT64 INT64_not
    PROTO_N ( ( arg ) )
    PROTO_T ( INT64 arg )
{
  INT64 res;
  low_INT64(res) = ~low_INT64(arg);
  high_INT64(res) = ~high_INT64(arg);
  return res;
}


/*******************************************************************/



/*
   The following functions implement left and right shift operations 
   for the INT64 type.
*/

/*******************************************************************/

INT64 INT64_shift_left
    PROTO_N ( ( arg,shift,sgned ) )
    PROTO_T ( INT64 arg X int shift X int sgned )
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



INT64 INT64_shift_right
    PROTO_N ( ( arg,shift,sgned ) )
    PROTO_T ( INT64 arg X int shift X int sgned )
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

/*******************************************************************/
  



/*
   The following functions implement the comparison operations 
   >,>= and = for the INT64 type.
*/

/*******************************************************************/
bool INT64_eq
    PROTO_N ( ( arg1,arg2 ) )
    PROTO_T ( INT64 arg1 X INT64 arg2 )
{
  return (low_INT64(arg1)==low_INT64(arg2))&&
    (high_INT64(arg1)==high_INT64(arg2));
}

bool INT64_leq
    PROTO_N ( ( arg1,arg2 ) )
    PROTO_T ( INT64 arg1 X INT64 arg2 )
{
  /*
     test arg1<arg2
     */
  return ((high_INT64(arg1)<high_INT64(arg2))||
	  ((high_INT64(arg1)==high_INT64(arg2))&&
	   (low_INT64(arg1)<=low_INT64(arg2))));
}

bool INT64_lt
    PROTO_N ( ( arg1,arg2 ) )
    PROTO_T ( INT64 arg1 X INT64 arg2 )
{
  return ((high_INT64(arg1)<high_INT64(arg2))||
	  ((high_INT64(arg1)==high_INT64(arg2))&&
	   (low_INT64(arg1)<low_INT64(arg2))));
}





  
/*
   This function constructs an INT64 variable from two INT32
*/
INT64 make_INT64
    PROTO_N ( ( big,small ) )
    PROTO_T ( INT32 big X UINT32 small )
{
  INT64 res;
  high_INT64(res)=big;
  low_INT64(res)=small;
  return res;
}

#endif /* FS_64_BIT */
