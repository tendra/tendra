/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MULDVREMDECS_H
#define MULDVREMDECS_H

#include <local/exptypes.h>

#include <construct/installtypes.h>

#include "memtdf.h"
#include "procrectypes.h"


extern needs multneeds(exp *, exp **);
extern needs divneeds(exp *, exp **);
extern needs remneeds(exp *, exp **);

extern int do_mul_comm_op(exp , space , where , bool);
extern int do_div_op(exp, space , where , bool);
extern int do_rem_op(exp , space, where , bool);

#endif /* muldvremdecs.h */
