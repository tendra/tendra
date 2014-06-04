/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <reader/exp.h>

extern int freeregs(long);
#define freefregs(rmask)		freeregs(rmask)

extern int getreg(long);
extern int getfreg(long);

extern void settempregs(exp);

extern int next_creg(void);
