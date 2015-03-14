/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MOVEDECS_H
#define MOVEDECS_H

#include <construct/installtypes.h>

#include "addresstypes.h"
#include "instruct.h"

extern Instruction_P i_ld_sz(int , int);
extern Instruction_P i_st_sz(int);

extern int move(ans , where , long , bool);

#endif /* movedecs.h */
