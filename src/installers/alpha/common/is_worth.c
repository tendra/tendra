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


/* 	$Id: is_worth.c,v 1.1.1.1 1998/01/17 15:56:00 release Exp $	 */

#ifndef lint
static char vcid[] = "$Id: is_worth.c,v 1.1.1.1 1998/01/17 15:56:00 release Exp $";
#endif /* lint */

#include "config.h"
#include "common_types.h"
#include "tags.h"
#include "expmacs.h"
#include "exp.h"
#include "shapemacs.h"
#include "coder.h"
#include "is_worth.h"

#define true 1
#define false 0

int is_worth
    PROTO_N ( ( c ) )
    PROTO_T ( exp c )
{
  /* decide if constant c is worth declaring
     separately */
  unsigned char cnam = name (c);
  bool isflt = is_floating(name(sh(c)));
  
  if (name (sh (c)) == ptrhd && al1(sh(c))==1 )
    return 0;			/* ptr bits */
  if (cnam == real_tag) return true;
  if (cnam==cont_tag&&isflt&&(name(son(c))!=name_tag||isglob(son(son(c))))){
    return true;
  }
  if (cnam==cont_tag && name (son(c))==name_tag && isglob(son(son (c)))) { 
    return true;      
  }
  if (cnam == val_tag) {	/* it is sometimes worthwhile extracting
				   big constants from loops ... */
    int  n = no (c);
    exp dad;
    if (n == 0) {
      return false;
    }
    dad = father (c);
    if(dad == nilexp) return 0;	/* bug ? */
    switch (name (dad)) {
    case and_tag: {
      exp grandad = father (dad);
      if ((name (grandad) == test_tag && (n & (n - 1)) == 0 &&
	  (props (grandad) == 5 || props (grandad) == 6) &&
	  (name (bro (son (grandad))) == val_tag 
	   && no (bro (son (grandad))) == 0))|| ((name (son (grandad)) == 
					  val_tag && no (son (grandad)) == 0))){
	  /*  a & 2^n == 0 is transformed later to
	      shift and test negative */
	return 0;
      }
      /* else next case */
    }
    FALL_THROUGH
    case or_tag: 
    case xor_tag: 
    case test_tag:
      return (n < 0 || n >= 0xffff  ); /* short literal operands */
      
    case mult_tag: case offset_mult_tag: 
    {
      if (n <= 0x7fff && n > -0x8000)
	return 0;		/* short literal operands */
      /*a*2^n and a*2^(n+-1) are transformed later to shifts and adds
       */
      return ((n&(n-1))!=0 && (n&(n+1)) != 0 && ((n-1)&(n-2))!=0);
	}
    case div1_tag: 
    case div2_tag: 
    case rem2_tag: 
    {
      if (n <= 0x7fff && n > -0x8000)
	return 0 /* short literal operands */ ;
      /* a/2^n transformed later to shift */  
      return ((n & (n - 1)) != 0);
    }
    default: 
    {
      return (n > 0x7fff || n < -0x8000) /* short literal operands */ ;
    }
    }				/* end sw */
  }      
  return ((!is_o (cnam) && cnam != clear_tag) ||
	  /* ignore simple things unless ... */
	  (cnam == cont_tag && name (son (c)) == cont_tag &&
	   name (son (son (c))) == name_tag)
	  );
}
