/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * tdf-write.h - TDF writer ADT.
 *
 * See the file "tdf-write.c" for more information.
 */

#ifndef H_TDF_WRITE
#define H_TDF_WRITE

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/bostream.h>
#include <exds/dstring.h>
#include "name-key.h"

typedef struct TDFWriterT {
    BOStreamT			bostream;
    ByteT			byte;
    bool			new_byte;
} TDFWriterT;

extern bool			tdf_writer_open
(TDFWriterT *, char *);
extern const char *		tdf_writer_name
(TDFWriterT *);
extern void			tdf_write_int
(TDFWriterT *, unsigned);
extern void			tdf_write_align
(TDFWriterT *);
extern void			tdf_write_bytes
(TDFWriterT *, NStringT *);
extern void			tdf_write_string
(TDFWriterT *, NStringT *);
extern void			tdf_write_name
(TDFWriterT *, NameKeyT *);
extern void			tdf_writer_close
(TDFWriterT *);

#endif /* !defined (H_TDF_WRITE) */
