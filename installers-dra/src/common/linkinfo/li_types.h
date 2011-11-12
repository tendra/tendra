/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:48 $
$Revision: 1.1.1.1 $
$Log: li_types.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:48  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:43:17  currie
 * Initial revision
 *
***********************************************************************/
#ifndef li_types_key
#define li_types_key 1



typedef int linkinfo;
typedef int linkinfo_list;

typedef struct weak_cell_t {
	char *weak_id;
	char *val_id;
	struct weak_cell_t *next;
} weak_cell;

#endif
