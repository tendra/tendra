/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/labels.h,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: labels.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/13  10:18:41  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:20  djch
 * Initial revision
 *
 * Revision 1.2  93/09/27  14:46:24  14:46:24  ra (Robert Andrews)
 * Declare lab_prefix, the prefix for labels.
 *
 * Revision 1.1  93/06/24  14:58:33  14:58:33  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef LABELDECS_INCLUDED
#define LABELDECS_INCLUDED

extern char *lab_prefix;
extern void seed_label(void);
extern int new_label(void);
extern void set_label(int);

#endif /* LABELDECS_INCLUDED */
