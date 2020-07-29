/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEX_INCLUDED
#define LEX_INCLUDED

#include "defs.h"

extern LEX reader(void);
extern char *fformat(char *s, int l);
extern void skip_term(int);
extern FILE *in_file;

#endif
