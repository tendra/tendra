/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EVALDECS_H
#define EVALDECS_H

#include "addrtypes.h"

#include <construct/flpt.h>

extern int next_data_lab(void);

extern mm maxmin(shape);

extern instore evaluated(exp , int);
extern instore evaluated_const(exp);

#endif
