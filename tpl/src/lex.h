/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:57:22 $
$Revision: 1.1.1.1 $
$Log: lex.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:22  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1995/08/21  16:00:57  currie
 * put <stdlib> at top of headers
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.2  1994/07/21  10:36:31  currie
 * Added banner
 *
***********************************************************************/
#ifndef LEX_INCLUDED
#define LEX_INCLUDED

#include "defs.h"

extern LEX reader(void);
extern char *fformat(char *s, int l);
extern void skip_term(int);
extern FILE *in_file;

#endif
