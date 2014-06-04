/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#include <shared/bool.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/is_worth.h>

#include "sparcins.h"

bool
is_worth ( exp c )
{
    unsigned char cnam = name ( c ) ;
    bool isflt = ( bool ) is_floating ( name ( sh ( c ) ) ) ;

    if ( name ( sh ( c ) ) == ptrhd && al1 ( sh ( c ) ) == 1 ) {
	/* Pointers to bits aren't */
	return false;
    }

    if ( cnam == real_tag ) {
	/* Real constants are */
	return true;
    }

    if ( cnam == goto_tag ) {
	/* Extracting gotos messes things up */
	return false;
    }

    if ( cnam == cont_tag ) {
	exp s = son ( c ) ;
	if ( isflt && ( name ( s ) != name_tag || isglob ( son ( s ) ) ) ) {
	    return true;
	}
	if ( name ( s ) == reff_tag && no ( s ) == 0 ) s = son ( s ) ;
	if ( name ( s ) == name_tag && isglob ( son ( s ) ) ) {
	    return true;
	}
	if ( name ( s ) == cont_tag ) {
	   exp ss = son ( s ) ;
	   if ( name ( ss ) == reff_tag && no ( ss ) == 0 ) ss = son ( ss ) ;
	   if ( name ( ss ) == name_tag ) return true;
	}
	return false;
    }

    if ( cnam == val_tag ) {
	/* It is sometimes worth extracting large integer constants */
	exp dad ;
	long n = no ( c ) ;
	if ( n == 0 ) return false;
	if(name(sh(c)) == u64hd || name(sh(c)) == s64hd) return false;
	dad = father ( c ) ;

	if (dad == NULL)
	{
	  if ( SIMM13_SIZE ( n ) ) return false;
	  return true;
	}
	
	switch ( name ( dad ) ) {

	    case and_tag : {
		exp grandad = father ( dad ) ;
		if ( (name ( grandad ) == test_tag && ( n & ( n - 1 ) ) == 0
		     && ( props ( grandad ) == 5 || props ( grandad ) == 6 )
		     && ( name ( bro ( son ( grandad ) ) ) == val_tag
		     && no ( bro ( son ( grandad ) ) ) == 0 ))
		     || ( name ( son ( grandad ) ) == val_tag
		     && no ( son ( grandad ) ) == 0 ) ) {
			/* a & 2^n == 0 is transformed into a shift */
			return false;
		}
		/* FALL THROUGH */
	    }

	    case or_tag :
	    case xor_tag :
	    case test_tag : {
		/* Large or negative constants are worth extracting */
		return ( int ) ( n < 0 || !SIMM13_SIZE ( n ) ) ;
	    }

	    case mult_tag :
	    case offset_mult_tag : {
#if 0
		/* Is this necessarily true? */
		if ( SIMM13_SIZE ( n ) ) return false;
		return ( int ) ( ( n & ( n - 1 ) ) != 0 &&
				    ( n & ( n + 1 ) ) != 0 &&
				    ( ( n - 1 ) & ( n - 2 ) ) != 0 ) ;
#endif
		return false;
	    }

	    case div1_tag :
	    case div2_tag :
	    case rem2_tag : {
#if 0
		/* Is this necessarily true? */
		if ( SIMM13_SIZE ( n ) ) return false;
#endif
		return ( int ) ( ( n & ( n - 1 ) ) != 0 ) ; /* LINT */
	    }

	    default : {
		/* Extract large constants */
		if ( SIMM13_SIZE ( n ) ) return false;
		return true;
	    }
	}
    }

    if ( is_o ( cnam ) || cnam == clear_tag ) return false;
    return true;
}
