/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCATEDECS_H
#define LOCATEDECS_H

#include <reader/exp.h>

#include "procrectypes.h"

extern baseoff boff(exp);
extern baseoff boff_location(int);
extern where locate(exp , space , shape , int);
extern int ENCODE_FOR_BOFF(int,int);

#define OUTPUT_CALLER_PARAMETER  1
#define INPUT_CALLER_PARAMETER   2
#define INPUT_CALLEE_PARAMETER   3

#endif
