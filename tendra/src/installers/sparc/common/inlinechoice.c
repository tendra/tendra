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
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/inlinechoice.c,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: inlinechoice.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1996/08/15  16:26:59  pwe
 * add missing file headers
 *
--------------------------------------------------------------------------
*/



#include "config.h"
#include "common_types.h"
#include "installglob.h"
#include "exp.h"
#include "expmacs.h"
#include "tags.h"
#include "flags.h"
#include "shapemacs.h"
#include "myassert.h"
#include "sparcins.h"
#include "inl_norm.h"

int crit_inline    = 120;
int crit_decs	   = 6;
int crit_decsatapp = 4;
int show_inlining  = 0;


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
	return ( sbl ( son ( e ),  ( count - 3 ),
		       ( newdecs + 1 ) ) ) ;
      }

      case rep_tag : {
	return ( complexity ( bro ( son ( e ) ),  ( count - 1 ),
			      (newdecs + 1)));
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
      case prof_tag :
      case clear_tag : {
	return ( count ) ;
      }

      case case_tag : {
	return ( complexity ( son ( e ),  ( count - 1 ),
			      newdecs ) ) ;
      }

      case name_tag :
      case string_tag :
      case env_offset_tag : {
	return ( count - 1 ) ;
      }

      case labst_tag : {
	return ( complexity ( bro ( son ( e ) ), count, newdecs ) ) ;
      }

      case cond_tag :
      case solve_tag :
      case seq_tag :
      return ( sbl ( son ( e ), count, newdecs ) ) ;
      
      case val_tag:
      return ( SIMM13_SIZE(no(e)) ? count : (count-1));
	 
      default : {
	return ( sbl ( son ( e ),  ( count - 1 ), newdecs ) ) ;
      }
    }
    /* NOT REACHED */
}

#define MASK 3
#define REJ_ONCE (1)
#define OK_ONCE  (2)
static char *classify[] = { "Impossible","Never","Always","Sometimes"};

int inlinechoice
    PROTO_N ( (t, def, cnt) )
    PROTO_T ( exp t X exp def X int cnt )
	/* delivers 0 if no uses of this proc can be inlined.
	   delivers 1 if this use cannot be inlined
	   delivers 2 if this use can be inlined.
	*/
{
  int res, left;
  
  exp apars;
  exp fpars;
  exp pr_ident;
  
  int newdecs = 0;
  int no_actuals;
  int max_complexity;

  int nparam ;
  CONST unsigned int CONST_BONUS_UNIT = 16 ;
  unsigned int const_param_bonus ;
  unsigned int adjusted_max_complexity ;
    
/*  static exp last_ident = nilexp;
  static int last_inlined_times;*/
  
  nparam = 0 ;
  newdecs = 0 ;
  const_param_bonus = 0 ;
  
  pr_ident = son(t);		/* t is name_tag */
  assert(name(pr_ident) == ident_tag);
  
  max_complexity = ( 300 / cnt) ; /* was no(pr_ident), but that changes */

  {
#define LOG2_ALLOW_EXTRA 2
    int i;
    if (cnt >=(1<<LOG2_ALLOW_EXTRA))
    {
      for (i= cnt >> LOG2_ALLOW_EXTRA ; i>0; i >>=1)
      {
	max_complexity *= 3;
	max_complexity /= 2;
      }
    }
#undef LOG2_ALLOW_EXTRA
  }    
  if ( max_complexity < 15 ) {
    max_complexity = 15 ;
  } else if ( max_complexity > crit_inline) {
    max_complexity = crit_inline ;
  }

  if (show_inlining)
  {
    exp proc_in = t;

    while (name(proc_in) != proc_tag)
    {
      proc_in = father(proc_in);
      assert (proc_in != nilexp);
    }
    proc_in = bro(proc_in);
    assert (name(proc_in) = ident_tag);
         
    fprintf(stderr,"Considering %s in %s\n",
	    brog(pr_ident)->dec_u.dec_val.dec_id,
	    brog(proc_in)->dec_u.dec_val.dec_id);
  }
    
  apars = bro(t);		/* t is name_tag */
  no_actuals = last(t);		/* if so then apars is apply_tag... */  
  fpars = son(def);      	

  for(;;) {
     if (name(fpars)!=ident_tag || !isparam(fpars)) { /* first beyond formals */
       if (!last(t))
	 newdecs = 10; /* more actuals than formals, since last(apars)->break */
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
	
	if ( !SIMM13_SIZE ( n ) ) {
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
  if (show_inlining)
    fprintf(stderr,"%d params %u complexity, %d newdecs -> ",nparam, 
	 adjusted_max_complexity, newdecs);
  
  if ( (left = complexity ( fpars,  adjusted_max_complexity, newdecs )) >= 0 )
    res = 2;
  else if (newdecs == 0)
    res = 0;
  else
    res = 1;

  if (show_inlining)
  {
    switch (res)
    {
     case 2:
      fprintf(stderr,"%d left (%d decs) YES\n",left, last_new_decs);
      (ptno(def)) |= OK_ONCE;
      break;
     case 1:
      if (left == -1)
	fprintf(stderr,"no (count, %d decs)\n", last_new_decs);
      else if (left == -2)
	fprintf(stderr,"no (decs)\n");
      else
	fprintf(stderr,"no (appdecs)\n");
      
      (ptno(def)) |= REJ_ONCE;
      break;
     case 0:
      fprintf(stderr,"NO WAY\n");
    }

    fprintf(stderr,"--%s %s\n",brog(pr_ident)->dec_u.dec_val.dec_id, 
	    classify[(ptno(def) & MASK)]);
  }
  
  return res;
  
}
