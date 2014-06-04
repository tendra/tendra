/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MAIN_H
#define MAIN_H

#include <construct/installtypes.h>

extern int majorno;
extern int minorno;

extern long currentfile;	/* our source fileno 0.. */
extern long mainfile;		/* would be best if it actually contained main! */
extern dec** main_globals;

#endif

