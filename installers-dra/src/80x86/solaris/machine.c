/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* sol86/machine.c */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:53 $
$Revision: 1.1.1.1 $
$Log: machine.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1996/03/12  12:44:38  pwe
 * 64-bit ints compatible with gcc long long
 *
 * Revision 1.4  1995/09/20  12:00:47  pwe
 * svr4 and solaris initial_value, and solaris 64 bit correction
 *
 * Revision 1.3  1995/01/30  12:57:36  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.2  1994/07/13  07:44:28  jmf
 * initialise prefix here.
 *
**********************************************************************/


#include "config.h"
#include "expmacs.h"
#include "exp.h"
#include "shapemacs.h"
#include "out.h"
#include "localflags.h"
#include "szs_als.h"

/* VARIABLES */
/* All variables are initialised, jmf */

char *local_prefix = ".L";
char *name_prefix = "";


/* PROCEDURES */

/* is the result of a procedure delivering
   this shape produced in registers. */
int
reg_result(shape sha)
{
  unsigned char  n = name(sha);
  if (gcc_compatible) {
    int sz = shape_size(sha);
    if (n == nofhd) {
      return 0;
    }
    if (n == cpdhd && sz > 32 && sz != 64) {
      return 0;
    }
    return 1;
  }
  if (n == cpdhd || n == nofhd) {
    return 0;
  }
  return 1;
}
