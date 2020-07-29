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

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/ustring.h>
#include <utility/xalloc.h>

#include <parse/char.h>
#include <parse/literal.h>

#include <output/encode.h>

/*
    This routine adds the n ASCII characters given by s to the bitstream bs.
*/

BITSTREAM *
enc_ascii(BITSTREAM *bs, unsigned long n, string s)
{
	if (is_ascii) {
		bs = enc_bytes(bs, n, s);
	} else {
		if (bs->bits) {
			/* Unaligned bitstream */
			unsigned long i;
			for (i = 0; i < n; i++) {
				int ch = CHAR_SIMPLE;
				unsigned long c = (unsigned long)s[i];
				c = to_ascii(c, &ch);
				bs = enc_bits(bs, (unsigned)BYTE_SIZE,
					      (unsigned)c);
			}
		} else {
			/* Aligned bitstream */
			unsigned long i;
			string text = bs->text;
			unsigned bytes = bs->bytes;
			for (i = 0; i < n; i++) {
				int ch = CHAR_SIMPLE;
				unsigned long c = (unsigned long)s[i];
				if (bytes >= CHUNK_SIZE) {
					/* Start new chunk if necessary */
					bs = extend_bitstream(bs);
					text = bs->text;
					bytes = 0;
				}
				c = to_ascii(c, &ch);
				text[bytes] = (unsigned char)c;
				bytes++;
			}
			bs->bytes = bytes;
		}
	}
	return bs;
}


/*
    This routine adds the identifier string starting with s of length n
    to the bitstream bs.  This is encoded as two integers, giving the
    bits per character and the number of characters, followed by an
    alignment, followed by the characters comprising the identifier.
*/

BITSTREAM *
enc_ident(BITSTREAM *bs, string s, unsigned long n)
{
	bs = enc_int(bs,(unsigned long)BYTE_SIZE);
	bs = enc_int(bs, n);
	bs = enc_boundary(bs);
	bs = enc_ascii(bs, n, s);
	return bs;
}


/*
    This routine adds the string s of length n to the bitstream bs.
*/

BITSTREAM *
enc_tdfstring(BITSTREAM *bs, unsigned long n, string s)
{
	bs = enc_int(bs,(unsigned long)BYTE_SIZE);
	bs = enc_int(bs, n);
	bs = enc_ascii(bs, n, s);
	return bs;
}


/*
    This routine is identical to enc_tdfstring except that strlen is
    used to calculate the length of the string.
*/

BITSTREAM *
enc_ustring(BITSTREAM *bs, string s)
{
	unsigned long n = (unsigned long)ustrlen(s);
	bs = enc_int(bs,(unsigned long)BYTE_SIZE);
	bs = enc_int(bs, n);
	bs = enc_ascii(bs, n, s);
	return bs;
}

