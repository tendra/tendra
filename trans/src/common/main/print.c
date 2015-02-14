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

const char *margin = "\t"; /* left indent before instructions */
const char *fringe = "\t"; /* after code, before trailing comments */

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

static void
asm_vfprintop(FILE *f, const char *fmt, va_list ap)
{
	asm_printf("%s", margin);

	asm_vfprintf(f, fmt, ap);

	asm_printf("\n");
}

void
asm_fprintop(FILE *f, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	asm_vfprintop(f, fmt, ap);
	va_end(ap);
}

void
asm_printop(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	asm_vfprintop(file, fmt, ap);
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
asm_vfcomment(FILE *f, const char *m, const char *fmt, va_list ap)
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

	if (!do_comment) {
		return;
	}

	asm_fprintf(f, "%s%c ", m, c);

	asm_vfprintf(f, fmt, ap);

	asm_fprintf(f, "\n");
}

void
asm_fcommentln(FILE *f, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	asm_vfcomment(f, margin, fmt, ap);
	va_end(ap);
}

void
asm_commentln(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	asm_vfcomment(file, margin, fmt, ap);
	va_end(ap);
}

void
asm_fcomment(FILE *f, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	asm_vfcomment(f, fringe, fmt, ap);
	va_end(ap);
}

void
asm_comment(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	asm_vfcomment(file, fringe, fmt, ap);
	va_end(ap);
}

void
asm_ferror(FILE *f)
{
	asm_fprintf(f, "\n");
	asm_fprintf(f, "error\n");
}

void
asm_error(void)
{
	asm_ferror(file);
}

