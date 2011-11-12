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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/out.h,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: out.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:50  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:30  djch
 * Initial revision
 *
 * Revision 1.1  93/06/24  14:59:00  14:59:00  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef OUTDECS_INCLUDED
#define OUTDECS_INCLUDED

#include <stdio.h>

extern FILE *as_file ;

#define fpout		as_file

#define outs( X )	fputs ( ( X ), as_file )
#define outc( X )	fputc ( ( X ), as_file )
#define outn( X )	fprintf ( as_file, "%ld", ( long ) ( X ) )
#define outf( X, Y )	fprintf ( as_file, ( X ), ( Y ) )
#define outnl()		fputc ( '\n', as_file )

#endif
