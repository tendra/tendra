/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/maxminmacs.h,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: maxminmacs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:44  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:24  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:58:44  14:58:44  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef MAXMINMACS_INCLUDED
#define MAXMINMACS_INCLUDED

#define MAX_OF( a, b )	( ( ( a ) >= ( b ) ) ? ( a ) : ( b ) )
#define MIN_OF( a, b )	( ( ( a ) <= ( b ) ) ? ( a ) : ( b ) )
#define ABS_OF( a )	( ( ( a ) < 0 ) ? -( a ) : ( a ) )

#endif /* MAXMINMACS_INCLUDED */
