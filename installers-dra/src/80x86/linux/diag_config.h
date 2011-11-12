/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* linux/diag_config.h */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:52 $
$Revision: 1.1.1.1 $
$Log: diag_config.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/03/17  18:29:49  pwe
 * stabs diagnostics for solaris and linux
 *
 * Revision 1.2  1995/01/30  12:57:13  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1995/01/27  17:25:32  jmf
 * Initial revision
 *
 * Revision 1.2  1994/07/13  07:59:32  jmf
 * Added Log
 *
**********************************************************************/

#ifndef diag_config_key
#define diag_config_key


typedef long OUTPUT_REC;
typedef diag_descriptor diag_global;

#define INSPECT_FILENAME(x)	stab_collect_files(x)
#define NEW_DIAG_GLOBAL(x)	(x)
#define OUTPUT_DIAG_TAGS()	stab_tagdefs()
#define OUTPUT_GLOBALS_TAB()	stab_typedefs()

#define STABS

extern void stab_collect_files(filename f);
extern void stab_tagdefs(void);
extern void stab_typedefs(void);
extern void init_stab_aux(void);

#endif
