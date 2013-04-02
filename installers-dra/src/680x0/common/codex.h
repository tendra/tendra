/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CODEX_INCLUDED
#define CODEX_INCLUDED

#include "utility.h"

#include <construct/installtypes.h>

extern int ins(long, int, int, int);
extern int insf(long, int, int, int);
extern void libcall(char *);
extern bool reserved(char *);

extern bitpattern regsinuse;
extern bitpattern regsinproc;
extern bitpattern reuseables;
extern bitpattern regsindec;
extern bitpattern bigregs;
extern long crt_ret_lab;

extern bool used_stack;
extern bool used_ldisp;
extern long max_stack;
extern long extra_stack;
extern long stack_dec;
extern long stack_size;
extern long ldisp;
extern int no_calls;

extern long stack_change;
extern int stack_direction;
extern void add_to_reg(int, long);
extern void dec_stack(long);
extern void update_stack(void);

extern void area(int);
#define  ptext		0
#define  pdata		1
#define  pbss		2
#define  plast		3

extern void profile_hack(void);
extern void cproc(exp, char *, long, int, int, diag_global *);

#endif
