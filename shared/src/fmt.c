/* $Id$ */

/*
 * Copyright 2008-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This facility provides an extensible fprintf-like interface. It is intended
 * for outputting error messages with relatively simple formatting strings (for
 * example, no precision specifiers or alternate formats are provided).
 *
 * A set of default formatting specifiers are provided; applications may provide
 * their own, for convenient representation of their own data. This is
 * particularly useful for presenting ADTs in a form recognisable to the user;
 * the motivation for this is to display parsed constructs in their input syntax
 * when highlighting errors in user-input languages.
 *
 * The implementation is not particularly efficient, since error messages do not
 * need to be.
 */

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>

#include <shared/fmt.h>

/*
 * These are callback functions for efprintf(), indexed by an unsigned char.
 */
void (*fmtf[256])(FILE *, void *);

/*
 * Read the precision given by a formatting specifier. This is expected to be
 * passed a pointer to the character after the '.' which begins the precision
 * specificiation. It will consume as many further character as it needs, up to
 * but not including the conversion specifier.
 *
 * A pointer to the conversion specifier is returned. (That is, a pointer to
 * the next character after the precision has been dealt with.)
 */
static const char *
readprecision(const char *p, int *precision)
{
	char *ep;
	long int l;

	assert(p);
	assert(*p != '\0');
	assert(precision != NULL);

	/* no precision; e.g. "%.s" */
	if (!isdigit((unsigned char) *p)) {
		*precision = 0;
		return p;
	}

	/* hardcoded precision; e.g. "%.14s" */
	errno = 0;
	l = strtol(p, &ep, 10);
	assert(ep > p);

	if (ERANGE == errno && (LONG_MAX == l || LONG_MIN == l)) {
		assert(!"precision out of range");
		return ep;
	}

	if (l > INT_MAX || l < INT_MIN) {
		assert(!"precision out of range");
		return ep;
	}

	*precision = (int) l;
	return ep;
}

/*
 * This is an analogue of fprintf, based on the fmt[] callback functions. This
 * provides a mechanism for custom format specifiers which may be registered
 * by fmt_register().
 *
 * The default formatting specifiers provided are a subset of the usual fprintf
 * specifiers. For simplicity only those required have been implemented.
 */
void
vefprintf(FILE *fp, const char *fmt, va_list ap)
{
	const char *p;

	assert(fmt != NULL);

	for (p = fmt; *p != '\0'; p++) {
		int precision = -1;
		int mlong = 0;

		switch (*p) {
		case '%':
			p++;
			assert(*p != '\0');

			if ('.' == *p) {
				p++;

				if ('*' == *p) {
					/* precision passed as parameter */
					precision = va_arg(ap, int);
				} else {
					p = readprecision(p, &precision);
				}

				assert(precision >= 0);
			}

			assert(precision == -1 || (*p == 's'));


			/* %l* modifier */
			if ('l' == *p) {
				mlong = 1;
				p++;
				assert(*p != '\0');
			}

			assert(mlong == 0 || (*p == 'd' || *p == 'u' || *p == 'x'));


			/* defaults */
			switch (*p) {
			case '%':
				(void) fputc('%', fp);
				continue;

			case 's':
				if (precision == -1) {
					(void) fputs(va_arg(ap, char *), fp);
				} else {
					(void) fprintf(fp, "%.*s", precision, va_arg(ap, char *));
				}
				continue;

			case 'c':
				(void) fputc(va_arg(ap, int), fp);	/* promoted */
				continue;

			case 'd':
				if (mlong) {
					(void) fprintf(fp, "%ld", va_arg(ap, long));
				} else {
					(void) fprintf(fp, "%d", va_arg(ap, int));
				}
				continue;

			case 'u':
				if (mlong) {
					(void) fprintf(fp, "%lu", va_arg(ap, unsigned long));
				} else {
					(void) fprintf(fp, "%u", va_arg(ap, unsigned));
				}
				continue;

			case 'x':
				if (mlong) {
					(void) fprintf(fp, "%lx", va_arg(ap, long));
				} else {
					(void) fprintf(fp, "%d", va_arg(ap, int));
				}
				continue;

			default:
				break;
			}


			/* user-defined extensions */
			assert(fmtf[(unsigned char) *p] != NULL);

			fmtf[(unsigned char) *p](fp, va_arg(ap, void *));
			break;

		default:
			(void) putc((unsigned char) *p, fp);
			break;
		}
	}
}

void
efprintf(FILE *fp, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vefprintf(fp, fmt, ap);
	va_end(ap);
}

/*
 * Format specifiers registered here draw a void * from the va_list consumed in
 * vefprintf().
 */
void
fmt_register(char c, void (*f)(FILE *fp, void *))
{
	/* reserved specifiers */
	assert(c != 'l');
	assert(c != '.');
	assert(c != '#');
	assert(c != '*');

	assert(fmtf[(unsigned char) c] == NULL);

	fmtf[(unsigned char) c] = f;
}
