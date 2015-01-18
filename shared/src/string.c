/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <shared/string.h>
#include <shared/xalloc.h>


char *
xstrdup(const char *s1)
{
	size_t len;
	char *s2;

	len = strlen(s1) + 1;
	s2 = xmalloc(len);
	(void) strcpy(s2, s1);

	return s2;
}

/*
 * This routine allocates space for n characters.  The memory allocation
 * is buffered except for very long strings.
 */
char *
xstr(size_t n)
{
	char *r;

	if (n >= 1000) {
		r = xmalloc_nof(char, n);
	} else {
		static size_t chars_left = 0;
		static char *chars_free = 0;

		if (n >= chars_left) {
			chars_left = 5000;
			chars_free = xmalloc_nof(char, chars_left);
		}

		r = chars_free;
		chars_free += n;
		chars_left -= n;
	}

	return r;
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
	r = xstr(m);

	(void) strcpy(r, s);
	(void) strcpy(r + n, t);

	return r;
}
