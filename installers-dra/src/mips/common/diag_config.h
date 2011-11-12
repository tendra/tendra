/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:05 $
$Revision: 1.1.1.1 $
$Log: diag_config.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/09/12  10:59:15  currie
 * gcc pedanttry
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
#ifndef diag_config_key
#define diag_config_key

extern void collect_files(filename);
#define INSPECT_FILENAME(fn)collect_files(fn)


typedef void *OUTPUT_REC;
typedef diag_descriptor  diag_global;
#define OUTPUT_GLOBALS_TAB()
extern void OUTPUT_DIAG_TAGS(void);
#define NEW_DIAG_GLOBAL(x)x


#endif
