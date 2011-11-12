/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */







/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:06 $
$Revision: 1.1.1.1 $
$Log: machine.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/

#include "config.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "installtypes.h"


/* is the result of a procedure delivering
   this shape produced in registers. */
bool
reg_result(shape sha)
{
  return ( is_floating(name(sha)) ||
    (shape_size(sha) <= 32 && name (sha) != cpdhd && name(sha) != nofhd));

}

char * local_prefix;
char * name_prefix;
