/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:46 $
$Revision: 1.1.1.1 $
$Log: global_opt.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/


/******************************************************************

                            checkextdecs.h

   checkext looks to see if it can improve the definition (exp)
   of an globally declared item. If it makes a change it returns 1,
   otherwise 0.

   The most important transformation is inlining of procedures.

 *******************************************************************/


extern void checkext(exp e);
