/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:06 $
$Revision: 1.1.1.1 $
$Log: operators.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/08/16  15:38:39  currie
 * Initial revision
 *
 * Revision 1.2  1995/08/16  15:32:34  currie
 * update long includes
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* operatorsdecs.h
*/


#include "exptypes.h"
#include "addrtypes.h"


extern int comm_op(exp e, space sp, where d, char *rins);
extern int non_comm_op(exp e, space sp, where dest, char *ins);
extern int monop(exp e, space sp, where dest, char *ins);
extern int fop(exp e, space sp, where dest, char *ins);
extern int fmop(exp e, space sp, where dest, char *ins);
