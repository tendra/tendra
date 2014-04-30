/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SHARED_STRING_H
#define SHARED_STRING_H

#include <stddef.h>

char *xstrdup(const char *);
char *xstr(size_t);
char *xstrcat(const char *, const char *);

#endif

