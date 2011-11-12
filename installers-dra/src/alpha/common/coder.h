/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
$Log: coder.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:59  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/08/21  08:44:07  john
 * Changed include files
 *
 * Revision 1.2  1995/07/27  09:32:24  john
 * New structure for postlude handling
 *
 * Revision 1.1.1.1  1995/03/23  10:39:29  john
 * Entered into CVS
 *
 * Revision 1.4  1995/03/23  10:01:57  john
 * Added support for scheduler
 *
 * Revision 1.3  1995/01/26  13:38:00  john
 * Changed declaration of fscopefile
 *
*/

#ifndef CODER_H
#define CODER_H

#include "config.h"

#include "installtypes.h"
#include "addresstypes.h"
#include "procrectypes.h"
#include "exptypes.h"

extern where nowhere;
extern int fscopefile;

extern bool last_param(exp);
extern makeans make_code(exp e, space sp, where dest, int exitlab);
extern int bitsin(int);


typedef struct _postl {
  exp postlude;
  struct _postl * outer;
} postlude_chain;


#if !DO_SCHEDULE
#define start_new_capsule(X)
#define close_capsule()
#define false 0
#define true 1
#endif

#endif
