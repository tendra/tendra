/*
 * Copyright (c) 2003-2004, Boris Popov.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $TenDRA$
 */


#include <limits.h>

#include "config.h"

#include "char.h"
#include "cstring.h"
#include "fmm.h"
#include "msgcat.h"
#include "tdf_types.h"
#include "tdf_stream.h"

static ByteT revmask[TDF_BYTE_SIZE + 1] = {
	0, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF
};

/*
 * Write n bits of d to a stream.
 * n should be in range [0..sizeof(d)*CHAR_BIT]
 */
void
tdf_en_bits(struct tdf_stream *sp, unsigned int n, unsigned long d)
{
	ByteT b;
	tdf_pos pos;
	unsigned int bleft, bit;
	const unsigned int d_width = sizeof(d) * CHAR_BIT;

	ASSERT(n <= d_width);
	if (n == 0)
		return;

	/* Align data by the left boundary */
	d <<= d_width - n;
	b = sp->ts_byte;
	pos = sp->ts_pos;
	bit = tdf_pos_bit(pos);
	while (n) {
		bleft = TDF_BYTE_SIZE - bit;
		if (bleft > n)
			bleft = n;
		/* Fill remaining bits in the byte */
		b |= ((d >> (d_width - TDF_BYTE_SIZE)) & revmask[bleft]) >> bit;
		n -= bleft;
		bit += bleft;
		pos += bleft;
		d <<= bleft;
		if (bit == TDF_BYTE_SIZE) {
			sp->ts_pos = pos;		/* allow stream to verify position */
			TDF_STREAM_WRITE_BYTE(sp, b);
			bit = 0;
			b = 0;
		}
	}
	sp->ts_byte = b;
	sp->ts_pos = pos;
	return;
}

/*
 * Align tdf_stream to a byte boundary.
 */
void
tdf_en_align(struct tdf_stream *sp)
{
	unsigned int bit = tdf_pos_bit(sp->ts_pos);

	if (bit == 0)
		return;
	tdf_en_bits(sp, TDF_BYTE_SIZE - bit, 0);
	return;
}

void
tdf_en_tdfbool(struct tdf_stream *sp, TDFBOOL v)
{
	tdf_en_bits(sp, 1, v);
}

/*
 * Encode part of TDF integer.
 */
void
tdf_en_tdfintl_aux(struct tdf_stream *sp, TDFINTL n)
{
	if (n >= 8)
		tdf_en_tdfintl_aux(sp, n >> 3);
	tdf_en_bits(sp, 4, n & 7);
}

/*
 * Encode TDF integer.
 */
void
tdf_en_tdfintl(struct tdf_stream *sp, TDFINTL n)
{
	if (n >= 8)
		tdf_en_tdfintl_aux(sp, n >> 3);
	tdf_en_bits(sp, 4, n | 8);
}

/*
 * Adds the bit pattern d to the stream using the extended
 * encoding as n-bit packets.  Note that d cannot be zero.
 */
void
tdf_en_tdfextint(struct tdf_stream *sp, unsigned int n, TDFEXTINT d)
{
	TDFEXTINT e;

	if (d == 0)
		MSG_fatal_tdf_cant_encode_0_as_extended_value(sp);
	for (e = (1 << n) - 1; d > e; d -= e)
		tdf_en_bits(sp, n, 0);
	tdf_en_bits(sp, n, d);
}


void
tdf_en_ascii(struct tdf_stream *sp, size_t n, const unsigned char *s)
{
	int chtype;

	if (is_ascii) {
		while (n--)
			tdf_en_bits(sp, 8, *s++);
		return;
	}

	while (n--) {
		chtype = CHAR_SIMPLE;
		tdf_en_bits(sp, 8, to_ascii (*s++, &chtype));
	}
}

/*
 * Encode an eight bit TDF string.
 */
void
tdf_en_tdfstring8(struct tdf_stream *sp, size_t n, const unsigned char *s)
{
	tdf_en_tdfintl(sp, 8);
	tdf_en_tdfintl(sp, n);
	tdf_en_ascii(sp, n, s);
}

/*
 * Encode an eight bit null-terminated string.
 */
void
tdf_en_cstringn(struct tdf_stream *sp, size_t n, const char *s)
{
	tdf_en_tdfstring8(sp, n, (const unsigned char*)s);
}

void
tdf_en_ustring(struct tdf_stream *sp, const unsigned char *s)
{
	tdf_en_tdfstring8(sp, strlen((const char *)s), s);
}

/*
 * Encode a TDF identifier.
 */
void
tdf_en_tdfident(struct tdf_stream *sp, size_t n, const unsigned char *s)
{
	tdf_en_tdfintl(sp, 8);
	tdf_en_tdfintl(sp, n);
	tdf_en_align(sp);
	tdf_en_ascii(sp, n, s);
}


/*
 * Add tdf_stream s2 to the end of stream s1.  Either of them can be null,
 * but not both.  The s2 stream deallocated and s2 pointer will not be
 * valid after function termination. Destination stream may have an
 * arbitrary position before operation.
 * It is not recommended to pass s1 as NULL and only broken code in producers
 * relays on this feature.
 */
struct tdf_stream *
tdf_en_stream(struct tdf_stream *s1, struct tdf_stream *s2)
{
	tdf_pos s2sz;
	ByteT cpbuf[16];
	unsigned int ncp, ncpbits;

	if (s2 == NULL)
		return s1;
	if (s1 == NULL)
		return s2;
	if (s1->ts_link == NULL)
		s1->ts_link = s2->ts_link;

	s2sz = s2->ts_pos;
	tdf_stream_rewind(s2);
	if (tdf_pos_bit(s1->ts_pos)) {
		/* writing to unaligned stream */
		while (s2sz) {
			ncpbits = sizeof(TDFINTL) * TDF_BYTE_SIZE;
			if (s2sz < ncpbits)
				ncpbits = s2sz;
			tdf_en_bits(s1, ncpbits, tdf_de_bits(s2, ncpbits));
			s2sz -= ncpbits;
		}
	} else {
		while (s2sz) {
			ncpbits = sizeof(cpbuf) * TDF_BYTE_SIZE;
			if (s2sz < ncpbits)
				ncpbits = s2sz;
			ncp = ncpbits / TDF_BYTE_SIZE;
			if (ncp) {
				tdf_stream_read(s2, ncp, cpbuf);
				tdf_stream_write(s1, ncp, cpbuf);
			}
			ncp = ncpbits % TDF_BYTE_SIZE;
			if (ncp) {
				tdf_en_bits(s1, ncp, tdf_de_bits(s2, ncp));
			}
			s2sz -= ncpbits;
		}
	}
	tdf_stream_destroy(s2);
	return s1;
}

/*
 * Encode TDF stream src into sp as TDFBITSTREAM entity.
 * src stream destructed on exit.
 */
void
tdf_en_bitstream(struct tdf_stream *sp, struct tdf_stream *src)
{
	tdf_en_tdfintl(sp, src->ts_pos);
	(void)tdf_en_stream(sp, src);
}
