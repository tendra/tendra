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


/*** tdf-read.c --- TDF reader ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the TDF reader routines used by the TDF linker.
 *
 *** Change Log:
 * $Log: tdf-read.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:20  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:37  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:46:55  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:38  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "tdf-read.h"
#include "gen-errors.h"
#include "ostream.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

ExceptionP XX_tdf_read_error = EXCEPTION ("error reading TDF capsule");

/*--------------------------------------------------------------------------*/

static unsigned
tdf_read_nibble PROTO_N ((reader))
		PROTO_T (TDFReaderP reader)
{
    if (reader->new_byte) {
	switch (reader->type) EXHAUSTIVE {
	  case RT_STREAM:
	    if (bistream_read_byte (&(reader->u.bistream), &(reader->byte))) {
		reader->new_byte = FALSE;
		return (((unsigned) reader->byte >> 4) & 0xF);
	    }
	    E_unexpected_eof_in_tdf (reader);
	    THROW (XX_tdf_read_error);
	    UNREACHED;
	  case RT_STRING:
	    if (reader->u.string.current < reader->u.string.limit) {
		reader->byte     = (ByteT) (*(reader->u.string.current ++));
		reader->new_byte = FALSE;
		reader->u.string.byte ++;
		return (((unsigned) reader->byte >> 4) & 0xF);
	    }
	    E_unexpected_eof_in_tdf (reader);
	    THROW (XX_tdf_read_error);
	    UNREACHED;
	}
    }
    reader->new_byte = TRUE;
    return (reader->byte & 0xF);
}

/*--------------------------------------------------------------------------*/

BoolT
tdf_reader_open PROTO_N ((reader, name))
		PROTO_T (TDFReaderP reader X
			 CStringP   name)
{
    reader->type     = RT_STREAM;
    reader->new_byte = TRUE;
    if (!bistream_open (&(reader->u.bistream), name)) {
	return (FALSE);
    }
    return (TRUE);
}

void
tdf_reader_open_string PROTO_N ((reader, name, bytes))
		       PROTO_T (TDFReaderP reader X
				CStringP   name X
				NStringP   bytes)
{
    CStringP contents = nstring_contents (bytes);
    unsigned length   = nstring_length (bytes);

    reader->type              = RT_STRING;
    reader->new_byte          = TRUE;
    reader->u.string.contents = contents;
    reader->u.string.current  = contents;
    reader->u.string.limit    = (contents + length);
    reader->u.string.name     = name;
    reader->u.string.byte     = 0;
}

CStringP
tdf_reader_name PROTO_N ((reader))
		PROTO_T (TDFReaderP reader)
{
    switch (reader->type) EXHAUSTIVE {
      case RT_STREAM:
	return (bistream_name (&(reader->u.bistream)));
      case RT_STRING:
	return (reader->u.string.name);
    }
    UNREACHED;
}

unsigned
tdf_reader_byte PROTO_N ((reader))
		PROTO_T (TDFReaderP reader)
{
    switch (reader->type) EXHAUSTIVE {
      case RT_STREAM:
	return (bistream_byte (&(reader->u.bistream)));
      case RT_STRING:
	return (reader->u.string.byte);
    }
    UNREACHED;
}

unsigned
tdf_read_int PROTO_N ((reader))
	     PROTO_T (TDFReaderP reader)
{
    unsigned value = 0;
    unsigned limit = (UINT_MAX >> 3);

    for (;;) {
	unsigned nibble = tdf_read_nibble (reader);

	if (value > limit) {
	    E_tdf_integer_too_big_in_tdf (reader);
	    THROW (XX_tdf_read_error);
	    UNREACHED;
	}
	value <<= 3;
	value |= (nibble & 0x7);
	if (nibble & 0x8) {
	    return (value);
	}
    }
}

void
tdf_read_align PROTO_N ((reader))
	       PROTO_T (TDFReaderP reader)
{
    reader->new_byte = TRUE;
}

void
tdf_read_bytes PROTO_N ((reader, nstring))
	       PROTO_T (TDFReaderP reader X
			NStringP   nstring)
{
    unsigned length   = nstring_length (nstring);
    CStringP contents = nstring_contents (nstring);

    tdf_read_align (reader);
    switch (reader->type) EXHAUSTIVE {
      case RT_STREAM:
	if (bistream_read_chars (&(reader->u.bistream), length, contents) !=
	    length) {
	    E_unexpected_eof_in_tdf (reader);
	    THROW (XX_tdf_read_error);
	    UNREACHED;
	}
	break;
      case RT_STRING:
	if ((reader->u.string.current + length) > reader->u.string.limit) {
	    E_unexpected_eof_in_tdf (reader);
	    THROW (XX_tdf_read_error);
	    UNREACHED;
	}
	nstring_insert_cstring (nstring, reader->u.string.current);
	reader->u.string.current += length;
	reader->u.string.byte    += length;
	break;
    }
}

void
tdf_read_string PROTO_N ((reader, nstring))
		PROTO_T (TDFReaderP reader X
			 NStringP   nstring)
{
    unsigned size = tdf_read_int (reader);
    unsigned length;

    if (size != 8) {
	E_unsupported_char_size_in_tdf (reader, size);
	THROW (XX_tdf_read_error);
	UNREACHED;
    }
    length = tdf_read_int (reader);
    nstring_init_length (nstring, length);
    tdf_read_bytes (reader, nstring);
}

void
tdf_read_name PROTO_N ((reader, name))
	      PROTO_T (TDFReaderP reader X
		       NameKeyP   name)
{
    unsigned type = ((tdf_read_nibble (reader) >> 2) & 0x3);
    NStringT nstring;
    unsigned components;
    unsigned i;

    tdf_read_align (reader);
    switch (type) {
      case 0x1:
	tdf_read_string (reader, &nstring);
	name_key_init_string (name, &nstring);
	break;
      case 0x2:
	components = tdf_read_int (reader);
	name_key_init_unique (name, components);
	for (i = 0; i < components; i ++) {
	    tdf_read_string (reader, &nstring);
	    name_key_set_component (name, i, &nstring);
	}
	break;
      default:
	E_bad_name_type_in_tdf (reader, type);
	THROW (XX_tdf_read_error);
	UNREACHED;
    }
}

void
tdf_read_eof PROTO_N ((reader))
	     PROTO_T (TDFReaderP reader)
{
    ByteT byte;

    switch (reader->type) EXHAUSTIVE {
      case RT_STREAM:
	if (bistream_read_byte (&(reader->u.bistream), &byte)) {
	    E_expected_eof_in_tdf (reader);
	    THROW (XX_tdf_read_error);
	    UNREACHED;
	}
	break;
      case RT_STRING:
	if (reader->u.string.current < reader->u.string.limit) {
	    E_expected_eof_in_tdf (reader);
	    THROW (XX_tdf_read_error);
	    UNREACHED;
	}
	break;
    }
}

void
tdf_reader_rewind PROTO_N ((reader))
		  PROTO_T (TDFReaderP reader)
{
    switch (reader->type) EXHAUSTIVE {
      case RT_STREAM:
	bistream_rewind (&(reader->u.bistream));
	break;
      case RT_STRING:
	reader->u.string.current = reader->u.string.contents;
	break;
    }
}

void
tdf_reader_close PROTO_N ((reader))
		 PROTO_T (TDFReaderP reader)
{
    switch (reader->type) EXHAUSTIVE {
      case RT_STREAM:
	bistream_close (&(reader->u.bistream));
	break;
      case RT_STRING:
	break;
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
