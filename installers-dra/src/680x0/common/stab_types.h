/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
			    VERSION INFORMATION
			    ===================
--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/stab_types.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: stab_types.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:43:02  ma
First version.
Revision 1.1.1.1  1997/03/14 07:50:22  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:57:01  john
 *
 * Revision 1.2  1996/07/05  14:33:10  john
 * Removed copyright message
 *
 * Revision 1.1  95/03/08  16:46:15  ra
 * Added missing files.
 *
 * Revision 1.2  94/02/21  16:08:31  16:08:31  ra (Robert Andrews)
 * make_stabs and make_stabn now take an int in place of one long.
 *
 * Revision 1.1  93/02/22  17:17:18  17:17:18  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef STAB_TYPES_INCLUDED
#define STAB_TYPES_INCLUDED

extern void make_stabs(char *, int, long, mach_op *);
extern void make_stabn(int, long);
extern void init_stab_types(void);
extern char * analyse_stab_type(diag_type, char *, char *);

#endif
