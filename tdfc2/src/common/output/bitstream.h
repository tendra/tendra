/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef BITSTREAM_INCLUDED
#define BITSTREAM_INCLUDED


/*
 * TYPE REPRESENTING A SERIES OF BITS
 *
 * A bitstream consists of an array of characters comprising the bits
 * themselves, plus the current offset (in bytes and bits) of the end of these
 * bits. A pointer to the previous bitstream is used to chain bitstreams
 * together.
*/

typedef struct bits_tag {
	string text;
	unsigned bytes;
	unsigned bits;
	unsigned size;
	FILE *file;
	void *link;
	struct bits_tag *prev;
} BITSTREAM;


#endif
