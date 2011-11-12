/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:57:25 $
$Revision: 1.1.1.1 $
$Log: util.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:25  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.2  1994/07/21  10:36:44  currie
 * Added banner
 *
***********************************************************************/

#include "config.h"
#include "errors.h"
#include "util.h"

#include <shared/xalloc.h>


char *
copy_string(char *s)
{
	unsigned i;
	unsigned ls = (unsigned)strlen(s);
	char *res = xcalloc(sizeof *res, ls + 1);
	for (i = 0; i < ls; i++) {
		res[i] = s[i];
	}
	res[ls] = 0;
	return res;
}

char *
append_string(char *a, char *b)
{
	unsigned i;
	unsigned la = (unsigned)strlen(a);
	unsigned lb = (unsigned)strlen(b);
	char *res = xcalloc(sizeof *res, la + lb + 1);
	for (i = 0; i < la; i++) {
		res[i] = a[i];
	}
	for (i = 0; i < lb; i++) {
		res[i + la] = b[i];
	}
	res[la + lb] = 0;
	return res;
}
