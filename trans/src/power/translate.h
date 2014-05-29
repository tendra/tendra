/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TRANSLATDECS_H
#define TRANSLATDECS_H

#include <stdio.h>

#include <construct/installtypes.h>

#include "codegen.h"

extern dec * diag_def;

extern FILE *as_file;			/* assembler output file */

dec **main_globals;			/* the globals decs array */

extern int maxfix_tregs;		/* the number of t regs allocatable */

extern void translate_capsule(void);
extern baseoff find_tg(char *);
extern bool done_scan;

#endif
