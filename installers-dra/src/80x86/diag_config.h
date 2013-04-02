/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef diag_config_key
#define diag_config_key

#ifdef NEWDIAGS
#include <newdiag/dg_first.h>
#else
#include <diag/diagtypes1.h>
#endif

#define STABS

#ifndef NEWDIAGS

typedef long OUTPUT_REC;
typedef diag_descriptor diag_global;

#define INSPECT_FILENAME(x)     stab_collect_files(x)
#define NEW_DIAG_GLOBAL(x)      (x)
#define OUTPUT_DIAG_TAGS()      stab_tagdefs()
#define OUTPUT_GLOBALS_TAB()    stab_typedefs()

extern void stab_collect_files(filename f);
extern void stab_tagdefs(void);
extern void stab_typedefs(void);
extern void init_stab_aux(void);

#else

#include "exptypes.h"

extern void dw2_proc_start(exp p, dg_name d);
extern void dw2_proc_end(exp p);
extern void dw2_code_info(dg_info d, void(*mcode)(void *), void * args);
extern void dw2_start_basic_block(void);

extern void code_diag_info(diag_info *d, void(*mcode)(void *), void * args);
extern void out_diag_global(dg_name di, int global, int cname, char* pname);
extern void diag_proc_begin(dg_name di, int global, int cname, char* pname);
extern void diag_proc_end(void);



#define DIAG_VAL_BEGIN(d,g,c,s)	if (diag != DIAG_DWARF2)\
				  out_diag_global(d, g, c, s);

#define DIAG_VAL_END(d)

#define DIAG_PROC_BEGIN(d,g,c,s,p) if (diag == DIAG_DWARF2)\
				     dw2_proc_start(p, d);\
				   else \
				     diag_proc_begin(d, g, c, s);

#define DIAG_PROC_END(d,p)	if (diag == DIAG_DWARF2)\
				  dw2_proc_end(p);\
				else \
				  diag_proc_end();

#define CODE_DIAG_INFO(d,n,x,a)	if (diag == DIAG_DWARF2)\
				  dw2_code_info(d, x, a);\
				else \
				  code_diag_info(d, x, a);


#define START_BB()		if (diag == DIAG_DWARF2)\
				  dw2_start_basic_block();

#endif

#endif

