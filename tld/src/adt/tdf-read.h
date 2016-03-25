/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * tdf-read.h - TDF reader ADT.
 *
 * See the file "tdf-read.c" for more information.
 */

#ifndef H_TDF_READ
#define H_TDF_READ

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/bistream.h>
#include <exds/dstring.h>
#include "name-key.h"

typedef enum {
    RT_STREAM,
    RT_STRING
} ReaderTypeT;

typedef struct TDFReaderT {
    ReaderTypeT			type;
    union {
	BIStreamT		bistream;
	struct {
	    char *		contents;
	    char *		current;
	    char *		limit;
	    char *            name;
	    size_t		byte;
	} string;
    } u;
    ByteT			byte;
    bool			new_byte;
} TDFReaderT;

extern ExceptionT *	XX_tdf_read_error;

extern bool			tdf_reader_open
(TDFReaderT *, const char *);
extern void			tdf_reader_open_string
(TDFReaderT *, char *, NStringT *);
extern const char *			tdf_reader_name
(TDFReaderT *);
extern size_t			tdf_reader_byte
(TDFReaderT *);
extern unsigned			tdf_read_int
(TDFReaderT *);
extern void			tdf_read_align
(TDFReaderT *);
extern void			tdf_read_bytes
(TDFReaderT *, NStringT *);
extern void			tdf_read_string
(TDFReaderT *, NStringT *);
extern void			tdf_read_name
(TDFReaderT *, NameKeyT *);
extern void			tdf_read_eof
(TDFReaderT *);
extern void			tdf_reader_rewind
(TDFReaderT *);
extern void			tdf_reader_close
(TDFReaderT *);

#endif /* !defined (H_TDF_READ) */
