/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef INST_FMT_INCLUDED
#define INST_FMT_INCLUDED

#include <stdio.h>

#include "addr.h"
#include "hppains.h"

extern char *ext_name(long);

extern void ldmb_ins(ins_p, int, int, int);
extern void ld_ins(ins_p, int, baseoff, int);

extern void st_ins(ins_p, int, baseoff);

extern void riir_ins(ins_p, ins_p, int, long, long, int);

extern void ir_ins(ins_p, ins_p, const char*, long, int);

extern void imm_to_r(long, int);

extern void set_ins(char*, baseoff, int);
extern void z_ins(ins_p);

extern void condrr_ins(char, ins_p, int, int, int, int);
extern void condri_ins(ins_p, int, long, int);

extern void extj_special_ins(const char *, int, char *, int);
extern void extj_reg_ins(ins_p, int);

extern void ret_ins(ins_p);

extern void ldf_ro_ins(ins_p, baseoff, int);
extern void ldf_rr_ins(ins_p,ins_p, int, int, int);
extern void ldf_ins(ins_p, baseoff, int);
extern void stf_ro_ins(ins_p, int, baseoff);
extern void stf_ins(ins_p, int, baseoff);

extern void rrf_ins(ins_p,ins_p,ins_p, int, int);
extern void rrrf_ins(ins_p, ins_p, int, int, int);

extern void rrf_cmp_ins(ins_p, int, int);
extern void immr_ins(ins_p, char*,char*,long,char*,int);
extern void ld_immr_ins(ins_p, char*,char*,long,char*,int,int);
extern void st_immr_ins(ins_p,int, char*,char*,long,char*,int);
extern void iiir_ins(ins_p,ins_p,int,int,int,int);
extern void bb_in(ins_p,int,int,int);
extern void rr_ins(ins_p, int, int);
extern void rrr_ins(ins_p, ins_p, int, int, int);
extern void ub_ins(const char*, int);
extern void cj_ins(const char*, int, int, int);
extern void st_ir_ins(ins_p, ins_p, int, ins_p, const char*, long, int);
extern void ld_ir_ins(ins_p, ins_p, ins_p, const char*, long, int, int);
extern void comb_ins(const char*, int, int, int);
extern void cmp_rrf_ins(ins_p, ins_p, ins_p, int, int);
extern void rrir_ins(ins_p, ins_p, int, int, long, int);
extern void cij_ins(const char*, long, int, int);
extern void irr_ins(ins_p, ins_p, ins_p, long, int, int);
extern void ld_rr_ins(ins_p, ins_p, int, int, int);
extern void r_ins(ins_p, int);
extern void out_directive(const char*, const char*);
extern void iir_ins(ins_p, ins_p, int, int, int);
extern void rir_ins(ins_p, ins_p, int, long, int);
extern const char* reg_name(int);
extern void call_ins(ins_p, char*, int, char*);
extern void outlab(char*, int);
extern void bl_in(ins_p, char*, int);

int line,lines,nLabels;

typedef fpos_t FILE_POSN;
#define SET_FILE_POSN(A, B)		fsetpos((A), & (B))
#define GET_FILE_POSN(A, B)		fgetpos((A), & (B))

typedef struct {
   FILE_POSN fpos;     /* position in outf  */
   ins_p  ins;        /* instruction       */
   ins_p  cc;        /* condition code    */
   int    op[4];    /* operands          */
   int    lab;     /* label             */
} psuedoIn;

typedef psuedoIn *pIn;

/* #define BLOCK 131072 */

#define BLOCK 65536
#define INCR  4096

pIn *pCode;
int *labIntro;  /*  `labIntro[lab]' will record the line number on
                     which label `lab' was introduced. */



#endif /* INST_FMT_INCLUDED */
