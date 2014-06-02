/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef REG_RECORD_H
#define REG_RECORD_H

#include <reader/exptypes.h>

extern reg_record crt_reg_record;

void clear_reg_record(regcell * s);
void clear_low_reg_record(regcell * s);
void invalidate_dest(where dest);
void move_reg(where from, where to, shape sha);
where equiv_reg(where w, int sz);
int invalidates(exp d, exp r);

#endif /* REG_RECORD_H */
