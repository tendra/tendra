/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
			    VERSION INFORMATION
			    ===================
--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/instr.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: instr.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.2  1997/10/29 10:22:20  ma
Replaced use_alloca with has_alloca.
Revision 1.1.1.1  1997/10/13 12:42:54  ma
First version.

Revision 1.1.1.1  1997/03/14 07:50:13  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:54  john
 *
 * Revision 1.2  1996/07/05  14:21:12  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:13  john
 *
 * Revision 1.1  93/02/22  17:15:52  17:15:52  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef INSTR_INCLUDED
#define INSTR_INCLUDED

extern mach_op * operand(long, where);
extern bitpattern regs_changed(mach_op *, int);
extern void ins0(int);
extern void ins1(int, long, where, int);
extern void ins2(int, long, long, where, where, int);
extern void ins2n(int, long, long, where, int);
extern void ins2h(int, long, long, where, int);
extern void save_stack(void);
extern void restore_stack(void);

#endif
