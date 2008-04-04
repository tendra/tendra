/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

/*
 * istream.c - Input stream handling.
 *
 * This file implements the input stream facility specified in the file
 * "istream.h".  See that file for more details.
 */

#include <stddef.h>
#include <stdio.h>

#include "shared/check/check.h"
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
istream_open(IStreamT *istream, char *name)
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
	return(istream->name != NULL);
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

char *
istream_name(IStreamT *istream)
{
	return istream->name;
}

void
istream_close(IStreamT *istream)
{
	(void) fclose(istream->file);

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
    *(istream->end)++  = '\0';
}
