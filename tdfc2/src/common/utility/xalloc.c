/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include <limits.h>

#include "config.h"

#include "c_types.h"
#include "error.h"
#include "char.h"
#include "ustring.h"
#include "xalloc.h"


/*
    All the program's memory allocation is through the routines defined in
    this file.  This routine allocates sz bytes of memory.
*/

gen_ptr
xmalloc(gen_size sz)
{
	gen_ptr p;
	if (sz == 0) {
		sz = 1;
	}
	p = malloc((size_t)sz);
	if (p == NULL) {
		max_errors = ULONG_MAX;
		error(ERROR_INTERNAL, "Memory allocation error");
		term_error(1);
	}
	return p;
}


/*
    This routine reallocates the block of memory p to contain sz bytes.
    p can be the result of a previous memory allocation routine, or NULL.
*/

gen_ptr
xrealloc(gen_ptr p, gen_size sz)
{
	gen_ptr q;
	if (sz == 0) {
		sz = 1;
	}
	if (p) {
		q = realloc(p,(size_t)sz);
	} else {
		q = malloc((size_t)sz);
	}
	if (q == NULL) {
		max_errors = ULONG_MAX;
		error(ERROR_INTERNAL, "Memory allocation error");
		term_error(1);
	}
	return q;
}


/*
    This routine frees the block of memory p.  p can be the result of a
    previous memory allocation routine, or NULL.
*/

void
xfree(gen_ptr p)
{
	if (p) {
		free(p);
	}
	return;
}


/*
    This buffer is used in the allocation of small strings.
*/

static gen_size chars_left = 0;
static string chars_free = NULL;


/*
    This routine allocates space for n characters.  The memory allocation
    is buffered except for very long strings.
*/

string
xustr(gen_size n)
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
xufree(string s, gen_size n)
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
xustrncpy(string s, gen_size n)
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
	gen_size n;
	if (s == NULL) {
		return NULL;
	}
	n = (gen_size)ustrlen(s);
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
	gen_size n, m;
	if (s == NULL) {
		return xustrcpy(t);
	}
	if (t == NULL) {
		return xustrcpy(s);
	}
	n = (gen_size)ustrlen(s);
	m = n + (gen_size)ustrlen(t) + 1;
	r = xustr(m);
	ustrcpy_v(r, s);
	ustrcpy_v(r + n, t);
	return r;
}


/*
    This routine copies n characters from t to s.
*/

void
xumemcpy(string s, string t, gen_size n)
{
	if (n) {
		memcpy_v((gen_ptr)s, (gen_ptr)t, (size_t)n);
	}
	return;
}


/*
    This routine compares the n characters given by s and t.
*/

int
xumemcmp(string s, string t, gen_size n)
{
	if (s == t || n == 0) {
		return 0;
	}
	return memcmp((gen_ptr)s,(gen_ptr)t,(size_t)n);
}
