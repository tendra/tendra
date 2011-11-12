/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* sol86/diag_config.h */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: diag_config.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.9  1998/01/09  14:47:46  pwe
 * prep restructure
 *
 * Revision 1.8  1997/10/23  09:37:26  pwe
 * extra_diags
 *
 * Revision 1.7  1997/08/23  13:46:01  pwe
 * initial ANDF-DE
 *
 * Revision 1.6  1997/04/02  10:33:40  pwe
 * diagnose pl_tests
 *
 * Revision 1.5  1997/03/20  16:24:32  pwe
 * dwarf2
 *
 * Revision 1.4  1995/03/17  18:31:25  pwe
 * stabs diagnostics for solaris and linux
 *
 * Revision 1.3  1995/01/30  12:57:35  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.2  1994/07/13  07:46:54  jmf
 * Added Log
 *
**********************************************************************/

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
