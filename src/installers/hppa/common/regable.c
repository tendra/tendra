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
$Log: regable.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1996/03/14  16:18:48  wfs
 * tophed is not valregable + ptr position in apply_general case of scan() + superfluous "set -x" in bl_install script.
 *
 * Revision 1.2  1995/12/18  13:12:25  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.1  1995/10/05  08:59:34  wfs
 * "isoutpar" check added to "fixregable()" and "floatregable()".
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  10:25:41  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  10:25:41  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:27:56  16:27:56  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:18:47  11:18:47  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:28:37  15:28:37  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.1  95/01/11  13:15:06  13:15:06  wfs (William Simmonds)
 * Initial revision
 * 
*/


#define HPPATRANS_CODE
#include "config.h"
#include "expmacs.h"
#include "common_types.h"
#include "shapemacs.h"
#include "regable.h"
#include "tags.h"

/*
    DOES A VALUE OF SHAPE s FIT INTO A FIXED REGISTER?
*/

bool valregable 
    PROTO_N ( ( s ) )
    PROTO_T ( shape s )
{
    int n = name(s);
    if ( is_floating(n) )
    {
	return 0 ; /* floats don't go in fixed point registers */
    } 
    else
    {
	ash a ;
	a = ashof(s) ;
	if ( a.ashsize > 32 )
	{
	    return (0) ; /* too big for a 32 bit register */
	} 
	else if ( n==cpdhd || n==nofhd )
	{
	    return 0 ; /* Compound shapes are not put in registers */
	}
	else if ( n==tophd )
	{
	    return 0 ;
	}
	else
	{
	    return 1 ;
	}
    }
}

/*
    DOES THE EXPRESSION e FIT INTO A FIXED REGISTER?
*/

bool fixregable 
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
    if ( !isvis ( e ) && !isoutpar( e ) && !isglob ( e ) && !isenvoff(e)
		      && (name(son(e))!=caller_name_tag) ) {
	shape s = sh ( son ( e ) ) ;
	return ( valregable ( s ) ) ;
    }
    return ( 0 ) ;
}


/*
    DOES THE EXPRESSION e FIT INTO A FLOATING POINT REGISTER?
*/

bool floatregable 
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
    if ( !isvis ( e ) && !isoutpar( e ) && !isglob ( e ) && !isenvoff(e)
		      && (name(son(e))!=caller_name_tag) ) {
	shape s = sh ( son ( e ) ) ;
	if ( is_floating ( name ( s ) ) ) {
#if use_long_double
	   if ( shape_size ( s ) > 64 )
	   {
	      return ( 0 ) ;
	   }
#endif
	   return ( 1 ) ;
	} else {
	    return ( 0 ) ;
	}
    }
    return (0) ;
}
