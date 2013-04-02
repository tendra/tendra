/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SCAN2_H
#define SCAN2_H

#include "exptypes.h"

int scan2(int sto, exp to, exp e, int usereg0);
void check_asm_seq(exp e, int ext);

#endif /* SCAN2_H */
