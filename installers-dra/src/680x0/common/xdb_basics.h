/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
			    VERSION INFORMATION
			    ===================
--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/xdb_basics.h,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: xdb_basics.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:43:02  ma
First version.
Revision 1.1.1.1  1997/03/14 07:50:23  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:57:01  john
 *
 * Revision 1.2  1996/07/05  14:35:27  john
 * Fix to diagnostics
 *
 * Revision 1.1  95/03/08  16:46:22  ra
 * Added missing files.
 *
 * Revision 1.1  93/02/22  17:17:22  17:17:22  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#ifndef XDB_BASICS_INCLUDED
#define XDB_BASICS_INCLUDED

#include "config.h"

#include "dg_first.h"
#include "diaginfo.h"

extern void diag_prologue(void);
extern void diag_epilogue(void);
extern void diag_start(diag_info *, exp);
extern void diag_end(diag_info *, exp);
extern void xdb_diag_proc_begin(diag_global *, exp, char *, long, int);
extern void xdb_diag_proc_return(void);
extern void xdb_diag_proc_end(diag_global *);
extern void xdb_diag_val_begin(diag_global *, char *, long, int);
extern dec *sort_decs(dec *);
extern void OUTPUT_GLOBALS_TAB(void);
extern void OUTPUT_DIAG_TAGS(void);
extern void INSPECT_FILENAME(filename);

#endif
