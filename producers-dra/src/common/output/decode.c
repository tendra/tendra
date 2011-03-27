/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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


#include "config.h"
#include "c_types.h"
#include "error.h"
#include "buffer.h"
#include "char.h"
#include "decode.h"
#include "encode.h"
#include "file.h"
#include "literal.h"


/*
    FILL A BITSTREAM

    This routine fills the bitstream bs from its associated file.  It
    returns the number of bytes read.
*/

static unsigned
fill_bitstream(BITSTREAM *bs)
{
	unsigned sz;
	FILE *f = bs->file;
	string text = bs->text;
	sz = (unsigned)fread((gen_ptr)text, sizeof(character),
			     (size_t)CHUNK_SIZE, f);
	if (sz == 0) {
		/* No more characters in file */
		bs->link = (gen_ptr)text;
		while (sz < CHUNK_SIZE) {
			/* Fill buffer with all ones */
			text[sz] = (character)BYTE_MASK;
			sz++;
		}
	}
	bs->size = sz;
	return (sz);
}


/*
    CHECK FOR END OF FILE

    This routine checks whether the end of the file associated with the
    bitstream bs has been precisely reached.  Note that the link field
    is set to a non-null value by fill_bitstream if the end of file is
    encountered.
*/

int
de_eof(BITSTREAM *bs)
{
	if (bs->link) {
		return (0);
	}
	if (bs->bytes >= bs->size) {
		IGNORE fill_bitstream(bs);
		if (bs->link) {
			return (1);
		}
	}
	return (0);
}


/*
    TABLE OF BIT MASKS

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
    READ A NUMBER OF BITS FROM A BITSTREAM

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
	return ((unsigned)d);
}


/*
    READ A LARGE NUMBER OF BITS FROM A BITSTREAM

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
	return ((a << 16) | b);
}


/*
    READ AN INTEGER FROM A BITSTREAM

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
	return (n);
}


/*
    ALIGN A BITSTREAM TO A BYTE BOUNDARY

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
    READ A STRING FROM A BITSTREAM

    This routine reads a string from the bitstream bs into the buffer bf.
*/

void
de_tdfstring(BITSTREAM *bs, BUFFER *bf)
{
	unsigned m = (unsigned)de_int(bs);
	unsigned long n = de_int(bs);
	string p = stretch_buffer(bf, bf->posn,(gen_size)n);
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
