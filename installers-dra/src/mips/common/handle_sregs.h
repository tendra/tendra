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
$Log: handle_sregs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/* handle_sregs.h
*/



extern long floatdump;
extern long fixdump;

extern long dumpstart;
extern long fldumpstart;

extern long fixdone;
extern long fltdone;

extern void dump_sreg(int n);
extern void dump_sfreg(int n);
extern void recover_sreg(int n);
extern void recover_sfreg(int n);

extern void restore_sregs(long fd, long fld);
extern void dump_sregs(long fd, long fld);

extern void dump_all_sregs(void);
