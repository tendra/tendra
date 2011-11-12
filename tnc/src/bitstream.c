/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <limits.h>

#include <shared/xalloc.h>

#include "config.h"
#include "types.h"
#include "enc_types.h"
#include "bitstream.h"
#include "file.h"
#include "utility.h"


/*
    BITMASKS

    The nth value in this array can be used to extract the bottom n
    bits of a value.
*/

static unsigned long mask[] = {
	0, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff
};


/*
    SIZE OF A STANDARD BITSTREAM

    Each bitstream contains BITSTREAM_SIZE bytes.  It is worth garbage
    collecting if it has CRITICAL_SIZE bytes free when it is closed.
*/

#define BITSTREAM_SIZE		100
#define CRITICAL_SIZE		50


/*
    LIST OF FREE BITSTREAMS

    Bitstreams are allocated from this list.
*/

static bitstream *free_bitstreams = NULL;


/*
    CREATE A NEW BITSTREAM

    A new bitstream is allocated and initialized.
*/

bitstream *
new_bitstream(void)
{
	unsigned int i;
	bitstream *p;

	if (free_bitstreams == NULL) {
		p = xmalloc_nof(bitstream, 1);
		p->length = BITSTREAM_SIZE;
		p->source = xmalloc_nof(byte, BITSTREAM_SIZE + 10);
	} else {
		p = free_bitstreams;
		free_bitstreams = p->next;
	}

	for (i = 0; i < p->length; i++)
		p->source[i] = 0;

	p->bytes = 0;
	p->bits = 0;
	p->next = NULL;
	p->end = p;

	return p;
}


#if 0

/*
    CLOSE OFF A BITSTREAM

    The bitstream p is closed off and any free space is garbage collected.
    (Not currently used.)
*/

static void
close_bitstream(bitstream *p)
{
	bitstream *q;
	int used = p->end->bytes + 4;
	int left = p->end->length - used;

	if (left < CRITICAL_SIZE)
		return;

	q = xmalloc_nof(bitstream, 1);
	q->length = left;
	q->source = p->end->source + used;
	q->next = free_bitstreams;
	free_bitstreams = q;
	p->end->length = used;
}

#endif


/*
    PRINT A BITSTREAM

    The bitstream p is dumped to the output file.
*/

void
print_bitstream(bitstream *p)
{
	unsigned int r = 0;
	unsigned long buff = 0;

	for (; p; p = p->next) {
		unsigned int i;
		for (i = 0; i < p->bytes; i++) {
			byte b = p->source[i];
			if (r == 0) {
				(void) fputc((int)b, output);
			} else {
				buff = (buff << CHAR_BIT) | ((unsigned long)b);
				(void) fputc((int)((buff >> r) & 0xff), output);
				buff &= mask[r];
			}
		}
		if (p->bits) {
			byte b = p->source[p->bytes];
			b = (byte)((unsigned)b >> (CHAR_BIT - p->bits));
			buff = (buff << p->bits) | ((unsigned long)b);
			r += p->bits;
			if (r >= CHAR_BIT) {
				r -= CHAR_BIT;
				(void) fputc((int)((buff >> r) & 0xff), output);
				buff &= mask[r];
			}
		}
	}

	if (r) {
		buff <<= (CHAR_BIT - r);
		(void) fputc((int)buff, output);
	}
}


/*
    FIND THE LENGTH OF A BITSTREAM

    The length of the bitstream p (in bits) is returned.
*/

long
bitstream_length(bitstream *p)
{
	unsigned int n = 0;

	for (; p; p = p->next)
		n += (CHAR_BIT * p->bytes) + p->bits;

	return (long)n;
}


/*
    JOIN TWO BITSTREAMS

    The bitstream q is appended to p.
*/

void
join_bitstreams(bitstream *p, bitstream *q)
{
#if 0
	close_bitstream(p);
#endif
	p->end->next = q;
	p->end = q->end;
}


/*
    ADD A NUMBER OF BITS TO THE END OF A BITSTREAM

    n bits of value v are added to the end of the bitstream p.
*/

void
enc_bits(bitstream *p, int n, long v)
{
	byte *t;
	bitstream *q = p->end;
	unsigned int m = (unsigned int)n;
	unsigned int left = CHAR_BIT - q->bits;
	unsigned long w = (unsigned long)v;

	if (left == 0) {
		left = CHAR_BIT;
		q->bits = 0;
		q->bytes++;

		if (q->bytes >= q->length) {
			q->next = new_bitstream();
			q = q->next;
			p->end = q;
		}

		q->source[q->bytes] = 0;
	}

	if (m > left) {
		enc_bits(p,(int)(m - left), (long)(w >> left));
		enc_bits(p,(int)left,(long)(w & mask[left]));
		return;
	}

	w <<= (left - m);
	t = q->source + q->bytes;
	*t = (byte)(*t | (byte)w);
	q->bits += m;
}


/*
    ALIGN A BITSTREAM TO A BYTE BOUNDARY

    The bitstream p is aligned to a byte boundary.
*/

void
align_bitstream(bitstream *p)
{
	int bit = (int)(bitstream_length(p)% CHAR_BIT);

	if (bit)
		enc_bits(p, CHAR_BIT - bit,(long)0);
}
