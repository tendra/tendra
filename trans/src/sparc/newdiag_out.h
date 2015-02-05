/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SPARCDDECS_INCLUDED
#define SPARCDDECS_INCLUDED

#include <diag4/dg_first.h>

#include <reader/exp.h>

#include <construct/installtypes.h>

extern void init_stab(void);
extern void init_stab_aux(void);
extern void code_diag_info(dg_info, void(*)(void *), void *);
extern void stab_global(dg_name, exp, char *, int);
extern void stab_proc(dg_name, exp, char *, int);
extern void stab_proc_end(void);
extern void stab_types(void);

#endif /* SPARCDDECS_INCLUDED */
