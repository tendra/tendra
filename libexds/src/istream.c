/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * istream.c - Input stream handling.
 *
 * This file implements the input stream facility specified in the file
 * "istream.h".  See that file for more details.
 */

#include <stddef.h>
#include <stdio.h>

#include <shared/check.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/istream.h>
#include <exds/cstring.h>

#include "syntax.h"

#define ISTREAM_BUFSIZE 8193

ExceptionT *XX_istream_read_error = EXCEPTION("error reading from stream");

static char istream_input_buffer[ISTREAM_BUFSIZE];

static IStreamT istream_input_1 = {
	NULL,
	&istream_input_buffer[0],
	&istream_input_buffer[ISTREAM_BUFSIZE - 1],
	&istream_input_buffer[ISTREAM_BUFSIZE],
	&istream_input_buffer[ISTREAM_BUFSIZE],
	1,
	"<stdin>",
	FALSE
};

IStreamT *const istream_input = &istream_input_1;

static IStreamStatusT
istream_read_hex_char(IStreamT *istream, char *c_ref)
{
	int value;
	int tmp;
	char c;

redo1:
	switch (c = ISTREAM_READ_CHAR(istream)) {
	case '\0':
		ISTREAM_HANDLE_NULL(istream, redo1, eof);
		return ISTREAM_STAT_SYNTAX_ERROR;

	case '\n':
		istream_inc_line(istream);
		return ISTREAM_STAT_SYNTAX_ERROR;

	default:
		if ((value = syntax_value(c)) == SYNTAX_NO_VALUE || value >= 16) {
			return ISTREAM_STAT_SYNTAX_ERROR;
		}

		tmp = value;
		break;
	}

redo2:
	switch (c = ISTREAM_READ_CHAR(istream)) {
	case '\0':
		ISTREAM_HANDLE_NULL(istream, redo2, eof);
		return ISTREAM_STAT_SYNTAX_ERROR;

	case '\n':
		istream_inc_line(istream);
		return ISTREAM_STAT_SYNTAX_ERROR;

	default:
		if ((value = syntax_value(c)) == SYNTAX_NO_VALUE || value >= 16) {
			return ISTREAM_STAT_SYNTAX_ERROR;
		}
		break;
	}
	*c_ref = (char) ((tmp * 16) + value);

	return ISTREAM_STAT_READ_CHAR;

eof:
	return ISTREAM_STAT_SYNTAX_ERROR;
}

/*
 * Externally visible functions
 */

void
istream_setup(void)
{
	istream_input_1.file = stdin;
}

void
istream_init(IStreamT *istream)
{
	istream->name = NULL;
}

BoolT
istream_open(IStreamT *istream, const char *name)
{
    if ((istream->file = fopen(name, "r")) == NULL) {
		return FALSE;
    }

    istream->buffer  = ALLOCATE_VECTOR(char, ISTREAM_BUFSIZE);
    istream->limit   = &istream->buffer[ISTREAM_BUFSIZE];
    istream->line    = 1;
    istream->name    = name;
    X__istream_fill_buffer(istream);
    return TRUE;
}

void
istream_assign(IStreamT *to, IStreamT *from)
{
    to->file      = from->file;
    to->buffer    = from->buffer;
    to->current   = from->current;
    to->end       = from->end;
    to->limit     = from->limit;
    to->line      = from->line;
    to->name      = from->name;
    to->read_last = from->read_last;
}

BoolT
istream_is_open(IStreamT *istream)
{
	return istream->name != NULL;
}

BoolT
istream_read_char(IStreamT *istream, char *c_ref)
{
	char c;

redo:
	switch (c = ISTREAM_READ_CHAR(istream)) {
	case '\n':
		istream_inc_line(istream);
		break;

	case '\0':
		ISTREAM_HANDLE_NULL(istream, redo, eof);
		break;

	default:
		break;
	}

	*c_ref = c;
	return TRUE;

eof:
	return FALSE;
}

BoolT
istream_peek_char(IStreamT *istream, char *c_ref)
{
	char c;

redo:
	switch (c = ISTREAM_PEEK_CHAR(istream)) {
	case '\0':
		ISTREAM_HANDLE_NULL(istream, redo, eof);
		break;
	default:
		break;
	}

	*c_ref = c;
	return TRUE;

eof:
	return FALSE;
}

IStreamStatusT
istream_read_escaped_char(IStreamT *istream, char *c_ref)
{
	char c;

redo:
	switch (c = ISTREAM_READ_CHAR(istream)) {
	case '\0':
		ISTREAM_HANDLE_NULL(istream, redo, eof);
		*c_ref = c;
		return ISTREAM_STAT_READ_CHAR;

	case '\n':
		istream_inc_line(istream);
		return ISTREAM_STAT_NO_CHAR;

	case '0':
		*c_ref = '\0';
		return ISTREAM_STAT_READ_CHAR;

	case 'f': case 'F':
		*c_ref = '\f';
		return ISTREAM_STAT_READ_CHAR;

	case 'n': case 'N':
		*c_ref = '\n';
		return ISTREAM_STAT_READ_CHAR;

	case 'r': case 'R':
		*c_ref = '\r';
		return ISTREAM_STAT_READ_CHAR;

	case 't': case 'T':
		*c_ref = '\t';
		return ISTREAM_STAT_READ_CHAR;

	case 'x': case 'X':
		return istream_read_hex_char(istream, c_ref);

	default:
		*c_ref = c;
		return ISTREAM_STAT_READ_CHAR;
	}

eof:
	return ISTREAM_STAT_SYNTAX_ERROR;
}

void
istream_inc_line(IStreamT *istream)
{
	istream->line++;
}

unsigned
istream_line(IStreamT *istream)
{
	return istream->line;
}

const char *
istream_name(IStreamT *istream)
{
	return istream->name;
}

void
istream_close(IStreamT *istream)
{
	IGNORE fclose(istream->file);

	if (istream != istream_input) {
		DEALLOCATE(istream->buffer);
	}

	istream_init(istream);
}

void
X__istream_fill_buffer(IStreamT *istream)
{
    size_t bytes = fread(istream->buffer, sizeof(char),
		(size_t) (ISTREAM_BUFSIZE - 1), istream->file);

    if (bytes == (size_t) 0 && ferror(istream->file)) {
		char *name = cstring_duplicate(istream->name);

		THROW_VALUE(XX_istream_read_error, name);
		UNREACHED;
    }

    istream->current   = istream->buffer;
    istream->end       = istream->current + bytes;
    istream->read_last = FALSE;
    *istream->end++  = '\0';
}
