/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * ostream.c - Output stream handling.
 *
 * This file implements the output stream facility specified in the file
 * "ostream.h".  See that file for more details.
 *
 * TODO this would really benifit from a printf() style interface.
 */

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <shared/check.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/ostream.h>
#include <exds/cstring.h>

#include "syntax.h"

ExceptionT *XX_ostream_write_error = EXCEPTION("error writing to stream");

static OStreamT ostream_output_1 = {
	NULL,
	"<stdout>",
	"<stdout>",
	0,
	1
};

static OStreamT ostream_error_1 = {
	NULL,
	"<stderr>",
	"<stderr>",
	0,
	1
};

OStreamT *const ostream_output = &ostream_output_1;
OStreamT *const ostream_error  = &ostream_error_1;

#define OSTREAM_WRITE_ERROR_CHECK(ostream) \
	if (ferror((ostream)->file)) { \
		char * X___name = cstring_duplicate(ostream_name((ostream))); \
		THROW_VALUE(XX_ostream_write_error, X___name); \
	}

void
ostream_setup(void)
{
	ostream_output_1.file = stdout;
	ostream_error_1.file  = stderr;
}

void
ostream_init(OStreamT *ostream)
{
	ostream->name = NULL;
}

BoolT
ostream_open(OStreamT *ostream, const char *name)
{
	const char *oname = name;
	const char *pname = strrchr(name, '@');

	if (pname != NULL) {
		char *s = ALLOCATE_VECTOR(char, strlen(name) + 10);
		IGNORE sprintf(s, "%.*s%d%s", (int) (pname - name), name,
			++ostream->no, pname + 1);
		oname = s;
	}
	if ((ostream->file = fopen(oname, "w")) == NULL) {
		return FALSE;
	}
	ostream->name = oname;
	ostream->gen_name = name;
	ostream->line = 1;
	IGNORE setvbuf(ostream->file, NULL, _IOFBF, (size_t) BUFSIZ);
	return TRUE;
}

BoolT
ostream_is_open(OStreamT *ostream)
{
	return ostream->name != NULL;
}

void
ostream_buffer(OStreamT *ostream)
{
	IGNORE setvbuf(ostream->file, NULL, _IOFBF, (size_t) BUFSIZ);
}

void
ostream_unbuffer(OStreamT *ostream)
{
	IGNORE setvbuf(ostream->file, NULL, _IONBF, (size_t) 0);
}

void
ostream_close(OStreamT *ostream)
{
	if (fclose(ostream->file)) {
		char *name = cstring_duplicate(ostream_name(ostream));

		THROW_VALUE(XX_ostream_write_error, name);
	}
	ostream_init(ostream);
}

void
ostream_flush(OStreamT *ostream)
{
	if (fflush(ostream->file)) {
		char *name = cstring_duplicate(ostream_name(ostream));

		THROW_VALUE(XX_ostream_write_error, name);
	}
}

const char *
ostream_name(OStreamT *ostream)
{
	return ostream->name;
}

const char *
ostream_gen_name(OStreamT *ostream)
{
	return ostream->gen_name;
}

unsigned
ostream_line(OStreamT *ostream)
{
	return ostream->line;
}

void
write_newline(OStreamT *ostream)
{
	ostream->line++;
	IGNORE putc('\n', ostream->file);
	OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_tab(OStreamT *ostream)
{
	IGNORE putc('\t', ostream->file);
	OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_char(OStreamT *ostream, char c)
{
	if (c == '\n') {
		ostream->line++;
	}

	IGNORE putc((int) c, ostream->file);
	OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_escaped_char(OStreamT *ostream, char c)
{
	switch (c) {
	case '\0':
		IGNORE fputs("\\0", ostream->file);
		break;

	case '\f':
		IGNORE fputs("\\f", ostream->file);
		break;

	case '\n':
		ostream->line++;
		IGNORE fputc('\n', ostream->file);
		break;

	case '\r':
		IGNORE fputs("\\r", ostream->file);
		break;

	case '\t':
		IGNORE fputc('\t', ostream->file);
		break;

	case '\\':
		IGNORE fputs("\\\\", ostream->file);
		break;

	default:
		if (isprint((unsigned char) c)) {
			IGNORE fputc((int) c, ostream->file);
		} else {
			IGNORE fprintf(ostream->file, "\\x%02x",
				(unsigned) (unsigned char) c);
		}
	}
	OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_int(OStreamT *ostream, int i)
{
	IGNORE fprintf(ostream->file, "%d", i);
	OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_unsigned(OStreamT *ostream, unsigned i)
{
	IGNORE fprintf(ostream->file, "%u", i);
	OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_cstring(OStreamT *ostream, const char *cstring)
{
	const char *tmp = cstring;

	/* TODO: use strchr() */
	while (*tmp) {
		if (*tmp++ == '\n') {
			ostream->line++;
		}
	}

	IGNORE fputs(cstring, ostream->file);
	OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_chars(OStreamT *ostream, const char *chars, size_t length)
{
	while (length--) {
		write_char(ostream, *chars++);
	}
}

void
write_escaped_chars(OStreamT *ostream, const char *chars, size_t length)
{
	while (length--) {
		write_escaped_char(ostream, *chars++);
	}
}

void
write_system_error(OStreamT *ostream)
{
	char *message = strerror(errno);
	write_cstring(ostream, message);
}

void
write_pointer(OStreamT *ostream, const void *pointer)
{
	IGNORE fprintf(ostream->file, "%p", pointer);
	OSTREAM_WRITE_ERROR_CHECK(ostream);
}
