/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:57:24 $
$Revision: 1.1.1.1 $
$Log: includes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:24  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.3  1994/12/05  10:13:01  currie
 * Extended size of input buffer
 *
 * Revision 1.2  1994/07/21  10:36:18  currie
 * Added banner
 *
***********************************************************************/
#ifndef INCLUDES_INCLUDED
#define INCLUDES_INCLUDED


extern char *file_name;

typedef struct Path_struct{
	char *name;
	struct Path_struct *next;
} Path;

extern void init_includes(void);
extern void add_include(char *);
extern FILE *open_include(char *);


#endif
