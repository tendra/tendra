/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * tdf-write.c - TDF writer ADT.
 *
 * This file implements the TDF writer routines used by the TDF linker.
 */

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/ostream.h>

#include "tdf-write.h"
#include "solve-cycles.h"


static void
tdf_write_nibble(TDFWriterT *writer,			  unsigned   nibble)
{
    if (writer->new_byte) {
	writer->new_byte = FALSE;
	writer->byte     = (ByteT)((nibble & 0x0F) << 4);
    } else {
	writer->new_byte = TRUE;
	writer->byte    |= (ByteT)(nibble & 0x0F);
	bostream_write_byte(& (writer->bostream), writer->byte);
    }
}

BoolT
tdf_writer_open(TDFWriterT *writer,			 char *   name)
{
    writer->new_byte = TRUE;
    if (!bostream_open(& (writer->bostream), name)) {
	return FALSE;
    }
    return TRUE;
}

const char *
tdf_writer_name(TDFWriterT *writer)
{
    return bostream_name(&writer->bostream);
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
    size_t length   = nstring_length(nstring);
    char * contents = nstring_contents(nstring);

    tdf_write_align(writer);
    bostream_write_chars(& (writer->bostream), length, contents);
}

void
tdf_write_string(TDFWriterT *writer,			  NStringT *  nstring)
{
    size_t length = nstring_length(nstring);

    tdf_write_int(writer, 8);
    tdf_write_int(writer, (unsigned) length);
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
