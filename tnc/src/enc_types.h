/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef ENC_TYPES_H
#define ENC_TYPES_H


/*
    TYPE REPRESENTING A BITSTREAM

    A bitstream consists of a table, source, of length bytes.  The
    current position in the table is given by the bytes and bits fields.
    Bitstreams may be linked via the next field.  The end field of the
    first bitstream in a list points to the last bitstream in that list.
*/

typedef struct x_bitstream {
	unsigned int bytes;
	unsigned int bits;
	unsigned int length;
	byte *source;
	struct x_bitstream *next;
	struct x_bitstream *end;
} bitstream;


#endif /* ENC_TYPES_H */
