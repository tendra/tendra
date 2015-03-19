/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SHARED_STRING_H
#define SHARED_STRING_H

#define streq(a, b)     (strcmp ((a), (b))      == 0)
#define strneq(a, b, n) (strncmp((a), (b), (n)) == 0)

char *xstrdup(const char *);
char *xstrldup(const char *s, size_t l);
char *xstrcat(const char *, const char *);

#endif

