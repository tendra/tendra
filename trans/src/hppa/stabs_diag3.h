/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef HPPADDECS_INCLUDED
#define HPPADDECS_INCLUDED

#include <construct/installtypes.h>
#include <diag3/dg_first.h>
#include <diag3/diaginfo.h>
#include <reader/exp.h>

extern void init_stab(void);
extern void init_stab_aux(void);
extern void stab_begin(diag_info *, int, exp);

extern void init_stab_aux(void);
extern void init_diag(void);
extern void stabn(long, long);
extern void stab_types(void);
extern void close_function_scope(int);
extern long currentfile;
extern void stab_end(diag_info*, exp);
#ifdef _SYMTAB_INCLUDED
extern void output_DEBUG(void);
#endif
#endif /* HPPADDECS_INCLUDED */
