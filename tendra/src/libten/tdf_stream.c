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
#include "ostream.h"
#include "tdf_types.h"
#include "tdf_stream.h"


static int tdf_stream_initialized;

static void
msg_uh_tdf_stream(char ch, void *pp)
{
	tdf_pos pos;
	struct tdf_stream *sp;
	const char *sname;

	UNUSED(ch);
	sp = pp;
	if (sp->ts_name)
		sname = sp->ts_name;
	else
		sname = "<noname>";
	pos = tdf_stream_tell (sp);
	write_fmt(msg_stream, "%s: at %lu.%d: ", sname,
		(unsigned long)tdf_pos_offset(pos), tdf_pos_bit(pos));
}


static void
tdf_streams_init(void)
{
	msg_uh_add(MSG_KEY_tdf_stream, msg_uh_tdf_stream);
	tdf_stream_initialized = 1;
}

/*
 * Internal method, should be called only by descendant objects.
 */
void
tdf_stream_init(struct tdf_stream *sp, tdf_stream_mode mode, const char *name)
{
	if (!tdf_stream_initialized)
		tdf_streams_init();
	memset(sp, 0, sizeof(*sp));
	sp->ts_mode = mode;
	sp->ts_name = string_copy(name);
	sp->ts_pos = 0;
	sp->ts_need_byte = 1;	/* indicate that the byte buffer is empty */
	sp->ts_eof = 0;
}

/*
 * Deallocate TDF stream.
 * Destructor TDF_STREAM_DONE() invoked prior to any destructive action.
 */
void
tdf_stream_destroy(struct tdf_stream *sp)
{
	if (sp->ts_done)
		TDF_STREAM_DONE(sp);
	if (sp->ts_name)
		string_free((char*)sp->ts_name);
	xfree(sp);
}

const char*
tdf_stream_name(struct tdf_stream *sp)
{
	return sp->ts_name;
}

int
tdf_stream_eof(struct tdf_stream *sp)
{
	return sp->ts_eof;
}

void
tdf_stream_expect_eof(struct tdf_stream *sp)
{
	ByteT b;

	if (TDF_STREAM_READ_BYTE(sp, &b))
		MSG_fatal_tdf_expect_eof(sp);
}

void
tdf_stream_flush(struct tdf_stream *sp)
{
	if (sp->ts_mode != TDFS_MODE_WRITE)
		return;
	if (tdf_pos_bit(sp->ts_pos) != 0)
		TDF_STREAM_WRITE_BYTE(sp, sp->ts_byte);
}

void
tdf_stream_rewind(struct tdf_stream *sp)
{
	tdf_stream_flush(sp);
	TDF_STREAM_REWIND(sp);
}

void
tdf_stream_seek(struct tdf_stream *sp, tdf_pos pos)
{
	TDF_STREAM_SEEK(sp, tdf_pos_offset(pos));
	sp->ts_pos = tdf_pos_align(pos);
	sp->ts_need_byte = 1;
	(void)tdf_de_bits(sp, tdf_pos_bit(pos));
}

tdf_pos
tdf_stream_tell(struct tdf_stream *sp)
{
	return sp->ts_pos;
}

void
tdf_stream_read(struct tdf_stream *sp, size_t length, void *dest)
{
	size_t nread;

	if (tdf_pos_bit(sp->ts_pos) != 0)
		MSG_int_tdf_unaligned_access(sp, "tdf_stream_read");
	nread = TDF_STREAM_READ(sp, length, dest);
	sp->ts_pos += tdf_pos_encode(nread, 0);
	sp->ts_need_byte = 1;
}

void
tdf_stream_write(struct tdf_stream *sp, size_t length, const ByteT *dp)
{
	if (tdf_pos_bit(sp->ts_pos) != 0)
		MSG_int_tdf_unaligned_access(sp, "tdf_stream_write");
	TDF_STREAM_WRITE(sp, length, dp);
	sp->ts_pos += tdf_pos_encode(length, 0);
}
