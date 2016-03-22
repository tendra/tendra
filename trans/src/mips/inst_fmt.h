/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* inst_fmtdecs.h
    procs for outputting various MIPS instruction formats to external files
    as_file and ba_file
*/

#include "addr.h"

extern void ls_ins(char *ins, int reg, baseoff a);
extern void mon_ins(char *ins, int dest, int src);
extern void rrr_ins(char *ins, int dest, int src1, int src2);
extern void rri_ins(char *ins, int dest, int src1, long imm);
extern void uncond_ins(char *ins, int lab);
extern void condrr_ins(char *ins, int src1, int src2, int lab);
extern void condri_ins(char *ins, int src1, long imm, int lab);
extern void condr_ins(char *ins, int src1, int lab);
extern void cop_ins(char *ins, int gr, int fr);
extern void lsfp_ins(char *ins, int reg, baseoff a);
extern void rrfp_ins(char *ins, int dest, int src);
extern void rrfpcond_ins(char *ins, int dest, int src);
extern void rrrfp_ins(char *ins, int dest, int src1, int src2);
extern void ri_ins(char *ins, int dest, long imm);
extern void br_ins(char *ins, int dest);
extern void extj_ins(char *ins, baseoff b);
extern void tround_ins(char *ins, int dfr, int sfr, int gpr);
extern void multdiv_ins(char *ins, int r1, int r2);
extern void hilo_ins(char * ins, int dest);
