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


/*
** float.c
*/

#include "config.h"
#include "common_types.h"
#include "flpttypes.h"
#include "flpt.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "tags.h"
#include "float.h"
#define is_negative(x)	(x.sign<0)


/*
  This function takes an exp _e_ corresponding to a real_tag, and
  returns the floating point value referenced, by reading it from 
  the flptnos[] array in the correct format.
*/
#if (FBASE == 10)
char * floating_value
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
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
bool is_denormal
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
  int fraction;
  int exponent;
  int fv = name(sh(e)) - shrealhd;
  bool result;
  r2l ieeeflt = real2longs_IEEE(&flptnos[no(e)],fv);
  Assert(name(e) == real_tag);
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
    failer("Invalid floating point variety");
    break;
  }
  result = (exponent == 0) && (fraction != 0);
  return result;
}

    
    

