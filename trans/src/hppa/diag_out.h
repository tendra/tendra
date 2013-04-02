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
#include <diag/dg_first.h>
#include <diag/diaginfo.h>
#include "exptypes.h"

extern void init_stab(void);
extern void init_stab_aux(void);
extern void stab_collect_files(filename);
extern void stab_tagdefs(void);
extern void stab_typedefs(void);
extern void stab_begin(diag_info *, int, exp);

extern void init_stab_aux(void);
extern void init_diag(void);
extern void stab_file(long, bool);
extern void stabn(long, long);
extern long diagbr_open(long);
extern void diagbr_close(long);
extern void stab_types(void);
extern void stab_global(shape, char *, bool);
extern void stab_proc(exp, char *, bool);
extern void stab_local(char *, diag_type, exp, long, long);
extern void close_function_scope(int);
extern long currentfile;
extern void stab_end(diag_info*, exp);
#ifdef _SYMTAB_INCLUDED
extern void output_DEBUG(void);
#endif
#endif /* HPPADDECS_INCLUDED */
