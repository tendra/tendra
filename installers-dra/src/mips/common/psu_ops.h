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
$Log: psu_ops.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* psu_opsdecs.h
*/



extern void setnoreorder(void);
extern void setreorder(void);
extern void setnomove(void);
extern void setmove(void);
extern void setvolatile(void);
extern void setnovolatile(void);
extern void setnoat(void);
extern void setat(void);
extern void comment(char *mess);
extern void setframe(long st);
extern void settext(void);
extern void setmask(long mask, long disp);
extern void setfmask(long mask, long disp);
