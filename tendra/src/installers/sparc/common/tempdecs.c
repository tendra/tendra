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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/tempdecs.c,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: tempdecs.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1997/02/18  11:48:33  pwe
 * NEWDIAGS for debugging optimised code
 *
 * Revision 1.4  1995/10/27  10:52:20  john
 * Fix to general procs
 *
 * Revision 1.3  1995/09/29  09:23:20  john
 * Fixed APPLYLIKE
 *
 * Revision 1.2  1995/05/26  13:02:10  john
 * Reformatting
 *
 * Revision 1.1.1.1  1995/03/13  10:18:59  john
 * Entered into CVS
 *
 * Revision 1.3  1994/12/01  13:24:05  djch
 * Break id scan on env_offset_tag as well as name_tag
 * Add goto_lv and long_jump to set of transfer operations
 *
 * Revision 1.2  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.1  1994/05/03  14:50:00  djch
 * Initial revision
 *
 * Revision 1.4  93/08/27  11:39:39  11:39:39  ra (Robert Andrews)
 * A couple of lint-like changes.  Use of pset etc to set properties.
 * 
 * Revision 1.3  93/08/13  14:48:00  14:48:00  ra (Robert Andrews)
 * Reformatted.
 * 
 * Revision 1.2  93/06/29  14:36:10  14:36:10  ra (Robert Andrews)
 * Have to include muldvrem.h.
 * 
 * Revision 1.1  93/06/24  14:59:33  14:59:33  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE
#include "config.h"
#include "tags.h"
#include "common_types.h"
#include "exp.h"
#include "const.h"
#include "expmacs.h"
#include "bitsmacs.h"
#include "muldvrem.h"
#include "tempdecs.h"


/*
  IS THE EXPRESSION e A PROCEDURE APPLICATION?
*/

#define APPLYLIKE( e ) ( name ( e ) == apply_tag || \
			 name ( e ) == apply_general_tag || \
			 is_muldivrem_call ( e ) )


/*
  FLAG : APPLY TEMPDEF OPTIMISATION?
*/

bool tempdecopt ;


/*
  VARIABLES SET BY TRACE_USES
*/	

static int nouses ;
static bool useinpar ;


/*
  TRACE USES OF AN IDENTITY
  Reduces nouses for each non-assignment use of id encountered in e,
  sets useinpar if use in actual parameter (or function) position,
  terminates with 0 on applications or jumps, terminates with 2 on
  assignment to id, otherwise delivers 1.
*/

int trace_uses 
    PROTO_N ( ( e, id ) )
    PROTO_T ( exp e X exp id ){
  if ( APPLYLIKE ( e ) ) {
    int u = nouses ;
    int p = 1 ;
    exp l = son ( e ) ;
    while ( p == 1 ) {
      p = trace_uses ( l, id ) ;
      if ( u != nouses || p == 2 ) useinpar = 1 ;
      if ( p == 0 ) nouses = u ;
      if ( last ( l ) ) break ;
      l = bro ( l ) ;
    }
    return ( 0 ) ;
  }
  switch ( name ( e ) ) {
  case env_offset_tag :
  case name_tag : {
    nouses -= ( son ( e ) == id ? 1 : 0 ) ;
    return ( 1 ) ;
  }
  case ident_tag : {
    exp f = son ( e ) ;
    exp s = bro ( f ) ;
    int a ;
    if ( ( props ( e ) & defer_bit ) != 0 ) {
      exp t = f ;
      f = s ;
      s = t ;
    }
    a = trace_uses ( f, id ) ;
    if ( a != 1 ) return ( a ) ;
    return ( trace_uses ( s, id ) ) ;
  }
  case case_tag : {
    ( void ) trace_uses ( son ( e ), id ) ;
    return ( 0 ) ;
  }
  case current_env_tag :
  case labst_tag : {
    return ( 0 ) ;
  }
  case seq_tag : {
    exp s = son ( son ( e ) ) ;
    for ( ; ; ) {
      int el = trace_uses ( s, id ) ;
      if ( el != 1 ) return ( el ) ;
      if ( last ( s ) ) {
	return ( trace_uses ( bro ( son ( e ) ), id ) ) ;
      }
      s = bro ( s ) ;
    }
    /* NOT REACHED */
  }
  case ass_tag : {
    if ( isvar ( id ) && name ( son ( e ) ) == name_tag &&
	 son ( son ( e ) ) == id ) {
      ( void ) trace_uses ( bro ( son ( e ) ), id ) ;
      return ( 2 ) ;
    } else if ( APPLYLIKE ( bro ( son ( e ) ) ) ) {
      return ( trace_uses ( bro ( son ( e ) ), id ) ) ;
    }
    /* FALL THROUGH */
  }
  default : {
    exp s = son ( e ) ;
    int nu = nouses ;	 /* s list can be done in any order ... */
    if ( s == nilexp ) return ( 1 ) ;
    for ( ; ; ) {
      int el = trace_uses ( s, id ) ;
      if ( el != 1 ) {
	/* ... so reset nouses if any terminate */
	nouses = nu ;
	return el ;
      }
      if ( last ( s ) ) return ( 1 ) ;
      s = bro ( s ) ;
    }
    /* NOT REACHED */
  }
  }
    /* NOT REACHED */
}


/*
  APPLY TRACE_USES TO DYNAMIC SUCCESSORS OF a
*/

void after_a 
    PROTO_N ( ( a, id ) )
    PROTO_T ( exp a X exp id ){
  unsigned char n ;
  exp dad ;
  exp l ;
  tailrec : {
    dad = father ( a ) ;
    n = name ( dad ) ;
    if ( nouses == 0 ) return ;
    if ( n == cond_tag || n == rep_tag || n == solve_tag ||
	 n == labst_tag || n == case_tag || n == goto_tag ||
	 n == goto_lv_tag || n == long_jump_tag || /* new ones */
	 n == test_tag || APPLYLIKE ( dad ) ) {
      /* Don't try too hard! */
      while ( APPLYLIKE ( dad ) && dad != id ) dad = father ( dad ) ;
      if ( APPLYLIKE ( dad ) ) {
	useinpar = 1 ;
      }
      return ;
    }
    for ( l = a ; !last ( l ) ; l = bro ( l ) ){
      int u = trace_uses ( bro ( l ), id ) ;
      if ( u != 1 || nouses == 0 ) return ;
    }
    a = dad ;
  }
  if ( dad != id ) goto tailrec ;
  return ;
}	


/*
  CHECK SIMPLE SEQUENCES
*/

bool simple_seq 
    PROTO_N ( ( e, id ) )
    PROTO_T ( exp e X exp id ){
  exp dad = father ( e ) ;
  for ( ; ; ) {
    if ( dad == id ) return ( 1 ) ;
    if ( name ( dad ) == seq_tag || name ( dad ) == 0 ||
	 name ( dad ) == ident_tag ) {
      dad = father ( dad ) ;
    } 
    else {
      return ( 0 ) ;
    }
  }
    /* NOT REACHED */
}


/*
  CAN e BE ALLOCATED INTO A T-REGISTER?
  e contains a local declaration.  enoughs is true to indicate that
  there are t-registers available.  The routine delivers 1 if e can
  be allocated into a t-register or parameter register.
*/

bool tempdec 
    PROTO_N ( ( e, enoughs ) )
    PROTO_T ( exp e X bool enoughs ){
  exp p ;
  if ( !tempdecopt ) return ( 0 ) ;
  nouses = 0 ;
  useinpar = 0 ;
  if ( isvar ( e ) ) {
    for ( p = pt ( e ) ; p != nilexp ; p = pt ( p ) ) {
      /* find no of uses which are not assignments to id ... */
#ifdef NEWDIAGS
      if (isdiaginfo(p))
	continue ;
#endif
      if ( !last ( p ) && last ( bro ( p ) ) &&
	   name ( bro ( bro ( p ) ) ) == ass_tag ) {
	if ( !simple_seq ( bro ( bro ( p ) ), e ) ) return  ( 0 ) ;
	/* ... in simple sequence */
	continue ;
      }
      nouses++ ;
    }
  } 
  else {
    nouses = no ( e ) ;
  }
  /* trace simple successors to assignmnets or initialisations to 
     id to find if all uses occur before unpredictable change of 
     control (or another assignment to id ) */
  
  if ( name ( son ( e ) ) != clear_tag || isparam ( e ) ) {
    after_a ( son ( e ), e ) ;
  }
  if ( isvar ( e ) ) {
    for ( p = pt ( e ) ; p != nilexp ; p = pt ( p ) ) {
#ifdef NEWDIAGS
      if (isdiaginfo(p))
	continue ;
#endif
      if ( !last ( p ) && last ( bro ( p ) ) &&
	   name ( bro ( bro ( p ) ) ) == ass_tag ) {
	after_a ( bro ( bro ( p ) ), e ) ;
      }
    }
  }
  if ( nouses == 0 && ( enoughs || !useinpar ) ) {
#if 0
    /* temporary circumvention */
    if ( useinpar ) return ( 0 ) ;
#else
    /* don't allocate this into a parameter register */
    if ( useinpar ){
      return 0;
      pset ( e, notparreg ) ;
    }
#endif
    return ( 1 ) ;
  }
  return ( 0 ) ;
}






