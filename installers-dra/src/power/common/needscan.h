/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef NEEDSCANDECS_H
#define NEEDSCANDECS_H

#include <construct/installtypes.h>

#include "exptypes.h"


extern int maxfix, maxfloat;
extern long callee_size;
extern long max_callees;
extern bool gen_call;
extern long no_of_returns;

extern needs likeplus(exp *, exp **);
extern needs likeminus(exp *, exp **);
extern needs scan(exp *, exp **);


/*
 * For a general proc 4 parameters are passed in t-regs R_3 -- R_6 
 * for a normal proc by ABI 8 params must be passed in t-regs R_3 -- R_10
 */
#define GENERAL_PROC_PARAM_REGS 4
#define PROC_PARAM_REGS         8

/*
 * In an ideal world REGISTER_SAFETY_NUMBER would be zero 
 * It is a measure of how bad needscan is
 * It represents the number of t-regs available if needscan gets it wrong
 */
#define REGISTER_SAFETY_NUMBER 2


#endif /* needscandecs.h */
