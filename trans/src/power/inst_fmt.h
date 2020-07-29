/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef INST_FMTDECS_H
#define INST_FMTDECS_H

#include "addr.h"	/* for baseoff */
#include "instruct.h"	/* for Instruction_P */


extern char *ext_name(long);


extern void ld_ro_ins(Instruction_P,baseoff,int);
extern void ld_rr_ins(Instruction_P,int,int,int);
extern void ld_ins(Instruction_P,baseoff,int);

extern void st_ro_ins(Instruction_P,int,baseoff);
extern void st_rr_ins(Instruction_P,int,int,int);
extern void st_ins(Instruction_P,int,baseoff);

extern void rrr_ins(Instruction_P,int,int,int);
extern void rir_ins(Instruction_P,int,long,int);
extern void rr_ins(Instruction_P,int,int);

extern void mov_rr_ins(int,int);

extern void ld_const_ins(long,int);

extern void mf_ins(Instruction_P,int);
extern void mt_ins(Instruction_P,int);

extern void set_ins(baseoff,int);
extern void z_ins(Instruction_P);
extern void unimp_ins(long);

extern void cmp_rr_ins(Instruction_P,int,int,int);
extern void cmp_ri_ins(Instruction_P,int,long,int);

extern void bc_ins(Instruction_P,int,int ,int);
extern void long_bc_ins(Instruction_P,int,int ,int);
extern void uncond_ins(Instruction_P,int);

extern void extj_ins(Instruction_P,baseoff);
extern void extj_special_ins(Instruction_P,char *);

extern void ldf_ro_ins(Instruction_P,baseoff,int);
extern void ldf_rr_ins(Instruction_P,int,int,int);
extern void ldf_ins(Instruction_P,baseoff,int);
extern void stf_ro_ins(Instruction_P,int,baseoff);
extern void stf_rr_ins(Instruction_P,int,int,int);
extern void stf_ins(Instruction_P,int,baseoff);

extern void rrf_ins(Instruction_P,int,int);
extern void rrrf_ins(Instruction_P,int,int,int);
extern void rrrrf_ins(Instruction_P,int,int,int,int);
extern void rrf_cmp_ins(Instruction_P,int,int,int);
extern void fbr_ins(Instruction_P,int);
extern void rlinm_ins(Instruction_P,int,int,unsigned int,int);
extern void mfspr_ins(int,int);
extern void mtfsfi_ins(int,int);
extern void mtfsb1_ins(int);
extern void mtfsb0_ins(int);
extern void mcrfs_ins(int,int);
extern char *get_instruction(Instruction_P);
extern void lsi_ins(int,int,int);
extern void stsi_ins(int,int,int);
/* for mtfsfi_ins */

#define BITS_0_to_3     0
#define BITS_4_to_7     1
#define BITS_8_to_11    2
#define BITS_12_to_15   3
#define BITS_16_to_19   4
#define BITS_20_to_23   5
#define BITS_24_to_27   6
#define BITS_28_to_31   7

/* for bc_ins */
#define LIKELY_TO_JUMP   0
#define UNLIKELY_TO_JUMP 1

#endif /* inst_fmtdecs.h */


