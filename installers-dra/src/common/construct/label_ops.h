/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:47 $
$Revision: 1.1.1.1 $
$Log: label_ops.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/
#ifndef label_ops_key
#define label_ops_key 1

#include "config.h"
#include "exptypes.h"

extern int label_is_next(exp lab, exp e);
extern exp short_next_jump(exp e);
extern exp jump_dest(exp lab);
extern exp final_dest(exp lab);
extern exp final_dest_test(exp lab, exp e);

#endif
