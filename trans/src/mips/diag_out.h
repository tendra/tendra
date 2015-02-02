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
extern void collect_files(filename f);
extern int current_file;		/* dense no of current source file */
extern void stab_file(int i);	/* symtab entry for file source file i */
extern void stabd(long findex, long lno);/* .. entry for linenos */
extern void diagbr_open(long findex);/* .. entry for open scope */
extern void diagbr_close(long findex);/* .. entry for close scope */
extern void stab_local(char *nm, diag_type dt, exp id, long disp, long findex);
 /* entry for local */
extern  void stab_types(void);	/* aux entries for types  */
extern long currentlno;


extern long find_aux(diag_type s /* struct or union shape */ );
extern void symnosforfiles(void);
extern int find_file(char*);

#endif
