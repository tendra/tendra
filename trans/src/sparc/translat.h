/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TRANSLAT_INCLUDED
#define TRANSLAT_INCLUDED

#include "addrtypes.h"
#include <local/localtypes.h>

extern int optim_level;
extern int g_reg_max;
extern int maxfix_tregs;
extern int sysV_assembler;

extern dec *diag_def;
extern dec **main_globals;

enum section {
    no_section = 0,
    data_section,
    text_section,
    rodata_section,
    init_section
};
extern int local_reg;
extern int callee_start_reg;
extern int callee_end_reg;
extern int caller_offset_used;
extern enum section current_section;
extern ash ashof(shape);
extern void init_translator(void);
extern void exit_translator(void);
extern void insection(enum section);
extern void mark_unaliased(exp);
extern void translate_capsule(void);
extern void translate_tagdef(void);
extern void translate_unit(void);
extern baseoff find_tag(char *);


#endif /* TRANSLAT_INCLUDED */
