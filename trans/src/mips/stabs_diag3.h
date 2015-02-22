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
extern int *file_dnos;		/* dense nos for files */
extern int current_file;		/* dense no of current source file */
extern void stab_local(char *nm, diag_type dt, exp id, long disp, long findex);
 /* entry for local */
extern  void stab_types(void);	/* aux entries for types  */
extern long currentlno;


extern long find_aux(diag_type s /* struct or union shape */ );
extern void symnosforfiles(void);
extern int find_file(char*);

#endif
