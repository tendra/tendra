/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef diag_config_key
#define diag_config_key

#include "config.h"

#include "dg_first.h"
#include "diaginfo.h"


typedef long OUTPUT_REC;

#ifdef NEWDIAGS

extern int dwarf2;
extern void dw2_proc_start(exp p, dg_name d);
extern void dw2_proc_end(exp p);
extern void dw2_code_info(dg_info d, void(*mcode)(void *), void * args);
extern void dw2_start_basic_block(void);

extern void code_diag_info(diag_info *d, void(*mcode)(void *), void * args);
extern void out_diag_global(dg_name di, int global, int cname, char* pname);
extern void diag_proc_begin(dg_name di, int global, int cname, char* pname);
extern void diag_proc_end(void);



#define DIAG_VAL_BEGIN(d,g,c,s)	if (!dwarf2)\
				  out_diag_global(d, g, c, s);

#define DIAG_VAL_END(d)

#define DIAG_PROC_BEGIN(d,g,c,s,p) if (dwarf2)\
				     dw2_proc_start(p, d);\
				   else \
				     diag_proc_begin(d, g, c, s);

#define DIAG_PROC_END(d,p)	if (dwarf2)\
				  dw2_proc_end(p);\
				else \
				  diag_proc_end();

#define CODE_DIAG_INFO(d,n,x,a)	if (dwarf2)\
				  dw2_code_info(d, x, a);\
				else \
				  code_diag_info(d, x, a);


#define START_BB()		if (dwarf2)\
				  dw2_start_basic_block();


#else

#define INSPECT_FILENAME(x)	stab_collect_files(x)
#define NEW_DIAG_GLOBAL(x)	(x)
#define OUTPUT_DIAG_TAGS()	stab_tagdefs()
#define OUTPUT_GLOBALS_TAB()	stab_typedefs()

extern void stab_collect_files(dg_filename f);
extern void stab_tagdefs(void);
extern void stab_typedefs(void);

#endif

#define STABS

extern void init_stab_aux(void);

#endif
