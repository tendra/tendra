/* $Id: driver.h 3277 2014-05-29 16:16:15Z kate $ */

/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MAIN_PRINT_H
#define MAIN_PRINT_H

#include <shared/check.h>

void
asm_file(FILE *f);

void
asm_fprintf(FILE *f, const char *fmt, ...)
	ATTR_FMT(printf, 2, 3);

void
asm_printf(const char *fmt, ...)
	ATTR_FMT(printf, 1, 2);

void
asm_fprintop(FILE *f, const char *fmt, ...)
	ATTR_FMT(printf, 2, 3);

void
asm_printop(const char *fmt, ...)
	ATTR_FMT(printf, 1, 2);

void
asm_flabel(FILE *f, const char *fmt, ...)
	ATTR_FMT(printf, 2, 3);

void
asm_label(const char *fmt, ...)
	ATTR_FMT(printf, 1, 2);

void
asm_fcommentln(FILE *f, const char *fmt, ...)
	ATTR_FMT(printf, 2, 3);

void
asm_commentln(const char *fmt, ...)
	ATTR_FMT(printf, 1, 2);

void
asm_fcomment(FILE *f, const char *fmt, ...)
	ATTR_FMT(printf, 2, 3);

void
asm_comment(const char *fmt, ...)
	ATTR_FMT(printf, 1, 2);

void
asm_ferror(FILE *f);

void
asm_error(void);

#endif

