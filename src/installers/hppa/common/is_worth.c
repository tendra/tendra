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
$Log: is_worth.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:11:42  wfs
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
 * Revision 3.4  1995/08/25  13:33:36  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  13:33:36  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:26:58  16:26:58  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:17:55  11:17:55  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:27:42  15:27:42  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.2  95/01/17  17:25:20  17:25:20  wfs (William Simmonds)
 * Changed name of an included header file
 * 
 * Revision 1.1  95/01/11  13:10:17  13:10:17  wfs (William Simmonds)
 * Initial revision
 * 
*/


#define HPPATRANS_CODE
#include "config.h"
#include "common_types.h"
#include "tags.h"
#include "expmacs.h"
#include "exp.h"
#include "shapemacs.h"
#include "hppains.h"
#include "is_worth.h"

/*
    BOOLEAN VALUES
*/

#define true 1
#define false 0


/*
    IS THE EXPRESSION c WORTH EXTRACTING FROM A LOOP?

    This is called from mc_list.
*/

int is_worth
    PROTO_N ( ( c ) )
    PROTO_T ( exp c )
{
    unsigned char cnam = name ( c ) ;
    bool isflt = ( bool ) is_floating ( name ( sh ( c ) ) ) ;

    if ( name ( sh ( c ) ) == ptrhd && al1 ( sh ( c ) ) == 1 ) {
	/* Pointers to bits aren't */
	return ( false ) ;
    }

#if 0
    if (cnam==name_tag && name(father(c))==addptr_tag && isglob(son(c)))
       return(true);
#endif

    if ( cnam == real_tag ) {
	/* Real constants are */
	return ( true ) ;
    }

    if ( cnam == goto_tag ) {
	/* Extracting gotos messes things up */
	return ( false ) ;
    }

    if ( cnam == cont_tag ) {
	exp s = son ( c ) ;
	if ( isflt && ( name ( s ) != name_tag || isglob ( son ( s ) ) ) ) {
	    return ( true ) ;
	}
	if ( name ( s ) == reff_tag && no ( s ) == 0 ) s = son ( s ) ;
	if ( name ( s ) == name_tag && isglob ( son ( s ) ) ) {
	    return ( true ) ;
	}
	if ( name ( s ) == cont_tag ) {
	   exp ss = son ( s ) ;
	   if ( name ( ss ) == reff_tag && no ( ss ) == 0 ) ss = son ( ss ) ;
	   if ( name ( ss ) == name_tag ) return ( true ) ;
	}
	return ( false ) ;
    }

#if 0
    if ( name ( sh ( c ) ) == ptrhd && isglob(son(c)) ) {
	return ( true ) ;
    }
#endif

    if ( cnam == val_tag ) {
	/* It is sometimes worth extracting large integer constants */
	exp dad ;
	long n = no ( c ) ;
	if ( n==0  )
	   return (false) ;
	if ( shape_size(sh(c))==64 )
	   return (false) ; /* Cannot put 64 bit integers in registers! */
	dad = father ( c ) ;
	if (dad==nilexp)
	{
	   if (SIMM13(n)) return (false);
	   return (true);
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
			return ( false ) ;
		}
		/* FALL THROUGH */
		if (((n+1)&n) ==0)
		   return false;

	    }

	    case or_tag :
	    case xor_tag :
	    case test_tag : {
		/* Large or negative constants are worth extracting */
		return ( ( bool ) ( n<0 || !SIMM5( n ) ) ) ;
	    }

	    case mult_tag :
	    case offset_mult_tag : {
#if 0
		/* Is this necessarily true? */
		if ( SIMM13( n ) ) return ( false ) ;
		return ( ( bool ) ( ( n & ( n - 1 ) ) != 0 &&
				    ( n & ( n + 1 ) ) != 0 &&
				    ( ( n - 1 ) & ( n - 2 ) ) != 0 ) ) ;
#endif
		return ( false ) ;
	    }

	    case div1_tag :
	    case div2_tag :
	    case rem2_tag : {
#if 0
		/* Is this necessarily true? */
		if ( SIMM13( n ) ) return ( false ) ;
#endif
		return ( ( bool ) ( ( n & ( n - 1 ) ) != 0 ) ) ; /* LINT */
	    }

	    default : {
		/* Extract large constants */
		if ( SIMM13( n ) ) return ( false ) ;
		return ( true ) ;
	    }
	}
    }

    if ( is_o ( cnam ) || cnam == clear_tag ) return ( false ) ;
    return ( true ) ;
}

