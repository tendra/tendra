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

#ifndef TDF_STREAM_H
#define TDF_STREAM_H

/*
 * tdf_stream open mode
 */
typedef enum {
	TDFS_MODE_READ,
	TDFS_MODE_WRITE
} tdf_stream_mode;

/*
 * tdf_stream flags
 */
#define	TSF_READ		0x01		/* stream supports read operations */
#define	TSF_WRITE		0x02		/* stream supports write operations */

struct tdf_stream {
	const char *	ts_name;
	tdf_stream_mode	ts_mode;
	int				ts_flags;
	char			ts_type;
	tdf_pos			ts_pos;
	ByteT			ts_byte;
	int				ts_need_byte;
	int				ts_eof;
	size_t			ts_tdfintlen;
    void *			ts_link;		/* user defined field */
	ByteT			ts_tdfint[TDFINT_MAXLEN + 1];

	void	(*ts_done) (struct tdf_stream *);
	size_t	(*ts_read) (struct tdf_stream *, size_t, void *);
	BoolT	(*ts_read_byte) (struct tdf_stream *, ByteT *);
	void 	(*ts_rewind) (struct tdf_stream *);
	void	(*ts_seek) (struct tdf_stream *, unsigned long);
	void	(*ts_write) (struct tdf_stream *, size_t, const ByteT*);
	void	(*ts_write_byte) (struct tdf_stream *, ByteT);
};

#define	TDF_STREAM_DONE(sp)				((sp)->ts_done((sp)))
#define	TDF_STREAM_READ(sp, sz, p)		((sp)->ts_read((sp), (sz), (p)))
#define	TDF_STREAM_READ_BYTE(sp, bp)	((sp)->ts_read_byte((sp), (bp)))
#define	TDF_STREAM_REWIND(sp)			((sp)->ts_rewind(sp))
#define	TDF_STREAM_SEEK(sp, off)		((sp)->ts_seek((sp), (off)))
#define	TDF_STREAM_WRITE(sp, sz, p)		((sp)->ts_write((sp), (sz), (p)))
#define	TDF_STREAM_WRITE_BYTE(sp, b)	((sp)->ts_write_byte((sp), (b)))

/*
 * Public methods
 */
void		tdf_stream_destroy(struct tdf_stream *);
const char*	tdf_stream_name(struct tdf_stream *);
int			tdf_stream_eof(struct tdf_stream *);
void		tdf_stream_expect_eof(struct tdf_stream *);
void		tdf_stream_flush(struct tdf_stream *sp);
void		tdf_stream_read(struct tdf_stream *, size_t, void *);
void		tdf_stream_rewind(struct tdf_stream *);
void		tdf_stream_seek(struct tdf_stream *, tdf_pos);
tdf_pos		tdf_stream_tell(struct tdf_stream *);
void		tdf_stream_write(struct tdf_stream *, size_t, const ByteT *);

/*
 * Private methods
 */
void		tdf_stream_init(struct tdf_stream *, tdf_stream_mode, const char *);

/*
 * Simple and fast file oriented readonly stream.
 */
struct tdf_stream *tdf_fstream_create(const char *);
struct tdf_stream *tdf_fstream_createf(FILE *, const char *);

 /*
  * Memory oriented reader/writer
  */
struct tdf_stream *tdf_bs_create(FILE *, tdf_stream_mode, void *link);

/*
 * Common decoding functions.
 */
void		tdf_de_align(struct tdf_stream *);
unsigned long tdf_de_bits(struct tdf_stream *, unsigned int);
void		tdf_de_magic(struct tdf_stream *, const char *);
void		tdf_de_make_version(struct tdf_stream *, struct tdf_version *);
TDFBOOL		tdf_de_tdfbool(struct tdf_stream *);
TDFEXTINT	tdf_de_tdfextint(struct tdf_stream *, unsigned int);
void		tdf_de_tdfident(struct tdf_stream *, TDFIDENT *);
ByteT*		tdf_de_tdfintstr(struct tdf_stream *);
TDFINTL		tdf_de_tdfintl(struct tdf_stream *);
void		tdf_de_tdfstring(struct tdf_stream *, TDFSTRING *);
void		tdf_skip_bits(struct tdf_stream *, tdf_pos);

/*
 * Common encoding functions.
 */
void		tdf_en_align(struct tdf_stream *);
void		tdf_en_ascii(struct tdf_stream *, size_t, const unsigned char *);
void		tdf_en_bits(struct tdf_stream *, unsigned int, unsigned long);
void		tdf_en_bitstream(struct tdf_stream *, struct tdf_stream *);
void		tdf_en_cstringn(struct tdf_stream *, size_t, const char *);
struct tdf_stream *tdf_en_stream(struct tdf_stream *, struct tdf_stream *);
void		tdf_en_tdfbool(struct tdf_stream *sp, TDFBOOL v);
void		tdf_en_tdfextint(struct tdf_stream *, unsigned int, TDFEXTINT);
void		tdf_en_tdfident(struct tdf_stream *, size_t, const unsigned char *);
void		tdf_en_tdfintl(struct tdf_stream *, TDFINTL);
void		tdf_en_tdfintl_aux(struct tdf_stream *, TDFINTL);
void		tdf_en_tdfstring8(struct tdf_stream *, size_t, const unsigned char *);
void		tdf_en_ustring(struct tdf_stream *, const unsigned char *);


#endif /* !TDF_STREAM_H */
