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
 * tdf-write.c - TDF writer ADT.
 *
 * This file implements the TDF writer routines used by the TDF linker.
 */

#include <stdint.h>

#include "tdf-write.h"
#include "solve-cycles.h"

#include "errors/gen-errors.h"

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/ostream.h>


static void
tdf_write_nibble(TDFWriterT *writer,			  unsigned   nibble)
{
    if (writer->new_byte) {
	writer->new_byte = FALSE;
	writer->byte     = (uint8_t)((nibble & 0x0F) << 4);
    } else {
	writer->new_byte = TRUE;
	writer->byte    |= (uint8_t)(nibble & 0x0F);
	bostream_write_byte(& (writer->bostream), writer->byte);
    }
}

BoolT
tdf_writer_open(TDFWriterT *writer,			 char *   name)
{
    writer->new_byte = TRUE;
    if (!bostream_open(& (writer->bostream), name)) {
	return(FALSE);
    }
    return(TRUE);
}

const char *
tdf_writer_name(TDFWriterT *writer)
{
    return(bostream_name(& (writer->bostream)));
}

void
tdf_write_int(TDFWriterT *writer,		       unsigned   value)
{
    unsigned shift = 0;
    unsigned tmp   = value;
    unsigned mask  = (~(unsigned)0x07);

    while (tmp & mask) {
	tmp >>= 3;
	shift++;
    }
    while (shift) {
	tmp = ((value >> (3 * shift)) & 0x07);
	shift--;
	tdf_write_nibble(writer, tmp);
    }
    tmp = ((value & 0x07) | 0x08);
    tdf_write_nibble(writer, tmp);
}

void
tdf_write_align(TDFWriterT *writer)
{
    if (!(writer->new_byte)) {
	bostream_write_byte(& (writer->bostream), writer->byte);
	writer->new_byte = TRUE;
    }
}

void
tdf_write_bytes(TDFWriterT *writer,			 NStringT *  nstring)
{
    unsigned length   = nstring_length(nstring);
    char * contents = nstring_contents(nstring);

    tdf_write_align(writer);
    bostream_write_chars(& (writer->bostream), length, contents);
}

void
tdf_write_string(TDFWriterT *writer,			  NStringT *  nstring)
{
    unsigned length = nstring_length(nstring);

    tdf_write_int(writer,(unsigned)8);
    tdf_write_int(writer, length);
    tdf_write_bytes(writer, nstring);
}

void
tdf_write_name(TDFWriterT *writer,			NameKeyT *  name)
{
    unsigned  type;
    unsigned  components;
    unsigned  i;
    NStringT * nstring;

    switch (name_key_type(name)) {
      case KT_STRING:
	type = (unsigned)(0x1 << 2);
	tdf_write_nibble(writer, type);
	tdf_write_align(writer);
	tdf_write_string(writer, name_key_string(name));
	break;
      case KT_UNIQUE:
	type = (unsigned)(0x2 << 2);
	tdf_write_nibble(writer, type);
	tdf_write_align(writer);
	components = name_key_components(name);
	tdf_write_int(writer, components);
	for (i = 0; i < components; i++) {
	    nstring = name_key_get_component(name, i);
	    tdf_write_string(writer, nstring);
	}
	break;
    }
}

void
tdf_writer_close(TDFWriterT *writer)
{
    tdf_write_align(writer);
    bostream_close(& (writer->bostream));
}

