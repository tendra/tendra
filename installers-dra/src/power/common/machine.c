/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */



/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:48:54 $
$Revision: 1.2 $
$Log: machine.c,v $
 * Revision 1.2  1998/02/04  15:48:54  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:01:58  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "config.h"
#include "memtdf.h"
#include "machine.h"


/* prefixes for assembler labels, set in translat.c */
char *local_prefix;
char *name_prefix;


/* Is the result of a procedure delivering this shape produced in registers? */
bool reg_result(shape sha)
{
  return is_floating(name(sha) ||
    (shape_size(sha) <= 32 && !IS_AGGREGATE(sha)));
}
