/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/buffer.h>
#include <utility/ustring.h>
#include <utility/xalloc.h>


/*
    This routine frees the contents of the buffer bf.
*/

void
free_buffer(BUFFER *bf)
{
	xfree_nof(bf->start);
	bf->start = NULL;
	bf->posn = NULL;
	bf->end = NULL;
	return;
}


/*
    This routine sets the current position of the buffer bf to the start
    of the buffer and sets the buffer file to f.  It returns bf.
*/

BUFFER *
clear_buffer(BUFFER *bf, FILE *f)
{
	bf->posn = bf->start;
	bf->file = f;
	return bf;
}


/*
    This routine outputs the content of the buffer bf to the associated
    file and resets the position to the start of the buffer.  If fl is
    true then the file is flushed.
*/

void
output_buffer(BUFFER *bf, int fl)
{
	FILE *f = bf->file;
	if (f) {
		string s = bf->start;
		size_t n = (size_t)(bf->posn - s);
		if (n) {
			IGNORE fwrite((gen_ptr)s, sizeof(character), n, f);
			if (fl) {
				IGNORE fflush_v(f);
			}
			bf->posn = s;
		}
	}
	return;
}


/*
    This routine extends the buffer bf.  s gives a pointer into the buffer,
    the corresponding position in the extended buffer is returned.
*/

string
extend_buffer(BUFFER *bf, string s)
{
	string p = bf->start;
	gen_size m = (gen_size)(s - p);
	gen_size n = (gen_size)(bf->end - p) + 500;
	p = xrealloc_nof(p, character, n + 12);
	bf->start = p;
	bf->end = p + n;
	return p + m;
}


/*
    This routine makes space for at least m + 1 characters in the buffer
    bf following the position s.  It returns the corresponding position
    in the extended buffer.
*/

string
stretch_buffer(BUFFER *bf, string s, gen_size m)
{
	gen_size n = (gen_size)(bf->end - s);
	while (m >= n) {
		s = extend_buffer(bf, s);
		n = (gen_size)(bf->end - s);
	}
	return s;
}


/*
    This routine adds the character c to the buffer bf.  Note that bf will
    not necessarily be null terminated after this routine.
*/

void
bfputc(BUFFER *bf, int c)
{
	string p = bf->posn;
	if (p == bf->end)p = extend_buffer(bf, p);
	*p = (character)c;
	bf->posn = p + 1;
	return;
}


/*
    This routine adds the string s to the buffer bf.  Note that this
    guarantees that bf will be null terminated.
*/

void
bfputs(BUFFER *bf, string s)
{
	gen_size m = (gen_size)ustrlen(s);
	string p = stretch_buffer(bf, bf->posn, m);
	ustrcpy_v(p, s);
	bf->posn = p + m;
	return;
}


/*
    This routine adds the string s to the buffer bf, using printf-like
    format characters to print the extra arguments.  Note that this
    guarantees that bf will be null terminated.
*/

void
bfprintf(BUFFER *bf, const char *s, ...) /* VARARGS */
{
	char c;
	string p;
	gen_size m;
	va_list args;
	va_start(args, s);
	m = (gen_size)strlen(s);
	p = stretch_buffer(bf, bf->posn, m);

	/* Scan through format string */
	while (c = *(s++), c != 0) {
		if (c == '%') {
			int ext = 0;
			c = *(s++);
			if (c == 'l') {
				c = *(s++);
				ext = 1;
			}
			switch (c) {
			case 'c': {
				/* '%c' -> character (passed as int) */
				int ac = va_arg(args, int);
				*(p++) = (character)ac;
				break;
			}
			case 'd': {
				p = stretch_buffer(bf, p,(gen_size)50);
				if (ext) {
					/* '%ld' -> long */
					long al = va_arg(args, long);
					sprintf_v(strlit(p), "%ld", al);
				} else {
					/* '%d' -> int */
					int ad = va_arg(args, int);
					sprintf_v(strlit(p), "%d", ad);
				}
				p = p + ustrlen(p);
				break;
			}
			case 's': {
				/* '%s' -> string */
				string as = va_arg(args, string);
				if (as) {
					m = (gen_size)ustrlen(as);
					p = stretch_buffer(bf, p, m);
					ustrcpy_v(p, as);
					p += m;
				}
				break;
			}
			case 'u': {
				p = stretch_buffer(bf, p,(gen_size)50);
				if (ext) {
					/* '%lu' -> unsigned long */
					unsigned long al =
					    va_arg(args, unsigned long);
					sprintf_v(strlit(p), "%lu", al);
				} else {
					/* '%u' -> unsigned */
					unsigned au = va_arg(args, unsigned);
					sprintf_v(strlit(p), "%u", au);
				}
				p = p + ustrlen(p);
				break;
			}
			case 'x': {
				/* '%x' -> char * */
				char *ax = va_arg(args, char *);
				if (ax) {
					m = (gen_size)strlen(ax);
					p = stretch_buffer(bf, p, m);
					ustrcpy_v(p, ustrlit(ax));
					p += m;
				}
				break;
			}
			case '%': {
				/* '%%' -> percent */
				*(p++) = (character)c;
				break;
			}
			default : {
				/* Other characters */
				error(ERR_INTERNAL, "Unknown format character");
				s = "<ERROR>";
				break;
			}
			}
		} else {
			*(p++) = (character)c;
		}
	}
	*p = 0;
	bf->posn = p;
	va_end(args);
	return;
}


/*
    This routine reads at most n characters from the buffer bf into the
    string s.  It returns the number of characters read.
*/

gen_size
bfread(BUFFER *bf, string s, gen_size n)
{
	string p = bf->posn;
	gen_size m = (gen_size)(bf->end - p);
	if (m > n)m = n;
	if (m) {
		xumemcpy(s, p, m);
		bf->posn = p + m;
	}
	return m;
}
