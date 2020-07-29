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

void dump_bitstream(BITSTREAM *bs);


/*
 * This variable gives the list of bitstreams from which new bitstreams
 * are allocated.
 */
static BITSTREAM *free_bitstreams = NULL;


/*
 * This routine creates a new bitstream with associated file f and
 * linkage lnk.
 */
BITSTREAM *
start_bitstream(FILE *f, void *lnk)
{
	BITSTREAM *bs;

	bs = free_bitstreams;
	if (bs) {
		free_bitstreams = bs->prev;
	} else {
		bs = xmalloc(sizeof *bs);
		bs->text = xmalloc(sizeof *bs->text * CHUNK_SIZE);
	}

	bs->bytes = 0;
	bs->bits  = 0;
	bs->size  = 0;
	bs->file  = f;
	bs->link  = lnk;
	bs->prev  = NULL;

	return bs;
}

/*
 * This routine frees the bitstream bs including clearing the buffer
 * for any file bitstream if w is true.
 */
void
end_bitstream(BITSTREAM *bs, int w)
{
	BITSTREAM *ps;

	ps = bs;
	if (w && ps->file) {
		/* Align bitstream and dump */
		ps = enc_boundary(ps);
		dump_bitstream(ps);
	}

	while (ps->prev != NULL) {
		ps = ps->prev;
	}

	ps->prev = free_bitstreams;
	free_bitstreams = bs;
}

/*
 * This routine returns the length of the bitstream bs in bits.
 */
unsigned
length_bitstream(BITSTREAM *bs)
{
	unsigned n;

	n = 0;
	while (bs != NULL) {
		n += BYTE_SIZE * bs->bytes + bs->bits;
		bs = bs->prev;
	}

	return n;
}

