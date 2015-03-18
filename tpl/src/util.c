/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/xalloc.h>

#include "errors.h"
#include "util.h"


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
