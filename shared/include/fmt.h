/* $Id$ */

/*
 * Copyright 2008-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SHARED_FMT_H
#define SHARED_FMT_H

#include <stdarg.h>

void vefprintf(FILE *fp, const char *fmt, va_list ap);
void efprintf(FILE *fp, const char *fmt, ...);

#endif

