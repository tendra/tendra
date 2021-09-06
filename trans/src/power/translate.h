/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TRANSLATDECS_H
#define TRANSLATDECS_H

#include <construct/installtypes.h>

void translate_capsule(void);
baseoff find_tag(char *);

extern dec * diag_def;
extern dec **main_globals;
extern int maxfix_tregs;		/* the number of t regs allocatable */
extern bool done_scan;

#endif
