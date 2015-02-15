/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <shared/check.h>
#include <shared/string.h>
#include <shared/xalloc.h>


char *
xstrdup(const char *s1)
{
	size_t len;
	char *s2;

	len = strlen(s1) + 1;
	s2 = xmalloc(len);
	IGNORE strcpy(s2, s1);

	return s2;
}


char *
xstrcat(const char *s, const char *t)
{
	char *r;
	size_t n, m;

	if (s == NULL) return xstrdup(t);
	if (t == NULL) return xstrdup(s);

	n = strlen(s);
	m = n + strlen(t) + 1;
	r = xmalloc(m);

	IGNORE strcpy(r, s);
	IGNORE strcpy(r + n, t);

	return r;
}
