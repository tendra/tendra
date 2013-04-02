/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef f64_key
#define f64_key

#include <construct/flpttypes.h>

extern flt64 flt_to_f64(flpt fp, int sg, int *ov);
extern flpt f64_to_flt(flt64 a, int sg);
extern int f64_to_flpt(flt64 a, int sg, int *pr, int sz);
extern flt64 int_to_f64(int i, int sg);
extern flt64 exp_to_f64(exp e);

#endif
