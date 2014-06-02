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

#include <reader/exptypes.h>

#include <construct/installtypes.h>

#include "procrectypes.h"

extern where nowhere;
extern void adjust_to_size(int,int,int,int,int);

extern makeans make_code(exp , space , where , int);
extern prop notbranch[];
extern prop combranch[];
extern int regfrmdest(where *,space);
extern freg fregfrmdest(bool,where *, space);
#define cbranch(x)(combranch[x])
#define obranch(x)(notbranch[x])
#endif /* makecodedecs.h */



