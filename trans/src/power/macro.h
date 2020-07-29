/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MACRO_H
#define MACRO_H

extern char * reg_macro(int);
extern char * freg_macro(int);
extern char * cr_macro(int);
extern char * spr_macro(int);
extern void init_macros(void);
extern int do_macros;

#endif
