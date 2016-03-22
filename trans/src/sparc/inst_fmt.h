/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef INST_FMT_INCLUDED
#define INST_FMT_INCLUDED

#include "addr.h"
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

extern void extj_special_ins(ins_p, const char * const, int);
extern void extj_reg_ins(ins_p, int, int);
extern void extj_reg_ins_no_delay(ins_p, int, int);

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
