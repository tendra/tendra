/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef STAB_CONF_INCLUDED
#define STAB_CONF_INCLUDED

#ifdef NEWDIAGS
#include <newdiag/dg_first.h>
#else
#include <diag/dg_first.h>
#include <diag/diaginfo.h>
#endif

#ifndef NEWDIAGS

typedef long OUTPUT_REC ;
typedef diag_descriptor diag_global ;

#define INSPECT_FILENAME( x )   stab_collect_files ( x )
#define NEW_DIAG_GLOBAL( x )    ( x )
#define OUTPUT_DIAG_TAGS()      stab_tagdefs ()
#define OUTPUT_GLOBALS_TAB()    stab_typedefs ()

#define DIAG_VAL_BEGIN(d,g,c,s,e)       \
                                stab_global (d, e, s, g);
#define DIAG_VAL_END(d)         
#define DIAG_PROC_BEGIN(d,g,c,s,e)      \
                                stab_proc (d, e, s, g);
#define DIAG_PROC_END(d)
#define CODE_DIAG_INFO(d,n,x,a) code_diag_info (d, n, x, a);

#else

#define DIAG_VAL_BEGIN(d,g,c,s,e)	if (diag != DIAG_DWARF2)\
				  stab_global(d, e, s, g);

#define DIAG_VAL_END(d)

#define DIAG_PROC_BEGIN(d,g,c,s,e) if (diag == DIAG_DWARF2)\
				  dw2_proc_start(e, d);\
				else \
				  stab_proc(d, e, s, g);

#define DIAG_PROC_END(e)	if (diag == DIAG_DWARF2)\
				  dw2_proc_end(e);\
				else \
				  stab_proc_end();

#define CODE_DIAG_INFO(d,n,x,a)	if (diag == DIAG_DWARF2)\
				  dw2_code_info(d, x, a);\
				else \
				  code_diag_info(d, x, a);


#define START_BB()		if (diag == DIAG_DWARF2)\
				  dw2_start_basic_block();
#endif

#endif /* STAB_CONF_INCLUDED */

