/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
$Log: pseudo.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:00  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1.1.1  1995/03/23  10:39:18  john
 * Entered into CVS
 *
 * Revision 1.7  1995/03/23  10:12:05  john
 * Changed prototype
 *
 * Revision 1.6  1995/01/26  13:47:22  john
 * Added prototype for set_lineno
 *
*/

#ifndef PSEUDO_H
#define PSEUDO_H
#include "cross.h"


extern void setnoreorder(void);
extern void setreorder(void);
extern void setnomove(void);
extern void setmove(void);
extern void setvolatile(void);
extern void setnovolatile(void);
extern void setnoat(void);
extern void setat(void);
extern void comment(char *mess);
extern void setframe(int32,int32);
extern void set_text_section(void);
extern void setmask(int mask, int disp);
extern void setfmask(int mask, int disp);
extern void set_file(char *,int);
extern void setprologue(int);
extern void set_align(int);
extern void set_lineno(int,int);


#endif
