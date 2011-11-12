/* $Id$ */

/*
 * Copyright 2008-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef ERROR_FMT_INCLUDED
#define ERROR_FMT_INCLUDED


#include <stdarg.h>


void vefprintf(FILE *fp, const char *fmt, va_list ap);
void efprintf(FILE *fp, const char *fmt, ...);


#endif /* ERROR_FMT_INCLUDED */
