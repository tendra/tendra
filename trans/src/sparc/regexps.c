/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <reader/exp.h>

#include <shared/check.h>
#include <shared/error.h>

#ifdef DWARF2
#include <local/dw2_config.h>
#endif

#include <construct/aldefs.h>
#include <construct/tags.h>
#include <construct/shape.h>

#include <main/flags.h>

#include "addrtypes.h"
#include "move.h"
#include "bitsmacs.h"
#include "maxminmacs.h"
#include "regmacs.h"
#include "regexps.h"

#ifdef DWARF2
#include "dw2_extra.h"
#include <dwarf2/dw2_iface.h>
#endif

static bool 
couldaffect ( exp e, exp z );

/*
    0-31 represent the fixed point registers, 32-47 the floating point
    registers.
*/

regpeep regexps [48] ;


/*
    ARE TWO SHAPES OF THE SAME SIZE, ALIGNMENT AND FLOATING-POINT-NESS?
*/

static bool 
eq_sze ( shape as, shape bs )
{
    if ( is_floating ( name ( as ) ) ) {
	return ( bool ) ( name ( as ) == name ( bs ) ) ;
    }
    if ( is_floating ( name ( bs ) ) ) {
	return 0;
    }
    return ( bool ) ( shape_size ( as ) == shape_size ( bs ) &&
			shape_align ( as ) == shape_align ( bs ) ) ;
}


/*
    ARE TWO LISTS OF EXPRESSIONS SIMILAR?
*/

static bool 
sim_explist ( exp al, exp bl )
{
    if ( al == NULL && bl == NULL ) return 1;
    if ( al == NULL || bl == NULL ) return 0;
    if ( !sim_exp ( al, bl ) ) return 0;
    if ( last ( al ) && last ( bl ) ) return 1;
    if ( last ( al ) || last ( bl ) ) return 0;
    return sim_explist ( bro ( al ), bro ( bl ) ) ;
}


/*
    Basically this is the same as eq_exp except that equal shapes requirement
    is weakened to equal size and alignment.
*/

bool 
sim_exp ( exp a, exp b )
{
    if ( name ( a ) == name ( b ) ) {
	if ( name ( a ) == name_tag ) {
	    return ( bool ) ( son ( a ) == son ( b ) &&
				no ( a ) == no ( b ) &&
				eq_sze ( sh ( a ), sh ( b ) ) ) ;
	}
	if ( !is_a ( name ( a ) ) || !eq_sze ( sh ( a ), sh ( b ) ) ) {
	    return 0;
	}
	return ( bool ) ( no ( a ) == no ( b ) &&
			    sim_explist ( son ( a ), son ( b ) ) 
			    && ((name(a) != current_env_tag) || 
				(props(a) == props(b))));
    }
    return 0;
}


/*
    FORGET ALL REGISTER-EXP ASSOCIATIONS
*/

void 
clear_all (void) {
    int i ;
    for ( i = 0 ; i < 48 ; i++ ) {
	regexps [i].keptexp = NULL ;
	setregalt ( regexps [i].inans, 0 ) ;
#ifdef DWARF2
	if (diag == DIAG_DWARF2)
	  dw_close_regassn (i);
#endif
    }
}


/*
    FORGET THE EXP ASSOCIATED WITH REGISTER i
*/

void 
clear_reg ( int i )
{
    i = ABS_OF ( i ) ;
    if ( i >= 0 && i < 48 ) {
	regexps [i].keptexp = NULL ;
	setregalt ( regexps [i].inans, 0 ) ;
#ifdef DWARF2
	if (diag == DIAG_DWARF2)
	  dw_close_regassn (i);
#endif
    }
}


/*
    HAS AN EXPRESSION ALREADY BEEN EVALUATED INTO A REGISTER?
*/

ans 
iskept ( exp e )
{
    int i ;
    ans nilans ;
    setregalt ( nilans, 0 ) ;

#ifdef NO_KEPT_OPTS
    /* no register tracking */
    return nilans;
#endif

    if ( name ( sh ( e ) ) == cpdhd ) {
	/* Tracking of unions is unsafe */
	return nilans;
    }

    for ( i = 0 ; i < 48 ; i++ ) {
	exp ke = regexps [i].keptexp ;
	bool isc = regexps [i].iscont ;

	if ( ke != NULL ) {
	    /* there is an association with register i? */
	    if ( ( ( !isc && sim_exp ( ke, e ) ) ||
		 ( name ( e ) == cont_tag && isc &&
		   eq_sze ( sh ( ke ), sh ( e ) ) &&
		   sim_exp ( ke, son ( e ) )  && 
		   al1(sh(son(e))) == al1(sh(ke))  ) ) ) {
		ans aa ;
		aa = regexps [i].inans ;

		switch ( discrim ( aa ) ) {

		    case notinreg : {
			if ( !aa.val.instoreans.adval ) {
			    /* the expression is given indirectly, it may
			       also be in another register */
			    continue ;
			}
			/* FALL THROUGH */
		    }

		    default : {
#ifdef DWARF2
			if (diag == DIAG_DWARF2)
			  dw_used_regassn (i);
#endif
			return aa;
		    }
		}
	    } else if ( name ( ke ) == cont_tag && !isc ) {
		ans aq ;

		aq = regexps [i].inans ;
		if ( discrim ( aq ) == notinreg ) {
		    instore is ;
		    is = insalt ( aq ) ;
		    if ( !is.adval && is.b.offset == 0 &&
			 IS_FIXREG ( is.b.base ) &&
			 sim_exp ( son ( ke ), e ) ) {
			/* the contents of required expression is here as
			   a register-offset */
#ifdef DWARF2
			if (diag == DIAG_DWARF2)
			  dw_used_regassn (i);
#endif
			is.adval = 1 ;
			setinsalt ( aq, is ) ;
			return aq;
		    }
		}
	    } else if ( name ( ke ) == reff_tag && !isc ) {
		ans aq ;
		aq = regexps [i].inans ;
		if ( discrim ( aq ) == notinreg ) {
		    instore is ;
		    is = insalt ( aq ) ;
		    if ( is.adval && is.b.offset == ( no ( ke ) / 8 ) &&
			 IS_FIXREG ( is.b.base ) &&
			 sim_exp ( son ( ke ), e ) ) {
			/* a ref selection of required expression is here as
			   a register-offset */
#ifdef DWARF2
			if (diag == DIAG_DWARF2)
			  dw_used_regassn (i);
#endif
			is.adval = 1 ;
			is.b.offset = 0 ;
			setinsalt ( aq, is ) ;
			return aq;
		    }
		}
	    }
	}
    }
    return nilans;
}


/*
    SET UP AN EXP-LOCATION ASSOCIATION
*/

void 
keepexp ( exp e, ans loc )
{
    int reg ;

    /* Find the register number */
    switch ( discrim ( loc ) ) {
	case insomereg:
	case insomefreg:
	    error(ERR_SERIOUS,  "Illegal location in keepexp" ) ;
	    return ;
	case inreg:
	    reg = regalt ( loc ) ;
	    break ;
	case infreg:
	    reg = fregalt ( loc ).fr + 32 ;
	    break ;
	case notinreg:
	    reg = insalt ( loc ).b.base ;
	    if ( !IS_FIXREG ( reg ) ) return ;
	    break ;
    }

    assert ( reg >= 0 && reg < 48 ) ;
    assert ( reg != R_TMP ) ;
    regexps [ reg ].keptexp = e ;
    regexps [ reg ].inans = loc ;
    regexps [ reg ].iscont = 0 ;
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
	dw_init_regassn (reg);
#endif
}


/*
    SET UP A CONTENTS-REGISTER ASSOCIATION
*/

void 
keepcont ( exp e, int regcode )
{
    freg fr ;
    int reg = ABS_OF ( regcode ) ;
    assert ( reg >= 0 && reg < 48 ) ;
    assert ( reg != R_TMP ) ;

    if ( reg > 31 ) {
	fr.dble = ( bool ) ( regcode < 0 ) ;
	fr.fr = reg - 32 ;
	setfregalt ( regexps [ reg ].inans, fr ) ;
    } else {
	instore is ;
	is.b.base = regcode ;
	is.b.offset = 0 ;
	is.adval = 1 ;
	setinsalt ( regexps [ reg ].inans, is ) ;
    }

    regexps [ reg ].keptexp = e ;
    regexps [ reg ].iscont = 1 ;
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
	dw_init_regassn (reg);
#endif
}


/*
    SET UP AN EXP-REGISTER ASSOCIATION
*/

void 
keepreg ( exp e, int regcode )
{
    freg fr ;
    int reg = ABS_OF ( regcode ) ;
    assert ( reg >= 0 && reg < 48 ) ;
    assert ( reg != R_TMP ) ;

    if ( reg > 31 ) {
	fr.dble = ( bool ) ( regcode < 0 ) ;
	fr.fr = reg - 32 ;
	setfregalt ( regexps [ reg ].inans, fr ) ;
    } else {
	instore is ;
	is.b.base = regcode ;
	is.b.offset = 0 ;
	is.adval = 1 ;
	setinsalt ( regexps [ reg ].inans, is ) ;
    }

    regexps [ reg ].keptexp = e ;
    regexps [ reg ].iscont = 0 ;
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
	dw_init_regassn (reg);
#endif
}


/* COULD e BE lhs?  */
static bool 
couldbe ( exp e, exp lhs )
{
    unsigned char ne = name ( e ) ;
    exp s = son ( e ) ;

    if ( ne == name_tag ) {
	if ( lhs != 0 && s == son ( lhs ) ) return 1;
	if ( isvar ( s ) ) 
	  return ( bool ) ( lhs == 0 && 
			     (isvis ( s ) || isglob(s)));
	if ( name ( s ) == proc_tag ) return ( bool ) ( lhs == 0 ) ;
	if ( son ( s ) == NULL ) return 1;
	return couldbe ( son ( s ), lhs ) ;
    }
    if ( ne == cont_tag ) {
	if ( lhs != 0 && name ( s ) == name_tag && son ( s ) != NULL ) {
	    return ( bool ) ( son ( s ) == son ( lhs ) ||
				isvis ( son ( lhs ) ) ||
				isvis ( son ( s ) ) ) ;
	}
	return 1;
    }
    if ( ne == reff_tag || ne == field_tag ) {
	return couldbe ( s, lhs ) ;
    }
    if ( ne == addptr_tag || ne == subptr_tag ) {
	return ( bool ) ( couldbe ( s, lhs ) ||
			    couldaffect ( bro ( s ), lhs ) ) ;
    }
    return 1;

}

/*
    COULD AN ALTERATION TO z AFFECT e?
*/

static bool 
couldaffect ( exp e, exp z )
{
    unsigned char ne = name ( e ) ;

    if ( ne == cont_tag ) return couldbe ( son ( e ), z ) ;
    if ( ne == name_tag ) {
	if ( isvar ( son ( e ) ) ) {
	    return ( bool ) ( z == 0 && isvis ( son ( e ) ) ) ;
	}
	if ( name ( son ( e ) ) == proc_tag ) return 0;
	if ( son ( son ( e ) ) == NULL ) return 1;
	return couldaffect ( son ( son ( e ) ), z ) ;

    }
    if ( ne < plus_tag || ne == contvol_tag ) return 1;

    e = son ( e ) ;
    while ( e != NULL ) {
	if ( couldaffect ( e, z ) ) return 1;
	if ( last ( e ) ) return 0;
	e = bro ( e ) ;
    }
    return 0;
}


/*
    DOES e DEPEND ON z?
*/

static bool 
dependson ( exp e, bool isc, exp z )
{
    if (e == NULL) {
	return 0;
    }
    for ( ; ; ) {
	if ( name ( z ) == reff_tag || name ( z ) == addptr_tag ||
	     name ( z ) == subptr_tag ) {
	    z = son ( z ) ;
	}
	if ( name ( z ) != name_tag ) {
	    if ( name ( z ) != cont_tag ) return 1;
	    z = 0 ;
	    break ;
	}
	
	if ( isvar ( son ( z ) ) ) break ;
	if ( name ( son ( z ) ) == proc_tag ) {
	    z = 0 ;
	    break ;
	}
	if ( son ( son ( z ) ) == NULL ) {
	    /* can it happen? */
	    return 1;
	}
	z = son ( son ( z ) ) ;
    }

    /* z is now unambiguous variable name or 0 (meaning some contents) */
    return ( bool ) ( isc ? couldbe ( e, z ) : couldaffect ( e, z ) ) ;
}


/*
    REMOVE ASSOCATIONS OF ANY REGISTERS DEPENDING ON lhs
*/

void 
clear_dep_reg ( exp lhs )
{
  int i ;
  for ( i = 0 ; i < 48 ; i++ )
  {
    if (regexps[i].keptexp != NULL)
      switch(name(regexps[i].keptexp))
      {
       case val_tag:
       case null_tag:
       case real_tag:
       case string_tag:
       case name_tag:
	if (!regexps[i].iscont)
	{			/* constant value, cannot be changed
				   by assign */
	  continue;
	}
       default:
	if ( dependson ( regexps [i].keptexp, regexps [i].iscont, lhs ) ) 
	{	
	  regexps [i].keptexp = NULL ;
	  setregalt ( regexps [i].inans, 0 ) ;
#ifdef DWARF2
	  if (diag == DIAG_DWARF2)
	    dw_close_regassn (i);
#endif
	}
      }
  }
}
