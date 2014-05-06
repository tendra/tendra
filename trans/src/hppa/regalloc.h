/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef REGALLOC_INCLUDED
#define REGALLOC_INCLUDED

#include <local/exptypes.h>
#include "proctypes.h"

extern spacereq regalloc(exp, int, int, long);
extern int real_reg[16];

#endif /* REGALLOC_INCLUDED */




