/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#include "config.h"
#include "producer.h"

#include <limits.h>

#include "cstring.h"
#include "fmm.h"

#include "c_types.h"
#include "error.h"
#include "char.h"
#include "encode.h"
#include "literal.h"
#include "ustring.h"


/*
 *    DUMP A BITSTREAM TO A FILE
 *
 *    This routine dumps the contents of the bitstream bs to its associated
 *    file.  The contents will be lost if this is the null file.  Any odd
 *    bits will remain in the bitstream.
 */

static void
dump_bitstream(BITSTREAM *bs)
{
    size_t n = (size_t) bs->bytes;
    if (n) {
		string t = bs->text;
		FILE *f = bs->file;
		if (f) {
			IGNORE fwrite (t, sizeof (character), n, f);
		}
		t [0] = t [n];
    }
    bs->bytes = 0;
    return;
}


/*
 *    LIST OF FREE BITSTREAMS
 *
 *    This variable gives the list of bitstreams from which new bitstreams
 *    are allocated.
 */

static BITSTREAM *free_bitstreams = NULL;


/*
 *    CREATE A NEW BITSTREAM
 *
 *    This routine creates a new bitstream with associated file f and
 *    linkage lnk.
 */

BITSTREAM
*start_bitstream(FILE *f, void *lnk)
{
    BITSTREAM *bs = free_bitstreams;
    if (bs) {
		free_bitstreams = bs->prev;
    } else {
		bs = xmalloc (sizeof(*bs));
		bs->text = ustring_alloc ((size_t) CHUNK_SIZE);
    }
    bs->bytes = 0;
    bs->bits = 0;
    bs->size = 0;
    bs->file = f;
    bs->link = lnk;
    bs->prev = NULL;
    return (bs);
}


/*
 *    END A BITSTREAM
 *
 *    This routine frees the bitstream bs including clearing the buffer
 *    for any file bitstream if w is true.
 */

void
end_bitstream(BITSTREAM *bs, int w)
{
    BITSTREAM *ps = bs;
    if (w && ps->file) {
		/* Align bitstream and dump */
		ps = enc_boundary (ps);
		dump_bitstream (ps);
    }
    while (ps->prev) ps = ps->prev;
    ps->prev = free_bitstreams;
    free_bitstreams = bs;
    return;
}


/*
 *    EXTEND A BITSTREAM
 *
 *    This routine extends the bitstream bs by dumping its contents to a
 *    file or linking it to a fresh chunk.
 */

static BITSTREAM
*extend_bitstream(BITSTREAM *bs)
{
    bs->bytes = CHUNK_SIZE;
    bs->bits = 0;
    if (bs->file) {
		dump_bitstream (bs);
    } else {
		BITSTREAM *ps = start_bitstream (NULL, bs->link);
		ps->prev = bs;
		bs = ps;
    }
    return (bs);
}


/*
 *    ADD A NUMBER OF BITS TO A BITSTREAM
 *
 *    This routine adds the n bits given by d to the bitstream bs.  n will
 *    always be at most 16.
 */

BITSTREAM
*enc_bits(BITSTREAM *bs, unsigned n, unsigned d)
{
    if (n) {
		unsigned long b = (unsigned long) d;
		string text = bs->text;
		unsigned bytes = bs->bytes;
		unsigned bits = bs->bits;
		if (bits) {
			/* Add existing bits */
			unsigned r = (BYTE_SIZE - bits);
			unsigned long c = (unsigned long) text [ bytes ];
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
				bs = extend_bitstream (bs);
				text = bs->text;
				bytes = 0;
			}
			n -= BYTE_SIZE;
			text [ bytes ] = (character) ((b >> n) & BYTE_MASK);
			bytes++;
		} while (n);
		if (bits) bytes--;
		bs->bytes = bytes;
		bs->bits = bits;
    }
    return (bs);
}


/*
 *    ADD A LARGER NUMBER OF BITS TO A BITSTREAM
 *
 *    This routine is identical to enc_bits except that it works for up to
 *    32 bits.
 */

BITSTREAM
*enc_long_bits(BITSTREAM *bs, unsigned n,
			   unsigned long d)
{
    if (n > 16) {
		bs = enc_bits (bs, n - 16, (unsigned) (d >> 16));
		n = 16;
    }
    bs = enc_bits (bs, n, (unsigned) d);
    return (bs);
}


/*
 *    ADD A NUMBER OF BYTES TO A BITSTREAM
 *
 *    This routine adds the n bytes given by s to the bitstream bs.
 */

BITSTREAM
*enc_bytes(BITSTREAM *bs, unsigned long n,
		   string s)
{
    if (bs->bits) {
		/* Unaligned bitstream */
		unsigned long i;
		for (i = 0 ; i < n ; i++) {
			unsigned c = (unsigned) s [i];
			bs = enc_bits (bs, (unsigned) BYTE_SIZE, c);
		}
    } else {
		/* Aligned bitstream */
		unsigned long i;
		string text = bs->text;
		unsigned bytes = bs->bytes;
		for (i = 0 ; i < n ; i++) {
			if (bytes >= CHUNK_SIZE) {
				/* Start new chunk if necessary */
				bs = extend_bitstream (bs);
				text = bs->text;
				bytes = 0;
			}
			text [ bytes ] = s [i];
			bytes++;
		}
		bs->bytes = bytes;
    }
    return (bs);
}


/*
 *    ADD A NUMBER OF ASCII CHARACTERS TO A BITSTREAM
 *
 *    This routine adds the n ASCII characters given by s to the bitstream bs.
 */

BITSTREAM
*enc_ascii(BITSTREAM *bs, unsigned long n,
		   string s)
{
    if (is_ascii) {
		bs = enc_bytes (bs, n, s);
    } else {
		if (bs->bits) {
			/* Unaligned bitstream */
			unsigned long i;
			for (i = 0 ; i < n ; i++) {
				int ch = CHAR_SIMPLE;
				unsigned long c = (unsigned long) s [i];
				c = to_ascii (c, &ch);
				bs = enc_bits (bs, (unsigned) BYTE_SIZE, (unsigned) c);
			}
		} else {
			/* Aligned bitstream */
			unsigned long i;
			string text = bs->text;
			unsigned bytes = bs->bytes;
			for (i = 0 ; i < n ; i++) {
				int ch = CHAR_SIMPLE;
				unsigned long c = (unsigned long) s [i];
				if (bytes >= CHUNK_SIZE) {
					/* Start new chunk if necessary */
					bs = extend_bitstream (bs);
					text = bs->text;
					bytes = 0;
				}
				c = to_ascii (c, &ch);
				text [ bytes ] = (unsigned char) c;
				bytes++;
			}
			bs->bytes = bytes;
		}
    }
    return (bs);
}


/*
 *    COPY A BITSTREAM
 *
 *    This routine copies a component of the bitstream bs to the end of
 *    the bitstream fs.
 */

static BITSTREAM
*copy_bitstream(BITSTREAM *fs, BITSTREAM *bs)
{
    string text = bs->text;
    unsigned bits = bs->bits;
    unsigned bytes = bs->bytes;
    if (bytes) {
		/* Copy any bytes */
		fs = enc_bytes (fs, (unsigned long) bytes, text);
    }
    if (bits) {
		/* Copy any spare bits */
		unsigned c = (unsigned) text [ bytes ];
		c >>= (BYTE_SIZE - bits);
		fs = enc_bits (fs, bits, c);
    }
    return (fs);
}


/*
 *    JOIN TWO BITSTREAMS
 *
 *    This routine adds the bitstream bs to the end of the bitstream fs.
 *    bs will not have an associated file.
 */

BITSTREAM
*join_bitstreams(BITSTREAM *fs, BITSTREAM *bs)
{
    FILE *f;
    BITSTREAM *ps;
    if (bs == NULL) return (fs);
    if (fs == NULL) return (bs);
    if (fs->link == NULL) fs->link = bs->link;
	
    /* Copy bitstream to file */
    ps = bs->prev;
    f = fs->file;
    if (f) {
		if (ps) fs = join_bitstreams (fs, ps);
		if (fs->bits == 0 && bs->bytes) {
			/* Dump any bytes to file */
			bs->file = f;
			if (fs->bytes) dump_bitstream (fs);
			dump_bitstream (bs);
			bs->file = NULL;
		}
		fs = copy_bitstream (fs, bs);
		if (ps == NULL) end_bitstream (bs, 0);
		return (fs);
    }
	
    /* Copy small bitstreams */
    if (ps == NULL && bs->bytes < CHUNK_COPY) {
		fs = copy_bitstream (fs, bs);
		end_bitstream (bs, 0);
		return (fs);
    }
	
    /* Link larger bitstreams */
    ps = bs;
    while (ps->prev) ps = ps->prev;
    ps->prev = fs;
    return (bs);
}


/*
 *    FIND THE LENGTH OF A BITSTREAM
 *
 *    This routine returns the length of the bitstream bs in bits.
 */

unsigned
length_bitstream(BITSTREAM *bs)
{
    unsigned n = 0;
    while (bs) {
		n += (BYTE_SIZE * bs->bytes + bs->bits);
		bs = bs->prev;
    }
    return (n);
}


/*
 *    ALIGN A BITSTREAM TO A BYTE BOUNDARY
 *
 *    This routine aligns the bitstream bs so that it consists of a whole
 *    number of bytes.
 */

BITSTREAM
*enc_boundary(BITSTREAM *bs)
{
    unsigned n = length_bitstream (bs);
    unsigned r = (n % BYTE_SIZE);
    if (r) {
		/* Add extra bits if necessary */
		bs = enc_bits (bs, BYTE_SIZE - r, (unsigned) 0);
    }
    return (bs);
}


/*
 *    ADD AN EXTENDED BIT PATTERN TO A BITSTREAM
 *
 *    This routine adds the bit pattern d to the bitstream bs using the
 *    extended encoding as n-bit packets.  Note that d cannot be zero.
 */

BITSTREAM
*enc_extn(BITSTREAM *bs, unsigned n, unsigned d)
{
    unsigned e = ((unsigned) 1 << n) - 1;
    while (d > e) {
		/* Encode zero for each multiple of e */
		bs = enc_bits (bs, n, (unsigned) 0);
		d -= e;
    }
    /* Encode the remainder */
    bs = enc_bits (bs, n, d);
    return (bs);
}


/*
 *    ADD A SERIES OF OCTAL DIGITS TO A BITSTREAM
 *
 *    This is an auxiliary routine used by enc_int.  It is identical
 *    except that the last digit is not marked.
 */

BITSTREAM
*enc_int_aux(BITSTREAM *bs, unsigned long n)
{
    unsigned m;
    if (n >= 8) bs = enc_int_aux (bs, n >> 3);
    m = (unsigned) (n & 0x7);
    bs = enc_bits (bs, (unsigned) 4, m);
    return (bs);
}


/*
 *    ADD AN INTEGER TO A BITSTREAM
 *
 *    This routine adds the integer n as a series of octal digits to the
 *    bitstream bs.  The last digit is marked by means of a set bit.
 */

BITSTREAM
*enc_int(BITSTREAM *bs, unsigned long n)
{
    unsigned m;
    if (n >= 8) bs = enc_int_aux (bs, n >> 3);
    m = (unsigned) ((n & 0x7) | 0x8);
    bs = enc_bits (bs, (unsigned) 4, m);
    return (bs);
}


/*
 *    ADD AN IDENTIFIER TO A BITSTREAM
 *
 *    This routine adds the identifier string starting with s of length n
 *    to the bitstream bs.  This is encoded as two integers, giving the
 *    bits per character and the number of characters, followed by an
 *    alignment, followed by the characters comprising the identifier.
 */

BITSTREAM
*enc_ident(BITSTREAM *bs, string s, unsigned long n)
{
    bs = enc_int (bs, (unsigned long) BYTE_SIZE);
    bs = enc_int (bs, n);
    bs = enc_boundary (bs);
    bs = enc_ascii (bs, n, s);
    return (bs);
}


/*
 *    ADD A STRING TO A BITSTREAM
 *
 *    This routine adds the string s of length n to the bitstream bs.
 */

BITSTREAM
*enc_tdfstring(BITSTREAM *bs, unsigned long n,
			   string s)
{
    bs = enc_int (bs, (unsigned long) BYTE_SIZE);
    bs = enc_int (bs, n);
    bs = enc_ascii (bs, n, s);
    return (bs);
}


/*
 *    ADD A STRING TO A BITSTREAM
 *
 *    This routine is identical to enc_tdfstring except that strlen is
 *    used to calculate the length of the string.
 */

BITSTREAM
*enc_ustring(BITSTREAM *bs, string s)
{
    unsigned long n = (unsigned long) ustrlen (s);
    bs = enc_int (bs, (unsigned long) BYTE_SIZE);
    bs = enc_int (bs, n);
    bs = enc_ascii (bs, n, s);
    return (bs);
}


/*
 *    ADD A TDF BITSTREAM TO A BITSTREAM
 *
 *    This routine adds the bitstream ps, preceded by its length, to the
 *    bitstream bs.
 */

BITSTREAM
*enc_bitstream(BITSTREAM *bs, BITSTREAM *ps)
{
    unsigned n = length_bitstream (ps);
    bs = enc_int (bs, (unsigned long) n);
    bs = join_bitstreams (bs, ps);
    return (bs);
}
