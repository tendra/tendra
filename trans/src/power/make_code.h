/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MAKECODEDECS_H
#define MAKECODEDECS_H

#include <reader/exp.h>

#include <construct/installtypes.h>

#include "procrectypes.h"

extern int no_error_jump;

extern where nowhere;
extern void adjust_to_size(int,int,int,int,int);

extern makeans make_code(exp , space , where , int);
extern prop notbranch[];
extern prop combranch[];
extern int regfrmdest(where *,space);

#define cbranch(x)(combranch[x])
#define obranch(x)(notbranch[x])

#endif



