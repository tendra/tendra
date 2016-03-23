/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * tdf-read.c - TDF reader ADT.
 *
 * This file implements the TDF reader routines used by the TDF linker.
 */

#include <limits.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/ostream.h>

#include <shared/check.h>
#include <shared/error.h>

#include "tdf-read.h"
#include "solve-cycles.h"


ExceptionT *XX_tdf_read_error = EXCEPTION("error reading TDF capsule");

static unsigned
tdf_read_nibble(TDFReaderT *reader)
{
    if (reader->new_byte) {
	switch (reader->type) {
	  case RT_STREAM:
	    if (bistream_read_byte(& (reader->u.bistream), & (reader->byte))) {
		reader->new_byte = FALSE;
		return ((unsigned) reader->byte >> 4) & 0xF;
	    }
		error(ERR_SERIOUS, "%s: #%u: unexpected end of file", 
			tdf_reader_name(reader), (unsigned) tdf_reader_byte(reader));
	    THROW(XX_tdf_read_error);
	    UNREACHED;
	  case RT_STRING:
	    if (reader->u.string.current < reader->u.string.limit) {
		reader->byte     = (ByteT)(*(reader->u.string.current++));
		reader->new_byte = FALSE;
		reader->u.string.byte++;
		return ((unsigned) reader->byte >> 4) & 0xF;
	    }
	error(ERR_SERIOUS, "%s: #%u: unexpected end of file", 
		tdf_reader_name(reader), (unsigned) tdf_reader_byte(reader));
	    THROW(XX_tdf_read_error);
	    UNREACHED;
	}
    }
    reader->new_byte = TRUE;
    return reader->byte & 0xF;
}

BoolT
tdf_reader_open(TDFReaderT *reader,			 const char *   name)
{
    reader->type     = RT_STREAM;
    reader->new_byte = TRUE;
    if (!bistream_open(& (reader->u.bistream), name)) {
	return FALSE;
    }
    return TRUE;
}

void
tdf_reader_open_string(TDFReaderT *reader,				char *   name, 
				NStringT *  bytes)
{
    char * contents = nstring_contents(bytes);
    size_t length   = nstring_length(bytes);

    reader->type              = RT_STRING;
    reader->new_byte          = TRUE;
    reader->u.string.contents = contents;
    reader->u.string.current  = contents;
    reader->u.string.limit    = (contents + length);
    reader->u.string.name     = name;
    reader->u.string.byte     = 0;
}

const char *
tdf_reader_name(TDFReaderT *reader)
{
    switch (reader->type) {
      case RT_STREAM:
	return bistream_name(&reader->u.bistream);
      case RT_STRING:
	return reader->u.string.name;
    }
    UNREACHED;
}

size_t
tdf_reader_byte(TDFReaderT *reader)
{
    switch (reader->type) {
      case RT_STREAM:
	return bistream_byte(&reader->u.bistream);
      case RT_STRING:
	return reader->u.string.byte;
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
		error(ERR_SERIOUS, "%s: #%u: TDF integer is "
			"too large for this machine", 
			tdf_reader_name(reader), (unsigned) tdf_reader_byte(reader));
	    THROW(XX_tdf_read_error);
	    UNREACHED;
	}
	value <<= 3;
	value |= (nibble & 0x7);
	if (nibble & 0x8) {
	    return value;
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
    size_t length   = nstring_length(nstring);
    char * contents = nstring_contents(nstring);

    tdf_read_align(reader);
    switch (reader->type) {
      case RT_STREAM:
	if (bistream_read_chars(&(reader->u.bistream), length, contents) !=
	    length) {
	error(ERR_SERIOUS, "%s: #%u: unexpected end of file", 
		tdf_reader_name(reader), (unsigned) tdf_reader_byte(reader));
	    THROW(XX_tdf_read_error);
	    UNREACHED;
	}
	break;
      case RT_STRING:
	if ((reader->u.string.current + length) > reader->u.string.limit) {
		error(ERR_SERIOUS, "%s: #%u: unexpected end of file", 
			tdf_reader_name(reader), (unsigned) tdf_reader_byte(reader));
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
    size_t length;

    if (size != 8) {
	error(ERR_SERIOUS, "%s: #%u: string character size %u "
		"is not supported on this machine", 
		tdf_reader_name(reader), (unsigned) tdf_reader_byte(reader), size);
	THROW(XX_tdf_read_error);
	UNREACHED;
    }
    length = (size_t) tdf_read_int(reader);
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
	error(ERR_SERIOUS, "%s: #%u: name type %u is unknown", 
		tdf_reader_name(reader), (unsigned) tdf_reader_byte(reader), type);
	THROW(XX_tdf_read_error);
	UNREACHED;
    }
}

void
tdf_read_eof(TDFReaderT *reader)
{
    ByteT byte;

    switch (reader->type) {
      case RT_STREAM:
	if (bistream_read_byte(& (reader->u.bistream), &byte)) {
	error(ERR_SERIOUS, "%s: #%u: expected end of file", 
		tdf_reader_name(reader), (unsigned) tdf_reader_byte(reader));
	    THROW(XX_tdf_read_error);
	    UNREACHED;
	}
	break;
      case RT_STRING:
	if (reader->u.string.current < reader->u.string.limit) {
	error(ERR_SERIOUS, "%s: #%u: expected end of file", 
		tdf_reader_name(reader), (unsigned) tdf_reader_byte(reader));
	    THROW(XX_tdf_read_error);
	    UNREACHED;
	}
	break;
    }
}

void
tdf_reader_rewind(TDFReaderT *reader)
{
    switch (reader->type) {
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
    switch (reader->type) {
      case RT_STREAM:
	bistream_close(& (reader->u.bistream));
	break;
      case RT_STRING:
	break;
    }
}
