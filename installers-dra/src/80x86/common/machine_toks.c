/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* 80x86/machine_toks.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: machine_toks.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/01/30  12:56:34  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.2  1994/08/09  12:42:46  jmf
 * added ~rem
 *
 * Revision 1.1  1994/07/12  14:37:10  jmf
 * Initial revision
 *
**********************************************************************/


#include "config.h"

int machine_toks
(char * s)
{
  if (!strcmp(s, "~div"))
    return 1;
  if (!strcmp(s, "~rem"))
    return 1;
  if (!strcmp(s, "JMFprofile"))
    return 1;
  if (!strcmp(s, "JMFinline"))
    return 1;

  return 0;
}
