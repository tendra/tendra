/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef TEMP_H
#define TEMP_H

#include <stdio.h>

extern const char *temp_mkdir(const char *, const char *);
extern FILE *temp_fopen(char *buf, size_t bufsz,
	const char *name, const char *mode);

#endif

