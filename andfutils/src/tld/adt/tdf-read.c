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


/*
 * tdf-read.c - TDF reader ADT.
 *
 * This file implements the TDF reader routines used by the TDF linker.
 */

#include <limits.h>

#include "tdf-read.h"
#include "../gen-errors.h"
#include <exds/common.h>
#include <exds/exception.h>
#include <exds/ostream.h>

#include "solve-cycles.h"

ExceptionT *XX_tdf_read_error = EXCEPTION("error reading TDF capsule");

static unsigned
tdf_read_nibble(TDFReaderT *reader)
{
    if (reader->new_byte) {
	switch (reader->type)EXHAUSTIVE {
	  case RT_STREAM:
	    if (bistream_read_byte(& (reader->u.bistream), & (reader->byte))) {
		reader->new_byte = FALSE;
		return(((unsigned)reader->byte >> 4) & 0xF);
	    }
	    E_unexpected_eof_in_tdf(reader);
	    THROW(XX_tdf_read_error);
	    UNREACHED;
	  case RT_STRING:
	    if (reader->u.string.current < reader->u.string.limit) {
		reader->byte     = (ByteT)(*(reader->u.string.current++));
		reader->new_byte = FALSE;
		reader->u.string.byte++;
		return(((unsigned)reader->byte >> 4) & 0xF);
	    }
	    E_unexpected_eof_in_tdf(reader);
	    THROW(XX_tdf_read_error);
	    UNREACHED;
	}
    }
    reader->new_byte = TRUE;
    return(reader->byte & 0xF);
}

BoolT
tdf_reader_open(TDFReaderT *reader,			 char *   name)
{
    reader->type     = RT_STREAM;
    reader->new_byte = TRUE;
    if (!bistream_open(& (reader->u.bistream), name)) {
	return(FALSE);
    }
    return(TRUE);
}

void
tdf_reader_open_string(TDFReaderT *reader,				char *   name, 
				NStringT *  bytes)
{
    char * contents = nstring_contents(bytes);
    unsigned length   = nstring_length(bytes);

    reader->type              = RT_STRING;
    reader->new_byte          = TRUE;
    reader->u.string.contents = contents;
    reader->u.string.current  = contents;
    reader->u.string.limit    = (contents + length);
    reader->u.string.name     = name;
    reader->u.string.byte     = 0;
}

char *
tdf_reader_name(TDFReaderT *reader)
{
    switch (reader->type)EXHAUSTIVE {
      case RT_STREAM:
	return(bistream_name(& (reader->u.bistream)));
      case RT_STRING:
	return(reader->u.string.name);
    }
    UNREACHED;
}

unsigned
tdf_reader_byte(TDFReaderT *reader)
{
    switch (reader->type)EXHAUSTIVE {
      case RT_STREAM:
	return(bistream_byte(& (reader->u.bistream)));
      case RT_STRING:
	return(reader->u.string.byte);
    }
    UNREACHED;
}

unsigned
tdf_read_int(TDFReaderT *reader)
{
    unsigned value = 0;
    unsigned limit = (UINT_MAX >> 3);

    for (;;) {
	unsigned nibble = tdf_read_nibble(reader);

	if (value > limit) {
	    E_tdf_integer_too_big_in_tdf(reader);
	    THROW(XX_tdf_read_error);
	    UNREACHED;
	}
	value <<= 3;
	value |= (nibble & 0x7);
	if (nibble & 0x8) {
	    return(value);
	}
    }
}

void
tdf_read_align(TDFReaderT *reader)
{
    reader->new_byte = TRUE;
}

void
tdf_read_bytes(TDFReaderT *reader,			NStringT *  nstring)
{
    unsigned length   = nstring_length(nstring);
    char * contents = nstring_contents(nstring);

    tdf_read_align(reader);
    switch (reader->type)EXHAUSTIVE {
      case RT_STREAM:
	if (bistream_read_chars(&(reader->u.bistream), length, contents) !=
	    length) {
	    E_unexpected_eof_in_tdf(reader);
	    THROW(XX_tdf_read_error);
	    UNREACHED;
	}
	break;
      case RT_STRING:
	if ((reader->u.string.current + length) > reader->u.string.limit) {
	    E_unexpected_eof_in_tdf(reader);
	    THROW(XX_tdf_read_error);
	    UNREACHED;
	}
	nstring_insert_cstring(nstring, reader->u.string.current);
	reader->u.string.current += length;
	reader->u.string.byte    += length;
	break;
    }
}

void
tdf_read_string(TDFReaderT *reader,			 NStringT *  nstring)
{
    unsigned size = tdf_read_int(reader);
    unsigned length;

    if (size != 8) {
	E_unsupported_char_size_in_tdf(reader, size);
	THROW(XX_tdf_read_error);
	UNREACHED;
    }
    length = tdf_read_int(reader);
    nstring_init_length(nstring, length);
    tdf_read_bytes(reader, nstring);
}

void
tdf_read_name(TDFReaderT *reader,		       NameKeyT *  name)
{
    unsigned type = ((tdf_read_nibble(reader) >> 2) & 0x3);
    NStringT nstring;
    unsigned components;
    unsigned i;

    tdf_read_align(reader);
    switch (type) {
      case 0x1:
	tdf_read_string(reader, &nstring);
	name_key_init_string(name, &nstring);
	break;
      case 0x2:
	components = tdf_read_int(reader);
	name_key_init_unique(name, components);
	for (i = 0; i < components; i++) {
	    tdf_read_string(reader, &nstring);
	    name_key_set_component(name, i, &nstring);
	}
	break;
      default:
	E_bad_name_type_in_tdf(reader, type);
	THROW(XX_tdf_read_error);
	UNREACHED;
    }
}

void
tdf_read_eof(TDFReaderT *reader)
{
    ByteT byte;

    switch (reader->type)EXHAUSTIVE {
      case RT_STREAM:
	if (bistream_read_byte(& (reader->u.bistream), &byte)) {
	    E_expected_eof_in_tdf(reader);
	    THROW(XX_tdf_read_error);
	    UNREACHED;
	}
	break;
      case RT_STRING:
	if (reader->u.string.current < reader->u.string.limit) {
	    E_expected_eof_in_tdf(reader);
	    THROW(XX_tdf_read_error);
	    UNREACHED;
	}
	break;
    }
}

void
tdf_reader_rewind(TDFReaderT *reader)
{
    switch (reader->type)EXHAUSTIVE {
      case RT_STREAM:
	bistream_rewind(& (reader->u.bistream));
	break;
      case RT_STRING:
	reader->u.string.current = reader->u.string.contents;
	break;
    }
}

void
tdf_reader_close(TDFReaderT *reader)
{
    switch (reader->type)EXHAUSTIVE {
      case RT_STREAM:
	bistream_close(& (reader->u.bistream));
	break;
      case RT_STRING:
	break;
    }
}

