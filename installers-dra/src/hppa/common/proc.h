/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/*
$Log: proc.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:02  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/12/18  13:12:19  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.1  1995/09/15  14:18:15  wfs
 * "extern void restore_sregs()" added.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.4  1995/08/25  11:12:16  wfs
 * *** empty log message ***
 *
 * Revision 3.1  95/04/10  16:27:47  16:27:47  wfs (William Simmonds)
 * Apr95 tape version.
 *
 * Revision 3.0  95/03/30  11:18:38  11:18:38  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 *
 * Revision 2.0  95/03/15  15:28:29  15:28:29  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 *
 * Revision 1.1  95/01/11  13:41:48  13:41:48  wfs (William Simmonds)
 * Initial revision
 *
*/


#ifndef PROCDECS_INCLUDED
#define PROCDECS_INCLUDED

#include "config.h"

#include "installtypes.h"
#include "addrtypes.h"
#include "proctypes.h"
#include "exptypes.h"

struct proc_state {
    ans procans;
    bool leaf;
    baseoff mem_temp0;
    int rscope_level;
    int rscope_label;
    int result_label;
    long callees_offset;
    long params_offset;
    long frame_sz;
    long locals_offset;
    long locals_space;
    long max_args;
    long fixdump;
};


extern struct proc_state proc_state;
extern baseoff mem_temp(int);
extern makeans make_proc_tag_code(exp, space, where, int);
extern makeans make_rscope_tag_code(exp, space, where, int);
extern makeans make_res_tag_code(exp, space, where, int);
extern makeans make_apply_tag_code(exp, space, where, int);
extern void restore_sregs(void);

#endif /* PROCDECS_INCLUDED */
