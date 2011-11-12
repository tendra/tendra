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
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/comment.h,v 1.1.1.1 1998/01/17 15:55:53 release Exp $
--------------------------------------------------------------------------
$Log: comment.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/07/14  16:29:51  john
 * Added comment macro
 *
 * Revision 1.1.1.1  1995/03/13  10:18:29  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.1  1994/05/03  14:50:07  djch
 * Initial revision
 *
 * Revision 1.3  93/08/13  14:35:40  14:35:40  ra (Robert Andrews)
 * Got rid of the comment macros.
 *
 * Revision 1.2  93/06/29  14:23:42  14:23:42  ra (Robert Andrews)
 * Declared sparctrans (executable name).
 *
 * Revision 1.1  93/06/24  14:58:05  14:58:05  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef COMMENT_INCLUDED
#define COMMENT_INCLUDED

#include <stdio.h>

#include "config.h"

#include "exptypes.h"
#include "codetypes.h"
#include "installtypes.h"

extern char *sparctrans;
extern bool do_comment;
extern void fail(char *);
extern FILE *as_file;

#define comment(st)	fprintf(as_file,"\t! %s\n",st);

#endif /* COMMENT_INCLUDED */
