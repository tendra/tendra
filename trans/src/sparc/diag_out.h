/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SPARCDDECS_INCLUDED
#define SPARCDDECS_INCLUDED

#ifdef NEWDIAGS
#include <newdiag/dg_first.h>
#else
#include <diag/dg_first.h>
#include <diag/diaginfo.h>
#endif

#include <construct/installtypes.h>
#include <local/exptypes.h>

#ifdef NEWDIAGS

extern void init_stab(void);
extern void init_stab_aux(void);
extern void code_diag_info(dg_info, void(*)(void *), void *);
extern void stab_global(dg_name, exp, char *, int);
extern void stab_proc(dg_name, exp, char *, int);
extern void stab_proc_end(void);
extern void stab_types(void);

#else

extern void init_stab(void);
extern void init_stab_aux(void);
extern void stab_collect_files(filename);
extern void stab_tagdefs(void);
extern void stab_typedefs(void);
extern void stab_begin(diag_info *, int, exp);
extern void stab_end(diag_info *, exp);
extern void stab_file(long, bool);
extern void stab_global(diag_descriptor *, exp, char *, bool);
extern void stab_local(char *, diag_type, exp, long, long);
extern void stab_proc(diag_descriptor *, exp, char *, bool);
extern void stab_proc_end(void);
extern void stab_types(void);
extern void stabd(long, long, int);
extern long currentfile;

#endif

#endif /* SPARCDDECS_INCLUDED */
