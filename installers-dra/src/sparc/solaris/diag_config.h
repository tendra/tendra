/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef STAB_CONF_INCLUDED
#define STAB_CONF_INCLUDED

#include "config.h"

#include "dg_first.h"
#include "diaginfo.h"
#include "exptypes.h"

typedef long OUTPUT_REC;

#ifdef NEWDIAGS

extern int dwarf2;
extern void dw2_proc_start(exp p, dg_name d);
extern void dw2_proc_end(exp p);
extern void dw2_code_info(dg_info d, void(*mcode)(void *), void * args);
extern void dw2_start_basic_block(void);


#define DIAG_VAL_BEGIN(d,g,c,s,e)	if (!dwarf2)\
				  stab_global(d, e, s, g);

#define DIAG_VAL_END(d)

#define DIAG_PROC_BEGIN(d,g,c,s,e) if (dwarf2)\
				  dw2_proc_start(e, d);\
				else \
				  stab_proc(d, e, s, g);

#define DIAG_PROC_END(e)	if (dwarf2)\
				  dw2_proc_end(e);\
				else \
				  stab_proc_end();

#define CODE_DIAG_INFO(d,n,x,a)	if (dwarf2)\
				  dw2_code_info(d, x, a);\
				else \
				  code_diag_info(d, x, a);


#define START_BB()		if (dwarf2)\
				  dw2_start_basic_block();


#else

#define DIAG_VAL_BEGIN(d,g,c,s,e)	stab_global(d, e, s, g);

#define DIAG_VAL_END(d)	;

#define DIAG_PROC_BEGIN(d,g,c,s,e)	stab_proc(d, e, s, g);

#define DIAG_PROC_END(e);


#define INSPECT_FILENAME(x)	stab_collect_files(x)
#define NEW_DIAG_GLOBAL(x)	(x)
#define OUTPUT_DIAG_TAGS()	stab_tagdefs()
#define OUTPUT_GLOBALS_TAB()	stab_typedefs()

#endif


#endif /* STAB_CONF_INCLUDED */
