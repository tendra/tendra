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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/is_worth.c,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: is_worth.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/15  11:12:14  john
 * Change for 64 bit values
 *
 * Revision 1.1.1.1  1995/03/13  10:18:40  john
 * Entered into CVS
 *
 * Revision 1.4  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.3  1994/06/22  09:50:43  djch
 * added check for val_tag to avoid derefing father if nil - jmf may not have
 * connected the bro field, and we read it to get operator name.
 *
 * Revision 1.2  1994/05/13  12:33:17  djch
 * Incorporates improvements from expt version
 * Added bracket to make structure clearer
 *
 * Revision 1.1  1994/05/03  14:49:39  djch
 * Initial revision
 *
 * Revision 1.5  94/02/21  16:11:11  16:11:11  ra (Robert Andrews)
 * is_worth now returns an int, not a bool.
 * 
 * Revision 1.4  93/11/19  16:29:18  16:29:18  ra (Robert Andrews)
 * Never remove constant multiplicand from loops - it introduces a call
 * when we could get away with shifts and adds.
 * 
 * Revision 1.3  93/08/27  11:29:07  11:29:07  ra (Robert Andrews)
 * Added a couple of explicit integer casts.
 * 
 * Revision 1.2  93/07/14  11:18:46  11:18:46  ra (Robert Andrews)
 * Reformatted.  Changed cont_tag case to deal with reff_0's (because
 * remove_zero_offsets is 0 they are not being removed by check).
 * 
 * Revision 1.1  93/06/24  14:58:31  14:58:31  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE
#include "config.h"
#include "common_types.h"
#include "tags.h"
#include "expmacs.h"
#include "exp.h"
#include "shapemacs.h"
#include "sparcins.h"
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

    if ( cnam == val_tag ) {
	/* It is sometimes worth extracting large integer constants */
	exp dad ;
	long n = no ( c ) ;
	if ( n == 0 ) return ( false ) ;
	if(name(sh(c)) == u64hd || name(sh(c)) == s64hd) return (false);
	dad = father ( c ) ;

	if (dad == nilexp)
	{
	  if ( SIMM13_SIZE ( n ) ) return ( false ) ;
	  return ( true ) ;
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
	    }

	    case or_tag :
	    case xor_tag :
	    case test_tag : {
		/* Large or negative constants are worth extracting */
		return ( ( int ) ( n < 0 || !SIMM13_SIZE ( n ) ) ) ;
	    }

	    case mult_tag :
	    case offset_mult_tag : {
#if 0
		/* Is this necessarily true? */
		if ( SIMM13_SIZE ( n ) ) return ( false ) ;
		return ( ( int ) ( ( n & ( n - 1 ) ) != 0 &&
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
		if ( SIMM13_SIZE ( n ) ) return ( false ) ;
#endif
		return ( ( int ) ( ( n & ( n - 1 ) ) != 0 ) ) ; /* LINT */
	    }

	    default : {
		/* Extract large constants */
		if ( SIMM13_SIZE ( n ) ) return ( false ) ;
		return ( true ) ;
	    }
	}
    }

    if ( is_o ( cnam ) || cnam == clear_tag ) return ( false ) ;
    return ( true ) ;
}
