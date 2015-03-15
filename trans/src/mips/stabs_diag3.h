/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MIPSDGDECS
#define MIPSDGDECS

#include <reader/exp.h>

#include <diag3/diagtypes.h>

extern int nofds;
extern int current_file;		/* dense no of current source file */
extern  void stab_types(void);	/* aux entries for types  */
extern long currentlno;


extern long find_aux(diag_type s /* struct or union shape */ );
extern void symnosforfiles(void);
extern int find_file(const char *);

#endif
