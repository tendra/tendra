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


/**** bostream.c --- Binary output stream handling.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the binary output stream facility specified in the
 * file "bostream.h".  See that file for more details.
 *
 **** Change Log:
 * $Log: bostream.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:17  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:45:21  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:14  smf
 * Initial import of os-interface shared files.
 *
**/

/****************************************************************************/

#include "bostream.h"
#include "cstring.h"

/*--------------------------------------------------------------------------*/

ExceptionP XX_bostream_write_error = EXCEPTION ("error writing to binary stream");

/*--------------------------------------------------------------------------*/

void
bostream_init PROTO_N ((bostream))
	      PROTO_T (BOStreamP bostream)
{
    bostream->name = NIL (CStringP);
}

BoolT
bostream_open PROTO_N ((bostream, name))
	      PROTO_T (BOStreamP bostream X
		       CStringP  name)
{
#ifdef FS_BINARY_STDIO
    if ((bostream->file = fopen (name, "wb")) == NIL (FILE *)) {
	return (FALSE);
    }
#else
    if ((bostream->file = fopen (name, "w")) == NIL (FILE *)) {
	return (FALSE);
    }
#endif /* defined (FS_BINARY_STDIO) */
    bostream->name  = name;
    return (TRUE);
}

void
bostream_assign PROTO_N ((to, from))
		PROTO_T (BOStreamP to X
			 BOStreamP from)
{
    to->file  = from->file;
    to->name  = from->name;
}

BoolT
bostream_is_open PROTO_N ((bostream))
		 PROTO_T (BOStreamP bostream)
{
    return (bostream->name != NIL (CStringP));
}

void
bostream_write_chars PROTO_N ((bostream, length, chars))
		     PROTO_T (BOStreamP bostream X
			      unsigned  length X
			      CStringP  chars)
{
    unsigned bytes_read = (unsigned) fwrite ((GenericP) chars, sizeof (char),
					     (SizeT) length, bostream->file);

    if ((bytes_read != length) && (ferror (bostream->file))) {
	CStringP name = cstring_duplicate (bostream->name);

	THROW_VALUE (XX_bostream_write_error, name);
	UNREACHED;
    }
}

void
bostream_write_bytes PROTO_N ((bostream, length, bytes))
		     PROTO_T (BOStreamP bostream X
			      unsigned  length X
			      ByteP     bytes)
{
    unsigned bytes_read = (unsigned) fwrite ((GenericP) bytes, sizeof (ByteT),
					     (SizeT) length, bostream->file);

    if ((bytes_read != length) && (ferror (bostream->file))) {
	CStringP name = cstring_duplicate (bostream->name);

	THROW_VALUE (XX_bostream_write_error, name);
	UNREACHED;
    }
}

void
bostream_write_byte PROTO_N ((bostream, byte))
		    PROTO_T (BOStreamP bostream X
			     ByteT     byte)
{
    if ((fputc ((int) byte, bostream->file) == EOF) &&
	(ferror (bostream->file))) {
	CStringP name = cstring_duplicate (bostream->name);

	THROW_VALUE (XX_bostream_write_error, name);
	UNREACHED;
    }
}

CStringP
bostream_name PROTO_N ((bostream))
	      PROTO_T (BOStreamP bostream)
{
    return (bostream->name);
}

void
bostream_close PROTO_N ((bostream))
	       PROTO_T (BOStreamP bostream)
{
    if (fclose (bostream->file)) {
	CStringP name = cstring_duplicate (bostream->name);

	THROW_VALUE (XX_bostream_write_error, name);
	UNREACHED;
    }
    bostream_init (bostream);
}
