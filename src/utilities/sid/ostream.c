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
 * Revision 1.1.1.1  1998/01/17  15:57:45  release
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

#include "ostream.h"
#include "cstring.h"
#include "syntax.h"

/*--------------------------------------------------------------------------*/

ExceptionP XX_ostream_write_error = EXCEPTION ("error writing to stream");

static OStreamT			ostream_output_1 = {
    NIL (FILE *),
    "<stdout>",
    "<stdout>",
    0,
    1
};
static OStreamT			ostream_error_1 = {
    NIL (FILE *),
    "<stderr>",
    "<stderr>",
    0,
    1
};

OStreamT		 *const ostream_output = &ostream_output_1;
OStreamT		 *const ostream_error  = &ostream_error_1;

/*--------------------------------------------------------------------------*/

#define OSTREAM_WRITE_ERROR_CHECK(ostream) \
if (ferror ((ostream)->file)) { \
    CStringP X___name = cstring_duplicate (ostream_name (ostream)); \
    THROW_VALUE (XX_ostream_write_error, X___name); \
}

/*--------------------------------------------------------------------------*/

void
ostream_setup PROTO_Z ()
{
    ostream_output_1.file = stdout;
    ostream_error_1.file  = stderr;
}

#ifdef FS_FAST
#undef ostream_init
#endif /* defined (FS_FAST) */
void
ostream_init PROTO_N ((ostream))
	     PROTO_T (OStreamP ostream)
{
    ostream->name = NIL (CStringP);
}
#ifdef FS_FAST
#define ostream_init(os) ((os)->name = NIL (CStringP))
#endif /* defined (FS_FAST) */

BoolT
ostream_open PROTO_N ((ostream, name))
	     PROTO_T (OStreamP ostream X
		      CStringP name)
{
    CStringP oname = name;
    CStringP pname = cstring_find_reverse (name, '@');
    if (pname != NIL (CStringP)) {
	oname = ALLOCATE_VECTOR (char, cstring_length (name) + 10);
	(void) sprintf (oname, "%.*s%d%s", (int) (pname - name), name,
			++ostream->no, pname + 1);
    }
    if ((ostream->file = fopen (oname, "w")) == NIL (FILE *)) {
	return (FALSE);
    }
    ostream->name = oname;
    ostream->gen_name = name;
    ostream->line = 1;
    (void) setvbuf (ostream->file, NIL (CStringP), _IOFBF, (SizeT) BUFSIZ);
    return (TRUE);
}

#ifdef FS_FAST
#undef ostream_is_open
#endif /* defined (FS_FAST) */
BoolT
ostream_is_open PROTO_N ((ostream))
		PROTO_T (OStreamP ostream)
{
    return (ostream->name != NIL (CStringP));
}
#ifdef FS_FAST
#define ostream_is_open(os) ((os)->name != NIL (CStringP))
#endif /* defined (FS_FAST) */

void
ostream_buffer PROTO_N ((ostream))
	       PROTO_T (OStreamP ostream)
{
    (void) setvbuf (ostream->file, NIL (CStringP), _IOFBF, (SizeT) BUFSIZ);
}

void
ostream_unbuffer PROTO_N ((ostream))
		 PROTO_T (OStreamP ostream)
{
    (void) setvbuf (ostream->file, NIL (CStringP), _IONBF, (SizeT) 0);
}

void
ostream_close PROTO_N ((ostream))
	      PROTO_T (OStreamP ostream)
{
    if (fclose (ostream->file)) {
	CStringP name = cstring_duplicate (ostream_name (ostream));

	THROW_VALUE (XX_ostream_write_error, name);
    }
    ostream_init (ostream);
}

void
ostream_flush PROTO_N ((ostream))
	      PROTO_T (OStreamP ostream)
{
    if (fflush (ostream->file)) {
	CStringP name = cstring_duplicate (ostream_name (ostream));

	THROW_VALUE (XX_ostream_write_error, name);
    }
}

#ifdef FS_FAST
#undef ostream_name
#endif /* defined (FS_FAST) */
CStringP
ostream_name PROTO_N ((ostream))
	     PROTO_T (OStreamP ostream)
{
    return (ostream->name);
}
#ifdef FS_FAST
#define ostream_name(os) ((os)->name)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef ostream_gen_name
#endif /* defined (FS_FAST) */
CStringP
ostream_gen_name PROTO_N ((ostream))
		 PROTO_T (OStreamP ostream)
{
    return (ostream->gen_name);
}
#ifdef FS_FAST
#define ostream_gen_name(os) ((os)->gen_name)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef ostream_line
#endif /* defined (FS_FAST) */
unsigned
ostream_line PROTO_N ((ostream))
	     PROTO_T (OStreamP ostream)
{
    return (ostream->line);
}
#ifdef FS_FAST
#define ostream_line(os) ((os)->line)
#endif /* defined (FS_FAST) */

void
write_newline PROTO_N ((ostream))
	      PROTO_T (OStreamP ostream)
{
    ostream->line ++;
    (void) putc ('\n', ostream->file);
    OSTREAM_WRITE_ERROR_CHECK (ostream);
}

void
write_tab PROTO_N ((ostream))
	  PROTO_T (OStreamP ostream)
{
    (void) putc ('\t', ostream->file);
    OSTREAM_WRITE_ERROR_CHECK (ostream);
}

void
write_byte PROTO_N ((ostream, c))
	   PROTO_T (OStreamP ostream X
		    ByteT    c)
{
    if (c == '\n') {
	ostream->line ++;
    }
    (void) putc ((int) c, ostream->file);
    OSTREAM_WRITE_ERROR_CHECK (ostream);
}

void
write_char PROTO_N ((ostream, c))
	   PROTO_T (OStreamP ostream X
		    char     c)
{
    if (c == '\n') {
	ostream->line ++;
    }
    (void) putc ((int) c, ostream->file);
    OSTREAM_WRITE_ERROR_CHECK (ostream);
}

void
write_escaped_char PROTO_N ((ostream, c))
		   PROTO_T (OStreamP ostream X
			    char     c)
{
    switch (c) {
      case '\0':
	(void) fputs ("\\0", ostream->file);
	break;
      case '\f':
	(void) fputs ("\\f", ostream->file);
	break;
      case '\n':
	ostream->line ++;
	(void) fputc ('\n', ostream->file);
	break;
      case '\r':
	(void) fputs ("\\r", ostream->file);
	break;
      case '\t':
	(void) fputc ('\t', ostream->file);
	break;
      case '\\':
	(void) fputs ("\\\\", ostream->file);
	break;
      default:
	if (syntax_is_printable (c)) {
	    (void) fputc ((int) c, ostream->file);
	} else {
	    (void) fprintf (ostream->file, "\\x%02x",
			    (unsigned) (unsigned char) c);
	}
    }
    OSTREAM_WRITE_ERROR_CHECK (ostream);
}

void
write_int PROTO_N ((ostream, i))
	  PROTO_T (OStreamP ostream X
		   int      i)
{
    (void) fprintf (ostream->file, "%d", i);
    OSTREAM_WRITE_ERROR_CHECK (ostream);
}

void
write_unsigned PROTO_N ((ostream, i))
	       PROTO_T (OStreamP ostream X
			unsigned i)
{
    (void) fprintf (ostream->file, "%u", i);
    OSTREAM_WRITE_ERROR_CHECK (ostream);
}

void
write_cstring PROTO_N ((ostream, cstring))
	      PROTO_T (OStreamP ostream X
		       CStringP cstring)
{
    CStringP tmp = cstring;

    while (*tmp) {
	if (*tmp ++ == '\n') {
	    ostream->line ++;
	}
    }
    (void) fputs (cstring, ostream->file);
    OSTREAM_WRITE_ERROR_CHECK (ostream);
}

void
write_bytes PROTO_N ((ostream, bytes, length))
	    PROTO_T (OStreamP ostream X
		     ByteP    bytes X
		     unsigned length)
{
    unsigned tmp_length = length;
    ByteP    tmp_bytes  = bytes;

    while (tmp_length --) {
	if (*tmp_bytes ++ == '\n') {
	    ostream->line ++;
	}
    }
    (void) fwrite ((GenericP) bytes, sizeof (ByteT), (SizeT) length,
		   ostream->file);
    OSTREAM_WRITE_ERROR_CHECK (ostream);
}

void
write_chars PROTO_N ((ostream, chars, length))
	    PROTO_T (OStreamP ostream X
		     CStringP chars X
		     unsigned length)
{
    while (length --) {
	write_char (ostream, *chars ++);
    }
}

void
write_escaped_chars PROTO_N ((ostream, chars, length))
		    PROTO_T (OStreamP ostream X
			     CStringP chars X
			     unsigned length)
{
    while (length --) {
	write_escaped_char (ostream, *chars ++);
    }
}

void
write_system_error PROTO_N ((ostream))
		   PROTO_T (OStreamP ostream)
{
#if (defined (FS_STRERROR) || defined (FS_SYS_ERRLIST))
# ifdef FS_STRERROR
    CStringP message = strerror (errno);
# else
    CStringP message;

    if ((errno >= 0) && (errno < sys_nerr)) {
	message = sys_errlist [errno];
    } else {
	message = "unknown error";
    }
# endif /* defined (FS_STRERROR) */
    write_cstring (ostream, message);
#else
    write_cstring (ostream, "error ");
    write_int (ostream, errno);
#endif /* (defined (FS_STRERROR) || defined (FS_SYS_ERRLIST)) */
}

void
write_pointer PROTO_N ((ostream, pointer))
	      PROTO_T (OStreamP ostream X
		       GenericP pointer)
{
    (void) fprintf (ostream->file, "%p", pointer);
    OSTREAM_WRITE_ERROR_CHECK (ostream);
}
