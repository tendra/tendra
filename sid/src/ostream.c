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

#include "ostream.h"
#include "cstring.h"
#include "syntax.h"

ExceptionP XX_ostream_write_error = EXCEPTION("error writing to stream");

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

#define OSTREAM_WRITE_ERROR_CHECK(ostream)\
if (ferror((ostream)->file)) { \
    char * X___name = cstring_duplicate(ostream_name(ostream)); \
    THROW_VALUE(XX_ostream_write_error, X___name); \
}

void
ostream_setup(void)
{
    ostream_output_1.file = stdout;
    ostream_error_1.file  = stderr;
}

void
ostream_init(OStreamT * ostream)
{
    ostream->name = NULL;
}

BoolT
ostream_open(OStreamT * ostream, char * name)
{
    char * oname = name;
    char * pname = strrchr(name, '@');
    if (pname != NULL) {
	oname = ALLOCATE_VECTOR(char, strlen(name) + 10);
	(void)sprintf(oname, "%.*s%d%s", (int)(pname - name), name,
		      ++ostream->no, pname + 1);
    }
    if ((ostream->file = fopen(oname, "w")) == NULL) {
	return(FALSE);
    }
    ostream->name = oname;
    ostream->gen_name = name;
    ostream->line = 1;
    (void)setvbuf(ostream->file, NULL, _IOFBF, (size_t)BUFSIZ);
    return(TRUE);
}

BoolT
ostream_is_open(OStreamT * ostream)
{
    return(ostream->name != NULL);
}

void
ostream_buffer(OStreamT * ostream)
{
    (void)setvbuf(ostream->file, NULL, _IOFBF, (size_t)BUFSIZ);
}

void
ostream_unbuffer(OStreamT * ostream)
{
    (void)setvbuf(ostream->file, NULL, _IONBF, (size_t)0);
}

void
ostream_close(OStreamT * ostream)
{
    if (fclose(ostream->file)) {
	char * name = cstring_duplicate(ostream_name(ostream));

	THROW_VALUE(XX_ostream_write_error, name);
    }
    ostream_init(ostream);
}

void
ostream_flush(OStreamT * ostream)
{
    if (fflush(ostream->file)) {
	char * name = cstring_duplicate(ostream_name(ostream));

	THROW_VALUE(XX_ostream_write_error, name);
    }
}

char *
ostream_name(OStreamT * ostream)
{
    return(ostream->name);
}

char *
ostream_gen_name(OStreamT * ostream)
{
    return(ostream->gen_name);
}

unsigned
ostream_line(OStreamT * ostream)
{
    return(ostream->line);
}

void
write_newline(OStreamT * ostream)
{
    ostream->line++;
    (void)putc('\n', ostream->file);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_tab(OStreamT * ostream)
{
    (void)putc('\t', ostream->file);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_byte(OStreamT * ostream, ByteT c)
{
    if (c == '\n') {
	ostream->line++;
    }
    (void)putc((int)c, ostream->file);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_char(OStreamT * ostream, char c)
{
    if (c == '\n') {
	ostream->line++;
    }
    (void)putc((int)c, ostream->file);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_escaped_char(OStreamT * ostream, char c)
{
    switch (c) {
      case '\0':
	(void)fputs("\\0", ostream->file);
	break;
      case '\f':
	(void)fputs("\\f", ostream->file);
	break;
      case '\n':
	ostream->line++;
	(void)fputc('\n', ostream->file);
	break;
      case '\r':
	(void)fputs("\\r", ostream->file);
	break;
      case '\t':
	(void)fputc('\t', ostream->file);
	break;
      case '\\':
	(void)fputs("\\\\", ostream->file);
	break;
      default:
	if (isprint((unsigned char)c)) {
	    (void)fputc((int)c, ostream->file);
	} else {
	    (void)fprintf(ostream->file, "\\x%02x",
			  (unsigned)(unsigned char)c);
	}
    }
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_int(OStreamT * ostream, int i)
{
    (void)fprintf(ostream->file, "%d", i);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_unsigned(OStreamT * ostream, unsigned i)
{
    (void)fprintf(ostream->file, "%u", i);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_cstring(OStreamT * ostream, char * cstring)
{
    char * tmp = cstring;

    while (*tmp) {
	if (*tmp++ == '\n') {
	    ostream->line++;
	}
    }
    (void)fputs(cstring, ostream->file);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_bytes(OStreamT * ostream, ByteT * bytes, unsigned length)
{
    unsigned tmp_length = length;
    ByteT *    tmp_bytes  = bytes;

    while (tmp_length--) {
	if (*tmp_bytes++ == '\n') {
	    ostream->line++;
	}
    }
    (void)fwrite((void *)bytes, sizeof(ByteT), (size_t)length,
		 ostream->file);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_chars(OStreamT * ostream, char * chars, unsigned length)
{
    while (length--) {
	write_char(ostream, *chars++);
    }
}

void
write_escaped_chars(OStreamT * ostream, char * chars, unsigned length)
{
    while (length--) {
	write_escaped_char(ostream, *chars++);
    }
}

void
write_system_error(OStreamT * ostream)
{
    char * message = strerror(errno);
    write_cstring(ostream, message);
}

void
write_pointer(OStreamT * ostream, void * pointer)
{
    (void)fprintf(ostream->file, "%p", pointer);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}
