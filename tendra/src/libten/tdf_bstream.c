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

#define	CHUNK_SIZE		256

struct tdf_chunk;

struct tdf_bstream {
	struct tdf_stream	s;
	FILE *				ts_file;
	struct tdf_chunk *	ts_first;
	struct tdf_chunk *	ts_last;
};

struct tdf_chunk {
	size_t				tc_offset;		/* read or write position */
	size_t				tc_size;		/* total data size in this chunk */
	struct tdf_chunk *	tc_next;		/* next chunk */
	ByteT *				tc_data;
};


static struct fmm_type *memtype_tdfbs;

static void tdf_bs_done(struct tdf_stream *);
static size_t tdf_bs_read(struct tdf_stream *, size_t, void *);
static BoolT tdf_bs_read_byte(struct tdf_stream *, ByteT *);
static void tdf_bs_rewind(struct tdf_stream *);
static void tdf_bs_write_byte(struct tdf_stream *, ByteT);
static void tdf_bs_write(struct tdf_stream *, size_t, const ByteT *);

static struct tdf_chunk *
tdf_bs_alloc_chunk(struct tdf_bstream *sp)
{
	struct tdf_chunk *chp;

	chp = fmm_malloc(sizeof(*chp), memtype_tdfbs);
	chp->tc_data = fmm_malloc(CHUNK_SIZE, memtype_tdfbs);
	chp->tc_next = NULL;
	chp->tc_offset = chp->tc_size = 0;
	return chp;
}

static void
tdf_bs_free_chunk(struct tdf_chunk *chp)
{
	fmm_free(chp->tc_data, memtype_tdfbs);
	fmm_free(chp, memtype_tdfbs);
}

/*
 * Write complete bytes to a file.
 */
static void
tdf_bs_writechunk(struct tdf_stream *asp, struct tdf_chunk *chp)
{
	struct tdf_bstream *sp = (struct tdf_bstream *)asp;
	size_t n, nw;

	n = chp->tc_size;
	chp->tc_offset = chp->tc_size = 0;
	if (n == 0)
		return;
	nw = fwrite(chp->tc_data, 1, n, sp->ts_file);
	if (nw != n)
		MSG_file_write_error(asp->ts_name);
}


struct tdf_stream*
tdf_bs_create(FILE *f, tdf_stream_mode mode, void *link)
{
    struct tdf_bstream *sp;

	if (memtype_tdfbs == NULL)
		memtype_tdfbs = fmm_type_add ("tdf_bs", "tdf bit stream");

	sp = fmm_malloc(sizeof(*sp), memtype_tdfbs);
	tdf_stream_init(&sp->s, mode, "bit stream");
	sp->ts_first = sp->ts_last = NULL;
	sp->s.ts_done = tdf_bs_done;
	sp->s.ts_rewind = tdf_bs_rewind;
	sp->s.ts_read = tdf_bs_read;
	sp->s.ts_read_byte = tdf_bs_read_byte;
	if (mode == TDFS_MODE_WRITE) {
		sp->s.ts_write = tdf_bs_write;
		sp->s.ts_write_byte = tdf_bs_write_byte;
	}
	sp->ts_file = f;
	sp->s.ts_link = link;
	sp->ts_first = sp->ts_last = tdf_bs_alloc_chunk(sp);
	return (struct tdf_stream*)sp;
}

static void
tdf_bs_done(struct tdf_stream *asp)
{
	struct tdf_bstream *sp = (struct tdf_bstream *)asp;
	struct tdf_chunk *chp, *chn;

	if (asp->ts_mode == TDFS_MODE_WRITE && sp->ts_file) {
		if (tdf_pos_bit(asp->ts_pos) != 0)
			MSG_int_tdf_extend_unaligned(asp, (long)tdf_pos_bit(asp->ts_pos));
		tdf_bs_writechunk(asp, sp->ts_last);
	}
	chp = sp->ts_first;
	while (chp) {
		chn = chp->tc_next;
		tdf_bs_free_chunk(chp);
		chp = chn;
	}
}

static size_t
tdf_bs_read(struct tdf_stream *asp, size_t n, void *dest)
{
	struct tdf_bstream *sp = (struct tdf_bstream *)asp;
	struct tdf_chunk *chp;
	ByteT *dp;
	size_t nread, toread, bytecnt;

	chp = sp->ts_last;
	if (chp == NULL)
		return 0;
	bytecnt = chp->tc_offset;
	nread = 0;
	dp = dest;
	while (n && chp) {
		toread = chp->tc_size - bytecnt;
		if (toread == 0) {
			chp = chp->tc_next;
			bytecnt = 0;
			continue;
		}
		if (n < toread)
			toread = n;
		memcpy(dp, chp->tc_data + bytecnt, toread);
		bytecnt += toread;
		chp->tc_offset = bytecnt;
		nread += toread;
		dp += toread;
		n -= toread;
	}
	sp->ts_last = chp;
	return nread;
}

static BoolT
tdf_bs_read_byte(struct tdf_stream *asp, ByteT *bp)
{
	struct tdf_bstream *sp = (struct tdf_bstream *)asp;
	struct tdf_chunk *chp;
	size_t bytecnt;

	chp = sp->ts_last;
	bytecnt = chp->tc_offset;
	if (bytecnt >= chp->tc_size) {
		chp = chp->tc_next;
		if (chp == NULL) {
			asp->ts_eof = 1;
			return (FALSE);
		}
		bytecnt = 0;
		sp->ts_last = chp;
	}
	*bp = chp->tc_data[bytecnt];
	chp->tc_offset = bytecnt + 1;
	return (TRUE);
}

static void
tdf_bs_rewind(struct tdf_stream *asp)
{
	struct tdf_bstream *sp = (struct tdf_bstream *)asp;

	asp->ts_pos = 0;
	asp->ts_need_byte = 1;
	asp->ts_eof = 0;
	asp->ts_mode = TDFS_MODE_READ;
	sp->ts_last = sp->ts_first;
	sp->ts_first->tc_offset = 0;
}

/*
 * Mark current chunk as completed and start a new one.
 */
static struct tdf_chunk*
tdf_bs_extend(struct tdf_stream *asp)
{
	struct tdf_bstream *sp = (struct tdf_bstream *)asp;
	struct tdf_chunk *chp, *np;

	chp = sp->ts_last;
	if (sp->ts_file == NULL) {
		np = tdf_bs_alloc_chunk(sp);
		sp->ts_last = chp->tc_next = np;
    	return np;
	}
	tdf_en_align(asp);
	tdf_bs_writechunk(asp, chp);
	chp->tc_size = 0;
	return chp;
}

/*
 * Append byte to a stream allocating chunks as necessary.
 */
static void
tdf_bs_write_byte(struct tdf_stream *asp, ByteT b)
{
	struct tdf_bstream *sp = (struct tdf_bstream *)asp;
	struct tdf_chunk *chp;
	size_t bytecnt;

	chp = sp->ts_last;
	bytecnt = chp->tc_offset;
	if (bytecnt >= CHUNK_SIZE) {
		chp = tdf_bs_extend(asp);
		bytecnt = 0;
	}
	chp->tc_data[bytecnt++] = b;
	chp->tc_offset = bytecnt;
	chp->tc_size++;
	return;
}

/*
 * Append a number of bytes to tdf_stream.
 */
static void
tdf_bs_write(struct tdf_stream *asp, size_t n, const ByteT *bp)
{
	struct tdf_bstream *sp = (struct tdf_bstream *)asp;
	struct tdf_chunk *chp;
	ByteT *dp;
	size_t bytecnt;

	chp = sp->ts_last;
	bytecnt = chp->tc_offset;
	dp = chp->tc_data + bytecnt;
	while (n--) {
		if (bytecnt >= CHUNK_SIZE) {
			chp->tc_offset = bytecnt;
			chp->tc_size = bytecnt;
			chp = tdf_bs_extend(asp);
			bytecnt = 0;
			dp = chp->tc_data;
		}
		*dp++ = *bp++;
		bytecnt++;
	}
	chp->tc_offset = bytecnt;
	chp->tc_size = bytecnt;
    return;
}
