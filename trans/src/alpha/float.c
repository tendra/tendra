/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <tdf/tag.h>

#include <construct/shape.h>

#include <flpt/flpt.h>

#include "float.h"
#include "localexpmacs.h"

#define is_negative(x)	(x.sign<0)



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
  int fv = sh(e)->tag - shrealhd;
  bool result;
  r2l ieeeflt = real2longs_IEEE(&flptnos[no(e)],fv);
  assert(e->tag == real_tag);
  switch (sh(e)->tag){
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

    
    

