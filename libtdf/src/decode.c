/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include <tdf/bitstream.h>
#include <tdf/decode.h>


/*
 * This routine fills the bitstream bs from its associated file.
 * It returns the number of bytes read.
 */
static unsigned
fill_bitstream(BITSTREAM *bs)
{
	size_t sz;
	FILE *f;

	f = bs->file;
	sz = fread(bs->text, sizeof *bs->text, CHUNK_SIZE, f);
	if (sz == 0) {
		/* No more characters in file */
		bs->link = bs->text;
		while (sz < CHUNK_SIZE) {
			/* Fill buffer with all ones */
			bs->text[sz] = (bitstream_byte) BYTE_MASK;
			sz++;
		}
	}

	bs->size = sz;
	return sz;
}

/*
 * This routine checks whether the end of the file associated with the
 * bitstream bs has been precisely reached.  Note that the link field
 * is set to a non-null value by fill_bitstream if the end of file is
 * encountered.
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
 * This array gives the bit masks for values up to 16 bits.
 */
static unsigned long bit_mask[17] = {
	0x0000,
	0x0001UL, 0x0003UL, 0x0007UL, 0x000fUL,
	0x001fUL, 0x003fUL, 0x007fUL, 0x00ffUL,
	0x01ffUL, 0x03ffUL, 0x07ffUL, 0x0fffUL,
	0x1fffUL, 0x3fffUL, 0x7fffUL, 0xffffUL
};

/*
 * This routine reads the next n bits from the bitstream bs.
 * n will be at most 16.
 */
unsigned
de_bits(BITSTREAM *bs, unsigned n)
{
	unsigned long d;
	unsigned bits, bytes;
	unsigned sz;
	unsigned m;

	d = 0;
	bytes = bs->bytes;
	bits  = 0;

	/* Build up result */
	m = n + bs->bits;
	while (m) {
		unsigned long c;
		unsigned b;

		/* Refill buffer from file if necessary */
		if (bytes >= sz) {
			sz = fill_bitstream(bs);
			bytes = 0;
			bits  = 0;
		}

		/* Get next character */
		c = bs->text[bytes];
		d = (d << BYTE_SIZE) | c;
		b = BYTE_SIZE - bits;
		if (m < b) {
			d >>= (b - m);
			bits += m;
			m = 0;
		} else {
			bits += b;
			m    -= b;
		}

		if (bits == BYTE_SIZE) {
			bits = 0;
			bytes++;
		}
	}

	bs->bytes = bytes;
	bs->bits  = bits;

	return d & bit_mask[n];
}

/*
 * This routine is identical to de_bits except that it works
 * for up to 32 bits.
 */
unsigned long
de_long_bits(BITSTREAM *bs, unsigned n)
{
	unsigned long a, b;

	if (n > 16) {
		a = de_bits(bs, n - 16);
		n = 16;
	} else {
		a = 0;
	}

	b = de_bits(bs, n);

	return (a << 16) | b;
}

/*
 * This routine reads an integer as a series of octal digits from the
 * bitstream bs.
 */
unsigned long
de_int(BITSTREAM *bs)
{
	unsigned long d, n;

	n = 0;

	for (;;) {
		d = de_bits(bs, 4);
		if (d & 0x8) {
			break;
		}

		n = (n << 3) | d;
	}

	n = (n << 3) | (d & 0x7);

	return n;
}

/*
 * This routine reads enough bits from the bitstream bs to align it to
 * the next byte boundary.
 */
void
de_boundary(BITSTREAM *bs)
{
	if (bs->bits) {
		IGNORE de_bits(bs, BYTE_SIZE - bs->bits);
	}
}

