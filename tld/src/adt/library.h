/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * library.h - TDF library ADT.
 *
 * See the file "library.c" for more information.
 */

#ifndef H_LIBRARY
#define H_LIBRARY

#include "capsule.h"
#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include "shape-table.h"
#include "tdf-read.h"
#include "tdf-write.h"

typedef enum {
    LT_INPUT,
    LT_OUTPUT
} LibraryTypeT;

struct LibraryT;

typedef struct LibCapsuleT {
    struct LibraryT	       *library;
    char *			name;
    NStringT			contents;
    bool			loaded;
} LibCapsuleT;

typedef struct LibraryT {
    LibraryTypeT		type;
    union {
	TDFReaderT		reader;
	TDFWriterT		writer;
    } u;
    const char *			name;
    unsigned			num_capsules;
    LibCapsuleT *		capsules;
    unsigned			major;
    unsigned			minor;
    bool			complete;
} LibraryT;

extern char *			lib_capsule_name
(LibCapsuleT *);
extern char *			lib_capsule_full_name
(LibCapsuleT *);
extern NStringT *		lib_capsule_contents
(LibCapsuleT *);
extern bool			lib_capsule_is_loaded
(LibCapsuleT *);
extern void			lib_capsule_loaded
(LibCapsuleT *);

extern void			write_lib_capsule_full_name
(OStreamT *, LibCapsuleT *);

extern LibraryT *		library_create_stream_input
(const char *);
extern LibraryT *		library_create_stream_output
(char *);
extern const char *		library_name
(LibraryT *);
extern unsigned			library_num_capsules
(LibraryT *);
extern LibCapsuleT *	library_get_capsule
(LibraryT *, unsigned);
extern size_t			library_byte
(LibraryT *);
extern void			library_content
(LibraryT *, bool, bool, bool);
extern void			library_extract_all
(LibraryT *, bool);
extern void			library_extract
(LibraryT *, bool, bool, unsigned, char * *);
extern void			library_read
(LibraryT *, ShapeTableT *);
extern void			library_write
(LibraryT *, ShapeTableT *, unsigned, CapsuleT **);
extern void			library_close
(LibraryT *);

#endif /* !defined (H_LIBRARY) */
