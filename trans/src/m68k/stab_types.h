/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef STAB_TYPES_INCLUDED
#define STAB_TYPES_INCLUDED

extern void make_stabs(char *, int, long, mach_op *);
extern void make_stabn(int, long);
extern void init_stab_types(void);
extern char * analyse_stab_type(diag_type, char *, char *);

#endif
