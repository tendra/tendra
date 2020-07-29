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
    This routine allocates space for a persistent copy of the string s
    of length n.  There is only one copy of each small string, otherwise
    xmalloc is used to allocate the space.
*/

string
xustrncpy(string s, size_t n)
{
	string r;
	r = xmalloc(n + 1);
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
    followed by the string t.  The memory is allocated using xmalloc.
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
	r = xmalloc(m);
	ustrcpy_v(r, s);
	ustrcpy_v(r + n, t);
	return r;
}

