/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef STRING_INCLUDED
#define STRING_INCLUDED

#include <stddef.h>

char *xstrdup(const char *);
char *xstr(size_t);
char *xstrcat(const char *, const char *);

#endif
