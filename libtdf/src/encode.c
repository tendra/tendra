/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <tdf/bitstream.h>
#include <tdf/encode.h>

/*
 * This routine dumps the contents of the bitstream bs to its associated file.
 * The contents will be lost if this is the null file.
 * Any odd bits will remain in the bitstream.
 */
void
dump_bitstream(BITSTREAM *bs)
{
	if (bs->bytes == 0) {
		return;
	}

	if (bs->file) {
		IGNORE fwrite(bs->text, sizeof *bs->text, bs->bytes, bs->file);
	}

	assert(bs->bytes <= CHUNK_SIZE);

	if (bs->bytes < CHUNK_SIZE) {
		bs->text[0] = bs->text[bs->bytes];
	} else {
		assert(bs->bits == 0);
	}

	bs->bytes   = 0;
}

/*
 * This routine extends the bitstream bs by dumping its contents to a
 * file or linking it to a fresh chunk.
 */
BITSTREAM *
extend_bitstream(BITSTREAM *bs)
{
	bs->bytes = CHUNK_SIZE;
	bs->bits  = 0;

	if (bs->file) {
		dump_bitstream(bs);
	} else {
		BITSTREAM *ps;

		ps = start_bitstream(NULL, bs->link);
		ps->prev = bs;

		bs = ps;
	}

	return bs;
}

/*
 * This routine adds the n bits given by d to the bitstream bs.
 * n will always be at most 16.
 */
BITSTREAM *
enc_bits(BITSTREAM *bs, unsigned n, unsigned d)
{
	unsigned long b;
	unsigned bits, bytes;
	bitstream_byte *text;

	assert(n <= 16);

	if (n == 0) {
		return bs;
	}

	b = d;
	text  = bs->text;
	bytes = bs->bytes;
	bits  = bs->bits;

	if (bits) {
		/* Move existing odd bits to b */
		unsigned long c;
		unsigned r;

		assert(bytes < CHUNK_SIZE);

		r = BYTE_SIZE - bits;
		c = text[bytes];

		b |= ((c >> r) << n);
		n += bits;
	}

	bits = n % BYTE_SIZE;
	if (bits) {
		unsigned r;

		/* Zero pad to a whole number of bytes */
		r = BYTE_SIZE - bits;
		b <<= r;
		n += r;
	}

	do {
		/* Output each byte */
		if (bytes >= CHUNK_SIZE) {
			/* Start new chunk if necessary */
			bs = extend_bitstream(bs);
			text = bs->text;
			bytes = 0;
		}

		n -= BYTE_SIZE;
		text[bytes] = (b >> n) & BYTE_MASK;
		bytes++;
	} while (n);

	if (bits) {
		bytes--;
	}

	bs->bytes = bytes;
	bs->bits  = bits;

	return bs;
}

/*
 * This routine is identical to enc_bits except that it works
 * for up to 32 bits.
 */
BITSTREAM *
enc_long_bits(BITSTREAM *bs, unsigned n, unsigned long d)
{
	if (n > 16) {
		bs = enc_bits(bs, n - 16, d >> 16);
		n = 16;
	}

	bs = enc_bits(bs, n, d);

	return bs;
}

/*
 * This routine adds the n bytes given by s to the bitstream bs.
 */
BITSTREAM *
enc_bytes(BITSTREAM *bs, unsigned long n, bitstream_byte *s)
{
	if (bs->bits) {
		/* Unaligned bitstream */

		unsigned long i;

		for (i = 0; i < n; i++) {
			unsigned c;

			c = s[i];
			bs = enc_bits(bs, BYTE_SIZE, c);
		}
	} else {
		/* Aligned bitstream */

		bitstream_byte *text;
		unsigned long i;
		unsigned bytes;

		text  = bs->text;
		bytes = bs->bytes;

		for (i = 0; i < n; i++) {
			/* Start new chunk if necessary */
			if (bytes >= CHUNK_SIZE) {
				bs = extend_bitstream(bs);
				text  = bs->text;
				bytes = 0;
			}

			text[bytes] = s[i];
			bytes++;
		}

		bs->bytes = bytes;
	}

	return bs;
}

/*
 * This routine copies a component of the bitstream bs to the end of
 * the bitstream fs.
 */
static BITSTREAM *
copy_bitstream(BITSTREAM *fs, BITSTREAM *bs)
{
	if (bs->bytes) {
		/* Copy any bytes */
		fs = enc_bytes(fs, bs->bytes, bs->text);
	}

	/* Copy any spare bits */
	if (bs->bits) {
		unsigned c;

		c = bs->text[bs->bytes];
		c >>= (BYTE_SIZE - bs->bits);
		fs = enc_bits(fs, bs->bits, c);
	}

	return fs;
}

/*
 * This routine adds the bitstream bs to the end of the bitstream fs.
 * bs will not have an associated file.
 */
BITSTREAM *
join_bitstreams(BITSTREAM *fs, BITSTREAM *bs)
{
	BITSTREAM *ps;
	FILE *f;

	if (bs == NULL) {
		return fs;
	}

	if (fs == NULL) {
		return bs;
	}

	if (fs->link == NULL) {
		fs->link = bs->link;
	}

	/* Copy bitstream to file */
	ps = bs->prev;
	f  = fs->file;
	if (f != NULL) {
		if (ps != NULL) {
			fs = join_bitstreams(fs, ps);
		}

		/* Dump any bytes to file */
		if (fs->bits == 0 && bs->bytes) {
			bs->file = f;
			if (fs->bytes) {
				dump_bitstream(fs);
			}

			dump_bitstream(bs);
			bs->file = NULL;
		}

		fs = copy_bitstream(fs, bs);
		if (ps == NULL) {
			end_bitstream(bs, 0);
		}

		return fs;
	}

	/* Copy small bitstreams */
	if (ps == NULL && bs->bytes < CHUNK_COPY) {
		fs = copy_bitstream(fs, bs);
		end_bitstream(bs, 0);
		return fs;
	}

	/* Link larger bitstreams */
	for (ps = bs; ps->prev != NULL; ps = ps->prev)
		;
	ps->prev = fs;

	return bs;
}

/*
 * This routine aligns the bitstream bs so that it consists of a whole
 * number of bytes.
 */
BITSTREAM *
enc_boundary(BITSTREAM *bs)
{
	unsigned n;
	unsigned r;

	n = length_bitstream(bs);
	r = n % BYTE_SIZE;

	/* Add extra bits if necessary */
	if (r) {
		bs = enc_bits(bs, BYTE_SIZE - r,(unsigned)0);
	}

	return bs;
}

/*
 * This routine adds the bit pattern d to the bitstream bs using the
 * extended encoding as n-bit packets. Note that d cannot be zero.
 */
BITSTREAM *
enc_extn(BITSTREAM *bs, unsigned n, unsigned d)
{
	unsigned e;

	e = (1u << n) - 1;
	while (d > e) {
		/* Encode zero for each multiple of e */
		bs = enc_bits(bs, n,(unsigned)0);
		d -= e;
	}

	/* Encode the remainder */
	return enc_bits(bs, n, d);
}

/*
 * This is an auxiliary routine used by enc_int. It is identical
 * except that the last digit is not marked.
 */
BITSTREAM *
enc_int_aux(BITSTREAM *bs, unsigned long n)
{
	unsigned m;

	if (n >= 8) {
		bs = enc_int_aux(bs, n >> 3);
	}

	m = n & 0x7;
	bs = enc_bits(bs, 4, m);

	return bs;
}

/*
 * This routine adds the integer n as a series of octal digits to the
 * bitstream bs. The last digit is marked by means of a set bit.
 */
BITSTREAM *
enc_int(BITSTREAM *bs, unsigned long n)
{
	unsigned m;

	if (n >= 8) {
		bs = enc_int_aux(bs, n >> 3);
	}

	m = (n & 0x7) | 0x8;
	bs = enc_bits(bs, 4, m);

	return bs;
}

/*
 * This routine adds the bitstream ps, preceded by its length, to the
 * bitstream bs.
 */
BITSTREAM *
enc_bitstream(BITSTREAM *bs, BITSTREAM *ps)
{
	unsigned n;

	n = length_bitstream(ps);
	bs = enc_int(bs, n);
	bs = join_bitstreams(bs, ps);

	return bs;
}

