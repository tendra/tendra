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
$Log: inlinechoice.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:11:37  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  09:39:31  wfs
 * A 4.0 "general_env_offset_tag" case added.
 *
 * Revision 3.4  1995/08/25  09:39:31  wfs
 * A 4.0 "general_env_offset_tag" case added.
 *
 * Revision 3.1  95/04/10  16:26:51  16:26:51  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:17:28  11:17:28  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:27:35  15:27:35  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:09:12  13:09:12  wfs (William Simmonds)
 * Initial revision
 * 
*/


#include "config.h"
#include "common_types.h"
#include "installglob.h"
#include "exp.h"
#include "expmacs.h"
#include "tags.h"
#include "flags.h"
#include "shapemacs.h"
#include "inl_norm.h"

#define crit_inline	300
#define crit_decs	5
#define crit_decsatapp	5
#define apply_cost      3

static int  complexity PROTO_S ((exp e, int count, int newdecs));
static last_new_decs = -999;

/*
    APPLY COMPLEXITY TO A LIST OF EXPRESSIONS
*/

int sbl 
    PROTO_N ( ( e, count, newdecs ) )
    PROTO_T ( exp e X int count X int newdecs )
{
    int c = complexity ( e, count, newdecs ) ;
    if ( c < 0 ) return ( c ) ;
    if ( last ( e ) ) return ( c ) ;
    return ( sbl ( bro ( e ), c, newdecs ) ) ;
}


/*
    FIND THE COMPLEXITY OF AN EXPRESSION

    This routine examines the structure of e to see if its complexity
    (roughly the number of nodes) is greater than count.  As soon as the
    complexity exceeds this value it stops.  It returns the difference
    between count and the calculated complexity.
*/

static int complexity 
    PROTO_N ( ( e, count, newdecs ) )
    PROTO_T ( exp e X int count X int newdecs )
{
    unsigned char n = name ( e ) ;
    
    last_new_decs = newdecs;
    
    if ( count < 0 )
      return ( -1 ) ;
    if (newdecs > crit_decs )
      return ( -2);
    if ( son ( e ) == nilexp ) 
      return ( count ) ;

    switch ( n ) {

	case apply_tag : {
	    if ( newdecs > crit_decsatapp ) 
	      return ( -3 ) ;
	    return ( sbl ( son ( e ),  ( count - apply_cost ),
			  ( newdecs + 1 ) ) ) ;
	}

	case rep_tag : {
	    return ( complexity ( bro ( son ( e ) ),  ( count - 1 ),
		      (newdecs + 1)
				 ));
	}

	case res_tag : {
	    return ( complexity ( son ( e ),  ( count + 1 ),
				  newdecs ) ) ;
	}

	case ident_tag : {
	    return ( sbl ( son ( e ),  ( count - 1 ),
			    ( newdecs + 1 ) ) ) ;
	}

	case top_tag :
	case clear_tag :
	case val_tag : {
	    return ( count ) ;
	}

	case case_tag : {
	    return ( complexity ( son ( e ),  ( count - 1 ),
				  newdecs ) ) ;
	}

	case name_tag :
	case string_tag :
	case env_offset_tag :
	case general_env_offset_tag:
	{
	    return ( count - 1 ) ;
	}

	case labst_tag : {
	    return ( complexity ( bro ( son ( e ) ), count, newdecs ) ) ;
	}

	case solve_tag :
	case seq_tag :
	case cond_tag : {
	    return ( sbl ( son ( e ), count, newdecs ) ) ;
	}

	default : {
	    return ( sbl ( son ( e ),  ( count - 1 ), newdecs ) ) ;
	}
    }
    /* NOT REACHED */
}

#define MASK 3
#define REJ_ONCE (1)
#define OK_ONCE  (2)
	

int inlinechoice
    PROTO_N ( ( t, def, total_uses ) )
    PROTO_T ( exp t X exp def X int total_uses )
	/* delivers 0 if no uses of this proc can be inlined.
	   delivers 1 if this use cannot be inlined
	   delivers 2 if this use can be inlined.
	*/
{
  int res;
  
  exp apars;
  exp fpars;
  
  int newdecs = 0;

  int max_complexity;

  int nparam ;
  CONST unsigned int CONST_BONUS_UNIT = 16 ;
  int const_param_bonus ;
  int adjusted_max_complexity ;

#if 1
  shape shdef = pt(def);
  if (!eq_shape(sh(father(t)), shdef) ) 
  {
    /* shape required by application is different from definition */
    return 1;
  }
#endif
    
  nparam = 0 ;
  const_param_bonus = 0 ;
  

  max_complexity = ( crit_inline / total_uses ) ;



#if ishppa  
  {
#define QQQ 2
    int i;
    if (total_uses >=(1<<QQQ))
    {
      for (i= total_uses >> QQQ ; i>0; i >>=1)
      {
	max_complexity *= 3;
	max_complexity /= 2;
      }
    }
#undef QQQ
  }
#endif
   
  if ( max_complexity < 15 ) {
    max_complexity = 15 ;
  } else if ( max_complexity > 120 ) {
    max_complexity = 120 ;
  }

  apars = bro(t); /* only uses are applications */
  fpars = son(def);      	

  for(;;) {
     if (name(fpars)!=ident_tag || !isparam(fpars)) {
       if (name(apars) != top_tag) newdecs = 10;
      	 break;
     }
     nparam++ ;

     switch (name(apars)) {
      case val_tag: case real_tag: case string_tag: case name_tag: 
      	   break;
      case cont_tag: {
      	   if (name(son(apars))==name_tag && isvar(son(son(apars))) &&
      	        		!isvar(fpars) ) break;
      	   } /* ... else continue */
      default: newdecs++;
     }
     switch ( name ( apars ) ) 
     {
      case val_tag : {
	int n = no ( apars ) ;
	
	/* Simple constant param. Increase desire to
	   inline since a constant may cause further
	   optimisation, eg strength reduction (mul
	   to shift) or dead code savings */

#define IS_POW2( c )	( ( c ) != 0 && ( ( c ) & ( ( c ) - 1 ) ) == 0 )
	
	if ( 0 ) {
	  /* needs a register - poor */
	  const_param_bonus += CONST_BONUS_UNIT / 4 ;
	} else if ( n == 0 || ( n > 0 && IS_POW2 ( n ) ) ) {
	  /* very good */
	  const_param_bonus += CONST_BONUS_UNIT ;
	} else {
	  /* less good */
	  const_param_bonus += CONST_BONUS_UNIT / 2 ;
	}
	break ;
      }

#undef IS_POW2
       
      case real_tag : 
	/* reals not that useful */
	const_param_bonus += CONST_BONUS_UNIT / 4 ;
	break ;
       
      case string_tag :
       case name_tag : 
	 break ;

      case cont_tag : 
	if ( name ( son ( apars ) ) == name_tag &&
	    isvar ( son ( son ( apars ) ) ) &&
	    !isvar ( fpars ) ) {
	  break ;
	}
	/* FALL THROUGH */
       
      default : {
	newdecs++ ;
	break ;
      }
     }
     fpars = bro(son(fpars));
     if (last(apars)) break;
     apars = bro(apars);
   }

  adjusted_max_complexity = max_complexity ;
  
  /* increase to up to 3 times (average around 2) according
     to const params */
  if ( nparam != 0 ) {
    adjusted_max_complexity += 
      ( 2 * max_complexity * const_param_bonus ) /
	( CONST_BONUS_UNIT * nparam ) ;
  }
    
  /* increase by number of instructions saved for call */
    adjusted_max_complexity += nparam - newdecs + 1 ;
  
  if ( (complexity ( fpars,  adjusted_max_complexity, newdecs )) >= 0 )
    res = 2;
  else if (newdecs == 0)
    res = 0;
  else
    res = 1;


  switch (res)
  {
   case 2:
    (ptno(def)) |= OK_ONCE;
    break;
   case 1:

    (ptno(def)) |= REJ_ONCE;
    break;
   case 0:
    ;
  }

  return res;
  
}

