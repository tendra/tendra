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

#include "fmm.h"
#include "msgcat.h"
#include "tdf_types.h"
#include "tdf_stream.h"

/*
 * A file oriented TDF reader
 */
struct tdf_fstream {
	struct tdf_stream	s;
	FILE *				ts_file;
	int					ts_noclose;
};

static void tdf_fstream_done(struct tdf_stream *);
static size_t tdf_fstream_read(struct tdf_stream *, size_t, void *);
static BoolT tdf_fstream_read_byte(struct tdf_stream *, ByteT *);
static void tdf_fstream_rewind(struct tdf_stream *);
static void tdf_fstream_seek(struct tdf_stream *, unsigned long);

struct tdf_stream*
tdf_fstream_create(const char *name)
{
	FILE *f;
	struct tdf_fstream *sp;

	f = fopen (name, "rb");
	if (f == NULL)
		return NULL;
	sp = (struct tdf_fstream *)tdf_fstream_createf(f, name);
	sp->ts_noclose = 1;
	return (struct tdf_stream*)sp;
}

struct tdf_stream*
tdf_fstream_createf(FILE *f, const char *name)
{
	struct tdf_fstream *sp;

	sp = xmalloc (sizeof (*sp));
	tdf_stream_init(&sp->s, TDFS_MODE_READ, name);
	sp->ts_noclose = 0;
	sp->s.ts_done = tdf_fstream_done;
	sp->s.ts_read = tdf_fstream_read;
	sp->s.ts_read_byte = tdf_fstream_read_byte;
	sp->s.ts_rewind = tdf_fstream_rewind;
	sp->s.ts_seek = tdf_fstream_seek;
	sp->ts_file = f;
	return (struct tdf_stream*)sp;
}

static void
tdf_fstream_done(struct tdf_stream *asp)
{
	struct tdf_fstream *sp = (struct tdf_fstream *)asp;

	if (!sp->ts_noclose)
		(void)fclose (sp->ts_file);
}

static size_t
tdf_fstream_read(struct tdf_stream *asp, size_t length, void *dest)
{
	struct tdf_fstream *sp = (struct tdf_fstream *)asp;
	size_t nread;

	nread = fread (dest, sizeof (char), length, sp->ts_file);

	if (nread == 0 && ferror (sp->ts_file))
		MSG_fatal_tdf_stream_read_error(asp->ts_name);
	return nread;
}

static BoolT
tdf_fstream_read_byte(struct tdf_stream *asp, ByteT *bp)
{
	struct tdf_fstream *sp = (struct tdf_fstream *)asp;
	int byte;

	byte = fgetc (sp->ts_file);

	if (byte == EOF) {
		if (ferror (sp->ts_file))
			MSG_fatal_tdf_stream_read_error(asp->ts_name);
		if (feof (sp->ts_file)) {
			asp->ts_eof = 1;
			return FALSE;
		}
	}
	*bp = (ByteT)byte;
	return TRUE;
}

static void
tdf_fstream_rewind(struct tdf_stream *asp)
{
	struct tdf_fstream *sp = (struct tdf_fstream *)asp;

	rewind (sp->ts_file);
	asp->ts_pos = 0;
	asp->ts_need_byte = 1;
	asp->ts_eof = 0;
}

static void
tdf_fstream_seek(struct tdf_stream *asp, unsigned long off)
{
	struct tdf_fstream *sp = (struct tdf_fstream *)asp;

	if (fseek (sp->ts_file, (long)off, SEEK_SET))
		MSG_fatal_tdf_stream_seek_error(sp);
}
