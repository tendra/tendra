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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/fbase.h,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: fbase.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:34  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:16  djch
 * Initial revision
 *
 * Revision 1.2  93/09/27  14:44:21  14:44:21  ra (Robert Andrews)
 * If we are using quad precision then we need to increase the accuracy
 * of the floating point constant emulator to 160 bits from the default
 * 128 bits.
 * 
 * Revision 1.1  93/06/24  14:58:17  14:58:17  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#ifndef FBASE_INCLUDED
#define FBASE_INCLUDED

#define FBASE		65536

#if use_long_double
#define MANT_SIZE	10
#endif

#endif /* FBASE_INCLUDED */
