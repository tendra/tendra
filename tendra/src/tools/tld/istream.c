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


/**** istream.c --- Input stream handling.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the input stream facility specified in the file
 * "istream.h".  See that file for more details.
 *
 **** Change Log:
 * $Log: istream.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:45:41  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:10  smf
 * Initial import of os-interface shared files.
 *
**/

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
istream_read_hex_char PROTO_N ((istream, c_ref))
		      PROTO_T (IStreamP istream X
			       char    *c_ref)
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
istream_setup PROTO_Z ()
{
    istream_input_1.file = stdin;
}

#ifdef FS_FAST
#undef istream_init
#endif /* defined (FS_FAST) */
void
istream_init PROTO_N ((istream))
	     PROTO_T (IStreamP istream)
{
    istream->name = NIL (CStringP);
}
#ifdef FS_FAST
#define istream_init(is) ((is)->name = NIL (CStringP))
#endif /* defined (FS_FAST) */

BoolT
istream_open PROTO_N ((istream, name))
	     PROTO_T (IStreamP istream X
		      CStringP name)
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
istream_assign PROTO_N ((to, from))
	       PROTO_T (IStreamP to X
			IStreamP from)
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
istream_is_open PROTO_N ((istream))
		PROTO_T (IStreamP istream)
{
    return (istream->name != NIL (CStringP));
}
#ifdef FS_FAST
#define istream_is_open(is) ((is)->name != NIL (CStringP))
#endif /* defined (FS_FAST) */

BoolT
istream_read_char PROTO_N ((istream, c_ref))
		  PROTO_T (IStreamP istream X
			   char    *c_ref)
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
istream_peek_char PROTO_N ((istream, c_ref))
		  PROTO_T (IStreamP istream X
			   char    *c_ref)
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
istream_read_escaped_char PROTO_N ((istream, c_ref))
			  PROTO_T (IStreamP istream X
				   char    *c_ref)
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
istream_inc_line PROTO_N ((istream))
		 PROTO_T (IStreamP istream)
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
istream_line PROTO_N ((istream))
	     PROTO_T (IStreamP istream)
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
istream_name PROTO_N ((istream))
	     PROTO_T (IStreamP istream)
{
    return (istream->name);
}
#ifdef FS_FAST
#define istream_name(is) ((is)->name)
#endif /* defined (FS_FAST) */

void
istream_close PROTO_N ((istream))
	      PROTO_T (IStreamP istream)
{
    (void) fclose (istream->file);
    if (istream != istream_input) {
	DEALLOCATE (istream->buffer);
    }
    istream_init (istream);
}

/*--------------------------------------------------------------------------*/

void
X__istream_fill_buffer PROTO_N ((istream))
		       PROTO_T (IStreamP istream)
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
