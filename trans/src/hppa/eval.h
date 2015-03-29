/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EVALDECS_INCLUDED
#define EVALDECS_INCLUDED

#include "addrtypes.h"

#include <flpt/flpt.h>

extern int next_data_lab(void);
extern int next_PIC_pcrel_lab(void);
extern mm maxmin(shape);
extern instore evaluated(exp, long);
extern void set_align(int);
extern void evalone(exp, int);

#endif /* EVALDECS_INCLUDED */
