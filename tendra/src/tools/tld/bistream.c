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


/**** bistream.c --- Binary input stream handling.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the binary input stream facility specified in the file
 * "bistream.h".  See that file for more details.
 *
 **** Change Log:
 * $Log: bistream.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:17  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:45:16  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:12  smf
 * Initial import of os-interface shared files.
 *
**/

/****************************************************************************/

#include "bistream.h"
#include "cstring.h"

/*--------------------------------------------------------------------------*/

ExceptionP XX_bistream_read_error = EXCEPTION ("error reading from binary stream");

/*--------------------------------------------------------------------------*/

void
bistream_init PROTO_N ((bistream))
	      PROTO_T (BIStreamP bistream)
{
    bistream->name = NIL (CStringP);
}

BoolT
bistream_open PROTO_N ((bistream, name))
	      PROTO_T (BIStreamP bistream X
		       CStringP  name)
{
#ifdef FS_BINARY_STDIO
    if ((bistream->file = fopen (name, "rb")) == NIL (FILE *)) {
	return (FALSE);
    }
#else
    if ((bistream->file = fopen (name, "r")) == NIL (FILE *)) {
	return (FALSE);
    }
#endif /* defined (FS_BINARY_STDIO) */
    bistream->bytes = 0;
    bistream->name  = name;
    return (TRUE);
}

void
bistream_assign PROTO_N ((to, from))
		PROTO_T (BIStreamP to X
			 BIStreamP from)
{
    to->file  = from->file;
    to->bytes = from->bytes;
    to->name  = from->name;
}

BoolT
bistream_is_open PROTO_N ((bistream))
		 PROTO_T (BIStreamP bistream)
{
    return (bistream->name != NIL (CStringP));
}

unsigned
bistream_read_chars PROTO_N ((bistream, length, chars))
		    PROTO_T (BIStreamP bistream X
			     unsigned  length X
			     CStringP  chars)
{
    unsigned bytes_read = (unsigned) fread ((GenericP) chars, sizeof (char),
					    (SizeT) length, bistream->file);

    if ((bytes_read == 0) && (ferror (bistream->file))) {
	CStringP name = cstring_duplicate (bistream->name);

	THROW_VALUE (XX_bistream_read_error, name);
	UNREACHED;
    }
    bistream->bytes += bytes_read;
    return (bytes_read);
}

unsigned
bistream_read_bytes PROTO_N ((bistream, length, bytes))
		    PROTO_T (BIStreamP bistream X
			     unsigned  length X
			     ByteP     bytes)
{
    unsigned bytes_read = (unsigned) fread ((GenericP) bytes, sizeof (ByteT),
					    (SizeT) length, bistream->file);

    if ((bytes_read == 0) && (ferror (bistream->file))) {
	CStringP name = cstring_duplicate (bistream->name);

	THROW_VALUE (XX_bistream_read_error, name);
	UNREACHED;
    }
    bistream->bytes += bytes_read;
    return (bytes_read);
}

BoolT
bistream_read_byte PROTO_N ((bistream, byte_ref))
		   PROTO_T (BIStreamP bistream X
			    ByteT    *byte_ref)
{
    int byte = fgetc (bistream->file);

    if (byte == EOF) {
	if (ferror (bistream->file)) {
	    CStringP name = cstring_duplicate (bistream->name);

	    THROW_VALUE (XX_bistream_read_error, name);
	    UNREACHED;
	} else if (feof (bistream->file)) {
	    return (FALSE);
	}
    }
    bistream->bytes ++;
    *byte_ref = (ByteT) byte;
    return (TRUE);
}

unsigned
bistream_byte PROTO_N ((bistream))
	      PROTO_T (BIStreamP bistream)
{
    return (bistream->bytes);
}

CStringP
bistream_name PROTO_N ((bistream))
	      PROTO_T (BIStreamP bistream)
{
    return (bistream->name);
}

void
bistream_rewind PROTO_N ((bistream))
		PROTO_T (BIStreamP bistream)
{
#ifdef FS_ANSI_ENVIRON
    rewind (bistream->file);
#else
    (void) fseek (bistream->file, (long) 0, SEEK_SET);
#endif /* defined (FS_REWIND) */
}

void
bistream_close PROTO_N ((bistream))
	       PROTO_T (BIStreamP bistream)
{
    (void) fclose (bistream->file);
    bistream_init (bistream);
}
