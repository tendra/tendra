/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef TDF_BITSTREAM_H
#define TDF_BITSTREAM_H


/*
 * TYPE REPRESENTING A SERIES OF BITS
 *
 * A bitstream consists of an array of characters comprising the bits
 * themselves, plus the current offset (in bytes and bits) of the end of these
 * bits. A pointer to the previous bitstream is used to chain bitstreams
 * together.
 *
 * Bits are buffered up in byte-sized chunks; this is always an unsigned char
 * (and so code may rely on that), but is given its own typedef to avoid
 * confusion with other similar things.
 */

typedef unsigned char bitstream_byte;

typedef struct bits_tag {
	bitstream_byte *text;
	unsigned bytes;
	unsigned bits;
	unsigned size;
	FILE *file;
	void *link;
	struct bits_tag *prev;
} BITSTREAM;


#endif
