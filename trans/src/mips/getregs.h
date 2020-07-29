/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* getregdecs.h
    routines for grabbing registers
*/

#include <reader/exp.h>

extern int  getreg(long fixed);
extern int  getfreg(long fl);
extern  void settempregs(exp tag);
