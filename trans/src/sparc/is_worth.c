/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <construct/exp.h>
#include <construct/is_worth.h>

#include "sparcins.h"

bool
is_worth ( exp c )
{
	unsigned char cnam = c->tag ;
	bool isflt = ( bool ) is_floating ( sh ( c ) -> tag ) ;

	if ( sh ( c ) -> tag == ptrhd && al1 ( sh ( c ) ) == 1 ) {
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
		if ( isflt && ( s->tag != name_tag || isglob ( son ( s ) ) ) ) {
			return true;
		}
		if ( s->tag == reff_tag && no ( s ) == 0 ) {
			s = son ( s ) ;
		}
		if ( s->tag == name_tag && isglob ( son ( s ) ) ) {
			return true;
		}
		if ( s->tag == cont_tag ) {
			exp ss = son ( s ) ;
			if ( ss->tag == reff_tag && no ( ss ) == 0 ) {
				ss = son ( ss ) ;
			}
			if ( ss->tag == name_tag ) {
				return true;
			}
		}
		return false;
	}

	if ( cnam == val_tag ) {
		/* It is sometimes worth extracting large integer constants */
		exp dad ;
		long n = no ( c ) ;
		if ( n == 0 ) {
			return false;
		}
		if(sh(c)->tag == u64hd || sh(c)->tag == s64hd) {
			return false;
		}
		dad = father ( c ) ;

		if (dad == NULL) {
			if ( SIMM13_SIZE ( n ) ) {
				return false;
			}
			return true;
		}

		switch ( dad->tag ) {
		case and_tag : {
			exp grandad = father ( dad ) ;

			if ( (grandad->tag == test_tag && ( n & ( n - 1 ) ) == 0
			      && ( props ( grandad ) == 5 || props ( grandad ) == 6 )
			      && ( bro ( son ( grandad ) ) -> tag == val_tag
			           && no ( bro ( son ( grandad ) ) ) == 0 ))
			     || ( son ( grandad ) -> tag == val_tag
			          && no ( son ( grandad ) ) == 0 ) ) {
				/* a & 2^n == 0 is transformed into a shift */
				return false;
			}

			FALL_THROUGH;
		}

		case or_tag :
		case xor_tag :
		case test_tag :
			/* Large or negative constants are worth extracting */
			return ( int ) ( n < 0 || !SIMM13_SIZE ( n ) ) ;

		case mult_tag :
		case offset_mult_tag :
#if 0
			/* Is this necessarily true? */
			if ( SIMM13_SIZE ( n ) ) {
				return false;
			}

			return ( int ) ( ( n & ( n - 1 ) ) != 0 &&
			                 ( n & ( n + 1 ) ) != 0 &&
			                 ( ( n - 1 ) & ( n - 2 ) ) != 0 ) ;
#endif
			return false;

		case div1_tag :
		case div2_tag :
		case rem2_tag :
#if 0
			/* Is this necessarily true? */
			if ( SIMM13_SIZE ( n ) ) {
				return false;
			}
#endif

			return ( int ) ( ( n & ( n - 1 ) ) != 0 ) ; /* LINT */

		default :
			/* Extract large constants */
			if ( SIMM13_SIZE ( n ) ) {
				return false;
			}

			return true;
		}
	}

	if ( is_o ( cnam ) || cnam == clear_tag ) {
		return false;
	}

	return true;
}

