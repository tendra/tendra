/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef flpt_key
#define flpt_key 1

#include <reader/code.h>
#include <construct/installtypes.h>
#include <construct/flpttypes.h>

#include <main/flags.h>

extern void init_flpt(void);
extern flpt new_flpt(void);
extern void flpt_ret(flpt f);
extern int cmpflpt(flpt a, flpt b, int testno);
extern flpt floatrep(int n);
extern flpt floatrep_unsigned(unsigned int n);
extern flt *flptnos;

/* floatingpoint functions - are these needed externally??? */
extern void flt_zero(flt *f);
extern void flt_copy(flt f, flt *res);
extern int  flt_add(flt f1, flt f2, flt *res);
extern int  flt_sub(flt f1, flt f2, flt *res);
extern int  flt_mul(flt f1, flt f2, flt *res);
extern int  flt_div(flt f1, flt f2, flt *res);
extern int  flt_cmp(flt f1, flt f2);
extern void flpt_newdig(unsigned int dig, flt *res, int base);
extern void flpt_scale(int decexp, flt *res, int base);
extern void flpt_round(int rdnmd, int pos, flt *res);
extern int flpt_bits(floating_variety fv);
extern int flpt_round_to_integer(int rndmd, flt *f);

#if FBASE != 10
extern r2l real2longs_IEEE(flt *f, int sw);
#endif

extern int fzero_no;
extern int fone_no;

#endif
