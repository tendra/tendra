/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/*
 ** Output stream handling.
 *
 ** Original author: Steve Folkes <smf@hermes.mod.uk>
 *
 ** Commentary:
 *
 * This file implements the output stream facility specified in the file
 * "ostream.h".  See that file for more details.
 *
 */

#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "cstring.h"
#include "fmm.h"
#include "msgcat.h"
#include "ostream.h"

#define OSTREAM_WRITE_ERROR_CHECK(ostream) \
	if (ferror((ostream)->file)) { \
		MSG_ostream_write_error(ostream_name(ostream)); \
	}


/*
 * Standard output streams mapped to stdout and stderr
 */
static OStreamT	ostream_output_1 = {
	NULL, "<stdout>", 1, 0, NULL, 0
};

static OStreamT	ostream_error_1 = {
	NULL, "<stderr>", 1, 0, NULL, 0
};

OStreamT *const ostream_output = &ostream_output_1;
OStreamT *const ostream_error  = &ostream_error_1;


void
ostream_setup(void)
{
	ostream_output_1.file = stdout;
	ostream_error_1.file  = stderr;
}

OStreamP
ostream_new(void)
{
	OStreamP ostream;

	ostream = fmm_malloc(sizeof(OStreamT), fmm_deftype);
	ostream_init(ostream);
	return (ostream);
}

void
ostream_free(OStreamP ostream)
{
	fmm_free(ostream, fmm_deftype);
}

void
ostream_init(OStreamP ostream)
{
	ostream->name = NULL;
}

BoolT
ostream_open(OStreamP ostream, const char *name)
{
	const char *oname, *pname;
	char *s;

	oname = name;
	pname = strrchr (name, '@');

	if (pname != NULL) {
		oname = s = string_alloc (strlen (name) + 10);
		(void) sprintf (s, "%.*s%d%s", (int) (pname - name), name,
						++ostream->no, pname + 1);
	}
	if ((ostream->file = fopen (oname, "w")) == NULL) {
		return (FALSE);
	}
	ostream->name = oname;
	ostream->gen_name = name;
	ostream->line = 1;
	ostream->column = 0;
	ostream_buffer(ostream);
	return (TRUE);
}

BoolT
ostream_is_open(OStreamP ostream)
{
	return (ostream->name != NULL);
}

void
ostream_buffer(OStreamP ostream)
{
	(void)setvbuf(ostream->file, NIL (CStringP), _IOFBF, (size_t) BUFSIZ);
}

void
ostream_unbuffer(OStreamP ostream)
{
	(void)setvbuf(ostream->file, NIL (CStringP), _IONBF, (size_t)0);
}

void
ostream_close(OStreamP ostream)
{
	if (fclose(ostream->file)) {
		MSG_ostream_write_error(ostream_name(ostream));
	}
	ostream_init(ostream);
}

void
ostream_flush(OStreamP ostream)
{
	if (fflush(ostream->file)) {
		MSG_ostream_write_error(ostream_name(ostream));
	}
}

const char*
ostream_name(OStreamP ostream)
{
	return (ostream->name);
}

const char*
ostream_gen_name(OStreamP ostream)
{
	return (ostream->gen_name);
}

unsigned
ostream_column(OStreamP ostream)
{
	return (ostream->column + 1);
}

unsigned
ostream_line(OStreamP ostream)
{
	return (ostream->line);
}

void
ostream_unput(OStreamP ostream, unsigned n)
{
	fseek(ostream->file, -1, SEEK_CUR);
}

void
write_char(OStreamP ostream, char c)
{
	if (c == '\n') {
		ostream->line++;
		ostream->column = 0;
	} else if (c == '\t') {
		ostream->column = 8 * ((ostream->column + 8) / 8);
	} else
		ostream->column++;
	if (putc((int)c, ostream->file) == EOF)
		MSG_ostream_write_error(ostream_name(ostream));
}

void
write_newline(OStreamP ostream)
{
	write_char(ostream, '\n');
}

void
write_tab(OStreamP ostream)
{
	write_char(ostream, '\t');
}

void
write_byte(OStreamP ostream, ByteT c)
{
	if (c == '\n') {
		ostream->line++;
	}
	if (putc((int)c, ostream->file) == EOF)
		MSG_ostream_write_error(ostream_name(ostream));
}

void
write_escaped_char(OStreamP ostream, char c)
{
	switch (c) {
	case '\0':
		(void)fputs ("\\0", ostream->file);
		break;
	case '\f':
		(void)fputs ("\\f", ostream->file);
		break;
	case '\n':
		ostream->line++;
		(void)fputc ('\n', ostream->file);
		break;
	case '\r':
		(void)fputs ("\\r", ostream->file);
		break;
	case '\t':
		(void)fputc ('\t', ostream->file);
		break;
	case '\\':
		(void)fputs ("\\\\", ostream->file);
		break;
	default:
		if (isprint(c)) {
			(void)fputc((int)c, ostream->file);
		} else {
			(void)fprintf(ostream->file, "\\x%02x", (unsigned)(unsigned char)c);
		}
	}
	OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_int(OStreamP ostream, int i)
{
	if (fprintf (ostream->file, "%d", i) == EOF)
		MSG_ostream_write_error(ostream_name(ostream));
}

void
write_unsigned(OStreamP ostream, unsigned i)
{
	if (fprintf (ostream->file, "%u", i) == EOF)
		MSG_ostream_write_error(ostream_name(ostream));
}

void
write_cstring(OStreamP ostream, const char *cp)
{
	if (fputs(cp, ostream->file) == EOF)
		MSG_ostream_write_error(ostream_name(ostream));
	while (*cp) {
		if (*cp++ == '\n') {
			ostream->line++;
		}
	}
}

void
write_bytes(OStreamP ostream, ByteP bp, size_t length)
{
	if (fwrite((void*)bp, sizeof(ByteT), length, ostream->file) < length)
		MSG_ostream_write_error(ostream_name(ostream));
	while (length--) {
		if (*bp++ == '\n') {
			ostream->line++;
		}
	}
}

void
write_chars(OStreamP ostream, const char *cp, size_t length)
{
	while (length--) {
		write_char(ostream, *cp++);
	}
}

void
write_escaped_chars(OStreamP ostream, const char *cp, size_t length)
{
	while (length--) {
		write_escaped_char(ostream, *cp++);
	}
}

void
write_system_error(OStreamP ostream)
{
	write_cstring (ostream, strerror(errno));
}

void
write_fmt(OStreamP ostream, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(ostream->file, fmt, ap);
	va_end(ap);
	OSTREAM_WRITE_ERROR_CHECK (ostream);
}

void
write_vfmt(OStreamP ostream, const char *fmt, va_list ap)
{
	vfprintf(ostream->file, fmt, ap);
	OSTREAM_WRITE_ERROR_CHECK (ostream);
}

void
write_pointer(OStreamP ostream, const void *ptr)
{
	write_fmt(ostream, "%p", ptr);
}

