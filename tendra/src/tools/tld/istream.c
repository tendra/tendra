/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


/**** istream.c --- Input stream handling.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the input stream facility specified in the file
 * "istream.h".  See that file for more details.
 *
 **** Change Log:*/

/****************************************************************************/

#include "istream.h"
#include "cstring.h"
#include "syntax.h"

/*--------------------------------------------------------------------------*/

#define ISTREAM_BUFSIZE 8193

/*--------------------------------------------------------------------------*/

ExceptionP XX_istream_read_error = EXCEPTION ("error reading from stream");

/*--------------------------------------------------------------------------*/

static char istream_input_buffer [ISTREAM_BUFSIZE];

static IStreamT		istream_input_1 = {
    NIL (FILE *),
    &(istream_input_buffer [0]),
    &(istream_input_buffer [ISTREAM_BUFSIZE - 1]),
    &(istream_input_buffer [ISTREAM_BUFSIZE]),
    &(istream_input_buffer [ISTREAM_BUFSIZE]),
    1,
    "<stdin>",
    FALSE
};

IStreamT	 *const istream_input = &istream_input_1;

/*--------------------------------------------------------------------------*/

static IStreamStatusT
istream_read_hex_char(IStreamP istream, char *c_ref)
{
    int value;
    int tmp;
    char c;

  redo1:
    switch (c = ISTREAM_READ_CHAR (istream)) {
	case '\0':
		ISTREAM_HANDLE_NULL (istream, redo1, eof);
		return (ISTREAM_STAT_SYNTAX_ERROR);
	case '\n':
		istream_inc_line (istream);
		return (ISTREAM_STAT_SYNTAX_ERROR);
	default:
		if (((value = syntax_value (c)) == SYNTAX_NO_VALUE) || (value >= 16)) {
			return (ISTREAM_STAT_SYNTAX_ERROR);
		}
		tmp = value;
		break;
    }
  redo2:
    switch (c = ISTREAM_READ_CHAR (istream)) {
	case '\0':
		ISTREAM_HANDLE_NULL (istream, redo2, eof);
		return (ISTREAM_STAT_SYNTAX_ERROR);
	case '\n':
		istream_inc_line (istream);
		return (ISTREAM_STAT_SYNTAX_ERROR);
	default:
		if (((value = syntax_value (c)) == SYNTAX_NO_VALUE) || (value >= 16)) {
			return (ISTREAM_STAT_SYNTAX_ERROR);
		}
		break;
    }
    *c_ref = (char) ((tmp * 16) + value);
    return (ISTREAM_STAT_READ_CHAR);
  eof:
    return (ISTREAM_STAT_SYNTAX_ERROR);
}

/*--------------------------------------------------------------------------*/

void
istream_setup()
{
    istream_input_1.file = stdin;
}

#ifdef FS_FAST
#undef istream_init
#endif /* defined (FS_FAST) */
void
istream_init(IStreamP istream)
{
    istream->name = NIL (CStringP);
}
#ifdef FS_FAST
#define istream_init(is) ((is)->name = NIL (CStringP))
#endif /* defined (FS_FAST) */

BoolT
istream_open(IStreamP istream, CStringP name)
{
    if ((istream->file = fopen (name, "r")) == NIL (FILE *)) {
		return (FALSE);
    }
    istream->buffer  = ALLOCATE_VECTOR (char, ISTREAM_BUFSIZE);
    istream->limit   = &(istream->buffer [ISTREAM_BUFSIZE]);
    istream->line    = 1;
    istream->name    = name;
    X__istream_fill_buffer (istream);
    return (TRUE);
}

void
istream_assign(IStreamP to, IStreamP from)
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

#ifdef FS_FAST
#undef istream_is_open
#endif /* defined (FS_FAST) */
BoolT
istream_is_open(IStreamP istream)
{
    return (istream->name != NIL (CStringP));
}
#ifdef FS_FAST
#define istream_is_open(is) ((is)->name != NIL (CStringP))
#endif /* defined (FS_FAST) */

BoolT
istream_read_char(IStreamP istream, char *c_ref)
{
    char c;

  redo:
    switch (c = ISTREAM_READ_CHAR (istream)) {
	case '\n':
		istream_inc_line (istream);
		break;
	case '\0':
		ISTREAM_HANDLE_NULL (istream, redo, eof);
		break;
	default:
		break;
    }
    *c_ref = c;
    return (TRUE);
  eof:
    return (FALSE);
}

BoolT
istream_peek_char(IStreamP istream, char *c_ref)
{
    char c;

  redo:
    switch (c = ISTREAM_PEEK_CHAR (istream)) {
	case '\0':
		ISTREAM_HANDLE_NULL (istream, redo, eof);
		break;
	default:
		break;
    }
    *c_ref = c;
    return (TRUE);
  eof:
    return (FALSE);
}

IStreamStatusT
istream_read_escaped_char(IStreamP istream,
						  char *c_ref)
{
    char c;

  redo:
    switch (c = ISTREAM_READ_CHAR (istream)) {
	case '\0':
		ISTREAM_HANDLE_NULL (istream, redo, eof);
		*c_ref = c;
		return (ISTREAM_STAT_READ_CHAR);
	case '\n':
		istream_inc_line (istream);
		return (ISTREAM_STAT_NO_CHAR);
	case '0':
		*c_ref = '\0';
		return (ISTREAM_STAT_READ_CHAR);
	case 'f': case 'F':
		*c_ref = '\f';
		return (ISTREAM_STAT_READ_CHAR);
	case 'n': case 'N':
		*c_ref = '\n';
		return (ISTREAM_STAT_READ_CHAR);
	case 'r': case 'R':
		*c_ref = '\r';
		return (ISTREAM_STAT_READ_CHAR);
	case 't': case 'T':
		*c_ref = '\t';
		return (ISTREAM_STAT_READ_CHAR);
	case 'x': case 'X':
		return (istream_read_hex_char (istream, c_ref));
	default:
		*c_ref = c;
		return (ISTREAM_STAT_READ_CHAR);
    }
  eof:
    return (ISTREAM_STAT_SYNTAX_ERROR);
}

#ifdef FS_FAST
#undef istream_inc_line
#endif /* defined (FS_FAST) */
void
istream_inc_line(IStreamP istream)
{
    istream->line ++;
}
#ifdef FS_FAST
#define istream_inc_line(is) ((is)->line ++)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef istream_line
#endif /* defined (FS_FAST) */
unsigned
istream_line(IStreamP istream)
{
    return (istream->line);
}
#ifdef FS_FAST
#define istream_line(is) ((is)->line)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef istream_name
#endif /* defined (FS_FAST) */
CStringP
istream_name(IStreamP istream)
{
    return (istream->name);
}
#ifdef FS_FAST
#define istream_name(is) ((is)->name)
#endif /* defined (FS_FAST) */

void
istream_close(IStreamP istream)
{
    (void) fclose (istream->file);
    if (istream != istream_input) {
		DEALLOCATE (istream->buffer);
    }
    istream_init (istream);
}

/*--------------------------------------------------------------------------*/

void
X__istream_fill_buffer(IStreamP istream)
{
    SizeT bytes = fread ((GenericP) (istream->buffer), sizeof (char),
						 (SizeT) (ISTREAM_BUFSIZE - 1), istream->file);

    if ((bytes == (SizeT) 0) && (ferror (istream->file))) {
		CStringP name = cstring_duplicate (istream->name);

		THROW_VALUE (XX_istream_read_error, name);
		UNREACHED;
    }
    istream->current   = istream->buffer;
    istream->end       = (istream->current + bytes);
    istream->read_last = FALSE;
    *(istream->end) ++ = '\0';
}
