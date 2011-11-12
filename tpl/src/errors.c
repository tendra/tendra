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
$Log: errors.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:24  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.3  1994/12/05  10:12:57  currie
 * Extended size of input buffer
 *
 * Revision 1.2  1994/07/21  10:35:59  currie
 * Added banner
 *
***********************************************************************/
#include "config.h"
#include <stdarg.h>
#include "util.h"
#include "streams.h"
#include "errors.h"
#include "defs.h"


void
fail(char *s, ...)
    /*VARARGS*/
{
	char c;
	va_list args;
	FILE *f = stderr;
	va_start(args, s);
	IGNORE fprintf(f, "Error: ");
	IGNORE vfprintf(f, s, args);
	c = buff[bind];
	buff[bind] = 0;
	IGNORE fprintf(f, ", %s, line %ld.\n", file_name, cLINE);
	IGNORE fprintf(f, "    %s!!!!", buff);
	buff[bind] = c;
	IGNORE fprintf(f, "%s\n", buff + bind);
	va_end(args);
	exit(EXIT_FAILURE);
}

void
assert_sort(unsigned x)
{
	unsigned y = current_TDF->sort;
	if (y != x) {
		fail("Sort error: req = %u, curr = %u", x, y);
	}
	return;
}


void
assert_sort_or_empty(unsigned x)
{
	unsigned y = current_TDF->sort;
	if (current_TDF->no != 0 && y != x) {
		fail("Sort/list error: req = %u, curr = %u", x, y);
	}
	return;
}
