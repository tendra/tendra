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

ExceptionP XX_bostream_write_error = EXCEPTION("error writing to binary stream");

/*--------------------------------------------------------------------------*/

void
bostream_init(BOStreamP bostream)
{
    bostream->name = NIL(CStringP);
}

BoolT
bostream_open(BOStreamP bostream,		       CStringP  name)
{
#ifdef FS_BINARY_STDIO
    if ((bostream->file = fopen(name, "wb")) == NIL(FILE *)) {
	return(FALSE);
    }
#else
    if ((bostream->file = fopen(name, "w")) == NIL(FILE *)) {
	return(FALSE);
    }
#endif /* defined (FS_BINARY_STDIO) */
    bostream->name  = name;
    return(TRUE);
}

void
bostream_assign(BOStreamP to,			 BOStreamP from)
{
    to->file  = from->file;
    to->name  = from->name;
}

BoolT
bostream_is_open(BOStreamP bostream)
{
    return(bostream->name != NIL(CStringP));
}

void
bostream_write_chars(BOStreamP bostream,			      unsigned  length ,
			      CStringP  chars)
{
    unsigned bytes_read = (unsigned)fwrite((void *)chars, sizeof(char),
					    (SizeT)length, bostream->file);

    if ((bytes_read != length) && (ferror(bostream->file))) {
	CStringP name = cstring_duplicate(bostream->name);

	THROW_VALUE(XX_bostream_write_error, name);
	UNREACHED;
    }
}

void
bostream_write_bytes(BOStreamP bostream,			      unsigned  length ,
			      ByteP     bytes)
{
    unsigned bytes_read = (unsigned)fwrite((void *)bytes, sizeof(ByteT),
					    (SizeT)length, bostream->file);

    if ((bytes_read != length) && (ferror(bostream->file))) {
	CStringP name = cstring_duplicate(bostream->name);

	THROW_VALUE(XX_bostream_write_error, name);
	UNREACHED;
    }
}

void
bostream_write_byte(BOStreamP bostream,			     ByteT     byte)
{
    if ((fputc((int)byte, bostream->file) == EOF) &&
	(ferror(bostream->file))) {
	CStringP name = cstring_duplicate(bostream->name);

	THROW_VALUE(XX_bostream_write_error, name);
	UNREACHED;
    }
}

CStringP
bostream_name(BOStreamP bostream)
{
    return(bostream->name);
}

void
bostream_close(BOStreamP bostream)
{
    if (fclose(bostream->file)) {
	CStringP name = cstring_duplicate(bostream->name);

	THROW_VALUE(XX_bostream_write_error, name);
	UNREACHED;
    }
    bostream_init(bostream);
}
