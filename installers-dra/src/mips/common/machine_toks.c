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
$Log: machine_toks.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/

#include "config.h"

int
machine_toks(char * s)
{
  if (!strcmp(s, "~div"))
    return 1;
  if (!strcmp(s, "JMFprofile"))
    return 1;
  if (!strcmp(s, "JMFinline"))
    return 1;

  return 0;
}
