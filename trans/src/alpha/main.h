/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

#include <construct/installtypes.h>

extern FILE *as_file;
extern FILE *ba_file;

extern int majorno;
extern int minorno;

extern long currentfile;	/* our source fileno 0.. */
extern long mainfile;		/* would be best if it actually contained main! */
extern dec** main_globals;

#endif

