/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/error.h>
#include <shared/xalloc.h>

#include <construct/flpttypes.h>
#include <construct/flpt.h>
#include <construct/shape.h>
#include <construct/tags.h>

#include "float.h"
#include "localexpmacs.h"

#define is_negative(x)	(x.sign<0)


/*
  This function takes an exp _e_ corresponding to a real_tag, and
  returns the floating point value referenced, by reading it from 
  the flptnos[] array in the correct format.
*/
#if (FBASE == 10)
char *
floating_value(exp e)
{
  int ref = no(e);
  unsigned char *frac = (flptnos[ref].mant);
  char *result = (char*)xcalloc(128,sizeof(char*));
  int n,j;
  int pos=0;

  /* find end of value */
  for(n=MANT_SIZE-1;(n>1) && (frac[n]==0);n--);
  if( is_negative(flptnos[ref]) )
    result[pos++]='-';
  result[pos++]=frac[0]+'0';
  result[pos++]='.';
  for(j=1;j<=n;++pos,++j)
    result[pos] = frac[j]+'0';
  if(flptnos[ref].exp != 0){
    char *expstr=(char*)xcalloc(20,sizeof(char));
    sprintf(expstr,"E%ld",flptnos[ref].exp);
    strcat(result,expstr);
  }
  return result;
}
#endif



/*
  Return true if the floating point constant produced by the 
  make_floating construct is an IEEE denormal.  Denormals are 
  identified by having a non-zero fraction and a zero exponent.
*/
bool
is_denormal(exp e)
{
  int fraction;
  int exponent;
  int fv = name(sh(e)) - shrealhd;
  bool result;
  r2l ieeeflt = real2longs_IEEE(&flptnos[no(e)],fv);
  assert(name(e) == real_tag);
  switch(name(sh(e))){
  case shrealhd:
    exponent = ieeeflt.i1 & 0x7f800000;
    fraction = ieeeflt.i1 & ~0xff800000;
    break;
  case realhd:
    exponent = ieeeflt.i2 &  0x7ff00000;
    fraction = (ieeeflt.i2 & ~0xfff00000) | ieeeflt.i1;
    break;
  default:
    error(ERR_INTERNAL, "Invalid floating point variety");
    break;
  }
  result = (exponent == 0) && (fraction != 0);
  return result;
}

    
    

