/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/xalloc.h>

#include "list.h"
#include "environ.h"
#include "flags.h"
#include "main.h"
#include "options.h"
#include "suffix.h"
#include "utility.h"


/*
 * PRINT A COMMENT
 *
 * This routine prints the comments (a printf-style string, which may be
 * followed by any number of arguments) to the standard output.
 */
void
comment(int e, char *s, ...)
{
	FILE *f;
	va_list args;

	va_start(args, s);
	f = (e ? stdout : stderr);
	IGNORE fflush(f);
	IGNORE vfprintf(f, s, args);
	IGNORE fflush(f);
	va_end(args);
}


/*
 * ALLOCATE SPACE FOR A STRING
 *
 * This routine allocates n characters of memory for use in the string memory
 * allocation routines.
 */
/* TODO: this is an unneccessary optimisation */
static char *
string_alloc(int n)
{
	char *r;
	if (n >= 1000) {
		/* Long strings are allocated space by alloc_nof */
		r = xmalloc_nof(char, n);
	} else {
		/* Short strings are allocated space from a buffer */
		static int no_free;
		static char *free_chars;

		no_free = 0;
		free_chars = NULL;
		if (n >= no_free) {
			no_free = 4000;
			free_chars = xmalloc_nof(char, no_free);
		}
		r = free_chars;
		no_free -= n;
		free_chars += n;
	}

	return r;
}


/*	
 * APPEND TWO STRINGS	
 *   
 * This routine allocates space for a copy of the string s followed by a copy
 * of the string t and concatenates the strings into this space, placing the
 * delimiter character between them. The copy is returned.  E.g.,:	
 *   
 * Given:    "foo" + "bar" + ':'	
 * Returns:  "foo:bar"	
 */	
 	 	
char *	
string_append(const char *s, const char *t, char delimeter)	
{	
	int n = (int)strlen(s);	
	int m = (int)strlen(t);	
	char *r = string_alloc(n + m + 2);	
	IGNORE strcpy(r, s);	
	*(r + n) = delimeter;	
	IGNORE strcpy(r + n + 1, t);	
	return r;
}


/*
 * TEMPORARY WORK SPACE
 *
 * This variable gives a temporary work space of size buffer_size (see
 * utility.h) which is used as a scratch work area.
 */
char *buffer;
