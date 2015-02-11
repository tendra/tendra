/* $Id: driver.h 3277 2014-05-29 16:16:15Z kate $ */

/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MAIN_PRINT_H
#define MAIN_PRINT_H

void
asm_file(FILE *f);

void
asm_fprintf(FILE *f, const char *fmt, ...);

void
asm_printf(const char *fmt, ...);

void
asm_fprintop(FILE *f, const char *fmt, ...);

void
asm_printop(const char *fmt, ...);

void
asm_flabel(FILE *f, const char *fmt, ...);

void
asm_label(const char *fmt, ...);

void
asm_fcommentln(FILE *f, const char *fmt, ...);

void
asm_commentln(const char *fmt, ...);

void
asm_fcomment(FILE *f, const char *fmt, ...);

void
asm_comment(const char *fmt, ...);

#endif

