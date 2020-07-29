/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* handle_sregs.h
*/



extern int floatdump;
extern int fixdump;

extern int dumpstart;
extern int fldumpstart;

extern int fixdone;
extern int fltdone;

extern  void restore_sregs(unsigned int,unsigned int);
extern  void dump_sregs(unsigned int, unsigned int);

extern void dump_all_sregs(void);
