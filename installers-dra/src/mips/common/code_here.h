/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:05 $
$Revision: 1.1.1.1 $
$Log: code_here.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/08/16  16:06:33  currie
 * Shortened some .h names
 *
 * Revision 1.1  1995/08/16  15:38:39  currie
 * Initial revision
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* code_heredecs.h
*/

#include "procrectypes.h"
#include "addrtypes.h"

extern int  regofval(exp e);
extern int  fregofval(exp e);
extern int  reg_operand(exp e, space sp);
extern int  freg_operand(exp e, space sp);
extern int  code_here(exp e, space sp, where dest);
