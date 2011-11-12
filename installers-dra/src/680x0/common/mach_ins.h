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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/mach_ins.h,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: mach_ins.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:42:55  ma
First version.

Revision 1.3  1997/10/13 08:49:37  ma
Made all pl_tests for general proc & exception handling pass.

Revision 1.2  1997/05/13 11:30:35  ma
Introduced make_comment for debug.

Revision 1.1.1.1  1997/03/14 07:50:14  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:55  john
 *
 * Revision 1.2  1996/07/05  14:22:32  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:14  john
 *
 * Revision 1.2  94/02/21  16:00:14  16:00:14  ra (Robert Andrews)
 * A couple of flags which used to be bool are now int.
 *
 * Revision 1.1  93/02/22  17:16:05  17:16:05  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef MACH_INS_INCLUDED
#define MACH_INS_INCLUDED

#include "config.h"

#include "installtypes.h"

extern void make_instr_aux(int, mach_op *, mach_op *, bitpattern, int);

#define  make_instr(A, B, C, D)\
    make_instr_aux((A), (B), (C), (D), 0)

extern int output_immediately;
extern mach_ins *all_mach_ins;
extern mach_ins *current_ins;
extern void free_all_ins(void);
extern void reclaim_ins(mach_ins *);

extern long last_jump;
extern bitpattern last_jump_regs;

extern void make_external_label(char *);
extern void make_jump(int, long);
extern void make_label(long);
extern void set_special(char *, mach_op *);
#ifdef EBUG
extern void make_comment(char *);
#else
#define make_comment(X)
#endif

#endif











