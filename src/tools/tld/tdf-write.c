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


/*** tdf-write.c --- TDF writer ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the TDF writer routines used by the TDF linker.
 *
 *** Change Log:
 * $Log: tdf-write.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:20  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/09/22  08:39:40  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.2  1994/12/12  11:46:58  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:39  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "tdf-write.h"
#include "gen-errors.h"
#include "ostream.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

static void
tdf_write_nibble PROTO_N ((writer, nibble))
		 PROTO_T (TDFWriterP writer X
			  unsigned   nibble)
{
    if (writer->new_byte) {
	writer->new_byte = FALSE;
	writer->byte     = (ByteT) ((nibble & 0x0F) << 4);
    } else {
	writer->new_byte = TRUE;
	writer->byte    |= (ByteT) (nibble & 0x0F);
	bostream_write_byte (&(writer->bostream), writer->byte);
    }
}

/*--------------------------------------------------------------------------*/

BoolT
tdf_writer_open PROTO_N ((writer, name))
		PROTO_T (TDFWriterP writer X
			 CStringP   name)
{
    writer->new_byte = TRUE;
    if (!bostream_open (&(writer->bostream), name)) {
	return (FALSE);
    }
    return (TRUE);
}

CStringP
tdf_writer_name PROTO_N ((writer))
		PROTO_T (TDFWriterP writer)
{
    return (bostream_name (&(writer->bostream)));
}

void
tdf_write_int PROTO_N ((writer, value))
	      PROTO_T (TDFWriterP writer X
		       unsigned   value)
{
    unsigned shift = 0;
    unsigned tmp   = value;
    unsigned mask  = (~(unsigned) 0x07);

    while (tmp & mask) {
	tmp >>= 3;
	shift ++;
    }
    while (shift) {
	tmp = ((value >> (3 * shift)) & 0x07);
	shift --;
	tdf_write_nibble (writer, tmp);
    }
    tmp = ((value & 0x07) | 0x08);
    tdf_write_nibble (writer, tmp);
}

void
tdf_write_align PROTO_N ((writer))
		PROTO_T (TDFWriterP writer)
{
    if (!(writer->new_byte)) {
	bostream_write_byte (&(writer->bostream), writer->byte);
	writer->new_byte = TRUE;
    }
}

void
tdf_write_bytes PROTO_N ((writer, nstring))
		PROTO_T (TDFWriterP writer X
			 NStringP   nstring)
{
    unsigned length   = nstring_length (nstring);
    CStringP contents = nstring_contents (nstring);

    tdf_write_align (writer);
    bostream_write_chars (&(writer->bostream), length, contents);
}

void
tdf_write_string PROTO_N ((writer, nstring))
		 PROTO_T (TDFWriterP writer X
			  NStringP   nstring)
{
    unsigned length = nstring_length (nstring);

    tdf_write_int (writer, (unsigned) 8);
    tdf_write_int (writer, length);
    tdf_write_bytes (writer, nstring);
}

void
tdf_write_name PROTO_N ((writer, name))
	       PROTO_T (TDFWriterP writer X
			NameKeyP   name)
{
    unsigned  type;
    unsigned  components;
    unsigned  i;
    NStringP  nstring;

    switch (name_key_type (name)) EXHAUSTIVE {
      case KT_STRING:
	type = (unsigned) (0x1 << 2);
	tdf_write_nibble (writer, type);
	tdf_write_align (writer);
	tdf_write_string (writer, name_key_string (name));
	break;
      case KT_UNIQUE:
	type = (unsigned) (0x2 << 2);
	tdf_write_nibble (writer, type);
	tdf_write_align (writer);
	components = name_key_components (name);
	tdf_write_int (writer, components);
	for (i = 0; i < components; i ++) {
	    nstring = name_key_get_component (name, i);
	    tdf_write_string (writer, nstring);
	}
	break;
    }
}

void
tdf_writer_close PROTO_N ((writer))
		 PROTO_T (TDFWriterP writer)
{
    tdf_write_align (writer);
    bostream_close (&(writer->bostream));
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
