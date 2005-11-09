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

#include "cstring.h"
#include "fmm.h"
#include "msgcat.h"
#include "tdf_types.h"
#include "tdf_stream.h"

/*
 * Align to a byte boundary if not already at.
 */
void
tdf_de_align(struct tdf_stream *sp)
{
	if (tdf_pos_bit(sp->ts_pos) == 0)
		return;
	sp->ts_pos = tdf_pos_align(sp->ts_pos) + 8;
	sp->ts_need_byte = 1;
}

/*
 * Read n bits from the input stream, where 0 < n <= sizeof(long).
 */
unsigned long
tdf_de_bits(struct tdf_stream *sp, unsigned int n)
{
	ByteT b;
	tdf_pos pos;
	unsigned int bit, bc, right;
	unsigned long res;

	res = 0;
	b = sp->ts_byte;
	pos = sp->ts_pos;
	for (; n; n -= bc) {
		if (sp->ts_need_byte) {
			if (!TDF_STREAM_READ_BYTE(sp, &b)) {
				sp->ts_pos = pos;
				sp->ts_byte = b;
				MSG_fatal_tdf_unexpected_eof(sp);
			}
			sp->ts_need_byte = 0;
			/* may be align pos as well ? Or make an assert ? */
		}
		bit = tdf_pos_bit(pos);
		bc = TDF_BYTE_SIZE - bit;
		if (n < bc)
			bc = n;
		right = TDF_BYTE_SIZE - bc;
		res = (res << bc) + (b >> right);
		b = (b << bc) & 0xff; /* clean used bits */
		if ((bit + bc) >= TDF_BYTE_SIZE)
			sp->ts_need_byte = 1;
		pos += bc;
	}
	sp->ts_pos = pos;
	sp->ts_byte = b;
	return res;
}

/*
 * Skip n bits from the input stream
 */
void
tdf_skip_bits(struct tdf_stream *sp, tdf_pos n)
{
	if (n <= TDF_BYTE_SIZE) {
		(void) tdf_de_bits(sp, n);
		return;
	}
	tdf_stream_seek(sp, sp->ts_pos + n);
}

/*
 * TDFINT encoding uses octal digits encoded in 4-bit basic integers. The most
 * significant octal digit is encoded first, the least significant last.
 * For all digits except the last the 4-bit integer is the value of the octal
 * digit. For the last digit the 4-bit integer is the value of the octal digit
 * plus 8.
 */
TDFINTL
tdf_de_tdfintl(struct tdf_stream *sp)
{
	TDFINTL res;
	unsigned nibble, octal;

	for (res = 0;;) {
		nibble = tdf_de_bits(sp, 4);
		octal = nibble & 7;
		if ((TDFINTL)(res + octal) < res)
			MSG_fatal_tdf_integer_too_big (sp, res);
		res = res * 8 + octal;
		if (nibble & 0x8)
			break;
	}
	return res;
}

ByteT*
tdf_de_tdfintstr(struct tdf_stream *sp)
{
	unsigned nibble, i, too_long;

	too_long = 0;
	for (i = 0;;) {
		nibble = tdf_de_bits(sp, 4);
		if (i < TDFINT_MAXLEN) {
			sp->ts_tdfint[i++] = '0' + (nibble & 7);
		} else if (!too_long) {
			MSG_tdf_integer_too_long (sp, i);
			too_long = 1;
		}
		if (nibble & 0x8)
			break;
	}
	sp->ts_tdfint[i] = 0;
	sp->ts_tdfintlen = i;
	return sp->ts_tdfint;
}

/*
 * Read an extended number of width n
 */
TDFEXTINT
tdf_de_tdfextint(struct tdf_stream *sp, unsigned int n)
{
	TDFEXTINT res, s;

	res = 0;
	while (s = tdf_de_bits(sp, n), s == 0)
		res += (1 << n) - 1;
	return res + s;
}

TDFBOOL
tdf_de_tdfbool(struct tdf_stream *sp)
{
	return (TDFBOOL)tdf_de_bits(sp, 1);
}

/*
 * TDFSTRING encodes a sequence containing n non-negative integers,
 * each of k bits. The encoding consists of, first a TDFINT giving
 * the number of bits, second a TDFINT giving the number of integers,
 * which may be zero. Thirdly it contains n k-bit basic integers,
 * giving the sequence of integers required, the first integer being
 * first in this sequence.
 */
void
tdf_de_tdfstring(struct tdf_stream *sp, TDFSTRING *ip)
{
	TDFINTL i, k, n;
	int esize;

	k = tdf_de_tdfintl(sp);
	n = tdf_de_tdfintl(sp);
	esize = 0;

	ip->number = n;
	if (k <= sizeof(char) * TDF_BYTE_SIZE) {
		esize = sizeof(char) * TDF_BYTE_SIZE;
		ip->ints.chars = xcalloc(n + 1, esize);
		for (i = 0; i < n; i++)
			ip->ints.chars[i] = (char)tdf_de_bits(sp, k);
		ip->ints.chars[i] = 0;
	} else if (k <= sizeof(short) * TDF_BYTE_SIZE) {
		esize = sizeof(short) * TDF_BYTE_SIZE;
		ip->ints.shorts = xcalloc (n + 1, esize);
		for (i = 0; i < n; i++)
			ip->ints.shorts[i] = (short)tdf_de_bits(sp, k);
		ip->ints.shorts[i] = 0;
	} else if (k <= 32) {
		esize = sizeof(long) * TDF_BYTE_SIZE;
		ip->ints.longs = xcalloc (n + 1, esize);
		for (i = 0; i < n; i++)
			ip->ints.longs[i] = (long)tdf_de_bits(sp, k);
		ip->ints.longs[i] = 0;
	} else if (k <= 64) {
		esize = 64;
#ifdef notyet
		ip->ints.longs = xcalloc (n + 1, sizeof (flpt));
		for (i = 0; i < n; i++) {
			flt64 x;
			flpt f;

			x.big = tdf_de_bits(sp, k - 32);
			x.small = tdf_de_bits(sp, 32);
			f = f64_to_flt(x, 0);
			ip->ints.longs[i] = f;
		}
#endif
		ip->ints.longs[n] = 0;
	} else
		MSG_fatal_tdf_string_element_too_big(sp, k);
	ip->size = esize;
	return;
}

/*
 * TDFSTRING encodes a sequence containing n non-negative integers,
 * each of k bits. The encoding consists of, first a TDFINT giving
 * the number of bits, second a TDFINT giving the number of integers,
 * which may be zero. Thirdly it contains n k-bit basic integers,
 * giving the sequence of integers required, the first integer being
 * first in this sequence.
 */
void
tdf_de_tdfident(struct tdf_stream *sp, TDFIDENT *ip)
{
	TDFINTL i, k, n;
	int esize;

	k = tdf_de_tdfintl(sp);
	n = tdf_de_tdfintl(sp);
	tdf_de_align(sp);
	esize = 0;

	ip->number = n;
	if (k <= sizeof(char) * TDF_BYTE_SIZE) {
		esize = sizeof(char) * TDF_BYTE_SIZE;
		ip->ints.chars = xcalloc(n + 1, esize);
		for (i = 0; i < n; i++)
			ip->ints.chars[i] = (char)tdf_de_bits(sp, k);
		ip->ints.chars[i] = 0;
	} else if (k <= sizeof(short) * TDF_BYTE_SIZE) {
		esize = sizeof(short) * TDF_BYTE_SIZE;
		ip->ints.shorts = xcalloc (n + 1, esize);
		for (i = 0; i < n; i++)
			ip->ints.shorts[i] = (short)tdf_de_bits(sp, k);
		ip->ints.shorts[i] = 0;
	} else if (k <= 32) {
		esize = sizeof(long) * TDF_BYTE_SIZE;
		ip->ints.longs = xcalloc (n + 1, esize);
		for (i = 0; i < n; i++)
			ip->ints.longs[i] = (long)tdf_de_bits(sp, k);
		ip->ints.longs[i] = 0;
	} else
		MSG_fatal_tdf_string_element_too_big(sp, k);
	ip->size = esize;
	tdf_de_align(sp);
	return;
}

/*
 * Decode TDF magic number and compare it with emagic.
 * If emagic is NULL, then check only first 3 bytes of magic.
 */
void
tdf_de_magic(struct tdf_stream *sp, const char *emagic)
{
	char magic[TDF_MAGIC_LEN + 1];

	tdf_stream_read(sp, TDF_MAGIC_LEN, magic);
	magic[TDF_MAGIC_LEN] = 0;
	if (emagic) {
		if (memcmp(magic, emagic, TDF_MAGIC_LEN) != 0)
			MSG_fatal_tdf_bad_magic(sp, magic, tdf_cap_magic);
	} else {
		if (memcmp(magic, tdf_gen_magic, 3) != 0)
			MSG_fatal_tdf_bad_magic(sp, magic, tdf_gen_magic);
	}
	sp->ts_type = magic[3];
}

/*
 * Decode make_version construct.
 * Do not perform any version verification.
 */
void
tdf_de_make_version(struct tdf_stream *sp, struct tdf_version *vp)
{
	vp->major = tdf_de_tdfintl(sp);
	vp->minor = tdf_de_tdfintl(sp);
	MSG_debug_tdf_version(sp, vp->major, vp->minor);
}
