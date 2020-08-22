/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* tempdec.c - is the value in the declaration required over proc calls ?
    if it isn't, declaration can be allocated in t-reg, rather than
    s-reg.

*/

#include <shared/bool.h>
#include <shared/check.h>

#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/exp.h>

#include <main/flags.h>

#include <refactor/const.h>

#include "procrec.h"
#include "bits.h"
#include "muldvrem.h"
#include "tempdecs.h"


/*
    IS THE EXPRESSION e A PROCEDURE APPLICATION?
*/

#define APPLYLIKE( e ) ( e->tag==apply_tag || e->tag==apply_general_tag ||\
			 e->tag==tail_call_tag || is_muldivrem_call(e) )


/*
    VARIABLES SET BY TRACE_USES
*/

static int nouses ;
static bool useinpar ;


/*
    Reduces nouses for each non-assignment use of id encountered in e,
    sets useinpar if use in actual parameter (or function) position,
    terminates with 0 on applications or jumps, terminates with 2 on
    assignment to id, otherwise delivers 1.
*/

static int
trace_uses(exp e, exp id)
{
    if ( APPLYLIKE ( e ) ) {
	int u = nouses ;
	int p = 1 ;
	exp l = son ( e ) ;

	while ( p == 1 ) {
	    p = trace_uses ( l, id ) ;
	    if ( u != nouses || p == 2 ) useinpar = 1 ;
	    if ( p == 0 ) nouses = u ;
	    if ( ( l ) -> last ) break ;
	    l = next ( l ) ;
	}
	return 0;
    }

    switch ( e->tag ) {

	case env_offset_tag:
	case name_tag : {
	    nouses -= ( son ( e ) == id ? 1 : 0 ) ;
	    return 1;
	}

	case ident_tag : {
	    exp f = son ( e ) ;
	    exp s = next ( f ) ;
	    int a ;

	    if ( ( props ( e ) & defer_bit ) != 0 ) {
		exp t = f ;
		f = s ;
		s = t ;
	    }
	    a = trace_uses ( f, id ) ;
	    if ( a != 1 ) return a;
	    return trace_uses ( s, id ) ;
	}

	case case_tag : {
	    trace_uses ( son ( e ), id ) ;
	    return 0;
	}

	case labst_tag : {
	    return 0;
	}

	case seq_tag : {
	    exp s = son ( son ( e ) ) ;
	    for ( ; ; ) {
		int el = trace_uses ( s, id ) ;
		if ( el != 1 ) return el;
		if ( ( s ) -> last ) {
		    return trace_uses ( next ( son ( e ) ), id ) ;
		}
		s = next ( s ) ;
	    }
        UNREACHED;
	    break ;
	}

	case test_tag: case goto_lv_tag:{
		int nu = nouses;
		if (trace_uses(son(e),id) != 1 || 
				trace_uses(next(son(e)), id) !=1 ){
			nouses = nu;
		}
		return 0;
	}

	case ass_tag : {
	    if ( isvar ( id ) && son ( e ) -> tag == name_tag &&
		 son ( son ( e ) ) == id ) {
		trace_uses ( next ( son ( e ) ), id ) ;
		return 2;
	    } else if ( APPLYLIKE ( next ( son ( e ) ) ) ) {
		return trace_uses ( next ( son ( e ) ), id ) ;
	    }

		FALL_THROUGH;
	}

	default : {
	    exp s = son ( e ) ;
	    int nu = nouses ;	 /* s list can be done in any order ... */

	    if ( s == NULL ) return 1;
	    for ( ; ; ) {
		int el = trace_uses ( s, id ) ;

		if ( el != 1 ) {
		    /* ... so reset nouses if any terminate */
		    nouses = nu ;
		    return el ;
		}
		if ( ( s ) -> last ) return 1;
		s = next ( s ) ;
	    }
        UNREACHED;
	    break ;
	}
    }
    UNREACHED;
    return 0;
}


/*
    APPLY TRACE_USES TO DYNAMIC SUCCESSORS OF a
*/

static void
after_a(exp a, exp id)
{
    char n ;
    exp dad ;
    exp l ;

    tailrec : {
	dad = father ( a ) ;
	n = dad->tag ;
	if ( nouses == 0 ) return ;
	if ( n == cond_tag || n == rep_tag || n == solve_tag ||
	     n == labst_tag || n == case_tag || n == goto_tag ||
	     n == test_tag || n == goto_lv_tag || APPLYLIKE ( dad ) ) {
	    /* Don't try too hard! */
	    while ( APPLYLIKE ( dad ) && dad != id ) dad = father ( dad ) ;
	    if ( APPLYLIKE ( dad ) ) {
		useinpar = 1 ;
	    }
	    return ;
	}

	for ( l = a ; ! l -> last ; l = next ( l ) )
	{
	    int u = trace_uses ( next ( l ), id ) ;
	    if ( u != 1 || nouses == 0 ) return ;
	}
	a = dad ;
    }
    if ( dad != id ) goto tailrec ;
}


static bool
simple_seq(exp e, exp id)
{
    exp dad = father ( e ) ;
    for ( ; ; ) {
	if ( dad == id ) return 1;
	if ( dad->tag == seq_tag || dad->tag == 0 ||
	     dad->tag == ident_tag ) {
	    dad = father ( dad ) ;
	} else {
	    return 0;
	}
    }
    UNREACHED;
}


bool
tempdec(exp e, bool enoughs)
{
    /*
 * e is a local declaration ; 'enoughs' is a misnomer to say whether there
 * are t-regs available delivers 1 if e can be allocated into t-reg or par
 * reg
 */
    exp p ;
    if ( ~optim & OPTIM_TEMPDEC ) return 0;

    nouses = 0 ;
    useinpar = 0 ;

    if ( isvar ( e ) ) {
	for ( p = pt ( e ) ; p != NULL ; p = pt ( p ) ) {
	    /* find no of uses which are not assignments to id ... */
	    if ( !  p -> last && next ( p ) -> last &&
		 next ( next ( p ) ) -> tag == ass_tag ) {
		if ( !simple_seq ( next ( next ( p ) ), e ) ) return  ( 0 ) ;
		/* ... in simple sequence */
		continue ;
	    }
	    nouses++ ;
	}
    } else {
	nouses = no ( e ) ;
    }

    /*
 * trace simple successors to assignmnts or init to id to find if all uses
 * occur before unpredictable change of control ( or another assignment to
 * id )
 */

    if ( son ( e ) -> tag != clear_tag || isparam ( e ) ) {
	after_a ( son ( e ), e ) ;
    }

    if ( isvar ( e ) ) {
	for ( p = pt ( e ) ; p != NULL ; p = pt ( p ) ) {
	    if ( ! p -> last && next ( p ) -> last &&
		 next ( next ( p ) ) -> tag == ass_tag ) {
		after_a ( next ( next ( p ) ), e ) ;
	    }
	}
    }

    if ( nouses == 0 && ( enoughs || !useinpar ) ) {
#if 0
	/* +++ temp circumvention, we need to calculate t-reg reqt better when
     some not allowed by props ( e ) |= notparreg */
	if ( useinpar ) return 0;
#else
	if ( useinpar ) props ( e ) |= notparreg ;     /* don't allocate this into par reg */
#endif
	return 1;
    }
    return 0;
}








