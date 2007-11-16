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

#include <stdio.h>

#include "bistream.h"
#include "cstring.h"

/*--------------------------------------------------------------------------*/

ExceptionP XX_bistream_read_error = EXCEPTION("error reading from binary stream");

/*--------------------------------------------------------------------------*/

void
bistream_init(BIStreamP bistream)
{
    bistream->name = NIL(CStringP);
}

BoolT
bistream_open(BIStreamP bistream,		       CStringP  name)
{
#ifdef FS_BINARY_STDIO
    if ((bistream->file = fopen(name, "rb")) == NIL(FILE *)) {
	return(FALSE);
    }
#else
    if ((bistream->file = fopen(name, "r")) == NIL(FILE *)) {
	return(FALSE);
    }
#endif /* defined (FS_BINARY_STDIO) */
    bistream->bytes = 0;
    bistream->name  = name;
    return(TRUE);
}

void
bistream_assign(BIStreamP to,			 BIStreamP from)
{
    to->file  = from->file;
    to->bytes = from->bytes;
    to->name  = from->name;
}

BoolT
bistream_is_open(BIStreamP bistream)
{
    return(bistream->name != NIL(CStringP));
}

unsigned
bistream_read_chars(BIStreamP bistream,			     unsigned  length ,
			     CStringP  chars)
{
    unsigned bytes_read = (unsigned)fread((GenericP)chars, sizeof(char),
					   (SizeT)length, bistream->file);

    if ((bytes_read == 0) && (ferror(bistream->file))) {
	CStringP name = cstring_duplicate(bistream->name);

	THROW_VALUE(XX_bistream_read_error, name);
	UNREACHED;
    }
    bistream->bytes += bytes_read;
    return(bytes_read);
}

unsigned
bistream_read_bytes(BIStreamP bistream,			     unsigned  length ,
			     ByteP     bytes)
{
    unsigned bytes_read = (unsigned)fread((GenericP)bytes, sizeof(ByteT),
					   (SizeT)length, bistream->file);

    if ((bytes_read == 0) && (ferror(bistream->file))) {
	CStringP name = cstring_duplicate(bistream->name);

	THROW_VALUE(XX_bistream_read_error, name);
	UNREACHED;
    }
    bistream->bytes += bytes_read;
    return(bytes_read);
}

BoolT
bistream_read_byte(BIStreamP bistream,			    ByteT    *byte_ref)
{
    int byte = fgetc(bistream->file);

    if (byte == EOF) {
	if (ferror(bistream->file)) {
	    CStringP name = cstring_duplicate(bistream->name);

	    THROW_VALUE(XX_bistream_read_error, name);
	    UNREACHED;
	} else if (feof(bistream->file)) {
	    return(FALSE);
	}
    }
    bistream->bytes++;
    *byte_ref = (ByteT)byte;
    return(TRUE);
}

unsigned
bistream_byte(BIStreamP bistream)
{
    return(bistream->bytes);
}

CStringP
bistream_name(BIStreamP bistream)
{
    return(bistream->name);
}

void
bistream_rewind(BIStreamP bistream)
{
#ifdef FS_ANSI_ENVIRON
    rewind(bistream->file);
#else
   (void)fseek(bistream->file,(long)0, SEEK_SET);
#endif /* defined (FS_REWIND) */
}

void
bistream_close(BIStreamP bistream)
{
   (void)fclose(bistream->file);
    bistream_init(bistream);
}
