/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdarg.h>

#include <shared/check.h>

#include "config.h"

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
