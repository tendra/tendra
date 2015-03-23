/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <limits.h>
#include <string.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/ustring.h>
#include <utility/xalloc.h>

#include <parse/char.h>


/*
    This buffer is used in the allocation of small strings.
*/

static size_t chars_left = 0;
static string chars_free = NULL;


/*
    This routine allocates space for n characters.  The memory allocation
    is buffered except for very long strings.
*/

string
xustr(size_t n)
{
	string r;
	if (n < 1000) {
		/* Small strings */
		if (n >= chars_left) {
			chars_left = 5000;
			chars_free = xmalloc_nof(character, chars_left);
		}
		r = chars_free;
		chars_free += n;
		chars_left -= n;
	} else {
		/* Large strings */
		r = xmalloc_nof(character, n);
	}
	return r;
}


/*
    This routine frees the space allocated by a previous call to xustr.
    For small strings the memory is only freed for the last call to xustr.
*/

void
xufree(string s, size_t n)
{
	if (s) {
		if (n < 1000) {
			/* Small strings */
			if (s + n == chars_free) {
				chars_free = s;
				chars_left += n;
			}
		} else {
			/* Large strings */
			xfree_nof(s);
		}
	}
	return;
}


/*
    This routine allocates space for a persistent copy of the string s
    of length n.  There is only one copy of each small string, otherwise
    xustr is used to allocate the space.
*/

string
xustrncpy(string s, size_t n)
{
	string r;
	if (n < 2) {
		/* Small strings */
		static character buff[NO_CHAR][2];
		int c = (int)s[0];
		if (c < NO_CHAR) {
			r = buff[c];
			r[0] = (character)c;
			r[1] = 0;
			return r;
		}
	}
	/* Large strings */
	r = xustr(n + 1);
	ustrcpy_v(r, s);
	return r;
}


/*
    This routine allocates space for a persistent copy of the string s.
*/

string
xustrcpy(string s)
{
	size_t n;
	if (s == NULL) {
		return NULL;
	}
	n = ustrlen(s);
	return xustrncpy(s, n);
}


/*
    This routine allocates space for a persistent copy of the string s
    followed by the string t.  The memory is allocated using xustr.
*/

string
xustrcat(string s, string t)
{
	string r;
	size_t n, m;
	if (s == NULL) {
		return xustrcpy(t);
	}
	if (t == NULL) {
		return xustrcpy(s);
	}
	n = ustrlen(s);
	m = n + ustrlen(t) + 1;
	r = xustr(m);
	ustrcpy_v(r, s);
	ustrcpy_v(r + n, t);
	return r;
}


/*
    This routine copies n characters from t to s.
*/

void
xumemcpy(string s, string t, size_t n)
{
	if (n) {
		memcpy_v(s, t, n);
	}
	return;
}


/*
    This routine compares the n characters given by s and t.
*/

int
xumemcmp(string s, string t, size_t n)
{
	if (s == t || n == 0) {
		return 0;
	}
	return memcmp(s, t, n);
}
