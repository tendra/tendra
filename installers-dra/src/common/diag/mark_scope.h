/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:46 $
$Revision: 1.1.1.1 $
$Log: mark_scope.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1998/01/09  09:30:11  pwe
 * prep restructure
 *
 * Revision 1.1  1995/04/06  10:42:55  currie
 * Initial revision
 *
***********************************************************************/
#ifndef mark_scope_key
#define mark_scope_key 1



extern void mark_scope(exp e);
#ifdef NEWDIAGS
extern int doing_mark_scope;
extern void correct_mark_scope(exp e);
extern void mark_scope2(exp e);
#endif


#endif
