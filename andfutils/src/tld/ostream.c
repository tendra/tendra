/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
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


/**** ostream.c --- Output stream handling.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the output stream facility specified in the file
 * "ostream.h".  See that file for more details.
 *
 **** Change Log:
 * $Log: ostream.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:45:47  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:11  smf
 * Initial import of os-interface shared files.
 *
**/

/****************************************************************************/

#include <stdio.h>

#include "ostream.h"
#include "cstring.h"
#include "syntax.h"

/*--------------------------------------------------------------------------*/

ExceptionT *XX_ostream_write_error = EXCEPTION("error writing to stream");

static OStreamT			ostream_output_1 = {
    NIL(FILE *),
    "<stdout>",
    1
};
static OStreamT			ostream_error_1 = {
    NIL(FILE *),
    "<stderr>",
    1
};

OStreamT		 *const ostream_output = &ostream_output_1;
OStreamT		 *const ostream_error  = &ostream_error_1;

/*--------------------------------------------------------------------------*/

#define OSTREAM_WRITE_ERROR_CHECK(ostream)\
    if (ferror((ostream)->file)) { \
	    char * X___name = cstring_duplicate(ostream_name(ostream)); \
	    THROW_VALUE(XX_ostream_write_error, X___name); \
}

/*--------------------------------------------------------------------------*/

void
ostream_setup(void)
{
    ostream_output_1.file = stdout;
    ostream_error_1.file  = stderr;
}

#ifdef FS_FAST
#undef ostream_init
#endif /* defined (FS_FAST) */
void
ostream_init(OStreamT *ostream)
{
    ostream->name = NIL(char *);
}
#ifdef FS_FAST
#define ostream_init(os)	((os)->name = NIL(char *))
#endif /* defined (FS_FAST) */

BoolT
ostream_open(OStreamT *ostream,		      char * name)
{
    if ((ostream->file = fopen(name, "w")) == NIL(FILE *)) {
	return(FALSE);
    }
    ostream->name = name;
    ostream->line = 1;
   (void)setvbuf(ostream->file, NIL(char *), _IOFBF,(SizeT)BUFSIZ);
    return(TRUE);
}

#ifdef FS_FAST
#undef ostream_is_open
#endif /* defined (FS_FAST) */
BoolT
ostream_is_open(OStreamT *ostream)
{
    return(ostream->name != NIL(char *));
}
#ifdef FS_FAST
#define ostream_is_open(os)	((os)->name != NIL(char *))
#endif /* defined (FS_FAST) */

void
ostream_buffer(OStreamT *ostream)
{
   (void)setvbuf(ostream->file, NIL(char *), _IOFBF,(SizeT)BUFSIZ);
}

void
ostream_unbuffer(OStreamT *ostream)
{
   (void)setvbuf(ostream->file, NIL(char *), _IONBF,(SizeT)0);
}

void
ostream_close(OStreamT *ostream)
{
    if (fclose(ostream->file)) {
	char * name = cstring_duplicate(ostream_name(ostream));

	THROW_VALUE(XX_ostream_write_error, name);
    }
    ostream_init(ostream);
}

void
ostream_flush(OStreamT *ostream)
{
    if (fflush(ostream->file)) {
	char * name = cstring_duplicate(ostream_name(ostream));

	THROW_VALUE(XX_ostream_write_error, name);
    }
}

#ifdef FS_FAST
#undef ostream_name
#endif /* defined (FS_FAST) */
char *
ostream_name(OStreamT *ostream)
{
    return(ostream->name);
}
#ifdef FS_FAST
#define ostream_name(os)	((os)->name)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef ostream_line
#endif /* defined (FS_FAST) */
unsigned
ostream_line(OStreamT *ostream)
{
    return(ostream->line);
}
#ifdef FS_FAST
#define ostream_line(os)	((os)->line)
#endif /* defined (FS_FAST) */

void
write_newline(OStreamT *ostream)
{
    ostream->line++;
   (void)putc('\n', ostream->file);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_tab(OStreamT *ostream)
{
   (void)putc('\t', ostream->file);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_byte(OStreamT *ostream,		    ByteT    c)
{
    if (c == '\n') {
	ostream->line++;
    }
   (void)putc((int)c, ostream->file);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_char(OStreamT *ostream,		    char     c)
{
    if (c == '\n') {
	ostream->line++;
    }
   (void)putc((int)c, ostream->file);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_escaped_char(OStreamT *ostream,			    char     c)
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
	if (syntax_is_printable(c)) {
	   (void)fputc((int)c, ostream->file);
	} else {
	   (void)fprintf(ostream->file, "\\x%02x",
			   (unsigned)(unsigned char)c);
	}
    }
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_int(OStreamT *ostream,		   int      i)
{
   (void)fprintf(ostream->file, "%d", i);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_unsigned(OStreamT *ostream,			unsigned i)
{
   (void)fprintf(ostream->file, "%u", i);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_cstring(OStreamT *ostream,		       char * cstring)
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
write_bytes(OStreamT *ostream,		     ByteT *   bytes ,
		     unsigned length)
{
    unsigned tmp_length = length;
    ByteT *   tmp_bytes  = bytes;

    while (tmp_length--) {
	if (*tmp_bytes++ == '\n') {
	    ostream->line++;
	}
    }
   (void)fwrite((void *)bytes, sizeof(ByteT), (SizeT)length,
		   ostream->file);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}

void
write_chars(OStreamT *ostream,		     char * chars ,
		     unsigned length)
{
    while (length--) {
	write_char(ostream, *chars++);
    }
}

void
write_escaped_chars(OStreamT *ostream,			     char * chars ,
			     unsigned length)
{
    while (length--) {
	write_escaped_char(ostream, *chars++);
    }
}

void
write_system_error(OStreamT *ostream)
{
#if (defined(FS_STRERROR) || defined(FS_SYS_ERRLIST))
# ifdef FS_STRERROR
    char * message = strerror(errno);
# else
    char * message;

    if ((errno >= 0) && (errno < sys_nerr)) {
	message = sys_errlist[errno];
    } else {
	message = "unknown error";
    }
# endif /* defined (FS_STRERROR) */
    write_cstring(ostream, message);
#else
    write_cstring(ostream, "error ");
    write_int(ostream, errno);
#endif /* (defined (FS_STRERROR) || defined (FS_SYS_ERRLIST)) */
}

void
write_pointer(OStreamT *ostream,		       void * pointer)
{
   (void)fprintf(ostream->file, "%p", pointer);
    OSTREAM_WRITE_ERROR_CHECK(ostream);
}
