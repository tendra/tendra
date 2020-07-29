/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SCAN_H
#define SCAN_H

#include <reader/exp.h>

int scan(int sto, exp to, exp e, int usereg0);
void check_asm_seq(exp e, int ext);

#endif /* SCAN2_H */
