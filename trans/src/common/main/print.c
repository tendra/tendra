/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include <shared/check.h>
#include <shared/error.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

static FILE *file;

void
asm_file(FILE *f)
{
	assert(file == NULL && f != NULL);

	file = f;
}

static void
asm_vfprintf(FILE *f, const char *fmt, va_list ap)
{
	int r;

	assert(file != NULL);
	assert(fmt != NULL);

#if defined(TRANS_x86)
	if (f == file) {
		const char *p;

		for (p = fmt; *p != '\0'; p++) {
			if (*p == '\n') {
				out_hook_nl();
				break;
			}
		}
	}
#endif

	r = vfprintf(f, fmt, ap);
	if (r == -1) {
		error(ERROR_FATAL, "vfprintf: %s", strerror(errno));
	}
}

void
asm_fprintf(FILE *f, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	asm_vfprintf(f, fmt, ap);
	va_end(ap);
}

void
asm_printf(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	asm_vfprintf(file, fmt, ap);
	va_end(ap);
}

void
asm_fprintop(FILE *f, const char *fmt, ...)
{
	va_list ap;

	asm_printf("\t");

	va_start(ap, fmt);
	asm_vfprintf(f, fmt, ap);
	va_end(ap);

	asm_printf("\n");
}

void
asm_printop(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	asm_fprintop(file, fmt, ap);
	va_end(ap);
}

static void
asm_vflabel(FILE *f, const char *fmt, va_list ap)
{
	asm_vfprintf(f, fmt, ap);

	asm_fprintf(f, ":\n");
}

void
asm_flabel(FILE *f, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	asm_vflabel(f, fmt, ap);
	va_end(ap);
}

void
asm_label(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	asm_vflabel(file, fmt, ap);
	va_end(ap);
}

static void
asm_vfcommentln(FILE *f, const char *fmt, va_list ap)
{
	char c;

	switch (assembler) {
	case ASM_HP:     c = '!'; break;
	case ASM_SUN:    c = '/'; break;
	case ASM_GAS:    c = '#'; break;
	case ASM_OSF1:   c = '#'; break;
	case ASM_SGI:    c = '#'; break;
	case ASM_ULTRIX: c = '#'; break;
	case ASM_IBM:    c = '#'; break;

	default:
		error(ERROR_SERIOUS, "unsupported assembler dialect");
	}

	asm_fprintf(f, "%c ", c);

	asm_vfprintf(f, fmt, ap);

	asm_fprintf(f, "\n");
}

void
asm_fcommentln(FILE *f, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	asm_vfcommentln(f, fmt, ap);
	va_end(ap);
}

void
asm_commentln(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	asm_vfcommentln(file, fmt, ap);
	va_end(ap);
}

static void
asm_vfcomment(FILE *f, const char *fmt, va_list ap)
{
	asm_fprintf(f, "\t");

	asm_vfcommentln(f, fmt, ap);
}

void
asm_fcomment(FILE *f, const char *fmt, ...)
{
	va_list ap;

	asm_fprintf(f, "\t");

	va_start(ap, fmt);
	asm_vfcommentln(f, fmt, ap);
	va_end(ap);
}

void
asm_comment(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	asm_vfcomment(file, fmt, ap);
	va_end(ap);
}

