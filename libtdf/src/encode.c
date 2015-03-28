/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <limits.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <tdf/bitstream.h>
#include <tdf/encode.h>

/*
    This routine dumps the contents of the bitstream bs to its associated
    file.  The contents will be lost if this is the null file.  Any odd
    bits will remain in the bitstream.
*/

void
dump_bitstream(BITSTREAM *bs)
{
	size_t n = (size_t)bs->bytes;
	if (n) {
		bitstream_byte *t = bs->text;
		FILE *f = bs->file;
		if (f) {
			IGNORE fwrite(t, sizeof *t, n, f);
		}
		t[0] = t[n];
	}
	bs->bytes = 0;
	return;
}


/*
    This routine extends the bitstream bs by dumping its contents to a
    file or linking it to a fresh chunk.
*/

BITSTREAM *
extend_bitstream(BITSTREAM *bs)
{
	bs->bytes = CHUNK_SIZE;
	bs->bits = 0;
	if (bs->file) {
		dump_bitstream(bs);
	} else {
		BITSTREAM *ps = start_bitstream(NULL, bs->link);
		ps->prev = bs;
		bs = ps;
	}
	return bs;
}


/*
    This routine adds the n bits given by d to the bitstream bs.  n will
    always be at most 16.
*/

BITSTREAM *
enc_bits(BITSTREAM *bs, unsigned n, unsigned d)
{
	if (n) {
		unsigned long b = (unsigned long)d;
		bitstream_byte *text = bs->text;
		unsigned bytes = bs->bytes;
		unsigned bits = bs->bits;
		if (bits) {
			/* Add existing bits */
			unsigned r = (BYTE_SIZE - bits);
			unsigned long c = (unsigned long)text[bytes];
			b |= ((c >> r) << n);
			n += bits;
		}
		bits = (n % BYTE_SIZE);
		if (bits) {
			/* Zero pad to a whole number of bytes */
			unsigned r = (BYTE_SIZE - bits);
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
			text[bytes] = (bitstream_byte) ((b >> n) & BYTE_MASK);
			bytes++;
		} while (n);
		if (bits) {
			bytes--;
		}
		bs->bytes = bytes;
		bs->bits = bits;
	}
	return bs;
}


/*
    This routine is identical to enc_bits except that it works for up to
    32 bits.
*/

BITSTREAM *
enc_long_bits(BITSTREAM *bs, unsigned n, unsigned long d)
{
	if (n > 16) {
		bs = enc_bits(bs, n - 16,(unsigned)(d >> 16));
		n = 16;
	}
	bs = enc_bits(bs, n,(unsigned)d);
	return bs;
}


/*
    This routine adds the n bytes given by s to the bitstream bs.
*/

BITSTREAM *
enc_bytes(BITSTREAM *bs, unsigned long n, bitstream_byte *s)
{
	if (bs->bits) {
		/* Unaligned bitstream */
		unsigned long i;
		for (i = 0; i < n; i++) {
			unsigned c = (unsigned)s[i];
			bs = enc_bits(bs,(unsigned)BYTE_SIZE, c);
		}
	} else {
		/* Aligned bitstream */
		unsigned long i;
		bitstream_byte *text = bs->text;
		unsigned bytes = bs->bytes;
		for (i = 0; i < n; i++) {
			if (bytes >= CHUNK_SIZE) {
				/* Start new chunk if necessary */
				bs = extend_bitstream(bs);
				text = bs->text;
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
    This routine copies a component of the bitstream bs to the end of
    the bitstream fs.
*/

static BITSTREAM *
copy_bitstream(BITSTREAM *fs, BITSTREAM *bs)
{
	bitstream_byte *text = bs->text;
	unsigned bits = bs->bits;
	unsigned bytes = bs->bytes;
	if (bytes) {
		/* Copy any bytes */
		fs = enc_bytes(fs,(unsigned long)bytes, text);
	}
	if (bits) {
		/* Copy any spare bits */
		unsigned c = (unsigned)text[bytes];
		c >>= (BYTE_SIZE - bits);
		fs = enc_bits(fs, bits, c);
	}
	return fs;
}


/*
    This routine adds the bitstream bs to the end of the bitstream fs.
    bs will not have an associated file.
*/

BITSTREAM *
join_bitstreams(BITSTREAM *fs, BITSTREAM *bs)
{
	FILE *f;
	BITSTREAM *ps;
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
	f = fs->file;
	if (f) {
		if (ps) {
			fs = join_bitstreams(fs, ps);
		}
		if (fs->bits == 0 && bs->bytes) {
			/* Dump any bytes to file */
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
	ps = bs;
	while (ps->prev) {
		ps = ps->prev;
	}
	ps->prev = fs;
	return bs;
}


/*
    This routine aligns the bitstream bs so that it consists of a whole
    number of bytes.
*/

BITSTREAM *
enc_boundary(BITSTREAM *bs)
{
	unsigned n = length_bitstream(bs);
	unsigned r = (n % BYTE_SIZE);
	if (r) {
		/* Add extra bits if necessary */
		bs = enc_bits(bs, BYTE_SIZE - r,(unsigned)0);
	}
	return bs;
}


/*
    This routine adds the bit pattern d to the bitstream bs using the
    extended encoding as n-bit packets.  Note that d cannot be zero.
*/

BITSTREAM *
enc_extn(BITSTREAM *bs, unsigned n, unsigned d)
{
	unsigned e = ((unsigned)1 << n) - 1;
	while (d > e) {
		/* Encode zero for each multiple of e */
		bs = enc_bits(bs, n,(unsigned)0);
		d -= e;
	}
	/* Encode the remainder */
	bs = enc_bits(bs, n, d);
	return bs;
}


/*
    This is an auxiliary routine used by enc_int.  It is identical
    except that the last digit is not marked.
*/

BITSTREAM *
enc_int_aux(BITSTREAM *bs, unsigned long n)
{
	unsigned m;
	if (n >= 8) {
		bs = enc_int_aux(bs, n >> 3);
	}
	m = (unsigned)(n & 0x7);
	bs = enc_bits(bs,(unsigned)4, m);
	return bs;
}


/*
    This routine adds the integer n as a series of octal digits to the
    bitstream bs.  The last digit is marked by means of a set bit.
*/

BITSTREAM *
enc_int(BITSTREAM *bs, unsigned long n)
{
	unsigned m;
	if (n >= 8)bs = enc_int_aux(bs, n >> 3);
	m = (unsigned)((n & 0x7) | 0x8);
	bs = enc_bits(bs,(unsigned)4, m);
	return bs;
}


/*
    This routine adds the bitstream ps, preceded by its length, to the
    bitstream bs.
*/

BITSTREAM *
enc_bitstream(BITSTREAM *bs, BITSTREAM *ps)
{
	unsigned n = length_bitstream(ps);
	bs = enc_int(bs,(unsigned long)n);
	bs = join_bitstreams(bs, ps);
	return bs;
}
