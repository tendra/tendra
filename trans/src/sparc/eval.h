/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EVALDECS_INCLUDED
#define EVALDECS_INCLUDED

#include <construct/installtypes.h>
#include "addrtypes.h"
#include <construct/flpttypes.h>

extern bool is_zero(exp);
extern instore evaluated(exp, long, bool);
extern int next_data_lab(void);
extern long *realrep(exp);
extern long evalexp(exp);
extern mm maxmin(shape);
extern void evalone(exp, int, bool);
extern void outlab(int);

#endif /* EVALDECS_INCLUDED */
