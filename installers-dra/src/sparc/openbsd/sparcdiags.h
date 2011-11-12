/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */




/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/solaris/sparcdiags.h,v 1.1.1.1 1998/01/17 15:55:53 release Exp $
--------------------------------------------------------------------------
$Log: sparcdiags.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1998/01/09  15:00:08  pwe
 * prep restructure
 *
 * Revision 1.2  1997/04/04  15:23:38  pwe
 * tidy re old DWARF interface
 *
 * Revision 1.1  1997/03/24  17:10:00  pwe
 * reorganise solaris/sunos split
 *
 * Revision 1.1.1.1  1995/03/13  10:18:55  john
 * Entered into CVS
 *
 * Revision 1.3  1994/07/04  09:24:54  djch
 * Jun94 tape version
 *
 * Revision 1.2  1994/07/04  08:35:54  djch
 * extra param to stabd
 *
 * Revision 1.1  1994/05/03  14:50:40  djch
 * Initial revision
 *
 * Revision 1.3  93/07/05  18:26:02  18:26:02  ra (Robert Andrews)
 * Include diag_fns.h for DWARF.
 *
 * Revision 1.2  93/06/29  14:31:11  14:31:11  ra (Robert Andrews)
 * Minor renaming of diagnostic routines.
 *
 * Revision 1.1  93/06/24  14:59:20  14:59:20  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef SPARCDDECS_INCLUDED
#define SPARCDDECS_INCLUDED

#include "config.h"

#include "dg_first.h"
#include "diaginfo.h"

#include "exptypes.h"
#include "installtypes.h"

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
