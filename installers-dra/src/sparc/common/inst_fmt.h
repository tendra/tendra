/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/inst_fmt.h,v 1.1.1.1 1998/01/17 15:55:54 release Exp $
--------------------------------------------------------------------------
$Log: inst_fmt.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:54  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1997/10/10  18:32:29  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.5  1995/09/13  11:00:55  john
 * New prototype
 *
 * Revision 1.4  1995/07/18  09:38:50  john
 * New functions for return_to_label
 *
 * Revision 1.3  1995/07/14  16:31:16  john
 * Changed prototype name
 *
 * Revision 1.2  1995/05/26  12:58:48  john
 * New prototype
 *
 * Revision 1.1.1.1  1995/03/13  10:18:39  john
 * Entered into CVS
 *
 * Revision 1.5  1994/12/21  12:10:54  djch
 * added maxmin functions
 *
 * Revision 1.4  1994/12/01  13:17:17  djch
 * Added 3 new fns
 *
 * Revision 1.3  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.2  1994/05/13  12:32:10  djch
 * Incorporates improvements from expt version
 * changed extj_special_ins to match
 *
 * Revision 1.1  1994/05/03  14:50:19  djch
 * Initial revision
 *
 * Revision 1.2  93/08/27  11:28:10  11:28:10  ra (Robert Andrews)
 *  ext_name now takes an int not a long (I got the comment in inst_fmt.c
 * wrong).
 *
 * Revision 1.1  93/06/24  14:58:30  14:58:30  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef INST_FMT_INCLUDED
#define INST_FMT_INCLUDED

#include "addrtypes.h"
#include "sparcins.h"

/* special registers */
#define YREG	65
#define FSR	33

extern char *ext_name(int);

extern void ld_ro_ins(ins_p, baseoff, int);
extern void ld_rr_ins(ins_p, int, int, int);
extern void ld_ins(ins_p, baseoff, int);

extern void st_ro_ins(ins_p, int, baseoff);
extern void st_rr_ins(ins_p, int, int, int);
extern void st_ins(ins_p, int, baseoff);

extern void rrr_ins(ins_p, int, int, int);
extern void rir_ins(ins_p, int, long, int);
extern void rr_ins(ins_p, int, int);
extern void ir_ins(ins_p, long, int);
extern void lr_ins(int, int);

extern void set_ins(baseoff, int);
extern void z_ins(ins_p);
extern void unimp_ins(long);

extern void condrr_ins(ins_p, int, int, int);
extern void condri_ins(ins_p, int, long, int);
extern void fmaxminrr_ins(ins_p,int,int,int,int);
extern void maxminrr_ins(ins_p, int, int, int);
extern void maxminri_ins(ins_p, int, long, int);
extern void uncond_ins(ins_p, int);
extern void br_ins(ins_p, int);
extern void br_abs(int);
extern void lngjmp(int,int,int);

extern void extj_ins(ins_p, baseoff, int);
extern void extj_ins_without_delay(ins_p, baseoff, int);

extern void extj_special_ins(ins_p, const char * const, int);
extern void extj_special_ins_no_delay(ins_p, const char * const, int);
extern void extj_reg_ins(ins_p, int, int);
extern void extj_reg_ins_no_delay(ins_p, int, int);

extern void ret_ins(ins_p);
extern void ret_restore_ins(void);
extern void stret_restore_ins(void);

extern void ldf_ro_ins(ins_p, baseoff, int);
extern void ldf_rr_ins(ins_p, int, int, int);
extern void ldf_ins(ins_p, baseoff, int);
extern void stf_ro_ins(ins_p, int, baseoff);
extern void stf_rr_ins(ins_p, int, int, int);
extern void stf_ins(ins_p, int, baseoff);

extern void rrf_ins(ins_p, int, int);
extern void rrrf_ins(ins_p, int, int, int);

extern void rrf_cmp_ins(ins_p, int, int);
extern void fbr_ins(ins_p, int);

extern void out_asm_reg(int, int);
extern void out_asm_boff(baseoff, long);

#endif /* INST_FMT_INCLUDED */
