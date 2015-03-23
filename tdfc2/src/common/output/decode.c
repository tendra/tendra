/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/buffer.h>

#include <parse/char.h>
#include <parse/file.h>
#include <parse/literal.h>

#include <output/decode.h>
#include <output/encode.h>


/*
    This routine fills the bitstream bs from its associated file.  It
    returns the number of bytes read.
*/

static unsigned
fill_bitstream(BITSTREAM *bs)
{
	unsigned sz;
	FILE *f = bs->file;
	string text = bs->text;
	sz = (unsigned)fread(text, sizeof(character),
			     (size_t)CHUNK_SIZE, f);
	if (sz == 0) {
		/* No more characters in file */
		bs->link = text;
		while (sz < CHUNK_SIZE) {
			/* Fill buffer with all ones */
			text[sz] = (character)BYTE_MASK;
			sz++;
		}
	}
	bs->size = sz;
	return sz;
}


/*
    This routine checks whether the end of the file associated with the
    bitstream bs has been precisely reached.  Note that the link field
    is set to a non-null value by fill_bitstream if the end of file is
    encountered.
*/

int
de_eof(BITSTREAM *bs)
{
	if (bs->link) {
		return 0;
	}
	if (bs->bytes >= bs->size) {
		IGNORE fill_bitstream(bs);
		if (bs->link) {
			return 1;
		}
	}
	return 0;
}


/*
    This array gives the bit masks for values up to 16 bits.
*/

static unsigned long bit_mask[17] = {
	0x0000,
	0x0001UL, 0x0003UL, 0x0007UL, 0x000fUL,
	0x001fUL, 0x003fUL, 0x007fUL, 0x00ffUL,
	0x01ffUL, 0x03ffUL, 0x07ffUL, 0x0fffUL,
	0x1fffUL, 0x3fffUL, 0x7fffUL, 0xffffUL
};


/*
    This routine reads the next n bits from the bitstream bs.  n will be
    at most 16.
*/

unsigned
de_bits(BITSTREAM *bs, unsigned n)
{
	unsigned long d = 0;
	string text = bs->text;
	unsigned sz = bs->size;
	unsigned bytes = bs->bytes;
	unsigned bits = 0;

	/* Build up result */
	unsigned m = n + bs->bits;
	while (m) {
		unsigned b;
		unsigned long c;

		/* Refill buffer from file if necessary */
		if (bytes >= sz) {
			sz = fill_bitstream(bs);
			bytes = 0;
			bits = 0;
		}

		/* Get next character */
		c = (unsigned long)text[bytes];
		d = ((d << BYTE_SIZE) | c);
		b = BYTE_SIZE - bits;
		if (m < b) {
			d >>= (b - m);
			bits += m;
			m = 0;
		} else {
			bits += b;
			m -= b;
		}
		if (bits == BYTE_SIZE) {
			bits = 0;
			bytes++;
		}
	}
	bs->bytes = bytes;
	bs->bits = bits;
	d &= bit_mask[n];
	return (unsigned)d;
}


/*
    This routine is identical to de_bits except that it works for up to
    32 bits.
*/

unsigned long
de_long_bits(BITSTREAM *bs, unsigned n)
{
	unsigned long a, b;
	if (n > 16) {
		a = (unsigned long)de_bits(bs, n - 16);
		n = 16;
	} else {
		a = 0;
	}
	b = (unsigned long)de_bits(bs, n);
	return (a << 16) | b;
}


/*
    This routine reads an integer as a series of octal digits from the
    bitstream bs.
*/

unsigned long
de_int(BITSTREAM *bs)
{
	unsigned long d, n = 0;
	for (;;) {
		d = (unsigned long)de_bits(bs,(unsigned)4);
		if (d & 0x8) {
			break;
		}
		n = ((n << 3) | d);
	}
	n = ((n << 3) | (d & 0x7));
	return n;
}


/*
    This routine reads enough bits from the bitstream bs to align it to
    the next byte boundary.
*/

void
de_boundary(BITSTREAM *bs)
{
	unsigned bits = bs->bits;
	if (bits) {
		IGNORE de_bits(bs, BYTE_SIZE - bits);
	}
	return;
}


/*
    This routine reads a string from the bitstream bs into the buffer bf.
*/

void
de_tdfstring(BITSTREAM *bs, BUFFER *bf)
{
	unsigned m = (unsigned)de_int(bs);
	unsigned long n = de_int(bs);
	string p = stretch_buffer(bf, bf->posn, n);
	bf->posn = p + n;
	while (n) {
		int ch = CHAR_SIMPLE;
		unsigned long c = (unsigned long)de_bits(bs, m);
		c = from_ascii(c, &ch);
		*(p++) = (character)c;
		n--;
	}
	*p = 0;
	return;
}
